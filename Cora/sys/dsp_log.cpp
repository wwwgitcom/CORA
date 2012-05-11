#include "stdafx.h"
#include "dsp_log.h"

dsp_log::dsp_log()
{
  m_include_filters.resize(0);
  m_exclude_filters.resize(0);
  m_handle = stdout;
}

dsp_log::~dsp_log(){}

dsp_log& dsp_log::Instance()
{
  static dsp_log s_log;

  return s_log;
}

void dsp_log::clear_filters()
{
  m_include_filters.clear();
  m_exclude_filters.clear();
}

void dsp_log::add_include_filter(std::string keyword)
{
  m_include_filters.push_back(keyword);
}

void dsp_log::add_include_filter(const char * keyword)
{
  std::string str_keywork(keyword);
  m_include_filters.push_back(str_keywork);
}
void dsp_log::add_exclude_filter(std::string keyword)
{
  m_exclude_filters.push_back(keyword);
}

void dsp_log::add_exclude_filter(const char * keyword)
{
  std::string str_keywork(keyword);
  m_exclude_filters.push_back(str_keywork);
}

void dsp_log::operator()(const char * format, ... )
{
  va_list argp;
  bool b_show_up = true;

  char msg[2048];

  memset(msg, 0, sizeof(msg));
  va_start(argp, format);

  try{
    vsprintf_s(msg, 2048, format, argp);
  }
  catch(char * e){
    perror(e);
  }
  va_end(argp);

  if (m_include_filters.size() != 0)
  {
    b_show_up = false;
    for(unsigned int i = 0; i < m_include_filters.size(); i++)
    {
      if ( strstr(msg, m_include_filters[i].c_str()) )
      {
        b_show_up = true;
        break;
      }
    }
  }

  if (m_exclude_filters.size() != 0)
  {
    for(unsigned int i = 0; i < m_exclude_filters.size(); i++)
    {
      if ( strstr(msg, m_exclude_filters[i].c_str()) )
      {
        b_show_up = false;
        break;
      }
    }
  }

  if (b_show_up)
  {
    fprintf(m_handle, "%s", msg);
  }
}

