// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//--------------------------------------------------
#include "dsp_types.h"
#include "dsp_tickcount.h"
#include "dsp_log.h"
#include "dsp_math.h"
#include "dsp_channel_matrix.h"
#include "dsp_map.h"
#include "dsp_demap.h"
#include "dsp_crc.h"
#include "dsp_processor.h"
#include "dsp_cmd.h"
#include "dsp_vector1.h"

#include "dsp_draw.h"

#define enable_draw 0
#define enable_dbgplot 1
#include "DebugPlotU.h"
//--------------------------------------------------
#include "TBlock.h"
#include "TObject.h"
#include "TOP.h"
#include "TTask.h"
#include "TMain.h"
#include "TParallel.h"
#include "TPipeline.h"
#include "TSchedule.h"
#include "TOnce.h"
#include "TArray.h"
#include "TChannel.h"
#include "TThread.h"
#include "TReset.h"

//--------------------------------------------------
#include "b_plot.h"
#include "b_producer.h"
#include "b_consumer.h"
#include "b_passthru.h"
#include "b_wait.h"
#include "b_dot11n_param.h"

#include "b_awgn.h"

#include "b_drop.h"
#include "b_file_source.h"
#include "b_moving_energy.h"
#include "b_auto_corr.h"

#include "b_noise_estimator.h"
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
#include "b_socket.h"


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
#define dot11n_test 1
#include "b_dot11n_rx.h"
//#include "b_dot11n_rx_profile.h"
//#include "b_dot11n_tx.h"

//#include "b_mumimo_2x2_tx.h"
#include "b_mumimo_4x4_tx.h"
#include "b_mumimo_4x4_rx.h"





BOOL WINAPI HandlerRoutine(__in  DWORD dwCtrlType)
{
  ConsoleEvent(dwCtrlType) << cout;

  switch (dwCtrlType)
  {
  case CTRL_C_EVENT:
  case CTRL_BREAK_EVENT:
  case CTRL_CLOSE_EVENT:
    ExitProcess(0);
    return true;// we handle the msg
  default:
    return false;
  }
}



void pipeline_profiling()
{
  tick_count t1, t2, t;
  autoref producer = create_block<b_producer_v1>(2, string("nItemsEach=4"), string("nItemsTotal=6400000"));
  autoref consumer = create_block<b_consumer_v1>();

  Channel::Create(sizeof(uint8)).from(producer, 0).to(consumer, 0);

  int nItemsTotal = 6400000;
  for (int nItemsEach = 4; nItemsEach < 4096; nItemsEach += 4)
  {
    *producer.nItemsEach  = nItemsEach;
    *producer.nItemsTotal = nItemsTotal;
    *producer.nItemsLeft  = nItemsTotal;

    t1 = tick_count::now();
    PIPE_LINE(producer, consumer);
    t2 = tick_count::now();
    t = t2 - t1;
    printf("Pipeline producer & consumer: %f us, %d bytes, %f Mbps\n", t.us(), nItemsEach, nItemsTotal * 8.0 / t.us());
  }
}



int _tmain(int argc, _TCHAR* argv[])
{
  dsp_cmd cmdline;
  cmdline.parse(argc, argv);
  
  SetConsoleCtrlHandler(HandlerRoutine, true);
  SetThreadAffinityMask(GetCurrentThread(), 1);

  if (dsp_sysconfig::Instance()->GetCPUProcessorCount() > 2)
  {
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
  }

  //SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
  //SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

#if enable_dbgplot
  ::DebugPlotInit();
#endif

#if 0
  auto tx_main = [&]
  {
    dot11n_2x2_tx(argc, argv);
  };

  auto rx_main = [&]
  {
    dot11n_2x2_rx_profile(argc, argv);
  };

  dsp_main(rx_main);
#endif

  auto mumimo_tx_main = [&]
  {
    mumimo_4x4_tx(argc, argv);
  };

  auto mumimo_rx_main = [&]
  {
    mumimo_4x4_rx(argc, argv);
  };

#if 0
  if (cmdline.get("source").exist())
  {
    //test_source_sock();
    bigap_4x4_rx_back_end(argc, argv);
  }
  else if (cmdline.get("sink").exist())
  {
    //test_sink_sock();
    bigap_4x4_rx_front_end(argc, argv);
  }
  else
  {
    printf("Invalid socket type...\n");
  }
#endif
  
  //dsp_main(mumimo_tx_main);
  dsp_main(mumimo_rx_main);
  //dsp_main(pipeline_profiling);
  //dsp_main(rx_main);

  
#if 0
  if ( cmdline.get("rx").exist() )
  {
    dsp_main(mumimo_rx_main);
  }
  else if ( cmdline.get("tx").exist() )
  {
    dsp_main(mumimo_tx_main);
  }
  else
  {
    printf("invalid arguments....\n");
  }
#endif
#if enable_dbgplot
  ::DebugPlotDeinit();
#endif

  ExitProcess(0);
  exit(0);
	return 0;
}

