#if !defined(AFX_MDI_H__4EACFD10_0589_4C09_AC63_24EBD5D7F68A__INCLUDED_)
#define AFX_MDI_H__4EACFD10_0589_4C09_AC63_24EBD5D7F68A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MDI.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MDI window

#include "mdiedit.h"
#include "ControlRect.h"

class MDI : public CStatic
{
// Construction
public:
    DECLARE_DYNCREATE(MDI)
	MDI();
    
// Attributes
public:

// Operations
public:
   bool DeleteMe;
   CString label;
   MDIEdit   inbox;
   
   bool    m_Selected;
   COLORREF  selected, unselected;
   CString Block;
   CBrush        m_Brush,s_Brush;

   COLORREF    m_BackColor;

   CControlRect *Control;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MDI)
	public:
    protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnColor();
	void CompleteInput();
	void CompleteData();
	void ProcessInput( int key);
	void DeSelect();
	void Select();
	virtual ~MDI();

	// Generated message map functions
protected:
	//{{AFX_MSG(MDI)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point); 
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDI_H__4EACFD10_0589_4C09_AC63_24EBD5D7F68A__INCLUDED_)
