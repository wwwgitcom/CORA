#pragma once

// CT: subclass type
// ET: element type
// nDimetion: matrix dimension, square matrix
// nChannel: how many channels

template<int size, int align_byte>
class align_to
{
  static const int nLeft    = size % align_to;
  static const int nPadding = (nLeft > 0 ? (align_byte - nLeft) : 0);
  static const int value    = nPadding;
};

#if 0
template<typename CT, typename ET, int nDimension, int nChannel>
class dsp_channel_matrix
{
protected:
  typedef ET  element_type;
  typedef CT sub_class_type;
  static const int nCacheSize             = 64;
  static const int nVecSize               = 16;
  static const int nChannelRowSize        = sizeof(element_type) * nChannel;
  static const int nAlignedChannelRowSize = align_to<nChannelRowSize, nVecSize>::value;
  static const int nRowSize               = align_to<nAlignedChannelRowSize * nDimemsion, nCacheSize>::value;

  typedef vec_channel_row ET[nAlignedChannelRowSize];
  typedef vec_mat vec_channel_row[nDimension][nDimension];
  
  // internal storage for matrix
  vec_mat vmat;

public:
  __forceinline
  ET& operator()(int ch, int row, int column)
  {
    return vmat[row][column][ch];
  }

  __forceinline
  ET&& operator()(int ch, int row, int column)
  {
    return vmat[row][column][ch];
  }

  __forceinline
  ostream& operator<<(ostream &os)
  {
    __if_exists(sub_class_type::operator())
    {
      sub_class_type subthis = (sub_class_type*)this;
      return subthis->operator()(os);
    }
    __if_not_exists(sub_class_type::operator())
    {
      return os;
    }
  }
};

// sub-class
template<int nDimension, int nChannel>
class dsp_channel_matrix_f : public dsp_channel_matrix<dsp_channel_matrix_f, float, nDimention, nChannel>
{

};
#endif