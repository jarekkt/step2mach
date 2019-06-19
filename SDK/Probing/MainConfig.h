#pragma once


// MainConfig dialog

class MainConfig : public CDialog
{
	DECLARE_DYNAMIC(MainConfig)

public:
	MainConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~MainConfig();

// Dialog Data
	enum { IDD = IDD_MAINCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTooltouch();
	afx_msg void OnBnClickedCirclecenter();
	afx_msg void OnBnClickedOk();
};
