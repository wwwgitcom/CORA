#pragma once


#define viterbi_rate_inv (4 / 3)


DEFINE_BLOCK(b_viterbi_source_v1, 0, 1)
{
  //static const int N = 30 * 8 * 4;

  tick_count tstart, tend;

  int nProducedBits;

public:
  int nTotalBits;
  int nBlockSoftBits;

  int ntime;
  int nrate;

  BLOCK_INIT
  {
    nProducedBits = 0;
    nTotalBits = 1000 * 1000;
    nrate = 40;
    ntime = 8;
    nBlockSoftBits = 10 * 4 * ntime;// start from 40Msbps
    tstart = tick_count::now();

    nrate = 351;
  }


  BLOCK_INPUT_EVENT_HANDLER
  {
    if ($.Event.KeyEvent.uChar.AsciiChar == 'a')
    {
      nrate += 10;

      fprintf(stderr, "vit increase source rate to %d Msbps\n", nrate);
    }
    else if ($.Event.KeyEvent.uChar.AsciiChar == 'd')
    {
      nrate -= 10;// dec 10Msbps
      fprintf(stderr, "vit decrease source rate to %d Msbps\n", nrate);
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
      tdif = (tend - tstart);
    }while (tdif.us() < (double)ntime);

    tstart = tend;

    int nOut = (int)(tdif.us() * nrate);


    //printf("src %f -> %d, %f Msbps\n", tdif.us(), nOut, nOut / tdif.us());

    auto noutspace = noutput(0);


    if (noutspace < nOut )
    {
      nOut = noutspace;
      //printf("%d x %d\n", noutspace, nOut);
      //return true;
    }


    //for (int i = 0; i < nBlockSoftBits; i++)
    //{
    //  op[i] = 0;
    //}

    //nProducedBits += N;

    produce(0, nOut );
    return true;
  }
};



// parallel viterbi dispatcher
DEFINE_BLOCK(b_parallel_viterbi64_1v2, 1, 3)
{
  size_t   nTraceBackLength;
  size_t   nTraceBackOutput;
  size_t   nTracebackSoftbits;

  int   iOutPort;
  int   iOutLength;

  //////////////////////////////////////////////////////////////////////////

  size_t   nOutStat[2];
  size_t   nOutStatCnt;


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

    nTracebackSoftbits = (nTraceBackLength + nTraceBackOutput + nTraceBackLength) * viterbi_rate_inv;


    iOutPort = 0;
    //iOutLength =  (nTraceBackLength + nTraceBackLength) << 1;
    iOutLength = 0;

    nOutStat[0] = nOutStat[1] = 0;
    nOutStatCnt = 0;
  }


  BLOCK_RESET
  {
    iOutPort = 0;
    iOutLength = (nTraceBackLength + nTraceBackLength)  * viterbi_rate_inv;
  }
  //////////////////////////////////////////////////////////////////////////

  BLOCK_WORK
  {
    auto nInputSoftBits = ninput(0);
    if (nInputSoftBits < 1) 
    {
      /*nOutStatCnt++;
      if (nOutStatCnt % 10000 == 0)
      printf("vit disp no data in input buf...\n");*/
      return false;
    }

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



    //if (nspaces[iOutPort] < nTracebackSoftbits)
    //{
    //  //printf("-");
    //  return false;
    //}

    int nOutTotal = 0;
    while (nInputSoftBits > 0)
    {
      int nLeft = (int)nTracebackSoftbits - iOutLength;
      int nOut  = min(nLeft, nInputSoftBits);

      int nbufsize = noutput(iOutPort);
      nOut         = min(nOut, nbufsize);

      produce(iOutPort, nOut);

      nOutTotal += nOut;
      iOutLength += nOut;
      nInputSoftBits -= nOut;

      //printf("vit source produce %d @ %d, %d\n", nOut, iOutPort, iOutLength);

      if (iOutLength == nTracebackSoftbits)
      {
        //while (noutput(2) < 1)
        //{
        //  printf("control port full...\n");
        //}

        //nOutStat[iOutPort]++;
        //nOutStatCnt++;
        //if (nOutStatCnt % 10000  == 0)
        //{
        //  printf("vit disp : [0]=%d, [1]=%d\n", nOutStat[0], nOutStat[1]);
        //}

        //*op3++ = iOutPort;
        //produce(2, 1);

        iOutPort ++;
        iOutPort &= 0x1;

        iOutLength = (nTraceBackLength + nTraceBackLength)  * viterbi_rate_inv;

        while (noutput(iOutPort) < iOutLength)
        {
          //printf("out buf full when switch to port %d\n", iOutPort);
          //break;
          _mm_pause();
        }
        produce(iOutPort, iOutLength);
      }
    }

    consume(0, nOutTotal);



    //printf("vit disp=: port: %d, out: %d\n", iOutPort, nOutCount);
    return true;
  }
};

