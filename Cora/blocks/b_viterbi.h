#pragma once

// viterbi decoder 1/2
DEFINE_BLOCK(b_viterbi64_1o2_1v1, 1, 1)
{
  __int32                   nTraceBackLength;
  __int32                   nTraceBackOutput;

  __int32                   nTracebackDataCount;
  __int32                   nTracebackOffset;
  __int32                   nTraceBackOutputByte;

  //                    ACS
  v_align(64)           v_ub m_vBM[64][4]; // 64 states, each state has two 32 BM
  v_align(64)           v_ub m_vBM0[8][4]; // 64 states, each state has two 32 BM
  v_align(64)           v_ub m_vBM1[8][4]; // 64 states, each state has two 32 BM

  //                    shared
  v_align(64)           v_ub m_vShuffleMask;
  v_ub                  m_vNormMask;
  unsigned              __int8 *m_pSoftBits;
  unsigned              __int8 *m_pDecodedBytes;
  __int32               m_nDecodedBytes;
  typedef v_ub             TBState[4];
  typedef unsigned __int16 SurviorPath[4];
  v_align(64)           TBState   m_MinAddress[1024];
  v_align(64)           v_ub      m_vStateIndex[4];
  dsp_buffer_ptr        m_buffer;
  dsp_buffer_reader_ptr m_buffer_reader;
  int      m_IncomeSoftBits;
  v_ub m_vStates[4];

  _global_(int, VitTotalSoftBits);

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
    m_IncomeSoftBits   = 0;
    nTracebackDataCount  = nTraceBackLength + nTraceBackOutput;
    nTracebackOffset     = nTraceBackLength + nTraceBackOutput - 1;
    nTraceBackOutputByte = nTraceBackOutput / 8;

    m_buffer        = dsp_make_buffer(1024, sizeof(SurviorPath));
    m_buffer_reader = dsp_buffer_add_reader(m_buffer);

    unsigned char k = 0;
    int i;

    k = 0;
    for (i = 0; i < 8; i++)
    {
      m_vShuffleMask[i] = k;
      k += 2;
    }
    k = 1;
    for (; i < 16; i++)
    {
      m_vShuffleMask[i] = k;
      k += 2;
    }

    k = 0;
    for (i = 0; i < 64; i++)
    {
      m_vStateIndex[0][i] = k++;
    }

    m_vNormMask.v_setall(255 - 100);


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
    for (int i = 0; i < 4; i++)
    {
      m_vStates[i].v_setall(128);
    }
    m_vStates[0].v_set_at<0>(0);
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

  __forceinline void TraceBack(__int32 HistoryIndex, unsigned __int8 MinIndex, int TraceBackLength, int TraceOutputLength, unsigned __int8* pDecodedBytes)
  {
    unsigned __int8* pPathHistory;

    unsigned __int8 PHAddress;

    PHAddress = MinIndex;

    unsigned __int8 Output = 0;
    unsigned __int8* p = pDecodedBytes;

    SurviorPath* TBQ = (SurviorPath*)m_buffer_reader->read_pointer();

    for (int i = 0; i < TraceBackLength; i++)
    {
      pPathHistory = (unsigned __int8*)&TBQ[HistoryIndex];

      PHAddress = PrevPHAddress(pPathHistory, PHAddress);

      HistoryIndex--;
    }

    for (int i = 0; i < TraceOutputLength >> 3; i++)
    {
      for ( int j = 0; j < 8; j++)
      {
        Output <<= 1;
        Output |= (PHAddress >> 5);// since we know only 6 bits are valid

        pPathHistory = (unsigned __int8*)&TBQ[HistoryIndex];

        PHAddress = PrevPHAddress(pPathHistory, PHAddress);

        HistoryIndex--;
      }
      *p = Output;
      p--;
    }
  }
  //////////////////////////////////////////////////////////////////////////

  BLOCK_RESET
  {
    for (int i = 0; i < 4; i++)
    {
      m_vStates[i].v_setall(128);
    }
    m_vStates[0].v_set_at<0>(0);

    m_IncomeSoftBits = 0;

    m_buffer->reset();
    m_buffer_reader->reset();
  }
  //////////////////////////////////////////////////////////////////////////

  BLOCK_WORK
  {
    trace();

    v_ub vShuffleMask;
    v_ub vNormMask;
    
    v_ub vBM0, vBM1;

    int  BMIndex = 4;
    unsigned __int16 iPH0, iPH1;
    unsigned __int16 MinAddressIndex = 0;

    vShuffleMask = m_vShuffleMask;
    vNormMask    = m_vNormMask;

    bool bRet = false;

    auto nInputSoftBits = ninput(0);

    if (nInputSoftBits <= 0) return false;

    auto pSoftBits     = _$<unsigned __int8>(0);
    auto pDecodedBytes = $_<unsigned __int8>(0);

    unsigned __int32 TBQwit = 0;

    SurviorPath* TBQ = (SurviorPath*)m_buffer->write_pointer();

    int iTrellis = m_buffer_reader->items_available();
    int nTotalSoftBits = *VitTotalSoftBits;

    //printf("vit=> %d\n", iTrellis);
    for (__int32 nSoftBits = 0; nSoftBits < nInputSoftBits && m_IncomeSoftBits < nTotalSoftBits; nSoftBits += 4)
    {
      // stage StageIndex
      BMIndex = BMAddress(pSoftBits[nSoftBits], pSoftBits[nSoftBits + 1]);

      v_ub* pvBM = &m_vBM[BMIndex][0];

      vBM0 = pvBM[0];
      vBM1 = pvBM[1];
      ButterFly(m_vStates[0], m_vStates[1], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
      
      TBQ[TBQwit][0] = iPH0;
      TBQ[TBQwit][2] = iPH1;

      vBM0 = pvBM[2];
      vBM1 = pvBM[3];
      ButterFly(m_vStates[2], m_vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
      TBQ[TBQwit][1] = iPH0;
      TBQ[TBQwit][3] = iPH1;

      //m_viterbi.v_print(vStates, 4);

      TBQwit++;
      // stage StageIndex + 1
      BMIndex = BMAddress(pSoftBits[nSoftBits + 2], pSoftBits[nSoftBits + 3]);

      pvBM = &m_vBM[BMIndex][0];

      vBM0 = pvBM[0];
      vBM1 = pvBM[1];
      ButterFly(m_vStates[0], m_vStates[2], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
      TBQ[TBQwit][0] = iPH0;
      TBQ[TBQwit][1] = iPH1;

      vBM0 = pvBM[2];
      vBM1 = pvBM[3];
      ButterFly(m_vStates[1], m_vStates[3], vShuffleMask, vBM0, vBM1, iPH0, iPH1);
      TBQ[TBQwit][2] = iPH0;
      TBQ[TBQwit][3] = iPH1;

      TBQwit++;

      if (m_vStates[0].v_get_at<0>() > 208)
      {
        Normalize(m_vStates, vNormMask);
      }

      iTrellis += 2;
      m_IncomeSoftBits += 4;

      if (iTrellis >= nTracebackDataCount)
      {
        //printf("vit: trace back %d\n", iTrellis);

        unsigned __int8 MinAddress = FindMinValueAddress(m_vStates);
        
        TraceBack(nTracebackOffset, MinAddress, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);

        pDecodedBytes      += nTraceBackOutputByte;
        iTrellis           -= nTraceBackOutput;

        //printf("vit: trace back done %d\n", iTrellis);

        m_buffer_reader->update_read_pointer(nTraceBackOutput);

        produce(0, nTraceBackOutputByte);

        bRet = true;
      }
    }

    //printf("vit<= %d\n", iTrellis);

    m_buffer->update_write_pointer(TBQwit);

    consume(0, nInputSoftBits);

    if (m_IncomeSoftBits >= nTotalSoftBits)
    {
      log("vitok\n");
      log("vit: income: %d, total=%d\n", m_IncomeSoftBits, nTotalSoftBits);

      for (unsigned int i = 0; i < nTraceBackOutput; i++)
      {
        TBQ[TBQwit][0] = TBQ[TBQwit][1] = TBQ[TBQwit][2] = TBQ[TBQwit][3] = 0;
        TBQwit++;
      }

      unsigned __int8 MinAddress = FindMinValueAddress(m_vStates);

      TraceBack(nTracebackOffset, MinAddress, nTraceBackLength, nTraceBackOutput, pDecodedBytes + nTraceBackOutputByte - 1);
      
      m_buffer_reader->update_read_pointer(nTraceBackOutput);

      produce(0, nTraceBackOutputByte);

      bRet = true;

      reset();
    }

    return bRet;
  }
};