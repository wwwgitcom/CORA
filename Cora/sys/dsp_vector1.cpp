#include "stdafx.h"
#include "dsp_Vector1.h"

unsigned long v_lzcnt_s(__int16 s)
{
  unsigned long zn;
  char isNonzero;

  isNonzero = _BitScanReverse(&zn, s);
  if (isNonzero)
  {
    return 15 - zn;
  }
  else return 16;
}

unsigned long v_lzcnt_i(__int32 i)
{
  unsigned long zn;
  char isNonzero;

  isNonzero = _BitScanReverse(&zn, i);
  if (isNonzero)
  {
    return 31 - zn;
  }
  else return 32;
}

unsigned long v_lzcnt_q(__int64 q)
{
  unsigned long zn;
  char isNonzero;

  isNonzero = _BitScanReverse( &zn, (__int32)(q >> 32) );
  if (isNonzero)
  {
    return 31 - zn;
  }
  else 
  {
    isNonzero = _BitScanReverse( &zn, (__int32)(q) );
    if (isNonzero)
    {
      return 63 - zn;
    }
    else
    {
      return 64;
    }
  }
}

//////////////////////////////////////////////////////////////////////////