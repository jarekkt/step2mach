// _Mach1Button.h - replaces class with struct

#pragma once

#define HDIB HANDLE
//#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi))==sizeof(BITMAPINFOHEADER))
#define WIDTHBYTESB(bits)    (((bits) + 31) / 32 * 4)
#define BFT_ICON   0x4349   // 'IC'
#define BFT_BITMAP 0x4d42   // 'BM'
#define BFT_CURSOR 0x5450   // 'PT'

struct _CxDib
{
	HDIB	hDib;
    BITMAPINFOHEADER	m_bi;
	DWORD	m_LineWidth;
	WORD	m_nColors;
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

struct _Mach1Button
{
	BYTE	_fillCObject[0x04];			// fill to replace private CObject data
	int		m_dwRef;					// CWnd public data
	BYTE	_fillCWnd1[0x14];			// fill to replace private CWnd data
	HWND	m_hWnd;						// only published CWnd data
	BYTE	_fillCWnd2[0x14];			// fill to replace private CWnd data
	HWND	m_hWndOwner;				// CWnd public data
	int		m_nFlags;					// Cwnd public data
	BYTE	_fillCWnd3[0x14];			// fill to replace private CWnd data
	BYTE	_fillCBitmapButton[0x20];	// fill to replace private CBitmapButton data

    LPCSTR				GCode;

	int		Function;
	int		OEMCode;

	LPCSTR				Text;

	bool	TextOn;
	int		state;
	bool	m_bDrawBackground;

	LPCSTR				Temp;

	int     time;
    
	_CFont				m_Font;		//font object
	LOGFONT*			m_pLF;		//font structure
	LPCSTR				m_ToolTipUp,m_ToolTipDw;

	bool	m_Checked;		//radio & check buttons
	bool	m_IsPushLike;	//radio & check buttons
	DWORD	m_Style;

	_CxDib				m_dNormal, m_dDown, m_dDisabled, m_dOver, m_dh, m_dv;

    bool	m_tracking;
    bool	m_button_down;

	_CToolTipCtrl		m_tooltip;

	short	m_FocusRectMargin;	//dotted margin offset

	COLORREF			m_TextColor;		//button text color

	BOOL	m_Border;			//0=flat; 1=3D;
	HICON	m_Icon, m_IconDown, m_IconHighLight;

	_CRect				m_IconBox;

	UINT	m_TextAlign;
	UINT	m_IconAlign;
	bool	m_flat;
	short   Macro;
	bool    IsEmerg;

	LPCSTR				*pGCode;
	LPCSTR				*EmergCode;

	bool	m_bRaised;

	_CFont				buttonfont;
};
