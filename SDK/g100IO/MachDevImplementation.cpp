//TABS=3
// MachDevImplementation.cpp 
// This is the place where the implementor puts his/her code to actually implement the plugin
//
// -----------------------------------------------------------------------------------------------------
// Revision History:
// 7  Jun 2006 - JAP - Separated from MachDevice
// 21 Oct 2006 - SJH - Changed to use common G100 library
// -----------------------------------------------------------------------------------------------------

 

#include "stdafx.h"		// For use of precompiled headers
#include "resource.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "XMLProfile.h"
#include "MachDevice.h"
#include "G100-Structs.h"		// Includes protocol messages and common G100 library
#include "G100Config.h"
#include "G100General.h"
#include "GRexControl.h"
#include "MyHandler.h"
#include "G100FLASHCONFIG.h"
#include "Monitoring.h"

//#include "vldapi.h" //uncomment for leak detection tracing..
//#include "vld.h"

CString VerString = "&G100IO V2.49.00 Config ";

Monitoring *Monitor = NULL;

bool IPValid = false;;
unsigned int  IP = 0;
int m_AnaSel;
bool m_SpinAnaOff;
double m_CVRadius;
double m_MaxDev;

double ASC;
int MPGs[3];

// See this file for the Mach functions that can be called and the pointers to the variable blocks.
#include "MachDevImplementation.h"


#include <mmsystem.h>
#include <math.h>
 
#pragma warning(disable:4244 4554)	// We're cool with double -> WTSDDA conversions


// ==================================================================================================
// 
// Global variables for this code 
//
// ===================================================================================================
 
CString DefDir;  // the default directory Mach is placed in.
CString Profile; // the name of the profile .. e.g. "Mach3Mill"

extern setup * _setup;
extern CXMLProfile *DevProf;

//control of status opening.
bool OpenMonitor = false;
bool ShutDown = false;
int RangeStart = 0;

//our G100 controller.

GRexControl *TheRex = NULL;
MyHandler   *myG100handler;
int GLookAhead;
 
//======================================================================================================
//
// Here are the routines which are called by Mach3 via MachDevice. They are the "meat" of every plugin
//
//====================================================================================================


// Used for destruction of variables prior to exit..  Called as MAch3 shuts down.

void myCleanUp() 
{

	//spindle paramters
	ShutDown = true;
	if( TheRex != NULL)
	{
		TheRex->ShutDown();
	    delete TheRex;
		 
	}
	if( Monitor != NULL)
		delete Monitor;
}

//System Notifications.

void myNotify(int message)
{
	bool test = MainPlanner->m_ExternalFeedHold;
	if( message == -1 )
	{
		if( TheRex != NULL)
		{
			TheRex->UserStop();
		}

	}
	if( message == EX_SPINON || message == EX_SPINSPEED || message == EX_SPINOFF ) //this is Spindle ON;..
	{
		if( TheRex != NULL)
		{
			TheRex->SpinOn( message );
		}

	}

	if( message == EX_FEEDHOLD ) //General Setup required..
	{
		if( TheRex != NULL)
		{
			TheRex->FeedHold();
			MainPlanner->m_ExternalPaused = true;
		}

	}

	if( message == EX_RUN ) //Run request.
	{
		if( TheRex != NULL)
		{
			TheRex->Run();
		}

	}

	if( message == EX_SETUP ) //General Setup required..
	{
		if( TheRex != NULL)
		{
			TheRex->NeedSetup();
		}

	}
	if( message == EX_MOTORTUNED )
	{
       //the motors have just been tuned..
      
	}
	if( message == RangeStart )
	{
	  if(Monitor == NULL )
	  {
	    Monitor = new Monitoring();
		Monitor->Create(IDD_MONITOR,MachView);
		Monitor->ShowWindow(SW_SHOW);
	  }
	}

}

//Used for menu modifications in MAch3.

int FindMenuItem(CMenu* Menu, LPCTSTR MenuString)
{
	ASSERT(Menu);
	ASSERT(::IsMenu(Menu->GetSafeHmenu()));

	int count = Menu->GetMenuItemCount();
	for (int i = 0; i < count; i++)
	{
		CString str;
		if (Menu->GetMenuString(i, str, MF_BYPOSITION) &&
			(strcmp(str, MenuString) == 0))
			return i;
	}

	return -1;
}


