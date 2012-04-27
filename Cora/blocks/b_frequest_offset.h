#pragma once



__forceinline short v_estimate_i(v_cs* pvcs, int vcount, int vdist)
{
  v_ci vsum;
  vsum.v_zero();
  unsigned long nshift = 0;
  _BitScanReverse(&nshift, vcount);

  const v_cs vmsk = VMASK::__0x80000001800000018000000180000001<v_cs>();

  for (int i = 0; i < vcount; i++)
  {
    v_cs& va = (v_cs&)pvcs[i];
    v_cs& vb = (v_cs&)pvcs[i + vdist];
    v_ci vc;
    v_ci vd;

    v_conjmul2ci(va, vb, vmsk, vc, vd);
    vc = vc.v_shift_right_arithmetic(nshift);
    vd = vd.v_shift_right_arithmetic(nshift);
    vsum = v_add(vc, vsum);
    vsum = v_add(vd, vsum);
  }
  vsum = vsum.v_hsum();

  //printf(" vsum =[%d, %d]\n", vsum[0].re, vsum[0].im);

  short sdeltaf = dsp_math::atan(vsum[0].re, vsum[0].im);
  _BitScanReverse(&nshift, vdist);
  sdeltaf >>= nshift;

  return sdeltaf;
}



DEFINE_BLOCK(b_frequest_offset_estimator_1v, 1, 0)
{
  _local_(int, vEstimateLength, 16);// 16 v_cs => 64 complex16
  _local_(int, vEstimateDistance, 16);// 16 v_cs => 64 complex16
    
  _global_(v_s, vfo_delta_i);
  _global_(v_s, vfo_step_i);
  _global_(v_s, vfo_theta_i);

  BLOCK_INIT
  {
    auto v = $["vEstimateLength"];
    if (!v.empty())
    {
      *vEstimateLength = atoi(v.c_str());
    }
    v = $["vEstimateDistance"];
    if (!v.empty())
    {
      *vEstimateDistance = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < *vEstimateLength + *vEstimateDistance) return false;

    log("%s: n=%d\n", name(), n);

    auto ip = _$<v_cs>(0);

    short delta = v_estimate_i(ip, *vEstimateLength, *vEstimateDistance);

    v_s vcfodelta;
    (*vfo_theta_i).v_zero();

    vcfodelta.v_setall(delta);

    (*vfo_step_i)    = vcfodelta.v_shift_left(3);

    vcfodelta         = v_add(vcfodelta, (v_s&)vcfodelta.v_shift_bytes_left<2>());
    vcfodelta         = v_add(vcfodelta, (v_s&)vcfodelta.v_shift_bytes_left<4>());
    vcfodelta         = v_add(vcfodelta, (v_s&)vcfodelta.v_shift_bytes_left<8>());
    vcfodelta         = vcfodelta.v_shift_bytes_left<2>();
    (*vfo_delta_i)    = vcfodelta;
    
    // I don't consume any input items
    return true;
  }
};

//////////////////////////////////////////////////////////////////////////

DEFINE_BLOCK(b_frequest_offset_estimator_2v, 2, 0)
{
  _local_(int, vEstimateLength, 16);// 16 v_cs => 64 complex16
  _local_(int, vEstimateDistance, 16);// 16 v_cs => 64 complex16

  _global_(v_s, vfo_delta_i);
  _global_(v_s, vfo_step_i);
  _global_(v_s, vfo_theta_i);

  BLOCK_INIT
  {
    auto v = $["vEstimateLength"];
    if (!v.empty())
    {
      *vEstimateLength = atoi(v.c_str());
    }
    v = $["vEstimateDistance"];
    if (!v.empty())
    {
      *vEstimateDistance = atoi(v.c_str());
    }
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < *vEstimateLength + *vEstimateDistance) return false;
    
    auto ip1 = _$<v_cs>(0);
    auto ip2 = _$<v_cs>(0);

    short delta1 = v_estimate_i(ip1, *vEstimateLength, *vEstimateDistance);
    short delta2 = v_estimate_i(ip2, *vEstimateLength, *vEstimateDistance);
    short delta  = (delta1 >> 1) + (delta2 >> 1);

    v_s vcfodelta;
    (*vfo_theta_i).v_zero();

    vcfodelta.v_setall(delta);

    (*vfo_step_i)    = vcfodelta.v_shift_left(3);

    vcfodelta         = v_add(vcfodelta, (v_s&)vcfodelta.v_shift_bytes_left<2>());
    vcfodelta         = v_add(vcfodelta, (v_s&)vcfodelta.v_shift_bytes_left<4>());
    vcfodelta         = v_add(vcfodelta, (v_s&)vcfodelta.v_shift_bytes_left<8>());
    vcfodelta         = vcfodelta.v_shift_bytes_left<2>();
    
    log("%s: cfo=%d\n", name(), (*vfo_delta_i)[1]);

    (*vfo_delta_i)    = vcfodelta;

    // I don't consume any input items
    log("%s: cfo=%d\n", name(), (*vfo_delta_i)[1]);
    return true;
  }
};

//////////////////////////////////////////////////////////////////////////

