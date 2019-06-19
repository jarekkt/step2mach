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
#include "Winuser.h"
#include "menuhandler.h"
#include "mainconfig.h"



extern CMach4View *MachView;
MenuHandler *Menus = NULL;
extern CXMLProfile *DevProf;


#include "MachDevImplementation.h"
// --------------------------------------->>>>>>> See this file for the Mach functions that can be
//												called and the pointers to the variable blocks.
//#include "xxxxxxxx.h"					// add includes for code you call here

#include <mmsystem.h>
#include <math.h>
 
 

// ==================================================================================================
// 
// Global variables for this code 
//
// ===================================================================================================
 

extern CMach4View *MachView;
 
	

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

void myCleanUp() //used for destrcution of variables prior to exit..  Called as Mach3 shuts down. 
{
    CString NumOut;	
  	_gcvt( Menus->m_length , 4 , NumOut.GetBuffer(20) );
    DevProf->WriteProfileString("Probe3d", "Length", NumOut);
	_gcvt( Menus->m_width , 4 , NumOut.GetBuffer(20) );
    DevProf->WriteProfileString("Probe3d", "Width", NumOut);
	_gcvt( Menus->m_XGrid , 4 , NumOut.GetBuffer(20) );
    DevProf->WriteProfileString("Probe3d", "XGrid", NumOut);
	_gcvt( Menus->m_YGrid , 4 , NumOut.GetBuffer(20) );
    DevProf->WriteProfileString("Probe3d", "YGrid", NumOut);
	_gcvt( Menus->m_ProbeRad , 4 , NumOut.GetBuffer(20) );
    DevProf->WriteProfileString("Probe3d", "ProbeDia", NumOut);
	_gcvt( Menus->m_probedist , 4 , NumOut.GetBuffer(20) );
    DevProf->WriteProfileString("Probe3d", "ProbeDepth", NumOut);
	_gcvt( Menus->m_clearance , 4 , NumOut.GetBuffer(20) );
    DevProf->WriteProfileString("Probe3d", "Clearance", NumOut);
	 _gcvt( Menus->m_feedrate , 4 , NumOut.GetBuffer(20) );
    DevProf->WriteProfileString("Probe3d", "FeedRate", NumOut); 
    _gcvt( Menus->m_probestuck , 4 , NumOut.GetBuffer(20) );
    DevProf->WriteProfileString("Probe3d", "ProbeStuck", NumOut); 
 
	
   
	delete Menus;
}


CString	myProfileInit (CString name, CXMLProfile *DevProf)	
// initial access to Mach profile when enumerating available plugins
// Returns the second half on the "pluging id" for the list in Operator
// MachDevice adds the file name at the start of the string

{
	//this gets the default directory DefDir in which Mach3 is located.  and the profile name ex. "Mach3Mill"
	//DefDir = DevProf->GetProfileString("Preferences","DefDir","C:\\Mach3\\");
    //Profile = DevProf->GetProfileString("Preferences","Profile","Mach3Mill");
	
 
	return " 3d Digitising Fenerty Barker Version 2.00.046";
} // myProfileInit

void	myInitControl ()
// called during Mach initialisation. You can influence subsequent init by actions here
// **** Not used in typical device plugin
{
	 Menus = new MenuHandler();
	 Menus->RangeStart  = GetMenuRange( 15 ); //we request 10 menu ID's to use..
 	
     
 	 return;

} //myInitControl


//Used only by plugins that use menus. This is called when a plugin Menu item is used. 

void	myNotify ( int ID)
 
{

	if( ID == -1 ) //general Stop and Clear command
	{
		if( Menus != NULL )
		{
		   if(Menus->SEQUENCE != SEQNONE )
			   Menus->SetMachError("Probe Sequence Canceled.");
		   Menus->SEQUENCE = SEQNONE;
		   Engine->Axis[0].Memory[6] = 0; //turn off the Jog probe..
		}
	}
	else
	Menus->DoMenuItem( ID ); 

} //myInitControl


void	myPostInitControl ()
// called when mach fully set up so all data can be used but initialization  outcomes not affected

{
  //We'll read the configuration here as Profiles are allowed to be used in this routine..
  if( Menus != NULL )
  {
     Menus->InitMenus();
     
  }
 
  return;
} //myPostInitControl


  
 
CMenu addon;

void	myConfig (CXMLProfile *DevProf)
// Called to configure the device
// Has read/write access to Mach XML profile to remember what it needs to.

{
   MainConfig *cfg = new MainConfig();
   cfg->DoModal();
   delete cfg;

} // myConfig

void	myUpdate ()
// 10Hz update loop
//Updates the G100 10 times a second.
{
    static bool InCall = false; //semaphore for reiterative stopping..

	if( InCall ) return;
	InCall = true;
	//Here we just call the sequencer in the menu handler..
    //this will run a sequence of operations one step at a time..
	if( Menus != NULL )
		Menus->Sequencer();

	InCall = false;
     
} // myUpdate

void	myHighSpeedUpdate ()
// called at 40Hz. This is used for Higher Res timing needs. 
// only use as required, it can use alot of system reosurces. 
//not really required in the G100, so Ill leave it blank for now..

{

	

} // myHighSpeed Update
 
// ======================================================================================================
//
// The Helpers follow
//
//=======================================================================================================

// put your helper routines here

//This is a helper for Debug Messages. Mach3's MainPlanner->DebugRun var makes messages fill the file up during a run.




//All the following code runs th evarious phases of the G100. 

///PHASE Code. The thing to remember about phase fucntions below, is they are all called 10 times a second whan their phase is active;

//Discovery. This guys job is to open the G100 in the event of boot, attach, or reflash timeouts. It allows for an asyncronous way 
//           to attach to a G100 thats on the network. Furture work: Attach to selection of devices. 
 