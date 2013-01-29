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

#if enable_dbgplot
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

    for (int r = 0; r < 2; r++)
    {
      for (int c = 0; c < 2; c++)
      {
        char buf[64] = {0};
        memset(buf, 0, 64);
        sprintf_s(buf, 64, "H[%d][%d]", r, c);
        
        v_i vspec[16];
        int ispecpos = 0;
        for (int i = 0; i < 64; i += 4)
        {
          int n = (32 + i) % 64;
          v_cs& vch = (v_cs&)mimo_channel_2x2_inv[r][c * 64 + n];
          vspec[ispecpos++] = vch.v_sqr2i();
        }

        PlotSpectrum(buf, (int*)&vspec[0][0], 64);
      }
    }
#endif

    consume_each(32);

    return true;
  }
};


//////////////////////////////////////////////////////////////////////////



#define enable_4x4_H_draw 0

typedef complex16 MIMO_4x4_H[4][256];
typedef complexd MIMO_4x4_H_f[4][256];



__forceinline
void InverseMatrix(MIMO_4x4_H_f &H, MIMO_4x4_H_f &invH)
{
  memset(&invH, 0, sizeof(MIMO_4x4_H_f));

  for (int i = 0; i < 64; i++)
  {
    if (i == 0 || (i > 28 && i < 64 - 28))
    {
      continue;
    }

    complexd& a11 = H[0][i]; complexd& a12 = H[0][i + 64]; complexd& a13 = H[0][i + 128]; complexd& a14 = H[0][i + 192];
    complexd& a21 = H[1][i]; complexd& a22 = H[1][i + 64]; complexd& a23 = H[1][i + 128]; complexd& a24 = H[1][i + 192];
    complexd& a31 = H[2][i]; complexd& a32 = H[2][i + 64]; complexd& a33 = H[2][i + 128]; complexd& a34 = H[2][i + 192];
    complexd& a41 = H[3][i]; complexd& a42 = H[3][i + 64]; complexd& a43 = H[3][i + 128]; complexd& a44 = H[3][i + 192];

    complexd& c11 = invH[0][i]; complexd& c12 = invH[0][i + 64]; complexd& c13 = invH[0][i + 128]; complexd& c14 = invH[0][i + 192];
    complexd& c21 = invH[1][i]; complexd& c22 = invH[1][i + 64]; complexd& c23 = invH[1][i + 128]; complexd& c24 = invH[1][i + 192];
    complexd& c31 = invH[2][i]; complexd& c32 = invH[2][i + 64]; complexd& c33 = invH[2][i + 128]; complexd& c34 = invH[2][i + 192];
    complexd& c41 = invH[3][i]; complexd& c42 = invH[3][i + 64]; complexd& c43 = invH[3][i + 128]; complexd& c44 = invH[3][i + 192];

    complexd det 
      = a11 * a22 * a33 * a44 + a11 * a23 * a34 * a42 + a11 * a24 * a32 * a43
      + a12 * a21 * a34 * a43 + a12 * a23 * a31 * a44 + a12 * a24 * a33 * a41
      + a13 * a21 * a32 * a44 + a13 * a22 * a34 * a41 + a13 * a24 * a31 * a42
      + a14 * a21 * a33 * a42 + a14 * a22 * a31 * a43 + a14 * a23 * a32 * a41
      - a11 * a22 * a34 * a43 - a11 * a23 * a32 * a44 - a11 * a24 * a33 * a42
      - a12 * a21 * a33 * a44 - a12 * a23 * a34 * a41 - a12 * a24 * a31 * a43
      - a13 * a21 * a34 * a42 - a13 * a22 * a31 * a44 - a13 * a24 * a32 * a41
      - a14 * a21 * a32 * a43 - a14 * a22 * a33 * a41 - a14 * a23 * a31 * a42;

    complexd b11 = a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43 - a22 * a34 * a43 - a23 * a32 * a44 - a24 * a33 * a42;
    complexd b12 = a12 * a34 * a43 + a13 * a32 * a44 + a14 * a33 * a42 - a12 * a33 * a44 - a13 * a34 * a42 - a14 * a32 * a43;
    complexd b13 = a12 * a23 * a44 + a13 * a24 * a42 + a14 * a22 * a43 - a12 * a24 * a43 - a13 * a22 * a44 - a14 * a23 * a42;
    complexd b14 = a12 * a24 * a33 + a13 * a22 * a34 + a14 * a23 * a32 - a12 * a23 * a34 - a13 * a24 * a32 - a14 * a22 * a33;
                                                                                           
    complexd b21 = a21 * a34 * a43 + a23 * a31 * a44 + a24 * a33 * a41 - a21 * a33 * a44 - a23 * a34 * a41 - a24 * a31 * a43;
    complexd b22 = a11 * a33 * a44 + a13 * a34 * a41 + a14 * a31 * a43 - a11 * a34 * a43 - a13 * a31 * a44 - a14 * a33 * a41;
    complexd b23 = a11 * a24 * a43 + a13 * a21 * a44 + a14 * a23 * a41 - a11 * a23 * a44 - a13 * a24 * a41 - a14 * a21 * a43;
    complexd b24 = a11 * a23 * a34 + a13 * a24 * a31 + a14 * a21 * a33 - a11 * a24 * a33 - a13 * a21 * a34 - a14 * a23 * a31;
                                                                                           
    complexd b31 = a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42 - a21 * a34 * a42 - a22 * a31 * a44 - a24 * a32 * a41;
    complexd b32 = a11 * a34 * a42 + a12 * a31 * a44 + a14 * a32 * a41 - a11 * a32 * a44 - a12 * a34 * a41 - a14 * a31 * a42;
    complexd b33 = a11 * a22 * a44 + a12 * a24 * a41 + a14 * a21 * a42 - a11 * a24 * a42 - a12 * a21 * a44 - a14 * a22 * a41;
    complexd b34 = a11 * a24 * a32 + a12 * a21 * a34 + a14 * a22 * a31 - a11 * a22 * a34 - a12 * a24 * a31 - a14 * a21 * a32;

    complexd b41 = a21 * a33 * a42 + a22 * a31 * a43 + a23 * a32 * a41 - a21 * a32 * a43 - a22 * a33 * a41 - a23 * a31 * a42;
    complexd b42 = a11 * a32 * a43 + a12 * a33 * a41 + a13 * a31 * a42 - a11 * a33 * a42 - a12 * a31 * a43 - a13 * a32 * a41;
    complexd b43 = a11 * a23 * a42 + a12 * a21 * a43 + a13 * a22 * a41 - a11 * a22 * a43 - a12 * a23 * a41 - a13 * a21 * a42;
    complexd b44 = a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a11 * a23 * a32 - a12 * a21 * a33 - a13 * a22 * a31;

    //////////////////////////////////////////////////////////////////////////
    double detsqr = det.sqr();
    det = det.conj_im();
    
    // Get inverse of H
    c11 = b11 * det / detsqr;
    c12 = b12 * det / detsqr;
    c13 = b13 * det / detsqr;
    c14 = b14 * det / detsqr;

    c21 = b21 * det / detsqr;
    c22 = b22 * det / detsqr;
    c23 = b23 * det / detsqr;
    c24 = b24 * det / detsqr;

    c31 = b31 * det / detsqr;
    c32 = b32 * det / detsqr;
    c33 = b33 * det / detsqr;
    c34 = b34 * det / detsqr;

    c41 = b41 * det / detsqr;
    c42 = b42 * det / detsqr;
    c43 = b43 * det / detsqr;
    c44 = b44 * det / detsqr;

#if 0
    // validate invH * H = I
    complexd v1 = c11 * a11 + c12 * a21 + c13 * a31 + c14 * a41;
    complexd v2 = c11 * a12 + c12 * a22 + c13 * a32 + c14 * a42;
    complexd v3 = c11 * a13 + c12 * a23 + c13 * a33 + c14 * a43;
    complexd v4 = c11 * a14 + c12 * a24 + c13 * a34 + c14 * a44;
    
    v1 = b21 * a11 + b22 * a21 + b23 * a31 + b24 * a41;
    v2 = b21 * a12 + b22 * a22 + b23 * a32 + b24 * a42;
    v3 = b21 * a13 + b22 * a23 + b23 * a33 + b24 * a43;
    v4 = b21 * a14 + b22 * a24 + b23 * a34 + b24 * a44;

    v1 = b31 * a11 + b32 * a21 + b33 * a31 + b34 * a41;
    v2 = b31 * a12 + b32 * a22 + b33 * a32 + b34 * a42;
    v3 = b31 * a13 + b32 * a23 + b33 * a33 + b34 * a43;
    v4 = b31 * a14 + b32 * a24 + b33 * a34 + b34 * a44;

    v1 = b41 * a11 + b42 * a21 + b43 * a31 + b44 * a41;
    v2 = b41 * a12 + b42 * a22 + b43 * a32 + b44 * a42;
    v3 = b41 * a13 + b42 * a23 + b43 * a33 + b44 * a43;
    v4 = b41 * a14 + b42 * a24 + b43 * a34 + b44 * a44;
#endif
  }
}


