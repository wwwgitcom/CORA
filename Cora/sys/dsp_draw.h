#pragma once






typedef struct _DSP_DRAW_DESC
{
  LIST_ENTRY Entry;
  Bitmap*    pCanvas;
  Graphics*  pGraphics;
}DSP_DRAW_DESC, *PDSP_DRAW_DESC;

class GdiPlusWrapper
{
public:
  static LONG      m_RefCount;
  static ULONG_PTR m_gdiplusToken;

  GdiPlusWrapper()
  {
    // init GDI+
    GdiPlusWrapper::m_RefCount++;

    if (GdiPlusWrapper::m_RefCount == 1)
    {
      Gdiplus::GdiplusStartupInput gdiplusStartupInput;
      Gdiplus::Status st = Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
      printf("GdiPlut Init Status = %p\n", st);
    }
  }

  ~GdiPlusWrapper()
  {
    GdiPlusWrapper::m_RefCount--;
    if (GdiPlusWrapper::m_RefCount == 0)
    {
      GdiplusShutdown(m_gdiplusToken);
    }
  }
};


class dsp_draw_window
{
public:
  static const int     m_BitmapWidth              = 600;
  static const int     m_BitmapHeight             = 600;
  static const int     m_nGridX                   = 32;
  static const int     m_nGridY                   = 32;
  static const int     m_nWindowTitleLength       = 1024;
  static const int     nDrawDesc                  = 128;

  dsp_draw_window(const char* pszTitle, int x, int y, int Width, int Height,
    Color BkColor      = Color::Black,
    Color BkPenColor   = Color::LightGray, float BkPenWidth   = 1.0f, 
    Color AxisPenColor = Color(255, 0, 0), float AxisPenWidth = 3.0f, 
    Color PenColor     = Color(0, 255, 128), float PenWidth     = 8.0f,
    Color FontColor    = Color::Yellow
    );

  ~dsp_draw_window();

private:
  // 
  PDSP_DRAW_DESC PopFreeDrawDesc();
  void PushFreeDrawDesc(PDSP_DRAW_DESC pDrawDesc);
  void PushToDraw(PDSP_DRAW_DESC pDrawDesc);
  PDSP_DRAW_DESC PopToDraw();
  Gdiplus::Rect CopyRect(RECT &rect);

public:
  template<typename T>
  BOOL DrawCustomized(T* pData, int N)
  {
    BOOL bRet = FALSE;
    do 
    {
      Create();

      PDSP_DRAW_DESC pDrawDesc = PopFreeDrawDesc();
      if (NULL == pDrawDesc)
      {
        break;
      }

      DrawBackGround(pDrawDesc->pGraphics);

      OnDraw(pDrawDesc->pGraphics, pData, N);

      PushToDraw(pDrawDesc);

      InvalidateRect(m_hWnd, NULL, true);
      UpdateWindow(m_hWnd);

      bRet = TRUE;
    } while (FALSE);

    return bRet;
  }

  // Some Pre-Defined Drawing Functions
  template<typename T>
  BOOL DrawLine(T* pData, int N)
  {
    BOOL bRet = FALSE;
    do 
    {
      Create();

      PDSP_DRAW_DESC pDrawDesc = PopFreeDrawDesc();
      if (NULL == pDrawDesc)
      {
        break;
      }

      DrawBackGround(pDrawDesc->pGraphics);

      _Draw(pDrawDesc->pGraphics, pData, N);

      PushToDraw(pDrawDesc);

      InvalidateRect(m_hWnd, NULL, FALSE);
      UpdateWindow(m_hWnd);

      bRet = TRUE;
    } while (FALSE);

    return bRet;
  }

  template<typename T>
  BOOL DrawLineWithNegative(T* pData, int N)
  {
    BOOL bRet = FALSE;
    do 
    {
      Create();

      PDSP_DRAW_DESC pDrawDesc = PopFreeDrawDesc();
      if (NULL == pDrawDesc)
      {
        break;
      }

      DrawBackGround(pDrawDesc->pGraphics);

      _DrawWithNegativeAxis(pDrawDesc->pGraphics, pData, N);

      PushToDraw(pDrawDesc);

      InvalidateRect(m_hWnd, NULL, FALSE);
      UpdateWindow(m_hWnd);

      bRet = TRUE;
    } while (FALSE);

    return bRet;
  }

