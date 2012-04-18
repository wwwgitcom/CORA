#pragma once

#include <intrin.h>
#include <mmintrin.h>
#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <nmmintrin.h>
#include <pmmintrin.h>
#include <smmintrin.h>
#include <tmmintrin.h>
#include <wmmintrin.h>

#include "dsp_complex.h"

#ifdef __cplusplus
extern "C" extern __m128i _mm_sign_epi16 (__m128i a, __m128i b);
extern "C" extern __m128i _mm_abs_epi8 (__m128i a);
extern "C" extern __m128i _mm_abs_epi16 (__m128i a);
extern "C" extern __m128i _mm_abs_epi32 (__m128i a);
extern "C" extern __m128i _mm_abs_epi64 (__m128i a);
#else
extern __m128i _mm_sign_epi16 (__m128i a, __m128i b);
extern __m128i _mm_abs_epi8 (__m128i a);
extern __m128i _mm_abs_epi16 (__m128i a);
extern __m128i _mm_abs_epi32 (__m128i a);
extern __m128i _mm_abs_epi64 (__m128i a);
#endif

//////////////////////////////////////////////////////////////////////////
#define __SSE4__
#define __SSSE3__
//////////////////////////////////////////////////////////////////////////
#define v_align(n) __declspec(align(n))
#pragma region vector1 base
template<typename T>
struct __declspec(align(16)) vector1
{
  const static int elem_cnt  = sizeof(__m128) / sizeof(T);
  const static int size      = sizeof(__m128);
  static_assert(elem_cnt >=1  && elem_cnt <= 16, "vector1 element count must be in the range [1, 16]");
  typedef vector1<T> _Myt;
  typedef T __declspec(align(16)) type[elem_cnt];

  union
  {
    __m128i m128i;
    __m128  m128;
    __m128d m128d;
  };
  __forceinline void v_load(void *p){ this->m128i  = _mm_load_si128((__m128i*)p); }
  __forceinline void v_loadu(void *p){ this->m128i = _mm_loadu_si128((__m128i*)p); }
#ifdef __SSE4__
  __forceinline void v_lddqu(void *p){ this->m128i = _mm_lddqu_si128((__m128i*)p); }
#else
  __forceinline void v_lddqu(void *p){ this->m128i = _mm_loadu_si128((__m128i*)p); }
#endif
#ifdef __SSE4__
  __forceinline void v_loadnt(void *p){ this->m128i = _mm_stream_load_si128((__m128i*)p); }
#else
  __forceinline void v_loadnt(void *p){ this->m128i = _mm_load_si128((__m128i*)p); }
#endif

  // *p = _vec1
  __forceinline void v_store(void *p){ _mm_store_si128((__m128i*)p, this->m128i); }
  __forceinline void v_storeu(void *p){ _mm_storeu_si128((__m128i*)p, this->m128i); }
  __forceinline void v_storent(void *p){ _mm_stream_si128((__m128i*)p, this->m128i); }

  //////////////////////////////////////////////////////////////////////////
  // unary operations
  __forceinline void v_zero (){ this->m128   = _mm_setzero_ps(); }
  __forceinline void v_ones (){ this->m128i  = _mm_cmpeq_epi64(this->m128i, this->m128i); }

  template<int nBytes>
  __forceinline _Myt v_shift_bytes_left(){ _Myt c; c.m128i  = _mm_slli_si128(this->m128i, nBytes); return c; }

  template<int nBytes>
  __forceinline _Myt v_shift_bytes_right(){ _Myt c; c.m128i = _mm_srli_si128(this->m128i, nBytes); return c; }

  __forceinline T& operator[](int idx){ return ((T*)&(this->m128i))[idx]; }
};
#pragma endregion vector1 base

//////////////////////////////////////////////////////////////////////////

#define v_ctor(mytype)\
  __forceinline mytype(){};\
  __forceinline mytype(const type &d){this->m128i = *(__m128i*)d;}\
  __forceinline mytype(type &d){this->m128i = *(__m128i*)d;}\
  __forceinline mytype(const mytype &d){this->m128i = d.m128i;}\
  __forceinline mytype(const char *p){this->m128i  = _mm_load_si128((__m128i*)p);}\
  __forceinline mytype(const unsigned char *p){this->m128i  = _mm_load_si128((__m128i*)p);}\
  __forceinline mytype(__m128  &d){this->m128 = d;}\
  __forceinline mytype(__m128i &d){this->m128i = d;}\
  __forceinline mytype(__m128d &d){this->m128d = d;}\
  template<typename OT> __forceinline mytype(vector1<OT> &v){ this->m128i = v.m128i; }\
  __forceinline mytype& operator=(const mytype &d){this->m128i = d.m128i; return (*this);}\
  __forceinline mytype& operator=(const __m128  &d){this->m128 = d; return (*this);}\
  __forceinline mytype& operator=(const __m128i &d){this->m128i = d; return (*this);}\
  __forceinline mytype& operator=(const __m128d &d){this->m128d = d; return (*this);}\
  __forceinline mytype& operator=(const type &d){this->m128i = *(__m128i*)d; return (*this);}\
  __forceinline mytype& operator=(type &d){this->m128i = *(__m128i*)d; return (*this);}\
  template<typename OT> __forceinline mytype& operator=(vector1<OT> &d){ this->m128i = d.m128i;  return (*this);}


#pragma region forward declarations
struct v_b;  struct v_ub;    struct v_cb; struct v_cub;

struct v_s;  struct v_us;    struct v_cs; struct v_cus;

struct v_i;  struct v_ui;    struct v_ci; struct v_cui;

struct v_q;  struct v_uq;    struct v_cq; struct v_cuq;

struct v_f;  struct v_cf;    struct v_q;  struct v_cq;

#pragma endregion forward declarations


#pragma region "v_b"
struct v_b : public vector1<signed __int8>
{
  v_ctor(v_b);

  __forceinline v_b& v_set(char b0, char b1, char b2, char b3, char b4, char b5, char b6, char b7, char b8, char b9, char b10, char b11, char b12, char b13, char b14, char b15){ this->m128i = _mm_set_epi8(b15, b14, b13, b12, b11, b10, b9, b8, b7, b6, b5, b4, b3, b2, b1, b0);  return (*this); }
  __forceinline v_b& v_setall(char b){ this->m128i = _mm_set1_epi8(b);  return (*this); }

  template<int idx>
  __forceinline v_b& v_set_at(int value){ this->m128i = _mm_insert_epi8(this->m128i, value, idx);  return (*this); }
  template<int idx>
  __forceinline int v_get_at(){ return _mm_extract_epi8(this->m128i, idx); }


  __forceinline v_b  v_abs(){ v_b c; c.m128i = _mm_abs_epi8(this->m128i); return c; }
  __forceinline v_b  v_signmsk();
  __forceinline int  v_signmask();

  // if     b[7:0] <  0 then c[7:0]                        = neg(a[7:0])
  // elseif b[7:0]                                         == 0 then c[7:0] = 0
  // elseif b[7:0] >  0 then c[7:0]                        = a[7:0]
  __forceinline v_b v_neg_if_less0 (v_b &a){ v_b c; c.m128i= _mm_sign_epi8(this->m128i, a.m128i); return c; }
  __forceinline v_b v_neg_if_less0 (){ v_b c; c.m128i= _mm_sign_epi8(this->m128i, this->m128i); return c; }
  __forceinline v_b v_shuffle(v_b &msk){ v_b c; c.m128i    = _mm_shuffle_epi8(this->m128i, msk.m128i); return c; }


  __forceinline v_b  v_hsum()
  { 
    v_b temp, sum;
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(2, 3, 0, 1));
    sum.m128i  = _mm_add_epi8(this->m128i, temp.m128i);
    temp.m128i = _mm_shuffle_epi32(sum.m128i, _MM_SHUFFLE(1, 0, 3, 2));
    sum.m128i  = _mm_add_epi8(temp.m128i, sum.m128i);
    temp.m128i = _mm_shufflelo_epi16(sum.m128i, _MM_SHUFFLE(2, 3, 0, 1));
    sum.m128i  = _mm_add_epi8(temp.m128i, sum.m128i);
    temp.m128i = _mm_srli_si128(sum.m128i, 1);
    sum.m128i  = _mm_add_epi8(temp.m128i, sum.m128i);
    sum.m128i  = _mm_shuffle_epi32(sum.m128i, 0);
    return sum;
  }

  __forceinline v_b v_hsums()
  { 
    v_b temp, sum;
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(2, 3, 0, 1));
    sum.m128i  = _mm_adds_epi8(this->m128i, temp.m128i);
    temp.m128i = _mm_shuffle_epi32(sum.m128i, _MM_SHUFFLE(1, 0, 3, 2));
    sum.m128i  = _mm_adds_epi8(temp.m128i, sum.m128i);
    temp.m128i = _mm_shufflelo_epi16(sum.m128i, _MM_SHUFFLE(2, 3, 0, 1));
    sum.m128i  = _mm_adds_epi8(temp.m128i, sum.m128i);
    temp.m128i = _mm_srli_si128(sum.m128i, 1);
    sum.m128i  = _mm_adds_epi8(temp.m128i, sum.m128i);
    sum.m128i  = _mm_shuffle_epi32(sum.m128i, 0);
    return sum;
  }


  //////////////////////////////////////////////////////////////////////////
  __forceinline v_s  v_convert2s_lo();
  __forceinline v_s  v_convert2s_hi();
  template<int nByteOffset>
  __forceinline v_s  v_convert2s_offset();
  __forceinline void v_convert2s(v_s &s0, v_s &s1);
  template<int nByteOffset>
  __forceinline v_i  v_convert2i_offset();
  __forceinline void v_convert2i(v_i &i0, v_i &i1, v_i &i2, v_i &i3);
  template<int nByteOffset>
  __forceinline v_q  v_convert2q_offset();
  __forceinline void v_convert2q(v_q &q0, v_q &q1, v_q &q2, v_q &q3, v_q &q4, v_q &q5, v_q &q6, v_q &q7);

  __forceinline v_s v_hsum2s();
  __forceinline v_s v_hsums2s();
  __forceinline void sqr2s(v_s &s0, v_s &s1);
};

#pragma endregion

#pragma region "v_ub"
struct v_ub : public vector1<unsigned __int8>
{
  v_ctor(v_ub);

  __forceinline v_ub& v_set(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4, unsigned char b5, unsigned char b6, unsigned char b7, unsigned char b8, unsigned char b9, unsigned char b10, unsigned char b11, unsigned char b12, unsigned char b13, unsigned char b14, unsigned char b15){ this->m128i = _mm_set_epi8(b15, b14, b13, b12, b11, b10, b9, b8, b7, b6, b5, b4, b3, b2, b1, b0);  return (*this); }
  __forceinline v_ub& v_setall(unsigned char b){ this->m128i = _mm_set1_epi8(b);  return (*this); }

  template<int idx>
  __forceinline v_ub& v_set_at(int value){ this->m128i = _mm_insert_epi8(this->m128i, value, idx);  return (*this); }
  template<int idx>
  __forceinline int v_get_at(){ return _mm_extract_epi8(this->m128i, idx); }

  __forceinline v_ub v_shuffle(v_ub &msk){ v_ub c; c.m128i    = _mm_shuffle_epi8(this->m128i, msk.m128i); return c; }


  __forceinline unsigned __int8& operator[](int idx){ return this->m128i.m128i_u8[idx]; }
};

#pragma endregion
#pragma region "v_cb"
struct v_cb : public vector1<complex8>
{
  v_ctor(v_cb);

  template<int idx>
  __forceinline v_cb& v_set_at(complex8 &value){ this->m128i = _mm_insert_epi16(this->m128i, value._r, idx);  return (*this); }
  template<int idx>
  __forceinline complex8 v_get_at(){ return _mm_extract_epi16(this->m128i, idx); }

  __forceinline v_cb v_shuffle(char a0, char a1, char a2, char a3, char a4, char a5, char a6, char a7);

  __forceinline void v_convert2cs(v_cs &c0, v_cs &c1);

  __forceinline v_cb v_hsum()
  { 
    v_cb temp, sum;
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(2, 3, 0, 1));
    sum.m128i  = _mm_add_epi8(this->m128i, temp.m128i);
    temp.m128i = _mm_shuffle_epi32(sum.m128i, _MM_SHUFFLE(1, 0, 3, 2));
    sum.m128i  = _mm_add_epi8(temp.m128i, sum.m128i);
    temp.m128i = _mm_srli_si128(sum.m128i, 2);
    sum.m128i  = _mm_add_epi8(temp.m128i, sum.m128i);
    sum.m128i  = _mm_shuffle_epi32(sum.m128i, 0);
    return sum;
  }

  __forceinline v_cb v_hsums()
  { 
    v_cb temp, sum;
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(2, 3, 0, 1));
    sum.m128i  = _mm_adds_epi8(this->m128i, temp.m128i);
    temp.m128i = _mm_shuffle_epi32(sum.m128i, _MM_SHUFFLE(1, 0, 3, 2));
    sum.m128i  = _mm_adds_epi8(temp.m128i, sum.m128i);
    temp.m128i = _mm_srli_si128(sum.m128i, 2);
    sum.m128i  = _mm_add_epi8(temp.m128i, sum.m128i);
    sum.m128i  = _mm_shuffle_epi32(sum.m128i, 0);
    return sum;
  }
  __forceinline v_cb v_conj_im();
  __forceinline v_cb v_conj_re();

  __forceinline v_s v_sqr2s();
};



#pragma endregion

#pragma region "v_cub"
struct v_cub : public vector1<complex8u>
{
  v_ctor(v_cub);

  template<int idx>
  __forceinline v_cub& v_set_at(complex8u &value){ this->m128i = _mm_insert_epi16(this->m128i, value._r, idx);  return (*this); }
  template<int idx>
  __forceinline complex8u v_get_at(){ return _mm_extract_epi16(this->m128i, idx); }
};
__forceinline v_cub v_add(v_cub &a, v_cub &b){ v_cub c; c.m128i = _mm_add_epi8(a.m128i, b.m128i); return c; }
__forceinline v_cub v_adds(v_cub &a, v_cub &b){ v_cub c; c.m128i = _mm_adds_epu8(a.m128i, b.m128i); return c; }
#pragma endregion
//////////////////////////////////////////////////////////////////////////
#pragma region "v_s"
struct v_s : public vector1<signed __int16>
{
  v_ctor(v_s);

  //__forceinline __int16& operator[](int idx){ return this->m128i.m128i_i16[idx]; }

  __forceinline v_s& v_set(short s0, short s1, short s2, short s3, short s4, short s5, short s6, short s7){ this->m128i = _mm_set_epi16(s7, s6, s5, s4, s3, s2, s1, s0); return (*this); }
  __forceinline v_s& v_setall(short s){ this->m128i                                                                     = _mm_set1_epi16(s); return (*this); }

  template<int idx>
  __forceinline v_s& v_set_at(__int16 &value){ this->m128i = _mm_insert_epi16(this->m128i, value, idx);  return (*this); }
  template<int idx>
  __forceinline __int16 v_get_at(){ return _mm_extract_epi16(this->m128i, idx); }


  __forceinline v_s  v_abs(){ v_s c; c.m128i     = _mm_abs_epi16(this->m128i); return c; }        
  __forceinline v_s  v_signmsk();

  __forceinline v_s  v_neg_if_less0 (v_s &a){ v_s c; c.m128i = _mm_sign_epi16(this->m128i, a.m128i); return c; }

  template<int a0, int a1, int a2, int a3>
  __forceinline v_s  v_shuffle_hi(){ v_s c; c.m128i = _mm_shufflehi_epi16(this->m128i, _MM_SHUFFLE(a3, a2, a1, a0)); return c; }
  template<int a0, int a1, int a2, int a3>
  __forceinline v_s  v_shuffle_lo(){ v_s c; c.m128i = _mm_shufflelo_epi16(this->m128i, _MM_SHUFFLE(a3, a2, a1, a0)); return c; }

  __forceinline v_s  v_shuffle(char a0, char a1, char a2, char a3, char a4, char a5, char a6, char a7)
  {
    v_s c; __m128i vmsk;
    vmsk = _mm_set_epi8((a7 << 1) + 1, (a7 << 1), (a6 << 1) + 1, (a6 << 1), (a5 << 1) + 1, (a5 << 1), (a4 << 1) + 1, (a4 << 1), 
      (a3 << 1) + 1, (a3 << 1), (a2 << 1) + 1, (a2 << 1), (a1 << 1) + 1, (a1 << 1), (a0 << 1) + 1, (a0 << 1));

    c.m128i = _mm_shuffle_epi8(this->m128i, vmsk);
    return c;
  }

  __forceinline v_s v_shift_left(v_s &msk){ v_s c; c.m128i                       = _mm_sll_epi16(this->m128i, msk.m128i); return c; }
  __forceinline v_s v_shift_left(int i){ v_s c; c.m128i                          = _mm_slli_epi16(this->m128i, i); return c; }
  __forceinline v_s v_shift_right_logical(v_s &msk){ v_s c; c.m128i              = _mm_srl_epi16(this->m128i, msk.m128i); return c; }
  __forceinline v_s v_shift_right_logical(int i){ v_s c; c.m128i                 = _mm_srli_epi16(this->m128i, i); return c; }
  __forceinline v_s v_shift_right_arithmetic(v_s &msk){ v_s c; c.m128i           = _mm_sra_epi16(this->m128i, msk.m128i); return c; }
  __forceinline v_s v_shift_right_arithmetic(int i){ v_s c; c.m128i              = _mm_srai_epi16(this->m128i, i); return c; }

