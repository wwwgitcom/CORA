#pragma once

// feedback residual frequency offset to frequency compensator

__forceinline short dot11_pilot_tracking(complex16* pc)
{
  short th1 = dsp_math::atan(pc[64 - 21].re, pc[64 - 21].im);
  short th2 = dsp_math::atan(pc[64 - 07].re, pc[64 - 07].im);
  short th3 = dsp_math::atan(pc[07].re, pc[07].im);
  short th4 = dsp_math::atan(pc[21].re, pc[21].im);

  short ThisTheta = (th1 + th2 + th3 + th4) >> 2;

  return ThisTheta;
}

DEFINE_BLOCK(b_dot11_pilot_tracking_1v, 1, 0)
{
  _global_(v_s, vfo_theta_i);

  BLOCK_WORK
  {
    auto n = ninput(0);

    if (n < 16) return false;

    auto ip = _$<v_cs>(0);
    complex16* ipc = (complex16*)ip;

    short theta = dot11_pilot_tracking(ipc);
    v_s v_theta;
    v_theta.v_setall(theta);

    (*vfo_theta_i) = v_add((*vfo_theta_i), v_theta);

    return true;
  }
};

DEFINE_BLOCK(b_dot11_pilot_tracking_2v, 2, 0)
{
  _global_(v_s, vfo_theta_i);

  BLOCK_WORK
  {
    auto n = ninput(0);

    if (n < 16) return false;

    auto ip1 = _$<v_cs>(0);
    complex16* ipc1 = (complex16*)ip1;
    auto ip2 = _$<v_cs>(1);
    complex16* ipc2 = (complex16*)ip2;

    short theta1 = dot11_pilot_tracking(ipc1);
    short theta2 = dot11_pilot_tracking(ipc2);
    short theta  = ( (theta1 + theta2) >> 1 );

    v_s v_theta;
    v_theta.v_setall(theta);
    
    (*vfo_theta_i) = v_add((*vfo_theta_i), v_theta);
    return true;
  }
};