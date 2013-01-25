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
#include "dsp_source.h"
#include "dsp_draw.h"
#include "dsp_console.h"

#define USER_MODE
#include "sora.h"

#define enable_draw 0
#ifdef _WIN64
#define enable_dbgplot 0
#else
#define enable_dbgplot 0
#endif

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
#include "b_hw_source.h"
#include "b_hw_sink.h"

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


#include "b_audio.h"


#include "b_plot.h"

//#define split(T, ...) new (aligned_malloc<T>()) T(__VA_ARGS__)



//----------------------------------
#define dot11n_test 1
#include "b_dot11n_rx.h"
//#include "b_dot11n_rx_profile.h"
//#include "b_dot11n_tx.h"

//#include "b_mumimo_2x2_tx.h"
//#include "b_mumimo_4x4_tx.h"
//#include "b_mumimo_4x4_rx.h"




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
  autoref consumer = create_block<b_consumer_1v>();

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


#define fft_size 1024

vcs fft_input[fft_size/4];
vcs fft_output[fft_size/4];


template<int N>
DSP_INLINE1 void PFFT(vcs * pInput, vcs * pOutput)
{
  const int nArray = N / vcs::size;

  FFTSSE<N> (pInput);

  PARALLEL([&]{
    FFTSSEEx<N/4> (pInput);
    FFTSSEEx<N/4> (pInput + nArray / 4);
  },[&]{
    FFTSSEEx<N/4> (pInput + nArray / 2);
    FFTSSEEx<N/4> (pInput + nArray / 4 * 3);
  });

  int i;
  for (i = 0; i < N; i++)
    ((COMPLEX16*)pOutput)[i] = ((COMPLEX16*)pInput) [FFTLUTMapTable<N>(i)];
}


void fft_test()
{
  tick_count t1, t2, t;
  t1 = tick_count::now();
  for (int i = 0; i < 100000; i++)
  {
    FFT<fft_size>(fft_input, fft_output);
  }  
  t2 = tick_count::now();
  t = t2 - t1;
  printf("fft single: %f us\n", t.us() /  100000.0);

  //------------------------
  t1 = tick_count::now();
  for (int i = 0; i < 100000; i++)
  {
    PFFT<fft_size>(fft_input, fft_output);
  }
  t2 = tick_count::now();
  t = t2 - t1;
  printf("pfft single: %f us\n", t.us() /  100000.0);
}






#ifndef _WIN64
void evt_handler_test()
{
  autoref plot  = create_block<b_spectrum_plot_1v>();
  autoref audio_src  = create_block<b_audio_v1>();

  Channel::Create(sizeof(v_cs)).from(audio_src, 0).to(plot, 0);

  START(audio_src, plot);
}

void hw_plot()
{
  autoref hwsrc = create_block<b_hw_source_v1>();
  autoref plot  = create_block<b_plot_1v>();

  Channel::Create(sizeof(v_cs)).from(hwsrc, 0).to(plot, 0);

  START(hwsrc, plot);
}
void hw_sink(int argc, _TCHAR* argv[])
{
  dsp_cmd cmdline;
  cmdline.parse(argc, argv);


  string strFileName = string("FileName=c:\\mimo_tx_0.dmp");
  auto CmdArg = cmdline.get("FileName");
  if ( CmdArg.exist() )
  {
    strFileName = "FileName=" + CmdArg.as_string();
  }

  printf("|- %s\n", strFileName.c_str());

  autoref txsrc  = create_block<b_tx_file_source_v1>(1, strFileName);
  autoref hwsink = create_block<b_hw_sink_1v>();

  Channel::Create(sizeof(v_cb), 128 * 1024).from(txsrc, 0).to(hwsink, 0);

  dsp_main( [&]{START(txsrc, hwsink);} ); 
}
#endif

void dump_llts()
{
  autoref llts = create_block<b_dot11n_lstf_v4>();
  autoref sink = create_block<b_dot11n_dma_join_4v1>();

  Channel::Create(sizeof(dot11n_tx_symbol)).from(llts, 0).to(sink, 0);
  Channel::Create(sizeof(dot11n_tx_symbol)).from(llts, 1).to(sink, 1);
  Channel::Create(sizeof(dot11n_tx_symbol)).from(llts, 2).to(sink, 2);
  Channel::Create(sizeof(dot11n_tx_symbol)).from(llts, 3).to(sink, 3);

  Channel::Create(sizeof(v_cs)).from(sink, 0);

  ONCE(llts);
  START(sink);

  sink.toTxtFile("dot11n_llts");
}


