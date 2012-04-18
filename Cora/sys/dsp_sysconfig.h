#pragma once
#include <windows.h>

class dsp_sysconfig 
{
private:
  int m_iPageSize;
  int m_nCPUProcessors;
  DWORD m_dwAllocationGranularity;
  dsp_sysconfig();
  dsp_sysconfig(const dsp_sysconfig&) ;
  dsp_sysconfig& operator=(const dsp_sysconfig&) ;
public:
  static dsp_sysconfig* Instance();

  int GetPageSize(){return m_iPageSize;}
  int GetCPUProcessorCount(){return m_nCPUProcessors;}
  DWORD GetAllocationGranularity(){return m_dwAllocationGranularity;}
  void GetSysMemoryInfo();
};