#pragma once
#include "resource.h"

// Center dialog

class Center : public CDialog
{
	DECLARE_DYNAMIC(Center)

public:
	Center(CWnd* pParent = NULL);   // standard constructor
	virtual ~Center();

// Dialog Data
	enum { IDD = IDD_CENTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool   Move;
	double m_Xloc;
	double m_YLoc;
	double m_Rad;
	afx_msg void OnBnClickedMoveto();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
