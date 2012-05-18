#pragma once

#include "_b_lsig.h"

DEFINE_BLOCK(b_dot11n_lsig_v1, 0, 1)
{
  _global_(uint32, dot11_tx_frame_length);

  L_SIG _lsig;

  BLOCK_WORK
  {
    auto op = $_<uint8>(0);

    _lsig.clear();
    // indicate as legacy 6Mbps frame
    _lsig.update(DOT11A_RATE::_6M, *dot11_tx_frame_length);

    op[0] = _lsig.cdata[0];
    op[1] = _lsig.cdata[1];
    op[2] = _lsig.cdata[2];

    produce(0, L_SIG::SIZE);

    return true;
  }
};