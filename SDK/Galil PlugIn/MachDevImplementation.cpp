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
#include "dmcwin.h"
#include "MachDevImplementation.h"
#include "GalilStructs.h"
#include "GalilControl.h"
#include "GalilConfig.h"
// --------------------------------------->>>>>>> See this file for the Mach functions that can be
//												called and the pointers to the variable blocks.
//#include "xxxxxxxx.h"					// add includes for code you call here

#include <mmsystem.h>
#include <math.h>
 
 
extern GalilStruct State;
// ==================================================================================================
// 
// Global variables for this code 
//
// ===================================================================================================
 
 
extern CMach4View *MachView;
bool ShutDown = false;
CString DefDir,Profile;
GalilStruct  Galil;
GalilControl *GUnit; 
	

//Templates of control routines.



// ==================================================================================================
//
// Declare helper routines for your code - more obvious here than in your header
//
//====================================================================================================

//  Routines. 
CString	myProfileInit (CString name, CXMLProfile *DevProf)	
// initial access to Mach profile when enumerating available plugins
// Returns the second half on the "pluging id" for the list in Operator
// MachDevice adds the file name at the start of the string

{
	//this gets the default directory DefDir in which Mach3 is located.  and the profile name ex. "Mach3Mill"
	DefDir = DevProf->GetProfileString("Preferences","DefDir","C:\\Mach3\\");
    Profile = DevProf->GetProfileString("Preferences","Profile","Mach3Mill");
    //initial load of program vars.
	 m_UseRefPostion = DevProf->GetProfileInt("Preferences","RefPos",1) == 1;
     m_UseCalcSpeed  = DevProf->GetProfileInt("Preferences","CalcSpeed",1) == 1;
	 //set the default motor types..
	State.motortype[0] = DevProf->GetProfileInt("Galil","MotorType1",3);
	State.motortype[1] = DevProf->GetProfileInt("Galil","MotorType2",3);
	State.motortype[2] = DevProf->GetProfileInt("Galil","MotorType3",3);
	State.motortype[3] = DevProf->GetProfileInt("Galil","MotorType4",3);
	State.motortype[4] = DevProf->GetProfileInt("Galil","MotorType5",3);
	State.motortype[5] = DevProf->GetProfileInt("Galil","MotorType6",3);
	State.nSpindle = DevProf->GetProfileInt("Galil","Spindle_Axis",-1);
	m_UseVectorDecel = DevProf->GetProfileInt("Galil","VectorDecel",300000);
	m_UseVectorTimeConst = atof(DevProf->GetProfileString("Galil","UseVectorDecel","1"));
	State.HomeData.UseIndex[0] =  DevProf->GetProfileInt("Galil", "X_Index", 0);
	State.HomeData.UseIndex[1] =  DevProf->GetProfileInt("Galil", "Y_Index", 0);
	State.HomeData.UseIndex[2] =  DevProf->GetProfileInt("Galil", "Z_Index", 0);
	State.HomeData.UseIndex[3] =  DevProf->GetProfileInt("Galil", "A_Index", 0);
	State.HomeData.UseIndex[4] =  DevProf->GetProfileInt("Galil", "B_Index", 0);
	State.HomeData.UseIndex[5] =  DevProf->GetProfileInt("Galil", "C_Index", 0);
	
	
	return " Galil PlugIn - A.Fenerty B.Barker Ver .1a";
} // myProfileInit

 
//======================================================================================================
//
// Here are the routines which are called by Mach3 via MachDevice. They are the "meat" of every plugin
//
//====================================================================================================

void myCleanUp() //used for destrcution of variables prior to exit..  Called as MAch3 shuts down. 
{
   ShutDown = true;
  // GUnit->CloseWindow();
   delete GUnit;
}

void myReset() //used for destrcution of variables prior to exit..  Called as MAch3 shuts down. 
{
   
  if( GUnit != NULL )GUnit->ResetControl();
  
}



void	myInitControl ()
// called during Mach initialisation. You can influence subsequent init by actions here
// **** Not used in typical device plugin

