#pragma once

#include "_fft_r4dif.h"
#include "_ifft_r4dif.h"

// TX IFFT128 works on dot11n_tx_symbol directly
DEFINE_BLOCK(b_dot11n_tx_ifft_128_1v1, 1, 1)
{
  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<dot11n_tx_symbol>(0);
    auto op = $_<dot11n_tx_symbol>(0);

    IFFT<128>(reinterpret_cast<vcs *>(ip->vsubcarriers), reinterpret_cast<vcs *>(op->vsubcarriers));

    consume(0, 1);
    produce(0, 1);
    return true;
  }
};