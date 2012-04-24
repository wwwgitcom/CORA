#pragma once

DEFINE_BLOCK(b_htsig_parser_1v, 1, 0)
{
  _global_(uint16, ht_frame_length);
  _global_(uint32, ht_frame_mcs);

  crc::crc8 m_crc8;

  BLOCK_WORK
  {
    int n = ninput(0);
    if (n < 6) return false;

    auto ip = _$<unsigned __int8>(0);
    
    unsigned char  crc8value;
    bool bRet = true;

    do 
    {
      m_crc8.reset();
      m_crc8(ip, 4);
      m_crc8(ip[4] & 0x3, 2);
      crc8value = m_crc8.value();

      if (crc8value != ((ip[4] >> 2) | (ip[5] << 6)))
      {
        *ht_frame_mcs    = 0;
        *ht_frame_length = 0;
        log(" ht-sig error: crc8 check failed %X.\n", crc8value);

        bRet = false;
        break;
      }

      *ht_frame_mcs    = (ip[0] & 0x7F);
      *ht_frame_length = *((unsigned short*)(ip + 1));
    } while (false);

    log(" ht-sig : mcs %X, length %d B.\n", *ht_frame_mcs, *ht_frame_length);

    consume(0, 6);

    return bRet;
  }
};