#pragma once


struct dsp_demapper
{
  /**
  * The constellation uses the gray code
  */
  static const int lut_bpsk_size  = 256;
  static const int lut_qpsk_size  = 256;
  static const int lut_16qam_size = 256;
  static const int lut_64qam_size = 288;

  static const v_cs::type DemapMin;
  static const v_cs::type DemapMax;

  static const v_cs::type Demap64qamMin;
  static const v_cs::type Demap64qamMax;

  static const unsigned __int8 lookup_table_bpsk[lut_bpsk_size];

  static const unsigned __int8 lookup_table_qpsk[lut_qpsk_size];

  static const unsigned __int8 lookup_table_16qam1[lut_16qam_size];
  static const unsigned __int8 lookup_table_16qam2[lut_16qam_size];

  static const unsigned __int8 lookup_table_64qam1[lut_64qam_size];
  static const unsigned __int8 lookup_table_64qam2[lut_64qam_size];
  static const unsigned __int8 lookup_table_64qam3[lut_64qam_size];

  static const unsigned __int8 *p_lookup_table_64qam1;
  static const unsigned __int8 *p_lookup_table_64qam2;
  static const unsigned __int8 *p_lookup_table_64qam3;

  dsp_demapper(){}

  __forceinline void demap_limit_bpsk(v_cs* pvcs, int vcount)
  {
    for (int i = 0; i < vcount; i++)
    {
      pvcs[i] = v_min(v_max((v_s&)pvcs[i], (v_s&)DemapMin), (v_s&)DemapMax);
    }
  }

  __forceinline void demap_limit_qpsk(v_cs* pvcs, int vcount)
  {
    for (int i = 0; i < vcount; i++)
    {
      pvcs[i] = v_min(v_max((v_s&)pvcs[i], (v_s&)DemapMin), (v_s&)DemapMax);
    }
  }

  __forceinline void demap_limit_16qam(v_cs* pvcs, int vcount)
  {
    for (int i = 0; i < vcount; i++)
    {
      pvcs[i] = v_min(v_max((v_s&)pvcs[i], (v_s&)DemapMin), (v_s&)DemapMax);
    }
  }

  __forceinline void demap_limit_64qam(v_cs* pvcs, int vcount)
  {
    for (int i = 0; i < vcount; i++)
    {
      pvcs[i] = v_min(v_max((v_s&)pvcs[i], (v_s&)Demap64qamMin), (v_s&)Demap64qamMax);
    }
  }

  __forceinline void demap_bpsk_i(complex16 &cinput, unsigned __int8* pOutput)
  {
    *pOutput = lookup_table_bpsk[(unsigned __int8)cinput.re];
  }
  __forceinline void demap_bpsk_q(complex16 &cinput, unsigned __int8* pOutput)
  {
    *pOutput = lookup_table_bpsk[(unsigned __int8)cinput.im];
  }

  __forceinline void demap_qpsk(complex16 &cinput, unsigned __int8* pOutput)
  {
    pOutput[0] = lookup_table_qpsk[(unsigned __int8)cinput.re];
    pOutput[1] = lookup_table_qpsk[(unsigned __int8)cinput.im];
  }

  __forceinline void demap_16qam(complex16 &cinput, unsigned __int8* pOutput)
  {
    pOutput[0] = lookup_table_16qam1[(unsigned __int8)cinput.re];
    pOutput[1] = lookup_table_16qam2[(unsigned __int8)cinput.re];
    pOutput[2] = lookup_table_16qam1[(unsigned __int8)cinput.im];
    pOutput[3] = lookup_table_16qam2[(unsigned __int8)cinput.im];
  }

  __forceinline void demap_64qam(complex16 &cinput, unsigned __int8* pOutput)
  {
    pOutput[0] = p_lookup_table_64qam1[cinput.re];
    pOutput[1] = p_lookup_table_64qam2[cinput.re];
    pOutput[2] = p_lookup_table_64qam3[cinput.re];

    pOutput[3] = p_lookup_table_64qam1[cinput.im];
    pOutput[4] = p_lookup_table_64qam2[cinput.im];
    pOutput[5] = p_lookup_table_64qam3[cinput.im];
  }
};