  __forceinline v_i  v_convert2i_lo();
  __forceinline v_i  v_convert2i_hi();
  template<int nShortOffset>
  __forceinline v_i  v_convert2i_offset();
  __forceinline void v_convert2i(v_i &i0, v_i &i1);
  template<int nShortOffset>
  __forceinline v_q  v_convert2q_offset();
  __forceinline void v_convert2q(v_q &q0, v_q &q1, v_q &q2, v_q &q3);

  __forceinline v_s v_hsum()
  { 
    v_s temp, sum;
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(2, 3, 0, 1));
    sum.m128i  = _mm_add_epi16(this->m128i, temp.m128i);
    temp.m128i = _mm_shuffle_epi32(sum.m128i, _MM_SHUFFLE(1, 0, 3, 2));
    sum.m128i  = _mm_add_epi16(temp.m128i, sum.m128i);
    temp.m128i = _mm_srli_si128(sum.m128i, 2);
    sum.m128i  = _mm_add_epi16(temp.m128i, sum.m128i);
    sum.m128i  = _mm_shuffle_epi32(sum.m128i, 0);
    return sum;
  }

  __forceinline v_s v_hsums()
  { 
    v_s temp, sum;
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(2, 3, 0, 1));
    sum.m128i  = _mm_adds_epi16(this->m128i, temp.m128i);
    temp.m128i = _mm_shuffle_epi32(sum.m128i, _MM_SHUFFLE(1, 0, 3, 2));
    sum.m128i  = _mm_adds_epi16(temp.m128i, sum.m128i);
    temp.m128i = _mm_srli_si128(sum.m128i, 2);
    sum.m128i  = _mm_adds_epi16(temp.m128i, sum.m128i);
    sum.m128i  = _mm_shuffle_epi32(sum.m128i, 0);
    return sum;
  }

  __forceinline v_s v_hmaxpos();
  __forceinline v_s v_hminpos();
};

#pragma endregion

#pragma region "v_us"
struct v_us : public vector1<unsigned __int16>
{
  v_ctor(v_us);

  template<int idx>
  __forceinline v_us& v_set_at(unsigned __int16 &value){ this->m128i = _mm_insert_epi16(this->m128i, value, idx);  return (*this); }
  template<int idx>
  __forceinline unsigned __int16 v_get_at(){ return _mm_extract_epi16(this->m128i, idx); }

  __forceinline v_us v_hminpos(){ v_us c; c.m128i = _mm_minpos_epu16(this->m128i); return c; }

  __forceinline v_us v_hmaxpos();
};
__forceinline v_us v_add(v_us &a, v_us &b){ v_us c; c.m128i     = _mm_add_epi16(a.m128i, b.m128i); return c; }
__forceinline v_us v_adds(v_us &a, v_us &b){ v_us c; c.m128i    = _mm_adds_epu16(a.m128i, b.m128i); return c; }
__forceinline v_us v_sub(v_us &a, v_us &b){ v_us c; c.m128i     = _mm_sub_epi16(a.m128i, b.m128i); return c; }
__forceinline v_us v_subs(v_us &a, v_us &b){ v_us c; c.m128i    = _mm_subs_epu16(a.m128i, b.m128i); return c; }
__forceinline v_us v_max(v_us &a, v_us &b){ v_us c; c.m128i     = _mm_max_epu16(a.m128i, b.m128i); return c; }
__forceinline v_us v_min(v_us &a, v_us &b){ v_us c; c.m128i     = _mm_min_epu16(a.m128i, b.m128i); return c; }
__forceinline v_us v_mul_hi(v_us &a, v_us &b){ v_us c; c.m128i  = _mm_mulhi_epu16(a.m128i, b.m128i); return c; }
__forceinline v_us v_avg(v_us &a, v_us &b){ v_us c; c.m128i     = _mm_avg_epu16(a.m128i, b.m128i); return c; }
#pragma endregion

#pragma region "v_cs"
struct v_cs : public vector1<complex16>
{
  v_ctor(v_cs);

  __forceinline void v_setall(complex16 &value){this->m128i = _mm_set1_epi32(value._r);}

  template<int idx>
  __forceinline v_cs& v_set_at(complex16 &value){ this->m128i = _mm_insert_epi32(this->m128i, value._r, idx);  return (*this); }
  template<int idx>
  __forceinline complex16 v_get_at(){ return _mm_extract_epi32(this->m128i, idx); }

  template<int a0, int a1, int a2, int a3>
  __forceinline v_cs v_shuffle(){ v_cs c; c.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(a3, a2, a1, a0)); return c; }
  template<int m0, int m1, int a0, int a1>
  __forceinline v_cs v_shuffle_with(v_cs &a){ v_cs c; c.m128 = _mm_shuffle_ps(this->m128, a.m128, _MM_SHUFFLE(a1, a0, m1, m0)); return c; }

  __forceinline v_cs  v_abs(){ v_cs c; c.m128i     = _mm_abs_epi16(this->m128i); return c; }

  __forceinline void v_convert2ci(v_ci &c0, v_ci &c1);

  __forceinline v_cs v_shift_left(v_cs &msk){ v_cs c; c.m128i             = _mm_sll_epi16(this->m128i, msk.m128i); return c; }
  __forceinline v_cs v_shift_left(int i){ v_cs c; c.m128i                 = _mm_slli_epi16(this->m128i, i); return c; }
  __forceinline v_cs v_shift_right_logical(v_cs &msk){ v_cs c; c.m128i    = _mm_srl_epi16(this->m128i, msk.m128i); return c; }
  __forceinline v_cs v_shift_right_logical(int i){ v_cs c; c.m128i        = _mm_srli_epi16(this->m128i, i); return c; }
  __forceinline v_cs v_shift_right_arithmetic(v_cs &msk){ v_cs c; c.m128i = _mm_sra_epi16(this->m128i, msk.m128i); return c; }
  __forceinline v_cs v_shift_right_arithmetic(int i){ v_cs c; c.m128i     = _mm_srai_epi16(this->m128i, i); return c; }

  __forceinline v_cs v_hsum()
  { 
    v_cs temp, sum;
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(1, 0, 3, 2));
    sum.m128i  = _mm_add_epi16(this->m128i, temp.m128i);
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(2, 3, 0, 1));
    sum.m128i  = _mm_add_epi16(temp.m128i, sum.m128i);
    return sum;
  }
  __forceinline v_cs v_hsums()
  { 
    v_cs temp, sum;
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(1, 0, 3, 2));
    sum.m128i  = _mm_adds_epi16(this->m128i, temp.m128i);
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(2, 3, 0, 1));
    sum.m128i  = _mm_adds_epi16(temp.m128i, sum.m128i);
    return sum;
  }

  __forceinline v_cs v_conj_im();
  __forceinline v_cs v_conj_re();

  __forceinline v_i v_sqr2i();
};


#pragma endregion
#pragma region "v_cus"
struct v_cus : public vector1<complex16u>
{
  v_ctor(v_cus);

  __forceinline void v_setall(complex16u &value){this->m128i = _mm_set1_epi32(value._r);}

  template<int idx>
  __forceinline v_cus& v_set_at(complex16u &value){ this->m128i = _mm_insert_epi32(this->m128i, value._r, idx);  return (*this); }
  template<int idx>
  __forceinline complex16u v_get_at(){ return _mm_extract_epi32(this->m128i, idx); }
};

// conditional copy float from b and a to r on the mask f0~f3, 1: copy from b, 0: copy from a
template<int i0, int i1, int i2, int i3>
__forceinline v_cus v_select(v_cus &a, v_cus &b){ v_cus c; c.m128 = _mm_blend_ps( a.m128, b.m128, ( i0 | (i1 << 1) | (i2 << 2) | (i3 << 3) ) ); return c; }

#pragma endregion
//////////////////////////////////////////////////////////////////////////
#pragma region "v_i"
struct v_i : public vector1<signed __int32>
{
  v_ctor(v_i);

  __forceinline v_i& v_set(int i0, int i1, int i2, int i3){ this->m128i = _mm_set_epi32(i3, i2, i1, i0); return (*this); }
  __forceinline v_i& v_setall(int i){ this->m128i                       = _mm_set1_epi32(i); return (*this); }

  template<int idx>
  __forceinline v_i& v_set_at(__int32 &value){ this->m128i = _mm_insert_epi32(this->m128i, value, idx);  return (*this); }
  template<int idx>
  __forceinline __int32 v_get_at(){ return _mm_extract_epi32(this->m128i, idx); }

  __forceinline v_i v_abs(){ v_i c; c.m128i                 = _mm_abs_epi32(this->m128i); return c; }
  __forceinline v_i v_signmsk();
  __forceinline v_i v_neg_if_less0 (v_i &a){ v_i c; c.m128i = _mm_sign_epi32(this->m128i, a.m128i); return c; }
  template<int a0, int a1, int a2, int a3>
  __forceinline v_i v_shuffle(){ v_i c; c.m128i              = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(a3, a2, a1, a0)); return c; }
  template<int m0, int m1, int a0, int a1>
  __forceinline v_i v_shuffle_with(v_i &a){ v_i c; c.m128 = _mm_shuffle_ps(this->m128, a.m128, _MM_SHUFFLE(a1, a0, m1, m0)); return c; }

  __forceinline v_i v_shift_left(v_i &msk){ v_i c; c.m128i             = _mm_sll_epi32(this->m128i, msk.m128i); return c; }
  __forceinline v_i v_shift_left(int i){ v_i c; c.m128i                = _mm_slli_epi32(this->m128i, i); return c; }
  __forceinline v_i v_shift_right_logical(v_i &msk){ v_i c; c.m128i    = _mm_srl_epi32(this->m128i, msk.m128i); return c; }
  __forceinline v_i v_shift_right_logical(int i){ v_i c; c.m128i       = _mm_srli_epi32(this->m128i, i); return c; }
  __forceinline v_i v_shift_right_arithmetic(v_s &msk){ v_i c; c.m128i = _mm_sra_epi32(this->m128i, msk.m128i); return c; }
  __forceinline v_i v_shift_right_arithmetic(int i){ v_i c; c.m128i    = _mm_srai_epi32(this->m128i, i); return c; }

  __forceinline v_i  v_hsum();
  __forceinline void v_convert2q(v_q &a, v_q &b);
  __forceinline v_f  v_convert2f();
  __forceinline void v_convert2cq(v_cq &c0, v_cq &c1);
  __forceinline void v_sqr2q(v_q &q0, v_q &q1);
};


#pragma endregion
#pragma region "v_ui"
struct v_ui : public vector1<unsigned __int32>
{
  v_ctor(v_ui);

  __forceinline v_ui& v_set(unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3){ this->m128i = _mm_set_epi32(i3, i2, i1, i0); return (*this); }
  __forceinline v_ui& v_setall(unsigned int i){ this->m128i = _mm_set1_epi32(i); return (*this); }

  template<int idx>
  __forceinline v_ui& v_set_at(unsigned __int32 &value){ this->m128i = _mm_insert_epi32(this->m128i, value, idx);  return (*this); }
  template<int idx>
  __forceinline unsigned __int32 v_get_at(){ return _mm_extract_epi32(this->m128i, idx); }

  __forceinline v_ui v_shift_left(v_ui &msk){ v_ui c; c.m128i             = _mm_sll_epi32(this->m128i, msk.m128i); return c; }
  __forceinline v_ui v_shift_left(int i){ v_ui c; c.m128i                 = _mm_slli_epi32(this->m128i, i); return c; }
  __forceinline v_ui v_shift_right_logical(v_ui &msk){ v_ui c; c.m128i    = _mm_srl_epi32(this->m128i, msk.m128i); return c; }
  __forceinline v_ui v_shift_right_logical(int i){ v_ui c; c.m128i        = _mm_srli_epi32(this->m128i, i); return c; }
};

#pragma endregion
#pragma region "v_ci"
struct v_ci : public vector1<complex32>
{
  v_ctor(v_ci);
#if defined(_M_X64)
  template<int idx>
  __forceinline v_ci& v_set_at(complex32 &value){ this->m128i = _mm_insert_epi64(this->m128i, value._r, idx);  return (*this); }
  template<int idx>
  __forceinline complex32 v_get_at(){ return _mm_extract_epi64(this->m128i, idx); }
#endif
  template<int a0, int a1>
  __forceinline v_ci v_shuffle(){ v_ci c; c.m128d               = _mm_shuffle_pd(this->m128d, this->m128d, (a0 | (a1 << 1))); return c; }
  template<int m0, int a0>
  __forceinline v_ci v_shuffle_with(v_ci &a){ v_ci c; c.m128d = _mm_shuffle_pd(this->m128d, a.m128d, (m0 | (a0 << 1))); return c; }

  __forceinline v_ci v_shift_left(v_i &msk){ v_ci c; c.m128i             = _mm_sll_epi32(this->m128i, msk.m128i); return c; }
  __forceinline v_ci v_shift_left(int i){ v_ci c; c.m128i                = _mm_slli_epi32(this->m128i, i); return c; }
  __forceinline v_ci v_shift_right_logical(v_i &msk){ v_ci c; c.m128i    = _mm_srl_epi32(this->m128i, msk.m128i); return c; }
  __forceinline v_ci v_shift_right_logical(int i){ v_ci c; c.m128i       = _mm_srli_epi32(this->m128i, i); return c; }
  __forceinline v_ci v_shift_right_arithmetic(v_i &msk){ v_ci c; c.m128i = _mm_sra_epi32(this->m128i, msk.m128i); return c; }
  __forceinline v_ci v_shift_right_arithmetic(int i){ v_ci c; c.m128i    = _mm_srai_epi32(this->m128i, i); return c; }

  __forceinline v_cf v_convert2cf();

  __forceinline v_ci v_hsum()
  { 
    v_ci temp, sum;
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(1, 0, 3, 2));
    sum.m128i  = _mm_add_epi32(this->m128i, temp.m128i);
    return sum;
  }

  __forceinline v_ci v_conj_im();
  __forceinline v_ci v_conj_re();

  __forceinline v_q v_sqr2q();
};


#pragma endregion
#pragma region "v_cui"
struct v_cui : public vector1<complex32u>
{
  v_ctor(v_cui);
#if defined(_M_X64)
  template<int idx>
  __forceinline v_cui& v_set_at(complex32u &value){ this->m128i = _mm_insert_epi64(this->m128i, value._r, idx);  return (*this); }
  template<int idx>
  __forceinline complex32u v_get_at(){ return _mm_extract_epi64(this->m128i, idx); }
#endif
  __forceinline v_cui v_shift_left(v_ui &msk){ v_cui c; c.m128i             = _mm_sll_epi32(this->m128i, msk.m128i); return c; }
  __forceinline v_cui v_shift_left(int i){ v_cui c; c.m128i                = _mm_slli_epi32(this->m128i, i); return c; }
  __forceinline v_cui v_shift_right_logical(v_ui &msk){ v_cui c; c.m128i    = _mm_srl_epi32(this->m128i, msk.m128i); return c; }
  __forceinline v_cui v_shift_right_logical(int i){ v_cui c; c.m128i       = _mm_srli_epi32(this->m128i, i); return c; }
};
#pragma endregion
//////////////////////////////////////////////////////////////////////////
#pragma region "v_q"
struct v_q : public vector1<signed __int64>
{
  v_ctor(v_q);
#if defined(_M_X64)
  template<int idx>
  __forceinline v_q& v_set_at(__int64 &value){ this->m128i = _mm_insert_epi64(this->m128i, value, idx);  return (*this); }
  template<int idx>
  __forceinline __int64 v_get_at(){ return _mm_extract_epi64(this->m128i, idx); }
#endif
  __forceinline v_q& v_set(__m64 q0, __m64 q1){ this->m128i = _mm_set_epi64(q1, q0); return (*this); }
  __forceinline v_q& v_setall(__m64 q){ this->m128i         = _mm_set1_epi64(q); return (*this); }

  template<int a0, int a1>
  __forceinline v_q v_shuffle(int a0, int a1){ v_q c; c.m128d              = _mm_shuffle_pd(this->m128d, this->m128d, (a0 | (a1 << 1))); return c; }
  template<int m0, int a0>
  __forceinline v_q v_shuffle_with(v_q &a){ v_q c; c.m128d = _mm_shuffle_pd(this->m128d, a.m128d, (m0 | (a0 << 1))); return c; }

  __forceinline v_q v_unpack_lo(v_q &a){ v_q c; c.m128i = _mm_unpacklo_epi64(this->m128i, a.m128i); return c; }
  __forceinline v_q v_unpack_hi(v_q &a){ v_q c; c.m128i = _mm_unpackhi_epi64(this->m128i, a.m128i); return c; }

  __forceinline v_q v_shift_left(v_q &msk){ v_q c; c.m128i                 = _mm_sll_epi64(this->m128i, msk.m128i); return c; }
  __forceinline v_q v_shift_left(int i){ v_q c; c.m128i                    = _mm_slli_epi64(this->m128i, i); return c; }
  __forceinline v_q v_shift_right_logical(v_q &msk){ v_q c; c.m128i        = _mm_srl_epi64(this->m128i, msk.m128i); return c; }
  __forceinline v_q v_shift_right_logical(int i){ v_q c; c.m128i           = _mm_srli_epi64(this->m128i, i); return c; }

  __forceinline v_q  v_signmsk();

  __forceinline v_q v_hsum()
  { 
    v_q temp, sum;
    temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(1, 0, 3, 2));
    sum.m128i  = _mm_add_epi64(this->m128i, temp.m128i);
    return sum;
  }
};

