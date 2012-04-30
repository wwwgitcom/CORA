#include "stdafx.h"
#include "dsp_draw.h"

//////////////////////////////////////////////////////////////////////////
// BEGIN

// Static VAR
//////////////////////////////////////////////////////////////////////////
BOOL      dsp_draw_window::m_bWindowClassRegistered      = FALSE;
LONG      GdiPlusWrapper::m_RefCount          = 0;
ULONG_PTR GdiPlusWrapper::m_gdiplusToken      = 0;

// Static FUNC
//////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK dsp_draw_window::stWndProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  dsp_draw_window * pWnd;
  if ( uMsg == WM_NCCREATE ) 
  {
    SetWindowLong ( hWnd, GWL_USERDATA, (long) ((LPCREATESTRUCT(lParam))->lpCreateParams));
  }

  pWnd = GetThisFromWindow ( hWnd );
  if ( pWnd ) 
  {
    return pWnd->WndProc ( hWnd, uMsg, wParam, lParam);
  }
  else
  {
    return DefWindowProc ( hWnd, uMsg, wParam, lParam );
  }
}

dsp_draw_window* dsp_draw_window::GetThisFromWindow(HWND hWnd)
{
  return (dsp_draw_window *)GetWindowLong(hWnd, GWL_USERDATA);
}

DWORD WINAPI dsp_draw_window::msg_dispatch_thread(LPVOID lpdwThreadParam)
{
  dsp_draw_window* me = (dsp_draw_window*)lpdwThreadParam;

  DWORD dwWaitResult;
  BOOL  bICreated = FALSE;

  dwWaitResult = WaitForSingleObject( 
    me->m_WindowMutex,    // handle to mutex
    INFINITE);  // no time-out interval

  switch (dwWaitResult) 
  {
    // The thread got ownership of the mutex
  case WAIT_OBJECT_0: 
    __try
    {
      if ( !me->m_bWindowCreated )
      {
        me->m_bWindowCreated = me->CreateDrawWindow();
        bICreated = TRUE;
      }
    } 

    __finally 
    { 
      // Release ownership of the mutex object
      if (! ReleaseMutex(me->m_WindowMutex)) 
      { 
        // Handle error.
      } 
    } 
    break; 

    // The thread got ownership of an abandoned mutex
    // The database is in an indeterminate state
  case WAIT_ABANDONED: 
    return FALSE; 
  }

  if (me->m_bWindowCreated && bICreated)
  {
    me->MessageLoop();
  }

  return 1;
}

