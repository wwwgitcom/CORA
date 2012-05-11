#pragma once

DEFINE_BLOCK(b_stream_joiner_1_2v1, 2, 1)
{
  BLOCK_WORK
  {
    trace();
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto op  = $_<uint8>(0);

    int iOut = 0;
    int iIn  = 0;
    for ( ; iIn < n; iIn++, iOut += 2)
    {
      op[iOut]     = ip1[iIn];
      op[iOut + 1] = ip2[iIn];
    }

    consume(0, iIn);
    consume(1, iIn);
    produce(0, iOut);

    return true;
  }
};

DEFINE_BLOCK(b_stream_joiner_2_2v1, 2, 1)
{
  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 2) return false;

    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto op  = $_<uint8>(0);

    int iOut = 0;
    int iIn  = 0;
    for (; iIn < n; iIn += 2, iOut += 4)
    {
      op[iOut + 0] = ip1[iIn + 0];
      op[iOut + 1] = ip1[iIn + 1];
      op[iOut + 2] = ip2[iIn + 0];
      op[iOut + 3] = ip2[iIn + 1];
    }
    consume(0, iIn);
    consume(1, iIn);
    produce(0, iOut);
    return true;
  }
};

DEFINE_BLOCK(b_stream_joiner_3_2v1, 2, 1)
{
  BLOCK_WORK
  {
    trace();
    auto n = ninput(0);
    if (n < 3) return false;

    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto op  = $_<uint8>(0);

    int iOut = 0;
    int iIn  = 0;
    for (; iIn < n; iIn += 3, iOut += 6)
    {
      op[iOut + 0] = ip1[iIn + 0];
      op[iOut + 1] = ip1[iIn + 1];
      op[iOut + 2] = ip1[iIn + 2];
      op[iOut + 3] = ip2[iIn + 0];
      op[iOut + 4] = ip2[iIn + 1];
      op[iOut + 5] = ip2[iIn + 2];
    }

    consume(0, iIn);
    consume(1, iIn);
    produce(0, iOut);
    return true;
  }
};