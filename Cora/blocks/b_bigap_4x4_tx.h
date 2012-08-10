#pragma once


inline void bigap_4x4_tx(int argc, _TCHAR* argv[])
{
  dsp_cmd cmdline;
  cmdline.parse(argc, argv);

  autoref dummy = create_block<dummy_block>();

  autoref lstf = create_block<b_dot11n_lstf_v4>();

  autoref lltf_1 = create_block<b_bigap_lltf_tx_v1>();
  autoref lltf_2 = create_block<b_bigap_lltf_tx_v1>();
  autoref lltf_3 = create_block<b_bigap_lltf_tx_v1>();
  autoref lltf_4 = create_block<b_bigap_lltf_tx_v1>();

  autoref dummy_lltf_1 = create_block<b_bigap_dummy_lltf_tx_v1>();
  autoref dummy_lltf_2 = create_block<b_bigap_dummy_lltf_tx_v1>();
  autoref dummy_lltf_3 = create_block<b_bigap_dummy_lltf_tx_v1>();
  autoref dummy_lltf_4 = create_block<b_bigap_dummy_lltf_tx_v1>();

  
  //////////////////////////////////////////////////////////////////////////
  // for L/HT-SIG
  autoref lsig_1 = create_block<b_dot11n_lsig_v1>();
  autoref lsig_2 = create_block<b_dot11n_lsig_v1>();
  autoref lsig_3 = create_block<b_dot11n_lsig_v1>();
  autoref lsig_4 = create_block<b_dot11n_lsig_v1>();

  autoref sigconv_1  = create_block<b_conv_1o2_1v1>();
  autoref sigconv_2  = create_block<b_conv_1o2_1v1>();
  autoref sigconv_3  = create_block<b_conv_1o2_1v1>();
  autoref sigconv_4  = create_block<b_conv_1o2_1v1>();

  autoref sigitlv_1  = create_block<b_dot11a_interleaver_1bpsc_1v1>();
  autoref sigitlv_2  = create_block<b_dot11a_interleaver_1bpsc_1v1>();
  autoref sigitlv_3  = create_block<b_dot11a_interleaver_1bpsc_1v1>();
  autoref sigitlv_4  = create_block<b_dot11a_interleaver_1bpsc_1v1>();

  autoref sigmap_1  = create_block<b_dot11a_map_bpsk_i_1v1>();
  autoref sigmap_2  = create_block<b_dot11a_map_bpsk_i_1v1>();
  autoref sigmap_3  = create_block<b_dot11a_map_bpsk_i_1v1>();
  autoref sigmap_4  = create_block<b_dot11a_map_bpsk_i_1v1>();

  autoref sigifft_1  = create_block<b_dot11n_tx_ifft_128_1v1>();
  autoref sigifft_2  = create_block<b_dot11n_tx_ifft_128_1v1>();
  autoref sigifft_3  = create_block<b_dot11n_tx_ifft_128_1v1>();
  autoref sigifft_4  = create_block<b_dot11n_tx_ifft_128_1v1>();
  
  autoref add_sigpilot_1 = create_block<b_dot11a_add_pilot_1v>();
  autoref add_sigpilot_2 = create_block<b_dot11a_add_pilot_1v>();
  autoref add_sigpilot_3 = create_block<b_dot11a_add_pilot_1v>();
  autoref add_sigpilot_4 = create_block<b_dot11a_add_pilot_1v>();

  autoref add_sigcp_1 = create_block<b_dot11n_add_cp_1v1>();
  autoref add_sigcp_2 = create_block<b_dot11n_add_cp_1v1>();
  autoref add_sigcp_3 = create_block<b_dot11n_add_cp_1v1>();
  autoref add_sigcp_4 = create_block<b_dot11n_add_cp_1v1>();
  //////////////////////////////////////////////////////////////////////////

  // for HT-DATA
  autoref ht_data_source = create_block<b_dot11_frame_source_v4>();

  autoref ht_scramble_1 = create_block<b_dot11n_scramble_1v1>();
  autoref ht_scramble_2 = create_block<b_dot11n_scramble_1v1>();
  autoref ht_scramble_3 = create_block<b_dot11n_scramble_1v1>();
  autoref ht_scramble_4 = create_block<b_dot11n_scramble_1v1>();

  autoref ht_conv12_1 = create_block<b_conv_1o2_1v1>();
  autoref ht_conv12_2 = create_block<b_conv_1o2_1v1>();
  autoref ht_conv12_3 = create_block<b_conv_1o2_1v1>();
  autoref ht_conv12_4 = create_block<b_conv_1o2_1v1>();

  autoref ht_conv23_1 = create_block<b_conv_2o3_1v1>();
  autoref ht_conv23_2 = create_block<b_conv_2o3_1v1>();
  autoref ht_conv23_3 = create_block<b_conv_2o3_1v1>();
  autoref ht_conv23_4 = create_block<b_conv_2o3_1v1>();

  autoref ht_conv34_1 = create_block<b_conv_3o4_1v1>();
  autoref ht_conv34_2 = create_block<b_conv_3o4_1v1>();
  autoref ht_conv34_3 = create_block<b_conv_3o4_1v1>();
  autoref ht_conv34_4 = create_block<b_conv_3o4_1v1>();

  // interleaver
  autoref ht_itlv_1bpsc_1 = create_block<b_dot11n_interleaver_1bpsc_half_1v1>(1, string("iss=1"));
  autoref ht_itlv_1bpsc_2 = create_block<b_dot11n_interleaver_1bpsc_half_1v1>(1, string("iss=1"));
  autoref ht_itlv_1bpsc_3 = create_block<b_dot11n_interleaver_1bpsc_half_1v1>(1, string("iss=1"));
  autoref ht_itlv_1bpsc_4 = create_block<b_dot11n_interleaver_1bpsc_half_1v1>(1, string("iss=1"));

  autoref ht_itlv_2bpsc_1 = create_block<b_dot11n_interleaver_2bpsc_1v1>(1, string("iss=1"));
  autoref ht_itlv_2bpsc_2 = create_block<b_dot11n_interleaver_2bpsc_1v1>(1, string("iss=1"));
  autoref ht_itlv_2bpsc_3 = create_block<b_dot11n_interleaver_2bpsc_1v1>(1, string("iss=1"));
  autoref ht_itlv_2bpsc_4 = create_block<b_dot11n_interleaver_2bpsc_1v1>(1, string("iss=1"));

  autoref ht_itlv_4bpsc_1 = create_block<b_dot11n_interleaver_4bpsc_1v1>(1, string("iss=1"));
  autoref ht_itlv_4bpsc_2 = create_block<b_dot11n_interleaver_4bpsc_1v1>(1, string("iss=1"));
  autoref ht_itlv_4bpsc_3 = create_block<b_dot11n_interleaver_4bpsc_1v1>(1, string("iss=1"));
  autoref ht_itlv_4bpsc_4 = create_block<b_dot11n_interleaver_4bpsc_1v1>(1, string("iss=1"));

  autoref ht_itlv_6bpsc_1 = create_block<b_dot11n_interleaver_6bpsc_1v1>(1, string("iss=1"));
  autoref ht_itlv_6bpsc_2 = create_block<b_dot11n_interleaver_6bpsc_1v1>(1, string("iss=1"));
  autoref ht_itlv_6bpsc_3 = create_block<b_dot11n_interleaver_6bpsc_1v1>(1, string("iss=1"));
  autoref ht_itlv_6bpsc_4 = create_block<b_dot11n_interleaver_6bpsc_1v1>(1, string("iss=1"));

  // mapper
  autoref ht_map_bpsk_1   = create_block<b_dot11n_map_bpsk_i_1v1>();
  autoref ht_map_bpsk_2   = create_block<b_dot11n_map_bpsk_i_1v1>();
  autoref ht_map_bpsk_3   = create_block<b_dot11n_map_bpsk_i_1v1>();
  autoref ht_map_bpsk_4   = create_block<b_dot11n_map_bpsk_i_1v1>();

  autoref ht_map_qpsk_1   = create_block<b_dot11n_map_qpsk_1v1>();
  autoref ht_map_qpsk_2   = create_block<b_dot11n_map_qpsk_1v1>();
  autoref ht_map_qpsk_3   = create_block<b_dot11n_map_qpsk_1v1>();
  autoref ht_map_qpsk_4   = create_block<b_dot11n_map_qpsk_1v1>();

  autoref ht_map_16qam_1  = create_block<b_dot11n_map_16qam_1v1>();
  autoref ht_map_16qam_2  = create_block<b_dot11n_map_16qam_1v1>();
  autoref ht_map_16qam_3  = create_block<b_dot11n_map_16qam_1v1>();
  autoref ht_map_16qam_4  = create_block<b_dot11n_map_16qam_1v1>();

  autoref ht_map_64qam_1  = create_block<b_dot11n_map_64qam_1v1>();
  autoref ht_map_64qam_2  = create_block<b_dot11n_map_64qam_1v1>();
  autoref ht_map_64qam_3  = create_block<b_dot11n_map_64qam_1v1>();
  autoref ht_map_64qam_4  = create_block<b_dot11n_map_64qam_1v1>();
  // pilot
  autoref ht_add_pilot_1 = create_block<b_dot11n_4x4_add_pilot_1v>(1, string("iss=0"));
  autoref ht_add_pilot_2 = create_block<b_dot11n_4x4_add_pilot_1v>(1, string("iss=1"));
  autoref ht_add_pilot_3 = create_block<b_dot11n_4x4_add_pilot_1v>(1, string("iss=2"));
  autoref ht_add_pilot_4 = create_block<b_dot11n_4x4_add_pilot_1v>(1, string("iss=3"));

  // ifft
  autoref ht_ifft_1  = create_block<b_dot11n_tx_ifft_128_1v1>();
  autoref ht_ifft_2  = create_block<b_dot11n_tx_ifft_128_1v1>();
  autoref ht_ifft_3  = create_block<b_dot11n_tx_ifft_128_1v1>();
  autoref ht_ifft_4  = create_block<b_dot11n_tx_ifft_128_1v1>();

  // add cp
  autoref ht_add_cp_1 = create_block<b_dot11n_add_cp_1v1>();
  autoref ht_add_cp_2 = create_block<b_dot11n_add_cp_1v1>();
  autoref ht_add_cp_3 = create_block<b_dot11n_add_cp_1v1>();
  autoref ht_add_cp_4 = create_block<b_dot11n_add_cp_1v1>();
  //////////////////////////////////////////////////////////////////////////
  autoref dma_join = create_block<b_dot11n_dma_join_4v1>();


  //////////////////////////////////////////////////////////////////////////
  // Create channels to link blocks
  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(lstf, 0).from(lltf_1, 0).from(dummy_lltf_1, 0).from(add_sigcp_1, 0).from(ht_add_cp_1, 0)
    .to(dma_join, 0);
  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(lstf, 1).from(lltf_2, 0).from(dummy_lltf_2, 0).from(add_sigcp_2, 0).from(ht_add_cp_2, 0)
    .to(dma_join, 1);
  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(lstf, 2).from(lltf_3, 0).from(dummy_lltf_3, 0).from(add_sigcp_3, 0).from(ht_add_cp_3, 0)
    .to(dma_join, 2);
  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(lstf, 3).from(lltf_4, 0).from(dummy_lltf_4, 0).from(add_sigcp_4, 0).from(ht_add_cp_4, 0)
    .to(dma_join, 3);
  //////////////////////////////////////////////////////////////////////////
  // L-SIG
  Channel::Create(sizeof(uint8)).from(lsig_1, 0).to(sigconv_1, 0);
  Channel::Create(sizeof(uint8)).from(lsig_2, 0).to(sigconv_2, 0);
  Channel::Create(sizeof(uint8)).from(lsig_3, 0).to(sigconv_3, 0);
  Channel::Create(sizeof(uint8)).from(lsig_4, 0).to(sigconv_4, 0);

  Channel::Create(sizeof(uint8)).from(sigconv_1, 0).to(sigitlv_1, 0);
  Channel::Create(sizeof(uint8)).from(sigconv_2, 0).to(sigitlv_2, 0);
  Channel::Create(sizeof(uint8)).from(sigconv_3, 0).to(sigitlv_3, 0);
  Channel::Create(sizeof(uint8)).from(sigconv_4, 0).to(sigitlv_4, 0);

  Channel::Create(sizeof(v_ub)).from(sigitlv_1, 0).to(sigmap_1, 0);
  Channel::Create(sizeof(v_ub)).from(sigitlv_2, 0).to(sigmap_2, 0);
  Channel::Create(sizeof(v_ub)).from(sigitlv_3, 0).to(sigmap_3, 0);
  Channel::Create(sizeof(v_ub)).from(sigitlv_4, 0).to(sigmap_4, 0);

  Channel::Create(sizeof(dot11n_tx_symbol)).from(sigmap_1, 0).to(add_sigpilot_1, 0).to(sigifft_1, 0);
  Channel::Create(sizeof(dot11n_tx_symbol)).from(sigmap_2, 0).to(add_sigpilot_2, 0).to(sigifft_2, 0);
  Channel::Create(sizeof(dot11n_tx_symbol)).from(sigmap_3, 0).to(add_sigpilot_3, 0).to(sigifft_3, 0);
  Channel::Create(sizeof(dot11n_tx_symbol)).from(sigmap_4, 0).to(add_sigpilot_4, 0).to(sigifft_4, 0);

  Channel::Create(sizeof(dot11n_tx_symbol)).from(sigifft_1, 0).to(add_sigcp_1, 0);
  Channel::Create(sizeof(dot11n_tx_symbol)).from(sigifft_2, 0).to(add_sigcp_2, 0);
  Channel::Create(sizeof(dot11n_tx_symbol)).from(sigifft_3, 0).to(add_sigcp_3, 0);
  Channel::Create(sizeof(dot11n_tx_symbol)).from(sigifft_4, 0).to(add_sigcp_4, 0);
  //////////////////////////////////////////////////////////////////////////
  Channel::Create(sizeof(uint8)).from(ht_data_source, 0).to(ht_scramble_1, 0);
  Channel::Create(sizeof(uint8)).from(ht_data_source, 1).to(ht_scramble_2, 0);
  Channel::Create(sizeof(uint8)).from(ht_data_source, 2).to(ht_scramble_3, 0);
  Channel::Create(sizeof(uint8)).from(ht_data_source, 3).to(ht_scramble_4, 0);

  Channel::Create(sizeof(uint8)).from(ht_scramble_1, 0).to(ht_conv12_1, 0).to(ht_conv23_1, 0).to(ht_conv34_1, 0);
  Channel::Create(sizeof(uint8)).from(ht_scramble_2, 0).to(ht_conv12_2, 0).to(ht_conv23_2, 0).to(ht_conv34_2, 0);
  Channel::Create(sizeof(uint8)).from(ht_scramble_3, 0).to(ht_conv12_3, 0).to(ht_conv23_3, 0).to(ht_conv34_3, 0);
  Channel::Create(sizeof(uint8)).from(ht_scramble_4, 0).to(ht_conv12_4, 0).to(ht_conv23_4, 0).to(ht_conv34_4, 0);

  Channel::Create(sizeof(uint8))
    .from(ht_conv12_1, 0).from(ht_conv23_1, 0).from(ht_conv34_1, 0)
    .to(ht_itlv_1bpsc_1, 0).to(ht_itlv_2bpsc_1, 0).to(ht_itlv_4bpsc_1, 0).to(ht_itlv_6bpsc_1, 0);

  Channel::Create(sizeof(uint8))
    .from(ht_conv12_2, 0).from(ht_conv23_2, 0).from(ht_conv34_2, 0)
    .to(ht_itlv_1bpsc_2, 0).to(ht_itlv_2bpsc_2, 0).to(ht_itlv_4bpsc_2, 0).to(ht_itlv_6bpsc_2, 0);

  Channel::Create(sizeof(uint8))
    .from(ht_conv12_3, 0).from(ht_conv23_3, 0).from(ht_conv34_3, 0)
    .to(ht_itlv_1bpsc_3, 0).to(ht_itlv_2bpsc_3, 0).to(ht_itlv_4bpsc_3, 0).to(ht_itlv_6bpsc_3, 0);

  Channel::Create(sizeof(uint8))
    .from(ht_conv12_4, 0).from(ht_conv23_4, 0).from(ht_conv34_4, 0)
    .to(ht_itlv_1bpsc_4, 0).to(ht_itlv_2bpsc_4, 0).to(ht_itlv_4bpsc_4, 0).to(ht_itlv_6bpsc_4, 0);

  Channel::Create(sizeof(v_ub))
    .from(ht_itlv_1bpsc_1, 0).from(ht_itlv_2bpsc_1, 0).from(ht_itlv_4bpsc_1, 0).from(ht_itlv_6bpsc_1, 0)
    .to(ht_map_bpsk_1, 0).to(ht_map_qpsk_1, 0).to(ht_map_16qam_1, 0).to(ht_map_64qam_1, 0);
  Channel::Create(sizeof(v_ub))
    .from(ht_itlv_1bpsc_2, 0).from(ht_itlv_2bpsc_2, 0).from(ht_itlv_4bpsc_2, 0).from(ht_itlv_6bpsc_2, 0)
    .to(ht_map_bpsk_2, 0).to(ht_map_qpsk_2, 0).to(ht_map_16qam_2, 0).to(ht_map_64qam_2, 0);
  Channel::Create(sizeof(v_ub))
    .from(ht_itlv_1bpsc_3, 0).from(ht_itlv_2bpsc_3, 0).from(ht_itlv_4bpsc_3, 0).from(ht_itlv_6bpsc_3, 0)
    .to(ht_map_bpsk_3, 0).to(ht_map_qpsk_3, 0).to(ht_map_16qam_3, 0).to(ht_map_64qam_3, 0);
  Channel::Create(sizeof(v_ub))
    .from(ht_itlv_1bpsc_4, 0).from(ht_itlv_2bpsc_4, 0).from(ht_itlv_4bpsc_4, 0).from(ht_itlv_6bpsc_4, 0)
    .to(ht_map_bpsk_4, 0).to(ht_map_qpsk_4, 0).to(ht_map_16qam_4, 0).to(ht_map_64qam_4, 0);

  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(ht_map_bpsk_1, 0).from(ht_map_qpsk_1, 0).from(ht_map_16qam_1, 0).from(ht_map_64qam_1, 0)
    .to(ht_add_pilot_1, 0).to(ht_ifft_1, 0);
  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(ht_map_bpsk_2, 0).from(ht_map_qpsk_2, 0).from(ht_map_16qam_2, 0).from(ht_map_64qam_2, 0)
    .to(ht_add_pilot_2, 0).to(ht_ifft_2, 0);
  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(ht_map_bpsk_3, 0).from(ht_map_qpsk_3, 0).from(ht_map_16qam_3, 0).from(ht_map_64qam_3, 0)
    .to(ht_add_pilot_3, 0).to(ht_ifft_3, 0);
  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(ht_map_bpsk_4, 0).from(ht_map_qpsk_4, 0).from(ht_map_16qam_4, 0).from(ht_map_64qam_4, 0)
    .to(ht_add_pilot_4, 0).to(ht_ifft_4, 0);


  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(ht_ifft_1, 0).to(ht_add_cp_1, 0);
  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(ht_ifft_2, 0).to(ht_add_cp_2, 0);
  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(ht_ifft_3, 0).to(ht_add_cp_3, 0);
  Channel::Create(sizeof(dot11n_tx_symbol))
    .from(ht_ifft_4, 0).to(ht_add_cp_4, 0);

  //////////////////////////////////////////////////////////////////////////
  Channel::Create(sizeof(v_cs), 1024 * 1024)
    .from(dma_join, 0).to(dummy, 0);

  //////////////////////////////////////////////////////////////////////////
  v_align(64)
  _global_(uint32, dot11_tx_frame_mcs);
  _global_(uint32, dot11_tx_frame_length);
  _global_(int,    scramble_length);

  tick_count t1, t2, t3, tdiff;

  auto get_time = [&](tick_count & t)
  {
    t = tick_count::now();
  };
  auto get_throughput = [&] (tick_count& t1, tick_count& t2, uint32 nbytes)
  {
    tick_count t = t2 - t1;

    printf("time is %f us, throughput is %f Mbps\n", t.us(), 4.0f * nbytes * 8.0f / t.us());
  };
  //////////////////////////////////////////////////////////////////////////
  
  auto make_lsig_1 = [&]
  {
    RESET(sigconv_1, add_sigpilot_1);
    *lsig_1.rate = *dot11_tx_frame_mcs;
    ONCE(lsig_1, [&]
    {
      START(sigconv_1, sigitlv_1, sigmap_1, add_sigpilot_1, sigifft_1, add_sigcp_1);
    });
  };

  auto make_lsig_2 = [&]
  {
    RESET(sigconv_2, add_sigpilot_2);
    *lsig_2.rate = *dot11_tx_frame_mcs;
    ONCE(lsig_2, [&]
    {
      START(sigconv_2, sigitlv_2, sigmap_2, add_sigpilot_2, sigifft_2, add_sigcp_2);
    });
  };
  auto make_lsig_3 = [&]
  {
    RESET(sigconv_3, add_sigpilot_3);
    *lsig_3.rate = *dot11_tx_frame_mcs;
    ONCE(lsig_3, [&]
    {
      START(sigconv_3, sigitlv_3, sigmap_3, add_sigpilot_3, sigifft_3, add_sigcp_3);
    });
  };
  auto make_lsig_4 = [&]
  {
    RESET(sigconv_4, add_sigpilot_4);
    *lsig_4.rate = *dot11_tx_frame_mcs;
    ONCE(lsig_4, [&]
    {
      START(sigconv_4, sigitlv_4, sigmap_4, add_sigpilot_4, sigifft_4, add_sigcp_4);
    });
  };

  auto make_plcp = [&]
  {
    ONCE(lstf);
    ONCE(lltf_1, make_lsig_1, dummy_lltf_1, dummy_lltf_1, dummy_lltf_1);
    ONCE(dummy_lltf_2, lltf_2, make_lsig_2, dummy_lltf_2, dummy_lltf_2);
    ONCE(dummy_lltf_3, dummy_lltf_3, lltf_3, make_lsig_3, dummy_lltf_3);
    ONCE(dummy_lltf_4, dummy_lltf_4, dummy_lltf_4, lltf_4, make_lsig_4);
    START(dma_join);
  };

  auto make_htdata_mcs8 = [&]
  {
    RESET(ht_scramble_1, ht_conv12_1, ht_add_pilot_1);
    RESET(ht_scramble_2, ht_conv12_2, ht_add_pilot_2);
    RESET(ht_scramble_3, ht_conv12_3, ht_add_pilot_3);
    RESET(ht_scramble_4, ht_conv12_4, ht_add_pilot_4);

    ONCE([&]{
      START(ht_scramble_1, ht_conv12_1, ht_itlv_1bpsc_1, ht_map_bpsk_1, ht_add_pilot_1, ht_ifft_1, ht_add_cp_1);
    }, [&]{
      START(ht_scramble_2, ht_conv12_2, ht_itlv_1bpsc_2, ht_map_bpsk_2, ht_add_pilot_2, ht_ifft_2, ht_add_cp_2);
    }, [&]{
      START(ht_scramble_3, ht_conv12_3, ht_itlv_1bpsc_3, ht_map_bpsk_3, ht_add_pilot_3, ht_ifft_3, ht_add_cp_3);
    }, [&]{
      START(ht_scramble_4, ht_conv12_4, ht_itlv_1bpsc_4, ht_map_bpsk_4, ht_add_pilot_4, ht_ifft_4, ht_add_cp_4);
    });

    START(dma_join);
  };

  auto make_htdata_mcs9 = [&]
  {
    RESET(ht_scramble_1, ht_conv12_1, ht_add_pilot_1);
    RESET(ht_scramble_2, ht_conv12_2, ht_add_pilot_2);
    RESET(ht_scramble_3, ht_conv12_3, ht_add_pilot_3);
    RESET(ht_scramble_4, ht_conv12_4, ht_add_pilot_4);

    START(ht_scramble_1, ht_conv12_1, ht_itlv_2bpsc_1, ht_map_qpsk_1, ht_add_pilot_1, ht_ifft_1, ht_add_cp_1);
    START(ht_scramble_2, ht_conv12_2, ht_itlv_2bpsc_2, ht_map_qpsk_2, ht_add_pilot_2, ht_ifft_2, ht_add_cp_2);
    START(ht_scramble_3, ht_conv12_3, ht_itlv_2bpsc_3, ht_map_qpsk_3, ht_add_pilot_3, ht_ifft_3, ht_add_cp_3);
    START(ht_scramble_4, ht_conv12_4, ht_itlv_2bpsc_4, ht_map_qpsk_4, ht_add_pilot_4, ht_ifft_4, ht_add_cp_4);

    START(dma_join);
  };

  auto make_htdata_mcs10 = [&]
  {
    RESET(ht_scramble_1, ht_conv34_1, ht_add_pilot_1);
    RESET(ht_scramble_2, ht_conv34_2, ht_add_pilot_2);
    RESET(ht_scramble_3, ht_conv34_3, ht_add_pilot_3);
    RESET(ht_scramble_4, ht_conv34_4, ht_add_pilot_4);

    START(ht_scramble_1, ht_conv34_1, ht_itlv_2bpsc_1, ht_map_qpsk_1, ht_add_pilot_1, ht_ifft_1, ht_add_cp_1);
    START(ht_scramble_2, ht_conv34_2, ht_itlv_2bpsc_2, ht_map_qpsk_2, ht_add_pilot_2, ht_ifft_2, ht_add_cp_2);
    START(ht_scramble_3, ht_conv34_3, ht_itlv_2bpsc_3, ht_map_qpsk_3, ht_add_pilot_3, ht_ifft_3, ht_add_cp_3);
    START(ht_scramble_4, ht_conv34_4, ht_itlv_2bpsc_4, ht_map_qpsk_4, ht_add_pilot_4, ht_ifft_4, ht_add_cp_4);

    START(dma_join);
  };

  auto make_htdata_mcs11 = [&]
  {
    RESET(ht_scramble_1, ht_conv12_1, ht_add_pilot_1);
    RESET(ht_scramble_2, ht_conv12_2, ht_add_pilot_2);
    RESET(ht_scramble_3, ht_conv12_3, ht_add_pilot_3);
    RESET(ht_scramble_4, ht_conv12_4, ht_add_pilot_4);

    START(ht_scramble_1, ht_conv12_1, ht_itlv_4bpsc_1, ht_map_16qam_1, ht_add_pilot_1, ht_ifft_1, ht_add_cp_1);
    START(ht_scramble_2, ht_conv12_2, ht_itlv_4bpsc_2, ht_map_16qam_2, ht_add_pilot_2, ht_ifft_2, ht_add_cp_2);
    START(ht_scramble_3, ht_conv12_3, ht_itlv_4bpsc_3, ht_map_16qam_3, ht_add_pilot_3, ht_ifft_3, ht_add_cp_3);
    START(ht_scramble_4, ht_conv12_4, ht_itlv_4bpsc_4, ht_map_16qam_4, ht_add_pilot_4, ht_ifft_4, ht_add_cp_4);

    START(dma_join);
  };

  auto make_htdata_mcs12 = [&]
  {
    RESET(ht_scramble_1, ht_conv34_1, ht_add_pilot_1);
    RESET(ht_scramble_2, ht_conv34_2, ht_add_pilot_2);
    RESET(ht_scramble_3, ht_conv34_3, ht_add_pilot_3);
    RESET(ht_scramble_4, ht_conv34_4, ht_add_pilot_4);

    START(ht_scramble_1, ht_conv34_1, ht_itlv_4bpsc_1, ht_map_16qam_1, ht_add_pilot_1, ht_ifft_1, ht_add_cp_1);
    START(ht_scramble_2, ht_conv34_2, ht_itlv_4bpsc_2, ht_map_16qam_2, ht_add_pilot_2, ht_ifft_2, ht_add_cp_2);
    START(ht_scramble_3, ht_conv34_3, ht_itlv_4bpsc_3, ht_map_16qam_3, ht_add_pilot_3, ht_ifft_3, ht_add_cp_3);
    START(ht_scramble_4, ht_conv34_4, ht_itlv_4bpsc_4, ht_map_16qam_4, ht_add_pilot_4, ht_ifft_4, ht_add_cp_4);

    START(dma_join);
  };

  auto make_htdata_mcs13 = [&]
  {
    RESET(ht_scramble_1, ht_conv23_1, ht_add_pilot_1);
    RESET(ht_scramble_2, ht_conv23_2, ht_add_pilot_2);
    RESET(ht_scramble_3, ht_conv23_3, ht_add_pilot_3);
    RESET(ht_scramble_4, ht_conv23_4, ht_add_pilot_4);

    START(ht_scramble_1, ht_conv23_1, ht_itlv_6bpsc_1, ht_map_64qam_1, ht_add_pilot_1, ht_ifft_1, ht_add_cp_1);
    START(ht_scramble_2, ht_conv23_2, ht_itlv_6bpsc_2, ht_map_64qam_2, ht_add_pilot_2, ht_ifft_2, ht_add_cp_2);
    START(ht_scramble_3, ht_conv23_3, ht_itlv_6bpsc_3, ht_map_64qam_3, ht_add_pilot_3, ht_ifft_3, ht_add_cp_3);
    START(ht_scramble_4, ht_conv23_4, ht_itlv_6bpsc_4, ht_map_64qam_4, ht_add_pilot_4, ht_ifft_4, ht_add_cp_4);

    START(dma_join);
  };

  auto make_htdata_mcs14 = [&]
  {
#if 1
    PARALLEL([&]{
      RESET(ht_scramble_1, ht_conv34_1, ht_add_pilot_1);
      START(ht_scramble_1, ht_conv34_1, ht_itlv_6bpsc_1, ht_map_64qam_1, ht_add_pilot_1, ht_ifft_1, ht_add_cp_1);      
    }, [&]{
      RESET(ht_scramble_2, ht_conv34_2, ht_add_pilot_2);
      START(ht_scramble_2, ht_conv34_2, ht_itlv_6bpsc_2, ht_map_64qam_2, ht_add_pilot_2, ht_ifft_2, ht_add_cp_2);
    }, [&]{
      RESET(ht_scramble_3, ht_conv34_3, ht_add_pilot_3);
      START(ht_scramble_3, ht_conv34_3, ht_itlv_6bpsc_3, ht_map_64qam_3, ht_add_pilot_3, ht_ifft_3, ht_add_cp_3);
    }, [&]{
      RESET(ht_scramble_4, ht_conv34_4, ht_add_pilot_4);
      START(ht_scramble_4, ht_conv34_4, ht_itlv_6bpsc_4, ht_map_64qam_4, ht_add_pilot_4, ht_ifft_4, ht_add_cp_4);
    });
#else
    RESET(ht_scramble_1, ht_conv34_1, ht_add_pilot_1);
    RESET(ht_scramble_2, ht_conv34_2, ht_add_pilot_2);
    RESET(ht_scramble_3, ht_conv34_3, ht_add_pilot_3);
    RESET(ht_scramble_4, ht_conv34_4, ht_add_pilot_4);

    START(ht_scramble_1, ht_conv34_1, ht_itlv_6bpsc_1, ht_map_64qam_1, ht_add_pilot_1, ht_ifft_1, ht_add_cp_1);
    START(ht_scramble_2, ht_conv34_2, ht_itlv_6bpsc_2, ht_map_64qam_2, ht_add_pilot_2, ht_ifft_2, ht_add_cp_2);
    START(ht_scramble_3, ht_conv34_3, ht_itlv_6bpsc_3, ht_map_64qam_3, ht_add_pilot_3, ht_ifft_3, ht_add_cp_3);
    START(ht_scramble_4, ht_conv34_4, ht_itlv_6bpsc_4, ht_map_64qam_4, ht_add_pilot_4, ht_ifft_4, ht_add_cp_4);
#endif
    START(dma_join);
  };

  auto mcs8_entry = [&]
  {
    ONCE(ht_data_source, [&]{get_time(t1);}, make_plcp, make_htdata_mcs8, [&]{get_time(t2); get_throughput(t1, t2, *dot11_tx_frame_length);});
  };

  auto mcs9_entry = [&]
  {
    ONCE(ht_data_source, [&]{get_time(t1);}, make_plcp, make_htdata_mcs9, [&]{get_time(t2); get_throughput(t1, t2, *dot11_tx_frame_length);});
  };

  auto mcs10_entry = [&]
  {
    ONCE(ht_data_source, [&]{get_time(t1);}, make_plcp, make_htdata_mcs10, [&]{get_time(t2); get_throughput(t1, t2, *dot11_tx_frame_length);});
  };

  auto mcs11_entry = [&]
  {
    ONCE(ht_data_source, [&]{get_time(t1);}, make_plcp, make_htdata_mcs11, [&]{get_time(t2); get_throughput(t1, t2, *dot11_tx_frame_length);});
  };

  auto mcs12_entry = [&]
  {
    ONCE(ht_data_source, [&]{get_time(t1);}, make_plcp, make_htdata_mcs12, [&]{get_time(t2); get_throughput(t1, t2, *dot11_tx_frame_length);});
  };

  auto mcs13_entry = [&]
  {
    ONCE(ht_data_source, [&]{get_time(t1);}, make_plcp, make_htdata_mcs13, [&]{get_time(t2); get_throughput(t1, t2, *dot11_tx_frame_length);});
  };

  auto mcs14_entry = [&]
  {
    ONCE(ht_data_source, [&]{get_time(t1);}, make_plcp, make_htdata_mcs14, [&]{get_time(t2); get_throughput(t1, t2, *dot11_tx_frame_length);});
  };

  //////////////////////////////////////////////////////////////////////////

  auto _init_ = [&](int mcs, int frame_length)
  {
    *dot11_tx_frame_mcs    = mcs;
    *dot11_tx_frame_length = frame_length;
    *scramble_length       = *dot11_tx_frame_length + 2;

    *ht_scramble_1.scramble_length = *dot11_tx_frame_length + 2;
    *ht_scramble_2.scramble_length = *dot11_tx_frame_length + 2;
    *ht_scramble_3.scramble_length = *dot11_tx_frame_length + 2;
    *ht_scramble_4.scramble_length = *dot11_tx_frame_length + 2;
  };

  int mcs = cmdline.get("mcs").as_int();
  if (mcs == 0)
  {
    mcs = 8;
  }

  int frame_length = cmdline.get("frame_length").as_int();
  if (frame_length == 0)
  {
    frame_length = 1500;
  }

  _init_(mcs, frame_length);

  int nloop = 1;

  START(
    WHILE(IsTrue(nloop-- > 0)), 
    IF(IsTrue(*dot11_tx_frame_mcs == 8)),       mcs8_entry,
    ELSE_IF(IsTrue(*dot11_tx_frame_mcs == 9)),  mcs9_entry,
    ELSE_IF(IsTrue(*dot11_tx_frame_mcs == 10)), mcs10_entry,
    ELSE_IF(IsTrue(*dot11_tx_frame_mcs == 11)), mcs11_entry,
    ELSE_IF(IsTrue(*dot11_tx_frame_mcs == 12)), mcs12_entry,
    ELSE_IF(IsTrue(*dot11_tx_frame_mcs == 13)), mcs13_entry,
    ELSE_IF(IsTrue(*dot11_tx_frame_mcs == 14)), mcs14_entry,
    ELSE, NOP
    );

  dma_join.toRxDumpFile20M("mimo");
  //dma_join.toTxtFile("mimo");
}