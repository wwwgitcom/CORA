#pragma once

template<typename _Function1, typename _Function2>
void PIPE_LINE(_Function1 &_Func1, _Function2 &_Func2)
{
  static cpu_manager* cm = cpu_manager::Instance();
  task_obj to = make_task_obj(_Func2);

  while(_Func1())
  {
    to.wait();
    cm->run_task(&to);
  }
  to.wait();
  cm->run_task(&to);
  to.wait();
}

__forceinline void _PIPE_LINE(task_obj &_Func1, task_obj &_Func2)
{
  static cpu_manager* cm = cpu_manager::Instance();

  _Func1();
  _Func2.wait();
  cm->run_task(&_Func2);
}

template<typename _Function1, typename _Function2, typename _Function3>
void PIPE_LINE(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3)
{
  static cpu_manager* cm = cpu_manager::Instance();
  task_obj to2 = make_task_obj(_Func2);
  task_obj to3 = make_task_obj(_Func3);

  task_obj to = make_task_obj([&]
  {
    _PIPE_LINE(to2, to3);
  });

  while(_Func1())
  {
    to.wait();
    cm->run_task(&to);
  }
  to.wait();
  cm->run_task(&to);
  to.wait();
  to3.wait();
}

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4>
void PIPE_LINE(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4)
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
void PIPE_LINE(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5)
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




