// Fundamental operators defined on SSE vector registers
#pragma once

// WARNING: DO NOT include non default header files to maintain the independency
#include <limits.h>
#include <mmintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include "_complex.h"

// Note:
//   1. SSE2 intrinsic is assumed to be supported on target platform
//   2. if below instruction set is not supported, please disable respectively
//
//#define __SSE4__      // optional

// NOTE!!!!
// Set code optimization option "MSC_OPTIMIZATION" to /O2 (maximize speed)
// in the sources file, which is necessary for DSP related inline functions.
// Otherwise inline functions will not inline expanded. The default value
// is /Oxs (minimize size) in free build, and /Od /Oi in check build.
// ref: http://msdn.microsoft.com/en-us/library/ff549305%28VS.85%29.aspx
#define DSP_INLINE		__forceinline
// Note: DSP_INLINE1 is just a hint for compilier, not compulsive
#define DSP_INLINE1		inline

// Note: below declaration are orginal found in <tmmintrin.h> in VS2008 include directory.
// However the header file is missing in WinDDK\7600.16385.0, so copy here to remove the dependency
extern "C" extern __m128i _mm_sign_epi8 (__m128i a, __m128i b);
extern "C" extern __m128i _mm_sign_epi16 (__m128i a, __m128i b);
extern "C" extern __m128i _mm_sign_epi32 (__m128i a, __m128i b);
extern "C" extern __m128i _mm_sign_epi64 (__m128i a, __m128i b);
extern "C" extern __m128i _mm_abs_epi8 (__m128i a);
extern "C" extern __m128i _mm_abs_epi16 (__m128i a);
extern "C" extern __m128i _mm_abs_epi32 (__m128i a);
extern "C" extern __m128i _mm_abs_epi64 (__m128i a);

// Note: 
// 1. Below declaration are orginal found in <smmintrin.h> in VS2008 include directory.
//    However the header file is missing in WinDDK\7600.16385.0, so copy here to remove the dependency
// 2. Below are SSE4.1 intrinsics, it may be compiled on other CPU, but runtime will throw
//    an unhandled exception of illegal instruction
extern "C" extern __m128i _mm_min_epi8 (__m128i val1, __m128i val2);
extern "C" extern __m128i _mm_max_epi8 (__m128i val1, __m128i val2);
extern "C" extern __m128i _mm_min_epu16(__m128i val1, __m128i val2);
extern "C" extern __m128i _mm_max_epu16(__m128i val1, __m128i val2);
extern "C" extern __m128i _mm_min_epi32(__m128i val1, __m128i val2);
extern "C" extern __m128i _mm_max_epi32(__m128i val1, __m128i val2);
extern "C" extern __m128i _mm_min_epu32(__m128i val1, __m128i val2);
extern "C" extern __m128i _mm_max_epu32(__m128i val1, __m128i val2);

// Note: below declaration are orginal found in <smmintrin.h> in VS2008 include directory.
extern "C" extern int _mm_extract_epi8 (__m128i src, const int ndx);
extern "C" extern int _mm_extract_epi32(__m128i src, const int ndx);
#if defined(_M_X64)
extern __int64 _mm_extract_epi64(__m128i src, const int ndx);
#endif


template<typename TO, typename T>
DSP_INLINE TO operator+=(TO& a, const T& b) { a.re += b.re; a.im += b.im; return a; }
template<typename TO, typename T>
DSP_INLINE TO operator-=(TO& a, const T& b) { a.re -= b.re; a.im -= b.im; return a; }
template<typename T>
DSP_INLINE T operator>>(const T& a, int shift) { T t; t.re = a.re >> shift; t.im = a.im >> shift; return t; }

//////////////////////////////////////////////////////////////////////////////
// Data structure definition for m128 wrapper types
// Note:
// 1. normally we use template to define similiar structs, but in this case,
// align() parameter is hard to defined by template parameter, so we use macro
// instead.
// 2. the structs all have constructors, so don't define global static objects
// in kernel mode, otherwise, .CRT section will be introduced.
#define PVECTOR_STRUCT(NEWSTRUCT, TRAW, TDATA, ALIGN)		\
struct NEWSTRUCT												\
{																\
    static const size_t size = sizeof(TRAW) / sizeof(TDATA);	\
    typedef __declspec(align(ALIGN)) TDATA data_type[size];		\
    typedef TRAW raw_type;                                      \
    typedef TDATA elem_type;                                    \
    NEWSTRUCT() { }												\
    explicit NEWSTRUCT(TRAW r) : _raw(r) { }					\
    template<typename TA> __forceinline explicit NEWSTRUCT(const TA& a) : _raw(TRAW(a)) { }              \
    __forceinline NEWSTRUCT(const data_type& pa) : _raw(*(TRAW*)pa) { }		\
    __forceinline TDATA& operator[](size_t index) { return _data[index]; }	\
    __forceinline const TDATA& operator[](size_t index) const { return _data[index]; }	        \
    __forceinline NEWSTRUCT& operator=(const NEWSTRUCT& a) { _raw = a._raw; return *this; }	    \
    __forceinline NEWSTRUCT& operator=(const data_type& pa) { _raw = *(TRAW*)pa; return *this; }	\
    __forceinline NEWSTRUCT& operator=(const raw_type& r) { _raw = r; return *this; }	    \
    __forceinline operator TRAW&() { return _raw; }                           \
    __forceinline operator const TRAW&() const { return _raw; }               \
private:                                                        \
    union														\
    {															\
        TRAW _raw;												\
        TDATA _data[size];										\
    };															\
};

