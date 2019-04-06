// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------

#include "stdafx.h"
#include "myconsole.h"
#include "stdio.h"


MyConsoleClass::MyConsoleClass()
{

	ConsoleValid = AllocConsole();

	if(ConsoleValid)
	{
		SetConsoleTitle(_T("STEP2MACH plugin - debug console"));

		hhwnd   = GetConsoleWindow();
		hhandle = GetStdHandle(STD_OUTPUT_HANDLE);
				
	}
}

MyConsoleClass::~MyConsoleClass()
{
	FreeConsole();

}

void MyConsoleClass::ConsolePrint(int x, int y,const char * msg)
{
	DWORD NumberOfCharsWritten;
	COORD dwCursorPosition;
         
	if(ConsoleValid)
	{
		 dwCursorPosition.X = x;
		 dwCursorPosition.Y = y;
		 SetConsoleCursorPosition(hhandle,dwCursorPosition);
		 WriteConsole(hhandle,msg,strlen(msg),&NumberOfCharsWritten,NULL);
	}
}
		
