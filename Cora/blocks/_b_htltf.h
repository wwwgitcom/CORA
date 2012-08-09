#pragma once
#include "dsp_vector1.h"
struct HT_LTF
{
  static const int SIZE   = 160 * sizeof(complex16);
  static const int COUNT  = 160;
  static const int VCOUNT = 160 / 4;
  static const int csd    = 4;// 16samples = 400ns, 40Mhz

  //////////////////////////////////////////////////////////////////////////

  __forceinline void get_as_lltf(complex16* pout)
  {
    v_cs *pvin  = reinterpret_cast<v_cs*>(_ltf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);

    int i = 8; // start from data part
    int j = 16; // long cp, 16v_cs=64complex16
    for (; i < VCOUNT; i++, j++)
    {
      pvout[j] = pvin[i];
    }
    // repeat
    for (i = 8; i < VCOUNT; i++, j++)
    {
      pvout[j] = pvin[i];
    }

    i = VCOUNT - 16;
    j = 0;
    for (; i < VCOUNT; i++, j++)
    {
      pvout[j] = pvin[i];
    }
  }
  // 1 -1 1 1, csd = 0ns, 0 v_cs
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

  __forceinline void get_ltf_13(complex16* pout)
  {
    get_ltf_11(pout);
  }

  __forceinline void get_ltf_14(complex16* pout)
  {
    get_ltf_11(pout);
  }
  //////////////////////////////////////////////////////////////////////////
  // 1 1 -1 1, csd = 400ns, 4 v_cs
  __forceinline void get_ltf_21(complex16* pout)
  {
    v_cs *pvin  = reinterpret_cast<v_cs*>(_ltf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);
    static const int _csd = 4;
    int i = 0;
    for (; i < 32; i++)
    {
      pvout[i + 8] = pvin[i + 8 - _csd];
    }

    for (i = 0; i < 8; i++)
    {
      pvout[i] = pvout[VCOUNT - 8 + i];
    }
  }
  __forceinline void get_ltf_22(complex16* pout)
  {
    get_ltf_21(pout);
  }
  __forceinline void get_ltf_23(complex16* pout)
  {
    auto msk = VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_cs>();
    v_cs *pvin  = reinterpret_cast<v_cs*>(_ltf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);
    static const int _csd = 4;
    v_cs temp;

    int i = 0;
    for (; i < 32; i++)
    {
      temp = v_xor(msk, pvin[i + 8 - _csd]);
      pvout[i + 8] = v_sub(temp, msk);
    }

    for (i = 0; i < 8; i++)
    {
      pvout[i] = pvout[VCOUNT - 8 + i];
    }
  }
  __forceinline void get_ltf_24(complex16* pout)
  {
    get_ltf_21(pout);
  }
  //////////////////////////////////////////////////////////////////////////
  // 1 1 1 -1, csd = 200ns, 2 v_cs
  __forceinline void get_ltf_31(complex16* pout)
  {
    v_cs *pvin  = reinterpret_cast<v_cs*>(_ltf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);
    static const int _csd = 2;
    int i = 0;
    for (; i < 32; i++)
    {
      pvout[i + 8] = pvin[i + 8 - _csd];
    }

    for (i = 0; i < 8; i++)
    {
      pvout[i] = pvout[VCOUNT - 8 + i];
    }
  }
  __forceinline void get_ltf_32(complex16* pout)
  {
    get_ltf_31(pout);
  }
  __forceinline void get_ltf_33(complex16* pout)
  {
    get_ltf_31(pout);
  }
  __forceinline void get_ltf_34(complex16* pout)
  {
    auto msk = VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_cs>();
    v_cs *pvin  = reinterpret_cast<v_cs*>(_ltf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);
    static const int _csd = 2;
    v_cs temp;

    int i = 0;
    for (; i < 32; i++)
    {
      temp = v_xor(msk, pvin[i + 8 - _csd]);
      pvout[i + 8] = v_sub(temp, msk);
    }

    for (i = 0; i < 8; i++)
    {
      pvout[i] = pvout[VCOUNT - 8 + i];
    }    
  }
  //////////////////////////////////////////////////////////////////////////
  // -1 1 1 1, csd = 600ns, 6 v_cs
  __forceinline void get_ltf_41(complex16* pout)
  {
    auto msk = VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_cs>();
    v_cs *pvin  = reinterpret_cast<v_cs*>(_ltf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);
    static const int _csd = 6;
    v_cs temp;

    int i = 0;
    for (; i < 32; i++)
    {
      temp = v_xor(msk, pvin[i + 8 - _csd]);
      pvout[i + 8] = v_sub(temp, msk);
    }

    for (i = 0; i < 8; i++)
    {
      pvout[i] = pvout[VCOUNT - 8 + i];
    }    
  }
  __forceinline void get_ltf_42(complex16* pout)
  {
    v_cs *pvin  = reinterpret_cast<v_cs*>(_ltf);
    v_cs *pvout = reinterpret_cast<v_cs*>(pout);
    static const int _csd = 6;
    int i = 0;
    for (; i < 32; i++)
    {
      pvout[i + 8] = pvin[i + 8 - _csd];
    }

    for (i = 0; i < 8; i++)
    {
      pvout[i] = pvout[VCOUNT - 8 + i];
    }
  }
  __forceinline void get_ltf_43(complex16* pout)
  {
    get_ltf_42(pout);
  }
  __forceinline void get_ltf_44(complex16* pout)
  {
    get_ltf_42(pout);
  }

private:
  static complex16::type _ltf[160];
};
