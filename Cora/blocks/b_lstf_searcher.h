#pragma once
DEFINE_BLOCK(b_lstf_searcher_2v1, 2, 1)
{
  _local_(int, peak_up_shift, 1);
  _local_(int, peak_down_shift, 3);
  _local_(bool, peak_found, false);
  _local_(int, peak_count, 0);

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
  }

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
      if (!*peak_found)
      {
        if ( _ip0[i] > (_ip1[i] >> *peak_up_shift) && (_ip1[i] > 20000000000))
        {
          (*peak_count)++;
          if ( *peak_count > 3)
          {
            *peak_found = true;
            //cout << "peak ->" << endl;
          }
        }
      }
      else
      {
        log("%I64d\t%I64d\n", _ip0[i], _ip1[i]);
        if ( _ip0[i] < (_ip1[i] >> *peak_down_shift) )
        {
          if (*peak_count > 96 && *peak_count < 160)
          {
            *peak_found = false;
            *peak_count = 0;
            ret = true;

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
            *peak_found = false;
            *peak_count = 0;
          }
        }
      }
    }

    consume(0, nin0);
    consume(1, nin1);

    //printf("%s, in=%d, ret=%d\n", name(), nin0, ret);

    return ret;
  }
};