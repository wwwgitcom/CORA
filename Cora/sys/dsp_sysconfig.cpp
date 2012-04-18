#include "stdafx.h"
#include "dsp_sysconfig.h"
#include <Psapi.h>

#pragma comment(lib, "Psapi.lib")

dsp_sysconfig::dsp_sysconfig()
{
  SYSTEM_INFO si;
  GetSystemInfo(&si);

  printf("============System  Info===============\n");
  printf("PageSize                    = %p\n", si.dwPageSize);
  printf("NumberOfProcessors          = %p\n", si.dwNumberOfProcessors);
  printf("AllocationGranularity       = %p\n", si.dwAllocationGranularity);
  printf("MinimumApplicationAddress   = %p\n", si.lpMinimumApplicationAddress);
  printf("MaximumApplicationAddress   = %p\n", si.lpMaximumApplicationAddress);
  printf("=======================================\n");

  m_iPageSize               = si.dwPageSize;
  m_nCPUProcessors          = si.dwNumberOfProcessors;
  m_dwAllocationGranularity = si.dwAllocationGranularity;
}

dsp_sysconfig* dsp_sysconfig::Instance()
{
  static dsp_sysconfig s_SysConfig;

  return &s_SysConfig;
}

void dsp_sysconfig::GetSysMemoryInfo()
{
  PROCESS_MEMORY_COUNTERS psmemCounters;

  BOOL bRet = GetProcessMemoryInfo(
    GetCurrentProcess(),
    &psmemCounters,
    sizeof(PROCESS_MEMORY_COUNTERS)
    );
  if (bRet)
  {
    printf("=========Process Memory Info===========\n");
    printf("PageFaultCount              = %d\n", psmemCounters.PageFaultCount);
    printf("PagefileUsage               = %d\n", psmemCounters.PagefileUsage);
    printf("PeakPagefileUsage           = %d\n", psmemCounters.PeakPagefileUsage);
    printf("WorkingSetSize              = %d\n", psmemCounters.WorkingSetSize);
    printf("PeakWorkingSetSize          = %d\n", psmemCounters.PeakWorkingSetSize);
    printf("QuotaNonPagedPoolUsage      = %d\n", psmemCounters.QuotaNonPagedPoolUsage);
    printf("QuotaPagedPoolUsage         = %d\n", psmemCounters.QuotaPagedPoolUsage);
    printf("QuotaPeakNonPagedPoolUsage  = %d\n", psmemCounters.QuotaPeakNonPagedPoolUsage);
    printf("QuotaPeakPagedPoolUsage     = %d\n", psmemCounters.QuotaPeakPagedPoolUsage);
    printf("=======================================\n");
  }
}