__forceinline
void NormalizeMatrix(MIMO_4x4_H_f &H_f, MIMO_4x4_H &H, float NormFactor)
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 256; j++)
    {
      H[i][j].re = (short)(H_f[i][j].re * NormFactor);
      H[i][j].im = (short)(H_f[i][j].im * NormFactor);
    }
  }
}

__forceinline
  void MultilyMatrix(MIMO_4x4_H_f &a, MIMO_4x4_H_f &b, MIMO_4x4_H_f &c)
{
  for (int i = 0; i < 64; i++)
  {
    complexd& a11 = a[0][i]; complexd& a12 = a[0][i + 64]; complexd& a13 = a[0][i + 128]; complexd& a14 = a[0][i + 192];
    complexd& a21 = a[1][i]; complexd& a22 = a[1][i + 64]; complexd& a23 = a[1][i + 128]; complexd& a24 = a[1][i + 192];
    complexd& a31 = a[2][i]; complexd& a32 = a[2][i + 64]; complexd& a33 = a[2][i + 128]; complexd& a34 = a[2][i + 192];
    complexd& a41 = a[3][i]; complexd& a42 = a[3][i + 64]; complexd& a43 = a[3][i + 128]; complexd& a44 = a[3][i + 192];

    complexd& b11 = b[0][i]; complexd& b12 = b[0][i + 64]; complexd& b13 = b[0][i + 128]; complexd& b14 = b[0][i + 192];
    complexd& b21 = b[1][i]; complexd& b22 = b[1][i + 64]; complexd& b23 = b[1][i + 128]; complexd& b24 = b[1][i + 192];
    complexd& b31 = b[2][i]; complexd& b32 = b[2][i + 64]; complexd& b33 = b[2][i + 128]; complexd& b34 = b[2][i + 192];
    complexd& b41 = b[3][i]; complexd& b42 = b[3][i + 64]; complexd& b43 = b[3][i + 128]; complexd& b44 = b[3][i + 192];

    complexd& c11 = c[0][i]; complexd& c12 = c[0][i + 64]; complexd& c13 = c[0][i + 128]; complexd& c14 = c[0][i + 192];
    complexd& c21 = c[1][i]; complexd& c22 = c[1][i + 64]; complexd& c23 = c[1][i + 128]; complexd& c24 = c[1][i + 192];
    complexd& c31 = c[2][i]; complexd& c32 = c[2][i + 64]; complexd& c33 = c[2][i + 128]; complexd& c34 = c[2][i + 192];
    complexd& c41 = c[3][i]; complexd& c42 = c[3][i + 64]; complexd& c43 = c[3][i + 128]; complexd& c44 = c[3][i + 192];

    c11 = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
    c12 = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
    c13 = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
    c14 = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

    c21 = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
    c22 = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
    c23 = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
    c24 = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

    c31 = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
    c32 = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
    c33 = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
    c34 = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

    c41 = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
    c42 = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
    c43 = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
    c44 = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;
  }
}