// parallel viterbi dispatcher
DEFINE_BLOCK(b_parallel_viterbi64_1v3, 1, 4)
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

    nTracebackSoftbits = (nTraceBackLength + nTraceBackOutput + nTraceBackLength) * viterbi_rate_inv;

    iOutPort = 0;
    iOutLength = 0;
  }


  BLOCK_RESET
  {
    iOutPort = 0;
  }
  //////////////////////////////////////////////////////////////////////////

  BLOCK_WORK
  {
    auto nInputSoftBits = ninput(0);
    if (nInputSoftBits < 1) return false;

    auto ip  = _$<uint8>(0);
    auto op1 = $_<uint8>(0); // data port
    auto op2 = $_<uint8>(1); // data port
    auto op3 = $_<uint8>(2); // data port
    auto op4 = $_<uint8>(3); // control port

    uint8* op[] = {op1, op2, op3};

    // min-schedule
#if 0
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
#endif

    auto nspace1 = noutput(0);
    auto nspace2 = noutput(1);
    auto nspace3 = noutput(2);
    auto nspace4 = noutput(3);// control port

    uint32 nspaces[] = {nspace1, nspace2, nspace3, nspace4};

    //memcpy(op[iOutPort], ip, sizeof(uint8) * nTracebackBlockBits);

    int nOutTotal = 0;
    while (nInputSoftBits > 0)
    {
      int nLeft = (int)nTracebackSoftbits - iOutLength;
      int nOut  = min(nLeft, nInputSoftBits);

      int nbufsize = noutput(iOutPort);
      nOut         = min(nOut, nbufsize);

      produce(iOutPort, nOut);

      nOutTotal += nOut;
      iOutLength += nOut;
      nInputSoftBits -= nOut;

      //printf("vit source produce %d @ %d, %d\n", nOut, iOutPort, iOutLength);

      if (iOutLength == nTracebackSoftbits)
      {
        iOutPort ++;
        iOutPort %= 3;

        iOutLength = (nTraceBackLength + nTraceBackLength)  * viterbi_rate_inv;

        while (noutput(iOutPort) < iOutLength)
        {
          //printf("out buf full when switch to port %d\n", iOutPort);
          //break;
          _mm_pause();
        }
        produce(iOutPort, iOutLength);
      }
    }

    consume(0, nOutTotal);

    //printf("vit disp=: port: %d\n", iOutPort);
    return true;
  }
};

