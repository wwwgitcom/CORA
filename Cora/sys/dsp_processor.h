#pragma once
#include "dsp_helper.h"

const size_t CacheLineSize = 64;

typedef void (*task_function)();

//////////////////////////////////////////////////////////////////////////

template<class T, int Size>
struct padded_base : T {
  char pad[CacheLineSize - sizeof(T) % CacheLineSize];
};
template<class T> struct padded_base<T, 0> : T {};

//! Pads type T to fill out to a multiple of cache line size.
template<class T>
struct padded : padded_base<T, sizeof(T)> {};

//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
class __declspec(align(64)) _sync_obj
{
public:
  volatile unsigned __int32 status;
};

class sync_obj : public _sync_obj
{
  padded<_sync_obj> pad;
};

//////////////////////////////////////////////////////////////////////////

class __declspec(align(64)) _task_obj
{
public:
  volatile unsigned __int32 status;
  LIST_ENTRY                entry;
  void *                    obj;
};

class task_obj : public _task_obj
{
  padded<_task_obj> pad;
};

//////////////////////////////////////////////////////////////////////////

class cpu_processor
{
public:
  cpu_processor(DWORD affinity = 0xFFFFFFFF)
  {
    m_hThread      = INVALID_HANDLE_VALUE;
    m_affinity     = affinity;
    m_active       = true;
    m_status       = idle;
    m_event        = CreateEvent(NULL, FALSE, FALSE, NULL);
    InitializeListHead(&m_TaskList);
  }

  static DWORD WINAPI processor_thread(LPVOID lpThreadParam);

  void Create()
  {
    m_active  = true;
    m_hThread = CreateThread(NULL, 0, cpu_processor::processor_thread, this, 0, NULL);
    SetThreadAffinityMask(m_hThread, m_affinity);
    //SetThreadPriority(m_hThread, THREAD_PRIORITY_TIME_CRITICAL);
  }

  void Destroy()
  {
    m_active = false;
    CloseHandle(m_hThread);
    m_hThread = INVALID_HANDLE_VALUE;
  }

  void Enqueue(task_obj* t)
  {
    m_spinlock.Acquire();
    InsertTailList(&this->m_TaskList, &t->entry);
    m_spinlock.Release();
  }

  task_obj* Dequeue()
  {
    task_obj* t                = NULL;
    PLIST_ENTRY pListEntry = NULL;

    do 
    {
      if (IsListEmpty(&this->m_TaskList))
      {
        break;
      }

      m_spinlock.Acquire();
      pListEntry = RemoveHeadList(&this->m_TaskList);
      m_spinlock.Release();

      t = CONTAINING_RECORD(pListEntry, task_obj, entry);
    } while (FALSE);

    return t;
  }

  void Run();

  void Stop()
  {
    m_active = false;
    TerminateThread(m_hThread, 0);
  }

  void set_status_mask(volatile unsigned int* mask){m_status_mask = mask;}

  LIST_ENTRY      m_ListEntry;

  enum status
  {
    running, idle
  };
  status processor_status() const {return m_status;}
  void wake_up();

private:
  volatile ULONG  m_active;
  volatile status m_status;

  HANDLE          m_hThread;
  HANDLE          m_event;
  DWORD           m_affinity;
  dsp_spin_lock   m_spinlock;
  LIST_ENTRY      m_TaskList;
  volatile unsigned int* m_status_mask;
};