  template<typename T>
  BOOL DrawScatter(T* pData, int N)
  {
    BOOL bRet = FALSE;
    do 
    {
      Create();

      PDSP_DRAW_DESC pDrawDesc = PopFreeDrawDesc();
      if (NULL == pDrawDesc)
      {
        break;
      }

      DrawBackGround(pDrawDesc->pGraphics);

      _CDrawScatter(pDrawDesc->pGraphics, pData, N);

      PushToDraw(pDrawDesc);

      InvalidateRect(m_hWnd, NULL, FALSE);
      UpdateWindow(m_hWnd);

      bRet = TRUE;
    } while (FALSE);

    return bRet;
  }

  template<typename T>
  BOOL DrawComplex(T* pData, int N)
  {
    BOOL bRet = FALSE;
    do 
    {
      Create();

      PDSP_DRAW_DESC pDrawDesc = PopFreeDrawDesc();
      if (NULL == pDrawDesc)
      {
        break;
      }

      DrawBackGround(pDrawDesc->pGraphics);

      _CDrawLine(pDrawDesc->pGraphics, pData, N);

      PushToDraw(pDrawDesc);

      InvalidateRect(m_hWnd, NULL, FALSE);
      UpdateWindow(m_hWnd);

      bRet = TRUE;
    } while (FALSE);

    return bRet;
  }

  template<typename T>
  BOOL DrawSqrt(T* pData, int N)
  {
    BOOL bRet = FALSE;
    do 
    {
      Create();

      PDSP_DRAW_DESC pDrawDesc = PopFreeDrawDesc();
      if (NULL == pDrawDesc)
      {
        break;
      }

      DrawBackGround(pDrawDesc->pGraphics);

      _CSqrtDraw(pDrawDesc->pGraphics, pData, N);

      PushToDraw(pDrawDesc);

      InvalidateRect(m_hWnd, NULL, FALSE);
      UpdateWindow(m_hWnd);

      bRet = TRUE;
    } while (FALSE);

    return bRet;
  }

  template<typename T>
  BOOL DrawSqrtShift(T* pData, int N)
  {
    BOOL bRet = FALSE;
    do 
    {
      Create();

      PDSP_DRAW_DESC pDrawDesc = PopFreeDrawDesc();
      if (NULL == pDrawDesc)
      {
        break;
      }

      DrawBackGround(pDrawDesc->pGraphics);

      _CSqrtShiftDraw(pDrawDesc->pGraphics, pData, N);

      PushToDraw(pDrawDesc);

      InvalidateRect(m_hWnd, NULL, FALSE);
      UpdateWindow(m_hWnd);

      bRet = TRUE;
    } while (FALSE);

    return bRet;
  }

  // User Defined Draw Function
  virtual void OnDraw(Graphics* pGraphics, void* pData, int N){}

  // A common background
  virtual void DrawBackGround(Graphics* pGraphics);

protected:
  // Internal Helper Template Functions
  template<typename T>
  REAL MakeX(T &Data, REAL &NormFactor)
  {
    return (REAL)Data;
  }

  template<typename T>
  REAL MakeY(T &Data, REAL &NormFactor)
  {
    REAL y = ( ((REAL)m_CanvasHeight / 2.0f) * ((REAL)Data / (REAL)NormFactor) );
    return (REAL)m_CanvasHeight / 2.0f - y;
  }

  template<typename T>
  REAL MakeYPositive(T &Data, REAL &NormFactor)
  {
    REAL y = ( ((REAL)m_CanvasHeight) * ((REAL)Data / (REAL)NormFactor) );
    return (REAL)m_CanvasHeight - y;
  }

  template<typename T>
  REAL CMakeY(T &Data, REAL &NormFactor)
  {
    REAL y = ( ((REAL)m_CanvasHeight / 2.0f) * ((REAL)Data.im / (REAL)NormFactor) );
    return (REAL)m_CanvasHeight / 2.0f - y;
  }

