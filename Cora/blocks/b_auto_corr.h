#pragma once

DEFINE_BLOCK(b_auto_corr_1v2, 1, 2)
{
  v_align(16) v_cs vMulMask;
  v_i  vInputEnergy;
  v_ci vInputCorr[2];

  v_i  vAverageEnergySum;
  v_ci vAverageCorrSum[2];

  v_cs* vHisSample;
  v_ci* vHisCorr;
  v_i*  vHisEnergy;

  v_q  vCorrEnergy[2];
  v_q  vEnergy[2];

  _local_(int, vHisLength, 8);
  _local_(int, vHisIdx, 0);
  int vShift;

  //--------------------------------------------
  BLOCK_RESET
  {
    *vHisIdx  = 0;
  }
  BLOCK_INIT
  {
    auto v = $["vHisLength"];
    if (!v.empty())
    {
      *vHisLength = atoi(v.c_str());
    }

    vMulMask   = VMASK::__0x80000001800000018000000180000001<v_cs>();
    
    unsigned long ns = 0;
    _BitScanReverse(&ns, (*vHisLength * 4));
    vShift = ns;

    //printf("normalize shift %d\n", vShift);

    vHisSample = (v_cs*)_aligned_malloc( *vHisLength * sizeof(v_cs), 16);
    memset(vHisSample, 0, *vHisLength * sizeof(v_cs));

    vHisCorr   = (v_ci*)_aligned_malloc( *vHisLength * sizeof(v_ci) * 2, 16);
    memset(vHisCorr, 0, *vHisLength * sizeof(v_ci) * 2);

    vHisEnergy = (v_i*)_aligned_malloc( *vHisLength * sizeof(v_i), 16);
    memset(vHisEnergy, 0, *vHisLength * sizeof(v_i));

    vAverageEnergySum.v_zero();
    vAverageCorrSum[0].v_zero();
    vAverageCorrSum[1].v_zero();
  }

  BLOCK_WORK
  {
    auto nin = ninput(0);

    if (nin < 1) return false;

    v_cs &vInput = *_$<v_cs>(0);
    auto vop0 = $_<v_q>(0);// output auto correlation sqr energy
    auto vop1 = $_<v_q>(1);// output average sqr energy

    vInputEnergy = vInput.v_sqr2i();
    vInputEnergy = vInputEnergy.v_shift_right_arithmetic(vShift);

    //printf("msk %p\n", &vMulMask);
    v_conjmul2ci(vInput, vHisSample[*vHisIdx], vMulMask, vInputCorr[0], vInputCorr[1]);
    vInputCorr[0] = vInputCorr[0].v_shift_right_arithmetic(vShift);
    vInputCorr[1] = vInputCorr[1].v_shift_right_arithmetic(vShift);

    vHisSample[*vHisIdx] = vInput;

    v_ci vDeltaCorr[3];

    vDeltaCorr[0] = v_sub(vInputCorr[0], vHisCorr[2 * (*vHisIdx)]);
    vDeltaCorr[1] = v_sub(vInputCorr[1], vHisCorr[2 * (*vHisIdx) + 1]);

    vHisCorr[2 * (*vHisIdx)]     = vInputCorr[0];
    vHisCorr[2 * (*vHisIdx) + 1] = vInputCorr[1];

    vDeltaCorr[2] = vDeltaCorr[0].v_shuffle_with<1, 0>(vDeltaCorr[1]);

    vDeltaCorr[0] = v_add(vDeltaCorr[0], (v_ci)vDeltaCorr[0].v_shift_bytes_left<8>());

    vAverageCorrSum[0] = v_add(vAverageCorrSum[0], vDeltaCorr[0]);
    vAverageCorrSum[1] = v_add(vAverageCorrSum[0], vDeltaCorr[1]);
    vAverageCorrSum[1] = v_add(vAverageCorrSum[1], vDeltaCorr[2]);

    // so far, we get 4 auto correlation results
    vop0[0] = vAverageCorrSum[0].v_sqr2q();
    vop0[1] = vAverageCorrSum[1].v_sqr2q();

    // calculate moving energy now
    vAverageCorrSum[0] = vAverageCorrSum[1].v_shuffle<1, 1>();

    v_i vDeltaEnergy;
    vDeltaEnergy = v_sub(vInputEnergy, vHisEnergy[*vHisIdx]);

    vHisEnergy[*vHisIdx] = vInputEnergy;
    
    vDeltaEnergy = v_add(vDeltaEnergy, (v_i)vDeltaEnergy.v_shift_bytes_left<4>());
    vDeltaEnergy = v_add(vDeltaEnergy, (v_i)vDeltaEnergy.v_shift_bytes_left<8>());

    vAverageEnergySum  = v_add(vAverageEnergySum, vDeltaEnergy);

    vAverageEnergySum.v_sqr2q(vop1[0], vop1[1]);

    vAverageEnergySum = vAverageEnergySum.v_shuffle<3, 3, 3, 3>();

    (*vHisIdx)++;
    (*vHisIdx) %= *vHisLength;

    consume(0, 1);
    produce(0, 2);
    produce(1, 2);

    return true;
  }
};

