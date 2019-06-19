#pragma once


// ResetWarning dialog

class ResetWarning : public CDialog
{
	DECLARE_DYNAMIC(ResetWarning)

public:
	ResetWarning(CWnd* pParent = NULL);   // standard constructor
	virtual ~ResetWarning();

// Dialog Data
	enum { IDD = IDD_RESETWARN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_NoWarn;
	afx_msg void OnBnClickedOk();
};
