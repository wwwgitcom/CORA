#include "stdafx.h"
#include "dsp_processor.h"

DWORD WINAPI cpu_processor::processor_thread(LPVOID lpdwThreadParam)
{
  cpu_processor* me = (cpu_processor*)lpdwThreadParam;

  SetThreadAffinityMask(GetCurrentThread(), me->m_affinity);

  me->Run();

  return 1;
}



void cpu_processor::Run()
{
  while (m_active)
  {
    task_obj* t = NULL;

    t = Dequeue();
    if (t)
    {
      do 
      {
        //while (t->m_status != t_run && t->m_status != t_cancel);
        if (t->status == 0)
        {
          //t->m_status = t_done;
        }
        else
        {
          //t();
        }
        t = Dequeue();
      } while (t != NULL);
      // no task to do, mark it as free
      _InterlockedXor((volatile long*)m_status_mask, m_affinity);
    }
    else
    {
      //_mm_pause();
      //Sleep(50);
      // TODO: imp. as event based or APC based
      // NOTE:: user mode APC works at passive level, no fundermental improvement
      //SleepEx(10, TRUE);
      // TODO: keep a timer, busy looping for a while then goto sleep
      m_status = idle;
      WaitForSingleObject(m_event, INFINITE);
      m_status = running;

    }
  }
}
