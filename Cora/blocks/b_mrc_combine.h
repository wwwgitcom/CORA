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
    auto ip2 = _$<v_cs>(1);
    auto op  = $_<v_cs>(0);
#if 1
    for (int i = 0; i < n; i++)
    {
      v_cs r = v_add(ip1[i], ip2[i]);
      op[i]  = r.v_shift_right_arithmetic(1);
    }
#else
    for (int i = 0; i < n; i++)
    {
      op[i] = ip1[i];
    }
#endif
    consume(0, n);
    consume(1, n);
    produce(0, n);

    return true;
  }
};

DEFINE_BLOCK(b_mrc_combine_4v1, 4, 1)
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
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    auto op  = $_<v_cs>(0);
#if 1
    for (int i = 0; i < n; i++)
    {
      v_cs r1 = v_add(ip1[i], ip2[i]).v_shift_right_arithmetic(1);
      v_cs r2 = v_add(ip3[i], ip4[i]).v_shift_right_arithmetic(1);
      op[i]   = v_add(r1, r2).v_shift_right_arithmetic(1);
    }
#else
    for (int i = 0; i < n; i++)
    {
      op[i] = ip1[i];
    }
#endif
    consume_each(n);
    produce(0, n);

    return true;
  }
};