{

	MachView->m_PrinterOn = false;  // Tell Mach3 we are a movement plugin. 
	ShutDown = false;  //this will be set to true as we shut down.
	GUnit = new GalilControl();     //create a new window just for Galil's. 
	
	return;
} //myInitControl

void	myPostInitControl ()
// called when mach fully set up so all data can be used but initialization  outcomes not affected

{
  //In the case of a MotionControl plugin, this rouine is only called to tell us to 
  // take over. We HAVE been selected and are now commanded to do whatever it takes 
  // to OWN the IO and movement of this run.
  // If you wish for example, to zero all IO at this point, your free to do so..

  GUnit->Create( NULL, "Galil", WS_DISABLED , CRect(0,0,0,0), MachView, 55555);
  GUnit->ShowWindow( SW_HIDE );
  GUnit->Connect();
  return;
} //myPostInitControl


//This is called by Mach3 when homing is commanded. Relevent axis are in the Engine.Axis status
//word to indicate they should be homed..

void   myHome( short axis)
{
	GUnit->HomeAxis(axis);

} //Called to add a homing axis.. "axis" is the one to add to current homing if applicable..
void  myProbe(){ }; //OK, we have a probe command. So we need to activate the Halt mask, check to see its on, then do the move..


void	myConfig (CXMLProfile *DevProf)
{
    GalilConfig *fig = new GalilConfig();
	fig->DoModal();
    delete fig;
	CString NumOut;
	//restore globals here..
	DevProf->WriteProfileInt("Preferences","RefPos",m_UseRefPostion);
    DevProf->WriteProfileInt("Preferences","CalcSpeed", m_UseCalcSpeed);
	DevProf->WriteProfileInt("Galil","MotorType1",State.motortype[0]);
	DevProf->WriteProfileInt("Galil","MotorType2",State.motortype[1]);
	DevProf->WriteProfileInt("Galil","MotorType3",State.motortype[2]);
	DevProf->WriteProfileInt("Galil","MotorType4",State.motortype[3]);
	DevProf->WriteProfileInt("Galil","MotorType5",State.motortype[4]);
	DevProf->WriteProfileInt("Galil","MotorType6",State.motortype[5]);
	DevProf->WriteProfileInt("Galil","Spindle_Axis",State.nSpindle);
	DevProf->WriteProfileInt("Galil","VectorDecel",m_UseVectorDecel);
	_gcvt( m_UseVectorTimeConst, 4 , NumOut.GetBuffer(20) );
    DevProf->WriteProfileString("Galil","UseVectorDecel", NumOut); 
	DevProf->WriteProfileInt("Galil", "X_Index", State.HomeData.UseIndex[0]);
	DevProf->WriteProfileInt("Galil", "Y_Index", State.HomeData.UseIndex[1]);
	DevProf->WriteProfileInt("Galil", "Z_Index", State.HomeData.UseIndex[2]);
	DevProf->WriteProfileInt("Galil", "A_Index", State.HomeData.UseIndex[3]);
	DevProf->WriteProfileInt("Galil", "B_Index", State.HomeData.UseIndex[4]);
	DevProf->WriteProfileInt("Galil", "C_Index", State.HomeData.UseIndex[5]);
	

};	//this will open the Config Dialogs.



void	myUpdate ()
// 10Hz update loop
//Updates the G100 10 times a second.
{
  



} // myUpdate

void myNotify(int message)
{
  if( message == -1 )
  {
	  if( State.Connected)
		GUnit->Stop( );

  }
}

void	myHighSpeedUpdate ()
{
	if( !ShutDown && State.Connected ) 
	  GUnit->Update();  
 

}; // myHighSpeed Update
void MyJogOn( short axis, short dir, double speed)
{ 
	if( State.Connected)
		GUnit->JogOn( axis, dir, speed );

};           //Routines to start and stop Jogging..
void MyJogOff(short axis)
{

     if( State.Connected)
		GUnit->JogOff( axis );

};
void myDwell( double time){ };
void myPurge( short flags){ };            
 