#if !defined(AFX_SLAVE_H__35771702_1C18_4BB4_ADA7_BEEBEFCEFEC3__INCLUDED_)
#define AFX_SLAVE_H__35771702_1C18_4BB4_ADA7_BEEBEFCEFEC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Slave.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Slave dialog

class Slave : public CDialog
{
// Construction
public:
	Slave(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Slave)
	enum { IDD = IDD_SLAVE };
	int		m_Primary;
	int		m_Slave;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Slave)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Slave)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLAVE_H__35771702_1C18_4BB4_ADA7_BEEBEFCEFEC3__INCLUDED_)
