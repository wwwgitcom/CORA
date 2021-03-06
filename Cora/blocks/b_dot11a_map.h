#pragma once

DEFINE_BLOCK(b_dot11a_map_bpsk_q_1v1, 1, 1)
{
  dsp_mapper_bpsk<complex16> *mapper;

  BLOCK_INIT
  {
    mapper = new dsp_mapper_bpsk<complex16>(complex16(0, 30339));
  }

  BLOCK_WORK
  {
    int n = ninput(0);
    // need 6 bytes contained in 1 v_ub
    if (n < 1) return false;

    auto ip = _$<v_ub>(0);
    uint8* p = reinterpret_cast<uint8*>(ip);
    auto op = $_<dot11n_tx_symbol>(0);

    memset(op, 0, sizeof(dot11n_tx_symbol));

    unsigned int sc_idx = 128 - 26;
    for (int i = 0; i < 6; i++)
    {
      dsp_mapper_bpsk<complex16>::output_type& out = (*mapper)[p[i]];

      for(int j = 0; j < 8; j++, sc_idx++)
      {
        if (sc_idx == 7 || sc_idx == 21)
        {
          sc_idx++;
        }
        else if (sc_idx == (128 - 7) || sc_idx == (128 - 21))
        {
          sc_idx++;
        }
        else if (sc_idx == 128)
        {
          sc_idx = 1;
        }
        op[0].subcarriers[sc_idx] = out.values[j];
      }
    }

    consume(0, 1);
    produce(0, 1);
    return true;
  }
};

DEFINE_BLOCK(b_dot11a_map_bpsk_i_1v1, 1, 1)
{
  dsp_mapper_bpsk<complex16> *mapper;

  BLOCK_INIT
  {
    mapper = new dsp_mapper_bpsk<complex16>(complex16(30339, 0));
  }

  BLOCK_WORK
  {
    int n = ninput(0);
    // need 6 bytes contained in 1 v_ub
    if (n < 1) return false;

    auto ip = _$<v_ub>(0);
    uint8* p = reinterpret_cast<uint8*>(ip);
    auto op = $_<dot11n_tx_symbol>(0);

    memset(op, 0, sizeof(dot11n_tx_symbol));

    unsigned int sc_idx = 128 - 26;
    for (int i = 0; i < 6; i++)
    {
      dsp_mapper_bpsk<complex16>::output_type& out = (*mapper)[p[i]];

      for(int j = 0; j < 8; j++, sc_idx++)
      {
        if (sc_idx == 7 || sc_idx == 21)
        {
          sc_idx++;
        }
        else if (sc_idx == (128 - 7) || sc_idx == (128 - 21))
        {
          sc_idx++;
        }
        else if (sc_idx == 128)
        {
          sc_idx = 1;
        }
        op[0].subcarriers[sc_idx] = out.values[j];
      }
    }

    consume(0, 1);
    produce(0, 1);
    return true;
  }
};
