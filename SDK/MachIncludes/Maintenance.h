#pragma once
#include "afxwin.h"


// Maintenance dialog

class Maintenance : public CDialog
{
	DECLARE_DYNAMIC(Maintenance)

public:
	Maintenance(CWnd* pParent = NULL);   // standard constructor
	virtual ~Maintenance();

// Dialog Data
	enum { IDD = IDD_MAINTENANCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// //hours of actual runtime
	double m_Hours;
	double m_Axis1Dist;
	double m_Axis2Dist;
	double m_Axis3Dist;
	double m_Axis4Dist;
	double m_Axis5Dist;
	double m_Axis6Dist;

	afx_msg void OnBnClickedReset();
	virtual BOOL OnInitDialog();
	double m_ThisTime;
	CEdit m_HourEdit;
	CEdit m_ThisEdit;
	int m_M3;
	afx_msg void OnBnClickedZerom3();
};
