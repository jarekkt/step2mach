#if !defined(AFX_TRAJECTORYCONTROL_H__C8CBC326_3A49_4703_B02E_13CBC7C2848C__INCLUDED_)
#define AFX_TRAJECTORYCONTROL_H__C8CBC326_3A49_4703_B02E_13CBC7C2848C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrajectoryControl.h : header file
//

 



/////////////////////////////////////////////////////////////////////////////
// TrajectoryControl window

#include "engine.h" 
#include "memmap.h"
#include "activdbg.h"
#include "spindlefm.h"
#include "toolcabinet.h"
#include "MPGControl.h"
#include "formelParser.h"
#include "screwmapcurve.h"
#include "scewmap.H"
#include "traj.h"
#include "Reprocessor.h"
#include "SerialRingThread.h"
#include "SerialRingThread.h"
#include "MyScriptObject.h"
#include "MySplitterWnd.h"
#include "GenUDPSocket.h"
#include "LEDConditions.h"
#include "DROValues.h"
#include "fixtureCabinet.h"
#include "afxtempl.h"
#include "normals.h"
#include "Titletip.h"
#include "BrainHandler.h"
#include "brain.h"


extern CMySplitterWnd *Splitter;

#define STRAIGHTFEED       1
#define STRAIGHTTRAVERSE   2
#define SETFEEDRATE        3
#define ARCFEED            4
#define SETTRAVERSERATE    5
#define TRANSDWELL         6
#define SPINDLECW          7
#define SPINDLECCW         8
#define SPINDLEOFF         9
#define MOTIONMODE         10
#define SETUNITS           11
#define SETPLANE           12
#define CHANGETOOL         13
#define FLOODOFF           114
#define FLOODON            115
#define MISTON             116
#define MISTOFF            117
#define SPINDLESPEED       118
#define PRESLINE           119
#define HOLDLINENUMBER     120
#define OVERRIDE           121
#define REFAXISON          122
#define RADCIRCW           123
#define RADCIRCCW          124
#define STRAIGHTHREAD      125
#define SETCSSON           126
#define SETRPMON           127
#define COMPTURNOFF        128
#define COMPTURNON         129
#define DOTHREAD           130
#define PAUSECYCLEOFF      131
#define GOTOSAFE           132

//Plugin Notifications and defines..
enum { EX_DDA , EX_VMS, EX_COMMAND, EX_SPINON, EX_SPINOFF, EX_SPINSPEED, EX_MOTORTUNED 
       , EX_SETUP, EX_FEEDHOLD, EX_RUN, EX_ESTOP ,EX_CONFIG };

enum {SAFEMACHINE, SAFEWORK, SAFERISE };


#define JOGCONT 0
#define JOGINC  1
#define JOGMPG  2

struct Externals
{
   int Line;
   bool Active;
   int  Signal;
   bool State;
};

struct Extreme
{
  double px,py,pz;
  double mx,my,mz;


};

struct ModCfg
{
 short Data[128];
 char Comment[80];
 bool Enabled;
 int ModAdd; //modbus address
 int nReg;
 int Input;
 int Port;
 int Slave;
 int Refresh;
 int timref;
 int status;
 char msgstatus[40];
};

struct ModCon
{
  ModCfg cgf[65];
};

struct TCPModCfg
{
	short Data[128];
	char Comment[80];
	bool Enabled;
	int ModAdd; //modbus address
	int nReg;
	int Input;
	int Port;
	int Slave;
	int Refresh;
	int timref;
	int status;
	char msgstatus[40];
};

struct TCPModCon
{
	TCPModCfg cgf[65];
};


struct GMoves
{
 int type;    // 0 is linear, 1 is cubic
 double cx,cy,cz; // center of move for cubics. 
 double ex,ey,ez,ea,eb,ec;
 double sx,sy,sz,sa,sb,sc;
 __int64  DDA1[6]; //DDA1's for cubics
 __int64  DDA2[6];
 __int64  DDA3[6];
 double Time;
 bool   Stop;
};

struct GMoves1
{
  double diffs[6];
  double velocity;
  double accel;
  double sweep;
  double radius;
  short nx,ny,nz;
  short line;
};

struct Commands
{
  int Command[0x400];
  int LineID[0x400];
  double params[0x400];
  int nCommand; 
  int tail;
  int head;
};

struct ModBusRedir
{
  bool SpindleOn;
  int  SpindleSpeedReg;
  double SpindleCal;
};

