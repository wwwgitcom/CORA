#pragma once

typedef complex16 MIMO_2x2_H[2][128];

DEFINE_BLOCK(b_dot11_mimo_channel_compensator_2v2, 2, 2)
{
  _global_(MIMO_2x2_H, dot11n_2x2_channel_inv);
#if enable_draw
  dsp_draw_window* m_draw1;
  dsp_draw_window* m_draw2;
#endif
  BLOCK_INIT
  {
#if enable_draw
    m_draw1 = new dsp_draw_window("dot11 2x2 mimo channel compensator: 1", 0, 400, 400, 400);
    m_draw2 = new dsp_draw_window("dot11 2x2 mimo channel compensator: 2", 400, 400, 400, 400);
#endif
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 16) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);

    auto ipc1 = reinterpret_cast<complex16*>(ip1);
    auto ipc2 = reinterpret_cast<complex16*>(ip2);
    
    auto op1 = $_<v_cs>(0);
    auto op2 = $_<v_cs>(1);

    auto opc1 = reinterpret_cast<complex16*>(op1);
    auto opc2 = reinterpret_cast<complex16*>(op2);

    MIMO_2x2_H& mimo_channel_2x2 = *dot11n_2x2_channel_inv;

    const v_cs vMulMask = VMASK::__0x80000001800000018000000180000001<v_cs>();
    v_ci vcomp1[2], vcomp2[2];

    for (int i = 0; i < 64; i += 4)
    {
      v_cs &vinvh11 = (v_cs&)mimo_channel_2x2[0][i];
      v_cs &vinvh12 = (v_cs&)mimo_channel_2x2[0][i + 64];
      v_cs &vinvh21 = (v_cs&)mimo_channel_2x2[1][i];
      v_cs &vinvh22 = (v_cs&)mimo_channel_2x2[1][i + 64];
      v_cs &y1      = (v_cs&)ipc1[i];
      v_cs &y2      = (v_cs&)ipc2[i];
      v_cs& x1      = (v_cs&)opc1[i];
      v_cs& x2      = (v_cs&)opc2[i];

      v_mul2ci(vinvh11, y1, vMulMask, vcomp1[0], vcomp1[1]);
      v_mul2ci(vinvh12, y2, vMulMask, vcomp2[0], vcomp2[1]);

      vcomp1[0] = v_add(vcomp1[0], vcomp2[0]);
      vcomp1[1] = v_add(vcomp1[1], vcomp2[1]);

      vcomp1[0] = vcomp1[0].v_shift_right_arithmetic(9);
      vcomp1[1] = vcomp1[1].v_shift_right_arithmetic(9);

      x1 = v_convert2cs(vcomp1[0], vcomp1[1]);

      v_mul2ci(vinvh21, y1, vMulMask, vcomp1[0], vcomp1[1]);
      v_mul2ci(vinvh22, y2, vMulMask, vcomp2[0], vcomp2[1]);

      vcomp1[0] = v_add(vcomp1[0], vcomp2[0]);
      vcomp1[1] = v_add(vcomp1[1], vcomp2[1]);

      vcomp1[0] = vcomp1[0].v_shift_right_arithmetic(9);
      vcomp1[1] = vcomp1[1].v_shift_right_arithmetic(9);

      x2 = v_convert2cs(vcomp1[0], vcomp1[1]);
    }

#if enable_draw
    opc1[0] = 0;
    for (int i = 29; i < 64 - 28; i++)
    {
      opc1[i] = 0;
    }
    
    //m_draw1->DrawSqrtShift(opc1, 64);
    m_draw1->DrawScatter(opc1, 64);
    m_draw2->DrawScatter(opc2, 64);
#endif

    consume_each(16);
    produce_each(16);
    return true;
  }
};

//////////////////////////////////////////////////////////////////////////
#define enable_4x4_channel_compensate_draw 0

typedef complex16 MIMO_4x4_H[4][256];