PVECTOR_STRUCT(vb,   __m128i, __int8,           16);
PVECTOR_STRUCT(vub,  __m128i, unsigned __int8,  16);
PVECTOR_STRUCT(vs,   __m128i, __int16,          16);
PVECTOR_STRUCT(vus,  __m128i, unsigned __int16, 16);
PVECTOR_STRUCT(vi,   __m128i, __int32,          16);
PVECTOR_STRUCT(vui,  __m128i, unsigned __int32, 16);
PVECTOR_STRUCT(vq,   __m128i, __int64,          16);
PVECTOR_STRUCT(vuq,  __m128i, unsigned __int64, 16);
PVECTOR_STRUCT(vf,   __m128,  float,            16);
PVECTOR_STRUCT(vcb,  __m128i, COMPLEX8,         16);
PVECTOR_STRUCT(vcub, __m128i, COMPLEXU8,        16);
PVECTOR_STRUCT(vcs,  __m128i, COMPLEX16,        16);
PVECTOR_STRUCT(vcus, __m128i, COMPLEXU16,       16);
PVECTOR_STRUCT(vci,  __m128i, COMPLEX32,        16);
PVECTOR_STRUCT(vcui, __m128i, COMPLEXU32,       16);
PVECTOR_STRUCT(vcq,  __m128i, COMPLEX64,        16);
PVECTOR_STRUCT(vcuq, __m128i, COMPLEXU64,       16);
PVECTOR_STRUCT(vcf,  __m128,  COMPLEXF,         16);

struct SignalBlock
{
    static const size_t size = 7;
    vcs _data[size];
    vcs& operator[](size_t index) { return _data[index]; }
    const vcs& operator[](size_t index) const { return _data[index]; }
};


//////////////////////////////////////////////////////////////////////////////
// Constants

// Note:
//   1. embedded all consts into function so that we have opportunity to optimize its implemtation
//   2. possible impl: RAM, dynamic calc
class vector128_consts
{
    const static __declspec(align(16)) __m128i int__0x00018000000180000001800000018000;
    const static __declspec(align(16)) __m128i int__0x80000001800000018000000180000001;
    const static __declspec(align(16)) __m128i int__0x0000FFFF0000FFFF0000FFFF0000FFFF;
public:
    template<typename T>
    DSP_INLINE static const T __0x00000000000000000000000000000000()
    {
        T ret;
        set_zero(ret);
        return ret;
    }

    template<typename T>
    DSP_INLINE static const T __0x00018000000180000001800000018000()
    {
        const static vub::data_type value =
        {
            0x00, 0x80, 0x01, 0x00,
            0x00, 0x80, 0x01, 0x00,
            0x00, 0x80, 0x01, 0x00,
            0x00, 0x80, 0x01, 0x00,
        };
        return T(vub(value));
    }

    template<typename T>
    DSP_INLINE static const T __0x80000001800000018000000180000001()
    {
        const static vub::data_type value =
        {
            0x01, 0x00, 0x00, 0x80,
            0x01, 0x00, 0x00, 0x80,
            0x01, 0x00, 0x00, 0x80,
            0x01, 0x00, 0x00, 0x80,
        };
        return T(vub(value));
    }

    template<typename T>
    DSP_INLINE static const T __0x0000FFFF0000FFFF0000FFFF0000FFFF()
    {
        const static vub::data_type value =
        {
            0xFF, 0xFF, 0x00, 0x00,
            0xFF, 0xFF, 0x00, 0x00,
            0xFF, 0xFF, 0x00, 0x00,
            0xFF, 0xFF, 0x00, 0x00
        };
        return T(vub(value));
    }

    template<typename T>
    DSP_INLINE static const T __0xFFFF0000FFFF0000FFFF0000FFFF0000()
    {
        vi t;
        set_all_bits(t);
        t = shift_left(t, 16);
        return (T)t;
    }

    template<typename T>
    DSP_INLINE static const T __0xFFFFFFFF00000000FFFFFFFF00000000()
    {
        vq t;
        set_all_bits(t);
        t = shift_left(t, 32);
        return (T)t;
    }

    template<typename T>
    DSP_INLINE static const T __0xFFFFFFFFFFFFFFFF0000000000000000()
    {
        vq t;
        set_all_bits(t);
        // Shift left by 8 bytes
        t = (vq)_mm_slli_si128(t, 8);
        return (T)t;
    }

    template<typename T>
    DSP_INLINE static const T __0xFFFF0000FFFF00000000000000000000()
    {
        vi t;
        set_all_bits(t);
        // Shift left by 8 bytes
        t = (vi)_mm_slli_si128(t, 8);
        t = shift_left(t, 16);
        return (T)t;
    }

    template<typename T>
    DSP_INLINE static const T __0xFFFF0000000000000000000000000000()
    {
        vq t;
        set_all_bits(t);
        // Shift left by 15 bytes
        t = (vq)_mm_slli_si128(t, 14);
        return (T)t;
    }

    template<typename T> DSP_INLINE static const T middle() { }
    template<> DSP_INLINE static const vub middle<vub>()
    {
        const static vub::data_type mid = {
            0x80, 0x80, 0x80, 0x80, 
            0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 
            0x80, 0x80, 0x80, 0x80,
        };
        return mid;
    }
    template<> DSP_INLINE static const vs middle<vs>()
    {
        const static vus::data_type mid = {
            0x8000, 0x8000, 0x8000, 0x8000,
            0x8000, 0x8000, 0x8000, 0x8000,
        };
        return (vs)(vus)mid;
    }
};

//////////////////////////////////////////////////////////////////////////////
// Private macros

// Macro to define operators with 1 operand and 1 result, which are of the same type
// Note: non template version
#define DEFINE_OP_ARITHMETIC1(OP, T, INSTRINSIC)        \
    DSP_INLINE T OP(const T& a) { return (T)INSTRINSIC(a); }

