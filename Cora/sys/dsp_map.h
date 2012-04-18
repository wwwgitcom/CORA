#pragma once


template<typename complexT>
struct dsp_mapper_bpsk
{
  static const int lut_size = 256;

  struct output_type
  {
    complexT values[8];
  };

  complexT one;

  dsp_mapper_bpsk(complexT _one) : one(_one)
  {
    create_lookuptable();
  }

  __forceinline output_type& operator[](unsigned __int8 input)
  {
    return lookuptable[input];
  }

private:
  output_type lookuptable[lut_size];

  void create_lookuptable()
  {
    for (int i = 0; i < lut_size; i++)
    {
      unsigned __int8 inputbyte = static_cast<unsigned __int8>(i);
      for (int j = 0; j < 8; j++)
      {
        if ((inputbyte >> j) & 0x01)
        {
          lookuptable[i].values[j] = one;
        }
        else
        {
          lookuptable[i].values[j] = -one;
        }
      }
    }
  }

  dsp_mapper_bpsk(){}
  dsp_mapper_bpsk(dsp_mapper_bpsk &){}
};

template<typename complexT>
struct dsp_mapper_qpsk
{
  static const int lut_size = 256;

  struct output_type
  {
    complexT values[4];
  };
  complexT one;

  dsp_mapper_qpsk(complexT _one) : one(_one)
  {
    create_lookuptable();
  }

  __forceinline output_type& operator[](unsigned __int8 input)
  {
    return lookuptable[input];
  }

private:
  output_type lookuptable[lut_size];

  void create_lookuptable()
  {
    for (int i = 0; i < lut_size; i++)
    {
      unsigned __int8 inputbyte = static_cast<unsigned __int8>(i);
      for (int j = 0; j < 4; j++)
      {
        unsigned __int8 v = ((inputbyte >> (j * 2)) & 0x03);
        switch (v)
        {
        case 0:
          lookuptable[i].values[j] = -one;
          break;
        case 1:
          lookuptable[i].values[j] = one.conj_im();
          break;
        case 2:
          lookuptable[i].values[j] = one.conj_re();
          break;
        case 3:
          lookuptable[i].values[j] = one;
          break;
        }
      }
    }
  }

  dsp_mapper_qpsk(){}
  dsp_mapper_qpsk(dsp_mapper_qpsk &){}
};

template<typename complexT>
struct dsp_mapper_16qam
{
  static const int lut_size = 256;

  struct output_type
  {
    complexT values[2];
  };
  complexT one;

  dsp_mapper_16qam(complexT _one) : one(_one)
  {
    create_lookuptable();
  }

  __forceinline output_type& operator[](unsigned __int8 input)
  {
    return lookuptable[input];
  }

private:
  output_type lookuptable[lut_size];

  void create_lookuptable()
  {
    for (int i = 0; i < lut_size; i++)
    {
      unsigned __int8 inputbyte = static_cast<unsigned __int8>(i);
      for (int j = 0; j < 2; j++)
      {
        unsigned __int8 v = ((inputbyte >> (j * 4)) & 0x0F);
        switch (v)
        {
        case 0:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * -3);
          break;
        case 1:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * -3);
          break;
        case 2:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * -3);
          break;
        case 3:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * -3);
          break;
        case 4:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * 3);
          break;
        case 5:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * 3);
          break;
        case 6:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * 3);
          break;
        case 7:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * 3);
          break;
        case 8:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * -1);
          break;
        case 9:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * -1);
          break;
        case 10:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * -1);
          break;
        case 11:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * -1);
          break;
        case 12:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * 1);
          break;
        case 13:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * 1);
          break;
        case 14:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * 1);
          break;
        case 15:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * 1);
          break;
        }
      }
    }
  }

  dsp_mapper_16qam(){}
  dsp_mapper_16qam(dsp_mapper_16qam &){}
};

template<typename complexT>
struct dsp_mapper_64qam
{
  static const int lut_size = 1024 * 4;

  struct output_type
  {
    complexT values[2];
  };
  complexT one;

  dsp_mapper_64qam(complexT _one) : one(_one)
  {
    create_lookuptable();
  }

  __forceinline output_type& operator[](unsigned __int16 input)
  {
    return lookuptable[input];
  }

private:
  output_type lookuptable[lut_size];

  void create_lookuptable()
  {
    for (int i = 0; i < lut_size; i++)
    {
      unsigned __int16 inputvalue = static_cast<unsigned __int16>(i);
      for (int j = 0; j < 2; j++)
      {
        unsigned __int16 v = ((inputvalue >> (j * 6)) & 0x3F);
        switch (v)
        {
        case 0:
          lookuptable[i].values[j] = complexT(one.re * -7, one.im * -7);
          break;
        case 1:
          lookuptable[i].values[j] = complexT(one.re * 7, one.im * -7);
          break;
        case 2:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * -7);
          break;
        case 3:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * -7);
          break;
        case 4:
          lookuptable[i].values[j] = complexT(one.re * -5, one.im * -7);
          break;
        case 5:
          lookuptable[i].values[j] = complexT(one.re * 5, one.im * -7);
          break;
        case 6:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * -7);
          break;
        case 7:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * -7);
          break;

