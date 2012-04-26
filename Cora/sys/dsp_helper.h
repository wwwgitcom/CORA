#pragma once

#include "dsp_vector1.h"
#include "math.h"

__forceinline
  VOID
  InitializeListHead(
  PLIST_ENTRY ListHead
  )
{
  ListHead->Flink = ListHead->Blink = ListHead;
}

BOOLEAN
  __forceinline
  IsListEmpty(
  const LIST_ENTRY * ListHead
  )
{
  return (BOOLEAN)(ListHead->Flink == ListHead);
}

__forceinline
  BOOLEAN
  RemoveEntryList(
  PLIST_ENTRY Entry
  )
{
  PLIST_ENTRY Blink;
  PLIST_ENTRY Flink;

  Flink = Entry->Flink;
  Blink = Entry->Blink;
  Blink->Flink = Flink;
  Flink->Blink = Blink;
  return (BOOLEAN)(Flink == Blink);
}

__forceinline
  PLIST_ENTRY
  RemoveHeadList(
  PLIST_ENTRY ListHead
  )
{
  PLIST_ENTRY Flink;
  PLIST_ENTRY Entry;

  Entry           = ListHead->Flink;
  Flink           = Entry->Flink;
  ListHead->Flink = Flink;
  Flink->Blink    = ListHead;
  return Entry;
}



__forceinline
  PLIST_ENTRY
  RemoveTailList(
  PLIST_ENTRY ListHead
  )
{
  PLIST_ENTRY Blink;
  PLIST_ENTRY Entry;

  Entry = ListHead->Blink;
  Blink = Entry->Blink;
  ListHead->Blink = Blink;
  Blink->Flink = ListHead;
  return Entry;
}


__forceinline
  void
  InsertTailList(
  PLIST_ENTRY ListHead,
  PLIST_ENTRY Entry
  )
{
  PLIST_ENTRY Blink;

  Blink = ListHead->Blink;
  Entry->Flink = ListHead;
  Entry->Blink = Blink;
  Blink->Flink = Entry;
  ListHead->Blink = Entry;
}


__forceinline
  void
  InsertHeadList(
  PLIST_ENTRY ListHead,
  PLIST_ENTRY Entry
  )
{
  PLIST_ENTRY Flink;

  Flink = ListHead->Flink;
  Entry->Flink = Flink;
  Entry->Blink = ListHead;
  Flink->Blink = Entry;
  ListHead->Flink = Entry;
}

__forceinline
  void
  AppendTailList(
  PLIST_ENTRY ListHead,
  PLIST_ENTRY ListToAppend
  )
{
  PLIST_ENTRY ListEnd = ListHead->Blink;

  ListHead->Blink->Flink = ListToAppend;
  ListHead->Blink = ListToAppend->Blink;
  ListToAppend->Blink->Flink = ListHead;
  ListToAppend->Blink = ListEnd;
}

//////////////////////////////////////////////////////////////////////////


struct dsp_spin_lock 
{
  volatile ULONG _lock;
  dsp_spin_lock(){_lock = 0;}

  void Acquire()
  {
    ULONG v;
    while (TRUE)
    {
      v = InterlockedExchange(&_lock, 1);
      if (v == 0)// success
      {
        break;
      }
    }
  }

  void Release()
  {
    _lock = 0;
  }
};


//////////////////////////////////////////////////////////////////////////

template<typename T>
__inline T CMax(T* p, int N)
{
  T _max;
  _max.re = _max.im = 0;
  for (int i = 0; i < N; i++)
  {
    if (abs(p[i].re) > _max.re)
    {
      _max.re = abs(p[i].re);
    }

    if (abs(p[i].im) > _max.im)
    {
      _max.im = abs(p[i].im);
    }
  }
  return _max;
}

template<>
__inline complexf CMax(complexf* p, int N)
{
  complexf _max;
  _max.re = _max.im = 0;
  for (int i = 0; i < N; i++)
  {
    if (fabs(p[i].re) > _max.re)
    {
      _max.re = fabs(p[i].re);
    }

    if (fabs(p[i].im) > _max.im)
    {
      _max.im = fabs(p[i].im);
    }
  }
  return _max;
}

template<>
__inline complexd CMax(complexd* p, int N)
{
  complexd _max;
  _max.re = _max.im = 0;
  for (int i = 0; i < N; i++)
  {
    if (fabs(p[i].re) > _max.re)
    {
      _max.re = fabs(p[i].re);
    }

    if (fabs(p[i].im) > _max.im)
    {
      _max.im = fabs(p[i].im);
    }
  }
  return _max;
}

template<typename T>
__inline float CSqrtMax(T* p, int N)
{
  float _max = 0;

  for (int i = 0; i < N; i++)
  {
    float x = p[i].re;
    float y = p[i].im;

    float e = x * x + y * y;
    e = sqrt(e);

    if (e > _max)
    {
      _max = e;
    }
  }
  return _max;
}

template<typename T>
__inline T PeakOfArray(T* p, int N)
{
  T _max;
  _max = 0;
  for (int i = 0; i < N; i++)
  {
    if (abs(p[i]) > _max)
    {
      _max = p[i];
    }
  }
  return _max;
}

template<>
__inline float PeakOfArray(float* p, int N)
{
  float _max;
  _max = 0;
  for (int i = 0; i < N; i++)
  {
    if (fabs(p[i]) > _max)
    {
      _max = p[i];
    }
  }
  return _max;
}

template<>
__inline double PeakOfArray(double* p, int N)
{
  double _max;
  _max = 0;
  for (int i = 0; i < N; i++)
  {
    if (fabs(p[i]) > _max)
    {
      _max = p[i];
    }
  }
  return _max;
}