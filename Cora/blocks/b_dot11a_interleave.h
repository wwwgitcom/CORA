#pragma once

#include "_dot11_interleave.h"

DEFINE_BLOCK(b_dot11a_interleaver_1bpsc_1v1, 1, 1)
{
  dot11a_interleaver_1bpsc interleaver;

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 6) return false;

    auto ip = _$<uint8>(0);
    auto op = _$<v_ub>(0);

    interleaver(ip, op);

    consume(0, 6);
    produce(0, interleaver.voutbuffer_size);

    return true;
  }
};