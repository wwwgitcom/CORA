#pragma once
#include "dsp_draw.h"

DEFINE_BLOCK(b_plot_complex16_1v, 1, 0)
{
  dsp_draw_window* m_pDraw;

  BLOCK_INIT
  {
    m_pDraw = new dsp_draw_window("title", 0, 0, 400, 400);
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 1)
    {
      return false;
    }
    auto ip = _$<v_cs>(0);
    complex16* ipc = reinterpret_cast<complex16*>(ip);

    m_pDraw->DrawSqrt(ipc, n * 4);

    return false;
  }
};