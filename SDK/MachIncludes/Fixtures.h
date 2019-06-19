#if !defined(AFX_CFixtures_H__52FC4A05_7BC5_45D3_8445_1E33B500B750__INCLUDED_)
#define AFX_CFixtures_H__52FC4A05_7BC5_45D3_8445_1E33B500B750__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CFixtures.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFixtures dialog

class CFixtures : public CDialog
{
// Construction
public:
	void SaveSettings();
	CFixtures(CWnd* pParent = NULL);   // standard constructor


    
// Dialog Data
	//{{AFX_DATA(CFixtures)
	enum { IDD = IDD_FIXTURES };
	CGridCtrl	m_FixtureGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFixtures)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFixtures)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfixture();
	afx_msg void OnActivate();
	afx_msg void OnDeactivate();
	afx_msg void OnSave();
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFixtures_H__52FC4A05_7BC5_45D3_8445_1E33B500B750__INCLUDED_)
