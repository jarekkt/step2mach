#pragma once
#include "spindgraph.h"
#include "afxwin.h"


// SpindleCal dialog

class SpindleCal : public CDialog
{
	DECLARE_DYNAMIC(SpindleCal)

public:
	SpindleCal(CWnd* pParent = NULL);   // standard constructor
	virtual ~SpindleCal();

// Dialog Data
	enum { IDD = IDD_SPINCAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSpindgraph m_Graph;
	double m_PValue;
	double m_IValue;
	double m_DValue;
	int    AutoWait;
	bool   AutoComplete;
	afx_msg void OnBnClickedUpdate();
	int m_Pulses;
	double m_SetPoint;
    int m_position;
	bool AutoMode;
	bool wasclosed;
	double MaxSpeed;
	double AutoStage;
	double Linearity[101];
	double LinearityOld[101];
	bool   wasAvg;
	bool   CalSucc;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedButton1();
	int m_Pulley;
	afx_msg void OnBnClickedOk();
	double m_TrueRPM;
	CEdit m_True;
	afx_msg void OnBnClickedAutocal();
	double m_Ratio;
	CEdit m_RatioEdit;
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedDefaults();
};