// Macro to define operators with 2 operands and 1 result, which are of the same type
// Using template to define operations are all m128 wrapper types
#define DEFINE_TEMPLATE_OP_ARITHMETIC2(OP, INSTRINSIC)              \
    template<typename T>                                            \
    DSP_INLINE T OP(const T& a, const T& b) { return (T)INSTRINSIC(a, b); }

// Macro to define operators with 2 operands and 1 result, which are of the same type
// Note: non template version
#define DEFINE_OP_ARITHMETIC2(OP, T, INSTRINSIC)        \
    DSP_INLINE T OP(const T& a, const T& b) { return (T)INSTRINSIC(a, b); }

// Macro to define permutation operators
#define DEFINE_OP_PERMUTATION(OP, T, INSTRINSIC)        \
    template<int n>                                     \
    DSP_INLINE T OP(const T& a) { return (T)INSTRINSIC(a, n); }

// Macro to define 4-element permutation operators
// Note: it is indeed 2 templates, including DEFINE_OP_PERMUTATION
#define DEFINE_OP_PERMUTATION4(OP, T, INSTRINSIC)       \
    template<int a0, int a1, int a2, int a3>            \
    DSP_INLINE T OP(const T& a) { return (T)INSTRINSIC(a, _MM_SHUFFLE(a3, a2, a1, a0)); }   \
    DEFINE_OP_PERMUTATION(OP, T, INSTRINSIC)

// Macro to define shift operatiors
#define DEFINE_OP_SHIFT(OP, T, INSTRINSIC)              \
    DSP_INLINE T OP(const T& a, int nbits) { return (T)INSTRINSIC(a, nbits); }

// Macro to define 4-way reducing operators
// eg. Get sum of 4 elements in each operands and packed the 4 summarations into returned wrapper
// Note:
//   1. all operands, returned wrapper and all intermediate wrapper are of the same type T
//   2. REDUCE_OP is the underlying 2-way reducing operator
#define DEFINE_OP_REDUCE4(OP, T, REDUCE_OP)                             \
DSP_INLINE T OP(const T& a0, const T& a1, const T& a2, const T& a3)         \
{                                                                       \
    T temp1, temp2, temp3;                                              \
    temp1 = interleave_low(a0, a2);         /* 2.1 0.1 2.0 0.0*/        \
    temp2 = interleave_high(a0, a2);        /* 2.3 0.3 2.2 0.2*/        \
    temp3 = REDUCE_OP(temp1, temp2);        /* 2.13 0.13 2.02 0.02*/    \
                                                                        \
    temp1 = interleave_low(a1, a3);         /* 3.1 1.1 3.0 1.0*/        \
    temp2 = interleave_high(a1, a3);        /* 3.3 1.3 3.2 1.2*/        \
    temp1 = REDUCE_OP(temp1, temp2);        /* 3.13 1.13 3.02 1.02*/    \
                                                                        \
    temp2 = interleave_low(temp3, temp1);   /* 3.02 2.02 1.02 0.02*/    \
    temp3 = interleave_high(temp3, temp1);  /* 3.13 2.13 1.13 0.13*/    \
    return REDUCE_OP(temp2, temp3);                                     \
}

#define DEFINE_OP_REDUCE(OP, T, REDUCE_OP)								\
DSP_INLINE T OP(const T& a)													\
{																		\
    T t = REDUCE_OP(a, permutation<0xb1>(a));							\
    return REDUCE_OP(t, permutation<0x4e>(t));							\
}

// Duplicate the maximal/minimal element to all 8 components of a vector128 type
#define DEFINE_OP_DUPLICATION16_OPERATION(OP, T, OPER)      \
    DSP_INLINE T OP(const T& a)                             \
    {                                                       \
        T xmm0, xmm1 = a;                                   \
        xmm0 = (T)permutation<0x4E>((vcs)xmm1);             \
        xmm0 = OPER(xmm0, xmm1);                            \
        xmm1 = (T)permutation<0xB1>((vcs)xmm0);             \
        xmm0 = OPER(xmm0, xmm1);                            \
        xmm0 = interleave_low(xmm0, xmm0);                  \
        xmm0 = interleave_low(xmm0, xmm0);                  \
        xmm1 = (T)permutation<0x4E>((vcs)xmm0);             \
        xmm0 = OPER(xmm0, xmm1);                            \
        xmm1 = (T)permutation<0xB1>((vcs)xmm0);             \
        xmm0 = OPER(xmm0, xmm1);                            \
        return xmm0;                                        \
    }

// TODO: not duplcate to all?
#define DEFINE_OP_DUPLICATION8_OPERATION(OP, T, OPER)       \
    DSP_INLINE T OP(const T& a)                             \
    {                                                       \
        T r1, r2, r0 = a;                                   \
        r1 = (T)permutation<0x4E>((vcs)r0);                 \
        r2 = OPER(r0, r1);                                  \
        r1 = (T)permutation<0xB1>((vcs)r2);                 \
        r2 = OPER(r2, r1);                                  \
        r1 = (T)permutation_low<0xB1>(r2);                  \
        r1 = (T)permutation<1, 0, 1, 0>((vcs)r1);           \
        r2 = OPER(r2, r1);                                  \
        return r2;                                          \
    }

// Macro to define min/max for unsigned vector128 from signed one or vice-verse
#define DEFINE_OP_MINMAX_SIGNED_UNSIGNED(OP, T, TA)             \
    DSP_INLINE T OP(const T& a, const T& b)                     \
    {                                                           \
        const static TA mid = vector128_consts::middle<TA>();   \
        TA aa = xor((TA&)a, mid);                               \
        TA bb = xor((TA&)b, mid);                               \
        return (T)xor(OP(aa, bb), mid);                        \
    }

// Micro to define extracting method, similar to index operator
#define DEFINE_OP_EXTRACT(T, INTRINSIC)                     \
    template<int index> DSP_INLINE T::elem_type extract(const T& a) { return (T::elem_type)INTRINSIC(a, index); }

