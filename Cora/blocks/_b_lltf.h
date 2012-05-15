#pragma once
#include "dsp_vector1.h"

struct L_LTF
{
  static const int SIZE   = 160 * 2 * sizeof(complex16);
  static const int COUNT  = 160 * 2;
  static const int VCOUNT = 160 * 2 / 4;
  static const int csd = 2;

  __forceinline void get_ltf_1(complex16* pout)
  {
    v_cs *pvin  = reinterpret_cast<v_cs*>(_ltf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);

    for (int i = 0; i < VCOUNT; i++)
    {
      pvout[i] = pvin[i];
    }
  }

  __forceinline void get_ltf_2(complex16* pout)
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
private:
  static complex16::type _ltf[160 * 2];
};