// parallel viterbi dispatcher
DEFINE_BLOCK(b_parallel_viterbi64_1v4, 1, 5)
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

    nTracebackSoftbits = (nTraceBackLength + nTraceBackOutput + nTraceBackLength) * viterbi_rate_inv;

    iOutPort = 0;
    iOutLength = 0;
  }


  BLOCK_RESET
  {
    iOutPort = 0;
  }
  //////////////////////////////////////////////////////////////////////////

  BLOCK_WORK
  {
    auto nInputSoftBits = ninput(0);
    if (nInputSoftBits < 1) return false;

    auto ip  = _$<uint8>(0);
    auto op1 = $_<uint8>(0); // data port
    auto op2 = $_<uint8>(1); // data port
    auto op3 = $_<uint8>(2); // data port
    auto op4 = $_<uint8>(3); // data port
    auto op5 = $_<uint8>(4); // control port

    uint8* op[] = {op1, op2, op3, op4};

    auto nspace1 = noutput(0);
    auto nspace2 = noutput(1);
    auto nspace3 = noutput(2);
    auto nspace4 = noutput(3);
    auto nspace5 = noutput(4);

    uint32 nspaces[] = {nspace1, nspace2, nspace3, nspace4};

    //memcpy(op[iOutPort], ip, sizeof(uint8) * nTracebackBlockBits);

    int nOutTotal = 0;
    while (nInputSoftBits > 0)
    {
      int nLeft = (int)nTracebackSoftbits - iOutLength;
      int nOut  = min(nLeft, nInputSoftBits);

      int nbufsize = noutput(iOutPort);
      nOut         = min(nOut, nbufsize);

      produce(iOutPort, nOut);

      nOutTotal += nOut;
      iOutLength += nOut;
      nInputSoftBits -= nOut;

      if (iOutLength == nTracebackSoftbits)
      {
        iOutPort ++;
        iOutPort %= 4;

        iOutLength = (nTraceBackLength + nTraceBackLength) * viterbi_rate_inv;

        while (noutput(iOutPort) < iOutLength)
        {
          //printf("out buf full when switch to port %d\n", iOutPort);
          //break;
          _mm_pause();
        }
        produce(iOutPort, iOutLength);
      }
    }

    consume(0, nOutTotal);

    //printf("vit disp=: port: %d\n", iOutPort);
    return true;
  }
};

// parallel viterbi dispatcher
DEFINE_BLOCK(b_parallel_viterbi64_1v5, 1, 6)
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

    nTracebackSoftbits = (nTraceBackLength + nTraceBackOutput + nTraceBackLength) * viterbi_rate_inv;

    iOutPort = 0;
    iOutLength = 0;
  }


  BLOCK_RESET
  {
    iOutPort = 0;
  }
  //////////////////////////////////////////////////////////////////////////

  BLOCK_WORK
  {
    auto nInputSoftBits = ninput(0);
    if (nInputSoftBits < 1) return false;

    auto ip  = _$<uint8>(0);
    auto op1 = $_<uint8>(0); // data port
    auto op2 = $_<uint8>(1); // data port
    auto op3 = $_<uint8>(2); // data port
    auto op4 = $_<uint8>(3); // data port
    auto op5 = $_<uint8>(4); // data port

    uint8* op[] = {op1, op2, op3, op4, op5};

    auto nspace1 = noutput(0);
    auto nspace2 = noutput(1);
    auto nspace3 = noutput(2);
    auto nspace4 = noutput(3);
    auto nspace5 = noutput(4);

    uint32 nspaces[] = {nspace1, nspace2, nspace3, nspace4, nspace5};

    //memcpy(op[iOutPort], ip, sizeof(uint8) * nTracebackBlockBits);

    int nOutTotal = 0;
    while (nInputSoftBits > 0)
    {
      int nLeft = (int)nTracebackSoftbits - iOutLength;
      int nOut  = min(nLeft, nInputSoftBits);

      int nbufsize = noutput(iOutPort);
      nOut         = min(nOut, nbufsize);

      produce(iOutPort, nOut);

      nOutTotal += nOut;
      iOutLength += nOut;
      nInputSoftBits -= nOut;

      if (iOutLength == nTracebackSoftbits)
      {
        iOutPort ++;
        iOutPort %= 5;

        iOutLength = (nTraceBackLength + nTraceBackLength) * viterbi_rate_inv;

        while (noutput(iOutPort) < iOutLength)
        {
          //printf("out buf full when switch to port %d\n", iOutPort);
          //break;
          _mm_pause();
        }
        produce(iOutPort, iOutLength);
      }
    }

    consume(0, nOutTotal);

    //printf("vit disp=: port: %d\n", iOutPort);
    return true;
  }
};


