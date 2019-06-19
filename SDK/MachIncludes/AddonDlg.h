#pragma once
#include "afxcmn.h"
 

// AddonDlg dialog

class AddonDlg : public CDialog
{
	DECLARE_DYNAMIC(AddonDlg)

public:
	AddonDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddonDlg();

	void FillGrid(void);
	void GetAuthorDesc( int x );

// Dialog Data
	enum { IDD = IDD_ADDONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	 afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	 
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
