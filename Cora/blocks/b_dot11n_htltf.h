#pragma once

#include "_b_htltf.h"

DEFINE_BLOCK(b_dot11n_htltf_v2, 0, 2)
{
  HT_LTF _htltf;

  BLOCK_WORK
  {
    auto op1 = $_<dot11n_tx_symbol>(0);
    auto op2 = $_<dot11n_tx_symbol>(1);

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

DEFINE_BLOCK(b_dot11n_htltf_v4, 0, 4)
{
  HT_LTF _htltf;

  BLOCK_WORK
  {
    auto op1 = $_<dot11n_tx_symbol>(0);
    auto op2 = $_<dot11n_tx_symbol>(1);
    auto op3 = $_<dot11n_tx_symbol>(2);
    auto op4 = $_<dot11n_tx_symbol>(3);

    _htltf.get_ltf_11(op1->data);
    op1++;
    _htltf.get_ltf_12(op1->data);
    op1++;
    _htltf.get_ltf_13(op1->data);
    op1++;
    _htltf.get_ltf_14(op1->data);

    _htltf.get_ltf_21(op2->data);
    op2++;
    _htltf.get_ltf_22(op2->data);
    op2++;
    _htltf.get_ltf_23(op2->data);
    op2++;
    _htltf.get_ltf_24(op2->data);

    _htltf.get_ltf_31(op3->data);
    op3++;
    _htltf.get_ltf_32(op3->data);
    op3++;
    _htltf.get_ltf_33(op3->data);
    op3++;
    _htltf.get_ltf_34(op3->data);

    _htltf.get_ltf_41(op4->data);
    op4++;
    _htltf.get_ltf_42(op4->data);
    op4++;
    _htltf.get_ltf_43(op4->data);
    op4++;
    _htltf.get_ltf_44(op4->data);

    produce_each(4);

    return true;
  }
};