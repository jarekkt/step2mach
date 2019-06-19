//Axis definitions

#if !defined(AFX_ENGINE_H__738D3A62_292C_413C_A76F_052BE3C1250C__INCLUDED_)
#define AFX_ENGINE_H__738D3A62_292C_413C_A76F_052BE3C1250C__INCLUDED_


#define XAXIS    0
#define YAXIS    1
#define ZAXIS    2
#define AAXIS    3   // disptype
#define BAXIS    4
#define CAXIS    5
#define SPINDLE  6
#define ENC1     7
#define ENC2     8
#define ENC3     9
#define TOOLPATH 10
// Controller States
#define STOP   0
#define RUN    1
#define PAUSE  2
#define FINISHING 3
#define MDISTATE 4
#define WAITING 5
#define SINGLE  6
//  Device outputs
/*
#define EXTERNACT1    1
#define EXTERNACT2    2
#define EXTERNACT3    3
#define EXTERNACT4    4
#define EXTERNACT5    5
#define EXTERNACT6    6
*/

// EStop reasons;

#define  LOCALWATCHDOG   1
#define  REQUESTED       2
#define  DRIVERWATCHDOG  3
#define  LIMITSWITCH     4
#define  DRIVERSAFETY    5  
#define  ESTOPINPUTLINE  6
#define  SOFTLIMITS      7
#define  CONFIG          8
#define  SIMSTOP         9
#define  ENDOFFILE       10
#define  SERVODISABLE    11
#define  EXTERNALCOMTIMEOUT 12



// Commands to Engine

#define COMDWELL      1
#define COMDIGTRIGON  2
#define COMDIGTRGOFF  3
#define COMEXT1ON     4
#define COMEXT1OFF    5
#define COMEXT2ON     6
#define COMEXT2OFF    7
#define COMEXT3ON     8
#define COMEXT3OFF    9
#define MOTIONCS      10
#define MOTIONCV      11
#define CHANGEUNITS   12
#define SETFEED       13
#define CHANGEPLANE   14
#define CHANGESLOT    15
#define LENGTHOFFSET  16
#define SETORIGINS    17
#define SETMAXVEL     18
#define PROGRAMSTOP   19
#define PROGRAMSTOPOPT  20
#define PROGRAMEND      21
#define SPINAXISSPEED   22
#define SPINAXISCW      23
#define SPINAXISCCW     24
#define SPINAXISSTOP    25
#define RUNSUB          26
#define RETSUB          27
#define CALLMAC         28
#define PROBEAXIS       29
#define WAITCOMMAND     30
#define THREADOFF       31
#define FINISHSLOT      32
#define DISABLESPEED    33
#define REFCOM          34
#define COMEXT4ON       35
#define COMEXT4OFF      36
#define COMEXT5ON       37
#define COMEXT5OFF      38
#define COMEXT6ON       39
#define COMEXT6OFF      40
#define FLOODSIGON      41
#define FLOODSIGOFF     42
#define MISTSIGON       43
#define MISTSIGOFF      44   
#define TURNOFFCOMP     45
#define TURNONCOMP      46
#define ESIGON          47
#define ESIGOFF         48
#define EPURGE          49

#define CW  0
#define CCW 1



#define MMS 0
#define INCHES 1
#define DEGREES 2  //dispunits
#define COUNTS 3
#define VELOCITY 4

// Number of input signals in total that need to be loaded from engine
#define nSigs        53  

