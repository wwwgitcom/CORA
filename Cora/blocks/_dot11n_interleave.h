
template<int nbpsc>
struct dot11a_interleaver
{
  static_assert((nbpsc == 1 || nbpsc == 2 || nbpsc == 4 || nbpsc == 6), 
    "nbpsc only takes 1, 2, 4, 6");

  static const int total_sc      = 48;
  static const int bit_per_sc    = nbpsc;
  static const int total_bits    = total_sc * bit_per_sc;
  static const int padding_bits  = total_bits % 8;
  static const int padding_bound = padding_bits ? (1 << padding_bits) : 0;
  static const int padding_byte  = (padding_bits > 0);
  static const int total_bytes   = total_bits / 8 + padding_byte;

  static const int block_bits    = (nbpsc / 2) ? (nbpsc / 2) : 1;
  static const int outbuffer_size = 0 + ((total_bytes > 16) ? 16 : 0)
    + ((total_bytes > 32) ? 16 : 0) + ((total_bytes > 48) ? 16 : 0)
    + ((total_bytes & 0x7F) ? 16 : 0);
  static const int voutbuffer_size = outbuffer_size / v_ub::size;

  struct output_type
  {
    v_ub values[voutbuffer_size];
  };

  v_ub::type lookuptable[total_bytes][256][voutbuffer_size];

  void zero_lookuptable()
  {
    memset(lookuptable, 0, total_bytes * 256 * voutbuffer_size * v_ub::size);
  }

  void create_lookuptable()
  {
    for (int iB = 0; iB < (total_bytes - padding_byte); iB++)
    {
      for (int v = 0; v < 256; v++)
      {
        for (int ib = 0; ib < 8; ib++)
        {
          int ibpos = iB * 8 + ib;
          int obpos = 0;
          obpos = interleave(ibpos);

          int oB = obpos / 8;
          int ob = obpos % 8;

          unsigned char ibv = (((unsigned char)v & (1 << ib)) >> ib);
          unsigned char obv = (ibv << ob);
          lookuptable[iB][v][0][oB] |= obv;
        }
      }
    }
  }

  int interleave(int k)
  {
    int temp = round1(k);
    temp     = round2(temp);
    return temp;
  }

  int round1(int k)
  {
    return 3 * bit_per_sc * (k % 16) + k / 16;
  }

  int round2(int k)
  {
    return block_bits * (k / block_bits) + (k + total_bits - (16 * k) / total_bits) % block_bits;
  }
};

struct dot11a_interleaver_1bpsc : dot11a_interleaver<1>
{
  // 48 bits, 6 bytes are valid in the output
  dot11a_interleaver_1bpsc()
  {
    zero_lookuptable();
    create_lookuptable();
  }

