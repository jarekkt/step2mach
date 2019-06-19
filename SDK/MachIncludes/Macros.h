#pragma once


// Macros dialog

class Macros : public CDialog
{
	DECLARE_DYNAMIC(Macros)

public:
	Macros(CWnd* pParent = NULL);   // standard constructor
	virtual ~Macros();

// Dialog Data
	enum { IDD = IDD_MACROS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
