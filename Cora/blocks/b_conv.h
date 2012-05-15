#pragma once
#include "_b_conv.h"

DEFINE_BLOCK(b_conv_1o2_1v1, 1, 1)
{
  conv_1_2 _conv;

  BLOCK_INIT
  {
    _conv.reset(0);
  }

  BLOCK_RESET
  {
    _conv.reset(0);
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<uint8>(0);

    for (int i = 0; i < n; i++)
    {
      _conv(ip, op);
      ip += 1;
      op += 2;
    }

    consume(0, n);
    produce(0, n << 1);

    return true;
  }
};

DEFINE_BLOCK(b_conv_2o3_1v1, 1, 1)
{
  conv_2_3 _conv;

  BLOCK_INIT
  {
    _conv.reset(0);
  }

  BLOCK_RESET
  {
    _conv.reset(0);
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 2) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<uint8>(0);

    int nround = 0;
    for (int i = 0; i <= n - 2; i += 2)
    {
      _conv(ip, op);
      ip += 2;
      op += 3;
      nround += 1;
    }

    consume(0, nround * 2);
    produce(0, nround * 3);

    return true;
  }
};

DEFINE_BLOCK(b_conv_3o4_1v1, 1, 1)
{
  conv_3_4 _conv;

  BLOCK_INIT
  {
    _conv.reset(0);
  }

  BLOCK_RESET
  {
    _conv.reset(0);
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 3) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<uint8>(0);
    
    int nround = 0;
    for (int i = 0; i <= n - 3; i += 3)
    {
      _conv(ip, op);
      ip += 3;
      op += 4;
      nround += 1;
    }

    consume(0, nround * 3);
    produce(0, nround * 4);

    return true;
  }
};