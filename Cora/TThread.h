#pragma once

enum : unsigned int
{
  _waiting = 0,
  _running,
  _done,
  _cancel
};



template<typename _Function>
class TThread
{
  _Function m_func;
  volatile unsigned int m_cancle;
  volatile unsigned int m_status;
  volatile unsigned int m_stop;
  volatile unsigned int m_affinity;
  HANDLE   m_hThread;
public:
  TThread(_Function func) : m_func(func)
  {
    m_hThread = CreateThread(NULL, 0, TThread::_thread, this, 0, NULL);
    printf("Thread handle = %p\n", m_hThread);
  }

  ~TThread()
  {
    if (m_hThread) CloseHandle(m_hThread);
  }

  void run()
  {
    m_func();
  }

  void wait()
  {
    while(m_status != _done && m_status != _cancel) __asm pause;
  }

  static unsigned long __stdcall _thread(LPVOID lpVoid)
  {
    TThread* func = (TThread*)lpVoid;
    //SetThreadAffinityMask(GetCurrentThread(), me->m_viterbi_affinity);
    //SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
    printf("  ::Thread handle = %p\n", GetCurrentThread());
    func->m_status = _running;
    func->run();
    func->m_status = _done;
    cout << "thread done" << endl;
    return 0;
  }
};

template<typename _Function>
TThread<_Function> make_thread(_Function &func)
{
  return TThread<_Function>(func);
}