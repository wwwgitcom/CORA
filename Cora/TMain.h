#pragma once


struct ConsoleEventItem
{
  DWORD dwEventId;
  char* szEvent;
  ostream& operator << (ostream& os)
  {
    os << "Console Event: " << szEvent << endl;
    return os;
  }
};

#define DECLARE_EVENT(_event_) \
{_event_, #_event_}

#define CTRL_MAX_EVENT (CTRL_SHUTDOWN_EVENT + 1)
__declspec(selectany) ConsoleEventItem ConsoleEventTable[] = 
{
  DECLARE_EVENT(CTRL_C_EVENT),
  DECLARE_EVENT(CTRL_BREAK_EVENT),
  DECLARE_EVENT(CTRL_CLOSE_EVENT),
  DECLARE_EVENT(3),
  DECLARE_EVENT(4),
  DECLARE_EVENT(CTRL_LOGOFF_EVENT),
  DECLARE_EVENT(CTRL_SHUTDOWN_EVENT),
  DECLARE_EVENT(CTRL_MAX_EVENT),
};

inline ConsoleEventItem& ConsoleEvent(DWORD dwEvt)
{
  if (dwEvt > CTRL_MAX_EVENT)
  {
    dwEvt = CTRL_MAX_EVENT;
  }
  return ConsoleEventTable[dwEvt];
}


template<typename _Function>
void dsp_main(const _Function& _Func)
{
  task_obj obj = make_task_obj(_Func);
  cpu_manager::Instance()->run_task(&obj);

  //printf("Main thread suspened...\n");
  //SuspendThread(GetCurrentThread());

  //////////////////////////////////////////////////////////////////////////
  HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE);

  /*DWORD dwConsoleMode = 0;
  
  GetConsoleMode(hStdInput, &dwConsoleMode);
  dwConsoleMode ^= ENABLE_LINE_INPUT;
  SetConsoleMode(hStdInput, dwConsoleMode);
  */
  FlushConsoleInputBuffer(hStdInput);

  DWORD dwWaitObj = 0;
  DWORD dwNumberOfEvents = 0;
  DWORD dwNumberOfEventsRead = 0;
  INPUT_RECORD InputRec;
  DWORD dwConsoleEventCount = 0;
  BOOL  bQuit = false;
  while(!bQuit)
  {
    dwWaitObj = WaitForSingleObject(hStdInput, INFINITE);
    dwNumberOfEvents = 0;
    dwNumberOfEventsRead = 0;

    GetNumberOfConsoleInputEvents(hStdInput, &dwNumberOfEvents);

    BOOL bRet = ReadConsoleInput(hStdInput, &InputRec, 1, &dwNumberOfEventsRead);
    if (InputRec.Event.KeyEvent.bKeyDown)
    {
      UCHAR uInputChar = InputRec.Event.KeyEvent.uChar.AsciiChar;
#if 0
      printf("Console input: bKeyDown=%d, dwControlKeyState=%p, wRepeatCount=%d, wVirtualKeyCode=%d, wVirtualScanCode=%d, AsciiChar=%c\n", 
        InputRec.Event.KeyEvent.bKeyDown,
        InputRec.Event.KeyEvent.dwControlKeyState,
        InputRec.Event.KeyEvent.wRepeatCount,
        InputRec.Event.KeyEvent.wVirtualKeyCode,
        InputRec.Event.KeyEvent.wVirtualScanCode,
        InputRec.Event.KeyEvent.uChar.AsciiChar);
#endif

      // broadcast keyboard input to all blocks
      _GlobalBlockMan.event_handler(InputRec);

      // global handler responding to q & Q to exit program
      if (uInputChar == 'q' || uInputChar == 'Q')
      {
        bQuit = true;
      }
    }
  }
  dsp_console::info("Quit program... \n");
}