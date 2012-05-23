#pragma once
#include "dsp_helper.h"
// already defined in ppl.h
//typedef void (__cdecl * TaskProc)(void *);

const size_t CacheLineSize = 64;

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
  SLIST_ENTRY               entry;
  TaskProc                  proc;
  void *                    obj;

  __forceinline void operator ()()
  {
    proc(obj);
  }

  __forceinline void invoke()
  {
    proc(obj);
  }

  __forceinline void done()
  {
    status = 0;
  }

  __forceinline void wait()
  {
    while (status)
    {
      //printf("waiting task for done\n");
      __asm pause;
    }
  }
};

class task_obj : public _task_obj
{
  padded<_task_obj> pad;
};

//////////////////////////////////////////////////////////////////////////


class _UnrealizedChore
{
public:
  // Invocation bridge between the _UnrealizedChore and PPL.
  template <typename _ChoreType>
  static void __cdecl _InvokeBridge(_ChoreType * _PChore)
  {
    (*_PChore)();
  }
  template <typename _ChoreType>
  static void __cdecl _InvokeBridgeRef(_ChoreType & _PChore)
  {
    _PChore();
  }
};


template<typename _Function>
class dsp_task
{
  TaskProc m_pFunction;
  _Function _M_function;
  dsp_task const & operator=(dsp_task const&);    // no assignment operator
public:

  TaskProc GetProc() const {return m_pFunction;}

  dsp_task(const _Function &function) : _M_function(function)
  {
    m_pFunction = reinterpret_cast <TaskProc> (&::_UnrealizedChore::_InvokeBridge<dsp_task>);
  }

  __forceinline void operator()() const {_M_function();}

  // mark
  void IsDspTask(){}
};


template <class _Function>
dsp_task<_Function> make_dsp_task(const _Function& _Func)
{
    return dsp_task<_Function>(_Func);
}

template <class _Function>
task_obj make_task_obj(const _Function& _Func)
{
  task_obj to;
  to.status = 0;
  to.proc   = reinterpret_cast <TaskProc> (&::_UnrealizedChore::_InvokeBridgeRef<_Function>);
  to.obj    = &const_cast<_Function&>(_Func);
  return to;
}

template <class _Function>
task_obj make_task_obj(const dsp_task<_Function>& tsk)
{
  task_obj to;
  to.status = 0;
  to.proc   = tsk.GetProc();
  to.obj    = &const_cast<dsp_task<_Function>&>(tsk);
  return to;
}

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
    m_task_count   = 0;
    m_event        = CreateEvent(NULL, FALSE, FALSE, NULL);
    InitializeSListHead(&m_TaskList);
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
    WaitForSingleObject(m_hThread, INFINITE);
    CloseHandle(m_hThread);
    m_hThread = INVALID_HANDLE_VALUE;
  }

  __forceinline void Enqueue(task_obj* t)
  {
    t->status = 1;
    //m_spinlock.Acquire();
    InterlockedPushEntrySList(&this->m_TaskList, &t->entry);
    _InterlockedIncrement(&m_task_count);
    //m_spinlock.Release();
  }

  __forceinline task_obj* Dequeue()
  {
    task_obj* t            = NULL;
    PSLIST_ENTRY pListEntry = NULL;

    do 
    {
      if (!m_task_count)
      {
        break;
      }
      //m_spinlock.Acquire();
      //if (IsListEmpty(&this->m_TaskList))
      //if (!m_task_count)
      //{
      //  m_spinlock.Release();
      //  break;
      //}

      pListEntry = InterlockedPopEntrySList(&this->m_TaskList);
      _InterlockedDecrement(&m_task_count);
      //m_spinlock.Release();

      t = CONTAINING_RECORD(pListEntry, task_obj, entry);
    } while (FALSE);

    return t;
  }

  void wake_up();

  void Run();

  void Stop()
  {
    m_active = false;
    TerminateThread(m_hThread, 0);
  }

  void set_status_mask(volatile unsigned int* mask){m_status_mask = mask;}

  enum status
  {
    running, idle
  };
  status processor_status() const {return m_status;}

private:
  volatile ULONG  m_active;
  volatile LONG   m_task_count;
  volatile status m_status;
  dsp_spin_lock   m_spinlock;  
  volatile unsigned int* m_status_mask;

  SLIST_HEADER    m_TaskList;
  HANDLE          m_hThread;
  HANDLE          m_event;
  DWORD           m_affinity;
};


