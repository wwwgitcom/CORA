#pragma once

#include "b_perf_source.h"
#include "b_perf_sink.h"

typedef int TNULL;

template<typename TBlock, typename TInputItem, typename TOutputItem>
class TAutoPerf
{
public:
  TBlock& _block;
  vector<b_perf_source_v1*> producers;
  vector<b_perf_sink_v1*>   consumers;

  static const int PerfInputItemSize   = sizeof(TInputItem);
  static const int PerfInputItemCount  = 128 * 1024;
  static const int PerfOutputItemSize   = sizeof(TOutputItem);
  static const int PerfOutputItemCount  = 64 * 1024;

  static const int PerfRound      = 10;


  TAutoPerf(TBlock& block) : _block(block)
  {
    for (int i = 0; i < _block.ninput_port(); i++)
    {
      autoref block_from = create_block<b_perf_source_v1>();
      
      Channel::Create(PerfInputItemSize, PerfInputItemCount).from(block_from, 0).to(_block, i).random();
      
      producers.push_back(&block_from);
    }
    for (int i = 0; i < _block.noutput_port(); i++)
    {
      autoref block_to = create_block<b_perf_sink_v1>();

      auto nOutItemCount = PerfInputItemCount * _block.ninput_port();

      Channel::Create(PerfOutputItemSize, nOutItemCount).from(_block, i).to(block_to, 0);

      consumers.push_back(&block_to);
    }
  }

  void perf_work()
  {
    int graulity = 1;
    int round = PerfRound;

    printf("\nPerf %s <%s, %s>\n", typeid(TBlock).name(), typeid(TInputItem).name(), typeid(TOutputItem).name());

    for (int i = graulity; i < PerfInputItemCount - graulity; i <<= 1)
    {
      tick_count thistick = 0;
      tick_count sumtick  = 0;
      
      for (int r = 0; r < round; r++)
      {
        thistick = _perf_work(i, PerfInputItemCount);
        sumtick += thistick;
      }
      
      // generate sta. and show them to console
      printf("+-G=%d\n", i);
      for (auto it = producers.begin(); it != producers.end(); it++)
      {
        auto nout = *(**it).nout_sum;
        double doutrate = nout / (sumtick.us() / round);
        printf(" |>>T=%d, MIPS=%f\n", nout, doutrate);
      }

      for (auto it = consumers.begin(); it != consumers.end(); it++)
      {
        auto nout = *(**it).nin_sum;
        double doutrate = nout / (sumtick.us() / round);
        printf(" |<<T=%d, MIPS=%f\n", nout, doutrate);
      }
    }
  }


  void perf_source_work()
  {
    int graulity = 1;
    int total = PerfInputItemCount;
    int round = PerfRound;

    printf("Perf %s\n", typeid(TBlock).name());

    for (int i = graulity; i < total - graulity; i <<= 1)
    {
      //tick_count sumrate  = 0;
      //double avgrate  = 0;

      //sumrate = _perf_source_work();

      //avgrate = sumrate.us() / round;

      //printf("  G=%d, T=%d, MIPS=%f\n", i, total, avgrate);
    }
  }



  tick_count _perf_work(int iGranulity, int iTotal)
  {
    for (int i = producers.size() - 1; i >= 0 ; i--)
    {
      *(*producers[i]).nout_granulity = iGranulity;
      *(*producers[i]).nout_total     = iTotal;
      RESET(*producers[i]);
    }

    for (int i = consumers.size() - 1; i >= 0 ; i--)
    {
      RESET(*consumers[i]);
    }

    
    int icanwork = 0;

    tick_count tstart = tick_count::now();
    do 
    {
      icanwork = 0;

      
      // producers work once
      for (auto it = producers.rbegin(); it != producers.rend(); it++)
      {
        icanwork += (**it)( );
      }

      // block work once
      START(_block);

      for (auto rit = consumers.rbegin(); rit != consumers.rend(); rit++)
      {
        (**rit)();
      }
    } while (icanwork);
    tick_count tend = tick_count::now();
    tick_count tdif = tend - tstart + 1;

    return tdif;
  }

  double _perf_source_work()
  {
    tick_count tstart = tick_count::now();
    for (int r = 0; r < PerfRound; r++)
    {
      _block();
    }
    tick_count tend = tick_count::now();
    tick_count tdif = tend - tstart + 1;

    double drate = (double)(PerfRound * PerfItemSize) / tdif.us();

    return drate;
  }

};


//////////////////////////////////////////////////////////////////////////

#define AUTO_PERF_BLOCK(T, TInputItem, TOutputItem, ...) \
{\
  autoref block = create_block<T>(__VA_ARGS__);\
  autoref perf  = CreateObject<TAutoPerf<T, TInputItem, TOutputItem>>(block);\
  perf.perf_work();\
}

#define AUTO_PERF_SOURCE_BLOCK(T, TItem, ...) \
{\
  autoref block = create_block<T>(__VA_ARGS__);\
  autoref perf  = CreateObject<TAutoPerf<T, TInputItem, TOutputItem>>(block);\
  perf.perf_source_work();\
}