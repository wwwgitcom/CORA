#pragma once

DEFINE_BLOCK(b_mrc_combine_2v1, 2, 1)
{
  _local_(int, CombineLength, 1);

  BLOCK_INIT
  {
    auto v = $["Combinelength"];
    if (!v.empty())
    {
      *CombineLength = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < *CombineLength) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(0);
    auto op  = $_<v_cs>(0);

    for (int i = 0; i < *CombineLength; i++)
    {
      v_cs r = v_add(ip1[i], ip2[i]);
      op[i]  = r.v_shift_right_arithmetic(1);
    }
  }
};