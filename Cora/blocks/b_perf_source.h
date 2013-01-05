#pragma once


DEFINE_BLOCK(b_perf_source_v1, 0, 1)
{
public:
  _local_(int, nout_granulity, 1);
  _local_(int, nout_total, 1000);
  _local_(int, nout_sum, 1000);

  BLOCK_RESET
  {
    *nout_sum = 0;
  }

  BLOCK_WORK
  {
    produce(0, *nout_granulity);

    *nout_sum += *nout_granulity;

    if (*nout_sum >= *nout_total)
    {
      return false;
    }

    return true;
  }
};