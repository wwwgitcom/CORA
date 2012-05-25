#pragma once

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

void dot11n_2x2_rx(int argc, _TCHAR* argv[])
{
  autoref dummy = create_block<dummy_block>();

#if 0
  autoref src = create_block<b_file_source_v2>(
    3, 
    string("FileName1=c:\\MiMoRx_0.dmp"), 
    string("FileName2=c:\\MiMoRx_1.dmp"), 
    string("Decimate=1")
    );
#else
  autoref src = create_block<b_file_source_v2>(
    3, 
    string("FileName1=c:\\MiMo_0.dmp"), 
    string("FileName2=c:\\MiMo_1.dmp"), 
    string("Decimate=1")
    );
#endif

  autoref wait_lltf = create_block<b_wait_2v2>(
    1, string("nwait=32"));

  autoref wait_ofdm = create_block<b_wait_2v2>(
    1, string("nwait=20"));

  autoref axorr = create_block<b_auto_corr_2v2>(
    1, 
    string("vHisLength=8")
    );

  autoref lstf_searcher = create_block<b_lstf_searcher_2v1>();

  autoref cfo_est = create_block<b_frequest_offset_estimator_2v>(
    2,
    string("vEstimateLength=16"),
    string("vEstimateDistance=16")
    );

  autoref cfo_comp = create_block<b_frequest_offset_compensator_2v2>(
    1,
    string("vCompensateLength=2")
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
    string("Combinelength=16"));

  autoref siso_lsig_demap_bpsk_i = create_block<b_dot11_demap_bpsk_i_1v1>(
    2,
    string("low=-26"),
    string("high=26")
    );

  autoref siso_lsig_deinterleave = create_block<b_dot11a_deinterleave_1bpsc_1v1>();


  autoref l_sig_vit = create_block<b_viterbi64_1o2_1v1>(
    2,
    string("TraceBackLength=24"),
    string("TraceBackOutput=24")
    );

  autoref htsig_demap_bpsk_q = create_block<b_dot11_demap_bpsk_q_1v1>(
    2,
    string("low=-26"),
    string("high=26")
    );

  autoref ht_sig_vit = create_block<b_viterbi64_1o2_1v1>(
    2,
    string("TraceBackLength=48"),
    string("TraceBackOutput=48")
    );

  autoref ht_data_vit_12 = create_block<b_viterbi64_1o2_1v1>(
    2,
    string("TraceBackLength=48"),
    string("TraceBackOutput=96")
    );

  autoref ht_data_vit_23 = create_block<b_viterbi64_2o3_1v1>(
    2,
    string("TraceBackLength=96"),
    string("TraceBackOutput=192")
    );

  autoref ht_data_vit_34 = create_block<b_viterbi64_3o4_1v1>(
    2,
    string("TraceBackLength=144"),
    string("TraceBackOutput=384")
    );

  autoref l_sig_parser = create_block<b_lsig_parser_1v>();
  autoref ht_sig_parser = create_block<b_htsig_parser_1v>();
  autoref ht_stf = create_block<b_drop_2v>(
    1,
    string("nDrop=20")
    );

  autoref mimo_channel_estimator = create_block<b_dot11_mimo_channel_estimator_2v>();

  autoref mimo_channel_compensator = create_block<b_dot11_mimo_channel_compensator_2v2>();

  autoref ht_demap_bpsk1 = create_block<b_dot11_demap_bpsk_i_1v1>(
    2,
    string("low=-28"),
    string("high=28"));
  autoref ht_demap_bpsk2 = create_block<b_dot11_demap_bpsk_i_1v1>(
    2,
    string("low=-28"),
    string("high=28"));

  autoref ht_demap_qpsk1 = create_block<b_dot11_demap_qpsk_1v1>(
    2,
    string("low=-28"),
    string("high=28"));
  autoref ht_demap_qpsk2 = create_block<b_dot11_demap_qpsk_1v1>(
    2,
    string("low=-28"),
    string("high=28"));

  autoref ht_demap_16qam1 = create_block<b_dot11_demap_16qam_1v1>(
    2,
    string("low=-28"),
    string("high=28"));
  autoref ht_demap_16qam2 = create_block<b_dot11_demap_16qam_1v1>(
    2,
    string("low=-28"),
    string("high=28"));

  autoref ht_demap_64qam1 = create_block<b_dot11_demap_64qam_1v1>(
    2,
    string("low=-28"),
    string("high=28"));
  autoref ht_demap_64qam2 = create_block<b_dot11_demap_64qam_1v1>(
    2,
    string("low=-28"),
    string("high=28"));

  autoref ht_deinterleave_1bpsc_iss1 = create_block<b_dot11n_deinterleave_1bpsc_1v1>(
    1, string("iss=1"));
  autoref ht_deinterleave_1bpsc_iss2 = create_block<b_dot11n_deinterleave_1bpsc_1v1>(
    1, string("iss=2"));
  autoref ht_deinterleave_2bpsc_iss1 = create_block<b_dot11n_deinterleave_2bpsc_1v1>(
    1, string("iss=1"));
  autoref ht_deinterleave_2bpsc_iss2 = create_block<b_dot11n_deinterleave_2bpsc_1v1>(
    1, string("iss=2"));
  autoref ht_deinterleave_4bpsc_iss1 = create_block<b_dot11n_deinterleave_4bpsc_1v1>(
    1, string("iss=1"));
  autoref ht_deinterleave_4bpsc_iss2 = create_block<b_dot11n_deinterleave_4bpsc_1v1>(
    1, string("iss=2"));
  autoref ht_deinterleave_6bpsc_iss1 = create_block<b_dot11n_deinterleave_6bpsc_1v1>(
    1, string("iss=1"));
  autoref ht_deinterleave_6bpsc_iss2 = create_block<b_dot11n_deinterleave_6bpsc_1v1>(
    1, string("iss=2"));

  autoref ht_stream_joiner_1 = create_block<b_stream_joiner_1_2v1>();
  autoref ht_stream_joiner_2 = create_block<b_stream_joiner_2_2v1>();
  autoref ht_stream_joiner_3 = create_block<b_stream_joiner_3_2v1>();

  autoref descramble_seed = create_block<b_dot11_descramble_seed_1v>();
  autoref descramble      = create_block<b_dot11_descramble_1v1>();
  autoref crc32_checker   = create_block<b_crc32_check_1v>();
  autoref pilot_tracking  = create_block<b_dot11_pilot_tracking_2v>();

  //---------------------------------------------------------
  Channel::Create(sizeof(v_cs))
    .from(src, 0)
    .to(wait_lltf, 0).to(wait_ofdm, 0).to(axorr, 0).to(cfo_est, 0).to(cfo_comp, 0);

  Channel::Create(sizeof(v_cs))
    .from(src, 1)
    .to(wait_lltf, 1).to(wait_ofdm, 1).to(axorr, 1).to(cfo_est, 1).to(cfo_comp, 1);

  Channel::Create(sizeof(v_q))
    .from(axorr, 0)
    .to(lstf_searcher, 0);

  Channel::Create(sizeof(v_q))
    .from(axorr, 1)
    .to(lstf_searcher, 1);

  Channel::Create(sizeof(v_cs))
    .from(cfo_comp, 0)
    .to(fft_lltf1, 0).to(remove_gi1, 0).to(fft_data1, 0).to(ht_stf, 0);

  Channel::Create(sizeof(v_cs))
    .from(cfo_comp, 1)
    .to(fft_lltf2, 0).to(remove_gi2, 0).to(fft_data2, 0).to(ht_stf, 1);

  Channel::Create(sizeof(v_cs))
    .from(fft_lltf1, 0)
    .to(siso_channel_est, 0);

  Channel::Create(sizeof(v_cs))
    .from(fft_lltf2, 0)
    .to(siso_channel_est, 1);

  Channel::Create(sizeof(v_cs))
    .from(fft_data1, 0)
    .to(siso_channel_comp, 0).to(mimo_channel_estimator, 0).to(mimo_channel_compensator, 0);
  Channel::Create(sizeof(v_cs))
    .from(fft_data2, 0)
    .to(siso_channel_comp, 1).to(mimo_channel_estimator, 1).to(mimo_channel_compensator, 1);

  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 0).to(siso_mrc_combine, 0)
    .from(mimo_channel_compensator, 0).to(ht_demap_bpsk1, 0).to(ht_demap_qpsk1, 0).to(ht_demap_16qam1, 0).to(ht_demap_64qam1, 0).to(pilot_tracking, 0);
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 1).to(siso_mrc_combine, 1)
    .from(mimo_channel_compensator, 1).to(ht_demap_bpsk2, 0).to(ht_demap_qpsk2, 0).to(ht_demap_16qam2, 0).to(ht_demap_64qam2, 0).to(pilot_tracking, 1);

  Channel::Create(sizeof(v_cs))
    .from(siso_mrc_combine, 0)
    .to(siso_lsig_demap_bpsk_i, 0).to(htsig_demap_bpsk_q, 0);

  Channel::Create(sizeof(unsigned __int8))
    .from(siso_lsig_demap_bpsk_i, 0).from(htsig_demap_bpsk_q, 0)
    .to(siso_lsig_deinterleave, 0);

  Channel::Create(sizeof(unsigned __int8))
    .from(siso_lsig_deinterleave, 0).to(l_sig_vit, 0).to(ht_sig_vit, 0);

  Channel::Create(sizeof(unsigned __int8))
    .from(l_sig_vit, 0)
    .to(l_sig_parser, 0);

  Channel::Create(sizeof(unsigned __int8))
    .from(ht_sig_vit, 0)
    .to(ht_sig_parser, 0);

  Channel::Create(sizeof(unsigned __int8))
    .from(ht_demap_bpsk1, 0).from(ht_demap_qpsk1, 0).from(ht_demap_16qam1, 0).from(ht_demap_64qam1, 0)
    .to(ht_deinterleave_1bpsc_iss1, 0).to(ht_deinterleave_2bpsc_iss1, 0).to(ht_deinterleave_4bpsc_iss1, 0).to(ht_deinterleave_6bpsc_iss1, 0);

  Channel::Create(sizeof(unsigned __int8))
    .from(ht_demap_bpsk2, 0).from(ht_demap_qpsk2, 0).from(ht_demap_16qam2, 0).from(ht_demap_64qam2, 0)
    .to(ht_deinterleave_1bpsc_iss2, 0).to(ht_deinterleave_2bpsc_iss2, 0).to(ht_deinterleave_4bpsc_iss2, 0).to(ht_deinterleave_6bpsc_iss2, 0);

  Channel::Create(sizeof(unsigned __int8))
    .from(ht_deinterleave_1bpsc_iss1, 0).from(ht_deinterleave_2bpsc_iss1, 0).from(ht_deinterleave_4bpsc_iss1, 0).from(ht_deinterleave_6bpsc_iss1, 0)
    .to(ht_stream_joiner_1, 0).to(ht_stream_joiner_2, 0).to(ht_stream_joiner_3, 0);
  Channel::Create(sizeof(unsigned __int8))
    .from(ht_deinterleave_1bpsc_iss2, 0).from(ht_deinterleave_2bpsc_iss2, 0).from(ht_deinterleave_4bpsc_iss2, 0).from(ht_deinterleave_6bpsc_iss2, 0)
    .to(ht_stream_joiner_1, 1).to(ht_stream_joiner_2, 1).to(ht_stream_joiner_3, 1);

  Channel::Create(sizeof(unsigned __int8))
    .from(ht_stream_joiner_1, 0).from(ht_stream_joiner_2, 0).from(ht_stream_joiner_3, 0)
    .to(ht_data_vit_12, 0).to(ht_data_vit_23, 0).to(ht_data_vit_34, 0);

  Channel::Create(sizeof(uint8))
    .from(ht_data_vit_12, 0).from(ht_data_vit_23, 0).from(ht_data_vit_34, 0)
    .to(descramble_seed, 0).to(descramble, 0);

  Channel::Create(sizeof(uint8))
    .from(descramble, 0).to(crc32_checker, 0);
  //---------------------------------------------------------
  v_align(64)
  _global_(bool, l_sig_ok);
  _global_(bool, ht_sig_ok);
  _global_(uint32, ht_frame_mcs);
  _global_(uint16, ht_frame_length);

  v_align(64)
  _global_(int, VitTotalSoftBits);
  _global_(int, VitTotalBits);  
  _global_(int, crc32_check_length);
  _global_(bool, crc32_check_result);
  
  //////////////////////////////////////////////////////////////////////////
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
    L_SIG,    
    HT_SIG1,
    HT_SIG2,
    HT_STF,
    HT_LTF,
    HT_DATA,
    HT_OTHER
  }branch2 = SISO_CHANNEL_ESTIMATION;

  bool frame_decode_done = false;  
  int symbol_count;
  int total_symbol_count;
  int thread1_count = 0;
  int thread2_count = 0;

  v_align(64) int descramble_state = 0;

  tick_count t1, t2, t3;

  cpu_manager* cm = cpu_manager::Instance();

