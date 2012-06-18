#pragma once

#include "_dot11_interleave.h"

DEFINE_BLOCK(b_dot11n_interleaver_1bpsc_1v1, 1, 1)
{
  dot11n_interleaver_1bpsc interleaver;

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty())
    {
      interleaver.init(atoi(v.c_str()));
    }
    else
    {
      interleaver.init(1);
    }
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < interleaver.total_bytes) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<v_ub>(0);

    interleaver(ip, op);


#if 0
    for (int i = 0; i < interleaver.total_bytes; i++)
    {
      printf("%02x ", op[0][i]);
    }
    printf("\n");
#endif

    consume(0, interleaver.total_bytes);
    produce(0, interleaver.voutbuffer_size);

    return true;
  }
};

DEFINE_BLOCK(b_dot11n_interleaver_1bpsc_half_1v1, 1, 1)
{
  dot11n_interleaver_1bpsc interleaver;
  _local_(int, iCount, 0);

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty())
    {
      interleaver.init(atoi(v.c_str()));
    }
    else
    {
      interleaver.init(1);
    }
  }

  BLOCK_RESET
  {
    *iCount = 0;
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 13) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<v_ub>(0);

    interleaver.first_half(ip, op);
    interleaver.second_half(ip + 6, op + 1);

#if 0
    for (int i = 0; i < interleaver.total_bytes; i++)
    {
      printf("%02x ", op[0][i]);
    }
    printf("\n");
#endif

    consume(0, 13);
    produce(0, 2);

    return true;
  }
};

DEFINE_BLOCK(b_dot11n_interleaver_2bpsc_1v1, 1, 1)
{
  dot11n_interleaver_2bpsc interleaver;

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty())
    {
      interleaver.init(atoi(v.c_str()));
    }
    else
    {
      interleaver.init(1);
    }
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < interleaver.total_bytes) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<v_ub>(0);

    interleaver(ip, op);

    consume(0, interleaver.total_bytes);
    produce(0, interleaver.voutbuffer_size);

    return true;
  }
};

DEFINE_BLOCK(b_dot11n_interleaver_4bpsc_1v1, 1, 1)
{
  dot11n_interleaver_4bpsc interleaver;

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty())
    {
      interleaver.init(atoi(v.c_str()));
    }
    else
    {
      interleaver.init(1);
    }
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < interleaver.total_bytes) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<v_ub>(0);

    interleaver(ip, op);

    consume(0, interleaver.total_bytes);
    produce(0, interleaver.voutbuffer_size);

    return true;
  }
};

DEFINE_BLOCK(b_dot11n_interleaver_6bpsc_1v1, 1, 1)
{
  dot11n_interleaver_6bpsc interleaver;

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty())
    {
      interleaver.init(atoi(v.c_str()));
    }
    else
    {
      interleaver.init(1);
    }
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < interleaver.total_bytes) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<v_ub>(0);

    interleaver(ip, op);

    consume(0, interleaver.total_bytes);
    produce(0, interleaver.voutbuffer_size);

    return true;
  }
};