//////////////////////////////////////////////////////////////////////////
class cpu_manager
{
private:
  sync_obj        m_sync_obj;
  cpu_processor **m_cpu_array;
  ULONG          *m_cpu_index;
  ULONG           m_cpu_count;
  int             m_nCurrentIndex;

  int             m_nTotalProcessor;  
  dsp_spin_lock   m_lock;

  cpu_manager();
  cpu_manager(const cpu_manager&) ;
  cpu_manager& operator=(const cpu_manager&) ;
  void setup();
  void destroy();
public:
  ~cpu_manager();

  __forceinline static cpu_manager* Instance()
  {
    static cpu_manager s_cpu_manager;

    return &s_cpu_manager;
  }

  __forceinline void run_task(task_obj* t)
  {
    DWORD dwFreeCpu = 0;

    m_lock.Acquire();

    //printf("[cpu_man] status %p.\n", m_sync_obj.status);
    if (_BitScanForward(&dwFreeCpu, m_sync_obj.status))
    {
      //debug
      //dwFreeCpu = 1;

      _InterlockedXor((volatile long*)&m_sync_obj.status, (1L << dwFreeCpu));
      //m_sync_obj.status ^= (1L << dwFreeCpu);
      
      m_cpu_array[dwFreeCpu]->Enqueue(t);
      //if (m_cpu_array[dwFreeCpu]->processor_status() == cpu_processor::idle)
      //{
      //  m_cpu_array[dwFreeCpu]->wake_up();
      //}
      //printf("[cpu_man] enqueue task %p to processor %d.\n", t, (1L << dwFreeCpu));
    }
    else
    {
      printf("[cpu_man] random access status %p.\n", m_sync_obj.status);
      t->invoke();
      t->done();
#if 0
      // all cpu are busy, use random cpu
      printf("[cpu_man] random access status %p.\n", m_sync_obj.status);
      m_cpu_array[m_cpu_index[m_nCurrentIndex]]->Enqueue(t);
      printf("[cpu_man] random enqueue task %p to processor %d.\n", t, m_cpu_index[m_nCurrentIndex]);
      m_nCurrentIndex++;
      m_nCurrentIndex %= m_cpu_count;
#endif
    }
    m_lock.Release();
  }
};



//////////////////////////////////////////////////////////////////////////


enum dsp_task_group_status
{
    /// <summary>
    ///     The tasks queued to the <c>task_group</c> object have not completed.  Note that this value is not presently returned by
    ///     the Concurrency Runtime.
    /// </summary>
    /**/
    not_complete,

    /// <summary>
    ///     The tasks queued to the <c>task_group</c> or <c>structured_task_group</c> object completed successfully.
    /// </summary>
    /**/
    completed,

    /// <summary>
    ///     The <c>task_group</c> or <c>structured_task_group</c> object was canceled.  One or more tasks may not have executed.
    /// </summary>
    /**/
    canceled
};

class dsp_task_group
{
public:
  template<typename _Function>
  void run(_Function& _Func)
  {
    _Func();
    // CPU.Schedule(_Func);
    //_M_task_collection._Schedule(::Concurrency::details::_UnrealizedChore::_InternalAlloc<task_handle<_Function>, _Function>(_Func));
  }
  template<typename _Function>
  void run(dsp_task<_Function>& _Task)
  {
    _Task();
    //_Task_handle._SetRuntimeOwnsLifetime(false);
    //_M_task_collection._Schedule(&_Task_handle);
  }
  template<class _Function>
  dsp_task_group_status run_and_wait(dsp_task<_Function>& _Task_handle)
  {
    //
    // The underlying scheduler's definitions map exactly to the PPL's.  No translation beyond the cast is necessary.
    //
    //_Task_handle._SetRuntimeOwnsLifetime(false);
    //return (task_group_status)_M_task_collection._RunAndWait(&_Task_handle);
    _Task_handle();
    return dsp_task_group_status::completed;
  }

  template<class _Function>
  dsp_task_group_status run_and_wait(_Function& _Func)
  {
    //
    // The underlying scheduler's definitions map exactly to the PPL's.  No translation beyond the cast is necessary.
    //
    //return (dsp_task_group_status)_M_task_collection._RunAndWait(::Concurrency::details::_UnrealizedChore::_InternalAlloc<task_handle<_Function>, _Function>(_Func));
    _Func();
    return dsp_task_group_status::completed;
  }
private:
  // Disallow passing in an r-value for a task handle argument
  template<class _Function> void run(dsp_task<_Function>&& _Task_handle);
};
