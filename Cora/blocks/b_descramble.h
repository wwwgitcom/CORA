#pragma once
#include "dsp_scramble.h"


DEFINE_BLOCK(b_dot11_descramble_seed_1v, 1, 0)
{
  _global_(dsp_descrambler::dot11n_descrambler, descrambler);

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
public:
  dsp_descrambler::dot11n_descrambler descrambler;
  _local_(int, nInputCount, 0);

  BLOCK_RESET
  {
    *nInputCount = 0;
  }

  BLOCK_WORK
  {
    trace();
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<uint8>(0);

    if (*nInputCount < 2 && n >= 2)
    {
      descrambler.reset(ip[1]);
      ip += 2;
      n  -= 2;
      consume(0, 2);
      *nInputCount = 2;
    }

    for (int i = 0; i < n; i++)
    {
      op[i] = descrambler(ip[i]);
      //printf("%02X ", op[i]);
    }
    //printf("\n\n");

    consume(0, n);
    produce(0, n);
    return true;
  }
};

