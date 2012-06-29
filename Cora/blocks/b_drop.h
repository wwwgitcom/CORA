#pragma once

DEFINE_BLOCK(b_drop_1v, 1, 0)
{
  _local_(int, nDrop, 1);

  BLOCK_INIT
  {
    auto v = $["nDrop"];
    if (!v.empty())
    {
      *nDrop = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < *nDrop) return false;
    consume(0, *nDrop);
    return true;
  }
};

DEFINE_BLOCK(b_drop_2v, 2, 0)
{
  _local_(int, nDrop, 1);

  BLOCK_INIT
  {
    auto v = $["nDrop"];
    if (!v.empty())
    {
      *nDrop = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < *nDrop) return false;
    consume_each(*nDrop);
    return true;
  }
};


DEFINE_BLOCK(b_drop_4v, 4, 0)
{
  _local_(int, nDrop, 1);

  BLOCK_INIT
  {
    auto v = $["nDrop"];
    if (!v.empty())
    {
      *nDrop = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < *nDrop) return false;
    consume_each(*nDrop);
    return true;
  }
};