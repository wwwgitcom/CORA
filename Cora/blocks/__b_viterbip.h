#pragma once


// parallel viterbi dispatcher
DEFINE_BLOCK(b_parallel_viterbi64_1v2, 1, 3)
{
  size_t   nTraceBackLength;
  size_t   nTraceBackOutput;
  size_t   nTracebackSoftbits;

  size_t   iOutPort;
  size_t   iOutLength;

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

    nTracebackSoftbits = (nTraceBackLength + nTraceBackOutput + nTraceBackLength) << 1;

    iOutPort = 0;
    iOutLength = 0;
  }


  BLOCK_RESET
  {
    auto nin = ninput(0);
    consume(0,nin);

    auto nout = nTraceBackLength - TB_PREFIX_VITAS;

    auto op1 = $_<uint8>(0); // data port
    auto op2 = $_<uint8>(1); // data port

    memset(op1, 0, sizeof(uint8) * nout);
    memset(op2, 0, sizeof(uint8) * nout);

    produce_each(nout);

    iOutPort = 0;
    iOutLength = 0;
  }
  //////////////////////////////////////////////////////////////////////////

  BLOCK_WORK
  {
    auto nInputSoftBits = ninput(0);
    if (nInputSoftBits < nTracebackSoftbits) return false;

    auto ip  = _$<uint8>(0);
    auto op1 = $_<uint8>(0); // data port
    auto op2 = $_<uint8>(1); // data port
    auto op3 = $_<uint8>(2); // control port

    uint8* op[] = {op1, op2};

    auto nitems1 = nitems(0);
    auto nitems2 = nitems(1);
    uint32 nitems[] = {nitems1, nitems2};
    // TODO: add schemes to decide which port to write to 

    auto nspace1 = noutput(0);
    auto nspace2 = noutput(1);
    auto nspace3 = noutput(2);

    uint32 nspaces[] = {nspace1, nspace2, nspace3};

    if (nspace3 < 1 )
    {
      //printf("%d. ", nspace3);
      return false;
    }

    if (nspaces[iOutPort] < nTracebackSoftbits)
    {
      //printf("-");
      return false;
    }

    memcpy(op[iOutPort], ip, sizeof(uint8) * nTracebackSoftbits);

    consume(0, nTracebackSoftbits);

    produce(iOutPort, nTracebackSoftbits);
    *op3 = iOutPort;
    produce(2, 1);

    iOutPort ++;
    iOutPort &= 0x1;

    //printf("vit disp=: port: %d, out: %d\n", iOutPort, nOutCount);
    return true;
  }
};



