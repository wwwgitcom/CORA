#pragma once


DEFINE_BLOCK(b_hw_sink_1v, 1, 0)
{
  BOOLEAN     bHWInitOK;
  // Modulation sample buffer
  PVOID				SampleBuffer;
  ULONG				SampleSize; // 4MB
  SORA_RADIO_RX_STREAM	RxStream;	// RxStream
#define MAX_RX_GAIN 56
#define MIN_RX_GAIN 2
  ULONG       RxPa;  // 2450 specific
  ULONG       RxG;  // 2450 specific
  enum 
  {
    TARGET_RADIO = 0
  };

  static const int ChannelFreq = 2422;

  void ConfigureRadio () 
  {
    // Start Radio
    SoraURadioStart (TARGET_RADIO);

    Sleep (10);

    SoraURadioSetCentralFreq (TARGET_RADIO, ChannelFreq * 1000);

    // Set Tx Gain to a fixed value
    SoraURadioSetTxGain ( TARGET_RADIO, 0x1500 ); // 21 dBm

    // Set the Receiver Gain
    ULONG RxGain = MAX_RX_GAIN; 
    int G = (RxGain+1) / 2;
    if ( G <= 9 ) {
      RxPa = 0X1000;
      RxG  = G*0x200;
    } else if ( G <= 17 ) {
      RxPa = 0X2000;
      RxG  = (G-8)*0x200;
    } else {
      RxPa = 0X3000;
      RxG  = (G-16)*0x200;
    }

    SoraURadioSetRxPA	(TARGET_RADIO, RxPa);  // 0dB
    SoraURadioSetRxGain (TARGET_RADIO, RxG);   // 2G dB

    SampleSize = 4 * 1024 * 1024;
    printf("SampleBufferSize=%d\n", SampleSize);
    SampleBuffer = SoraUForceAllocContinuousBuffer(SampleSize);
    if (!SampleBuffer) {
      printf ( "SoraUForceAllocContinuousBuffer Fails...\n" );
      SampleBuffer = SoraUAllocBuffer(SampleSize);
      if (!SampleBuffer) {
        printf ( "SoraUAllocBuffer Fails...\n" );
      }
      else
      {
        printf ( "SoraUAllocBuffer OK...%p\n", SampleBuffer );
      }
    }
  }

  BLOCK_INIT
  {
    bHWInitOK = SoraUInitUserExtension("\\\\.\\HWTest");
    if (!bHWInitOK) {
      printf ( "Error: fail to find the hwtest driver!\n" );
      return;
    }

    ConfigureRadio();
  }


  BLOCK_WORK
  {
    if (!bHWInitOK)
    {
      return false;
    }

    auto n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<v_cb>(0);
    auto op = (v_cb*)(SampleBuffer);

    memcpy(op, ip, n * v_cb::size);

    ULONG SignalLength = n * v_cb::size;
    ULONG SignalID = 0;
    HRESULT hr = SoraURadioTransferEx(TARGET_RADIO, SampleBuffer, SignalLength, &SignalID);
    if (SUCCEEDED(hr))
    {      
      SoraURadioTx(TARGET_RADIO, SignalID);
      SoraURadioTxFree(TARGET_RADIO, SignalID);
    }
    else
    {
      printf("Sora radio transferEx failed, 0x%p.\n", hr);
    }

    consume(0, n);

    return true;
  }
};