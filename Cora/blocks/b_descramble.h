#pragma once
#include "dsp_scramble.h"


DEFINE_BLOCK(b_dot11_descramble_seed_1v, 1, 0)
{
  _global_(descrambler::dot11n_descrambler, descrambler);

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 2) return false;

    auto ip = _$<uint8>(0);

    (*descrambler).reset(ip[1]);

    consume(0, 2);

    return true;
  }
};

DEFINE_BLOCK(b_dot11_descramble_1v1, 1, 1)
{
  _global_(descrambler::dot11n_descrambler, descrambler);
  
  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<uint8>(0);

    autoref ds = *descrambler;

    for (int i = 0; i < n; i++)
    {
      op[i] = ds(ip[i]);
      //printf("%02X ", op[i]);
    }
    //printf("\n\n");

    consume(0, n);
    produce(0, n);
    return true;
  }
};