#if 1


  auto frame_detection = [&]() -> bool
  {
    START(src, axorr, lstf_searcher, STOP(NOP));
    return true;
  };

  auto lltf_handler = [&]() -> bool
  {
    START(src, wait_lltf, IF([&]
    {
      ONCE(cfo_est, cfo_comp);
      START(fft_lltf1, fft_lltf2);
      ONCE(siso_channel_est);
      return true;
    }), STOP(NOP));

    printf("lltf_handler\n");
    return true;
  };

  auto lsig_handler = [&]() -> bool
  {
    *VitTotalBits = 24;
    *l_sig_ok = false;
    //l-sig
    START(src, wait_ofdm, STOP([&]
    {
      ONCE(cfo_comp, remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2, siso_channel_comp, siso_mrc_combine, siso_lsig_demap_bpsk_i, siso_lsig_deinterleave, l_sig_vit);

      ONCE(l_sig_parser);
    }));
    return *l_sig_ok;
  };

  auto htsig_handler = [&]() -> bool
  {
    *VitTotalBits = 48;
    *ht_sig_ok = false;
    //ht-sig
    START(src, wait_ofdm, IF([&]
    {
      bool bRet = false;
      ONCE(cfo_comp, remove_gi1,fft_data1);
      ONCE(remove_gi2, fft_data2, siso_channel_comp, siso_mrc_combine, htsig_demap_bpsk_q, siso_lsig_deinterleave, ht_sig_vit);

      START(IF(ht_sig_parser), [&]{bRet = true;});
      return bRet;
    }), STOP(NOP), ELSE, NOP);
    printf("HT_SIG: MCS=%d, Length=%d\n", *ht_frame_mcs, *ht_frame_length);
    return *ht_sig_ok;
  };

  auto htstf_handler = [&]() -> bool
  {
    // ht-stf
    START(src, wait_ofdm, cfo_comp, ht_stf, STOP(NOP));
    return true;
  };

  auto htltf_handler = [&]() -> bool
  {
    // ht-ltf
    START(src, wait_ofdm, IF([&]
    {
      bool bRet = false;

      ONCE(cfo_comp, remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);

      START(IF(mimo_channel_estimator), [&]{bRet = true;});

      return bRet;
    }), STOP(NOP), ELSE, NOP);
    return true;
  };

  auto pipeline_init = [&]
  {
    *crc32_check_length = *ht_frame_length;

    frame_decode_done = false;
    descramble_state = 0;

    symbol_count = ht_symbol_count(*ht_frame_mcs, *ht_frame_length, &VitTotalBits);
    total_symbol_count = symbol_count;
  };

  int nwork1 = 0;
  int nwork2 = 0;

  auto rx_vit12_pipeline = [&]
  {
    START(ht_data_vit_12, 
      IF(IsTrue(descramble_state == 0)), 
      IF(descramble_seed), [&]{descramble_state = 1;}, ELSE, NOP,
      ELSE, descramble, crc32_checker, STOP(NOP)
      );
    //printf("nworker2 : %d\n", ++nwork2);
  };

  auto rx_vit23_pipeline = [&]
  {
    START(ht_data_vit_23, 
      IF(IsTrue(descramble_state == 0)), 
      IF(descramble_seed), [&]{descramble_state = 1;}, ELSE, NOP,
      ELSE, descramble, crc32_checker, STOP(NOP)
      );
    //printf("nworker2 : %d\n", ++nwork2);
  };

  auto rx_vit34_pipeline = [&]
  {
    START(ht_data_vit_34, 
      IF(IsTrue(descramble_state == 0)), 
      IF(descramble_seed), [&]{descramble_state = 1;}, ELSE, NOP,
      ELSE, descramble, crc32_checker, STOP(NOP)
      );
    //printf("nworker2 : %d\n", ++nwork2);
  };
  //////////////////////////////////////////////////////////////////////////

  auto rx_bpsk_pipeline_1 = [&]() -> bool
  {
    START(src, wait_ofdm, STOP([&]
    {
      ONCE(cfo_comp, remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2, mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_bpsk1, ht_deinterleave_1bpsc_iss1,
        ht_demap_bpsk2, ht_deinterleave_1bpsc_iss2, ht_stream_joiner_1);
    }));

    //printf("nworker1 : %d\n", ++nwork1);

    symbol_count--;
    return symbol_count > 0;
  };

  auto rx_qpsk_pipeline_1 = [&]() -> bool
  {
    START(src, wait_ofdm, STOP([&]
    {
      ONCE(cfo_comp, remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2, mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_qpsk1, ht_deinterleave_2bpsc_iss1,
        ht_demap_qpsk2, ht_deinterleave_2bpsc_iss2, ht_stream_joiner_1);
    }));

    //printf("nworker1 : %d\n", ++nwork1);

    symbol_count--;
    return symbol_count > 0;
  };

  auto rx_16qam_pipeline_1 = [&]() -> bool
  {
    START(src, wait_ofdm, STOP([&]
    {
      ONCE(cfo_comp, remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2, mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_16qam1, ht_deinterleave_4bpsc_iss1,
        ht_demap_16qam2, ht_deinterleave_4bpsc_iss2, ht_stream_joiner_2);
    }));

    //printf("nworker1 : %d\n", ++nwork1);

    symbol_count--;
    return symbol_count > 0;
  };

  auto rx_64qam_pipeline_1 = [&]() -> bool
  {
    START(src, wait_ofdm, STOP([&]
    {
      ONCE(cfo_comp, remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2, mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_64qam1, ht_deinterleave_6bpsc_iss1,
        ht_demap_64qam2, ht_deinterleave_6bpsc_iss2, ht_stream_joiner_3);
    }));

    //printf("nworker1 : %d\n", ++nwork1);

    symbol_count--;
    return symbol_count > 0;
  };
  //////////////////////////////////////////////////////////////////////////
  auto rx_mcs8_pipeline = [&]
  {
    t1 = tick_count::now();
    PIPE_LINE(rx_bpsk_pipeline_1, rx_vit12_pipeline);
    t2 = tick_count::now();
    tick_count t = t2 - t1;
    printf("time = %f us, %f MSPS\n", t.us(), total_symbol_count * 80 / t.us());
    printf("frame decode done! %d\n", *crc32_check_result);
  };

  auto rx_mcs9_pipeline = [&]
  {
    t1 = tick_count::now();
    PIPE_LINE(rx_qpsk_pipeline_1, rx_vit12_pipeline);
    t2 = tick_count::now();
    tick_count t = t2 - t1;
    printf("time = %f us, %f MSPS\n", t.us(), total_symbol_count * 80 / t.us());
    printf("frame decode done! %d\n", *crc32_check_result);
  };

  auto rx_mcs10_pipeline = [&]
  {
    t1 = tick_count::now();
    PIPE_LINE(rx_qpsk_pipeline_1, rx_vit34_pipeline);
    t2 = tick_count::now();
    tick_count t = t2 - t1;
    printf("time = %f us, %f MSPS\n", t.us(), total_symbol_count * 80 / t.us());
    printf("frame decode done! %d\n", *crc32_check_result);
  };

  auto rx_mcs11_pipeline = [&]
  {
    t1 = tick_count::now();
    PIPE_LINE(rx_16qam_pipeline_1, rx_vit12_pipeline);
    t2 = tick_count::now();
    tick_count t = t2 - t1;
    printf("time = %f us, %f MSPS\n", t.us(), total_symbol_count * 80 / t.us());
    printf("frame decode done! %d\n", *crc32_check_result);
  };

  auto rx_mcs12_pipeline = [&]
  {
    t1 = tick_count::now();
    PIPE_LINE(rx_16qam_pipeline_1, rx_vit34_pipeline);
    t2 = tick_count::now();
    tick_count t = t2 - t1;
    printf("time = %f us, %f MSPS\n", t.us(), total_symbol_count * 80 / t.us());
    printf("frame decode done! %d\n", *crc32_check_result);
  };

  auto rx_mcs13_pipeline = [&]
  {
    t1 = tick_count::now();
    PIPE_LINE(rx_64qam_pipeline_1, rx_vit23_pipeline);
    t2 = tick_count::now();
    tick_count t = t2 - t1;
    printf("time = %f us, %f MSPS\n", t.us(), total_symbol_count * 80 / t.us());
    printf("frame decode done! %d\n", *crc32_check_result);
  };

  auto rx_mcs14_pipeline = [&]
  {
    t1 = tick_count::now();
    PIPE_LINE(rx_64qam_pipeline_1, rx_vit34_pipeline);
    t2 = tick_count::now();
    tick_count t = t2 - t1;
    printf("time = %f us, %f MSPS\n", t.us(), total_symbol_count * 80 / t.us());
    printf("frame decode done! %d\n", *crc32_check_result);
  };

  auto htdata_handler = [&]
  {
    ONCE(pipeline_init);
    START(
      IF(IsTrue(*ht_frame_mcs == 8)),  rx_mcs8_pipeline,
      ELSE_IF(IsTrue(*ht_frame_mcs == 9)),  rx_mcs9_pipeline,
      ELSE_IF(IsTrue(*ht_frame_mcs == 10)), rx_mcs10_pipeline,
      ELSE_IF(IsTrue(*ht_frame_mcs == 11)), rx_mcs11_pipeline,
      ELSE_IF(IsTrue(*ht_frame_mcs == 12)), rx_mcs12_pipeline,
      ELSE_IF(IsTrue(*ht_frame_mcs == 13)), rx_mcs13_pipeline,
      ELSE_IF(IsTrue(*ht_frame_mcs == 14)), rx_mcs14_pipeline,
      ELSE, NOP
      );
  };

  START(
    WHILE(frame_detection), IF(lltf_handler), IF(lsig_handler), IF(htsig_handler), IF(htstf_handler), IF(htltf_handler), htdata_handler
    );



