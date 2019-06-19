#pragma once


// MPGCalibrate dialog

class MPGCalibrate : public CDialog
{
	DECLARE_DYNAMIC(MPGCalibrate)

public:
	MPGCalibrate(CWnd* pParent = NULL);   // standard constructor
	virtual ~MPGCalibrate();

// Dialog Data
	enum { IDD = IDD_CALMPG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCaldetent();
	afx_msg void OnBnClickedCalmax();
	afx_msg void OnBnClickedCalswitch();
	afx_msg void OnBnClickedCalculate();
	int m_StepPerDetent;
	double m_MaxSpeed;
	double m_PercentageSwitch;
	int m_nMPG;
	int axis;
	double DetStart;
	int Stage;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedMpg();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedSave();
	CString m_Message;
};