void auto_perf_test()
{
  //AUTO_PERF_SOURCE_BLOCK(b_dot11n_lstf_v2, dot11n_tx_symbol);
  //AUTO_PERF_SOURCE_BLOCK(b_dot11n_lltf_v2, dot11n_tx_symbol);
  
  AUTO_PERF_BLOCK(b_dot11n_add_cp_1v1, dot11n_tx_symbol, dot11n_tx_symbol);

  AUTO_PERF_BLOCK(b_conv_1o2_1v1, uint8, uint8);
  AUTO_PERF_BLOCK(b_conv_2o3_1v1, uint8, uint8);
  AUTO_PERF_BLOCK(b_conv_3o4_1v1, uint8, uint8);
  
  //AUTO_PERF_BLOCK(b_dot11n_add_pilot_1v);
  //AUTO_PERF_BLOCK(b_dot11a_add_pilot_1v);
  AUTO_PERF_BLOCK(b_dot11a_map_bpsk_q_1v1, v_ub, dot11n_tx_symbol);
  AUTO_PERF_BLOCK(b_dot11n_map_bpsk_i_1v1, v_ub, dot11n_tx_symbol);
  AUTO_PERF_BLOCK(b_dot11n_map_qpsk_1v1, v_ub, dot11n_tx_symbol);
  AUTO_PERF_BLOCK(b_dot11n_map_16qam_1v1, v_ub, dot11n_tx_symbol);
  AUTO_PERF_BLOCK(b_dot11n_map_64qam_1v1, v_ub, dot11n_tx_symbol);

  AUTO_PERF_BLOCK(b_dot11n_csd_1v1, dot11n_tx_symbol, dot11n_tx_symbol);
  AUTO_PERF_BLOCK(b_dot11a_interleaver_1bpsc_1v1, uint8, v_ub);

  AUTO_PERF_BLOCK(b_ifft_128_1v1, v_cs, v_cs);

  AUTO_PERF_BLOCK(b_stream_parser_bpsk_1v2, uint8, uint8);
  AUTO_PERF_BLOCK(b_stream_parser_qpsk_1v2, uint8, uint8);
  AUTO_PERF_BLOCK(b_stream_parser_16qam_1v2, uint8, uint8);
  AUTO_PERF_BLOCK(b_stream_parser_64qam_1v2, uint8, uint8);

  AUTO_PERF_BLOCK(b_dot11n_scramble_1v1, uint8, uint8);
  AUTO_PERF_BLOCK(b_dot11_descramble_1v1, uint8, uint8);
  
  AUTO_PERF_BLOCK(b_auto_corr_1v2, v_cs, v_q);
  
  AUTO_PERF_BLOCK(b_dot11_demap_bpsk_i_1v1, v_cs, uint8);
  AUTO_PERF_BLOCK(b_dot11_demap_qpsk_1v1, v_cs, uint8);
  AUTO_PERF_BLOCK(b_dot11_demap_16qam_1v1, v_cs, uint8);
  AUTO_PERF_BLOCK(b_dot11_demap_64qam_1v1, v_cs, uint8);

  //AUTO_PERF_BLOCK(b_lstf_searcher_2v1);

  AUTO_PERF_BLOCK(b_dot11_siso_channel_estimator_1v, v_cs, TNULL);
  AUTO_PERF_BLOCK(b_dot11_siso_channel_compensator_1v1, v_cs, v_cs);

  AUTO_PERF_BLOCK(b_dot11_mimo_channel_estimator_2v, v_cs, TNULL);
  AUTO_PERF_BLOCK(b_dot11_mimo_channel_compensator_2v2, v_cs, v_cs);


  AUTO_PERF_BLOCK(b_remove_gi_1v, v_cs, TNULL);
  AUTO_PERF_BLOCK(b_fft_64_1v1, v_cs, v_cs);
  //AUTO_PERF_BLOCK(b_dot11_pilot_tracking_2v, v_cs, TNULL);

  AUTO_PERF_BLOCK(b_stream_joiner_1_2v1, uint8, uint8);
  AUTO_PERF_BLOCK(b_stream_joiner_2_2v1, uint8, uint8);
  AUTO_PERF_BLOCK(b_stream_joiner_3_2v1, uint8, uint8);
}


size_t B = 2400;

