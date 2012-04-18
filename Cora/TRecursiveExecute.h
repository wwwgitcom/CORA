#pragma once

template<typename T, typename T1>
__forceinline bool while_execute(T &my, T1 &t1)
{
  bool bRet = false;
  while(bRet = t1(my))
  ;
  return bRet;
}


template<typename T, typename T1, typename T2>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, typename T60>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59, T60 &t60)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, typename T60, typename T61>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59, T60 &t60, T61 &t61)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, typename T60, typename T61, typename T62>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59, T60 &t60, T61 &t61, T62 &t62)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61, t62);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, typename T60, typename T61, typename T62, typename T63>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59, T60 &t60, T61 &t61, T62 &t62, T63 &t63)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61, t62, t63);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, typename T60, typename T61, typename T62, typename T63, typename T64>
__forceinline bool while_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59, T60 &t60, T61 &t61, T62 &t62, T63 &t63, T64 &t64)
{
  bool bRet = false;
  while(bRet = t1(my))
  while_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61, t62, t63, t64);
  return bRet;
}


#pragma once

template<typename T, typename T1>
__forceinline bool if_execute(T &my, T1 &t1)
{
  bool bRet = false;
  if(bRet = t1(my))
  ;
  return bRet;
}


template<typename T, typename T1, typename T2>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, typename T60>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59, T60 &t60)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, typename T60, typename T61>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59, T60 &t60, T61 &t61)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, typename T60, typename T61, typename T62>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59, T60 &t60, T61 &t61, T62 &t62)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61, t62);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, typename T60, typename T61, typename T62, typename T63>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59, T60 &t60, T61 &t61, T62 &t62, T63 &t63)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61, t62, t63);
  return bRet;
}


template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, typename T60, typename T61, typename T62, typename T63, typename T64>
__forceinline bool if_execute(T &my, T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10, T11 &t11, T12 &t12, T13 &t13, T14 &t14, T15 &t15, T16 &t16, T17 &t17, T18 &t18, T19 &t19, T20 &t20, T21 &t21, T22 &t22, T23 &t23, T24 &t24, T25 &t25, T26 &t26, T27 &t27, T28 &t28, T29 &t29, T30 &t30, T31 &t31, T32 &t32, T33 &t33, T34 &t34, T35 &t35, T36 &t36, T37 &t37, T38 &t38, T39 &t39, T40 &t40, T41 &t41, T42 &t42, T43 &t43, T44 &t44, T45 &t45, T46 &t46, T47 &t47, T48 &t48, T49 &t49, T50 &t50, T51 &t51, T52 &t52, T53 &t53, T54 &t54, T55 &t55, T56 &t56, T57 &t57, T58 &t58, T59 &t59, T60 &t60, T61 &t61, T62 &t62, T63 &t63, T64 &t64)
{
  bool bRet = false;
  if(bRet = t1(my))
  if_execute(my, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61, t62, t63, t64);
  return bRet;
}


