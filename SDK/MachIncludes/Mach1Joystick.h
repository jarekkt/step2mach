#if !defined(AFX_MACH1JOYSTICK_H__877BA2E3_7EEA_42EB_8B09_7417EEC85D06__INCLUDED_)
#define AFX_MACH1JOYSTICK_H__877BA2E3_7EEA_42EB_8B09_7417EEC85D06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mach1Joystick.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Mach1Joystick window

class Mach1Joystick : public CStatic
{
// Construction
public:
	Mach1Joystick();
	CBitmap picture;
	void DrawBitmap(CDC* pDC, CBitmap& bitmap, CPalette *pPal );
   	CDC memDC;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Mach1Joystick)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~Mach1Joystick();

	// Generated message map functions
protected:
	//{{AFX_MSG(Mach1Joystick)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACH1JOYSTICK_H__877BA2E3_7EEA_42EB_8B09_7417EEC85D06__INCLUDED_)
