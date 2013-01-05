#pragma once


DEFINE_BLOCK(b_perf_sink_v1, 0, 1)
{
public:
  _local_(int, nin_sum, 0);

  BLOCK_RESET
  {
    *nin_sum = 0;
  }

  BLOCK_WORK
  {
    auto n = ninput(0);

    *nin_sum += n;
    consume(0, n);

    return false;
  }
};