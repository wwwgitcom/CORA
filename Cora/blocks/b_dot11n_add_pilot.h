#pragma once

#include "_b_dot11_pilot.h"

DEFINE_BLOCK(b_dot11n_add_pilot_1v, 1, 0)
{
  _local_(int, pilot_index, 0);
  _local_(int, iss, 1);
  _local_(complex16, bpsk_one, complex16(30339, 0));

  dot11_ofdm_pilot _pilot_tracker;
  int16  _pilots[4];

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty())
    {
      *iss = atoi(v.c_str());
    }
  }

  BLOCK_RESET
  {
    *pilot_index = 0;
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<dot11n_tx_symbol>(0);

    _pilot_tracker(*iss, *pilot_index, _pilots);
    
    ip->subcarriers[128 - 21]  = *bpsk_one * _pilots[0];
    ip->subcarriers[128 - 7]   = *bpsk_one * _pilots[1];
    ip->subcarriers[7]         = *bpsk_one * _pilots[2];
    ip->subcarriers[21]        = *bpsk_one * _pilots[3];

    (*pilot_index)++;

    return true;
  }
};


DEFINE_BLOCK(b_dot11n_4x4_add_pilot_1v, 1, 0)
{
  _local_(int, pilot_index, 0);
  _local_(int, iss, 1);
  _local_(complex16, bpsk_one, complex16(30339, 0));

  dot11n_4x4_pilot _pilot_tracker;
  int16  _pilots[4];

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty())
    {
      *iss = atoi(v.c_str());
    }
  }

  BLOCK_RESET
  {
    *pilot_index = 0;
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<dot11n_tx_symbol>(0);

    _pilot_tracker(*iss, *pilot_index, _pilots);

    ip->subcarriers[128 - 21]  = *bpsk_one * _pilots[0];
    ip->subcarriers[128 - 7]   = *bpsk_one * _pilots[1];
    ip->subcarriers[7]         = *bpsk_one * _pilots[2];
    ip->subcarriers[21]        = *bpsk_one * _pilots[3];

    (*pilot_index)++;

    return true;
  }
};