#if !defined(AFX_EMERGBUTTON_H__F491156B_5F4A_49F6_9FD3_19DC100DDA34__INCLUDED_)
#define AFX_EMERGBUTTON_H__F491156B_5F4A_49F6_9FD3_19DC100DDA34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmergButton.h : header file
//
#include "Mach3Image.h"

/////////////////////////////////////////////////////////////////////////////
// EmergButton view
 
class EmergButton : public CWnd
{
public:
	EmergButton();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(EmergButton)
 
// Attributes
public:
   bool DeleteMe;
   Mach3Image picture;
   Mach3Image picture2;
   CString *OriginalGCode;
   bool back;
   bool    Loaded;
   CString Text;
   bool Locked;
   bool KeysSet;
   int  KeyReset;
   int  KeyEmerg;
   int  time;
   bool dualimage;
   HBITMAP hbmScreen;
   bool    blankloaded;
   CBitmap  OutButton;
   
   bool  LastState;
   //CBitmap m_Reset,m_EStop,m_Reset1,m_Reset2,m_Reset3,m_Reset4;
   int lox,hix,loy,hiy;
   int cycledir;
   int cycle;
   int m_Watch;
// Operations
public:
	 
	void SetBitmap( CString path);
	void OnButton();
	CRect clientrect,shrunk;
 
	void Update();
	CDC memDC;
 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EmergButton)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	 
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	void doOEMCode();
	int      Function;
	CString  GCode;
	int      OEMCode;
	CControlRect rect;
	Mach1Button  button;
 
	virtual ~EmergButton();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(EmergButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnInitMenu(CMenu* pMenu);
	void CloseWindow(void);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnIconEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	void ToggleButton(void);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMERGBUTTON_H__F491156B_5F4A_49F6_9FD3_19DC100DDA34__INCLUDED_)
