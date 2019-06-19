#pragma once
#include "afxcmn.h"


// AxisMotor dialog

class AxisMotor : public CDialog
{
	DECLARE_DYNAMIC(AxisMotor)

public:
	AxisMotor(CWnd* pParent = NULL);   // standard constructor
	virtual ~AxisMotor();
	void SetData();
	static BOOL CALLBACK GridCallBack(GV_DISPINFO *pDispInfo, LPARAM /*lParam*/);

// Dialog Data
	enum { IDD = IDD_MOTORCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CGridCtrl m_AxisMotor;
	CImageList m_ImageList;
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnOK();
public:
	BOOL m_PWM;
	afx_msg void OnLvnItemchangedAxis(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeG20coor2();
	double m_G20X;
	double m_G20Y;
	double m_G20Z;
	double m_G20A;
	double m_G20B;
	double m_G20C;
	afx_msg void OnBnClickedOk();
};
