#pragma once

typedef complex16 MIMO_2x2_H[2][128];

DEFINE_BLOCK(b_dot11_mimo_channel_compensator_2v2, 2, 2)
{
  _global_(MIMO_2x2_H, dot11n_2x2_channel);

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

    MIMO_2x2_H& mimo_channel_2x2 = *dot11n_2x2_channel;

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

    consume_each(16);
    produce_each(16);
    return true;
  }
};