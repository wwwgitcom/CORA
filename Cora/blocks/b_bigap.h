#pragma once


DEFINE_BLOCK(b_bigap_lltf_tx_v1, 0, 1)
{
  HT_LTF _lltf;

  BLOCK_WORK
  {
    auto op = $_<dot11n_tx_symbol>(0);

    _lltf.get_as_lltf(op->data);

    produce(0, 2);

    return true;
  }
};

DEFINE_BLOCK(b_bigap_dummy_lltf_tx_v1, 0, 1)
{
  BLOCK_WORK
  {
    auto op = $_<dot11n_tx_symbol>(0);

    op->zero();
    op++;
    op->zero();
    op++;
    op->zero();

    produce(0, 3);

    return true;
  }
};


#define BIGAP_LTF_0 0x0000FFFF
#define BIGAP_LTF_1 0xFFFF0000

__declspec(selectany) v_align(16) v_cs::type _bigap_LTFMask[16] =
{
  //0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
  { BIGAP_LTF_0, BIGAP_LTF_1, BIGAP_LTF_0, BIGAP_LTF_0 },
  { BIGAP_LTF_1, BIGAP_LTF_1, BIGAP_LTF_0, BIGAP_LTF_1 },
  { BIGAP_LTF_0, BIGAP_LTF_1, BIGAP_LTF_0, BIGAP_LTF_0 },
  { BIGAP_LTF_0, BIGAP_LTF_0, BIGAP_LTF_0, BIGAP_LTF_1 },

  //1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  { BIGAP_LTF_1, BIGAP_LTF_0, BIGAP_LTF_0, BIGAP_LTF_1 },
  { BIGAP_LTF_0, BIGAP_LTF_1, BIGAP_LTF_0, BIGAP_LTF_1 },
  { BIGAP_LTF_1, BIGAP_LTF_1, BIGAP_LTF_1, BIGAP_LTF_0 },
  { BIGAP_LTF_0, BIGAP_LTF_0, BIGAP_LTF_0, BIGAP_LTF_0 },

  //0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1,
  { BIGAP_LTF_0, BIGAP_LTF_0, BIGAP_LTF_0, BIGAP_LTF_0 },
  { BIGAP_LTF_1, BIGAP_LTF_1, BIGAP_LTF_1, BIGAP_LTF_1 },
  { BIGAP_LTF_0, BIGAP_LTF_0, BIGAP_LTF_1, BIGAP_LTF_1 },
  { BIGAP_LTF_0, BIGAP_LTF_1, BIGAP_LTF_0, BIGAP_LTF_1 },

  //1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1
  { BIGAP_LTF_1, BIGAP_LTF_1, BIGAP_LTF_1, BIGAP_LTF_1 },
  { BIGAP_LTF_1, BIGAP_LTF_0, BIGAP_LTF_0, BIGAP_LTF_1 },
  { BIGAP_LTF_1, BIGAP_LTF_0, BIGAP_LTF_1, BIGAP_LTF_0 },
  { BIGAP_LTF_1, BIGAP_LTF_1, BIGAP_LTF_1, BIGAP_LTF_1 }
};