//////////////////////////////////////////////////////////////////////////
DEFINE_BLOCK(b_auto_corr_2v2, 2, 2)
{
  v_align(16) v_cs vMulMask;
  v_i  vInputEnergy;
  v_ci vInputCorr[2];

  v_i  vAverageEnergySum;
  v_ci vAverageCorrSum[2];

  v_i  vAverageEnergySum2;
  v_ci vAverageCorrSum2[2];

  v_cs* vHisSample;
  v_ci* vHisCorr;
  v_i*  vHisEnergy;

  v_cs* vHisSample2;
  v_ci* vHisCorr2;
  v_i*  vHisEnergy2;

  v_q  vCorrEnergy[2];
  v_q  vEnergy[2];

  _local_(int, vHisLength, 8);
  _local_(int, vHisIdx, 0);
  int vShift;

  //--------------------------------------------
  BLOCK_RESET
  {
    *vHisIdx  = 0;
  }
  BLOCK_INIT
  {
    auto v = $["vHisLength"];
    if (!v.empty())
    {
      *vHisLength = atoi(v.c_str());
    }

    vMulMask   = VMASK::__0x80000001800000018000000180000001<v_cs>();

    unsigned long ns = 0;
    _BitScanReverse(&ns, (*vHisLength * 4));
    vShift = ns;

    //printf("normalize shift %d\n", vShift);

    vHisSample = (v_cs*)_aligned_malloc( *vHisLength * sizeof(v_cs), 16);
    memset(vHisSample, 0, *vHisLength * sizeof(v_cs));

    vHisCorr   = (v_ci*)_aligned_malloc( *vHisLength * sizeof(v_ci) * 2, 16);
    memset(vHisCorr, 0, *vHisLength * sizeof(v_ci) * 2);

    vHisEnergy = (v_i*)_aligned_malloc( *vHisLength * sizeof(v_i), 16);
    memset(vHisEnergy, 0, *vHisLength * sizeof(v_i));

    //
    vHisSample2 = (v_cs*)_aligned_malloc( *vHisLength * sizeof(v_cs), 16);
    memset(vHisSample2, 0, *vHisLength * sizeof(v_cs));

    vHisCorr2   = (v_ci*)_aligned_malloc( *vHisLength * sizeof(v_ci) * 2, 16);
    memset(vHisCorr2, 0, *vHisLength * sizeof(v_ci) * 2);

    vHisEnergy2 = (v_i*)_aligned_malloc( *vHisLength * sizeof(v_i), 16);
    memset(vHisEnergy2, 0, *vHisLength * sizeof(v_i));

    vAverageEnergySum.v_zero();
    vAverageCorrSum[0].v_zero();
    vAverageCorrSum[1].v_zero();

    vAverageEnergySum2.v_zero();
    vAverageCorrSum2[0].v_zero();
    vAverageCorrSum2[1].v_zero();
  }

  __forceinline void auto_corr(v_cs& vInput, v_ci& vCorrSum1, v_ci& vCorrSum2, v_cs* pvHisSample, v_ci* pvHisCorr)
  {
    //printf("msk %p\n", &vMulMask);
    v_conjmul2ci(vInput, pvHisSample[*vHisIdx], vMulMask, vInputCorr[0], vInputCorr[1]);
    vInputCorr[0] = vInputCorr[0].v_shift_right_arithmetic(vShift);
    vInputCorr[1] = vInputCorr[1].v_shift_right_arithmetic(vShift);

    pvHisSample[*vHisIdx] = vInput;

    v_ci vDeltaCorr[3];

    vDeltaCorr[0] = v_sub(vInputCorr[0], pvHisCorr[2 * (*vHisIdx)]);
    vDeltaCorr[1] = v_sub(vInputCorr[1], pvHisCorr[2 * (*vHisIdx) + 1]);

    pvHisCorr[2 * (*vHisIdx)]     = vInputCorr[0];
    pvHisCorr[2 * (*vHisIdx) + 1] = vInputCorr[1];

    vDeltaCorr[2] = vDeltaCorr[0].v_shuffle_with<1, 0>(vDeltaCorr[1]);

    vDeltaCorr[0] = v_add(vDeltaCorr[0], (v_ci)vDeltaCorr[0].v_shift_bytes_left<8>());

    vCorrSum1 = v_add(vCorrSum1, vDeltaCorr[0]);
    vCorrSum2 = v_add(vCorrSum1, vDeltaCorr[1]);
    vCorrSum2 = v_add(vCorrSum2, vDeltaCorr[2]);
  }

  __forceinline void moving_energy(v_cs& vInput, v_i& vAvgEnergySum, v_i* pvHisEnergy, v_i& ve)
  {
    vInputEnergy = vInput.v_sqr2i();
    vInputEnergy = vInputEnergy.v_shift_right_arithmetic(vShift);

    v_i vDeltaEnergy;
    vDeltaEnergy = v_sub(vInputEnergy, pvHisEnergy[*vHisIdx]);

    pvHisEnergy[*vHisIdx] = vInputEnergy;

    vDeltaEnergy = v_add(vDeltaEnergy, (v_i)vDeltaEnergy.v_shift_bytes_left<4>());
    vDeltaEnergy = v_add(vDeltaEnergy, (v_i)vDeltaEnergy.v_shift_bytes_left<8>());

    vAvgEnergySum  = v_add(vAvgEnergySum, vDeltaEnergy);

    ve = vAvgEnergySum;
    //vAvgEnergySum.v_sqr2q(vout1, vout2);

    vAvgEnergySum = vAvgEnergySum.v_shuffle<3, 3, 3, 3>();
  }

  BLOCK_WORK
  {
    //trace();

    auto nin = ninput(0);

    if (nin < 1) return false;

    v_cs &vInput1 = *_$<v_cs>(0);
    v_cs &vInput2 = *_$<v_cs>(1);

    auto vop0 = $_<v_q>(0);// output auto correlation sqr energy
    auto vop1 = $_<v_q>(1);// output average sqr energy

    // joint auto correlation
    auto_corr(vInput1, vAverageCorrSum[0], vAverageCorrSum[1], vHisSample, vHisCorr);
    auto_corr(vInput2, vAverageCorrSum2[0], vAverageCorrSum2[1], vHisSample2, vHisCorr2);

    // we get 4 auto correlation results
    vop0[0] = v_add(vAverageCorrSum[0].v_shift_right_arithmetic(1), 
      vAverageCorrSum2[0].v_shift_right_arithmetic(1)).v_sqr2q();
    vop0[1] = v_add(vAverageCorrSum[1].v_shift_right_arithmetic(1), 
      vAverageCorrSum2[1].v_shift_right_arithmetic(1)).v_sqr2q();
    
    vAverageCorrSum[0]  = vAverageCorrSum[1].v_shuffle<1, 1>();
    vAverageCorrSum2[0] = vAverageCorrSum2[1].v_shuffle<1, 1>();

    // calculate moving energy now

    v_i ve1, ve2, vesum;
    moving_energy(vInput1, vAverageEnergySum, vHisEnergy, ve1);
    moving_energy(vInput2, vAverageEnergySum2, vHisEnergy2, ve2);

    vesum = v_add(ve1.v_shift_right_arithmetic(1), ve2.v_shift_right_arithmetic(1));
    vesum.v_sqr2q(vop1[0], vop1[1]);


    (*vHisIdx)++;
    (*vHisIdx) %= *vHisLength;

    consume_each(1);
    produce_each(2);

    return true;
  }
};

