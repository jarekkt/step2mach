#if !defined(AFX_BACKLASH_H__1362FFF1_E966_46EE_B554_58F5225134BE__INCLUDED_)
#define AFX_BACKLASH_H__1362FFF1_E966_46EE_B554_58F5225134BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Backlash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Backlash dialog

class Backlash : public CDialog
{
// Construction
public:
	Backlash(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Backlash)
	enum { IDD = IDD_BACKLASH };
	double	m_BackB;
	double	m_BackA;
	double	m_BackC;
	double	m_BackSpeed;
	double	m_BackX;
	double	m_BackY;
	double	m_BackZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Backlash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Backlash)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_BackOn;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBacklash();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKLASH_H__1362FFF1_E966_46EE_B554_58F5225134BE__INCLUDED_)
