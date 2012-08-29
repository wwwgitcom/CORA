#pragma once 

#include <vector128.h>

__forceinline
HRESULT 
SORAAPI
SoraRadioReadRxStream(
        PSORA_RADIO_RX_STREAM pRxStream,
        FLAG * pbTouched,
        SignalBlock& block)
{
    PRX_BLOCK pbScanPoint = SoraRadioGetRxStreamPos(pRxStream);
    HRESULT hr = 
        SoraCheckSignalBlock(pbScanPoint, SoraGetStreamVStreamMask(pRxStream), SORA_MAX_RX_SPIN_WAIT, pbTouched);
    if (FAILED(hr)) 
        return hr; // hardware error

    block = (SignalBlock&)(pbScanPoint->u.SampleBlock);
    
    // Advance scan ponter
    __SoraRadioAdvanceRxStreamPos(pRxStream);
    return hr;
}
