#if !defined(AFX_SETHOTKEY_H__ED3B5510_6603_49E8_B7C4_B181A79284EA__INCLUDED_)
#define AFX_SETHOTKEY_H__ED3B5510_6603_49E8_B7C4_B181A79284EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetHotKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetHotKey dialog

class SetHotKey : public CDialog
{
// Construction
public:
	SetHotKey(CWnd* pParent = NULL);   // standard constructor
    int KEY;
// Dialog Data
	//{{AFX_DATA(SetHotKey)
	enum { IDD = IDD_HOTKEY };
	CString	m_Key;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetHotKey)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetHotKey)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETHOTKEY_H__ED3B5510_6603_49E8_B7C4_B181A79284EA__INCLUDED_)