DEFINE_BLOCK(b_bigap_lltf_rx_4v, 4, 0)
{
  _global_(MIMO_4x4_H, bigap_4x4_H);
  _local_(int, state, 0);

  Dot11aChannelCoefficient siso_channel_1;
  Dot11aChannelCoefficient siso_channel_2;

  v_cs fft_buffer[2][16];
  v_cs noise_buffer[4];
  v_i  h_power[4][16];
  v_i  n_power[4];

  BLOCK_INIT
  {
    for each (v_cs& var in noise_buffer)
    {
      var.v_zero();
    }
    for each (v_i& var in n_power)
    {
      var.v_zero();
    }
  }


  BLOCK_RESET
  {
    *state = 0;
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);

    int  nwait = 32;
    if (*state > 0)
    {
      nwait += 8;
    }

    if (n < nwait) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    v_cs *pvmask = (v_cs*)&_bigap_LTFMask[0];

    if (*state > 0)
    {
      ip1 += 8;
      ip2 += 8;
      ip3 += 8;
      ip4 += 8;
    }

    short delta1 = v_estimate_i(ip1, 16, 16);
    short delta2 = v_estimate_i(ip2, 16, 16);
    short delta3 = v_estimate_i(ip3, 16, 16);
    short delta4 = v_estimate_i(ip4, 16, 16);

    printf("BigAP::%d::f1=%d, f2=%d, f3=%d, f4=%d\n", 
      *state, delta1, delta2, delta3, delta4);

    autoref ch  = *bigap_4x4_H;
    // 1
    FFT<64>((vcs*)ip1, (vcs*)fft_buffer[0]);
    v_siso_channel_estimation_64(fft_buffer[0], pvmask, (v_cs*)&siso_channel_1[0]);
    FFT<64>((vcs*)(ip1 + 16), (vcs*)fft_buffer[1]);
    v_siso_channel_estimation_64(fft_buffer[1], pvmask, (v_cs*)&siso_channel_2[0]);
    
    fft_buffer[0][0][0]._r = 0;
    fft_buffer[1][0][0]._r = 0;
    // average
    v_cs* pvcs = (v_cs*)&ch[0][*state * 64];
    v_cs  vnoise;
    vnoise.v_zero();
    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      pvcs[i]  = r.v_shift_right_arithmetic(1);

      v_cs h = v_add(fft_buffer[0][i], fft_buffer[1][i]).v_shift_right_arithmetic(1);
      v_i  hp = h.v_sqr2i();
      h_power[0][i] = v_add(h_power[0][i], hp);

      vnoise = v_add(vnoise, v_sub(fft_buffer[0][i], fft_buffer[1][i]));
    }
    vnoise = vnoise.v_hsums().v_shift_right_arithmetic(4);

    noise_buffer[0] = (v_cs&)v_max((v_s&)vnoise, (v_s&)noise_buffer[0]);

#if enable_dbgplot
    int Spectrum[64];
    char title[128];
    Spectrum[0] = 0;
#endif

#if enable_dbgplot
    for (int i = 1; i < 64; i++)
    {
      Spectrum[i] = ch[0][*state * 64 + i].sqr2();
    }

    memset(title, 0, 128);
    sprintf_s(title, 128, "channel %d : 1", *state);
    PlotSpectrum(title, Spectrum, 64);
#endif


    // 2
    FFT<64>((vcs*)ip2, (vcs*)fft_buffer[0]);
    v_siso_channel_estimation_64(fft_buffer[0], pvmask, (v_cs*)&siso_channel_1[0]);
    FFT<64>((vcs*)(ip2 + 16), (vcs*)fft_buffer[1]);
    v_siso_channel_estimation_64(fft_buffer[1], pvmask, (v_cs*)&siso_channel_2[0]);
    
    fft_buffer[0][0][0]._r = 0;
    fft_buffer[1][0][0]._r = 0;

    pvcs = (v_cs*)&ch[1][*state * 64];
    vnoise.v_zero();

    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      pvcs[i]  = r.v_shift_right_arithmetic(1);

      v_cs h = v_add(fft_buffer[0][i], fft_buffer[1][i]).v_shift_right_arithmetic(1);
      v_i  hp = h.v_sqr2i();
      h_power[1][i] = v_add(h_power[1][i], hp);

      vnoise = v_add(vnoise, v_sub(fft_buffer[0][i], fft_buffer[1][i]));
    }
    vnoise = vnoise.v_hsums().v_shift_right_arithmetic(4);

    noise_buffer[1] = (v_cs&)v_max((v_s&)vnoise, (v_s&)noise_buffer[1]);

#if enable_dbgplot
    for (int i = 1; i < 64; i++)
    {
      Spectrum[i] = ch[1][*state * 64 + i].sqr2();
    }

    memset(title, 0, 128);
    sprintf_s(title, 128, "channel %d : 2", *state);
    PlotSpectrum(title, Spectrum, 64);
