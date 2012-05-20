#pragma once
#include "dsp_scramble.h"


DEFINE_BLOCK(b_dot11n_scramble_1v1, 1, 1)
{
  _global_(int, scramble_length);
  _local_(int, scrambled_length, 0);

  scrambler::dot11n_scrambler _scrambler;

  BLOCK_INIT
  {
    _scrambler.reset(0xAB);
  }

  BLOCK_RESET
  {
    _scrambler.reset(0xAB);
    *scrambled_length = 0;
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<uint8>(0);

    for (int i = 0; i < n; i++)
    {
      op[i] = _scrambler(ip[i]);
      (*scrambled_length)++;
      if (*scrambled_length == *scramble_length + 1)
      {
        op[i] &= 0xC0;
      }
    }

    consume(0, n);
    produce(0, n);
    return true;
  }
};