#pragma once

namespace crc
{
  //////////////////////////////////////////////////////////////////////////
  //unsigned char testinput[] = {0x8f, 0x64, 0x00, 0x07, 0x00};
  // total 34 bits for 802.11n test, crc=0x15
  struct crc8
  {
    static const int lut_size       = 256;
    static const unsigned char poly = 0xE0;

    unsigned __int8 _crc_register;

    crc8() : _crc_register(0xFF){}

    void reset(){_crc_register = 0xFF;}

    __forceinline void operator()(unsigned __int8 &ubInput)
    {
      _crc_register = lookup_table[ubInput ^ _crc_register];
    }

    __forceinline unsigned __int8 value(){ return ~ _crc_register; }

    __forceinline unsigned __int8 operator()(unsigned __int8 *pubInput, int nInputBytes)
    {
      int i = 0;
      for ( ; i < nInputBytes; i += 4)
      {
        this->operator()(pubInput[i + 0]);
        this->operator()(pubInput[i + 1]);
        this->operator()(pubInput[i + 2]);
        this->operator()(pubInput[i + 3]);
      }

      for (int j = 0; j < (nInputBytes & 0x3); j++)
      {
        this->operator()(pubInput[i + j]);
      }

      return this->value();
    }

    __forceinline void operator()(unsigned __int8 ubInput, int nBits)
    {
      _crc_register ^= ubInput;
      for(int i = 0; i< nBits; i++)
      {
        if(_crc_register & 1 )
          _crc_register = (_crc_register >> 1) ^ poly;
        else
          _crc_register >>= 1;
      }
    }

  private:
    static const unsigned __int8 lookup_table[lut_size];
    unsigned char calc(unsigned char *pInput, int nInput)
    {
      unsigned char  tempcrc=0xFF;
      unsigned char genPoly = 0xE0;

      for (int j = 0; j < nInput; j++)
      {
        unsigned char c = pInput[j];
        tempcrc ^= c;
        // the for-loop can be optimized by lookup table
        for(int i = 0; i<8; i++)
        {
          if(tempcrc & 1 )
            tempcrc = (tempcrc >> 1) ^ genPoly;
          else
            tempcrc >>= 1;
        }
        tempcrc &= 0xff;
      }

      return ~tempcrc;
    }
  };

  //////////////////////////////////////////////////////////////////////////

  struct crc16
  {
    static const int lut_size   = 256;

    unsigned __int16 _crc_register;

    crc16() : _crc_register(0xFFFF){}

    __forceinline void operator()(unsigned __int8 &ubInput)
    {
      _crc_register = ((_crc_register >> 8) & 0x00FF) ^ lookup_table[(_crc_register & 0x00FF) ^ (ubInput & 0x00FF)];;
    }

    __forceinline unsigned __int16 value(){ return ~ _crc_register; }

    __forceinline unsigned __int16 operator()(unsigned __int8 *pubInput, int nInputBytes)
    {
      int i = 0;
      for ( ; i < nInputBytes; i += 4)
      {
        this->operator()(pubInput[i + 0]);
        this->operator()(pubInput[i + 1]);
        this->operator()(pubInput[i + 2]);
        this->operator()(pubInput[i + 3]);
      }

      for (int j = 0; j < (nInputBytes & 0x3); j++)
      {
        this->operator()(pubInput[i + j]);
      }

      return this->value();
    }

  private:
    static const unsigned __int16 lookup_table[lut_size];
  };

  //////////////////////////////////////////////////////////////////////////
  struct crc32
  {
    static const int lut_size   = 256;

    unsigned __int32 _crc_register;

    crc32() : _crc_register(0xFFFFFFFF){}

    __forceinline void reset(){_crc_register = 0xFFFFFFFF;}

    __forceinline unsigned __int32 value(){ return ~ _crc_register; }

    __forceinline void operator()(unsigned __int8 &ubInput)
    {
      _crc_register = ((_crc_register ) >> 8 ) ^ lookup_table[ubInput ^ (_crc_register & 0x000000FF )];
    }

    __forceinline unsigned __int32 operator()(unsigned __int8 *pubInput, int nInputBytes)
    {
      int i = 0;
      for ( ; i < nInputBytes; i += 4)
      {
        this->operator()(pubInput[i + 0]);
        this->operator()(pubInput[i + 1]);
        this->operator()(pubInput[i + 2]);
        this->operator()(pubInput[i + 3]);
      }

      for (int j = 0; j < (nInputBytes & 0x3); j++)
      {
        this->operator()(pubInput[i + j]);
      }

      return this->value();
    }

  private:
    static const unsigned __int32 lookup_table[lut_size];
  };
}