struct Executions
{
   bool line;
   EmcPose end;
   PmCartesian center, normal;
   double rotation;
   double Arotation;
   int linenumber;
   bool rapid;
   double toolz;
   double toolx;
   double Feedrate;
   short toolnumber;
   bool  Abs;
   double comp;
};

struct ProgData
{
 int UnitType;
 double MaxX, MaxY, MaxZ, MaxA, MaxB, MaxC;
 double MinX, MinY, MinZ, MinA, MinB, MinC;

};

struct NextLine
{
 CString Block;
};

struct AddStruct
{
	CString path,name;
	bool  present;
	CString setname;

};

struct Subs
{
  int name;
  int line;
};


struct ComBuf{

int nCommands;
int    Commands[10000];
double Params[40000];
int    nParams;
int    LastParam;
int LastCommand;

}; 

struct AxisDDA
{
  double points[64]; //64 control points to work with, in the end, only the first 4 will be filled.. 
  double fDDA[3];
};

struct CommandBuffer
{
  CString Commands[0x1000];
  short   Lines[0x1000];
  short   head,tail;
};

struct GeckoBuf{
	double XPos;
	double YPos;
	double ZPos;
	double APos;
	double BPos;
	double CPos;
};

struct PPoint
{
 double x,y,z,a,b,c;

};

struct ProgramState
{
 CString Filename;
 int     ExecutionLine;
 bool    IsFile;
};

#include "PathProgress.h"
#include "Mach1Button.h"


