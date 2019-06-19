#if !defined(AFX_MACH1BUTTON_H__1169BB34_9886_476B_94E6_B7A2E817A3BB__INCLUDED_)
#define AFX_MACH1BUTTON_H__1169BB34_9886_476B_94E6_B7A2E817A3BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mach1Button.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Mach1Button window


#define HDIB HANDLE
//#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi))==sizeof(BITMAPINFOHEADER))
#define WIDTHBYTESB(bits)    (((bits) + 31) / 32 * 4)
#define BFT_ICON   0x4349   // 'IC'
#define BFT_BITMAP 0x4d42   // 'BM'
#define BFT_CURSOR 0x5450   // 'PT'

class CxDib
{
public:
	CxDib();
	~CxDib();
	HDIB Create(DWORD dwWidth, DWORD dwHeight, WORD wBitCount);
	void Clear(BYTE bval=0);
	void Clone(CxDib *src);
	BOOL IsValid();
	long GetSize();
	BYTE* GetBits();
	DWORD GetHeight() {return m_bi.biHeight;};
	DWORD GetWidth() {return m_bi.biWidth;};
	DWORD GetLineWidth() {return m_LineWidth;};
	WORD GetNumColors() {return m_nColors;};
	WORD GetBitCount() {return m_bi.biBitCount;};
	WORD GetPaletteSize();
	BYTE GetPixelIndex(long x,long y);
	RGBQUAD GetPaletteIndex(BYTE idx);
	RGBQUAD GetPixelColor(long x,long y);
	BYTE GetNearestIndex(RGBQUAD c);
	long Draw(HDC pDC, long xoffset, long yoffset);
	long Stretch(HDC pDC, long xoffset, long yoffset, long xsize, long ysize);
	void BlendPalette(COLORREF cr,long perc);
	void SetPaletteIndex(BYTE idx, BYTE r, BYTE g, BYTE b);
	void SetPaletteIndex(BYTE idx, RGBQUAD c);
	void SetPaletteIndex(BYTE idx, COLORREF cr);
	void SetPixelColor(long x,long y,RGBQUAD c);
	void SetPixelIndex(long x,long y,BYTE i);
	void SetPixelColor(long x,long y,COLORREF cr);
	void SetGrayPalette();
	long WriteBMP(LPSTR bmpFileName);
	RGBQUAD HSLtoRGB(COLORREF cHSLColor);
	RGBQUAD RGB2RGBQUAD(COLORREF cr);
	COLORREF RGBQUAD2RGB (RGBQUAD c);
	RGBQUAD RGBtoHSL(RGBQUAD lRGBColor);
	RGBQUAD HSLtoRGB(RGBQUAD lHSLColor);
protected:
	HDIB hDib;
    BITMAPINFOHEADER    m_bi;
	DWORD m_LineWidth;
	WORD  m_nColors;
	bool IsWin30Dib();
	WORD HueToRGB(WORD n1,WORD n2,WORD hue);
};
#define SHS_NOISE 0
#define SHS_DIAGSHADE 1
#define SHS_HSHADE 2
#define SHS_VSHADE 3
#define SHS_HBUMP 4
#define SHS_VBUMP 5
#define SHS_SOFTBUMP 6
#define SHS_HARDBUMP 7
#define SHS_METAL 8
#define WM_CXSHADE_RADIO WM_USER+0x100

class Mach1Button : public CBitmapButton
{
// Construction
public:
	DECLARE_DYNCREATE(Mach1Button);
	Mach1Button();
	LOGFONT* GetFont();
	void ToggleButton(void);
	void FixCode();
	bool SetFont(LOGFONT* pNewStyle);
	bool SetFont(CString sFontName, long lSize=0, long lWeight=400, BYTE bItalic=0, BYTE bUnderline=0);
	void SetButtonStyle( UINT nStyle, BOOL bRedraw = TRUE );
	void SetFlat(bool bFlag);
	void SetTextAlign(UINT nTextAlign);
	void SetIcon(UINT nIcon, UINT nIconAlign=BS_CENTER, UINT nIconDown=0, UINT nIconHighLight=0);
	void SetShade(UINT shadeID=0,BYTE granularity=8,BYTE highlight=10,BYTE coloring=0,COLORREF color=0);
	void SetToolTipText(CString s, CString sDown="");
	COLORREF SetTextColor(COLORREF new_color);
    void CalcFont();
    CString GCode;
	int  Function;
	int OEMCode;
	CString Text;
	bool TextOn;
	int state;
	bool m_bDrawBackground;
	CString Temp;
	int     time;
    
	CFont	m_Font;		//font object
	LOGFONT* m_pLF;		//font structure
	CString m_ToolTipUp,m_ToolTipDw;
	bool	m_Checked;		//radio & check buttons
	bool	m_IsPushLike;	//radio & check buttons
	DWORD	m_Style;
	CxDib	m_dNormal,m_dDown,m_dDisabled,m_dOver,m_dh,m_dv;
    bool	m_tracking;
    bool	m_button_down;
	void	RelayEvent(UINT message, WPARAM wParam, LPARAM lParam);
	CToolTipCtrl m_tooltip;
	short	m_FocusRectMargin;	//dotted margin offset
	COLORREF m_TextColor;		//button text color
	BOOL	m_Border;			//0=flat; 1=3D;
	HICON	m_Icon,m_IconDown,m_IconHighLight;
	CRect	m_IconBox;
	UINT	m_TextAlign;
	UINT	m_IconAlign;
	bool	m_flat;
	short   Macro;
	bool    IsEmerg;
	CString *pGCode;
	CString *EmergCode;
	
 
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxShadeButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
// Implementation
	//{{AFX_MSG(CxShadeButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnClicked();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
	afx_msg LRESULT OnRadioInfo(WPARAM, LPARAM);
	afx_msg LRESULT OnBMSetCheck(WPARAM, LPARAM);
	afx_msg LRESULT OnBMGetCheck(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
	//afx_msg BOOL OnClicked();

// Implementation
public:
	void OnButton();
	void SpinOff();
	void Draw(CDC* pDC, const CRect& rect, UINT state);
	void SpinCW();
	void SpinCCW();
	void doOEMCode();
	void SetUp();
	void ShutDown();
	virtual ~Mach1Button();

public:
	void FloodOff(void);
	void FloodOn(void);
	void MistOn(void);
	void MistOff(void);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void DrawBorders( CDC* pDC, CRect& rect,UINT state); 
	void DrawText(CDC* pDC, const CRect& rect, LPCTSTR text, UINT state);

	bool m_bRaised;
	CFont buttonfont;
 
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	void Update(void);
};





/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACH1BUTTON_H__1169BB34_9886_476B_94E6_B7A2E817A3BB__INCLUDED_)
