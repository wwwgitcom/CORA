#pragma once

#include "_b_stream_parser.h"

DEFINE_BLOCK(b_stream_parser_bpsk_1v2, 1, 2)
{
  stream_paser_bpsk_2ss _stream_parser;

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < stream_paser_bpsk_2ss::NINPUT) return false;

    auto ip = _$<uint8>(0);
    auto op1 = $_<uint8>(0);
    auto op2 = $_<uint8>(1);

    _stream_parser(ip, op1, op2);

    consume(0, stream_paser_bpsk_2ss::NINPUT);
    produce(0, stream_paser_bpsk_2ss::NOUTPUT);
    produce(1, stream_paser_bpsk_2ss::NOUTPUT);

    return true;
  }
};

DEFINE_BLOCK(b_stream_parser_qpsk_1v2, 1, 2)
{
  stream_paser_qpsk_2ss _stream_parser;

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < stream_paser_qpsk_2ss::NINPUT) return false;

    auto ip  = _$<uint8>(0);
    auto op1 = $_<uint8>(0);
    auto op2 = $_<uint8>(1);

    _stream_parser(ip, op1, op2);

    consume(0, stream_paser_qpsk_2ss::NINPUT);
    produce(0, stream_paser_qpsk_2ss::NOUTPUT);
    produce(1, stream_paser_qpsk_2ss::NOUTPUT);

    return true;
  }
};

DEFINE_BLOCK(b_stream_parser_16qam_1v2, 1, 2)
{
  stream_paser_16qam_2ss _stream_parser;

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < stream_paser_16qam_2ss::NINPUT) return false;

    auto ip  = _$<uint8>(0);
    auto op1 = $_<uint8>(0);
    auto op2 = $_<uint8>(1);

    _stream_parser(ip, op1, op2);

    consume(0, stream_paser_16qam_2ss::NINPUT);
    produce(0, stream_paser_16qam_2ss::NOUTPUT);
    produce(1, stream_paser_16qam_2ss::NOUTPUT);

    return true;
  }
};

DEFINE_BLOCK(b_stream_parser_64qam_1v2, 1, 2)
{
  stream_paser_64qam_2ss _stream_parser;

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < stream_paser_64qam_2ss::NINPUT) return false;

    auto ip  = _$<uint8>(0);
    auto op1 = $_<uint8>(0);
    auto op2 = $_<uint8>(1);

    _stream_parser(ip, op1, op2);

    consume(0, stream_paser_64qam_2ss::NINPUT);
    produce(0, stream_paser_64qam_2ss::NOUTPUT);
    produce(1, stream_paser_64qam_2ss::NOUTPUT);

    return true;
  }
};