#endif

    // 3
    FFT<64>((vcs*)ip3, (vcs*)fft_buffer[0]);
    v_siso_channel_estimation_64(fft_buffer[0], pvmask, (v_cs*)&siso_channel_1[0]);
    FFT<64>((vcs*)(ip3 + 16), (vcs*)fft_buffer[1]);
    v_siso_channel_estimation_64(fft_buffer[1], pvmask, (v_cs*)&siso_channel_2[0]);

    fft_buffer[0][0][0]._r = 0;
    fft_buffer[1][0][0]._r = 0;

    pvcs = (v_cs*)&ch[2][*state * 64];
    vnoise.v_zero();
    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      pvcs[i]  = r.v_shift_right_arithmetic(1);

      v_cs h = v_add(fft_buffer[0][i], fft_buffer[1][i]).v_shift_right_arithmetic(1);
      v_i  hp = h.v_sqr2i();
      h_power[2][i] = v_add(h_power[2][i], hp);

      vnoise = v_add(vnoise, v_sub(fft_buffer[0][i], fft_buffer[1][i]));
    }
    vnoise = vnoise.v_hsums().v_shift_right_arithmetic(4);

    noise_buffer[2] = (v_cs&)v_max((v_s&)vnoise, (v_s&)noise_buffer[2]);
    
#if enable_dbgplot
    for (int i = 1; i < 64; i++)
    {
      Spectrum[i] = ch[2][*state * 64 + i].sqr2();
    }

    memset(title, 0, 128);
    sprintf_s(title, 128, "channel %d : 3", *state);
    PlotSpectrum(title, Spectrum, 64);
#endif
    // 4
    FFT<64>((vcs*)ip4, (vcs*)fft_buffer[0]);
    v_siso_channel_estimation_64(fft_buffer[0], pvmask, (v_cs*)&siso_channel_1[0]);
    FFT<64>((vcs*)(ip4 + 16), (vcs*)fft_buffer[1]);
    v_siso_channel_estimation_64(fft_buffer[1], pvmask, (v_cs*)&siso_channel_2[0]);

    fft_buffer[0][0][0]._r = 0;
    fft_buffer[1][0][0]._r = 0;

    pvcs = (v_cs*)&ch[3][*state * 64];
    vnoise.v_zero();

    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      pvcs[i]  = r.v_shift_right_arithmetic(1);

      v_cs h = v_add(fft_buffer[0][i], fft_buffer[1][i]).v_shift_right_arithmetic(1);
      v_i  hp = h.v_sqr2i();
      h_power[3][i] = v_add(h_power[3][i], hp);

      vnoise = v_add(vnoise, v_sub(fft_buffer[0][i], fft_buffer[1][i]));
    }
    vnoise = vnoise.v_hsums().v_shift_right_arithmetic(4);

    noise_buffer[3] = (v_cs&)v_max((v_s&)vnoise, (v_s&)noise_buffer[3]);

#if enable_dbgplot
    for (int i = 1; i < 64; i++)
    {
      Spectrum[i] = ch[3][*state * 64 + i].sqr2();
    }

    memset(title, 0, 128);
    sprintf_s(title, 128, "channel %d : 4", *state);
    PlotSpectrum(title, Spectrum, 64);
#endif

    (*state) += 1;

    if (*state == 4)
    {
      *state = 0;

      //////////////////////////////////////////////////////////////////////////
      // calc. noise power according to the maximum noise variance
      for (int i = 0; i < 4; i++)
      {
        n_power[i] = noise_buffer[i].v_sqr2i();
      }

      for (int n = 0; n < 4; n++)
      {
        int32* php = (int32*)&h_power[n];
        int32* pnp = (int32*)&n_power[n];
        PlotText("SNR", "Antenna %d ===hpower vs npower---\n", n);
        for (int i = 0; i < 64; i++)
        {
          PlotText("SNR", "sc_%2d: \t %d \t %d \t SNR = %f dB\n", i, 
            php[i], pnp[n] + 1, 10.0 * log10(php[i] * 1.0 / (pnp[n] + 1)));
        }
      }
      



      // reset 
      for each (v_cs& var in noise_buffer)
      {
        var.v_zero();
      }
      for each (v_i& var in h_power)
      {
        var.v_zero();
      }

    }

    consume_each(nwait);
    return true;
  }
};

