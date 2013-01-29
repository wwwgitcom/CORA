#pragma once
DEFINE_BLOCK(b_lstf_searcher_2v1, 2, 1)
{
  _local_(int, peak_up_shift, 1);
  _local_(int, peak_down_shift, 2);
  _local_(bool, peak_found, false);
  _local_(int, peak_count, 0);

  int energy_buffer[4];
  int axorr_buffer[4];
  __int64 his_moving_energy[32];
  int his_index;


  BLOCK_INIT
  {
    auto v = $["peak_up_shift"];
    if (!v.empty())
    {
      *peak_up_shift = atoi(v.c_str());
    }
    v = $["peak_down_shift"];
    if (!v.empty())
    {
      *peak_down_shift = atoi(v.c_str());
    }
    memset(his_moving_energy, 1, 32 * sizeof(__int64));
    his_index = 0;
  }


  int ebmax;
  int maxpos;

  BLOCK_WORK
  {
    //trace();

    auto nin0 = ninput(0);
    auto nin1 = ninput(1);

    auto ip0  = _$<v_q>(0);
    auto ip1  = _$<v_q>(1);

    __int64 *_ip0 = (__int64*)ip0;
    __int64 *_ip1 = (__int64*)ip1;
    auto    _nin  = nin0 << 1;
    

#if 0
    if (nin0 < 96)
    {
      return false;
    }
    else
    {
      consume(0, 96);
      return true;
    }
#endif

#if enable_dbgplot
    for (int i = 0; i < 4; i++)
    {
      axorr_buffer[i] = (int)(_ip0[i] >> 32);
      energy_buffer[i] = (int)(_ip1[i] >> 32);
    }
    PlotLine("moving average energy", energy_buffer, 4);
    PlotLine("moving average axorr^2", axorr_buffer, 4);
#endif

    bool ret = false;

    if (_nin < 1) return false;

#if 0
    for (int i = 0; i < _nin; i++)
    {
      printf("%I64d\n", _ip1[i]);
    }
#endif

    

    //if (*peak_found)
    //log("-----------\n");
    for (int i = 0; i < _nin; i++)
    {
      __int64 e = _ip1[i];
      __int64 eb = e / (his_moving_energy[his_index] + 1);
      int eb32 = (int)(eb);
      
      eb32 *= 100;

      if (!*peak_found)
      {
        //if (eb > 2000)
        if ( _ip0[i] > (_ip1[i] >> *peak_up_shift)  && (_ip1[i] > 20000000000) )
        {
          (*peak_count)++;

          if ( *peak_count > 3)
          {
            *peak_found = true;
            eb32 = 300 * 1024;

            ebmax = eb;
            //cout << "peak ->" << endl;
          }
        }
        else
        {
          *peak_count = 0;
        }
      }
      else
      {
        //log("%I64d\t%I64d\n", _ip0[i], _ip1[i]);
        if ( _ip0[i] < (_ip1[i] >> *peak_down_shift) )
        {
          if (*peak_count > 96 && *peak_count < 160)
          {

            PlotText("[log]", "PeakCount=%d", *peak_count);

            *peak_found = false;
            *peak_count = 0;
            ret = true;

            eb32 = 500 * 1024;
            PlotLine("moving dwe", &eb32, 1);
            //cout << "peak <-" << endl;
            //getchar();
            break;
          }
          else
          {
            // it's a fake preamble
            *peak_found = false;
            *peak_count = 0;
            break;
          }
        }
        else
        {
          (*peak_count)++;
          
          if ( *peak_count > 160 )
          {
            //log("Too many peaks..................\n");
            //getchar();

            eb32 = 200 * 1024;

            *peak_found = false;
            *peak_count = 0;
          }
        }
      }

      PlotLine("moving dwe", &eb32, 1);
      

      his_moving_energy[his_index++] = _ip1[i];
      his_index %= 32;
    }

    consume(0, nin0);
    consume(1, nin1);

    //printf("%s, in=%d, ret=%d\n", name(), nin0, ret);

    return ret;
  }
};