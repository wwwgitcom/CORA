#pragma once

#include "dsp_ofdm_symbol.h"

// TX, over sampled
typedef ofdm_symbol<complex16, v_cs, 128, 32> dot11n_tx_symbol;
// RX 
typedef ofdm_symbol<complex16, v_cs, 64, 16> dot11n_rx_symbol;

#define dot11n_stream1_csd_v 4

struct dot11n_rate_param
{
  int cdbps;
  int ndbps;
};

__declspec(selectany) dot11n_rate_param DOT11N_RATE_PARAMS[16] =
{
  /* MCS 0~7: for single spatial stream*/
  {52, 26},
  {104, 52},
  {104, 78},
  {208, 104},
  {208, 156},
  {312, 208},
  {312, 234},
  {312, 260},
  /* MCS 8~15: for two spatial streams*/
  {104, 52},
  {208, 104},
  {208, 156},
  {416, 208},
  {416, 312},
  {624, 416},
  {624, 468},
  {624, 520},
};

__forceinline int ht_symbol_count(int mcs, int length_bytes, int* total_soft_bits)
{
  int ntotalbits   = (length_bytes << 3) + 16 + 6; // + service: 16 bits, tail: 6 bits
  int nsymbolcount = (ntotalbits + DOT11N_RATE_PARAMS[mcs].ndbps) / DOT11N_RATE_PARAMS[mcs].ndbps;

  *total_soft_bits = nsymbolcount * DOT11N_RATE_PARAMS[mcs].ndbps;
  return nsymbolcount;
}

__forceinline int ht_padding_bytes(int mcs, int length_bytes)
{
  int ntotalbytes = 2 + length_bytes;

}