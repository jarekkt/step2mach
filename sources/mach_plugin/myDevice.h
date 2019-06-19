// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------

#pragma once

#include "stdafx.h"
#include "MachDevice.h"
#include "myConsole.h"
#include "myHardware.h"

#define  MOTION_TIME_SLICE		0.004 /* in seconds */


typedef enum
{
	SEQ_IDLE,
	SEQ_WAIT_FOR_IDLE,
	SEQ_DWELLING,
	SEQ_HOME_FIND,
	SEQ_HOME_DEREF,
	SEQ_HOME_FINISHED

}MySequenceEnum;

typedef struct
{
	uint32_t	JogOnCall;
	uint32_t	JogOffCall;
	uint32_t	DwellCall;
	uint32_t	HomeCall;
	uint32_t	ProbeCall;
	uint32_t	PurgeCall;
	uint32_t	ResetCall;
	uint32_t	TrajectoryItems;

}MyDeviceStatsType;



class MyDeviceClass
{

private:
	
	int32_t				  ReadyForRun;
	int32_t				  DataLinkOk;
	MyConsoleClass		* console;
	MyHardwareClass		* hardware;
	std::string			  dev_ip_addr;
	MyDeviceStatsType	  stats;

	// Main state machine variables
	MySequenceEnum		  sequence;
	int32_t				  InMotion;
	int32_t				  WaitForGcodeIdle;
	int32_t				  WaitForJogIdle;
	
	// For servicing Dwell requests
	DWORD				  DwellTimestamp;
	DWORD				  DwellDelay;

	// For servicing Jog requests
	int32_t				  JogAxis;
    double				  JogFeed;
    double				  JogVel;
    double				  JogAcc;
	int32_t				  JogDistance;

	// For servicing Home requests
	int32_t				  HomeAxis;
	int32_t				  HomePin;
	int32_t			      HomeSignal;
	double				  HomeVel;
	double				  HomeAcc;
	uint64_t			  HomeMask;
	uint64_t		      HomeMaskValActive;
	uint64_t			  HomeMaskValInActive;
	int32_t				  HomeDistance;
	int32_t				  HomeDelay;

	// For servicing outputs update
	int32_t				  OutputValid;
	uint64_t			  OutputCurrent;
	uint64_t			  OutputMaskCurrent;




	void  SendHoldingMovement(void);
	void  GetInputs(void);
	void  SetOutputs(void);
	void  HandleSequences(void);
	void  ConfigureHardware(void);

	void  DumpConfig(void);

public:
	MyDeviceClass();
	virtual ~MyDeviceClass();


	void  InitControl(void);
	void  Reconfigure(std::string ip_addr,bool debug_mode);
	void  SetMachError(CString  Message);
	void  JogOn( short axis, short direction, double SpeedNorm);
	void  JogOff(short axis);
	void  Dwell(double time);
	void  Home(short axis);
	void  Probe(void);
	void  Purge(short flags);
	void  Reset(void);
    void  Update(void);	

	// Helpers
	static std::string wchar2s(wchar_t * wchar_string,int32_t size);
	static std::string nets2s(System::String^ net_string);

		int32_t				  last_notification;

};
