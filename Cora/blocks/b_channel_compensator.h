#pragma once

typedef Array<v_cs, 64> Dot11aChannelCoefficient;

DEFINE_BLOCK(b_dot11_siso_channel_compensator_1v1, 1, 1)
{
  _global_(Dot11aChannelCoefficient, dot11a_siso_channel);

  v_cs vmask;

  BLOCK_INIT
  {
    vmask = VMASK::__0x80000001800000018000000180000001<v_cs>();
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 16) return false;

    auto ip = _$<v_cs>(0);
    auto op = $_<v_cs>(0);

    v_ci vciout1, vciout2;
    
    auto channel_factor = *dot11a_siso_channel;

    for (int i = 0; i < 16; i++)
    {
      v_cs &vin   = (v_cs &)ip[i];
      v_cs &vcof  = (v_cs &)channel_factor[i];
      v_cs &vout  = (v_cs &)op[i];

      v_mul2ci(vin, vcof, vmask, vciout1, vciout2);

      vciout1 = vciout1.v_shift_right_arithmetic(9);
      vciout2 = vciout2.v_shift_right_arithmetic(9);

      vout        = v_convert2cs(vciout1, vciout2);
    }

    consume(0, 16);
    produce(0, 16);
  }
};

//////////////////////////////////////////////////////////////////////////
DEFINE_BLOCK(b_dot11_siso_channel_compensator_2v2, 2, 2)
{
  _global_(Dot11aChannelCoefficient, dot11a_siso_channel_1);
  _global_(Dot11aChannelCoefficient, dot11a_siso_channel_2);

  v_cs vmask;

  BLOCK_INIT
  {
    vmask = VMASK::__0x80000001800000018000000180000001<v_cs>();
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < 16) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(0);
    auto op1 = $_<v_cs>(0);
    auto op2 = $_<v_cs>(0);

    v_ci vciout1, vciout2;

    auto channel_factor = *dot11a_siso_channel_1;

    for (int i = 0; i < 16; i++)
    {
      v_cs &vin   = (v_cs &)ip1[i];
      v_cs &vcof  = (v_cs &)channel_factor[i];
      v_cs &vout  = (v_cs &)op1[i];

      v_mul2ci(vin, vcof, vmask, vciout1, vciout2);

      vciout1 = vciout1.v_shift_right_arithmetic(9);
      vciout2 = vciout2.v_shift_right_arithmetic(9);

      vout        = v_convert2cs(vciout1, vciout2);
    }

    channel_factor = *dot11a_siso_channel_2;

    for (int i = 0; i < 16; i++)
    {
      v_cs &vin   = (v_cs &)ip2[i];
      v_cs &vcof  = (v_cs &)channel_factor[i];
      v_cs &vout  = (v_cs &)op2[i];

      v_mul2ci(vin, vcof, vmask, vciout1, vciout2);

      vciout1 = vciout1.v_shift_right_arithmetic(9);
      vciout2 = vciout2.v_shift_right_arithmetic(9);

      vout        = v_convert2cs(vciout1, vciout2);
    }

    consume(0, 16);
    consume(1, 16);
    produce(0, 16);
    produce(1, 16);
    return true;
  }
};