__forceinline
  void AddMatrix(MIMO_4x4_H_f &a, MIMO_4x4_H_f &b, MIMO_4x4_H_f &c)
{
  for (int i = 0; i < 64; i++)
  {
    complexd& a11 = a[0][i]; complexd& a12 = a[0][i + 64]; complexd& a13 = a[0][i + 128]; complexd& a14 = a[0][i + 192];
    complexd& a21 = a[1][i]; complexd& a22 = a[1][i + 64]; complexd& a23 = a[1][i + 128]; complexd& a24 = a[1][i + 192];
    complexd& a31 = a[2][i]; complexd& a32 = a[2][i + 64]; complexd& a33 = a[2][i + 128]; complexd& a34 = a[2][i + 192];
    complexd& a41 = a[3][i]; complexd& a42 = a[3][i + 64]; complexd& a43 = a[3][i + 128]; complexd& a44 = a[3][i + 192];

    complexd& b11 = b[0][i]; complexd& b12 = b[0][i + 64]; complexd& b13 = b[0][i + 128]; complexd& b14 = b[0][i + 192];
    complexd& b21 = b[1][i]; complexd& b22 = b[1][i + 64]; complexd& b23 = b[1][i + 128]; complexd& b24 = b[1][i + 192];
    complexd& b31 = b[2][i]; complexd& b32 = b[2][i + 64]; complexd& b33 = b[2][i + 128]; complexd& b34 = b[2][i + 192];
    complexd& b41 = b[3][i]; complexd& b42 = b[3][i + 64]; complexd& b43 = b[3][i + 128]; complexd& b44 = b[3][i + 192];

    complexd& c11 = c[0][i]; complexd& c12 = c[0][i + 64]; complexd& c13 = c[0][i + 128]; complexd& c14 = c[0][i + 192];
    complexd& c21 = c[1][i]; complexd& c22 = c[1][i + 64]; complexd& c23 = c[1][i + 128]; complexd& c24 = c[1][i + 192];
    complexd& c31 = c[2][i]; complexd& c32 = c[2][i + 64]; complexd& c33 = c[2][i + 128]; complexd& c34 = c[2][i + 192];
    complexd& c41 = c[3][i]; complexd& c42 = c[3][i + 64]; complexd& c43 = c[3][i + 128]; complexd& c44 = c[3][i + 192];

    c11 = a11 + b11;
    c12 = a12 + b12;
    c13 = a13 + b13;
    c14 = a14 + b14;

    c21 = a21 + b21;
    c22 = a22 + b22;
    c23 = a23 + b23;
    c24 = a24 + b24;

    c31 = a31 + b31;
    c32 = a32 + b32;
    c33 = a33 + b33;
    c34 = a34 + b34;

    c41 = a41 + b41;
    c42 = a42 + b42;
    c43 = a43 + b43;
    c44 = a44 + b44;
  }
}



