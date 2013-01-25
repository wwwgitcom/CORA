#pragma once

template<int nTraceBackLength = 36, int nTraceBackOutput = 48>
struct dsp_viterbi_64
{
  static_assert(nTraceBackOutput % 8 == 0, "Trace back output must a factor of 8!");

  static const int nTracebackDataCount  = nTraceBackLength + nTraceBackOutput;

  static_assert(nTracebackDataCount % 2 == 0, "(nTraceBackLength + nTraceBackOutput) % 2 != 0");

  static const int nTracebackOffset     = nTraceBackLength + nTraceBackOutput - 1;
  static const int nTraceBackOutputByte = nTraceBackOutput / 8;

  // ACS
  v_align(64) v_ub m_vBM[64][4]; // 64 states, each state has two 32 BM
  v_align(64) v_ub m_vBM0[8][4]; // 64 states, each state has two 32 BM
  v_align(64) v_ub m_vBM1[8][4]; // 64 states, each state has two 32 BM

  // shared
  v_align(64) v_ub m_vShuffleMask;
  v_ub m_vNormMask;
  unsigned __int8 *m_pSoftBits;
  unsigned __int8 *m_pDecodedBytes;
  __int32          m_nDecodedBytes;

  // shared
#define RQ_MASK (1024 - 1)
  typedef v_ub TBState[4];
  typedef unsigned __int16 SurviorPath[4];
  
  v_align(64) SurviorPath m_TBQ[1024];
  v_align(64) TBState     m_MinAddress[1024];

  // TB
  v_align(64) v_ub        m_vStateIndex[4];

  //////////////////////////////////////////////////////////////////////////

  dsp_viterbi_64()
  {
    unsigned char v = 0;
    int i;

    v = 0;
    for (i = 0; i < 8; i++)
    {
      m_vShuffleMask[i] = v;
      v += 2;
    }
    v = 1;
    for (; i < 16; i++)
    {
      m_vShuffleMask[i] = v;
      v += 2;
    }

    v = 0;
    for (i = 0; i < 64; i++)
    {
      m_vStateIndex[0][i] = v++;
    }

    m_vNormMask.v_setall(128);


    unsigned __int8 bAddress;
    unsigned __int8 m00, m01, m10, m11;
    unsigned __int8 m0, m1;

    v_ub v14;
    v14.v_setall(14);

    v_ub v7;
    v7.v_setall(7);

    for (unsigned __int8 b0 = 0; b0 < 8; b0++)
    {
      for (unsigned __int8 b1 = 0; b1 < 8; b1++)
      {
        bAddress = ( (b0 & 0x7) | ((b1 & 0x7) << 3) );

        //printf("b0= %d, b1 = %d, Address = %d \nSoftBits", b0, b1, bAddress);

        m00 = b1 + b0;
        m01 = b1 + 7 - b0;
        m10 = 7 - b1 + b0;
        m11 = 7 - b1 + 7 - b0;

        //printf("m00 = %d, m01 = %d, m10 = %d, m11 = %d\nSoftBits", m00, m01, m10, m11);

        m_vBM[bAddress][0].v_set(m00, m01, m00, m01, m11, m10, m11, m10, m11, m10, m11, m10, m00, m01, m00, m01);
        m_vBM[bAddress][1] = v_sub(v14, m_vBM[bAddress][0]);
        m_vBM[bAddress][2].v_set(m10, m11, m10, m11, m01, m00, m01, m00, m01, m00, m01, m00, m10, m11, m10, m11);
        m_vBM[bAddress][3] = v_sub(v14, m_vBM[bAddress][2]);
      }
    }

    for (unsigned __int8 b0 = 0; b0 < 8; b0++)
    {
      bAddress = (b0 & 0x7);

      //printf("b0= %d, b1 = %d, Address = %d \nSoftBits", b0, b1, bAddress);

      m0 = b0;
      m1 = 7 - b0;

      //printf("m00 = %d, m01 = %d, m10 = %d, m11 = %d\nSoftBits", m00, m01, m10, m11);

      m_vBM0[bAddress][0].v_set(m0, m1, m0, m1, m1, m0, m1, m0, m1, m0, m1, m0, m0, m1, m0, m1);
      m_vBM0[bAddress][1] = v_sub(v7, m_vBM0[bAddress][0]);
      m_vBM0[bAddress][2].v_set(m0, m1, m0, m1, m1, m0, m1, m0, m1, m0, m1, m0, m0, m1, m0, m1);
      m_vBM0[bAddress][3] = v_sub(v7, m_vBM0[bAddress][2]);
    }

    for (unsigned __int8 b1 = 0; b1 < 8; b1++)
    {
      bAddress = (b1 & 0x7);

      //printf("b0= %d, b1 = %d, Address = %d \nSoftBits", b0, b1, bAddress);

      m0 = b1;
      m1 = 7 - b1;

      //printf("m00 = %d, m01 = %d, m10 = %d, m11 = %d\nSoftBits", m00, m01, m10, m11);

      m_vBM1[bAddress][0].v_set(m0, m0, m0, m0, m1, m1, m1, m1, m1, m1, m1, m1, m0, m0, m0, m0);
      m_vBM1[bAddress][1] = v_sub(v7, m_vBM1[bAddress][0]);
      m_vBM1[bAddress][2].v_set(m1, m1, m1, m1, m0, m0, m0, m0, m0, m0, m0, m0, m1, m1, m1, m1);
      m_vBM1[bAddress][3] = v_sub(v7, m_vBM1[bAddress][2]);
    }
  }