//////////////////////////////////////////////////////////////////////////////
// Private functions

DEFINE_OP_ARITHMETIC2(interleave_low, vb, _mm_unpacklo_epi8);
DEFINE_OP_ARITHMETIC2(interleave_low, vs, _mm_unpacklo_epi16);
DEFINE_OP_ARITHMETIC2(interleave_low, vi, _mm_unpacklo_epi32);
DEFINE_OP_ARITHMETIC2(interleave_low, vq, _mm_unpacklo_epi64);
DEFINE_OP_ARITHMETIC2(interleave_low, vcb, _mm_unpacklo_epi16);
DEFINE_OP_ARITHMETIC2(interleave_low, vcs, _mm_unpacklo_epi32);
DEFINE_OP_ARITHMETIC2(interleave_low, vci, _mm_unpacklo_epi64);
DEFINE_OP_ARITHMETIC2(interleave_low, vub, _mm_unpacklo_epi8);
DEFINE_OP_ARITHMETIC2(interleave_low, vus, _mm_unpacklo_epi16);
DEFINE_OP_ARITHMETIC2(interleave_low, vui, _mm_unpacklo_epi32);
DEFINE_OP_ARITHMETIC2(interleave_low, vuq, _mm_unpacklo_epi64);
DEFINE_OP_ARITHMETIC2(interleave_low, vcub, _mm_unpacklo_epi16);
DEFINE_OP_ARITHMETIC2(interleave_low, vcus, _mm_unpacklo_epi32);
DEFINE_OP_ARITHMETIC2(interleave_low, vcui, _mm_unpacklo_epi64);

DEFINE_OP_ARITHMETIC2(interleave_high, vb, _mm_unpackhi_epi8);
DEFINE_OP_ARITHMETIC2(interleave_high, vs, _mm_unpackhi_epi16);
DEFINE_OP_ARITHMETIC2(interleave_high, vi, _mm_unpackhi_epi32);
DEFINE_OP_ARITHMETIC2(interleave_high, vq, _mm_unpackhi_epi64);
DEFINE_OP_ARITHMETIC2(interleave_high, vcb, _mm_unpackhi_epi16);
DEFINE_OP_ARITHMETIC2(interleave_high, vcs, _mm_unpackhi_epi32);
DEFINE_OP_ARITHMETIC2(interleave_high, vci, _mm_unpackhi_epi64);
DEFINE_OP_ARITHMETIC2(interleave_high, vub, _mm_unpackhi_epi8);
DEFINE_OP_ARITHMETIC2(interleave_high, vus, _mm_unpackhi_epi16);
DEFINE_OP_ARITHMETIC2(interleave_high, vui, _mm_unpackhi_epi32);
DEFINE_OP_ARITHMETIC2(interleave_high, vuq, _mm_unpackhi_epi64);
DEFINE_OP_ARITHMETIC2(interleave_high, vcub, _mm_unpackhi_epi16);
DEFINE_OP_ARITHMETIC2(interleave_high, vcus, _mm_unpackhi_epi32);
DEFINE_OP_ARITHMETIC2(interleave_high, vcui, _mm_unpackhi_epi64);

DEFINE_OP_ARITHMETIC2(is_great, vb, _mm_cmpgt_epi8);
DEFINE_OP_ARITHMETIC2(is_great, vs, _mm_cmpgt_epi16);
DEFINE_OP_ARITHMETIC2(is_great, vi, _mm_cmpgt_epi32);
DEFINE_OP_ARITHMETIC2(is_great, vf, _mm_cmpgt_ps);

DEFINE_OP_ARITHMETIC2(is_less, vb, _mm_cmplt_epi8);
DEFINE_OP_ARITHMETIC2(is_less, vs, _mm_cmplt_epi16);
DEFINE_OP_ARITHMETIC2(is_less, vi, _mm_cmplt_epi32);
DEFINE_OP_ARITHMETIC2(is_less, vf, _mm_cmplt_ps);

template<typename T>
DSP_INLINE T signmask(const T& a) { return is_less(a, vector128_consts::__0x00000000000000000000000000000000<T>()); }

DEFINE_OP_ARITHMETIC2(sign, vb, _mm_sign_epi8);
DEFINE_OP_ARITHMETIC2(sign, vs, _mm_sign_epi16);
DEFINE_OP_ARITHMETIC2(sign, vi, _mm_sign_epi32);
DEFINE_OP_ARITHMETIC2(sign, vq, _mm_sign_epi64);
DEFINE_OP_ARITHMETIC2(sign, vcs, _mm_sign_epi16);

#ifdef __SSE4__
// Note: _mm_srli_si128 expects const shift bits, so template is introduced
// Warning: semantics changed from original v_ns2i, v_ni2q: nbytes
template<int nbytes>
DSP_INLINE vs shift_unpack_low(const vb& a) { vs r; r = _mm_cvtepi8_epi16(_mm_srli_si128(a, nbytes)); return r; }
template<int nbytes>
DSP_INLINE vi shift_unpack_low(const vs& a) { vi r; r = _mm_cvtepi16_epi32(_mm_srli_si128(a, nbytes)); return r; }
template<int nbytes>
DSP_INLINE vq shift_unpack_low(const vi& a) { vq r; r = _mm_cvtepi32_epi64(_mm_srli_si128(a, nbytes)); return r; }
#endif


//////////////////////////////////////////////////////////////////////////////
// Public Operators

// Set m128 wrapper to 0
template<typename T>
DSP_INLINE void set_zero(T& a) { __m128 t = _mm_setzero_ps(); a = (T::raw_type&)t; }

