#if !defined(AFX_GSTATE_H__63436C78_F988_449D_8F77_641B6616371B__INCLUDED_)
#define AFX_GSTATE_H__63436C78_F988_449D_8F77_641B6616371B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GState.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GState dialog

class GState : public CDialog
{
// Construction
public:
	void UpdatePlanner();
DECLARE_DYNCREATE(GState);
	void Update();
	GState(CWnd* pParent = NULL);   // standard constructor
    bool changeing;
	CString* ActiveG[11];
 
// Dialog Data
	//{{AFX_DATA(GState)
	enum { IDD = IDD_STATE };
	int		m_IJMode;
	int		m_DistanceMode;
	int		m_MotionMode;
	int		m_Plane;
	int		m_BackLash;
	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
 	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GState)
	virtual BOOL OnInitDialog();
	afx_msg void OnBloff();
	afx_msg void OnBlon();
	afx_msg void OnOk();
	afx_msg void OnConstant();
	afx_msg void OnExactstop();
	afx_msg void OnIjmode();
	afx_msg void OnIjmode1();
	afx_msg void OnDistancemode();
	afx_msg void OnIncremental();
	afx_msg void OnPlane();
	afx_msg void OnYz();
	afx_msg void OnXz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeAr();
	double JogInc0,JogInc1,JogInc2,JogInc3,JogInc4,JogInc5,JogInc6,JogInc7,JogInc8,JogInc9;
	CString m_Init;
	BOOL m_InitAllResets;
	BOOL m_JogPersist;
	BOOL m_SlowMode;
	BOOL m_PersistOff;
	BOOL m_SaveOffDialog;
	BOOL m_G54Back;
	BOOL m_AutoScreen;
	BOOL m_Diameter;
	BOOL m_ChargePump;
	BOOL m_Z25D;
	double m_ShuttleAccel;
	BOOL m_MacroPump;
	BOOL m_OverRide2;
	BOOL m_Slow;
	BOOL m_Watch;
	int LookAhead;
	BOOL m_Debug;
	BOOL m_ShortRot;
	BOOL m_HWSafe;
	BOOL m_Rot360;
	afx_msg void OnBnClickedZ25();
	BOOL m_Nurbs;
	BOOL m_HiRes;
	BOOL m_UDP;
	afx_msg void OnBnClickedOverride2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GSTATE_H__63436C78_F988_449D_8F77_641B6616371B__INCLUDED_)
