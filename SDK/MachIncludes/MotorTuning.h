#pragma once
#include "spindgraph.h"
#include "afxcmn.h"
#include "afxwin.h"


// MotorTuning dialog

class MotorTuning : public CDialog
{
	DECLARE_DYNAMIC(MotorTuning)

public:
	MotorTuning(CWnd* pParent = NULL);   // standard constructor
	virtual ~MotorTuning();
	CToolTipCtrl* m_pToolTip;
	unsigned long cpuSpeed;
	int   m_CurrentAxis;

// Dialog Data
	enum { IDD = IDD_MOTORTUNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// Static for display of the Units in effect presently
	CString m_StepsPerUnit;
	CSpindgraph m_MotorGraph;
	double m_Steps;
	double m_Velocity;
	double m_Acceleration;
	double Ymax;
	double ScaleAcc;
	bool   NoReturn;
	CSliderCtrl m_AccelSlide;
	CSliderCtrl m_VelSlide;
	afx_msg void OnBnClickedAxisx();
	afx_msg void OnBnClickedAxisy();
	afx_msg void OnBnClickedAxisz();
	afx_msg void OnBnClickedAxisa();
	afx_msg void OnBnClickedAxisb();
	afx_msg void OnBnClickedAxisc();
	afx_msg void OnBnClickedAxiss();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void    GraphCurve();
	CButton m_cOK;
	CEdit m_StepsBox;
	CEdit m_VelBox;
	CEdit m_AccBox;
	CButton m_XBut;
	CButton m_YBut;
	CButton m_ZBut;
	CButton m_ABut;
	CButton m_BBut;
	CButton m_CBut;
	CButton m_SpinBut;
	CButton m_Save;
	double  XRange;
	int AccSecSec, VelMax;
	afx_msg void OnBnClickedSaveaxis();
	afx_msg void OnNMCustomdrawVelslide(NMHDR *pNMHDR, LRESULT *pResult);
	int m_VelInt;
	int m_AccInt;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeStepsperunit();
	afx_msg void OnEnChangeVelocity();
	afx_msg void OnEnChangeAccel();
	afx_msg void OnEnKillfocusAccel();
	afx_msg void OnEnKillfocusVelocity();
	afx_msg void OnEnSetfocusVelocity();
	afx_msg void OnEnSetfocusAccel();
	afx_msg void OnEnKillfocusStepsperunit();
	afx_msg void OnEnSetfocusStepsperunit();
	int m_StepWidth;
	afx_msg void OnEnChangeStepwidth();
	int m_DIR;
	// G's of acceleration
	double m_Gs;
};