// Set m128 wrapper to all-1
#pragma warning (push)
#pragma warning (disable:4700)
template<typename T>
DSP_INLINE void set_all_bits(T& a)
{
    __m128i t;
#ifndef NDEBUG
    // Note: prevent runtime error in debug mode: variable is used without initialization
    *reinterpret_cast<__m128*>(&t) = _mm_setzero_ps();
#endif
    t = _mm_cmpeq_epi32(t, t);
    reinterpret_cast<__m128i&>(a) = t;
}
#pragma warning (pop)

// Extract element from vector128 types
// TODO: is it possible to embeded the extract method as index operator of vector128 types
DEFINE_OP_EXTRACT(vb, _mm_extract_epi8);
DEFINE_OP_EXTRACT(vub, _mm_extract_epi8);
DEFINE_OP_EXTRACT(vs, _mm_extract_epi16);
DEFINE_OP_EXTRACT(vus, _mm_extract_epi16);
DEFINE_OP_EXTRACT(vi, _mm_extract_epi32);
DEFINE_OP_EXTRACT(vui, _mm_extract_epi32);
DEFINE_OP_EXTRACT(vq, _mm_extract_epi64);
DEFINE_OP_EXTRACT(vuq, _mm_extract_epi64);

// Bitwise OR
DEFINE_TEMPLATE_OP_ARITHMETIC2(or, _mm_or_si128);
// Bitwise XOR
DEFINE_TEMPLATE_OP_ARITHMETIC2(xor, _mm_xor_si128);
// Bitwise AND
DEFINE_TEMPLATE_OP_ARITHMETIC2(and, _mm_and_si128);
// Bitwise ANDNOT
// ANDNOT(a, b) == (NOT(a)) AND b
DEFINE_TEMPLATE_OP_ARITHMETIC2(andnot, _mm_andnot_si128);

// Element-wise add
DEFINE_OP_ARITHMETIC2(add, vb, _mm_add_epi8);
DEFINE_OP_ARITHMETIC2(add, vub, _mm_add_epi8);
DEFINE_OP_ARITHMETIC2(add, vs, _mm_add_epi16);
DEFINE_OP_ARITHMETIC2(add, vus, _mm_add_epi16);
DEFINE_OP_ARITHMETIC2(add, vi, _mm_add_epi32);
DEFINE_OP_ARITHMETIC2(add, vui, _mm_add_epi32);
DEFINE_OP_ARITHMETIC2(add, vq, _mm_add_epi64);
DEFINE_OP_ARITHMETIC2(add, vuq, _mm_add_epi64);
DEFINE_OP_ARITHMETIC2(add, vf, _mm_add_ps);
DEFINE_OP_ARITHMETIC2(add, vcb, _mm_add_epi8);
DEFINE_OP_ARITHMETIC2(add, vcub, _mm_add_epi8);
DEFINE_OP_ARITHMETIC2(add, vcs, _mm_add_epi16);
DEFINE_OP_ARITHMETIC2(add, vcus, _mm_add_epi16);
DEFINE_OP_ARITHMETIC2(add, vci, _mm_add_epi32);
DEFINE_OP_ARITHMETIC2(add, vcui, _mm_add_epi32);
DEFINE_OP_ARITHMETIC2(add, vcq, _mm_add_epi64);
DEFINE_OP_ARITHMETIC2(add, vcuq, _mm_add_epi64);
DEFINE_OP_ARITHMETIC2(add, vcf, _mm_add_ps);

// Element-wise Subtract
DEFINE_OP_ARITHMETIC2(sub, vb, _mm_sub_epi8);
DEFINE_OP_ARITHMETIC2(sub, vub, _mm_sub_epi8);
DEFINE_OP_ARITHMETIC2(sub, vs, _mm_sub_epi16);
DEFINE_OP_ARITHMETIC2(sub, vus, _mm_sub_epi16);
DEFINE_OP_ARITHMETIC2(sub, vi, _mm_sub_epi32);
DEFINE_OP_ARITHMETIC2(sub, vui, _mm_sub_epi32);
DEFINE_OP_ARITHMETIC2(sub, vq, _mm_sub_epi64);
DEFINE_OP_ARITHMETIC2(sub, vuq, _mm_sub_epi64);
DEFINE_OP_ARITHMETIC2(sub, vf, _mm_sub_ps);
DEFINE_OP_ARITHMETIC2(sub, vcb, _mm_sub_epi8);
DEFINE_OP_ARITHMETIC2(sub, vcub, _mm_sub_epi8);
DEFINE_OP_ARITHMETIC2(sub, vcs, _mm_sub_epi16);
DEFINE_OP_ARITHMETIC2(sub, vcus, _mm_sub_epi16);
DEFINE_OP_ARITHMETIC2(sub, vci, _mm_sub_epi32);
DEFINE_OP_ARITHMETIC2(sub, vcui, _mm_sub_epi32);
DEFINE_OP_ARITHMETIC2(sub, vcq, _mm_sub_epi64);
DEFINE_OP_ARITHMETIC2(sub, vcuq, _mm_sub_epi64);
DEFINE_OP_ARITHMETIC2(sub, vcf, _mm_sub_ps);

// Element-wise saturation add
// Note: there is no _mm_adds_epi/u for 32/64 size elements
DEFINE_OP_ARITHMETIC2(saturation_add, vb, _mm_adds_epi8);
DEFINE_OP_ARITHMETIC2(saturation_add, vub, _mm_adds_epu8);
DEFINE_OP_ARITHMETIC2(saturation_add, vs, _mm_adds_epi16);
DEFINE_OP_ARITHMETIC2(saturation_add, vus, _mm_adds_epu16);
DEFINE_OP_ARITHMETIC2(saturation_add, vcb, _mm_adds_epi8);
DEFINE_OP_ARITHMETIC2(saturation_add, vcub, _mm_adds_epu8);
DEFINE_OP_ARITHMETIC2(saturation_add, vcs, _mm_adds_epi16);
DEFINE_OP_ARITHMETIC2(saturation_add, vcus, _mm_adds_epu16);

