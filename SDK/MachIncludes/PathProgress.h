#if !defined(AFX_PATHPROGRESS_H__B5D1AB3A_F59B_474B_994C_DAB5B3022CAF__INCLUDED_)
#define AFX_PATHPROGRESS_H__B5D1AB3A_F59B_474B_994C_DAB5B3022CAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PathProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PathProgress dialog

#include "resource.h"

class PathProgress : public CDialog
{
// Construction
public:
	PathProgress(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PathProgress)
	enum { IDD = IDD_PATHPROGRESS };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PathProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PathProgress)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATHPROGRESS_H__B5D1AB3A_F59B_474B_994C_DAB5B3022CAF__INCLUDED_)
