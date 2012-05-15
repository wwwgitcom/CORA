#pragma once

#include "_b_lltf.h"

DEFINE_BLOCK(b_dot11n_lltf_v2, 0, 2)
{
  L_LTF _lltf;

  BLOCK_WORK
  {
    auto op1 = $_<dot11n_tx_symbol>(0);
    auto op2 = $_<dot11n_tx_symbol>(0);

    _lltf.get_ltf_1(op1->data);
    _lltf.get_ltf_2(op2->data);

    produce(0, 2);
    produce(1, 2);

    return true;
  }
};