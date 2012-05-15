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


DEFINE_BLOCK(b_dot11n_map_qpsk_1v1, 1, 1)
{
  dsp_mapper_qpsk<complex16> *mapper;

  BLOCK_INIT
  {
    mapper = new dsp_mapper_qpsk<complex16>(complex16(21453, 21453));
  }

  BLOCK_WORK
  {
    int n = ninput(0);
    // need 13 bytes
    if (n < 13) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<dot11n_tx_symbol>(0);

    unsigned int sc_idx = 128 - 26;
    for (int i = 0; i < 13; i++)
    {
      dsp_mapper_qpsk<complex16>::output_type& out = (*mapper)[ip[i]];

      for(int j = 0; j < 4; j++, sc_idx++)
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
    consume(0, 13);
    produce(0, 1);
  }
};


DEFINE_BLOCK(b_dot11n_map_16qam_1v1, 1, 1)
{
  dsp_mapper_16qam<complex16> *mapper;

  BLOCK_INIT
  {
    mapper = new dsp_mapper_16qam<complex16>(complex16(9594, 9594));
  }

  BLOCK_WORK
  {
    int n = ninput(0);
    // need 26 bytes
    if (n < 26) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<dot11n_tx_symbol>(0);

    unsigned int sc_idx = 128 - 26;
    for (int i = 0; i < 26; i++)
    {
      dsp_mapper_16qam<complex16>::output_type& out = (*mapper)[ip[i]];

      for(int j = 0; j < 2; j++, sc_idx++)
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
    consume(0, 26);
    produce(0, 1);
  }
};

DEFINE_BLOCK(b_dot11n_map_64qam_1v1, 1, 1)
{
  typedef dsp_mapper_64qam<complex16> mapper_type;
  mapper_type *mapper;

  BLOCK_INIT
  {
    mapper = new mapper_type(complex16(4681, 4681));
  }

  BLOCK_WORK
  {
    int n = ninput(0);
    // need 39 bytes
    if (n < 39) return false;

    auto ip = _$<uint8>(0);
    auto op = $_<dot11n_tx_symbol>(0);

    unsigned int sc_idx = 128 - 26;
    for (int i = 0; i < 39; i += 3)
    {
      uint32 lo = ip[i];
      uint32 hi = (ip[i + 1] & 0x0F);
      uint32 bt = lo | (hi << 8);

      mapper_type::output_type& out = (*mapper)[bt];

      for(int j = 0; j < 2; j++, sc_idx++)
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

      lo = (ip[i + 1] & 0xF0);
      hi = ip[i + 2];
      bt = hi | (lo >> 8);

      for(int j = 0; j < 2; j++, sc_idx++)
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
    consume(0, 39);
    produce(0, 1);
  }
};