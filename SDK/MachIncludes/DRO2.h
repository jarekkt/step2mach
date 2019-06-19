#if !defined(AFX_DRO2_H__BF857634_416B_4601_A825_91A7C9CCAC87__INCLUDED_)
#define AFX_DRO2_H__BF857634_416B_4601_A825_91A7C9CCAC87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DRO2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DRO2 window

#include "Mach3Image.h"
#include "ControlRect.h"
#include "DROCalc.h"
 


class DRO2 : public CEdit
{
// Construction
public:
	DRO2();

// Attributes
public:
	bool    Dirty;
	CFont   labelfont;
	int     Function;
	CString format;
	double  Value;
	CString Data;
	CTimeSpan oldtime;
	COLORREF selected, unselected;
	bool  m_Selected;
	int   nPos;
	bool  dec;
	bool neg;
	int  OEMCode;

	bool Slider;
	double m_low,m_high;
	bool   m_Top;
	CRect ssize,tsize;
	bool  Tracking;
	bool  m_DRO;

	CControlRect *Control;

	void SetPath( CString path);
	void  FixCode();
	Mach3Image image;
	bool Loaded;
	 
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DRO2)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SendOEM();
	void CompleteData();
	char TranlateKey( int key );
	void ProcessInput( int key);
	void DeSelect();
	void Select();
	void SetFunction( int Function );
	void Update();
	virtual ~DRO2();

	// Generated message map functions
protected:
	//{{AFX_MSG(DRO2)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	void OnHotKey(void);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRO2_H__BF857634_416B_4601_A825_91A7C9CCAC87__INCLUDED_)