__forceinline
  void HermitMatrix(MIMO_4x4_H_f &a, MIMO_4x4_H_f &b)
{
  for (int i = 0; i < 64; i++)
  {
    complexd& a11 = a[0][i]; complexd& a12 = a[0][i + 64]; complexd& a13 = a[0][i + 128]; complexd& a14 = a[0][i + 192];
    complexd& a21 = a[1][i]; complexd& a22 = a[1][i + 64]; complexd& a23 = a[1][i + 128]; complexd& a24 = a[1][i + 192];
    complexd& a31 = a[2][i]; complexd& a32 = a[2][i + 64]; complexd& a33 = a[2][i + 128]; complexd& a34 = a[2][i + 192];
    complexd& a41 = a[3][i]; complexd& a42 = a[3][i + 64]; complexd& a43 = a[3][i + 128]; complexd& a44 = a[3][i + 192];

    complexd& b11 = b[0][i]; complexd& b12 = b[0][i + 64]; complexd& b13 = b[0][i + 128]; complexd& b14 = b[0][i + 192];
    complexd& b21 = b[1][i]; complexd& b22 = b[1][i + 64]; complexd& b23 = b[1][i + 128]; complexd& b24 = b[1][i + 192];
    complexd& b31 = b[2][i]; complexd& b32 = b[2][i + 64]; complexd& b33 = b[2][i + 128]; complexd& b34 = b[2][i + 192];
    complexd& b41 = b[3][i]; complexd& b42 = b[3][i + 64]; complexd& b43 = b[3][i + 128]; complexd& b44 = b[3][i + 192];

    b11 = a11.conj_im(); b12 = a21.conj_im(); b13 = a31.conj_im(); b14 = a41.conj_im();
    b21 = a12.conj_im(); b22 = a22.conj_im(); b23 = a32.conj_im(); b24 = a42.conj_im();
    b31 = a13.conj_im(); b32 = a23.conj_im(); b33 = a33.conj_im(); b34 = a43.conj_im();
    b41 = a14.conj_im(); b42 = a24.conj_im(); b43 = a34.conj_im(); b44 = a44.conj_im();
  }
}

