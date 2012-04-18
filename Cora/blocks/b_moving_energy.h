#pragma once

DEFINE_BLOCK(b_moving_energy_1v1, 1, 1)
{
  _local_(int, nAverageLength, 4);
  _local_(int, nShift, 2);
  _local_(int, iIndex, 0);
  _local_(int, iESum, 0);
  _local_(int*, pHistoryEnergy, nullptr);

  BLOCK_INIT
  {
    auto v = $["AverageLength"];
    if (!v.empty())
    {
      *nAverageLength = atoi(v.c_str());
    }
    unsigned long ns = 0;
    _BitScanReverse(&ns, (*nAverageLength));
    *nShift = ns;

    *pHistoryEnergy = new int[*nAverageLength];
    memset(*pHistoryEnergy, 0, *nAverageLength * sizeof(int));
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n <= 0) return false;

    auto ip = _$<complex16>(0);
    auto op = $_<int>(0);

    for (int i = 0; i < n; i++)
    {
      int e = ip[i].re * ip[i].re + ip[i].im * ip[i].im;
      e /= *nAverageLength;
      //e >>= *nShift;

      *iESum = *iESum - (*pHistoryEnergy)[*iIndex] + e; 
      op[i] = *iESum;

      (*pHistoryEnergy)[*iIndex] = e;
      (*iIndex)++;
      (*iIndex) %= *nAverageLength;

      cout << name() << " " << *iESum << endl;
    }
    cout << "---" << endl;

    consume(0, n);
    produce(0, n);
    return true;
  }
};
