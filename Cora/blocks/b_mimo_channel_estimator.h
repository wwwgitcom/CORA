#pragma once


__declspec(selectany) v_align(16) v_cs::type _80211n_HTLTFMask[16] =
{
  //0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
  { 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF },
  { 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000 },
  { 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF },
  { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 },

  //1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  { 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 },
  { 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000 },
  { 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF },
  { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF },

  //0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1,
  { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF },
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
  { 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000 },
  { 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000 },

  //1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
  { 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 },
  { 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF },
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }
};




typedef complex16 MIMO_2x2_H[2][128];


DEFINE_BLOCK(b_mimo_channel_estimator_2v, 2, 0)
{
  _global_(MIMO_2x2_H, dot11n_2x2_channel);

  BLOCK_WORK
  {
    v_ci vtemp[4];

    v_ci vstar[2];
    v_q  vstarsqr[2];

    v_ci vcih1, vcih2;

    const v_cs vMulMask = VMASK::__0x80000001800000018000000180000001<v_cs>();
    const v_cs vNegMask = VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_cs>();

    const complex16* pHTLTFMask = &_80211n_HTLTFMask[0][0];

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);

    int n = ninput(0);
    if (n < 32) return false;

    auto ipc1 = (complex16*)ip1;
    auto ipc2 = (complex16*)ip2;

    MIMO_2x2_H& mimo_channel_2x2 = *dot11n_2x2_channel;

    int i;

    for (i = 0; i < 64; i += 4)
    {
      v_cs& vhtmsk = (v_cs&)pHTLTFMask[i];

      v_cs& v11    = (v_cs&)ipc1[i];
      v_cs& v12    = (v_cs&)ipc1[i + 64];
      v_cs& v21    = (v_cs&)ipc2[i];
      v_cs& v22    = (v_cs&)ipc2[i + 64];

      v_cs& vh11   = (v_cs&)ipc1[i];
      v_cs& vh12   = (v_cs&)ipc1[i + 64];
      v_cs& vh21   = (v_cs&)ipc2[i];
      v_cs& vh22   = (v_cs&)ipc2[i + 64];

      v_cs& vtemph = (v_cs&)vtemp[0];

      vtemph = v_subs(v11, v12);
      vtemph = vtemph.v_shift_right_arithmetic(1);
      vtemph = v_xor(vtemph, vhtmsk);
      vh11   = v_sub(vtemph, vhtmsk);

      vtemph = v_adds(v11, v12); 
      vtemph = vtemph.v_shift_right_arithmetic(1);
      vtemph = v_xor(vtemph, vhtmsk);
      vh12   = v_sub(vtemph, vhtmsk);

      vtemph = v_subs(v21, v22);
      vtemph = vtemph.v_shift_right_arithmetic(1);
      vtemph = v_xor(vtemph, vhtmsk);
      vh21   = v_sub(vtemph, vhtmsk);

      vtemph = v_adds(v21, v22); 
      vtemph = vtemph.v_shift_right_arithmetic(1);
      vtemph = v_xor(vtemph, vhtmsk);
      vh22   = v_sub(vtemph, vhtmsk);
    }

    for (i = 0; i < 64; i += 4)
    {
      v_cs& vh11   = (v_cs&)ipc1[i];
      v_cs& vh12   = (v_cs&)ipc1[i + 64];
      v_cs& vh21   = (v_cs&)ipc2[i];
      v_cs& vh22   = (v_cs&)ipc2[i + 64];

      v_mul2ci(vh11, vh22, vMulMask, vtemp[0], vtemp[1]);
      v_mul2ci(vh12, vh21, vMulMask, vtemp[2], vtemp[3]);

      vstar[0] = v_sub(vtemp[0], vtemp[2]);
      vstar[1] = v_sub(vtemp[1], vtemp[3]);

      vstarsqr[0] = vstar[0].v_sqr2q();
      vstarsqr[1] = vstar[1].v_sqr2q();

      // Add 1 to avoid divided by 0 exception
      vstarsqr[0] = v_sub(vstarsqr[0], (v_q&)vNegMask);
      vstarsqr[1] = v_sub(vstarsqr[1], (v_q&)vNegMask);
      //
      v_cs &vinvh11 = (v_cs&)mimo_channel_2x2[0][i];
      v_cs &vinvh12 = (v_cs&)mimo_channel_2x2[0][i + 64];
      v_cs &vinvh21 = (v_cs&)mimo_channel_2x2[1][i];
      v_cs &vinvh22 = (v_cs&)mimo_channel_2x2[1][i + 64];

      v_cq &vres1 = (v_cq&)vtemp[0];
      v_cq &vres2 = (v_cq&)vtemp[1];
      v_cq &vres3 = (v_cq&)vtemp[2];
      v_cq &vres4 = (v_cq&)vtemp[3];

      // - invh11
      vh22.v_convert2ci(vcih1, vcih2);

      v_conjmul2cq(vcih1, vstar[0], vres1, vres2);
      v_conjmul2cq(vcih2, vstar[1], vres3, vres4);

      vres1 = vres1.v_shift_left(16);
      vres2 = vres2.v_shift_left(16);
      vres3 = vres3.v_shift_left(16);
      vres4 = vres4.v_shift_left(16);

      vres1[0].re /= vstarsqr[0][0]; vres1[0].im /= vstarsqr[0][0];
      vres2[0].re /= vstarsqr[0][1]; vres2[0].im /= vstarsqr[0][1];
      vres3[0].re /= vstarsqr[1][0]; vres3[0].im /= vstarsqr[1][0];
      vres4[0].re /= vstarsqr[1][1]; vres4[0].im /= vstarsqr[1][1];

      ((v_ci&)vres1) = v_convert2ci_lo(vres1, vres2);
      ((v_ci&)vres3) = v_convert2ci_lo(vres3, vres4);

      v_cs &vout11 = (v_cs&)vres2;
      vout11       = v_convert2cs((v_ci&)vres1, (v_ci&)vres3);
      vinvh11      = vout11;

      // - invh12
      vh12.v_convert2ci(vcih1, vcih2);

      v_conjmul2cq(vcih1, vstar[0], vres1, vres2);
      v_conjmul2cq(vcih2, vstar[1], vres3, vres4);

      vres1 = vres1.v_shift_left(16);
      vres2 = vres2.v_shift_left(16);
      vres3 = vres3.v_shift_left(16);
      vres4 = vres4.v_shift_left(16);

      vres1[0].re /= vstarsqr[0][0]; vres1[0].im /= vstarsqr[0][0];
      vres2[0].re /= vstarsqr[0][1]; vres2[0].im /= vstarsqr[0][1];
      vres3[0].re /= vstarsqr[1][0]; vres3[0].im /= vstarsqr[1][0];
      vres4[0].re /= vstarsqr[1][1]; vres4[0].im /= vstarsqr[1][1];

      ((v_ci&)vres1) = v_convert2ci_lo(vres1, vres2);
      ((v_ci&)vres3) = v_convert2ci_lo(vres3, vres4);

      v_cs &vout12 = (v_cs&)vres2;
      vout12       = v_convert2cs((v_ci&)vres1, (v_ci&)vres3);
      vout12       = v_xor(vout12, vNegMask);
      vout12       = v_sub((v_cs&)vout12, (v_cs&)vNegMask);
      vinvh12      = vout12;

      // - invh21
      vh21.v_convert2ci(vcih1, vcih2);

      v_conjmul2cq(vcih1, vstar[0], vres1, vres2);
      v_conjmul2cq(vcih2, vstar[1], vres3, vres4);

      vres1 = vres1.v_shift_left(16);
      vres2 = vres2.v_shift_left(16);
      vres3 = vres3.v_shift_left(16);
      vres4 = vres4.v_shift_left(16);

      vres1[0].re /= vstarsqr[0][0]; vres1[0].im /= vstarsqr[0][0];
      vres2[0].re /= vstarsqr[0][1]; vres2[0].im /= vstarsqr[0][1];
      vres3[0].re /= vstarsqr[1][0]; vres3[0].im /= vstarsqr[1][0];
      vres4[0].re /= vstarsqr[1][1]; vres4[0].im /= vstarsqr[1][1];

      ((v_ci&)vres1) = v_convert2ci_lo(vres1, vres2);
      ((v_ci&)vres3) = v_convert2ci_lo(vres3, vres4);

      v_cs &vout21 = (v_cs&)vres2;
      vout21       = v_convert2cs((v_ci&)vres1, (v_ci&)vres3);
      vout21       = v_xor(vout21, vNegMask);
      vout21       = v_sub((v_cs&)vout21, (v_cs&)vNegMask);
      vinvh21      = vout21;

      // - invh22
      vh11.v_convert2ci(vcih1, vcih2);

      v_conjmul2cq(vcih1, vstar[0], vres1, vres2);
      v_conjmul2cq(vcih2, vstar[1], vres3, vres4);

      vres1 = vres1.v_shift_left(16);
      vres2 = vres2.v_shift_left(16);
      vres3 = vres3.v_shift_left(16);
      vres4 = vres4.v_shift_left(16);

      vres1[0].re /= vstarsqr[0][0]; vres1[0].im /= vstarsqr[0][0];
      vres2[0].re /= vstarsqr[0][1]; vres2[0].im /= vstarsqr[0][1];
      vres3[0].re /= vstarsqr[1][0]; vres3[0].im /= vstarsqr[1][0];
      vres4[0].re /= vstarsqr[1][1]; vres4[0].im /= vstarsqr[1][1];

      ((v_ci&)vres1) = v_convert2ci_lo(vres1, vres2);
      ((v_ci&)vres3) = v_convert2ci_lo(vres3, vres4);

      v_cs &vout22 = (v_cs&)vres2;
      vout22       = v_convert2cs((v_ci&)vres1, (v_ci&)vres3);
      vinvh22      = vout22;
    }

    consume_each(32);

    return true;
  }
};