DEFINE_BLOCK(b_bigap_siso_channel_compensator_4v4, 4, 4)
{
  _global_(MIMO_4x4_H, bigap_4x4_H);
  _local_(int, state, 0);

  v_cs vmask;

  BLOCK_INIT
  {
    vmask = VMASK::__0x80000001800000018000000180000001<v_cs>();
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 16) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    auto op1 = $_<v_cs>(0);
    auto op2 = $_<v_cs>(1);
    auto op3 = $_<v_cs>(2);
    auto op4 = $_<v_cs>(3);

    autoref ch  = *bigap_4x4_H;

    v_ci vciout1, vciout2;

    v_cs* channel_factor1 = (v_cs*)&ch[0][*state * 64];

    for (int i = 0; i < 16; i++)
    {
      v_cs &vin   = (v_cs &)ip1[i];
      v_cs &vcof  = (v_cs &)channel_factor1[i];
      v_cs &vout  = (v_cs &)op1[i];

      v_mul2ci(vin, vcof, vmask, vciout1, vciout2);

      vciout1 = vciout1.v_shift_right_arithmetic(9);
      vciout2 = vciout2.v_shift_right_arithmetic(9);

      vout        = v_convert2cs(vciout1, vciout2);
    }

    v_cs* channel_factor2 = (v_cs*)&ch[1][*state * 64];

    for (int i = 0; i < 16; i++)
    {
      v_cs &vin   = (v_cs &)ip2[i];
      v_cs &vcof  = (v_cs &)channel_factor2[i];
      v_cs &vout  = (v_cs &)op2[i];

      v_mul2ci(vin, vcof, vmask, vciout1, vciout2);

      vciout1 = vciout1.v_shift_right_arithmetic(9);
      vciout2 = vciout2.v_shift_right_arithmetic(9);

      vout        = v_convert2cs(vciout1, vciout2);
    }

    v_cs* channel_factor3 = (v_cs*)&ch[2][*state * 64];

    for (int i = 0; i < 16; i++)
    {
      v_cs &vin   = (v_cs &)ip3[i];
      v_cs &vcof  = (v_cs &)channel_factor3[i];
      v_cs &vout  = (v_cs &)op3[i];

      v_mul2ci(vin, vcof, vmask, vciout1, vciout2);

      vciout1 = vciout1.v_shift_right_arithmetic(9);
      vciout2 = vciout2.v_shift_right_arithmetic(9);

      vout        = v_convert2cs(vciout1, vciout2);
    }

    v_cs* channel_factor4 = (v_cs*)&ch[3][*state * 64];

    for (int i = 0; i < 16; i++)
    {
      v_cs &vin   = (v_cs &)ip4[i];
      v_cs &vcof  = (v_cs &)channel_factor4[i];
      v_cs &vout  = (v_cs &)op4[i];

      v_mul2ci(vin, vcof, vmask, vciout1, vciout2);

      vciout1 = vciout1.v_shift_right_arithmetic(9);
      vciout2 = vciout2.v_shift_right_arithmetic(9);

      vout        = v_convert2cs(vciout1, vciout2);
    }

    *state = (*state + 1) % 4;

    consume_each(16);
    produce_each(16);

    return true;
  }
};



