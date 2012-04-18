#pragma once

template<typename _Function>
class dsp_task
{
  _Function m_function;
  dsp_task const & operator=(dsp_task const&);    // no assignment operator
public:
  dsp_task(_Function &function) : m_function(function){}
  __forceinline void operator()(){m_function();}
};


template <class _Function>
dsp_task<_Function> make_dsp_task(_Function& _Func)
{
    return dsp_task<_Function>(_Func);
}


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
};
