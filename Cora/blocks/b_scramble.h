#pragma once
#include "dsp_scramble.h"


DEFINE_BLOCK(b_dot11_scramble_1v1, 1, 1)
{
  scrambler::dot11n_scrambler m_scrambler;

  BLOCK_INIT
  {
    m_scrambler.reset(0xAB);
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<uint8>(0);

    for (int i = 0; i < n; i++)
    {
      op[i] = m_scrambler(ip[i]);
    }

    consume(0, n);
    produce(0, n);
    return true;
  }
};