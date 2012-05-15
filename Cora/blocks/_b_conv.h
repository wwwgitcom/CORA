#pragma once

struct conv_1_2
{
  static const int input_size = (0x1 << 14);
  static const int lut_size   = input_size;

  conv_1_2(unsigned __int16 conv_register) : _conv_register(conv_register){}

  __forceinline unsigned __int16 operator()(unsigned __int8 &ubInput)
  {
    unsigned __int16 usOutput;

    usOutput       = lookup_table[((_conv_register << 8) | ubInput)];
    _conv_register = (ubInput >> 2);

    return usOutput;
  }

  __forceinline void operator()(unsigned __int8 &ubInput, unsigned __int16 &usOutput)
  {
    usOutput       = lookup_table[((_conv_register << 8) | ubInput)];
    _conv_register = (ubInput >> 2);
  }

  __forceinline void operator()(unsigned __int8 *ubInput, unsigned __int8 *ubOutput)
  {
    *((unsigned __int16*)ubOutput) = lookup_table[((_conv_register << 8) | *ubInput)];
    _conv_register = (*ubInput >> 2);
  }

  void reset(unsigned __int16 conv_register)
  {
    _conv_register = conv_register;
  }

private:
  unsigned __int16 _conv_register;
  static const unsigned __int16 lookup_table[lut_size];
};

struct conv_2_3
{
  static const int input_size = (0x1 << 14);
  static const int lut_size   = input_size;

  conv_2_3(unsigned __int16 conv_register) : _conv_register(conv_register){}

  __forceinline void operator()(unsigned __int8 pubInput[2], unsigned __int8 pubOutput[3])
  {
    unsigned __int16 b1, b2;
    unsigned __int16 l1, l2;

    b1 = (pubInput[0] << 6) | (_conv_register);
    b2 = (pubInput[1] << 6) | (pubInput[0] >> 2);

    l1 = lookup_table[b1];
    l2 = lookup_table[b2];

    pubOutput[0] = l1 & 0xff;
    pubOutput[1] = (l1 >> 8) | (l2 << 4);
    pubOutput[2] = (l2 >> 4);

    _conv_register = (pubInput[1] >> 2);
  }

  void reset(unsigned __int16 conv_register)
  {
    _conv_register = conv_register;
  }

private:
  unsigned __int16 _conv_register;
  static const unsigned __int16 lookup_table[lut_size];
};

struct conv_3_4
{
  static const int input_size = (0x1 << 12);
  static const int lut_size   = input_size;

  conv_3_4(unsigned __int16 conv_register) : _conv_register(conv_register){}

  __forceinline void operator()(unsigned __int8 pubInput[3], unsigned __int8 pubOutput[4])
  {
    unsigned char c1, c2, c3;
    unsigned short b1, b2, b3, b4;

    c1 = (unsigned char)(pubInput[0]);
    c2 = (unsigned char)(pubInput[1]);
    c3 = (unsigned char)(pubInput[2]);

    b1 = ((c1 & 0x3F) << 6) | _conv_register;
    b2 = ((c2 & 0xF) << 8) | c1;
    b3 = ((c3 & 0x3) << 10) | (c2 << 2) | (c1 >> 6);
    b4 = (c3 << 4) | (c2 >> 4);

    _conv_register = (c3 >> 2);

    pubOutput[0] = lookup_table[b1];
    pubOutput[1] = lookup_table[b2];
    pubOutput[2] = lookup_table[b3];
    pubOutput[3] = lookup_table[b4];
  }

  void reset(unsigned __int16 conv_register)
  {
    _conv_register = conv_register;
  }

private:
  unsigned __int16 _conv_register;
  static const unsigned __int8 lookup_table[lut_size];
};