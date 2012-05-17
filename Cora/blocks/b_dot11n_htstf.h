#pragma once

#include "_b_htstf.h"

DEFINE_BLOCK(b_dot11n_htstf_v2, 0, 2)
{
  HT_STF _htstf;

  BLOCK_WORK
  {
    auto op1 = $_<dot11n_tx_symbol>(0);
    auto op2 = $_<dot11n_tx_symbol>(1);

    _htstf.get_stf_1(op1->data);
    _htstf.get_stf_2(op2->data);

    produce(0, 1);
    produce(1, 1);

    return true;
  }
};