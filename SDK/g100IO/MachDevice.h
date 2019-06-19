// MachDevice.h : main header file for the MachDevice DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//#include "resource.h"		            // main symbols
 
// =======================================================================================================
// Here are the types of the pointers to functions that can be called

typedef void (CALLBACK *NoParms) ();
typedef void (_cdecl *OneShort) ( short );
typedef double (_cdecl *DoubleShort) ( short );
typedef void (_cdecl *VoidShortDouble) ( short , double );
typedef bool (_cdecl *BoolShort) ( short );
typedef void (_cdecl *CSTRret) ( CString );
typedef void (_cdecl *VoidLPCSTR) (LPCTSTR );
typedef void (_cdecl *VoidShortBool) ( short, bool );
typedef int  (_cdecl *IntShort) ( short );


extern void SetMachError(CString Message);

//=========================================================================================================

// CMachDeviceApp
// See MachDevice.cpp for the implementation of this class

class CMachDeviceApp : public CWinApp
{
public:
	CMachDeviceApp();
	~CMachDeviceApp();


// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()


  
};

