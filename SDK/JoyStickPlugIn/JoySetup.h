#pragma once

// JoySetup dialog

class JoySetup : public CDialog
{
	DECLARE_DYNAMIC(JoySetup)

public:
	JoySetup(CWnd* pParent = NULL);   // standard constructor
	virtual ~JoySetup();

// Dialog Data
	enum { IDD = IDD_JOYSTICKCON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_JoyOn;
	int m_Horiz;
	// Vertical Joystick Axis
	int m_Vert;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTtnGetDispInfoCustom1(NMHDR *pNMHDR, LRESULT *pResult);
};
