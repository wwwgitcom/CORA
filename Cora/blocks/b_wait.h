#pragma once

DEFINE_BLOCK(b_wait_2v, 2, 0)
{
  _local_(int, nwait, 0);
  BLOCK_INIT
  {
    auto v = $["nwait"];
    if (!v.empty()) *nwait = atoi(v.c_str());
  }
  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < *nwait)
    {
      return false;
    }

    return true;
  }
};

DEFINE_BLOCK(b_wait_4v, 4, 0)
{
  _local_(int, nwait, 0);
  BLOCK_INIT
  {
    auto v = $["nwait"];
    if (!v.empty()) *nwait = atoi(v.c_str());
  }
  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < *nwait)
    {
      return false;
    }

    return true;
  }
};