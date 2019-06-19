#pragma once
#include "afxwin.h"


// G100Monitor dialog



class G100Monitor : public CDialog
{
	DECLARE_DYNAMIC(G100Monitor)

public:
	G100Monitor(CWnd* pParent = NULL);   // standard constructor
	virtual ~G100Monitor();

	void     FillData();

// Dialog Data
	enum { IDD = IDD_MONITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	int m_LastMessage;
	int m_LastSent;
	int m_LastQueued;
	int m_Window;
	int m_ISR;
	int m_SSEQ;
	int m_ESEQ;
	BOOL m_Still;
	BOOL m_Drained;
	UINT m_Flags;
	UINT m_Encoder[6];
	int m_DDAS[6];
	double m_Pos[6];
	BOOL m_DigReq;
	BOOL m_AnaReq;
	BOOL m_Halt[22];
	BOOL m_Ins[22];
	BOOL m_Outs[16];
	BOOL m_Debug;
	afx_msg void OnBnClickedEnabledebug();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedOk();
	CString m_AnaOut[4];
	CString m_AnaIn[4];
	CButton m_DebugBox;
	BOOL m_SEQError;
	int m_QueueUsed;
	int m_MISR;
	int m_Mavg;
	BOOL m_HaltWait;
	int m_nMess;
};

class CMonitorThread : public CWinThread
{
   friend class CMainFrame;
   DECLARE_DYNCREATE(CMonitorThread)

public:
   CMonitorThread();
   virtual ~CMonitorThread();
   

private:
 
public:
   virtual BOOL InitInstance();
   virtual int ExitInstance();
   DECLARE_MESSAGE_MAP()
};