class TrajectoryControl : public CWnd
{
// Construction // Put all variables in this block to keep them synced to the main engine..
public:
	Traj  trajectory;
	short HomannSlave;
	_int64 GeckoPos[6];
	bool  TPersist;
	bool  m_RevArc;
	Traj  Tooltraj;
	double RexRateDRO, RexRateTemp;
	bool   RexRateTrigger;
	int     PosChange[6];
	double  FrontToRear;
	double LastPositions[6];
	double FrontXOffS;
	double FrontXOffE;
	double ThreadParm[6];
    bool  RapidOverRide;
	double RapidFeedrate;
	double nextradius;
	int    nextside;
	bool   RegenNeeded;
	bool   DROBack;
	int    nextindex;
	ProgData  rundata;
	CString DROFont,CodeFont,LabelFont;
	bool   JOGPINS[8];
	CString SlabIP;
	double DiffX, DiffY, DiffZ; //offset differentials..
	double DiffA, DiffB, DiffC;
	CommandBuffer BCommands;
    bool  m_HWSafe;
	int M3;
	//laser variables.
	bool HotKeysPersist;
	int  m_LookAhead;
	bool WatchHold;
	int LaserPort;
	int Serial;
	int m_ServoSerial;
	int LaserBaud;
    int LaserStops;
    int LaserData;
	int Timers[25];
    CString LaserInit;
    CString LaserCommand;
	// end of laser vars
	bool IsPanel;
	double MPGFeed;
	double TempFeed;
	bool PlasmaHome;
	bool m_UDP;
	CString NextSub;
	ProgramState returns[1000];
	ToolCabinet  Tools;
	double RefCounts[6];
	double    m_Seconds;
	double    MinPerPass;
	bool      InCycle;
	bool      HommanHolding;
	bool      OverRideMode2;
	int       PanelOut;
	CTime     SinceOn;
	bool     m_PathBoxed;
	bool     m_Plane;
	double    AxisDist[6];
	Executions BackBuffer;
	int BackHead,BackTail;
    double FeedRate;                       //feedrate velocity;
	ModBusRedir  ModCouple;
	bool   ChangeScreens;
    int    Units;
	double FeedInc; 
	double ToolPostOffset;
	double StepsPerAxis[6];
	double Velocities[6];
	double Acceleration[6];
	double Corrections[6];
	GeckoBuf GeckoBuffer[4096];
    Commands CommandBuffer;
	int history[6];
	int load;
	bool  m_ZInhPersist;
	bool  TangentalControl;
	bool  AutoScreens;
	bool  skiptan;
	double LiftAngle;
	double LiftLevel;
	bool  m_OVPersist;
	bool  m_AutoSpindle;
	bool  ToolFlip;
	CMemMapFile GCodeFile;
	CMemMapFile DisplayComs;
	CFile   BackBufferFile;
	bool    BufferFileOpen;
	bool m_Loaded;
	LPVOID GCodeData;
	int *GLines;
	int Lines;
	CString m_FileName;
	int   TermMode;
	bool configured;
	bool pathconfig;
    double OrigSpindleSpeed;
	bool   m_Flash;
	bool g_ZInhibit;
    double g_ZInhDepth;
	bool   m_ToolChange;
	double m_SafeZ,m_SafeZO;
	bool   m_ToolIgnore;
	int SetupUnits;
	double nStepsStore[6];
	double VelStore[6];
	double AccStore[6];
	int    unitscommand;
	double OffsetLength;
	int Tool;
	double NextFeed;
	bool   FeedTrigger;
	bool   OriginTrigger;
	bool   MacroTrigger;
	bool   DwellTrigger;
	bool   ProbeTrigger;
	double m_ByPassFeed;
	bool   ByPassFeedOn;
	int    DwellAmount;
	int    macro;
	double VelLimit;
	bool   AAng,BAng,CAng;
	double rpm;
	bool   Simulating;
 	bool  ArcTest;
	int FeedID,OriginID,ToolID,UnitID,LengthID,DwellID,SpinID,MacroID,ProbeID;
    int SpinVelPerRPM;
	int SpinAcc;
    int    lines;  // current translation line while loading
    Subs   oSubroutines[100]; //unused padding..
	int    nSubs;
    int    nReturns;
	double THCSpeed;
	double THCCurrent;
	double THCMax;
    double THCMin;
	double PlungePercent;
	bool   PWMLaser;
	int full_circle_in_active_plane;
	double radius;
    bool   ModBusOn;
	bool   OverRide;
	bool   m_MacroPump;
	double Estimate;
	bool  SimDone;
	double simx,simy,simz,sima,simb,simc;
	double MacroP1,MacroP2,MacroP3;
	int RefSpeed[6];
	int Vels[6],Accs[6];
	bool AxisNegs[6];
	int     References[6];
	double  Returns[6];
	bool    SingleVerify;
	int     SingleAxis;
	int     tempExec;
	bool    Silence;
	bool    Stage2Trigger,Stage3Trigger;
	bool    LastAutoZero[6];
	int     ProbeAction;
	double  ProbeGoto;
	double  ProbeX, ProbeY, ProbeZ, ProbeA, ProbeB, ProbeC;
	bool    DigFileOpen;
	CStdioFile  digfile;
	double  RadiusA, RadiusB, RadiusC; // distance per 1 degree of angular movement
    double  m_Increment;
	int AxisKeys[12];
	int m_DROCode;    //hot key for DRO selection;
	int m_MDICode;    //hot key for MDI selection;
	int m_GCode;      // hotkey for GCODE selection
	int m_ListKey;     // hotkey for GCode display
	bool m_ExcludeZ;
    bool m_JoyOn; 
	bool m_Linear;
	bool MDIMove;
	double m_IncFeed;
	int  Platform; 
	bool Homeing;
	bool Jogging;
    bool CustomIncremental;
    bool SoftLimitHold;
	ComBuf CannonBuffer;
	bool m_Virtual;
	CString LastError;
	int Line;
	int name,repeat; //for subroutines.
	bool FileFinished;
	int   LastPress;
	double OVMaxVel;
	int   PausedFrom;
	bool  Follow;
	int   EStopCause;
	bool  CommandWaiting;
	bool  m_DisplayMachineCoord;
	double FeedOverRide;
	double tFeedOverRide;
	double JogSlideIncr;
	bool   ConstantVolume;
	bool   PathGenerate;
	int    toolpath;
	bool   PathLoaded;
	double m_CPULoad;
	CString LastFile;
	bool   Threading;
	double CycleInts[10];
	bool   ErrorClear;
	bool   AutoRun;
    int    EncJogAxis;
	double RatioTaper;
	bool   TaperMode;
	bool   DualMPG;
	int    EncJogAxis2;
	int    EncJogAxis3;
	int    LastEncJogCount;
	int    CurrentEncJogCount;
	int    LastEncJogCount2;
	int    CurrentEncJogCount2;
	bool   m_Z25D;
	bool   BlockDelete;
	bool   m_AutoTool;
	int    OldTool;
	bool   OnFeed;
	CFile *ErrorFile;
	CArchive *Errors;
	double  OEMDROs[256];
	bool    OEMLeds[256];
	CString Tickers[256];
	CString UserLabels[256];
    bool   ErrorsOpen;
	int    ScriptsRunning;
    bool   TeachFileOpen;
	double LaserMaxSpin;
	//CArchive *TeachFile;
	CStdioFile TeachFileFile;
	CString   TeachFileName;
	bool      SingleAxisVerify;
	int       nSingleAxisVerify;
	bool      MaxCLMode;
	bool      Regening;
    int       RegenLine;
	EmcPose   whereold;
	bool      Dig4Axis;
	int       SerialType;
	bool      RunAt;
	bool      DigLetter;
	bool      filestart; //for the backbuffer initialization.
	bool      DelayedReset[6];
	int       ResetTimer;
	bool      OrigXDir;
	bool      FrontPost;
	int       m_OEMRegNum;
	bool      m_OEMRegOn;
	int       VelMode;
	double    VelPer1,VelPer2,VelPer3;
	double    m_RealVelocity[7];
	double    m_RealAccel[7];
	double    m_G20X;
	double    m_G20Y;
	double    m_G20Z;
	double    m_G20A;
	double    m_G20B;
	double    m_G20C;
    bool      m_Rot360;

