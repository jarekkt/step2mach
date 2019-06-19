#pragma once
 
#include "afxwin.h"
#include "./ListCtrl/GridCtrl.h"
#include ".\grid\MyCug.h"


// ModBusConfig dialog

class ModBusConfig : public CDialog
{
	DECLARE_DYNAMIC(ModBusConfig)

public:
	ModBusConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~ModBusConfig();

	MyCug  m_ModCfg;

// Dialog Data
	enum { IDD = IDD_MODSETDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	 void ModBusConfig::OnStnClickedGrid();


	 virtual BOOL OnInitDialog();
	 afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	 afx_msg void OnSize(UINT nType, int cx, int cy);
	 CListBox m_ModCon;
	 afx_msg void OnBnClickedOk();
	 afx_msg void OnBnClickedApply();
	 CString GetStatusMessage( short nStatus );
	 void    UpdateStatusDisplay( CString csMsg );

//ModBus Commmands

	 bool Applying;
     int  TimerTick;
     int  m_Port;
     int  m_Baud;
	 int  m_ProtoCol;
	 CStatic m_StatusBox;
	 CComboBox m_Prot;
	 BOOL      m_RTSON;
	 int       m_TimeOut;
	 afx_msg void OnBnClickedTest();
	 CStatic m_Status;
	 bool    visible;
	 bool    SystemDown;
	 afx_msg void OnClose();
protected:
	virtual void OnOK();
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnTimer(UINT nIDEvent);
	BOOL m_Run;
	afx_msg void OnBnClickedRun();
	void OpenBus(void);
	CString m_StatusWin;
	void UpdateFromCFG(void);
};
