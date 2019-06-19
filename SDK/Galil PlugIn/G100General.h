#pragma once


// G100General dialog

class G100General : public CDialog
{
	DECLARE_DYNAMIC(G100General)

public:
	G100General(CWnd* pParent = NULL);   // standard constructor
	virtual ~G100General();



// Dialog Data
	enum { IDD = IDD_GENERALCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDiscovery();
	afx_msg void OnBnClickedGeneralparam();
	afx_msg void OnBnClickedStatus();
	afx_msg void OnBnClickedOk();
};