	CString   ProgramDir;
	CString   ThisProfile;

	double    m_ToGo[6];
	bool      ToGo;

    LEDConditions   LEDBool;
	DROValues       DROS;

	GenSocket  UDPIO;

	int       EncoderZeros[6];
	
	AxisDDA   AllDDA[6];
	 
	bool   m_ShortRot;
	CString m_Init;
	bool m_InitAllResets;
	double  BackOffsetx, BackOffsety, BackOffsetz, BackOffseta, BackOffsetb, BackOffsetc;
	double  BackToolZ, BackToolX;
 //////////////////////////////////
	//
	//   Values for DRO's
	/////////////////////////////
	double XPosition;
	double YPosition;
	double ZPosition;
	double APosition;
	double BPosition;
	double CPosition;
	double MXPosition,MYPosition,MZPosition;
    double MAPosition,MBPosition,MCPosition;

	double XVel, YVel, ZVel, AVel, BVel, CVel, BlendVel;
	double JogFeedRate;

	double Maxs[6];
	double Mins[6];

	PmCartesian dummy; // for addtobuffer
	double feedtemp;
	bool CancelPath;
	PathProgress *progress;
	bool  LastMoveRapid;
 
	double RefPoints[6];
	int    OldState;
 	bool   MillMode;
	double MachPositions[6]; //machine coordinates of first three axis

	double SlowPoints[6];
    double m_SoftMaxs[6];
	double m_SoftMins[6];

	double SlowPointsO[6];
    double m_SoftMaxsO[6];
	double m_SoftMinsO[6];
	
	bool  ToolPathOn;
	double LatheCorrection;
	double Diameter;
	bool   RunInReverse;

	bool m_DroLock;

	double Throttle;
	int    ThrottleFunc;

	int simcount;

	double cpuSpeed;
    bool   CorrectionOn;
	bool   AutoLimitOverRide;

	bool SetSkip;  // skip the softlimits setup on Ref All from G-Code
	int  refaxis;

	bool  SingleTriggerOn;
	bool  SingleActive4On;

	bool  ConditionRapid;
	bool  CurveLoaded;

	int   MaxFeedOverRide;
	double thcmax;
	double thcmin;
	bool  SpinActual;

	double m_BB, m_BR, m_BG, m_RB, m_RG, m_RR, m_FB, m_FR, m_FG, m_AR, m_AB, m_AG,
		   m_EG, m_EB, m_ER;
	int BaudRate, ComPort;
	int EntranceAngle;
	int m_PWMin;
	double RotError;
	int    SpinInc;

	bool   m_XMapOn,m_YMapOn,m_ZMapOn;

	double LaserXGrid;
	double LaserAGrid;
	double LaserYGrid;
	int  LaserYOff;
	int  LaserXOff;
	int  LaserAOff;

	int m_UseCR;
    CString m_Char;
	bool    m_SLS;
	double  Repeats;
	double ZInhibInc;
	double  SLSDist;
	int     LastMode;

	bool    MacroRunning;

    bool   DwellMilli;
    double NextZLength, NextXLength;
	bool   OEMTriggers[15];
	
    Mach1Button  OEMButton;
	short OEMPins[15];

   bool  UseSwitches;
   double PWMMaxSpeed;
   
   bool   DoRegen;
   bool   m_Homann;

