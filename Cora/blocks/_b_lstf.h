#pragma once
#include "dsp_vector1.h"
struct L_STF
{
  static const int SIZE   = 160 * 2 * sizeof(complex16);
  static const int COUNT  = 160 * 2;
  static const int VCOUNT = 160 * 2 / 4;
  static const int csd = 2;

  __forceinline void get_stf_1(complex16* pout)
  {
    v_cs *pvin  = reinterpret_cast<v_cs*>(_stf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);

    for (int i = 0; i < VCOUNT; i++)
    {
      pvout[i] = pvin[i];
    }
  }

  __forceinline void get_stf_2(complex16* pout)
  {
    v_cs *pvin  = reinterpret_cast<v_cs*>(_stf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);
        
    int i = 0;
    for (; i < VCOUNT - csd; i++)
    {
      pvout[i + csd] = pvin[i];
    }
    for (int j = 0; i < VCOUNT; i++, j++)
    {
      pvout[j] = pvin[i];
    }
  }

private:
  static complex16::type _stf[160 * 2];
};
