#pragma once


// Helper dialog

class Helper : public CDialog
{
	DECLARE_DYNAMIC(Helper)

public:
	Helper(CWnd* pParent = NULL);   // standard constructor
	virtual ~Helper();

// Dialog Data
	enum { IDD = IDD_HELPER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
