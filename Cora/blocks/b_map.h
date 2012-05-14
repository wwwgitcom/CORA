#pragma once


DEFINE_BLOCK(b_dot11n_mcs8_map_bpsk_i_1v1, 1, 1)
{
  dsp_mapper_bpsk<complex16> *mapper;

  BLOCK_INIT
  {
    mapper = new dsp_mapper_bpsk<complex16>(complex16(30339, 0));
  }

  BLOCK_WORK
  {
    int n = ninput(0);
    // need 6.5 bytes
    if (n < 7) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<dot11n_tx_symbol>(0);

    unsigned int sc_idx = 100;
    for (int i = 0; i < 6; i++)
    {
      dsp_mapper_bpsk<complex16>::output_type& out = (*mapper)[ip[i]];

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

    dsp_mapper_bpsk<complex16>::output_type& out = (*mapper)[ip[6]];
    for (int j = 0; j < 4; j++, sc_idx++)
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

    consume(0, 7);
    produce(0, 1);
  }
};

DEFINE_BLOCK(b_map_bpsk_q_1v1, 1, 1)
{
  dsp_mapper_bpsk<complex16> *mapper;

  BLOCK_INIT
  {
    mapper = new dsp_mapper_bpsk<complex16>(complex16(0, 30339));
  }

  BLOCK_WORK
  {
    int n = ninput(0);
    // need 6 bytes
    if (n < 6) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<dot11n_tx_symbol>(0);

    unsigned int sc_idx = 128 - 26;
    for (int i = 0; i < 6; i++)
    {
      dsp_mapper_bpsk<complex16>::output_type& out = (*mapper)[ip[i]];

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

    consume(0, 6);
    produce(0, 1);
  }
};


DEFINE_BLOCK(b_map_qpsk_1v1, 1, 1)
{
  dsp_mapper_qpsk<complex16> *mapper;

  BLOCK_INIT
  {
    mapper = new dsp_mapper_qpsk<complex16>(complex16(21453, 21453));
  }

  BLOCK_WORK
  {
    trace();

    int n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<complex16>(0);

    for (int i = 0; i < n; i++)
    {
      autoref out = (*mapper)[i];
      memcpy(op, out.values, sizeof(dsp_mapper_qpsk<complex16>::output_type));
      op += 4;
    }

    consume(0, n);
    produce(0, n * 4);
  }
};


DEFINE_BLOCK(b_map_16qam_1v1, 1, 1)
{
  dsp_mapper_16qam<complex16> *mapper;

  BLOCK_INIT
  {
    mapper = new dsp_mapper_16qam<complex16>(complex16(9594, 9594));
  }

  BLOCK_WORK
  {
    trace();

    int n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<complex16>(0);

    for (int i = 0; i < n; i++)
    {
      dsp_mapper_bpsk<complex16>::output_type& out = (*mapper)[i];
      memcpy(op, out.values, sizeof(dsp_mapper_qpsk<complex16>::output_type));
      op += 4;
    }

    consume(0, n);
    produce(0, n * 4);
  }
};