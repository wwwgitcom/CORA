#include "stdafx.h"
#include "__b_viterbi.h"
vub::data_type ALL_INVERSE_ONE = {
  __int8(0xFE), __int8(0xFE), __int8(0xFE), __int8(0xFE), 
  __int8(0xFE), __int8(0xFE), __int8(0xFE), __int8(0xFE),
  __int8(0xFE), __int8(0xFE), __int8(0xFE), __int8(0xFE), 
  __int8(0xFE), __int8(0xFE), __int8(0xFE), __int8(0xFE),
};

vub::data_type ALL_ONE = {
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
};

vub::data_type ALL_M128 = {
  __int8(0x80), __int8(0x80), __int8(0x80), __int8(0x80), 
  __int8(0x80), __int8(0x80), __int8(0x80), __int8(0x80),
  __int8(0x80), __int8(0x80), __int8(0x80), __int8(0x80), 
  __int8(0x80), __int8(0x80), __int8(0x80), __int8(0x80),
};

A16 vub::data_type ALL_INIT = {
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
};

A16 vub::data_type ALL_INIT0 = {
  0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
};


A16 vub::data_type INDEXES[4] = {
  {0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C,
  0x20, 0x24, 0x28, 0x2C, 0x30, 0x34, 0x38, 0x3C,},

  {0x40, 0x44, 0x48, 0x4C, 0x50, 0x54, 0x58, 0x5C,
  0x60, 0x64, 0x68, 0x6C, 0x70, 0x74, 0x78, 0x7C,},

  {__int8(0x80), __int8(0x84), __int8(0x88), __int8(0x8C), 
  __int8(0x90), __int8(0x94), __int8(0x98), __int8(0x9C),
  __int8(0xA0), __int8(0xA4), __int8(0xA8), __int8(0xAC), 
  __int8(0xB0), __int8(0xB4), __int8(0xB8), __int8(0xBC),},

  {__int8(0xC0), __int8(0xC4), __int8(0xC8), __int8(0xCC), 
  __int8(0xD0), __int8(0xD4), __int8(0xD8), __int8(0xDC),
  __int8(0xE0), __int8(0xE4), __int8(0xE8), __int8(0xEC), 
  __int8(0xF0), __int8(0xF4), __int8(0xF8), __int8(0xFC),}
};

