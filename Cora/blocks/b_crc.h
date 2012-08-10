#pragma once

DEFINE_BLOCK(b_crc32_check_1v, 1, 0)
{
  _local_(int, checked_length, 0);
  crc::crc32 crc32_check;
public:
  _local_(int, crc32_check_length, 0);
  _local_(bool, crc32_check_result, false);
  
  BLOCK_INIT
  {
    crc32_check.reset();
  }

  BLOCK_RESET
  {
    auto n = ninput(0);
    consume(0, n);
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 1) {return false;}

    auto ip = _$<uint8>(0);

    //printf("cd::crc::%p:: ", this);
    //for (int i = 0; i < n; i++)
    //{
    //  printf("%02X ", ip[i]);
    //}
    //printf("\n\n");


    int total = *crc32_check_length;
    int i = 0;
    for (; i < n && (*checked_length < (total - 4)); i++)
    {
      //printf("%02X ", ip[i]);
      crc32_check(ip[i]);
      (*checked_length)++;
    }
    //printf("checked length = %d\n", *checked_length);
    if (*checked_length == total - 4)
    {
      if (n - i >= 4)
      {
        uint32 calc_crc32 = crc32_check.value();
        uint32 local_crc32 = *((uint32*)&ip[i]);

        printf("cd:: CRC: calc:%X : local:%X\n", calc_crc32, local_crc32);

        *crc32_check_result = ( *((uint32*)&ip[i]) == crc32_check.value() );
        crc32_check.reset();
        *checked_length = 0;
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