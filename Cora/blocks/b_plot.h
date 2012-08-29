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
      vpower[i] = ip[i].v_sqr2i();
    }

    PlotLine("HW Energy", (int*)&vpower, 4 * 7);

    consume(0, 7);

    return true;
  }
};