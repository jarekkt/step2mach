// Mach4View.h : interface of the CMach4View class
//

#include "ControlRect.h" //to allow all the other classes to get their definitions here
#include "Afxtempl.h"
#include "xmlprofile.h"
#include "engine.h"
#include "trajectoryControl.h"
#include "Addondlg.h"
#include "circinterp.h"
#include "memdc.h"
#include "PluginManager.h"
#include "TitleTip.h"
#include "flashview.h"

 

#import  "PROGID:ShockwaveFlash.ShockwaveFlash" no_namespace raw_interfaces_only

typedef  char*  (_cdecl *stringfunc)(int string);


struct bdata
{
 CString Name;
 CString Date;
 bool    Timeout;
 bool    Dxf;
 bool    Hpgl;
 bool    Jpg;
 CString Test;
};

   
#define DELETE_SCREW 10325


#pragma once



class CMach4View : public CView
{
 

public:
	bool m_Selection;  // Is an input control selected?
	int  selpos;
	int  nControls;
	int  nHotControls;
	int  CurrentTab;
	int  Tabs[100];
	int  numgroups;
	char trawdata[210];
	char trawdata2[210];
    bdata   Block;
	bdata   Block2;
	bool Stable;        // Was engine stable on last run
	OVERLAPPED ov;      // for overlapped IO
	TimeData     Info;  // for timing info
	HANDLE hEvent;
    unsigned long    cpuSpeed;    // CPU speed
	int    m_Units;     // default setup units
	double En0_nSteps,En1_nSteps,En2_nSteps;
	bool     RemoteHandle;
	HWND     Remhandle;   // remotely set handle
    bool     FilePres,mConverse;   // file protection string
	char     LicData[1024];
	CString  rName;
    CString  LoadedScreen;
	char acrData[200];
	char acrData2[200];
	bool AutoLoadAddon;
	CString  tempstring;
	bool   JogAllowed[100];
	bool   External;
    AddonDlg *addons;
	double  OEMDROs[255];
	bool    OEMLeds[255];
	CString Tickers[255];
	bool    LoadCode; 
	bool ScreenAuto;
	bool LockedUp;
   double m_cxMax,m_cxMin,m_cyMax,m_cyMin;
//PlugIn variables.
	bool m_PrinterOn;
	bool *m_ShiftState;
	bool *m_CtrlState;
	CFrameWnd *MachFrame;
	int           LocTest;
    bool          NormalScreen;	
	HWND          FlashWnd;
	IShockwaveFlash* flash;
	bool          FlashAvailable;
	bool          FlashLoaded;
	FlashView     *FlashWindow;
	bool          Protected;
	CString       sPassword;
	HANDLE        ClickRes;
	LPSTR         lpClick;
	CString      runtime;
	CString      esttime;
	
	

//all position sensitive. Keep vars above..//////////////////////////////////////////////////////////
protected: // create from serialization only
	CMach4View();
	DECLARE_DYNCREATE(CMach4View)

// Attributes
public: //from the ocx
	 CMemDC  *memdc;
	PlugInManager plugin;
	COLORREF BackColor;
	CBrush BackBrush;
    TrajectoryControl  Planner;
	CObList  m_listCtrls;
	LRESULT  DoHelpIt(WPARAM /*wParam*/, LPARAM /*lParam*/);
	LRESULT  DoDeferredStart(WPARAM /*wParam*/, LPARAM /*lParam*/);
	LRESULT  DeleteScrew(WPARAM /*wParam*/, LPARAM /*lParam*/);
    CControlRect *m_Controls[2000]; // array of controls
	CControlRect *m_HotKeys[2000];  // array of hot-keyed controls
	CControlRect *Selection;                           // Selected Control
    bool          Calculators;
	int          tripmenu;
	int          Slave0,Slave1,Slave2;
	bool         StanScreen;
	
 
    	
// Operations
public: //from the ocx.
	