// CONSTRUCTOR & DESTRUCTOR
//////////////////////////////////////////////////////////////////////////
dsp_draw_window::dsp_draw_window
  (
  const char* pszTitle, int x, int y, int Width, int Height,
  Color BkColor,
  Color BkPenColor, float BkPenWidth, 
  Color AxisPenColor, float AxisPenWidth,
  Color PenColor, float PenWidth,
  Color FontColor
  )
  : m_GdiplusWrapper(),
  m_WindowX(x), m_WindowY(y), m_WindowWidth(Width), m_WindowHeight(Height),
  m_CanvasWidth(m_BitmapWidth), m_CanvasHeight(m_BitmapHeight),
  m_BoundBox(0, 0, m_BitmapWidth - 1, m_BitmapHeight - 1), 
  m_BkColor(BkColor), m_BkPen(BkPenColor, BkPenWidth),
  m_Pen(PenColor, PenWidth), m_AxisPen(AxisPenColor, AxisPenWidth),
  m_DefaultBkBitmap(m_BitmapWidth, m_CanvasHeight),
  m_Font(FontFamily::GenericSansSerif(), 14, FontStyleBold, UnitPixel),
  m_FontBrush(FontColor)
{
  m_GridStepX = (float)m_CanvasWidth / (float)m_nGridX;
  m_GridStepY = (float)m_CanvasHeight / (float)m_nGridY;

  m_AxisPen.SetLineCap(LineCapTriangle, LineCapArrowAnchor, DashCapTriangle);

  m_pDefaultBkGraphics = Graphics::FromImage(&m_DefaultBkBitmap);
  //m_pDefaultBkGraphics->SetInterpolationMode(InterpolationModeHighQualityBicubic);
  //m_pDefaultBkGraphics->SetPixelOffsetMode(PixelOffsetModeHighQuality);
  //m_pDefaultBkGraphics->SetCompositingQuality(CompositingQualityHighQuality);
  //m_pDefaultBkGraphics->SetSmoothingMode(SmoothingModeHighQuality);

  DrawBackGround(m_pDefaultBkGraphics);

  m_pPrevBitmap = &m_DefaultBkBitmap;

  InitializeListHead(&m_DrawFreeList);
  InitializeListHead(&m_DrawBusyList);

  for (int i = 0; i < nDrawDesc; i++)
  {
    m_DrawDesc[i].pCanvas = new Bitmap(m_CanvasWidth, m_CanvasHeight);
    m_DrawDesc[i].pGraphics = Graphics::FromImage(m_DrawDesc[i].pCanvas);

    // For faster rendering, disable high quality properties
    //m_DrawDesc[i].pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
    //m_DrawDesc[i].pGraphics->SetInterpolationMode(InterpolationModeHighQualityBicubic);
    //m_DrawDesc[i].pGraphics->SetPixelOffsetMode(PixelOffsetModeHighQuality);
    //m_DrawDesc[i].pGraphics->SetCompositingQuality(CompositingQualityHighQuality);
    //m_DrawDesc[i].pGraphics->SetSmoothingMode(SmoothingModeHighQuality);

    InsertTailList(&m_DrawFreeList, &m_DrawDesc[i].Entry);
  }

  //////////////////////////////////////////////////////////////////////////
  memset(m_WindowTitle, 0, m_nWindowTitleLength * sizeof(char));
  if (NULL == pszTitle)
  {
    strcpy_s(m_WindowTitle, m_nWindowTitleLength, "Untiled Window");
  }
  else
  {
    strcpy_s(m_WindowTitle, m_nWindowTitleLength, pszTitle);
  }

  m_DrawFreeListMutex = CreateMutex(
    NULL,              // default security attributes
    FALSE,             // initially not owned
    NULL);             // unnamed mutex

  m_DrawBusyListMutex = CreateMutex(
    NULL,              // default security attributes
    FALSE,             // initially not owned
    NULL);             // unnamed mutex

  m_WindowMutex = CreateMutex(
    NULL,              // default security attributes
    FALSE,             // initially not owned
    NULL);             // unnamed mutex

  m_bWindowClose         = FALSE;
  m_hWnd           = NULL;
  m_bWindowCreated = FALSE;
  Create();
}

dsp_draw_window::~dsp_draw_window()
{
  if (m_pDefaultBkGraphics)
  {
    delete m_pDefaultBkGraphics;
    m_pDefaultBkGraphics = NULL;
  }

  m_pPrevBitmap = NULL;

  for (int i = 0; i < nDrawDesc; i++)
  {
    delete m_DrawDesc[i].pCanvas;
    delete m_DrawDesc[i].pGraphics;
  }

  CloseHandle(m_DrawFreeListMutex);
  CloseHandle(m_DrawBusyListMutex);
  CloseHandle(m_WindowMutex);
}
// DRAW LIST
//////////////////////////////////////////////////////////////////////////
PDSP_DRAW_DESC dsp_draw_window::PopFreeDrawDesc()
{
  DWORD dwWaitResult;

  dwWaitResult = WaitForSingleObject( 
    m_DrawFreeListMutex,    // handle to mutex
    INFINITE);  // no time-out interval

  switch (dwWaitResult) 
  {
    // The thread got ownership of the mutex
  case WAIT_OBJECT_0: 
    __try {
      if ( IsListEmpty(&m_DrawFreeList) )
      {
        return NULL;
      }

      return (PDSP_DRAW_DESC)RemoveHeadList(&m_DrawFreeList);
    } 

    __finally { 
      // Release ownership of the mutex object
      if (! ReleaseMutex(m_DrawFreeListMutex)) 
      { 
        // Handle error.
      } 
    } 
    break; 

    // The thread got ownership of an abandoned mutex
    // The database is in an indeterminate state
  case WAIT_ABANDONED: 
    ; 
  }
  return NULL;
}