// vdeltaf = 7*deltaf, 6*deltaf, 5*deltaf, 4*deltaf 3*deltaf, 2*deltaf, 1*deltaf, 0*deltaf
// vstep   = 8*deltaf, 8*deltaf, 8*deltaf, 8*deltaf, 8*deltaf, 8*deltaf, 8*deltaf, 8*deltaf
__forceinline void v_make_coeff_i(v_cs* pvcs, int vcount, v_s &vdeltaf, v_s &vstep, v_s &vthetaf)
{
  v_s _vdeltaf = vdeltaf;
  v_s vsrad;
  v_cs vout;
  short v;
  int j = 0;
  for (int i = 0; i < (vcount >> 1); i++)
  {
    vsrad       = v_sub(_vdeltaf, vthetaf);

    v           = vsrad.v_get_at<0>(); vout.v_set_at<0>( dsp_math::sincos( v ) );
    v           = vsrad.v_get_at<1>(); vout.v_set_at<1>( dsp_math::sincos( v ) );
    v           = vsrad.v_get_at<2>(); vout.v_set_at<2>( dsp_math::sincos( v ) );
    v           = vsrad.v_get_at<3>(); vout.v_set_at<3>( dsp_math::sincos( v ) );

    pvcs[j]     = vout;

    v           = vsrad.v_get_at<4>(); vout.v_set_at<0>( dsp_math::sincos( v ) );
    v           = vsrad.v_get_at<5>(); vout.v_set_at<1>( dsp_math::sincos( v ) );
    v           = vsrad.v_get_at<6>(); vout.v_set_at<2>( dsp_math::sincos( v ) );
    v           = vsrad.v_get_at<7>(); vout.v_set_at<3>( dsp_math::sincos( v ) );

    pvcs[j + 1] = vout;

    j          += 2;
    _vdeltaf    = v_add(_vdeltaf, vstep);
  }
  vdeltaf = _vdeltaf;
}


__forceinline void v_compensate_i(v_cs* pvcsin, v_cs* pvcscoeff, v_cs* pvcsout, int vcount)
{
  v_ci vciout1, vciout2;
  const v_cs vmsk = VMASK::__0x80000001800000018000000180000001<v_cs>();

  for (int i = 0; i < vcount; i++)
  {
    v_cs &vin   = (v_cs &)pvcsin[i];
    v_cs &vcof  = (v_cs &)pvcscoeff[i];

    v_mul2ci(vin, vcof, vmsk, vciout1, vciout2);

    vciout1 = vciout1.v_shift_right_arithmetic(15);
    vciout2 = vciout2.v_shift_right_arithmetic(15);

    v_cs &vout  = (v_cs &)pvcsout[i];
    vout        = v_convert2cs(vciout1, vciout2);
  }
}

DEFINE_BLOCK(b_frequest_offset_compensator_1v1, 1, 1)
{
  _local_(int, vCompensateLength, 16);// 16 v_cs => 64 complex16
  v_cs* vfo_coeff;

  _global_(v_s, vfo_delta_i);
  _global_(v_s, vfo_step_i);
  _global_(v_s, vfo_theta_i);

  BLOCK_INIT
  {
    auto v = $["vCompensateLength"];
    if (!v.empty())
    {
      *vCompensateLength = atoi(v.c_str());
    }

    vfo_coeff = (v_cs*)_aligned_malloc( *vCompensateLength * sizeof(v_cs), 16);
    memset(vfo_coeff, 0, *vCompensateLength * sizeof(v_cs));
  }

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < *vCompensateLength) return false;

    auto ip = _$<v_cs>(0);
    auto op = $_<v_cs>(0);

    v_make_coeff_i(vfo_coeff, *vCompensateLength, *vfo_delta_i, *vfo_step_i, *vfo_theta_i);
    v_compensate_i(ip, vfo_coeff, op, *vCompensateLength);

    log("%s: n=%d\n", name(), n);

    consume(0, *vCompensateLength);
    produce(0, *vCompensateLength);
    return true;
  }
};

//////////////////////////////////////////////////////////////////////////
DEFINE_BLOCK(b_frequest_offset_compensator_2v2, 2, 2)
{
  _local_(int, vCompensateLength, 16);// 16 v_cs => 64 complex16
  v_cs* vfo_coeff;

  _global_(v_s, vfo_delta_i);
  _global_(v_s, vfo_step_i);
  _global_(v_s, vfo_theta_i);

  BLOCK_INIT
  {
    auto v = $["vCompensateLength"];
    if (!v.empty())
    {
      *vCompensateLength = atoi(v.c_str());
    }

    vfo_coeff = (v_cs*)_aligned_malloc( *vCompensateLength * sizeof(v_cs), 16);
    memset(vfo_coeff, 0, *vCompensateLength * sizeof(v_cs));
  }

  BLOCK_WORK
  {
    trace();

    auto n = ninput(0);
    if (n < *vCompensateLength) return false;

    auto ip1 = _$<v_cs>(0);
    auto op1 = $_<v_cs>(0);

    auto ip2 = _$<v_cs>(1);
    auto op2 = $_<v_cs>(1);

#if 0
    for (int i = 0; i < *vCompensateLength; i++)
    {
      op1[i] = ip1[i];
      op2[i] = ip2[i];
    }
#else
    v_make_coeff_i(vfo_coeff, *vCompensateLength, *vfo_delta_i, *vfo_step_i, *vfo_theta_i);
    v_compensate_i(ip1, vfo_coeff, op1, *vCompensateLength);
    v_compensate_i(ip2, vfo_coeff, op2, *vCompensateLength);

    log("%s: n=%d,cfo=%d", name(), n, (*vfo_delta_i)[1]);
#endif

    consume(0, *vCompensateLength);
    consume(1, *vCompensateLength);

    produce(0, *vCompensateLength);    
    produce(1, *vCompensateLength);
    return true;
  }
};