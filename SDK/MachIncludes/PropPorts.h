#include "afxwin.h"
#if !defined(AFX_PROPPORTS_H__6A3B27A6_E6C2_4CE5_821C_98FAC0C557FD__INCLUDED_)
#define AFX_PROPPORTS_H__6A3B27A6_E6C2_4CE5_821C_98FAC0C557FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropPorts.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PropPorts dialog

class PropPorts : public CPropertyPage
{
// Construction
	DECLARE_DYNCREATE(PropPorts)

// Construction
public:
	PropPorts();
	~PropPorts();
public:
	int ConvertHex( CString hex );
 

// Dialog Data
	//{{AFX_DATA(PropPorts)
	enum { IDD = IDD_PROPPORTSETUP };
	BOOL	m_AOn;
	BOOL	m_BOn;
	BOOL	m_COn;
	BOOL	m_XOn;
	BOOL	m_YOn;
	BOOL	m_ZOn;
	BOOL	m_SpindleOn;
	BOOL	m_Port2On;
	BOOL	m_Port1On;
	BOOL	m_PWM;
	CString	m_Port2Hex;
	CString	m_Port1Hex;
	int		m_PulseMode;
	//}}AFX_DATA
    int     m_Port1,m_Port2;

	virtual BOOL OnSetActive();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PropPorts)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PropPorts)
	virtual BOOL OnInitDialog();
	afx_msg void OnAon();
	afx_msg void OnBon();
	afx_msg void OnCon();
	afx_msg void OnPort1enabled();
	afx_msg void OnPort2enabled();
	afx_msg void OnSpinaxison();
	afx_msg void OnXon();
	afx_msg void OnYon();
	afx_msg void OnZon();
	afx_msg void On35000();
	afx_msg void On45000();
	afx_msg void On25000();
	afx_msg void OnPwm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_Gecko;
	int m_Inputs;
	int m_Outputs;
	BOOL m_MaxCL;
	afx_msg void OnBnClickedMaxcl();
	BOOL m_Max10;
	afx_msg void OnBnClickedMaxnc10();
	BOOL m_ModBus;
	BOOL m_Port2Input;
	afx_msg void OnBnClickedPort2input();
	BOOL m_Sherline;
	afx_msg void OnBnClickedSherline();
	afx_msg void OnBnClickedModbus();
	BOOL m_Serial;
	afx_msg void OnBnClickedServoserial();
	afx_msg void OnBnClickedSerial();
	CButton m_ServoLink;
	BOOL m_ServoSerial;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPORTS_H__6A3B27A6_E6C2_4CE5_821C_98FAC0C557FD__INCLUDED_)
