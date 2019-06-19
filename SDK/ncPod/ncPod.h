#pragma once

#include "ncPODDriver.h"


// ncPod

struct PodCon
{
  bool    Connected;
  short   LastError;
  CString ErrorString;
}; 

enum Sequence { PNOSEQ, PHOMING, PHOMING2, PHOMING3, PHOMING31, PHOMING4, PPROBE, PDWELL };

class ncPod : public CWnd
{
	DECLARE_DYNAMIC(ncPod)

public:
	ncPod();
	//buffer for usb commands
	double        DripTime;
	int           SEQUENCE;
	int           DripSel;
	unsigned char buffer[512];
	unsigned char bufferout[512];
    int           index;
	int           returnCode;
	__int64       handle;
	bool          SDOpen;
	bool          BufferHolding;
	int           Holding;
	double total[6]; //accuracy checks..
	_int64 vtotal[6]; //accuracy checks..
	double fractions[6];
	double        cCount[100];
	int           HomeAxis;
	int           DwellTick;
	int           DwellTarget;

	bool          StartDiagBuff;
	int           DiagSeq;
	int           dsync;
    CFile          debug;
    int           HomeHold[6];
	bool          HomeBool[6];
	int           nHolding;
	int           nHomePos;
    int           SpinTarget;
	int           SpinCur;
	bool          ProbeRead;
	int           ProbeX,ProbeY,ProbeZ,ProbeA,ProbeB,ProbeC;
	int           WaitForMove;
    
//handlers..
	virtual ~ncPod();
	void    SetMachError(CString Message);
	void    CheckError();
	void    Update();
	bool    Connect();
	void    Home(int axis, bool slow = false);
	void    HomeDeRef();
	void    HomeSingle(int axis, bool slow = false);
	void    Stop();
	void    SetDrip();
	void    ClearCommand( );
	void    SetCycleTime(int time);
	void    SendCommand( );
	void    SendEP1Command( ); //512 byte block sender. 
	void    SendSimpleCommand(char commandEnum);
	void    Close();
	void    DoProbe();
	void    ReadStatus();
	void    Open();
	void    write4(int value){
					  buffer[index+0] = (value>>24) & 255;
					  buffer[index+1] = (value>>16) & 255;
					  buffer[index+2] = (value>>8) & 255;
					  buffer[index+3] = value & 255;
					  index += 4;
				      }
	void    write2(short value){
					  buffer[index+0] = (value>>8) & 255;
					  buffer[index+1] = value & 255;
					  index += 2;
				  }
	void    write1(char value){
					  buffer[index++] = value;
				  }
	int read4(){
					  int value = 256*256*256*buffer[index] + 256*256 *buffer[index+1] +
						  256* buffer[index+2]+buffer[index+3];
					  index += 4;
					  return value;
				  }
	short read2(){
					  short value = (buffer[index]<<8) +buffer[index+1];
					  index += 2;
					  return value;
				  }
	char read1(){
					  return buffer[index++];
				  }
    
 


protected:
	DECLARE_MESSAGE_MAP()

public:
 //Pod Variables and Structures.
	
	ncPODCommand  Command;
	PodCon        Connection;
	ncPODStatus   PodStatus;

};