//////////////////////////////////////////////////////////////////////////



DEFINE_BLOCK(b_viterbi_sink_2v1, 3, 1)
{
  size_t nSegmentSize;

  int nTotalDecodedBits;
  int  nDecodedBits;
  tick_count tstart, tend;
  size_t   nOutStat[2];
  size_t   nOutStatCnt;

  size_t   iPort;

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

    nOutStat[0] = nOutStat[1] = 0;
    nOutStatCnt = 0;

    iPort = 0;
  }



  BLOCK_WORK
  {
    auto nin1 = ninput(0);
    auto nin2 = ninput(1);

    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto ip3 = _$<uint8>(2);

    uint8 * ip[] = {ip1, ip2, ip3};

    auto op  = $_<uint8>(0);

    while (ninput(iPort) > nSegmentSize)
    {
      // read from control port to get the data port

      //nOutStat[iPort]++;
      //nOutStatCnt++;
      //if (nOutStatCnt % 100 == 0)
      //{
      //  printf("vit combiner : [0]=%d, [1]=%d\n", nOutStat[0], nOutStat[1]);
      //}

      //printf("vit combiner: port: %d, len: %d\n", iport, nin);
#if 0
      printf("vit combiner: port: %d, len: %d\n", iport, nSegmentSize);
      for (int k = 0; k < nSegmentSize; k++)
      {
        printf(" %02X ", ip[iport][k]);
      }
      printf("\n");
#endif


      //memcpy(op, ip[iport], sizeof(uint8) * nSegmentSize);

      produce(0, nSegmentSize);
      consume(iPort, nSegmentSize);

      nDecodedBits += nSegmentSize * 8;
      nTotalDecodedBits += nSegmentSize * 8;

      iPort++;
      iPort &= 0x1;
    }

    tick_count tdif;

    tend = tick_count::now();
    tdif = tend - tstart;
    if (tdif.s() > 2.0)
    {
      double rate = nDecodedBits / tdif.us();

      printf("dT %f Mbps, b=%d, bt=%d, t=%f ms\n", rate, nDecodedBits, nTotalDecodedBits, tdif.ms());

      printf("** %d, %d, %d\n", ninput(0), ninput(1), ninput(2));

      nDecodedBits = 0;
      tstart = tend;
    }

    return true;
  }
};


DEFINE_BLOCK(b_viterbi_sink_3v1, 4, 1)
{
  size_t nSegmentSize;

  int nTotalDecodedBits;
  int  nDecodedBits;
  tick_count tstart, tend;
  size_t   nOutStat[2];
  size_t   nOutStatCnt;

  size_t   iPort;

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

    nOutStat[0] = nOutStat[1] = 0;
    nOutStatCnt = 0;

    iPort = 0;
  }



  BLOCK_WORK
  {
    auto nin1 = ninput(0);
    auto nin2 = ninput(1);

    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto ip3 = _$<uint8>(2);

    uint8 * ip[] = {ip1, ip2, ip3};

    auto op  = $_<uint8>(0);

    while (ninput(iPort) > nSegmentSize)
    {
      //memcpy(op, ip[iport], sizeof(uint8) * nSegmentSize);

      produce(0, nSegmentSize);
      consume(iPort, nSegmentSize);

      nDecodedBits += nSegmentSize * 8;
      nTotalDecodedBits += nSegmentSize * 8;

      iPort++;
      iPort %= 3;
    }

    tick_count tdif;

    tend = tick_count::now();
    tdif = tend - tstart;
    if (tdif.s() > 2.0)
    {
      double rate = nDecodedBits / tdif.us();

      printf("dT %f Mbps, b=%d, bt=%d, t=%f ms\n", rate, nDecodedBits, nTotalDecodedBits, tdif.ms());

      printf("** %d, %d, %d\n", ninput(0), ninput(1), ninput(2));

      nDecodedBits = 0;
      tstart = tend;
    }

    return true;
  }
};

