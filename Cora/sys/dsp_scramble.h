#pragma once


namespace scrambler
{
  struct dot11a_scrambler
  {
    static const int input_size = 0x1 << 7;
    static const int input_unit = 1;
    static const int lut_size   = input_unit * input_size;

    unsigned __int8 _scrambler_register;

    dot11a_scrambler(unsigned __int8 scrambler_register) : _scrambler_register(scrambler_register){}

    __forceinline unsigned __int8 operator()(unsigned __int8 &ubInput)
    {
      return ( ubInput ^ (_scrambler_register = lookup_table[_scrambler_register >> 1]) );
    }

    __forceinline void operator()(unsigned __int8 &ubInput, unsigned __int8 &ubOutput)
    {
      ubOutput = ( ubInput ^ (_scrambler_register = lookup_table[_scrambler_register >> 1]) );
    }

    __forceinline void reset(unsigned __int8 scrambler_register)
    {
      _scrambler_register = scrambler_register;
    }

  private:
    static const unsigned __int8 lookup_table[lut_size];
  };

  struct dot11n_scrambler : dot11a_scrambler
  {
    dot11n_scrambler(unsigned __int8 scrambler_register) : dot11a_scrambler(scrambler_register){}
  };

  //////////////////////////////////////////////////////////////////////////

  struct dot11b_scrambler
  {
    static const int lut_size_x = 256;
    static const int lut_size_y = 128;

    unsigned __int8 _scrambler_register;

    dot11b_scrambler(unsigned __int8 scrambler_register) : _scrambler_register(scrambler_register){}

    __forceinline unsigned __int8 operator()(unsigned __int8 &ubInput)
    {
      unsigned __int8 ubOutput;
      ubOutput            = lookup_table[ ubInput ][_scrambler_register];
      _scrambler_register = ubOutput >> 1;

      return ubOutput;
    }

    __forceinline void operator()(unsigned __int8 &ubInput, unsigned __int8 &ubOutput)
    {
      ubOutput            = lookup_table[ ubInput ][_scrambler_register];
      _scrambler_register = ubOutput >> 1;
    }

    __forceinline void reset(unsigned __int8 scrambler_register)
    {
      _scrambler_register = scrambler_register;
    }

  private:
    static const unsigned __int8 lookup_table[lut_size_x][lut_size_y];
  };
}

namespace descrambler
{
  struct dot11a_descrambler : scrambler::dot11a_scrambler
  {
    dot11a_descrambler(unsigned __int8 scrambler_register) : scrambler::dot11a_scrambler(scrambler_register){}
  };

  struct dot11n_descrambler : dot11a_descrambler
  {
    dot11n_descrambler(unsigned __int8 scrambler_register) : dot11a_descrambler(scrambler_register){}
  };

  struct dot11b_descrambler
  {
    static const int lut_size_x = 256;
    static const int lut_size_y = 128;

    unsigned __int8 _descrambler_register;

    dot11b_descrambler(unsigned __int8 descrambler_register) : _descrambler_register(descrambler_register){}

    __forceinline unsigned __int8 operator()(unsigned __int8 &ubInput)
    {
      unsigned __int8 ubOutput;
      ubOutput              = lookup_table[ ubInput ][_descrambler_register];
      _descrambler_register = ubOutput >> 1;

      return ubOutput;
    }

    __forceinline void operator()(unsigned __int8 &ubInput, unsigned __int8 &ubOutput)
    {
      ubOutput              = lookup_table[ ubInput ][_descrambler_register];
      _descrambler_register = ubOutput >> 1;
    }

    __forceinline void reset(unsigned __int8 descrambler_register)
    {
      _descrambler_register = descrambler_register;
    }

  private:
    static const unsigned __int8 lookup_table[lut_size_x][lut_size_y];
  };
}