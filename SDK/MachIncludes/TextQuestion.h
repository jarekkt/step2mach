#pragma once


// TextQuestion dialog

class TextQuestion : public CDialog
{
	DECLARE_DYNAMIC(TextQuestion)

public:
	TextQuestion(CWnd* pParent = NULL);   // standard constructor
	virtual ~TextQuestion();

// Dialog Data
	enum { IDD = IDD_TEXTQUESTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Question;
	CString m_Answer;
	afx_msg void OnBnClickedOk();
};
