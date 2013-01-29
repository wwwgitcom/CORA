#pragma once

#include "dsp_source.h"

DEFINE_BLOCK(b_file_source_v1, 0, 1)
{
  _local_(string, filename, "unknown");
  _local_(char*, pBufferStart, nullptr);
  _local_(char*, pBufferEnd, nullptr);
  _local_(char*, pBufferRead, nullptr);
  _local_(psignal_block, pSignalBlock, nullptr);
  _local_(int, nDecimate, 1);
  _local_(int, nOffset, 0);
  _local_(int, nLoop, 1000);

public:
  int report()
  {
    char * pcur = (char*)*pSignalBlock;

    int distance = (pcur - *pBufferStart) * 28 / 128;
    return distance;
  }

#if enable_draw
  dsp_draw_window* m_draw;
#endif

  BLOCK_INIT
  {
    auto v = $["FileName"];
    if (!v.empty())
    {
      *filename = v;
    }

    v = $["Decimate"];
    if (!v.empty())
    {
      *nDecimate = atoi(v.c_str());
    }

    if (!load_file())
    {
      string msg = "error: " + string(name()) + " can not load file " + *filename;
      cout << msg << endl;
      throw::invalid_argument(msg);
    }
#if enable_draw
    m_draw = new dsp_draw_window("dot11 siso channel estimator", 200, 200, 400, 400);
#endif
  }

  bool load_file()
  {
    FILE* hFile;
    fopen_s(&hFile, (*filename).c_str(), "rb");

    if (NULL == hFile)
    {
      return false;
    }

    fseek(hFile, 0, SEEK_END);

    long file_length = ftell(hFile);

    assert(file_length > 0);

    *pBufferStart = (char*)_aligned_malloc(file_length, 64);
    assert(*pBufferStart != NULL);

    fseek(hFile, 0, SEEK_SET);
    size_t read_length = fread(*pBufferStart, sizeof(char), file_length, hFile);

    assert(read_length == file_length);

    *pBufferRead  = *pBufferStart;
    *pBufferEnd   = *pBufferStart + file_length;
    *pSignalBlock = (psignal_block)*pBufferStart;

    std::cout << name() << " read from " << *filename << " " << file_length << " bytes." << endl;

    return true;
  }

  BLOCK_WORK
  {
    //if (noutput(0) < 1) return true;

    log("%s\n", name());

    if ((char*)(*pSignalBlock) >= (*pBufferEnd))
    {
      (*pSignalBlock) = (psignal_block)(*pBufferStart);
      std::cout << "source wrap once..." << endl;
    }
    //printf("%d\n", *pBufferEnd - (char*)*pSignalBlock);

    auto op = $_<v_cs>(0);

#if enable_draw
    m_draw->DrawSqrt((complex16*)m_outputs[0]->m_base, m_outputs[0]->bufsize() * 4);
#endif
    
    *op = (*pSignalBlock)->operator[](*nOffset);

    (*nOffset)++;
    if (*nOffset == 7)
    {
      (*pSignalBlock)++;
      *nOffset = 0;
    }

    produce(0, 1);
    return true;
  }
};

#define draw_source_2v 0