#else

  auto vit_task = make_task_obj([&]
  {
    //----------------
    // start viterbi
    //----------------
    START(
      IF( IsTrue( (*ht_frame_mcs == 8 || *ht_frame_mcs == 9 || *ht_frame_mcs == 11) ) ),
      ht_data_vit_12,
      ELSE_IF( IsTrue( (*ht_frame_mcs == 13) ) ),
      ht_data_vit_23,
      ELSE_IF( IsTrue( (*ht_frame_mcs == 10 || *ht_frame_mcs == 12 || *ht_frame_mcs == 14) ) ),
      ht_data_vit_34,
      ELSE, NOP
      );

    //printf("---symbol count = %d\n", symbol_count);
    // descramble and crc32 checking
    START(
      IF(IsTrue(descramble_state == 0)), 
      IF(descramble_seed), [&]{descramble_state = 1;}, ELSE, NOP,
      ELSE, descramble, crc32_checker, STOP([&]
    {
      frame_decode_done = true; 
    })
      );
  });


  START(src,
    // frame detection
    IF(IsTrue(branch1 == CS)),[&]
  {
    START(axorr, IF(lstf_searcher), STOP([&]{branch1 = CFO;}));
  },
    ELSE_IF(IsTrue(branch1 == CFO)),
    // carrier frequency offset estimation using L-LTF
    IF(cfo_est), [&]{branch1 = OTHER; branch2 = SISO_CHANNEL_ESTIMATION;}, ELSE, NOP,
    ELSE_IF(IsTrue(branch1 == OTHER)), [&]
  {
    START(
      // carrier frequency offset compensation
      cfo_comp,
      // L-LTF branch: SISO channel estimation
      IF(IsTrue(branch2 == SISO_CHANNEL_ESTIMATION)),[&]
    {
      START(fft_lltf1);
      START(fft_lltf2, siso_channel_est, STOP([&]{branch2 = L_SIG; *VitTotalSoftBits = 48;}));
    },
      // L-SIG branch: legacy signal field decoding using MRC
      ELSE_IF(IsTrue(branch2 == L_SIG)), [&]
    {
      START(IF(remove_gi1), fft_data1);
      START(IF(remove_gi2), fft_data2, siso_channel_comp, siso_mrc_combine, siso_lsig_demap_bpsk_i, siso_lsig_deinterleave, l_sig_vit, l_sig_parser), STOP([&]{ if (*l_sig_ok) branch2 = HT_SIG1; else {branch1 = CS; branch2 = HT_OTHER;} }));
    },
      ELSE_IF(IsTrue(branch2 == HT_SIG1)), [&]
    {
      START(IF(remove_gi1), fft_data1);
      START(IF(remove_gi2), fft_data2, siso_channel_comp, siso_mrc_combine, htsig_demap_bpsk_q, siso_lsig_deinterleave, STOP([&]{branch2 = HT_SIG2; *VitTotalSoftBits = 96;}));
    },
      ELSE_IF(IsTrue(branch2 == HT_SIG2)), [&]
    {
      START(IF(remove_gi1), fft_data1);
      START(IF(remove_gi2), fft_data2, siso_channel_comp, siso_mrc_combine, htsig_demap_bpsk_q, siso_lsig_deinterleave, ht_sig_vit, ht_sig_parser, STOP([&]{if (*ht_sig_ok) branch2 = HT_STF; else {branch1 = CS; branch2 = HT_OTHER;} }));
    },
      ELSE_IF(IsTrue(branch2 == HT_STF)), [&]
    {
      START(ht_stf, [&]{branch2 = HT_LTF;});
    },
      ELSE_IF(IsTrue(branch2 == HT_LTF)), [&]
    {
      START(remove_gi1, fft_data1);
      START(remove_gi2, fft_data2, mimo_channel_estimator, 
        STOP([&]{
          branch2 = HT_DATA;

          printf("HT_SIG: MCS=%d, Length=%d\n", *ht_frame_mcs, *ht_frame_length);

          if (*ht_frame_mcs == 8 || *ht_frame_mcs == 9 || *ht_frame_mcs == 11) // 1/2
          {
            *VitTotalSoftBits = (*ht_frame_length * 8 + 16 + 6) * 2; // 1/2 coding
          }
          else if (*ht_frame_mcs == 13) // 2/3
          {
            *VitTotalSoftBits = (*ht_frame_length * 8 + 16 + 6) * 3 / 2;
          }
          else if (*ht_frame_mcs == 10 || *ht_frame_mcs == 12 || *ht_frame_mcs == 14)
          {
            *VitTotalSoftBits = (*ht_frame_length * 8 + 16 + 6) * 4 / 3 + 1;
          }

          *crc32_check_length = *ht_frame_length;

          frame_decode_done = false;
          descramble_state = 0;

          symbol_count = ht_symbol_count(*ht_frame_mcs, *ht_frame_length);
          total_symbol_count = symbol_count;

          t1 = tick_count::now();
      })
        );
    },
      ELSE_IF(IsTrue(branch2 == HT_DATA)), 
      IF(IsTrue(symbol_count > 0)), [&]
    {
      START(IF(remove_gi1), [&]
      {
        START(fft_data1);
        START(remove_gi2, fft_data2, mimo_channel_compensator, pilot_tracking, [&]
        {
          START( IF(IsTrue(*ht_frame_mcs == 8)), [&]
          {
            START(ht_demap_bpsk1, ht_deinterleave_1bpsc_iss1);
            START(ht_demap_bpsk2, ht_deinterleave_1bpsc_iss2, ht_stream_joiner_1);
          },
            ELSE_IF(IsTrue( (*ht_frame_mcs == 9 || *ht_frame_mcs == 10) )), [&]
          {
            START(ht_demap_qpsk1, ht_deinterleave_2bpsc_iss1);
            START(ht_demap_qpsk2, ht_deinterleave_2bpsc_iss2, ht_stream_joiner_2);
          },
            ELSE_IF(IsTrue( (*ht_frame_mcs == 11 || *ht_frame_mcs == 12) )), [&]
          {
            START(ht_demap_16qam1, ht_deinterleave_4bpsc_iss1);
            START(ht_demap_16qam2, ht_deinterleave_4bpsc_iss2, ht_stream_joiner_3);
          },
            ELSE_IF(IsTrue( (*ht_frame_mcs == 13 || *ht_frame_mcs == 14) )), [&]
          {
            START(ht_demap_64qam1, ht_deinterleave_6bpsc_iss1);
            START(ht_demap_64qam2, ht_deinterleave_6bpsc_iss2, ht_stream_joiner_4);
          },
            ELSE, NOP
            );
          symbol_count--;
#if 0
          vit_task.invoke();
#else
          vit_task.wait();
          cm->run_task(&vit_task);
#endif
        });
      });
    },
      ELSE, STOP([&]
    {
      vit_task.wait(); 

      t2 = tick_count::now();
      tick_count t = t2 - t1;
      printf("time = %f us, %f MSPS\n", t.us(), total_symbol_count * 80 / t.us());

      printf("frame decode done! %d\n", *crc32_check_result);

      branch1 = CS; 
      branch2 = SISO_CHANNEL_ESTIMATION;
    }),
      ELSE, NOP
      );
  },
    ELSE, STOP(NOP)
    );
#endif
};