struct HT_SIG 
{
    static const int SIZE = 6;

    struct sig_format
    {
      unsigned __int8 mcs : 7;
      unsigned __int8 cbw : 1;

      unsigned __int16 length;

      unsigned __int8 smoothing : 1;
      unsigned __int8 notsounding : 1;
      unsigned __int8 reserved : 1; // value is 1
      unsigned __int8 aggregation : 1;
      unsigned __int8 stbc : 2;
      unsigned __int8 feccoding : 1;
      unsigned __int8 shortgi : 1;

      unsigned __int16 nes : 2; // number of extension spatial streams
      unsigned __int16 crc8 : 8;
      unsigned __int16 tail : 6;
    };

    union
    {
      sig_format  fmt;
      unsigned __int8 cdata[6];
      struct
      {
        unsigned __int32 lo4;
        unsigned __int16 hi2;
      };
    };

    crc::crc8 _crc8;

    __forceinline void clear()
    {
        lo4 = 0; hi2 = 0;
    }

    __forceinline void zerotail()
    {
        hi2 &= 0x03FF; // zero tailing bits
    }

    __forceinline void update(unsigned __int32 msc, unsigned __int32 uLength)
    {
      cdata[0] = (uint8)msc;
      *(unsigned __int16 *)&cdata[1] = (uint16)uLength;
      cdata[3] = 3;

      // calc crc8
      _crc8.reset();
      _crc8(cdata, 4);
      _crc8(cdata[4], 2);

      cdata[4] |= (_crc8.value() << 2);
      cdata[5] |= (_crc8.value() >> 6);
    }
};