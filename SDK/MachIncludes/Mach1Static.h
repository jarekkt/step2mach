#if !defined(AFX_MACH1STATIC_H__CC64DF5A_C5F6_428B_8621_38DDC5E795AF__INCLUDED_)
#define AFX_MACH1STATIC_H__CC64DF5A_C5F6_428B_8621_38DDC5E795AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mach1Static.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Mach1Static window
#include "Mach3Image.h"
 
 

class Mach1Static : public CStatic
{
// Construction
public:
	Mach1Static();
    void DrawBitmap(CDC* pDC, CBitmap& bitmap, CPalette *pPal );
	void DrawTransparentBitmap(CDC *pDC, CBitmap *Bitmap, short xStart, 
		                       short yStart, int nWidth, int nHeight, COLORREF cTransparentColor);
    BOOL  LoadBMPImage( LPCTSTR sBMPFile, CBitmap& bitmap, CPalette *pPal );
	void  SetPath( CString path);
    Mach3Image image;
	bool Loaded;
	bool other;
	CDC memDC;
// Attributes
public:
   
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Mach1Static)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~Mach1Static();

	// Generated message map functions
protected:
	//{{AFX_MSG(Mach1Static)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACH1STATIC_H__CC64DF5A_C5F6_428B_8621_38DDC5E795AF__INCLUDED_)
