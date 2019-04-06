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

class MyConsoleClass
{
	HWND    hhwnd;
	HANDLE  hhandle;
	BOOL  ConsoleValid;

public:
	MyConsoleClass();
	virtual ~MyConsoleClass();

	void ConsolePrint(int x, int y,const char * msg);

};