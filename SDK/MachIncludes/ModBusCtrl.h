#pragma once
#include "smrl.h"

#if !defined(AFX_SMRLTEST1DLG_H__529E1C81_36E7_48F6_8D3C_8829CDB06580__INCLUDED_)
#define AFX_SMRLTEST1DLG_H__529E1C81_36E7_48F6_8D3C_8829CDB06580__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000






// Define radio button selector constants

#define INPUT_REG 0
#define HOLDING_REG 1
#define COIL 2
#define DISCRETE_INPUT 3



// Define format types for UpdateDataDisplay.

#define FMT_HEX4 0		// display register value as four hex
#define FMT_SINT 1		// display register value as signed integer
#define FMT_UINT 2		// display register value as unsigned integer
#define FMT_HEX2 3		// display register value as two hex







/////////////////////////////////////////////////////////////////////////////
// ModBusCtrl dialog

class ModBusCtrl : public CDialog
{
// Construction
public:
	ModBusCtrl(CWnd* pParent = NULL);	// standard constructor
	void CloseDialog( void );				// function for allowing parent to close dialog

// Dialog Data
	//{{AFX_DATA(ModBusCtrl)
	enum { IDD = IDD_MODBUS };
	CSliderCtrl	m_ctrlReadSlider;
	CString	m_csData;
	int		m_nInput;
	short	m_nNumRegs;
	short	m_nSlaveAddr;
	int		m_nFormat;
	UINT	m_nStartReg;
	short m_nRcvTimeout;
	short m_nXmtTimeout;
	long m_nBaud;
	short m_nParity;
	short m_nStopBits;
	short m_nDataBits;
	short m_nCommPortNum;
	short m_nCommPortState;
	short m_nXmtDelay;
	short m_nRTSControl;
	short m_nDTRControl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ModBusCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	void SetControlState( int nID, BOOL bState );
	void UpdateDisplay( CString s, int nID );
	void UpdateStatusDisplay( CString csMsg );
	void UpdateDataDisplay( WORD *pData, WORD nNumRegs, int nFormat );
	void SetIOLabels( int nIoType );
	short m_buffer[ 800 ];						// place to read words into


	void CheckError( short nStatus );
	CString GetStatusMessage( short nStatus );

	// Generated message map functions
	//{{AFX_MSG(ModBusCtrl)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenPortButton();
	afx_msg void OnClosePortButton();
	afx_msg void OnClose();
	afx_msg void OnCoil();
	afx_msg void OnDecimal();
	afx_msg void OnDiscreteInput();
	afx_msg void OnHex();
	afx_msg void OnHoldingReg();
	afx_msg void OnInputReg();
	afx_msg void OnRead();
	afx_msg void OnReadExceptionStatusButton();
	afx_msg void OnReportSlaveId();
	afx_msg void OnWrite();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMRLTEST1DLG_H__529E1C81_36E7_48F6_8D3C_8829CDB06580__INCLUDED_)
