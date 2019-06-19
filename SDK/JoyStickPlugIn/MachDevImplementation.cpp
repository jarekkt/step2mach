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

#include "MachDevImplementation.h"
// --------------------------------------->>>>>>> See this file for the Mach functions that can be
//												called and the pointers to the variable blocks.
//#include "xxxxxxxx.h"					// add includes for code you call here

#include <mmsystem.h>
#include <math.h>
#include "JoySetup.h"


// ==================================================================================================
// 
// Global variables for this code 
//
// ===================================================================================================

bool JoyStickOn;
bool IgnoreStick;
int  XJoyAxis = 0, YJoyAxis = 1;
int  Accs[6]; // holder for acceleration
int  Vels[6];  // holder for maximum velocities
int  AccSecX, VelMaxX;
int  AccSecY, VelMaxY;
bool TrackingX = false;
bool TrackingY = false;
double ScaleX, ScaleY;  // % of move in each axis by JoyStick Command;
int ReadStick = 0;
bool Enabled = false;

//Templates of JotStick control routines.



// ==================================================================================================
//
// Declare helper routines for your code - more obvious here than in your header
//
//====================================================================================================

//JoyStick Routines. 

bool CheckJoyStick();
void JogByStick();
void SetupJoyStick( CXMLProfile *DevProf);



//======================================================================================================
//
// Here are the routines which are called by Mach3 via MachDevice. They are the "meat" of every plugin
//
//====================================================================================================

void myCleanUp() //used for destrcution of variables prior to exit..
{

}


CString	myProfileInit (CString name, CXMLProfile *DevProf)	
// initial access to Mach profile when enumerating available plugins
// Returns the second half on the "pluging id" for the list in Operator
// MachDevice adds the file name at the start of the string

{
	SetupJoyStick( DevProf );  
	return " JoyStick PlugIn- Art Fenerty Ver 1.0a";
} // myProfileInit

void	myInitControl ()
// called during Mach initialisation. You can influence subsequent init by actions here
// **** Not used in typical device plugin

{
	JoyStickOn = false;     //Set The startup Implementation of the JoyStick to Off so it gets checked at startup.
    IgnoreStick = false;    // If any Cal error is seen, turn off the JoyStick for safety. JoyStick must be centered at Startup
	return;
} //myInitControl

void	myPostInitControl ()
// called when mach fully set up so all data can be used but initialization  outcomes not affected

{
		return;
} //myPostInitControl

void	myConfig (CXMLProfile *DevProf)
// Called to configure the device
// Has read/write access to Mach XML profile to remember what it needs to.

{
	 JoySetup *joy = new JoySetup();
	 Engine->JoyOn = Enabled;
	 joy->m_JoyOn = Engine->JoyOn;
     joy->DoModal();
     DevProf->WriteProfileInt("JogPlugIn","JogPlugHoriz",joy->m_Horiz);
     DevProf->WriteProfileInt("JogPlugIn","JogPlugVert",joy->m_Vert);
	 DevProf->WriteProfileInt("JogPlugIn","JogStartEnabled",joy->m_JoyOn);
	 Enabled  = joy->m_JoyOn == 1;
	 Engine->JoyOn = Enabled;
	 XJoyAxis = joy->m_Horiz;
	 YJoyAxis = joy->m_Vert;
     delete joy; 

} // myConfig

void	myUpdate ()
// 10Hz update loop
//Updates the JoyStick 10 times a second.

{
	if( !Engine->JoyOn && Enabled ) Engine->JoyOn = true;
	if( !JoyStickOn && Engine->JoyOn && !IgnoreStick )  //Check JoyStick is calibrated before turning it on.
	{
      if( CheckJoyStick() ) JoyStickOn = true;  //Allow Stick if it is currently centered.
	  else
	  {
		  IgnoreStick = true; //Turn off plugin till Calibrated JoyStick is seen. Restart Program.
		  AfxMessageBox(" Disabling JoyStick. Fails Config test. Check connections, calibrate it, then restart program. ", MB_OK );
	  }
     
	}

	if( JoyStickOn && Engine->JoyOn )
	{
	  //JoyStick has passed calibration routines and is Turned on in Mach3, so allow jogging..
      JogByStick(); //this will be called 10 times a second for variable speed jogging ..
	}
	return;
} // myUpdate

void	myHighSpeedUpdate ()
// called at 40Hz. Unused by the JoyStick
{

} // myHighSpeed Update

