#pragma once

__forceinline void _PIPE_LINE(task_obj &_Func1, task_obj &_Func2)
{
  static cpu_manager* cm = cpu_manager::Instance();

  _Func1();
  _Func2.wait();
  cm->run_task(&_Func2);
}

template<typename _Function1, typename _Function2>
__forceinline void PIPE_LINE(const _Function1 &_Func1, const _Function2 &_Func2)
{
  static cpu_manager* cm = cpu_manager::Instance();
  task_obj to = make_task_obj(_Func2);
  //to.set_as_cachable();
  cm->run_task(&to);  

  while(const_cast<_Function1&>(_Func1)())
  {
    //to.wait();
    /*while (to.status)
    {
      printf(".");
    }*/
    //cm->fast_run_task(&to);
  }
  //to.wait();  
  //to.set_as_not_cachable();
  //printf("wait %p for done, cache=%d\n", &to, to.cachable);
  //cm->fast_run_task(&to);
  
  to.wait();
}

template<typename _Function1, typename _Function2, typename _Function3>
__forceinline void PIPE_LINE(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3)
{
  static cpu_manager* cm = cpu_manager::Instance();
  task_obj to2 = make_task_obj(_Func2);
  task_obj to3 = make_task_obj(_Func3);

  cm->run_task(&to2);
  cm->run_task(&to3);

  while(const_cast<_Function1&>(_Func1)());
  to2.wait();
  to3.wait();
  //task_obj to = make_task_obj([&]
  //{
  //  _PIPE_LINE(to2, to3);
  //});

  //while(_Func1())
  //{
  //  to.wait();
  //  cm->run_task(&to);
  //}
  //to.wait();
  //cm->run_task(&to);
  //to.wait();
  //to3.wait();

}

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4>
__forceinline void PIPE_LINE(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4)
{
  static cpu_manager* cm = cpu_manager::Instance();
  task_obj to2 = make_task_obj(_Func2);
  task_obj to3 = make_task_obj(_Func3);
  task_obj to4 = make_task_obj(_Func4);

  task_obj to34 = make_task_obj([&]
  {
    _PIPE_LINE(to3, to4);
  });
  
  task_obj next = make_task_obj([&]
  {
    _PIPE_LINE(to2, to34);
  });

  while(_Func1())
  {
    next.wait();
    cm->run_task(&next);
  }
  next.wait();
  cm->run_task(&next);
  next.wait();
  to34.wait();
  to4.wait();
}

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5>
__forceinline void PIPE_LINE(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5)
{
  static cpu_manager* cm = cpu_manager::Instance();
  task_obj to2 = make_task_obj(_Func2);
  task_obj to3 = make_task_obj(_Func3);
  task_obj to4 = make_task_obj(_Func4);
  task_obj to5 = make_task_obj(_Func5);

  task_obj to45 = make_task_obj([&]
  {
    _PIPE_LINE(to4, to5);
  });

  task_obj to345 = make_task_obj([&]
  {
    _PIPE_LINE(to3, to45);
  });

  task_obj next = make_task_obj([&]
  {
    _PIPE_LINE(to2, to345);
  });

  while(_Func1())
  {
    next.wait();
    cm->run_task(&next);
  }
  next.wait();
  cm->run_task(&next);
  next.wait();
  to345.wait();
  to45.wait();
  to5.wait();
}

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6>
__forceinline void PIPE_LINE(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6)
{
  static cpu_manager* cm = cpu_manager::Instance();
  task_obj to2 = make_task_obj(_Func2);
  task_obj to3 = make_task_obj(_Func3);
  task_obj to4 = make_task_obj(_Func4);
  task_obj to5 = make_task_obj(_Func5);
  task_obj to6 = make_task_obj(_Func6);

  task_obj to56 = make_task_obj([&]
  {
    _PIPE_LINE(to5, to6);
  });

  task_obj to456 = make_task_obj([&]
  {
    _PIPE_LINE(to4, to56);
  });

  task_obj to3456 = make_task_obj([&]
  {
    _PIPE_LINE(to3, to456);
  });

  task_obj to23456 = make_task_obj([&]
  {
    _PIPE_LINE(to2, to3456);
  });

  while(_Func1())
  {
    to23456.wait();
    cm->run_task(&to23456);
  }
  to23456.wait();
  cm->run_task(&to23456);
  to23456.wait();
  to3456.wait();
  to456.wait();
  to56.wait();
  to6.wait();
}


