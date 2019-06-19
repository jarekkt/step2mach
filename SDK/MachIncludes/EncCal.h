#if !defined(AFX_ENCCAL_H__0405EF00_9D77_4BDC_9A53_74EB58EB84BA__INCLUDED_)
#define AFX_ENCCAL_H__0405EF00_9D77_4BDC_9A53_74EB58EB84BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EncCal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EncCal dialog

class EncCal : public CDialog
{
// Construction
public:
	EncCal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(EncCal)
	enum { IDD = IDD_CALENC };
	double	m_Enc1;
	double	m_Enc2;
	double	m_Enc3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EncCal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EncCal)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENCCAL_H__0405EF00_9D77_4BDC_9A53_74EB58EB84BA__INCLUDED_)
