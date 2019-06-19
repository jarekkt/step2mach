#if !defined(AFX_SAFEMOVEYESNO_H__91AF61A1_4DF3_41E1_8714_202A7B2A0C08__INCLUDED_)
#define AFX_SAFEMOVEYESNO_H__91AF61A1_4DF3_41E1_8714_202A7B2A0C08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SafeMoveYesNo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SafeMoveYesNo dialog

class SafeMoveYesNo : public CDialog
{
// Construction
public:
	SafeMoveYesNo(CWnd* pParent = NULL);   // standard constructor
    double m_XPos;
    double m_YPos;
	double m_ZPos;
	double m_APos;
	double m_BPos;
	double m_CPos;
	double m_SafeZ;
// Dialog Data
	//{{AFX_DATA(SafeMoveYesNo)
	enum { IDD = IDD_SAFEMOVE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SafeMoveYesNo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SafeMoveYesNo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAFEMOVEYESNO_H__91AF61A1_4DF3_41E1_8714_202A7B2A0C08__INCLUDED_)
