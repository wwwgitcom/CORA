#pragma once

#include "_b_htltf.h"

DEFINE_BLOCK(b_dot11n_htltf_v2, 0, 2)
{
  HT_LTF _htltf;

  BLOCK_WORK
  {
    auto op1 = $_<dot11n_tx_symbol>(0);
    auto op2 = $_<dot11n_tx_symbol>(0);

    _htltf.get_ltf_11(op1->data);
    op1++;
    _htltf.get_ltf_12(op1->data);

    _htltf.get_ltf_21(op2->data);
    op2++;
    _htltf.get_ltf_22(op2->data);

    produce(0, 2);
    produce(1, 2);

    return true;
  }
};