void parallel_viterbi2()
{
  /************************************************************************/
  /* Setup parallel viterbi parameters                                    */
  /************************************************************************/
  char buf[100];

  memset(buf, 100, 0);
  sprintf(buf, "TraceBackOutput=%d", B);
  string strB = buf;

  memset(buf, 100, 0);
  sprintf(buf, "nSegmentSize=%d", B / 8);
  string strSeg = buf;

  autoref vit_source = create_block<b_viterbi_source_v1>();
  
  autoref vit_dispatcher = create_block<b_parallel_viterbi64_1v2>(2,string("TraceBackLength=48"), strB);

  autoref vit_worker1 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"), strB);
  autoref vit_worker2 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"), strB);

  autoref vit_combiner = create_block<b_viterbi_sink_2v1>(1, strSeg);


  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_source, 0).to(vit_dispatcher, 0);

  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 0).to(vit_worker1, 0);
  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 1).to(vit_worker2, 0);
  Channel::Create(sizeof(uint8)).from(vit_dispatcher, 2).to(vit_combiner, 2);
  
  Channel::Create(sizeof(uint8)).from(vit_worker1, 0).to(vit_combiner, 0);
  Channel::Create(sizeof(uint8)).from(vit_worker2, 0).to(vit_combiner, 1);

  Channel::Create(sizeof(uint8)).from(vit_combiner, 0);
  
#if 0
  START(vit_source, vit_dispatcher, [&]{
    START(vit_worker1);
    START(vit_worker2);
    START(vit_combiner);
  });
#else

  cc_align bool bRun = true;

  auto f1 = [&]
  {
    START(vit_source, vit_dispatcher);
    //bRun = false;

    return false;
  };

  auto f2 = [&]
  {
    PARALLEL(
      [&]{START(WHILE(IsTrue(bRun)), vit_worker1);},
      [&]{START(WHILE(IsTrue(bRun)), vit_worker2);}
    );
    return false;
  };

  auto f3 = [&]{
    START(WHILE(IsTrue(bRun)), vit_combiner);
    return false;
  };


  //AUTO_PERF_BLOCK(b_parallel_viterbi64_3o4_1v1, uint8, uint8, 2,string("TraceBackLength=48"), string("TraceBackOutput=2400"));


  tick_count tstart = tick_count::now();

  PIPE_LINE(f1, f2, f3);

  tick_count tstop = tick_count::now();

  tick_count tdif = tstop - tstart;

  double rate = vit_source.nTotalBits / tdif.us();
  printf("Parallel Viterbi Throughtput: %f Msbps\n", rate);

#endif
}

void parallel_viterbi3()
{
  /************************************************************************/
  /* Setup parallel viterbi parameters                                    */
  /************************************************************************/
  char buf[100];

  memset(buf, 100, 0);
  sprintf(buf, "TraceBackOutput=%d", B);
  string strB = buf;

  memset(buf, 100, 0);
  sprintf(buf, "nSegmentSize=%d", B / 8);
  string strSeg = buf;

  autoref vit_source = create_block<b_viterbi_source_v1>();

  autoref vit_dispatcher = create_block<b_parallel_viterbi64_1v3> (2,string("TraceBackLength=48"),strB);
  autoref vit_worker1 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_worker2 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_worker3 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_combiner = create_block<b_viterbi_sink_3v1>(1,strSeg);


  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_source, 0).to(vit_dispatcher, 0);

  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 0).to(vit_worker1, 0);
  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 1).to(vit_worker2, 0);
  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 2).to(vit_worker3, 0);

  Channel::Create(sizeof(uint8)).from(vit_dispatcher, 3).to(vit_combiner, 3);

  Channel::Create(sizeof(uint8)).from(vit_worker1, 0).to(vit_combiner, 0);
  Channel::Create(sizeof(uint8)).from(vit_worker2, 0).to(vit_combiner, 1);
  Channel::Create(sizeof(uint8)).from(vit_worker3, 0).to(vit_combiner, 2);

  Channel::Create(sizeof(uint8)).from(vit_combiner, 0);

#if 0
  START(vit_source, vit_dispatcher, [&]{
    START(vit_worker1);
    START(vit_worker2);
    START(vit_worker3);
    START(vit_combiner);
  });