// parallel viterbi dispatcher
DEFINE_BLOCK(b_parallel_viterbi64_1v4, 1, 5)
{
  size_t   nTraceBackLength;
  size_t   nTraceBackOutput;
  size_t   nTracebackBlockBits;
  size_t   nTracebackHistoryBits;

  size_t   iOutPort;
  size_t   iOutLength;

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

    nTracebackBlockBits = (nTraceBackLength + nTraceBackOutput + nTraceBackLength) << 1;
    nTracebackHistoryBits  = (nTraceBackLength + nTraceBackOutput) << 1;

    iOutPort = 0;
    iOutLength = 0;
  }


  BLOCK_RESET
  {
    auto nin = ninput(0);
    consume(0,nin);

    auto nout = nTraceBackLength - TB_PREFIX_VITAS;

    auto op1 = $_<uint8>(0); // data port
    auto op2 = $_<uint8>(1); // data port
    auto op3 = $_<uint8>(2); // data port
    auto op4 = $_<uint8>(3); // data port

    memset(op1, 0, sizeof(uint8) * nout);
    memset(op2, 0, sizeof(uint8) * nout);
    memset(op3, 0, sizeof(uint8) * nout);
    memset(op4, 0, sizeof(uint8) * nout);

    produce_each(nout);

    iOutPort = 0;
    iOutLength = 0;
  }
  //////////////////////////////////////////////////////////////////////////

  BLOCK_WORK
  {
    auto nInputSoftBits = ninput(0);
    if (nInputSoftBits < nTracebackBlockBits) return false;

    auto ip  = _$<uint8>(0);
    auto op1 = $_<uint8>(0); // data port
    auto op2 = $_<uint8>(1); // data port
    auto op3 = $_<uint8>(2); // data port
    auto op4 = $_<uint8>(3); // data port
    auto op5 = $_<uint8>(4); // control port

    uint8* op[] = {op1, op2, op3, op4};

    auto nitems1 = nitems(0);
    auto nitems2 = nitems(1);
    auto nitems3 = nitems(2);
    auto nitems4 = nitems(3);
    uint32 nitems[] = {nitems1, nitems2, nitems3, nitems4};
    // TODO: add schemes to decide which port to write to 

    uint32 minitems = UINT32_MAX;
    for (uint32 i = 0; i < 4; i++)
    {
      if (nitems[i] < minitems)
      {
        minitems = nitems[i];
        iOutPort = i;
      }
    }

    auto nspace1 = noutput(0);
    auto nspace2 = noutput(1);
    auto nspace3 = noutput(2);
    auto nspace4 = noutput(3);
    auto nspace5 = noutput(4);// control port

    uint32 nspaces[] = {nspace1, nspace2, nspace3, nspace4, nspace5};

    if (nspace5 < 1 )
    {
      //printf("%d. ", nspace3);
      return false;
    }

    if (nspaces[iOutPort] < nTracebackBlockBits)
    {
      //printf("-");
      return false;
    }

    memcpy(op[iOutPort], ip, sizeof(uint8) * nTracebackBlockBits);

    consume(0, nTracebackHistoryBits);

    produce(iOutPort, nTracebackBlockBits);
    *op5 = iOutPort;
    produce(4, 1);

    iOutPort ++;
    iOutPort &= 0x3;

    //printf("vit disp=: port: %d\n", iOutPort);
    return true;
  }
};




//////////////////////////////////////////////////////////////////////////


DEFINE_BLOCK(b_viterbi_source_v1, 0, 1)
{
  //static const int N = 30 * 8 * 4;



  tick_count tstart, tend;

  int nProducedBits;

public:
  int nTotalBits;
  int nBlockSoftBits;

  BLOCK_INIT
  {
    nProducedBits = 0;
    nTotalBits = 1000 * 1000;
    nBlockSoftBits = 10 * 8 * 4;// start from 40Mbps
    tstart = tick_count::now();
  }


  BLOCK_INPUT_EVENT_HANDLER
  {
    if ($.Event.KeyEvent.uChar.AsciiChar == 'a')
    {
      nBlockSoftBits += 10 * 2 * 4; // inc 10Mbps
      printf("increase source rate to %d Mbps\n", nBlockSoftBits / 8);
    }
    else if ($.Event.KeyEvent.uChar.AsciiChar == 'd')
    {
      nBlockSoftBits -= 10 * 2 * 4; // inc 10Mbps
      printf("decrease source rate to %d Mbps\n", nBlockSoftBits / 8);
    }
  }

  BLOCK_WORK
  {
    //if (nProducedBits > nTotalBits)
    //{
    //  return false;
    //}

    auto op = $_<uint8>(0);
    tick_count tdif;

    do
    {
      _mm_pause();
      tend = tick_count::now();
      tdif = tend - tstart;
    }while (tdif.us() < 4.0);

    tstart = tick_count::now();

    auto nout = noutput(0);

    if (nout < nBlockSoftBits)
    {
      //printf("x");
      return true;
    }


    for (int i = 0; i < nBlockSoftBits; i++)
    {
      op[i] = 0;
    }

    //nProducedBits += N;

    produce(0, nBlockSoftBits);
    return true;
  }
};

