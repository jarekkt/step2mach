#pragma once
#include "afxwin.h"
#include "memmap.h"

// ModBusStatus dialog

#define WM_MY_NOTIFY  WM_USER+666

 

class ModBusStatus : public CDialog
{
	DECLARE_DYNAMIC(ModBusStatus)

public:
	ModBusStatus(CWnd* pParent = NULL);   // standard constructor
	virtual ~ModBusStatus();

// Dialog Data
	enum { IDD = IDD_MODBUSSTATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnBnClickedTest();
	virtual BOOL OnInitDialog();
	CString GetStatusMessage( short nStatus );
	void    CheckError( short nStatus );
	void    UpdateStatusDisplay( CString csMsg );

	void    FillFromInput( int slave, int start, int nBytes );
    void    FillFromHolding( int slave, int start, int nBytes );
	void    FillFromCoil( int slave, int start, int nBytes ); 
	void    FillFromStatus( int slave,int start, int nBytes );
	int     GetInputWord( int bit );
	
	int timer;

	LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);

    short   m_fillStatus;
    short ScriptInBuffer[512];
	short ScriptOutBuffer[512];
    bool  FirstMPG;
    bool  InTest;
	int m_AutoType1;
	int m_AutoType2;
	int m_AutoType3;
	int m_AutoType4;
	BOOL m_Auto1On;
	BOOL m_Auto2On;
	BOOL m_Auto3On;
	BOOL m_Auto4On;
	int m_AutoSlave1;
	int m_AutoSlave2;
	int m_AutoSlave3;
    int m_AutoSlave4;
	int m_AutoStart1;
	int m_AutoStart2;
	int m_AutoStart3;
	int m_AutoStart4;
	int m_AutoEnd1;
	int m_AutoEnd2;
	int m_AutoEnd3;
	int m_AutoEnd4;
	short nStatus;
	bool  visible;

	bool FillInput,FillHolding,FillCoil;
	int  FillnRegs;
	int  RemStart,RemSlave;
	//CSystemTray m_TrayIcon;
 
	afx_msg void OnBnClickedApply();
	CString m_Status;
	CStatic m_StatusBox;
	int m_Port;
	int m_Baud;
	int m_Hz;
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL DestroyWindow();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnEndSession(BOOL bEnding);
	BOOL m_OEMReg;
	int m_OEMRegnum;
	BOOL m_Homann;
	afx_msg void OnBnClickedHomann();
	afx_msg void OnBnClickedConfighoman();
	void WriteToInput(int slave, int start, int nBytes);
	void WriteSingle(int slave, int address, short data);
	BOOL m_BitPack1;
	int m_BitPackReg1;
	BOOL m_BitPackOut1;
	int m_BitPackOutReg1;
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	BOOL m_RTSON;
	int m_TimeOut;
	afx_msg void OnCbnSelchangeProtocol();
	CComboBox m_Prot;
	afx_msg void OnEnChangeOemreg();
	BOOL m_MPG1;
	BOOL m_MPG2;
};
