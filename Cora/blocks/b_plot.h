#pragma once
#include "dsp_draw.h"

DEFINE_BLOCK(b_plot_1v, 1, 0)
{
  BLOCK_INIT
  {
  }
  v_i vpower[7];
  v_i vfftpower[7];

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

    PlotLine("HW Energy", (int*)&vpower, 4 * 7);

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