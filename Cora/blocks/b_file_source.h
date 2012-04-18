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

public:
  int report()
  {
    char * pcur = (char*)*pSignalBlock;

    int distance = (pcur - *pBufferStart) * 28 / 128;
    return distance;
  }


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
    if (noutput(0) < 28) return true;

    log("%s\n", name());

    if ((char*)(*pSignalBlock) >= (*pBufferEnd))
    {
      (*pSignalBlock) = (psignal_block)(*pBufferStart);
      std::cout << "source wrap once..." << endl;
    }
    //printf("%d\n", *pBufferEnd - (char*)*pSignalBlock);

    auto op = $_<v_cs>(0);
    
    for (int i = 0; i < signal_block::v_datacount; i++)
    {
      op[i] = (*pSignalBlock)->operator[](i);
    }
    (*pSignalBlock)++;

    produce(0, signal_block::v_datacount);
    return true;
  }
};


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

public:
  int report()
  {
    char * pcur = (char*)*pSignalBlock1;

    int distance = (pcur - *pBufferStart1) * 28 / 128;
    return distance;
  }


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
    if (noutput(0) < 28) return true;

    log("%s\n", name());

    if ((char*)(*pSignalBlock1) >= (*pBufferEnd1))
    {
      (*pSignalBlock1) = (psignal_block)(*pBufferStart1);
      std::cout << "source wrap once..." << endl;
    }
    //printf("%d\n", *pBufferEnd - (char*)*pSignalBlock);

    auto op1 = $_<v_cs>(0);
    auto op2 = $_<v_cs>(1);
    
    for (int i = 0; i < signal_block::v_datacount; i++)
    {
      op1[i] = (*pSignalBlock1)->operator[](i);
      op2[i] = (*pSignalBlock2)->operator[](i);
    }
    (*pSignalBlock1)++;
    (*pSignalBlock2)++;

    produce(0, signal_block::v_datacount);
    produce(1, signal_block::v_datacount);
    return true;
  }
};