#pragma once


#include "MacroRun.h"

// RealTimeMacro

class RealTimeMacro : public CWinThread
{
	DECLARE_DYNCREATE(RealTimeMacro)

public:
	RealTimeMacro();           // protected constructor used by dynamic creation
	virtual ~RealTimeMacro();

public:
	MacroRun     *macrowin;
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


