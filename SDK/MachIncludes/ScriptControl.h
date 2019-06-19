#pragma once


/// ScriptControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ScriptControl dialog

#include "TWScriptEdit.h"
#include "afxcmn.h"
#include "afxwin.h"

class ScriptControl : public CDialog
{
// Construction
public:
	ScriptControl(CWnd* pParent = NULL);   // standard constructor
 
// Dialog Data
	//{{AFX_DATA(ScriptControl)
	enum { IDD = IDD_SCRIPTCONTROL };
	CListBox	m_MacroList;
	CButton	m_Load;
	CString	m_MacroName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ScriptControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ScriptControl)
	afx_msg void OnSetfocusMacrolist();
	afx_msg void OnKillfocusMacrolist();
	afx_msg void OnKillfocusMacro();
	afx_msg void OnSetfocusMacro();
	afx_msg void OnLoad();
	afx_msg void OnAvailable();
	afx_msg void OnSavemacro();
	afx_msg void OnTest();
	virtual BOOL OnInitDialog();
	afx_msg void OnGuide();
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CTWScriptEdit m_wndScriptEdit;
	//CRichEditCtrl m_wndScriptEdit;
	 
	 
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};