// ======================================================================================================
//
// The Helpers follow
//
//=======================================================================================================

// put your helper routines here

//The Following Routines are added to add a JoyStick to this device.


//////////////////////////////////////This routine calibrates Joystick speeds. Call it if the motor tuning has changed. 
//                                    Since startup, or at least once AT startup..
void SetupJoyStick( CXMLProfile *DevProf)
{

   XJoyAxis = DevProf->GetProfileInt("JogPlugIn","JogPlugHoriz",0);
   YJoyAxis = DevProf->GetProfileInt("JogPlugIn","JogPlugVert",1);
   Enabled = Engine->JoyOn =  DevProf->GetProfileInt("JogPlugIn","JogStartEnabled",0) == 1;
   //set String variable to get calibration data from the system xml file.
   CString Vel,Acc,Steps;
   Vel.Format( "Vel%d", XJoyAxis);
   Acc.Format( "Acc%d", XJoyAxis);
   Steps.Format("Steps%d",XJoyAxis);
  
   double m_Velocity,m_Acceleration,m_StepsPerUnit;
   m_Velocity =     atof(DevProf->GetProfileString("Preferences",Vel, "2.0"));  //get the JogX axis Velocity
   m_Acceleration = atof(DevProf->GetProfileString("Preferences",Acc , "4.0")); // and acceleration
   m_StepsPerUnit = atof(DevProf->GetProfileString("Preferences",Steps ,"1000.0"));  //and steps/unit
   AccSecX = (int) (m_Acceleration * (m_StepsPerUnit/ Engine->PPS) * 2048); //calculate on engine current frequency
   VelMaxX =  (int)(m_Velocity     * (m_StepsPerUnit/ Engine->PPS) * (Engine->PPS*2048)); //and fastest step speed allowed.
 
   //now do the same for the YJogstick axis..
   Vel.Format( "Vel%d", YJoyAxis);
   Acc.Format( "Acc%d", YJoyAxis);
   Steps.Format("Steps%d", YJoyAxis);

   m_Velocity = atof(DevProf->GetProfileString("Preferences",Vel, "2.0"));
   m_Acceleration = atof(DevProf->GetProfileString("Preferences",Acc , "4.0"));
   m_StepsPerUnit = atof(DevProf->GetProfileString("Preferences",Steps ,"1000.0"));
 
   AccSecY = (int) (m_Acceleration * (m_StepsPerUnit/Engine->PPS) * 2048);
   VelMaxY =  (int)(m_Velocity     * (m_StepsPerUnit/Engine->PPS) * (Engine->PPS*2048));
  
   Accs[  XJoyAxis ] = AccSecX; Vels[  XJoyAxis ] = VelMaxX;  //now we have the max accelaeration and velocity of each
   Accs[  YJoyAxis ] = AccSecY; Vels[  YJoyAxis ] = VelMaxY;  //axis of the joystick..

}

//////////////////////////////////// This routine checks the JoyStick is centered at program start, runaway would be dangerous.
bool CheckJoyStick()
{

JOYINFO joy;
if( !Engine->JoyOn && Enabled ) Engine->JoyOn = true;
for( int x = 0; x < 4; x++ )
{
  MMRESULT test = joyGetPos(x , &joy); 
  ReadStick = x;  //Find an Active JoyStick..
  if( test == 0 ) break;
}

if ( ReadStick == 3 ) 
{
    return false;  // 0, 1 and 2 are not responding.. So kill the JoySticks..
}
 
if(  joy.wXpos > 42000  || joy.wXpos < 22000 || joy.wYpos < 22000 || joy.wYpos > 42000) 
  {
    MainPlanner->m_JoyOn = false;
    Engine->JoyOn = false; //send message to user that JoyStick has been disabled till program restart.
	return false;
  }
return true;
 
}

//////////////////////  This routine actually controls jogging the various axis by JoyStick, variable speed depending on the position of the stick. 
//We'll vary from 0% to 100% of stick deflection
#define HI 42000  // Level above which Jog is turned on in forward.
#define LO 22000  // Level below which Jog is turned on in reverse direction


