#if !defined(AFX_LABELS_H__C6C7C59B_B725_4899_8691_3B4559545915__INCLUDED_)
#define AFX_LABELS_H__C6C7C59B_B725_4899_8691_3B4559545915__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Labels.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Labels window

class Labels : public CEdit
{
// Construction
public:
	Labels();
    DECLARE_DYNCREATE(Labels)
// Attributes
public:

// Operations
public:
 
   bool DeleteMe;
   bool ErrorRed;
   CString label;
   int     TickerStep;
   int     TickerNum;
   int     UserNum;
   bool    IsTicker;
   CFont   labelfont;
   bool Errorline;
   bool ModeLine;
   bool FileLine;
   bool IsUserLabel;
   bool Diametric;
   bool Measurement;
   bool RevMin;
   bool ToolDisc;
   bool Fixture;
   bool FrontRear;
   int hRevMin ;
   int Units ;
   int oldindex;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Labels)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	void Update();
	void SetLabel(CString Label);
	void CloseLabel();
	virtual ~Labels();

	// Generated message map functions
protected:
	//{{AFX_MSG(Labels)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABELS_H__C6C7C59B_B725_4899_8691_3B4559545915__INCLUDED_)
