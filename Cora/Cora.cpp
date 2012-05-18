// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//--------------------------------------------------
#include "dsp_types.h"
#include "dsp_tickcount.h"
#include "dsp_log.h"
#include "dsp_math.h"
#include "dsp_map.h"
#include "dsp_demap.h"
#include "dsp_crc.h"
#include "dsp_processor.h"
#include "dsp_cmd.h"
//--------------------------------------------------
#include "TBlock.h"
#include "TObject.h"
#include "TOP.h"
#include "TTask.h"
#include "TParallel.h"
#include "TSchedule.h"
#include "TOnce.h"
#include "TArray.h"
#include "TChannel.h"
#include "TThread.h"
#include "TReset.h"

#define enable_draw 0
//--------------------------------------------------
#include "b_plot.h"

#include "b_dot11n_param.h"

#include "b_drop.h"
#include "b_file_source.h"
#include "b_moving_energy.h"
#include "b_auto_corr.h"

#include "b_lstf_searcher.h"
#include "b_frequest_offset.h"
#include "b_fft.h"
#include "b_channel_estimator.h"
#include "b_channel_compensator.h"
#include "b_remove_gi.h"
#include "b_pilot_tracking.h"
#include "b_demap.h"
#include "b_mrc_combine.h"
#include "b_deinterleave.h"
#include "b_viterbi.h"
#include "b_lsig_parser.h"
#include "b_htsig_parser.h"
#include "b_mimo_channel_estimator.h"
#include "b_mimo_channel_compensator.h"
#include "b_stream_joiner.h"
#include "b_descramble.h"
#include "b_crc.h"


//////////////////////////////////////////////////////////////////////////
#include "b_dot11_frame_source.h"
#include "b_dot11n_scramble.h"
#include "b_conv.h"
#include "b_stream_parser.h"

#include "b_dot11a_interleave.h"
#include "b_dot11n_interleave.h"

#include "b_dot11a_map.h"
#include "b_dot11n_map.h"

#include "b_dot11n_lstf.h"
#include "b_dot11n_lltf.h"
#include "b_dot11n_htstf.h"
#include "b_dot11n_htltf.h"
#include "b_dot11n_lsig.h"
#include "b_dot11n_htsig.h"
#include "b_dot11n_tx_ifft.h"
#include "b_dot11a_add_pilot.h"
#include "b_dot11n_add_pilot.h"
#include "b_dot11n_csd.h"
#include "b_dot11n_add_cp.h"
#include "b_dot11n_dma_join.h"


//#define split(T, ...) new (aligned_malloc<T>()) T(__VA_ARGS__)



//----------------------------------










//m_pFunction = reinterpret_cast <TaskProc> (&::Concurrency::details::_UnrealizedChore::_InvokeBridge<task_handle>);

#include "b_dot11n_rx.h"
#include "b_dot11n_tx.h"



auto make_func() -> std::function<void()>
{
  static int a = 10;
  auto f = [&]{
    printf("inside function...a=%d\n", a++);
  };
  return f;
}



int _tmain(int argc, _TCHAR* argv[])
{
  

  SetThreadAffinityMask(GetCurrentThread(), 1);

  auto f1 = make_func();
  auto f2 = make_func();
  f1();
  f2();


  dot11n_2x2_tx(argc, argv);
  //dot11n_2x2_rx(argc, argv);




	return 0;
}

