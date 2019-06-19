#if !defined(AFX_GODELIST_H__6ED24101_3732_4F08_A84E_2A97BB88366D__INCLUDED_)
#define AFX_GODELIST_H__6ED24101_3732_4F08_A84E_2A97BB88366D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GodeList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGodeList window

class CGodeList : public CListBox
{
// Construction
public:
	CGodeList();
	 DECLARE_DYNCREATE(CGodeList)

   bool DeleteMe;
   CFont   labelfont;
   CString GCodeLines[80];
   CString FileName;
   int     m_CurrentLine;
   bool    FileLoaded;
   double  scale;
   int     nLines;
   bool    m_Selected;
   bool    inmouse;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGodeList)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	void DisplayLines( int line );
	void Select();
	void DeSelect();
	void Update();
	void ProcessInput( int key);
	virtual ~CGodeList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGodeList)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GODELIST_H__6ED24101_3732_4F08_A84E_2A97BB88366D__INCLUDED_)
