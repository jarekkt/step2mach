#if !defined(AFX_MYABOUT_H__38720DD3_F736_4B3B_B247_461E4B0B567A__INCLUDED_)
#define AFX_MYABOUT_H__38720DD3_F736_4B3B_B247_461E4B0B567A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyAbout.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyAbout dialog

#include "JMatrixCtrl.h"
#include "afxwin.h"

class MyAbout : public CDialog
{
// Construction
public:
	MyAbout(CWnd* pParent = NULL);   // standard constructor
    CString m_AppVer;
	
// Dialog Data
	//{{AFX_DATA(MyAbout)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_Name;
	//}}AFX_DATA
    

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyAbout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MyAbout)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	 
	JMatrixCtrl  Matrix;
	CString m_Version;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYABOUT_H__38720DD3_F736_4B3B_B247_461E4B0B567A__INCLUDED_)
