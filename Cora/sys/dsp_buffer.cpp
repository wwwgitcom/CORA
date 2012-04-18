#include "stdafx.h"
#include "dsp_buffer.h"
#include "dsp_sysconfig.h"

int GreatestCommonDivisor(int x, int y)
{
  while (y != 0)
  {
    const int temp = y;
    y = x % y;
    x = temp;
  }
  return x;
}

/*
* Compute the minimum number of buffer items that work (i.e.,
* address space wrap-around works).  To work is to satisfy this
* contraint for integer buffer_size and k:
*
*     type_size * nitems == k * page_size
*/
static long minimum_buffer_items (long type_size, long granularity)
{
  return granularity / GreatestCommonDivisor(type_size, granularity);
}

/*
LPVOID WINAPI MapViewOfFileEx(
__in      HANDLE hFileMappingObject,
__in      DWORD dwDesiredAccess,
__in      DWORD dwFileOffsetHigh,
__in      DWORD dwFileOffsetLow,
__in      SIZE_T dwNumberOfBytesToMap,
__in_opt  LPVOID lpBaseAddress
);

lpBaseAddress [in, optional]
A pointer to the memory address in the calling process address space where mapping begins.
This must be a multiple of the system's memory allocation granularity, or the function fails.
To determine the memory allocation granularity of the system, use the GetSystemInfo function.
If there is not enough address space at the specified address, the function fails.
If lpBaseAddress is NULL, the operating system chooses the mapping address. 
In this scenario, the function is equivalent to the MapViewOfFile function.
While it is possible to specify an address that is safe now (not used by the operating system), 
there is no guarantee that the address will remain safe over time. 
Therefore, it is better to let the operating system choose the address. 
In this case, you would not store pointers in the memory mapped file, you would store offsets 
from the base of the file mapping so that the mapping can be used at any address.

To obtain the size of a view, use the VirtualQueryEx function.
The initial contents of the pages in a file mapping object backed by the page file are 0 (zero).
If a suggested mapping address is supplied, the file is mapped at the specified address 
(rounded down to the nearest 64K-boundary) if there is enough address space at the specified address. 
If there is not enough address space, the function fails.
Typically, the suggested address is used to specify that a file should be mapped at the same address
in multiple processes. This requires the region of address space to be available in all involved processes. 
No other memory allocation can take place in the region that is used for mapping, 
including the use of the VirtualAlloc or VirtualAllocEx function to reserve memory.
If the lpBaseAddress parameter specifies a base offset, the function succeeds if the specified memory region
is not already in use by the calling process. The system does not ensure that the same memory region 
is available for the memory mapped file in other 32-bit processes.
Multiple views of a file (or a file mapping object and its mapped file) are coherent 
if they contain identical data at a specified time. 
This occurs if the file views are derived from the same file mapping object. 
A process can duplicate a file mapping object handle into another process by using the DuplicateHandle function, 
or another process can open a file mapping object by name by using the OpenFileMapping function.
*/
int dsp_vmcircbuf::s_bufcount = 0;
dsp_vmcircbuf* dsp_vmcircbuf::create(int size)
{
  int actualsize        = size << 1;
  LPVOID  lpMemReserved = NULL;
  dsp_vmcircbuf* pvmBuf = NULL;

  lpMemReserved = VirtualAlloc( NULL, actualsize, MEM_RESERVE, PAGE_READWRITE );

  printf("Alloc virtual memory %p.\n", lpMemReserved);

  if( lpMemReserved == NULL ) 
  {
    printf("Cannot reserve memory.\n");
    return NULL;
  }
  VirtualFree( lpMemReserved, 0, MEM_RELEASE );

  //////////////////////////////////////////////////////////////////////////

  pvmBuf = new dsp_vmcircbuf(size);

  if (NULL == pvmBuf)
  {
    return NULL;
  }

  memset(pvmBuf->m_szName, 0, cNameSize);
  sprintf_s(pvmBuf->m_szName, "dsp_vmcircbuf_%d", dsp_vmcircbuf::s_bufcount++);

  pvmBuf->m_hMapFile = CreateFileMapping(
    INVALID_HANDLE_VALUE,    // use paging file
    NULL,                    // default security
    PAGE_READWRITE,          // read/write access
    0,                       // maximum object size (high-order DWORD)
    size,        // maximum object size (low-order DWORD)
    pvmBuf->m_szName);                 // name of mapping object

  if (pvmBuf->m_hMapFile == NULL)
  {
    printf("Could not create file mapping object (%d).\n", GetLastError());
    delete pvmBuf;
    return NULL;
  }

  pvmBuf->m_pFirstCopy = (LPTSTR) MapViewOfFileEx(pvmBuf->m_hMapFile,   // handle to map object
    FILE_MAP_ALL_ACCESS, // read/write permission
    0,
    0,
    size,
    lpMemReserved);

  if (pvmBuf->m_pFirstCopy == NULL)
  {
    printf("Could not map view of file (%d).\n", GetLastError());
    delete pvmBuf;
    return NULL;
  }

  pvmBuf->m_bLocked = VirtualLock((LPVOID)pvmBuf->m_pFirstCopy, size);
  if ( !pvmBuf->m_bLocked )
  {
    printf("Cannot lock spaces into physical memory!\n");
  }

  pvmBuf->m_pSecondCopy = (LPTSTR) MapViewOfFileEx(pvmBuf->m_hMapFile,   // handle to map object
    FILE_MAP_ALL_ACCESS, // read/write permission
    0,
    0,
    size,
    (PVOID)((char*)lpMemReserved + size));

  if (pvmBuf->m_pSecondCopy == NULL)
  {
    printf("Could not map view of file (%d).\n", GetLastError());
    delete pvmBuf;
    return NULL;
  }

  assert(pvmBuf->m_pFirstCopy + size == pvmBuf->m_pSecondCopy);

  pvmBuf->m_base = (char*)pvmBuf->m_pFirstCopy;

  return pvmBuf;
}

