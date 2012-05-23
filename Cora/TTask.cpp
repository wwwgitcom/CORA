#include "stdafx.h"
#include "dsp_log.h"
#include "dsp_sysconfig.h"
#include "TTask.h"

DWORD WINAPI cpu_processor::processor_thread(LPVOID lpdwThreadParam)
{
  cpu_processor* me = (cpu_processor*)lpdwThreadParam;

  SetThreadAffinityMask(GetCurrentThread(), me->m_affinity);

  me->Run();

  return 1;
}

void cpu_processor::wake_up()
{
  SetEvent(m_event);
}

void cpu_processor::Run()
{
  task_obj* t = NULL;

  while (m_active)
  {
    t = Dequeue();
    if (t)
    {
      //printf("Get a work...%p\n", t);
      do 
      {
        t->invoke();
        t->done();
        t = Dequeue();
      } while (t);
      
      // BUG::: Only one task could be queued at a time.
      _InterlockedXor((volatile long*)m_status_mask, m_affinity);
      //*m_status_mask ^= m_affinity;
    }
    else
    {
      //_mm_pause();
      //Sleep(50);
      // TODO: imp. as event based or APC based
      // NOTE:: user mode APC works at passive level, no fundermental improvement
      //SleepEx(10, TRUE);
      // TODO: keep a timer, busy looping for a while then goto sleep
      //m_status = idle;
      //WaitForSingleObject(m_event, INFINITE);
      //m_status = running;
    }
  }
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

cpu_manager::cpu_manager() : m_nCurrentIndex(0), m_nTotalProcessor(0)
{
  m_sync_obj.status = 0;
  setup();
}
cpu_manager::~cpu_manager()
{
  destroy();
}

void cpu_manager::setup()
{
  static int iconfig = 0;

  printf("cpu manager configed %d times...\n", ++iconfig);

  dsp_sysconfig* config = dsp_sysconfig::Instance();
  m_nTotalProcessor     = config->GetCPUProcessorCount();
  m_cpu_count = 0;

  m_sync_obj.status = 0;

  m_cpu_array           = new cpu_processor *[m_nTotalProcessor];
  m_cpu_index           = new ULONG[m_nTotalProcessor];

  for (int i = 0; i < m_nTotalProcessor; i++)
  {
    m_cpu_array[i] = nullptr;
    m_cpu_index[i] = 0;
  }

  if (m_nTotalProcessor == 8)
  {
    //m_nTotalProcessor = 4;
    int j = 0;
    for (int i = 2; i < 8; i += 2)
    {
      cpu_processor* cpu = new cpu_processor((1L << i));
      m_sync_obj.status |= (1L << i);
      cpu->set_status_mask(&m_sync_obj.status);
      cpu->Create();
      m_cpu_array[i] = cpu;
      m_cpu_index[j] = i;
      m_cpu_count++;
      j++;

      log("create virtual processor %d\n", i);
    }
  }
  else if (m_nTotalProcessor == 12)
  {
    //m_nTotalProcessor = 6;
    int j = 0;
    for (int i = 1; i < 6; i++)
    {
      cpu_processor* cpu = new cpu_processor((1L << i));
      m_sync_obj.status |= (1L << i);
      cpu->set_status_mask(&m_sync_obj.status);
      cpu->Create();
      m_cpu_array[i] = cpu;
      m_cpu_index[j] = i;
      m_cpu_count++;
      j++;

      log("create virtual processor %d\n", i);
    }
  }
  else if (m_nTotalProcessor == 2)
  {
    int j = 0;
    for (int i = 1; i < m_nTotalProcessor; i++)
    {
      cpu_processor* cpu = new cpu_processor((1L << i));
      m_sync_obj.status |= (1L << i);
      cpu->set_status_mask(&m_sync_obj.status);
      cpu->Create();
      m_cpu_array[i] = cpu;
      m_cpu_index[j] = i;
      m_cpu_count++;
      j++;
      log("create virtual processor %d, %X\n", i, m_sync_obj.status);
    }
  }
  
}

void cpu_manager::destroy()
{
  for (int i = 0; i < m_nTotalProcessor; i++)
  {
    if (m_cpu_array[i])
    {
      m_cpu_array[i]->Destroy();
      delete m_cpu_array[i];
    }
  }

  delete[] m_cpu_array;
  delete[] m_cpu_index;
}

//////////////////////////////////////////////////////////////////////////
static cpu_manager* g_cm = cpu_manager::Instance();