vub::data_type VIT_MA[8*SOFT_RANGE] = {
  { 0, 14,  0, 14, 14,  0, 14,  0, 14,  0, 14,  0,  0, 14,  0, 14,},     
  {14,  0, 14,  0,  0, 14,  0, 14,  0, 14,  0, 14, 14,  0, 14,  0,},     
  { 0, 14,  0, 14, 14,  0, 14,  0, 14,  0, 14,  0,  0, 14,  0, 14,},     
  {14,  0, 14,  0,  0, 14,  0, 14,  0, 14,  0, 14, 14,  0, 14,  0,},     
  {14,  0, 14,  0,  0, 14,  0, 14,  0, 14,  0, 14, 14,  0, 14,  0,},     
  { 0, 14,  0, 14, 14,  0, 14,  0, 14,  0, 14,  0,  0, 14,  0, 14,},     
  {14,  0, 14,  0,  0, 14,  0, 14,  0, 14,  0, 14, 14,  0, 14,  0,},     
  { 0, 14,  0, 14, 14,  0, 14,  0, 14,  0, 14,  0,  0, 14,  0, 14,},     
  { 2, 12,  2, 12, 12,  2, 12,  2, 12,  2, 12,  2,  2, 12,  2, 12,},     
  {12,  2, 12,  2,  2, 12,  2, 12,  2, 12,  2, 12, 12,  2, 12,  2,},     
  { 2, 12,  2, 12, 12,  2, 12,  2, 12,  2, 12,  2,  2, 12,  2, 12,},     
  {12,  2, 12,  2,  2, 12,  2, 12,  2, 12,  2, 12, 12,  2, 12,  2,},     
  {12,  2, 12,  2,  2, 12,  2, 12,  2, 12,  2, 12, 12,  2, 12,  2,},     
  { 2, 12,  2, 12, 12,  2, 12,  2, 12,  2, 12,  2,  2, 12,  2, 12,},     
  {12,  2, 12,  2,  2, 12,  2, 12,  2, 12,  2, 12, 12,  2, 12,  2,},     
  { 2, 12,  2, 12, 12,  2, 12,  2, 12,  2, 12,  2,  2, 12,  2, 12,},     
  { 4, 10,  4, 10, 10,  4, 10,  4, 10,  4, 10,  4,  4, 10,  4, 10,},     
  {10,  4, 10,  4,  4, 10,  4, 10,  4, 10,  4, 10, 10,  4, 10,  4,},     
  { 4, 10,  4, 10, 10,  4, 10,  4, 10,  4, 10,  4,  4, 10,  4, 10,},     
  {10,  4, 10,  4,  4, 10,  4, 10,  4, 10,  4, 10, 10,  4, 10,  4,},     
  {10,  4, 10,  4,  4, 10,  4, 10,  4, 10,  4, 10, 10,  4, 10,  4,},     
  { 4, 10,  4, 10, 10,  4, 10,  4, 10,  4, 10,  4,  4, 10,  4, 10,},     
  {10,  4, 10,  4,  4, 10,  4, 10,  4, 10,  4, 10, 10,  4, 10,  4,},     
  { 4, 10,  4, 10, 10,  4, 10,  4, 10,  4, 10,  4,  4, 10,  4, 10,},     
  { 6,  8,  6,  8,  8,  6,  8,  6,  8,  6,  8,  6,  6,  8,  6,  8,},     
  { 8,  6,  8,  6,  6,  8,  6,  8,  6,  8,  6,  8,  8,  6,  8,  6,},     
  { 6,  8,  6,  8,  8,  6,  8,  6,  8,  6,  8,  6,  6,  8,  6,  8,},     
  { 8,  6,  8,  6,  6,  8,  6,  8,  6,  8,  6,  8,  8,  6,  8,  6,},     
  { 8,  6,  8,  6,  6,  8,  6,  8,  6,  8,  6,  8,  8,  6,  8,  6,},     
  { 6,  8,  6,  8,  8,  6,  8,  6,  8,  6,  8,  6,  6,  8,  6,  8,},     
  { 8,  6,  8,  6,  6,  8,  6,  8,  6,  8,  6,  8,  8,  6,  8,  6,},     
  { 6,  8,  6,  8,  8,  6,  8,  6,  8,  6,  8,  6,  6,  8,  6,  8,},     
  { 8,  6,  8,  6,  6,  8,  6,  8,  6,  8,  6,  8,  8,  6,  8,  6,},     
  { 6,  8,  6,  8,  8,  6,  8,  6,  8,  6,  8,  6,  6,  8,  6,  8,},     
  { 8,  6,  8,  6,  6,  8,  6,  8,  6,  8,  6,  8,  8,  6,  8,  6,},     
  { 6,  8,  6,  8,  8,  6,  8,  6,  8,  6,  8,  6,  6,  8,  6,  8,},     
  { 6,  8,  6,  8,  8,  6,  8,  6,  8,  6,  8,  6,  6,  8,  6,  8,},     
  { 8,  6,  8,  6,  6,  8,  6,  8,  6,  8,  6,  8,  8,  6,  8,  6,},     
  { 6,  8,  6,  8,  8,  6,  8,  6,  8,  6,  8,  6,  6,  8,  6,  8,},     
  { 8,  6,  8,  6,  6,  8,  6,  8,  6,  8,  6,  8,  8,  6,  8,  6,},     
  {10,  4, 10,  4,  4, 10,  4, 10,  4, 10,  4, 10, 10,  4, 10,  4,},     
  { 4, 10,  4, 10, 10,  4, 10,  4, 10,  4, 10,  4,  4, 10,  4, 10,},     
  {10,  4, 10,  4,  4, 10,  4, 10,  4, 10,  4, 10, 10,  4, 10,  4,},     
  { 4, 10,  4, 10, 10,  4, 10,  4, 10,  4, 10,  4,  4, 10,  4, 10,},     
  { 4, 10,  4, 10, 10,  4, 10,  4, 10,  4, 10,  4,  4, 10,  4, 10,},     
  {10,  4, 10,  4,  4, 10,  4, 10,  4, 10,  4, 10, 10,  4, 10,  4,},     
  { 4, 10,  4, 10, 10,  4, 10,  4, 10,  4, 10,  4,  4, 10,  4, 10,},     
  {10,  4, 10,  4,  4, 10,  4, 10,  4, 10,  4, 10, 10,  4, 10,  4,},     
  {12,  2, 12,  2,  2, 12,  2, 12,  2, 12,  2, 12, 12,  2, 12,  2,},     
  { 2, 12,  2, 12, 12,  2, 12,  2, 12,  2, 12,  2,  2, 12,  2, 12,},     
  {12,  2, 12,  2,  2, 12,  2, 12,  2, 12,  2, 12, 12,  2, 12,  2,},     
  { 2, 12,  2, 12, 12,  2, 12,  2, 12,  2, 12,  2,  2, 12,  2, 12,},     
  { 2, 12,  2, 12, 12,  2, 12,  2, 12,  2, 12,  2,  2, 12,  2, 12,},     
  {12,  2, 12,  2,  2, 12,  2, 12,  2, 12,  2, 12, 12,  2, 12,  2,},     
  { 2, 12,  2, 12, 12,  2, 12,  2, 12,  2, 12,  2,  2, 12,  2, 12,},     
  {12,  2, 12,  2,  2, 12,  2, 12,  2, 12,  2, 12, 12,  2, 12,  2,},     
  {14,  0, 14,  0,  0, 14,  0, 14,  0, 14,  0, 14, 14,  0, 14,  0,},     
  { 0, 14,  0, 14, 14,  0, 14,  0, 14,  0, 14,  0,  0, 14,  0, 14,},     
  {14,  0, 14,  0,  0, 14,  0, 14,  0, 14,  0, 14, 14,  0, 14,  0,},     
  { 0, 14,  0, 14, 14,  0, 14,  0, 14,  0, 14,  0,  0, 14,  0, 14,},     
  { 0, 14,  0, 14, 14,  0, 14,  0, 14,  0, 14,  0,  0, 14,  0, 14,},     
  {14,  0, 14,  0,  0, 14,  0, 14,  0, 14,  0, 14, 14,  0, 14,  0,},     
  { 0, 14,  0, 14, 14,  0, 14,  0, 14,  0, 14,  0,  0, 14,  0, 14,},     
  {14,  0, 14,  0,  0, 14,  0, 14,  0, 14,  0, 14, 14,  0, 14,  0,}, 
};

