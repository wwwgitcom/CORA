#pragma once

void bigap_4x4_rx(int argc, _TCHAR* argv[])
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
    strFileName1 = CmdArg.as_string();
  }
  CmdArg = cmdline.get("FileName2");
  if ( CmdArg.exist() )
  {
    strFileName2 = CmdArg.as_string();
  }
  CmdArg = cmdline.get("FileName3");
  if ( CmdArg.exist() )
  {
    strFileName3 = CmdArg.as_string();
  }
  CmdArg = cmdline.get("FileName4");
  if ( CmdArg.exist() )
  {
    strFileName4 = CmdArg.as_string();
  }

  autoref src = create_block<b_file_source_v4>(
    5, strFileName1, strFileName2, strFileName3, strFileName4, string("Decimate=1"));

  autoref wait_lltf                  = create_block<b_wait_4v>( 1, string("nwait=40") );
  autoref wait_ofdm                  = create_block<b_wait_4v>( 1, string("nwait=20") );
  autoref axorr                      = create_block<b_auto_corr_4v2>( 1,  string("vHisLength=8") );

  autoref lstf_searcher              = create_block<b_lstf_searcher_2v1>();
  autoref lltf                       = create_block<b_bigap_lltf_rx_4v>( );

  autoref remove_gi1                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );
  autoref remove_gi2                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );
  autoref remove_gi3                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );
  autoref remove_gi4                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );

  autoref fft_data1                  = create_block<b_fft_64_1v1>();
  autoref fft_data2                  = create_block<b_fft_64_1v1>();
  autoref fft_data3                  = create_block<b_fft_64_1v1>();
  autoref fft_data4                  = create_block<b_fft_64_1v1>();

  autoref siso_channel_comp          = create_block<b_bigap_siso_channel_compensator_4v4>();

  autoref siso_mrc_combine           = create_block<b_mrc_combine_4v1>();
  autoref lsig_demap_bpsk_i          = create_block<b_dot11_demap_bpsk_i_1v1>( 2, string("low=-26"), string("high=26") );
  autoref siso_sig_deinterleave      = create_block<b_dot11a_deinterleave_1bpsc_1v1>();
  autoref l_sig_vit                  = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=24"), string("TraceBackOutput=24") );

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
  autoref noise_estimator            = create_block<b_bigap_4x4_noise_estimator_4v>();
  autoref mimo_channel_estimator_zf  = create_block<b_dot11_mimo_channel_estimator_4v>();
  autoref mimo_channel_estimator_mmse= create_block<b_dot11_mimo_channel_estimator_mmse_4v>();
  
  autoref mimo_channel_compensator   = create_block<b_bigap_channel_compensator_4v4>();

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
  autoref ht_deinterleave_1bpsc_iss2 = create_block<b_dot11n_deinterleave_1bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_1bpsc_iss3 = create_block<b_dot11n_deinterleave_1bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_1bpsc_iss4 = create_block<b_dot11n_deinterleave_1bpsc_1v1>( 1, string("iss=1") );

  autoref ht_deinterleave_2bpsc_iss1 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_2bpsc_iss2 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_2bpsc_iss3 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_2bpsc_iss4 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=1") );

  autoref ht_deinterleave_4bpsc_iss1 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_4bpsc_iss2 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_4bpsc_iss3 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_4bpsc_iss4 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=1") );

  autoref ht_deinterleave_6bpsc_iss1 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_6bpsc_iss2 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_6bpsc_iss3 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_6bpsc_iss4 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=1") );

  autoref descramble_1               = create_block<b_dot11_descramble_1v1>();
  autoref descramble_2               = create_block<b_dot11_descramble_1v1>();
  autoref descramble_3               = create_block<b_dot11_descramble_1v1>();
  autoref descramble_4               = create_block<b_dot11_descramble_1v1>();

  autoref crc32_checker_1            = create_block<b_crc32_check_1v>();
  autoref crc32_checker_2            = create_block<b_crc32_check_1v>();
  autoref crc32_checker_3            = create_block<b_crc32_check_1v>();
  autoref crc32_checker_4            = create_block<b_crc32_check_1v>();

  autoref pilot_tracking             = create_block<b_dot11_pilot_tracking_4v>();
  //---------------------------------------------------------
  Channel::Create(sizeof(v_cs))
    .from(src, 0)
    .to(wait_lltf, 0).to(wait_ofdm, 0).to(axorr, 0).to(lltf, 0)
    .to(remove_gi1, 0).to(fft_data1, 0);

  Channel::Create(sizeof(v_cs))
    .from(src, 1)
    .to(wait_lltf, 1).to(wait_ofdm, 1).to(axorr, 1).to(lltf, 1)
    .to(remove_gi2, 0).to(fft_data2, 0);

  Channel::Create(sizeof(v_cs))
    .from(src, 2)
    .to(wait_lltf, 2).to(wait_ofdm, 2).to(axorr, 2).to(lltf, 2)
    .to(remove_gi3, 0).to(fft_data3, 0);

  Channel::Create(sizeof(v_cs))
    .from(src, 3)
    .to(wait_lltf, 3).to(wait_ofdm, 3).to(axorr, 3).to(lltf, 3)
    .to(remove_gi4, 0).to(fft_data4, 0);

  Channel::Create(sizeof(v_q))
    .from(axorr, 0)
    .to(lstf_searcher, 0);

  Channel::Create(sizeof(v_q))
    .from(axorr, 1)
    .to(lstf_searcher, 1);

  //
  Channel::Create(sizeof(v_cs))
    .from(fft_data1, 0)
    .to(siso_channel_comp, 0).to(mimo_channel_estimator_zf, 0).to(mimo_channel_estimator_mmse, 0).to(mimo_channel_compensator, 0);
  Channel::Create(sizeof(v_cs))
    .from(fft_data2, 0)
    .to(siso_channel_comp, 1).to(mimo_channel_estimator_zf, 1).to(mimo_channel_estimator_mmse, 1).to(mimo_channel_compensator, 1);
  Channel::Create(sizeof(v_cs))
    .from(fft_data3, 0)
    .to(siso_channel_comp, 2).to(mimo_channel_estimator_zf, 2).to(mimo_channel_estimator_mmse, 2).to(mimo_channel_compensator, 2);
  Channel::Create(sizeof(v_cs))
    .from(fft_data4, 0)
    .to(siso_channel_comp, 3).to(mimo_channel_estimator_zf, 3).to(mimo_channel_estimator_mmse, 3).to(mimo_channel_compensator, 3);

  //
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 0).to(noise_estimator, 0).to(siso_mrc_combine, 0)
    .from(mimo_channel_compensator, 0).to(ht_demap_bpsk1, 0).to(ht_demap_qpsk1, 0).to(ht_demap_16qam1, 0).to(ht_demap_64qam1, 0).to(pilot_tracking, 0);
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 1).to(noise_estimator, 1).to(siso_mrc_combine, 1)
    .from(mimo_channel_compensator, 1).to(ht_demap_bpsk2, 0).to(ht_demap_qpsk2, 0).to(ht_demap_16qam2, 0).to(ht_demap_64qam2, 0).to(pilot_tracking, 1);
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 2).to(noise_estimator, 2).to(siso_mrc_combine, 2)
    .from(mimo_channel_compensator, 2).to(ht_demap_bpsk3, 0).to(ht_demap_qpsk3, 0).to(ht_demap_16qam3, 0).to(ht_demap_64qam3, 0).to(pilot_tracking, 2);
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 3).to(noise_estimator, 3).to(siso_mrc_combine, 3)
    .from(mimo_channel_compensator, 3).to(ht_demap_bpsk4, 0).to(ht_demap_qpsk4, 0).to(ht_demap_16qam4, 0).to(ht_demap_64qam4, 0).to(pilot_tracking, 3);

  //
  Channel::Create(sizeof(v_cs))
    .from(siso_mrc_combine, 0)
    .to(lsig_demap_bpsk_i, 0);

  Channel::Create(sizeof(uint8))
    .from(lsig_demap_bpsk_i, 0)
    .to(siso_sig_deinterleave, 0);

  Channel::Create(sizeof(uint8))
    .from(siso_sig_deinterleave, 0).to(l_sig_vit, 0);

  Channel::Create(sizeof(uint8))
    .from(l_sig_vit, 0)
    .to(l_sig_parser, 0);

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
  _global_(uint16, l_frame_length);
  _global_(uint32, l_frame_rate);

  bool   lsig_ok_1      = false;
  bool   lsig_ok_2      = false;
  bool   lsig_ok_3      = false;
  bool   lsig_ok_4      = false;
  uint16 frame_length_1 = 0;
  uint16 frame_length_2 = 0;
  uint16 frame_length_3 = 0;
  uint16 frame_length_4 = 0;
  uint32 frame_mcs_1    = 0;
  uint32 frame_mcs_2    = 0;
  uint32 frame_mcs_3    = 0;
  uint32 frame_mcs_4    = 0;

  int VitTotalBits       = 0;
  int state              = 0;
  int max_symbol_count   = 0;
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
    START(src, wait_lltf, lltf, STOP(NOP));
    return true;
  };

  auto lsig_handler = [&]() -> bool
  {
    START(src, wait_ofdm, IF([&]
    {
      *l_sig_vit.VitTotalBits     = 24;
      *l_sig_vit.VitTotalSoftBits = 48;
      *l_sig_ok                   = false;

      ONCE(remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(siso_channel_comp, noise_estimator, siso_mrc_combine, lsig_demap_bpsk_i, siso_sig_deinterleave, l_sig_vit);

      *l_frame_length = 0;
      *l_frame_rate   = 0;
      
      ONCE(l_sig_parser, [&]{
        printf(" lsig%d: %d, length=%d, rate=%d\n", state, *l_sig_ok, *l_frame_length, *l_frame_rate);
        switch (state)
        {
        case 0:
          lsig_ok_1      = *l_sig_ok;
          frame_length_1 = *l_frame_length;
          frame_mcs_1    = *l_frame_rate;
          break;
        case 1:
          lsig_ok_2      = *l_sig_ok;          
          frame_length_2 = *l_frame_length;
          frame_mcs_2    = *l_frame_rate;          
          break;
        case 2:
          lsig_ok_3      = *l_sig_ok;
          frame_length_3 = *l_frame_length;
          frame_mcs_3    = *l_frame_rate;
          break;
        case 3:
          lsig_ok_4      = *l_sig_ok;
          frame_length_4 = *l_frame_length;
          frame_mcs_4    = *l_frame_rate;
          break;
        default:
          break;
        }
      });

      state = (state + 1) % 4;

      return true;
    }), STOP(NOP), ELSE, NOP);
    return true;
  };

  auto pipeline_init = [&]() -> bool
  {
    int symbol_count = 0;

    RESET(descramble_1, descramble_2, descramble_3, descramble_4);
    RESET(ht_data_vit_12_1, ht_data_vit_12_2, ht_data_vit_12_3, ht_data_vit_12_4);
    RESET(ht_data_vit_23_1, ht_data_vit_23_2, ht_data_vit_23_3, ht_data_vit_23_4);
    RESET(ht_data_vit_34_1, ht_data_vit_34_2, ht_data_vit_34_3, ht_data_vit_34_4);

    *crc32_checker_1.crc32_check_length = frame_length_1;
    *crc32_checker_2.crc32_check_length = frame_length_2;
    *crc32_checker_3.crc32_check_length = frame_length_3;
    *crc32_checker_4.crc32_check_length = frame_length_4;

    max_symbol_count = 0;

    // setup 1st stream
    if (lsig_ok_1)
    {
      symbol_count     = pht_symbol_count(frame_mcs_1, frame_length_1, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);

      switch (frame_mcs_1)
      {
      case 8:
      case 9:
      case 11:
        *ht_data_vit_12_1.VitTotalBits     = VitTotalBits;
        *ht_data_vit_12_1.VitTotalSoftBits = VitTotalBits << 1;
        break;
      case 10:
      case 12:
      case 14:
        *ht_data_vit_34_1.VitTotalBits     = VitTotalBits;
        *ht_data_vit_34_1.VitTotalSoftBits = VitTotalBits * 4 / 3;
        break;
      case 13:
        *ht_data_vit_23_1.VitTotalBits     = VitTotalBits;
        *ht_data_vit_23_1.VitTotalSoftBits = VitTotalBits * 3 / 2;
        break;
      default:
        break;
      }
    }

    // setup 2nd stream
    if (lsig_ok_2)
    {
      symbol_count     = pht_symbol_count(frame_mcs_2, frame_length_2, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);

      switch (frame_mcs_2)
      {
      case 8:
      case 9:
      case 11:
        *ht_data_vit_12_2.VitTotalBits     = VitTotalBits;
        *ht_data_vit_12_2.VitTotalSoftBits = VitTotalBits << 1;
        break;
      case 10:
      case 12:
      case 14:
        *ht_data_vit_34_2.VitTotalBits     = VitTotalBits;
        *ht_data_vit_34_2.VitTotalSoftBits = VitTotalBits * 4 / 3;
        break;
      case 13:
        *ht_data_vit_23_2.VitTotalBits     = VitTotalBits;
        *ht_data_vit_23_2.VitTotalSoftBits = VitTotalBits * 3 / 2;
        break;
      default:
        break;
      }
    }

    // setup 3rd stream
    if (lsig_ok_3)
    {
      symbol_count     = pht_symbol_count(frame_mcs_3, frame_length_3, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);

      switch (frame_mcs_3)
      {
      case 8:
      case 9:
      case 11:
        *ht_data_vit_12_3.VitTotalBits     = VitTotalBits;
        *ht_data_vit_12_3.VitTotalSoftBits = VitTotalBits << 1;
        break;
      case 10:
      case 12:
      case 14:
        *ht_data_vit_34_3.VitTotalBits     = VitTotalBits;
        *ht_data_vit_34_3.VitTotalSoftBits = VitTotalBits * 4 / 3;
        break;
      case 13:
        *ht_data_vit_23_3.VitTotalBits     = VitTotalBits;
        *ht_data_vit_23_3.VitTotalSoftBits = VitTotalBits * 3 / 2;
        break;
      default:
        break;
      }
    }
    
    // setup 4th stream
    if (lsig_ok_4)
    {
      symbol_count     = pht_symbol_count(frame_mcs_4, frame_length_4, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);

      switch (frame_mcs_4)
      {
      case 8:
      case 9:
      case 11:
        *ht_data_vit_12_4.VitTotalBits     = VitTotalBits;
        *ht_data_vit_12_4.VitTotalSoftBits = VitTotalBits << 1;
        break;
      case 10:
      case 12:
      case 14:
        *ht_data_vit_34_4.VitTotalBits     = VitTotalBits;
        *ht_data_vit_34_4.VitTotalSoftBits = VitTotalBits * 4 / 3;
        break;
      case 13:
        *ht_data_vit_23_4.VitTotalBits     = VitTotalBits;
        *ht_data_vit_23_4.VitTotalSoftBits = VitTotalBits * 3 / 2;
        break;
      default:
        break;
      }
    }

    total_symbol_count = max_symbol_count;

    printf("DATA: MCS1=%d, Length1=%d, MCS2=%d, Length2=%d, "
      "MCS3=%d, Length3=%d, MCS4=%d, Length4=%d, SymbolCount=%d\n", 
      frame_mcs_1, frame_length_1, frame_mcs_2, frame_length_2, 
      frame_mcs_3, frame_length_3, frame_mcs_4, frame_length_4, total_symbol_count);

    return max_symbol_count > 0;
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
    START(WHILE(IsTrue(true)), ht_data_vit_34_4, descramble_4, crc32_checker_4, STOP(NOP));
  };
  //////////////////////////////////////////////////////////////////////////

  auto rx_bpsk_pipeline_1 = [&]() -> bool
  {    
    START(src, wait_ofdm, STOP([&]
    {
      ONCE(remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_bpsk1, ht_deinterleave_1bpsc_iss1,
        ht_demap_bpsk2, ht_deinterleave_1bpsc_iss2,
        ht_demap_bpsk3, ht_deinterleave_1bpsc_iss3,
        ht_demap_bpsk4, ht_deinterleave_1bpsc_iss4);
    }));

    max_symbol_count--;
    return max_symbol_count > 0;
  };

  auto rx_qpsk_pipeline_1 = [&]() -> bool
  {
    //printf("symbol - %d\n", symbol_count);

    START(src, wait_ofdm, STOP([&]
    {
      ONCE(remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_qpsk1, ht_deinterleave_2bpsc_iss1,
        ht_demap_qpsk2, ht_deinterleave_2bpsc_iss2,
        ht_demap_qpsk3, ht_deinterleave_2bpsc_iss3,
        ht_demap_qpsk4, ht_deinterleave_2bpsc_iss4);
    }));

    max_symbol_count--;
    return max_symbol_count > 0;
  };

  auto rx_16qam_pipeline_1 = [&]() -> bool
  {
    START(src, wait_ofdm, STOP([&]
    {
      ONCE(remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_16qam1, ht_deinterleave_4bpsc_iss1,
        ht_demap_16qam2, ht_deinterleave_4bpsc_iss2,
        ht_demap_16qam3, ht_deinterleave_4bpsc_iss3,
        ht_demap_16qam4, ht_deinterleave_4bpsc_iss4);
    }));

    max_symbol_count--;
    return max_symbol_count > 0;
  };

  auto rx_64qam_pipeline_1 = [&]() -> bool
  {
    START(src, wait_ofdm, STOP([&]
    {
#if 0
      ONCE(remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_64qam1, ht_deinterleave_6bpsc_iss1);
      ONCE(ht_demap_64qam2, ht_deinterleave_6bpsc_iss2);
      ONCE(ht_demap_64qam3, ht_deinterleave_6bpsc_iss3);
      ONCE(ht_demap_64qam4, ht_deinterleave_6bpsc_iss4);
#else
      ONCE([&]{
        ONCE(remove_gi1, fft_data1);
        ONCE(remove_gi2, fft_data2);
      }, [&]{
        ONCE(remove_gi3, fft_data3);
        ONCE(remove_gi4, fft_data4);
      });
      
      ONCE(mimo_channel_compensator, pilot_tracking);
#if 1
      ONCE([&]{
        ONCE(ht_demap_64qam1, ht_deinterleave_6bpsc_iss1,
          ht_demap_64qam2, ht_deinterleave_6bpsc_iss2);
      }, [&]{
        ONCE(ht_demap_64qam3, ht_deinterleave_6bpsc_iss3,
          ht_demap_64qam4, ht_deinterleave_6bpsc_iss4);
      });
#else
      ONCE(ht_demap_64qam3, ht_deinterleave_6bpsc_iss3);
#endif
#endif
    }));

    max_symbol_count--;
    return max_symbol_count > 0;
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
      //PARALLEL(rx_vit34_pipeline_3);
    });
  };

  auto htdata_handler = [&]
  {
    uint32 frame_mcs;
    if (lsig_ok_1)
    {
      frame_mcs = frame_mcs_1;
    }
    else if (lsig_ok_2)
    {
      frame_mcs = frame_mcs_2;
    }
    else if (lsig_ok_3)
    {
      frame_mcs = frame_mcs_3;
    }
    else if (lsig_ok_4)
    {
      frame_mcs = frame_mcs_4;
    }
    else
    {
      printf("error: none l-sig is right! abort decoding...\n");
      return;
    }

    t1 = tick_count::now();
    START(
      IF(IsTrue(frame_mcs == 8)),  rx_mcs8_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 9)),  rx_mcs9_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 10)), rx_mcs10_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 11)), rx_mcs11_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 12)), rx_mcs12_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 13)), rx_mcs13_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 14)), rx_mcs14_pipeline,
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
    WHILE(frame_detection), 
    IF(lltf_handler), IF(lsig_handler), 
    IF(lltf_handler), IF(lsig_handler), 
    IF(lltf_handler), IF(lsig_handler), 
    IF(lltf_handler), IF(lsig_handler), 
    IF(pipeline_init), htdata_handler
    );
