#pragma once


DEFINE_BLOCK(b_bigap_lltf_tx_v4, 0, 4)
{
  /*
  * make time domain orthogonal LLTF
  */

  L_LTF _lltf;

  BLOCK_WORK
  {
    auto op1 = $_<dot11n_tx_symbol>(0);
    auto op2 = $_<dot11n_tx_symbol>(1);
    auto op3 = $_<dot11n_tx_symbol>(2);
    auto op4 = $_<dot11n_tx_symbol>(3);

    _lltf.get_ltf_1_of_4(op1->data);
    _lltf.get_ltf_1_of_4(op2->data);    
    _lltf.get_ltf_1_of_4(op3->data);
    _lltf.get_ltf_1_of_4(op4->data);

    produce_each(2);

    return true;
  }
};


DEFINE_BLOCK(b_bigap_lltf_rx_4v, 4, 0)
{
  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 32) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);
    
    short delta1 = v_estimate_i(ip1, 16, 16);
    short delta2 = v_estimate_i(ip2, 16, 16);
    short delta3 = v_estimate_i(ip3, 16, 16);
    short delta4 = v_estimate_i(ip4, 16, 16);

    printf("f11=%d, f21=%d, f31=%d, f41=%d\n", delta1, delta2, delta3, delta4);

    //consume_each(32);
    return true;
  }
};