// Element-wise saturation subtract
DEFINE_OP_ARITHMETIC2(saturation_sub, vb, _mm_subs_epi8);
DEFINE_OP_ARITHMETIC2(saturation_sub, vub, _mm_subs_epu8);
DEFINE_OP_ARITHMETIC2(saturation_sub, vs, _mm_subs_epi16);
DEFINE_OP_ARITHMETIC2(saturation_sub, vus, _mm_subs_epu16);
DEFINE_OP_ARITHMETIC2(saturation_sub, vcb, _mm_subs_epi8);
DEFINE_OP_ARITHMETIC2(saturation_sub, vcub, _mm_subs_epu8);
DEFINE_OP_ARITHMETIC2(saturation_sub, vcs, _mm_subs_epi16);
DEFINE_OP_ARITHMETIC2(saturation_sub, vcus, _mm_subs_epu16);

// Permutate on low 4 elements
DEFINE_OP_PERMUTATION4(permutation_low, vs, _mm_shufflelo_epi16);
DEFINE_OP_PERMUTATION4(permutation_low, vcs, _mm_shufflelo_epi16);
DEFINE_OP_PERMUTATION4(permutation_low, vus, _mm_shufflelo_epi16);
DEFINE_OP_PERMUTATION4(permutation_low, vcus, _mm_shufflelo_epi16);
// Permutate on high 4 elements
DEFINE_OP_PERMUTATION4(permutation_high, vs, _mm_shufflehi_epi16);
DEFINE_OP_PERMUTATION4(permutation_high, vcs, _mm_shufflehi_epi16);
DEFINE_OP_PERMUTATION4(permutation_high, vus, _mm_shufflehi_epi16);
DEFINE_OP_PERMUTATION4(permutation_high, vcus, _mm_shufflehi_epi16);
// Permutate on all 4 elements
DEFINE_OP_PERMUTATION4(permutation, vcs, _mm_shuffle_epi32);
DEFINE_OP_PERMUTATION4(permutation, vi, _mm_shuffle_epi32);

// 4-way reducing add
DEFINE_OP_REDUCE4(reduce4_add, vcs, add);
DEFINE_OP_REDUCE4(reduce4_add, vi, add);
DEFINE_OP_REDUCE4(reduce4_saturation_add, vcs, saturation_add);
// Note: there is no intrinsic _mm_subs_epu32, so no reduce4_saturation_add on vi

// Reducing add
DEFINE_OP_REDUCE(reduce_saturation_add, vcs, saturation_add);
DEFINE_OP_REDUCE(reduce_add, vcs, add);
DEFINE_OP_REDUCE(reduce_add, vi, add);

// Element-wise assign to the same value
DSP_INLINE void set_all(vb& x, __int8 a) { x = (vb)_mm_set1_epi8(a); }
DSP_INLINE void set_all(vs& x, __int16 a) { x = (vs)_mm_set1_epi16(a); }
DSP_INLINE void set_all(vi& x, __int32 a) { x = (vi)_mm_set1_epi32(a); }
DSP_INLINE void set_all(vcs& x, COMPLEX16 a) { x = (vcs)_mm_set1_epi32(*reinterpret_cast<__int32*>(&a)); }
DSP_INLINE void set_all(vf& x, float a) { x = (vf)_mm_set1_ps(a); }
DSP_INLINE void set_all(vq& x, __int64 a)
{
#if (SIZE_MAX == _UI64_MAX)
    // _mm_set1_epi64x only available on AMD64 platform
    x = (vq)_mm_set1_epi64x(a);
#elif (SIZE_MAX == _UI32_MAX)
    // __m64 and _mm_set1_epi64 only available on IX86 platform
    __m64 t;
    t.m64_i64 = a;
    x = (vq)_mm_set1_epi64(t);
    // _mm_empty to suppresss warning C4799
    _mm_empty();
#else
#error The target platform is neither AMD64 or X86, not supported!
#endif
}

// Element-wise arithmetic left shift
DEFINE_OP_SHIFT(shift_left, vs, _mm_slli_epi16);
DEFINE_OP_SHIFT(shift_left, vi, _mm_slli_epi32);
DEFINE_OP_SHIFT(shift_left, vq, _mm_slli_epi64);
DEFINE_OP_SHIFT(shift_left, vcs, _mm_slli_epi16);
DEFINE_OP_SHIFT(shift_left, vci, _mm_slli_epi32);
DEFINE_OP_SHIFT(shift_left, vcq, _mm_slli_epi64);
DEFINE_OP_SHIFT(shift_left, vus, _mm_slli_epi16);
DEFINE_OP_SHIFT(shift_left, vui, _mm_slli_epi32);
DEFINE_OP_SHIFT(shift_left, vuq, _mm_slli_epi64);
DEFINE_OP_SHIFT(shift_left, vcus, _mm_slli_epi16);
DEFINE_OP_SHIFT(shift_left, vcui, _mm_slli_epi32);
DEFINE_OP_SHIFT(shift_left, vcuq, _mm_slli_epi64);