DEFINE_BLOCK(b_dot11_mimo_channel_compensator_4v4, 4, 4)
{
  _global_(MIMO_4x4_H, dot11n_4x4_channel_inv);
#if enable_4x4_channel_compensate_draw
  dsp_draw_window* m_draw1;
  dsp_draw_window* m_draw2;
  dsp_draw_window* m_draw3;
  dsp_draw_window* m_draw4;
#endif
  BLOCK_INIT
  {
#if enable_4x4_channel_compensate_draw
    m_draw1 = new dsp_draw_window("y1", 0, 400, 400, 400);
    m_draw2 = new dsp_draw_window("y2", 400, 400, 400, 400);
    m_draw3 = new dsp_draw_window("y3", 800, 400, 400, 400);
    m_draw4 = new dsp_draw_window("y4", 1200, 400, 400, 400);
#endif
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 16) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    auto ipc1 = reinterpret_cast<complex16*>(ip1);
    auto ipc2 = reinterpret_cast<complex16*>(ip2);
    auto ipc3 = reinterpret_cast<complex16*>(ip3);
    auto ipc4 = reinterpret_cast<complex16*>(ip4);

    auto op1 = $_<v_cs>(0);
    auto op2 = $_<v_cs>(1);
    auto op3 = $_<v_cs>(2);
    auto op4 = $_<v_cs>(3);

    auto opc1 = reinterpret_cast<complex16*>(op1);
    auto opc2 = reinterpret_cast<complex16*>(op2);
    auto opc3 = reinterpret_cast<complex16*>(op3);
    auto opc4 = reinterpret_cast<complex16*>(op4);

    MIMO_4x4_H& H_Inv = *dot11n_4x4_channel_inv;

    const v_cs vMulMask = VMASK::__0x80000001800000018000000180000001<v_cs>();
    v_ci vcomp1[2], vcomp2[2], vcomp3[2], vcomp4[2];

    for (int i = 0; i < 64; i += 4)
    {
      v_cs &vinvh11 = (v_cs&)H_Inv[0][i];
      v_cs &vinvh12 = (v_cs&)H_Inv[0][i + 64];
      v_cs &vinvh13 = (v_cs&)H_Inv[0][i + 128];
      v_cs &vinvh14 = (v_cs&)H_Inv[0][i + 192];

      v_cs &vinvh21 = (v_cs&)H_Inv[1][i];
      v_cs &vinvh22 = (v_cs&)H_Inv[1][i + 64];
      v_cs &vinvh23 = (v_cs&)H_Inv[1][i + 128];
      v_cs &vinvh24 = (v_cs&)H_Inv[1][i + 192];

      v_cs &vinvh31 = (v_cs&)H_Inv[2][i];
      v_cs &vinvh32 = (v_cs&)H_Inv[2][i + 64];
      v_cs &vinvh33 = (v_cs&)H_Inv[2][i + 128];
      v_cs &vinvh34 = (v_cs&)H_Inv[2][i + 192];

      v_cs &vinvh41 = (v_cs&)H_Inv[3][i];
      v_cs &vinvh42 = (v_cs&)H_Inv[3][i + 64];
      v_cs &vinvh43 = (v_cs&)H_Inv[3][i + 128];
      v_cs &vinvh44 = (v_cs&)H_Inv[3][i + 192];

      v_cs &y1      = (v_cs&)ipc1[i];
      v_cs &y2      = (v_cs&)ipc2[i];
      v_cs &y3      = (v_cs&)ipc3[i];
      v_cs &y4      = (v_cs&)ipc4[i];

      v_cs& x1      = (v_cs&)opc1[i];
      v_cs& x2      = (v_cs&)opc2[i];
      v_cs& x3      = (v_cs&)opc3[i];
      v_cs& x4      = (v_cs&)opc4[i];

      // x1
      v_mul2ci(vinvh11, y1, vMulMask, vcomp1[0], vcomp1[1]);
      v_mul2ci(vinvh12, y2, vMulMask, vcomp2[0], vcomp2[1]);
      v_mul2ci(vinvh13, y3, vMulMask, vcomp3[0], vcomp3[1]);
      v_mul2ci(vinvh14, y4, vMulMask, vcomp4[0], vcomp4[1]);

      vcomp1[0] = v_add(v_add(vcomp1[0], vcomp2[0]), v_add(vcomp3[0], vcomp4[0]));
      vcomp1[1] = v_add(v_add(vcomp1[1], vcomp2[1]), v_add(vcomp3[1], vcomp4[1]));

      vcomp1[0] = vcomp1[0].v_shift_right_arithmetic(9);
      vcomp1[1] = vcomp1[1].v_shift_right_arithmetic(9);

      x1 = v_convert2cs(vcomp1[0], vcomp1[1]);

      // x2
      v_mul2ci(vinvh21, y1, vMulMask, vcomp1[0], vcomp1[1]);
      v_mul2ci(vinvh22, y2, vMulMask, vcomp2[0], vcomp2[1]);
      v_mul2ci(vinvh23, y3, vMulMask, vcomp3[0], vcomp3[1]);
      v_mul2ci(vinvh24, y4, vMulMask, vcomp4[0], vcomp4[1]);

      vcomp1[0] = v_add(v_add(vcomp1[0], vcomp2[0]), v_add(vcomp3[0], vcomp4[0]));
      vcomp1[1] = v_add(v_add(vcomp1[1], vcomp2[1]), v_add(vcomp3[1], vcomp4[1]));

      vcomp1[0] = vcomp1[0].v_shift_right_arithmetic(9);
      vcomp1[1] = vcomp1[1].v_shift_right_arithmetic(9);

      x2 = v_convert2cs(vcomp1[0], vcomp1[1]);

      // x3
      v_mul2ci(vinvh31, y1, vMulMask, vcomp1[0], vcomp1[1]);
      v_mul2ci(vinvh32, y2, vMulMask, vcomp2[0], vcomp2[1]);
      v_mul2ci(vinvh33, y3, vMulMask, vcomp3[0], vcomp3[1]);
      v_mul2ci(vinvh34, y4, vMulMask, vcomp4[0], vcomp4[1]);

      vcomp1[0] = v_add(v_add(vcomp1[0], vcomp2[0]), v_add(vcomp3[0], vcomp4[0]));
      vcomp1[1] = v_add(v_add(vcomp1[1], vcomp2[1]), v_add(vcomp3[1], vcomp4[1]));

      vcomp1[0] = vcomp1[0].v_shift_right_arithmetic(9);
      vcomp1[1] = vcomp1[1].v_shift_right_arithmetic(9);

      x3 = v_convert2cs(vcomp1[0], vcomp1[1]);

      // x4
      v_mul2ci(vinvh41, y1, vMulMask, vcomp1[0], vcomp1[1]);
      v_mul2ci(vinvh42, y2, vMulMask, vcomp2[0], vcomp2[1]);
      v_mul2ci(vinvh43, y3, vMulMask, vcomp3[0], vcomp3[1]);
      v_mul2ci(vinvh44, y4, vMulMask, vcomp4[0], vcomp4[1]);

      vcomp1[0] = v_add(v_add(vcomp1[0], vcomp2[0]), v_add(vcomp3[0], vcomp4[0]));
      vcomp1[1] = v_add(v_add(vcomp1[1], vcomp2[1]), v_add(vcomp3[1], vcomp4[1]));

      vcomp1[0] = vcomp1[0].v_shift_right_arithmetic(9);
      vcomp1[1] = vcomp1[1].v_shift_right_arithmetic(9);

      x4 = v_convert2cs(vcomp1[0], vcomp1[1]);
    }

#if enable_4x4_channel_compensate_draw
    opc1[0] = opc2[0] = opc3[0] = opc4[0] = 0;
    for (int i = 29; i < 64 - 28; i++)
    {
      opc1[i] = opc2[i] = opc3[i] = opc4[i] = 0;
    }

    //m_draw1->DrawSqrtShift(opc1, 64);
    m_draw1->DrawSqrtShift(opc1, 64);
    m_draw2->DrawSqrtShift(opc2, 64);
    m_draw3->DrawSqrtShift(opc3, 64);
    m_draw4->DrawSqrtShift(opc4, 64);
#endif

#if enable_dbgplot
    PlotDots("RX 1", opc1, 64);
    PlotDots("RX 2", opc2, 64);
    PlotDots("RX 3", opc3, 64);
    PlotDots("RX 4", opc4, 64);
#endif

    consume_each(16);
    produce_each(16);
    return true;
  }
};



