#pragma once


// TurnOptions dialog

class TurnOptions : public CPropertyPage
{
	DECLARE_DYNAMIC(TurnOptions)

public:
	TurnOptions();
	virtual ~TurnOptions();

// Dialog Data
	enum { IDD = IDD_TURNOPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_Radial;
	BOOL m_Diametric;
	afx_msg void OnBnClickedRadial();
	afx_msg void OnBnClickedDiam();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	double m_DepthLastPass;
	double m_InFeed;
	double m_Spring;
	double m_MinDepth;
	double m_XClear;
	double m_ZClear;
	double m_Chamfer;
	double m_DepthFirstPass;
	int m_CutType;
	int m_InfeedType;
	double m_CutDepth;
	BOOL m_RevArc;
};