// Element-wise arithmetic right shift
DEFINE_OP_SHIFT(shift_right, vs, _mm_srai_epi16);
DEFINE_OP_SHIFT(shift_right, vi, _mm_srai_epi32);
DEFINE_OP_SHIFT(shift_right, vcs, _mm_srai_epi16);
DEFINE_OP_SHIFT(shift_right, vci, _mm_srai_epi32);
DEFINE_OP_SHIFT(shift_right, vus, _mm_srli_epi16);
DEFINE_OP_SHIFT(shift_right, vui, _mm_srli_epi32);
DEFINE_OP_SHIFT(shift_right, vcus, _mm_srli_epi16);
DEFINE_OP_SHIFT(shift_right, vcui, _mm_srli_epi32);
DSP_INLINE vub shift_right(const vub& a, int nbits)
{
    const static vub::data_type zero_end = {
        0xFE, 0xFE, 0xFE, 0xFE, 
        0xFE, 0xFE, 0xFE, 0xFE,
        0xFE, 0xFE, 0xFE, 0xFE, 
        0xFE, 0xFE, 0xFE, 0xFE,
    };
    vub rub0 = and (a, vub(zero_end));
    return (vub)_mm_srli_epi16(rub0, nbits);
}
//DEFINE_OP_SHIFT(shift_right, vq, _mm_srai_epi64);    // intrinsic N/A

// Packs the vcs from a and b into vcb and saturates.
DSP_INLINE vb saturation_pack(const vs& a, const vs& b) { return (vb)_mm_packs_epi16(a, b); }

// Pack elements in 2 source wrappers into returned wrapper
// Note:
//    1. each element will be packed to a half-length field, eg. __int32 --> __int16
DSP_INLINE vs pack(const vi& a, const vi& b)
{
    const vi xmm6 = vector128_consts::__0x0000FFFF0000FFFF0000FFFF0000FFFF<vi>();
    vi ta = and(a, xmm6);
    vi tb = and(b, xmm6);
    tb = shift_left(tb, 0x10);
    return (vs)or(ta, tb);
}

// Unpack elements in source wrapper to 2 destination wrappers
// Note:
//    1. each element will be unpacked to a double-length field, eg. __int8 --> __int16
//    2. r1 got the unpacked elements in source low part, r2 got high part
template<typename TO, typename T>
DSP_INLINE void unpack(TO& r1, TO& r2, const T& a)
{
#ifdef __SSE4__
    r1 = (TO)shift_unpack_low<0>(a);
    r2 = (TO)shift_unpack_low<8>(a);
#else
    T s = signmask(a);
    r1 = (TO)interleave_low(a, s);
    r2 = (TO)interleave_high(a, s);
#endif
}

// Add pair-wisely of element-wise multiplication product
// eg. (vs, vs) --> vi
//     r0 := (a0 * b0) + (a1 * b1)
//     r1 := (a2 * b2) + (a3 * b3)
//     r2 := (a4 * b4) + (a5 * b5)
//     r3 := (a6 * b6) + (a7 * b7)
DSP_INLINE vi pairwise_mul(const vs& a, const vs& b) { return (vi)_mm_madd_epi16(a, b); }

// Element-wise multiplication, leaving only low/high part product
DEFINE_OP_ARITHMETIC2(mul_low, vs, _mm_mullo_epi16);
DEFINE_OP_ARITHMETIC2(mul_high, vs, _mm_mulhi_epi16);

// Comprise complex numbers by real and imaginary parts in 2 source wrappers
// Note:
//   1. r1 got the comprised complex numbers by source low parts, r2 got high parts
DSP_INLINE void comprise(vci& r1, vci& r2, const vi& re, const vi& im)
{
    r1 = (vci)interleave_low(re, im);
    r2 = (vci)interleave_high(re, im);
}

// Negative real part of each complex numbers
// TODO: need test
DSP_INLINE vcs conjre(const vcs& a) { return sign(a, vector128_consts::__0x00018000000180000001800000018000<vcs>()); }

// Get approximate conjugate of each complex numbers, used for better performance
DSP_INLINE vcs conj(const vcs& a) { return xor(a, vector128_consts::__0xFFFF0000FFFF0000FFFF0000FFFF0000<vcs>()); }

// Get accurate conjugate of each complex numbers
DSP_INLINE vcs conj0(const vcs& a) { return sign(a, vector128_consts::__0x80000001800000018000000180000001<vcs>()); }

// Swap real and image part of each complex number
DSP_INLINE vcs flip(const vcs& a)
{
    vcs b = permutation_low<0xb1>(a);
    return permutation_high<0xb1>(b);
}

// Conjugate of first source and multiply with the second source
// ie. re + j * im = a * conj(b)
// Note:
//   1. re got all real parts of products, im got all imaginary parts
//   2. elments of product has double-length field compared to source elements
DSP_INLINE void conj_mul(vi& re, vi& im, const vcs& a, const vcs& b)
{
    vcs vs1 = permutation_low<1, 0, 3, 2>(b);
    vs1 = permutation_high<1, 0, 3, 2>(vs1);
    vs1 = conjre(vs1);
    re = pairwise_mul((vs&)a, (vs&)b);
    im = pairwise_mul((vs&)vs1, (vs&)a);
}

// Conjugate of first source and multiply with the second source, leaving only right-shifted low part product
// ie. return a * conj(b) >> nbits_right
DSP_INLINE vcs conj_mul_shift(const vcs& a, const vcs& b, int nbits_right)
{
    // b = Q3 I3 Q2 I2 Q1 I1 Q0 I0
    // vcs1 = -I3 Q3 -I2 Q2 -I1 Q1 -I0 Q0
    vcs vcs1 = conjre(a);
    vcs1 = flip(vcs1);
    
    vi vi0 = pairwise_mul((vs&)a, (vs&)b);       // vi0 = I3 I2 I1 I0, where Ii=ac-bd (a+bj)*(c+dj)=(ac-bd)+(ad+bc)j
    vi vi1 = pairwise_mul((vs&)vcs1, (vs&)b);    // vi1 = Q3 Q2 Q1 Q0

    // Shift right to normalize
    vi0 = shift_right(vi0, nbits_right);
    vi1 = shift_right(vi1, nbits_right);

    // Q3 I3 Q2 I2 Q1 I1 Q0 I0
    return (vcs)pack(vi0, vi1);
}

