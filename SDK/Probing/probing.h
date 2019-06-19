#pragma once


// probing dialog

class probing : public CDialog
{
	DECLARE_DYNAMIC(probing)

public:
	probing(CWnd* pParent = NULL);   // standard constructor
	virtual ~probing();

// Dialog Data
	enum { IDD = IDD_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
