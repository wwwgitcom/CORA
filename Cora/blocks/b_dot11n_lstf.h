#pragma once

#include "_b_lstf.h"

DEFINE_BLOCK(b_dot11n_lstf_v2, 0, 2)
{
  L_STF _lstf;

  BLOCK_WORK
  {
    auto op1 = $_<dot11n_tx_symbol>(0);
    auto op2 = $_<dot11n_tx_symbol>(1);

    _lstf.get_stf_1(op1->data);
    _lstf.get_stf_2(op2->data);

    produce(0, 2);
    produce(1, 2);

    return true;
  }
};

DEFINE_BLOCK(b_dot11n_lstf_v4, 0, 4)
{
  L_STF _lstf;

  BLOCK_WORK
  {
    auto op1 = $_<dot11n_tx_symbol>(0);
    auto op2 = $_<dot11n_tx_symbol>(1);
    auto op3 = $_<dot11n_tx_symbol>(2);
    auto op4 = $_<dot11n_tx_symbol>(3);

    _lstf.get_stf_1_of_4(op1->data);
    _lstf.get_stf_2_of_4(op2->data);
    _lstf.get_stf_3_of_4(op3->data);
    _lstf.get_stf_4_of_4(op4->data);

    produce_each(2);

    return true;
  }
};