   //Toolpath variables for display
    BOOL m_OriginSphere;
	BOOL m_3dCompass;
	CString  HomannString;
	short    HomannLoc;
	bool     m_BitPack1;
	int      m_BitPack1Reg;
	bool     m_BitPackOut1;
	int      m_BitPackOutReg1;
	BOOL m_Boundries;
	BOOL m_ToolPosition;
	BOOL m_AParallel;
	double m_AtoXOff;
	double m_AtoYOff;
	double m_AtoZOff;
	//Threading Variables for defaults...
    int nAddons;
	AddStruct AddonNames[200];
	int AddonSelected;
    bool LoadAddon;
	CString Addon2Load;
	CString Init2Load;
	bool   AddonReady;;
	bool   AddonLoaded;
	bool   AutoRegen;
	bool   SoundsOn;
	bool   VoiceOn;
	bool   SingleStepMode;
	bool   EditLoad;
	bool   JogActive;
    bool   m_Arots;
    NextLine  AfterPause;
	bool      HeldInReverse;
	bool      LastMovePartial;
	
// Operations
public:
    CString   defaultscreen;
	bool   LoadScreen;
	int    ActiveGroup;
	int    LastActiveGroup;
	int    JogMode;
	 
	bool   KeepRef;
	bool   Speech;
	bool   HelpContext;
	bool   LastSpeech;
	bool   MovingAverageDone;
	bool   MovingAverageOn;
	 
	bool   JogPersist;
	bool   SaveWizard;

	double StepsX,StepsY,StepsZ,StepsA,StepsB,StepsC;

	double loadToolXOff;
	double loadToolZOff;
	int    loadSlot;
	bool   ToolDirty, FixDirty;
	bool   PersistOffsets, OffsetsDialog;
    bool   G54Back;
	SpindleFM   Spindle;
	MPGControl   MPG;
	bool   JogVelocity;
	bool   LastVelJog;
	double m_DepthLastPass;
	double m_InFeed;
	double m_Spring;
	double m_MinDepth;
	double m_XClear;
	double m_ZClear;
	double m_CutDepth;
	double m_Chamfer;
	double m_DepthFirstPass;
    int    ReversalLine;
	bool   MidLine;
	bool   UnReversed;
	bool   SkipProgress;
	double StockSize;
	bool   ShowSolid;
	double LastLineFeed, LastArcFeed;

	double TurnMatR;
    double TurnMatG;
	double TurnMatB;
 
	ScrewMapCurve  XCurve,YCurve,ZCurve;
    ScewMap *screw;
	int m_IncJogBuffer;
	bool OEMDualTemp;
	bool RunPlus;
	bool RunMinus; //these two are for runnign forward and back buttons.
    bool LaserStandby;
	bool ResetInit;
	bool LastRunBackward;
	int  LastLineExec;
    EmcPose SyncWhere;
	bool FeedHolding;
	bool NoPartial;
	bool m_PlasmaMode;
	bool m_UseSafeZ;
	bool m_CompPlus;
	bool EmergCalled;
	Reprocessor *Processsor;
	SerialRingThread *SerialRing;
	bool ShuttleAutoOff;
	CString LastMacroFile;
	CString filetoload;
	bool m_TurnReverse;
	Mach1Button *lastbutton;
	bool MPG1,MPG2;
	bool NoGConf;
	bool TorchVoltageControl;
	int TorchSpeed;
    GMoves    Movements[4096];
	double    EncoderPos[4];
	double     TouchZ, TouchX;
	bool       FirstRev;
	double     PierceDelay;
	bool       m_WarnOnReset;
	bool      HighRes;
	bool      m_ToolLines;
    ModCon  ModBusData;
	bool    m_ModPlug;
	double MB_MPGTime;
    bool UsingModMPGs,MBHaveReading;
    bool Polled;
    short  *ModInputs;   //ModBus variable Inputs Short[128]
    short  *ModOutputs;  //ModBus varibale OutPuts[128] 
	bool    ShutDown;
	bool    DebugRun;
	double  ExternalPulseRates[7]; //number 7 is for the spindle
	bool    ExternalStill;
    int     ELine;                 //used in triggering External Device outputs in realtime;
	bool    PurgeMovements;        //Will cause MAch3 to purge all pending movement
    int     EHead;
    Externals   EXCtrls[16];
    bool    ModBusCfg;
	unsigned __int64 SoftWait;
	bool     DoExternalProbe;
	int      ExternHomedMask;
	bool     MovementDone;
	double   SpindlePer;
	bool     HasRot;
	bool     m_UseDiam;
	bool     Sequence;
//Probe Radius
	double      ProbeRad;
	PmSpherical ProbeAngles;
	PmCartesian ProbeVec;

//safeZ correction
	int         m_SafeZType;
	bool        m_SafeZStop;