void dsp_draw_window::PushFreeDrawDesc(PDSP_DRAW_DESC pDrawDesc)
{
  DWORD dwWaitResult;

  dwWaitResult = WaitForSingleObject( 
    m_DrawFreeListMutex,    // handle to mutex
    INFINITE);  // no time-out interval

  switch (dwWaitResult) 
  {
    // The thread got ownership of the mutex
  case WAIT_OBJECT_0: 
    __try {
      InsertTailList(&m_DrawFreeList, &pDrawDesc->Entry);
    } 

    __finally { 
      // Release ownership of the mutex object
      if (! ReleaseMutex(m_DrawFreeListMutex)) 
      { 
        // Handle error.
      } 
    } 
    break; 

    // The thread got ownership of an abandoned mutex
    // The database is in an indeterminate state
  case WAIT_ABANDONED: 
    ;
  }
}

void dsp_draw_window::PushToDraw(PDSP_DRAW_DESC pDrawDesc)
{
  DWORD dwWaitResult;

  dwWaitResult = WaitForSingleObject( 
    m_DrawBusyListMutex,    // handle to mutex
    INFINITE);  // no time-out interval

  switch (dwWaitResult) 
  {
    // The thread got ownership of the mutex
  case WAIT_OBJECT_0: 
    __try {                
      InsertTailList(&m_DrawBusyList, &pDrawDesc->Entry);
    } 

    __finally { 
      // Release ownership of the mutex object
      if (! ReleaseMutex(m_DrawBusyListMutex)) 
      { 
        // Handle error.
      }
      //InvalidateRect()
    } 
    break; 

    // The thread got ownership of an abandoned mutex
    // The database is in an indeterminate state
  case WAIT_ABANDONED: 
    ;
  }
}

PDSP_DRAW_DESC dsp_draw_window::PopToDraw()
{
  DWORD dwWaitResult;

  dwWaitResult = WaitForSingleObject( 
    m_DrawBusyListMutex,    // handle to mutex
    INFINITE);  // no time-out interval

  switch (dwWaitResult) 
  {
    // The thread got ownership of the mutex
  case WAIT_OBJECT_0: 
    __try
    {
      if ( IsListEmpty(&m_DrawBusyList) )
      {
        return NULL;
      }

      return (PDSP_DRAW_DESC)RemoveHeadList(&m_DrawBusyList);
    } 

    __finally 
    { 
      // Release ownership of the mutex object
      if (! ReleaseMutex(m_DrawBusyListMutex)) 
      { 
        // Handle error.
      } 
    } 
    break; 

    // The thread got ownership of an abandoned mutex
    // The database is in an indeterminate state
  case WAIT_ABANDONED: 
    return NULL; 
  }
  return NULL;
}

// GIDPlus
//////////////////////////////////////////////////////////////////////////
Gdiplus::Rect dsp_draw_window::CopyRect(RECT &rect)
{    
  return Gdiplus::Rect(rect.top, rect.left, rect.right - rect.left, rect.bottom - rect.top);
}

void dsp_draw_window::DrawBackGround(Graphics* pGraphics)
{
  pGraphics->Clear(m_BkColor);

  for (int i = 0; i < m_nGridX; i++)
  {
    REAL fx = i * m_GridStepX;

    pGraphics->DrawLine(&m_BkPen, 
      PointF(fx, (REAL)m_BoundBox.GetTop()), 
      PointF(fx, (REAL)m_BoundBox.GetBottom())
      );
  }

  for (int i = 0; i < m_nGridY; i++)
  {
    REAL fy = i * m_GridStepY;

    pGraphics->DrawLine(&m_BkPen, 
      PointF((REAL)m_BoundBox.GetLeft(), fy), 
      PointF((REAL)m_BoundBox.GetRight(), fy)
      );
  }
  pGraphics->DrawRectangle(&m_BkPen, m_BoundBox);
}

