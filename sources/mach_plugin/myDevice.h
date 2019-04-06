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
	unsigned int	JogOnCall;
	unsigned int	JogOffCall;
	unsigned int	DwellCall;
	unsigned int	HomeCall;
	unsigned int	ProbeCall;
	unsigned int	PurgeCall;
	unsigned int	ResetCall;
	unsigned long	TrajectoryItems;

}MyDeviceStatsType;



class MyDeviceClass
{

private:
	
	int					  ReadyForRun;
	MyConsoleClass		* console;
	MyHardwareClass		* hardware;
	std::string			  dev_ip_addr;
	MyDeviceStatsType	  stats;

	// Main state machine variables
	MySequenceEnum		  sequence;
	int				      InMotion;
	int					  WaitForGcodeIdle;
	int					  WaitForJogIdle;
	
	// For servicing Dwell requests
	DWORD				  DwellTimestamp;
	DWORD				  DwellDelay;

	// For servicing Jog requests
	int				      JogAxis;
    double				  JogFeed;
    double				  JogVel;
    double				  JogAcc;
	int					  JogDistance;

	// For servicing Home requests
	int				      HomeAxis;
	int					  HomePin;
	int					  HomeSignal;
	double				  HomeVel;
	double				  HomeAcc;
	int					  HomeMask;
	int					  HomeMaskValActive;
	int					  HomeMaskValInActive;
	int					  HomeDistance;
	int					  HomeDelay;

	// For servicing outputs update
	int					  OutputValid;
	int					  OutputCurrent;
	int					  OutputMaskCurrent;




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
	static std::string wchar2s(wchar_t * wchar_string,int size);
	static std::string nets2s(System::String^ net_string);


};
