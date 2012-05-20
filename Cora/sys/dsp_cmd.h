#pragma once

class arg_obj
{
  string str_obj;
public:
  arg_obj(string str) : str_obj(str){}
  arg_obj(char* str) : str_obj(str){}

  bool exist()
  {
    return !str_obj.empty();
  }

  int as_int()
  {
    return atoi(str_obj.c_str());
  }
  uint as_uint()
  {
    return (uint)atoi(str_obj.c_str());
  }
  float as_float()
  {
    return (float)atof(str_obj.c_str());
  }
  double as_double()
  {
    return atof(str_obj.c_str());
  }
  long as_long()
  {
    return atol(str_obj.c_str());
  }
};

class dsp_cmd
{
  map<string, string> m_cmd_map;

public:
  void parse(int argc, _TCHAR* argv[])
  {
    for (int i = 0; i < argc; i++)
    {
      string str_arg(argv[i]);

      int pos = str_arg.find("=");
      if (pos < 0) continue;

      m_cmd_map.insert( make_pair(str_arg.substr(0, pos), str_arg.substr(pos + 1) ) );    
    }

    cout << "----------------------------------" << endl;
    for (auto i = m_cmd_map.begin(); i != m_cmd_map.end(); i++)
    {
      cout << " Arg: " << i->first << ", Value: " << i->second << endl;
    }
    cout << "----------------------------------" << endl;
  }

  arg_obj get(char* arg)
  {
    arg_obj cmd(m_cmd_map[arg]);
    return cmd;
  }
};