#pragma once

DEFINE_BLOCK(b_dot11_demap_bpsk_i_1v1, 1, 1)
{
  _local_(int, low, -26);
  _local_(int, high, 26);

  dsp_demapper demapper;

  BLOCK_INIT
  {
    auto v = $["low"];
    if (!v.empty())
    {
      *low = atoi(v.c_str());
    }
    v = $["high"];
    if (!v.empty())
    {
      *high = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    trace();

    if (ninput(0) < 16) return false;

    auto ip = _$<v_cs>(0);
    complex16* cip = (complex16*)ip;
    auto op = $_<unsigned __int8>(0);

    demapper.demap_limit_bpsk((v_cs*)ip, 16);

    int i;
    int j = 0;

    for (i = 64 + *low; i < 64; i++)
    {
      if (i == 64 - 21 || i == 64 - 7)
        continue;
      demapper.demap_bpsk_i(cip[i], &op[j++]);
    }

    for (i = 1; i <= *high; i++)
    {
      if (i == 7 || i == 21)
        continue;

      demapper.demap_bpsk_i(cip[i], &op[j++]);
    }

    consume(0, 16);
    produce(0, *high - *low - 4);

    return true;
  }
};


DEFINE_BLOCK(b_dot11_demap_bpsk_q_1v1, 1, 1)
{
  _local_(int, low, -26);
  _local_(int, high, 26);

  dsp_demapper demapper;

  BLOCK_INIT
  {
    auto v = $["low"];
    if (!v.empty())
    {
      *low = atoi(v.c_str());
    }
    v = $["high"];
    if (!v.empty())
    {
      *high = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    trace();

    if (ninput(0) < 16) return false;

    auto ip = _$<v_cs>(0);
    complex16* cip = (complex16*)ip;
    auto op = $_<unsigned __int8>(0);

    demapper.demap_limit_bpsk((v_cs*)ip, 16);

    int i;
    int j = 0;

    for (i = 64 + *low; i < 64; i++)
    {
      if (i == 64 - 21 || i == 64 - 7)
        continue;
      demapper.demap_bpsk_q(cip[i], &op[j++]);
    }

    for (i = 1; i <= *high; i++)
    {
      if (i == 7 || i == 21)
        continue;

      demapper.demap_bpsk_q(cip[i], &op[j++]);
    }

    consume(0, 16);
    produce(0, *high - *low - 4);

    return true;
  }
};

DEFINE_BLOCK(b_dot11_demap_qpsk_1v1, 1, 1)
{
  _local_(int, low, -26);
  _local_(int, high, 26);

  dsp_demapper demapper;

  BLOCK_INIT
  {
    auto v = $["low"];
    if (!v.empty())
    {
      *low = atoi(v.c_str());
    }
    v = $["high"];
    if (!v.empty())
    {
      *high = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    trace();

    if (ninput(0) < 16) return false;

    auto ip = _$<v_cs>(0);
    complex16* cip = (complex16*)ip;
    auto op = $_<unsigned __int8>(0);

    demapper.demap_limit_qpsk((v_cs*)ip, 16);

    int i;
    int j = 0;

    for (i = 64 + *low; i < 64; i++)
    {
      if (i == 64 - 21 || i == 64 - 7)
        continue;
      demapper.demap_qpsk(cip[i], &op[j]);
      j += 2;
    }

    for (i = 1; i <= *high; i++)
    {
      if (i == 7 || i == 21)
        continue;

      demapper.demap_qpsk(cip[i], &op[j]);
      j += 2;
    }

    consume(0, 16);
    produce(0, (*high - *low - 4) * 2);

    return true;
  }
};

DEFINE_BLOCK(b_dot11_demap_16qam_1v1, 1, 1)
{
  _local_(int, low, -26);
  _local_(int, high, 26);

  dsp_demapper demapper;

  BLOCK_INIT
  {
    auto v = $["low"];
    if (!v.empty())
    {
      *low = atoi(v.c_str());
    }
    v = $["high"];
    if (!v.empty())
    {
      *high = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    trace();

    if (ninput(0) < 16) return false;

    auto ip = _$<v_cs>(0);
    complex16* cip = (complex16*)ip;
    auto op = $_<unsigned __int8>(0);

    demapper.demap_limit_16qam((v_cs*)ip, 16);

    int i;
    int j = 0;

    for (i = 64 + *low; i < 64; i++)
    {
      if (i == 64 - 21 || i == 64 - 7)
        continue;
      demapper.demap_16qam(cip[i], &op[j]);
      j += 4;
    }

    for (i = 1; i <= *high; i++)
    {
      if (i == 7 || i == 21)
        continue;

      demapper.demap_16qam(cip[i], &op[j]);
      j += 4;
    }

    consume(0, 16);
    produce(0, (*high - *low - 4) * 4);

    return true;
  }
};


DEFINE_BLOCK(b_dot11_demap_64qam_1v1, 1, 1)
{
  _local_(int, low, -26);
  _local_(int, high, 26);

  dsp_demapper demapper;

  BLOCK_INIT
  {
    auto v = $["low"];
    if (!v.empty())
    {
      *low = atoi(v.c_str());
    }
    v = $["high"];
    if (!v.empty())
    {
      *high = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    trace();

    if (ninput(0) < 16) return false;

    auto ip = _$<v_cs>(0);
    complex16* cip = (complex16*)ip;
    auto op = $_<unsigned __int8>(0);

    demapper.demap_limit_64qam((v_cs*)ip, 16);

    int i;
    int j = 0;

    for (i = 64 + *low; i < 64; i++)
    {
      if (i == 64 - 21 || i == 64 - 7)
        continue;
      demapper.demap_64qam(cip[i], &op[j]);
      j += 6;
    }

    for (i = 1; i <= *high; i++)
    {
      if (i == 7 || i == 21)
        continue;

      demapper.demap_64qam(cip[i], &op[j]);
      j += 6;
    }

    consume(0, 16);
    produce(0, (*high - *low - 4) * 6);

    return true;
  }
};