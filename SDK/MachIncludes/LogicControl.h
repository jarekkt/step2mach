#if !defined(AFX_LOGICCONTROL_H__1F775D73_D31B_4DD8_8A19_573E4B0D2008__INCLUDED_)
#define AFX_LOGICCONTROL_H__1F775D73_D31B_4DD8_8A19_573E4B0D2008__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogicControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LogicControl dialog

class LogicControl : public CDialog
{
// Construction
public:
    DECLARE_DYNCREATE(LogicControl);
	void Update();
	LogicControl(CWnd* pParent = NULL);   // standard constructor
    bool Setting;
    
// Dialog Data
	//{{AFX_DATA(LogicControl)
	enum { IDD = IDD_ANCILLARY };
	BOOL	m_DroLock;
	BOOL	m_ZInhibit;
	double	m_InhibitDepth;
	double	m_SafeZ;
	int		m_IgnoreTool;
	int     m_SerialType;
	BOOL	m_AAngular;
	BOOL	m_BAngular;
	BOOL	m_CAngular;
	BOOL	m_AutoEStop;
	BOOL	m_AutoTurnOff;
	BOOL	m_JoyOn;
	BOOL	m_OptStop;
	BOOL	m_ProgramSafe;
	CString	m_Editor;
	BOOL	m_HotKeyCheck;
	int		m_PulleyNumber;
	int		m_Speed0;
	int		m_Speed1;
	int		m_Speed3;
	int		m_Speed4;
	BOOL	m_GougeCheck;
	double	m_PWMBase;
	BOOL	m_SpinActual;
	int		m_Debouce;
	BOOL	m_DROPersistant;
	BOOL	m_OriginsOff;
	BOOL	m_G92Off;
	int		m_Baud;
	int		m_Com;
	int		m_PWMin;
	BOOL	m_ToolOffsetOff;
	BOOL	m_RadiusCompOff;

	//from state
	int		m_IJMode;
	int		m_DistanceMode;
	int		m_MotionMode;
	int		m_Plane;
	int		m_BackLash;
	//}}AFX_DATA

		double JogInc0,JogInc1,JogInc2,JogInc3,JogInc4,JogInc5,JogInc6,JogInc7,JogInc8,JogInc9;
    BOOL m_Boxed;
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


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LogicControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LogicControl)
	afx_msg void OnDrolock();
	virtual BOOL OnInitDialog();
	afx_msg void OnZinhibit();
	afx_msg void OnKillfocusInhdepth();
	afx_msg void OnDotool();
	afx_msg void OnIgnoretool();
	afx_msg void OnKillfocusSafez();
	afx_msg void OnAang();
	afx_msg void OnBang();
	afx_msg void OnCang();
	afx_msg void OnAutoestop();
	afx_msg void OnTurnoff();
	afx_msg void OnOptstop();
	afx_msg void OnProgramsafe();
	afx_msg void OnBrowse();
	afx_msg void OnHkeycheck();
	afx_msg void OnKillfocusRatio1();
	afx_msg void OnKillfocusRatio2();
	afx_msg void OnKillfocusRatio3();
	afx_msg void OnKillfocusRatio4();
	afx_msg void OnSetfocusRatio1();
	afx_msg void OnSetfocusRatio2();
	afx_msg void OnSetfocusRatio3();
	afx_msg void OnSetfocusRatio4();
	afx_msg void OnSetfocusSafez();
	afx_msg void OnSetfocusInhdepth();
	afx_msg void OnGougecheck();
	afx_msg void OnOk();
	afx_msg void OnG92off();
	afx_msg void OnOriginsoff();
	afx_msg void OnTooloffsetoff();
	afx_msg void OnRadiuscompoff();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_DwellMilli;
	int m_IndexDebounce;
	BOOL m_AutoTool;
	afx_msg void OnBnClickedToolauto();
	BOOL m_ZInhPersist;
	BOOL m_OVPersist;
	afx_msg void OnBnClickedLaserpwm();
	BOOL m_Plasma;
	BOOL Angular;
	afx_msg void OnBnClickedSounds();
	BOOL m_Sounds;
	afx_msg void OnBnClickedCheck4();
	BOOL m_Speech;
	BOOL m_LaserStand;
	BOOL m_UseSafeZ;
	BOOL m_Flash;
	afx_msg void OnBnClickedDromemory();
	BOOL m_TPersist;
	afx_msg void OnBnClickedConstant();
	afx_msg void OnBnClickedExactstop();
	afx_msg void OnBnClickedIjmode();
	afx_msg void OnBnClickedIjmode1();
	afx_msg void OnBnClickedDistancemode();
	afx_msg void OnBnClickedIncremental();
	afx_msg void OnBnClickedPlane();
	afx_msg void OnBnClickedYz();
	afx_msg void OnBnClickedXz();
	double CV_Dist;
	BOOL m_SpinOff;
	int m_SpinInc;
	BOOL m_UseCVAngle;
	double m_CVAngleDeg;
	int SpinInc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGICCONTROL_H__1F775D73_D31B_4DD8_8A19_573E4B0D2008__INCLUDED_)
