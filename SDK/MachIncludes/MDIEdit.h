#if !defined(AFX_MDIEDIT_H__7A93026B_7183_4EB6_8FA7_7B672E386495__INCLUDED_)
#define AFX_MDIEDIT_H__7A93026B_7183_4EB6_8FA7_7B672E386495__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MDIEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MDIEdit window

#include "TitleTip.h"
#include "ControlRect.h"

class MDIEdit : public CEdit
{
// Construction
public:
	MDIEdit();

// Attributes
public:
   CString label;
   bool    m_Selected;
   CFont   labelfont;
   CTitleTip  hist;
   bool   KilledJog;
   CControlRect *Control;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MDIEdit)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ProcessInput( int key);
	void CompleteInput();
	void DeSelect();
	void Select();
	virtual ~MDIEdit();
    
	CString History[50];
	int     nHistory;
	int     nChoice;
	// Generated message map functions
public:
	void Init();
	//{{AFX_MSG(MDIEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point); 
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	void ShowHistory(void);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIEDIT_H__7A93026B_7183_4EB6_8FA7_7B672E386495__INCLUDED_)
