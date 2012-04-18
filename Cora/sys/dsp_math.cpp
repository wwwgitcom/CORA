#include "stdafx.h"
#include "dsp_math.h"

complex16 dsp_math::sincos_lookup_table[dsp_math::sincos_lookup_table_size];
short     dsp_math::atan_lookup_table[dsp_math::atan_lookup_table_size];
int       dsp_math::m_lookup_table_init = false;

static    dsp_math dspmath;
