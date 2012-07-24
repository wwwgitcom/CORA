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
  _global_(Dot11aChannelCoefficient, dot11a_siso_channel);
  _global_(MIMO_4x4_H, bigap_4x4_H);
  _local_(int, state, 0);

  Dot11aChannelCoefficient siso_channel_1;
  Dot11aChannelCoefficient siso_channel_2;

  BLOCK_RESET
  {
    *state = 0;
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 32) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    v_cs *pvmask = (v_cs*)&_bigap_LTFMask[0];
    
    short delta1 = v_estimate_i(ip1, 16, 16);
    short delta2 = v_estimate_i(ip2, 16, 16);
    short delta3 = v_estimate_i(ip3, 16, 16);
    short delta4 = v_estimate_i(ip4, 16, 16);

    printf("f%d1=%d, f%d1=%d, f%d1=%d, f%d1=%d\n", 
      *state, delta1, *state, delta2, *state, delta3, *state, delta4);

    autoref ch  = *bigap_4x4_H;
    // 1
    v_siso_channel_estimation_64(ip1, pvmask, (v_cs*)&siso_channel_1[0]);
    v_siso_channel_estimation_64(ip1 + 16, pvmask, (v_cs*)&siso_channel_2[0]);

    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      ch[0][*state * 16 + i]  = r.v_shift_right_arithmetic(1);
    }
    if (*state == 0)
    {
      memcpy(&(*dot11a_siso_channel)[0], &ch[0][*state * 16], sizeof(v_cs) * 16);
    }

    // 2
    v_siso_channel_estimation_64(ip2, pvmask, (v_cs*)&siso_channel_1[0]);
    v_siso_channel_estimation_64(ip2 + 16, pvmask, (v_cs*)&siso_channel_2[0]);

    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      ch[1][*state * 16 + i]  = r.v_shift_right_arithmetic(1);
    }

    if (*state == 1)
    {
      memcpy(&(*dot11a_siso_channel)[0], &ch[1][*state * 16], sizeof(v_cs) * 16);
    }

    // 3
    v_siso_channel_estimation_64(ip3, pvmask, (v_cs*)&siso_channel_1[0]);
    v_siso_channel_estimation_64(ip3 + 16, pvmask, (v_cs*)&siso_channel_2[0]);

    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      ch[1][*state * 16 + i]  = r.v_shift_right_arithmetic(1);
    }
    if (*state == 2)
    {
      memcpy(&(*dot11a_siso_channel)[0], &ch[2][*state * 16], sizeof(v_cs) * 16);
    }
    // 4
    v_siso_channel_estimation_64(ip4, pvmask, (v_cs*)&siso_channel_1[0]);
    v_siso_channel_estimation_64(ip4 + 16, pvmask, (v_cs*)&siso_channel_2[0]);

    for (int i = 0; i < 16; i++)
    {
      v_cs r = v_add(siso_channel_1[i], siso_channel_2[i]);
      ch[1][*state * 16 + i]  = r.v_shift_right_arithmetic(1);
    }
    if (*state == 3)
    {
      memcpy(&(*dot11a_siso_channel)[0], &ch[3][*state * 16], sizeof(v_cs) * 16);
    }

    (*state) += 1;

    if (*state == 4)
    {
      *state = 0;
    }

    consume_each(32);
    return true;
  }
};


#include "b_bigap_4x4_tx.h"
#include "b_bigap_4x4_rx.h"