#pragma endregion
#pragma region "v_uq"
struct v_uq : public vector1<unsigned __int64>
{
  v_ctor(v_uq);
#if defined(_M_X64)
  template<int idx>
  __forceinline v_uq& v_set_at(unsigned __int64 &value){ this->m128i = _mm_insert_epi64(this->m128i, value, idx);  return (*this); }
  template<int idx>
  __forceinline unsigned __int64 v_get_at(){ return _mm_extract_epi64(this->m128i, idx); }
#endif
  template<int a0, int a1>
  __forceinline v_uq v_shuffle(){ v_uq c; c.m128d               = _mm_shuffle_pd(this->m128d, this->m128d, (a0 | (a1 << 1))); return c; }
  template<int m0, int a0>
  __forceinline v_uq v_shuffle_with(v_uq &a){ v_uq c; c.m128d = _mm_shuffle_pd(this->m128d, a.m128d, (m0 | (a0 << 1))); return c; }
  __forceinline v_uq v_shift_left(v_uq &msk){ v_uq c; c.m128i                 = _mm_sll_epi64(this->m128i, msk.m128i); return c; }
  __forceinline v_uq v_shift_left(int i){ v_uq c; c.m128i                     = _mm_slli_epi64(this->m128i, i); return c; }
  __forceinline v_uq v_shift_right_logical(v_uq &msk){ v_uq c; c.m128i        = _mm_srl_epi64(this->m128i, msk.m128i); return c; }
  __forceinline v_uq v_shift_right_logical(int i){ v_uq c; c.m128i            = _mm_srli_epi64(this->m128i, i); return c; }
};

#pragma endregion
#pragma region "v_cq"
struct v_cq : public vector1<complex64>
{
  v_ctor(v_cq);

  template<int a0, int a1>
  __forceinline v_cq v_shuffle(){ v_cq c; c.m128d               = _mm_shuffle_pd(this->m128d, this->m128d, (a0 | (a1 << 1))); return c; }
  template<int m0, int a0>
  __forceinline v_cq v_shuffle_with(v_cq &a){ v_cq c; c.m128d = _mm_shuffle_pd(this->m128d, a.m128d, (m0 | (a0 << 1))); return c; }
  __forceinline v_cq v_shift_left(v_q &msk){ v_cq c; c.m128i                  = _mm_sll_epi64(this->m128i, msk.m128i); return c; }
  __forceinline v_cq v_shift_left(int i){ v_cq c; c.m128i                     = _mm_slli_epi64(this->m128i, i); return c; }
  __forceinline v_cq v_shift_right_logical(v_q &msk){ v_cq c; c.m128i         = _mm_srl_epi64(this->m128i, msk.m128i); return c; }
  __forceinline v_cq v_shift_right_logical(int i){ v_cq c; c.m128i            = _mm_srli_epi64(this->m128i, i); return c; }
};
__forceinline void v_convert2cq(v_q &re, v_q &im, v_cq &c1, v_cq &c2){ c1.m128i = _mm_unpacklo_epi64(re.m128i, im.m128i); c2.m128i = _mm_unpackhi_epi64(re.m128i, im.m128i); }
__forceinline void v_convert2q(v_cq &c1, v_cq &c2, v_q &re, v_q &im){ re.m128   = _mm_shuffle_ps(c1.m128, c2.m128, _MM_SHUFFLE(2, 0, 2, 0)); im.m128 = _mm_shuffle_ps(c1.m128, c2.m128, _MM_SHUFFLE(3, 1, 3, 1)); }

// keep low 32 bits
__forceinline v_ci v_convert2ci_lo(v_cq &a, v_cq &b){ v_ci c; c.m128 = _mm_shuffle_ps(a.m128, b.m128, _MM_SHUFFLE(2, 0, 2, 0)); return c; }
// keep high 32 bits
__forceinline v_ci v_convert2ci_hi(v_cq &a, v_cq &b){ v_ci c; c.m128 = _mm_shuffle_ps(a.m128, b.m128, _MM_SHUFFLE(3, 1, 3, 1)); return c; }

#pragma endregion
#pragma region "v_cuq"
struct v_cuq : public vector1<complex64u>
{
  v_ctor(v_cuq);

  template<int a0, int a1>
  __forceinline v_cuq v_shuffle(){ v_cuq c; c.m128d                = _mm_shuffle_pd(this->m128d, this->m128d, (a0 | (a1 << 1))); return c; }
  template<int m0, int a0>
  __forceinline v_cuq v_shuffle_with(v_cuq &a){ v_cuq c; c.m128d = _mm_shuffle_pd(this->m128d, a.m128d, (m0 | (a0 << 1))); return c; }
  __forceinline v_cuq v_shift_left(v_uq &msk){ v_cuq c; c.m128i                  = _mm_sll_epi64(this->m128i, msk.m128i); return c; }
  __forceinline v_cuq v_shift_left(int i){ v_cuq c; c.m128i                      = _mm_slli_epi64(this->m128i, i); return c; }
  __forceinline v_cuq v_shift_right_logical(v_uq &msk){ v_cuq c; c.m128i         = _mm_srl_epi64(this->m128i, msk.m128i); return c; }
  __forceinline v_cuq v_shift_right_logical(int i){ v_cuq c; c.m128i             = _mm_srli_epi64(this->m128i, i); return c; }
};
#pragma endregion

#pragma region "v_dq"
struct v_dq : public vector1<__int8>
{
  v_ctor(v_dq);

};
#pragma endregion

//////////////////////////////////////////////////////////////////////////
#pragma region "v_f"
struct v_f : public vector1<float>
{
  v_ctor(v_f);

  __forceinline void v_set(float a0, float a1, float a2, float a3){ this->m128 = _mm_set_ps(a3, a2, a1, a0);}
  __forceinline void v_setall(float a){ this->m128 = _mm_set1_ps(a);}

  __forceinline v_f v_set_first(int a){ v_f c; c.m128 = _mm_cvt_si2ss(this->m128, a); return c; }
  __forceinline int v_round_first(){ return _mm_cvt_ss2si(this->m128); }
  __forceinline int v_truncate_first(){ return _mm_cvtt_ss2si(this->m128); }

  __forceinline v_i v_round2i();
  __forceinline v_i v_truncate2i();
  __forceinline v_f v_sqrt(){ v_f c; c.m128        = _mm_sqrt_ps(this->m128); return c; }
  __forceinline v_f v_sqrt_first(){ v_f c; c.m128  = _mm_sqrt_ss(this->m128); return c; }// vf_r[31:0] <- SQRT (vf_a[31:0]); (* vf_r[127:32] unchanged *)
  __forceinline v_f v_rsqrt(){ v_f c; c.m128       = _mm_rsqrt_ps(this->m128); return c; }//DEST[31:0] <- APPROXIMATE(1.0/SQRT(SRC[31:0]));    //DEST[63:32] <-  APPROXIMATE(1.0/SQRT(SRC[63:32]));    //DEST[95:64] <-  APPROXIMATE(1.0/SQRT(SRC[95:64]));    //DEST[127:96] <-  APPROXIMATE(1.0/SQRT(SRC[127:96]));
  __forceinline v_f v_rsqrt_first(){ v_f c; c.m128 = _mm_rsqrt_ss(this->m128); return c; }// APPROXIMATE(1.0/SQRT(vf_a[31:0])); (* vf_r[127:32] unchanged *)

  __forceinline v_f v_dup_low(){v_f c; c.m128  = _mm_moveldup_ps(this->m128); return c; } // dup 0 2 elem
  __forceinline v_f v_dup_high(){v_f c; c.m128 = _mm_movehdup_ps(this->m128); return c; }// dup 1 3 elem

  __forceinline void v_sincos(v_f &vsin, v_f &vcos);

  template<int a0, int a1, int a2, int a3>
  __forceinline v_f v_shuffle(){ v_f c; c.m128i             = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(a3, a2, a1, a0)); return c; }
  template<int m0, int m1, int a0, int a1>
  __forceinline v_f v_shuffle_with(v_f &a){ v_f c; c.m128 = _mm_shuffle_ps(this->m128, a.m128, _MM_SHUFFLE(a1, a0, m1, m0)); return c; }
};

#pragma endregion
#pragma region "v_cf"
struct v_cf : public vector1<complexf>
{
  v_ctor(v_cf);
};
template<int f0, int f1>
__forceinline v_cf v_select(v_cf &a, v_cf &b){ v_cf c; c.m128d = _mm_blend_pd( a.m128d, b.m128d, ( f0 | (f1 << 1) ) ); return c; }

__forceinline v_cf v_add(v_cf &a, v_cf &b)
{
  v_cf c;
  c.m128 = _mm_add_ps(a.m128, b.m128);
  return c;
}

__forceinline v_cf v_sub(v_cf &a, v_cf &b)
{
  v_cf c;
  c.m128 = _mm_sub_ps(a.m128, b.m128);
  return c;
}

