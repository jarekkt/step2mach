#pragma once
#include "dmcwin.h"

// GalilControl
enum seq { SEQNONE, FINDSWITCH, MOVEOFFSWITCH, ROUGHHOME, FINDINDEX, SYNCSTATE, 
         };
struct HomeStruct
{
	bool IsHoming;//This is no longer needed...
	int HomeStage;//Holdes the stage of the home move that is being done
	short HomingAxis;//The number of the axis that is being homed 0=x,1=y...
	int HomeVel;//The Velocity of the axis that we are goign to home along with the Direction (+/-)
	CString AxisString;//this is where we hold the  ",,," for the axis that we are homing
	BOOL UseIndex[6];//this will tell us if the axis needs to use the index pulse...

};
struct GalilStruct
{
	short Normal;
	bool  IsMoving;
	CString Linear;
	CString Contour;
	CString Begin;
	short   BufferLeft;
    short motortype[6];
	bool Connected;
	short nAxis; 
    int  ErrorCode;
    int  Status;
	double SpindleRate;//The rate that the spindle is running at...
	CString Spinlde;
	bool SoftLimitsOn;
	int nSpindle; //axis number of the spindle...
	DMCDATARECORD  *Record; 
	HomeStruct HomeData;
};



class GalilControl : public CWnd
{
	DECLARE_DYNAMIC(GalilControl)

public:
	GalilControl();
	virtual ~GalilControl();
    
	
	CDMCWin *m_DMCWin;
	HANDLEDMC m_hDmc;
    HANDLEDMC handle;
    long rc;
    HANDLEDMC hDmc;
    HWND hWnd;
    char *pch;
    char szBuffer[256];
    int nNum;
	ULONG length;
	USHORT DataType;
	ULONG data;
	int   Indexs[6];
	short Ids[256];
	int   IdIn;
	CStdioFile debug;
	short slots;
	short DebugCtl;
	double fractions[6];
	bool LEReq ;



protected:
	DECLARE_MESSAGE_MAP()
public:
	bool Connect(void);
	void Stop();
	void SetMachError(CString Message);
	void Update(void);
	void UpdateInputs();
	void JogOn(  short axis, short dir, double speed);
	void JogOff( short axis );
	void CheckError();
	void EnsureStopped();
	void ResetControl(void);
	void DoCommandGCode(void);
	void Do4MsGCode(void); 
	void MoveRelative( short index );
	int BufferLeft(void);
	int SendCommand(CString com, bool nobinary = false);
	void SendProgram(char* Program[],int sz);
	void GalilControl::SetHead( int head );
	void AddLinear( GMoves* move, GMoves1 *add);
	void HomeAxis(short Axis);
	
};




