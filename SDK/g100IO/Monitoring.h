#pragma once
#include "resource.h"
#include "afxwin.h"


// Monitoring dialog

class Monitoring : public CDialog
{
	DECLARE_DYNAMIC(Monitoring)

public:
	Monitoring(CWnd* pParent = NULL);   // standard constructor
	virtual ~Monitoring();

	 
	BOOL m_Still;
	int m_Encoder[6];
	int m_DDAS[6];
	double m_Pos[6];
 	BOOL m_Halt[22];
	BOOL m_Ins[22];
	BOOL m_Outs[16];
  	CString m_AnaOut[4];
	CString m_AnaIn[4];
	UINT    hcolor[22];

	void    FillData();
 
// Dialog Data
	enum { IDD = IDD_MONITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	BOOL m_IsConnected;
	BOOL m_IsMovable;
	BOOL m_EndOfQueue;
	BOOL m_SyncError;
	afx_msg void OnBnClickedClose();
	int m_BufferTime;
	double m_Rate;
	int m_LocalTime;
	int m_Clock;
	CButton m_bHalt[22];
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	int m_SpinDDA;
	BOOL m_Queue5;
};
