#pragma once

void mumimo_4x4_rx(int argc, _TCHAR* argv[])
{
  dsp_cmd cmdline;
  cmdline.parse(argc, argv);

  int bUseZF = cmdline.get("zf").as_int();

  autoref dummy = create_block<dummy_block>();

  string strFileName1 = string("FileName1=c:\\MiMo_0.dmp");
  string strFileName2 = string("FileName2=c:\\MiMo_1.dmp");
  string strFileName3 = string("FileName3=c:\\MiMo_2.dmp");
  string strFileName4 = string("FileName4=c:\\MiMo_3.dmp");

  auto CmdArg = cmdline.get("FileName1");
  if ( CmdArg.exist() )
  {
    strFileName1 = "FileName1=" + CmdArg.as_string();
  }
  CmdArg = cmdline.get("FileName2");
  if ( CmdArg.exist() )
  {
    strFileName2 = "FileName2=" + CmdArg.as_string();
  }
  CmdArg = cmdline.get("FileName3");
  if ( CmdArg.exist() )
  {
    strFileName3 = "FileName3=" + CmdArg.as_string();
  }
  CmdArg = cmdline.get("FileName4");
  if ( CmdArg.exist() )
  {
    strFileName4 = "FileName4=" + CmdArg.as_string();
  }

  autoref src = create_block<b_file_source_v4>(
    5, strFileName1, strFileName2, strFileName3, strFileName4, string("Decimate=1"));

  autoref wait_lltf                  = create_block<b_wait_4v>( 1, string("nwait=32") );
  autoref wait_ofdm                  = create_block<b_wait_4v>( 1, string("nwait=20") );
  autoref axorr                      = create_block<b_auto_corr_4v2>( 1,  string("vHisLength=8") );

  autoref lstf_searcher              = create_block<b_lstf_searcher_2v1>();
  autoref cfo_est                    = create_block<b_frequest_offset_estimator_parallel_4_4v>( 2, string("vEstimateLength=16"), string("vEstimateDistance=16") );
  autoref cfo_comp                   = create_block<b_frequest_offset_compensator_parallel_4_4v4>( 1, string("vCompensateLength=2") );

  autoref fft_lltf1                  = create_block<b_fft_64_1v1>();
  autoref fft_lltf2                  = create_block<b_fft_64_1v1>();
  autoref fft_lltf3                  = create_block<b_fft_64_1v1>();
  autoref fft_lltf4                  = create_block<b_fft_64_1v1>();


  autoref remove_gi1                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );
  autoref remove_gi2                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );
  autoref remove_gi3                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );
  autoref remove_gi4                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );

  autoref fft_data1                  = create_block<b_fft_64_1v1>();
  autoref fft_data2                  = create_block<b_fft_64_1v1>();
  autoref fft_data3                  = create_block<b_fft_64_1v1>();
  autoref fft_data4                  = create_block<b_fft_64_1v1>();

  autoref siso_channel_est           = create_block<b_dot11_siso_channel_estimator_4v>();
  autoref siso_channel_comp          = create_block<b_dot11_siso_channel_compensator_4v4>();

  autoref siso_mrc_combine           = create_block<b_mrc_combine_4v1>();

  autoref siso_lsig_demap_bpsk_i     = create_block<b_dot11_demap_bpsk_i_1v1>( 2, string("low=-26"), string("high=26") );

  autoref siso_lsig_deinterleave     = create_block<b_dot11a_deinterleave_1bpsc_1v1>();

  autoref l_sig_vit                  = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=24"), string("TraceBackOutput=24") );

  autoref htsig_demap_bpsk_q         = create_block<b_dot11_demap_bpsk_q_1v1>( 2, string("low=-26"), string("high=26") );

  autoref ht_sig_vit                 = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=48"), string("TraceBackOutput=48") );

  autoref ht_data_vit_12_1           = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=48"), string("TraceBackOutput=96") );
  autoref ht_data_vit_12_2           = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=48"), string("TraceBackOutput=96") );
  autoref ht_data_vit_12_3           = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=48"), string("TraceBackOutput=96") );
  autoref ht_data_vit_12_4           = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=48"), string("TraceBackOutput=96") );

  autoref ht_data_vit_23_1           = create_block<b_viterbi64_2o3_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192") );
  autoref ht_data_vit_23_2           = create_block<b_viterbi64_2o3_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192") );
  autoref ht_data_vit_23_3           = create_block<b_viterbi64_2o3_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192") );
  autoref ht_data_vit_23_4           = create_block<b_viterbi64_2o3_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192") );

  autoref ht_data_vit_34_1           = create_block<b_viterbi64_3o4_1v1>(
    2,
    //string("TraceBackLength        =144"),
    //string("TraceBackOutput        =384")
    string("TraceBackLength          =36"),
    string("TraceBackOutput          =192")
    );
  autoref ht_data_vit_34_2           = create_block<b_viterbi64_3o4_1v1>(
    2,
    //string("TraceBackLength        =144"),
    //string("TraceBackOutput        =384")
    string("TraceBackLength          =36"),
    string("TraceBackOutput          =192")
    );
  autoref ht_data_vit_34_3           = create_block<b_viterbi64_3o4_1v1>(
    2,
    //string("TraceBackLength        =144"),
    //string("TraceBackOutput        =384")
    string("TraceBackLength          =36"),
    string("TraceBackOutput          =192")
    );
  autoref ht_data_vit_34_4           = create_block<b_viterbi64_3o4_1v1>(
    2,
    //string("TraceBackLength        =144"),
    //string("TraceBackOutput        =384")
    string("TraceBackLength          =36"),
    string("TraceBackOutput          =192")
    );

  autoref l_sig_parser               = create_block<b_lsig_parser_1v>();
  autoref ht_sig_parser              = create_block<b_htsig_parser_1v>();
  autoref ht_stf                     = create_block<b_drop_4v>(1, string("nDrop=20") );

  autoref noise_estimator            = create_block<b_noise_estimator2_4v>();
  autoref mimo_channel_estimator_zf  = create_block<b_dot11_mimo_channel_estimator_4v>();
  autoref mimo_channel_estimator_mmse= create_block<b_dot11_mimo_channel_estimator_mmse_4v>();
  
  autoref mimo_channel_compensator_1 = create_block<b_dot11_mimo_channel_compensator_4v1>(1, string("iss=0"));
  autoref mimo_channel_compensator_2 = create_block<b_dot11_mimo_channel_compensator_4v1>(1, string("iss=1"));
  autoref mimo_channel_compensator_3 = create_block<b_dot11_mimo_channel_compensator_4v1>(1, string("iss=2"));
  autoref mimo_channel_compensator_4 = create_block<b_dot11_mimo_channel_compensator_4v1>(1, string("iss=3"));

  autoref ht_demap_bpsk1             = create_block<b_dot11_demap_bpsk_i_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_bpsk2             = create_block<b_dot11_demap_bpsk_i_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_bpsk3             = create_block<b_dot11_demap_bpsk_i_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_bpsk4             = create_block<b_dot11_demap_bpsk_i_1v1>( 2, string("low=-28"), string("high=28") );

  autoref ht_demap_qpsk1             = create_block<b_dot11_demap_qpsk_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_qpsk2             = create_block<b_dot11_demap_qpsk_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_qpsk3             = create_block<b_dot11_demap_qpsk_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_qpsk4             = create_block<b_dot11_demap_qpsk_1v1>( 2, string("low=-28"), string("high=28") );

  autoref ht_demap_16qam1            = create_block<b_dot11_demap_16qam_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_16qam2            = create_block<b_dot11_demap_16qam_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_16qam3            = create_block<b_dot11_demap_16qam_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_16qam4            = create_block<b_dot11_demap_16qam_1v1>( 2, string("low=-28"), string("high=28") );

  autoref ht_demap_64qam1            = create_block<b_dot11_demap_64qam_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_64qam2            = create_block<b_dot11_demap_64qam_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_64qam3            = create_block<b_dot11_demap_64qam_1v1>( 2, string("low=-28"), string("high=28") );
  autoref ht_demap_64qam4            = create_block<b_dot11_demap_64qam_1v1>( 2, string("low=-28"), string("high=28") );

  // deinterleave
  autoref ht_deinterleave_1bpsc_iss1 = create_block<b_dot11n_deinterleave_1bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_1bpsc_iss2 = create_block<b_dot11n_deinterleave_1bpsc_1v1>( 1, string("iss=2") );
  autoref ht_deinterleave_1bpsc_iss3 = create_block<b_dot11n_deinterleave_1bpsc_1v1>( 1, string("iss=3") );
  autoref ht_deinterleave_1bpsc_iss4 = create_block<b_dot11n_deinterleave_1bpsc_1v1>( 1, string("iss=4") );

  autoref ht_deinterleave_2bpsc_iss1 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_2bpsc_iss2 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=2") );
  autoref ht_deinterleave_2bpsc_iss3 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=3") );
  autoref ht_deinterleave_2bpsc_iss4 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=4") );

  autoref ht_deinterleave_4bpsc_iss1 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_4bpsc_iss2 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=2") );
  autoref ht_deinterleave_4bpsc_iss3 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=3") );
  autoref ht_deinterleave_4bpsc_iss4 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=4") );

  autoref ht_deinterleave_6bpsc_iss1 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_6bpsc_iss2 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=2") );
  autoref ht_deinterleave_6bpsc_iss3 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=3") );
  autoref ht_deinterleave_6bpsc_iss4 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=4") );

  autoref descramble_1               = create_block<b_dot11_descramble_1v1>();
  autoref descramble_2               = create_block<b_dot11_descramble_1v1>();
  autoref descramble_3               = create_block<b_dot11_descramble_1v1>();
  autoref descramble_4               = create_block<b_dot11_descramble_1v1>();

  autoref crc32_checker_1            = create_block<b_crc32_check_1v>();
  autoref crc32_checker_2            = create_block<b_crc32_check_1v>();
  autoref crc32_checker_3            = create_block<b_crc32_check_1v>();
  autoref crc32_checker_4            = create_block<b_crc32_check_1v>();

  autoref pilot_tracking_1           = create_block<b_dot11_pilot_tracking_parallel_4_1v>(1, string("iss=0"));
  autoref pilot_tracking_2           = create_block<b_dot11_pilot_tracking_parallel_4_1v>(1, string("iss=1"));
  autoref pilot_tracking_3           = create_block<b_dot11_pilot_tracking_parallel_4_1v>(1, string("iss=2"));
  autoref pilot_tracking_4           = create_block<b_dot11_pilot_tracking_parallel_4_1v>(1, string("iss=3"));
  //---------------------------------------------------------
  Channel::Create(sizeof(v_cs))
    .from(src, 0)
    .to(wait_lltf, 0).to(wait_ofdm, 0).to(axorr, 0).to(cfo_est, 0).to(cfo_comp, 0);

  Channel::Create(sizeof(v_cs))
    .from(src, 1)
    .to(wait_lltf, 1).to(wait_ofdm, 1).to(axorr, 1).to(cfo_est, 1).to(cfo_comp, 1);

  Channel::Create(sizeof(v_cs))
    .from(src, 2)
    .to(wait_lltf, 2).to(wait_ofdm, 2).to(axorr, 2).to(cfo_est, 2).to(cfo_comp, 2);

  Channel::Create(sizeof(v_cs))
    .from(src, 3)
    .to(wait_lltf, 3).to(wait_ofdm, 3).to(axorr, 3).to(cfo_est, 3).to(cfo_comp, 3);

  Channel::Create(sizeof(v_q))
    .from(axorr, 0)
    .to(lstf_searcher, 0);

  Channel::Create(sizeof(v_q))
    .from(axorr, 1)
    .to(lstf_searcher, 1);

  //
  Channel::Create(sizeof(v_cs))
    .from(cfo_comp, 0)
    .to(fft_lltf1, 0).to(remove_gi1, 0).to(fft_data1, 0).to(ht_stf, 0);

  Channel::Create(sizeof(v_cs))
    .from(cfo_comp, 1)
    .to(fft_lltf2, 0).to(remove_gi2, 0).to(fft_data2, 0).to(ht_stf, 1);

  Channel::Create(sizeof(v_cs))
    .from(cfo_comp, 2)
    .to(fft_lltf3, 0).to(remove_gi3, 0).to(fft_data3, 0).to(ht_stf, 2);

  Channel::Create(sizeof(v_cs))
    .from(cfo_comp, 3)
    .to(fft_lltf4, 0).to(remove_gi4, 0).to(fft_data4, 0).to(ht_stf, 3);

  // 
  Channel::Create(sizeof(v_cs))
    .from(fft_lltf1, 0).to(noise_estimator, 0)
    .to(siso_channel_est, 0);

  Channel::Create(sizeof(v_cs))
    .from(fft_lltf2, 0).to(noise_estimator, 1)
    .to(siso_channel_est, 1);

  Channel::Create(sizeof(v_cs))
    .from(fft_lltf3, 0).to(noise_estimator, 2)
    .to(siso_channel_est, 2);

  Channel::Create(sizeof(v_cs))
    .from(fft_lltf4, 0).to(noise_estimator, 3)
    .to(siso_channel_est, 3);

  //
  Channel::Create(sizeof(v_cs))
    .from(fft_data1, 0)
    .to(siso_channel_comp, 0).to(mimo_channel_estimator_zf, 0).to(mimo_channel_estimator_mmse, 0)
    .to(mimo_channel_compensator_1, 0).to(mimo_channel_compensator_2, 0).to(mimo_channel_compensator_3, 0).to(mimo_channel_compensator_4, 0);
  Channel::Create(sizeof(v_cs))
    .from(fft_data2, 0)
    .to(siso_channel_comp, 1).to(mimo_channel_estimator_zf, 1).to(mimo_channel_estimator_mmse, 1)
    .to(mimo_channel_compensator_1, 1).to(mimo_channel_compensator_2, 1).to(mimo_channel_compensator_3, 1).to(mimo_channel_compensator_4, 1);
  Channel::Create(sizeof(v_cs))
    .from(fft_data3, 0)
    .to(siso_channel_comp, 2).to(mimo_channel_estimator_zf, 2).to(mimo_channel_estimator_mmse, 2)
    .to(mimo_channel_compensator_1, 2).to(mimo_channel_compensator_2, 2).to(mimo_channel_compensator_3, 2).to(mimo_channel_compensator_4, 2);
  Channel::Create(sizeof(v_cs))
    .from(fft_data4, 0)
    .to(siso_channel_comp, 3).to(mimo_channel_estimator_zf, 3).to(mimo_channel_estimator_mmse, 3)
    .to(mimo_channel_compensator_1, 3).to(mimo_channel_compensator_2, 3).to(mimo_channel_compensator_3, 3).to(mimo_channel_compensator_4, 3);

  //
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 0).to(siso_mrc_combine, 0)
    .from(mimo_channel_compensator_1, 0)
    .to(ht_demap_bpsk1, 0).to(ht_demap_qpsk1, 0).to(ht_demap_16qam1, 0).to(ht_demap_64qam1, 0).to(pilot_tracking_1, 0);
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 1).to(siso_mrc_combine, 1)
    .from(mimo_channel_compensator_2, 0)
    .to(ht_demap_bpsk2, 0).to(ht_demap_qpsk2, 0).to(ht_demap_16qam2, 0).to(ht_demap_64qam2, 0).to(pilot_tracking_2, 0);
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 2).to(siso_mrc_combine, 2)
    .from(mimo_channel_compensator_3, 0)
    .to(ht_demap_bpsk3, 0).to(ht_demap_qpsk3, 0).to(ht_demap_16qam3, 0).to(ht_demap_64qam3, 0).to(pilot_tracking_3, 0);
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 3).to(siso_mrc_combine, 3)
    .from(mimo_channel_compensator_4, 0)
    .to(ht_demap_bpsk4, 0).to(ht_demap_qpsk4, 0).to(ht_demap_16qam4, 0).to(ht_demap_64qam4, 0).to(pilot_tracking_4, 0);

  //
  Channel::Create(sizeof(v_cs))
    .from(siso_mrc_combine, 0)
    .to(siso_lsig_demap_bpsk_i, 0).to(htsig_demap_bpsk_q, 0);

  Channel::Create(sizeof(uint8))
    .from(siso_lsig_demap_bpsk_i, 0).from(htsig_demap_bpsk_q, 0)
    .to(siso_lsig_deinterleave, 0);

  Channel::Create(sizeof(uint8))
    .from(siso_lsig_deinterleave, 0).to(l_sig_vit, 0).to(ht_sig_vit, 0);

  Channel::Create(sizeof(uint8))
    .from(l_sig_vit, 0)
    .to(l_sig_parser, 0);

  Channel::Create(sizeof(uint8))
    .from(ht_sig_vit, 0)
    .to(ht_sig_parser, 0);

  // ht-data
  
  // demap
  Channel::Create(sizeof(uint8))
    .from(ht_demap_bpsk1, 0).from(ht_demap_qpsk1, 0).from(ht_demap_16qam1, 0).from(ht_demap_64qam1, 0)
    .to(ht_deinterleave_1bpsc_iss1, 0).to(ht_deinterleave_2bpsc_iss1, 0).to(ht_deinterleave_4bpsc_iss1, 0).to(ht_deinterleave_6bpsc_iss1, 0);

  Channel::Create(sizeof(uint8))
    .from(ht_demap_bpsk2, 0).from(ht_demap_qpsk2, 0).from(ht_demap_16qam2, 0).from(ht_demap_64qam2, 0)
    .to(ht_deinterleave_1bpsc_iss2, 0).to(ht_deinterleave_2bpsc_iss2, 0).to(ht_deinterleave_4bpsc_iss2, 0).to(ht_deinterleave_6bpsc_iss2, 0);
  Channel::Create(sizeof(uint8))
    .from(ht_demap_bpsk3, 0).from(ht_demap_qpsk3, 0).from(ht_demap_16qam3, 0).from(ht_demap_64qam3, 0)
    .to(ht_deinterleave_1bpsc_iss3, 0).to(ht_deinterleave_2bpsc_iss3, 0).to(ht_deinterleave_4bpsc_iss3, 0).to(ht_deinterleave_6bpsc_iss3, 0);
  Channel::Create(sizeof(uint8))
    .from(ht_demap_bpsk4, 0).from(ht_demap_qpsk4, 0).from(ht_demap_16qam4, 0).from(ht_demap_64qam4, 0)
    .to(ht_deinterleave_1bpsc_iss4, 0).to(ht_deinterleave_2bpsc_iss4, 0).to(ht_deinterleave_4bpsc_iss4, 0).to(ht_deinterleave_6bpsc_iss4, 0);
  
  //deinterleave
  Channel::Create(sizeof(uint8))
    .from(ht_deinterleave_1bpsc_iss1, 0).from(ht_deinterleave_2bpsc_iss1, 0).from(ht_deinterleave_4bpsc_iss1, 0).from(ht_deinterleave_6bpsc_iss1, 0)
    .to(ht_data_vit_12_1, 0).to(ht_data_vit_23_1, 0).to(ht_data_vit_34_1, 0);
  Channel::Create(sizeof(uint8))
    .from(ht_deinterleave_1bpsc_iss2, 0).from(ht_deinterleave_2bpsc_iss2, 0).from(ht_deinterleave_4bpsc_iss2, 0).from(ht_deinterleave_6bpsc_iss2, 0)
    .to(ht_data_vit_12_2, 0).to(ht_data_vit_23_2, 0).to(ht_data_vit_34_2, 0);
  Channel::Create(sizeof(uint8))
    .from(ht_deinterleave_1bpsc_iss3, 0).from(ht_deinterleave_2bpsc_iss3, 0).from(ht_deinterleave_4bpsc_iss3, 0).from(ht_deinterleave_6bpsc_iss3, 0)
    .to(ht_data_vit_12_3, 0).to(ht_data_vit_23_3, 0).to(ht_data_vit_34_3, 0);
  Channel::Create(sizeof(uint8))
    .from(ht_deinterleave_1bpsc_iss4, 0).from(ht_deinterleave_2bpsc_iss4, 0).from(ht_deinterleave_4bpsc_iss4, 0).from(ht_deinterleave_6bpsc_iss4, 0)
    .to(ht_data_vit_12_4, 0).to(ht_data_vit_23_4, 0).to(ht_data_vit_34_4, 0);

  // descramble  
  Channel::Create(sizeof(uint8))
    .from(ht_data_vit_12_1, 0).from(ht_data_vit_23_1, 0).from(ht_data_vit_34_1, 0)
    .to(descramble_1, 0);
  Channel::Create(sizeof(uint8))
    .from(ht_data_vit_12_2, 0).from(ht_data_vit_23_2, 0).from(ht_data_vit_34_2, 0)
    .to(descramble_2, 0);
  Channel::Create(sizeof(uint8))
    .from(ht_data_vit_12_3, 0).from(ht_data_vit_23_3, 0).from(ht_data_vit_34_3, 0)
    .to(descramble_3, 0);
  Channel::Create(sizeof(uint8))
    .from(ht_data_vit_12_4, 0).from(ht_data_vit_23_4, 0).from(ht_data_vit_34_4, 0)
    .to(descramble_4, 0);

  // crc
  Channel::Create(sizeof(uint8))
    .from(descramble_1, 0).to(crc32_checker_1, 0);
  Channel::Create(sizeof(uint8))
    .from(descramble_2, 0).to(crc32_checker_2, 0);
  Channel::Create(sizeof(uint8))
    .from(descramble_3, 0).to(crc32_checker_3, 0);
  Channel::Create(sizeof(uint8))
    .from(descramble_4, 0).to(crc32_checker_4, 0);
  //---------------------------------------------------------
  // var used by 1st block
  v_align(64)
  _global_(bool, l_sig_ok);
  _global_(bool, ht_sig_ok);
  _global_(uint32, ht_frame_mcs);
  _global_(uint16, ht_frame_length);
  int VitTotalBits = 0;
  int symbol_count = 0;
  int total_symbol_count = 0;
  tick_count t1, t2, t3;

  // var used by 2nd block
  //v_align(64)
  //////////////////////////////////////////////////////////////////////////
  auto frame_detection = [&]() -> bool
  {
    bool bRet = false;
    RESET(axorr);
    START(src, axorr, lstf_searcher, STOP([&]{bRet = true;}));
    return bRet;
  };

  auto lltf_handler = [&]() -> bool
  {
    START(src, wait_lltf, IF([&]
    {
      ONCE(cfo_est, cfo_comp);
      START(fft_lltf1, fft_lltf2, fft_lltf3, fft_lltf4);
      ONCE(noise_estimator, siso_channel_est);
      return true;
    }), STOP(NOP));
    return true;
  };

  auto lsig_handler = [&]() -> bool
  {
    *l_sig_vit.VitTotalBits     = 24;
    *l_sig_vit.VitTotalSoftBits = 48;
    *l_sig_ok = false;
    //l-sig
    START(src, wait_ofdm, STOP([&]
    {
      ONCE(cfo_comp, remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(siso_channel_comp, siso_mrc_combine, siso_lsig_demap_bpsk_i, siso_lsig_deinterleave, l_sig_vit);

      ONCE(l_sig_parser);
    }));
    return *l_sig_ok;
  };

  auto htsig_handler = [&]() -> bool
  {
    *ht_sig_vit.VitTotalBits = 48;
    *ht_sig_vit.VitTotalSoftBits = 96;
    *ht_sig_ok = false;
    //ht-sig
    START(src, wait_ofdm, IF([&]
    {
      bool bRet = false;
      ONCE(cfo_comp, remove_gi1,fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(siso_channel_comp, siso_mrc_combine, htsig_demap_bpsk_q, siso_lsig_deinterleave, ht_sig_vit);

      START(IF(ht_sig_parser), [&]{bRet = true;});
      return bRet;
    }), STOP(NOP), ELSE, NOP);
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
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);

      if (bUseZF)
      {
        START(IF(mimo_channel_estimator_zf), [&]{bRet = true;});
      }
      else
      {
        START(IF(mimo_channel_estimator_mmse), [&]{bRet = true;});
      }

      return bRet;
    }), STOP(NOP), ELSE, NOP);
    return true;
  };

  auto pipeline_init = [&]
  {
    RESET(descramble_1, descramble_2, descramble_3, descramble_4);
    
    *crc32_checker_1.crc32_check_length = *ht_frame_length;
    *crc32_checker_2.crc32_check_length = *ht_frame_length;
    *crc32_checker_3.crc32_check_length = *ht_frame_length;
    *crc32_checker_4.crc32_check_length = *ht_frame_length;

    symbol_count = pht_symbol_count(*ht_frame_mcs, *ht_frame_length, &VitTotalBits);
    total_symbol_count = symbol_count;

    switch (*ht_frame_mcs)
    {
    case 8:
    case 9:
    case 11:
      *ht_data_vit_12_1.VitTotalBits = VitTotalBits;
      *ht_data_vit_12_1.VitTotalSoftBits = VitTotalBits << 1;
      *ht_data_vit_12_2.VitTotalBits = VitTotalBits;
      *ht_data_vit_12_2.VitTotalSoftBits = VitTotalBits << 1;
      *ht_data_vit_12_3.VitTotalBits = VitTotalBits;
      *ht_data_vit_12_3.VitTotalSoftBits = VitTotalBits << 1;
      *ht_data_vit_12_4.VitTotalBits = VitTotalBits;
      *ht_data_vit_12_4.VitTotalSoftBits = VitTotalBits << 1;
      break;
    case 10:
    case 12:
    case 14:
      *ht_data_vit_34_1.VitTotalBits = VitTotalBits;
      *ht_data_vit_34_1.VitTotalSoftBits = VitTotalBits * 4 / 3;
      *ht_data_vit_34_2.VitTotalBits = VitTotalBits;
      *ht_data_vit_34_2.VitTotalSoftBits = VitTotalBits * 4 / 3;
      *ht_data_vit_34_3.VitTotalBits = VitTotalBits;
      *ht_data_vit_34_3.VitTotalSoftBits = VitTotalBits * 4 / 3;
      *ht_data_vit_34_4.VitTotalBits = VitTotalBits;
      *ht_data_vit_34_4.VitTotalSoftBits = VitTotalBits * 4 / 3;
      break;
    case 13:
      *ht_data_vit_23_1.VitTotalBits = VitTotalBits;
      *ht_data_vit_23_1.VitTotalSoftBits = VitTotalBits * 3 / 2;
      *ht_data_vit_23_2.VitTotalBits = VitTotalBits;
      *ht_data_vit_23_2.VitTotalSoftBits = VitTotalBits * 3 / 2;
      *ht_data_vit_23_3.VitTotalBits = VitTotalBits;
      *ht_data_vit_23_3.VitTotalSoftBits = VitTotalBits * 3 / 2;
      *ht_data_vit_23_4.VitTotalBits = VitTotalBits;
      *ht_data_vit_23_4.VitTotalSoftBits = VitTotalBits * 3 / 2;
      break;
    default:
      break;
    }

    printf("HT: MCS=%d, Length=%d, SymbolCount=%d\n", *ht_frame_mcs, *ht_frame_length, total_symbol_count);
  };

  auto rx_vit12_pipeline_1 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_12_1, descramble_1, crc32_checker_1, STOP([&]{bFinish = true;}));
  };

  auto rx_vit12_pipeline_2 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_12_2, descramble_2, crc32_checker_2, STOP([&]{bFinish = true;}));
  };

  auto rx_vit12_pipeline_3 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_12_3, descramble_3, crc32_checker_3, STOP([&]{bFinish = true;}));
  };

  auto rx_vit12_pipeline_4 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_12_4, descramble_4, crc32_checker_4, STOP([&]{bFinish = true;}));
  };

  auto rx_vit23_pipeline_1 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_23_1, descramble_1, crc32_checker_1, STOP([&]{bFinish = true;}));
  };

  auto rx_vit23_pipeline_2 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_23_2, descramble_2, crc32_checker_2, STOP([&]{bFinish = true;}));
  };

  auto rx_vit23_pipeline_3 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_23_3, descramble_3, crc32_checker_3, STOP([&]{bFinish = true;}));
  };

  auto rx_vit23_pipeline_4 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_23_4, descramble_4, crc32_checker_4, STOP([&]{bFinish = true;}));
  };

  auto rx_vit34_pipeline_1 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_34_1, descramble_1, crc32_checker_1, STOP([&]{bFinish = true;}));
  };

  auto rx_vit34_pipeline_2 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_34_2, descramble_2, crc32_checker_2, STOP([&]{bFinish = true;}));
  };

  auto rx_vit34_pipeline_3 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_34_3, descramble_3, crc32_checker_3, STOP([&]{bFinish = true;}));
  };

  auto rx_vit34_pipeline_4 = [&]
  {
    bool bFinish = false;
    START(WHILE(IsTrue(!bFinish)), ht_data_vit_34_4, descramble_4, crc32_checker_4, STOP([&]{bFinish = true;}));
  };
  //////////////////////////////////////////////////////////////////////////

  auto rx_bpsk_pipeline_1 = [&]() -> bool
  {    
    START(src, wait_ofdm, STOP([&]
    {
#if 0
      ONCE(cfo_comp, remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);

      ONCE(mimo_channel_compensator_1, mimo_channel_compensator_2, mimo_channel_compensator_3, mimo_channel_compensator_4);
      ONCE(pilot_tracking_1, pilot_tracking_2, pilot_tracking_3, pilot_tracking_4);

      ONCE(ht_demap_bpsk1, ht_deinterleave_1bpsc_iss1,
        ht_demap_bpsk2, ht_deinterleave_1bpsc_iss2,
        ht_demap_bpsk3, ht_deinterleave_1bpsc_iss3,
        ht_demap_bpsk4, ht_deinterleave_1bpsc_iss4);
#else
      ONCE(cfo_comp);

      PARALLEL([&]{
        ONCE(remove_gi1, fft_data1);
        ONCE(remove_gi2, fft_data2);
      }, [&]{
        ONCE(remove_gi3, fft_data3);
        ONCE(remove_gi4, fft_data4);
      });

      PARALLEL([&]{
        ONCE(mimo_channel_compensator_1, mimo_channel_compensator_2);
        ONCE(pilot_tracking_1, pilot_tracking_2);
        ONCE(ht_demap_bpsk1, ht_deinterleave_1bpsc_iss1,
          ht_demap_bpsk2, ht_deinterleave_1bpsc_iss2);
      }, [&]{
        ONCE(mimo_channel_compensator_3, mimo_channel_compensator_4);
        ONCE(pilot_tracking_3, pilot_tracking_4);
        ONCE(ht_demap_bpsk3, ht_deinterleave_1bpsc_iss3,
          ht_demap_bpsk4, ht_deinterleave_1bpsc_iss4);
      });
#endif
      mimo_channel_compensator_1.fence();
    }));
    
    symbol_count--;
    return symbol_count > 0;
  };

  auto rx_qpsk_pipeline_1 = [&]() -> bool
  {
    //printf("symbol - %d\n", symbol_count);

    START(src, wait_ofdm, STOP([&]
    {
#if 0
      ONCE(cfo_comp, remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(mimo_channel_compensator_1, mimo_channel_compensator_2, mimo_channel_compensator_3, mimo_channel_compensator_4);
      ONCE(pilot_tracking_1, pilot_tracking_2, pilot_tracking_3, pilot_tracking_4);

      ONCE(ht_demap_qpsk1, ht_deinterleave_2bpsc_iss1,
        ht_demap_qpsk2, ht_deinterleave_2bpsc_iss2,
        ht_demap_qpsk3, ht_deinterleave_2bpsc_iss3,
        ht_demap_qpsk4, ht_deinterleave_2bpsc_iss4);
#else
      ONCE(cfo_comp);

      PARALLEL([&]{
        ONCE(remove_gi1, fft_data1);
        ONCE(remove_gi2, fft_data2);
      }, [&]{
        ONCE(remove_gi3, fft_data3);
        ONCE(remove_gi4, fft_data4);
      });

      PARALLEL([&]{
        ONCE(mimo_channel_compensator_1, mimo_channel_compensator_2);
        ONCE(pilot_tracking_1, pilot_tracking_2);
        ONCE(ht_demap_qpsk1, ht_deinterleave_2bpsc_iss1,
          ht_demap_qpsk2, ht_deinterleave_2bpsc_iss2);
      }, [&]{
        ONCE(mimo_channel_compensator_3, mimo_channel_compensator_4);
        ONCE(pilot_tracking_3, pilot_tracking_4);
        ONCE(ht_demap_qpsk3, ht_deinterleave_2bpsc_iss3,
          ht_demap_qpsk4, ht_deinterleave_2bpsc_iss4);
      });
#endif
      mimo_channel_compensator_1.fence();
    }));

    symbol_count--;
    return symbol_count > 0;
  };

  auto rx_16qam_pipeline_1 = [&]() -> bool
  {
    START(src, wait_ofdm, STOP([&]
    {
#if 0
      ONCE(cfo_comp, remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);

      ONCE(mimo_channel_compensator_1, mimo_channel_compensator_2, mimo_channel_compensator_3, mimo_channel_compensator_4);
      ONCE(pilot_tracking_1, pilot_tracking_2, pilot_tracking_3, pilot_tracking_4);

      ONCE(ht_demap_16qam1, ht_deinterleave_4bpsc_iss1,
        ht_demap_16qam2, ht_deinterleave_4bpsc_iss2,
        ht_demap_16qam3, ht_deinterleave_4bpsc_iss3,
        ht_demap_16qam4, ht_deinterleave_4bpsc_iss4);
#else
      ONCE(cfo_comp);

      PARALLEL([&]{
        ONCE(remove_gi1, fft_data1);
        ONCE(remove_gi2, fft_data2);
      }, [&]{
        ONCE(remove_gi3, fft_data3);
        ONCE(remove_gi4, fft_data4);
      });

      PARALLEL([&]{
        ONCE(mimo_channel_compensator_1, mimo_channel_compensator_2);
        ONCE(pilot_tracking_1, pilot_tracking_2);
        ONCE(ht_demap_16qam1, ht_deinterleave_4bpsc_iss1,
          ht_demap_16qam2, ht_deinterleave_4bpsc_iss2);
      }, [&]{
        ONCE(mimo_channel_compensator_3, mimo_channel_compensator_4);
        ONCE(pilot_tracking_3, pilot_tracking_4);
        ONCE(ht_demap_16qam3, ht_deinterleave_4bpsc_iss3,
          ht_demap_16qam4, ht_deinterleave_4bpsc_iss4);
      });
#endif
      
      mimo_channel_compensator_1.fence();
    }));

    symbol_count--;
    return symbol_count > 0;
  };

  auto rx_64qam_pipeline_1 = [&]() -> bool
  {
    START(src, wait_ofdm, STOP([&]
    {
#if 0
      ONCE(cfo_comp, remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(mimo_channel_compensator_1, mimo_channel_compensator_2, mimo_channel_compensator_3, mimo_channel_compensator_4);
      ONCE(pilot_tracking_1, pilot_tracking_2, pilot_tracking_3, pilot_tracking_4);

      ONCE(ht_demap_64qam1, ht_deinterleave_6bpsc_iss1);
      ONCE(ht_demap_64qam2, ht_deinterleave_6bpsc_iss2);
      ONCE(ht_demap_64qam3, ht_deinterleave_6bpsc_iss3);
      ONCE(ht_demap_64qam4, ht_deinterleave_6bpsc_iss4);
#else
      ONCE(cfo_comp);

      PARALLEL([&]{
        ONCE(remove_gi1, fft_data1);
        ONCE(remove_gi2, fft_data2);
      }, [&]{
        ONCE(remove_gi3, fft_data3);
        ONCE(remove_gi4, fft_data4);
      });
      
      PARALLEL([&]{
        ONCE(mimo_channel_compensator_1, mimo_channel_compensator_2);
        ONCE(pilot_tracking_1, pilot_tracking_2);
        ONCE(ht_demap_64qam1, ht_deinterleave_6bpsc_iss1,
          ht_demap_64qam2, ht_deinterleave_6bpsc_iss2);
      }, [&]{
        ONCE(mimo_channel_compensator_3, mimo_channel_compensator_4);
        ONCE(pilot_tracking_3, pilot_tracking_4);
        ONCE(ht_demap_64qam3, ht_deinterleave_6bpsc_iss3,
          ht_demap_64qam4, ht_deinterleave_6bpsc_iss4);
      });
#endif
      mimo_channel_compensator_1.fence();
    }));

    symbol_count--;
    return symbol_count > 0;
  };
  //////////////////////////////////////////////////////////////////////////
  auto rx_mcs8_pipeline = [&]
  {
    PIPE_LINE(rx_bpsk_pipeline_1, [&]{
      PARALLEL(rx_vit12_pipeline_1, rx_vit12_pipeline_2, rx_vit12_pipeline_3, rx_vit12_pipeline_4);
    });
  };

  auto rx_mcs9_pipeline = [&]
  {
    PIPE_LINE(rx_qpsk_pipeline_1, [&]{
      PARALLEL(rx_vit12_pipeline_1, rx_vit12_pipeline_2, rx_vit12_pipeline_3, rx_vit12_pipeline_4);
    });
  };

  auto rx_mcs10_pipeline = [&]
  {
    PIPE_LINE(rx_qpsk_pipeline_1, [&]{
      PARALLEL(rx_vit34_pipeline_1, rx_vit34_pipeline_2, rx_vit34_pipeline_3, rx_vit34_pipeline_4);
    });
  };

  auto rx_mcs11_pipeline = [&]
  {
    PIPE_LINE(rx_16qam_pipeline_1, [&]{
      PARALLEL(rx_vit12_pipeline_1, rx_vit12_pipeline_2, rx_vit12_pipeline_3, rx_vit12_pipeline_4);
    });
  };

  auto rx_mcs12_pipeline = [&]
  {
    PIPE_LINE(rx_16qam_pipeline_1, [&]{
      PARALLEL(rx_vit34_pipeline_1, rx_vit34_pipeline_2, rx_vit34_pipeline_3, rx_vit34_pipeline_4);
    });
  };

  auto rx_mcs13_pipeline = [&]
  {
    PIPE_LINE(rx_64qam_pipeline_1, [&]{
      PARALLEL(rx_vit23_pipeline_1, rx_vit23_pipeline_2, rx_vit23_pipeline_3, rx_vit23_pipeline_4);
    });
  };

  auto rx_mcs14_pipeline = [&]
  {
    PIPE_LINE(rx_64qam_pipeline_1, [&]{
      PARALLEL(rx_vit34_pipeline_1, rx_vit34_pipeline_2, rx_vit34_pipeline_3, rx_vit34_pipeline_4);
    });
  };

  auto htdata_handler = [&]
  {
    ONCE(pipeline_init);
    t1 = tick_count::now();
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
    t2 = tick_count::now();
    tick_count t = t2 - t1;
    printf("time = %f us, %f MSPS\n", t.us(), total_symbol_count * 80 / t.us());
    printf("frame decode done! %d : %d : %d : %d\n", 
      *crc32_checker_1.crc32_check_result, *crc32_checker_2.crc32_check_result,
      *crc32_checker_3.crc32_check_result, *crc32_checker_4.crc32_check_result);
  };

#if 1
  START(
    WHILE(frame_detection), IF(lltf_handler), IF(lsig_handler), IF(htsig_handler), IF(htstf_handler), IF(htltf_handler), htdata_handler
    );
#else
  profile_viterbi34();
#endif


  printf("rx main terminated...\n");
};