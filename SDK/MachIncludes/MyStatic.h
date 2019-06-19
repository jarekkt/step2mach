#if !defined(AFX_MYSTATIC_H__E6BDA078_FB74_42C0_8793_169232391ADF__INCLUDED_)
#define AFX_MYSTATIC_H__E6BDA078_FB74_42C0_8793_169232391ADF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyStatic window

class MyStatic : public CStatic
{
// Construction
public:
	MyStatic();
    int height;
    int lineWidth;
    int lineHeight;
    int width;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetLine( int x, int y, int z, int a);
	 
	virtual ~MyStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(MyStatic)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__E6BDA078_FB74_42C0_8793_169232391ADF__INCLUDED_)
