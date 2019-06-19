#pragma once



// OkayToMove dialog

class OkayToMove : public CDialog
{
	DECLARE_DYNAMIC(OkayToMove)

public:
	OkayToMove(CWnd* pParent = NULL);   // standard constructor
	virtual ~OkayToMove();

// Dialog Data
	enum { IDD = IDD_OKAYTOMOVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_IsProbeActive;
	bool m_IsOkayToMove;
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedYes();
	afx_msg void OnBnClickedNo();
};
