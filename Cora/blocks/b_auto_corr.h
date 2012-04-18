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

    log("%s\n", name());

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

    log("%s\n", name());

    v_cs &vInput = *_$<v_cs>(0);
    v_cs &vInput2 = *_$<v_cs>(1);// don't use data from port 2 in this impl.

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
    consume(1, 1);

    produce(0, 2);
    produce(1, 2);

    return true;
  }
};