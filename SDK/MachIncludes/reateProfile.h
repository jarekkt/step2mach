#pragma once
#include "afxwin.h"
#include "resource.h"


// CreateProfile dialog

class CreateProfile : public CDialog
{
	DECLARE_DYNAMIC(CreateProfile)

public:
	CreateProfile(CWnd* pParent = NULL);   // standard constructor
	virtual ~CreateProfile();

// Dialog Data
	enum { IDD = IDD_CREATEPROFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// list of profiles.
	CListBox ProList;
	void FillList(void);
	int FileNum;
	virtual BOOL OnInitDialog();
	CEdit NewName;
   	int Blank;
};