DEFINE_BLOCK(b_bigap_4x4_noise_estimator_4v, 4, 0)
{
  _global_(MIMO_4x4_H_f, dot11n_4x4_noise_var);
  _local_(int, state, 0);

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 16) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    complex16* ipc[4] = {(complex16*)ip1, (complex16*)ip2, (complex16*)ip3, (complex16*)ip4};

    MIMO_4x4_H_f &noise_matrix = *dot11n_4x4_noise_var;

    complexd noise;
    complexd norm(128.0f, 0.0f);
    double   normsqr = norm.sqr();

    memset(&noise_matrix[*state][0], 0, sizeof(MIMO_4x4_H_f) / 4);

    //for (int k = 0; k < 4; k++)
    int k = *state;
    {
      for (int i = 0; i < 64; i++)
      {
        if (i == 0 || (i > 26 && i < 64 - 26))
        {
          continue;
        }

        complexd cf;
        cf.re = dsp_math::abs(ipc[k][i].re);
        cf.im = dsp_math::abs(ipc[k][i].im);
        noise = cf - norm;

        double noise_energy = noise.sqr();
#if 0
        double snr = 10 * log10f(normsqr / noise_energy);
        printf("snr_%d@%d: %f dB\n", k, i, snr);
#endif
        //noise_matrix[k][k * 64 + i].re = noise_energy / normsqr;
        noise_matrix[k][k * 64 + i].re = noise_energy;
        noise_matrix[k][k * 64 + i].im = 0.0f;
      }

      noise_matrix[k][k * 64 + 27] = noise_matrix[k][k * 64 + 26];
      noise_matrix[k][k * 64 + 28] = noise_matrix[k][k * 64 + 26];
      noise_matrix[k][k * 64 + 64 - 27] = noise_matrix[k][k * 64 + 64 - 26];
      noise_matrix[k][k * 64 + 64 - 28] = noise_matrix[k][k * 64 + 64 - 26];
    }

    *state = (*state + 1) % 4;

    return true;
  }
};




