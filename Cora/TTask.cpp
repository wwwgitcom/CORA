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
        
        //printf("work %p status %d cache %d\n", t, t->status, t->cachable);

        //if (t->cachable)
        //{
        //  //while (!t->status)
        //  //{
        //  //  __asm pause;
        //  //}
        //  continue;
        //}

        //printf("work done %p status %d cache %d\n", t, t->status, t->cachable);
        
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
  dsp_sysconfig* config = dsp_sysconfig::Instance();
  m_nTotalProcessor     = config->GetCPUProcessorCount();
  m_cpu_count = 0;

  m_sync_obj.status = 0;

  // create CPUs from config file
  
  do 
  {
    FILE* hCPUConfig;
    errno_t err;

    err = fopen_s(&hCPUConfig, "CPUConfig.txt", "r");
    
    if (err != 0)
    {
      break;
    }

    ULONG nAffinity;
    while (!feof(hCPUConfig))
    {
      nAffinity = 0; 
      fscanf_s(hCPUConfig, "%d\n", &nAffinity);

      if (nAffinity == 0)
      {
        printf("Invalid affinity 0, skip....\n");
        continue;
      }

      if (nAffinity >= m_nTotalProcessor)
      {
        printf("Invalid affinity %d on this CPU, should be less than %d....\n", m_nTotalProcessor);
        continue;
      }

      m_sync_obj.status |= (1L << nAffinity);
      m_cpus[nAffinity].set_status_mask(&m_sync_obj.status);
      m_cpus[nAffinity].Create((1L << nAffinity));
    }

    fclose(hCPUConfig);
    return;
  } while (false);

  // create CPUs as usual
  m_cpu_index           = new ULONG[m_nTotalProcessor];

  for (ULONG i = 0; i < m_nTotalProcessor; i++)
  {
    m_cpu_index[i] = 0;
  }

  if (m_nTotalProcessor == 8)
  {
    //m_nTotalProcessor = 4;
    int j = 0;
    for (int i = 1; i < 8; i += 2)
    {
      m_sync_obj.status |= (1L << i);
      m_cpus[i].set_status_mask(&m_sync_obj.status);
      m_cpus[i].Create((1L << i));
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
    for (int i = 6; i < 12; i++)
    {
      m_sync_obj.status |= (1L << i);
      m_cpus[i].set_status_mask(&m_sync_obj.status);
      m_cpus[i].Create((1L << i));
      m_cpu_index[j] = i;
      m_cpu_count++;
      j++;

      log("create virtual processor %d\n", i);
    }
  }
  else if (m_nTotalProcessor == 2)
  {
    int j = 0;
    for (ULONG i = 0; i < m_nTotalProcessor; i++)
    {
      m_sync_obj.status |= (1L << i);
      m_cpus[i].set_status_mask(&m_sync_obj.status);
      m_cpus[i].Create((1L << i));
      m_cpu_index[j] = i;
      m_cpu_count++;
      j++;
      log("create virtual processor %d, %X\n", i, m_sync_obj.status);
    }
  }
  else
  {
    ULONG j = 0;
    for (ULONG i = 1; i < m_nTotalProcessor; i++)
    {
      m_sync_obj.status |= (1L << i);
      m_cpus[i].set_status_mask(&m_sync_obj.status);
      m_cpus[i].Create((1L << i));
      m_cpu_index[j] = i;
      m_cpu_count++;
      j++;
      log("create virtual processor %d, %X\n", i, m_sync_obj.status);
    }
  }
  
}

void cpu_manager::destroy()
{
  for (int i = 0; i < 16; i++)
  {
    m_cpus[i].Destroy();
  }
  delete[] m_cpu_index;
}

//////////////////////////////////////////////////////////////////////////
cpu_manager g_cm;

#if 1
#pragma section("dsp_shared_section", read, write, shared)

#define declare_shared_var(...)\
  __declspec(allocate("dsp_shared_section")) __VA_ARGS__

declare_shared_var(int idsp = 0;);
declare_shared_var(int idsp2 = 0;);
#else

#pragma comment(linker,"/SECTION:dsp_shared_section,RWS")

#pragma data_seg("dsp_shared_section")
int idsp = 0;
int idsp2 = 1;
#pragma data_seg()

#endif