#pragma once

DEFINE_BLOCK(b_lsig_parser_1v, 1, 0)
{
  _global_(bool, l_sig_ok);
  _global_(uint16, l_frame_length);
  _global_(uint32, l_frame_rate);
  _global_(uint32, l_frame_dbps);

  BLOCK_WORK
  {
    int n = ninput(0);
    if (n < 3) return false;

    auto ip = _$<unsigned __int8>(0);

    unsigned int uiParity = 0;
    unsigned int uiSignal = 0;

    uiSignal = *((unsigned int*)ip);

    // signal rate look up table
    static const unsigned int g11a_rguiDBPSLookUp[16] = {
      /* R1-4 */
      /* 0000 */ 0,
      /* 1000 */ 0,
      /* 0100 */ 0,
      /* 1100 */ 0,
      /* 0010 */ 0,
      /* 1010 */ 0,
      /* 0110 */ 0,
      /* 1110 */ 0,

      /* 0001 */ 192,
      /* 1001 */ 96,
      /* 0101 */ 48,
      /* 1101 */ 24,
      /* 0011 */ 216,
      /* 1011 */ 144,
      /* 0111 */ 72,
      /* 1111 */ 36
    };



    do 
    {
      uiSignal &= 0xFFFFFF;
      if (uiSignal & 0xFC0010) // all these bits should be always zero
      {
        printf(" l-sig error: unexpected value %p\n", uiSignal);
        *l_sig_ok = false;
        break;
      }

      uiParity = (uiSignal >> 16) ^ (uiSignal);
      uiParity = (uiParity >> 8) ^ (uiParity);
      uiParity = (uiParity >> 4) ^ (uiParity);
      uiParity = (uiParity >> 2) ^ (uiParity);
      uiParity = (uiParity >> 1) ^ (uiParity);
      if (uiParity & 0x1)
      {
        printf(" l-sig error: parity check fail, signal %X\n", uiSignal);
        *l_sig_ok = false;
        break;
      }

      (*l_frame_rate) = uiSignal & 0xF;
      if (!((*l_frame_rate) & 0x8))
      {
        printf(" l-sig error: unexpected data rate %X, signal %X\n", *l_frame_rate, uiSignal);
        *l_sig_ok = false;
        break;
      }

      (*l_frame_length) = (uiSignal >> 5) & 0xFFF;
      (*l_frame_dbps) = g11a_rguiDBPSLookUp[*l_frame_rate];

      *l_sig_ok = true;
      
      printf(" l-sig ok: signal %x, rate %x, length %d B, dbps = %d\n", uiSignal, *l_frame_rate, *l_frame_length, *l_frame_dbps);
    } while (false);

    consume(0, 3);
    return true;
  }
};