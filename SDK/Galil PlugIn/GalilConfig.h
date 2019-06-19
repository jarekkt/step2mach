#pragma once
#include "resource.h"
#include "afxwin.h"

// GalilConfig dialog

class GalilConfig : public CDialog
{
	DECLARE_DYNAMIC(GalilConfig)

public:
	GalilConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~GalilConfig();

// Dialog Data
	enum { IDD = IDD_GALILCON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	BOOL m_CalcSpeed;
	BOOL m_RefPos;
	afx_msg void OnBnClickedOk();
 
	CComboBox m_Motor[6];
	int m_xbuf;
	int m_Compos;
	int m_PlanPos;
	afx_msg void OnTimer(UINT nIDEvent);
	int m_SpindleAxis;
	double m_VectorTimeConst;
	int m_VectorDecel;
	BOOL m_Index[6];
	
	afx_msg void OnEnChangeVectdecel();
};
