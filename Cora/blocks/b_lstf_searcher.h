#pragma once
DEFINE_BLOCK(b_lstf_searcher_2v1, 2, 1)
{
  _local_(int, peak_up_shift, 1);
  _local_(int, peak_down_shift, 3);
  _local_(bool, peak_found, false);
  _local_(int, peak_count, 0);

  int energy_buffer[4];
  int axorr_buffer[4];
  __int64 his_moving_energy[64];
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
    memset(his_moving_energy, 1, 64 * sizeof(__int64));
    his_index = 0;

    itracept = 0;
  }


  int ebmax;
  int maxpos;

  int itracept;

  BLOCK_WORK
  {
    //trace();

    auto nin0 = ninput(0);
    auto nin1 = ninput(1);

    auto ip0  = _$<v_q>(0);
    auto ip1  = _$<v_q>(1);

    __int64 *acorr = (__int64*)ip0;
    __int64 *energy = (__int64*)ip1;
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
      axorr_buffer[i] = (int)(acorr[i] >> 32);
      energy_buffer[i] = (int)(energy[i] >> 32);
    }
    PlotLine("moving average energy", energy_buffer, 4);
    PlotLine("moving average axorr^2", axorr_buffer, 4);
#endif

    bool ret = false;

    if (_nin < 1) return false;

#if 0
    for (int i = 0; i < _nin; i++)
    {
      printf("%I64d, %I64d\n", acorr[i], energy[i]);
    }
#endif

    

    //if (*peak_found)
    //log("-----------\n");
    for (int i = 0; i < _nin; i++)
    {
      itracept++;

      __int64 eb = energy[i] / (his_moving_energy[his_index] + 1);
      int eb32 = (int)(eb);

      // for debug only, make it easy to be seen on screen
      eb32 *= 10;

      if (!*peak_found)
      {
        if ( eb > 5 && acorr[i] > (energy[i] >> 1)/*  && (e > 200000)*/ )
        {
          (*peak_count)++;

          //if ( *peak_count > 3)
          {
            float fsnr = 10 * log10((float)eb) - 1.0;

            PlotText("[log]", "Frame SNR=%.3f dB", fsnr);

            printf("peak-->%d\n", itracept);
            *peak_found = true;
            eb32 = energy_buffer[i];

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
        if ( acorr[i] < (energy[i] >> 3) )
        {
          if (*peak_count > 96 && *peak_count < 160)
          {

            PlotText("[log]", "PeakCount=%d", *peak_count);
            
            printf("peak<--%d, eb=%d\n", itracept, eb32 / 10);

            *peak_found = false;
            *peak_count = 0;
            ret = true;

            eb32 = energy_buffer[i] * 2;
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
            //break;
          }
        }
        else
        {
          (*peak_count)++;
          
          //if ( *peak_count > 160 )
          //{
          //  //log("Too many peaks..................\n");
          //  //getchar();

          //  eb32 = 200 * 1024;

          //  *peak_found = false; 
          //  *peak_count = 0;
          //}
        }
      }

      PlotLine("moving dwe", &eb32, 1);
      

      his_moving_energy[his_index++] = energy[i];
      his_index %= 64;
    }

    consume(0, nin0);
    consume(1, nin1);

    //printf("%s, in=%d, ret=%d\n", name(), nin0, ret);

    return ret;
  }
};