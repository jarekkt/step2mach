#pragma once


// FormulaSet dialog

class FormulaSet : public CDialog
{
	DECLARE_DYNAMIC(FormulaSet)

public:
	FormulaSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~FormulaSet();

// Dialog Data
	enum { IDD = IDD_FORMULA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_FormulaOn;
	CString m_Formulas[6];
	double m_Variables[10];
	afx_msg void OnBnClickedTest1();
	afx_msg void OnBnClickedTest2();
	afx_msg void OnBnClickedTest3();
	afx_msg void OnBnClickedTest4();
	afx_msg void OnBnClickedTest5();
	afx_msg void OnBnClickedTest6();
	void SetVars();
	double  m_Answer;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