// Multiply leaving only right-shifted low part product
// ie. return a * b >> nbits_right
DSP_INLINE vcs mul_shift(const vcs& a, const vcs& b, int nbits_right)
{
    vi vi0 = pairwise_mul((vs&)a, (vs)conj(b));
    vi vi1 = pairwise_mul((vs&)a, (vs)flip(b));

    // Shift right to normalize
    vi0 = shift_right(vi0, nbits_right);
    vi1 = shift_right(vi1, nbits_right);

    // Q3 I3 Q2 I2 Q1 I1 Q0 I0
    return (vcs)pack(vi0, vi1);
}

// Multiply with imaginary unit
DSP_INLINE vcs mul_j(const vcs& a)
{
    return xor(flip(a), vector128_consts::__0x0000FFFF0000FFFF0000FFFF0000FFFF<vcs>());
}

// Absolute value
// TODO: for back-compatiable only, otherwise replace with accurate implementation
//template<typename T>
//DSP_INLINE T abs(const T& a) { return xor(a, shift_right(a, sizeof(a[0])*8-1)); }

// Accurate absolute value
DEFINE_OP_ARITHMETIC1(abs0, vb, _mm_abs_epi8);
DEFINE_OP_ARITHMETIC1(abs0, vs, _mm_abs_epi16);
DEFINE_OP_ARITHMETIC1(abs0, vi, _mm_abs_epi32);
DEFINE_OP_ARITHMETIC1(abs0, vq, _mm_abs_epi64);

// Minimal
// Note: don't try use the name "min", since it defined as a macro in <WinDef.h>
DEFINE_OP_ARITHMETIC2(smin, vs, _mm_min_epi16);
DEFINE_OP_ARITHMETIC2(smin, vcs, _mm_min_epi16);
DEFINE_OP_ARITHMETIC2(smin, vub, _mm_min_epu8);
DEFINE_OP_ARITHMETIC2(smin, vcub, _mm_min_epu8);
// Note: below fuctions are disabled since underlying intrinsics are in SSE4, and hard to rewrite with old intrinsics set
//DEFINE_OP_ARITHMETIC2(smin, vci, _mm_min_epi32);
//DEFINE_OP_ARITHMETIC2(smin, vcui, _mm_min_epu32);
//DEFINE_OP_ARITHMETIC2(smin, vui, _mm_min_epu32);
//DEFINE_OP_ARITHMETIC2(smin, vi, _mm_min_epi32);
#ifdef __SSE4__
DEFINE_OP_ARITHMETIC2(smin, vb, _mm_min_epi8);
DEFINE_OP_ARITHMETIC2(smin, vcb, _mm_min_epi8);
DEFINE_OP_ARITHMETIC2(smin, vus, _mm_min_epu16);
DEFINE_OP_ARITHMETIC2(smin, vcus, _mm_min_epu16);
#else
DEFINE_OP_MINMAX_SIGNED_UNSIGNED(smin, vb, vub);
DEFINE_OP_MINMAX_SIGNED_UNSIGNED(smin, vcb, vub);
DEFINE_OP_MINMAX_SIGNED_UNSIGNED(smin, vus, vs);
DEFINE_OP_MINMAX_SIGNED_UNSIGNED(smin, vcus, vs);
#endif

// Maximal
// Note: don't use max, since it defined as macro in <WinDef.h>
DEFINE_OP_ARITHMETIC2(smax, vs, _mm_max_epi16);
DEFINE_OP_ARITHMETIC2(smax, vcs, _mm_max_epi16);
DEFINE_OP_ARITHMETIC2(smax, vub, _mm_max_epu8);
DEFINE_OP_ARITHMETIC2(smax, vcub, _mm_max_epu8);
// Note: below fuctions are disabled since underlying intrinsics are in SSE4, and hard to rewrite with old intrinsics set
//DEFINE_OP_ARITHMETIC2(smax, vui, _mm_max_epu32);
//DEFINE_OP_ARITHMETIC2(smax, vcui, _mm_max_epu32);
//DEFINE_OP_ARITHMETIC2(smax, vi, _mm_max_epi32);
//DEFINE_OP_ARITHMETIC2(smax, vci, _mm_max_epi32);
#ifdef __SSE4__
DEFINE_OP_ARITHMETIC2(smax, vb, _mm_max_epi8);
DEFINE_OP_ARITHMETIC2(smax, vcb, _mm_max_epi8);
DEFINE_OP_ARITHMETIC2(smax, vus, _mm_max_epu16);
DEFINE_OP_ARITHMETIC2(smax, vcus, _mm_max_epu16);
#else
DEFINE_OP_MINMAX_SIGNED_UNSIGNED(smax, vb, vub);
DEFINE_OP_MINMAX_SIGNED_UNSIGNED(smax, vcb, vub);
DEFINE_OP_MINMAX_SIGNED_UNSIGNED(smax, vus, vs);
DEFINE_OP_MINMAX_SIGNED_UNSIGNED(smax, vcus, vs);
#endif

// Duplicate the maximal/minimal element to all components of a vector128 type
DEFINE_OP_DUPLICATION16_OPERATION(hmin, vb, smin);
DEFINE_OP_DUPLICATION16_OPERATION(hmin, vub, smin);
DEFINE_OP_DUPLICATION16_OPERATION(hmax, vb, smax);
DEFINE_OP_DUPLICATION16_OPERATION(hmax, vub, smax);
DEFINE_OP_DUPLICATION8_OPERATION(hmin, vs, smin);
DEFINE_OP_DUPLICATION8_OPERATION(hmin, vus, smin);
DEFINE_OP_DUPLICATION8_OPERATION(hmax, vs, smax);
DEFINE_OP_DUPLICATION8_OPERATION(hmax, vus, smax);