void JogByStick()
{
  JOYINFO joy;
   //this static will remember if Jogging is currently underway
  static bool joyjog = false;
  static bool JogOn[2] = { false , false };
  //get JoyStick position.
  MMRESULT test = joyGetPos(ReadStick   , &joy);  
  //If the Engine is running anything, or Estopped, exit out..
  //Mach3 will stop the Jog when those states arise, no need to babysit them.
  if( Engine->State != STOP || Engine->EStop) { TrackingX = TrackingY = false; return; }	
  //position of the JoyStick X and Y deflection
  int XPos = joy.wXpos; // 0 - 0xffff , 0x7fff is centered and no jog..
  int YPos = joy.wYpos;
  
  //assume they are off
  bool XOn = false, YOn = false;
  if( XPos > HI || XPos < LO ) XOn = true;   // See if we should be jogging in JogX 
  if( YPos > HI || YPos < LO ) YOn = true;   // Same for Y

  //If we're not tracking a previous jog, just exit, if tracking previous and Joy is centered, tell it to decelerate to a stop.
  if( !TrackingX && !TrackingY && !XOn && !YOn ) return;

  // XPos and YPos are now equal to the joystick values;
  // and something should be jogging. Otherwise we have left by now..
  
  // Engine->PPS is th ePulsesPerSecond Mach3 is programmed for 25K, 35K or 45K..

   static int XDir,YDir;
   if(  XPos >= HI ) { ScaleX = ((double)XPos - HI) / Engine->PPS; XDir = 0; }
	    else    
	if( XPos <= LO)  { ScaleX = ((double)LO  -XPos) / Engine->PPS; XDir = 1; }

   if(  YPos >= HI ) { ScaleY = ((double)YPos - HI) / Engine->PPS; YDir = 1; }
	    else        
	if( YPos <= LO)  { ScaleY = ((double)LO  -YPos) / Engine->PPS; YDir = 0; }

	//_setup->JogPercent is the setting the user has set for his Jog%
		
   ScaleX = fabs( ScaleX ) * (_setup->JogPercent / 100); // this is percent of X movement scaled by Max Jog % rate
   ScaleY = fabs( ScaleY ) * (_setup->JogPercent / 100); // this is percent of Y movement scaled by max Jog % rate

   double MaxX = ((double)VelMaxX) * ScaleX;  // speed of x
   double MaxY = ((double)VelMaxY) * ScaleY;  // speed of Y

   //This will Actually start movement. Be carefull here. Engine->Axis controls the movement of axis in Jog. 
   // JogDirr is 1 or 0 and represents each direction
   //MaxVelcoity is the top speed it will accelerate to.. using Acceleration param, MasterVelcoity is a master limit of speed. 
   // Velocity will never exceed the MasterVelocity setting.

   Engine->Axis[ XJoyAxis].JoggDir = XDir; 
   Engine->Axis[ XJoyAxis].MaxVelocity =  (int) (MaxX );
   Engine->Axis[ XJoyAxis].Acceleration = AccSecX;
   Engine->Axis[ XJoyAxis].MasterVelocity = VelMaxX;

if( XOn && !TrackingX && !Engine->Axis[  XJoyAxis ].Dec)
  {
   //If .Dec is set to true, the axis will decelerate down using Acceleration until it stops, then the 
   // .Dec will be set to false by Mach3. So set it to false prior to starting a move. 
   Engine->Axis[ XJoyAxis].Dec = false;
   Engine->Axis[ XJoyAxis].Jogging = true;
   TrackingX = true;
  }
 
//Now we do the Y- Stick axis 
   Engine->Axis[ YJoyAxis].JoggDir = YDir;
   Engine->Axis[ YJoyAxis].MaxVelocity = (int) (MaxY  ); 
   Engine->Axis[ YJoyAxis].Acceleration = AccSecY;
   Engine->Axis[ YJoyAxis].MasterVelocity = VelMaxY;
 
if( YOn && !TrackingY && !Engine->Axis[ YJoyAxis ].Dec)
   {
   Engine->Axis[ YJoyAxis].Dec = false;
   Engine->Axis[ YJoyAxis].Jogging = true;
   TrackingY = true;
   }

if( !YOn && TrackingY && Engine->Axis[ YJoyAxis ].Jogging)
   {
   //Here we have decided its time to stop, so we just set .dec to true, the axis will 
   // slow to a stop on its own. Mach3 will take care of that for us..
   Engine->Axis[ YJoyAxis].Dec = true;
   TrackingY = false;
   }

if( !XOn && TrackingX && Engine->Axis[  XJoyAxis ].Jogging)
   {
   //Same with X , its now time to stop ...
   Engine->Axis[ XJoyAxis].Dec = true;
   TrackingX = false;
   }
}





