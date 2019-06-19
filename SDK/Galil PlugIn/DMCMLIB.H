#ifndef H_DMCMLIB
#define H_DMCMLIB

#define  STRICT
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>

#include "dmccom.h"

#define MAX_AXES	10

// Constants
enum DMC_MOVE_TYPES
{
	DMC_JG_MOVE = 1,
	DMC_PR_MOVE,
	DMC_PA_MOVE,
	DMC_VM_MOVE,
	DMC_LM_MOVE,
	DMC_CM_MOVE
};

enum DMC_SEGMENT_TYPES
{
	DMC_LINE_SEGMENT = 1,
	DMC_ARC_SEGMENT
};

// Axis flags
#define X_AXIS			0x0001
#define Y_AXIS			0x0002
#define Z_AXIS			0x0004
#define W_AXIS			0x0008
#define E_AXIS			0x0010
#define F_AXIS			0x0020
#define G_AXIS			0x0040
#define H_AXIS			0x0080
#define S_AXIS			0x0100
#define T_AXIS			0x0200

// Axis indicies
#define X_AXIS_INDEX	0
#define Y_AXIS_INDEX	1
#define Z_AXIS_INDEX	2
#define W_AXIS_INDEX	3
#define E_AXIS_INDEX	4
#define F_AXIS_INDEX	5
#define G_AXIS_INDEX	6
#define H_AXIS_INDEX	7
#define S_AXIS_INDEX	8
#define T_AXIS_INDEX	9

// Structure defintions
typedef struct _DMC_ENCODER_RESOLUTION
{
	unsigned short	fAxes;					// bit-field for which axes are used
	double			dResolution[8];		// encoder resolution (counts/user-units)
} DMC_ENCODER_RESOLUTION, *PDMC_ENCODER_RESOLUTION;

typedef struct _DMC_POSITION
{
	double			dPosition[8];			// axis position (user-units)
} DMC_POSITION, *PDMC_POSITION;

typedef struct _DMC_ARC
{
	double			dRadius;					// arc radius (user-units)
	double			dStartAngle;			// start angle
	double			dEndAngle;				// end angle
	double			dDeltaTheta;			// traverse angle
	DMC_POSITION	posCenter;				// arc center (user-units)
} DMC_ARC, *PDMC_ARC;

typedef struct _DMC_MOVE_HEADER
{
	unsigned short	fMoveType;				// bit-field for what type of move: PR, LM, etc.
	unsigned short	usAxesUsed;				// how many axes were are in this move
	unsigned short	fAxes;					// bit-field for which axes are used
	double			dAccel[MAX_AXES];		// acceleration (user-units)
	double			dDecel[MAX_AXES];		// deceleration (user-units)
	double			dSpeed[MAX_AXES];		// initial speed (user-units)
	unsigned short	usTimeInterval;		// time interval (2**n) for contour mode
} DMC_MOVE_HEADER, *PDMC_MOVE_HEADER;

typedef struct _DMC_MOVE_SEGMENT
{
	unsigned short	fSegmentType;			// line or arc
	double			dBegSpeed;				// beginning speed (user-units)
	double			dEndSpeed;				// ending speed (user-units)
	DMC_POSITION	posBeg;					// where we started
	DMC_POSITION	posEnd;					// where we ended up
	PDMC_ARC			pArc;						// if arc, arc info
	struct _DMC_MOVE_SEGMENT*	Prev;		// previous in list
	struct _DMC_MOVE_SEGMENT*	Next;		// next in list
	PDMC_MOVE_HEADER				pHeader;	// move header if any
} DMC_MOVE_SEGMENT, *PDMC_MOVE_SEGMENT;


// Exported function declarations
#ifdef __cplusplus
	extern "C" {
#endif

#define GALILCALL __stdcall

// Public motion functions
LONG GALILCALL DMCGeneralTuning(CHAR chAxis, USHORT usStepSize, LPSTR lpstrFileName);
LONG GALILCALL DMCAutoTuning(CHAR chAxis, double dPulseMagnitudeVolts,
	USHORT usPulseDurationMS, LPSTR lpstrFileName);
LONG GALILCALL DMCHelix(CHAR chPlaneAxis1, CHAR chPlaneAxis2, CHAR chTraverseAxis,
	SHORT sPitch, ULONG ulRadius, SHORT sStartAngle, LONG lDist, ULONG ulSpeed,
	ULONG ulAccel, ULONG ulDecel, LPSTR lpstrFileName);
LONG GALILCALL DMCEllipse(LPSTR lpstrFileName, int FirstOffset, int SecondOffset,
	double a, double b, double dTheta, double dDeltaTheta, double dIncrement, double dRotation);
LONG GALILCALL DMCSCurve(char chAxis, ULONG ulDist, ULONG ulSpeed,
	ULONG ulAccel, ULONG ulJerk, LPSTR lpstrFileName);
LONG GALILCALL DMCSpline(LPSTR lpstrSourceFileName, LPSTR lpstrOutputFileName,
	double dDeltaVector);
LONG GALILCALL DMCCDtoLI(LPSTR lpstrSourceFileName, LPSTR lpstrOutputFileName,
	double dDetaTime, int ACPerc);

// Motion Segment linked-list functions
PDMC_MOVE_SEGMENT GALILCALL DMCAddMotionSegment(PDMC_MOVE_SEGMENT pDMCMoveSegmentHead);
void GALILCALL DMCDeleteMotionSegment(PDMC_MOVE_SEGMENT pDMCMoveSegment);
PDMC_MOVE_SEGMENT GALILCALL DMCInsertMotionSegment(PDMC_MOVE_SEGMENT pDMCMoveSegment, int fInsertBefore);
PDMC_MOVE_SEGMENT GALILCALL DMCNextMotionSegment(PDMC_MOVE_SEGMENT pDMCMoveSegment);
PDMC_MOVE_SEGMENT GALILCALL DMCPrevMotionSegment(PDMC_MOVE_SEGMENT pDMCMoveSegment);
void GALILCALL DMCFreeMotionSegments(PDMC_MOVE_SEGMENT pDMCMoveSegmentHead);
PDMC_MOVE_HEADER	GALILCALL DMCAddHeaderToMotionSegment(PDMC_MOVE_SEGMENT pDMCMoveSegment);
PDMC_ARC GALILCALL DMCAddArcToMotionSegment(PDMC_MOVE_SEGMENT pDMCMoveSegment);
LONG GALILCALL DMCMotionSegmentsToDMC(PDMC_MOVE_SEGMENT pDMCMoveSegmentHead,
	PDMC_ENCODER_RESOLUTION pResolution, LPSTR lpstrFileName);

#ifdef __cplusplus
	}
#endif


#endif // H_DMCMLIB