DEFINE_BLOCK(b_bigap_channel_compensator_4v4, 4, 4)
{
  _global_(MIMO_4x4_H, bigap_4x4_H);
  // feedback phase later

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 16) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    auto ipc1 = reinterpret_cast<complex16*>(ip1);
    auto ipc2 = reinterpret_cast<complex16*>(ip2);
    auto ipc3 = reinterpret_cast<complex16*>(ip3);
    auto ipc4 = reinterpret_cast<complex16*>(ip4);

    auto op1 = $_<v_cs>(0);
    auto op2 = $_<v_cs>(1);
    auto op3 = $_<v_cs>(2);
    auto op4 = $_<v_cs>(3);

    auto opc1 = reinterpret_cast<complex16*>(op1);
    auto opc2 = reinterpret_cast<complex16*>(op2);
    auto opc3 = reinterpret_cast<complex16*>(op3);
    auto opc4 = reinterpret_cast<complex16*>(op4);

    MIMO_4x4_H& H_Inv = *bigap_4x4_H;

    const v_cs vMulMask = VMASK::__0x80000001800000018000000180000001<v_cs>();
    v_ci vcomp1[2], vcomp2[2], vcomp3[2], vcomp4[2];

    for (int i = 0; i < 64; i += 4)
    {
      v_cs &vinvh11 = (v_cs&)H_Inv[0][i];
      v_cs &vinvh12 = (v_cs&)H_Inv[0][i + 64];
      v_cs &vinvh13 = (v_cs&)H_Inv[0][i + 128];
      v_cs &vinvh14 = (v_cs&)H_Inv[0][i + 192];

      v_cs &vinvh21 = (v_cs&)H_Inv[1][i];
      v_cs &vinvh22 = (v_cs&)H_Inv[1][i + 64];
      v_cs &vinvh23 = (v_cs&)H_Inv[1][i + 128];
      v_cs &vinvh24 = (v_cs&)H_Inv[1][i + 192];

      v_cs &vinvh31 = (v_cs&)H_Inv[2][i];
      v_cs &vinvh32 = (v_cs&)H_Inv[2][i + 64];
      v_cs &vinvh33 = (v_cs&)H_Inv[2][i + 128];
      v_cs &vinvh34 = (v_cs&)H_Inv[2][i + 192];

      v_cs &vinvh41 = (v_cs&)H_Inv[3][i];
      v_cs &vinvh42 = (v_cs&)H_Inv[3][i + 64];
      v_cs &vinvh43 = (v_cs&)H_Inv[3][i + 128];
      v_cs &vinvh44 = (v_cs&)H_Inv[3][i + 192];

      v_cs &y1      = (v_cs&)ipc1[i];
      v_cs &y2      = (v_cs&)ipc2[i];
      v_cs &y3      = (v_cs&)ipc3[i];
      v_cs &y4      = (v_cs&)ipc4[i];

      v_cs& x1      = (v_cs&)opc1[i];
      v_cs& x2      = (v_cs&)opc2[i];
      v_cs& x3      = (v_cs&)opc3[i];
      v_cs& x4      = (v_cs&)opc4[i];


#define compression_shift_1 5
#define compression_shift_2 6
#define compression_shift_3 7
#define compression_shift_4 8

      
      y1 = y1.v_shift_right_logical(compression_shift_1);
      y1 = y1.v_shift_left(compression_shift_1);
      y2 = y2.v_shift_right_logical(compression_shift_2);
      y2 = y2.v_shift_left(compression_shift_2);
      y3 = y3.v_shift_right_logical(compression_shift_3);
      y3 = y3.v_shift_left(compression_shift_3);
      y4 = y4.v_shift_right_logical(compression_shift_4);
      y4 = y4.v_shift_left(compression_shift_4);

      // x1
      v_mul2ci(vinvh11, y1, vMulMask, vcomp1[0], vcomp1[1]);
      v_mul2ci(vinvh12, y2, vMulMask, vcomp2[0], vcomp2[1]);
      v_mul2ci(vinvh13, y3, vMulMask, vcomp3[0], vcomp3[1]);
      v_mul2ci(vinvh14, y4, vMulMask, vcomp4[0], vcomp4[1]);

      vcomp1[0] = v_add(v_add(vcomp1[0], vcomp2[0]), v_add(vcomp3[0], vcomp4[0]));
      vcomp1[1] = v_add(v_add(vcomp1[1], vcomp2[1]), v_add(vcomp3[1], vcomp4[1]));

      vcomp1[0] = vcomp1[0].v_shift_right_arithmetic(9);
      vcomp1[1] = vcomp1[1].v_shift_right_arithmetic(9);

      x1 = v_convert2cs(vcomp1[0], vcomp1[1]);

      // x2
      v_mul2ci(vinvh21, y1, vMulMask, vcomp1[0], vcomp1[1]);
      v_mul2ci(vinvh22, y2, vMulMask, vcomp2[0], vcomp2[1]);
      v_mul2ci(vinvh23, y3, vMulMask, vcomp3[0], vcomp3[1]);
      v_mul2ci(vinvh24, y4, vMulMask, vcomp4[0], vcomp4[1]);

      vcomp1[0] = v_add(v_add(vcomp1[0], vcomp2[0]), v_add(vcomp3[0], vcomp4[0]));
      vcomp1[1] = v_add(v_add(vcomp1[1], vcomp2[1]), v_add(vcomp3[1], vcomp4[1]));

      vcomp1[0] = vcomp1[0].v_shift_right_arithmetic(9);
      vcomp1[1] = vcomp1[1].v_shift_right_arithmetic(9);

      x2 = v_convert2cs(vcomp1[0], vcomp1[1]);

      // x3
      v_mul2ci(vinvh31, y1, vMulMask, vcomp1[0], vcomp1[1]);
      v_mul2ci(vinvh32, y2, vMulMask, vcomp2[0], vcomp2[1]);
      v_mul2ci(vinvh33, y3, vMulMask, vcomp3[0], vcomp3[1]);
      v_mul2ci(vinvh34, y4, vMulMask, vcomp4[0], vcomp4[1]);

      vcomp1[0] = v_add(v_add(vcomp1[0], vcomp2[0]), v_add(vcomp3[0], vcomp4[0]));
      vcomp1[1] = v_add(v_add(vcomp1[1], vcomp2[1]), v_add(vcomp3[1], vcomp4[1]));

      vcomp1[0] = vcomp1[0].v_shift_right_arithmetic(9);
      vcomp1[1] = vcomp1[1].v_shift_right_arithmetic(9);

      x3 = v_convert2cs(vcomp1[0], vcomp1[1]);

      // x4
      v_mul2ci(vinvh41, y1, vMulMask, vcomp1[0], vcomp1[1]);
      v_mul2ci(vinvh42, y2, vMulMask, vcomp2[0], vcomp2[1]);
      v_mul2ci(vinvh43, y3, vMulMask, vcomp3[0], vcomp3[1]);
      v_mul2ci(vinvh44, y4, vMulMask, vcomp4[0], vcomp4[1]);

      vcomp1[0] = v_add(v_add(vcomp1[0], vcomp2[0]), v_add(vcomp3[0], vcomp4[0]));
      vcomp1[1] = v_add(v_add(vcomp1[1], vcomp2[1]), v_add(vcomp3[1], vcomp4[1]));

      vcomp1[0] = vcomp1[0].v_shift_right_arithmetic(9);
      vcomp1[1] = vcomp1[1].v_shift_right_arithmetic(9);

      x4 = v_convert2cs(vcomp1[0], vcomp1[1]);
    }

