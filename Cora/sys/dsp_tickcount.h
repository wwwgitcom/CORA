#pragma once

#include <windows.h>

class tick_count 
{
public:
  friend tick_count operator-( const tick_count& t1, const tick_count& t0 );

  friend tick_count operator+( const tick_count& i, const tick_count& j ) 
  {
    return tick_count(i.value+j.value);
  }

  //! Subtract two intervals.
  friend tick_count operator-( const tick_count& i, const tick_count& j ) 
  {
    return tick_count(i.value-j.value);
  }

  //! Accumulation operator
  tick_count& operator+=( const tick_count& i ) {value += i.value; return *this;}

  //! Subtraction operator
  tick_count& operator-=( const tick_count& i ) {value -= i.value; return *this;}

  //! Construct an absolute timestamp initialized to zero.
  tick_count() : value(0) {};

  tick_count(long long count) : value(count){}

  //! Return current time.
  static tick_count now();

  //! Turn to different time scales.
  double s() const;
  double ms() const;
  double us() const;
private:
  long long value;
};

inline tick_count tick_count::now() 
{
  tick_count result;

  LARGE_INTEGER qpcnt;
  QueryPerformanceCounter(&qpcnt);
  result.value = qpcnt.QuadPart;

  return result;
}

inline double tick_count::s() const 
{
  LARGE_INTEGER qpfreq;
  QueryPerformanceFrequency(&qpfreq);
  return value/(double)qpfreq.QuadPart;
}

inline double tick_count::ms() const 
{
  LARGE_INTEGER qpfreq;
  QueryPerformanceFrequency(&qpfreq);
  return (value * 1000)/(double)qpfreq.QuadPart;
}

inline double tick_count::us() const 
{
  LARGE_INTEGER qpfreq;
  QueryPerformanceFrequency(&qpfreq);
  return (value * 1000000)/(double)qpfreq.QuadPart;
}