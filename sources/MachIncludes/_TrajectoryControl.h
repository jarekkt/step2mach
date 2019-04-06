//=====================================================================
//
//	_TrajectoryControl.h
//
//		this is a converted struct to replace the TrajectoryControl class
//		contained in TrajectoryControl.h.
//
//		version 1.0 - 3 aug 2008
//
//		created by j1sys to make _TrajectoryControl a struct to be more
//		portable across compilers. all data objects are either simple
//		objects (int, double, etc.) or structs containing only simple
//		objects.
//
//		also reduced other #include statement to minimal list
//
//=====================================================================

#pragma once

#include "_MFC.h"		// new include for MFC replacements
#include "_Traj.h"		// a modified Traj.h

#include "_ToolCabinet.h"
#include "_Mach1Button.h"
#include "_SpindleFM.h"
#include "_MPGControl.h"
#include "_ScrewMapCurve.h"
#include "_FixtureCabinet.h"
#include "_Normals.h"

#include "_TrajectoryStructs.h"

struct _LEDConditions
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	int		m_dwRef;				// CWnd public data
	BYTE	_fillCWnd1[0x14];		// fill to replace private CWnd data
	HWND	m_hWnd;					// only published CWnd data
	BYTE	_fillCWnd2[0x14];		// fill to replace private CWnd data
	HWND	m_hWndOwner;			// CWnd public data
	int		m_nFlags;				// Cwnd public data
	BYTE	_fillCWnd3[0x14];		// fill to replace private CWnd data

};

struct _DROValues
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	int		m_dwRef;				// CWnd public data
	BYTE	_fillCWnd1[0x14];		// fill to replace private CWnd data
	HWND	m_hWnd;					// only published CWnd data
	BYTE	_fillCWnd2[0x14];		// fill to replace private CWnd data
	HWND	m_hWndOwner;			// CWnd public data
	int		m_nFlags;				// Cwnd public data
	BYTE	_fillCWnd3[0x14];		// fill to replace private CWnd data

};

struct _GenSocket
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	HANDLE	m_hSocket;
};

struct _PathProgress
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	int		m_dwRef;				// CWnd public data
	BYTE	_fillCWnd1[0x14];		// fill to replace private CWnd data
	HWND	m_hWnd;					// only published CWnd data
	BYTE	_fillCWnd2[0x14];		// fill to replace private CWnd data
	HWND	m_hWndOwner;			// CWnd public data
	int		m_nFlags;				// Cwnd public data
	BYTE	_fillCWnd3[0x14];		// fill to replace private CWnd data
	BYTE	_fillCDialog[0x20];		// fill to replace private CDialog data
	BYTE	_fillPathProgress[0x50];// fill to replace PathProgress control
};

struct	_BrainHandler
{
	_CArray			Brains;			// replace class - original template - CArray < Brain*, Brain*> Brains;
};

//---------------------------------------------------------------------
//
//	struct _TrajectoryControl - the actual shared memory block
//
//		all classes have been replaced by structs.
//
//		all impure structs (containg non-simple members) have been
//		replaced by pure structs.
//
//		whenever a replacement has been made the replacement is
//		the same name as the old object with a '_' prepended to
//		the name.
//
//		all CString have been replaced with LPCSTR.
//
//		column location of all object names have been normalized. all
//		simple object names start in column 13. all complex object
//		names start in column 25. comments have been added to describe
//		the alterations. as time allows comments will be added to
//		more fully define the members.
//
//		_TrajectoryControl is 2,800,816 bytes long. that is the first
//		thing to check when porting to other compilers/versions.
//
//---------------------------------------------------------------------


