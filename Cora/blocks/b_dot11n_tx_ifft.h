#pragma once

#include "_fft_r4dif.h"
#include "_ifft_r4dif.h"


// TX IFFT128 works on dot11n_tx_symbol directly
DEFINE_BLOCK(b_dot11n_tx_ifft_128_1v1, 1, 1)
{
#if enable_draw
  dsp_draw_window* m_draw;

  BLOCK_INIT
  {
    m_draw = new dsp_draw_window("b_dot11n_tx_ifft_128_1v1", 0, 0, 400, 400);
  }
#endif

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<dot11n_tx_symbol>(0);
    auto op = $_<dot11n_tx_symbol>(0);

#if enable_draw
    m_draw->DrawSqrt((complex16*)ip->data, dot11n_tx_symbol::ntotal);
#endif

    IFFT<128>(reinterpret_cast<vcs *>(ip->vsubcarriers), reinterpret_cast<vcs *>(op->vsubcarriers));



    consume(0, 1);
    produce(0, 1);
    return true;
  }
};