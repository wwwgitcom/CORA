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
    consume(0, ninput(0));
    return false;
  }
};