  inline void v_print(v_ub &v)
  {
    for (int i = 0; i < v_ub::elem_cnt; i++)
    {
      printf("%4d ", v[i]);
    }

    printf("\n");
  }

  inline void v_print(v_ub &v1, v_ub &v2, v_ub &v3, v_ub &v4)
  {
    static int icount = 0;
    printf("%d: ", icount++);
    for (int i = 0; i < v_ub::elem_cnt; i++)
    {
      printf("%2d ", v1[i]);
    }

    printf("| ");

    for (int i = 0; i < v_ub::elem_cnt; i++)
    {
      printf("%2d ", v2[i]);
    }
    printf("| ");

    for (int i = 0; i < v_ub::elem_cnt; i++)
    {
      printf("%2d ", v3[i]);
    }
    printf("| ");
    for (int i = 0; i < v_ub::elem_cnt; i++)
    {
      printf("%2d ", v4[i]);
    }

    printf("\n");
  }

  inline void v_print(v_ub *v, int nv)
  {
    static int icount = 0;
    printf("%d: ", icount++);
    for (int j = 0; j < nv; j++)
    {
      for (int i = 0; i < v_ub::elem_cnt; i++)
      {
        printf("%4d ", v[j][i]);
      }                
    }
    printf("\n");
  }


  __forceinline v_ub ACS_Branch(v_ub& va, v_ub& vb, v_ub& vBM1, v_ub& vBM2, unsigned __int16& iPH)
  {
    v_ub vc    = v_add(va, vBM1);// from 0
    v_ub vd    = v_add(vb, vBM2);// from 1
    v_b vdiff  = v_sub(vd, vc); // difference

    iPH        = (unsigned __int16)vdiff.v_signmask();

    v_ub vmin  = v_min(vc, vd);

    return vmin;
  }

  __forceinline void Shuffle(v_ub& va, v_ub& vb, v_ub& vmask, v_ub& veven, v_ub&vodd)
  {
    va = va.v_shuffle(vmask);
    vb = vb.v_shuffle(vmask);

    (v_q&)veven = ((v_q&)va).v_unpack_lo((v_q&)vb);
    (v_q&)vodd  = ((v_q&)va).v_unpack_hi((v_q&)vb);
  }

  __forceinline void ButterFly(v_ub& va, v_ub& vb, v_ub& vShuffleMask, v_ub& vBM1, v_ub& vBM2, unsigned __int16& iPH1, unsigned __int16& iPH2)
  {
    v_ub veven, vodd;
    Shuffle(va, vb, vShuffleMask, veven, vodd);

    va = ACS_Branch(veven, vodd, vBM1, vBM2, iPH1);//0-branch
    vb = ACS_Branch(veven, vodd, vBM2, vBM1, iPH2);//1-branch
  }

  __forceinline __int8 BMAddress(unsigned __int8 b0, unsigned __int8 b1)
  {
    return ( (b0 & 7) | ((b1 & 7) << 3) );
  }

  __forceinline unsigned __int8 BMAddress(unsigned __int8 b)
  {
    return b;
  }

  __forceinline __int8 PrevPHAddress(unsigned __int8* pvPath, unsigned __int8& Index)
  {
    unsigned __int8 AddressHi = Index >> 3;
    unsigned __int8 AddressLo = Index & 0x7;

    unsigned __int8 v = pvPath[AddressHi];
    return ( ((v >> AddressLo) & 1) | ((Index << 1) & 0x3F) );
  }