__forceinline
  void IdendityMatrix(MIMO_4x4_H_f &a)
{
  memset(&a, 0, sizeof(MIMO_4x4_H_f));

  for (int i = 0; i < 64; i++)
  {
    complexd& a11 = a[0][i]; complexd& a12 = a[0][i + 64]; complexd& a13 = a[0][i + 128]; complexd& a14 = a[0][i + 192];
    complexd& a21 = a[1][i]; complexd& a22 = a[1][i + 64]; complexd& a23 = a[1][i + 128]; complexd& a24 = a[1][i + 192];
    complexd& a31 = a[2][i]; complexd& a32 = a[2][i + 64]; complexd& a33 = a[2][i + 128]; complexd& a34 = a[2][i + 192];
    complexd& a41 = a[3][i]; complexd& a42 = a[3][i + 64]; complexd& a43 = a[3][i + 128]; complexd& a44 = a[3][i + 192];

    a11 = a22 = a33 = a44 = complexd(1.0f, 0);
  }
}

// a->b
__forceinline
  void ConvertMatrix(MIMO_4x4_H &a, MIMO_4x4_H_f &b)
{
  for (int i = 0; i < 64; i++)
  {
    complex16& a11 = a[0][i]; complex16& a12 = a[0][i + 64]; complex16& a13 = a[0][i + 128]; complex16& a14 = a[0][i + 192];
    complex16& a21 = a[1][i]; complex16& a22 = a[1][i + 64]; complex16& a23 = a[1][i + 128]; complex16& a24 = a[1][i + 192];
    complex16& a31 = a[2][i]; complex16& a32 = a[2][i + 64]; complex16& a33 = a[2][i + 128]; complex16& a34 = a[2][i + 192];
    complex16& a41 = a[3][i]; complex16& a42 = a[3][i + 64]; complex16& a43 = a[3][i + 128]; complex16& a44 = a[3][i + 192];

    complexd& b11 = b[0][i]; complexd& b12 = b[0][i + 64]; complexd& b13 = b[0][i + 128]; complexd& b14 = b[0][i + 192];
    complexd& b21 = b[1][i]; complexd& b22 = b[1][i + 64]; complexd& b23 = b[1][i + 128]; complexd& b24 = b[1][i + 192];
    complexd& b31 = b[2][i]; complexd& b32 = b[2][i + 64]; complexd& b33 = b[2][i + 128]; complexd& b34 = b[2][i + 192];
    complexd& b41 = b[3][i]; complexd& b42 = b[3][i + 64]; complexd& b43 = b[3][i + 128]; complexd& b44 = b[3][i + 192];

    b11.re = a11.re; b11.im = a11.im; b12.re = a12.re; b12.im = a12.im; b13.re = a13.re; b13.im = a13.im; b14.re = a14.re; b14.im = a14.im;
    b21.re = a21.re; b21.im = a21.im; b22.re = a22.re; b22.im = a22.im; b23.re = a23.re; b23.im = a23.im; b24.re = a24.re; b24.im = a24.im;
    b31.re = a31.re; b31.im = a31.im; b32.re = a32.re; b32.im = a32.im; b33.re = a33.re; b33.im = a33.im; b34.re = a34.re; b34.im = a34.im;
    b41.re = a41.re; b41.im = a41.im; b42.re = a42.re; b42.im = a42.im; b43.re = a43.re; b43.im = a43.im; b44.re = a44.re; b44.im = a44.im;
  }
}



__forceinline
void dot11_estimate_channel_4x4(
  complex16* &ipc1, complex16* &ipc2, complex16* &ipc3, complex16* &ipc4, 
  complex16* &pHTLTFMask, MIMO_4x4_H &dot11n_4x4_channel
  )
{
  v_ci vtemp[4];

  v_ci vstar[2];
  v_q  vstarsqr[2];

  v_ci vcih1, vcih2;

  const v_cs vMulMask = VMASK::__0x80000001800000018000000180000001<v_cs>();
  const v_cs vNegMask = VMASK::__0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF<v_cs>();


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
}


