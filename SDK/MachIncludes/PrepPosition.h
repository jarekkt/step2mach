#if !defined(AFX_PREPPOSITION_H__059F7F75_BF3C_4168_B399_E2B5AC856615__INCLUDED_)
#define AFX_PREPPOSITION_H__059F7F75_BF3C_4168_B399_E2B5AC856615__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrepPosition.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PrepPosition dialog

class PrepPosition : public CDialog
{
// Construction
public:
	PrepPosition(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PrepPosition)
	enum { IDD = IDD_RUNFROM };
	CButton	m_OK;
	double	m_BPos;
	double	m_APos;
	double	m_CPos;
	double	m_XPos;
	double	m_YPos;
	double	m_ZPos;
	double	m_SafeZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PrepPosition)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PrepPosition)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_StartSpindle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREPPOSITION_H__059F7F75_BF3C_4168_B399_E2B5AC856615__INCLUDED_)
