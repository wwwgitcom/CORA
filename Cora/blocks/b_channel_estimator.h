#pragma once


__declspec(selectany) v_align(16) v_cs::type _80211_LLTFMask[16] =
{
  //0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
  { 0x0000FFFF, 0xFFFF0000, 0x0000FFFF, 0x0000FFFF },
  { 0xFFFF0000, 0xFFFF0000, 0x0000FFFF, 0xFFFF0000 },
  { 0x0000FFFF, 0xFFFF0000, 0x0000FFFF, 0x0000FFFF },
  { 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0xFFFF0000 },

  //1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  { 0xFFFF0000, 0x0000FFFF, 0x0000FFFF, 0xFFFF0000 },
  { 0x0000FFFF, 0xFFFF0000, 0x0000FFFF, 0xFFFF0000 },
  { 0xFFFF0000, 0xFFFF0000, 0xFFFF0000, 0x0000FFFF },
  { 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF },

  //0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1,
  { 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF },
  { 0x0000FFFF, 0x0000FFFF, 0xFFFF0000, 0xFFFF0000 },
  { 0x0000FFFF, 0x0000FFFF, 0xFFFF0000, 0xFFFF0000 },
  { 0x0000FFFF, 0xFFFF0000, 0x0000FFFF, 0xFFFF0000 },

  //1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1
  { 0xFFFF0000, 0xFFFF0000, 0xFFFF0000, 0xFFFF0000 },
  { 0xFFFF0000, 0x0000FFFF, 0x0000FFFF, 0xFFFF0000 },
  { 0xFFFF0000, 0x0000FFFF, 0xFFFF0000, 0x0000FFFF },
  { 0xFFFF0000, 0xFFFF0000, 0xFFFF0000, 0xFFFF0000 }
};


void v_siso_channel_estimation_64(__in v_cs* pcsin, __out v_cs* pcschannel)
{
  v_i  vsqr, vsqrtemp;
  v_i  vciinput1, vciinput2;
  v_cs vout;
  v_cs *pvmask = (v_cs*)&_80211_LLTFMask[0];
  int  v;
  int  i;

  for (i = 0; i < 7; i++)
  {
    v_cs& vin = (v_cs&)pcsin[i];
    int sqr;
    vsqr = vin.v_sqr2i();

    vin.v_convert2ci((v_ci&)vciinput1, (v_ci&)vciinput2);

    vciinput1 = vciinput1.v_shift_left(16);
    vciinput2 = vciinput2.v_shift_left(16);

    vsqrtemp = vsqr.v_shift_right_arithmetic(1);

    vciinput1 = v_add(vciinput1, vsqrtemp);
    vciinput2 = v_add(vciinput2, vsqrtemp);

    sqr = vsqr.v_get_at<0>();
    if (sqr == 0) sqr = 1;
    v = vciinput1.v_get_at<0>() / sqr;
    vciinput1.v_set_at<0>( v );

    v = vciinput1.v_get_at<1>() / sqr;
    vciinput1.v_set_at<1>( v );

    sqr = vsqr.v_get_at<1>();
    if (sqr == 0) sqr = 1;
    v = vciinput1.v_get_at<2>() / sqr;
    vciinput1.v_set_at<2>( v );

    v = vciinput1.v_get_at<3>() / sqr;    
    vciinput1.v_set_at<3>( v );

    sqr = vsqr.v_get_at<2>();
    if (sqr == 0) sqr = 1;
    v = vciinput2.v_get_at<0>() / sqr;
    vciinput2.v_set_at<0>( v );

    v = vciinput2.v_get_at<1>() / sqr;
    vciinput2.v_set_at<1>( v );

    sqr = vsqr.v_get_at<3>();
    if (sqr == 0) sqr = 1;
    v = vciinput2.v_get_at<2>() / sqr;
    vciinput2.v_set_at<2>( v );

    v = vciinput2.v_get_at<3>() / sqr;
    vciinput2.v_set_at<3>( v );

    vout = v_convert2cs((v_ci&)vciinput1, (v_ci&)vciinput2);

    vout = v_xor(vout, pvmask[i]);
    vout = v_sub(vout, pvmask[i]);

    pcschannel[i] = vout;
  }

  for (i = 9; i < 16; i++)
  {
    v_cs& vin = (v_cs&)pcsin[i];
    int sqr;
    vsqr = vin.v_sqr2i();

    vin.v_convert2ci((v_ci&)vciinput1, (v_ci&)vciinput2);

    vciinput1 = vciinput1.v_shift_left(16);
    vciinput2 = vciinput2.v_shift_left(16);

    vsqrtemp = vsqr.v_shift_right_arithmetic(1);

    vciinput1 = v_add(vciinput1, vsqrtemp);
    vciinput2 = v_add(vciinput2, vsqrtemp);

    sqr = vsqr.v_get_at<0>();
    if (sqr == 0) sqr = 1;
    v = vciinput1.v_get_at<0>() / sqr;
    vciinput1.v_set_at<0>( v );

    v = vciinput1.v_get_at<1>() / sqr;
    vciinput1.v_set_at<1>( v );

    sqr = vsqr.v_get_at<1>();
    if (sqr == 0) sqr = 1;
    v = vciinput1.v_get_at<2>() / sqr;
    vciinput1.v_set_at<2>( v );

    v = vciinput1.v_get_at<3>() / sqr;
    vciinput1.v_set_at<3>( v );

    sqr = vsqr.v_get_at<2>();
    if (sqr == 0) sqr = 1;
    v = vciinput2.v_get_at<0>() / sqr;
    vciinput2.v_set_at<0>( v );

    v = vciinput2.v_get_at<1>() / sqr;
    vciinput2.v_set_at<1>( v );

    sqr = vsqr.v_get_at<3>();
    if (sqr == 0) sqr = 1;
    v = vciinput2.v_get_at<2>() / sqr;
    vciinput2.v_set_at<2>( v );

    v = vciinput2.v_get_at<3>() / sqr;
    vciinput2.v_set_at<3>( v );

    vout = v_convert2cs((v_ci&)vciinput1, (v_ci&)vciinput2);

    vout = v_xor(vout, pvmask[i]);
    vout = v_sub(vout, pvmask[i]);

    pcschannel[i] = vout;
  }
}




