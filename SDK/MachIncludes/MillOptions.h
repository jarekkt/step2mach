#pragma once
 


// MillOptions dialog

class MillOptions : public CPropertyPage
{
	DECLARE_DYNAMIC(MillOptions)

public:
	MillOptions();
	virtual ~MillOptions();

// Dialog Data
	enum { IDD = IDD_MILLOPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_ZInhPersist;
	double m_InhibitDepth;
	BOOL m_ZInhibit;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	BOOL m_Dig4;
	BOOL DigLetter;
	BOOL m_UpDown;
	BOOL m_CompPlus;
	afx_msg void OnBnClickedAdvancedcomp();
	afx_msg void OnBnClickedZinhibit();
	afx_msg void OnBnClickedZinhpersist();
	afx_msg void OnBnClicked4axis();
	afx_msg void OnBnClickedDigletter();
	afx_msg void OnBnClickedThcupdown();
	BOOL m_Plasma;
	afx_msg void OnBnClickedPlasma();
	BOOL m_Hold1;
	 
	BOOL m_KeepRef;
};