DEFINE_BLOCK(b_viterbi_sink_4v1, 5, 1)
{
  size_t nSegmentSize;

  int nTotalDecodedBits;
  int  nDecodedBits;
  tick_count tstart, tend;
  size_t   nOutStat[2];
  size_t   nOutStatCnt;

  size_t   iPort;

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

    nOutStat[0] = nOutStat[1] = 0;
    nOutStatCnt = 0;

    iPort = 0;
  }



  BLOCK_WORK
  {
    auto nin1 = ninput(0);
    auto nin2 = ninput(1);

    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto ip3 = _$<uint8>(2);
    auto ip4 = _$<uint8>(3);

    uint8 * ip[] = {ip1, ip2, ip3, ip4};

    auto op  = $_<uint8>(0);

    while (ninput(iPort) > nSegmentSize)
    {
      //memcpy(op, ip[iport], sizeof(uint8) * nSegmentSize);

      produce(0, nSegmentSize);
      consume(iPort, nSegmentSize);

      nDecodedBits += nSegmentSize * 8;
      nTotalDecodedBits += nSegmentSize * 8;

      iPort++;
      iPort %= 4;
    }

    tick_count tdif;

    tend = tick_count::now();
    tdif = tend - tstart;
    if (tdif.s() > 2.0)
    {
      double rate = nDecodedBits / tdif.us();

      printf("dT %f Mbps, b=%d, bt=%d, t=%f ms\n", rate, nDecodedBits, nTotalDecodedBits, tdif.ms());

      printf("** %d, %d, %d\n", ninput(0), ninput(1), ninput(2));

      nDecodedBits = 0;
      tstart = tend;
    }

    return true;
  }
};

DEFINE_BLOCK(b_viterbi_sink_5v1, 6, 1)
{
  size_t nSegmentSize;

  int nTotalDecodedBits;
  int  nDecodedBits;
  tick_count tstart, tend;
  size_t   nOutStat[2];
  size_t   nOutStatCnt;

  size_t   iPort;

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

    nOutStat[0] = nOutStat[1] = 0;
    nOutStatCnt = 0;

    iPort = 0;
  }



  BLOCK_WORK
  {
    auto nin1 = ninput(0);
    auto nin2 = ninput(1);

    auto ip1 = _$<uint8>(0);
    auto ip2 = _$<uint8>(1);
    auto ip3 = _$<uint8>(2);
    auto ip4 = _$<uint8>(3);

    uint8 * ip[] = {ip1, ip2, ip3, ip4};

    auto op  = $_<uint8>(0);

    while (ninput(iPort) > nSegmentSize)
    {
      //memcpy(op, ip[iport], sizeof(uint8) * nSegmentSize);

      produce(0, nSegmentSize);
      consume(iPort, nSegmentSize);

      nDecodedBits += nSegmentSize * 8;
      nTotalDecodedBits += nSegmentSize * 8;

      iPort++;
      iPort %= 5;
    }

    tick_count tdif;

    tend = tick_count::now();
    tdif = tend - tstart;
    if (tdif.s() > 2.0)
    {
      double rate = nDecodedBits / tdif.us();

      printf("dT %f Mbps, b=%d, bt=%d, t=%f ms\n", rate, nDecodedBits, nTotalDecodedBits, tdif.ms());

      printf("** %d, %d, %d\n", ninput(0), ninput(1), ninput(2));

      nDecodedBits = 0;
      tstart = tend;
    }

    return true;
  }
};
