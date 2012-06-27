#pragma once

__forceinline void Reverse(v_cs* arr, int b, int e)
{
  for(; b < e; b++, e--)
  {
    v_cs temp = arr[e];
    arr[e] = arr[b];
    arr[b] = temp;
  }
}


DEFINE_BLOCK(b_dot11n_csd_1v1, 1, 0)
{
  _local_(int, ncsd, 0);

  BLOCK_INIT
  {
    auto v = $["ncsd"];
    if (!v.empty()) *ncsd = atoi(v.c_str());
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<dot11n_tx_symbol>(0);
    auto op = $_<dot11n_tx_symbol>(0);
    
#if 0
    // work on input symbol
    Reverse(ip->vsubcarriers, 0, dot11n_tx_symbol::vnsubcarrier - *ncsd - 1);
    Reverse(ip->vsubcarriers, dot11n_tx_symbol::vnsubcarrier - *ncsd, dot11n_tx_symbol::vnsubcarrier - 1);
    Reverse(ip->vsubcarriers, 0, dot11n_tx_symbol::vnsubcarrier - 1);
#else
    // produce a new symbol
    ip->csd(*op, *ncsd);

    consume(0, 1);
    produce(0, 1);
#endif

    return true;
  }
};


DEFINE_BLOCK(b_dot11n_complex16_csd_1v1, 1, 0)
{
  _local_(int, ncsd, 0);

  BLOCK_INIT
  {
    auto v = $["ncsd"];
    if (!v.empty()) *ncsd = atoi(v.c_str());
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<dot11n_tx_symbol>(0);
    auto op = $_<dot11n_tx_symbol>(0);

    // produce a new symbol
    ip->c_csd(*op, *ncsd);

    consume(0, 1);
    produce(0, 1);

    return true;
  }
};