	BOOL LoadLayout(CString FileName) ;
	void Lock( bool Lock );
	void CloseXML();
	void OpenXML();
	void SetHotKeysOn();
	void SetHotKeysOff();
	void ConfigureEngine();
	void OnAllocate();
	BOOL StopEngine();
	void GetFileName( CString &path);
	void SelectionMDICalled();
	void CalcTabs();
	void SortTabs();
	bool included( int*vects, int check, int nItems);
	void NextGroup();
	void PreviousGroup();
	void PreviousSelection();
	void NextSelection();
	bool SelectionType( int key );
	void SelectionCalled(int type );
	BOOL StartEngine();
	void ShowGroup();
	void CreateAll();
	void CheckCirc( char* Pass );
	void CheckCirc2( char* Pass );
	void CheckCirc3( char* Pass );
	void CircInterp( CString Pass);
	void CircInterp2( CString Pass); //wizlic
	void CircInterp3( CString Pass); //g100
	void JPeg();
	void SetupBacklash();
	void CalculateEncoderVars();
	void CalEncoders();
	void UnHookKeys(); 
	void UpdateLoop();
	void ResizeControls( CControlRect* );
    BOOL CMach4View::InitEngine() ;
	void CMach4View::HookKeys();
	void ShowGroupZero(void);
	void CloseLayout( void);
	void CheckForAddons(void);
    void LoadAddon(void);
	void LoadDefLayout(CString screen );
	SHORT GetnToolpathOps(void);
	VARIANT GetOperation(SHORT nOperation);
	void Offline(SHORT state);
	void ConfigToolPath(void);
	void Regen(void);
	void SelectionListCalled();
	void LoadNoRun(LPCTSTR name);
	DOUBLE GetParam(LPCTSTR param);
	void CalSpindle(void);
	void Maintain(void);
	void Formulas(void);
	void ScrewMap(void);
	LRESULT LoadDefaultLayout(WPARAM /*wParam*/, LPARAM /*lParam*/);
	LRESULT LoadGCodeMessage(WPARAM /*wParam*/, LPARAM /*lParam*/);
	LRESULT LoadAddonButton(WPARAM /*wParam*/, LPARAM /*lParam*/);
	bool    CheckTime();
	bool    CheckTime2();
	bool    SetLog();
	void    MenuOn();
	void    MenuOff();
    void    CheckSer();
	void    FlushSettings();

	LRESULT OnViewVideoScript(WPARAM /*wParam*/, LPARAM /*lParam*/);

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMach4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFileNew();
protected:
	virtual void OnDraw(CDC* /*pDC*/);
public:
	 
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLoadgcode();
	afx_msg void OnImporthpgl();
	afx_msg void OnImportdxf();
	afx_msg void OnClosefile();
	afx_msg void OnSetnative();
	afx_msg void OnPortspins();
	afx_msg void OnHominglimits();
	afx_msg void OnSlave();
	afx_msg void OnSethotkeys();
	afx_msg void OnTunemotor();
	afx_msg void OnBacklash();
	afx_msg void OnToolpath();
	afx_msg void OnLogic();
	afx_msg void OnState();
	afx_msg void OnLoadscreens();
	afx_msg void OnRegen();
	afx_msg void OnPickwizard();
	afx_msg void OnOffline();
	afx_msg void OnLock();
	afx_msg void OnUnlock();
	afx_msg void OnMacros();
	afx_msg void OnFixtures();
	afx_msg void OnTooltable();
	afx_msg void OnSpincal();
	afx_msg void OnScrewmap();
	afx_msg void OnFormulas();
	afx_msg void OnMaintenance();
	afx_msg void OnAbout();
	afx_msg void OnArtsoft();
	afx_msg void OnExit();
	BOOL CMach4View::LoadGCode() ;
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnUpdateOffline(CCmdUI *pCmdUI);
	void ShowRight(void);
	void TogglePanel(void);
	afx_msg void OnOperatorCalibratempg();
	afx_msg void OnOperatorModbuscontrol();
	afx_msg void OnOperatorTCPModbuscontrol();
	afx_msg void OnHelpEmailsupportrequest();
	afx_msg void OnConfigSerialmonitor();
	void StoreLayout(void);
	afx_msg void OnViewSavecurrentlayout();
	afx_msg void OnFileDxfturnimport();
	afx_msg void OnViewVideowindow();
	afx_msg void OnConfigFonts();
	afx_msg void OnHelpWww32894();
	afx_msg void OnConfigEditbutotnscript();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnConfigCheckconfig();
	afx_msg void OnConfigModbusconfig();
	afx_msg void OnOperatorConfigplugins();
	afx_msg void OnConfigGeneralmodbusconfig();
	void SU(void);
	afx_msg void OnConfigResetdevicesel();
	afx_msg void OnConfigSpindlepulleys();
	afx_msg void OnConfigSafe();
	afx_msg void OnOperatorAuto();
	afx_msg void OnUpdateOperatorAuto(CCmdUI *pCmdUI);
	afx_msg void OnOperatorSetnormalcondition();
	bool AttachFlash(void);
	bool DetachFlash(void);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnViewManualencoderdroscreen();
	afx_msg void OnViewDefaultmotorcontrolscreen();
	afx_msg void OnOperatorRestoresettings();

