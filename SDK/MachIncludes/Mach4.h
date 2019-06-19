// Mach4.h : main header file for the Mach4 application
//
#pragma once

#include <afxctl.h>
#include "memdc.h"
#include "time.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

 
#include "resource.h"       // main symbols
 
 
 
extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;
 

// CMach4App:
// See Mach4.cpp for the implementation of this class
//

class CMach4App : public CWinApp
{
public:
	CMach4App();
	
private:
		WINDOWPLACEMENT m_WP;
	public:
		const WINDOWPLACEMENT& GetWP(void) const;
		void PutWP(const WINDOWPLACEMENT& newval);
	public:
		virtual void ReadConfig(void);
		virtual void WriteConfig(void);
		virtual void ReadWindowConfig(void);
		virtual void WriteWindowConfig(void);

		void HookTimer();
        void UnHookTimer();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	 
	DECLARE_MESSAGE_MAP()
	virtual BOOL InitApplication();
	 
	afx_msg void OnLoadgcode();
	afx_msg void OnImporthpgl();
	afx_msg void OnImportdxf();
	afx_msg void OnClosefile();
	afx_msg void OnExit();
	afx_msg void OnSetnative();
	afx_msg void OnPortspins();
	afx_msg void OnHominglimits();
	afx_msg void OnSlave();
	afx_msg void OnSethotkeys();
	afx_msg void OnTunemotor();
	afx_msg void OnBacklash();
	afx_msg void OnToolpath();
	afx_msg void OnLogic();
	afx_msg void OnState();
	afx_msg void OnLoadscreens();
	afx_msg void OnRegen();
	afx_msg void OnPickwizard();
	afx_msg void OnOffline();
	afx_msg void OnLock();
	afx_msg void OnUnlock();
	afx_msg void OnMacros();
	afx_msg void OnFixtures();
	afx_msg void OnTooltable();
	afx_msg void OnSpincal();
	afx_msg void OnScrewmap();
	afx_msg void OnFormulas();
	afx_msg void OnMaintenance();
	afx_msg void OnAbout();
	afx_msg void OnArtsoft();
	afx_msg void OnUpdateOffline(CCmdUI *pCmdUI);
	virtual int ExitInstance();
	afx_msg void OnOperatorCalibratempg();
};

extern CMach4App theApp;

