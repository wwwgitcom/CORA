#include <math.h>
#include <assert.h>
#include "DebugPlotU.h"

/*

Here is a simple sample code
the process generate a 16M sine wave data (the amplitude is 20000)
In this sine wave data, there's a *interesting data* with ampletude 30000.

The proces write the sine wave data into the source trace buffer, 
read 64 samples out every time, calculate the enery and plot to viewer.

When it find the *interesting data*, it calls PauseView() to pause the viewer

*/


#define PROCESS_SIZE 64
COMPLEX16 readBuf[PROCESS_SIZE];
int reBuf[PROCESS_SIZE];
int imBuf[PROCESS_SIZE];
int energyBuf[PROCESS_SIZE];

#define SPECTRUM_SIZE 63
int spectrumBuf[SPECTRUM_SIZE];

static void GenSpectrum()
{
	for (int i = 0; i < SPECTRUM_SIZE; i++)
	{
		int dist = i - SPECTRUM_SIZE/2;
		spectrumBuf[i] = 10000 -dist*dist + rand()%1000;
	}
}

static void PrepareData(COMPLEX16 * buf, int size, int egyPeriod)
{
	const int PERIOD = 20;
	const double PI_2 = 3.14159*2;
	const int AMP = 20;

	for (int i = 0; i < size; i++)
	{
		if ((i/egyPeriod)%2)
		{
			const double PI_2 = 3.14 * 2;
			const int AMP = 20000;
			const int PERIOD = 100;
			const int PERIOD_AMP = PERIOD * 10;
			COMPLEX16 complex;

			complex.re = short(/*double(i % PERIOD_AMP) / PERIOD_AMP * */AMP * sin(PI_2 * i / PERIOD));
			complex.im = short(/*double(i % PERIOD_AMP) / PERIOD_AMP * */AMP * cos(PI_2 * i / PERIOD));
			buf[i] = complex;
		}
		else
		{
			buf[i].re = 0;
			buf[i].im = 0;
		}
	}
}

bool TestPlotter()
{
	HRESULT hr = S_OK;

	hr = ::DebugPlotInit();
	if (FAILED(hr))
		return false;

	const int COMPLEX_16M_BYTES = 16*1024*1024/sizeof(COMPLEX16);
	COMPLEX16 * dataToProcess = new COMPLEX16[COMPLEX_16M_BYTES];

	PrepareData(dataToProcess, COMPLEX_16M_BYTES, 4*1024);		// generate a sine wave data and write to a 4k buffer

	// add a special *interesting data* at index 256k
	int interestDataIdx = 256*1024;
	dataToProcess[interestDataIdx].re = 30000;
	dataToProcess[interestDataIdx].im = 30000;

	__int64 counter = 0;
	DWORD timer = 0;
	DWORD lastTimer = 0;

	do
	{
		while(1)	// Periodically write data in 4k buffer to source trace buffer util the buffer is full (16M bytes)
		{
			int numWritten;
			hr = ::TracebufferWriteData(dataToProcess, COMPLEX_16M_BYTES, &numWritten);
			if (hr == E_END_OF_BUF)
			{
				assert(numWritten <= COMPLEX_16M_BYTES);
				break;
			}
		}

		bool endOfSourceBuf = false;
		while(!endOfSourceBuf)
		{
			int numRead;

			// syncronize with viewer, if the plotter plot too much data, wait for viewer will block until viewer read the data
			::WaitForViewer(INFINITE);

			// process PROCESS_SIZE COMPLEX16 every time
			hr = ::TracebufferReadData(readBuf, PROCESS_SIZE, &numRead);
			if (hr == E_END_OF_BUF)	// source trace buffer is empty
			{
				endOfSourceBuf = true;
				assert(numRead <= PROCESS_SIZE);
			}

			if (numRead == 0)
				continue;

			// process each COMPLEX
			double avgEnergy = 0.0;
			for (int i = 0; i < numRead; i++)
			{
				int re = readBuf[i].re;
				int im = readBuf[i].im;

				if (re > 20000)	// find our interesting data!!!
				{
					PauseViewer();
				}

				// calculate energy
				double energyF = log(double(re*re + im*im)) - 10;
				energyF = max(energyF, 0.0);
				avgEnergy += energyF;
				energyBuf[i] = (int)energyF;

				// set re & im value
				reBuf[i] = re;
				imBuf[i] = im;
			}
			avgEnergy /= numRead;

			// generate a fake spectrum using rand()
			GenSpectrum();
			
			// plot
			PlotLine("re part", reBuf, numRead);
			PlotLine("im part", imBuf, numRead);
			PlotLine("energy", energyBuf, numRead);
			PlotDots("dots", readBuf, numRead);
			PlotText("text", "%f\n", avgEnergy);
			//PlotSpectrum("spectrum", spectrumBuf, SPECTRUM_SIZE);
			Log("log", "%I64d\n", counter++);

			timer = ::GetTickCount();
			if (timer - lastTimer > 200)
			{
				static int lowFrequencyData = 0;
				//::PlotLine("low frequency", &lowFrequencyData, 1);
				lowFrequencyData = (lowFrequencyData+1)%100;
				lastTimer = timer;
				::PlotSpectrum("spectrum", spectrumBuf, SPECTRUM_SIZE);
			}

		}

		::TracebufferClear();
	} while(1);

	delete [] dataToProcess;

	DebugPlotDeinit();

	return true;
}
