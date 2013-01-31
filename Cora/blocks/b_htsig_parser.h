#pragma once

DEFINE_BLOCK(b_htsig_parser_1v, 1, 0)
{
  _global_(uint16, ht_frame_length);
  _global_(uint32, ht_frame_mcs);
  _global_(bool, ht_sig_ok);

  crc::crc8 m_crc8;

  BLOCK_WORK
  {
    int n = ninput(0);
    if (n < 6) return false;

    auto ip = _$<unsigned __int8>(0);
    
    unsigned char  crc8value;
    
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
        printf(" ht-sig error: crc8 check failed %p, crc8 %p\n", *(uint32*)ip, crc8value);

        *ht_sig_ok = false;
        break;
      }

      *ht_frame_mcs    = (ip[0] & 0x7F);
      *ht_frame_length = *((unsigned short*)(ip + 1));
      *ht_sig_ok = true;
      printf(" ht-sig ok: sig=%x, mcs=%d, length=%d Bytes\n", *(uint32*)ip, *ht_frame_mcs, *ht_frame_length);
#if enable_dbgplot
      PlotText("[log]", " ht-sig ok: sig=%x, mcs=%d, length=%d Bytes\n", *(uint32*)ip, *ht_frame_mcs, *ht_frame_length);
#endif
    } while (false);

    consume(0, 6);

    return true;
  }
};