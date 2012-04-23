#pragma once

DEFINE_BLOCK(b_lsig_parser_1v, 1, 1)
{
  BLOCK_WORK
  {
    int n = ninput(0);
    if (n < 3) return false;


  }
};