DEFINE_BLOCK(b_dot11_mimo_channel_estimator_4v, 4, 0)
{
  _global_(MIMO_4x4_H, dot11n_4x4_channel_inv);
  v_align(16)
  MIMO_4x4_H   dot11n_4x4_channel;
  MIMO_4x4_H_f dot11n_4x4_channel_f;
  MIMO_4x4_H_f dot11n_4x4_channel_inv_f;
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
    int n = ninput(0);
    if (n < 64) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    auto ipc1 = (complex16*)ip1;
    auto ipc2 = (complex16*)ip2;
    auto ipc3 = (complex16*)ip3;
    auto ipc4 = (complex16*)ip4;

    complex16* pHTLTFMask = &_80211n_HTLTFMask[0][0];
    MIMO_4x4_H& mimo_channel_4x4_inv = *dot11n_4x4_channel_inv;

    // estimate channel
    dot11_estimate_channel_4x4(ipc1, ipc2, ipc3, ipc4, pHTLTFMask, dot11n_4x4_channel);

    ConvertMatrix(dot11n_4x4_channel, dot11n_4x4_channel_f);
    //////////////////////////////////////////////////////////////////////////
    float norm = 65535.0f;

    // zero force estimation, get compensation matrix as inverse of H
    InverseMatrix(dot11n_4x4_channel_f, dot11n_4x4_channel_inv_f);
    NormalizeMatrix(dot11n_4x4_channel_inv_f, mimo_channel_4x4_inv, norm);

    consume_each(64);

    return true;
  }
};

DEFINE_BLOCK(b_dot11_mimo_channel_estimator_mmse_4v, 4, 0)
{
  _global_(MIMO_4x4_H, dot11n_4x4_channel_inv);
  _global_(MIMO_4x4_H_f, dot11n_4x4_noise_var);

  v_align(16) 
  MIMO_4x4_H   dot11n_4x4_channel;  
  MIMO_4x4_H_f dot11n_4x4_channel_f;
  MIMO_4x4_H_f dot11n_4x4_channel_inv_f;
  MIMO_4x4_H_f dot11n_4x4_channel_hermit_f;
  MIMO_4x4_H_f dot11n_4x4_idendity_f;
  MIMO_4x4_H_f dot11n_4x4_compensate_f;
  MIMO_4x4_H_f temp_matrix;

  BLOCK_INIT
  {
  }

  BLOCK_WORK
  {
    int n = ninput(0);
    if (n < 64) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    auto ipc1 = (complex16*)ip1;
    auto ipc2 = (complex16*)ip2;
    auto ipc3 = (complex16*)ip3;
    auto ipc4 = (complex16*)ip4;

    complex16* pHTLTFMask = &_80211n_HTLTFMask[0][0];
    MIMO_4x4_H& mimo_channel_4x4_inv = *dot11n_4x4_channel_inv;
    MIMO_4x4_H_f &noise_var = *dot11n_4x4_noise_var;

    // estimate channel
    dot11_estimate_channel_4x4(ipc1, ipc2, ipc3, ipc4, pHTLTFMask, dot11n_4x4_channel);

    ConvertMatrix(dot11n_4x4_channel, dot11n_4x4_channel_f);

    //////////////////////////////////////////////////////////////////////////
    float norm = 65535.0f;

    HermitMatrix(dot11n_4x4_channel_f, dot11n_4x4_channel_hermit_f);
    MultilyMatrix(dot11n_4x4_channel_hermit_f, dot11n_4x4_channel_f, temp_matrix);

    //IdendityMatrix(dot11n_4x4_idendity_f);
    //AddMatrix(temp_matrix, dot11n_4x4_idendity_f, temp_matrix);
    AddMatrix(temp_matrix, noise_var, temp_matrix);

    InverseMatrix(temp_matrix, dot11n_4x4_channel_inv_f);

    MultilyMatrix(dot11n_4x4_channel_inv_f, dot11n_4x4_channel_hermit_f, dot11n_4x4_compensate_f);

    NormalizeMatrix(dot11n_4x4_compensate_f, mimo_channel_4x4_inv, norm);

    consume_each(64);

    return true;
  }
};