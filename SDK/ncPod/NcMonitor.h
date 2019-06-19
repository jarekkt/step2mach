#pragma once
#include "afxwin.h"
#include "resource.h"


// NcMonitor dialog

class NcMonitor : public CDialog
{
	DECLARE_DYNAMIC(NcMonitor)

public:
	NcMonitor(CWnd* pParent = NULL);   // standard constructor
	virtual ~NcMonitor();

// Dialog Data
	enum { IDD = IDD_NCPOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton Bit1;
	CButton Bit2;
	CButton Bit4;
	CButton Bit8;
	CButton Bit16;
	CButton Bit32;
	CButton Bit64;
	CButton Bit128;
    CButton Bit256;
	CButton Bit512;
	double m_Pulloff[6];
	bool Apply;

	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	CButton m_Out0;
	CButton m_In0;
	CButton m_Out1;
	CButton m_In1;
	CButton m_Out2;
	CButton m_In2;
	CButton m_Out3;
	CButton m_In3;
	CButton m_Out4;
	CButton m_In4;
	CButton m_Out5;
	CButton m_In5;
	CButton m_Out6;
	CButton m_In6;
	CButton m_Out7;
	CButton m_In7;
	CComboBox m_Cycle;
	afx_msg void OnCbnSelchangeCycle();
	int m_MachTotal;
	double m_VelTotal;
	int m_PodTotal;
	CString m_Firmware;
	afx_msg void OnBnClickedClearcounts();
	int m_HomeType;
	afx_msg void OnBnClickedHoming();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	double m_Diffs;
	BOOL m_Home[4];
	
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedApplypodsettings();
	afx_msg void OnBnClickedRadio1();
};

class PodThread : public CWinThread
{
   friend class CMainFrame;
   DECLARE_DYNCREATE(PodThread)

public:
   PodThread();
   virtual ~PodThread();
   

private:
 
public:
   virtual BOOL InitInstance();
   virtual int ExitInstance();
   DECLARE_MESSAGE_MAP()
};