	int         m_UnusedBufferFill;
	bool        FlashSizing;
	short        ExternalType;
	GMoves1      MovementsAdd[4096];
	bool         BufferEnding;
	double       ExTime;
	int          ExBufferHi;
	bool         SkipShutdown;
	CString      MDIEntry;
	bool         m_MenuOff;
	bool         m_IgnoreM3;
	bool         m_MutiHome;
	int          m_HomeMask;
	int          PartialModes[255];
	bool         SkipFeed;
	double       aProbeX, aProbeY, aProbeZ, aProbeA, aProbeB, aProbeC;
	double       PausedFeed;
	bool         TrajDone;
	bool         ExecNow;
	HANDLE       thandle;
	Subs         nSubroutines[1000];
	CString      ExternalMacro;
	CString      lCOSYS,lTOOLDESC,lUNITREVMIN,lRADDIA,lINMM,lMODE,lPROFILE,lFILE;
	bool         VBTest;
	bool         FileLoadOK;
	bool         FileSimOK;
	bool         m_ExternalFeedHold;
	int          m_Ex_Loop3Time;

	short        MasterInputs[1024];
	short        MasterOutputs[1024];
	short        UserInputs[1024];
	short        UserOutputs[1024];
	

	bool         m_ExternalPaused;
	bool         m_SpindleOn;
	short        ex_purgeflags;
    bool         G100TripSection;
	bool         ReDraw;
	int          SpinDir;
	double       RXPosition,RYPosition;
	bool         InternalJogProbe;
	double       flashsec;
	bool         ExternalFRO;

	bool         SecondPass;
	bool         ComBufferOpen;
	int          CompHead,CompTail;
	TCPModCon    TCPModBusData;
	CString      m_FileOnly;
	CArray < Brain*, Brain*> *TheBrains;
	int          m_nBrains;
	double       OEMDROs2[1000];
	bool         OEMLeds2[1000];
	bool         m_UsingTCPIO;
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////
// No plugin Variables below this point..

 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TrajectoryControl)
	//}}AFX_VIRTUAL


	FixtureCabinet Fix;
	
