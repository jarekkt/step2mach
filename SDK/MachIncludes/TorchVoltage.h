#pragma once
#include "afxwin.h"


// TorchVoltage dialog

class TorchVoltage : public CDialog
{
	DECLARE_DYNAMIC(TorchVoltage)

public:
	TorchVoltage(CWnd* pParent = NULL);   // standard constructor
	virtual ~TorchVoltage();
	CString Volts[10];
	int     Speeds[10];
	int     valid;

// Dialog Data
	enum { IDD = IDD_TORCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	 
	void OnOK(void);
	CGridCtrl m_Torch;
	afx_msg void OnLbnSelchangeTorchvolts();
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	virtual BOOL DestroyWindow();
	virtual void OnFinalRelease();
protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnBnClickedSelect();
	afx_msg void OnBnClickedSave();
};
