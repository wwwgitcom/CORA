#pragma once

// as SORA MIMO specification, samples from 2 streams are interleaved by 4 samples (or, 1 v_cs)
// join sample from 2 inputs and flush to memory without polluting cache lines
DEFINE_BLOCK(b_dot11n_dma_join_2v1, 2, 1)
{
  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip1 = _$<dot11n_tx_symbol>(0);
    auto ip2 = _$<dot11n_tx_symbol>(1);
    auto op  = $_<v_cs>(0);

    for (int k = 0; k < n; k++)
    {
      for (int i = 0; i < dot11n_tx_symbol::vntotal; i++)
      {
        ip1->vdata[i].v_storent(op);
        ip2->vdata[i].v_storent(op + 1);
        op += 2;
      }
    }

    consume(0, n);
    consume(1, n);
    produce(0, n * dot11n_tx_symbol::vntotal << 1);

    return true;
  }
};