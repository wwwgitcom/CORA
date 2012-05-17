#pragma once

DEFINE_BLOCK(b_dot11_frame_source_v1, 1, 1)
{
  _global_(uint32, dot11_tx_frame_mcs);
  _global_(uint32, dot11_tx_frame_length);

  _local_(int, ntotal_bytes, 1000);
  _local_(int, npadding_bytes, 0);

  BLOCK_INIT
  {
    
  }

  BLOCK_WORK
  {
    *ntotal_bytes = *dot11_tx_frame_length;
    *npadding_bytes = ht_padding_bytes(*dot11_tx_frame_mcs, *dot11_tx_frame_length);

    auto op = $_<uint8>(0);

    op[0] = 0;
    op[1] = 0;

    for (int i = 2; i < *ntotal_bytes + 2; i++)
    {
      op[i] = 0x3;
    }

    for (int i = 0; i < *npadding_bytes; i++)
    {
      op[i] = 0x0;
    }

    produce(0, *ntotal_bytes + *npadding_bytes + 2);
    return true;
  }
};