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

#include "_dot11n_deinterleave.h"

DEFINE_BLOCK(b_dot11n_deinterleave_1bpsc_1v1, 1, 1)
{
  static const int ItemsRequired = 52 * 1;
  dot11n_deinterleaver<1> deinterleaver;

  _local_(int, iss, 1);

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty()) *iss = atoi(v.c_str());

    deinterleaver.init(*iss);
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < ItemsRequired) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<unsigned __int8>(0);

    deinterleaver(ip, op);

    consume(0, ItemsRequired);
    produce(0, ItemsRequired);

    return true;
  }
};

DEFINE_BLOCK(b_dot11n_deinterleave_2bpsc_1v1, 1, 1)
{
  static const int ItemsRequired = 52 * 2;
  dot11n_deinterleaver<2> deinterleaver;

  _local_(int, iss, 1);

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty()) *iss = atoi(v.c_str());

    deinterleaver.init(*iss);
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < ItemsRequired) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<unsigned __int8>(0);

    deinterleaver(ip, op);

    consume(0, ItemsRequired);
    produce(0, ItemsRequired);

    return true;
  }
};


DEFINE_BLOCK(b_dot11n_deinterleave_4bpsc_1v1, 1, 1)
{
  static const int ItemsRequired = 52 * 4;
  dot11n_deinterleaver<4> deinterleaver;

  _local_(int, iss, 1);

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty()) *iss = atoi(v.c_str());

    deinterleaver.init(*iss);
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < ItemsRequired) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<unsigned __int8>(0);

    deinterleaver(ip, op);

    consume(0, ItemsRequired);
    produce(0, ItemsRequired);

    return true;
  }
};


DEFINE_BLOCK(b_dot11n_deinterleave_6bpsc_1v1, 1, 1)
{
  static const int ItemsRequired = 52 * 6;
  dot11n_deinterleaver<6> deinterleaver;

  _local_(int, iss, 1);

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty()) *iss = atoi(v.c_str());

    deinterleaver.init(*iss);
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < ItemsRequired) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<unsigned __int8>(0);

    deinterleaver(ip, op);

#if 0
    printf("deinterleave %d: ", *iss);
    for (int i = 0; i < ItemsRequired; i++)
    {
      printf("%02X ", ip[i]);
    }
    printf("\n");
#endif

    consume(0, ItemsRequired);
    produce(0, ItemsRequired);

    return true;
  }
};