struct _TrajectoryControl
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	int		m_dwRef;				// CWnd public data
	BYTE	_fillCWnd1[0x14];		// fill to replace private CWnd data
	HWND	m_hWnd;					// only published CWnd data
	BYTE	_fillCWnd2[0x14];		// fill to replace private CWnd data
	HWND	m_hWndOwner;			// CWnd public data
	int		m_nFlags;				// Cwnd public data
	BYTE	_fillCWnd3[0x14];		// fill to replace private CWnd data

	_Traj				trajectory;			// _Traj struct - replaces Traj class

	short	HomannSlave;
	_int64	GeckoPos[6];
	bool	TPersist;
	bool	m_RevArc;

	_Traj				Tooltraj;			// _Traj struct - replaces Traj class

	double	RexRateDRO, RexRateTemp;
	bool	RexRateTrigger;

	int		PosChange[6];
	double	FrontToRear;
	double	LastPositions[6];
	double	FrontXOffS;
	double	FrontXOffE;
	double	ThreadParm[6];
    bool	RapidOverRide;
	double	RapidFeedrate;
	double	nextradius;
	int		nextside;
	bool	RegenNeeded;
	bool	DROBack;
	int		nextindex;

	ProgData			rundata;			// pure struct

	LPCSTR				DROFont;			// CString replacement
	LPCSTR				CodeFont;			// CString replacement
	LPCSTR				LabelFont;			// CString replacement

	bool	JOGPINS[8];

	LPCSTR				SlabIP;				// CString replacement

	double	DiffX, DiffY, DiffZ; //offset differentials..
	double	DiffA, DiffB, DiffC;

	_CommandBuffer		BCommands;			// _ struct - replaces impure struct

    bool	m_HWSafe;
	int		M3;

	//laser variables.

	bool	HotKeysPersist;
	int		m_LookAhead;
	bool	WatchHold;
	int		LaserPort;
	int		Serial;
	int		m_ServoSerial;
	int		LaserBaud;
    int		LaserStops;
    int		LaserData;
	int		Timers[25];

    LPCSTR				LaserInit;			// CString replacement
    LPCSTR				LaserCommand;		// CString replacement

	// end of laser vars

	bool	IsPanel;
	double	MPGFeed;
	double	TempFeed;
	bool	PlasmaHome;
	bool	m_UDP;

	LPCSTR				NextSub;			// CString replacement
	_ProgramState		returns[1000];		// _ struct - replaces impure struct

	_ToolCabinet		Tools;				// _ struct - replace class / impure struct

	double	RefCounts[6];
	double	m_Seconds;
	double	MinPerPass;
	bool	InCycle;
	bool	HommanHolding;
	bool	OverRideMode2;
	int		PanelOut;

	__time64_t			SinceOn;			// just a guess - 8 bytes - replace class CTime

	bool	m_PathBoxed;
	bool	m_Plane;
	double	AxisDist[6];

	Executions			BackBuffer;			// pure struct

	int		BackHead, BackTail;
    double	FeedRate;                       //feedrate velocity;

	ModBusRedir			ModCouple;			// pure struct

	bool	ChangeScreens;
    int		Units;
	double	FeedInc; 
	double	ToolPostOffset;
	double	StepsPerAxis[6];
	double	Velocities[6];
	double	Acceleration[6];
	double	Corrections[6];

	GeckoBuf			GeckoBuffer[4096];	// pure struct
    Commands			CommandBuffer;		// pure struct

	int		history[6];
	int		load;
	bool	m_ZInhPersist;
	bool	TangentalControl;
	bool	AutoScreens;
	bool	skiptan;
	double	LiftAngle;
	double	LiftLevel;
	bool	m_OVPersist;
	bool	m_AutoSpindle;
	bool	ToolFlip;

	_CMemMapFile		GCodeFile;			// _ struct - replace class
	_CMemMapFile		DisplayComs;		// _ struct - replace class
	_CFile				BackBufferFile;		// _ struct - replace class

	bool	BufferFileOpen;
	bool	m_Loaded;
	LPVOID	GCodeData;
	int		*GLines;
	int		Lines;

	LPCSTR				m_FileName;			// CString replacement

	int		TermMode;
	bool	configured;
	bool	pathconfig;
    double	OrigSpindleSpeed;
	bool	m_Flash;
	bool	g_ZInhibit;
    double	g_ZInhDepth;
	bool	m_ToolChange;
	double	m_SafeZ, m_SafeZO;
	bool	m_ToolIgnore;
	int		SetupUnits;
	double	nStepsStore[6];
	double	VelStore[6];
	double	AccStore[6];
	int		unitscommand;
	double	OffsetLength;
	int		Tool;
	double	NextFeed;
	bool	FeedTrigger;
	bool	OriginTrigger;
	bool	MacroTrigger;
	bool	DwellTrigger;
	bool	ProbeTrigger;
	double	m_ByPassFeed;
	bool	ByPassFeedOn;
	int		DwellAmount;
	int		macro;
	double	VelLimit;
	bool	AAng, BAng, CAng;
	double	rpm;
	bool	Simulating;
 	bool	ArcTest;
	int		FeedID, OriginID, ToolID, UnitID, LengthID, DwellID, SpinID, MacroID, ProbeID;
    int		SpinVelPerRPM;
	int		SpinAcc;
    int		lines;  // current translation line while loading

    Subs				oSubroutines[100]; //unused padding..	// pure struct

	int		nSubs;
    int		nReturns;
	double	THCSpeed;
	double	THCCurrent;
	double	THCMax;
    double	THCMin;
	double	PlungePercent;
	bool	PWMLaser;
	int		full_circle_in_active_plane;
	double	radius;
    bool	ModBusOn;
	bool	OverRide;
	bool	m_MacroPump;
	double	Estimate;
	bool	SimDone;
	double	simx, simy, simz, sima, simb, simc;
	double	MacroP1, MacroP2, MacroP3;
	int		RefSpeed[6];
	int		Vels[6], Accs[6];
	bool	AxisNegs[6];
	int		References[6];
	double	Returns[6];
	bool	SingleVerify;
	int		SingleAxis;
	int		tempExec;
	bool	Silence;
	bool	Stage2Trigger, Stage3Trigger;
	bool	LastAutoZero[6];
	int		ProbeAction;
	double	ProbeGoto;
	double	ProbeX, ProbeY, ProbeZ, ProbeA, ProbeB, ProbeC;
	bool	DigFileOpen;

	_CStdioFile			digfile;			// _ struct - replace class

	double	RadiusA, RadiusB, RadiusC; // distance per 1 degree of angular movement
    double	m_Increment;
	int		AxisKeys[12];
	int		m_DROCode;    //hot key for DRO selection;
	int		m_MDICode;    //hot key for MDI selection;
	int		m_GCode;      // hotkey for GCODE selection
	int		m_ListKey;     // hotkey for GCode display
	bool	m_ExcludeZ;
    bool	m_JoyOn; 
	bool	m_Linear;
	bool	MDIMove;
	double	m_IncFeed;
	int		Platform; 
	bool	Homeing;
	bool	Jogging;
    bool	CustomIncremental;
    bool	SoftLimitHold;

	ComBuf				CannonBuffer;		// pure struct

	bool	m_Virtual;

	LPCSTR				LastError;			// CString replacement

	int		Line;
	int		name, repeat; //for subroutines.
	bool	FileFinished;
	int		LastPress;
	double	OVMaxVel;
	int		PausedFrom;
	bool	Follow;
	int		EStopCause;
	bool	CommandWaiting;
	bool	m_DisplayMachineCoord;
	double	FeedOverRide;
	double	tFeedOverRide;
	double	JogSlideIncr;
	bool	ConstantVolume;
	bool	PathGenerate;
	int		toolpath;
	bool	PathLoaded;
	double	m_CPULoad;

	LPCSTR				LastFile;			// CString replacement

	bool	Threading;
	double	CycleInts[10];
	bool	ErrorClear;
	bool	AutoRun;
    int		EncJogAxis;
	double	RatioTaper;
	bool	TaperMode;
	bool	DualMPG;
	int		EncJogAxis2;
	int		EncJogAxis3;
	int		LastEncJogCount;
	int		CurrentEncJogCount;
	int		LastEncJogCount2;
	int		CurrentEncJogCount2;
	bool	m_Z25D;
	bool	BlockDelete;
	bool	m_AutoTool;
	int		OldTool;
	bool	OnFeed;

	_CFile				*ErrorFile;				// _ struct - replace class - it is a pointer!!
	_CArchive			*Errors;				// _ struct - replace class - it is a pointer!!

	double	OEMDROs[256];
	bool	OEMLeds[256];

	LPCSTR				Tickers[256];			// CString replacement
	LPCSTR				UserLabels[256];		// CString replacement

    bool	ErrorsOpen;
	int		ScriptsRunning;
    bool	TeachFileOpen;
	double	LaserMaxSpin;

	_CStdioFile			TeachFileFile;			// _ struct - replace class
	LPCSTR				TeachFileName;			// CString replacement

	bool	SingleAxisVerify;
	int		nSingleAxisVerify;
	bool	MaxCLMode;
	bool	Regening;
    int		RegenLine;

	EmcPose				whereold;				// pure struct

	bool	Dig4Axis;
	int		SerialType;
	bool	RunAt;
	bool	DigLetter;
	bool	filestart; //for the backbuffer initialization.
	bool	DelayedReset[6];
	int		ResetTimer;
	bool	OrigXDir;
	bool	FrontPost;
	int		m_OEMRegNum;
	bool	m_OEMRegOn;
	int		VelMode;
	double	VelPer1, VelPer2, VelPer3;
	double	m_RealVelocity[7];
	double	m_RealAccel[7];
	double	m_G20X;
	double	m_G20Y;
	double	m_G20Z;
	double	m_G20A;
	double	m_G20B;
	double	m_G20C;
    bool	m_Rot360;

	LPCSTR				ProgramDir;			// CString replacement
	LPCSTR				ThisProfile;		// CString replacement

	double	m_ToGo[6];
	bool	ToGo;

    _LEDConditions		LEDBool;			// _ struct - replace class - NO DATA?
	_DROValues			DROS;				// _ struct - replace class - NO DATA?

	_GenSocket			UDPIO;				// _ struct - replace class

	int		EncoderZeros[6];
	
	AxisDDA				AllDDA[6];			// pure struct
	 
	bool	m_ShortRot;

	LPCSTR				m_Init;				// CString replacement

	bool	m_InitAllResets;
	double	BackOffsetx, BackOffsety, BackOffsetz, BackOffseta, BackOffsetb, BackOffsetc;
	double	BackToolZ, BackToolX;

	//////////////////////////////////
	//   Values for DRO's
	/////////////////////////////
	double	XPosition;
	double	YPosition;
	double	ZPosition;
	double	APosition;
	double	BPosition;
	double	CPosition;
	double	MXPosition, MYPosition, MZPosition;
    double	MAPosition, MBPosition, MCPosition;

	double	XVel, YVel, ZVel, AVel, BVel, CVel, BlendVel;
	double	JogFeedRate;

	double	Maxs[6];
	double	Mins[6];

	PmCartesian				dummy; // for addtobuffer	// pure struct

	double	feedtemp;
	bool	CancelPath;

	_PathProgress			*progress;		// _ struct - replace class - it is a pointer

	bool	LastMoveRapid;
 
	double	RefPoints[6];
	int		OldState;
 	bool	MillMode;
	double	MachPositions[6]; //machine coordinates of first three axis

	double	SlowPoints[6];
    double	m_SoftMaxs[6];
	double	m_SoftMins[6];

	double	SlowPointsO[6];
    double	m_SoftMaxsO[6];
	double	m_SoftMinsO[6];
	
	bool	ToolPathOn;
	double	LatheCorrection;
	double	Diameter;
	bool	RunInReverse;

	bool	m_DroLock;

	double	Throttle;
	int		ThrottleFunc;

	int		simcount;

	double	cpuSpeed;
    bool	CorrectionOn;
	bool	AutoLimitOverRide;

	bool	SetSkip;  // skip the softlimits setup on Ref All from G-Code
	int		refaxis;

	bool	SingleTriggerOn;
	bool	SingleActive4On;

	bool	ConditionRapid;
	bool	CurveLoaded;

	int		MaxFeedOverRide;
	double	thcmax;
	double	thcmin;
	bool	SpinActual;

	double	m_BB, m_BR, m_BG, m_RB, m_RG, m_RR, m_FB, m_FR, m_FG, m_AR, m_AB, m_AG,
			m_EG, m_EB, m_ER;
	int		BaudRate, ComPort;
	int		EntranceAngle;
	int		m_PWMin;
	double	RotError;
	int		SpinInc;

	bool	m_XMapOn, m_YMapOn, m_ZMapOn;

	double	LaserXGrid;
	double	LaserAGrid;
	double	LaserYGrid;
	int		LaserYOff;
	int		LaserXOff;
	int		LaserAOff;

	int		m_UseCR;

    LPCSTR				m_Char;				// CString replacement

	bool	m_SLS;
	double	Repeats;
	double	ZInhibInc;
	double	SLSDist;
	int		LastMode;

	bool	MacroRunning;

    bool	DwellMilli;
    double	NextZLength, NextXLength;
	bool	OEMTriggers[15];
	
    _Mach1Button		OEMButton;			// _ struct - replace class

	short	OEMPins[15];

	bool	UseSwitches;
	double	PWMMaxSpeed;
   
	bool	DoRegen;
	bool	m_Homann;

	//Toolpath variables for display
	BOOL	m_OriginSphere;
	BOOL	m_3dCompass;

	LPCSTR				HomannString;		// CString replacement

	short	HomannLoc;
	bool	m_BitPack1;
	int		m_BitPack1Reg;
	bool	m_BitPackOut1;
	int		m_BitPackOutReg1;
	BOOL	m_Boundries;
	BOOL	m_ToolPosition;
	BOOL	m_AParallel;
	double	m_AtoXOff;
	double	m_AtoYOff;
	double	m_AtoZOff;
	//Threading Variables for defaults...
    int		nAddons;

	_AddStruct			AddonNames[200];	// _ struct - replace impure struct

	int		AddonSelected;
    bool	LoadAddon;

	LPCSTR				Addon2Load;			// CString replacement
	LPCSTR				Init2Load;			// CString replacement

	bool	AddonReady;;
	bool	AddonLoaded;
	bool	AutoRegen;
	bool	SoundsOn;
	bool	VoiceOn;
	bool	SingleStepMode;
	bool	EditLoad;
	bool	JogActive;
    bool	m_Arots;

    _NextLine			AfterPause;

	bool	HeldInReverse;
	bool	LastMovePartial;
	
    LPCSTR				defaultscreen;		// CString replacement

	bool	LoadScreen;
	int		ActiveGroup;
	int		LastActiveGroup;
	int		JogMode;
	 
	bool	KeepRef;
	bool	Speech;
	bool	HelpContext;
	bool	LastSpeech;
	bool	MovingAverageDone;
	bool	MovingAverageOn;
	 
	bool	JogPersist;
	bool	SaveWizard;

	double	StepsX, StepsY, StepsZ, StepsA, StepsB, StepsC;

	double	loadToolXOff;
	double	loadToolZOff;
	int		loadSlot;
	bool	ToolDirty, FixDirty;
	bool	PersistOffsets, OffsetsDialog;
    bool	G54Back;

	_SpindleFM			Spindle;
	_MPGControl			MPG;

	bool	JogVelocity;
	bool	LastVelJog;
	double	m_DepthLastPass;
	double	m_InFeed;
	double	m_Spring;
	double	m_MinDepth;
	double	m_XClear;
	double	m_ZClear;
	double	m_CutDepth;
	double	m_Chamfer;
	double	m_DepthFirstPass;
    int		ReversalLine;
	bool	MidLine;
	bool	UnReversed;
	bool	SkipProgress;
	double	StockSize;
	bool	ShowSolid;
	double	LastLineFeed, LastArcFeed;

	double	TurnMatR;
    double	TurnMatG;
	double	TurnMatB;
 
	_ScrewMapCurve		XCurve, YCurve, ZCurve;
    LPVOID				screw;					// pointer to a CDialog with LOTS of stuff - ScewMap *screw;

	int		m_IncJogBuffer;
	bool	OEMDualTemp;
	bool	RunPlus;
	bool	RunMinus; //these two are for runnign forward and back buttons.
    bool	LaserStandby;
	bool	ResetInit;
	bool	LastRunBackward;
	int		LastLineExec;

    EmcPose				SyncWhere;			// pure struct

	bool	FeedHolding;
	bool	NoPartial;
	bool	m_PlasmaMode;
	bool	m_UseSafeZ;
	bool	m_CompPlus;
	bool	EmergCalled;

	LPVOID	Processsor;						// pointer to a CWinThread based class - Reprocessor *Processsor;
	LPVOID	SerialRing;						// pointer to a CWinThread based class - SerialRingThread *SerialRing;

	bool	ShuttleAutoOff;

	LPCSTR				LastMacroFile;		// CString replacement
	LPCSTR				filetoload;			// CString replacement

	bool	m_TurnReverse;

	_Mach1Button			*lastbutton;	// _ struct - replace class

	bool	MPG1,MPG2;
	bool	NoGConf;
	bool	TorchVoltageControl;
	int		TorchSpeed;

    GMoves				Movements[4096];	// pure struct

	double	EncoderPos[4];
	double	TouchZ, TouchX;
	bool	FirstRev;
	double	PierceDelay;
	bool	m_WarnOnReset;
	bool	HighRes;
	bool	m_ToolLines;

    ModCon				ModBusData;			// pure struct

	bool	m_ModPlug;
	double	MB_MPGTime;
    bool	UsingModMPGs, MBHaveReading;
    bool	Polled;
    short	*ModInputs;   //ModBus variable Inputs Short[128]
    short	*ModOutputs;  //ModBus varibale OutPuts[128] 
	bool	ShutDown;
	bool	DebugRun;
	double	ExternalPulseRates[7]; //number 7 is for the spindle
	bool	ExternalStill;
    int		ELine;                 //used in triggering External Device outputs in realtime;
	bool	PurgeMovements;        //Will cause MAch3 to purge all pending movement
    int		EHead;

    Externals			EXCtrls[16];		// pure struct

    bool	ModBusCfg;

	unsigned __int64	SoftWait;

	bool	DoExternalProbe;
	int		ExternHomedMask;
	bool	MovementDone;
	double	SpindlePer;
	bool	HasRot;
	bool	m_UseDiam;
	bool	Sequence;

	//Probe Radius
	double	ProbeRad;

	PmSpherical			ProbeAngles;		// pure struct
	PmCartesian			ProbeVec;			// pure struct

	//safeZ correction
	int		m_SafeZType;
	bool	m_SafeZStop;

	int		m_UnusedBufferFill;
	bool	FlashSizing;
	short	ExternalType;

	GMoves1				MovementsAdd[4096];	// pure struct

	bool	BufferEnding;
	double	ExTime;
	int		ExBufferHi;
	bool	SkipShutdown;

	LPCSTR				MDIEntry;			// CString replacement

	bool	m_MenuOff;
	bool	m_IgnoreM3;
	bool	m_MutiHome;
	int		m_HomeMask;
	int		PartialModes[255];
	bool	SkipFeed;
	double	aProbeX, aProbeY, aProbeZ, aProbeA, aProbeB, aProbeC;
	double	PausedFeed;
	bool	TrajDone;
	bool	ExecNow;
	HANDLE	thandle;

	Subs				nSubroutines[1000];		// pure struct

	LPCSTR				ExternalMacro;			// CString replacement
	LPCSTR				lCOSYS;
	LPCSTR				lTOOLDESC;
	LPCSTR				lUNITREVMIN;
	LPCSTR				lRADDIA;
	LPCSTR				lINMM;
	LPCSTR				lMODE;
	LPCSTR				lPROFILE;
	LPCSTR				lFILE;

	bool	VBTest;
	bool	FileLoadOK;
	bool	FileSimOK;
	bool	m_ExternalFeedHold;
	int		m_Ex_Loop3Time;

	short	MasterInputs[1024];
	short	MasterOutputs[1024];
	short	UserInputs[1024];
	short	UserOutputs[1024];
	

	bool	m_ExternalPaused;
	bool	m_SpindleOn;
	short	ex_purgeflags;
    bool	G100TripSection;
	bool	ReDraw;
	int		SpinDir;
	double	RXPosition,RYPosition;
	bool	InternalJogProbe;
	double	flashsec;
	bool	ExternalFRO;

	bool	SecondPass;
	bool	ComBufferOpen;
	int		CompHead,CompTail;

	TCPModCon			TCPModBusData;		// pure struct

	LPCSTR				m_FileOnly;			// CString replacement

	_CArray				*TheBrains;			// original template - CArray<Brain*, Brain*> *TheBrains;

	int		m_nBrains;
	double	OEMDROs2[1000];
	bool	OEMLeds2[1000];
	bool	m_UsingTCPIO;
	
	_FixtureCabinet		Fix;				// _ struct - replace class - NO DATA IN CLASS?
	
	_CArray				ProbePoints;		// original template - CArray<PPoint*, PPoint*> ProbePoints;
	_CArray				MissPoints;			// original template - CArray<PPoint*, PPoint*> MissPoints;

	Extreme				ProbeEx;			// pure struct
	_Normals			NormCond;			// _ struct - replace class

	bool	IncrementCorrect;

	EmcPose				TrueCenter;			// pure struct

	bool	ForwardCheck;
	double	AbsMaxs[6];
	double	AbsMins[6];
    int		Updates;

    LPCSTR				ButtonFont;			// CString replacement

    bool	m_AbsInc;
	bool	m_SpinOff;
	int		m_SpinInc;
	bool	m_UseCVAngle;
	double	m_CVAngleDeg;
    int		precompmove;
	double	Fractions[6];
	bool	m_THC5;
	bool	KeyClick;
	double	OldFeeds[64];
	bool	donesafemove;
	bool	m_JogHeat;
	bool	DelayedJog;
	int		DelayedJogAxis;
	int		DelayedJogDir;
	bool	JogSpindleOn;

	LPCSTR				Authors[100];		// CString replacement

	bool	THCEmulInOp;
	int		SpindleDelayedOn;
	bool	m_SlaveHome;
	double	LastFeedRate;
	bool	m_RotSoft;
	double	NormCycle;

	_CMemMapFile		CompComs;			// _ struct - replace class
	_CFile				CompBufferFile;		// _ struct - replace class

	bool	SecondPassDone;
    bool	JustSave;
	bool	m_TCPModBus;
	bool	m_ZBar;

	_BrainHandler		BrainControl;		// _ struct - replace class

	double	BrainMs;

	LPCSTR				ModBusString;		// CString replacement

	bool	ModStringHolding;
	int		ModStringAddress;
	int		ModStringcfg;
	bool	m_IgnoreMs;
	double	AxisOffs[6];
	int		ProbeStepsSec;

	bool	Emailer;
};
