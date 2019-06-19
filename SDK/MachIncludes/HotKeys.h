#if !defined(AFX_HOTKEYS_H__2305A9BB_5AA1_40EC_896A_3364C137A9AE__INCLUDED_)
#define AFX_HOTKEYS_H__2305A9BB_5AA1_40EC_896A_3364C137A9AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HotKeys.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// HotKeys dialog

class HotKeys : public CDialog
{
// Construction
public:
	void SetReadout( CString &text, int Index);
	HotKeys(CWnd* pParent = NULL);   // standard constructor
    int AxisKeys[12];
 
 
// Dialog Data
	//{{AFX_DATA(HotKeys)
	enum { IDD = IDD_HOTKEYS };
	int		m_AMCode;
	int		m_APCode;
	int		m_BMCode;
	int		m_BPCode;
	int		m_CMCode;
	int		m_CPCode;
	int		m_DROCode;
	int		m_XMCode;
	int		m_XPCode;
	int		m_YMCode;
	int		m_YPCode;
	int		m_ZMCode;
	int		m_ZPCode;
	int		m_MDICode;
	int		m_GCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HotKeys)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(HotKeys)
	afx_msg void OnAminus();
	afx_msg void OnAplus();
	afx_msg void OnBminus();
	afx_msg void OnBplus();
	afx_msg void OnCminus();
	afx_msg void OnCplus();
	afx_msg void OnXminus();
	afx_msg void OnXplus();
	afx_msg void OnYminus();
	afx_msg void OnYplus();
	afx_msg void OnZminus();
	afx_msg void OnZplus();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDroselect();
	afx_msg void OnMdiselect();
	afx_msg void OnLoadgcode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	short m_OEM1;
	short m_OEM2;
	short m_OEM3;
	short m_OEM4;
	short m_OEM5;
	short m_OEM6;
	afx_msg void OnBnClickedGlist();
	int m_listkey;
	int m_OEM7;
	int m_OEM8;
	int m_OEM9;
	int m_OEM10;
	int m_OEM11;
	int m_OEM12;
	int m_OEM13;
	int m_OEM14;
	int m_OEM15;
	afx_msg void OnEnChangeOem11();
	void SendPurge(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTKEYS_H__2305A9BB_5AA1_40EC_896A_3364C137A9AE__INCLUDED_)