///----------------------------------------------------
DEFINE_BLOCK(b_file_source_v2, 0, 2)
{
  _local_(string, filename1, "unknown");
  _local_(string, filename2, "unknown");
  _local_(char*, pBufferStart1, nullptr);
  _local_(char*, pBufferEnd1, nullptr);
  _local_(char*, pBufferRead1, nullptr);
  _local_(char*, pBufferStart2, nullptr);
  _local_(char*, pBufferEnd2, nullptr);
  _local_(char*, pBufferRead2, nullptr);
  _local_(psignal_block, pSignalBlock1, nullptr);
  _local_(psignal_block, pSignalBlock2, nullptr);
  _local_(int, nDecimate, 1);
  _local_(int, nOffset, 0);
  _local_(int, nLoop, 1000000);

public:
  int report()
  {
    char * pcur = (char*)*pSignalBlock1;

    int distance = (pcur - *pBufferStart1) * 28 / 128;
    return distance;
  }

#if draw_source_2v
  dsp_draw_window* m_draw1;
  dsp_draw_window* m_draw2;
  _local_(int, iDrawIndex, 0);
  _local_(int, iDrawLength, 10240);
  _local_(int, iDrawOffset, 0);
#endif

  BLOCK_INIT
  {
    auto v = $["FileName1"];
    if (!v.empty())
    {
      *filename1 = v;
    }
    v = $["FileName2"];
    if (!v.empty())
    {
      *filename2 = v;
    }

    v = $["Decimate"];
    if (!v.empty())
    {
      *nDecimate = atoi(v.c_str());
    }

    if (!load_file1())
    {
      string msg = "error: " + string(name()) + " can not load file " + *filename1;
      cout << msg << endl;
      throw::invalid_argument(msg);
    }
    if (!load_file2())
    {
      string msg = "error: " + string(name()) + " can not load file " + *filename2;
      cout << msg << endl;
      throw::invalid_argument(msg);
    }

#if draw_source_2v
    m_draw1 = new dsp_draw_window("dot11 file source 1", 200, 200, 400, 400);
    m_draw2 = new dsp_draw_window("dot11 file source 2", 300, 200, 400, 400);
#endif
  }

  bool load_file1()
  {
    FILE* hFile;
    fopen_s(&hFile, (*filename1).c_str(), "rb");

    if (NULL == hFile)
    {
      return false;
    }

    fseek(hFile, 0, SEEK_END);

    long file_length = ftell(hFile);

    assert(file_length > 0);

    *pBufferStart1 = (char*)_aligned_malloc(file_length, 64);
    assert(*pBufferStart1 != NULL);

    fseek(hFile, 0, SEEK_SET);
    size_t read_length = fread(*pBufferStart1, sizeof(char), file_length, hFile);

    assert(read_length == file_length);

    *pBufferRead1  = *pBufferStart1;
    *pBufferEnd1   = *pBufferStart1 + file_length;
    *pSignalBlock1 = (psignal_block)*pBufferStart1;

    std::cout << name() << " read from " << *filename1 << " " << file_length << " bytes." << endl;

    return true;
  }

  bool load_file2()
  {
    FILE* hFile;
    fopen_s(&hFile, (*filename2).c_str(), "rb");

    if (NULL == hFile)
    {
      return false;
    }

    fseek(hFile, 0, SEEK_END);

    long file_length = ftell(hFile);

    assert(file_length > 0);

    *pBufferStart2 = (char*)_aligned_malloc(file_length, 64);
    assert(*pBufferStart2 != NULL);

    fseek(hFile, 0, SEEK_SET);
    size_t read_length = fread(*pBufferStart2, sizeof(char), file_length, hFile);

    assert(read_length == file_length);

    *pBufferRead2  = *pBufferStart2;
    *pBufferEnd2   = *pBufferStart2 + file_length;
    *pSignalBlock2 = (psignal_block)*pBufferStart2;

    std::cout << name() << " read from " << *filename2 << " " << file_length << " bytes." << endl;

    return true;
  }

  static const int nproduce = 1;

  BLOCK_WORK
  {
    //log("%s\n", name());
    //if (noutput(0) < 1) return true;
    

    //printf("%d\n", *pBufferEnd - (char*)*pSignalBlock);

    auto op1 = $_<v_cs>(0);
    auto op2 = $_<v_cs>(1);
    
    for (int i = 0; i < nproduce; i++)
    {
      v_cs v1st_1 = (*pSignalBlock1)->operator[](*nOffset);
      v_cs v1st_2 = (*pSignalBlock2)->operator[](*nOffset);

      (*nOffset)++;
      if (*nOffset == 7)
      {
        (*pSignalBlock1)++;
        (*pSignalBlock2)++;
        *nOffset = 0;

        if ((char*)(*pSignalBlock1) >= (*pBufferEnd1))
        {
          (*pSignalBlock1) = (psignal_block)(*pBufferStart1);
          (*pSignalBlock2) = (psignal_block)(*pBufferStart2);
          //std::cout << "source wrap once..." << endl;
          (*nLoop)--;
          if (*nLoop == 0)
          {
            return false;
          }
        }
      }

      if (*nDecimate == 2)
      {
        v_cs v2nd_1 = (*pSignalBlock1)->operator[](*nOffset);
        v_cs v2nd_2 = (*pSignalBlock2)->operator[](*nOffset);


        //printf("\nsource...\n");

        //v_print(stdout, v1st_1);
        //v_print(stdout, v2nd_1);

        //v_print(stdout, v1st_2);
        //v_print(stdout, v2nd_2);


        //v1st_1 = v1st_1.v_shuffle_with<0, 2, 0, 2>(v2nd_1);
        //v1st_2 = v1st_2.v_shuffle_with<0, 2, 0, 2>(v2nd_2);

        //printf("down sample...\n");

        //v_print(stdout, v1st_1);
        //v_print(stdout, v1st_2);




        (*nOffset)++;
        if (*nOffset == 7)
        {
          (*pSignalBlock1)++;
          (*pSignalBlock2)++;
          *nOffset = 0;

          if ((char*)(*pSignalBlock1) >= (*pBufferEnd1))
          {
            (*pSignalBlock1) = (psignal_block)(*pBufferStart1);
            (*pSignalBlock2) = (psignal_block)(*pBufferStart2);
            //std::cout << "source wrap once..." << endl;
            (*nLoop)--;
            if (*nLoop == 0)
            {
              return false;
            }
          }
        }

        op1[i] = v1st_1;
        op2[i] = v1st_2;
      }


    }


#if draw_source_2v
    (*iDrawIndex) += 4;
    
    if ((*iDrawIndex) % 1024 == 0)
    {
      m_draw1->DrawSqrt((complex16*)m_outputs[0]->m_base, m_outputs[0]->bufsize() * 4);
      m_draw2->DrawSqrt((complex16*)m_outputs[1]->m_base, m_outputs[0]->bufsize() * 4);
    }
#endif

    produce(0, nproduce);
    produce(1, nproduce);
    return true;
  }
};

