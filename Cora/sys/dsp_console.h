#pragma once

class dsp_console
{
  static void print(WORD color, const char* format, ...)
  {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scinfo;
    GetConsoleScreenBufferInfo(hConsole, &scinfo);
    WORD wOldAttr = scinfo.wAttributes;
    WORD wNewAttr = wOldAttr;

    wNewAttr |= color;

    SetConsoleTextAttribute(hConsole, wNewAttr);

    va_list args;
    va_start(args, format);

    printf(format, args);

    SetConsoleTextAttribute(hConsole, wOldAttr);

    va_end(args);
  }
public:
  static void info(const char* format, ...)
  {
    va_list args;
    va_start(args, format);

    print((FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY), 
      format, args);

    va_end(args);
  }
  static void warning(const char* format, ...)
  {  
    va_list args;
    va_start(args, format);

    print((FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY), 
      format, args);

    va_end(args);
  }
  static void error(const char* format, ...)
  {  
    va_list args;
    va_start(args, format);

    print((FOREGROUND_RED | FOREGROUND_INTENSITY), 
      format, args);

    va_end(args);
  }

};