vub::data_type VIT_MB[8*SOFT_RANGE] = {
  0, 14, 14,  0, 14,  0,  0, 14, 14,  0,  0, 14,  0, 14, 14,  0,     
  14,  0,  0, 14,  0, 14, 14,  0,  0, 14, 14,  0, 14,  0,  0, 14,     
  0, 14, 14,  0, 14,  0,  0, 14, 14,  0,  0, 14,  0, 14, 14,  0,     
  14,  0,  0, 14,  0, 14, 14,  0,  0, 14, 14,  0, 14,  0,  0, 14,     
  0, 14, 14,  0, 14,  0,  0, 14, 14,  0,  0, 14,  0, 14, 14,  0,     
  14,  0,  0, 14,  0, 14, 14,  0,  0, 14, 14,  0, 14,  0,  0, 14,     
  0, 14, 14,  0, 14,  0,  0, 14, 14,  0,  0, 14,  0, 14, 14,  0,     
  14,  0,  0, 14,  0, 14, 14,  0,  0, 14, 14,  0, 14,  0,  0, 14,     
  2, 12, 12,  2, 12,  2,  2, 12, 12,  2,  2, 12,  2, 12, 12,  2,     
  12,  2,  2, 12,  2, 12, 12,  2,  2, 12, 12,  2, 12,  2,  2, 12,     
  2, 12, 12,  2, 12,  2,  2, 12, 12,  2,  2, 12,  2, 12, 12,  2,     
  12,  2,  2, 12,  2, 12, 12,  2,  2, 12, 12,  2, 12,  2,  2, 12,     
  2, 12, 12,  2, 12,  2,  2, 12, 12,  2,  2, 12,  2, 12, 12,  2,     
  12,  2,  2, 12,  2, 12, 12,  2,  2, 12, 12,  2, 12,  2,  2, 12,     
  2, 12, 12,  2, 12,  2,  2, 12, 12,  2,  2, 12,  2, 12, 12,  2,     
  12,  2,  2, 12,  2, 12, 12,  2,  2, 12, 12,  2, 12,  2,  2, 12,     
  4, 10, 10,  4, 10,  4,  4, 10, 10,  4,  4, 10,  4, 10, 10,  4,     
  10,  4,  4, 10,  4, 10, 10,  4,  4, 10, 10,  4, 10,  4,  4, 10,     
  4, 10, 10,  4, 10,  4,  4, 10, 10,  4,  4, 10,  4, 10, 10,  4,     
  10,  4,  4, 10,  4, 10, 10,  4,  4, 10, 10,  4, 10,  4,  4, 10,     
  4, 10, 10,  4, 10,  4,  4, 10, 10,  4,  4, 10,  4, 10, 10,  4,     
  10,  4,  4, 10,  4, 10, 10,  4,  4, 10, 10,  4, 10,  4,  4, 10,     
  4, 10, 10,  4, 10,  4,  4, 10, 10,  4,  4, 10,  4, 10, 10,  4,     
  10,  4,  4, 10,  4, 10, 10,  4,  4, 10, 10,  4, 10,  4,  4, 10,     
  6,  8,  8,  6,  8,  6,  6,  8,  8,  6,  6,  8,  6,  8,  8,  6,     
  8,  6,  6,  8,  6,  8,  8,  6,  6,  8,  8,  6,  8,  6,  6,  8,     
  6,  8,  8,  6,  8,  6,  6,  8,  8,  6,  6,  8,  6,  8,  8,  6,     
  8,  6,  6,  8,  6,  8,  8,  6,  6,  8,  8,  6,  8,  6,  6,  8,     
  6,  8,  8,  6,  8,  6,  6,  8,  8,  6,  6,  8,  6,  8,  8,  6,     
  8,  6,  6,  8,  6,  8,  8,  6,  6,  8,  8,  6,  8,  6,  6,  8,     
  6,  8,  8,  6,  8,  6,  6,  8,  8,  6,  6,  8,  6,  8,  8,  6,     
  8,  6,  6,  8,  6,  8,  8,  6,  6,  8,  8,  6,  8,  6,  6,  8,     
  8,  6,  6,  8,  6,  8,  8,  6,  6,  8,  8,  6,  8,  6,  6,  8,     
  6,  8,  8,  6,  8,  6,  6,  8,  8,  6,  6,  8,  6,  8,  8,  6,     
  8,  6,  6,  8,  6,  8,  8,  6,  6,  8,  8,  6,  8,  6,  6,  8,     
  6,  8,  8,  6,  8,  6,  6,  8,  8,  6,  6,  8,  6,  8,  8,  6,     
  8,  6,  6,  8,  6,  8,  8,  6,  6,  8,  8,  6,  8,  6,  6,  8,     
  6,  8,  8,  6,  8,  6,  6,  8,  8,  6,  6,  8,  6,  8,  8,  6,     
  8,  6,  6,  8,  6,  8,  8,  6,  6,  8,  8,  6,  8,  6,  6,  8,     
  6,  8,  8,  6,  8,  6,  6,  8,  8,  6,  6,  8,  6,  8,  8,  6,     
  10,  4,  4, 10,  4, 10, 10,  4,  4, 10, 10,  4, 10,  4,  4, 10,     
  4, 10, 10,  4, 10,  4,  4, 10, 10,  4,  4, 10,  4, 10, 10,  4,     
  10,  4,  4, 10,  4, 10, 10,  4,  4, 10, 10,  4, 10,  4,  4, 10,     
  4, 10, 10,  4, 10,  4,  4, 10, 10,  4,  4, 10,  4, 10, 10,  4,     
  10,  4,  4, 10,  4, 10, 10,  4,  4, 10, 10,  4, 10,  4,  4, 10,     
  4, 10, 10,  4, 10,  4,  4, 10, 10,  4,  4, 10,  4, 10, 10,  4,     
  10,  4,  4, 10,  4, 10, 10,  4,  4, 10, 10,  4, 10,  4,  4, 10,     
  4, 10, 10,  4, 10,  4,  4, 10, 10,  4,  4, 10,  4, 10, 10,  4,     
  12,  2,  2, 12,  2, 12, 12,  2,  2, 12, 12,  2, 12,  2,  2, 12,     
  2, 12, 12,  2, 12,  2,  2, 12, 12,  2,  2, 12,  2, 12, 12,  2,     
  12,  2,  2, 12,  2, 12, 12,  2,  2, 12, 12,  2, 12,  2,  2, 12,     
  2, 12, 12,  2, 12,  2,  2, 12, 12,  2,  2, 12,  2, 12, 12,  2,     
  12,  2,  2, 12,  2, 12, 12,  2,  2, 12, 12,  2, 12,  2,  2, 12,     
  2, 12, 12,  2, 12,  2,  2, 12, 12,  2,  2, 12,  2, 12, 12,  2,     
  12,  2,  2, 12,  2, 12, 12,  2,  2, 12, 12,  2, 12,  2,  2, 12,     
  2, 12, 12,  2, 12,  2,  2, 12, 12,  2,  2, 12,  2, 12, 12,  2,     
  14,  0,  0, 14,  0, 14, 14,  0,  0, 14, 14,  0, 14,  0,  0, 14,     
  0, 14, 14,  0, 14,  0,  0, 14, 14,  0,  0, 14,  0, 14, 14,  0,     
  14,  0,  0, 14,  0, 14, 14,  0,  0, 14, 14,  0, 14,  0,  0, 14,     
  0, 14, 14,  0, 14,  0,  0, 14, 14,  0,  0, 14,  0, 14, 14,  0,     
  14,  0,  0, 14,  0, 14, 14,  0,  0, 14, 14,  0, 14,  0,  0, 14,     
  0, 14, 14,  0, 14,  0,  0, 14, 14,  0,  0, 14,  0, 14, 14,  0,     
  14,  0,  0, 14,  0, 14, 14,  0,  0, 14, 14,  0, 14,  0,  0, 14,     
  0, 14, 14,  0, 14,  0,  0, 14, 14,  0,  0, 14,  0, 14, 14,  0, 
};