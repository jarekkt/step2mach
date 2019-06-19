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
#include <wtypes.h>
#include <initguid.h>

#include "MachDevImplementation.h"
#include "shuttlewin.h"
#include "propertiesdlg.h"

extern bool  ShuttleOpened;
extern short ButtonCodes[15]; 
extern CXMLProfile *DevProf;
extern int ProductID;
extern short m_Macro1;
extern short m_Macro2;
extern short m_OEM1;
extern short m_OEM2;


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


ShuttleWin * Shuttle;
 
	

//Templates of control routines.



// ==================================================================================================
//
// Declare helper routines for your code - more obvious here than in your header
//
//====================================================================================================

//  Routines. 

#include "hidsdi.h"
#include <setupapi.h>
#include <dbt.h>




//======================================================================================================
//
// Here are the routines which are called by Mach3 via MachDevice. They are the "meat" of every plugin
//
//====================================================================================================

void myCleanUp() //used for destrcution of variables prior to exit..  Called as MAch3 shuts down. 
{
   delete Shuttle;
   
}


CString	myProfileInit (CString name, CXMLProfile *DevProf)	
// initial access to Mach profile when enumerating available plugins
// Returns the second half on the "pluging id" for the list in Operator
// MachDevice adds the file name at the start of the string

{
	//this gets the default directory DefDir in which Mach3 is located.  and the profile name ex. "Mach3Mill"
	//DefDir = DevProf->GetProfileString("Preferences","DefDir","C:\\Mach3\\");
    //Profile = DevProf->GetProfileString("Preferences","Profile","Mach3Mill");
	return " Contour Shuttle Pendents - A.Fenerty Ver 2.60";
} // myProfileInit

void	myInitControl()
// called during Mach initialisation. You can influence subsequent init by actions here

{
	 
    Shuttle = new ShuttleWin(); 
	Shuttle->Create(NULL,NULL,WS_CHILD , CRect(0,0,10,10),MachView, 1 ); 
   	return;
} //myInitControl

void	myPostInitControl ()
// called when mach fully set up so all data can be used but initialization  outcomes not affected

{

  CString form;
	for( int x = 0; x < 15; x++ )
	{
	 form.Format("BUTTON%d",x);
	 ButtonCodes[x] = DevProf->GetProfileInt("Shuttle",form,0);
  	}
	ProductID = DevProf->GetProfileInt("Shuttle","Product",0x30 );
	ShuttleOpened = Shuttle->GetHIDDevice();

	m_Macro1 = DevProf->GetProfileInt("Shuttle","Macro1",00 );
	m_Macro2 = DevProf->GetProfileInt("Shuttle","Macro2",00 );
	m_OEM1 = DevProf->GetProfileInt("Shuttle","OEM1",00 );
	m_OEM2 = DevProf->GetProfileInt("Shuttle","OEM2",00 );
     
  return;
} //myPostInitControl
 
  
 


void	myConfig (CXMLProfile *DevProf)
// Called to configure the device
// Has read/write access to Mach XML profile to remember what it needs to.

{


	CString form;
	for( int x = 0; x < 15; x++ )
	{
	 form.Format("BUTTON%d",x);
	 ButtonCodes[x] = DevProf->GetProfileInt("Shuttle",form,0);
  	}
	ProductID = DevProf->GetProfileInt("Shuttle","Product",0x30 );
	propertiesdlg *dlg = new propertiesdlg();
	dlg->DoModal();
	delete dlg;
    for( int x = 0; x < 15; x++ )
	{
	 form.Format("BUTTON%d",x);
	 DevProf->WriteProfileInt("Shuttle",form,ButtonCodes[x]);
  	}
    DevProf->WriteProfileInt("Shuttle","Product",ProductID);
	DevProf->WriteProfileInt("Shuttle","Macro1",m_Macro1);
	DevProf->WriteProfileInt("Shuttle","Macro2",m_Macro2);
	DevProf->WriteProfileInt("Shuttle","OEM1",m_OEM1 );
	DevProf->WriteProfileInt("Shuttle","OEM2",m_OEM2 );


} // myConfig

void	myUpdate ()
// 10Hz update loop
//Updates the G100 10 times a second.
{

 
// Check here for disconnection for G100. If more than 1/2 second has passed and no ethernet message, trigger an EStop
// Inputs to InActive..
 
    
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
 