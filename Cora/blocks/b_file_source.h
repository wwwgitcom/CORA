#pragma once

#include "dsp_source.h"

DEFINE_BLOCK(b_file_source_v1, 1, 1)
{
  _local_(string, filename, "unknown");
  _local_(char*, pBufferStart, nullptr);
  _local_(char*, pBufferEnd, nullptr);
  _local_(char*, pBufferRead, nullptr);
  _local_(psignal_block, pSignalBlock, nullptr);
  _local_(int, nDecimate, 1);
  _local_(int, nOffset, 0);

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
DEFINE_BLOCK(b_file_source_v2, 2, 2)
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
      string msg = "error: " + string(name()) + " can not load file " + *filename1;
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

  BLOCK_WORK
  {
    //log("%s\n", name());
    //if (noutput(0) < 1) return true;
    
    if ((char*)(*pSignalBlock1) >= (*pBufferEnd1))
    {
      (*pSignalBlock1) = (psignal_block)(*pBufferStart1);
      (*pSignalBlock2) = (psignal_block)(*pBufferStart2);
      //std::cout << "source wrap once..." << endl;
    }
    //printf("%d\n", *pBufferEnd - (char*)*pSignalBlock);

    auto op1 = $_<v_cs>(0);
    auto op2 = $_<v_cs>(1);
    
    *op1 = (*pSignalBlock1)->operator[](*nOffset);
    *op2 = (*pSignalBlock2)->operator[](*nOffset);

    (*nOffset)++;
    if (*nOffset == 7)
    {
      (*pSignalBlock1)++;
      (*pSignalBlock2)++;
      *nOffset = 0;
    }

#if draw_source_2v
    (*iDrawIndex) += 4;
    
    if ((*iDrawIndex) % 1024 == 0)
    {
      m_draw1->DrawSqrt((complex16*)m_outputs[0]->m_base, m_outputs[0]->bufsize() * 4);
      m_draw2->DrawSqrt((complex16*)m_outputs[1]->m_base, m_outputs[0]->bufsize() * 4);
    }
#endif

    produce(0, 1);
    produce(1, 1);
    return true;
  }
};