typedef Array<v_cs, 16> Dot11aChannelCoefficient;

DEFINE_BLOCK(b_dot11_siso_channel_estimator_1v, 1, 0)
{
  _global_(Dot11aChannelCoefficient, dot11a_siso_channel);

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 32) return false;

    auto ip = _$<v_cs>(0);

    log("%s: n=%d\n", name(), n);

    auto ch = *dot11a_siso_channel;
    
    v_siso_channel_estimation_64(ip, (v_cs*)&ch[0]);

    consume(0, 32);
    return true;
  }
};

//////////////////////////////////////////////////////////////////////////

DEFINE_BLOCK(b_dot11_siso_channel_estimator_2v, 2, 0)
{
  _global_(Dot11aChannelCoefficient, dot11a_siso_channel_1);
  _global_(Dot11aChannelCoefficient, dot11a_siso_channel_2);
  Dot11aChannelCoefficient siso_channel_1;
  Dot11aChannelCoefficient siso_channel_2;

  dsp_draw_window* m_draw;

  BLOCK_INIT
  {
    m_draw = new dsp_draw_window("dot11 siso channel estimator", 0, 0, 400, 400);
  }

  BLOCK_WORK
  {
    trace();
    auto n = ninput(0);
    if (n < 32) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);

    m_draw->DrawSqrtShift((complex16*)ip1, 32 * 4);
    
    autoref ch1  = *dot11a_siso_channel_1;
    
    v_siso_channel_estimation_64(ip1, (v_cs*)&siso_channel_1[0]);
    v_siso_channel_estimation_64(ip1 + 16, (v_cs*)&siso_channel_2[0]);
    
#if 1
    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      ch1[i]  = r.v_shift_right_arithmetic(1);
    }
#else
    for (int i = 0; i < 16; i++)
    {
      ch1[i]  = siso_channel_1[i];
    }
#endif

    autoref ch2  = *dot11a_siso_channel_2;

    v_siso_channel_estimation_64(ip2, (v_cs*)&siso_channel_1[0]);
    v_siso_channel_estimation_64(ip2 + 16, (v_cs*)&siso_channel_2[0]);
#if 1
    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      ch2[i]  = r.v_shift_right_arithmetic(1);
    }
#else
    for (int i = 0; i < 16; i++)
    {
      ch2[i]  = siso_channel_1[i];
    }
#endif

    consume(0, 32);
    consume(1, 32);
    return true;
  }
};