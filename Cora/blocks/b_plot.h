#pragma once
#include "dsp_draw.h"

DEFINE_BLOCK(b_plot_1v, 1, 0)
{
  v_i vpower[7];
  v_i vfftpower[7];

  BLOCK_INIT
  {
  }
  
  BLOCK_INPUT_EVENT_HANDLER
  {
    dsp_console::error("evt: %p : %u\n", this, $.Event.KeyEvent.uChar);
  }


  BLOCK_WORK
  {
    auto n = ninput(0);

    //printf("Read a signal block...%d v_cs", n);

    if (n < 7)
    {
      return false;
    }
    auto ip = _$<v_cs>(0);
    
    for (int i = 0; i < 7; i++)
    {
      v_cs vtemp = ip[i].v_shift_right_arithmetic(1);
      vpower[i] = vtemp.v_sqr2i();
    }

    static int ncount = 0;
#if enable_dbgplot
    HRESULT hr = PlotLine("Energy", (int*)&vpower, 4 * 7);

    
    ncount++;
    if (ncount % 1000000 == 0)
    {
      fprintf(stderr, "Call PlotLine %d times, hr = 0x%p\n", ncount, hr);
    }
#endif
#if 0

    complex16* pc = &ip[0][0];
    int* p = &vpower[0][0];

    for (int i = 0; i < 28; i++)
    {
      printf("%d \t %d, %d", p[i], pc[i].re, pc[i].im);

      if (p[i] < 0)
      {
        printf("----------------------------");
      }
      printf("\n");
    }
    printf("\n");
#endif

    consume(0, 7);

    return true;
  }
};


DEFINE_BLOCK(b_spectrum_plot_1v, 1, 0)
{
  static const int in_cnt = 1024;
  static const int vin_cnt = in_cnt / 4;

  v_i vfftpower[vin_cnt];
  v_cs vfft[vin_cnt];

  BLOCK_INIT
  {
  }

  BLOCK_INPUT_EVENT_HANDLER
  {
    
  }


  BLOCK_WORK
  {
    auto n = ninput(0);

    //printf("Read a signal block...%d v_cs", n);

    if (n < vin_cnt)
    {
      return false;
    }
    auto ip = _$<v_cs>(0);

    for (int i = 0; i < vin_cnt; i++)
    {
      v_cs vtemp = ip[i].v_shift_right_arithmetic(2);
      vfftpower[i] = vtemp.v_sqr2i();
    }

#if enable_dbgplot
    HRESULT hr = PlotLine("Energy", (int*)&vfftpower, in_cnt);
#endif

    FFT<in_cnt>(reinterpret_cast<vcs *>(ip), reinterpret_cast<vcs *>(vfft));
    for (int i = 0; i < vin_cnt / 2; i++)
    {
      v_cs vtemp = vfft[i].v_shift_right_arithmetic(2);
      vfftpower[i + vin_cnt / 2] = vtemp.v_sqr2i();
    }


    for (int i = 0; i < vin_cnt / 2; i++)
    {
      v_cs vtemp = vfft[i + vin_cnt / 2].v_shift_right_arithmetic(2);
      vfftpower[i] = vtemp.v_sqr2i();
    }

#if enable_dbgplot
    hr = PlotSpectrum("Spectrum", (int*)&vfftpower, in_cnt);
#endif

    consume(0, vin_cnt);

    return true;
  }
};