void dsp_draw_window::_OnDraw(Graphics *pGraphics)
{
  RECT rect;
  Rect rectplus;
  do 
  {
    GetClientRect(m_hWnd, &rect);

    rectplus = CopyRect(rect);

    PDSP_DRAW_DESC pDrawDesc = PopToDraw();
    if (NULL == pDrawDesc)
    {
      pGraphics->DrawImage(m_pPrevBitmap, rectplus);

      break;
    }
    pGraphics->DrawImage(pDrawDesc->pCanvas, rectplus);

    m_pPrevBitmap = pDrawDesc->pCanvas;

    PushFreeDrawDesc(pDrawDesc);
  } while (FALSE);
}

// Internal Draw
void dsp_draw_window::_DrawPoint(Graphics* pGraphics, PointF &point)
{
  pGraphics->DrawLine(&m_Pen,
    PointF(point.X - 8, point.Y), 
    PointF(point.X + 8, point.Y));

  pGraphics->DrawLine(&m_Pen,
    PointF(point.X, point.Y - 8), 
    PointF(point.X, point.Y + 8));
}

void dsp_draw_window::_DrawLine(Graphics* pGraphics, PointF &point1, PointF &point2)
{
  pGraphics->DrawLine(&m_Pen, point1, point2);
}

// DISPLAY WINDOW
//////////////////////////////////////////////////////////////////////////
void dsp_draw_window::RegisterWindowClass ( )
{
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style			= CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc	= dsp_draw_window::stWndProc;
  wcex.cbClsExtra		= 0;
  wcex.cbWndExtra		= 0;
  wcex.hInstance		= GetModuleHandle(NULL);
  wcex.hIcon			= NULL;
  wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName	= NULL; /// MAKEINTRESOURCE(IDC_SRVIEW);
  wcex.lpszClassName	= "dsp_draw_window";
  wcex.hIconSm		= NULL;

  RegisterClassEx(&wcex);
}
LRESULT CALLBACK dsp_draw_window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hdc;        
  Graphics *g;

  switch (uMsg)
  {
  case WM_PAINT:
    //printf("Pain message\n");
    hdc = BeginPaint(m_hWnd, &ps);
    g = Graphics::FromHDC(hdc);

    _OnDraw(g);

    delete g;

    EndPaint(m_hWnd, &ps);
    break;
  case WM_DESTROY:
    m_bWindowClose = TRUE;
    break;
  default:
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }
  return 0;
}

BOOL dsp_draw_window::CreateDrawWindow()
{
  if (!dsp_draw_window::m_bWindowClassRegistered)
  {
    RegisterWindowClass();
    dsp_draw_window::m_bWindowClassRegistered = true;
  }

  m_hWnd = CreateWindow ( "dsp_draw_window", m_WindowTitle, WS_OVERLAPPEDWINDOW,
    m_WindowX, m_WindowY, m_WindowWidth, m_WindowHeight,
    NULL, NULL, GetModuleHandle(NULL), (void*)this 
    );

  if ( m_hWnd == NULL ) return FALSE;

  this->ShowWindow();

  return TRUE;
}

BOOL dsp_draw_window::Create()
{
  if ( m_bWindowCreated ) 
    return FALSE;

  m_hWindowMsgDispatchThread = CreateThread(NULL, 0, dsp_draw_window::msg_dispatch_thread, this, 0, NULL);
  if ( m_hWindowMsgDispatchThread == NULL ) return FALSE;

  CloseHandle(m_hWindowMsgDispatchThread);

  return TRUE;
}

BOOL dsp_draw_window::ShowWindow ()
{
  if ( m_hWnd == NULL ) 
    return FALSE;

  ::ShowWindow(m_hWnd, SW_SHOW);
  ::UpdateWindow(m_hWnd);

  // does not work :(
  //::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED);  

  return TRUE;
}

void dsp_draw_window::MessageLoop()
{
  // Just message loop
  BOOL bRet;
  MSG msg;
  m_bWindowClose = FALSE;

  while(!m_bWindowClose)
  {
    while( (bRet = ::GetMessage(&msg, m_hWnd, 0, 0)) != 0 )
    {
      if (bRet == -1)
      {
        printf("invalid msg\n");
        break;
      }
      ::TranslateMessage(&msg); 
      ::DispatchMessage(&msg); 
    }
  }
  m_hWnd = NULL;
  m_bWindowCreated = FALSE;
}

// END
//////////////////////////////////////////////////////////////////////////