  __forceinline unsigned __int8 FindMinValueAddress(v_ub* pvTrellis)
  {
    v_ub vb0, vb1;
    v_us vs0, vs1, vs2, vs3;

    unsigned __int16 MinPos;

    vb0 = m_vStateIndex[0];
    vb1 = pvTrellis[0];

    vs1 = (v_us)v_unpack_lo( vb0, vb1 );
    vs2 = (v_us)v_unpack_hi( vb0, vb1 );

    vs0 = v_min(vs1, vs2);

    vb0 = m_vStateIndex[1];
    vb1 = pvTrellis[1];
    vs1 = (v_us)v_unpack_lo ( vb0, vb1 );
    vs2 = (v_us)v_unpack_hi ( vb0, vb1 );

    vs3 = v_min (vs1, vs2);
    vs0 = v_min (vs0, vs3);

    vb0 = m_vStateIndex[2];
    vb1 = pvTrellis[2];
    vs1 = (v_us)v_unpack_lo ( vb0, vb1 );
    vs2 = (v_us)v_unpack_hi ( vb0, vb1 );

    vs3 = v_min (vs1, vs2);
    vs0 = v_min (vs0, vs3);

    vb0 = m_vStateIndex[3];
    vb1 = pvTrellis[3];
    vs1 = (v_us)v_unpack_lo ( vb0, vb1 );
    vs2 = (v_us)v_unpack_hi ( vb0, vb1 );

    vs3 = v_min (vs1, vs2);
    vs0 = v_min (vs0, vs3);

    vs0 = vs0.v_hminpos();

    MinPos = vs0.v_get_at<0>();// the minimum index in 7:0
    //MinPos &= 0xFF;

    return (unsigned __int8)MinPos;
  }

  __forceinline void Normalize(v_ub* pvTrellis)
  {
    v_ub vb0, vb1, vb2, vb3, vb4, vb5;

    vb0 = pvTrellis[0];
    vb1 = pvTrellis[1];

    vb4 = v_min(vb0, vb1);

    vb2 = pvTrellis[2];
    vb3 = pvTrellis[3];

    vb5 = v_min(vb2, vb3);

    vb4 = v_min(vb4, vb5);

    vb5 = ((v_i&)vb4).v_shuffle<2, 3, 0, 1>();

    vb4 = v_min(vb4, vb5);

    // vb0 contains 8 minimum values
    // cast into 8 shorts
    vb5 = v_unpack_lo(vb4, vb4);

    vb4 = ((v_us&)vb5).v_hminpos();

    vb4 = ((v_s&)vb4).v_shuffle_lo<0, 0, 0, 0>();
    vb4 = v_unpack_lo(vb4, vb4);

    pvTrellis[0] = v_sub(vb0, vb4);
    pvTrellis[1] = v_sub(vb1, vb4);
    pvTrellis[2] = v_sub(vb2, vb4);
    pvTrellis[3] = v_sub(vb3, vb4);
  }

  __forceinline void Normalize(v_ub* pvTrellis, v_ub& vNormConst)
  {
    pvTrellis[0] = v_sub(pvTrellis[0], vNormConst);
    pvTrellis[1] = v_sub(pvTrellis[1], vNormConst);
    pvTrellis[2] = v_sub(pvTrellis[2], vNormConst);
    pvTrellis[3] = v_sub(pvTrellis[3], vNormConst);
  }

  __forceinline void TraceBack(unsigned __int16 HistoryIndex, unsigned __int8 MinIndex, int TraceBackLength, int TraceOutputLength, unsigned __int8* pDecodedBytes)
  {
    unsigned __int8* pPathHistory;

    unsigned __int8 PHAddress;

    PHAddress = MinIndex;

    unsigned __int8 Output = 0;
    unsigned __int8* p = pDecodedBytes;

    for (int i = 0; i < TraceBackLength; i++)
    {
      pPathHistory = (unsigned __int8*)&m_TBQ[HistoryIndex];

      PHAddress = PrevPHAddress(pPathHistory, PHAddress);

      HistoryIndex -= 1;
      HistoryIndex &= RQ_MASK;
    }

    for (int i = 0; i < TraceOutputLength >> 3; i++)
    {
      for ( int j = 0; j < 8; j++)
      {
        Output <<= 1;
        Output |= (PHAddress >> 5);// since we know only 6 bits are valid

        pPathHistory = (unsigned __int8*)&m_TBQ[HistoryIndex];

        PHAddress = PrevPHAddress(pPathHistory, PHAddress);

        HistoryIndex -= 1;
        HistoryIndex &= RQ_MASK;
      }
      *p = Output;
      p--;
    }
  }


