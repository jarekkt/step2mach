//===========================================================================
//
//      SDIEdit.h - Function prototypes
//
//      Copyright 1993-2003 Cypress Software Inc.  All Rights Reserved.
//      Information Contained Herein Is Proprietary and Confidential.
//===========================================================================

#if !defined(AFX_SDIEDIT_H__FF5FFA62_FFD4_47C4_9047_D467EF5FC8B6__INCLUDED_)
#define AFX_SDIEDIT_H__FF5FFA62_FFD4_47C4_9047_D467EF5FC8B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//===========================================================================
static const char *pAppTitle = "Mach3 VB Scipt Editor";

//===========================================================================
inline void DisplayMessage( HWND hwnd, char *szMessage )
//===========================================================================
{
    MessageBox( hwnd, szMessage, pAppTitle, MB_OK | MB_ICONEXCLAMATION );
}

//===========================================================================
// Implemented in EditFile.cpp

STDAPI QuerySaveFile( HWND hwndEdit, HWND hwnd );

STDAPI enaFileMenuNew( HWND hwndEdit, HWND hwnd );
STDAPI enaFileMenuOpen( HWND hwndEdit, HWND hwnd );
STDAPI enaFileMenuSave( HWND hwndEdit, HWND hwnd );
STDAPI enaFileMenuSaveAs( HWND hwndEdit, HWND hwnd );

//===========================================================================
// Implemented in EditFind.cpp

STDAPI HandleFindReplace( HWND hwndEdit, LPFINDREPLACE pfr );

STDAPI enaEditMenuFind( HWND hwndEdit, HWND hwnd );
STDAPI enaEditMenuFindNext( HWND hwnd );
STDAPI enaEditMenuReplace( HWND hwnd );

//===========================================================================
// Implemented in RunDebug.cpp

STDAPI enaDebugMenuStepInto( HWND hwnd );
STDAPI enaDebugMenuStepOver( HWND hwnd );

STDAPI enaRunMenuStart( HWND hwnd );
STDAPI enaRunMenuEnd( HWND hwnd );
STDAPI enaRunMenuDebugFunction( HWND hwnd );

#endif // !defined(AFX_SDIEDIT_H__FF5FFA62_FFD4_47C4_9047_D467EF5FC8B6__INCLUDED_)
