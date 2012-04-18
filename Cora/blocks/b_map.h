#pragma once


DEFINE_BLOCK(b_map_bpsk_i_1v1, 1, 1)
{
  dsp_mapper_bpsk<complex16> *mapper;

  BLOCK_INIT
  {
    mapper = new dsp_mapper_bpsk<complex16>(complex16(30339, 0));
  }

  BLOCK_WORK
  {
    int n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<complex16>(0);

    for (int i = 0; i < n; i++)
    {
      dsp_mapper_bpsk<complex16>::output_type& out = (*mapper)[i];
      memcpy(op, out.values, sizeof(dsp_mapper_bpsk<complex16>::output_type));
      op += 8;
    }
    
    consume(0, n);
    produce(0, n * 8);
  }
};

DEFINE_BLOCK(b_map_bpsk_q_1v1, 1, 1)
{
  dsp_mapper_bpsk<complex16> *mapper;

  BLOCK_INIT
  {
    mapper = new dsp_mapper_bpsk<complex16>(complex16(0, 30339));
  }

  BLOCK_WORK
  {
    int n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<complex16>(0);

    for (int i = 0; i < n; i++)
    {
      dsp_mapper_bpsk<complex16>::output_type& out = (*mapper)[i];
      memcpy(op, out.values, sizeof(dsp_mapper_bpsk<complex16>::output_type));
      op += 8;
    }

    consume(0, n);
    produce(0, n * 8);
  }
};


DEFINE_BLOCK(b_map_qpsk_1v1, 1, 1)
{
  dsp_mapper_qpsk<complex16> *mapper;

  BLOCK_INIT
  {
    mapper = new dsp_mapper_qpsk<complex16>(complex16(21453, 21453));
  }

  BLOCK_WORK
  {
    trace();

    int n = ninput(0);
    if (n < 1) return false;

    auto ip = _$<unsigned __int8>(0);
    auto op = $_<complex16>(0);

    for (int i = 0; i < n; i++)
    {
      dsp_mapper_bpsk<complex16>::output_type& out = (*mapper)[i];
      memcpy(op, out.values, sizeof(dsp_mapper_qpsk<complex16>::output_type));
      op += 4;
    }

    consume(0, n);
    produce(0, n * 4);
  }
};