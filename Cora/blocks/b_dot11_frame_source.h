#pragma once

DEFINE_BLOCK(b_dot11_frame_source_v1, 1, 1)
{
  _global_(uint32, dot11_tx_frame_mcs);
  _global_(uint32, dot11_tx_frame_length);

  _local_(int, ntotal_bytes, 1000);
  _local_(int, npadding_bytes, 0);

  crc::crc32 _crc32;

  BLOCK_WORK
  {
    *ntotal_bytes = *dot11_tx_frame_length;
    *npadding_bytes = ht_padding_bytes(*dot11_tx_frame_mcs, *dot11_tx_frame_length);

    _crc32.reset();

    auto op = $_<uint8>(0);

    op[0] = 0;
    op[1] = 0;

    int i;
    for (i = 2; i < *ntotal_bytes + 2 - 4; i++)
    {
      uint8 c = 0x3;
      _crc32(c);
      op[i] = c;
    }

    *(uint32*)&op[i] = _crc32.value();
    i += 4;

    for (int j = 0; j < *npadding_bytes; j++)
    {
      op[i] = 0x0;
      i ++;
    }

    produce(0, *ntotal_bytes + *npadding_bytes + 2);
    return true;
  }
};