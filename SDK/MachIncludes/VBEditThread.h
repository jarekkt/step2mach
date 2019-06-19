#pragma once

#include "ScriptView.h"
#include "VBFrame.h"
 

class VBEditThread : public CWinThread
{
	DECLARE_DYNCREATE(VBEditThread)

public:
	VBEditThread();           // protected constructor used by dynamic creation
	virtual ~VBEditThread();
    VBFrame *frame;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


