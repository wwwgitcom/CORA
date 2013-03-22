#pragma once

DEFINE_BLOCK(b_fir_ss_1v1, 1, 1)
{
  short nTap;
  short *coeff;

  BLOCK_INIT
  {
    auto v = $["TapCount"];

    if (!v.empty()) 
      nTap = atoi(v.c_str());
    else
    {
      nTap = 16;
    }

    coeff = (short*)_aligned_malloc(nTap * sizeof(short) * 2, 64);
    assert(coeff != nullptr);
  }

  void set_coeff(short * p)
  {
    // ... do nothing here
    // just randn something for exp.
    srand(GetTickCount());
    for (int i = 0; i < nTap * 2; i++)
    {
      //coeff[i] = rand() % 32765;
      coeff[i] = 1;
    }
  }

  BLOCK_WORK
  {
    auto nin = ninput(0);

    if (nin < nTap * 2)
    {
      return false;
    }

    auto ip = _$<short>(0);
    auto op = $_<short>(0);

    // fake imp...
    // coeff should be inversed
    int isum1 = 0;
    int isum2 = 0;
    for (int i = 0; i < nTap * 2; i += 2)
    {
      int icoeff = coeff[i];
      int iinput = ip[i];

      isum1 += icoeff * iinput;

      icoeff = coeff[i + 1];
      iinput = ip[i + 1];

      isum2 += icoeff * iinput;
    }

    op[0] = isum1 >> 16;
    op[1] = isum2 >> 16;

    consume(0, 2);
    produce(0, 2);

    return true;
  }
};


DEFINE_BLOCK(b_fir_vsvs_1v1, 1, 1)
{
  short nTap;
  v_s *coeff;
  v_s *tempsum;

  BLOCK_INIT
  {
    auto v = $["TapCount"];

    if (!v.empty()) 
      nTap = atoi(v.c_str());
    else
    {
      nTap = 16;
    }

    coeff   = (v_s*)_aligned_malloc((nTap + 4) * sizeof(v_s), 64);
    tempsum = (v_s*)_aligned_malloc((nTap + 4) * sizeof(v_s), 64);
    assert(coeff   != nullptr);
    assert(tempsum != nullptr);
  }

  void set_coeff(short * p)
  {
    // ... do nothing here
    // just randn something for exp.
    srand(GetTickCount());
    for (int i = 0; i < nTap + 4; i++)
    {
      //coeff[i] = rand() % 32765;
      coeff[i].v_ones();
    }
  }

  BLOCK_WORK
  {
    auto nin = ninput(0);

    if (nin < 1)
    {
      return false;
    }

    auto ip = _$<v_s>(0);
    auto op = $_<v_s>(0);

    // fake imp...
    // coeff should be inversed
    for (int i = 0; i < nin; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        v_s vTemp = v_mul_lo(ip[i], coeff[j]);
        vTemp = v_add(vTemp, tempsum[j]);
      }

      op[i] = (v_s&)v_hsum((v_cs&)tempsum[0], (v_cs&)tempsum[1], (v_cs&)tempsum[2], (v_cs&)tempsum[3]);
      
      for (int j = 4; j < nTap + 4; j++)
      {
        v_s vTemp = v_mul_lo(ip[i], coeff[j]);
        tempsum[j - 4] = v_add(vTemp, tempsum[j]);
      }
    }

    consume(0, nin);
    produce(0, nin);

    return true;
  }
};