#pragma once
#include "afxwin.h"


// BrainControlDlg dialog

class BrainControlDlg : public CDialog
{
	DECLARE_DYNAMIC(BrainControlDlg)

public:
	BrainControlDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~BrainControlDlg();

// Dialog Data
	enum { IDD = IDD_BRAINS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_BrainList;
	BOOL m_Enable;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeBrains();
	afx_msg void OnBnClickedEnabled();
	afx_msg void OnBnClickedEnall();
	afx_msg void OnBnClickedDisall();
	afx_msg void OnBnClickedReloadone();
	afx_msg void OnBnClickedReloadall();
};
