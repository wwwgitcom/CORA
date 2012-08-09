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

  v_cs fft_buffer[16];

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
    FFT<64>((vcs*)ip1, (vcs*)fft_buffer);
    v_siso_channel_estimation_64(fft_buffer, pvmask, (v_cs*)&siso_channel_1[0]);
    FFT<64>((vcs*)(ip1 + 16), (vcs*)fft_buffer);
    v_siso_channel_estimation_64(fft_buffer, pvmask, (v_cs*)&siso_channel_2[0]);

    // average
    v_cs* pvcs = (v_cs*)&ch[0][*state * 64];
    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      pvcs[i]  = r.v_shift_right_arithmetic(1);
    }

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
    FFT<64>((vcs*)ip2, (vcs*)fft_buffer);
    v_siso_channel_estimation_64(fft_buffer, pvmask, (v_cs*)&siso_channel_1[0]);
    FFT<64>((vcs*)(ip2 + 16), (vcs*)fft_buffer);
    v_siso_channel_estimation_64(fft_buffer, pvmask, (v_cs*)&siso_channel_2[0]);

    pvcs = (v_cs*)&ch[1][*state * 64];
    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      pvcs[i]  = r.v_shift_right_arithmetic(1);
    }
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
    FFT<64>((vcs*)ip3, (vcs*)fft_buffer);
    v_siso_channel_estimation_64(fft_buffer, pvmask, (v_cs*)&siso_channel_1[0]);
    FFT<64>((vcs*)(ip3 + 16), (vcs*)fft_buffer);
    v_siso_channel_estimation_64(fft_buffer, pvmask, (v_cs*)&siso_channel_2[0]);

    pvcs = (v_cs*)&ch[2][*state * 64];
    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      pvcs[i]  = r.v_shift_right_arithmetic(1);
    }

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
    FFT<64>((vcs*)ip4, (vcs*)fft_buffer);
    v_siso_channel_estimation_64(fft_buffer, pvmask, (v_cs*)&siso_channel_1[0]);
    FFT<64>((vcs*)(ip4 + 16), (vcs*)fft_buffer);
    v_siso_channel_estimation_64(fft_buffer, pvmask, (v_cs*)&siso_channel_2[0]);

    pvcs = (v_cs*)&ch[3][*state * 64];
    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      pvcs[i]  = r.v_shift_right_arithmetic(1);
    }

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
    }

    //consume_each(32);
    return true;
  }
};


#include "b_bigap_4x4_tx.h"
#include "b_bigap_4x4_rx.h"