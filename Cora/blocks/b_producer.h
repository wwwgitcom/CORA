#pragma once


DEFINE_BLOCK(b_producer_v1, 0, 1)
{
public:
  _local_(int, nItemsTotal, 10000);
private:
  _local_(int, nItemsEach, 1);  
  _local_(int, nItemsLeft, 10000);

  BLOCK_INIT
  {
    auto v = $["nItemsEach"];
    if (!v.empty())
    {
      *nItemsEach = atoi(v.c_str());
    }

    v = $["nItemsTotal"];
    if (!v.empty())
    {
      *nItemsTotal = atoi(v.c_str());
      *nItemsLeft  = *nItemsTotal;
    }
  }

  BLOCK_WORK
  {
    if (*nItemsLeft <= 0)
    {
      return false;
    }
    produce(0, *nItemsEach);
    //printf("producer: %d items\n", *nItemsEach);
    *nItemsLeft  = *nItemsTotal;
    return true;
  }
};



DEFINE_BLOCK(b_producer_v2, 0, 2)
{
public:
  _local_(int, nItemsTotal, 10000);
private:
  _local_(int, nItemsEach, 1);  
  _local_(int, nItemsLeft, 10000);


  BLOCK_INIT
  {
    auto v = $["nItemsEach"];
    if (!v.empty())
    {
      *nItemsEach = atoi(v.c_str());
    }

    v = $["nItemsTotal"];
    if (!v.empty())
    {
      *nItemsTotal = atoi(v.c_str());
      *nItemsLeft  = *nItemsTotal;
    }
  }

  BLOCK_WORK
  {
    trace();
    if (*nItemsLeft <= 0)
    {
      return false;
    }

    auto op1 = $_<uint8>(0);
    auto op2 = $_<uint8>(0);

    for (int i = 0; i < *nItemsEach; i++)
    {
      op1[i] = 7;
      op2[i] = 7;
    }

    produce_each(*nItemsEach);
    //printf("producer: %d items\n", *nItemsEach);
    *nItemsLeft -= *nItemsEach;
    return true;
  }
};