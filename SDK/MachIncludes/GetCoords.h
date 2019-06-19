#pragma once


// GetCoords dialog

class GetCoords : public CDialog
{
	DECLARE_DYNAMIC(GetCoords)

public:
	GetCoords(CWnd* pParent = NULL);   // standard constructor
	virtual ~GetCoords();

// Dialog Data
	enum { IDD = IDD_GETCOORDs };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// // text of get coordinate question..
	CString m_Question;
	double m_XCoor;
	double m_YCoor;
	double m_ZCoor;
	double m_ACoor;
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButton1();
	void Update(void);
	virtual BOOL OnInitDialog();
};
