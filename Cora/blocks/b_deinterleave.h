#pragma once

#include "_dot11a_deinterleave_.h"

// deinterleaver defined in 802.11a
// requires 48 inputs and produces 48 outputs
DEFINE_BLOCK(b_dot11a_deinterleave_1bpsc_1v1, 1, 1)
{
  static const int ItemsRequired = 48;
  dot11a_deinterleaver deinterleaver;

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < ItemsRequired) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<unsigned __int8>(0);

    deinterleaver._1bpsc(ip, op);

    consume(0, ItemsRequired);
    produce(0, ItemsRequired);

    return true;
  }
};

DEFINE_BLOCK(b_dot11a_deinterleave_2bpsc_1v1, 1, 1)
{
  static const int ItemsRequired = 48 * 2;
  dot11a_deinterleaver deinterleaver;

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < ItemsRequired) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<unsigned __int8>(0);

    deinterleaver._2bpsc(ip, op);

    consume(0, ItemsRequired);
    produce(0, ItemsRequired);

    return true;
  }
};

DEFINE_BLOCK(b_dot11a_deinterleave_4bpsc_1v1, 1, 1)
{
  static const int ItemsRequired = 48 * 4;
  dot11a_deinterleaver deinterleaver;

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < ItemsRequired) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<unsigned __int8>(0);

    deinterleaver._4bpsc(ip, op);

    consume(0, ItemsRequired);
    produce(0, ItemsRequired);

    return true;
  }
};

DEFINE_BLOCK(b_dot11a_deinterleave_6bpsc_1v1, 1, 1)
{
  static const int ItemsRequired = 48 * 6;
  dot11a_deinterleaver deinterleaver;

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < ItemsRequired) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<unsigned __int8>(0);

    deinterleaver._6bpsc(ip, op);

    consume(0, ItemsRequired);
    produce(0, ItemsRequired);

    return true;
  }
};