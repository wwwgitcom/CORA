#pragma once

DEFINE_BLOCK(b_crc32_1v, 1, 0)
{
  _global_(int, crc32_check_length);
  _global_(bool, crc32_check_result);
  _local_(int, checked_length, 0);

  crc::crc32 crc32_check;

  BLOCK_INIT
  {
    crc32_check.reset();
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<uint8>(0);

    int total = *crc32_check_length;
    int i = 0;
    for (; i < n && (*checked_length < (total - 4)); i++)
    {
      crc32_check(ip[i]);
      (*checked_length)++;      
    }

    if (*checked_length == total - 4)
    {
      if (n - i >= 4)
      {
        *checked_length = 0;
        uint32 calc_crc32 = crc32_check.value();
        uint32 local_crc32 = *((uint32*)&ip[i]);

        log("CRC: calc:%X : local:%X\n", calc_crc32, local_crc32);

        *crc32_check_result = ( *((uint32*)&ip[i]) == crc32_check.value() );
        crc32_check.reset();
        consume(0, n);
        return true;
      }
      else
      {
        consume(0, i);
        return false;
      }
    }
    consume(0, n);
    return false;
  }
};