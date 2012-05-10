#pragma once
#include "_vector128.h"

// We use 3 bit SoftBit
#define SOFT_RANGE	    8

// The path metric range
#define METRIC_SIZE     128
#define METRIC_OFFSET   7

#define NOR_MASK_VITAS  0x7
#define BYTE_MAX_VITAS  6
#define BIT_MAX_VITAS   (BYTE_MAX_VITAS * 8)

// 6 leading bit
#define TB_PREFIX_VITAS  6          // must be 6. FJ: I guess this is by design trick. The real data start from the 7th
#define TB_DEPTH_VITAS   12         // must be multiple of 1
#define TB_OUTPUT_VITAS  (24)       // must be multiple of 8 and factor of 192
#define A16 __declspec(align(16))

#define SPACE_SIZE 64
#define INPUT_MAX_VITAS 96
#define BITS_PER_BYTE 8


extern vub::data_type ALL_INVERSE_ONE;
extern vub::data_type ALL_ONE;
extern vub::data_type ALL_M128;
extern vub::data_type VIT_MA[8 * SOFT_RANGE];
extern vub::data_type VIT_MB[8 * SOFT_RANGE];

extern A16 vub::data_type ALL_INIT;
extern A16 vub::data_type ALL_INIT0;
extern A16 vub::data_type INDEXES [4];

#if 0
inline void v_print(vub &v)
{
  for (int i = 0; i < 16; i++)
  {
    fprintf(stdout, "%u ", v[i]);
  }
  fprintf(stdout, "\n");
}
#else
inline void v_print(vub &v){}
#endif


__forceinline void ViterbiAdvance(vub *&pTrellis, vub pVITMA[], int i_ma, vub pVITMB[], int i_mb)
{
  const vub ALLONE    (ALL_ONE);
  const vub ALLINVONE (ALL_INVERSE_ONE);
  const vub ALLM128   (ALL_M128);

  // Index to the Branch Metric LUT table
  i_ma <<= 3;
  i_mb <<= 3;

  // temporal variables
  vub rub0, rub1, rub2, rub3;

  //for (int i = 0; i < 4; i++)
  //    v_print(pTrellis[i]);
  //printf("\n");

  // Compute the new states
  rub0 = interleave_low (pTrellis[0], pTrellis[0]);
  rub1 = interleave_low (pTrellis[2], pTrellis[2]);

  // branch 0
  rub0 = add ( rub0, pVITMA[i_ma] );
  rub0 = add ( rub0, pVITMB[i_mb] );
  rub0 = and ( rub0, ALLINVONE); // mark the path

  // branch 1
  rub1 = add ( rub1, pVITMA[i_ma+1] );
  rub1 = add ( rub1, pVITMB[i_mb+1] ); 
  rub1 = or  ( rub1, ALLONE );

  // store the shortest path, state:[0-15]
  pTrellis[4] = smin (rub0, rub1); 
  v_print(shift_right(pTrellis[4], 1));

  rub0 = interleave_high (pTrellis[0], pTrellis[0]);
  rub1 = interleave_high (pTrellis[2], pTrellis[2]);

  // branch 0
  rub0 = add ( rub0, pVITMA[i_ma+2] );
  rub0 = add ( rub0, pVITMB[i_mb+2] );  
  rub0 = and ( rub0, ALLINVONE); // mark the path

  // branch 1
  rub1 = add ( rub1, pVITMA[i_ma+3] );
  rub1 = add ( rub1, pVITMB[i_mb+3] ); 
  rub1 = or  ( rub1, ALLONE );

  // store the shortest path, state:[16-31]    
  pTrellis[5] = smin (rub0, rub1); 
  v_print(shift_right(pTrellis[5], 1));

  rub0 = interleave_low (pTrellis[1], pTrellis[1]);
  rub1 = interleave_low (pTrellis[3], pTrellis[3]);

  // branch 0
  rub0 = add ( rub0, pVITMA[i_ma+4] );
  rub0 = add ( rub0, pVITMB[i_mb+4] );
  rub0 = and ( rub0, ALLINVONE); // mark the path

  // branch 1
  rub1 = add ( rub1, pVITMA[i_ma+5] );
  rub1 = add ( rub1, pVITMB[i_mb+5] );
  rub1 = or  ( rub1, ALLONE );

  // store the shortest path, state:[32-47]    
  pTrellis[6] = smin (rub0, rub1);
  v_print(shift_right(pTrellis[6], 1));

  rub0 = interleave_high (pTrellis[1], pTrellis[1]);
  rub1 = interleave_high (pTrellis[3], pTrellis[3]);

  // branch 0
  rub0 = add ( rub0, pVITMA[i_ma+6] );
  rub0 = add ( rub0, pVITMB[i_mb+6] );
  rub0 = and ( rub0, ALLINVONE); // mark the path

  // branch 1
  rub1 = add ( rub1, pVITMA[i_ma+7] );
  rub1 = add ( rub1, pVITMB[i_mb+7] );
  rub1 = or  ( rub1, ALLONE );

  // store the shortest path, state:[48-63]        
  pTrellis[7] = smin (rub0, rub1); 
  v_print(shift_right(pTrellis[7], 1));

  pTrellis += 4;
}

