#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// G100FLASHCONFIG dialog

class G100FLASHCONFIG : public CDialog
{
	DECLARE_DYNAMIC(G100FLASHCONFIG)

public:
	G100FLASHCONFIG(CWnd* pParent = NULL);   // standard constructor
	virtual ~G100FLASHCONFIG();

// Dialog Data
	enum { IDD = IDD_G100WTCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_Firmware;
	int m_BoardID;
	CString m_VendorID;
	int m_nInputs;
	int m_nAnaIns;
	int m_nAnaOuts;
	int m_nMavg;
	int m_nAxis;
	int m_Verbosity;
	CString m_Controller;
	CIPAddressCtrl m_IP;
	CIPAddressCtrl m_NetMask;
	CComboBox m_NetFlags;
	CComboBox m_PulseMode;
	CComboBox m_EncoderCtrl;
	int m_ExternalInc;
	int m_InternalInc;
	CComboBox m_Freq;
	afx_msg void OnBnClickedFlash();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedReadrex();
	afx_msg void OnBnClickedReadsetup();
	virtual BOOL OnInitDialog();
	void FillData(void);
	int m_CurSel;
	afx_msg void OnBnClickedAxissel();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	int m_nOutPuts;
	afx_msg void OnCbnSelchangePulsemode();
	afx_msg void OnCbnSelchangeCountertrigger();
	afx_msg void OnEnChangeExtinc();
	afx_msg void OnCbnSelchangeDivider();
	afx_msg void OnEnChangeIntinc();
	afx_msg void OnCbnSelchangeNetflags();
	afx_msg void OnEnChangeVerbosity();
	afx_msg void OnIpnFieldchangedIpg100(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnIpnFieldchangedNetmask(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeControlname();
};