dsp_vmcircbuf::dsp_vmcircbuf(int size) : m_size(size), m_base(0), m_hMapFile(0),
  m_pFirstCopy(0), m_pSecondCopy(0), m_bLocked(false)
{
}

dsp_vmcircbuf::~dsp_vmcircbuf()
{
  if (m_pFirstCopy)
  {
    if (m_bLocked)
    {
      VirtualUnlock((LPVOID)m_pFirstCopy, m_size);
    }
    UnmapViewOfFile(m_pFirstCopy);
    m_pFirstCopy = NULL;
  }

  if (m_pSecondCopy)
  {
    UnmapViewOfFile(m_pSecondCopy);
    m_pSecondCopy = NULL;
  }

  if (m_hMapFile)
  {
    CloseHandle(m_hMapFile);
  }
  m_base = NULL;
  m_size = 0;
}
//////////////////////////////////////////////////////////////////////////

dsp_buffer_ptr 
  dsp_make_buffer (int nitems, size_t sizeof_item)
{
  return dsp_buffer_ptr(new dsp_buffer(nitems, sizeof_item));
}

int dsp_buffer::space_available ()
{
  if (m_readers.empty ())
  {
    return m_bufsize - 1;	// See comment below
  }
  else 
  {
    // Find out the maximum amount of data available to our readers

    int	most_data                   = m_readers[0]->items_available();

    for (size_t i = 1; i < m_readers.size (); i++) 
    {
      most_data      = max(most_data, m_readers[i]->items_available());
    }

    // The -1 ensures that the case d_write_index == d_read_index is
    // unambiguous.  It indicates that there is no data for the reader

    return m_bufsize - most_data - 1;
  }
}

void * dsp_buffer::write_pointer ()
{
  return &m_base[m_write_index * m_sizeof_item];
}

void dsp_buffer::update_write_pointer (int nitems)
{
  m_write_index       = index_add (m_write_index, nitems);
  m_abs_write_offset += nitems;
  //dump();
}

unsigned int dsp_buffer::index_add (unsigned int a, unsigned int b)
{
  unsigned s = a + b;
  s &= (m_bufsize - 1);
  //if (s >= m_bufsize)
  //    s -= m_bufsize;

  assert (s < m_bufsize);
  return s;
}

unsigned int dsp_buffer::index_sub (unsigned int a, unsigned int b)
{
  int s = a - b;
  s &= (m_bufsize - 1);
  //if (s < 0)
  //    s += m_bufsize;

  assert ((unsigned) s < m_bufsize);
  return s;
}

