#pragma once

DEFINE_BLOCK(b_stream_joiner_1_2v1, 2, 1)
{
  _local_(int, count_per_stream, 1);

  BLOCK_INIT
  {
    auto v = $["count_per_stream"];
    if (!v.empty())
    {
      *count_per_stream = atoi(v.c_str());

      if (*count_per_stream % 1 != 0)
      {
        string msg = "error: " + string(name()) + ": invalid argument of count_per_stream, must be a factor of 1";
        cout << msg << endl;
        throw::invalid_argument(msg);
      }
    }
  }

  BLOCK_WORK
  {
    trace();
    auto n = ninput(0);
    int total = *count_per_stream;
    if (n < total) return false;

    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto op  = $_<uint8>(0);

    int iOut = 0;
    
    for (int iIn = 0; iIn < total; iIn++, iOut += 2)
    {
      op[iOut]     = ip1[iIn];
      op[iOut + 1] = ip2[iIn];
    }

    consume(0, total);
    consume(1, total);
    produce(0, total << 1);

    return true;
  }
};

DEFINE_BLOCK(b_stream_joiner_2_2v1, 2, 1)
{
  _local_(int, count_per_stream, 2);

  BLOCK_INIT
  {
    auto v = $["count_per_stream"];
    if (!v.empty())
    {
      *count_per_stream = atoi(v.c_str());

      if (*count_per_stream % 2 != 0)
      {
        string msg = "error: " + string(name()) + ": invalid argument of count_per_stream, must be a factor of 2";
        cout << msg << endl;
        throw::invalid_argument(msg);
      }
    }
  }

  BLOCK_WORK
  {
    trace();
    auto n = ninput(0);
    int total = *count_per_stream;
    if (n < total) return false;

    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto op  = $_<uint8>(0);

    int iOut = 0;

    for (int iIn = 0; iIn < total; iIn += 2, iOut += 4)
    {
      op[iOut + 0] = ip1[iIn + 0];
      op[iOut + 1] = ip1[iIn + 1];
      op[iOut + 2] = ip2[iIn + 0];
      op[iOut + 3] = ip2[iIn + 1];
    }
    consume(0, total);
    consume(1, total);
    produce(0, total << 1);
    return true;
  }
};

DEFINE_BLOCK(b_stream_joiner_3_2v1, 2, 1)
{
  _local_(int, count_per_stream, 3);

  BLOCK_INIT
  {
    auto v = $["count_per_stream"];
    if (!v.empty())
    {
      *count_per_stream = atoi(v.c_str());
      if (*count_per_stream % 3 != 0)
      {
        string msg = "error: " + string(name()) + ": invalid argument of count_per_stream, must be a factor of 3";
        cout << msg << endl;
        throw::invalid_argument(msg);
      }
    }
  }

  BLOCK_WORK
  {
    trace();
    auto n = ninput(0);
    int total = *count_per_stream;
    if (n < total) return false;

    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto op  = $_<uint8>(0);

    int iOut = 0;

    for (int iIn = 0; iIn < total; iIn += 3, iOut += 6)
    {
      op[iOut + 0] = ip1[iIn + 0];
      op[iOut + 1] = ip1[iIn + 1];
      op[iOut + 2] = ip1[iIn + 2];
      op[iOut + 3] = ip2[iIn + 0];
      op[iOut + 4] = ip2[iIn + 1];
      op[iOut + 5] = ip2[iIn + 2];
    }
    consume(0, total);
    consume(1, total);
    produce(0, total << 1);
    return true;
  }
};