#pragma once

DEFINE_BLOCK(b_awgn_4v4, 4, 4)
{
  _local_(int16, noise_var, 1);

  BLOCK_INIT
  {
    auto v = $["NoiseVar"];
    if (!v.empty())
    {
      *noise_var = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(1);
    auto ip3 = _$<v_cs>(2);
    auto ip4 = _$<v_cs>(3);

    complex16* ipc1 = (complex16*)ip1;
    complex16* ipc2 = (complex16*)ip2;
    complex16* ipc3 = (complex16*)ip3;
    complex16* ipc4 = (complex16*)ip4;

    auto op1 = $_<v_cs>(0);
    auto op2 = $_<v_cs>(1);
    auto op3 = $_<v_cs>(2);
    auto op4 = $_<v_cs>(3);

    complex16* opc1 = (complex16*)op1;
    complex16* opc2 = (complex16*)op2;
    complex16* opc3 = (complex16*)op3;
    complex16* opc4 = (complex16*)op4;

    for (int i = 0; i < n * 4; i++)
    {
      opc1[i].re = ipc1[i].re + (rand() % *noise_var) * (rand() % 2 == 0 ? 1 : -1);
      opc1[i].im = ipc1[i].im + (rand() % *noise_var) * (rand() % 2 == 0 ? 1 : -1);

      opc2[i].re = ipc2[i].re + (rand() % *noise_var) * (rand() % 2 == 0 ? 1 : -1);
      opc2[i].im = ipc2[i].im + (rand() % *noise_var) * (rand() % 2 == 0 ? 1 : -1);

      opc3[i].re = ipc3[i].re + (rand() % *noise_var) * (rand() % 2 == 0 ? 1 : -1);
      opc3[i].im = ipc3[i].im + (rand() % *noise_var) * (rand() % 2 == 0 ? 1 : -1);

      opc4[i].re = ipc4[i].re + (rand() % *noise_var) * (rand() % 2 == 0 ? 1 : -1);
      opc4[i].im = ipc4[i].im + (rand() % *noise_var) * (rand() % 2 == 0 ? 1 : -1);
    }

    consume_each(n);
    produce_each(n);

    return true;
  }
};