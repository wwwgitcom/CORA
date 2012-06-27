#pragma once

#include "_b_lltf.h"

DEFINE_BLOCK(b_dot11n_lltf_v2, 0, 2)
{
  L_LTF _lltf;

  BLOCK_WORK
  {
    auto op1 = $_<dot11n_tx_symbol>(0);
    auto op2 = $_<dot11n_tx_symbol>(1);

    _lltf.get_ltf_1(op1->data);
    _lltf.get_ltf_2(op2->data);

    produce(0, 2);
    produce(1, 2);

    return true;
  }
};

DEFINE_BLOCK(b_dot11n_lltf_v4, 0, 4)
{
  L_LTF _lltf;

  BLOCK_WORK
  {
    auto op1 = $_<dot11n_tx_symbol>(0);
    auto op2 = $_<dot11n_tx_symbol>(1);
    auto op3 = $_<dot11n_tx_symbol>(2);
    auto op4 = $_<dot11n_tx_symbol>(3);

    _lltf.get_ltf_1_of_4(op1->data);
    _lltf.get_ltf_2_of_4(op2->data);
    _lltf.get_ltf_3_of_4(op3->data);
    _lltf.get_ltf_4_of_4(op4->data);

    produce_each(2);

    return true;
  }
};