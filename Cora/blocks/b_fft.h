#pragma once

#include "_fft_r4dif.h"
#include "_ifft_r4dif.h"
#include "_ifft_r4dif_wonorm.h"

DEFINE_BLOCK(b_fft_64_1v1, 1, 1)
{
  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 16) return false;

    auto ip = _$<v_cs>(0);
    auto op = $_<v_cs>(0);
    
    FFT<64>(reinterpret_cast<vcs *>(ip), reinterpret_cast<vcs *>(op));

    consume(0, 16);
    produce(0, 16);
    return true;
  }
};

DEFINE_BLOCK(b_ifft_64_1v1, 1, 1)
{
  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 16) return false;

    auto ip = _$<v_cs>(0);
    auto op = $_<v_cs>(0);

    IFFT<64>(reinterpret_cast<vcs *>(ip), reinterpret_cast<vcs *>(op));

    consume(0, 16);
    produce(0, 16);
    return true;
  }
};

DEFINE_BLOCK(b_ifft_128_1v1, 1, 1)
{
  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 32) return false;

    auto ip = _$<v_cs>(0);
    auto op = $_<v_cs>(0);

    IFFT<128>(reinterpret_cast<vcs *>(ip), reinterpret_cast<vcs *>(op));

    consume(0, 32);
    produce(0, 32);
    return true;
  }
};