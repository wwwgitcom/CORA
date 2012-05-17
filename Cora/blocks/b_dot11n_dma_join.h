#pragma once

// as SORA MIMO specification, samples from 2 streams are interleaved by 4 samples (or, 1 v_cs)
// join sample from 2 inputs and flush to memory without polluting cache lines
DEFINE_BLOCK(b_dot11n_dma_join_2v1, 2, 1)
{

  BLOCK_WORK
  {
    auto n = ninput(0);
    if (n < 1) return false;

    auto ip1 = _$<dot11n_tx_symbol>(0);
    auto ip2 = _$<dot11n_tx_symbol>(1);
    auto op  = $_<v_cs>(0);

    for (int k = 0; k < n; k++)
    {
      for (int i = 0; i < dot11n_tx_symbol::vntotal; i++)
      {
        ip1->vdata[i].v_storent(op);
        ip2->vdata[i].v_storent(op + 1);
        op += 2;
      }
    }

    consume(0, n);
    consume(1, n);
    produce(0, n * dot11n_tx_symbol::vntotal << 1);

    return true;
  }


  void toRxDumpFile20M(const char* filename)
  {
    for (int i = 0; i < 2; i++)
    {
      char namebuffer[1024];
      memset(namebuffer, 0, 1024);
      sprintf_s(namebuffer, 1024, "%s_%d.dmp", filename, i);
      FILE* hFile;
      fopen_s(&hFile, namebuffer, "wb");

      int nvtotal_count = (v_cs*)m_outputs[0]->write_pointer() - (v_cs*)m_outputs[0]->m_base;
      nvtotal_count >>= 1; // per stream

      int total_count = nvtotal_count << 2; // count in complex16

      unsigned char desc[16] = {0x01};

      complex16* pc = (complex16*)&m_outputs[0]->m_base[0];

      pc += (i * 4); // adjust pc to the start of the ith stream
      
      int j = 0;
      int iout = 0;
      while (j < total_count)
      {
        if (iout % 28 == 0)
        {
          fwrite(desc, 16, 1, hFile);
        }

        fwrite(pc, sizeof(complex16) * 1, 1, hFile);
        fwrite(pc + 2, sizeof(complex16) * 1, 1, hFile);
        pc += 8;

        iout += 2;
        j += 4;
      }

      complex16 padding(0);

      for (; iout < 28; iout++)
      {
        fwrite(&padding, sizeof(complex16) * 1, 1, hFile);
      }

      fclose(hFile);
    }
  }

};