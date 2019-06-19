// MachDevImplementation.cpp 
// This is the place where the implementor puts his/her code to actually implement the plugin
//
// -----------------------------------------------------------------------------------------------------
// Revision History:
// 7 June 2006 - Separated from MachDevice by JAP
// -----------------------------------------------------------------------------------------------------

//                    Blank Device
 

#include "stdafx.h"
#include "resource.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "XMLProfile.h"
#include "ExternalMovement.h"
#include "ncPod.h"
#include "ncMonitor.h"


extern TrajectoryControl *MainPlanner; //used for most planner funcitons and program control 
extern CMach4View *MachView;  //used for most framework and configuration calls. 
extern TrajBuffer *Engine;     //Ring0 memory for printer port control and other device syncronisation
extern setup *_setup;          //Trajectory planners setup block. Always in effect
extern CXMLProfile        *DevProf;
extern NcMonitor *monitor;

PodThread* pThread = NULL;
int DripSel;
int HomingType;
int RangeStart;
double PullOff[6]; //This was added so the user could set the pull off amount....



#include "MachDevImplementation.h"
// --------------------------------------->>>>>>> See this file for the Mach functions that can be
//												called and the pointers to the variable blocks.
//#include "xxxxxxxx.h"					// add includes for code you call here

#include <mmsystem.h>
#include <math.h>
 
#include "UDPSocket.h"

// ==================================================================================================
// 
// Global variables for this code 
//
// ===================================================================================================
 
 
bool   ShutDown = false;
 
CString DefDir;  //the default directoy Mach is placed in.
CString Profile; //the name of the profile .. ex. "Mach3Mill"
 
ncPod *Pod = NULL;
	

//Templates of control routines.



// ==================================================================================================
//
// Declare helper routines for your code - more obvious here than in your header
//
//====================================================================================================

//  Routines. 

//======================================================================================================
//
// Here are the routines which are called by Mach3 via MachDevice. They are the "meat" of every plugin
//
//====================================================================================================

extern NcMonitor *monitor;


void myNotify(int message)
{
	if( message == -1 )
	{
		if( Pod != NULL)
		{
			Pod->Stop( );
		}

	}
	if( message == EX_SPINOFF )
	{
		if( Pod != NULL)//meaning we have the pod running
		{
			//relay control of the spindle is automatic, 
			// but the pod can do a PWM signal, so lets turn on the 
			// PWM if the PWM mode is selected in Mach.
			if( MainPlanner->Spindle.PWMEnabled )
			{
				Pod->SpinTarget = 400;
				//Pod->ClearCommand();
				//Pod->Command.commandEnum = USBOUTPUT_PWM;
				//Pod->Command.loc = 400 ; //send a new PWM duty cycle..
				//Pod->SendCommand();
			}

		}
	}
	if( message == EX_SPINON || message == EX_SPINSPEED ) //this is Spindle ON;..
	{
		if( Pod != NULL)//meaning we have the pod running
		{
			if( !MainPlanner->Spindle.SpindleOn ) return;
			//relay control of the spindle is automatic, 
			// but the pod can do a PWM signal, so lets turn on the 
			// PWM if the PWM mode is selected in Mach.
			if( MainPlanner->Spindle.PWMEnabled )
			{
				double ratio = MainPlanner->Spindle.ratio; // speed from 0 - 1;
				if( ratio > 1 ) ratio = 1;
				//Pod->ClearCommand();
				//Pod->Command.commandEnum = USBOUTPUT_PWM;
				int vel =  (int)( ratio * 400.0 );
				if( vel == 0 ) vel = 1;
				//Pod->Command.velocity = vel;
				//Pod->Command.loc = 400 - vel; //send a new PWM duty cycle..
				//Pod->SendCommand();
				Pod->SpinTarget = 400 - vel;
			}

		}

	}
	if( message == RangeStart )
	{
		if( Pod != NULL)
		{
			if( pThread != NULL ) 
			{
				if( monitor != NULL ) return;
				delete pThread;
			}
			pThread = new PodThread( );
			pThread->CreateThread();
		}
	}

   
  
}

void myCleanUp() //used for destrcution of variables prior to exit..  Called as MAch3 shuts down. 
{
   ShutDown = true;	//keep Ethernet reciever from using deleted objects
   if( Pod != NULL )
   {
	   if( MainPlanner->Spindle.PWMEnabled )
	   {
		   Pod->ClearCommand();
		   Pod->Command.commandEnum = USBOUTPUT_PWM;
		   Pod->Command.loc = 400 ; //send a new PWM duty cycle..
		   Pod->SendCommand();
		   Pod->ClearCommand();
		   Pod->Command.axisX = 0xff;
		   Pod->Command.axisY = 0;
		   Pod->SendSimpleCommand( (char)USBOUTPUT );
	   }
		DevProf->WriteProfileInt( "Pod", "DripTime", Pod->DripSel);
		DevProf->WriteProfileInt( "Pod", "Homing", HomingType  );
		CString NumOut;
		_gcvt( PullOff[0], 4 , NumOut.GetBuffer(20) );
	    DevProf->WriteProfileString("Pod","XPullOff", NumOut); 
		_gcvt(PullOff[1], 4 , NumOut.GetBuffer(20) );
	    DevProf->WriteProfileString("Pod","YPullOff", NumOut); 
		_gcvt( PullOff[2], 4 , NumOut.GetBuffer(20) );
	    DevProf->WriteProfileString("Pod","ZPullOff", NumOut); 
		_gcvt( PullOff[3], 4 , NumOut.GetBuffer(20) );
	    DevProf->WriteProfileString("Pod","APullOff", NumOut); 
		_gcvt( PullOff[4], 4 , NumOut.GetBuffer(20) );
	    DevProf->WriteProfileString("Pod","BPullOff", NumOut); 
		_gcvt( PullOff[5], 4 , NumOut.GetBuffer(20) );
	    DevProf->WriteProfileString("Pod","CPullOff", NumOut); 

   }
  // if( monitor != NULL )
	//   if(( (unsigned int)monitor->m_hWnd) != 0xfeeefeee ) monitor->CloseWindow();
    if( Pod != NULL)
	   delete Pod;
	//if( pThread != NULL )
	//	delete pThread;
  
   //delete any variables you use in this section..
   
}


