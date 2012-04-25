template<int nbpsc>
struct dot11n_deinterleaver 
{
    static_assert((nbpsc == 1 || nbpsc == 2 || nbpsc == 4 || nbpsc == 6), 
        "nbpsc only takes 1, 2, 4, 6");

    static const int total_sc      = 52;
    static const int bit_per_sc    = nbpsc;
    static const int total_bits    = total_sc * bit_per_sc;
    static const int block_bits    = (nbpsc / 2) ? (nbpsc / 2) : 1;
    
    // make sure the number of total_bits can be fit in the range of __int16
    __int16 lookuptable[total_bits];

    dot11n_deinterleaver(){}

    dot11n_deinterleaver(int iss)
    {
        zero_lookuptable();
        create_lookuptable(iss);
    }
    
    void init(int iss)
    {
        zero_lookuptable();
        create_lookuptable(iss);
    }

    __forceinline void operator()(unsigned __int8 *pInput, unsigned __int8* pOutput)
    {
        for (int k = 0; k < total_bits; k++)
        {
            //printf("%d->%d\n", k, lookuptable[k]);
            pOutput[ lookuptable[k] ] = pInput[k];
        }
    }
    
protected:
    void zero_lookuptable()
    {
        memset(lookuptable, 0, total_bits * sizeof(int));
    }

    void create_lookuptable(int iss)
    {
        for (int i = 0; i < total_bits; i++)
        {
            lookuptable[i] = (__int16)interleave(iss, i);
        }
    }

    int interleave(int iss, int k)
    {
        int temp = round1(iss, k);
        temp     = round2(temp);
        temp     = round3(temp);
        return temp;
    }

    int round1(int iss, int k)
    {
        return (k + ( ( (iss - 1) * 2 ) % 3 + 3 * ((iss - 1) / 3) ) * 11 * bit_per_sc) % total_bits;
    }

    int round2(int k)
    {
        return block_bits * (k / block_bits) + (k + (13 * k) / total_bits) % block_bits;
    }

    int round3(int k)
    {
        return (k * 13) - (total_bits - 1) * (k / (4 * bit_per_sc));
    }
};