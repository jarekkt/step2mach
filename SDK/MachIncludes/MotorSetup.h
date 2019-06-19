#include "afxwin.h"
#if !defined(AFX_MOTORSETUP_H__A4773350_B6E9_4ADE_88E9_C6980C2957C5__INCLUDED_)
#define AFX_MOTORSETUP_H__A4773350_B6E9_4ADE_88E9_C6980C2957C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MotorSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MotorSetup dialog


class MotorSetup : public CDialog
{
// Construction
public:
	void Graph();
	void CalcScalers();
 
	void Convert();
	MotorSetup(CWnd* pParent = NULL);   // standard constructor
    
	double ScaleVel;  // scale var for calucating Vel from Slider 0-1000
	double ScaleAcc; // scale var for calucating Acc from Slider 0-1000
	unsigned long  cpuSpeed;
	unsigned long  PWidth,DWidth;

// Dialog Data
	//{{AFX_DATA(MotorSetup)
	enum { IDD = IDD_MOTORSETUP };
	CEdit	m_PulseWidthBox;
	CEdit	m_DirWidthBox;
	MyStatic	m_Graph;
	CSliderCtrl	m_AccSlider;
	CSliderCtrl	m_VelSlider;
	CEdit	m_VelBox;
	CEdit	m_StepBox;
	CEdit	m_AccBox;
	CButton	m_Save;
	double	m_StepsPerUnit;
	double	m_Velocity;
	double	m_Acceleration;
	CString	m_UnitText;
	CString	m_Current;
	int		m_AccInt;
	int		m_VelInt;
	int		m_DirWidth;
	int		m_PulseWidth;
	//}}AFX_DATA
   
	int m_Units;
    int CurrentAxis;
	int AccSecSec,VelMax; // integer acceleration and velocity values

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MotorSetup)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MotorSetup)
	afx_msg void OnAaxis();
	afx_msg void OnChangeAccedit();
	afx_msg void OnBaxis();
	afx_msg void OnCaxis();
	afx_msg void OnChangeVelocityedit();
	afx_msg void OnXaxis();
	afx_msg void OnYaxis();
	afx_msg void OnZaxis();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSave();
	afx_msg void OnChangeStepsperunit();
	afx_msg void OnSetfocusAccedit();
	afx_msg void OnSetfocusStepsperunit();
	afx_msg void OnSetfocusVelocityedit();
	afx_msg void OnReleasedcaptureAcceleration(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureVelocity(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawAcceleration(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawVelocity(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangePulsewidth();
	afx_msg void OnChangeDirwidth();
	afx_msg void OnSetfocusPulsewidth();
	afx_msg void OnSetfocusDirwidth();
	afx_msg void OnKillfocusStepsperunit();
	virtual void OnCancel();
	afx_msg void OnKillfocusDirwidth();
	afx_msg void OnKillfocusPulsewidth();
	afx_msg void OnKillfocusVelocityedit();
	afx_msg void OnKillfocusAccedit();
	afx_msg void OnSpindle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRutex();
	CButton m_SpinBut;
	CButton m_XBut;
	CButton m_YBut;
	CButton m_ZBut;
	CButton m_ABut;
	CButton m_BBut;
	CButton m_CBut;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTORSETUP_H__A4773350_B6E9_4ADE_88E9_C6980C2957C5__INCLUDED_)
