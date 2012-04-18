#pragma once

DEFINE_BLOCK(b_remove_gi_1v, 1, 0)
{
  _local_(int, gi_length, 4);
  _local_(int, symbol_length, 16);

  BLOCK_INIT
  {
    auto v = $["GILength"];
    if (!v.empty())
    {
      *gi_length = atoi(v.c_str());
    }
    v = $["SymbolLength"];
    if (!v.empty())
    {
      *symbol_length = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    int n = ninput(0);
    if (n < *gi_length + *symbol_length)
    {
      return false;
    }

    consume(0, *gi_length);
    return true;
  }
};