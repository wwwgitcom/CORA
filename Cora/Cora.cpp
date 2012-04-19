// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//--------------------------------------------------
#include "dsp_tickcount.h"
#include "dsp_log.h"
#include "dsp_math.h"
#include "dsp_map.h"
#include "dsp_demap.h"
//--------------------------------------------------
#include "TBlock.h"
#include "TObject.h"
#include "TOP.h"
#include "TTask.h"
#include "TPipeline.h"
#include "TSchedule.h"
#include "TOnce.h"
#include "TArray.h"
#include "TChannel.h"
#include "TThread.h"

//--------------------------------------------------
#include "b_file_source.h"
#include "b_moving_energy.h"
#include "b_auto_corr.h"

#include "b_lstf_searcher.h"
#include "b_frequest_offset.h"
#include "b_fft.h"
#include "b_channel_estimator.h"
#include "b_channel_compensator.h"
#include "b_remove_gi.h"
#include "b_demap.h"
#include "b_mrc_combine.h"
#include "b_deinterleave.h"



//#define split(T, ...) new (aligned_malloc<T>()) T(__VA_ARGS__)


//----------------------------------

DEFINE_BLOCK(dummy_block, 1, 1)
{
  BLOCK_INIT
  {
  }

  BLOCK_WORK
  {
    trace();

    int nin0 = ninput(0);
    auto ip = _$<unsigned __int8>(0);
    for (int i = 0; i < nin0; i++)
    {
      log("%d, ", ip[i]);
    }
    log("\n");
    consume(0, nin0);
    return false;
  }
};


int _tmain(int argc, _TCHAR* argv[])
{
  autoref dummy = create_block<dummy_block>();

  autoref src = create_block<b_file_source_v2>(
    3, 
    string("FileName1=c:\\MiMoRx_0.dmp"), 
    string("FileName2=c:\\MiMoRx_1.dmp"), 
    string("Decimate=1")
    );

  autoref axorr = create_block<b_auto_corr_2v2>(
    1, 
    string("vHisLength=8")
    );

  autoref lstf = create_block<b_lstf_searcher_2v1>();

  autoref cfo_est = create_block<b_frequest_offset_estimator_2v>(
    2,
    string("vEstimateLength=16"),
    string("vEstimateDistance=16")
    );

  autoref cfo_comp = create_block<b_frequest_offset_compensator_2v2>(
    1,
    string("vCompensateLength=1")
    );

  autoref fft_lltf1 = create_block<b_fft_64_1v1>();
  autoref fft_lltf2 = create_block<b_fft_64_1v1>();


  autoref remove_gi1 = create_block<b_remove_gi_1v>(
    2,
    string("GILength=4"),
    string("SymbolLength=16")
    );

  autoref remove_gi2 = create_block<b_remove_gi_1v>(
    2,
    string("GILength=4"),
    string("SymbolLength=16")
    );

  autoref fft_data1 = create_block<b_fft_64_1v1>();
  autoref fft_data2 = create_block<b_fft_64_1v1>();

  autoref siso_channel_est = create_block<b_dot11_siso_channel_estimator_2v>();
  autoref siso_channel_comp = create_block<b_dot11_siso_channel_compensator_2v2>();
  
  autoref siso_mrc_combine = create_block<b_mrc_combine_2v1>(
    1,
    string("Combinelength=1"));

  autoref siso_lsig_demap_bpsk_i = create_block<b_dot11_demap_bpsk_i_1v1>(
    2,
    string("low=-26"),
    string("high=26")
    );
  autoref siso_lsig_deinterleave = create_block<b_dot11a_deinterleave_1bpsc_1v1>();

  //---------------------------------------------------------
  Channel::Create(sizeof(v_cs))
  .from(src, 0)
  .to(axorr, 0).to(cfo_est, 0).to(cfo_comp, 0);

  Channel::Create(sizeof(v_cs))
    .from(src, 1)
    .to(axorr, 1).to(cfo_est, 1).to(cfo_comp, 1);


  Channel::Create(sizeof(v_q))
  .from(axorr, 0)
  .to(lstf, 0);

  Channel::Create(sizeof(v_q))
  .from(axorr, 1)
  .to(lstf, 1);

  Channel::Create(sizeof(v_cs))
    .from(cfo_comp, 0)
    .to(fft_lltf1, 0).to(remove_gi1, 0).to(fft_data1, 0);

  Channel::Create(sizeof(v_cs))
    .from(cfo_comp, 1)
    .to(fft_lltf2, 0).to(remove_gi2, 0).to(fft_data2, 0);

  Channel::Create(sizeof(v_cs))
    .from(fft_lltf1, 0)
    .to(siso_channel_est, 0);

  Channel::Create(sizeof(v_cs))
    .from(fft_lltf2, 0)
    .to(siso_channel_est, 1);
  
  Channel::Create(sizeof(v_cs))
    .from(fft_data1, 0).to(siso_channel_comp, 0);
  Channel::Create(sizeof(v_cs))
    .from(fft_data2, 0).to(siso_channel_comp, 1);

  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 0).to(siso_mrc_combine, 0);
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 1).to(siso_mrc_combine, 1);
  
  Channel::Create(sizeof(v_cs))
    .from(siso_mrc_combine, 0).to(siso_lsig_demap_bpsk_i, 0);

  Channel::Create(sizeof(unsigned __int8))
    .from(siso_lsig_demap_bpsk_i, 0).to(siso_lsig_deinterleave, 0);

  Channel::Create(sizeof(unsigned __int8))
    .from(siso_lsig_deinterleave, 0).to(dummy, 0);
  //---------------------------------------------------------
  
  //auto fk = make_thread([&]{    
  //});
  //fk.wait();

  enum : unsigned int
  {
    CS = 0,
    CFO,
    OTHER
  }branch1 = CS;


  enum : unsigned int
  {
    SISO_CHANNEL_ESTIMATION = 0,
    LSIG_DECODE,
    lltf
  }branch2 = SISO_CHANNEL_ESTIMATION;

  tick_count t1, t2;

  t1 = tick_count::now();
  
  START(src,
    // frame detection
    IF(IsTrue(branch1 == CS)),[&]
    {
      START(axorr, IF(lstf), STOP([&]{branch1 = CFO;}));
    },
    ELSE_IF(IsTrue(branch1 == CFO)),
      // carrier frequency offset estimation using L-LTF
      IF(cfo_est), [&]{branch1 = OTHER;}, ELSE, NOP,
    ELSE_IF(IsTrue(branch1 == OTHER)),
      // carrier frequency offset compensation
      cfo_comp,
      // L-LTF branch: SISO channel estimation
      IF(IsTrue(branch2 == SISO_CHANNEL_ESTIMATION)),[&]
      {
        START(fft_lltf1);
        START(fft_lltf2, siso_channel_est, STOP([&]{branch2 = LSIG_DECODE;}));
      },
      // L-SIG branch: legacy signal field decoding using MRC
      ELSE_IF(IsTrue(branch2 == LSIG_DECODE)), [&]
      {
        START(IF(remove_gi1), fft_data1);
        START(IF(remove_gi2), fft_data2, siso_channel_comp, siso_mrc_combine, siso_lsig_demap_bpsk_i, siso_lsig_deinterleave, dummy);
      },
      ELSE, NOP,
    ELSE, STOP(NOP)
  );

  t2 = tick_count::now();

  tick_count t = t2 - t1;
  printf("time = %f ms, %f MSPS\n",
    t.ms(), src.report() / t.us());

	return 0;
}

