#pragma once

DEFINE_BLOCK(b_consumer_1v, 1, 0)
{
  _local_(uint8, var, 0);

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<uint8>(0);

    for (int i = 0; i < n; i++)
    {
      *var = ip[i];
    }

    consume(0, n);
    return true;
  }
};