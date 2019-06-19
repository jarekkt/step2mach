#if !defined(AFX_MYCONFSHEET_H__A3394E8E_B492_48E1_BC49_A65E5F289732__INCLUDED_)
#define AFX_MYCONFSHEET_H__A3394E8E_B492_48E1_BC49_A65E5F289732__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyConfSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyConfSheet

class MyConfSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(MyConfSheet)

// Construction
public:
	MyConfSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	MyConfSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyConfSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MyConfSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(MyConfSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCONFSHEET_H__A3394E8E_B492_48E1_BC49_A65E5F289732__INCLUDED_)
