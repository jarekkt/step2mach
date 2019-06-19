#pragma once
#include "afxwin.h"


// SpindleSetup dialog

class SpindleSetup : public CPropertyPage
{
	DECLARE_DYNAMIC(SpindleSetup)

public:
	SpindleSetup();
	virtual ~SpindleSetup();

// Dialog Data
	enum { IDD = IDD_SPINDLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_PulleyNumber;
	int m_Speed0;
	int m_Speed1;
	int m_Speed2;
	int m_Speed3;
	int m_PWMin;
	BOOL m_PwmLaser;
	BOOL m_SpinActual;
	double m_SpinSeconds;
	double m_PWMBase;
	BOOL m_SpindleMotor;
	BOOL m_NoSpindle;
	BOOL m_NoFloodMist;
	int m_SpinCW;
	int m_SpinCCW;
	int m_Flood;
	int m_Mist;
	virtual void OnOK();
	void SetData();
	afx_msg void OnBnClickedUsespindlemotor();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	 
	BOOL m_PWM;
	BOOL m_StepDir;
	afx_msg void OnBnClickedPwmonoff();
	afx_msg void OnBnClickedStepdironoff();
	CEdit SRedit1;
	CEdit SRedit2;
	afx_msg void OnBnClickedSpindlerelayonoff();
	CEdit FloodEdit1;
	CEdit FloodEdit2;
	afx_msg void OnBnClickedFloodmistonoff();
	CButton pwm1;
	CButton pwm2;
	CEdit pwm3;
	afx_msg void OnEnChangeSignalcw();
	double m_SpinSeconds2;
	int Pulley1Low;
	int Pulley2Low;
	int Pulley3Low;
	int Pulley4Low;
	double m_CWDownDelay;
	double m_CCWDownDelay;
	BOOL ClosedLoop;
	double m_P;
	double m_I;
	double m_D;
	BOOL m_SpinAvg;
	BOOL m_Immediate;
	BOOL m_ModSpinOn;
	short m_ModSpinReg;
	short m_ModSpinCount;
	BOOL m_Torch;
	afx_msg void OnBnClickedSpinmodon();
};