__forceinline v_cf v_mul(v_cf &a, v_cf &b)
{
  v_cf bre, bim;
  //bre.m128i = _mm_shuffle_epi32(b.m128i, _MM_SHUFFLE(2, 2, 0, 0));
  //bim.m128i = _mm_shuffle_epi32(b.m128i, _MM_SHUFFLE(3, 3, 1, 1));
  bre.m128  = _mm_moveldup_ps(b.m128);
  bim.m128  = _mm_movehdup_ps(b.m128);
  bre.m128  = _mm_mul_ps(a.m128, bre.m128);
  bim.m128  = _mm_mul_ps(a.m128, bim.m128);
  bim.m128i = _mm_shuffle_epi32(bim.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  bim.m128  = _mm_addsub_ps(bre.m128, bim.m128);
  return bim;
}

// c = a * conj(b)
__forceinline v_cf v_conjmul(v_cf &a, v_cf &b)
{
  v_cf bre, bim;
  //bre.m128i = _mm_shuffle_epi32(b.m128i, _MM_SHUFFLE(2, 2, 0, 0));
  //bim.m128i = _mm_shuffle_epi32(b.m128i, _MM_SHUFFLE(3, 3, 1, 1));
  bre.m128  = _mm_moveldup_ps(b.m128);
  bim.m128  = _mm_movehdup_ps(b.m128);
  bre.m128  = _mm_mul_ps(a.m128, bre.m128);
  bim.m128  = _mm_mul_ps(a.m128, bim.m128);
  bre.m128i = _mm_shuffle_epi32(bre.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  bim.m128  = _mm_addsub_ps(bre.m128, bim.m128);
  bim.m128i = _mm_shuffle_epi32(bim.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  return bim;
}

#pragma endregion
//////////////////////////////////////////////////////////////////////////
#pragma region "v_d"
struct v_d : public vector1<double>
{
  v_ctor(v_d);

  __forceinline v_d v_dup_low(){v_d c; c.m128d = _mm_movedup_pd(this->m128d); return c;} // dup 0
};
// 0: from a
// 1: from b
template<int d0, int d1>
__forceinline v_d v_select(v_d &a, v_d &b){ v_d c; c.m128d = _mm_blend_pd( a.m128d, b.m128d, ( d0 | (d1 << 1) ) ); return c; }

__forceinline v_d v_add(v_d &a, v_d &b){ v_d c; c.m128d       = _mm_add_pd(a.m128d, b.m128d); return c; }
__forceinline v_d v_sub(v_d &a, v_d &b){ v_d c; c.m128d       = _mm_sub_pd(a.m128d, b.m128d); return c; }
__forceinline v_d v_mul(v_d &a, v_d &b){ v_d c; c.m128d       = _mm_mul_pd(a.m128d, b.m128d); return c; }
__forceinline v_d v_div(v_d &a, v_d &b){ v_d c; c.m128d       = _mm_div_pd(a.m128d, b.m128d); return c; }
__forceinline v_d v_div_first(v_d &a, v_d &b){ v_d c; c.m128d = _mm_div_sd(a.m128d, b.m128d); return c; }

#pragma endregion
#pragma region "v_cd"
struct v_cd : public vector1<complexd>
{
  v_ctor(v_cd);
};
#pragma endregion


//////////////////////////////////////////////////////////////////////////

#pragma region vector mask
// use memory or calculate these constants dynamically
// that's depends on the data used for computation
// if data for computation is quite larger than cache size, dynamical calculation would be better. vice versa.
struct __declspec(align(16)) VMASK
{
  template<typename T>
  __forceinline static const T __0x00000000000000000000000000000000()
  {
    T ret;
    ret.v_zero();
    return ret;
  }

  template<typename T>
  __forceinline static const T __0xFFFFFFFFFFFFFFFF0000000000000000()
  {
    v_dq ret;
    ret = ret.v_ones();
    ret = ret.v_shift_bytes_left<8>();
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x0000000000000000FFFFFFFFFFFFFFFF()
  {
    v_dq ret;
    ret.v_ones();
    ret = ret.v_shift_bytes_right<8>();
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0xFFFF0000FFFF0000FFFF0000FFFF0000()
  {
    v_i ret;
    ret.v_ones();
    ret = ret.v_shift_left(16);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x0000FFFF0000FFFF0000FFFF0000FFFF()
  {
    v_i ret;
    ret.v_ones();
    ret = ret.v_shift_right_logical(16);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0xFFFFFFFF00000000FFFFFFFF00000000()
  {
    v_q ret;
    ret.v_ones();
    ret = ret.v_shift_left(32);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x00000000FFFFFFFF00000000FFFFFFFF()
  {
    v_q ret;
    ret.v_ones();
    ret = ret.v_shift_right_logical(32);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x000000000000000000000000FFFF0000()
  {
    v_dq ret;
    ret.v_ones();
    ret = ret.v_shift_bytes_right<14>();
    ret = ret.v_shift_bytes_left<2>();
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x0000000000000000000000000000FFFF()
  {
    v_dq ret;
    ret.v_ones();
    ret = ret.v_shift_bytes_right<14>();
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x00000000000000000000000000007FFF()
  {
    v_dq ret;
    ret.v_ones();
    ret = ret.v_shift_bytes_right<14>();
    ((v_s&)ret).v_shift_right_logical(1);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF()
  {
    v_dq ret;
    ret.v_ones();
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x7FFF7FFF7FFF7FFF7FFF7FFF7FFF7FFF()
  {
    v_s ret;
    ret.v_ones();
    ret = ret.v_shift_right_logical(1);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x7FFE7FFE7FFE7FFE7FFE7FFE7FFE7FFE()
  {
    v_s ret;
    ret.v_ones();
    ret = ret.v_shift_left(2);
    ret = ret.v_shift_right_logical(1);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x80008000800080008000800080008000()
  {
    v_s ret;
    ret.v_ones();
    ret = ret.v_shift_left(15);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x80808080808080808080808080808080()
  {
    v_s ret, temp;
    ret.v_ones();
    ret  = ret.v_shift_left(15);
    temp = ret.v_shift_right_logical(8);
    ret  = v_xor(ret, temp);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x80000000000000008000000000000000()
  {
    v_q ret;
    ret.v_ones();
    ret = ret.v_shift_left(63);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x00000000000000000000000000008000()
  {
    v_dq ret;
    ret.v_ones();
    ret = ret.v_shift_bytes_right<14>();
    ret = ((v_s)ret).v_shift_right_logical(15);
    ret = ((v_s)ret).v_shift_left(15);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x80018001800180018001800180018001()
  {
    v_s ret, temp;
    ret.v_ones();
    temp = ret.v_shift_left(2);
    temp = temp.v_shift_right_logical(1);
    ret  = v_andnot(ret, temp);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x80000001800000018000000180000001()
  {
    v_i ret, temp;
    ret.v_ones();
    temp = ret.v_shift_left(2);
    temp = temp.v_shift_right_logical(1);
    ret  = v_andnot(temp, ret);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x80000000800000008000000080000000()
  {
    v_i ret, temp;
    ret.v_ones();
    ret = ret.v_shift_left(31);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x80000000000000018000000000000001()// neg pos neg pos
  {
    v_q ret, temp;
    ret.v_ones();
    temp = ret.v_shift_left(2);
    temp = temp.v_shift_right_logical(1);
    ret = v_andnot(ret, temp);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x01800180018001800180018001800180()
  {
    v_s ret, temp;
    ret.v_ones();
    ret = ret.v_shift_left(14);
    ret = ret.v_shift_right_logical(4);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x00018000000180000001800000018000()
  {
    v_i ret, temp;
    ret.v_ones();
    ret = ret.v_shift_left(30);
    ret = ret.v_shift_right_logical(15);
    return (T)ret;
  }

  template<typename T>
  __forceinline static const T __0x00000001800000000000000180000000()// pos neg pos neg
  {
    v_q ret, temp;
    ret.v_ones();
    ret = ret.v_shift_left(62);
    ret = ret.v_shift_right_logical(31);
    return (T)ret;
  }

  //vector1 __0x0F0D0B09070503010E0C0A0806040200;
  //vector1 __0x0F0E0B0A070603020D0C090805040100;
};

#pragma endregion vector mask

// binary operations
template<typename T>
__forceinline T v_or    (T &a, T &b){T c; c.m128i = _mm_or_si128    (a.m128i, b.m128i); return c; }
template<typename T>
__forceinline T v_or    (const T &a, const T &b){T c; c.m128i = _mm_or_si128    (a.m128i, b.m128i); return c; }

template<typename T>
__forceinline T v_xor   (T &a, T &b){T c; c.m128i = _mm_xor_si128   (a.m128i, b.m128i); return c; }

template<typename T>
__forceinline T v_xor   (const T &a, const T &b){T c; c.m128i = _mm_xor_si128   (a.m128i, b.m128i); return c; }

template<typename T>
__forceinline T v_and   (T &a, T &b){T c; c.m128i = _mm_and_si128   (a.m128i, b.m128i); return c; }
template<typename T>
__forceinline T v_and   (const T &a, const T &b){T c; c.m128i = _mm_and_si128   (a.m128i, b.m128i); return c; }

template<typename T>
__forceinline T v_andnot(T &a, T &b){T c; c.m128i = _mm_andnot_si128(a.m128i, b.m128i); return c; }
template<typename T>
__forceinline T v_andnot(const T &a, const T &b){T c; c.m128i = _mm_andnot_si128(a.m128i, b.m128i); return c; }


//////////////////////////////////////////////////////////////////////////
// v_b
//////////////////////////////////////////////////////////////////////////
__forceinline v_s  v_b::v_convert2s_lo(){ v_s c; c.m128i                           = _mm_cvtepi8_epi16(this->m128i); return c; }
__forceinline v_s  v_b::v_convert2s_hi(){ v_s c; c.m128i                           = _mm_cvtepi8_epi16(_mm_srli_si128(this->m128i, 8)); return c; }
template<int nByteOffset>
__forceinline v_s  v_b::v_convert2s_offset(){ v_s c; c.m128i        = _mm_cvtepi8_epi16(_mm_srli_si128(this->m128i, nByteOffset)); return c; }
__forceinline void v_b::v_convert2s(v_s &s0, v_s &s1){ s0.m128i                   = _mm_cvtepi8_epi16(this->m128i);  s1.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(this->m128i, 8));}
template<int nByteOffset>
__forceinline v_i  v_b::v_convert2i_offset(){ v_i c; c.m128i        = _mm_cvtepi8_epi32(_mm_srli_si128(this->m128i, nByteOffset)); return c; }
__forceinline void v_b::v_convert2i(v_i &i0, v_i &i1, v_i &i2, v_i &i3){ i0.m128i = _mm_cvtepi8_epi32(this->m128i);  i1.m128i = _mm_cvtepi8_epi32(_mm_srli_si128(this->m128i, 4)); i2.m128i = _mm_cvtepi8_epi32(_mm_srli_si128(this->m128i, 8)); i3.m128i = _mm_cvtepi8_epi32(_mm_srli_si128(this->m128i, 12)); }
template<int nByteOffset>
__forceinline v_q  v_b::v_convert2q_offset(){ v_q c; c.m128i        = _mm_cvtepi8_epi64(_mm_srli_si128(this->m128i, nByteOffset)); return c; }
__forceinline void v_b::v_convert2q(v_q &q0, v_q &q1, v_q &q2, v_q &q3, v_q &q4, v_q &q5, v_q &q6, v_q &q7){ 
  q0.m128i = _mm_cvtepi8_epi64(this->m128i);  q1.m128i = _mm_cvtepi8_epi64(_mm_srli_si128(this->m128i, 2)); q2.m128i = _mm_cvtepi8_epi64(_mm_srli_si128(this->m128i, 4)); q3.m128i = _mm_cvtepi8_epi64(_mm_srli_si128(this->m128i, 6));
  q4.m128i = _mm_cvtepi8_epi64(_mm_srli_si128(this->m128i, 8)); q5.m128i = _mm_cvtepi8_epi64(_mm_srli_si128(this->m128i, 10)); q6.m128i = _mm_cvtepi8_epi64(_mm_srli_si128(this->m128i, 12)); q7.m128i = _mm_cvtepi8_epi64(_mm_srli_si128(this->m128i, 14));
}

__forceinline v_b  v_b::v_signmsk(){ v_b c; c.m128i = _mm_cmpgt_epi8(this->m128i, VMASK::__0x00000000000000000000000000000000<v_b>().m128i); return c; }
__forceinline int  v_b::v_signmask(){return _mm_movemask_epi8(this->m128i);}
__forceinline v_s v_b::v_hsum2s(){ 
  v_s s0, s1, sum;
  this->v_convert2s(s0, s1);
  sum.m128i = _mm_add_epi16(s0.m128i, s1.m128i);
  sum = sum.v_hsum();
  return sum;
}

__forceinline v_s v_b::v_hsums2s(){ 
  v_s s0, s1, sum;
  this->v_convert2s(s0, s1);
  sum.m128i = _mm_adds_epi16(s0.m128i, s1.m128i);
  sum = sum.v_hsum();
  return sum;
}

__forceinline void v_b::sqr2s(v_s &s0, v_s &s1){ 
  v_s lo, hi;
  lo.m128i = _mm_cvtepi8_epi16(this->m128i);
  hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(this->m128i, 8));
  s0.m128i = _mm_mullo_epi16(lo.m128i, lo.m128i);
  s1.m128i = _mm_mullo_epi16(hi.m128i, hi.m128i);
}
__forceinline v_b v_add(v_b &a, v_b &b){ v_b c; c.m128i       = _mm_add_epi8(a.m128i, b.m128i); return c; }
__forceinline v_b v_adds(v_b &a, v_b &b){ v_b c; c.m128i      = _mm_adds_epi8(a.m128i, b.m128i); return c; }
__forceinline v_b v_sub(v_b &a, v_b &b){ v_b c; c.m128i       = _mm_sub_epi8(a.m128i, b.m128i); return c; }
__forceinline v_b v_subs(v_b &a, v_b &b){ v_b c; c.m128i      = _mm_subs_epi8(a.m128i, b.m128i); return c; }

__forceinline v_b v_hadd(v_b &a, v_b &b)
{ 
  v_b temp, sum1, sum2;
  temp.m128i  = _mm_slli_si128(a.m128i, 1);
  sum1.m128i  = _mm_add_epi8(a.m128i, temp.m128i);
  temp.m128i  = _mm_slli_si128(b.m128i, 1);
  sum2.m128i  = _mm_add_epi8(b.m128i, temp.m128i);
  sum1.m128i  = _mm_srai_epi16(sum1.m128i, 8);
  sum2.m128i  = _mm_srai_epi16(sum2.m128i, 8);
  temp.m128i  = _mm_packs_epi16(sum1.m128i, sum2.m128i);    
  return temp;
}

__forceinline v_b v_hadds(v_b &a, v_b &b)
{ 
  v_b temp, sum1, sum2;
  temp.m128i  = _mm_slli_si128(a.m128i, 1);
  sum1.m128i  = _mm_adds_epi8(a.m128i, temp.m128i);
  temp.m128i  = _mm_slli_si128(b.m128i, 1);
  sum2.m128i  = _mm_adds_epi8(b.m128i, temp.m128i);
  sum1.m128i  = _mm_srai_epi16(sum1.m128i, 8);
  sum2.m128i  = _mm_srai_epi16(sum2.m128i, 8);
  temp.m128i  = _mm_packs_epi16(sum1.m128i, sum2.m128i);
  return temp;
}
// a0-a1...b0-b1....
__forceinline v_b v_hsub(v_b &a, v_b &b)
{ 
  v_b temp, sum1, sum2;
  temp.m128i  = _mm_slli_si128(a.m128i, 1);
  sum1.m128i  = _mm_sub_epi8(temp.m128i, a.m128i);
  temp.m128i  = _mm_slli_si128(b.m128i, 1);
  sum2.m128i  = _mm_sub_epi8(temp.m128i, b.m128i);
  sum1.m128i  = _mm_srai_epi16(sum1.m128i, 8);
  sum2.m128i  = _mm_srai_epi16(sum2.m128i, 8);
  temp.m128i  = _mm_packs_epi16(sum1.m128i, sum2.m128i);    
  return temp;
}

__forceinline v_b v_hsubs(v_b &a, v_b &b)
{ 
  v_b temp, sum1, sum2;
  temp.m128i  = _mm_slli_si128(a.m128i, 1);
  sum1.m128i  = _mm_subs_epi8(temp.m128i, a.m128i);
  temp.m128i  = _mm_slli_si128(b.m128i, 1);
  sum2.m128i  = _mm_subs_epi8(temp.m128i, b.m128i);
  sum1.m128i  = _mm_srai_epi16(sum1.m128i, 8);
  sum2.m128i  = _mm_srai_epi16(sum2.m128i, 8);
  temp.m128i  = _mm_packs_epi16(sum1.m128i, sum2.m128i);
  return temp;
}

__forceinline v_b v_max(v_b &a, v_b &b){ v_b c; c.m128i       = _mm_max_epi8(a.m128i, b.m128i); return c; }
__forceinline v_b v_min(v_b &a, v_b &b){ v_b c; c.m128i       = _mm_min_epi8(a.m128i, b.m128i); return c; }
__forceinline v_b v_unpack_hi(v_b &a, v_b &b){ v_b c; c.m128i = _mm_unpackhi_epi8(a.m128i, b.m128i); return c; }
__forceinline v_b v_unpack_lo(v_b &a, v_b &b){ v_b c; c.m128i = _mm_unpacklo_epi8(a.m128i, b.m128i); return c; }
// if                                                        a==b, r=FF else r=0
__forceinline v_b v_equal(v_b &a, v_b &b){ v_b c; c.m128i     = _mm_cmpeq_epi8(a.m128i, b.m128i); return c; }
__forceinline v_b v_great(v_b &a, v_b &b){ v_b c; c.m128i     = _mm_cmpgt_epi8(a.m128i, b.m128i); return c; }
__forceinline v_b v_less (v_b &a, v_b &b){ v_b c; c.m128i     = _mm_cmpgt_epi8(b.m128i, a.m128i); return c; }

__forceinline v_b v_avg(v_b &a, v_b &b)
{ 
  v_b c;
  v_b vbr1, vbr2;
  v_b vmsk = VMASK::__0x80808080808080808080808080808080<v_b>();
  vbr1.m128i = _mm_xor_si128(a.m128i, vmsk.m128i);
  vbr2.m128i = _mm_xor_si128(b.m128i, vmsk.m128i);
  c.m128i    = _mm_avg_epu8(vbr1.m128i, vbr2.m128i);
  c.m128i    = _mm_xor_si128(c.m128i, vmsk.m128i);
  return c; 
}
//r0 := (mask0 & 0x80) ? b0 : a0
//r1 := (mask1 & 0x80) ? b1 : a1
//    ...
//r15 := (mask15 & 0x80) ? b15 : a15
// e.g. msk = _mm_cmpgt_epi8(a, b); c = _mm_blendv_epi8(a, b, msk);
__forceinline v_b v_select(v_b &a, v_b &b, v_b &msk){ v_b c; c.m128i = _mm_blendv_epi8( a.m128i, b.m128i, msk.m128i ); return c; }


__forceinline void v_real2complex(v_b &re, v_b &im, v_cb &c1, v_cb &c2){ c1.m128i = _mm_unpacklo_epi8(re.m128i, im.m128i); c2.m128i = _mm_unpackhi_epi8(re.m128i, im.m128i); }
__forceinline void v_complex2real(v_cb &c1, v_cb &c2, v_b &re, v_b &im){
  v_b msk; v_b vbtemp[2];    
  msk.v_set(0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15);    
  vbtemp[0].m128i = _mm_shuffle_epi8(c1.m128i, msk.m128i);
  vbtemp[1].m128i = _mm_shuffle_epi8(c2.m128i, msk.m128i);
  re.m128d        = _mm_shuffle_pd(vbtemp[0].m128d, vbtemp[1].m128d, 0);
  im.m128d        = _mm_shuffle_pd(vbtemp[0].m128d, vbtemp[1].m128d, 3);
}

__forceinline void v_mul2s(v_b &b0, v_b &b1, v_s &s0, v_s &s1){ 
  v_s s0lo, s0hi, s1lo, s1hi;
  s0lo.m128i = _mm_cvtepi8_epi16(b0.m128i);
  s0hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(b0.m128i, 8));
  s1lo.m128i = _mm_cvtepi8_epi16(b1.m128i);
  s1hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(b1.m128i, 8));
  s0.m128i   = _mm_mullo_epi16(s0lo.m128i, s1lo.m128i);
  s1.m128i   = _mm_mullo_epi16(s0hi.m128i, s1hi.m128i);
}


//////////////////////////////////////////////////////////////////////////
// v_ub
//////////////////////////////////////////////////////////////////////////
__forceinline v_ub v_add(v_ub &a, v_ub &b){ v_ub c; c.m128i = _mm_add_epi8(a.m128i, b.m128i); return c; }
__forceinline v_ub v_adds(v_ub &a, v_ub &b){ v_ub c; c.m128i = _mm_adds_epu8(a.m128i, b.m128i); return c; }
// a: unsigned bytes
// b: signed bytes
// c: saturate to signed shorts
__forceinline v_s v_mul_adds(v_ub &a, v_b &b){ v_s c; c.m128i = _mm_maddubs_epi16(a.m128i, b.m128i); return c; }
__forceinline v_ub v_sub(v_ub &a, v_ub &b){ v_ub c; c.m128i  = _mm_sub_epi8(a.m128i, b.m128i); return c; }
__forceinline v_ub v_subs(v_ub &a, v_ub &b){ v_ub c; c.m128i  = _mm_subs_epu8(a.m128i, b.m128i); return c; }
__forceinline v_ub v_max(v_ub &a, v_ub &b){ v_ub c; c.m128i   = _mm_max_epu8(a.m128i, b.m128i); return c; }
__forceinline v_ub v_min(v_ub &a, v_ub &b){ v_ub c; c.m128i   = _mm_min_epu8(a.m128i, b.m128i); return c; }
__forceinline v_ub v_avg(v_ub &a, v_ub &b){ v_ub c; c.m128i   = _mm_avg_epu8(a.m128i, b.m128i); return c; }

__forceinline v_ub v_unpack_hi(v_ub &a, v_ub &b){ v_ub c; c.m128i = _mm_unpackhi_epi8(a.m128i, b.m128i); return c; }
__forceinline v_ub v_unpack_lo(v_ub &a, v_ub &b){ v_ub c; c.m128i = _mm_unpacklo_epi8(a.m128i, b.m128i); return c; }

__forceinline v_q v_abs_sum_lh(v_ub &a, v_ub &b){ v_q c; c.m128i = _mm_min_epu8(a.m128i, b.m128i); return c; }
__forceinline v_ub v_select(v_ub &a, v_ub &b, v_ub &msk){ v_ub c; c.m128i = _mm_blendv_epi8( a.m128i, b.m128i, msk.m128i ); return c; }
//////////////////////////////////////////////////////////////////////////
// v_cb
//////////////////////////////////////////////////////////////////////////
__forceinline v_s v_cb::v_sqr2s(){ 
  v_s c;
  v_s lo, hi;
  lo.m128i = _mm_cvtepi8_epi16(this->m128i);
  hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(this->m128i, 8));
  lo.m128i = _mm_mullo_epi16(lo.m128i, lo.m128i);
  hi.m128i = _mm_mullo_epi16(hi.m128i, hi.m128i);
  c.m128i  = _mm_hadd_epi16(lo.m128i, hi.m128i);
  return c;
}

__forceinline void v_cb::v_convert2cs(v_cs &c0, v_cs &c1){ 
  c0.m128i = _mm_cvtepi8_epi16(this->m128i);
  c1.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(this->m128i, 8));
}

__forceinline v_cb v_cb::v_shuffle(char a0, char a1, char a2, char a3, char a4, char a5, char a6, char a7){ 
  v_s c; c.v_shuffle(a0, a1, a2, a3, a4, a5, a6, a7); return (v_cb)c;
}

__forceinline v_cb v_cb::v_conj_im(){ v_cb c; c.m128i = _mm_sign_epi8(this->m128i, VMASK::__0x80018001800180018001800180018001<v_cb>().m128i); return c; }
__forceinline v_cb v_cb::v_conj_re(){ v_cb c; c.m128i = _mm_sign_epi8(this->m128i, VMASK::__0x01800180018001800180018001800180<v_cb>().m128i); return c; }

__forceinline v_cb v_add(v_cb &a, v_cb &b){ v_cb c; c.m128i  = _mm_add_epi8(a.m128i, b.m128i); return c; }
__forceinline v_cb v_adds(v_cb &a, v_cb &b){ v_cb c; c.m128i = _mm_adds_epi8(a.m128i, b.m128i); return c; }
__forceinline v_cb v_sub(v_cb &a, v_cb &b){ v_cb c; c.m128i  = _mm_sub_epi8(a.m128i, b.m128i); return c; }
__forceinline v_cb v_subs(v_cb &a, v_cb &b){ v_cb c; c.m128i = _mm_subs_epi8(a.m128i, b.m128i); return c; }

__forceinline v_cb v_avg(v_cb &a, v_cb &b){ v_cb c; c = (v_cb)v_avg((v_b)a, (v_b)b); return c; }

__forceinline v_cb v_hadd(v_cb &a, v_cb &b){ 
  v_cb temp1, temp2, sum1, sum2;
  temp1.m128i = _mm_shufflelo_epi16(a.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp2.m128i = _mm_shufflelo_epi16(a.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  temp2.m128i = _mm_shufflelo_epi16(temp2.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  sum1.m128i  = _mm_add_epi8(temp1.m128i, temp2.m128i);

  temp1.m128i = _mm_shufflelo_epi16(b.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp2.m128i = _mm_shufflelo_epi16(b.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  temp2.m128i = _mm_shufflelo_epi16(temp2.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  sum2.m128i  = _mm_add_epi8(temp1.m128i, temp2.m128i);

  sum1.m128   = _mm_shuffle_ps(sum1.m128, sum2.m128, _MM_SHUFFLE(2, 0, 2, 0));

  return sum1;
}

__forceinline v_cb v_hadds(v_cb &a, v_cb &b){ 
  v_cb temp1, temp2, sum1, sum2;// improve with shuffleb
  temp1.m128i = _mm_shufflelo_epi16(a.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp2.m128i = _mm_shufflelo_epi16(a.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  temp2.m128i = _mm_shufflelo_epi16(temp2.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  sum1.m128i  = _mm_adds_epi8(temp1.m128i, temp2.m128i);

  temp1.m128i = _mm_shufflelo_epi16(b.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp2.m128i = _mm_shufflelo_epi16(b.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  temp2.m128i = _mm_shufflelo_epi16(temp2.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  sum2.m128i  = _mm_adds_epi8(temp1.m128i, temp2.m128i);

  sum1.m128   = _mm_shuffle_ps(sum1.m128, sum2.m128, _MM_SHUFFLE(2, 0, 2, 0));
  return sum1;
}

__forceinline v_cb v_hsub(v_cb &a, v_cb &b){ 
  v_cb temp1, temp2, sum1, sum2;
  temp1.m128i = _mm_shufflelo_epi16(a.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp2.m128i = _mm_shufflelo_epi16(a.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  temp2.m128i = _mm_shufflelo_epi16(temp2.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  sum1.m128i  = _mm_sub_epi8(temp1.m128i, temp2.m128i);

  temp1.m128i = _mm_shufflelo_epi16(b.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp2.m128i = _mm_shufflelo_epi16(b.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  temp2.m128i = _mm_shufflelo_epi16(temp2.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  sum2.m128i  = _mm_sub_epi8(temp1.m128i, temp2.m128i);

  sum1.m128   = _mm_shuffle_ps(sum1.m128, sum2.m128, _MM_SHUFFLE(2, 0, 2, 0));

  return sum1;
}

__forceinline v_cb v_hsubs(v_cb &a, v_cb &b){ 
  v_cb temp1, temp2, sum1, sum2;// improve with shuffleb
  temp1.m128i = _mm_shufflelo_epi16(a.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp2.m128i = _mm_shufflelo_epi16(a.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  temp2.m128i = _mm_shufflelo_epi16(temp2.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  sum1.m128i  = _mm_subs_epi8(temp1.m128i, temp2.m128i);

  temp1.m128i = _mm_shufflelo_epi16(b.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp2.m128i = _mm_shufflelo_epi16(b.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  temp2.m128i = _mm_shufflelo_epi16(temp2.m128i, _MM_SHUFFLE(2, 0, 3, 1));
  sum2.m128i  = _mm_subs_epi8(temp1.m128i, temp2.m128i);

  sum1.m128   = _mm_shuffle_ps(sum1.m128, sum2.m128, _MM_SHUFFLE(2, 0, 2, 0));
  return sum1;
}

__forceinline void v_mul2s(v_cb &c0, v_cb &c1, v_s &re, v_s &im){ 
  v_cs cs0lo, cs0hi, cs1lo, cs1hi;
  cs0lo.m128i = _mm_cvtepi8_epi16(c0.m128i);
  cs0hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(c0.m128i, 8));
  cs1lo.m128i = _mm_cvtepi8_epi16(c1.m128i);
  cs1hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(c1.m128i, 8));
  re.m128i    = _mm_hsub_epi16(_mm_mullo_epi16(cs0lo.m128i, cs1lo.m128i), _mm_mullo_epi16(cs0hi.m128i, cs1hi.m128i));
  cs1lo.m128i = _mm_shufflelo_epi16(cs1lo.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  cs1hi.m128i = _mm_shufflehi_epi16(cs1hi.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  im.m128i    = _mm_hadd_epi16(_mm_mullo_epi16(cs0lo.m128i, cs1lo.m128i), _mm_mullo_epi16(cs0hi.m128i, cs1hi.m128i));
}

__forceinline void v_mul2cs(v_cb &cb0, v_cb &cb1, v_cs &cs0, v_cs &cs1){ 
  v_cs cs0lo, cs0hi, cs1lo, cs1hi, re, im;
  cs0lo.m128i = _mm_cvtepi8_epi16(cb0.m128i);
  cs0hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(cb0.m128i, 8));
  cs1lo.m128i = _mm_cvtepi8_epi16(cb1.m128i);
  cs1hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(cb1.m128i, 8));
  re.m128i    = _mm_hsub_epi16(_mm_mullo_epi16(cs0lo.m128i, cs1lo.m128i), _mm_mullo_epi16(cs0hi.m128i, cs1hi.m128i));
  cs1lo.m128i = _mm_shufflelo_epi16(cs1lo.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  cs1hi.m128i = _mm_shufflehi_epi16(cs1hi.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  im.m128i    = _mm_hadd_epi16(_mm_mullo_epi16(cs0lo.m128i, cs1lo.m128i), _mm_mullo_epi16(cs0hi.m128i, cs1hi.m128i));

  cs0.m128i   = _mm_unpacklo_epi16(re.m128i, im.m128i);
  cs1.m128i   = _mm_unpackhi_epi16(re.m128i, im.m128i);
}

__forceinline void v_conjmul2s(v_cb &c0, v_cb &c1, v_s &re, v_s &im){ 
  v_cs cs0lo, cs0hi, cs1lo, cs1hi;
  cs0lo.m128i = _mm_cvtepi8_epi16(c0.m128i);
  cs0hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(c0.m128i, 8));
  cs1lo.m128i = _mm_cvtepi8_epi16(c1.m128i);
  cs1hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(c1.m128i, 8));
  re.m128i    = _mm_hadd_epi16(_mm_mullo_epi16(cs0lo.m128i, cs1lo.m128i), _mm_mullo_epi16(cs0hi.m128i, cs1hi.m128i));
  cs0lo.m128i = _mm_shufflelo_epi16(cs0lo.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  cs0hi.m128i = _mm_shufflehi_epi16(cs0hi.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  im.m128i    = _mm_hsub_epi16(_mm_mullo_epi16(cs0lo.m128i, cs1lo.m128i), _mm_mullo_epi16(cs0hi.m128i, cs1hi.m128i));
}

__forceinline void v_conjmul2cs(v_cb &cb0, v_cb &cb1, v_cs &cs0, v_cs &cs1){ 
  v_cs cs0lo, cs0hi, cs1lo, cs1hi, re, im;
  cs0lo.m128i = _mm_cvtepi8_epi16(cb0.m128i);
  cs0hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(cb0.m128i, 8));
  cs1lo.m128i = _mm_cvtepi8_epi16(cb1.m128i);
  cs1hi.m128i = _mm_cvtepi8_epi16(_mm_srli_si128(cb1.m128i, 8));
  re.m128i    = _mm_hsub_epi16(_mm_mullo_epi16(cs0lo.m128i, cs1lo.m128i), _mm_mullo_epi16(cs0hi.m128i, cs1hi.m128i));
  cs0lo.m128i = _mm_shufflelo_epi16(cs0lo.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  cs0hi.m128i = _mm_shufflehi_epi16(cs0hi.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  im.m128i    = _mm_hadd_epi16(_mm_mullo_epi16(cs0lo.m128i, cs1lo.m128i), _mm_mullo_epi16(cs0hi.m128i, cs1hi.m128i));

  cs0.m128i   = _mm_unpacklo_epi16(re.m128i, im.m128i);
  cs1.m128i   = _mm_unpackhi_epi16(re.m128i, im.m128i);
}

//////////////////////////////////////////////////////////////////////////
// v_s
//////////////////////////////////////////////////////////////////////////
__forceinline v_i  v_s::v_convert2i_lo(){ v_i c; c.m128i                             = _mm_cvtepi16_epi32(this->m128i); return c; }
__forceinline v_i  v_s::v_convert2i_hi(){ v_i c; c.m128i                             = _mm_cvtepi16_epi32(_mm_srli_si128(this->m128i, 8)); return c; }
template<int nShortOffset>
__forceinline v_i  v_s::v_convert2i_offset(){ v_i c; c.m128i         = _mm_cvtepi16_epi32(_mm_srli_si128(this->m128i, (nShortOffset << 1))); return c; }
__forceinline void v_s::v_convert2i(v_i &i0, v_i &i1){ i0.m128i                     = _mm_cvtepi16_epi32(this->m128i);  i1.m128i = _mm_cvtepi16_epi32(_mm_srli_si128(this->m128i, 8)); }
template<int nShortOffset>
__forceinline v_q  v_s::v_convert2q_offset(){ v_q c; c.m128i         = _mm_cvtepi16_epi64(_mm_srli_si128(this->m128i, (nShortOffset << 1))); return c; }
__forceinline void v_s::v_convert2q(v_q &q0, v_q &q1, v_q &q2, v_q &q3){ 
  q0.m128i = _mm_cvtepi16_epi64(this->m128i);
  q1.m128i = _mm_cvtepi16_epi64(_mm_srli_si128(this->m128i, 4));
  q2.m128i = _mm_cvtepi16_epi64(_mm_srli_si128(this->m128i, 8));
  q3.m128i = _mm_cvtepi16_epi64(_mm_srli_si128(this->m128i, 12));
}
__forceinline v_s  v_s::v_signmsk(){ v_s c; c.m128i = _mm_cmpgt_epi16(this->m128i, VMASK::__0x00000000000000000000000000000000<v_s>().m128i); return c; }

__forceinline v_s v_s::v_hmaxpos(){ v_s c;
c.m128i = _mm_xor_si128(this->m128i, VMASK::__0x0000000000000000000000000000FFFF<v_s>().m128i);
c.m128i = _mm_subs_epu16(VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_s>().m128i, c.m128i);
c.m128i = _mm_minpos_epu16(c.m128i);
c.m128i = _mm_xor_si128(c.m128i, VMASK::__0x00000000000000000000000000007FFF<v_s>().m128i);
return c; 
}

__forceinline v_s v_s::v_hminpos(){ v_s c;
c.m128i = _mm_xor_si128(this->m128i, VMASK::__0x80008000800080008000800080008000<v_s>().m128i);
c.m128i = _mm_minpos_epu16(c.m128i);
c.m128i = _mm_xor_si128(c.m128i, VMASK::__0x00000000000000000000000000008000<v_s>().m128i);
return c;
}

__forceinline v_b  v_convert2b(v_s &a, v_s &b){ v_b c; c.m128i   = _mm_packs_epi16(a.m128i, b.m128i); return c; }
__forceinline v_ub v_convert2ub(v_s &a, v_s &b){ v_ub c; c.m128i = _mm_packus_epi16(a.m128i, b.m128i); return c; }

__forceinline v_s v_add(v_s &a, v_s &b){ v_s c; c.m128i     = _mm_add_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_adds(v_s &a, v_s &b){ v_s c; c.m128i    = _mm_adds_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_hadd(v_s &a, v_s &b){ v_s c; c.m128i    = _mm_hadd_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_hadds(v_s &a, v_s &b){ v_s c; c.m128i   = _mm_hadds_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_sub(v_s &a, v_s &b){ v_s c; c.m128i     = _mm_sub_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_subs(v_s &a, v_s &b){ v_s c; c.m128i    = _mm_subs_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_hsub(v_s &a, v_s &b){ v_s c; c.m128i    = _mm_hsub_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_hsubs(v_s &a, v_s &b){ v_s c; c.m128i   = _mm_hsubs_epi16(a.m128i, b.m128i); return c; }
__forceinline v_i v_mul_add(v_s &a, v_s &b){ v_i c; c.m128i = _mm_madd_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_max(v_s &a, v_s &b){ v_s c; c.m128i     = _mm_max_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_min(v_s &a, v_s &b){ v_s c; c.m128i     = _mm_min_epi16(a.m128i, b.m128i); return c; }
//TEMP0[31:0] ¡û DEST[15:0] * SRr[15:0]; (* Signed multiplication *)
//...
//DEST[15:0] ¡û TEMP0[15:0];
__forceinline v_s v_mul_lo(v_s &a, v_s &b){ v_s c; c.m128i = _mm_mullo_epi16(a.m128i, b.m128i); return c; }
//TEMP0[31:0] ¡û DEST[15:0] * SRr[15:0]; (* Signed multiplication *)
//...
//DEST[15:0] ¡û TEMP0[31:16];
__forceinline v_s v_mul_hi(v_s &a, v_s &b){ v_s c; c.m128i = _mm_mulhi_epi16(a.m128i, b.m128i); return c; }

__forceinline v_i v_mul2i(v_s &a, v_s &b, v_i &i0, v_i &i1){ 
  v_s lo, hi;
  lo.m128i = _mm_mullo_epi16(a.m128i, b.m128i);
  hi.m128i = _mm_mulhi_epi16(a.m128i, b.m128i);
  i0.m128i = _mm_unpacklo_epi16(lo.m128i, hi.m128i);
  i1.m128i = _mm_unpackhi_epi16(lo.m128i, hi.m128i);
}

__forceinline v_b v_pack(v_s &a, v_s &b){ v_b c; c.m128i      = _mm_packs_epi16(a.m128i, b.m128i); return c; }
__forceinline v_ub v_packu(v_s &a, v_s &b){ v_ub c; c.m128i   = _mm_packus_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_unpack_hi(v_s &a, v_s &b){ v_s c; c.m128i = _mm_unpackhi_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_unpack_lo(v_s &a, v_s &b){ v_s c; c.m128i = _mm_unpacklo_epi16(a.m128i, b.m128i); return c; }
// if a==b, r=FF else r=0
__forceinline v_s v_equal(v_s &a, v_s &b){ v_s c; c.m128i = _mm_cmpeq_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_great(v_s &a, v_s &b){ v_s c; c.m128i = _mm_cmpgt_epi16(a.m128i, b.m128i); return c; }
__forceinline v_s v_less (v_s &a, v_s &b){ v_s c; c.m128i = _mm_cmpgt_epi16(b.m128i, a.m128i); return c; }

__forceinline v_s v_avg  (v_s &a, v_s &b)
{ 
  v_s c; 
  c.m128i = _mm_add_epi16(b.m128i, a.m128i);
  c.m128i = _mm_sub_epi16(c.m128i, VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_s>().m128i);
  c.m128i = _mm_srai_epi16(c.m128i, 1);
  return c;
}
template<int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7>
__forceinline v_s v_select(v_s &a, v_s &b){ v_s c; c.m128i = _mm_blend_epi16( a.m128i, b.m128i, ( s0 | (s1 << 1) | (s2 << 2) | (s3 << 3) | (s4 << 4) | (s5 << 5) | (s6 << 6) | (s7 << 7) ) ); return c; }

__forceinline void v_real2complex(v_s &re, v_s &im, v_cs &c1, v_cs &c2){ c1.m128i = _mm_unpacklo_epi16(re.m128i, im.m128i); c2.m128i = _mm_unpackhi_epi16(re.m128i, im.m128i); }
__forceinline void v_complex2real(v_cs &c1, v_cs &c2, v_s &re, v_s &im){
  v_i temp[3];
  temp[0].m128i = _mm_shufflelo_epi16(c1.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp[1].m128i = _mm_shufflelo_epi16(temp[0].m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp[0].m128i = _mm_shufflelo_epi16(c2.m128i, _MM_SHUFFLE(3, 1, 2, 0));
  temp[2].m128i = _mm_shufflelo_epi16(temp[0].m128i, _MM_SHUFFLE(3, 1, 2, 0));
  re.m128       = _mm_shuffle_ps(temp[1].m128, temp[2].m128, _MM_SHUFFLE(2, 0, 2, 0));
  im.m128       = _mm_shuffle_ps(temp[1].m128, temp[2].m128, _MM_SHUFFLE(1, 3, 1, 3));
}

//////////////////////////////////////////////////////////////////////////
// v_us
//////////////////////////////////////////////////////////////////////////
__forceinline v_us v_us::v_hmaxpos(){ v_us c;
c.m128i = _mm_subs_epu16(VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_us>().m128i, this->m128i);
c.m128i = _mm_minpos_epu16(c.m128i);
c.m128i = _mm_xor_si128(c.m128i, VMASK::__0x0000000000000000000000000000FFFF<v_us>().m128i);
return c; 
}

//////////////////////////////////////////////////////////////////////////
// v_cs
//////////////////////////////////////////////////////////////////////////
__forceinline v_i v_cs::v_sqr2i(){ v_i c; c.m128i = _mm_madd_epi16(this->m128i, this->m128i); return c; }
__forceinline void v_cs::v_convert2ci(v_ci &c0, v_ci &c1){ c0.m128i = _mm_cvtepi16_epi32(this->m128i);  c1.m128i = _mm_cvtepi16_epi32(_mm_srli_si128(this->m128i, 8));}

__forceinline v_cs v_cs::v_conj_im(){ v_cs c; c.m128i = _mm_sign_epi16(this->m128i, VMASK::__0x80000001800000018000000180000001<v_cs>().m128i); return c; }
__forceinline v_cs v_cs::v_conj_re(){ v_cs c; c.m128i = _mm_sign_epi16(this->m128i, VMASK::__0x00018000000180000001800000018000<v_cs>().m128i); return c; }

__forceinline v_cs v_add(v_cs &a, v_cs &b){ v_cs c; c.m128i     = _mm_add_epi16(a.m128i, b.m128i); return c; }
__forceinline v_cs v_adds(v_cs &a, v_cs &b){ v_cs c; c.m128i    = _mm_adds_epi16(a.m128i, b.m128i); return c; }
__forceinline v_cs v_sub(v_cs &a, v_cs &b){ v_cs c; c.m128i     = _mm_sub_epi16(a.m128i, b.m128i); return c; }
__forceinline v_cs v_subs(v_cs &a, v_cs &b){ v_cs c; c.m128i    = _mm_subs_epi16(a.m128i, b.m128i); return c; }

__forceinline v_cs v_avg(v_cs &a, v_cs &b){ v_cs c; c = (v_cs)v_avg((v_s)a, (v_s)b); return c; }
// conditional copy float from b and a to r on the mask f0~f3, 1: copy from b, 0: copy from a
template<int i0, int i1, int i2, int i3>
__forceinline v_cs v_select(v_cs &a, v_cs &b){ v_cs c; c.m128 = _mm_blend_ps( a.m128, b.m128, ( i0 | (i1 << 1) | (i2 << 2) | (i3 << 3) ) ); return c; }

__forceinline v_cb v_convert2cb(v_cs &c0, v_cs &c1){ v_cb c; c.m128i = _mm_packs_epi16(c0.m128i, c1.m128i); return c; }

__forceinline v_cs v_hadd(v_cs &a, v_cs &b){ 
  v_cs temp1, temp2, sum;
  temp1.m128i  = _mm_shuffle_epi32(a.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i  = _mm_add_epi16(a.m128i, temp1.m128i);
  temp2.m128i  = _mm_shuffle_epi32(b.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i  = _mm_add_epi16(b.m128i, temp1.m128i);
  sum.m128     = _mm_shuffle_ps(temp1.m128, temp2.m128, _MM_SHUFFLE(2, 0, 2, 0));
  return sum;
}

__forceinline v_cs v_hadds(v_cs &a, v_cs &b){ 
  v_cs temp1, temp2, sum;
  temp1.m128i  = _mm_shuffle_epi32(a.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i  = _mm_adds_epi16(a.m128i, temp1.m128i);
  temp2.m128i  = _mm_shuffle_epi32(b.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i  = _mm_adds_epi16(b.m128i, temp1.m128i);
  sum.m128     = _mm_shuffle_ps(temp1.m128, temp2.m128, _MM_SHUFFLE(2, 0, 2, 0));
  return sum;
}
__forceinline v_cs v_hsub(v_cs &a, v_cs &b){ 
  v_cs temp1, temp2, sum;
  temp1.m128i  = _mm_shuffle_epi32(a.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i  = _mm_sub_epi16(a.m128i, temp1.m128i);
  temp2.m128i  = _mm_shuffle_epi32(b.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i  = _mm_sub_epi16(b.m128i, temp1.m128i);
  sum.m128     = _mm_shuffle_ps(temp1.m128, temp2.m128, _MM_SHUFFLE(2, 0, 2, 0));
  return sum;
}

__forceinline v_cs v_hsubs(v_cs &a, v_cs &b){ 
  v_cs temp1, temp2, sum;
  temp1.m128i  = _mm_shuffle_epi32(a.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i  = _mm_subs_epi16(a.m128i, temp1.m128i);
  temp2.m128i  = _mm_shuffle_epi32(b.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i  = _mm_subs_epi16(b.m128i, temp1.m128i);
  sum.m128     = _mm_shuffle_ps(temp1.m128, temp2.m128, _MM_SHUFFLE(2, 0, 2, 0));
  return sum;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
__forceinline void v_mul2i(v_cs &c0, v_cs &c1, v_i &re, v_i &im){ 
  v_cs temp1, temp2;
  temp1.m128i = _mm_shufflelo_epi16(c0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i = _mm_sign_epi16(c1.m128i, VMASK::__0x80000001800000018000000180000001<v_cs>().m128i);
  re.m128i    = _mm_madd_epi16(c0.m128i, temp2.m128i);
  im.m128i    = _mm_madd_epi16(temp1.m128i, c1.m128i);
}
// 3rd parameter can be got from VMASK::__0x80000001800000018000000180000001<v_cs>()
__forceinline void v_mul2i(v_cs &c0, v_cs &c1, const v_cs &v_0x80000001800000018000000180000001, v_i &re, v_i &im){ 
  v_cs temp1, temp2;
  temp1.m128i = _mm_shufflelo_epi16(c0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i = _mm_sign_epi16(c1.m128i, v_0x80000001800000018000000180000001.m128i);
  re.m128i    = _mm_madd_epi16(c0.m128i, temp2.m128i);
  im.m128i    = _mm_madd_epi16(temp1.m128i, c1.m128i);
}
// 3rd parameter can be got from VMASK::__0x80000001800000018000000180000001<v_cs>()
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
__forceinline void v_mul2ci(v_cs &cs0, v_cs &cs1, v_ci &ci0, v_ci &ci1){ 
  v_cs temp1, temp2; v_i re, im;
  temp1.m128i = _mm_shufflelo_epi16(cs0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i = _mm_sign_epi16(cs1.m128i, VMASK::__0x80000001800000018000000180000001<v_cs>().m128i);
  re.m128i    = _mm_madd_epi16(cs0.m128i, temp2.m128i);
  im.m128i    = _mm_madd_epi16(temp1.m128i, cs1.m128i);
  ci0.m128i   = _mm_unpacklo_epi32(re.m128i, im.m128i);
  ci1.m128i   = _mm_unpackhi_epi32(re.m128i, im.m128i);
}
// 3rd parameter can be got from VMASK::__0x80000001800000018000000180000001<v_cs>()
__forceinline void v_mul2ci(v_cs &cs0, v_cs &cs1, const v_cs &v_0x80000001800000018000000180000001, v_ci &ci0, v_ci &ci1){ 
  v_cs temp1, temp2; v_i re, im;
  temp1.m128i = _mm_shufflelo_epi16(cs0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i = _mm_sign_epi16(cs1.m128i, v_0x80000001800000018000000180000001.m128i);
  re.m128i    = _mm_madd_epi16(cs0.m128i, temp2.m128i);
  im.m128i    = _mm_madd_epi16(temp1.m128i, cs1.m128i);
  ci0.m128i   = _mm_unpacklo_epi32(re.m128i, im.m128i);
  ci1.m128i   = _mm_unpackhi_epi32(re.m128i, im.m128i);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
__forceinline void v_conjmul2i(v_cs &c0, v_cs &c1, v_i &re, v_i &im){
  v_cs temp1, temp2;
  temp1.m128i = _mm_shufflelo_epi16(c0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i = _mm_sign_epi16(c1.m128i, VMASK::__0x80000001800000018000000180000001<v_cs>().m128i);
  re.m128i    = _mm_madd_epi16(c0.m128i, c1.m128i);
  im.m128i    = _mm_madd_epi16(temp1.m128i, temp2.m128i);
}
// 3rd parameter can be got from VMASK::__0x80000001800000018000000180000001<v_cs>()
__forceinline void v_conjmul2i(v_cs &c0, v_cs &c1, const v_cs &v_0x80000001800000018000000180000001, v_i &re, v_i &im){
  v_cs temp1, temp2;
  temp1.m128i = _mm_shufflelo_epi16(c0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i = _mm_sign_epi16(c1.m128i, v_0x80000001800000018000000180000001.m128i);
  re.m128i    = _mm_madd_epi16(c0.m128i, c1.m128i);
  im.m128i    = _mm_madd_epi16(temp1.m128i, temp2.m128i);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
__forceinline void v_conjmul2ci(v_cs &cs0, v_cs &cs1, v_ci &ci0, v_ci &ci1){
  v_cs temp1, temp2; v_i re, im;
  temp1.m128i = _mm_shufflelo_epi16(cs0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i = _mm_sign_epi16(cs1.m128i, VMASK::__0x80000001800000018000000180000001<v_cs>().m128i);
  re.m128i    = _mm_madd_epi16(cs0.m128i, cs1.m128i);
  im.m128i    = _mm_madd_epi16(temp1.m128i, temp2.m128i);
  ci0.m128i   = _mm_unpacklo_epi32(re.m128i, im.m128i);
  ci1.m128i   = _mm_unpackhi_epi32(re.m128i, im.m128i);
}
// 3rd parameter can be got from VMASK::__0x80000001800000018000000180000001<v_cs>()
__forceinline void v_conjmul2ci(v_cs &cs0, v_cs &cs1, const v_cs &v_0x80000001800000018000000180000001, v_ci &ci0, v_ci &ci1){
  v_cs temp1, temp2; v_i re, im;  
  temp1.m128i = _mm_shufflelo_epi16(cs0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_shufflehi_epi16(temp1.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp2.m128i = _mm_sign_epi16(cs1.m128i, v_0x80000001800000018000000180000001.m128i);
  re.m128i    = _mm_madd_epi16(cs0.m128i, cs1.m128i);
  im.m128i    = _mm_madd_epi16(temp1.m128i, temp2.m128i);
  ci0.m128i   = _mm_unpacklo_epi32(re.m128i, im.m128i);
  ci1.m128i   = _mm_unpackhi_epi32(re.m128i, im.m128i);
}

__forceinline v_cs v_hsum(v_cs &c0, v_cs &c1, v_cs &c2, v_cs &c3){
  v_cs temp1, temp2, temp3, sum;
  temp1.m128i = _mm_unpacklo_epi32(c0.m128i, c2.m128i);/* 2.1 0.1 2.0 0.0*/
  temp2.m128i = _mm_unpackhi_epi32(c0.m128i, c2.m128i);/* 2.3 0.3 2.2 0.2*/
  temp3.m128i = _mm_add_epi16(temp1.m128i, temp2.m128i);/* 2.13 0.13 2.02 0.02*/
  temp1.m128i = _mm_unpacklo_epi32(c1.m128i, c3.m128i);/* 3.1 1.1 3.0 1.0*/
  temp2.m128i = _mm_unpackhi_epi32(c1.m128i, c3.m128i);/* 3.3 1.3 3.2 1.2*/
  temp1.m128i = _mm_add_epi16(temp1.m128i, temp2.m128i);/* 3.13 1.13 3.02 1.02*/
  temp2.m128i = _mm_unpacklo_epi32(temp3.m128i, temp1.m128i);/* 3.02 2.02 1.02 0.02*/
  temp3.m128i = _mm_unpackhi_epi32(temp3.m128i, temp1.m128i);/* 3.13 2.13 1.13 0.13*/
  sum.m128i   = _mm_add_epi16(temp2.m128i, temp3.m128i);
  return sum;
}

__forceinline v_cs v_hsums(v_cs &c0, v_cs &c1, v_cs &c2, v_cs &c3){
  v_cs temp1, temp2, temp3, sum;
  temp1.m128i = _mm_unpacklo_epi32(c0.m128i, c2.m128i);/* 2.1 0.1 2.0 0.0*/
  temp2.m128i = _mm_unpackhi_epi32(c0.m128i, c2.m128i);/* 2.3 0.3 2.2 0.2*/
  temp3.m128i = _mm_adds_epi16(temp1.m128i, temp2.m128i);/* 2.13 0.13 2.02 0.02*/
  temp1.m128i = _mm_unpacklo_epi32(c1.m128i, c3.m128i);/* 3.1 1.1 3.0 1.0*/
  temp2.m128i = _mm_unpackhi_epi32(c1.m128i, c3.m128i);/* 3.3 1.3 3.2 1.2*/
  temp1.m128i = _mm_adds_epi16(temp1.m128i, temp2.m128i);/* 3.13 1.13 3.02 1.02*/
  temp2.m128i = _mm_unpacklo_epi32(temp3.m128i, temp1.m128i);/* 3.02 2.02 1.02 0.02*/
  temp3.m128i = _mm_unpackhi_epi32(temp3.m128i, temp1.m128i);/* 3.13 2.13 1.13 0.13*/
  sum.m128i   = _mm_adds_epi16(temp2.m128i, temp3.m128i);
  return sum;
}

//////////////////////////////////////////////////////////////////////////

__forceinline void v_i::v_convert2q(v_q &a, v_q &b){ a.m128i = _mm_cvtepi32_epi64(this->m128i); b.m128i = _mm_cvtepi32_epi64(_mm_srli_si128(this->m128i, 8));}
__forceinline v_f  v_i::v_convert2f(){ v_f c; c.m128 = _mm_cvtepi32_ps(this->m128i); return c; }

__forceinline void v_i::v_convert2cq(v_cq &c0, v_cq &c1){ c0.m128i = _mm_cvtepi32_epi64(this->m128i);  c1.m128i = _mm_cvtepi32_epi64(_mm_srli_si128(this->m128i, 8));}
__forceinline v_i  v_i::v_hsum(){
  v_i temp, sum;
  temp.m128i = _mm_shuffle_epi32(this->m128i, _MM_SHUFFLE(1, 0, 3, 2));
  sum.m128i  = _mm_add_epi32(this->m128i, temp.m128i);
  temp.m128i = _mm_shuffle_epi32(sum.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  sum.m128i  = _mm_add_epi32(temp.m128i, sum.m128i);
  return sum;
}
__forceinline void  v_i::v_sqr2q(v_q &q0, v_q &q1){
  v_q q13, q24; 
  q13.m128i = _mm_mul_epi32(this->m128i, this->m128i);
  v_q i24   = _mm_srli_epi64(this->m128i, 32);
  q24.m128i = _mm_mul_epi32(i24.m128i, i24.m128i);
  q0.m128i  = _mm_unpacklo_epi64(q13.m128i, q24.m128i); 
  q1.m128i  = _mm_unpackhi_epi64(q13.m128i, q24.m128i);
}

__forceinline v_i v_i::v_signmsk(){ v_i c; c.m128i             = _mm_cmpgt_epi32(this->m128i, VMASK::__0x00000000000000000000000000000000<v_i>().m128i); return c; }


__forceinline v_i v_add(v_i &a, v_i &b){ v_i c; c.m128i                     = _mm_add_epi32(a.m128i, b.m128i); return c; }
__forceinline v_i v_hadd(v_i &a, v_i &b){ v_i c; c.m128i                    = _mm_hadd_epi32(a.m128i, b.m128i); return c; }
__forceinline v_i v_sub(v_i &a, v_i &b){ v_i c; c.m128i                     = _mm_sub_epi32(a.m128i, b.m128i); return c; }
__forceinline v_i v_hsub(v_i &a, v_i &b){ v_i c; c.m128i                    = _mm_hsub_epi32(a.m128i, b.m128i); return c; }
__forceinline v_i v_max(v_i &a, v_i &b){ v_i c; c.m128i                     = _mm_max_epi32(a.m128i, b.m128i); return c; }
__forceinline v_i v_min(v_i &a, v_i &b){ v_i c; c.m128i                     = _mm_min_epi32(a.m128i, b.m128i); return c; }
// DEST[63:0]                                                               = DEST[31:0] * SRC[31:0];
// DEST[127:64]                                                             = DEST[95:64] * SRC[95:64];
__forceinline v_q v_mul13(v_i &a, v_i &b){ v_q c; c.m128i                   = _mm_mul_epi32(a.m128i, b.m128i); return c; }
__forceinline v_q v_mul24(v_i &a, v_i &b){ v_q c; c.m128i                   = _mm_mul_epi32(_mm_srli_epi64(a.m128i, 32), _mm_srli_epi64(b.m128i, 32)); return c; }
__forceinline void v_mul(v_i &a, v_i &b, v_q &q0, v_q &q1){ v_q q13, q24; q13 = v_mul13(a, b); q24 = v_mul24(a, b); q0.m128i = _mm_unpacklo_epi64(q13.m128i, q24.m128i); q1.m128i = _mm_unpackhi_epi64(q13.m128i, q24.m128i);}
//Temp0[63:0]                                                               = DEST[31:0] * SRC[31:0];
//...
//DEST[31:0]                                                = Temp0[31:0];
__forceinline v_i v_mul_lo(v_i &a, v_i &b){ v_i c; c.m128i  = _mm_mullo_epi32(a.m128i, b.m128i); return c; }
__forceinline v_s v_pack(v_i &a, v_i &b){ v_s c; c.m128i    = _mm_packs_epi32(a.m128i, b.m128i); return c; }
__forceinline v_us v_packu(v_i &a, v_i &b){ v_us c; c.m128i = _mm_packus_epi32(a.m128i, b.m128i); return c; }

__forceinline v_i v_unpack_lo(v_i &a, v_i &b){ v_i c; c.m128i = _mm_unpacklo_epi32(a.m128i, b.m128i); return c; }
__forceinline v_i v_unpack_hi(v_i &a, v_i &b){ v_i c; c.m128i = _mm_unpackhi_epi32(a.m128i, b.m128i); return c; }

// if                                                    a==b, r=FF else r=0
__forceinline v_i v_equal(v_i &a, v_i &b){ v_i c; c.m128i = _mm_cmpeq_epi32(a.m128i, b.m128i); return c; }
__forceinline v_i v_great(v_i &a, v_i &b){ v_i c; c.m128i = _mm_cmpgt_epi32(a.m128i, b.m128i); return c; }
__forceinline v_i v_less (v_i &a, v_i &b){ v_i c; c.m128i = _mm_cmpgt_epi32(b.m128i, a.m128i); return c; }

__forceinline v_i v_avg  (v_i &a, v_i &b)
{ 
  v_i c;
  c.m128i = _mm_add_epi32(b.m128i, a.m128i);
  c.m128i = _mm_sub_epi32(c.m128i, VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_i>().m128i);
  c.m128i = _mm_srai_epi32(c.m128i, 1);
  return c;
}

// conditional copy float from b and a to r on the mask f0~f3, 1: copy from b, 0: copy from a
template<int i0, int i1, int i2, int i3>
__forceinline v_i v_select(v_i &a, v_i &b){ v_i c; c.m128 = _mm_blend_ps( a.m128, b.m128, ( i0 | (i1 << 1) | (i2 << 2) | (i3 << 3) ) ); return c; }

//r0 := (mask0 & 0x80000000) ? b0 : a0
//r1 := (mask1 & 0x80000000) ? b1 : a1
//r2 := (mask2 & 0x80000000) ? b2 : a2
//r3 := (mask3 & 0x80000000) ? b3 : a3
// e.g. msk = _mm_cmpgt_ps(a, b); c = _mm_blendv_ps(a, b, msk);
__forceinline v_i v_select(v_i &a, v_i &b, v_i &msk){ v_i c; c.m128 = _mm_blendv_ps( a.m128, b.m128, msk.m128 ); return c; }

__forceinline v_s v_convert2s(v_i &a, v_i &b){ v_s c; c.m128i    = _mm_packs_epi32(a.m128i, b.m128i); return c; }
__forceinline v_us v_convert2us(v_i &a, v_i &b){ v_us c; c.m128i = _mm_packus_epi32(a.m128i, b.m128i); return c; }

__forceinline void v_real2complex(v_i &re, v_i &im, v_ci &c1, v_ci &c2){ c1.m128i = _mm_unpacklo_epi32(re.m128i, im.m128i); c2.m128i = _mm_unpackhi_epi32(re.m128i, im.m128i); }
__forceinline void v_complex2real(v_ci &c1, v_ci &c2, v_i &re, v_i &im){ v_i temp[3];
re.m128 = _mm_shuffle_ps(c1.m128, c2.m128, _MM_SHUFFLE(2, 0, 2, 0));
im.m128 = _mm_shuffle_ps(c1.m128, c2.m128, _MM_SHUFFLE(1, 3, 1, 3));}

__forceinline v_i v_hsum(v_i &c0, v_i &c1, v_i &c2, v_i &c3){
  v_i temp1, temp2, temp3, sum;
  temp1.m128i = _mm_unpacklo_epi32(c0.m128i, c2.m128i);/* 2.1 0.1 2.0 0.0*/
  temp2.m128i = _mm_unpackhi_epi32(c0.m128i, c2.m128i);/* 2.3 0.3 2.2 0.2*/
  temp3.m128i = _mm_add_epi32(temp1.m128i, temp2.m128i);/* 2.13 0.13 2.02 0.02*/
  temp1.m128i = _mm_unpacklo_epi32(c1.m128i, c3.m128i);/* 3.1 1.1 3.0 1.0*/
  temp2.m128i = _mm_unpackhi_epi32(c1.m128i, c3.m128i);/* 3.3 1.3 3.2 1.2*/
  temp1.m128i = _mm_add_epi32(temp1.m128i, temp2.m128i);/* 3.13 1.13 3.02 1.02*/
  temp2.m128i = _mm_unpacklo_epi32(temp3.m128i, temp1.m128i);/* 3.02 2.02 1.02 0.02*/
  temp3.m128i = _mm_unpackhi_epi32(temp3.m128i, temp1.m128i);/* 3.13 2.13 1.13 0.13*/
  sum.m128i   = _mm_add_epi32(temp2.m128i, temp3.m128i);
  return sum;
}

//////////////////////////////////////////////////////////////////////////
// v_ui
//////////////////////////////////////////////////////////////////////////
__forceinline v_ui v_add(v_ui &a, v_ui &b){ v_ui c; c.m128i                      = _mm_add_epi32(a.m128i, b.m128i); return c; }
__forceinline v_ui v_hadd(v_ui &a, v_ui &b){ v_ui c; c.m128i                     = _mm_hadd_epi32(a.m128i, b.m128i); return c; }
__forceinline v_ui v_sub(v_ui &a, v_ui &b){ v_ui c; c.m128i                      = _mm_sub_epi32(a.m128i, b.m128i); return c; }
__forceinline v_ui v_hsub(v_ui &a, v_ui &b){ v_ui c; c.m128i                     = _mm_hsub_epi32(a.m128i, b.m128i); return c; }
__forceinline v_ui v_max(v_ui &a, v_ui &b){ v_ui c; c.m128i                      = _mm_max_epu32(a.m128i, b.m128i); return c; }
__forceinline v_ui v_min(v_ui &a, v_ui &b){ v_ui c; c.m128i                      = _mm_min_epu32(a.m128i, b.m128i); return c; }
__forceinline v_uq v_mul13(v_ui &a, v_ui &b){ v_uq c; c.m128i                    = _mm_mul_epu32(a.m128i, b.m128i); return c; }
__forceinline v_uq v_mul24(v_ui &a, v_ui &b){ v_uq c; c.m128i                    = _mm_mul_epu32(_mm_srli_epi64(a.m128i, 32), _mm_srli_epi64(b.m128i, 32)); return c; }
__forceinline void v_mul(v_ui &a, v_ui &b, v_uq &c, v_uq &d){ v_uq q13, q24; q13 = v_mul13(a, b); q24 = v_mul24(a, b); c.m128i = _mm_unpacklo_epi64(q13.m128i, q24.m128i); d.m128i = _mm_unpackhi_epi64(q13.m128i, q24.m128i);}

//////////////////////////////////////////////////////////////////////////
// v_ci
//////////////////////////////////////////////////////////////////////////
__forceinline v_q v_ci::v_sqr2q(){ 
  v_q q0, q1, c;
  q0.m128i = _mm_mul_epi32(this->m128i, this->m128i);
  q1.m128i = _mm_mul_epi32(_mm_srli_epi64(this->m128i, 32), _mm_srli_epi64(this->m128i, 32));
  c.m128i  = _mm_add_epi64(q0.m128i, q1.m128i);
  return c;
}

__forceinline v_ci v_ci::v_conj_im(){ v_ci c; c.m128i = _mm_sign_epi16(this->m128i, VMASK::__0x80000000000000018000000000000001<v_ci>().m128i); return c; }
__forceinline v_ci v_ci::v_conj_re(){ v_ci c; c.m128i = _mm_sign_epi16(this->m128i, VMASK::__0x00000001800000000000000180000000<v_ci>().m128i); return c; }
__forceinline v_cf v_ci::v_convert2cf(){ v_cf c; c.m128 = _mm_cvtepi32_ps(this->m128i); return c; }

__forceinline v_ci v_add(v_ci &a, v_ci &b){ v_ci c; c.m128i = _mm_add_epi32(a.m128i, b.m128i); return c; }
__forceinline v_ci v_sub(v_ci &a, v_ci &b){ v_ci c; c.m128i = _mm_sub_epi32(a.m128i, b.m128i); return c; }
__forceinline v_ci v_avg(v_ci &a, v_ci &b){ v_ci c; c = (v_ci)v_avg((v_i)a, (v_i)b); return c; }
__forceinline v_cs v_convert2cs(v_ci &c1, v_ci &c2){ v_cs c; c.m128i = _mm_packs_epi32(c1.m128i, c2.m128i); return c; }

__forceinline v_ci v_hadd(v_ci &a, v_ci &b)
{ 
  v_ci temp1, temp2, sum;
  temp1.m128i = _mm_unpacklo_epi64(a.m128i, b.m128i);
  temp2.m128i = _mm_unpackhi_epi64(a.m128i, b.m128i);
  sum.m128i   = _mm_add_epi32(temp1.m128i, temp2.m128i);
  return sum;
}
__forceinline v_ci v_hsub(v_ci &a, v_ci &b)
{ 
  v_ci temp1, temp2, sum;
  temp1.m128i = _mm_unpacklo_epi64(a.m128i, b.m128i);
  temp2.m128i = _mm_unpackhi_epi64(a.m128i, b.m128i);
  sum.m128i   = _mm_sub_epi32(temp1.m128i, temp2.m128i);
  return sum;
}

__forceinline void v_mul2q(v_ci &c0, v_ci &c1, v_q &re, v_q &im){ 
  v_ci temp1, temp2, temp3;
  temp1.m128i = _mm_mul_epi32(c0.m128i, c1.m128i);
  temp2.m128i = _mm_mul_epi32(_mm_srli_epi64(c0.m128i, 32), _mm_srli_epi64(c1.m128i, 32));
  re.m128i    = _mm_sub_epi64(temp1.m128i, temp2.m128i);
  temp3.m128i = _mm_shuffle_epi32(c0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_mul_epi32(temp3.m128i, c1.m128i);
  temp2.m128i = _mm_mul_epi32(_mm_srli_epi64(temp3.m128i, 32), _mm_srli_epi64(c1.m128i, 32));
  im.m128i    = _mm_add_epi64(temp1.m128i, temp2.m128i);
}

__forceinline void v_mul2cq(v_ci &ci0, v_ci &ci1, v_cq &cq0, v_cq &cq1){ 
  v_ci temp1, temp2, temp3; v_q re, im;
  temp1.m128i = _mm_mul_epi32(ci0.m128i, ci1.m128i);
  temp2.m128i = _mm_mul_epi32(_mm_srli_epi64(ci0.m128i, 32), _mm_srli_epi64(ci1.m128i, 32));
  re.m128i    = _mm_sub_epi64(temp1.m128i, temp2.m128i);
  temp3.m128i = _mm_shuffle_epi32(ci0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_mul_epi32(temp3.m128i, ci1.m128i);
  temp2.m128i = _mm_mul_epi32(_mm_srli_epi64(temp3.m128i, 32), _mm_srli_epi64(ci1.m128i, 32));
  im.m128i    = _mm_add_epi64(temp1.m128i, temp2.m128i);
  cq0.m128i   = _mm_unpacklo_epi64(re.m128i, im.m128i);
  cq1.m128i   = _mm_unpackhi_epi64(re.m128i, im.m128i);
}

__forceinline void v_conjmul2q(v_ci &c0, v_ci &c1, v_q &re, v_q &im){ 
  v_ci temp1, temp2, temp3;
  temp1.m128i = _mm_mul_epi32(c0.m128i, c1.m128i);
  temp2.m128i = _mm_mul_epi32(_mm_srli_epi64(c0.m128i, 32), _mm_srli_epi64(c1.m128i, 32));
  re.m128i    = _mm_add_epi64(temp1.m128i, temp2.m128i);
  temp3.m128i = _mm_shuffle_epi32(c0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_mul_epi32(temp3.m128i, c1.m128i);
  temp2.m128i = _mm_mul_epi32(_mm_srli_epi64(temp3.m128i, 32), _mm_srli_epi64(c1.m128i, 32));
  im.m128i    = _mm_sub_epi64(temp1.m128i, temp2.m128i);
}

__forceinline void v_conjmul2cq(v_ci &ci0, v_ci &ci1, v_cq &cq0, v_cq &cq1){ 
  v_ci temp1, temp2, temp3; v_q re, im;
  temp1.m128i = _mm_mul_epi32(ci0.m128i, ci1.m128i);
  temp2.m128i = _mm_mul_epi32(_mm_srli_epi64(ci0.m128i, 32), _mm_srli_epi64(ci1.m128i, 32));
  re.m128i    = _mm_add_epi64(temp1.m128i, temp2.m128i);
  temp3.m128i = _mm_shuffle_epi32(ci0.m128i, _MM_SHUFFLE(2, 3, 0, 1));
  temp1.m128i = _mm_mul_epi32(temp3.m128i, ci1.m128i);
  temp2.m128i = _mm_mul_epi32(_mm_srli_epi64(temp3.m128i, 32), _mm_srli_epi64(ci1.m128i, 32));
  im.m128i    = _mm_sub_epi64(temp1.m128i, temp2.m128i);
  cq0.m128i   = _mm_unpacklo_epi64(re.m128i, im.m128i);
  cq1.m128i   = _mm_unpackhi_epi64(re.m128i, im.m128i);
}

__forceinline v_ci v_hsum(v_ci &c0, v_ci &c1){
  v_ci temp1, temp2, sum;
  temp1.m128i = _mm_unpacklo_epi64(c0.m128i, c1.m128i);/* 1.0 0.0*/
  temp2.m128i = _mm_unpackhi_epi64(c0.m128i, c1.m128i);/* 1.1 0.1*/
  sum.m128i   = _mm_add_epi32(temp1.m128i, temp2.m128i);/* 1.01 0.01*/
  return sum;
}

//////////////////////////////////////////////////////////////////////////
// v_q
//////////////////////////////////////////////////////////////////////////
__forceinline v_q  v_q::v_signmsk(){ v_q c; c.m128i = _mm_cmpgt_epi64(this->m128i, VMASK::__0x00000000000000000000000000000000<v_q>().m128i); return c; }

__forceinline v_q v_add(v_q &a, v_q &b){ v_q c; c.m128i                     = _mm_add_epi64(a.m128i, b.m128i); return c; }
__forceinline v_q v_sub(v_q &a, v_q &b){ v_q c; c.m128i                     = _mm_sub_epi64(a.m128i, b.m128i); return c; }
__forceinline v_q v_unpack_lo(v_q &a, v_q &b){ v_q c; c.m128i               = _mm_unpacklo_epi64(a.m128i, b.m128i); return c; }
__forceinline v_q v_unpack_hi(v_q &a, v_q &b){ v_q c; c.m128i               = _mm_unpackhi_epi64(a.m128i, b.m128i); return c; }

// if                                                                      a==b, r=FF else r=0
__forceinline v_q v_equal(v_q &a, v_q &b){ v_q c; c.m128i                   = _mm_cmpeq_epi64(a.m128i, b.m128i); return c; }
__forceinline v_q v_great(v_q &a, v_q &b){ v_q c; c.m128i                   = _mm_cmpgt_epi64(a.m128i, b.m128i); return c; }
__forceinline v_q v_less (v_q &a, v_q &b){ v_q c; c.m128i                   = _mm_cmpgt_epi64(b.m128i, a.m128i); return c; }

__forceinline v_q v_avg  (v_q &a, v_q &b)
{ 
  v_q c, d;
  c.m128i = _mm_add_epi64(b.m128i, a.m128i);
  c.m128i = _mm_sub_epi64(c.m128i, VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_q>().m128i);
  d.m128i = _mm_and_si128(c.m128i, VMASK::__0x80000000000000008000000000000000<v_q>().m128i);
  c.m128i = _mm_srli_epi64(c.m128i, 1);
  c.m128i = _mm_xor_si128(c.m128i, d.m128i);
  return c;
}
template<int q0, int q1>
__forceinline v_q v_select(v_q &a, v_q &b){ v_q c; c.m128d = _mm_blend_pd( a.m128d, b.m128d, ( q0 | (q1 << 1) ) ); return c; }

// keep high 32 bits
__forceinline v_i v_convert2i(v_q &a, v_q &b){ v_i c; c.m128 = _mm_shuffle_ps(a.m128, b.m128, _MM_SHUFFLE(2, 0, 2, 0)); return c; }

__forceinline v_q v_hadd(v_q &a, v_q &b)
{ 
  v_q temp1, temp2, sum;
  temp1.m128i = _mm_unpacklo_epi64(a.m128i, b.m128i);
  temp2.m128i = _mm_unpackhi_epi64(a.m128i, b.m128i);
  sum.m128i   = _mm_add_epi64(temp1.m128i, temp2.m128i);
  return sum;
}
__forceinline v_q v_hsub(v_q &a, v_q &b)
{ 
  v_q temp1, temp2, sum;
  temp1.m128i = _mm_unpacklo_epi64(a.m128i, b.m128i);
  temp2.m128i = _mm_unpackhi_epi64(a.m128i, b.m128i);
  sum.m128i   = _mm_sub_epi64(temp1.m128i, temp2.m128i);
  return sum;
}
//////////////////////////////////////////////////////////////////////////
// v_uq
//////////////////////////////////////////////////////////////////////////
__forceinline v_uq v_avg  (v_uq &a, v_uq &b)
{ 
  v_uq c;
  c.m128i = _mm_add_epi64(b.m128i, a.m128i);
  c.m128i = _mm_sub_epi64(c.m128i, VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_uq>().m128i);
  c.m128i = _mm_srli_epi64(c.m128i, 1);
  return c;
}
//////////////////////////////////////////////////////////////////////////
// v_f
//////////////////////////////////////////////////////////////////////////
__forceinline v_i v_f::v_round2i(){ v_i c; c.m128i    = _mm_cvtps_epi32(this->m128); return c; } // _mm_cvtps_epi32, round
__forceinline v_i v_f::v_truncate2i(){ v_i c; c.m128i = _mm_cvtps_epi32(this->m128); return c; } // _mm_cvttps_epi32, truncate
__forceinline v_f v_add(v_f &a, v_f &b){ v_f c; c.m128            = _mm_add_ps(a.m128, b.m128); return c; }    
__forceinline v_f v_add_first(v_f &a, v_f &b){ v_f c; c.m128      = _mm_add_ss(a.m128, b.m128); return c; }
__forceinline v_f v_sub(v_f &a, v_f &b){ v_f c; c.m128            = _mm_sub_ps(a.m128, b.m128); return c; }
__forceinline v_f v_sub_first(v_f &a, v_f &b){ v_f c; c.m128      = _mm_sub_ss(a.m128, b.m128); return c; }
__forceinline v_f v_oddadd_evensub(v_f &a, v_f &b){ v_f c; c.m128 = _mm_addsub_ps(a.m128, b.m128); return c; }// even: sub, odd: add
__forceinline v_f v_hadd(v_f &a, v_f &b){ v_f c; c.m128           = _mm_hadd_ps(a.m128, b.m128); return c; }
__forceinline v_f v_hsub(v_f &a, v_f &b){ v_f c; c.m128           = _mm_hsub_ps(a.m128, b.m128); return c; }

__forceinline v_f v_max(v_f &a, v_f &b){ v_f c; c.m128       = _mm_max_ps(a.m128, b.m128); return c; }
__forceinline v_f v_max_first(v_f &a, v_f &b){ v_f c; c.m128 = _mm_max_ss(a.m128, b.m128); return c; }
__forceinline v_f v_min(v_f &a, v_f &b){ v_f c; c.m128       = _mm_min_ps(a.m128, b.m128); return c; }
__forceinline v_f v_min_first(v_f &a, v_f &b){ v_f c; c.m128 = _mm_min_ss(a.m128, b.m128); return c; }

__forceinline v_f v_mul(v_f &a, v_f &b){ v_f c; c.m128       = _mm_mul_ps(a.m128, b.m128); return c; }
__forceinline v_f v_mul_first(v_f &a, v_f &b){ v_f c; c.m128 = _mm_mul_ss(a.m128, b.m128); return c; }
__forceinline v_f v_div(v_f &a, v_f &b){ v_f c; c.m128       = _mm_div_ps(a.m128, b.m128); return c; }
__forceinline v_f v_div_first(v_f &a, v_f &b){ v_f c; c.m128 = _mm_div_ss(a.m128, b.m128); return c; }

__forceinline v_f v_unpacklo(v_f &a, v_f &b){ v_f c; c.m128 = _mm_unpacklo_ps(a.m128, b.m128); return c; }
__forceinline v_f v_unpackhi(v_f &a, v_f &b){ v_f c; c.m128 = _mm_unpackhi_ps(a.m128, b.m128); return c; }

/* __m128 is ugly to write */
typedef __m128 v4sf;  // vector of 4 float (sse1)
typedef __m128i v4si; // vector of 4 int (sse2)
# define ALIGN16_BEG __declspec(align(16))
# define ALIGN16_END 
/* declare some SSE constants -- why can't I figure a better way to do that? */
#define _PS_CONST(Name, Val)\
  static const ALIGN16_BEG float _ps_##Name[4] ALIGN16_END = { Val, Val, Val, Val }
#define _PI32_CONST(Name, Val)\
  static const ALIGN16_BEG int _pi32_##Name[4] ALIGN16_END = { Val, Val, Val, Val }
#define _PS_CONST_TYPE(Name, Type, Val)\
  static const ALIGN16_BEG Type _ps_##Name[4] ALIGN16_END = { Val, Val, Val, Val }

_PS_CONST(1, 1.0f);
_PS_CONST(0p5, 0.5f);
/* the smallest non denormalized float number */
_PS_CONST_TYPE(min_norm_pos, int, 0x00800000);
_PS_CONST_TYPE(mant_mask, int, 0x7f800000);
_PS_CONST_TYPE(inv_mant_mask, int, ~0x7f800000);

_PS_CONST_TYPE(sign_mask, int, 0x80000000);
_PS_CONST_TYPE(inv_sign_mask, int, ~0x80000000);

_PI32_CONST(1, 1);
_PI32_CONST(inv1, ~1);
_PI32_CONST(2, 2);
_PI32_CONST(4, 4);
_PI32_CONST(0x7f, 0x7f);

_PS_CONST(cephes_SQRTHF, 0.707106781186547524f);
_PS_CONST(cephes_log_p0, 7.0376836292E-2f);
_PS_CONST(cephes_log_p1, -1.1514610310E-1f);
_PS_CONST(cephes_log_p2, 1.1676998740E-1f);
_PS_CONST(cephes_log_p3, -1.2420140846E-1f);
_PS_CONST(cephes_log_p4, +1.4249322787E-1f);

_PS_CONST(minus_cephes_DP1, -0.78515625f);
_PS_CONST(minus_cephes_DP2, -2.4187564849853515625e-4f);
_PS_CONST(minus_cephes_DP3, -3.77489497744594108e-8f);
_PS_CONST(sincof_p0, -1.9515295891E-4f);
_PS_CONST(sincof_p1,  8.3321608736E-3f);
_PS_CONST(sincof_p2, -1.6666654611E-1f);
_PS_CONST(coscof_p0,  2.443315711809948E-005f);
_PS_CONST(coscof_p1, -1.388731625493765E-003f);
_PS_CONST(coscof_p2,  4.166664568298827E-002f);
_PS_CONST(cephes_FOPI, 1.27323954473516f); // 4 / M_PI

/* since sin_ps and cos_ps are almost identical, sincos_ps could replace both of them..
it is almost as fast, and gives you a free cosine with your sine */
__forceinline void _sincos_ps(v4sf &x, v4sf &s, v4sf &c)
{
  v4sf xmm1, xmm2, xmm3 = _mm_setzero_ps(), sign_bit_sin, y;
  v4si emm0, emm2, emm4;

  sign_bit_sin = x;
  /* take the absolute value */
  x = _mm_and_ps(x, *(v4sf*)_ps_inv_sign_mask);
  /* extract the sign bit (upper one) */
  sign_bit_sin = _mm_and_ps(sign_bit_sin, *(v4sf*)_ps_sign_mask);

  /* scale by 4/Pi */
  y = _mm_mul_ps(x, *(v4sf*)_ps_cephes_FOPI);

  /* store the integer part of y in emm2 */
  emm2 = _mm_cvttps_epi32(y);

  /* j=(j+1) & (~1) (see the cephes sources) */
  emm2 = _mm_add_epi32(emm2, *(v4si*)_pi32_1);
  emm2 = _mm_and_si128(emm2, *(v4si*)_pi32_inv1);
  y = _mm_cvtepi32_ps(emm2);

  emm4 = emm2;

  /* get the swap sign flag for the sine */
  emm0 = _mm_and_si128(emm2, *(v4si*)_pi32_4);
  emm0 = _mm_slli_epi32(emm0, 29);
  v4sf swap_sign_bit_sin = _mm_castsi128_ps(emm0);

  /* get the polynom selection mask for the sine*/
  emm2 = _mm_and_si128(emm2, *(v4si*)_pi32_2);
  emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
  v4sf poly_mask = _mm_castsi128_ps(emm2);

  /* The magic pass: "Extended precision modular arithmetic" 
  x = ((x - y * DP1) - y * DP2) - y * DP3; */
  xmm1 = *(v4sf*)_ps_minus_cephes_DP1;
  xmm2 = *(v4sf*)_ps_minus_cephes_DP2;
  xmm3 = *(v4sf*)_ps_minus_cephes_DP3;
  xmm1 = _mm_mul_ps(y, xmm1);
  xmm2 = _mm_mul_ps(y, xmm2);
  xmm3 = _mm_mul_ps(y, xmm3);
  x = _mm_add_ps(x, xmm1);
  x = _mm_add_ps(x, xmm2);
  x = _mm_add_ps(x, xmm3);

  emm4 = _mm_sub_epi32(emm4, *(v4si*)_pi32_2);
  emm4 = _mm_andnot_si128(emm4, *(v4si*)_pi32_4);
  emm4 = _mm_slli_epi32(emm4, 29);
  v4sf sign_bit_cos = _mm_castsi128_ps(emm4);

  sign_bit_sin = _mm_xor_ps(sign_bit_sin, swap_sign_bit_sin);

  /* Evaluate the first polynom  (0 <= x <= Pi/4) */
  v4sf z = _mm_mul_ps(x,x);
  y = *(v4sf*)_ps_coscof_p0;

  y = _mm_mul_ps(y, z);
  y = _mm_add_ps(y, *(v4sf*)_ps_coscof_p1);
  y = _mm_mul_ps(y, z);
  y = _mm_add_ps(y, *(v4sf*)_ps_coscof_p2);
  y = _mm_mul_ps(y, z);
  y = _mm_mul_ps(y, z);
  v4sf tmp = _mm_mul_ps(z, *(v4sf*)_ps_0p5);
  y = _mm_sub_ps(y, tmp);
  y = _mm_add_ps(y, *(v4sf*)_ps_1);

  /* Evaluate the second polynom  (Pi/4 <= x <= 0) */

  v4sf y2 = *(v4sf*)_ps_sincof_p0;
  y2 = _mm_mul_ps(y2, z);
  y2 = _mm_add_ps(y2, *(v4sf*)_ps_sincof_p1);
  y2 = _mm_mul_ps(y2, z);
  y2 = _mm_add_ps(y2, *(v4sf*)_ps_sincof_p2);
  y2 = _mm_mul_ps(y2, z);
  y2 = _mm_mul_ps(y2, x);
  y2 = _mm_add_ps(y2, x);

  /* select the correct result from the two polynoms */  
  xmm3 = poly_mask;
  v4sf ysin2 = _mm_and_ps(xmm3, y2);
  v4sf ysin1 = _mm_andnot_ps(xmm3, y);
  y2 = _mm_sub_ps(y2,ysin2);
  y = _mm_sub_ps(y, ysin1);

  xmm1 = _mm_add_ps(ysin1,ysin2);
  xmm2 = _mm_add_ps(y,y2);

  /* update the sign */
  s = _mm_xor_ps(xmm1, sign_bit_sin);
  c = _mm_xor_ps(xmm2, sign_bit_cos);
}

__forceinline void v_f::v_sincos(v_f &vsin, v_f &vcos){ _sincos_ps((v4sf&)this->m128, (v4sf&)vsin, (v4sf&)vcos); }

// dot product
//tmp0 := (mask4 == 1) ? (a0 * b0) : +0.0
//tmp1 := (mask5 == 1) ? (a1 * b1) : +0.0
//tmp2 := (mask6 == 1) ? (a2 * b2) : +0.0
//tmp3 := (mask7 == 1) ? (a3 * b3) : +0.0
//
//tmp4 := tmp0 + tmp1 + tmp2 + tmp3
//
//r0 := (mask0 == 1) ? tmp4 : +0.0
//r1 := (mask1 == 1) ? tmp4 : +0.0
//r2 := (mask2 == 1) ? tmp4 : +0.0
//r3 := (mask3 == 1) ? tmp4 : +0.0
// mi: mul mask
// si: store mask
template<int m0, int m1, int m2, int m3, int s0, int s1, int s2, int s3>
__forceinline v_f v_dotproduct(v_f &a, v_f &b){ v_f c;
c.m128 = _mm_dp_ps( a.m128, b.m128, ( s0 | (s1 << 1) | (s2 << 2) | (s3 << 3) | (m0 << 4) | (m1 << 5) | (m2 << 6) | (m3 << 7) ) ); return c; }
__forceinline v_f v_dotproduct(v_f &a, v_f &b){ v_f c; c.m128 = _mm_dp_ps( a.m128, b.m128, 0xFF ); return c; }

// conditional copy float from b and a to r on the mask f0~f3, 1: copy from b, 0: copy from a
template<int f0, int f1, int f2, int f3>
__forceinline v_f v_select(v_f &a, v_f &b){ v_f c; c.m128 = _mm_blend_ps( a.m128, b.m128, ( f0 | (f1 << 1) | (f2 << 2) | (f3 << 3) ) ); return c; }
//r0 := (mask0 & 0x80000000) ? b0 : a0
//r1 := (mask1 & 0x80000000) ? b1 : a1
//r2 := (mask2 & 0x80000000) ? b2 : a2
//r3 := (mask3 & 0x80000000) ? b3 : a3
// e.g. msk = _mm_cmpgt_ps(a, b); c = _mm_blendv_ps(a, b, msk);
__forceinline v_f v_select(v_f &a, v_f &b, v_f &msk){ v_f c; c.m128 = _mm_blendv_ps( a.m128, b.m128, msk.m128 ); return c; }

////////////////////////////////////////////////////////////////////////// 
#pragma region memory operations
__forceinline void     v_storefence(){ _mm_sfence(); }
__forceinline void     v_loadfence(){ _mm_lfence(); }
__forceinline void     v_memoryfence(){ _mm_mfence(); }
// _MM_HINT_T0, _MM_HINT_T1, _MM_HINT_T2, and _MM_HINT_NTA
#define v_prefetch(/*const char* */p, /*int*/ hint) _mm_prefetch(p, hint)
__forceinline void     v_pause(){ _mm_pause(); }
__forceinline void     v_cachelineflush(void *p){ _mm_clflush(p); }
template<typename T, int align>
__forceinline T* v_malloc(int nBytes){ return (T*)_mm_malloc(nBytes, align); }
__forceinline void     v_free(void *p){ if(p){_mm_free(p); p = NULL;} }
#pragma endregion memory operations
//////////////////////////////////////////////////////////////////////////



//! vector array

template<typename VT>
__forceinline void va_add(VT* pva, VT* pvb, VT* pvc, int vcount)
{
  for (int i = 0; i < vcount; i++)
  {
    pvc[i] = v_add(pva[i], pvb[i]);
  }
}

template<typename VT>
__forceinline void va_add(VT* pva, VT &vb, VT* pvc, int vcount)
{
  for (int i = 0; i < vcount; i++)
  {
    pvc[i] = v_add(pva[i], vb);
  }
}

template<typename VT>
__forceinline void va_sub(VT* pva, VT* pvb, VT* pvc, int vcount)
{
  for (int i = 0; i < vcount; i++)
  {
    pvc[i] = v_sub(pva[i], pvb[i]);
  }
}

template<typename VT>
__forceinline void va_sub(VT* pva, VT &vb, VT* pvc, int vcount)
{
  for (int i = 0; i < vcount; i++)
  {
    pvc[i] = v_sub(pva[i], vb);
  }
}




#pragma intrinsic(_BitScanReverse)

unsigned long v_lzcnt_s(__int16 s);
unsigned long v_lzcnt_i(__int32 i);
unsigned long v_lzcnt_q(__int64 q);


__forceinline int vcs2vcb(v_cs* pvcs, int vcscnt, v_cb* pvcb)
{
  int i, j;
  int vcslft = (vcscnt & 0x00000001);
  v_s temp1, temp2;

  j = 0;
  for (i = 0; i < vcscnt; i += 2, j++)
  {
    temp1   = pvcs[i].v_shift_right_arithmetic(8);
    temp2   = pvcs[i + 1].v_shift_right_arithmetic(8);
    pvcb[i] = v_convert2cb((v_cs)temp1, v_cs(temp2));
  }

  if (vcslft)
  {
    temp1   = pvcs[i].v_shift_right_arithmetic(8);
    pvcb[i] = v_convert2cb((v_cs)temp1, (v_cs)temp1);
  }

  return (vcscnt >> 1) + vcslft;
}

typedef struct __declspec(align(16)) _sig_blk
{
  __int8 hdr[16];
  v_cs   sig[7];
}v_sig_blk;




#ifdef USER_MODE

//////////////////////////////////////////////////////////////////////////
// v_test
//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define v_test_begin \
{\
  LARGE_INTEGER ts1, ts2, tf;\
  SetProcessAffinityMask(GetCurrentProcess(), 2);\
  SetThreadAffinityMask(GetCurrentThread(), 2);\
  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);\
  Sleep(100);\
  QueryPerformanceFrequency(&tf);

#define v_test_unit(ntimes, _test_code)\
{\
  int i;\
  QueryPerformanceCounter(&ts1);\
  for(i = 0; i < ntimes; i++){\
  _test_code;\
  }\
  QueryPerformanceCounter(&ts2);\
  printf("%d\t%I64d\t%fus\n", ntimes, ts2.QuadPart - ts1.QuadPart, \
  (double)((ts2.QuadPart - ts1.QuadPart) * 1000000) / (double)tf.QuadPart);\
}

#define v_test_end }
//////////////////////////////////////////////////////////////////////////

inline bool v_loaddump(const char* pFileName, v_cs* pvBuffer)
{
  FILE* hDmpFile;

  v_sig_blk SigBlk;
  char* pData = (char*)pvBuffer;

  fopen_s(&hDmpFile, pFileName, "rb");
  if ( NULL ==  hDmpFile)
    return false;

  while (!feof(hDmpFile))
  {
    fread(&SigBlk, 128, 1, hDmpFile);

    memcpy(pData, SigBlk.sig, 112);
    pData += 112;
  }

  fclose(hDmpFile);
  return true;
}

//////////////////////////////////////////////////////////////////////////
inline void v_print(FILE *File, v_b &v)
{
  for (int i = 0; i < v_b::elem_cnt; i++)
  {
    fprintf(File, "%4d ", v[i]);
  }
  fprintf(File, "\n");
}

inline void v_print(FILE *File, v_ub &v)
{
  for (int i = 0; i < v_ub::elem_cnt; i++)
  {
    fprintf(File, "%ud ", v[i]);
  }
  fprintf(File, "\n");
}

inline void v_print(FILE *File, v_s &v)
{
  for (int i = 0; i < v_s::elem_cnt; i++)
  {
    fprintf(File, "%6d ", v[i]);
  }
  fprintf(File, "\n");
}

inline void v_print(FILE *File, v_cb &v)
{
  for (int i = 0; i < v_cb::elem_cnt; i++)
  {
    fprintf(File, "[%3d, %3d] ", v[i].re, v[i].im);
  }
  fprintf(File, "\n");
}

inline void v_print(FILE *File, v_cs &v)
{
  for (int i = 0; i < v_cs::elem_cnt; i++)
  {
    fprintf(File, "[%5d, %5d] ", v[i].re, v[i].im);
  }
  fprintf(File, "\n");
}

inline void v_print(FILE *File, v_i &v)
{
  for (int i = 0; i < v_i::elem_cnt; i++)
  {
    fprintf(File, "%10d ", v[i]);
  }
  fprintf(File, "\n");
}

inline void v_print(FILE *File, v_q &v)
{
  for (int i = 0; i < v_q::elem_cnt; i++)
  {
    fprintf(File, "%I64d ", v[i]);
  }
  fprintf(File, "\n");
}

inline void v_print(FILE *File, v_f &v)
{
  for (int i = 0; i < v_f::elem_cnt; i++)
  {
    fprintf(File, "%f ", v[i]);
  }
  fprintf(File, "\n");
}

inline void v_print(FILE *File, v_cf &v)
{
  for (int i = 0; i < v_cf::elem_cnt; i++)
  {
    fprintf(File, "[%f, %f] ", v[i].re, v[i].im);
  }
  fprintf(File, "\n");
}

inline void v_print(FILE *File, v_ci &v)
{
  for (int i = 0; i < v_ci::elem_cnt; i++)
  {
    fprintf(File, "[%d, %d] ", v[i].re, v[i].im);
  }
  fprintf(File, "\n");
}

inline void v_print(FILE *File, v_d &v)
{
  for (int i = 0; i < v_d::elem_cnt; i++)
  {
    fprintf(File, "%f ", v[i]);
  }
  fprintf(File, "\n");
}
#endif

