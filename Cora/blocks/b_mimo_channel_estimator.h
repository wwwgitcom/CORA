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


DEFINE_BLOCK(b_dot11_mimo_channel_estimator_2v, 2, 0)
{
  _global_(MIMO_2x2_H, dot11n_2x2_channel_inv);
  v_align(16) MIMO_2x2_H dot11n_2x2_channel;
#if enable_draw
  dsp_draw_window* m_draw;
#endif

  BLOCK_INIT
  {
#if enable_draw
    m_draw = new dsp_draw_window("dot11 2x2 mimo channel estimator", 800, 0, 400, 400);
#endif
  }

  BLOCK_WORK
  {
    v_ci vtemp[4];

    v_ci vstar[2];
    v_q  vstarsqr[2];

    v_ci vcih1, vcih2;

    int n = ninput(0);
    if (n < 32) return false;

    const v_cs vMulMask = VMASK::__0x80000001800000018000000180000001<v_cs>();
    const v_cs vNegMask = VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_cs>();

    const complex16* pHTLTFMask = &_80211n_HTLTFMask[0][0];

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);

    auto ipc1 = (complex16*)ip1;
    auto ipc2 = (complex16*)ip2;

    MIMO_2x2_H& mimo_channel_2x2_inv = *dot11n_2x2_channel_inv;

    int i;

    for (i = 0; i < 64; i += 4)
    {
      v_cs& vhtmsk = (v_cs&)pHTLTFMask[i];

      v_cs& v11    = (v_cs&)ipc1[i];
      v_cs& v12    = (v_cs&)ipc1[i + 64];
      v_cs& v21    = (v_cs&)ipc2[i];
      v_cs& v22    = (v_cs&)ipc2[i + 64];

      v_cs& vh11   = (v_cs&)dot11n_2x2_channel[0][i];
      v_cs& vh12   = (v_cs&)dot11n_2x2_channel[0][i + 64];
      v_cs& vh21   = (v_cs&)dot11n_2x2_channel[1][i];
      v_cs& vh22   = (v_cs&)dot11n_2x2_channel[1][i + 64];

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
      v_cs& vh11   = (v_cs&)dot11n_2x2_channel[0][i];
      v_cs& vh12   = (v_cs&)dot11n_2x2_channel[0][i + 64];
      v_cs& vh21   = (v_cs&)dot11n_2x2_channel[1][i];
      v_cs& vh22   = (v_cs&)dot11n_2x2_channel[1][i + 64];

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
      v_cs &vinvh11 = (v_cs&)mimo_channel_2x2_inv[0][i];
      v_cs &vinvh12 = (v_cs&)mimo_channel_2x2_inv[0][i + 64];
      v_cs &vinvh21 = (v_cs&)mimo_channel_2x2_inv[1][i];
      v_cs &vinvh22 = (v_cs&)mimo_channel_2x2_inv[1][i + 64];

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

    //m_draw->DrawSqrt(ipc1, 128);
    //getchar();
    //m_draw->DrawSqrt(ipc2, 128);
#if enable_draw
    mimo_channel_2x2_inv[0][0] = 0;
    mimo_channel_2x2_inv[0][64] = 0;
    mimo_channel_2x2_inv[1][0] = 0;
    mimo_channel_2x2_inv[1][64] = 0;
    for (int i = 29; i < 64 - 28; i++)
    {
      mimo_channel_2x2_inv[0][i] = 0;
      mimo_channel_2x2_inv[0][i + 64] = 0;
      mimo_channel_2x2_inv[1][i] = 0;
      mimo_channel_2x2_inv[1][i + 64] = 0;
    }

    m_draw->DrawSqrt(&mimo_channel_2x2_inv[0][0], 256);
#endif
    consume_each(32);

    return true;
  }
};


//////////////////////////////////////////////////////////////////////////
#define enable_4x4_H_draw 1

