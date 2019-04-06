//=====================================================================
//
//	_TrajectoryStructs.h : header file
//
//		broken out the enums and structs from _TrajectoryControl.h
//
//		there are only a couple that are impure replacements for class
//		all replacements are preceded by an underscore. mostly CString
//		replacements.
//
//=====================================================================

#pragma once

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

enum {	EX_DDA,
		EX_VMS,
		EX_COMMAND,
		EX_SPINON,
		EX_SPINOFF,
		EX_SPINSPEED,
		EX_MOTORTUNED,
        EX_SETUP,
		EX_FEEDHOLD,
		EX_RUN,
		EX_ESTOP,
		EX_CONFIG
};

enum {	SAFEMACHINE,
		SAFEWORK,
		SAFERISE
};

#define JOGCONT 0
#define JOGINC  1
#define JOGMPG  2

struct Externals
{
	int		Line;
	bool	Active;
	int		Signal;
	bool	State;
};

struct Extreme
{
	double	px, py, pz;
	double	mx, my, mz;
};

struct ModCfg
{
	short	Data[128];
	char	Comment[80];
	bool	Enabled;
	int		ModAdd;			//modbus address
	int		nReg;
	int		Input;
	int		Port;
	int		Slave;
	int		Refresh;
	int		timref;
	int		status;
	char	msgstatus[40];
};

struct ModCon
{
	ModCfg	cgf[65];
};

struct TCPModCfg
{
	short	Data[128];
	char	Comment[80];
	bool	Enabled;
	int		ModAdd; //modbus address
	int		nReg;
	int		Input;
	int		Port;
	int		Slave;
	int		Refresh;
	int		timref;
	int		status;
	char	msgstatus[40];
};

struct TCPModCon
{
	TCPModCfg	cgf[65];
};


struct GMoves
{
	int		type;			// 0 is linear, 1 is cubic
	double	cx, cy, cz;		// center of move for cubics. 
	double	ex, ey, ez, ea, eb, ec;
	double	sx, sy, sz, sa, sb, sc;
	__int64	DDA1[6];		//DDA1's for cubics
	__int64	DDA2[6];
	__int64	DDA3[6];
	double	Time;
	bool	Stop;
};

struct GMoves1
{
	double	diffs[6];
	double	velocity;
	double	accel;
	double	sweep;
	double	radius;
	short	nx, ny, nz;
	short	line;
};

struct Commands
{
	int		Command[0x400];
	int		LineID[0x400];
	double	params[0x400];
	int		nCommand; 
	int		tail;
	int		head;
};

struct ModBusRedir
{
	bool	SpindleOn;
	int		SpindleSpeedReg;
	double	SpindleCal;
};

struct Executions
{
	bool	line;
	EmcPose				end;
	PmCartesian			center, normal;
	double	rotation;
	double	Arotation;
	int		linenumber;
	bool	rapid;
	double	toolz;
	double	toolx;
	double	Feedrate;
	short	toolnumber;
	bool	Abs;
	double	comp;
};

struct ProgData
{
	int		UnitType;
	double	MaxX, MaxY, MaxZ, MaxA, MaxB, MaxC;
	double	MinX, MinY, MinZ, MinA, MinB, MinC;
};

struct _NextLine
{
	LPCSTR	Block;
};

struct _AddStruct
{
	LPCSTR	path, name;
	bool	present;
	LPCSTR	setname;
};

struct Subs
{
	int		name;
	int		line;
};

struct ComBuf
{
    int		nCommands;
	int		Commands[10000];
	double	Params[40000];
	int		nParams;
	int		LastParam;
	int		LastCommand;
}; 

struct AxisDDA
{
	double	points[64]; //64 control points to work with, in the end, only the first 4 will be filled.. 
	double	fDDA[3];
};

struct _CommandBuffer
{
	LPCSTR	Commands[0x1000];
	short	Lines[0x1000];
	short	head, tail;
};

struct GeckoBuf
{
	double	XPos;
	double	YPos;
	double	ZPos;
	double	APos;
	double	BPos;
	double	CPos;
};

struct PPoint
{
    double	x, y, z, a, b, c;
};

struct _ProgramState
{
	LPCSTR	Filename;
	int		ExecutionLine;
	bool	IsFile;
};
