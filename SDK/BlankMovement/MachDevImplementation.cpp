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


extern TrajectoryControl *MainPlanner; //used for most planner funcitons and program control 
extern CMach4View *MachView;  //used for most framework and configuration calls. 
extern TrajBuffer *Engine;     //Ring0 memory for printer port control and other device syncronisation
extern setup *_setup;          //Trajectory planners setup block. Always in effect




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
 
CUDPSocket  *g100sock = NULL;
bool   ShutDown = false;
 
CString DefDir;  //the default directoy Mach is placed in.
CString Profile; //the name of the profile .. ex. "Mach3Mill"
 
 
	

//Templates of control routines.



// ==================================================================================================
//
// Declare helper routines for your code - more obvious here than in your header
//
//====================================================================================================

//  Routines. 

 
void DoDigOutput();                         //Send the Digital IO data to the G100
 
 
//======================================================================================================
//
// Here are the routines which are called by Mach3 via MachDevice. They are the "meat" of every plugin
//
//====================================================================================================

void myCleanUp() //used for destrcution of variables prior to exit..  Called as MAch3 shuts down. 
{
   ShutDown = true;	//keep Ethernet reciever from using deleted objects
  
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
	return " Generic Movement PlugIn - A.Fenerty Ver 1.1a";
} // myProfileInit

void	myInitControl ()
// called during Mach initialisation. You can influence subsequent init by actions here
// **** Not used in typical device plugin

{
    
	MachView->m_PrinterOn = false; //This signifies to MAch that this is an external Control device driver. 
 	//This doesnt mean this device will run, the user will decide what movement device to run in each profile. 
    //use this only for a driver that actually controls pulsing..
	return;
} //myInitControl

void	myPostInitControl ()
// called when mach fully set up so all data can be used but initialization  outcomes not affected

{
  //In the case of a MotionControl plugin, this rouine is only called to tell us to 
  // take over. We HAVE been selected and are now commanded to do whatever it takes 
  // to OWN the IO and movement of this run.
  // If you wish for example, to zero all IO at this point, your free to do so..


  //First, lets add a message tracking facility to handle message traffic output.
  //Output is in its own class because its important that we do not overrun the G100's
  //buffers or queues. We'll make the tracker object intelligent enough to be able to handle any errors, retransmissions
  // and trackign ack numbers and such..
//First lets open a Debug File. We'll only use it if instructed by Mach3's DebugThisRun selection in config/state

  
  
}

 
 

//This is called by Mach3 when homing is commanded. Relevent axis are in the Engine.Axis status
//word to indicate they should be homed..

void   myHome( short axis)
{
  //Called to add a homing axis.. "axis" is the one to add to current homing if applicable..
  
}


//This routine is called by Mach3 when a probe should occur. Relevent positions are stored in 
// the MainPlanner as ProbeX, ProbeY..ect..

void  myProbe()
{
  //OK, we have a probe command. So we need to activate the Halt mask, check to see its on, then do the move..
  
}

 



void	myHighSpeedUpdate ()
// called at 40Hz. This is used for Higher Res timing needs. 
// only use as required, it can use alot of system reosurces. 
//not really required in the G100, so Ill leave it blank for now..

{

	

} // myHighSpeed Update


void	myConfig (CXMLProfile *DevProf)
// Called to configure the device
// Has read/write access to Mach XML profile to remember what it needs to.

{
	
     AfxMessageBox( "no config implemented" );

} // myConfig

void myPurge( short flags)
{
    
	//sent to zero an axis or reset hardware to 0,0,0 or empty messages depending on the flag.
    
}


void	myUpdate ()
// 10Hz update loop
//Updates the movement device about 10hz rate..
{
   GetInputs();
   SetOutputs();
   SendHoldingMovement();
   HandleSequences();
 
} // myUpdate
  