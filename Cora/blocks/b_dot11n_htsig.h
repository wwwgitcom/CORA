#pragma once

#include "_b_htsig.h"

DEFINE_BLOCK(b_dot11n_htsig_v1, 0, 1)
{
  _global_(uint32, dot11_tx_frame_mcs);
  _global_(uint32, dot11_tx_frame_length);

  HT_SIG _htsig;

  BLOCK_WORK
  {
    auto op = $_<uint8>(0);

    _htsig.clear();
    _htsig.update(*dot11_tx_frame_mcs, *dot11_tx_frame_length);

    memcpy(op, _htsig.cdata, HT_SIG::SIZE);

    produce(0, HT_SIG::SIZE);

    return true;
  }
};