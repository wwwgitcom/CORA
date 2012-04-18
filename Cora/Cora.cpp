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





//#define split(T, ...) new (aligned_malloc<T>()) T(__VA_ARGS__)


//----------------------------------

DEFINE_BLOCK(dummy_block, 1, 1)
{
  BLOCK_INIT
  {
  }

  BLOCK_WORK
  {
    int nin0 = ninput(0);

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

#if 0
  autoref remove_gi1 = create_block<b_remove_gi_1v>(
    2,
    "GILength=4",
    "SymbolLength=16"
    );
  autoref remove_gi2 = create_block<b_remove_gi_1v>(
    2,
    "GILength=4",
    "SymbolLength=16"
    );
#endif

  autoref fft_data1 = create_block<b_fft_64_1v1>();
  autoref fft_data2 = create_block<b_fft_64_1v1>();

  autoref siso_channel_est = create_block<b_dot11_siso_channel_estimator_2v>();

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
    .to(fft_lltf1, 0);

  Channel::Create(sizeof(v_cs))
    .from(cfo_comp, 1)
    .to(fft_lltf2, 0);

  Channel::Create(sizeof(v_cs))
    .from(fft_lltf1, 0)
    .to(siso_channel_est, 0);

  Channel::Create(sizeof(v_cs))
    .from(fft_lltf2, 0)
    .to(siso_channel_est, 1);
  //---------------------------------------------------------
  
  //auto fk = make_thread([&]{    
  //});
  //fk.wait();

  int status = 0;

  tick_count t1, t2;

  t1 = tick_count::now();
  
  START(src,
    IF([&]{return status == 0;}),
 [&]{
      START(axorr, IF(lstf), STOP([&]{status = 1;}));
    },
    ELSE_IF([&]{return status == 1;}),
      IF(cfo_est), [&]{status = 2;}, ELSE, NOP,
    ELSE_IF([&]{return status == 2;}),
      cfo_comp,
 [&]{
      START(fft_lltf1);
      START(fft_lltf2);
      START(siso_channel_est, STOP([&]{status = 3;}));
    },
    ELSE, STOP(NOP)
  );

  t2 = tick_count::now();

  tick_count t = t2 - t1;
  printf("time = %f ms, %f MSPS\n",
    t.ms(), src.report() / t.us());

	return 0;
}

