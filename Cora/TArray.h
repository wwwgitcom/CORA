#pragma once

template<typename T, size_t N>
class Array
{
public:
  typedef Array<T, N> type;

  T m_var[N];

  Array(){memset(m_var, 0, N * sizeof(T));}
  //Array(T v){for (T &x : m_var) x = v;}
  inline T& operator [](int i){return m_var[i];}
  inline void operator = (Array &rhs){memcpy(m_var, rhs.m_var, N * sizeof(T));}
  //inline void operator = (T v){for (T &x : m_var) x = v;}
};