CString	myProfileInit (CString name, CXMLProfile *DevProf)	
// initial access to Mach profile when enumerating available plugins
// Returns the second half on the "pluging id" for the list in Operator
// MachDevice adds the file name at the start of the string

{
	//this gets the default directory DefDir in which Mach3 is located.  and the profile name ex. "Mach3Mill"
	DefDir = DevProf->GetProfileString("Preferences","DefDir","C:\\Mach3\\");
    Profile = DevProf->GetProfileString("Preferences","Profile","Mach3Mill");
	DripSel = DevProf->GetProfileInt("Pod", "DripTime", 0 );
	HomingType =  DevProf->GetProfileInt("Pod", "Homing", 2 );
	PullOff[0] = atof(DevProf->GetProfileString("Pod","XPullOff",".25"));
	PullOff[1] = atof(DevProf->GetProfileString("Pod","YPullOff",".25"));
	PullOff[2] = atof(DevProf->GetProfileString("Pod","ZPullOff",".25"));
	PullOff[3] = atof(DevProf->GetProfileString("Pod","APullOff",".25"));
	PullOff[4] = atof(DevProf->GetProfileString("Pod","BPullOff",".25"));
	PullOff[5] = atof(DevProf->GetProfileString("Pod","CPullOff",".25"));
	return " NcPod PlugIn 2.58.  A.Fenerty B Barker";
} // myProfileInit

void	myInitControl ()
// called during Mach initialisation. You can influence subsequent init by actions here
// **** Not used in typical device plugin

{
    
	MachView->m_PrinterOn = false; //This signifies to MAch that this is an external Control device driver. 
 	//This doesnt mean this device will run, the user will decide what movement device to run in each profile. 
    //use this only for a driver that actually controls pulsing..
	RangeStart  = GetMenuRange( 12 ); //we request 10 menu ID's to use..
	return;
} //myInitControl

 

void	myPostInitControl ()
// called when mach fully set up so all data can be used but initialization  outcomes not affected
{

  if( Pod == NULL)
  {
	Pod = new ncPod();
	if( Pod != 0) Pod->DripSel = DripSel;
    if( !Pod->Connect())
    {
	  delete Pod;
	  Pod = NULL;
    }
  }
  //In the case of a MotionControl plugin, this rouine is only called to tell us to 
  // take over. We HAVE been selected and are now commanded to do whatever it takes 
  // to OWN the IO and movement of this run.
  // If you wish for example, to zero all IO at this point, your free to do so..
 
}

 
 

//This is called by Mach3 when homing is commanded. Relevent axis are in the Engine.Axis status
//word to indicate they should be homed..

void   myHome( short axis)
{
  //Called to add a homing axis.. "axis" is the one to add to current homing if applicable..
  if( Pod != 0) 
	  Pod->Home(axis);
  
}


//This routine is called by Mach3 when a probe should occur. Relevent positions are stored in 
// the MainPlanner as ProbeX, ProbeY..ect..

void  myProbe()
{
    if( !Engine->InSigs[DIGITIZE].Active )
	{
		Pod->SetMachError("Probe called but not turned on.");
	    Engine->State = STOP;
		MainPlanner->OldState = STOP;
		return;
	}
	if( Pod != 0) 
		Pod->DoProbe();
  
}

 



void	myHighSpeedUpdate ()
// called at 40Hz. This is used for Higher Res timing needs. 
// only use as required, it can use alot of system reosurces. 
//not really required in the G100, so Ill leave it blank for now..

{
  static bool intime = false;
  

  if( Pod != NULL && !intime)
	{
		intime = true;
		Pod->Update();
	    intime = false;
	}
	

} // myHighSpeed Update


void	myConfig (CXMLProfile *DevProf)
// Called to configure the device
// Has read/write access to Mach XML profile to remember what it needs to.

{

 if( Pod != NULL)
 {
	if( pThread != NULL ) delete pThread;
	pThread = new PodThread( );
	pThread->CreateThread();
 }	


} // myConfig

void myPurge( short flags)
{
    
 Pod->Command.axisX = Engine->Axis[0].Index;
 Pod->Command.axisY = Engine->Axis[1].Index;
 Pod->Command.axisZ = Engine->Axis[2].Index;
 Pod->Command.axisA = Engine->Axis[3].Index;
 Pod->Command.axisB = Engine->Axis[4].Index;
 Pod->Command.axisC = Engine->Axis[5].Index;
 Pod->Command.loc = 0x3f;
 
    if( (flags & 0x01) != 0) Pod->Command.axisX = 0;
 if( (flags & 0x02) != 0) Pod->Command.axisY = 0;
 if( (flags & 0x04) != 0) Pod->Command.axisZ = 0;
 if( (flags & 0x08) != 0) Pod->Command.axisA = 0;
 if( (flags & 0x10) != 0) Pod->Command.axisB = 0;
 if( (flags & 0x20) != 0) Pod->Command.axisC = 0;

 Pod->SendSimpleCommand(USBSETCOORDSXYZABC);
    
}


void	myUpdate ()
// 10Hz update loop
//Updates the movement device about 10hz rate..
{
    
 
} // myUpdate
  