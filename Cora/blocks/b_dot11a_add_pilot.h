#pragma once

#include "_b_dot11_pilot.h"

DEFINE_BLOCK(b_dot11a_add_pilot_1v, 1, 0)
{
  _local_(int, pilot_start_index, 0);
  _local_(int, pilot_index, 0);
  _local_(complex16, bpsk_one, complex16(30339, 0));
  _local_(complex16, bpsk_neg_one, complex16(-30339, 0));

  dot11_ofdm_pilot _pilot_tracker;

  BLOCK_INIT
  {
    auto v = $["pilot_start_index"];
    if (!v.empty()) *pilot_start_index = atoi(v.c_str());
    *pilot_index = *pilot_start_index;

    v = $["iss"];
    if (!v.empty()) *iss = atoi(v.c_str());
  }

  BLOCK_RESET
  {
    *pilot_index = *pilot_start_index;
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<dot11n_tx_symbol>(0);

    auto pilot_sign = _pilot_tracker(*pilot_index);

    if (pilot_sign == 1)
    {
      ip->subcarriers[128 - 21]  = *bpsk_one;
      ip->subcarriers[128 - 7]   = *bpsk_neg_one;
      ip->subcarriers[7]         = *bpsk_one;
      ip->subcarriers[21]        = *bpsk_one;
    }
    else
    {
      ip->subcarriers[128 - 21]  = *bpsk_neg_one;
      ip->subcarriers[128 - 7]   = *bpsk_one;
      ip->subcarriers[7]         = *bpsk_neg_one;
      ip->subcarriers[21]        = *bpsk_neg_one;
    }

    (*pilot_index)++;

    return true;
  }
};