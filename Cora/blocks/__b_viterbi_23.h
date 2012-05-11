#pragma once

// viterbi decoder 2/3
DEFINE_BLOCK(b_viterbi64_2o3_1v1, 1, 1)
{
  __int32                   nTraceBackLength;
  __int32                   nTraceBackOutput;

  __int32                   nTracebackDataCount;
  __int32                   nTracebackOffset;
  __int32                   nTraceBackOutputByte;

  int i_trellis;    // index of trellis
  int nDecodedBits;

  vub *pTrellisBase;
  vub *pTrellis;  
  vub vNormMask;
  
  _global_(int, VitTotalBits);

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
    nTracebackDataCount  = nTraceBackLength + nTraceBackOutput;
    nTracebackOffset     = nTraceBackLength + nTraceBackOutput - 1;
    nTraceBackOutputByte = nTraceBackOutput / 8;

    pTrellisBase = (vub*)_aligned_malloc(15000 * 4 * sizeof(vub), 64);
    pTrellis = pTrellisBase;

    // Initialize Trellis
    pTrellis[0] = vub(ALL_INIT0);
    pTrellis[1] = vub(ALL_INIT);
    pTrellis[2] = vub(ALL_INIT);
    pTrellis[3] = vub(ALL_INIT);
    nDecodedBits = 0;
    i_trellis = 0;
    for (int i = 0; i < 16; i++)
    {
      vNormMask[i] = 128;
    }
  }


  BLOCK_RESET
  {
    pTrellis = pTrellisBase;
    i_trellis = 0;
    nDecodedBits = 0;
  }
  //////////////////////////////////////////////////////////////////////////
#define VITTRACE 0

  // A0 A1 A2 A3
  // B0 *  B2 * 
  // A0 B0 A1 A2 B2 A3
  BLOCK_WORK
  {
    trace();

    auto nInputSoftBits = ninput(0);
    if (nInputSoftBits < 3) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<uint8>(0);
    
    // for trace back  
    vub * pTraceBk;       // trace back pointer in trellis
    int i_minpos = 0;     // the minimal path position
    int i_tpos   = 0;
    int nVitTotalBits = *VitTotalBits;

    // temporal variables
    vub rub0, rub1, rub2, rub3;
    vus rus0, rus1, rus2, rus3;
    vus rus4, rus5, rus6, rus7;
 
    unsigned char * pVTOutput;
    unsigned char outchar = 0;    // the output(decoded) char
    bool bFlush = false;

    //printf("vit in: %d\n", nInputSoftBits);
    
    __int32 nSoftBits;
    for (nSoftBits = 0; nSoftBits < nInputSoftBits; nSoftBits += 3)
    {
      ViterbiAdvance(pTrellis, (vub*)VIT_MA, ip[nSoftBits], (vub*)VIT_MB, ip[nSoftBits + 1]);
      ViterbiAdvance(pTrellis, (vub*)VIT_MA, ip[nSoftBits + 2]);
      i_trellis += 2;

      if (pTrellis[0][0] > 192)
      {
        pTrellis[0] = sub ( pTrellis[0], vNormMask);
        pTrellis[1] = sub ( pTrellis[1], vNormMask);
        pTrellis[2] = sub ( pTrellis[2], vNormMask);
        pTrellis[3] = sub ( pTrellis[3], vNormMask);
      }

      // Traceback 
      // We should first skip TB_DEPTH_VITAS bits and 
      // TB_OUTPUT_VITAS is actual bits we can output
      if ( i_trellis >= nTracebackDataCount + TB_PREFIX_VITAS )
      {
        // track back
        // we need to find the minimal state and index of the state

        //printf("traceback...@%d\n", i_trellis);
        // rub3 has the minimal value, we need to find the index
        // the algorithm to find the right index is to embed the index at the least
        // significant bits of state value, then we just find the minimal value

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
        int i, j;
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
        
        nDecodedBits += nTraceBackOutput;
        
        //for (i = 0; i < nTraceBackOutputByte; i++)
        //{
        //  printf("%02X ", pVTOutput[i]);
        //}
        //printf("\n");

        i_trellis -= nTraceBackOutput;//?????????
        //printf("nTotalBits=%d\nSoftBits", nTotalBits);
        //printf("nDecodedBits=%d, nTotalBits=%d, i_trellis=%d, trellisoffset=%d\n",
        //  nDecodedBits, nVitTotalBits, i_trellis, pTrellis - pTrellisBase);
        //if (nDecodedBits == 4096)
        //{
        //  printf("***");
        //}

        produce(0, nTraceBackOutputByte);



        //printf("in2: %d, total=%d, this left=%d\n", m_IncomeSoftBits, nTotalSoftBits, nInputSoftBits - nSoftBits - 8);

        if (nVitTotalBits - nDecodedBits - i_trellis <= nTraceBackOutput)
        {
          bFlush = true;
          if (nInputSoftBits - nSoftBits - 3 > 0)
          {
            continue;
          }
        }

        consume(0, nSoftBits + 3);
        return true;
      }
    }

    consume(0, nSoftBits);

    if (bFlush)
    {
      while ( nDecodedBits < nVitTotalBits)
      {
        int npadding = nTracebackDataCount - i_trellis + TB_PREFIX_VITAS;
        unsigned char opad = 0;
        //npadding >>= 1;

        for (int i = 0; i < npadding; i++)
        {
          ViterbiAdvance(pTrellis, (vub*)VIT_MA, opad, (vub*)VIT_MB, opad);
          //ViterbiAdvance(pTrellis, (vub*)VIT_MA, opad);
          //i_trellis += 2;
          i_trellis++;

          if (pTrellis[0][0] > 192)
          {
            pTrellis[0] = sub ( pTrellis[0], vNormMask);
            pTrellis[1] = sub ( pTrellis[1], vNormMask);
            pTrellis[2] = sub ( pTrellis[2], vNormMask);
            pTrellis[3] = sub ( pTrellis[3], vNormMask);
          }
        }

        
        if ( i_trellis >= nTracebackDataCount + TB_PREFIX_VITAS )
        {
          // track back
          // we need to find the minimal state and index of the state

          //printf("traceback...@%d\n", i_trellis);
          // rub3 has the minimal value, we need to find the index
          // the algorithm to find the right index is to embed the index at the least
          // significant bits of state value, then we just find the minimal value

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
          int i, j;
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

          nDecodedBits += nTraceBackOutput;

          i_trellis -= nTraceBackOutput;
          //printf("nTotalBits=%d\nSoftBits", nTotalBits);

          produce(0, nTraceBackOutputByte);
        }
      }
      reset();
    }
    return bFlush;
  }
};