void dsp_buffer::dump()
{
  printf("[dump_buffer] %p write index: %d\n", m_base, m_write_index);
  for (size_t i = 0; i < m_readers.size (); i++) 
  {
    printf(" [dump_buffer]read index: %d\n", m_readers[i]->m_read_index);
  }
}


bool dsp_buffer::allocate_buffer (int nitems, size_t sizeof_item)
{
  int	orig_nitems = nitems;

  // Any buffer size we come up with must be a multiple of min_nitems.

  int granularity = dsp_sysconfig::Instance()->GetAllocationGranularity();
  int min_nitems  =  minimum_buffer_items (sizeof_item, granularity);

  // Round-up nitems to a multiple of min_nitems.

  if (nitems % min_nitems != 0)
    nitems = ((nitems / min_nitems) + 1) * min_nitems;

  // If we rounded-up a whole bunch, give the user a heads up.
  // This only happens if sizeof_item is not a power of two.

  //if (nitems > 2 * orig_nitems && nitems * (int) sizeof_item > granularity)
  {
    cout << "dsp_buffer::allocate_buffer: warning: tried to allocate\n"
      << "   " << orig_nitems << " items of size "
      << sizeof_item << ". Due to alignment requirements\n"
      << "   " << nitems << " were allocated.  If this isn't OK, consider padding\n"
      << "   your structure to a power-of-two bytes.\n"
      << "   On this platform, our allocation granularity is " << granularity << " bytes.\n";
  }

  m_bufsize = nitems;
  m_vmcircbuf = dsp_vmcircbuf::create(m_bufsize * m_sizeof_item);
  if (m_vmcircbuf == 0){
    cerr << "gr_buffer::allocate_buffer: failed to allocate buffer of size "
      << m_bufsize * m_sizeof_item / 1024 << " KB\n";
    return false;
  }

  m_base = (char *) m_vmcircbuf->pointer_to_first_copy ();
  return true;
}

dsp_buffer::dsp_buffer (int nitems, size_t sizeof_item)
  : m_base (0), m_bufsize (0), m_vmcircbuf (0),
  m_sizeof_item (sizeof_item),
  m_write_index (0), m_abs_write_offset(0),
  m_last_min_items_read(0)
{
  if (!allocate_buffer (nitems, sizeof_item))
    throw std::bad_alloc ();
}

dsp_buffer::~dsp_buffer()
{
  if (m_vmcircbuf)
  {
    delete m_vmcircbuf;
    m_vmcircbuf = NULL;
  }

  //assert (m_readers.size() == 0);
}


void dsp_buffer::drop_reader (dsp_buffer_reader *reader)
{
  std::vector<dsp_buffer_reader *>::iterator result =
    std::find (m_readers.begin (), m_readers.end (), reader);

  if (result == m_readers.end ())
  {
    throw std::invalid_argument ("dsp_buffer::drop_reader");    // we didn't find it...
  }

  m_readers.erase (result);
}

dsp_buffer_reader_ptr
  dsp_buffer_add_reader (dsp_buffer_ptr buf)
{
  dsp_buffer_reader *r = new dsp_buffer_reader (buf, buf->m_write_index);
  buf->m_readers.push_back (r);

  return r;
}

//////////////////////////////////////////////////////////////////////////
dsp_buffer_reader::dsp_buffer_reader(dsp_buffer_ptr buffer, unsigned int read_index)
  : m_buffer(buffer), m_read_index(read_index), m_abs_read_offset(0)
{
}

dsp_buffer_reader::~dsp_buffer_reader ()
{
  //m_buffer->drop_reader(this);
}

const void* dsp_buffer_reader::read_pointer()
{
  return &m_buffer->m_base[m_read_index * m_buffer->m_sizeof_item];
}

int dsp_buffer_reader::items_available() const
{
  return m_buffer->index_sub (m_buffer->m_write_index, m_read_index);
}

void dsp_buffer_reader::update_read_pointer (int nitems)
{
  m_read_index       = m_buffer->index_add (m_read_index, nitems);
  m_abs_read_offset += nitems;
}
