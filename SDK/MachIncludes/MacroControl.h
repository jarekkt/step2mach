#include "afxcmn.h"
#if !defined(AFX_MACROCONTROL_H__FEC7D9F7_26A0_4782_A5D2_D898879BF2CA__INCLUDED_)
#define AFX_MACROCONTROL_H__FEC7D9F7_26A0_4782_A5D2_D898879BF2CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MacroControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MacroControl dialog

#include "TWScriptEdit.h"

class MacroControl : public CDialog
{
// Construction
public:
	MacroControl(CWnd* pParent = NULL);   // standard constructor
 
// Dialog Data
	//{{AFX_DATA(MacroControl)
	enum { IDD = IDD_SCRIPTCONTROL };
	CListBox	m_MacroList;
	CButton	m_Load;
	CString	m_MacroName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MacroControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MacroControl)
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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACROCONTROL_H__FEC7D9F7_26A0_4782_A5D2_D898879BF2CA__INCLUDED_)