	__int64  lic;
	

	afx_msg void OnOperatorBraincontrol();
};
#define WM_LOADDEF 10321
#define WM_LOADPROGRAM 10322
#define WM_RUNTHEHELP  10323
#define WM_LOADADDON   10324
#define DELETE_SCREW   10325
#define WM_DEFERRED    10326

/////init of the driver code..

#define MACH1_SUCCESS         0
#define MACH1_ERROR_MEMORY   21
#define MACH1_ERROR_NOTIMER   22
#define MACH1_ERROR_ALREADYON  1
#define MACH1_ERROR_NOIDT      2
#define MACH1_ERROR_NOVECTORS  3
#define MACH1_ERROR_NOFREEVECT 4
#define MACH1_ERROR_NOGDT      5
#define MACH1_ERROR_NOLIDT     6

#define	IOCTL_INBUF_SIZE	512
#define	IOCTL_OUTBUF_SIZE	512
#define MACH1_PREPTIMER  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define MACH1_STOPTIMER  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define MACH1_GETCOUNT   CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define MACH1_GETMAXTIME CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define MACH1_GETMINTIME CTL_CODE(FILE_DEVICE_UNKNOWN, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define MACH1_STARTTIMER CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)


// control code for iocontrol calls	for Master5 operations

#define  SOFT_GET_STATUS        CTL_CODE(FILE_DEVICE_UNKNOWN, 0x806, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_CONTROL_OUT       CTL_CODE(FILE_DEVICE_UNKNOWN, 0x807, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_SET_FREQUENCY     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x808, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_ACTIVATE          CTL_CODE(FILE_DEVICE_UNKNOWN, 0x809, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_GET_TIMES         CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80a, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_GET_DATA          CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80b, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_ADD_TO_BUFFER     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80c, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_GET_LOADINDEX     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80d, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_GET_CONTROLINDEX  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80e, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_SET_PORT          CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80f, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_LOAD_MASKS        CTL_CODE(FILE_DEVICE_UNKNOWN, 0x810, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_GET_ACTIVE        CTL_CODE(FILE_DEVICE_UNKNOWN, 0x811, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_GETINDEXS         CTL_CODE(FILE_DEVICE_UNKNOWN, 0x812, METHOD_BUFFERED, FILE_ANY_ACCESS) 
#define  SOFT_SETREVERSALS      CTL_CODE(FILE_DEVICE_UNKNOWN, 0x813, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_CONTROL_IN        CTL_CODE(FILE_DEVICE_UNKNOWN, 0x814, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_CONTROL_JOGON     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x815, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_CONTROL_JOGOFF    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x816, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_SETNEGS           CTL_CODE(FILE_DEVICE_UNKNOWN, 0x817, METHOD_BUFFERED, FILE_ANY_ACCESS) 
#define  SOFT_GETIDLE           CTL_CODE(FILE_DEVICE_UNKNOWN, 0x818, METHOD_BUFFERED, FILE_ANY_ACCESS) 
#define  SOFT_EMERGENCY         CTL_CODE(FILE_DEVICE_UNKNOWN, 0x819, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_OVERRIDE          CTL_CODE(FILE_DEVICE_UNKNOWN, 0x81a, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_GOHOME            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x81b, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_PAUSE             CTL_CODE(FILE_DEVICE_UNKNOWN, 0x81c, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_HALT              CTL_CODE(FILE_DEVICE_UNKNOWN, 0x81d, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_LASER             CTL_CODE(FILE_DEVICE_UNKNOWN, 0x81e, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_SPACE             CTL_CODE(FILE_DEVICE_UNKNOWN, 0x81f, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_GATE              CTL_CODE(FILE_DEVICE_UNKNOWN, 0x820, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  SOFT_ALLOCATE_BUFF    	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x821, METHOD_OUT_DIRECT,FILE_ANY_ACCESS)
#define  SOFT_SAMPLE_BUFF    	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x822, METHOD_OUT_DIRECT,FILE_ANY_ACCESS)
#define  SOFT_SAMPLE_ON         CTL_CODE(FILE_DEVICE_UNKNOWN, 0x823, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  MACH1_RELEASEBUFFERS   CTL_CODE(FILE_DEVICE_UNKNOWN, 0x824, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define  MACH1_DRIVERVERSION	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x825, METHOD_BUFFERED, FILE_ANY_ACCESS)

#ifndef _DEBUG  // debug version in Mach4View.cpp
//inline CMach4Doc* CMach4View::GetDocument() const
//   { return reinterpret_cast<CMach4Doc*>(m_pDocument); }
#endif


