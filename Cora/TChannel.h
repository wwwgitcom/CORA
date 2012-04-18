#pragma once

#include "TObject.h"
#include "dsp_buffer.h"
#include <utility>
#include <map>
#include <vector>

using namespace std;

class ChannelReader
{
public:  
};

class ChannelReaderShared : public ChannelReader
{
public:  
  void Shared(){}
};

class ChannelReaderIndependent : public ChannelReader
{
public:  
  void Independent(){}
};


class Channel
{
private:
  pair<dsp_buffer_ptr, dsp_buffer_reader_ptr> m_channel;
  vector<dsp_buffer_ptr> m_buffers;
  vector<dsp_buffer_reader_ptr> m_buffer_readers;
public:

  static Channel& Create(int ItemSize = 1, int MinItemCount = 1)
  {
    cout << "Create channel " << ItemSize << " " << MinItemCount << endl;
    return CreateObject<Channel, int, int>(MinItemCount, ItemSize);
  }

  Channel(int nItem = 1, int ItemSize = 1)
  {
      auto buffer        = dsp_make_buffer(nItem, ItemSize);
      auto buffer_reader = dsp_buffer_add_reader(buffer);
      m_channel.first    = buffer;
      m_channel.second   = buffer_reader;

      m_buffers.push_back(buffer);
      m_buffer_readers.push_back(buffer_reader);
  }
  ~Channel()
  {
    for (auto i = m_buffers.begin(); i != m_buffers.end(); i++)
    {
      delete (*i);
    }

    for (auto i = m_buffer_readers.begin(); i != m_buffer_readers.end(); i++)
    {
      delete (*i);
    }
  }

  template<typename S>
  Channel& from(S &src, int src_port)
  {
    src.set_output(m_channel.first, src_port);
    return (*this);
  }


  template<typename D>
  Channel& to(D &dst, int dst_port, bool r = true)
  {
    if(r)
    {
      dst.set_input(m_channel.second, dst_port);
    }
    else
    {
      auto buffer_reader = dsp_buffer_add_reader(m_channel.first);
      dst.set_input(buffer_reader, dst_port);
      m_buffer_readers.push_back(buffer_reader);
    }
    return (*this);
  }
};