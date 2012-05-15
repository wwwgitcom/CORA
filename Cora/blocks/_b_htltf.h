#pragma once
#include "dsp_vector1.h"
struct HT_LTF
{
  static const int SIZE   = 160 * sizeof(complex16);
  static const int COUNT  = 160;
  static const int VCOUNT = 160 / 4;
  static const int csd    = 4;// 16samples = 400ns, 40Mhz

  __forceinline void get_ltf_11(complex16* pout)
  {
    v_cs *pvin  = reinterpret_cast<v_cs*>(_ltf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);

    for (int i = 0; i < VCOUNT; i++)
    {
      pvout[i] = pvin[i];
    }
  }

  __forceinline void get_ltf_12(complex16* pout)
  {
    auto msk = VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_cs>();
    v_cs *pvin  = reinterpret_cast<v_cs*>(_ltf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);
    
    for (int i = 0; i < VCOUNT; i++)
    {
      v_cs temp;
      temp = v_xor(msk, pvin[i]);
      pvout[i] = v_sub(temp, msk);
    }
  }

  __forceinline void get_ltf_21(complex16* pout)
  {
    v_cs *pvin  = reinterpret_cast<v_cs*>(_ltf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);

    int i = 0;
    for (; i < 64; i++)
    {
      pvout[i + 16] = pvin[i + 16 - csd];
    }

    for (i = 0; i < 16; i++)
    {
      pvout[i] = pvout[80 - 16 + i];
    }
  }
  __forceinline void get_ltf_22(complex16* pout)
  {
    get_ltf_21(pout);
  }

private:
  static complex16::type _ltf[160];
};