// Implementation
public:
	CArray < PPoint*, PPoint*> ProbePoints;
	CArray < PPoint*, PPoint*> MissPoints;
	Extreme ProbeEx;
	Normals  NormCond;
	bool    IncrementCorrect;
	EmcPose TrueCenter;
	bool    ForwardCheck;
	double  AbsMaxs[6];
	double  AbsMins[6];
    int     Updates;
    CString ButtonFont;
    bool    m_AbsInc;
	bool    m_SpinOff;
	int     m_SpinInc;
	bool    m_UseCVAngle;
	double  m_CVAngleDeg;
    int     precompmove;
	double Fractions[6];
	bool   m_THC5;
	bool   KeyClick;
	double OldFeeds[64];
	bool   donesafemove;
	bool   m_JogHeat;
	bool   DelayedJog;
	int    DelayedJogAxis;
	int    DelayedJogDir;
	bool   JogSpindleOn;
	CString Authors[100];
	bool    THCEmulInOp;
	int     SpindleDelayedOn;
	bool    m_SlaveHome;
	double  LastFeedRate;
	bool    m_RotSoft;
	double  NormCycle;
	CMemMapFile CompComs;
	CFile   CompBufferFile;
	bool    SecondPassDone;
    bool    JustSave;
	bool    m_TCPModBus;
	bool    m_ZBar;
	BrainHandler   BrainControl;
	double         BrainMs;
	CString        ModBusString;
	bool           ModStringHolding;
	int            ModStringAddress;
	int            ModStringcfg;
	bool           m_IgnoreMs;
	double         AxisOffs[6];
	int            ProbeStepsSec;
 
	TrajectoryControl();
	int       GetProbeTrip( int ProbeGoto, int Accs, int MaxVelocity, int axis );
	void      ResetProbePoints();
	void      AddProbePoint(double x, double y, double z, double a, double b, double c, bool hit);
	void      computeDDAs(double time = 64);
	int    BufferUsed();
	void   DoGeckoLines(short num ,   int &orig);
	double ShortRot( double angle, double lastangle);
	void CompOff();
	void LoadFixtures();
	void JogInputHandler();
	int ConvertHex(CString hex);
	void SetVelocityMode( bool state );
	void TCReverse( TC_STRUCT *to, TC_STRUCT *from );
	void CreatePartials( int revline );
	void DoTorchRunReverse();
	void SetLastError( LPCSTR error );
	void ScrewCal();
	void SaveLinearity();
	int  GetNextPoint(int axis);
	int  SimCheckSoft( int , int );
	void FakeDriver();
	void SetFormulas();
	void LoadLinearity();
	void WorkOffsetTo( short axis, double Value);
	void ReversalSearch( int id );
	void RunReverse();
	bool DoHelp( int OEMnumber );
	void Speak(char* Text);
	void ScreenToggle();
	void CalcTrigger();
	bool DoExtOuts( short n );
	double WhereRel(int axis);
	void SetEntranceAngle( int angle );
	void Regen();
	double GetRandom();
	void CalcReverseLine(int nLine, CString& String);
	void CalcForwardPartial(int nLine, CString& String);
	void SetColors();
	void rs_exec( CString Block);
	void AutoSaveProfile();
	void THCOff();
	void THCOn();
	void RadCircleCCW( double radius);
	void RadCircleCW( double radius );
	void SafeEnd();
	void Check4ExtSingle();
	void FillBitMap();
	void SetLimitOV( bool cond);
	double GetFixtureAxis( int axis );
	void SetFixtureAxis( int axis, double value );
	 
	void GoHome();
	void SetFixture( int fixture );
	void FixtureOff();
	void SetSoftPoints();
	void SetRefPoint( int axis, double point);
	void DROToEncoder( int nEncoder, int nDRO);
	void EncoderToDRO( int nEncoder, int nDRO );
	void CalTHC();
	void Fixtures();
	void ToolTable();
	void TouchTool();
	void SetTHCMax( double unitsmax, double unitsmin);
	void SetTHCSpeed( double speed);
	void ToggleSoftLimits();
	void AddToBuffer( bool line, EmcPose end, PmCartesian center, 
		              PmCartesian normal, int rot, bool rapid);
	void EditFile();
	void CancelAllCommands();
	void SetEStopReason();
	void RunWaitingCommands();
	void SetJogInc( bool state );
	void SwitchWindow( int Window);
	void DROPositions();
	void WatchDogs();
	void Reset();
	bool GetMachineCoords();
	void SetMachineCoords( bool mach);
	void SetFollow( bool fol );
	void SetNextLine( int line );
	void RunFileAt( int line );
	void SimulateFile();
	void GoToZeros();
	void FloodToggle();
	void MistToggle();
	void ZeroAxis( int axis );
	void DisplayExec();
	void ZeroAll();
	void StopFile();
	void ResumeFile();
	void RewindFile();
	void PauseFile();
	void SingleStep();
	void RunFile();
	void LoadTraj();
	CString& GetLastError();
	void OnToolChange( double tool);
	void RetSub();
	void DoSub(int name, int repeat);
	void SetVirtual(bool state);
	bool ExecFunctions();
	bool Execute(CString *Block, int line);
	void ProgramReset();
	void DoGCodeLoop();
	void CalculateSpeeds(int axis);
	void RefA();
	void RefB();
	void RefC();
	void RefX();
	void RefY();
	void RefZ();
	void DoJogLoop();
	void RefHomeOn( int axis, int dir);
	bool CheckSkip();
	void SetSoftLimits();
	void JogOff( int axis );
	void JogOn( int axis, int dir );
	bool CheckJoyStick();
	void SetDiameters( double A, double B, double C );
	void CloseDigFile();
	void OpenDigFile();
	void ProbeCommandFinished();
	void DoProbe();
	void ProbeAxis(double x, double y, double z, double a, double b, double c);
	void VerifyReport();
	void VerifyStage2();
	void FinishVerify();
	void Verify(bool silent);
	void CalcVels( int axis);
	void HomeOn( int axis, int dir);
	void SafeTravel();
	void DoMacro();
	void SetRate( double rate);
	void MacroRunFile( CString &name );
	void RunInitFile(CString &name);
	void CheckforSubroutine();
	void DoSpinSpeed();
	void DoSpinSpeedInternal();
	void DoSpinStop();
	void DoSpinCW();
	void DoSpinCCW();
	bool LoadFromPath( CString file);
    bool LoadSub( CString file ); 
	void DoOrigins();
	void ChangeFeed();
	void CompleteToolChange();
	bool Same( double x, double y, double z, double a, double b, double c);
	void DoToolChange();
	void DoUnits( int units);
	void DoLength();
	void RunRecalculate();
	void ChangeTool( int tool );
	void SetPlane( int plane );
	void ReturnToPaused();
	void RememberPaused();
	void StartMacroPump();
	 
	void SetupBacklash();
	 
	bool CalcArcs(double first_end,double second_end,
                  double first_axis, double second_axis,
				  int rotation, double endpoint, 
			      double enda,double endb, double endc );
	void SetAccVelMan(EmcPose where );
	void AddCommand( int Command, int line, double param );
	void DoCommand( int Command );
	void ManualLine( double x, double y, double z, double a, double b, double c);
	void SetMMS();
	void SetInches();
	BOOL ChangeLine( int line, CString Text);
	void CloseFile();
	bool GetLine( int nLine, CString& String, bool skipreverse);
	bool LoadGCode();
	void Sync();
	bool SetAccVel( EmcPose where, double MaxVel);
	void SetLastPos( EmcPose where );
	void ReCalculate();
	void SetFeedRate( double Rate);
	void Resume();
	void Pause();
	bool StraightThread( double x, double y, double z, double a, double b, double c);
	bool StraightFeed( double x, double y, double z, double a, double b, double c);
	bool StraightTraverse( double x, double y, double z, double a, double b, double c);
	bool TrajectoryControl::ArcFeed(double first_end,double second_end,
                                double first_axis, double second_axis,
								int rotation, double endpoint, 
								double enda,double endb, double endc);
	void Init();
	void Update(void);
	void PlaySounds( char * sound );
	void SetHelpContext();
	virtual ~TrajectoryControl();
	void  DoShifter( short num ,   int &orig);
	void  DoGShifter( short num ,   int &orig);
    void  UpdateToolOffsets();
    void  SaveToolTable();
	void  GotoSafe_z();
	void  SetIncr( int pos);
	// Generated message map functions