#else

  cc_align bool bRun = true;

  auto f1 = [&]
  {
    START(vit_source, vit_dispatcher);
    //bRun = false;

    return false;
  };

  auto f2 = [&]
  {
    PARALLEL(
      [&]{START(WHILE(IsTrue(bRun)), vit_worker1);},
      [&]{START(WHILE(IsTrue(bRun)), vit_worker2);},
      [&]{START(WHILE(IsTrue(bRun)), vit_worker3);}
    );
    return false;
  };

  auto f3 = [&]{
    START(WHILE(IsTrue(bRun)), vit_combiner);
    return false;
  };


  AUTO_PERF_BLOCK(b_parallel_viterbi64_3o4_1v1, uint8, uint8, 2 ,string("TraceBackLength=48"), strB);


  tick_count tstart = tick_count::now();

  PIPE_LINE(f1, f3, f2);

  tick_count tstop = tick_count::now();

  tick_count tdif = tstop - tstart;

  double rate = vit_source.nTotalBits / tdif.us();
  printf("Parallel Viterbi Throughtput: %f Msbps\n", rate);

#endif
}


void parallel_viterbi4()
{
  /************************************************************************/
  /* Setup parallel viterbi parameters                                    */
  /************************************************************************/
  char buf[100];

  memset(buf, 100, 0);
  sprintf(buf, "TraceBackOutput=%d", B);
  string strB = buf;

  memset(buf, 100, 0);
  sprintf(buf, "nSegmentSize=%d", B / 8);
  string strSeg = buf;

  autoref vit_source = create_block<b_viterbi_source_v1>();

  autoref vit_dispatcher = create_block<b_parallel_viterbi64_1v4> (2,string("TraceBackLength=48"),strB);
  autoref vit_worker1 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_worker2 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_worker3 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_worker4 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_combiner = create_block<b_viterbi_sink_4v1>(1,strSeg);


  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_source, 0).to(vit_dispatcher, 0);

  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 0).to(vit_worker1, 0);
  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 1).to(vit_worker2, 0);
  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 2).to(vit_worker3, 0);
  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 3).to(vit_worker4, 0);

  Channel::Create(sizeof(uint8)).from(vit_dispatcher, 4).to(vit_combiner, 4);

  Channel::Create(sizeof(uint8)).from(vit_worker1, 0).to(vit_combiner, 0);
  Channel::Create(sizeof(uint8)).from(vit_worker2, 0).to(vit_combiner, 1);
  Channel::Create(sizeof(uint8)).from(vit_worker3, 0).to(vit_combiner, 2);
  Channel::Create(sizeof(uint8)).from(vit_worker4, 0).to(vit_combiner, 3);

  Channel::Create(sizeof(uint8)).from(vit_combiner, 0);

#if 0
  START(vit_source, vit_dispatcher, [&]{
    START(vit_worker1);
    START(vit_worker2);
    START(vit_worker3);
    START(vit_worker4);
    START(vit_combiner);
  });
#else

  cc_align bool bRun = true;

  auto f1 = [&]
  {
    START(vit_source, vit_dispatcher);
    //bRun = false;

    return false;
  };

  auto f2 = [&]
  {
    PARALLEL(
      [&]{START(WHILE(IsTrue(bRun)), vit_worker1);},
      [&]{START(WHILE(IsTrue(bRun)), vit_worker2);},
      [&]{START(WHILE(IsTrue(bRun)), vit_worker3);},
      [&]{START(WHILE(IsTrue(bRun)), vit_worker4);}
    );
    return false;
  };

  auto f3 = [&]{
    START(WHILE(IsTrue(bRun)), vit_combiner);
    return false;
  };


  AUTO_PERF_BLOCK(b_parallel_viterbi64_1o2_1v1, uint8, uint8, 2,string("TraceBackLength=48"), strB);


  tick_count tstart = tick_count::now();

  PIPE_LINE(f1, f3, f2);

  tick_count tstop = tick_count::now();

  tick_count tdif = tstop - tstart;

  double rate = vit_source.nTotalBits / tdif.us();
  printf("Parallel Viterbi Throughtput: %f Msbps\n", rate);

#endif
}