//////////////////////////////////////////////////////////////////////////
DEFINE_BLOCK(b_file_source_v4, 0, 4)
{
  _local_(string, filename1, "unknown");
  _local_(string, filename2, "unknown");
  _local_(string, filename3, "unknown");
  _local_(string, filename4, "unknown");

  _local_(char*, pBufferStart1, nullptr);
  _local_(char*, pBufferEnd1, nullptr);
  _local_(char*, pBufferRead1, nullptr);
  
  _local_(char*, pBufferStart2, nullptr);
  _local_(char*, pBufferEnd2, nullptr);
  _local_(char*, pBufferRead2, nullptr);

  _local_(char*, pBufferStart3, nullptr);
  _local_(char*, pBufferEnd3, nullptr);
  _local_(char*, pBufferRead3, nullptr);

  _local_(char*, pBufferStart4, nullptr);
  _local_(char*, pBufferEnd4, nullptr);
  _local_(char*, pBufferRead4, nullptr);

  _local_(psignal_block, pSignalBlock1, nullptr);
  _local_(psignal_block, pSignalBlock2, nullptr);
  _local_(psignal_block, pSignalBlock3, nullptr);
  _local_(psignal_block, pSignalBlock4, nullptr);

  _local_(int, nDecimate, 1);
  _local_(int, nOffset, 0);
  _local_(int, nLoop, 1000000);

public:
  int report()
  {
    char * pcur = (char*)*pSignalBlock1;

    int distance = (pcur - *pBufferStart1) * 28 / 128;
    return distance;
  }

#if draw_source_2v
  dsp_draw_window* m_draw1;
  dsp_draw_window* m_draw2;
  _local_(int, iDrawIndex, 0);
  _local_(int, iDrawLength, 10240);
  _local_(int, iDrawOffset, 0);
#endif

  BLOCK_INIT
  {
    auto v = $["FileName1"];
    if (!v.empty())
    {
      *filename1 = v;
    }
    v = $["FileName2"];
    if (!v.empty())
    {
      *filename2 = v;
    }
    v = $["FileName3"];
    if (!v.empty())
    {
      *filename3 = v;
    }
    v = $["FileName4"];
    if (!v.empty())
    {
      *filename4 = v;
    }

    v = $["Decimate"];
    if (!v.empty())
    {
      *nDecimate = atoi(v.c_str());
    }

    if (!load_file1())
    {
      string msg = "error: " + string(name()) + " can not load file " + *filename1;
      cout << msg << endl;
      throw::invalid_argument(msg);
    }
    if (!load_file2())
    {
      string msg = "error: " + string(name()) + " can not load file " + *filename2;
      cout << msg << endl;
      throw::invalid_argument(msg);
    }

    if (!load_file3())
    {
      string msg = "error: " + string(name()) + " can not load file " + *filename3;
      cout << msg << endl;
      throw::invalid_argument(msg);
    }

    if (!load_file4())
    {
      string msg = "error: " + string(name()) + " can not load file " + *filename4;
      cout << msg << endl;
      throw::invalid_argument(msg);
    }

#if draw_source_2v
    m_draw1 = new dsp_draw_window("dot11 file source 1", 200, 200, 400, 400);
    m_draw2 = new dsp_draw_window("dot11 file source 2", 300, 200, 400, 400);
#endif
  }

  bool load_file1()
  {
    FILE* hFile;
    fopen_s(&hFile, (*filename1).c_str(), "rb");

    if (NULL == hFile)
    {
      return false;
    }

    fseek(hFile, 0, SEEK_END);

    long file_length = ftell(hFile);

    assert(file_length > 0);

    *pBufferStart1 = (char*)_aligned_malloc(file_length, 64);
    assert(*pBufferStart1 != NULL);

    fseek(hFile, 0, SEEK_SET);
    size_t read_length = fread(*pBufferStart1, sizeof(char), file_length, hFile);

    assert(read_length == file_length);

    *pBufferRead1  = *pBufferStart1;
    *pBufferEnd1   = *pBufferStart1 + file_length;
    *pSignalBlock1 = (psignal_block)*pBufferStart1;

    std::cout << name() << " read from " << *filename1 << " " << file_length << " bytes." << endl;

    return true;
  }

  bool load_file2()
  {
    FILE* hFile;
    fopen_s(&hFile, (*filename2).c_str(), "rb");

    if (NULL == hFile)
    {
      return false;
    }

    fseek(hFile, 0, SEEK_END);

    long file_length = ftell(hFile);

    assert(file_length > 0);

    *pBufferStart2 = (char*)_aligned_malloc(file_length, 64);
    assert(*pBufferStart2 != NULL);

    fseek(hFile, 0, SEEK_SET);
    size_t read_length = fread(*pBufferStart2, sizeof(char), file_length, hFile);

    assert(read_length == file_length);

    *pBufferRead2  = *pBufferStart2;
    *pBufferEnd2   = *pBufferStart2 + file_length;
    *pSignalBlock2 = (psignal_block)*pBufferStart2;

    std::cout << name() << " read from " << *filename2 << " " << file_length << " bytes." << endl;

    return true;
  }


  bool load_file3()
  {
    FILE* hFile;
    fopen_s(&hFile, (*filename3).c_str(), "rb");

    if (NULL == hFile)
    {
      return false;
    }

    fseek(hFile, 0, SEEK_END);

    long file_length = ftell(hFile);

    assert(file_length > 0);

    *pBufferStart3 = (char*)_aligned_malloc(file_length, 64);
    assert(*pBufferStart3 != NULL);

    fseek(hFile, 0, SEEK_SET);
    size_t read_length = fread(*pBufferStart3, sizeof(char), file_length, hFile);

    assert(read_length == file_length);

    *pBufferRead3  = *pBufferStart3;
    *pBufferEnd3   = *pBufferStart3 + file_length;
    *pSignalBlock3 = (psignal_block)*pBufferStart3;

    std::cout << name() << " read from " << *filename3 << " " << file_length << " bytes." << endl;

    return true;
  }


  bool load_file4()
  {
    FILE* hFile;
    fopen_s(&hFile, (*filename4).c_str(), "rb");

    if (NULL == hFile)
    {
      return false;
    }

    fseek(hFile, 0, SEEK_END);

    long file_length = ftell(hFile);

    assert(file_length > 0);

    *pBufferStart4 = (char*)_aligned_malloc(file_length, 64);
    assert(*pBufferStart4 != NULL);

    fseek(hFile, 0, SEEK_SET);
    size_t read_length = fread(*pBufferStart4, sizeof(char), file_length, hFile);

    assert(read_length == file_length);

    *pBufferRead4  = *pBufferStart4;
    *pBufferEnd4   = *pBufferStart4 + file_length;
    *pSignalBlock4 = (psignal_block)*pBufferStart4;

    std::cout << name() << " read from " << *filename4 << " " << file_length << " bytes." << endl;

    return true;
  }

  static const int nproduce = 1;

  int RxBuffer[4][4];

  BLOCK_WORK
  {
    //log("%s\n", name());
    //if (noutput(0) < 1) return true;


    //printf("%d\n", *pBufferEnd - (char*)*pSignalBlock);

    auto op1 = $_<v_cs>(0);
    auto op2 = $_<v_cs>(1);
    auto op3 = $_<v_cs>(2);
    auto op4 = $_<v_cs>(3);

    for (int i = 0; i < nproduce; i++)
    {
      op1[i] = (*pSignalBlock1)->operator[](*nOffset);
      op2[i] = (*pSignalBlock2)->operator[](*nOffset);
      op3[i] = (*pSignalBlock3)->operator[](*nOffset);
      op4[i] = (*pSignalBlock4)->operator[](*nOffset);

#if 0
      for (int i = 0; i < 4; i++)
      {
        RxBuffer[0][i] = op1[0][i].re * op1[0][i].re + op1[0][i].im * op1[0][i].im;
        RxBuffer[1][i] = op2[0][i].re * op2[0][i].re + op2[0][i].im * op2[0][i].im;
        RxBuffer[2][i] = op3[0][i].re * op3[0][i].re + op3[0][i].im * op3[0][i].im;
        RxBuffer[3][i] = op4[0][i].re * op4[0][i].re + op4[0][i].im * op4[0][i].im;
      }
      PlotLine("RX Raw 1", &RxBuffer[0][0], 4);
      PlotLine("RX Raw 2", &RxBuffer[1][0], 4);
      PlotLine("RX Raw 3", &RxBuffer[2][0], 4);
      PlotLine("RX Raw 4", &RxBuffer[3][0], 4);
#endif

      (*nOffset)++;
      if (*nOffset == 7)
      {
        (*pSignalBlock1)++;
        (*pSignalBlock2)++;
        (*pSignalBlock3)++;
        (*pSignalBlock4)++;
        *nOffset = 0;

        if ((char*)(*pSignalBlock1) >= (*pBufferEnd1))
        {
          (*pSignalBlock1) = (psignal_block)(*pBufferStart1);
          (*pSignalBlock2) = (psignal_block)(*pBufferStart2);
          (*pSignalBlock3) = (psignal_block)(*pBufferStart3);
          (*pSignalBlock4) = (psignal_block)(*pBufferStart4);
          //std::cout << "source wrap once..." << endl;
          (*nLoop)--;
          if (*nLoop == 0)
          {
            return false;
          }
        }
      }
    }


#if draw_source_4v
    (*iDrawIndex) += 4;

    if ((*iDrawIndex) % 1024 == 0)
    {
      m_draw1->DrawSqrt((complex16*)m_outputs[0]->m_base, m_outputs[0]->bufsize() * 4);
      m_draw2->DrawSqrt((complex16*)m_outputs[1]->m_base, m_outputs[0]->bufsize() * 4);
    }
#endif

    produce_each(nproduce);
    return true;
  }
};