  template<typename T>
  REAL CMakeX(T &Data, REAL &NormFactor)
  {
    REAL x = ( ((REAL)m_CanvasWidth / 2.0f) * ((REAL)Data.re / (REAL)NormFactor) );
    return (REAL)m_CanvasWidth / 2.0f + x;
  }

protected:
  // This will be called automatically by WNDPROC
  void _OnDraw(Graphics *pGraphics);

  // Internal Draw
  void _DrawPoint(Graphics* pGraphics, PointF &point);
  void _DrawLine(Graphics* pGraphics, PointF &point1, PointF &point2);

  template<typename T>
  void _Draw(Graphics* pGraphics, T *pData, int N)
  {
    REAL fStep = (REAL)m_CanvasWidth / (REAL)N;
    REAL XTick = (REAL)m_CanvasWidth / (REAL)8.0f;
    REAL YTick = (REAL)m_CanvasHeight / 2.0f / (REAL)8.0f;

    REAL NormFactor = PeakOfArray(pData, N);

    REAL AxisFrom = -NormFactor;
    REAL AxisStep = NormFactor / 8.0f;

    int nXStep = N / 8;

    WCHAR wszBuf[128];
    size_t cbDest = 128 * sizeof(WCHAR);

    REAL x1, y1, x2, y2;

    x1 = 0.0f;
    y1 = MakeY(pData[0], NormFactor);

    for (int i = 1; i < N; i++)
    {
      x2 = i * fStep;
      y2 = MakeY(pData[i], NormFactor);

      pGraphics->DrawLine(&m_Pen, PointF(x1, y1), PointF(x2, y2));

      x1 = x2;
      y1 = y2;
    }

    pGraphics->DrawLine(&m_AxisPen, Point(0, m_CanvasHeight), Point(0, 0));
    pGraphics->DrawLine(&m_AxisPen, Point(0, m_CanvasHeight / 2), Point(m_CanvasWidth, m_CanvasHeight / 2));

    // X-Tick
    for (int i = 1; i < 8; i++)
    {
      int  v = i * nXStep;
      REAL x = i * XTick;

      //输出文字
      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-d", v);

      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(x, m_CanvasHeight / 2.0f), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(x, m_CanvasHeight / 2.0f - 4.0f), PointF(x, m_CanvasHeight / 2.0f + 4.0f));
    }

