#pragma once


// BugReport dialog

class BugReport : public CDialog
{
	DECLARE_DYNAMIC(BugReport)

public:
	BugReport(CWnd* pParent = NULL);   // standard constructor
	virtual ~BugReport();

// Dialog Data
	enum { IDD = IDD_BUGREPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString Subject;
	CString Body;
	BOOL AddMill;
	BOOL AddTurn;
	BOOL AddProgram;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIncludemill();
	afx_msg void OnBnClickedIncludeturn();
};
