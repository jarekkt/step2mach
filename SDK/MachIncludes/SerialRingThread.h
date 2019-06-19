#pragma once
#include "SerialRing.h"


// SerialRingThread

class SerialRingThread : public CWinThread
{
	DECLARE_DYNCREATE(SerialRingThread)

public:
	SerialRingThread();           // protected constructor used by dynamic creation
	virtual ~SerialRingThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	SerialRing *procdlg;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnFinalRelease();
};


