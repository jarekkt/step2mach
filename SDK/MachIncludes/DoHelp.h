#pragma once


// DoHelp dialog

class DoHelp : public CDialog
{
	DECLARE_DYNAMIC(DoHelp)

public:
	DoHelp(CWnd* pParent = NULL);   // standard constructor
	virtual ~DoHelp();

// Dialog Data
	enum { IDD = IDD_DOHELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
