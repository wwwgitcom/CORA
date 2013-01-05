#pragma once

// viterbi decoder 1/2
DEFINE_BLOCK(b_parallel_viterbi64_1o2_1v1, 1, 1)
{
  size_t                   nTraceBackLength;
  size_t                   nTraceBackOutput;

  size_t                   nTracebackDataCount;
  size_t                   nTracebackOffset;
  size_t                   nTraceBackOutputByte;
  size_t                   nTracebackSoftbits;

  size_t i_trellis;    // index of trellis
  vub *pTrellisBase;
  vub *pTrellis;
  vub vNormMask;



  //////////////////////////////////////////////////////////////////////////
  BLOCK_INIT
  {
    auto v = $["TraceBackLength"];
    if (!v.empty())
    {
      nTraceBackLength = atoi(v.c_str());
    }
    else
    {
      nTraceBackLength = 36;
    }

    v = $["TraceBackOutput"];
    if (!v.empty())
    {
      nTraceBackOutput = atoi(v.c_str());
    }
    else
    {
      nTraceBackOutput = 48;
    }

    nTracebackDataCount  = nTraceBackLength + nTraceBackOutput + nTraceBackLength; // D + L + D, D=5K
    nTracebackOffset     = nTraceBackLength + nTraceBackOutput - 1;
    nTraceBackOutputByte = nTraceBackOutput / 8;

    nTracebackSoftbits   = (nTraceBackLength + nTraceBackOutput + nTraceBackLength) << 1; // 1/2 coding

    pTrellisBase = (vub*)_aligned_malloc(1024 * 16 * sizeof(vub), 64);
    pTrellis = pTrellisBase;

    // Initialize Trellis
    pTrellis[0] = vub(ALL_INIT0);
    pTrellis[1] = vub(ALL_INIT);
    pTrellis[2] = vub(ALL_INIT);
    pTrellis[3] = vub(ALL_INIT);

    i_trellis = 0;
    for (size_t i = 0; i < 16; i++)
    {
      vNormMask[i] = 64;
    }
  }


  BLOCK_RESET
  {
    auto n = ninput(0);
    consume(0, n);

    pTrellis = pTrellisBase;
    i_trellis = 0;
  }
  //////////////////////////////////////////////////////////////////////////
#define VITTRACE 0

  BLOCK_WORK
  {
    trace();

    size_t nInputSoftBits = ninput(0);
    if (nInputSoftBits < nTracebackSoftbits) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<uint8>(0);

    // for trace back  
    vub * pTraceBk;       // trace back pointer in trellis
    size_t i_minpos = 0;     // the minimal path position
    size_t i_tpos   = 0;
    
    const vub ALLINVONE (ALL_INVERSE_ONE);
    // temporal variables
    vub rub0, rub1, rub2, rub3;
    vus rus0, rus1, rus2, rus3;
    vus rus4, rus5, rus6, rus7;

    uint8 * pVTOutput;
    uint8 outchar = 0;    // the output(decoded) char

    pTrellis = pTrellisBase;

    for (size_t nSoftBits = 0; nSoftBits < nTracebackSoftbits; nSoftBits += 2)
    {
      ViterbiAdvance(pTrellis, (vub*)VIT_MA, ip[nSoftBits], (vub*)VIT_MB, ip[nSoftBits + 1]);
      //i_trellis += 1;
      
      if (pTrellis[0][0] > 180)
      {
#if 0
        uint8* pcc = (unsigned char*)pTrellis;
        printf("-->\n");
        for (int i = 0; i < 64; i++)
        {
          printf("%u ", pcc[i]);
        }
        printf("<--\n\n");
#endif

        // normalization
        // find the smallest component and extract it from all states
        rub0 = smin (pTrellis[0], pTrellis[1] );
        rub1 = smin (pTrellis[2], pTrellis[3] );
        rub2 = smin (rub0, rub1);
        rub3 = hmin (rub2);

        // make sure to clear the marker bit
        rub3 = and  (rub3, ALLINVONE );

        // normalize
        pTrellis[0] = sub ( pTrellis[0], rub3);
        pTrellis[1] = sub ( pTrellis[1], rub3);
        pTrellis[2] = sub ( pTrellis[2], rub3);
        pTrellis[3] = sub ( pTrellis[3], rub3);
      }      
    }

    // Traceback 
    //if ( i_trellis == nTracebackDataCount )
    {
      rub0 = vub(INDEXES[0]);
      rub1 = pTrellis[0];

      rus2 = (vus)interleave_low  ( rub0, rub1 );
      rus3 = (vus)interleave_high ( rub0, rub1 );
      rus4 = smin ( rus2, rus3);

      rub0 = vub(INDEXES[1]);
      rub1 = pTrellis[1];
      rus2 = (vus)interleave_low  ( rub0, rub1 );
      rus3 = (vus)interleave_high ( rub0, rub1 );
      rus5 = smin (rus2, rus3);

      rus4 = smin (rus4, rus5);

      rub0 = vub(INDEXES[2]);
      rub1 = pTrellis[2];
      rus2 = (vus)interleave_low  ( rub0, rub1 );
      rus3 = (vus)interleave_high ( rub0, rub1 );
      rus6 = smin (rus2, rus3);

      rus4 = smin (rus4, rus6);

      rub0 = vub(INDEXES[3]);
      rub1 = pTrellis[3];
      rus2 = (vus)interleave_low  ( rub0, rub1 );
      rus3 = (vus)interleave_high ( rub0, rub1 );
      rus7 = smin (rus2, rus3);

      rus4 = smin (rus4, rus7);

      // now rus4 contains the minimal 8 
      rus0 = hmin (rus4);

      // now the first word contains the index and value
      // index: bit [7:2]; 
      // value: bit [15:8]
      i_minpos = extract<0>(rus0); 

      // now we can trace back ...
      pTraceBk = pTrellis;

      // first part - trace back without output
      i_minpos = (i_minpos >> 2) & 0x3F; // index 6:0
      size_t i, j;
      for ( i = 0; i < nTraceBackLength; i++)
      {
        pTraceBk -= 4;
        i_minpos  = (i_minpos >> 1) & 0x3F;
        i_tpos    = ((char*) pTraceBk)[i_minpos] ;
        i_minpos |= (i_tpos & 1) << 6;  // now i_minpos 6:0 is the new index
      }

      // second part - trace back with output
      op += nTraceBackOutputByte;
      pVTOutput    = op;

      for ( i = 0; i < nTraceBackOutputByte; i++)
      {
        for ( j = 0; j < 8; j++ )
        {
          outchar = outchar << 1;
          outchar |= (i_minpos >> 6) & 1;

          // next bit
          pTraceBk -= 4;
          i_minpos = (i_minpos >> 1) & 0x3F;
          i_tpos = ((char*) pTraceBk)[i_minpos] ;
          i_minpos |= (i_tpos & 1) << 6;  // now i_minpos 6:0 is the new index
        }

        pVTOutput --;
        *pVTOutput = outchar;

        outchar = 0;
      }

      produce(0, nTraceBackOutputByte);
      consume(0, nTracebackSoftbits);

      
      //i_trellis = 0;

      //printf("vit worker %p: in: %d, out: %d\n", this, nTracebackSoftbits, nTraceBackOutputByte);

      return true;// fix it... cannot return here, some bits maybe left continue...
    }

    //printf("vit worker %p: in: %d\n", this, nInputSoftBits);    
  }
};

