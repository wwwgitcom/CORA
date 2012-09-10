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

    print((BACKGROUND_RED | BACKGROUND_GREEN), 
      format, args);

    va_end(args);
  }
  static void warning(const char* format, ...)
  {  
    va_list args;
    va_start(args, format);

    print((BACKGROUND_RED), 
      format, args);

    va_end(args);
  }
};