//////////////////////////////////////////////////////////////////////////
DEFINE_BLOCK(b_auto_corr_4v2, 4, 2)
{
  v_align(16) v_cs vMulMask;
  v_i  vInputEnergy;
  v_ci vInputCorr[2];

  v_i  vAverageEnergySum;
  v_ci vAverageCorrSum[2];

  v_cs* vHisSample;
  v_ci* vHisCorr;
  v_i*  vHisEnergy;

  v_q  vCorrEnergy[2];
  v_q  vEnergy[2];

  _local_(int, vHisLength, 8);
  _local_(int, vHisIdx, 0);
  int vShift;

  //--------------------------------------------
  BLOCK_RESET
  {
    *vHisIdx  = 0;
  }
  BLOCK_INIT
  {
    auto v = $["vHisLength"];
    if (!v.empty())
    {
      *vHisLength = atoi(v.c_str());
    }

    vMulMask   = VMASK::__0x80000001800000018000000180000001<v_cs>();

    unsigned long ns = 0;
    _BitScanReverse(&ns, (*vHisLength * 4));
    vShift = ns;

    //printf("normalize shift %d\n", vShift);

    vHisSample = (v_cs*)_aligned_malloc( *vHisLength * sizeof(v_cs), 16);
    memset(vHisSample, 0, *vHisLength * sizeof(v_cs));

    vHisCorr   = (v_ci*)_aligned_malloc( *vHisLength * sizeof(v_ci) * 2, 16);
    memset(vHisCorr, 0, *vHisLength * sizeof(v_ci) * 2);

    vHisEnergy = (v_i*)_aligned_malloc( *vHisLength * sizeof(v_i), 16);
    memset(vHisEnergy, 0, *vHisLength * sizeof(v_i));

    vAverageEnergySum.v_zero();
    vAverageCorrSum[0].v_zero();
    vAverageCorrSum[1].v_zero();
  }

  BLOCK_WORK
  {
    //trace();

    auto nin = ninput(0);

    if (nin < 1) return false;

    v_cs &vInput = *_$<v_cs>(0);
    v_cs &vInput2 = *_$<v_cs>(1);// don't use data from port 2 in this impl.
    v_cs &vInput3 = *_$<v_cs>(2);// don't use data from port 3 in this impl.
    v_cs &vInput4 = *_$<v_cs>(3);// don't use data from port 4 in this impl.

    auto vop0 = $_<v_q>(0);// output auto correlation sqr energy
    auto vop1 = $_<v_q>(1);// output average sqr energy

    vInputEnergy = vInput.v_sqr2i();
    vInputEnergy = vInputEnergy.v_shift_right_arithmetic(vShift);

    //printf("msk %p\n", &vMulMask);
    v_conjmul2ci(vInput, vHisSample[*vHisIdx], vMulMask, vInputCorr[0], vInputCorr[1]);
    vInputCorr[0] = vInputCorr[0].v_shift_right_arithmetic(vShift);
    vInputCorr[1] = vInputCorr[1].v_shift_right_arithmetic(vShift);

    vHisSample[*vHisIdx] = vInput;

    v_ci vDeltaCorr[3];

    vDeltaCorr[0] = v_sub(vInputCorr[0], vHisCorr[2 * (*vHisIdx)]);
    vDeltaCorr[1] = v_sub(vInputCorr[1], vHisCorr[2 * (*vHisIdx) + 1]);

    vHisCorr[2 * (*vHisIdx)]     = vInputCorr[0];
    vHisCorr[2 * (*vHisIdx) + 1] = vInputCorr[1];

    vDeltaCorr[2] = vDeltaCorr[0].v_shuffle_with<1, 0>(vDeltaCorr[1]);

    vDeltaCorr[0] = v_add(vDeltaCorr[0], (v_ci)vDeltaCorr[0].v_shift_bytes_left<8>());

    vAverageCorrSum[0] = v_add(vAverageCorrSum[0], vDeltaCorr[0]);
    vAverageCorrSum[1] = v_add(vAverageCorrSum[0], vDeltaCorr[1]);
    vAverageCorrSum[1] = v_add(vAverageCorrSum[1], vDeltaCorr[2]);

    // so far, we get 4 auto correlation results
    vop0[0] = vAverageCorrSum[0].v_sqr2q();
    vop0[1] = vAverageCorrSum[1].v_sqr2q();

    // calculate moving energy now
    vAverageCorrSum[0] = vAverageCorrSum[1].v_shuffle<1, 1>();

    v_i vDeltaEnergy;
    vDeltaEnergy = v_sub(vInputEnergy, vHisEnergy[*vHisIdx]);

    vHisEnergy[*vHisIdx] = vInputEnergy;

    vDeltaEnergy = v_add(vDeltaEnergy, (v_i)vDeltaEnergy.v_shift_bytes_left<4>());
    vDeltaEnergy = v_add(vDeltaEnergy, (v_i)vDeltaEnergy.v_shift_bytes_left<8>());

    vAverageEnergySum  = v_add(vAverageEnergySum, vDeltaEnergy);

    vAverageEnergySum.v_sqr2q(vop1[0], vop1[1]);

    vAverageEnergySum = vAverageEnergySum.v_shuffle<3, 3, 3, 3>();

    (*vHisIdx)++;
    (*vHisIdx) %= *vHisLength;

    consume_each(1);
    produce_each(2);

    return true;
  }
};