#pragma once

DEFINE_BLOCK(b_dot11n_add_cp_1v1, 1, 1)
{

#if enable_draw
  dsp_draw_window* m_draw;

  BLOCK_INIT
  {
    m_draw = new dsp_draw_window("b_dot11n_add_cp_1v1", 0, 0, 400, 400);
  }
#endif

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<dot11n_tx_symbol>(0);
    auto op = $_<dot11n_tx_symbol>(0);

    ip->assign_with_cp(*op);
    
    consume(0, 1);
    produce(0, 1);

#if enable_draw
    m_draw->DrawSqrtShift((complex16*)op, dot11n_tx_symbol::ntotal);
#endif

    return true;
  }
};