void parallel_viterbi5()
{
  /************************************************************************/
  /* Setup parallel viterbi parameters                                    */
  /************************************************************************/
  char buf[100];

  memset(buf, 100, 0);
  sprintf(buf, "TraceBackOutput=%d", B);
  string strB = buf;

  memset(buf, 100, 0);
  sprintf(buf, "nSegmentSize=%d", B / 8);
  string strSeg = buf;

  autoref vit_source = create_block<b_viterbi_source_v1>();

  autoref vit_dispatcher = create_block<b_parallel_viterbi64_1v5> (2,string("TraceBackLength=48"),strB);
  autoref vit_worker1 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_worker2 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_worker3 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_worker4 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_worker5 = create_block<b_parallel_viterbi64_3o4_1v1>(2,string("TraceBackLength=48"),strB);
  autoref vit_combiner = create_block<b_viterbi_sink_5v1>(1, strSeg);


  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_source, 0).to(vit_dispatcher, 0);

  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 0).to(vit_worker1, 0);
  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 1).to(vit_worker2, 0);
  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 2).to(vit_worker3, 0);
  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 3).to(vit_worker4, 0);
  Channel::Create(sizeof(uint8), 1024 * 1024).from(vit_dispatcher, 4).to(vit_worker5, 0);

  Channel::Create(sizeof(uint8)).from(vit_dispatcher, 5).to(vit_combiner, 5);

  Channel::Create(sizeof(uint8)).from(vit_worker1, 0).to(vit_combiner, 0);
  Channel::Create(sizeof(uint8)).from(vit_worker2, 0).to(vit_combiner, 1);
  Channel::Create(sizeof(uint8)).from(vit_worker3, 0).to(vit_combiner, 2);
  Channel::Create(sizeof(uint8)).from(vit_worker4, 0).to(vit_combiner, 3);
  Channel::Create(sizeof(uint8)).from(vit_worker5, 0).to(vit_combiner, 4);

  Channel::Create(sizeof(uint8)).from(vit_combiner, 0);

#if 0
  START(vit_source, vit_dispatcher, [&]{
    START(vit_worker1);
    START(vit_worker2);
    START(vit_worker3);
    START(vit_worker4);
    START(vit_worker5);
    START(vit_combiner);
  });
#else

  cc_align bool bRun = true;

  auto f1 = [&]
  {
    START(vit_source, vit_dispatcher);
    //bRun = false;

    return false;
  };

  auto f2 = [&]
  {
    PARALLEL(
      [&]{START(WHILE(IsTrue(bRun)), vit_worker1);},
      [&]{START(WHILE(IsTrue(bRun)), vit_worker2);},
      [&]{START(WHILE(IsTrue(bRun)), vit_worker3);},
      [&]{START(WHILE(IsTrue(bRun)), vit_worker4);},
      [&]{START(WHILE(IsTrue(bRun)), vit_worker5);}
    );
    return false;
  };

  auto f3 = [&]{
    START(WHILE(IsTrue(bRun)), vit_combiner);
    return false;
  };


  AUTO_PERF_BLOCK(b_parallel_viterbi64_1o2_1v1, uint8, uint8, 2,string("TraceBackLength=48"), string("TraceBackOutput=1024"));


  tick_count tstart = tick_count::now();

  // need at least 7 cores
  PIPE_LINE(f1, f3, f2);

  tick_count tstop = tick_count::now();

  tick_count tdif = tstop - tstart;

  double rate = vit_source.nTotalBits / tdif.us();
  printf("Parallel Viterbi Throughtput: %f Msbps\n", rate);

#endif
}


int __cdecl _tmain(int argc, _TCHAR* argv[])
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
#ifndef _WIN64
  ::DebugPlotInit();
#endif 
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

  //dsp_main(evt_handler_test);
  //dump_llts();

  //dsp_main(auto_perf_test);
  
  size_t nvitcore = 3;
  if (cmdline.get("nvitcore").exist())
  {
    nvitcore = cmdline.get("nvitcore").as_uint();
  }

  if (cmdline.get("B").exist())
  {
    B = cmdline.get("B").as_uint();
  }


  switch (nvitcore)
  {
  case 2:
    dsp_main(parallel_viterbi2);
    break;
  case 3:
    dsp_main(parallel_viterbi3);
    break;
  case 4:
    dsp_main(parallel_viterbi4);
    break;
  case 5:
    dsp_main(parallel_viterbi5);
    break;
  default:
    break;
  }
  

  auto mumimo_tx_main = [&]
  {
    //mumimo_4x4_tx(argc, argv);
  };

  auto mumimo_rx_main = [&]
  {
    //mumimo_4x4_rx(argc, argv);
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
  
  //dsp_main(mumimo_rx_main);
  //dsp_main(fft_test);
  //dsp_main(pipeline_profiling);
  //dsp_main(hw_plot);
  //hw_sink(argc,argv);
  
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
#ifndef _WIN64
  ::DebugPlotDeinit();
#endif
#endif

  ExitProcess(0);
  exit(0); 
	return 0;
}

