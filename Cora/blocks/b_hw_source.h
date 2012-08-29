#pragma once


__forceinline
  HRESULT 
  SORAAPI
  _SoraRadioReadRxStream(
  PSORA_RADIO_RX_STREAM pRxStream,
  FLAG * pbTouched,
  signal_block* &block)
{
  PRX_BLOCK pbScanPoint = SoraRadioGetRxStreamPos(pRxStream);
  HRESULT hr = 
    SoraCheckSignalBlock(pbScanPoint, SoraGetStreamVStreamMask(pRxStream), SORA_MAX_RX_SPIN_WAIT, pbTouched);
  if (FAILED(hr)) 
    return hr; // hardware error

  block = (signal_block*)pbScanPoint;

  // Advance scan ponter
  __SoraRadioAdvanceRxStreamPos(pRxStream);
  return hr;
}


DEFINE_BLOCK(b_hw_source_v1, 0, 1)
{
  BOOLEAN     bHWInitOK;
  PVOID				RxBuffer;	// Mapped Rx Buffer
  ULONG				RxBufferSize;
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
    HRESULT		hr;

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

    hr = SoraURadioMapRxSampleBuf(TARGET_RADIO, &RxBuffer, &RxBufferSize);
    if (FAILED(hr)) {
      printf ( "Fail to map rx buffer!\n" );
      return;
    }

    hr = SoraURadioAllocRxStream(&RxStream, TARGET_RADIO, (PUCHAR)RxBuffer, RxBufferSize);
    if (FAILED(hr)) {
      printf("SoraAllocRadioRxStream ret: %08x\n", hr);
    }

    signal_block *sigblk = nullptr;
    FLAG bTouched = false;
    do 
    {
      hr = _SoraRadioReadRxStream(&RxStream, &bTouched, sigblk);
    } while (!bTouched);
  }

  BLOCK_INIT
  {
    bHWInitOK = SoraUInitUserExtension("\\\\.\\HWTest");
    if (!bHWInitOK) {
      printf ( "Error: fail to find the hwtest driver!\n" );
    }

    ConfigureRadio();
  }

  
  BLOCK_WORK
  {
    if (!bHWInitOK)
    {
      return false;
    }

    auto n = noutput(0);
    if (n < 7) return false;

    auto op = $_<v_cs>(0);
    signal_block *sigblk = nullptr;
    
    HRESULT hr;
    FLAG bTouched = false;

    hr = _SoraRadioReadRxStream(&RxStream, &bTouched, sigblk);

    if ( SUCCEEDED (hr) ) 
    {
      for (int i = 0; i < 7; i++)
      {
        op[i] = (*sigblk)[i];
      }
    }
    else
    {
      return false;
    }

    produce(0, 7);
    return true;
  }
};