    // Y-Tick
    for (int i = 0; i < 16; i++)
    {
      REAL v = AxisFrom + i * AxisStep;
      REAL y = m_CanvasHeight - i * YTick;

      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-.0f", v);
      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(0.0f, y), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(0.0f, y), PointF(8.0f, y));
    }
  }

  template<typename T>
  void _DrawWithNegativeAxis(Graphics* pGraphics, T *pData, int N)
  {
    REAL fStep = (REAL)m_CanvasWidth / (REAL)N;
    REAL XTick = (REAL)m_CanvasWidth / (REAL)8.0f;
    REAL YTick = (REAL)m_CanvasHeight / 2.0f / (REAL)8.0f;

    REAL NormFactor = PeakOfArray(pData, N);

    REAL AxisFrom = -NormFactor;
    REAL AxisStep = NormFactor / 8.0f;

    int nXStep = N / 8;

    WCHAR wszBuf[128];
    size_t cbDest = 128 * sizeof(WCHAR);

    REAL x1, y1, x2, y2;

    x1 = 0.0f;
    y1 = MakeY(pData[0], NormFactor);

    for (int i = 1; i < N; i++)
    {
      x2 = i * fStep;
      y2 = MakeY(pData[i], NormFactor);

      pGraphics->DrawLine(&m_Pen, PointF(x1, y1), PointF(x2, y2));

      x1 = x2;
      y1 = y2;
    }


    pGraphics->DrawLine(&m_AxisPen, Point(m_CanvasWidth / 2, m_CanvasHeight), Point(m_CanvasWidth / 2, 0));
    pGraphics->DrawLine(&m_AxisPen, Point(0, m_CanvasHeight / 2), Point(m_CanvasWidth, m_CanvasHeight / 2));

    // X-Tick
    for (int i = 0; i < 8; i++)
    {
      int  v = -N/2 + i * nXStep;
      REAL x = i * XTick;

      if (i == 4)
      {
        continue;
      }

      //输出文字
      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-d", v);

      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(x, m_CanvasHeight / 2.0f), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(x, m_CanvasHeight / 2.0f - 4.0f), PointF(x, m_CanvasHeight / 2.0f + 4.0f));
    }

    // Y-Tick
    for (int i = 0; i < 16; i++)
    {
      REAL v = AxisFrom + i * AxisStep;
      REAL y = m_CanvasHeight - i * YTick;

      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-.0f", v);
      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(m_CanvasWidth / 2.0f, y), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(m_CanvasWidth / 2.0f - 4.0f, y), PointF(m_CanvasWidth / 2.0f + 4.0f, y));
    }
  }

  // Draw IQ together
  template<typename T>
  void _CDrawLine(Graphics* pGraphics, T *pData, int N)
  {
    REAL fStep = (REAL)m_CanvasWidth / (REAL)N;
    REAL XTick = (REAL)m_CanvasWidth / (REAL)8.0f;
    REAL YTick = (REAL)m_CanvasHeight / 2.0f / (REAL)8.0f;

    T fMax = CMax(pData, N);
    REAL NormFactor = max(fMax.re, fMax.im);

    Pen  ImPen(Color::LightPink, m_Pen.GetWidth());

    REAL AxisFrom = -NormFactor;
    REAL AxisStep = NormFactor / 8.0f;

    int nXStep = N / 8;

    WCHAR wszBuf[128];
    size_t cbDest = 128 * sizeof(WCHAR);

    REAL x1, y1, x2, y2;
    REAL imx1, imy1, imx2, imy2;

    x1 = 0.0f;
    y1 = MakeY(pData[0].re, NormFactor);

    imx1 = 0.0f;
    imy1 = MakeY(pData[0].im, NormFactor);

    for (int i = 1; i < N; i++)
    {
      x2 = i * fStep;
      y2 = MakeY(pData[i].re, NormFactor);

      imx2 = i * fStep;
      imy2 = MakeY(pData[i].im, NormFactor);

      pGraphics->DrawLine(&m_Pen, PointF(x1, y1), PointF(x2, y2));
      pGraphics->DrawLine(&ImPen, PointF(imx1, imy1), PointF(imx2, imy2));

      x1 = x2;
      y1 = y2;

      imx1 = imx2;
      imy1 = imy2;
    }

    pGraphics->DrawLine(&m_AxisPen, Point(0, m_CanvasHeight), Point(0, 0));
    pGraphics->DrawLine(&m_AxisPen, Point(0, m_CanvasHeight / 2), Point(m_CanvasWidth, m_CanvasHeight / 2));

    // X-Tick
    for (int i = 1; i < 8; i++)
    {
      int  v = i * nXStep;
      REAL x = i * XTick;

      //输出文字
      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-d", v);

      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(x, m_CanvasHeight / 2.0f), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(x, m_CanvasHeight / 2.0f - 4.0f), PointF(x, m_CanvasHeight / 2.0f + 4.0f));
    }

    // Y-Tick
    for (int i = 0; i < 16; i++)
    {
      REAL v = AxisFrom + i * AxisStep;
      REAL y = m_CanvasHeight - i * YTick;

      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-.0f", v);
      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(0.0f, y), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(0.0f, y), PointF(8.0f, y));
    }
  }

  // Draw IQ Points
  template<typename T>
  void _CDrawScatter(Graphics* pGraphics, T *pData, int N)
  {
    REAL XTick = (REAL)m_CanvasWidth / 2.0f / (REAL)8.0f;
    REAL YTick = (REAL)m_CanvasHeight / 2.0f / (REAL)8.0f;

    T fMax = CMax(pData, N);
    REAL NormFactor = max(fMax.re, fMax.im);

    REAL AxisFrom = -NormFactor;
    REAL AxisStep = NormFactor / 8.0f;

    //输出文字
    WCHAR wszBuf[128];
    size_t cbDest = 128 * sizeof(WCHAR);

    //REAL OldWidth = m_Pen.GetWidth();
    //m_Pen.SetWidth(3.0f);

    for (int i = 0; i < N; i++)
    {
      REAL x, y;
      x = CMakeX(pData[i], NormFactor);
      y = CMakeY(pData[i], NormFactor);

      _DrawPoint(pGraphics, PointF(x, y));
    }

    //m_Pen.SetWidth(OldWidth);

    pGraphics->DrawLine(&m_AxisPen, Point(m_CanvasWidth / 2, m_CanvasHeight), Point(m_CanvasWidth / 2, 0));
    pGraphics->DrawLine(&m_AxisPen, Point(0, m_CanvasHeight / 2), Point(m_CanvasWidth, m_CanvasHeight / 2));

    // X-Tick
    for (int i = 0; i < 16; i++)
    {
      float v = AxisFrom + i * AxisStep;
      REAL x = i * XTick;

      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-.0f", v);
      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(x, m_CanvasHeight / 2.0f), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(x, m_CanvasHeight / 2.0f - 4.0f), PointF(x, m_CanvasHeight / 2.0f + 4.0f));
    }

    // Y-Tick
    for (int i = 0; i < 16; i++)
    {
      REAL v = AxisFrom + i * AxisStep;
      REAL y = m_CanvasHeight - i * YTick;

      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-.0f", v);
      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(m_CanvasWidth / 2.0f, y), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(m_CanvasWidth / 2.0f - 4.0f, y), PointF(m_CanvasWidth / 2.0f + 4.0f, y));
    }
  }

  template<typename T>
  void _CSqrtDraw(Graphics* pGraphics, T *pData, int N)
  {
    REAL fStep = (REAL)m_CanvasWidth / (REAL)N;
    REAL XTick = (REAL)m_CanvasWidth / (REAL)8.0f;
    REAL YTick = (REAL)m_CanvasHeight / (REAL)8.0f;

    REAL NormFactor = CSqrtMax(pData, N);
    REAL AxisStep = NormFactor / 8.0f;
    int  nXStep = N / 8;

    //输出文字
    WCHAR wszBuf[128];
    size_t cbDest = 128 * sizeof(WCHAR);

    REAL e1, e2;
    REAL x1, y1, x2, y2;

    x1 = 0.0f;
    e1 = (REAL)pData[0].re * (REAL)pData[0].re + (REAL)pData[0].im * (REAL)pData[0].im;
    e1 = sqrt(e1);
    y1 = MakeYPositive(e1, NormFactor);

    for (int i = 1; i < N - 1; i++)
    {
      x2 = x1 + fStep;
      e2 = (REAL)pData[i].re * (REAL)pData[i].re + (REAL)pData[i].im * (REAL)pData[i].im;
      e2 = sqrt(e2);
      y2 = MakeYPositive(e2, NormFactor);

      pGraphics->DrawLine(&m_Pen, PointF(x1, y1), PointF(x2, y2));

      x1 = x2;
      y1 = y2;
      e1 = e2;
    }

    pGraphics->DrawLine(&m_AxisPen, Point(0, m_CanvasHeight), Point(0, 0));
    pGraphics->DrawLine(&m_AxisPen, Point(0, 0), Point(m_CanvasWidth, 0));

    // X-Tick
    for (int i = 1; i < 8; i++)
    {
      int  v = i * nXStep;
      REAL x = i * XTick;

      //输出文字
      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-d", v);

      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(x, 0.0f), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(x, 0.0f), PointF(x, 8.0f));
    }

    // Y-Tick
    for (int i = 0; i < 8; i++)
    {
      REAL v = i * AxisStep;
      REAL y = m_CanvasHeight - i * YTick;

      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-.0f", v);
      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(0.0f, y), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(0.0f, y), PointF(8.0f, y));
    }
  }

  template<typename T>
  void _CSqrtShiftDraw(Graphics* pGraphics, T *pData, int N)
  {
    REAL fStep = (REAL)m_CanvasWidth / (REAL)N;
    REAL XTick = (REAL)m_CanvasWidth / (REAL)8.0f;
    REAL YTick = (REAL)m_CanvasHeight / (REAL)8.0f;

    REAL NormFactor = CSqrtMax(pData, N);
    REAL AxisStep = NormFactor / 8.0f;
    int  nXStep = N / 8;

    //输出文字
    WCHAR wszBuf[128];
    size_t cbDest = 128 * sizeof(WCHAR);

    REAL e1, e2;
    REAL x1, y1, x2, y2;

    x1 = 0.0f;
    e1 = (REAL)pData[N / 2].re * (REAL)pData[N / 2].re + (REAL)pData[N / 2].im * (REAL)pData[N / 2].im;
    e1 = sqrt(e1);
    y1 = MakeYPositive(e1, NormFactor);

    for (int i = N / 2 + 1; i < N; i++)
    {
      x2 = x1 + fStep;
      e2 = (REAL)pData[i].re * (REAL)pData[i].re + (REAL)pData[i].im * (REAL)pData[i].im;
      e2 = sqrt(e2);
      y2 = MakeYPositive(e2, NormFactor);

      pGraphics->DrawLine(&m_Pen, PointF(x1, y1), PointF(x2, y2));

      x1 = x2;
      y1 = y2;
      e1 = e2;
    }

    for (int i = 0; i < N / 2; i++)
    {
      x2 = x1 + fStep;
      e2 = (REAL)pData[i].re * (REAL)pData[i].re + (REAL)pData[i].im * (REAL)pData[i].im;
      e2 = sqrt(e2);
      y2 = MakeYPositive(e2, NormFactor);

      pGraphics->DrawLine(&m_Pen, PointF(x1, y1), PointF(x2, y2));

      x1 = x2;
      y1 = y2;
      e1 = e2;
    }

    pGraphics->DrawLine(&m_AxisPen, Point(0, m_CanvasHeight), Point(0, 0));
    pGraphics->DrawLine(&m_AxisPen, Point(0, 0), Point(m_CanvasWidth, 0));

    // X-Tick
    for (int i = 1; i < 8; i++)
    {
      int  v = i * nXStep;
      REAL x = i * XTick;

      //输出文字
      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-d", v);

      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(x, 0.0f), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(x, 0.0f), PointF(x, 8.0f));
    }

    // Y-Tick
    for (int i = 0; i < 8; i++)
    {
      REAL v = i * AxisStep;
      REAL y = m_CanvasHeight - i * YTick;

      memset(wszBuf, 0, cbDest);
      StringCbPrintfW(wszBuf, cbDest, L"%-.0f", v);
      pGraphics->DrawString(wszBuf, 128, &m_Font, PointF(0.0f, y), &m_FontBrush);
      pGraphics->DrawLine(&m_AxisPen, PointF(0.0f, y), PointF(8.0f, y));
    }
  }
  //////////////////////////////////////////////////////////////////////////