DEFINE_BLOCK(b_dot11_mimo_channel_compensator_4v1, 4, 1)
{
  _global_(MIMO_4x4_H, dot11n_4x4_channel_inv);
  _local_(int, iss, 0);

  BLOCK_INIT
  {
    auto v = $["iss"];
    if (!v.empty())
    {
      *iss = atoi(v.c_str());
    }
  }

  void fence()
  {
    consume_each(16);
  }

  BLOCK_WORK
  {
    trace();
    
    auto n = ninput(0);
    if (n < 16) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    auto ipc1 = reinterpret_cast<complex16*>(ip1);
    auto ipc2 = reinterpret_cast<complex16*>(ip2);
    auto ipc3 = reinterpret_cast<complex16*>(ip3);
    auto ipc4 = reinterpret_cast<complex16*>(ip4);

    auto op1 = $_<v_cs>(0);

    auto opc1 = reinterpret_cast<complex16*>(op1);

    MIMO_4x4_H& H_Inv = *dot11n_4x4_channel_inv;

    const v_cs vMulMask = VMASK::__0x80000001800000018000000180000001<v_cs>();
    v_ci vcomp1[2], vcomp2[2], vcomp3[2], vcomp4[2];

    for (int i = 0; i < 64; i += 4)
    {
      v_cs &vinvh11 = (v_cs&)H_Inv[*iss][i];
      v_cs &vinvh12 = (v_cs&)H_Inv[*iss][i + 64];
      v_cs &vinvh13 = (v_cs&)H_Inv[*iss][i + 128];
      v_cs &vinvh14 = (v_cs&)H_Inv[*iss][i + 192];
      
      v_cs &y1      = (v_cs&)ipc1[i];
      v_cs &y2      = (v_cs&)ipc2[i];
      v_cs &y3      = (v_cs&)ipc3[i];
      v_cs &y4      = (v_cs&)ipc4[i];

      v_cs& x1      = (v_cs&)opc1[i];

      // x1
      v_mul2ci(vinvh11, y1, vMulMask, vcomp1[0], vcomp1[1]);
      v_mul2ci(vinvh12, y2, vMulMask, vcomp2[0], vcomp2[1]);
      v_mul2ci(vinvh13, y3, vMulMask, vcomp3[0], vcomp3[1]);
      v_mul2ci(vinvh14, y4, vMulMask, vcomp4[0], vcomp4[1]);

      vcomp1[0] = v_add(v_add(vcomp1[0], vcomp2[0]), v_add(vcomp3[0], vcomp4[0]));
      vcomp1[1] = v_add(v_add(vcomp1[1], vcomp2[1]), v_add(vcomp3[1], vcomp4[1]));

      vcomp1[0] = vcomp1[0].v_shift_right_arithmetic(9);
      vcomp1[1] = vcomp1[1].v_shift_right_arithmetic(9);

      x1 = v_convert2cs(vcomp1[0], vcomp1[1]);      
    }
    produce_each(16);
    return true;
  }
};