#if enable_dbgplot
    opc1[0] = opc2[0] = opc3[0] = opc4[0] = 0;
    for (int i = 29; i < 64 - 28; i++)
    {
      opc1[i] = opc2[i] = opc3[i] = opc4[i] = 0;
    }
    PlotDots("X1", opc1, 64);
    PlotDots("X2", opc2, 64);
    PlotDots("X3", opc3, 64);
    PlotDots("X4", opc4, 64);
#endif

    consume_each(16);
    produce_each(16);
    return true;
  }
};

//////////////////////////////////////////////////////////////////////////



enum bigap_msg_type
{
  config = 0xABCD0001,
  data   = 0xABCD0002
};

struct _bigap_config_msg
{
  v_cs   channel[4][64];
  bool   frame1_ok;
  uint32 frame1_rate;
  uint32 frame1_length;
  bool   frame2_ok;
  uint32 frame2_rate;
  uint32 frame2_length;
  bool   frame3_ok;
  uint32 frame3_rate;
  uint32 frame3_length;
  bool   frame4_ok;
  uint32 frame4_rate;
  uint32 frame4_length;  
};

struct _bigap_data_msg
{
  v_cs data[4][16];
};

struct bigap_msg_hdr
{
  uint32 type;
  uint32 seq;
  uint32 length;
};

struct bigap_config_msg 
{
  uint32 type;
  uint32 seq;
  uint32 length;
  _bigap_config_msg msg;

  bigap_config_msg()
  {
    type   = bigap_msg_type::config;
    seq    = 0;
    length = sizeof(bigap_config_msg);
  }
};

struct bigap_data_msg 
{
  uint32 type;
  uint32 seq;
  uint32 length;
  _bigap_data_msg msg;

  bigap_data_msg()
  {
    type   = bigap_msg_type::data;
    seq    = 0;
    length = sizeof(bigap_data_msg);
  }
};


INHERIT_BLOCK(b_bigap_sink_4v, b_tcp_socket_sink_4v)
{
  bigap_data_msg data_msg;

  _local_(int, send_count, 0);

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 16) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    CopyMemory(&data_msg.msg.data[0], ip1, sizeof(v_cs) * 16);
    CopyMemory(&data_msg.msg.data[1], ip2, sizeof(v_cs) * 16);
    CopyMemory(&data_msg.msg.data[2], ip3, sizeof(v_cs) * 16);
    CopyMemory(&data_msg.msg.data[3], ip4, sizeof(v_cs) * 16);