// Input signals
#define XLIMITPLUS   0
#define XLIMITMINUS  1
#define XHOME        2
#define YLIMITPLUS   3
#define YLIMITMINUS  4
#define YHOME        5
#define ZLIMITPLUS   6
#define ZLIMITMINUS  7
#define ZHOME        8
#define ALIMITPLUS   9
#define ALIMITMINUS  10
#define AHOME        11
#define BLIMITPLUS   12
#define BLIMITMINUS  13
#define BHOME        14
#define CLIMITPLUS   15
#define CLIMITMINUS  16
#define CHOME        17
#define ACTIVATION1  18
#define ACTIVATION2  19
#define ACTIVATION3  20
#define ACTIVATION4  21
#define DIGITIZE     22
#define INDEX        23
#define LIMITOVER    24
#define EMERGENCY    25
#define THCON        26
#define THCUP        27
#define THCDOWN      28   //last engine signal
#define OEMTRIGGER1  29
#define OEMTRIGGER2  30
#define OEMTRIGGER3  31  // OEM Trigger signals..
#define OEMTRIGGER4  32
#define OEMTRIGGER5  33
#define OEMTRIGGER6  34  // OEM Trigger signals..
#define OEMTRIGGER7  35
#define OEMTRIGGER8  36
#define OEMTRIGGER9  37  // OEM Trigger signals..
#define OEMTRIGGER10 38
#define OEMTRIGGER11 39
#define OEMTRIGGER12 40  // OEM Trigger signals..
#define OEMTRIGGER13 41
#define OEMTRIGGER14 42
#define OEMTRIGGER15 43  // OEM Trigger signals..
#define TIMING       44
#define JOGXP        45
#define JOGXM        46
#define JOGYP        47  //Jog inputs
#define JOGYM        48
#define JOGZP        49
#define JOGZM        50
#define JOGAP        51
#define JOGAM        52
#define HOMING       53   //software signal
#define PROBING      54   //software signal
#define RESUME       55   //software signal
#define EXHOME       56   //software signal for external homing offset circuit.

//software triggers...Last 3 bits of the engine Wait condition... 
//which encompasses all 31 signals in a 32 bit word


#define nSigsOut    30  /// output signals

#define DIGTRIGGER  0
#define ENABLE1     1
#define ENABLE2     2 
#define ENABLE3     3
#define ENABLE4     4
#define ENABLE5     5
#define ENABLE6     6
#define EXTACT1     7
#define EXTACT2     8
#define EXTACT3     9
#define EXTACT4     10
#define EXTACT5     11
#define EXTACT6     12
#define CHARGE      13
#define CHARGE2     14
#define CURRENTHILOW 15
#define EXTACT7     16
#define EXTACT8     17
#define EXTACT9     18
#define EXTACT10    19
#define EXTACT11    20
#define EXTACT12    21
#define EXTACT13    22
#define EXTACT14    23
#define EXTACT15    24
#define EXTACT16    25
#define EXTACT17    26
#define EXTACT18    27
#define EXTACT19    28
#define EXTACT20    29



#define KEYNOCOMMAND 0
#define KEYFLOOD    1
#define KEYJOGINCR  2
#define KEYMIST     3
#define KEYPAUSE    4
#define KEYRESET    5
#define KEYRESUME   6
#define KEYREWIND   7
#define KEYRUN      8
#define KEYSINGLE   9
#define KEYSPINCCW  10
#define KEYSPINCW   11
#define KEYSPINOFF  12
#define KEYSTOP     13
#define KEYZEROX    14
#define KEYZEROY    15
#define KEYZEROZ    16
#define KEYZEROA    17
#define KEYZEROB    18
#define KEYZEROC    19
#define KEYZEROALL  20
#define KEYGOTOZERO 21
#define KEYREFALL   22
#define KEYOVERIDE  23

////  Control groups...
//
//
#define DRO     1
#define BITMAPCTRL  3
#define TEXTBUTTON  4
#define JOYSTICK    5
#define LED         6
#define LABLE       7
#define BITBUTTON   8
#define MDILINE     9
#define GCODE       10
#define PATHCTRL    11



 
// output signal structure

struct OutputInfo
{
    bool active;
	char OutPin;
	char OutPort;
	bool Negated;
	bool Activated;
};
 

// input signal structure
struct  InputInfo
{
    bool  Active;     // signal active?
	char  InPin;      // which Pin
	char  InPort;     // which Port
	bool  Negated;
    int   ReqState;   // Required State on Activation
	bool  Activated;
	bool  Emulated;
	int   EmulationKey;
};

