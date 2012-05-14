#pragma once

#include "_dot11n_interleave.h"

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

DEFINE_BLOCK(b_dot11n_interleaver_1bpsc_1v1, 1, 1)
{
  dot11n_interleaver_1bpsc interleaver;

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < interleaver.total_bytes) return false;

    auto ip = _$<uint8>(0);
    auto op = _$<v_ub>(0);

    interleaver(ip, op);

    consume(0, interleaver.total_bytes);
    produce(0, interleaver.voutbuffer_size);

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
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < interleaver.total_bytes) return false;

    auto ip = _$<uint8>(0);
    auto op = _$<v_ub>(0);

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
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < interleaver.total_bytes) return false;

    auto ip = _$<uint8>(0);
    auto op = _$<v_ub>(0);

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
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < interleaver.total_bytes) return false;

    auto ip = _$<uint8>(0);
    auto op = _$<v_ub>(0);

    interleaver(ip, op);

    consume(0, interleaver.total_bytes);
    produce(0, interleaver.voutbuffer_size);

    return true;
  }
};