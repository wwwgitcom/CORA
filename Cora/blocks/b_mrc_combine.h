#pragma once

DEFINE_BLOCK(b_mrc_combine_2v1, 2, 1)
{
  BLOCK_INIT
  {
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 1) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(0);
    auto op  = $_<v_cs>(0);

    for (int i = 0; i < n; i++)
    {
      v_cs r = v_add(ip1[i], ip2[i]);
      op[i]  = r.v_shift_right_arithmetic(1);
    }
    consume(0, n);
    consume(1, n);
    produce(0, n);

    return true;
  }
};