// encoder inputs
struct Encoder
{
	bool Active;  // is the encoder turned on?
	int  APin;    //  A Pin designations
	int  BPin;    //  B Pin designations
	int  APort;   //  A Pin Ports
	int  BPort;   //  B Pin Ports
	bool LastStateA;
	bool LastStateB;  // storage for the last known state
	int  Count[2];  //  Index counts for each encoder
	int  Memory[16];
	int  ActiveMemory;
	int  Color;

};

// axis information structure
struct AxisInfo
{
    int   Index;    // Current Count
	int   MasterIndex;
	char  StepPin; // Pin for step pulse
	char  DirPin;  // Pin for Direction Pulse
	char  StepPort; // Port # for step
	char  DirPort;  // Port # for Direction
	bool  StepNegate;   // low active step?
	bool  DirNegate;    // low active Direction?
	int   CurVelocity;  // Current Velocity
	int   MaxVelocity;  // Current Max Velocity (jogging )
	int   MasterVelocity; // Master Velocity...Maximum Velocity in all circumstances.
	int   Acceleration; // Acceleration
	bool  AtSpeed;      // At Speed Currently
	bool  Acc;          // Accelerating?
	bool  Dec;          // Decelerating?
	bool  Enable;       // Axis Enabled?
	bool  Jogging;      // Jogging On?
	int   JoggDir;       // Direction of Jog;
	bool  Homing;       // is this a homing jog?
	bool  DeRef;        // Dereferanceing Move?
	int   Memory[6];
	int   ActiveMemory;
	int   Color;
	int   TripCount;
	int   DepthCount;
	bool  Probing;
	bool  Slave;
	int   SlaveAxis;

};

struct TrajPoint
{
  int Points[6];
  int Command;
  int ID;
  char shifter[6];
};

struct TrajBuffer{

	
	TrajPoint Trajectories[0x1000];
	int   TrajIndex;	// Trajectory buffer current Index
	int   TrajHead;		// Trajectory buffer Fill point
    int   uSecStep;     // clock count for step signal
	int   uSecDir;      // clock count for pre-raising the direction bit;
	double LastCommandPos[6];
    bool  Configured;
	bool  Busy;
	bool  Idle;
	bool  Emergency;
	bool  Jogging;
	bool  IncrementalJog;
	bool  Sync;
	bool  Port1On;
	bool  Port2On;
    bool  Tuning;
	bool  ReconfigHotKeys;
	short Port1Address;
	short Port2Address;
 
