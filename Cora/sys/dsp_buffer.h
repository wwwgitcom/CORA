#pragma once
#include <assert.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#include <Windows.h>


class dsp_buffer;
class dsp_buffer_reader;
typedef dsp_buffer* dsp_buffer_ptr;
typedef dsp_buffer_reader* dsp_buffer_reader_ptr;

struct dsp_vmcircbuf 
{
  int	        m_size; // in bytes
  char	     *m_base;

  HANDLE      m_hMapFile;
  LPCTSTR     m_pFirstCopy;
  LPCTSTR     m_pSecondCopy;
  BOOL        m_bLocked;

  static const  int  cNameSize = 1024;
  char        m_szName[cNameSize];

  static int  s_bufcount;

  // CREATORS
  dsp_vmcircbuf (int size);
  ~dsp_vmcircbuf();

  // ACCESSORS
  void *pointer_to_first_copy  () const { return m_base; }
  void *pointer_to_second_copy () const { return m_base + m_size; }

  static dsp_vmcircbuf* create(int size);
};

dsp_buffer_ptr dsp_make_buffer (int nitems, size_t sizeof_item);

/*!
* \brief Allocate a buffer that holds at least \p nitems of size \p sizeof_item.
*
* The total size of the buffer will be rounded up to a system
* dependent boundary.  This is typically the system page size, but
* under MS windows is 64KB.
*
* \param nitems is the minimum number of items the buffer will hold.
* \param sizeof_item is the size of an item in bytes.
* \param link is the block that writes to this buffer.
*/

/*!
* \brief Single writer, multiple reader FIFO.
*/
class dsp_buffer 
{
public:
  char				       *m_base;		// base address of buffer
  unsigned int	 			m_bufsize;	// in items
  size_t	 			      m_sizeof_item; // in bytes
  dsp_vmcircbuf      *m_vmcircbuf;
  vector<dsp_buffer_reader_ptr>	m_readers;
  
  _declspec(align(64))
    volatile unsigned int       m_write_index;	// in items [0,d_bufsize)

  

  dsp_buffer(int nitems, size_t sizeof_item);
  ~dsp_buffer();

  bool allocate_buffer (int nitems, size_t sizeof_item);

  __forceinline void reset()
  {
    m_write_index = 0;
  }

  /*!
  * \brief return number of items worth of space available for writing
  */
  int space_available ();

  /*!
  * \brief return number of items in the buf
  */
  int items_count ();

  /*!
  * \brief return size of this buffer in items
  */
  int bufsize() const { return m_bufsize; }

  /*!
  * \brief return pointer to write buffer.
  *
  * The return value points at space that can hold at least
  * space_available() items.
  */
  __forceinline void * write_pointer ()
  {
    return &m_base[m_write_index * m_sizeof_item];
  }
  /*!
  * \brief tell buffer that we wrote \p nitems into it
  */
  __forceinline void update_write_pointer (int nitems)
  {
    m_write_index       = index_add (m_write_index, nitems);
  }

  __forceinline size_t nreaders() const { return m_readers.size(); }
  __forceinline dsp_buffer_reader* reader(size_t index) { return m_readers[index]; }
  void drop_reader (dsp_buffer_reader *reader);

  __forceinline unsigned int index_add (unsigned int a, unsigned int b)
  {
    unsigned s = a + b;
    s &= (m_bufsize - 1);
    return s;
  }

  __forceinline unsigned int index_sub (unsigned int a, unsigned int b)
  {
    int s = a - b;
    s &= (m_bufsize - 1);
    return s;
  }

  void dump();

  friend dsp_buffer_ptr dsp_make_buffer (int nitems, size_t sizeof_item);
};

//////////////////////////////////////////////////////////////////////////

class dsp_buffer_reader
{
public:
  dsp_buffer_ptr          m_buffer;

  _declspec(align(64))
    volatile unsigned int   m_read_index;	// in items [0,d->buffer.d_bufsize)

  dsp_buffer_reader(dsp_buffer_ptr buffer, unsigned int read_index);
  ~dsp_buffer_reader ();

  dsp_buffer_ptr buffer () const { return m_buffer; }

  int max_possible_items_available () const { return m_buffer->m_bufsize - 1; }

  __forceinline const void* read_pointer()
  {
    return &m_buffer->m_base[m_read_index * m_buffer->m_sizeof_item];
  }
  __forceinline void update_read_pointer (int nitems)
  {
    m_read_index       = m_buffer->index_add (m_read_index, nitems);
  }

  __forceinline void reset()
  {
    m_read_index = 0;
  }

  __forceinline int items_available() const
  {
    return m_buffer->index_sub (m_buffer->m_write_index, m_read_index);
  }
};

dsp_buffer_reader_ptr dsp_buffer_add_reader (dsp_buffer_ptr buf);