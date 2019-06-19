#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "G200x.h"


// GREXMotor dialog


extern WTConfig     pGeckoConfig;

class GREXMotor : public CDialog
{
	DECLARE_DYNAMIC(GREXMotor)

public:
	GREXMotor(CWnd* pParent = NULL);   // standard constructor
	virtual ~GREXMotor();

// Dialog Data
	enum { IDD = IDD_GECKOAXIS };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_DutyCycle;
	CComboBox m_MaxFreq;
	CComboBox m_TriggerEvent;
	int m_ExternInc;
	int m_InternIncr;
	afx_msg void OnBnClickedReadsetup();
	afx_msg void OnBnClickedReadrex();
	CSliderCtrl m_VelCtrl;
	CSliderCtrl m_AccCtrl;
	double m_Velocity;
	double m_Accel;
	double m_Steps;
	int CurrentAxis;
	bool dirty;
    double    tGRexSteps[6];
	double    tGRexAccel[6];
	double    tGRexVel[6];
	int       tGRexCV;
	double    maxvel;
	double    maxacc;
	int       max; //temp variable for maximum pulse freq.

	void FillData();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedStore();
	afx_msg void OnBnClickedAxis0();
	afx_msg void OnBnClickedAxis1();
	afx_msg void OnBnClickedAxis2();
	afx_msg void OnBnClickedAxis3();
	afx_msg void OnBnClickedAxis4();
	afx_msg void OnBnClickedAxis5();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCbnSelchangeCountertrigger();
	CString m_Current;
	afx_msg void OnEnKillfocusAccel();
	afx_msg void OnEnKillfocusVelocity();
	afx_msg void OnBnClickedButton1();
	void CalcVelAcc(void);
	afx_msg void OnCbnSelchangeDivider();
	afx_msg void OnEnChangeStepsperunit();
	afx_msg void OnEnKillfocusUnitsmin();
	afx_msg void OnEnKillfocusStepsperunit();
	afx_msg void OnBnSetfocusOk();
	afx_msg void OnBnClickedButton2();
	CButton m_Dummy;
	afx_msg void OnBnClickedEnd();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CString m_UnitsPer;
	CString m_AccPer;
	double m_AccTime;
	CSliderCtrl m_CV;
	int m_CVTime;
};
