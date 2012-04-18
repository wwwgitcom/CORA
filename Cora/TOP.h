#pragma once

#define op_if_function bool op_if(){ return true;};
#define op_if_not_function bool op_if_not(){ return true;};
#define op_else_if_function bool op_else_if(){return true;};
#define op_else_function bool op_else(){return true;};
#define op_while_function bool op_while(){return true;};
#define op_while_not_function bool op_while_not(){return true;};

#define op_break_function bool op_break(){return true;};
#define op_stop_function bool op_stop(){return true;};


template<typename T>
class if_op
{
  T &m_t;
public:
  if_op(T &t) : m_t(t){}

  op_if_function;

  __forceinline bool operator()()
  {
    return ( m_t() );
  };
};

template<typename T>
class if_not_op
{
  T &m_t;
public:
  if_not_op(T &t) : m_t(t){}

  op_if_not_function;

  __forceinline bool operator()()
  {
    return ( m_t() );
  };
};

template <class _Function>
if_op<_Function> make_if_op(_Function& _Func)
{
    return if_op<_Function>(_Func);
}


template<typename T>
class else_if_op
{
  T &m_t;
public:
  else_if_op(T &t) : m_t(t){}

  op_else_if_function;

  __forceinline bool operator()()
  {
    return ( m_t() );
  };
};


template <class _Function>
else_if_op<_Function> make_else_if_op(_Function& _Func)
{
    return else_if_op<_Function>(_Func);
}


class else_op
{
public:
  op_else_function

  __forceinline bool operator()()
  {
    return true;
  };
};


template<typename T>
class while_op
{
  T &m_t;
public:
  while_op(T &t) : m_t(t){}

  op_while_function;

  __forceinline bool operator()()
  {
    return ( m_t() );
  };
};

template<typename T>
class while_not_op
{
  T &m_t;
public:
  while_not_op(T &t) : m_t(t){}

  op_while_not_function;

  __forceinline bool operator()()
  {
    return ( m_t() );
  };
};

template <class _Function>
while_op<_Function> make_while_op(_Function& _Func)
{
    return while_op<_Function>(_Func);
}

class semi_op
{
public:
  bool op_semi(){};

  __forceinline bool operator()()
  {
    return true;
  };
};


template<typename _Function>
if_op<_Function> IF(const _Function &_Func)
{
  return if_op<_Function>( const_cast<_Function&>(_Func) );
}

template<typename _Function>
if_not_op<_Function> IFNOT(const _Function &_Func)
{
  return if_not_op<_Function>( const_cast<_Function&>(_Func) );
}

template<typename _Function>
while_op<_Function> WHILE(const _Function &_Func)
{
  return while_op<_Function>( const_cast<_Function&>(_Func) );
}

template<typename _Function>
while_not_op<_Function> WHILENOT(const _Function &_Func)
{
  return while_not_op<_Function>( const_cast<_Function&>(_Func) );
}

template<typename _Function>
else_if_op<_Function> ELSE_IF(const _Function &_Func)
{
  return else_if_op<_Function>( const_cast<_Function&>(_Func) );
}

class break_op
{
public:
  op_break_function;

  __forceinline bool operator()()
  {
    return true;
  };
};

template<typename T>
class stop_op
{
  T &m_t;
public:
  stop_op(T &t) : m_t(t){}

  op_stop_function;

  __forceinline void operator()()
  {
    m_t();
  };
};

template<typename _Function>
stop_op<_Function> STOP(const _Function &_Func)
{
  return stop_op<_Function>( const_cast<_Function&>(_Func) );
}

#define SEMI       semi_op()
//#define IF(x)      make_if_op(x)
//#define ELSE_IF(x) SEMI, else_if_op<decltype(x)>(x)
#define ELSE       else_op()
#define BREAK      break_op()
//#define STOP      stop_op()
//#define WHILE(x)   while_op<decltype(x)>(x)

#define NOP [&]{}
#define autoref auto&