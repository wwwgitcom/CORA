#pragma once

class dsp_log
{
private:
  FILE* m_handle;
  std::vector<std::string> m_include_filters;
  std::vector<std::string> m_exclude_filters;
  dsp_log();
  ~dsp_log();
public:
  static dsp_log& Instance();
  void add_include_filter(std::string keyword);
  void add_include_filter(const char * keyword);
  void add_exclude_filter(std::string keyword);
  void add_exclude_filter(const char * keyword);
  void clear_filters();
  void operator()(const char * format, ... );
};
extern dsp_log& _log;

#if 1
#define log(...)
#else
#define log _log
#endif