DEFINE_BLOCK(b_viterbi_sink_2v1, 3, 1)
{
  size_t nSegmentSize;

  int nTotalDecodedBits;
  int  nDecodedBits;

  BLOCK_INIT
  {
    auto v = $["nSegmentSize"];
    if (!v.empty())
    {
      nSegmentSize = atoi(v.c_str());
    }
    else
    {
      nSegmentSize = 1;
    }

    nDecodedBits = 0;
    nTotalDecodedBits = 0;
    tstart = tick_count::now();
  }

  tick_count tstart, tend;

  BLOCK_WORK
  {
    tick_count tdif;

    tend = tick_count::now();
    tdif = tend - tstart;
    if (tdif.s() > 1.0)
    {
      double rate = nDecodedBits / tdif.us();

      printf("dT %f Mbps, b=%d, bt=%d, t=%f ms\n", rate, nDecodedBits, nTotalDecodedBits, tdif.ms());
      nDecodedBits = 0;
      tstart = tick_count::now();
    }

    auto nin3 = ninput(2);

    if (nin3 < 1) return false;

    //printf("vit combiner: Nport: %d\n", nin3);

    auto nin1 = ninput(0);
    auto nin2 = ninput(1);

    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto ip3 = _$<uint8>(2);

    uint8 * ip[] = {ip1, ip2, ip3};

    auto op  = $_<uint8>(0);

    // read from control port to get the data port
    auto iport = ip3[0];

    auto nin = ninput(iport);
    if (nin < nSegmentSize)
    {
      return false;
    }

    //printf("vit combiner: port: %d, len: %d\n", iport, nin);
#if 0
    printf("vit combiner: port: %d, len: %d\n", iport, nSegmentSize);
    for (int k = 0; k < nSegmentSize; k++)
    {
      printf(" %02X ", ip[iport][k]);
    }
    printf("\n");
#endif
    

    memcpy(op, ip[iport], sizeof(uint8) * nSegmentSize);

    produce(0, nSegmentSize);
    consume(iport, nSegmentSize);
    consume(2, 1);
    
    nDecodedBits += nSegmentSize * 8;
    nTotalDecodedBits += nSegmentSize * 8;

    return true;
  }
};


DEFINE_BLOCK(b_viterbi_sink_4v1, 5, 1)
{
  size_t nSegmentSize;

  int nTotalDecodedBits;
  int  nDecodedBits;

  BLOCK_INIT
  {
    auto v = $["nSegmentSize"];
    if (!v.empty())
    {
      nSegmentSize = atoi(v.c_str());
    }
    else
    {
      nSegmentSize = 1;
    }

    nDecodedBits = 0;
    nTotalDecodedBits = 0;
    tstart = tick_count::now();
  }

  tick_count tstart, tend;

  BLOCK_WORK
  {
    tick_count tdif;

    tend = tick_count::now();
    tdif = tend - tstart;
    if (tdif.s() > 1.0)
    {
      double rate = nDecodedBits / tdif.us();

      printf("dT %f Mbps, b=%d, bt=%d, t=%f ms\n", rate, nDecodedBits, nTotalDecodedBits, tdif.ms());

      printf("** %d, %d, %d, %d, %d\n", ninput(0), ninput(1), ninput(2), ninput(3), ninput(4));

      nDecodedBits = 0;
      tstart = tick_count::now();
    }

    auto nin5 = ninput(4);
    if (nin5 < 1) return false;

    //printf("vit combiner: Nport: %d\n", nin5);
    
    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto ip3 = _$<uint8>(2);
    auto ip4 = _$<uint8>(3);
    auto ip5 = _$<uint8>(4);

    uint8 * ip[] = {ip1, ip2, ip3, ip4};

    auto op  = $_<uint8>(0);

    // read from control port to get the data port
    auto iport = ip5[0];

    auto nin = ninput(iport);
    if (nin < nSegmentSize)
    {
      //printf("***vit combiner: port: %d, len: %d\n", iport, nin);
      return false;
    }

    //printf("vit combiner: port: %d, len: %d\n", iport, nin);
    
    memcpy(op, ip[iport], sizeof(uint8) * nSegmentSize);

    produce(0, nSegmentSize);
    consume(iport, nSegmentSize);
    consume(4, 1);

    nDecodedBits += nSegmentSize * 8;
    nTotalDecodedBits += nSegmentSize * 8;

    return true;
  }
};