#if 0
    complex16 (*pc)[64] = (complex16 (*)[64])data_msg.msg.data;

    printf("\n-------\n");
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 64; j++)
      {
        printf("%d, %d \t ", pc[i][j].re, pc[i][j].im);
      }
      printf("\n");
    }
#endif

    data_msg.seq++;

    printf("%d: Send data msg... seq = %d\n", (*send_count)++, data_msg.seq);

    consume_each(16);
    //getchar();
    bool bRet = SendData((uint8*)&data_msg, sizeof(data_msg));
    //Sleep(1000);
    return bRet;
  }
};

INHERIT_BLOCK(b_bigap_source_v4, b_tcp_socket_source_v4)
{
  _global_(bigap_config_msg, config_msg);
  _global_(MIMO_4x4_H, bigap_4x4_H);

  uint8 rcvbuf[4016];
  _local_(int, recv_count, 0);

  static const int recvbuflen = 1040;//sizeof(bigap_config_msg);

  int recv_state;
  int recv_symbol_count;

  BLOCK_INIT
  {
    b_tcp_socket_source_v4::_init_($);
    recv_state = 0;
    recv_symbol_count = 0;
  }

  BLOCK_WORK
  {
    int32 recvedLen;

    if (recv_state == 0)
    {
      autoref msg = *config_msg;
      autoref ch  = *bigap_4x4_H;

      if ( !RecvData((uint8*)config_msg.p_var, sizeof(bigap_config_msg), &recvedLen) ) return false;

      bigap_msg_hdr* hdr = reinterpret_cast<bigap_msg_hdr*>(config_msg.p_var);

      printf("Recv::msg::config, len=%d\n", hdr->length);

      memcpy(&ch[0], &msg.msg.channel[0], sizeof(MIMO_4x4_H));

      int VitTotalBits;
      int symbol_count = pht_symbol_count((*config_msg).msg.frame1_rate, (*config_msg).msg.frame1_length, &VitTotalBits);
      recv_symbol_count = max(symbol_count, recv_symbol_count);

      symbol_count = pht_symbol_count((*config_msg).msg.frame2_rate, (*config_msg).msg.frame2_length, &VitTotalBits);
      recv_symbol_count = max(symbol_count, recv_symbol_count);

      symbol_count = pht_symbol_count((*config_msg).msg.frame3_rate, (*config_msg).msg.frame3_length, &VitTotalBits);
      recv_symbol_count = max(symbol_count, recv_symbol_count);

      symbol_count = pht_symbol_count((*config_msg).msg.frame4_rate, (*config_msg).msg.frame4_length, &VitTotalBits);
      recv_symbol_count = max(symbol_count, recv_symbol_count);

      recv_state = 1;
    }
    else if (recv_state == 1)
    {
      auto op1 = $_<v_cs>(0);
      auto op2 = $_<v_cs>(1);
      auto op3 = $_<v_cs>(2);
      auto op4 = $_<v_cs>(3);

      bigap_data_msg* data_msg = reinterpret_cast<bigap_data_msg*>(config_msg.p_var);

      if ( !RecvData((uint8*)config_msg.p_var, sizeof(bigap_data_msg), &recvedLen) ) return false;

      printf("Recv::msg::data, seq=%d\n", data_msg->seq);

      memcpy(op1, &data_msg->msg.data[0], 16 * sizeof(v_cs));
      memcpy(op2, &data_msg->msg.data[1], 16 * sizeof(v_cs));
      memcpy(op3, &data_msg->msg.data[2], 16 * sizeof(v_cs));
      memcpy(op4, &data_msg->msg.data[3], 16 * sizeof(v_cs));

      produce_each(16);

      recv_symbol_count--;
      if (recv_symbol_count <= 0)
      {
        recv_state = 0;
      }
    }

    return true;
  }
};

//////////////////////////////////////////////////////////////////////////


#include "b_bigap_4x4_tx.h"
#include "b_bigap_4x4_rx.h"