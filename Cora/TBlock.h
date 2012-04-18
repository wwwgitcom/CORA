#pragma once
#include "TOP.h"
#include "dsp_buffer.h"
#include <typeinfo>
#include <string>
#include <utility>
#include <map>

using namespace std;

class GlobalObj
{
public:
  int size;
  void * volatile p_var;
  string m_name;
  //void * obj;
};

class GlobalObjMan
{
  map<string, int> m_alloc_map;
public:
  GlobalObjMan()
  {
    m_alloc_map.clear();
  }
  ~GlobalObjMan()
  {
    GlobalObj *pObj = nullptr;
    for (auto i = m_alloc_map.begin(); i != m_alloc_map.end(); i++)
    {
      pObj = (GlobalObj *)i->second;
      _aligned_free(pObj->p_var);
      delete pObj;
    }
  }

  void insert(void * obj)
  {
    GlobalObj *objMeta = (GlobalObj*)obj;
    GlobalObj *pObj = nullptr;

    printf("Global MAN insert obj %s [%p]\n", objMeta->m_name.c_str(), obj);

    auto v = m_alloc_map.find(objMeta->m_name);

    if ( v != m_alloc_map.end() )
    {
      printf(" obj %s exist\n", objMeta->m_name.c_str());
      pObj = (GlobalObj *)v->second;
      objMeta->p_var = pObj->p_var;
      
      return;
    }

    pObj = new GlobalObj;
    pObj->m_name = objMeta->m_name;
    pObj->size   = objMeta->size;
    //pObj->obj    = obj;// who allocate this obj?
    objMeta->p_var  = (void *)_aligned_malloc(objMeta->size, 16);
    pObj->p_var = objMeta->p_var;
    
    m_alloc_map.insert(make_pair(objMeta->m_name, (int)pObj));
  }
};

__declspec(selectany) GlobalObjMan _GlobalObjMan;



template<typename T, int NINPUT, int NOUTPUT>
class dsp_block
{
  dsp_buffer_ptr        m_outputs[NOUTPUT + 1];// avoid zero ports
  dsp_buffer_reader_ptr m_inputs[NINPUT + 1];
public:
  dsp_block(){}
  const char* name(){return typeid(T).name();}

  // default op
  op_while_function;

  void trace()
  {
    log("%p: %s\n", this, name());
    for (int i = 0; i < NINPUT; i++)
    {
      log("  port %d: %d\n", i, ninput(i));
    }
  }

  void set_output(dsp_buffer_ptr buffer, int which)
  {
    m_outputs[which] = buffer;
  }

  void set_input(dsp_buffer_reader_ptr reader, int which)
  {
    m_inputs[which] = reader;
  }

  int ninput(int which)
  {
    return m_inputs[which]->items_available();
  }

  int noutput(int which)
  {
    return m_outputs[which]->space_available();
  }

  template<class T>
  T* input(unsigned int which){return (T*)(m_inputs[which]->read_pointer());}

  template<class T>
  T* _$(unsigned int which){return (T*)(m_inputs[which]->read_pointer());}

  template<class T>
  T* output(unsigned int which){return (T*)(m_outputs[which]->write_pointer());}

  template<class T>
  T* $_(unsigned int which){return (T*)(m_outputs[which]->write_pointer());}

  void consume (int which_input, int how_many_items)
  {
    if (how_many_items > 0) {
      m_inputs[which_input]->update_read_pointer (how_many_items);
    }
  }

  void consume_each (int how_many_items)
  {
    if (how_many_items > 0) {
      for (int i = 0; i < ninputs (); i++) {
        m_inputs[i]->update_read_pointer (how_many_items);
      }
    }
  }

  void produce (int which_output, int how_many_items)
  {
    if (how_many_items > 0){
      m_outputs[which_output]->update_write_pointer (how_many_items);
    }
  }

  void produce_each (int how_many_items)
  {
    if (how_many_items > 0) {
      for (int i = 0; i < noutputs (); i++) {
        m_outputs[i]->update_write_pointer (how_many_items);
      }
    }
  }

  template<typename T>
  __forceinline bool operator ()(T &my)
  {
    return true;
  }


  dsp_block & connect(int from_port, dsp_block &to_block, int to_port)
  {
    dsp_endpoint &from_end = CreateObject<dsp_endpoint>(*this, from_port);
    dsp_endpoint &to_end   = CreateObject<dsp_endpoint>(to_block, to_port);
    dsp_edge     &edge     = CreateObject<dsp_edge>(from_end, to_end);
    m_down_streams.push_back(edge);
    cout << this << " -> " << &to_block << endl;
    return *this;
  }
#if 0
  void _init(va_list args)
  {
    T * t = static_cast<T*>(this);
    t->init(args);
  }

  // overrideble
  void init(va_list args)
  {
  }
#endif
};


#define DEFINE_BLOCK(block_name, number_of_input, number_of_output)\
class _declspec(align(16)) block_name : public dsp_block<block_name, number_of_input, number_of_output>


#define END_BLOCK };

#define BLOCK_WORK \
public:\
__forceinline bool operator ()()

#define BLOCK_ATTRIBUTE(_type, _var)\
protected:\
  _type _var;\
public:\
  _type  get_##_var() const {return _var;}\
  void   set_##_var(_type v) {_var = v;}\
  void   set_##_var(_type& v) {_var = v;}\
public:

#define BLOCK_INIT \
public:\
void init(std::map<string, string> & $)

#define BLOCK_RESET \
public:\
void reset()


template<typename block_name>
auto _create_block(std::map<string, string> & arg_map) -> block_name &
{
  block_name & obj = CreateObject< block_name >();
  __if_exists(block_name::init)
  {
    obj.init(arg_map);
  }
  return (block_name &)obj;
}

template<typename block_name>
auto create_block(int nArg = 0, ...) -> block_name &
{
  std::map<string, string> arg_map;
  arg_map.clear();

  va_list args;
  va_start(args, nArg);

  cout << typeid(block_name).name() << endl;
  for (int i = 0; i < nArg; i++)
  {
    string str = va_arg(args, string);
    cout << "  arg " << i << ": " << str.c_str() << endl;
    int pos = str.find("=");
    if (pos < 0) continue;

    arg_map.insert( make_pair(str.substr(0, pos), str.substr(pos + 1) ) );    
  }

  va_end(args);

  return (block_name &)_create_block<block_name>(arg_map);
}


int g_test = 0;

// think about how to generate local and global vars
#define _global_(_type, _name)\
struct _global_##_name{\
  typedef _type type;\
  int size;\
  _type * volatile p_var;\
  string m_name;\
  _global_##_name() : p_var(nullptr), size(sizeof(_type)), m_name(#_name){_GlobalObjMan.insert(this);}\
  inline _type& operator *() {return *p_var;}\
  inline _type* operator &() {return  p_var;}\
  void operator=(_type &rhs){*p_var = rhs;}\
}_name;

#define _local_(_type, _name, _default)\
struct _local_##_name{\
  typedef _type type;\
  int m_size;\
  string m_name;\
  _type   m_var;\
  _local_##_name(decltype(_default) var = _default) : m_var(var), m_size(sizeof(_type)), m_name(#_name){}\
  inline _type& operator *() {return m_var;}\
  inline _type* operator &() {return  &m_var;}\
  void operator=(_type &rhs){m_var = rhs;}\
}_name;


