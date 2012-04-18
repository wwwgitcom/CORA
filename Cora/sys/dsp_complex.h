#pragma once

template<typename T, typename R>
struct _scomplex
{
  typedef _scomplex<T, R> _Myt;

  static_assert(sizeof(R) == sizeof(T) * 2, "complex size unequal!");

  typedef struct
  {
    T re, im;
  }type;

  union
  {
    struct  
    {
      T re, im;
    };
    R _r;
  };

  _Myt()
  {
    //this->_r = 0;
  }

  _Myt(const _Myt &c)
  {
    this->_r = c._r;
  }

  _Myt(T _re, T _im) : re(_re), im(_im)
  {
  }

  _Myt(R r) : _r(r)
  {
  }

  _Myt& operator=(const _Myt &c)
  {
    this->_r = c._r;
    return (*this);
  }

  _Myt operator-() const
  {
    _Myt t;
    t.re = -re;
    t.im = -im;
    return t;
  }

  _Myt conj_re() const
  {
    _Myt t;
    t.re = -re;
    t.im = im;
    return t;
  }

  _Myt conj_im() const
  {
    _Myt t;
    t.re = re;
    t.im = -im;
    return t;
  }

  T sqr() const
  {
    return re * re + im * im;
  }

  _Myt conj_mul(_Myt& c)
  {
    _Myt t;
    t.re = re * c.re + im * c.im;
    t.im = im * c.re - re * c.im;
    return t;
  }

  // this is harmful, because it convert any other type to _Myt forcibly
  template<typename OT>
  _Myt& operator=(OT &c)
  {
    this->_r = ((_Myt&)c)._r;
    return (*this);
  }

  _Myt operator+(_Myt &a)
  {
    _Myt r;
    r.re = a.re + this->re;
    r.im = a.im + this->im;
    return  r;
  }

  _Myt& operator+=(_Myt &a)
  {
    this->re += a.re;
    this->im += a.im;
    return (*this);
  }

  _Myt operator-(_Myt &a)
  {
    _Myt r;
    r.re = this->re - a.re;
    r.im = this->im - a.im;
    return r;
  }

  _Myt& operator-=(_Myt &a)
  {
    this->re -= a.re;
    this->im -= a.im;
    return (*this);
  }

  _Myt operator*(_Myt &a)
  {
    _Myt r;
    r.re = this->re * a.re - this->im * a.im;
    r.im = this->re * a.im + this->im * a.re;
    return r;
  }

  _Myt  const operator*(T& a) const
  {
    _Myt r;
    r.re = this->re * a;
    r.im = this->im * a;
    return r;
  }

  template<typename OT>
  _Myt  const operator*(OT& a)  const
  {
    _Myt r;
    r.re = this->re * (T&)a;
    r.im = this->im * (T&)a;
    return r;
  }

  _Myt operator*=(_Myt &a)
  {
    _Myt r, T t;
    t    = this->re * a.re - this->im * a.im;
    r.im = this->re * a.im + this->im * a.re;
    r.re = t;
    return r;
  }

  _Myt& operator*=(T a)
  {
    this->re *= a;
    this->im *= a;
    return (*this);
  }

  _Myt operator/(T a)
  {
    _Myt r;
    r.re = this->re / a;
    r.im = this->im / a;
    return r;
  }

  _Myt& operator/=(T a)
  {
    this->re /= a;
    this->im /= a;
    return (*this);
  }

  _Myt& operator>>=(const int n)
  {
    this->re >>= n;
    this->im >>= n;
    return (*this);
  }

  void toStringI(_Myt& a)
  {
    printf("[%d,%d]\n", a.re, a.im);
  }
};

typedef _scomplex<signed __int8, __int16>               complex8;
typedef _scomplex<signed __int16, __int32>              complex16;
typedef _scomplex<signed __int32, __int64>              complex32;
typedef _scomplex<signed __int64, __m128i>              complex64;
typedef _scomplex<unsigned __int8, unsigned __int16>    complex8u;
typedef _scomplex<unsigned __int16, unsigned __int32>   complex16u;
typedef _scomplex<unsigned __int32, unsigned __int64>   complex32u;
typedef _scomplex<unsigned __int64, __m128i>            complex64u;
typedef _scomplex<float, double>                        complexf;
typedef _scomplex<double, __m128>                       complexd;

//template<typename T>
//T CMax(T* p, int N)
//{
//    T _max;
//    _max.re = _max.im = 0;
//    for (int i = 0; i < N; i++)
//    {
//        if (abs(p[i].re) > _max.re)
//        {
//            _max.re = p[i].re;
//        }

//        if (abs(p[i].im) > _max.im)
//        {
//            _max.im = p[i].im;
//        }
//    }
//    return _max;
//}

//template<>
//complexf CMax(complexf* p, int N)
//{
//    complexf _max;
//    _max.re = _max.im = 0;
//    for (int i = 0; i < N; i++)
//    {
//        if (fabs(p[i].re) > _max.re)
//        {
//            _max.re = p[i].re;
//        }

//        if (fabs(p[i].im) > _max.im)
//        {
//            _max.im = p[i].im;
//        }
//    }
//    return _max;
//}

//template<>
//complexd CMax(complexd* p, int N)
//{
//    complexd _max;
//    _max.re = _max.im = 0;
//    for (int i = 0; i < N; i++)
//    {
//        if (fabs(p[i].re) > _max.re)
//        {
//            _max.re = p[i].re;
//        }

//        if (fabs(p[i].im) > _max.im)
//        {
//            _max.im = p[i].im;
//        }
//    }
//    return _max;
//}

//template<typename T>
//float CSqrtMax(T* p, int N)
//{
//    float _max = 0;

//    for (int i = 0; i < N; i++)
//    {
//        float x = p[i].re;
//        float y = p[i].im;

//        float e = x * x + y * y;
//        e = sqrt(e);

//        if (e > _max)
//        {
//            _max = e;
//        }
//    }
//    return _max;
//}

