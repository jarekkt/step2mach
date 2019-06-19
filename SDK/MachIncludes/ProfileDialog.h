#pragma once
#include "afxwin.h"


// ProfileDialog dialog

class ProfileDialog : public CDialog
{
	DECLARE_DYNAMIC(ProfileDialog)

public:
	ProfileDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~ProfileDialog();

// Dialog Data
	enum { IDD = IDD_PROFILER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCreateprofile();
	afx_msg void OnBnClickedDeleteprofile();
	afx_msg void OnLbnSelchangeProfilelist();
	afx_msg void OnLbnDblclkProfilelist();
	virtual BOOL OnInitDialog();
	CListBox ProList;
	int FileNum; //number of found profiles..
	CString ProName;
	// Fills the ListBox with Profile Names.
	void FillList(void);
	afx_msg void OnBnClickedOk();
};
