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

//////////////////////////////////////////////////////////////////////////
DEFINE_BLOCK(b_dot11_frame_source_v2, 0, 2)
{
  _global_(uint32, dot11_tx_frame_mcs);
  _global_(uint32, dot11_tx_frame_length);

  _local_(int, ntotal_bytes, 1000);
  _local_(int, npadding_bytes, 0);

  crc::crc32 _crc32_1;
  crc::crc32 _crc32_2;

  BLOCK_WORK
  {
    *ntotal_bytes = *dot11_tx_frame_length;
    *npadding_bytes = pht_padding_bytes(*dot11_tx_frame_mcs, *dot11_tx_frame_length + 2);

    _crc32_1.reset();
    _crc32_2.reset();

    auto op1 = $_<uint8>(0);
    auto op2 = $_<uint8>(0);

    op1[0] = 0;
    op1[1] = 0;

    op2[0] = 0;
    op2[1] = 0;

    int i;
    for (i = 2; i < *ntotal_bytes + 2 - 4; i++)
    {
      uint8 c = 0x3;
      _crc32_1(c);
      _crc32_2(c);
      op1[i] = c;
      op2[i] = c;
    }

    *(uint32*)&op1[i] = _crc32_1.value();
    *(uint32*)&op2[i] = _crc32_2.value();
    i += 4;

    for (int j = 0; j < *npadding_bytes; j++)
    {
      op1[i] = 0x0;
      op2[i] = 0x0;
      i ++;
    }

    produce_each(0, *ntotal_bytes + *npadding_bytes + 2);
    return true;
  }
};