#pragma once
#include "afxwin.h"


// HomanConf dialog

class HomanConf : public CDialog
{
	DECLARE_DYNAMIC(HomanConf)

public:
	HomanConf(CWnd* pParent = NULL);   // standard constructor
	virtual ~HomanConf();

// Dialog Data
	enum { IDD = IDD_HOMANN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSendconfig();
	afx_msg void OnBnClickedOk();
	short confAddr,config,confuart,conflash,confpump,confdebug,config2;
	BOOL m_UseLCD;
	BOOL m_UseAna;
	BOOL m_UseDiscrete;
	BOOL m_UsePump;
	BOOL m_UsePortB;
	BOOL m_UseCharGap;
	BOOL m_UseMessageGap;
	CComboBox m_Speed;
	CComboBox m_Proto;
	virtual BOOL OnInitDialog();
	CComboBox m_Pump;
	afx_msg void OnCbnSelchangePump();
	short m_FlashMask;
	BOOL m_LimitErr;
	BOOL m_MPG1;
	BOOL m_MPG2;
	BOOL m_DebugOff;
	BOOL m_FreqOff;
	BOOL m_DigiOff;
	BOOL m_MPG1HiRes;
	BOOL m_MPG2HiRes;
	BOOL m_KeyOff;
	afx_msg void OnBnClickedResetio();
	afx_msg void OnCbnSelchangeSpeed();
};
