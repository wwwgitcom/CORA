#pragma once

typedef complexd MIMO_4x4_H_f[4][256];

DEFINE_BLOCK(b_noise_estimator_4v, 4, 0)
{
  _global_(MIMO_4x4_H_f, dot11n_4x4_noise_var);

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 16) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    complex16* ipc[4] = {(complex16*)ip1, (complex16*)ip2, (complex16*)ip3, (complex16*)ip4};

    MIMO_4x4_H_f &noise_matrix = *dot11n_4x4_noise_var;

    complexd noise;
    complexd norm(128.0f, 0.0f);
    double   normsqr = norm.sqr();

    memset(&noise_matrix, 0, sizeof(MIMO_4x4_H_f));

    for (int k = 0; k < 4; k++)
    {
      for (int i = 0; i < 64; i++)
      {
        if (i == 0 || (i > 26 && i < 64 - 26))
        {
          continue;
        }

        complexd cf;
        cf.re = dsp_math::abs(ipc[k][i].re);
        cf.im = dsp_math::abs(ipc[k][i].im);
        noise = cf - norm;

        double noise_energy = noise.sqr();
#if 0
        double snr = 10 * log10f(normsqr / noise_energy);
        printf("snr_%d@%d: %f dB\n", k, i, snr);
#endif
        //noise_matrix[k][k * 64 + i].re = noise_energy / normsqr;
        noise_matrix[k][k * 64 + i].re = noise_energy;
        noise_matrix[k][k * 64 + i].im = 0.0f;
      }

      noise_matrix[k][k * 64 + 27] = noise_matrix[k][k * 64 + 26];
      noise_matrix[k][k * 64 + 28] = noise_matrix[k][k * 64 + 26];
      noise_matrix[k][k * 64 + 64 - 27] = noise_matrix[k][k * 64 + 64 - 26];
      noise_matrix[k][k * 64 + 64 - 28] = noise_matrix[k][k * 64 + 64 - 26];
    }

    return true;
  }
};