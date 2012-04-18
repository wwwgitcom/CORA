#pragma once

#include "dsp_vector1.h"

typedef struct _signal_block
{
  static const int v_datacount  = 7;
  static const int v_size       = 128;
  static const int v_datasize   = 112;
  static const int v_headersize = 16;

  unsigned char header[v_headersize];
  v_cs          v_data[v_datacount];
  v_cs&         operator[](int index) { return v_data[index]; }
  const v_cs&   operator[](int index) const { return v_data[index]; }
}signal_block, *psignal_block;

template<int streamcnt, int sbcntperstream>
struct dsp_stream
{
  int sourcetype;
  int sbcnt;
  int sbidx;

  psignal_block psb[streamcnt];

  signal_block* get(int streamid, int sbid)
  {
    return &psb[streamid][sbid];
  }

  __forceinline int currentsbidx()
  {
    return sbidx;
  }

  __forceinline int operator++()
  {
    sbidx++;
    if (sbidx == sbcnt)
    {
      sbidx = 0;
      exit(0);// user mode only
    }
    return sbidx;
  }

  dsp_stream()
  {
    for (int i = 0; i < streamcnt; i++)
    {
      psb[i] = (psignal_block)_aligned_malloc(sbcntperstream * sizeof(signal_block), 64);
      if (NULL == psb[i])
      {
        printf("Not enough memory! Allocating source %d of %d bytes!\n", i, sbcntperstream);
        sbcnt = 0;
      }
      else
      {
        sbcnt = sbcntperstream;
      }
      sbidx = 0;
    }
  }

  ~dsp_stream()
  {
    for (int i = 0; i < streamcnt; i++)
    {
      if (NULL != psb[i])
      {
        _aligned_free(psb[i]);
        psb[i] = NULL;
      }
    }
    sbcnt = 0;
    sbidx = 0;
  }

  bool load(char* filenames[streamcnt])
  {
    for (int i = 0; i < streamcnt; i++)
    {
      FILE* fp;
      fopen_s(&fp, filenames[i], "rb");
      if (!fp)
      {
        return false;
      }

      sbidx = 0;

      while ( !feof(fp) && sbidx < sbcnt )
      {
        fread(&psb[i][sbidx], sizeof(signal_block), 1, fp);
        sbidx++;
      }

      //printf("Total %d sb loaded for stream %d!\n", sbidx, i);

      fclose(fp);
    }
    sbidx = 0;
    return true;
  }
};