  //////////////////////////////////////////////////////////////////////////



  struct viterbi_worker 
  {
    dsp_viterbi_64& m_viterbi;

    viterbi_worker(dsp_viterbi_64& vit) : m_viterbi(vit)
    {

    }

    void execute_1_2()
    {
      v_ub vShuffleMask;
      v_ub vNormMask;
      v_ub vStates[4];
      v_ub vBM0, vBM1;

      int  BMIndex = 4;
      unsigned __int16 iPH0, iPH1;
      unsigned __int16 MinAddressIndex = 0;

      vShuffleMask = m_viterbi.m_vShuffleMask;
      vNormMask    = m_viterbi.m_vNormMask;

      for (int i = 0; i < 4; i++)
      {
        vStates[i].v_setall(128);
      }
      vStates[0].v_set_at<0>(0);


      unsigned __int16  TBQwit     = 0;
      unsigned __int16  TBQrit     = 0;
      unsigned int iTrellis   = 0;

      unsigned __int8 *pSoftBits         = m_viterbi.m_pSoftBits;
      unsigned __int8* pDecodedBytes     = m_viterbi.m_pDecodedBytes;
      __int32          TotalDecodedBytes = m_viterbi.m_nDecodedBytes;
      unsigned __int16 TraceBackPt       = 0;

      tick_count tbegin, tend, tend2, tduration, tduration2;

      __int32 nTotalSoftBits = m_viterbi.m_nDecodedBytes * 8 * 2; // 1/2 coding

      tbegin = tick_count::now();

      for (__int32 nSoftBits = 0; nSoftBits < nTotalSoftBits; nSoftBits += 4)
      {
        // stage StageIndex
        BMIndex = m_viterbi.BMAddress(pSoftBits[nSoftBits], pSoftBits[nSoftBits + 1]);

        v_ub* pvBM = &m_viterbi.m_vBM[BMIndex][0];

        vBM0 = pvBM[0];
        vBM1 = pvBM[1];
        m_viterbi.ButterFly(vStates[0], vStates[1], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][0] = iPH0;
        m_viterbi.m_TBQ[TBQwit][2] = iPH1;

        vBM0 = pvBM[2];
        vBM1 = pvBM[3];
        m_viterbi.ButterFly(vStates[2], vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][1] = iPH0;
        m_viterbi.m_TBQ[TBQwit][3] = iPH1;

        //m_viterbi.v_print(vStates, 4);

        TBQwit += 1;
        TBQwit &= RQ_MASK;
        // stage StageIndex + 1
        BMIndex = m_viterbi.BMAddress(pSoftBits[nSoftBits + 2], pSoftBits[nSoftBits + 3]);

        pvBM = &m_viterbi.m_vBM[BMIndex][0];

        vBM0 = pvBM[0];
        vBM1 = pvBM[1];
        m_viterbi.ButterFly(vStates[0], vStates[2], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][0] = iPH0;
        m_viterbi.m_TBQ[TBQwit][1] = iPH1;

        vBM0 = pvBM[2];
        vBM1 = pvBM[3];
        m_viterbi.ButterFly(vStates[1], vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][2] = iPH0;
        m_viterbi.m_TBQ[TBQwit][3] = iPH1;

        TBQwit   += 1;
        TBQwit   &= RQ_MASK;
        iTrellis += 2;

        //m_viterbi.v_print(vStates, 4);

        if (vStates[0].v_get_at<0>() > 170)
        {
          //printf("===Normalization===\n");
          //m_viterbi.v_print(vStates, 4);
          //m_viterbi.Normalize(vStates);
          m_viterbi.Normalize(vStates, vNormMask);
          //m_viterbi.v_print(vStates, 4);
        }

        if (iTrellis == nTracebackDataCount)
        {
          unsigned __int8 MinAddress = m_viterbi.FindMinValueAddress(vStates);
          //unsigned __int8 MinAddress = 0;

          TraceBackPt = TBQrit + nTracebackOffset;
          TraceBackPt &= RQ_MASK;

          m_viterbi.TraceBack(TraceBackPt, MinAddress, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);

          pDecodedBytes     += nTraceBackOutputByte;
          TotalDecodedBytes -= nTraceBackOutputByte;

          TBQrit            += nTraceBackOutput;
          TBQrit            &= RQ_MASK;
          iTrellis          -= nTraceBackOutput;
        }
      }


      //m_viterbi.TraceBack(TraceBackPt, 0, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);

      if ( iTrellis >= nTraceBackLength )
      {
        unsigned int iTrellisPadding = (nTracebackDataCount - iTrellis);

        for (unsigned int i = 0; i < iTrellisPadding; i++)
        {
          m_viterbi.m_TBQ[TBQwit][0] = m_viterbi.m_TBQ[TBQwit][1] = m_viterbi.m_TBQ[TBQwit][2] = m_viterbi.m_TBQ[TBQwit][3] = 0;                        
          TBQwit += 1;
          TBQwit &= RQ_MASK;
        }

        TraceBackPt = TBQrit + nTracebackOffset;
        TraceBackPt &= RQ_MASK;

        m_viterbi.TraceBack(TraceBackPt, 0, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);

        pDecodedBytes     += nTraceBackOutputByte;
        TotalDecodedBytes -= nTraceBackOutputByte;

        TBQrit            += nTraceBackOutput;
        TBQrit            &= RQ_MASK;
      }

      while (TotalDecodedBytes > 0)
      {
        // pad traceback length zeros
        for (unsigned int i = 0; i < nTraceBackOutput; i++)
        {
          m_viterbi.m_TBQ[TBQwit][0] = m_viterbi.m_TBQ[TBQwit][1] = m_viterbi.m_TBQ[TBQwit][2] = m_viterbi.m_TBQ[TBQwit][3] = 0;                        
          TBQwit += 1;
          TBQwit &= RQ_MASK;
        }

        TraceBackPt = TBQrit + nTracebackOffset;
        TraceBackPt &= RQ_MASK;

        m_viterbi.TraceBack(TraceBackPt, 0, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);

        pDecodedBytes     += nTraceBackOutputByte;
        TotalDecodedBytes -= nTraceBackOutputByte;

        TBQrit            += nTraceBackOutput;
        TBQrit            &= RQ_MASK;
      }


      tend = tick_count::now();
      tduration = tend - tbegin;
      printf("ACSThread: %f us, %f Mbps\n", tduration.us(), m_viterbi.m_nDecodedBytes * 8 / tduration.us());
    }

#if 0
    void execute_2_3()
    {
      v_ub vStates[4];
      v_ub vBM0, vBM1;
      v_ub vShuffleMask;
      int  BMIndex = 4;
      unsigned __int16 iPH0, iPH1;
      unsigned __int16 MinAddressIndex = 0;

      vShuffleMask = m_viterbi.m_vShuffleMask;

      for (int i = 0; i < 4; i++)
      {
        vStates[i].v_setall(128);
      }
      vStates[0].v_set_at<0>(0);


      VitRQ::iter  TBQwit     = 0;
      VitRQ::iter  TBQrit     = 0;
      unsigned int iTrellis   = 0;

      unsigned __int8 *pSoftBits         = m_viterbi.m_pSoftBits;
      unsigned __int8* pDecodedBytes     = m_viterbi.m_pDecodedBytes;
      __int32          TotalDecodedBytes = m_viterbi.m_nDecodedBytes;
      unsigned __int16 TraceBackPt       = 0;

      tick_count tbegin, tend, tend2, tduration, tduration2;

      __int32 nTotalSoftBits = m_viterbi.m_nDecodedBytes * 8 * 3 / 2; // 2/3 coding

      tbegin = tick_count::now();

      for (__int32 nSoftBits = 0; nSoftBits < nTotalSoftBits; nSoftBits += 3)
      {
        // stage StageIndex
        BMIndex = m_viterbi.BMAddress(pSoftBits[nSoftBits], pSoftBits[nSoftBits + 1]);

        v_ub* pvBM = &m_viterbi.m_vBM[BMIndex][0];

        vBM0 = pvBM[0];
        vBM1 = pvBM[1];
        m_viterbi.ButterFly(vStates[0], vStates[1], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][0] = iPH0;
        m_viterbi.m_TBQ[TBQwit][2] = iPH1;

        vBM0 = pvBM[2];
        vBM1 = pvBM[3];
        m_viterbi.ButterFly(vStates[2], vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][1] = iPH0;
        m_viterbi.m_TBQ[TBQwit][3] = iPH1;

        TBQwit += 1;
        TBQwit &= RQ_MASK;

        // stage StageIndex + 1
        BMIndex = m_viterbi.BMAddress(pSoftBits[nSoftBits + 2]);

        pvBM = &m_viterbi.m_vBM0[BMIndex][0];

        vBM0 = pvBM[0];
        vBM1 = pvBM[1];
        m_viterbi.ButterFly(vStates[0], vStates[2], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][0] = iPH0;
        m_viterbi.m_TBQ[TBQwit][1] = iPH1;

        vBM0 = pvBM[2];
        vBM1 = pvBM[3];
        m_viterbi.ButterFly(vStates[1], vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][2] = iPH0;
        m_viterbi.m_TBQ[TBQwit][3] = iPH1;

        TBQwit   += 1;
        TBQwit   &= RQ_MASK;
        iTrellis += 2;

        //m_viterbi.v_print(vStates, 4);

        if (vStates[0].v_get_at<0>() > 192)
        {
          //m_viterbi.v_print(vStates, 4);
          m_viterbi.Normalize(vStates);
        }

        if (iTrellis >= nTracebackDataCount)
        {
          unsigned __int8 MinAddress = m_viterbi.FindMinValueAddress(vStates);
          //unsigned __int8 MinAddress = 0;

          TraceBackPt = TBQrit + nTracebackOffset;
          TraceBackPt &= RQ_MASK;

          m_viterbi.TraceBack(TraceBackPt, MinAddress, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);

          pDecodedBytes     += nTraceBackOutputByte;
          TotalDecodedBytes -= nTraceBackOutputByte;

          TBQrit            += nTraceBackOutput;
          TBQrit            &= RQ_MASK;
          iTrellis          -= nTraceBackOutput;
        }
      }

      if ( iTrellis >= nTraceBackLength )
      {
        unsigned int iTrellisPadding = (nTracebackDataCount - iTrellis);

        for (unsigned int i = 0; i < iTrellisPadding; i++)
        {
          m_viterbi.m_TBQ[TBQwit][0] = m_viterbi.m_TBQ[TBQwit][1] = m_viterbi.m_TBQ[TBQwit][2] = m_viterbi.m_TBQ[TBQwit][3] = 0;                        
          TBQwit += 1;
          TBQwit &= RQ_MASK;
        }

        TraceBackPt = TBQrit + nTracebackOffset;
        TraceBackPt &= RQ_MASK;

        m_viterbi.TraceBack(TraceBackPt, 0, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);

        pDecodedBytes     += nTraceBackOutputByte;
        TotalDecodedBytes -= nTraceBackOutputByte;

        TBQrit            += nTraceBackOutput;
        TBQrit            &= RQ_MASK;
      }

      while (TotalDecodedBytes > 0)
      {
        // pad traceback length zeros
        for (unsigned int i = 0; i < nTraceBackOutput; i++)
        {
          m_viterbi.m_TBQ[TBQwit][0] = m_viterbi.m_TBQ[TBQwit][1] = m_viterbi.m_TBQ[TBQwit][2] = m_viterbi.m_TBQ[TBQwit][3] = 0;                        
          TBQwit += 1;
          TBQwit &= RQ_MASK;
        }

        TraceBackPt = TBQrit + nTracebackOffset;
        TraceBackPt &= RQ_MASK;

        m_viterbi.TraceBack(TraceBackPt, 0, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);

        pDecodedBytes     += nTraceBackOutputByte;
        TotalDecodedBytes -= nTraceBackOutputByte;

        TBQrit            += nTraceBackOutput;
        TBQrit            &= RQ_MASK;
      }


      tend = tick_count::now();
      tduration = tend - tbegin;
      printf("ACSThread: %f us, %f Mbps\n", tduration.us(), m_viterbi.m_nDecodedBytes * 8 / tduration.us());
    }

