// _Mach4View.h - replace class with struct
//

#pragma once

#include "_MFC.h" 

struct _bdata
{
	LPCSTR	Name;
	LPCSTR	Date;
    bool	Timeout;
	bool	Dxf;
    bool	Hpgl;
	bool	Jpg;
	LPCSTR	Test;
};
   
#define DELETE_SCREW 10325

struct _CMach4View
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	int		m_dwRef;				// CWnd public data
	BYTE	_fillCWnd1[0x14];		// fill to replace private CWnd data
	HWND	m_hWnd;					// only published CWnd data
	BYTE	_fillCWnd2[0x14];		// fill to replace private CWnd data
	HWND	m_hWndOwner;			// CWnd public data
	int		m_nFlags;				// Cwnd public data
	BYTE	_fillCWnd3[0x14];		// fill to replace private CWnd data
	BYTE	_fillCView[0x04];		// fill to replace private CView data

	bool	m_Selection;			// Is an input control selected?
	int		selpos;
	int		nControls;
	int		nHotControls;
	int		CurrentTab;
	int		Tabs[100];
	int		numgroups;
	char	trawdata[210];
	char	trawdata2[210];

    _bdata				Block;
	_bdata				Block2;

	bool	Stable;						// Was engine stable on last run
	OVERLAPPED	ov;						// for overlapped IO
	TimeData	Info;					// for timing info
	HANDLE	hEvent;
    unsigned long	cpuSpeed;			// CPU speed
	int		m_Units;					// default setup units
	double	En0_nSteps, En1_nSteps, En2_nSteps;
	bool	RemoteHandle;
	HWND	Remhandle;					// remotely set handle
    bool	FilePres, mConverse;		// file protection string
	char	LicData[1024];
	LPCSTR	rName;
    LPCSTR	LoadedScreen;
	char	acrData[200];
	char	acrData2[200];
	bool	AutoLoadAddon;
	LPCSTR	tempstring;
	bool	JogAllowed[100];
	bool	External;
    void	*addons;					// original AddonDlg
	double	OEMDROs[255];
	bool	OEMLeds[255];
	LPCSTR	Tickers[255];
	bool	LoadCode; 
	bool	ScreenAuto;
	bool	LockedUp;
	double	m_cxMax, m_cxMin, m_cyMax, m_cyMin;
//PlugIn variables.
	bool	m_PrinterOn;
	bool	*m_ShiftState;
	bool	*m_CtrlState;
	_CFrameWnd	*MachFrame;
	int		LocTest;
    bool	NormalScreen;	
	HWND	FlashWnd;
	void	*flash;						// original IShockwaveFlash
	bool	FlashAvailable;
	bool	FlashLoaded;
	void	*FlashWindow;				// original FlashView
	bool	Protected;
	LPCSTR	sPassword;
	HANDLE	ClickRes;
	LPSTR	lpClick;
	LPCSTR	runtime;
	LPCSTR	esttime;

	void	*memdc;						// original CMemDC
	_CWnd	plugin;						// original PlugInManager

	COLORREF BackColor;

	_CBrush				BackBrush;
    _TrajectoryControl	Planner;
	_CObList			m_listCtrls;

	// original all pointers to CControlRect - need to do
    void *m_Controls[2000]; // array of controls
	void *m_HotKeys[2000];  // array of hot-keyed controls
	void *Selection;        // Selected Control

    bool	Calculators;
	int		tripmenu;
	int		Slave0, Slave1, Slave2;
	bool	StanScreen;

	__int64  lic;
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
