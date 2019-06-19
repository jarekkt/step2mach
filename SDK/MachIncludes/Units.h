#if !defined(AFX_UNITS_H__5FC39755_B4EE_4321_BF85_32A1020FD70D__INCLUDED_)
#define AFX_UNITS_H__5FC39755_B4EE_4321_BF85_32A1020FD70D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Units.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Units dialog

class Units : public CDialog
{
// Construction
public:
	Units(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Units)
	enum { IDD = IDD_UNITS };
	CButton	m_MMs;
	CButton	m_Inches;
	//}}AFX_DATA
    int m_Units;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Units)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Units)
	afx_msg void OnInches();
	afx_msg void OnMms();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNITS_H__5FC39755_B4EE_4321_BF85_32A1020FD70D__INCLUDED_)
