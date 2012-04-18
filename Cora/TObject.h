#pragma once

#define ObjectNew new(_aligned_malloc(sizeof(T), __alignof(T)))

template<typename T>
T & CreateObject()
{
  return (T&)(*(ObjectNew T()));
}
template<typename T, typename P1>
T & CreateObject(P1 &p1)
{
  return  (T&)(*(ObjectNew T(p1)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2>
T & CreateObject(P1 &p1, P2 &p2)
{
  return  (T&)(*(ObjectNew T(p1, p2)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53, typename P54>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53, P54 &p54)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53, p54)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53, typename P54, typename P55>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53, P54 &p54, P55 &p55)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53, p54, p55)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53, typename P54, typename P55, typename P56>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53, P54 &p54, P55 &p55, P56 &p56)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53, p54, p55, p56)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53, typename P54, typename P55, typename P56, typename P57>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53, P54 &p54, P55 &p55, P56 &p56, P57 &p57)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53, typename P54, typename P55, typename P56, typename P57, typename P58>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53, P54 &p54, P55 &p55, P56 &p56, P57 &p57, P58 &p58)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53, typename P54, typename P55, typename P56, typename P57, typename P58, typename P59>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53, P54 &p54, P55 &p55, P56 &p56, P57 &p57, P58 &p58, P59 &p59)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58, p59)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53, typename P54, typename P55, typename P56, typename P57, typename P58, typename P59, typename P60>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53, P54 &p54, P55 &p55, P56 &p56, P57 &p57, P58 &p58, P59 &p59, P60 &p60)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58, p59, p60)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53, typename P54, typename P55, typename P56, typename P57, typename P58, typename P59, typename P60, typename P61>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53, P54 &p54, P55 &p55, P56 &p56, P57 &p57, P58 &p58, P59 &p59, P60 &p60, P61 &p61)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58, p59, p60, p61)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53, typename P54, typename P55, typename P56, typename P57, typename P58, typename P59, typename P60, typename P61, typename P62>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53, P54 &p54, P55 &p55, P56 &p56, P57 &p57, P58 &p58, P59 &p59, P60 &p60, P61 &p61, P62 &p62)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58, p59, p60, p61, p62)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53, typename P54, typename P55, typename P56, typename P57, typename P58, typename P59, typename P60, typename P61, typename P62, typename P63>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53, P54 &p54, P55 &p55, P56 &p56, P57 &p57, P58 &p58, P59 &p59, P60 &p60, P61 &p61, P62 &p62, P63 &p63)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58, p59, p60, p61, p62, p63)));
}

//---------------------------------------------

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32, typename P33, typename P34, typename P35, typename P36, typename P37, typename P38, typename P39, typename P40, typename P41, typename P42, typename P43, typename P44, typename P45, typename P46, typename P47, typename P48, typename P49, typename P50, typename P51, typename P52, typename P53, typename P54, typename P55, typename P56, typename P57, typename P58, typename P59, typename P60, typename P61, typename P62, typename P63, typename P64>
T & CreateObject(P1 &p1, P2 &p2, P3 &p3, P4 &p4, P5 &p5, P6 &p6, P7 &p7, P8 &p8, P9 &p9, P10 &p10, P11 &p11, P12 &p12, P13 &p13, P14 &p14, P15 &p15, P16 &p16, P17 &p17, P18 &p18, P19 &p19, P20 &p20, P21 &p21, P22 &p22, P23 &p23, P24 &p24, P25 &p25, P26 &p26, P27 &p27, P28 &p28, P29 &p29, P30 &p30, P31 &p31, P32 &p32, P33 &p33, P34 &p34, P35 &p35, P36 &p36, P37 &p37, P38 &p38, P39 &p39, P40 &p40, P41 &p41, P42 &p42, P43 &p43, P44 &p44, P45 &p45, P46 &p46, P47 &p47, P48 &p48, P49 &p49, P50 &p50, P51 &p51, P52 &p52, P53 &p53, P54 &p54, P55 &p55, P56 &p56, P57 &p57, P58 &p58, P59 &p59, P60 &p60, P61 &p61, P62 &p62, P63 &p63, P64 &p64)
{
  return  (T&)(*(ObjectNew T(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58, p59, p60, p61, p62, p63, p64)));
}

//---------------------------------------------

