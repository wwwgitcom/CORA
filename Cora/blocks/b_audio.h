#pragma once

#include "Audioclient.h"
#include "Mmdeviceapi.h"

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
const IID IID_IAudioClient = __uuidof(IAudioClient);
const IID IID_IAudioCaptureClient = __uuidof(IAudioCaptureClient);

DEFINE_BLOCK(b_audio_v1, 0, 1)
{


#define REFTIMES_PER_SEC  10000000
#define REFTIMES_PER_MILLISEC  10000

#define EXIT_ON_ERROR(hres)  \
  if (FAILED(hres)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
  if ((punk) != NULL)  \
  { (punk)->Release(); (punk) = NULL; }

  HRESULT hr;
  REFERENCE_TIME hnsRequestedDuration;
  REFERENCE_TIME hnsActualDuration;
  UINT32 bufferFrameCount;
  UINT32 numFramesAvailable;
  IMMDeviceEnumerator *pEnumerator;
  IMMDevice *pDevice;
  IAudioClient *pAudioClient;
  IAudioCaptureClient *pCaptureClient;
  WAVEFORMATEX *pwfx;
  UINT32 packetLength;
  BOOL bDone;
  BYTE *pData;
  DWORD flags;


  HRESULT SetupAudioStream()
  {
    bDone                =false;
    hnsRequestedDuration = REFTIMES_PER_SEC;
    pwfx                 = NULL;

    CoInitialize(NULL);

    hr = CoCreateInstance(
      CLSID_MMDeviceEnumerator, NULL,
      CLSCTX_ALL, IID_IMMDeviceEnumerator,
      (void**)&pEnumerator);
    EXIT_ON_ERROR(hr);

    hr = pEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &pDevice);
    EXIT_ON_ERROR(hr);

    hr = pDevice->Activate(
      IID_IAudioClient, CLSCTX_ALL,
      NULL, (void**)&pAudioClient);
    EXIT_ON_ERROR(hr);

    hr = pAudioClient->GetMixFormat(&pwfx);
    EXIT_ON_ERROR(hr);

    hr = pAudioClient->Initialize(
      AUDCLNT_SHAREMODE_SHARED,
      0,
      hnsRequestedDuration,
      0,
      pwfx,
      NULL);
    EXIT_ON_ERROR(hr);

    // Get the size of the allocated buffer.
    hr = pAudioClient->GetBufferSize(&bufferFrameCount);
    EXIT_ON_ERROR(hr);

    hr = pAudioClient->GetService(
      IID_IAudioCaptureClient,
      (void**)&pCaptureClient);
    EXIT_ON_ERROR(hr);
    
    // Calculate the actual duration of the allocated buffer.
    hnsActualDuration = (double)REFTIMES_PER_SEC *
      bufferFrameCount / pwfx->nSamplesPerSec;

    hr = pAudioClient->Start();  // Start recording.
    EXIT_ON_ERROR(hr);

    return hr;

Exit:
    CoTaskMemFree(pwfx);
    SAFE_RELEASE(pEnumerator);
    SAFE_RELEASE(pDevice);
    SAFE_RELEASE(pAudioClient);
    SAFE_RELEASE(pCaptureClient);

    return hr;
  }



  BLOCK_INIT
  {
    SetupAudioStream();
  }

  BLOCK_DEINIT
  {
    hr = pAudioClient->Stop();  // Stop recording.

    CoTaskMemFree(pwfx);
    SAFE_RELEASE(pEnumerator);
    SAFE_RELEASE(pDevice);
    SAFE_RELEASE(pAudioClient);
    SAFE_RELEASE(pCaptureClient);
  }

  BLOCK_WORK
  {
    // Each loop fills about half of the shared buffer.
    auto op = $_<uchar>(0);

    uint32 ocnt = 0;
    
    //while (bDone == FALSE)
    {
      // Sleep for half the buffer duration.
      //Sleep(hnsActualDuration/REFTIMES_PER_MILLISEC/2);
      packetLength = 0;

      hr = pCaptureClient->GetNextPacketSize(&packetLength);
      
      do
      {
        //ocnt += packetLength;

        // Get the available data in the shared buffer.
        hr = pCaptureClient->GetBuffer(
          &pData,
          &numFramesAvailable,
          &flags, NULL, NULL);

        if (FAILED(hr) || numFramesAvailable == 0)
        {
          hr = pCaptureClient->ReleaseBuffer(numFramesAvailable);
          break;
        }

        memcpy(op, pData, packetLength);

        printf("pktlength=%d, frm-avilb=%d\n", packetLength, numFramesAvailable);

        hr = pCaptureClient->ReleaseBuffer(numFramesAvailable);
      }while (false);
    }

    produce(0, packetLength / 4);
    //return numFramesAvailable > 0;
    return true;
  }
};