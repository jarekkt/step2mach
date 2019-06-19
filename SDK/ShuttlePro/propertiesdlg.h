#pragma once
#include "afxwin.h"
#include "resource.h"


// propertiesdlg dialog

class propertiesdlg : public CDialog
{
	DECLARE_DYNAMIC(propertiesdlg)

public:
	propertiesdlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~propertiesdlg();

// Dialog Data
	enum { IDD = IDD_PROP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit;
	int test;
	afx_msg void OnCbnSelchangeCombo8();
	CComboBox m_Function[17];
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	int m_Type;
	afx_msg void OnBnClickedRadio7();
	short m_dMacro1;
	short m_dMacro2;
	short m_dOEM1;
	short m_dOEM2;
};