    AxisInfo   Axis[7];        // axis information
    InputInfo  InSigs[nSigs];  // input signals
	OutputInfo OutSigs[nSigsOut];  // output signals
	Encoder    Encoders[7];    // encoder inputs
    int        LastCubics[6];
    // WatchDogs
	int   WDInt0;
	int   WDInt8;
	int   WD2Way;
	int   StartClocks;
	int   EndClocks;
	bool  ReadClocks;
	bool  Sampleing;    // Sampleing flag
	bool  CubicDrain;   // cubicDrain flag..sets cubics to zero;
	bool  EStop;
	// software limits
	int   XLimitPos,YLimitPos,ZLimitPos,ALimitPos,BLimitPos,CLimitPos;
	int   XLimitNeg,YLimitNeg,ZLimitNeg,ALimitNeg,BLimitNeg,CLimitNeg;
	int   StatHolders[6];
	int   StatLast[6];
    bool  StatBusy;
	int   StatCount;
	bool  SyncError;
	int   DwellTime;
	int   CurrentUnits;
	bool  Directions[7];
	bool  Safe;
// G-Code vars
	int   State;
	bool  NoTime;
	int   DisplayLine;
	int   CurrentLineExec;
	bool  Loaded;
	int   SpindleCW;
	int   SpindleCCW;
	bool  Jpg;
	double oSpinSeconds;
	bool  SpinDelayReq;
	int   Flood;
	int   Mist;
	bool  Hpgl;
	bool  NoSpindle;
	bool  NoFlood;
	bool  Pro;
	bool  Dxf;
	bool  Referenced[ 6 ];
	bool  HomeSpeed[ 6 ];
	unsigned long  TargetTime;
	int   BackCounts[ 6 ];
	int   BackSpeeds[ 6 ];
	bool  BackState[6];
	bool  BackLast[6];
	bool  BackOn; 
	bool  AutoZero[6];
	double ToolChangePos[6];
	int   LastState;
	int   LookAhead;
	int   Year;
	int   LastExec;
	int   DROUpdate;
	bool  WatchDogOn;
	bool  LimitsOff;
	bool  Simulate;
    int   Month;
	int   KeyAction;
	bool  JoyOn;
	unsigned __int64   WaitCondition;
	int   EStopReason;
	bool  PWM;
	int   PWMFreq;
	int   Day;
	int   oCurrentPulley; //remove this
	int   oldMaxSpeeds[4]; //and this..
	int   m_SetExec;
	bool  AutoHome;
	int   templookahead;
	bool  Homing;
	char  CircData[201];
	bool  CircLoaded;
	bool  DROMaster;
	int   SoftLimitsHi[6];
	int   SoftLimitsLo[6];
	bool  SoftDir[3];
	bool  SoftLimitEnable;
	bool  SoftLimitTriggered;
	bool  HotStart;
	bool  LCD;
	int   OverRide;
	bool  Follow;
    int   NewWindow;
	bool  Deselect;
	bool  DeSelectClick;
	bool  SelectClick;
	int   PWMBaseFrequency;
	int   PulseCount;
	int   THCCorrection;
	int   THCMaxCor;
	int   THCMinCor;
	bool  THCOn;
	int   THCAdder;
	bool  THCZero;
    int   PPS;
	int   RefCounts[6];

	 
	int   CurrentSpindleCount;
    int   IntsPerRotation;
	bool  SpinDec;
	bool  SpinAcc;

	long  WorstCase;
	int   VerifyChecks[6];
    int   Verifys[6];

	int   THCDev;

	int   Debounce;

	bool  WaitForTrigger;
	int   nTrigger;
	int   PumpTime;

	int   MaxSpinCounts;
	bool  Threading;
	int   NormSpinCounts;
	int   SpinCorrection;
	int   SpinAdder;
    int   SpinDebounce;

	int   SPIDataPin;
    int   SPIClockPin;
	int   DataOutPort;
	int   DataOutByte;
	bool  DataOutDone;
	int   DataInPort;
	int   DataInByte;
	bool  DataInDone;
	bool  LaserTrigger;
	int   Counter;
	bool  SPIOn;
	int   SPIDataOut;
	int   SPIDataIn;
	bool  SPIDone;
	bool  SPIhidata;

	bool  OffLine;
	int   SpinStability;
	char  BitTest;

	int   CurRate;
	int   PlungeLimit; 
	bool  NoPlunge;  //THC No plunge control
	bool  SpindleStable;
    short nSlots;
    bool  LaserMode;
	bool  MaxNCMode;
	int   MaxNCLag;
	bool  SlowMode;
	bool  MaxNC10;
	bool  Port2Input;
	bool  ChargeAlwaysOn;
	bool  RaiseLower;
	unsigned int   RawInputs;
	bool  HalfPulse;
	bool     Shuttle;
    int   ShuttleCurVel;  // Current Velocity
	int   ShuttleMaxVel;  // Current Max Velocity (jogging )
	int   ShuttleAccel;
	int   LaserX;
	int   LaserY;
	int   LaserZ;
    int   LaserXOff;
	int   LaserYOff;
	int   LaserZOff;
	bool  HoldInput1;
    int   Pierce;
	bool StopForBacklash;  
	int  GlobalCurHoldVel;
	int  GlobalTargetVel;
	bool BackLashHolding;
	bool backlash;
	bool BacklashEnded;
        bool TriggerBits;
};

struct  TimeData{

	int Time[32000];
};

#endif