        case 8:
          lookuptable[i].values[j] = complexT(one.re * -7, one.im * 7);
          break;
        case 9:
          lookuptable[i].values[j] = complexT(one.re * 7, one.im * 7);
          break;
        case 10:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * 7);
          break;
        case 11:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * 7);
          break;
        case 12:
          lookuptable[i].values[j] = complexT(one.re * -5, one.im * 7);
          break;
        case 13:
          lookuptable[i].values[j] = complexT(one.re * 5, one.im * 7);
          break;
        case 14:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * 7);
          break;
        case 15:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * 7);
          break;

        case 16:
          lookuptable[i].values[j] = complexT(one.re * -7, one.im * -1);
          break;
        case 17:
          lookuptable[i].values[j] = complexT(one.re * 7, one.im * -1);
          break;
        case 18:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * -1);
          break;
        case 19:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * -1);
          break;
        case 20:
          lookuptable[i].values[j] = complexT(one.re * -5, one.im * -1);
          break;
        case 21:
          lookuptable[i].values[j] = complexT(one.re * 5, one.im * -1);
          break;
        case 22:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * -1);
          break;
        case 23:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * -1);
          break;

        case 24:
          lookuptable[i].values[j] = complexT(one.re * -7, one.im * 1);
          break;
        case 25:
          lookuptable[i].values[j] = complexT(one.re * 7, one.im * 1);
          break;
        case 26:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * 1);
          break;
        case 27:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * 1);
          break;
        case 28:
          lookuptable[i].values[j] = complexT(one.re * -5, one.im * 1);
          break;
        case 29:
          lookuptable[i].values[j] = complexT(one.re * 5, one.im * 1);
          break;
        case 30:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * 1);
          break;
        case 31:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * 1);
          break;

        case 32:
          lookuptable[i].values[j] = complexT(one.re * -7, one.im * -5);
          break;
        case 33:
          lookuptable[i].values[j] = complexT(one.re * 7, one.im * -5);
          break;
        case 34:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * -5);
          break;
        case 35:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * -5);
          break;
        case 36:
          lookuptable[i].values[j] = complexT(one.re * -5, one.im * -5);
          break;
        case 37:
          lookuptable[i].values[j] = complexT(one.re * 5, one.im * -5);
          break;
        case 38:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * -5);
          break;
        case 39:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * -5);
          break;

        case 40:
          lookuptable[i].values[j] = complexT(one.re * -7, one.im * 5);
          break;
        case 41:
          lookuptable[i].values[j] = complexT(one.re * 7, one.im * 5);
          break;
        case 42:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * 5);
          break;
        case 43:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * 5);
          break;
        case 44:
          lookuptable[i].values[j] = complexT(one.re * -5, one.im * 5);
          break;
        case 45:
          lookuptable[i].values[j] = complexT(one.re * 5, one.im * 5);
          break;
        case 46:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * 5);
          break;
        case 47:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * 5);
          break;

        case 48:
          lookuptable[i].values[j] = complexT(one.re * -7, one.im * -3);
          break;
        case 49:
          lookuptable[i].values[j] = complexT(one.re * 7, one.im * -3);
          break;
        case 50:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * -3);
          break;
        case 51:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * -3);
          break;
        case 52:
          lookuptable[i].values[j] = complexT(one.re * -5, one.im * -3);
          break;
        case 53:
          lookuptable[i].values[j] = complexT(one.re * 5, one.im * -3);
          break;
        case 54:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * -3);
          break;
        case 55:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * -3);
          break;

        case 56:
          lookuptable[i].values[j] = complexT(one.re * -7, one.im * 3);
          break;
        case 57:
          lookuptable[i].values[j] = complexT(one.re * 7, one.im * 3);
          break;
        case 58:
          lookuptable[i].values[j] = complexT(one.re * -1, one.im * 3);
          break;
        case 59:
          lookuptable[i].values[j] = complexT(one.re * 1, one.im * 3);
          break;
        case 60:
          lookuptable[i].values[j] = complexT(one.re * -5, one.im * 3);
          break;
        case 61:
          lookuptable[i].values[j] = complexT(one.re * 5, one.im * 3);
          break;
        case 62:
          lookuptable[i].values[j] = complexT(one.re * -3, one.im * 3);
          break;
        case 63:
          lookuptable[i].values[j] = complexT(one.re * 3, one.im * 3);
          break;
        }
      }
    }
  }

  dsp_mapper_64qam(){}
  dsp_mapper_64qam(dsp_mapper_64qam &){}
};
