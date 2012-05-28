#include "stdafx.h"
#include "dsp_log.h"
#include "dsp_sysconfig.h"

dsp_log& _log = dsp_log::Instance();
dsp_sysconfig* config = dsp_sysconfig::Instance();

void global_init()
{
  //_log.add_include_filter("perf");
  //_log.add_exclude_filter("file_source");
}