protected:
	//{{AFX_MSG(TrajectoryControl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void SpinUp(void);
	void SpinDown(void);
	void SpinOverRide(double rpm);
	void ExecMacSub(CString Mac);
	void ResetZTHC(void);
	void CycleIncr(void);
	void FillJogIncs(void);
	void DoEncoderJog(void);
	void DoOEMTrigger(short Trigger);
	void DisableSpeedOv(void);
	void SetMill(void);
	void SetTurn(void);
	void LatheHome(int axis);
	void Add2MRU(CString fname);
	void DoMRU(void);
	void DisplayHistory(void);
	void AddToLog(CString text);
	void ExecuteButtonScript(CString script);
	void EditScript(CString script);
	void CalcThread(void);
	void VariJogOn(int axis, int direction , double speed);
	int OpenTechFile(LPCTSTR name);
	int OpenSubFile( LPCTSTR name);
	int AppendTeachFile( LPCTSTR name );
	void CloseTeachFile(void);
	void TeachLoad(void);
    void CheckMacroFolder(void);
	void ConfigToolPath(void);
	void SelectAddon(void);
	void SelectNewFangled(void);
	void CheckSoftLimits();
	void LoadDefaultScreens();
	void DoSingleStep(void);
	double CalcOrg( int axis);
	void   SaveFixtures();
	// Gets BackBuffer Entry
	Executions GetDisplayCom(int Com);
	void   UpdateIO();
	bool   GetInputs( int bit, bool Neg );
	void   SetOutput( int bit, bool onoff, bool neg);
	void KillScripts(HANDLE hCtx);
	void SyncLocation(void);
	void TurnTouchX(void);
	void TurnTouchZ(void);
	void SetDwell(double delay);
	void TorchVolts();
	void SwitchToRear();
	void SwitchToFront();
    Executions GetCompDisplay(int Com);

	double Get_Setup(double value);
	void RecieveUDP(void * buffer, int bytes);
	bool Emailer;

	
	bool SoftForCheck(void);
	int GetIndex(short axis);
	void SetIndex(short axis, int value);
	void RotConvert(TrajPoint &trajorg);
	void UpdateSyncWhere( GMoves move);
	void SetSoftMin();
    void SetSoftMax();
    void RestoreSoft();
	bool IsMoving();
	void SetToolDesc( int tool , LPSTR desc );
	void DoLabels();
    bool ReCheck();	 
	void CalcDecel();
	void AddPartialArc();
	void AddToCompDisplay(bool line, EmcPose end, PmCartesian center,
		PmCartesian normal, int rot, bool rapid);
	void DoMenu( int sub, int pos );

 
         
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAJECTORYCONTROL_H__C8CBC326_3A49_4703_B02E_13CBC7C2848C__INCLUDED_)