// Initial access to Mach profile when enumerating available plugins
// Returns the second half on the "plugin id" for the list in Operator
// MachDevice adds the file name at the start of the string

CString	myProfileInit (CString name, CXMLProfile *DevProf)	
{
	//Standard Init at startup of Mach3, G100 will not necessarily be in control.
	//this gets the default directory DefDir in which Mach3 is located.  and the profile name ex. "Mach3Mill"
	DefDir = DevProf->GetProfileString("Preferences","DefDir","C:\\Mach3\\");
	Profile = DevProf->GetProfileString("Preferences","Profile","Mach3Mill");
	IP = DevProf->GetProfileInt("G100Param", "IPAddress", 0);
    m_AnaSel = DevProf->GetProfileInt("G100Param", "AnaSel", 0);
    m_SpinAnaOff = DevProf->GetProfileInt("G100Param", "SpinAnaOff", 1) == 1;
	MPGs[0] = DevProf->GetProfileInt("G100Param", "MPG0", 0);
	MPGs[1] = DevProf->GetProfileInt("G100Param", "MPG1", 0);
	MPGs[2] = DevProf->GetProfileInt("G100Param", "MPG2", 0);

	
	return " - G100 IO Device 2.49";
} // myProfileInit



// Called during Mach initialisation. You can influence subsequent init by actions here

void	myInitControl ()
{
	//Standard Init, Mach3 still may or may not take control using this device..
    //no setitng f printer off, so no conflict with other movement devices..	 

	RangeStart  = GetMenuRange( 2 ); //we request 2 menu ID's to use..

} //myInitControl



// Called when mach fully set up so all data can be used but initialization outcomes not affected

void myPostInitControl ()
{
    //This gets called if we WILL be using the G100 as our controller.
	// The user has selected it, and Mach3 is now trying to start it up..
    //We'll now construct the G100 controller, "TheRex" from now on. It will take
	//care of initilization in its constructor.
	TheRex = new GRexControl(); //No checks should be necessary, this only gets called once..
	TheRex->msg_stamp.setTimeout(0);
   static bool menued = false;
	if( !menued)
	{
		menued = true;
		CFrameWnd *MachFrame = MachView->MachFrame;
		CMenu *menu = MachFrame->GetMenu();
		HMENU hSubmenu = CreatePopupMenu();
		int pos = FindMenuItem(menu,"PlugIn Control");
		//here we can add menu items to MAch3's menu..
		int x = pos;
		HMENU control = GetSubMenu( menu->m_hMenu, pos);
		InsertMenu ( control, -1, MF_BYPOSITION, RangeStart , _T("G100 Monitoring") );
		MachFrame->DrawMenuBar();
	}
	MainPlanner->m_UsingTCPIO = true; //tell Mach3 that MPG's are coming in from a g100..


} //myPostInitControl


// This is called by Mach3 when homing is commanded. Relevant axis are in the Engine.Axis status
// word to indicate they should be homed.

void   myHome( short axis)
{
	 
}
// This routine is called by Mach3 when a probe should occur. Relevant positions are stored in 
// the MainPlanner as ProbeX, ProbeY..ect..

void  myProbe()
{
	//pass Probe command to the G100
	 
  
}

// Called to configure the device
// Has read/write access to Mach XML profile to remember what it needs to.

void	myConfig (CXMLProfile *DevProf)
{
	
	AfxMessageBox("Unused");
} // myConfig



// 10Hz update loop
// Updates the G100 10 times a second.
static int upd_count = 0;

void	myUpdate ()
{
 //this will stop any thread re-entry when updating the G100

 static bool reenter = false;
 if( reenter ) return;
 reenter = true;

	if( TheRex != NULL ) 
	{
		TheRex->Update();
	}
 reenter = false; 		

} // myUpdate


// Called at 40Hz. This is used for Higher Res timing needs. 
// only use as required, it can use a lot of system resources. 

void	myHighSpeedUpdate ()
{

	if( TheRex != NULL ) 
	{
		TheRex->Update40Hz();
	}
	

} // myHighSpeed Update

void myPurge( short flags)
{
	 

}

void myDwell( double time)
{
	 
	
}

void myReset()
{
	 

}

void MyJogOn( short axis, short direction, double SpeedNorm)
{
 
	
}

void  MyJogOff(short axis)
{
 

}