    void execute_3_4()
    {
      v_ub vStates[4];
      v_ub vBM0, vBM1;
      v_ub vShuffleMask;
      int  BMIndex = 4;
      unsigned __int16 iPH0, iPH1;
      unsigned __int16 MinAddressIndex = 0;

      vShuffleMask = m_viterbi.m_vShuffleMask;

      for (int i = 0; i < 4; i++)
      {
        vStates[i].v_setall(128);
      }
      vStates[0].v_set_at<0>(0);


      VitRQ::iter  TBQwit     = 0;
      VitRQ::iter  TBQrit     = 0;
      unsigned int iTrellis   = 0;

      unsigned __int8 *pSoftBits         = m_viterbi.m_pSoftBits;
      unsigned __int8* pDecodedBytes     = m_viterbi.m_pDecodedBytes;
      __int32          TotalDecodedBytes = m_viterbi.m_nDecodedBytes;
      unsigned __int16 TraceBackPt       = 0;

      tick_count tbegin, tend, tend2, tduration, tduration2;

      __int32 nTotalSoftBits = m_viterbi.m_nDecodedBytes * 8 * 4 / 3; // 3/4 coding

      tbegin = tick_count::now();

      for (__int32 nSoftBits = 0; nSoftBits < nTotalSoftBits; nSoftBits += 8)
      {
        // stage StageIndex
        BMIndex = m_viterbi.BMAddress(pSoftBits[nSoftBits], pSoftBits[nSoftBits + 1]);

        v_ub* pvBM = &m_viterbi.m_vBM[BMIndex][0];

        vBM0 = pvBM[0];
        vBM1 = pvBM[1];
        m_viterbi.ButterFly(vStates[0], vStates[1], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][0] = iPH0;
        m_viterbi.m_TBQ[TBQwit][2] = iPH1;

        vBM0 = pvBM[2];
        vBM1 = pvBM[3];
        m_viterbi.ButterFly(vStates[2], vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][1] = iPH0;
        m_viterbi.m_TBQ[TBQwit][3] = iPH1;

        //m_viterbi.v_print(vStates, 4);

        TBQwit += 1;
        TBQwit &= RQ_MASK;
        // stage StageIndex + 1
        BMIndex = m_viterbi.BMAddress(pSoftBits[nSoftBits + 2]);

        pvBM = &m_viterbi.m_vBM0[BMIndex][0];

        vBM0 = pvBM[0];
        vBM1 = pvBM[1];
        m_viterbi.ButterFly(vStates[0], vStates[2], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][0] = iPH0;
        m_viterbi.m_TBQ[TBQwit][1] = iPH1;

        vBM0 = pvBM[2];
        vBM1 = pvBM[3];
        m_viterbi.ButterFly(vStates[1], vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][2] = iPH0;
        m_viterbi.m_TBQ[TBQwit][3] = iPH1;

        TBQwit   += 1;
        TBQwit   &= RQ_MASK;

        //m_viterbi.v_print(vStates, 4);

        // stage StageIndex + 2
        BMIndex = m_viterbi.BMAddress(pSoftBits[nSoftBits + 3]);

        pvBM = &m_viterbi.m_vBM1[BMIndex][0];

        vBM0 = pvBM[0];
        vBM1 = pvBM[1];
        m_viterbi.ButterFly(vStates[0], vStates[1], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][0] = iPH0;
        m_viterbi.m_TBQ[TBQwit][2] = iPH1;

        vBM0 = pvBM[2];
        vBM1 = pvBM[3];
        m_viterbi.ButterFly(vStates[2], vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][1] = iPH0;
        m_viterbi.m_TBQ[TBQwit][3] = iPH1;

        TBQwit   += 1;
        TBQwit   &= RQ_MASK;

        //m_viterbi.v_print(vStates, 4);

        // stage StageIndex + 3
        BMIndex = m_viterbi.BMAddress(pSoftBits[nSoftBits + 4], pSoftBits[nSoftBits + 5]);

        pvBM = &m_viterbi.m_vBM[BMIndex][0];

        vBM0 = pvBM[0];
        vBM1 = pvBM[1];
        m_viterbi.ButterFly(vStates[0], vStates[2], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][0] = iPH0;
        m_viterbi.m_TBQ[TBQwit][1] = iPH1;

        vBM0 = pvBM[2];
        vBM1 = pvBM[3];
        m_viterbi.ButterFly(vStates[1], vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][2] = iPH0;
        m_viterbi.m_TBQ[TBQwit][3] = iPH1;

        TBQwit   += 1;
        TBQwit   &= RQ_MASK;

        //m_viterbi.v_print(vStates, 4);

        // stage StageIndex + 4
        BMIndex = m_viterbi.BMAddress(pSoftBits[nSoftBits + 6]);

        pvBM = &m_viterbi.m_vBM0[BMIndex][0];

        vBM0 = pvBM[0];
        vBM1 = pvBM[1];
        m_viterbi.ButterFly(vStates[0], vStates[1], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][0] = iPH0;
        m_viterbi.m_TBQ[TBQwit][2] = iPH1;

        vBM0 = pvBM[2];
        vBM1 = pvBM[3];
        m_viterbi.ButterFly(vStates[2], vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][1] = iPH0;
        m_viterbi.m_TBQ[TBQwit][3] = iPH1;

        TBQwit += 1;
        TBQwit &= RQ_MASK;

        //m_viterbi.v_print(vStates, 4);

        // stage StageIndex + 5
        BMIndex = m_viterbi.BMAddress(pSoftBits[nSoftBits + 7]);

        pvBM = &m_viterbi.m_vBM1[BMIndex][0];

        vBM0 = pvBM[0];
        vBM1 = pvBM[1];
        m_viterbi.ButterFly(vStates[0], vStates[2], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][0] = iPH0;
        m_viterbi.m_TBQ[TBQwit][1] = iPH1;

        vBM0 = pvBM[2];
        vBM1 = pvBM[3];
        m_viterbi.ButterFly(vStates[1], vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
        m_viterbi.m_TBQ[TBQwit][2] = iPH0;
        m_viterbi.m_TBQ[TBQwit][3] = iPH1;

        TBQwit   += 1;
        TBQwit   &= RQ_MASK;
        iTrellis += 6;

        //m_viterbi.v_print(vStates, 4);

        if (vStates[0].v_get_at<0>() > 208)
        {
          //m_viterbi.v_print(vStates, 4);
          m_viterbi.Normalize(vStates);
        }

        if (iTrellis >= nTracebackDataCount)
        {
          unsigned __int8 MinAddress = m_viterbi.FindMinValueAddress(vStates);
          //unsigned __int8 MinAddress = 0;

          TraceBackPt = TBQrit + nTracebackOffset;
          TraceBackPt &= RQ_MASK;

          m_viterbi.TraceBack(TraceBackPt, MinAddress, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);

          pDecodedBytes     += nTraceBackOutputByte;
          TotalDecodedBytes -= nTraceBackOutputByte;

          TBQrit            += nTraceBackOutput;
          TBQrit            &= RQ_MASK;
          iTrellis          -= nTraceBackOutput;
        }
      }

      if ( iTrellis >= nTraceBackLength )
      {
        unsigned int iTrellisPadding = (nTracebackDataCount - iTrellis);

        for (unsigned int i = 0; i < iTrellisPadding; i++)
        {
          m_viterbi.m_TBQ[TBQwit][0] = m_viterbi.m_TBQ[TBQwit][1] = m_viterbi.m_TBQ[TBQwit][2] = m_viterbi.m_TBQ[TBQwit][3] = 0;                        
          TBQwit += 1;
          TBQwit &= RQ_MASK;
        }

        TraceBackPt = TBQrit + nTracebackOffset;
        TraceBackPt &= RQ_MASK;

        m_viterbi.TraceBack(TraceBackPt, 0, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);

        pDecodedBytes     += nTraceBackOutputByte;
        TotalDecodedBytes -= nTraceBackOutputByte;

        TBQrit            += nTraceBackOutput;
        TBQrit            &= RQ_MASK;
      }

      while (TotalDecodedBytes > 0)
      {
        // pad traceback length zeros
        for (unsigned int i = 0; i < nTraceBackOutput; i++)
        {
          m_viterbi.m_TBQ[TBQwit][0] = m_viterbi.m_TBQ[TBQwit][1] = m_viterbi.m_TBQ[TBQwit][2] = m_viterbi.m_TBQ[TBQwit][3] = 0;                        
          TBQwit += 1;
          TBQwit &= RQ_MASK;
        }

        TraceBackPt = TBQrit + nTracebackOffset;
        TraceBackPt &= RQ_MASK;

        m_viterbi.TraceBack(TraceBackPt, 0, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);

        pDecodedBytes     += nTraceBackOutputByte;
        TotalDecodedBytes -= nTraceBackOutputByte;

        TBQrit            += nTraceBackOutput;
        TBQrit            &= RQ_MASK;
      }

      tend = tick_count::now();
      tduration = tend - tbegin;
      printf("ACSThread: %f us, %f Mbps\n", tduration.us(), m_viterbi.m_nDecodedBytes * 8 / tduration.us());
    }
#endif


    void execute()
    {
      execute_1_2();
      //execute_2_3();
      //execute_3_4();

      return 1;
    }
  };
};