#else
  profile_viterbi34();
#endif


  printf("rx main terminated...\n");
};




//////////////////////////////////////////////////////////////////////////


void bigap_4x4_rx_front_end(int argc, _TCHAR* argv[])
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
    strFileName1 = CmdArg.as_string();
  }
  CmdArg = cmdline.get("FileName2");
  if ( CmdArg.exist() )
  {
    strFileName2 = CmdArg.as_string();
  }
  CmdArg = cmdline.get("FileName3");
  if ( CmdArg.exist() )
  {
    strFileName3 = CmdArg.as_string();
  }
  CmdArg = cmdline.get("FileName4");
  if ( CmdArg.exist() )
  {
    strFileName4 = CmdArg.as_string();
  }
  string backend_ip = string("ip=127.0.0.1");
  CmdArg = cmdline.get("ip");
  if ( CmdArg.exist() )
  {
    backend_ip = CmdArg.as_string();
  }

  string backend_port = string("port=99999");
  CmdArg = cmdline.get("port");
  if ( CmdArg.exist() )
  {
    backend_port = CmdArg.as_string();
  }

  autoref src = create_block<b_file_source_v4>(
    5, strFileName1, strFileName2, strFileName3, strFileName4, string("Decimate=1"));

  autoref wait_lltf                  = create_block<b_wait_4v>( 1, string("nwait=40") );
  autoref wait_ofdm                  = create_block<b_wait_4v>( 1, string("nwait=20") );
  autoref axorr                      = create_block<b_auto_corr_4v2>( 1,  string("vHisLength=8") );

  autoref lstf_searcher              = create_block<b_lstf_searcher_2v1>();
  autoref lltf                       = create_block<b_bigap_lltf_rx_4v>( );

  autoref remove_gi1                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );
  autoref remove_gi2                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );
  autoref remove_gi3                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );
  autoref remove_gi4                 = create_block<b_remove_gi_1v>( 2, string("GILength=4"), string("SymbolLength=16") );

  autoref fft_data1                  = create_block<b_fft_64_1v1>();
  autoref fft_data2                  = create_block<b_fft_64_1v1>();
  autoref fft_data3                  = create_block<b_fft_64_1v1>();
  autoref fft_data4                  = create_block<b_fft_64_1v1>();

  autoref siso_channel_comp          = create_block<b_bigap_siso_channel_compensator_4v4>();

  autoref siso_mrc_combine           = create_block<b_mrc_combine_4v1>();
  autoref lsig_demap_bpsk_i          = create_block<b_dot11_demap_bpsk_i_1v1>( 2, string("low=-26"), string("high=26") );
  autoref siso_sig_deinterleave      = create_block<b_dot11a_deinterleave_1bpsc_1v1>();
  autoref l_sig_vit                  = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=24"), string("TraceBackOutput=24") );


  autoref l_sig_parser               = create_block<b_lsig_parser_1v>();  
  autoref noise_estimator            = create_block<b_bigap_4x4_noise_estimator_4v>();
  autoref mimo_channel_estimator_zf  = create_block<b_dot11_mimo_channel_estimator_4v>();
  autoref mimo_channel_estimator_mmse= create_block<b_dot11_mimo_channel_estimator_mmse_4v>();

  autoref socket_sink                = create_block<b_bigap_sink_4v>(2, backend_ip, backend_port);
  //---------------------------------------------------------
  Channel::Create(sizeof(v_cs))
    .from(src, 0)
    .to(wait_lltf, 0).to(wait_ofdm, 0).to(axorr, 0).to(lltf, 0)
    .to(remove_gi1, 0).to(fft_data1, 0);

  Channel::Create(sizeof(v_cs))
    .from(src, 1)
    .to(wait_lltf, 1).to(wait_ofdm, 1).to(axorr, 1).to(lltf, 1)
    .to(remove_gi2, 0).to(fft_data2, 0);

  Channel::Create(sizeof(v_cs))
    .from(src, 2)
    .to(wait_lltf, 2).to(wait_ofdm, 2).to(axorr, 2).to(lltf, 2)
    .to(remove_gi3, 0).to(fft_data3, 0);

  Channel::Create(sizeof(v_cs))
    .from(src, 3)
    .to(wait_lltf, 3).to(wait_ofdm, 3).to(axorr, 3).to(lltf, 3)
    .to(remove_gi4, 0).to(fft_data4, 0);

  Channel::Create(sizeof(v_q))
    .from(axorr, 0)
    .to(lstf_searcher, 0);

  Channel::Create(sizeof(v_q))
    .from(axorr, 1)
    .to(lstf_searcher, 1);

  //
  Channel::Create(sizeof(v_cs))
    .from(fft_data1, 0)
    .to(socket_sink, 0).to(siso_channel_comp, 0);
  Channel::Create(sizeof(v_cs))
    .from(fft_data2, 0)
    .to(socket_sink, 1).to(siso_channel_comp, 1);
  Channel::Create(sizeof(v_cs))
    .from(fft_data3, 0)
    .to(socket_sink, 2).to(siso_channel_comp, 2);
  Channel::Create(sizeof(v_cs))
    .from(fft_data4, 0)
    .to(socket_sink, 3).to(siso_channel_comp, 3);

  //
  //
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 0).to(noise_estimator, 0).to(siso_mrc_combine, 0);
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 1).to(noise_estimator, 1).to(siso_mrc_combine, 1);
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 2).to(noise_estimator, 2).to(siso_mrc_combine, 2);
  Channel::Create(sizeof(v_cs))
    .from(siso_channel_comp, 3).to(noise_estimator, 3).to(siso_mrc_combine, 3);

  //
  Channel::Create(sizeof(v_cs))
    .from(siso_mrc_combine, 0)
    .to(lsig_demap_bpsk_i, 0);

  Channel::Create(sizeof(uint8))
    .from(lsig_demap_bpsk_i, 0)
    .to(siso_sig_deinterleave, 0);

  Channel::Create(sizeof(uint8))
    .from(siso_sig_deinterleave, 0).to(l_sig_vit, 0);

  Channel::Create(sizeof(uint8))
    .from(l_sig_vit, 0)
    .to(l_sig_parser, 0);
  //---------------------------------------------------------
  // var used by 1st block
  v_align(64)
  _global_(bool, l_sig_ok);
  _global_(uint16, l_frame_length);
  _global_(uint32, l_frame_rate);
  _global_(MIMO_4x4_H, bigap_4x4_H);

  bigap_config_msg config_msg;

  int state              = 0;
  int max_symbol_count   = 0;

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
    START(src, wait_lltf, lltf, STOP(NOP));
    return true;
  };

  auto lsig_handler = [&]() -> bool
  {
    START(src, wait_ofdm, IF([&]
    {
      *l_sig_vit.VitTotalBits     = 24;
      *l_sig_vit.VitTotalSoftBits = 48;
      *l_sig_ok                   = false;

      ONCE(remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(siso_channel_comp, noise_estimator, siso_mrc_combine, lsig_demap_bpsk_i, siso_sig_deinterleave, l_sig_vit);

      *l_frame_length = 0;
      *l_frame_rate   = 0;

      ONCE(l_sig_parser, [&]{
        printf(" lsig%d: %d, length=%d, rate=%d\n", state, *l_sig_ok, *l_frame_length, *l_frame_rate);
        switch (state)
        {
        case 0:
          config_msg.msg.frame1_ok     = *l_sig_ok;
          config_msg.msg.frame1_length = *l_frame_length;
          config_msg.msg.frame1_rate   = *l_frame_rate;
          break;
        case 1:
          config_msg.msg.frame2_ok     = *l_sig_ok;
          config_msg.msg.frame2_length = *l_frame_length;
          config_msg.msg.frame2_rate   = *l_frame_rate;
          break;
        case 2:
          config_msg.msg.frame3_ok     = *l_sig_ok;
          config_msg.msg.frame3_length = *l_frame_length;
          config_msg.msg.frame3_rate   = *l_frame_rate;
          break;
        case 3:
          config_msg.msg.frame4_ok     = *l_sig_ok;
          config_msg.msg.frame4_length = *l_frame_length;
          config_msg.msg.frame4_rate   = *l_frame_rate;
          break;
        default:
          break;
        }
      });

      state = (state + 1) % 4;

      return true;
    }), STOP(NOP), ELSE, NOP);
    return true;
  };

  auto pipeline_init = [&]() -> bool
  {
    int symbol_count = 0;
    int VitTotalBits = 0;

    max_symbol_count = 0;

    // setup 1st stream
    if (config_msg.msg.frame1_ok)
    {
      symbol_count     = pht_symbol_count(config_msg.msg.frame1_rate, config_msg.msg.frame1_length, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);
    }

    // setup 2nd stream
    if (config_msg.msg.frame2_ok)
    {
      symbol_count     = pht_symbol_count(config_msg.msg.frame2_rate, config_msg.msg.frame2_length, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);
    }

    // setup 3rd stream
    if (config_msg.msg.frame3_ok)
    {
      symbol_count     = pht_symbol_count(config_msg.msg.frame3_rate, config_msg.msg.frame3_length, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);
    }

    // setup 4th stream
    if (config_msg.msg.frame4_ok)
    {
      symbol_count     = pht_symbol_count(config_msg.msg.frame4_rate, config_msg.msg.frame4_length, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);
    }
    
    printf("DATA: MCS1=%d, Length1=%d, MCS2=%d, Length2=%d, "
      "MCS3=%d, Length3=%d, MCS4=%d, Length4=%d, SymbolCount=%d\n", 
      config_msg.msg.frame1_rate, config_msg.msg.frame1_length, config_msg.msg.frame2_rate, config_msg.msg.frame2_length, 
      config_msg.msg.frame3_rate, config_msg.msg.frame3_length, config_msg.msg.frame4_rate, config_msg.msg.frame4_length, max_symbol_count);

    if ( max_symbol_count > 0 )
    {
      autoref ch = *bigap_4x4_H;
      memcpy(&config_msg.msg.channel[0], &ch[0], 4 * 64 * sizeof(v_cs));

#if 0
      complex16 (*pc)[256] = (complex16 (*)[256])config_msg.msg.channel;

      for (int i = 0; i < 4; i++)
      {
        printf("%d:", i);
        for (int j = 0; j < 256; j++)
        {
          printf("%d, %d \t %d, %d\n", 
            pc[i][j].re, pc[i][j].im,
            ch[i][j].re, ch[i][j].im);
        }
      }
#endif
      
      socket_sink.SendData((uint8*)&config_msg, sizeof(config_msg));
      return true;
    }
    return false;
  };

  //////////////////////////////////////////////////////////////////////////

  auto rx_bpsk_pipeline_1 = [&]() -> bool
  {    
    START(src, wait_ofdm, STOP([&]
    {
      ONCE(remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(socket_sink);
    }));

    max_symbol_count--;

    if (max_symbol_count <= 0)
    {
      printf("Press ENTRE...\n");
      getchar();
    }

    return max_symbol_count > 0;
  };

  auto rx_qpsk_pipeline_1 = [&]() -> bool
  {
    //printf("symbol - %d\n", symbol_count);

    START(src, wait_ofdm, STOP([&]
    {
      ONCE(remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(socket_sink);
    }));

    max_symbol_count--;
    return max_symbol_count > 0;
  };

  auto rx_16qam_pipeline_1 = [&]() -> bool
  {
    START(src, wait_ofdm, STOP([&]
    {
      ONCE(remove_gi1, fft_data1);
      ONCE(remove_gi2, fft_data2);
      ONCE(remove_gi3, fft_data3);
      ONCE(remove_gi4, fft_data4);
      ONCE(socket_sink);
    }));

    max_symbol_count--;
    return max_symbol_count > 0;
  };

  auto rx_64qam_pipeline_1 = [&]() -> bool
  {
    START(src, wait_ofdm, STOP([&]
    {
      ONCE([&]{
        ONCE(remove_gi1, fft_data1);
        ONCE(remove_gi2, fft_data2);
      }, [&]{
        ONCE(remove_gi3, fft_data3);
        ONCE(remove_gi4, fft_data4);
      });

      ONCE(socket_sink);
    }));

    max_symbol_count--;
    return max_symbol_count > 0;
  };
  //////////////////////////////////////////////////////////////////////////
  auto htdata_handler = [&]
  {
    uint32 frame_mcs;
    if (config_msg.msg.frame1_ok)
    {
      frame_mcs = config_msg.msg.frame1_rate;
    }
    else if (config_msg.msg.frame2_ok)
    {
      frame_mcs = config_msg.msg.frame2_rate;
    }
    else if (config_msg.msg.frame3_ok)
    {
      frame_mcs = config_msg.msg.frame3_rate;
    }
    else if (config_msg.msg.frame4_ok)
    {
      frame_mcs = config_msg.msg.frame4_rate;
    }
    else
    {
      printf("error: none l-sig is right! abort decoding...\n");
      return;
    }

    START(
      IF(IsTrue(frame_mcs == 8)),  WHILE(rx_bpsk_pipeline_1),
      ELSE_IF(IsTrue(frame_mcs == 9  || frame_mcs == 10)),  WHILE(rx_qpsk_pipeline_1),
      ELSE_IF(IsTrue(frame_mcs == 11 || frame_mcs == 12)), WHILE(rx_16qam_pipeline_1),
      ELSE_IF(IsTrue(frame_mcs == 13 || frame_mcs == 14)), WHILE(rx_64qam_pipeline_1),
      ELSE, NOP
      );
  };

  START(
    WHILE(frame_detection), 
    IF(lltf_handler), IF(lsig_handler), 
    IF(lltf_handler), IF(lsig_handler), 
    IF(lltf_handler), IF(lsig_handler), 
    IF(lltf_handler), IF(lsig_handler), 
    IF(pipeline_init), htdata_handler
    );
};


//////////////////////////////////////////////////////////////////////////

void bigap_4x4_rx_back_end(int argc, _TCHAR* argv[])
{
  dsp_cmd cmdline;
  cmdline.parse(argc, argv);
  
  string backend_ip = string("ip=127.0.0.1");
  auto CmdArg = cmdline.get("ip");
  if ( CmdArg.exist() )
  {
    backend_ip = CmdArg.as_string();
  }

  string backend_port = string("port=99999");
  CmdArg = cmdline.get("port");
  if ( CmdArg.exist() )
  {
    backend_port = CmdArg.as_string();
  }

  autoref src = create_block<b_bigap_source_v4>(1, backend_port);

  autoref wait_ofdm                  = create_block<b_wait_4v>( 1, string("nwait=16") );
  
  autoref ht_data_vit_12_1           = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=48"), string("TraceBackOutput=96") );
  autoref ht_data_vit_12_2           = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=48"), string("TraceBackOutput=96") );
  autoref ht_data_vit_12_3           = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=48"), string("TraceBackOutput=96") );
  autoref ht_data_vit_12_4           = create_block<b_viterbi64_1o2_1v1>( 2, string("TraceBackLength=48"), string("TraceBackOutput=96") );

  autoref ht_data_vit_23_1           = create_block<b_viterbi64_2o3_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192") );
  autoref ht_data_vit_23_2           = create_block<b_viterbi64_2o3_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192") );
  autoref ht_data_vit_23_3           = create_block<b_viterbi64_2o3_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192") );
  autoref ht_data_vit_23_4           = create_block<b_viterbi64_2o3_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192") );

  autoref ht_data_vit_34_1           = create_block<b_viterbi64_3o4_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192"));
  autoref ht_data_vit_34_2           = create_block<b_viterbi64_3o4_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192"));
  autoref ht_data_vit_34_3           = create_block<b_viterbi64_3o4_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192"));
  autoref ht_data_vit_34_4           = create_block<b_viterbi64_3o4_1v1>( 2, string("TraceBackLength=36"), string("TraceBackOutput=192"));

  autoref mimo_channel_compensator   = create_block<b_bigap_channel_compensator_4v4>();

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
  autoref ht_deinterleave_1bpsc_iss2 = create_block<b_dot11n_deinterleave_1bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_1bpsc_iss3 = create_block<b_dot11n_deinterleave_1bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_1bpsc_iss4 = create_block<b_dot11n_deinterleave_1bpsc_1v1>( 1, string("iss=1") );

  autoref ht_deinterleave_2bpsc_iss1 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_2bpsc_iss2 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_2bpsc_iss3 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_2bpsc_iss4 = create_block<b_dot11n_deinterleave_2bpsc_1v1>( 1, string("iss=1") );

  autoref ht_deinterleave_4bpsc_iss1 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_4bpsc_iss2 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_4bpsc_iss3 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_4bpsc_iss4 = create_block<b_dot11n_deinterleave_4bpsc_1v1>( 1, string("iss=1") );

  autoref ht_deinterleave_6bpsc_iss1 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_6bpsc_iss2 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_6bpsc_iss3 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=1") );
  autoref ht_deinterleave_6bpsc_iss4 = create_block<b_dot11n_deinterleave_6bpsc_1v1>( 1, string("iss=1") );

  autoref descramble_1               = create_block<b_dot11_descramble_1v1>();
  autoref descramble_2               = create_block<b_dot11_descramble_1v1>();
  autoref descramble_3               = create_block<b_dot11_descramble_1v1>();
  autoref descramble_4               = create_block<b_dot11_descramble_1v1>();

  autoref crc32_checker_1            = create_block<b_crc32_check_1v>();
  autoref crc32_checker_2            = create_block<b_crc32_check_1v>();
  autoref crc32_checker_3            = create_block<b_crc32_check_1v>();
  autoref crc32_checker_4            = create_block<b_crc32_check_1v>();

  autoref pilot_tracking             = create_block<b_dot11_pilot_tracking_4v>();
  //---------------------------------------------------------
  Channel::Create(sizeof(v_cs))
    .from(src, 0).to(wait_ofdm, 0).to(mimo_channel_compensator, 0);

  Channel::Create(sizeof(v_cs))
    .from(src, 1).to(wait_ofdm, 0).to(mimo_channel_compensator, 1);

  Channel::Create(sizeof(v_cs))
    .from(src, 2).to(wait_ofdm, 0).to(mimo_channel_compensator, 2);

  Channel::Create(sizeof(v_cs))
    .from(src, 3).to(wait_ofdm, 0).to(mimo_channel_compensator, 3);

  //
  Channel::Create(sizeof(v_cs))
    .from(mimo_channel_compensator, 0).to(ht_demap_bpsk1, 0).to(ht_demap_qpsk1, 0).to(ht_demap_16qam1, 0).to(ht_demap_64qam1, 0).to(pilot_tracking, 0);
  Channel::Create(sizeof(v_cs))
    .from(mimo_channel_compensator, 1).to(ht_demap_bpsk2, 0).to(ht_demap_qpsk2, 0).to(ht_demap_16qam2, 0).to(ht_demap_64qam2, 0).to(pilot_tracking, 1);
  Channel::Create(sizeof(v_cs))
    .from(mimo_channel_compensator, 2).to(ht_demap_bpsk3, 0).to(ht_demap_qpsk3, 0).to(ht_demap_16qam3, 0).to(ht_demap_64qam3, 0).to(pilot_tracking, 2);
  Channel::Create(sizeof(v_cs))
    .from(mimo_channel_compensator, 3).to(ht_demap_bpsk4, 0).to(ht_demap_qpsk4, 0).to(ht_demap_16qam4, 0).to(ht_demap_64qam4, 0).to(pilot_tracking, 3);

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
  _global_(bigap_config_msg, config_msg);

  bool   lsig_ok_1      = false;
  bool   lsig_ok_2      = false;
  bool   lsig_ok_3      = false;
  bool   lsig_ok_4      = false;
  uint16 frame_length_1 = 0;
  uint16 frame_length_2 = 0;
  uint16 frame_length_3 = 0;
  uint16 frame_length_4 = 0;
  uint32 frame_mcs_1    = 0;
  uint32 frame_mcs_2    = 0;
  uint32 frame_mcs_3    = 0;
  uint32 frame_mcs_4    = 0;

  int VitTotalBits      = 0;
  int max_symbol_count  = 0;
  int total_symbol_count= 0;
  tick_count t1, t2, t3;

  // var used by 2nd block
  //v_align(64)
  //////////////////////////////////////////////////////////////////////////
  

  auto pipeline_init = [&]() -> bool
  {
    int symbol_count = 0;

    RESET(descramble_1, descramble_2, descramble_3, descramble_4);
    RESET(ht_data_vit_12_1, ht_data_vit_12_2, ht_data_vit_12_3, ht_data_vit_12_4);
    RESET(ht_data_vit_23_1, ht_data_vit_23_2, ht_data_vit_23_3, ht_data_vit_23_4);
    RESET(ht_data_vit_34_1, ht_data_vit_34_2, ht_data_vit_34_3, ht_data_vit_34_4);

    max_symbol_count = 0;

    // setup 1st stream
    if ((*config_msg).msg.frame1_ok)
    {
      symbol_count     = pht_symbol_count((*config_msg).msg.frame1_rate, (*config_msg).msg.frame1_length, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);
      *crc32_checker_1.crc32_check_length = (*config_msg).msg.frame1_length;

      switch ((*config_msg).msg.frame1_rate)
      {
      case 8:
      case 9:
      case 11:
        *ht_data_vit_12_1.VitTotalBits     = VitTotalBits;
        *ht_data_vit_12_1.VitTotalSoftBits = VitTotalBits << 1;
        break;
      case 10:
      case 12:
      case 14:
        *ht_data_vit_34_1.VitTotalBits     = VitTotalBits;
        *ht_data_vit_34_1.VitTotalSoftBits = VitTotalBits * 4 / 3;
        break;
      case 13:
        *ht_data_vit_23_1.VitTotalBits     = VitTotalBits;
        *ht_data_vit_23_1.VitTotalSoftBits = VitTotalBits * 3 / 2;
        break;
      default:
        break;
      }
    }

    // setup 2nd stream
    if ((*config_msg).msg.frame2_ok)
    {
      symbol_count     = pht_symbol_count((*config_msg).msg.frame2_rate, (*config_msg).msg.frame2_length, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);
      *crc32_checker_2.crc32_check_length = (*config_msg).msg.frame2_length;

      switch ((*config_msg).msg.frame2_rate)
      {
      case 8:
      case 9:
      case 11:
        *ht_data_vit_12_2.VitTotalBits     = VitTotalBits;
        *ht_data_vit_12_2.VitTotalSoftBits = VitTotalBits << 1;
        break;
      case 10:
      case 12:
      case 14:
        *ht_data_vit_34_2.VitTotalBits     = VitTotalBits;
        *ht_data_vit_34_2.VitTotalSoftBits = VitTotalBits * 4 / 3;
        break;
      case 13:
        *ht_data_vit_23_2.VitTotalBits     = VitTotalBits;
        *ht_data_vit_23_2.VitTotalSoftBits = VitTotalBits * 3 / 2;
        break;
      default:
        break;
      }
    }

    // setup 3rd stream
    if ((*config_msg).msg.frame3_ok)
    {
      symbol_count     = pht_symbol_count((*config_msg).msg.frame3_rate, (*config_msg).msg.frame3_length, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);
      *crc32_checker_3.crc32_check_length = (*config_msg).msg.frame3_length;

      switch ((*config_msg).msg.frame3_rate)
      {
      case 8:
      case 9:
      case 11:
        *ht_data_vit_12_3.VitTotalBits     = VitTotalBits;
        *ht_data_vit_12_3.VitTotalSoftBits = VitTotalBits << 1;
        break;
      case 10:
      case 12:
      case 14:
        *ht_data_vit_34_3.VitTotalBits     = VitTotalBits;
        *ht_data_vit_34_3.VitTotalSoftBits = VitTotalBits * 4 / 3;
        break;
      case 13:
        *ht_data_vit_23_3.VitTotalBits     = VitTotalBits;
        *ht_data_vit_23_3.VitTotalSoftBits = VitTotalBits * 3 / 2;
        break;
      default:
        break;
      }
    }

    // setup 4th stream
    if ((*config_msg).msg.frame4_ok)
    {
      symbol_count     = pht_symbol_count((*config_msg).msg.frame4_rate, (*config_msg).msg.frame4_length, &VitTotalBits);
      max_symbol_count = max(symbol_count, max_symbol_count);
      *crc32_checker_4.crc32_check_length = (*config_msg).msg.frame4_length;

      switch ((*config_msg).msg.frame4_rate)
      {
      case 8:
      case 9:
      case 11:
        *ht_data_vit_12_4.VitTotalBits     = VitTotalBits;
        *ht_data_vit_12_4.VitTotalSoftBits = VitTotalBits << 1;
        break;
      case 10:
      case 12:
      case 14:
        *ht_data_vit_34_4.VitTotalBits     = VitTotalBits;
        *ht_data_vit_34_4.VitTotalSoftBits = VitTotalBits * 4 / 3;
        break;
      case 13:
        *ht_data_vit_23_4.VitTotalBits     = VitTotalBits;
        *ht_data_vit_23_4.VitTotalSoftBits = VitTotalBits * 3 / 2;
        break;
      default:
        break;
      }
    }

    total_symbol_count = max_symbol_count;

    printf("DATA: MCS1=%d, Length1=%d, MCS2=%d, Length2=%d, "
      "MCS3=%d, Length3=%d, MCS4=%d, Length4=%d, SymbolCount=%d\n", 
      (*config_msg).msg.frame1_rate, (*config_msg).msg.frame1_length, (*config_msg).msg.frame2_rate, (*config_msg).msg.frame2_length, 
      (*config_msg).msg.frame3_rate, (*config_msg).msg.frame3_length, (*config_msg).msg.frame4_rate, (*config_msg).msg.frame4_length, max_symbol_count);

    return max_symbol_count > 0;
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
    START(WHILE(IsTrue(true)), ht_data_vit_34_4, descramble_4, crc32_checker_4, STOP(NOP));
  };
  //////////////////////////////////////////////////////////////////////////

  auto rx_bpsk_pipeline_1 = [&]() -> bool
  {
    START(src, IF([&]() -> bool
    {
      ONCE(mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_bpsk1, ht_deinterleave_1bpsc_iss1,
        ht_demap_bpsk2, ht_deinterleave_1bpsc_iss2,
        ht_demap_bpsk3, ht_deinterleave_1bpsc_iss3,
        ht_demap_bpsk4, ht_deinterleave_1bpsc_iss4);

      max_symbol_count--;
      printf("%d symbol left...\n", max_symbol_count);
      return (max_symbol_count <= 0);
    }), STOP(NOP));
    return false;
  };

  auto rx_qpsk_pipeline_1 = [&]() -> bool
  {
    START(src, STOP([&]
    {
      ONCE(mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_qpsk1, ht_deinterleave_2bpsc_iss1,
        ht_demap_qpsk2, ht_deinterleave_2bpsc_iss2,
        ht_demap_qpsk3, ht_deinterleave_2bpsc_iss3,
        ht_demap_qpsk4, ht_deinterleave_2bpsc_iss4);
    }));

    max_symbol_count--;
    return max_symbol_count > 0;
  };

  auto rx_16qam_pipeline_1 = [&]() -> bool
  {
    START(src, STOP([&]
    {
      ONCE(mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_16qam1, ht_deinterleave_4bpsc_iss1,
        ht_demap_16qam2, ht_deinterleave_4bpsc_iss2,
        ht_demap_16qam3, ht_deinterleave_4bpsc_iss3,
        ht_demap_16qam4, ht_deinterleave_4bpsc_iss4);
    }));

    max_symbol_count--;
    return max_symbol_count > 0;
  };

  auto rx_64qam_pipeline_1 = [&]() -> bool
  {
    START(src, STOP([&]
    {
      ONCE(mimo_channel_compensator, pilot_tracking);

      ONCE(ht_demap_64qam1, ht_deinterleave_6bpsc_iss1);
      ONCE(ht_demap_64qam2, ht_deinterleave_6bpsc_iss2);
      ONCE(ht_demap_64qam3, ht_deinterleave_6bpsc_iss3);
      ONCE(ht_demap_64qam4, ht_deinterleave_6bpsc_iss4);
    }));

    max_symbol_count--;
    return max_symbol_count > 0;
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

  auto wait_for_streams = [&]() -> bool
  {
    START(src, IF(pipeline_init), STOP(NOP));
    return true;
  };


  auto htdata_handler = [&]
  {
    uint32 frame_mcs;
    if ((*config_msg).msg.frame1_ok)
    {
      frame_mcs = (*config_msg).msg.frame1_rate;
    }
    else if ((*config_msg).msg.frame2_ok)
    {
      frame_mcs = (*config_msg).msg.frame2_rate;
    }
    else if ((*config_msg).msg.frame3_ok)
    {
      frame_mcs = (*config_msg).msg.frame3_rate;
    }
    else if ((*config_msg).msg.frame4_ok)
    {
      frame_mcs = (*config_msg).msg.frame4_rate;
    }
    else
    {
      printf("error: none l-sig is right! abort decoding...\n");
      return;
    }

    t1 = tick_count::now();
    START(
      IF     (IsTrue(frame_mcs == 8)),  rx_mcs8_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 9)),  rx_mcs9_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 10)), rx_mcs10_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 11)), rx_mcs11_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 12)), rx_mcs12_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 13)), rx_mcs13_pipeline,
      ELSE_IF(IsTrue(frame_mcs == 14)), rx_mcs14_pipeline,
      ELSE, NOP
      );
    t2 = tick_count::now();
    tick_count t = t2 - t1;
    printf("time = %f us, %f MSPS\n", t.us(), total_symbol_count * 80 / t.us());
    printf("frame decode done! %d : %d : %d : %d\n", 
      *crc32_checker_1.crc32_check_result, *crc32_checker_2.crc32_check_result,
      *crc32_checker_3.crc32_check_result, *crc32_checker_4.crc32_check_result);
  };

  START( WHILE(wait_for_streams), htdata_handler );
};