__forceinline void ViterbiAdvance(vub *&pTrellis, vub pVITMA[], int i_ma)
{
  const vub ALLONE    (ALL_ONE);
  const vub ALLINVONE (ALL_INVERSE_ONE);
  const vub ALLM128   (ALL_M128);

  // Index to the Branch Metric LUT table
  i_ma <<= 3;

  //for (int i = 0; i < 4; i++)
  //    v_print(pTrellis[i]);
  //printf("\n");

  // temporal variables
  vub rub0, rub1, rub2, rub3;

  // Compute the new states
  rub0 = interleave_low (pTrellis[0], pTrellis[0]);
  rub1 = interleave_low (pTrellis[2], pTrellis[2]);

  // branch 0
  rub0 = add ( rub0, pVITMA[i_ma] );
  rub0 = and ( rub0, ALLINVONE); // mark the path

  // branch 1
  rub1 = add ( rub1, pVITMA[i_ma+1] );
  rub1 = or  ( rub1, ALLONE );

  // store the shortest path, state:[0-15]
  pTrellis[4] = smin (rub0, rub1); 
  v_print(shift_right(pTrellis[4], 1));

  rub0 = interleave_high (pTrellis[0], pTrellis[0]);
  rub1 = interleave_high (pTrellis[2], pTrellis[2]);

  // branch 0
  rub0 = add ( rub0, pVITMA[i_ma+2] );
  rub0 = and ( rub0, ALLINVONE); // mark the path

  // branch 1
  rub1 = add ( rub1, pVITMA[i_ma+3] );
  rub1 = or  ( rub1, ALLONE );

  // store the shortest path, state:[16-31]    
  pTrellis[5] = smin (rub0, rub1); 
  v_print(shift_right(pTrellis[5], 1));

  rub0 = interleave_low (pTrellis[1], pTrellis[1]);
  rub1 = interleave_low (pTrellis[3], pTrellis[3]);

  // branch 0
  rub0 = add ( rub0, pVITMA[i_ma+4] );
  rub0 = and ( rub0, ALLINVONE); // mark the path

  // branch 1
  rub1 = add ( rub1, pVITMA[i_ma+5] );
  rub1 = or  ( rub1, ALLONE );

  // store the shortest path, state:[32-47]    
  pTrellis[6] = smin (rub0, rub1); 
  v_print(shift_right(pTrellis[6], 1));

  rub0 = interleave_high (pTrellis[1], pTrellis[1]);
  rub1 = interleave_high (pTrellis[3], pTrellis[3]);

  // branch 0
  rub0 = add ( rub0, pVITMA[i_ma+6] );
  rub0 = and ( rub0, ALLINVONE); // mark the path

  // branch 1
  rub1 = add ( rub1, pVITMA[i_ma+7] );
  rub1 = or  ( rub1, ALLONE );

  // store the shortest path, state:[48-63] 
  pTrellis[7] = smin (rub0, rub1);
  v_print(shift_right(pTrellis[7], 1));

  pTrellis += 4;
}

