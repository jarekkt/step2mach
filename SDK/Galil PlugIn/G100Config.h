#pragma once
#include "afxcmn.h"


// G100Config dialog

class G100Config : public CDialog
{
	DECLARE_DYNAMIC(G100Config)

public:
	G100Config(CWnd* pParent = NULL);   // standard constructor
	virtual ~G100Config();

// Dialog Data
	enum { IDD = IDD_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSendnew();
	CIPAddressCtrl m_G100IP;
	CIPAddressCtrl m_G100NM;
	CIPAddressCtrl m_MyIP;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
	CString m_Error;
	BOOL m_Perm;
};