//////////////////////////////////////////////////////////////////////////
// tx file
//////////////////////////////////////////////////////////////////////////



DEFINE_BLOCK(b_tx_file_source_v1, 0, 1)
{
  _local_(string, filename, "unknown");
  _local_(char*, pBufferStart, nullptr);
  _local_(char*, pBufferEnd, nullptr);
  _local_(char*, pBufferRead, nullptr);
  long file_length;
public:

  BLOCK_INIT
  {
    auto v = $["FileName"];
    printf(" ..... %s\n", v.c_str());
    if (!v.empty())
    {
      *filename = v;
    }
    
    if (!load_file())
    {
      string msg = "error: " + string(name()) + " can not load file " + *filename;
      cout << msg << endl;
      throw::invalid_argument(msg);
    }
  }

  bool load_file()
  {
    FILE* hFile;
    fopen_s(&hFile, (*filename).c_str(), "rb");

    if (NULL == hFile)
    {
      return false;
    }

    fseek(hFile, 0, SEEK_END);

    file_length = ftell(hFile);

    assert(file_length > 0);

    *pBufferStart = (char*)_aligned_malloc(file_length, 64);
    assert(*pBufferStart != NULL);

    fseek(hFile, 0, SEEK_SET);
    size_t read_length = fread(*pBufferStart, sizeof(char), file_length, hFile);

    assert(read_length == file_length);

    *pBufferRead  = *pBufferStart;
    *pBufferEnd   = *pBufferStart + file_length;

    std::cout << name() << " read from " << *filename << " " << file_length << " bytes." << endl;

    return true;
  }

  BLOCK_WORK
  {
    auto op = $_<v_cb>(0);

    memcpy(op, *pBufferStart, file_length);

    int nvcb = file_length / v_cb::size;
    produce(0, nvcb);

    return true;
  }
};