  __forceinline void operator()(unsigned char pInput[6], v_ub *Output)
  {
    Output[0] = (v_ub&)lookuptable[0][pInput[0]][0];
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[1][pInput[1]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[2][pInput[2]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[3][pInput[3]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[4][pInput[4]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[5][pInput[5]][0]);
  }
};


//////////////////////////////////////////////////////////////////////////

template<int nbpsc>
struct dot11n_interleaver 
{
  static_assert((nbpsc == 1 || nbpsc == 2 || nbpsc == 4 || nbpsc == 6), 
    "nbpsc only takes 1, 2, 4, 6");

  static const int total_sc      = 52;
  static const int bit_per_sc    = nbpsc;
  static const int total_bits    = total_sc * bit_per_sc;
  static const int padding_bits  = total_bits % 8;
  static const int padding_bound = padding_bits ? (1 << padding_bits) : 0;
  static const int padding_byte  = (padding_bits > 0);
  static const int total_bytes   = total_bits / 8 + padding_byte;

  static const int block_bits    = (nbpsc / 2) ? (nbpsc / 2) : 1;
  static const int outbuffer_size = 0 + ((total_bytes > 16) ? 16 : 0)
    + ((total_bytes > 32) ? 16 : 0) + ((total_bytes > 48) ? 16 : 0)
    + ((total_bytes & 0x7F) ? 16 : 0);
  static const int voutbuffer_size = outbuffer_size / v_ub::size;

  struct output_type
  {
    v_ub values[voutbuffer_size];
  };

  v_ub::type lookuptable[total_bytes][256][voutbuffer_size];

  void zero_lookuptable()
  {
    memset(lookuptable, 0, total_bytes * 256 * voutbuffer_size * v_ub::size);
  }

  void create_lookuptable(int iss)
  {
    for (int iB = 0; iB < (total_bytes - padding_byte); iB++)
    {
      for (int v = 0; v < 256; v++)
      {
        for (int ib = 0; ib < 8; ib++)
        {
          int ibpos = iB * 8 + ib;
          int obpos = 0;
          obpos = interleave(iss, ibpos);

          int oB = obpos / 8;
          int ob = obpos % 8;

          unsigned char ibv = (((unsigned char)v & (1 << ib)) >> ib);
          unsigned char obv = (ibv << ob);
          //printf("%d, %d, %d, %d\n", iB, v, oB, obv);
          lookuptable[iB][v][0][oB] |= obv;
          //printf("%d\n", lookuptable[iB][v][0][oB]);
        }
      }
    }
  }

  int interleave(int iss, int k)
  {
    int temp = round1(k);
    temp     = round2(temp);
    temp     = round3(iss, temp);
    return temp;
  }

  int round1(int k)
  {
    return 4 * bit_per_sc * (k % 13) + k / 13;
  }

  int round2(int k)
  {
    return block_bits * (k / block_bits) + (k + total_bits - (13 * k) / total_bits) % block_bits;
  }

  int round3(int iss, int k)
  {
    return (total_bits + k - ( ( (iss - 1) * 2 ) % 3 + 3 * ((iss - 1) / 3) ) * 11 * bit_per_sc) % total_bits;
  }
};


struct dot11n_interleaver_1bpsc : dot11n_interleaver<1>
{
  // 52 bits, 6.5 bytes are valid in the output
  dot11n_interleaver_1bpsc(){}

  dot11n_interleaver_1bpsc(int iss)
  {
    zero_lookuptable();
    zero_lookuptable_padding();
    create_lookuptable(iss);
    create_lookuptable_padding(iss);
  }

  void init(int iss)
  {
    zero_lookuptable();
    zero_lookuptable_padding();
    create_lookuptable(iss);
    create_lookuptable_padding(iss);
  }

  __forceinline void operator()(unsigned char pInput[7], v_ub *Output)
  {
    Output[0] = (v_ub&)lookuptable[0][pInput[0]][0];
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[1][pInput[1]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[2][pInput[2]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[3][pInput[3]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[4][pInput[4]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[5][pInput[5]][0]);

    Output[0] = v_xor(Output[0], (v_ub&)lookuptable_padding[pInput[6] & 0x0F][0]);
  }

protected:
  v_ub::type lookuptable_padding[padding_bound][voutbuffer_size];

  void zero_lookuptable_padding()
  {
    memset(lookuptable, 0, padding_bound * voutbuffer_size * v_ub::size);
  }

  void create_lookuptable_padding(int iss)
  {
    for (int v = 0; v < padding_bound; v++)
    {
      for (int ib = 0; ib < padding_bits; ib++)
      {
        int ibpos = (total_bytes - padding_byte) * 8 + ib;
        int obpos = 0;
        obpos = interleave(iss, ibpos);

        int oB = obpos / 8;
        int ob = obpos % 8;

        unsigned char ibv = ((v & (1 << ib)) >> ib);
        unsigned char obv = (ibv << ob);
        lookuptable_padding[v][0][oB] |= obv;
      }
    }

    //printf("interleave test\n");
    for (int i = 0; i < total_bits; i++)
    {
      int k = interleave(iss, i);
      //printf("[iss=%d, bpsc=%d]%d==>%d\n", iss, bit_per_sc, i, k);
    }
  }
};

struct dot11n_interleaver_2bpsc : dot11n_interleaver<2>
{
  // 104 bits, 13 bytes are valid in the output
  dot11n_interleaver_2bpsc(){}
  dot11n_interleaver_2bpsc(int iss)
  {
    zero_lookuptable();
    create_lookuptable(iss);
  }
  void init(int iss)
  {
    zero_lookuptable();
    create_lookuptable(iss);
  }

  __forceinline void operator()(unsigned char pInput[13], v_ub *Output)
  {
    Output[0] = (v_ub&)lookuptable[0][pInput[0]][0];
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[1][pInput[1]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[2][pInput[2]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[3][pInput[3]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[4][pInput[4]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[5][pInput[5]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[6][pInput[6]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[7][pInput[7]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[8][pInput[8]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[9][pInput[9]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[10][pInput[10]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[11][pInput[11]][0]);
    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[12][pInput[12]][0]);
  }
};

struct dot11n_interleaver_4bpsc : dot11n_interleaver<4>
{
  // 208 bits, 26 bytes are valid in the output
  dot11n_interleaver_4bpsc(){}
  dot11n_interleaver_4bpsc(int iss)
  {
    zero_lookuptable();
    create_lookuptable(iss);
  }
  void init(int iss)
  {
    zero_lookuptable();
    create_lookuptable(iss);
  }

  __forceinline void operator()(unsigned char pInput[26], v_ub *Output)
  {
    Output[0] = (v_ub&)lookuptable[0][pInput[0]][0];
    Output[1] = (v_ub&)lookuptable[0][pInput[0]][1];

    Output[0] = v_xor(Output[0], (v_ub&)lookuptable[1][pInput[1]][0]);
    Output[1] = v_xor(Output[1], (v_ub&)lookuptable[1][pInput[1]][1]);

#if 1
    for (int i = 2; i < 26; i += 4)
    {
      Output[0] = v_xor(Output[0], (v_ub&)lookuptable[i][pInput[i]][0]);
      Output[1] = v_xor(Output[1], (v_ub&)lookuptable[i][pInput[i]][1]);
      Output[0] = v_xor(Output[0], (v_ub&)lookuptable[i + 1][pInput[i + 1]][0]);
      Output[1] = v_xor(Output[1], (v_ub&)lookuptable[i + 1][pInput[i + 1]][1]);

      Output[0] = v_xor(Output[0], (v_ub&)lookuptable[i + 2][pInput[i + 2]][0]);
      Output[1] = v_xor(Output[1], (v_ub&)lookuptable[i + 2][pInput[i + 2]][1]);
      Output[0] = v_xor(Output[0], (v_ub&)lookuptable[i + 3][pInput[i + 3]][0]);
      Output[1] = v_xor(Output[1], (v_ub&)lookuptable[i + 3][pInput[i + 3]][1]);
    }
#endif
  }
};

struct dot11n_interleaver_6bpsc : dot11n_interleaver<6>
{
  // 312 bits, 39 bytes are valid in the output
  dot11n_interleaver_6bpsc(){}
  dot11n_interleaver_6bpsc(int iss)
  {
    zero_lookuptable();
    create_lookuptable(iss);
  }
  void init(int iss)
  {
    zero_lookuptable();
    create_lookuptable(iss);
  }

  __forceinline void operator()(unsigned char pInput[39], v_ub *Output)
  {
    Output[0] = (v_ub&)lookuptable[0][pInput[0]][0];
    Output[1] = (v_ub&)lookuptable[0][pInput[0]][1];
    Output[2] = (v_ub&)lookuptable[0][pInput[0]][2];

    for (int i = 1; i < 39; i += 2)
    {
      Output[0] = v_xor(Output[0], (v_ub&)lookuptable[i][pInput[i]][0]);
      Output[1] = v_xor(Output[1], (v_ub&)lookuptable[i][pInput[i]][1]);
      Output[2] = v_xor(Output[2], (v_ub&)lookuptable[i][pInput[i]][2]);
      Output[0] = v_xor(Output[0], (v_ub&)lookuptable[i + 1][pInput[i + 1]][0]);
      Output[1] = v_xor(Output[1], (v_ub&)lookuptable[i + 1][pInput[i + 1]][1]);
      Output[2] = v_xor(Output[2], (v_ub&)lookuptable[i + 1][pInput[i + 1]][2]);
    }
  }
};