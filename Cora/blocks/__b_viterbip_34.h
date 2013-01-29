#pragma once
// viterbi decoder 3/4
DEFINE_BLOCK(b_parallel_viterbi64_3o4_1v1, 1, 1)
{
  __int32                   nTraceBackLength;
  __int32                   nTraceBackOutput;

  __int32                   nTracebackDataCount;
  __int32                   nTracebackOffset;
  __int32                   nTraceBackOutputByte;
  size_t                    nTracebackSoftbits;

  int i_trellis;    // index of trellis
  int nDecodedBits;

  vub *pTrellisBase;
  vub *pTrellis;
  vub vNormMask;

  tick_count tDecodeStamp[1024];
  int        iDecodeCnt;
  int        iDecodeCnt2;

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
      nTraceBackLength = 72;
    }

    v = $["TraceBackOutput"];
    if (!v.empty())
    {
      nTraceBackOutput = atoi(v.c_str());
    }
    else
    {
      nTraceBackOutput = 192;
    }
    nTracebackDataCount  = nTraceBackLength + nTraceBackOutput + nTraceBackLength;
    nTracebackOffset     = nTracebackDataCount - 1;
    nTraceBackOutputByte = nTraceBackOutput / 8;

    nTracebackSoftbits   = nTracebackDataCount * 4 / 3; // 3/4 coding

    pTrellisBase = (vub*)_aligned_malloc(15000 * 4 * sizeof(vub), 64);
    pTrellis = pTrellisBase;

    // Initialize Trellis
    pTrellis[0] = vub(ALL_INIT0);
    pTrellis[1] = vub(ALL_INIT);
    pTrellis[2] = vub(ALL_INIT);
    pTrellis[3] = vub(ALL_INIT);

    i_trellis = 0;
    for (int i = 0; i < 16; i++)
    {
      vNormMask[i] = 64;
    }
    iDecodeCnt = 0;
    iDecodeCnt2 = 0;
  }


  BLOCK_RESET
  {
    pTrellis     = pTrellisBase;
    i_trellis    = 0;
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
    if (nInputSoftBits < 8) return false;

    nInputSoftBits -= (nInputSoftBits & 0x3);

    auto ip = _$<uint8>(0);
    auto op = $_<uint8>(0);

    // for trace back  
    vub * pTraceBk;       // trace back pointer in trellis
    int i_minpos = 0;     // the minimal path position
    int i_tpos   = 0;

    const vub ALLINVONE (ALL_INVERSE_ONE);
    // temporal variables
    vub rub0, rub1, rub2, rub3;
    vus rus0, rus1, rus2, rus3;
    vus rus4, rus5, rus6, rus7;

    unsigned char * pVTOutput;
    unsigned char outchar = 0;    // the output(decoded) char

    bool bRet = false;
    size_t nSoftBits = 0;
    while ( nSoftBits < nInputSoftBits )
    {
      ViterbiAdvance(pTrellis, (vub*)VIT_MA, ip[nSoftBits], (vub*)VIT_MB, ip[nSoftBits + 1]);
      ViterbiAdvance(pTrellis, (vub*)VIT_MA, ip[nSoftBits + 2]);
      ViterbiAdvance(pTrellis, (vub*)VIT_MB, ip[nSoftBits + 3]);

      i_trellis += 3;
      nSoftBits += 4;

      if (pTrellis[0][0] > 190)
      {
#if 0
        pTrellis[0] = sub ( pTrellis[0], vNormMask);
        pTrellis[1] = sub ( pTrellis[1], vNormMask);
        pTrellis[2] = sub ( pTrellis[2], vNormMask);
        pTrellis[3] = sub ( pTrellis[3], vNormMask);
#else
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
#endif
      }

      // Traceback 
      if ( i_trellis == nTracebackDataCount)
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


#if 1
        tDecodeStamp[iDecodeCnt] = tick_count::now();
        iDecodeCnt++;
        iDecodeCnt &= (1024 - 1);

        if (iDecodeCnt == 1024)
        {
          iDecodeCnt = 0;
        }

        iDecodeCnt2++;
        if (iDecodeCnt2 == 100000)
        {
          int i = 16;
          //for (int i = 1; i < 1024; i++)
          {
            fprintf(stderr, "vit time = %f us\n", (tDecodeStamp[i] - tDecodeStamp[i - 1]).us());
          }
          iDecodeCnt2 = 0;
        }
#endif



        while (noutput(0) < nTraceBackOutputByte)
        {
          //printf("vit out buf full %p...\n", this);
          //printf(" avail=%d, need=%d\n", noutput(0), nTraceBackOutputByte);
          _mm_pause();
        }

        produce(0, nTraceBackOutputByte);

        pTrellis = pTrellisBase;
        i_trellis = 0;

        bRet = true;
      }
    }

    consume(0, nSoftBits);
    return bRet;
  }
};