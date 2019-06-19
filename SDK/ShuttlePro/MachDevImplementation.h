// MachDevImplementatio.h : main header file for the user implementation code of the plugin
// Include near the end of the #Include llist
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


typedef void (CALLBACK *NoParms) ();
typedef void (_cdecl *OneShort) ( short );
typedef double (_cdecl *DoubleShort) ( short );
typedef void (_cdecl *DoubleShortDouble) ( short , double );
typedef bool (_cdecl *BoolShort) ( short );
typedef void (_cdecl *CSTRret) ( CString );
typedef void (_cdecl *VoidLPCSTR) (LPCTSTR );

// ===========================================================================================
//
// Here are the entrypoints to the implementation to be called by Mach3via MachDevice.cpp. Declare them dere in
// case user gets bad ideas and changes argument list

CString	myProfileInit (CString name, CXMLProfile *DevProf);	// initial acces to Mach profile
															// when enumerating available plugins
void	myInitControl (CXMLProfile *DevProf);									// called during Mach initialisation
															// you can influence subsequent init by actions here
															// **** Not used in typical device plugin
void	myPostInitControl (CXMLProfile *DevProf);								// called when mach fully set up
void	myConfig (CXMLProfile *DevProf);					// Called to configure the device

void	myUpdate ();										// 10Hz update loop
void	myHighSpeedUpdate ();								// called at 40Hz

void    myCleanUp();                                        //Used to cleanup heap variables before destrucion of PlugIn

void    myHome( short axis);
void    myProbe();                                          //homing and probing calls from Mach3.



// ==================================================================================================
//
// Here are the main data ares with which the implementer will do his/her work
//
// ==================================================================================================

// These pointers are set up in the MachDevice code during init of DLL

// ************** Beware *****************
// You can alter almost anything and so hasten the end of the world as we know it

extern TrajectoryControl *MainPlanner;	// used for most planner funcitons and program control 
extern CMach4View *MachView;			// used for most framework and configuration calls. 
extern TrajBuffer *Engine;				// Ring0 memory for printer port control and other device syncronisation
extern setup *_setup;					// Trajectory planners setup block. Always in effect


// =====================================================================================================
//
// Here are the pointers to the functions we can call in Mach 3
//
// =====================================================================================================


extern OneShort           DoButton;     // void DoButton( code )
extern DoubleShort        GetDRO;       // Double GetDRO( code )
extern DoubleShortDouble  SetDRO;       // void   SetDRO( short code, double value);
extern BoolShort          GetLED;       // bool   GetLED( short code );
extern CSTRret            GetProName;   // CString GetProName()
extern VoidLPCSTR         Code;         // void    Code( "G0X10Y10" );

// =====================================================================================================
