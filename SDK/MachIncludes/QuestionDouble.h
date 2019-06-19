#if !defined(AFX_QUESTIONDOUBLE_H__54E46461_8516_4EAB_A43B_AA38C6C41CC4__INCLUDED_)
#define AFX_QUESTIONDOUBLE_H__54E46461_8516_4EAB_A43B_AA38C6C41CC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuestionDouble.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// QuestionDouble dialog

class QuestionDouble : public CDialog
{
// Construction
public:
	QuestionDouble(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(QuestionDouble)
	enum { IDD = IDD_QUESTION };
	CEdit	m_Input;
	double	m_Answer;
	CString	m_Text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(QuestionDouble)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(QuestionDouble)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUESTIONDOUBLE_H__54E46461_8516_4EAB_A43B_AA38C6C41CC4__INCLUDED_)