typedef complex16 MIMO_4x4_H[4][256];
DEFINE_BLOCK(b_dot11_mimo_channel_estimator_4v, 4, 0)
{
  _global_(MIMO_4x4_H, dot11n_4x4_channel_inv);
  v_align(16) MIMO_4x4_H dot11n_4x4_channel;
#if enable_4x4_H_draw
  dsp_draw_window* m_draw;
#endif

  BLOCK_INIT
  {
#if enable_4x4_H_draw
    m_draw = new dsp_draw_window("dot11 4x4 mimo channel estimator", 800, 0, 400, 400);
#endif
  }

  BLOCK_WORK
  {
    v_ci vtemp[4];

    v_ci vstar[2];
    v_q  vstarsqr[2];

    v_ci vcih1, vcih2;

    int n = ninput(0);
    if (n < 64) return false;

    const v_cs vMulMask = VMASK::__0x80000001800000018000000180000001<v_cs>();
    const v_cs vNegMask = VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_cs>();

    const complex16* pHTLTFMask = &_80211n_HTLTFMask[0][0];

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    auto ipc1 = (complex16*)ip1;
    auto ipc2 = (complex16*)ip2;
    auto ipc3 = (complex16*)ip3;
    auto ipc4 = (complex16*)ip4;

    MIMO_4x4_H& mimo_channel_4x4_inv = *dot11n_4x4_channel_inv;

    int i;

    for (i = 0; i < 64; i += 4)
    {
      v_cs& vhtmsk = (v_cs&)pHTLTFMask[i];

      v_cs& v11    = (v_cs&)ipc1[i];
      v_cs& v12    = (v_cs&)ipc1[i + 64];
      v_cs& v13    = (v_cs&)ipc1[i + 128];
      v_cs& v14    = (v_cs&)ipc1[i + 192];

      v_cs& v21    = (v_cs&)ipc2[i];
      v_cs& v22    = (v_cs&)ipc2[i + 64];
      v_cs& v23    = (v_cs&)ipc2[i + 128];
      v_cs& v24    = (v_cs&)ipc2[i + 192];

      v_cs& v31    = (v_cs&)ipc3[i];
      v_cs& v32    = (v_cs&)ipc3[i + 64];
      v_cs& v33    = (v_cs&)ipc3[i + 128];
      v_cs& v34    = (v_cs&)ipc3[i + 192];

      v_cs& v41    = (v_cs&)ipc4[i];
      v_cs& v42    = (v_cs&)ipc4[i + 64];
      v_cs& v43    = (v_cs&)ipc4[i + 128];
      v_cs& v44    = (v_cs&)ipc4[i + 192];

      v_cs& vh11   = (v_cs&)dot11n_4x4_channel[0][i];
      v_cs& vh12   = (v_cs&)dot11n_4x4_channel[0][i + 64];
      v_cs& vh13   = (v_cs&)dot11n_4x4_channel[0][i + 128];
      v_cs& vh14   = (v_cs&)dot11n_4x4_channel[0][i + 192];

      v_cs& vh21   = (v_cs&)dot11n_4x4_channel[1][i];
      v_cs& vh22   = (v_cs&)dot11n_4x4_channel[1][i + 64];
      v_cs& vh23   = (v_cs&)dot11n_4x4_channel[1][i + 128];
      v_cs& vh24   = (v_cs&)dot11n_4x4_channel[1][i + 192];

      v_cs& vh31   = (v_cs&)dot11n_4x4_channel[2][i];
      v_cs& vh32   = (v_cs&)dot11n_4x4_channel[2][i + 64];
      v_cs& vh33   = (v_cs&)dot11n_4x4_channel[2][i + 128];
      v_cs& vh34   = (v_cs&)dot11n_4x4_channel[2][i + 192];

      v_cs& vh41   = (v_cs&)dot11n_4x4_channel[3][i];
      v_cs& vh42   = (v_cs&)dot11n_4x4_channel[3][i + 64];
      v_cs& vh43   = (v_cs&)dot11n_4x4_channel[3][i + 128];
      v_cs& vh44   = (v_cs&)dot11n_4x4_channel[3][i + 192];

      v_cs& vtemph  = (v_cs&)vtemp[0];
      v_cs& vtemph1 = (v_cs&)vtemp[1];
      v_cs& vtemph2 = (v_cs&)vtemp[2];

      vtemph1 = v_adds(v11, v14);
      vtemph2 = v_subs(v12, v13);
      
      vtemph  = v_subs(vtemph1, vtemph2);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh11   = v_sub(vtemph, vhtmsk);

      vtemph  = v_adds(vtemph2, vtemph1);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh12   = v_sub(vtemph, vhtmsk);

      vtemph1 = v_subs(v11, v14);
      vtemph2 = v_adds(v12, v13);

      vtemph  = v_adds(vtemph1, vtemph2);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh13   = v_sub(vtemph, vhtmsk);

      vtemph  = v_subs(vtemph2, vtemph1);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh14   = v_sub(vtemph, vhtmsk);

      //////////////////////////////////////////////////////////////////////////

      vtemph1 = v_adds(v21, v24);
      vtemph2 = v_subs(v22, v23);

      vtemph  = v_subs(vtemph1, vtemph2);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh21   = v_sub(vtemph, vhtmsk);

      vtemph  = v_adds(vtemph2, vtemph1);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh22   = v_sub(vtemph, vhtmsk);

      vtemph1 = v_subs(v21, v24);
      vtemph2 = v_adds(v22, v23);

      vtemph  = v_adds(vtemph1, vtemph2);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh23   = v_sub(vtemph, vhtmsk);

      vtemph  = v_subs(vtemph2, vtemph1);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh24   = v_sub(vtemph, vhtmsk);

      //////////////////////////////////////////////////////////////////////////

      vtemph1 = v_adds(v31, v34);
      vtemph2 = v_subs(v32, v33);

      vtemph  = v_subs(vtemph1, vtemph2);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh31   = v_sub(vtemph, vhtmsk);

      vtemph  = v_adds(vtemph2, vtemph1);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh32   = v_sub(vtemph, vhtmsk);

      vtemph1 = v_subs(v31, v34);
      vtemph2 = v_adds(v32, v33);

      vtemph  = v_adds(vtemph1, vtemph2);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh33   = v_sub(vtemph, vhtmsk);

      vtemph  = v_subs(vtemph2, vtemph1);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh34   = v_sub(vtemph, vhtmsk);

      //////////////////////////////////////////////////////////////////////////
      vtemph1 = v_adds(v41, v44);
      vtemph2 = v_subs(v42, v43);

      vtemph  = v_subs(vtemph1, vtemph2);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh41   = v_sub(vtemph, vhtmsk);

      vtemph  = v_adds(vtemph2, vtemph1);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh42   = v_sub(vtemph, vhtmsk);

      vtemph1 = v_subs(v41, v44);
      vtemph2 = v_adds(v42, v43);

      vtemph  = v_adds(vtemph1, vtemph2);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh43   = v_sub(vtemph, vhtmsk);

      vtemph  = v_subs(vtemph2, vtemph1);
      vtemph = vtemph.v_shift_right_arithmetic(2);
      vtemph = v_xor(vtemph, vhtmsk);
      vh44   = v_sub(vtemph, vhtmsk);
    }

#if 0
    // Get the inverse of H
    for (i = 0; i < 64; i += 4)
    {
      v_cs& vh11   = (v_cs&)dot11n_4x4_channel[0][i];
      v_cs& vh12   = (v_cs&)dot11n_4x4_channel[0][i + 64];
      v_cs& vh13   = (v_cs&)dot11n_4x4_channel[0][i + 128];
      v_cs& vh14   = (v_cs&)dot11n_4x4_channel[0][i + 192];

      v_cs& vh21   = (v_cs&)dot11n_4x4_channel[1][i];
      v_cs& vh22   = (v_cs&)dot11n_4x4_channel[1][i + 64];
      v_cs& vh23   = (v_cs&)dot11n_4x4_channel[1][i + 128];
      v_cs& vh24   = (v_cs&)dot11n_4x4_channel[1][i + 192];

      v_cs& vh31   = (v_cs&)dot11n_4x4_channel[2][i];
      v_cs& vh32   = (v_cs&)dot11n_4x4_channel[2][i + 64];
      v_cs& vh33   = (v_cs&)dot11n_4x4_channel[2][i + 128];
      v_cs& vh34   = (v_cs&)dot11n_4x4_channel[2][i + 192];

      v_cs& vh41   = (v_cs&)dot11n_4x4_channel[3][i];
      v_cs& vh42   = (v_cs&)dot11n_4x4_channel[3][i + 64];
      v_cs& vh43   = (v_cs&)dot11n_4x4_channel[3][i + 128];
      v_cs& vh44   = (v_cs&)dot11n_4x4_channel[3][i + 192];

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
      v_cs &vinvh11 = (v_cs&)mimo_channel_4x4_inv[0][i];
      v_cs &vinvh12 = (v_cs&)mimo_channel_4x4_inv[0][i + 64];
      v_cs &vinvh13 = (v_cs&)mimo_channel_4x4_inv[0][i + 128];
      v_cs &vinvh14 = (v_cs&)mimo_channel_4x4_inv[0][i + 192];

      v_cs &vinvh21 = (v_cs&)mimo_channel_4x4_inv[1][i];
      v_cs &vinvh22 = (v_cs&)mimo_channel_4x4_inv[1][i + 64];
      v_cs &vinvh23 = (v_cs&)mimo_channel_4x4_inv[1][i + 128];
      v_cs &vinvh24 = (v_cs&)mimo_channel_4x4_inv[1][i + 192];

      v_cs &vinvh31 = (v_cs&)mimo_channel_4x4_inv[2][i];
      v_cs &vinvh32 = (v_cs&)mimo_channel_4x4_inv[2][i + 64];
      v_cs &vinvh33 = (v_cs&)mimo_channel_4x4_inv[2][i + 128];
      v_cs &vinvh34 = (v_cs&)mimo_channel_4x4_inv[2][i + 192];

      v_cs &vinvh41 = (v_cs&)mimo_channel_4x4_inv[3][i];
      v_cs &vinvh42 = (v_cs&)mimo_channel_4x4_inv[3][i + 64];
      v_cs &vinvh43 = (v_cs&)mimo_channel_4x4_inv[3][i + 128];
      v_cs &vinvh44 = (v_cs&)mimo_channel_4x4_inv[3][i + 192];

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
#else
    for (i = 0; i < 64; i += 4)
    {
      v_cs &vinvh11 = (v_cs&)mimo_channel_4x4_inv[0][i];
      v_cs &vinvh12 = (v_cs&)mimo_channel_4x4_inv[0][i + 64];
      v_cs &vinvh13 = (v_cs&)mimo_channel_4x4_inv[0][i + 128];
      v_cs &vinvh14 = (v_cs&)mimo_channel_4x4_inv[0][i + 192];

      v_cs &vinvh21 = (v_cs&)mimo_channel_4x4_inv[1][i];
      v_cs &vinvh22 = (v_cs&)mimo_channel_4x4_inv[1][i + 64];
      v_cs &vinvh23 = (v_cs&)mimo_channel_4x4_inv[1][i + 128];
      v_cs &vinvh24 = (v_cs&)mimo_channel_4x4_inv[1][i + 192];

      v_cs &vinvh31 = (v_cs&)mimo_channel_4x4_inv[2][i];
      v_cs &vinvh32 = (v_cs&)mimo_channel_4x4_inv[2][i + 64];
      v_cs &vinvh33 = (v_cs&)mimo_channel_4x4_inv[2][i + 128];
      v_cs &vinvh34 = (v_cs&)mimo_channel_4x4_inv[2][i + 192];

      v_cs &vinvh41 = (v_cs&)mimo_channel_4x4_inv[3][i];
      v_cs &vinvh42 = (v_cs&)mimo_channel_4x4_inv[3][i + 64];
      v_cs &vinvh43 = (v_cs&)mimo_channel_4x4_inv[3][i + 128];
      v_cs &vinvh44 = (v_cs&)mimo_channel_4x4_inv[3][i + 192];

      vinvh11.v_setall(complex16(256, 0));
      vinvh12.v_setall(complex16(0, 0));
      vinvh13.v_setall(complex16(0, 0));
      vinvh14.v_setall(complex16(0, 0));

      vinvh21.v_setall(complex16(0, 0));
      vinvh22.v_setall(complex16(256, 0));
      vinvh23.v_setall(complex16(0, 0));
      vinvh24.v_setall(complex16(0, 0));

      vinvh31.v_setall(complex16(0, 0));
      vinvh32.v_setall(complex16(0, 0));
      vinvh33.v_setall(complex16(256, 0));
      vinvh34.v_setall(complex16(0, 0));

      vinvh41.v_setall(complex16(0, 0));
      vinvh42.v_setall(complex16(0, 0));
      vinvh43.v_setall(complex16(0, 0));
      vinvh44.v_setall(complex16(256, 0));
    }
#endif

    //m_draw->DrawSqrt(ipc1, 128);
    //getchar();
    //m_draw->DrawSqrt(ipc2, 128);
#if enable_4x4_H_draw
    dot11n_4x4_channel[0][0]   = 0;
    dot11n_4x4_channel[0][64]  = 0;
    dot11n_4x4_channel[0][128] = 0;
    dot11n_4x4_channel[0][192] = 0;
    dot11n_4x4_channel[1][0]   = 0;
    dot11n_4x4_channel[1][64]  = 0;
    dot11n_4x4_channel[1][128] = 0;
    dot11n_4x4_channel[1][192] = 0;

    dot11n_4x4_channel[2][0]   = 0;
    dot11n_4x4_channel[2][64]  = 0;
    dot11n_4x4_channel[2][128] = 0;
    dot11n_4x4_channel[2][192] = 0;
    dot11n_4x4_channel[3][0]   = 0;
    dot11n_4x4_channel[3][64]  = 0;
    dot11n_4x4_channel[3][128] = 0;
    dot11n_4x4_channel[3][192] = 0;

    for (int i = 29; i < 64 - 28; i++)
    {
      dot11n_4x4_channel[0][i]       = 0;
      dot11n_4x4_channel[0][i + 64]  = 0;
      dot11n_4x4_channel[0][i + 128] = 0;
      dot11n_4x4_channel[0][i + 192] = 0;
      dot11n_4x4_channel[1][i]       = 0;
      dot11n_4x4_channel[1][i + 64]  = 0;
      dot11n_4x4_channel[1][i + 128] = 0;
      dot11n_4x4_channel[1][i + 192] = 0;

      dot11n_4x4_channel[2][i]       = 0;
      dot11n_4x4_channel[2][i + 64]  = 0;
      dot11n_4x4_channel[2][i + 128] = 0;
      dot11n_4x4_channel[2][i + 192] = 0;
      dot11n_4x4_channel[3][i]       = 0;
      dot11n_4x4_channel[3][i + 64]  = 0;
      dot11n_4x4_channel[3][i + 128] = 0;
      dot11n_4x4_channel[3][i + 192] = 0;
    }

    m_draw->DrawSqrt(&dot11n_4x4_channel[0][0], 64 * 4 * 4);
#endif
    consume_each(64);

    return true;
  }
};