public:
  GdiPlusWrapper m_GdiplusWrapper;
protected:
  HANDLE        m_DrawFreeListMutex;
  HANDLE        m_DrawBusyListMutex;
  LIST_ENTRY    m_DrawFreeList;
  LIST_ENTRY    m_DrawBusyList;
  DSP_DRAW_DESC m_DrawDesc[nDrawDesc];

protected:
  Graphics     *m_pDefaultBkGraphics;
  Bitmap        m_DefaultBkBitmap;
  Bitmap       *m_pPrevBitmap;
  Color         m_BkColor;
  Pen           m_BkPen;
  Pen           m_AxisPen;
  Pen           m_Pen;

  FontFamily    m_FontFamily;
  Font          m_Font;
  SolidBrush    m_FontBrush;

  Rect          m_BoundBox;

  float         m_GridStepX;
  float         m_GridStepY;

  int           m_CanvasWidth;
  int           m_CanvasHeight;

  //////////////////////////////////////////////////////////////////////////
protected:
  static   BOOL m_bWindowClassRegistered;
  volatile HWND m_hWnd;
  volatile BOOL m_bWindowClose; // useful when in MSG loop
  volatile BOOL m_bWindowCreated;
  HANDLE        m_hWindowMsgDispatchThread;
  HANDLE        m_WindowMutex;
  int           m_WindowWidth;
  int           m_WindowHeight;
  int           m_WindowX;
  int           m_WindowY;
  char          m_WindowTitle[m_nWindowTitleLength];

public:
  static DWORD WINAPI msg_dispatch_thread(LPVOID lpThreadParam);
  static LRESULT CALLBACK stWndProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
  static dsp_draw_window *GetThisFromWindow(HWND hWnd);

protected:
  void RegisterWindowClass();
  BOOL CreateDrawWindow();
  BOOL Create();
  BOOL ShowWindow();
  void MessageLoop();
  LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};