#pragma once



// ModBusThread

#include "ModBusStatus.h"
#include "ModBusConfig.h"

class ModBusThread : public CWinThread
{
	DECLARE_DYNCREATE(ModBusThread)

public:
	ModBusThread();           // protected constructor used by dynamic creation
	virtual ~ModBusThread();

public:
	virtual BOOL InitInstance();
     ModBusStatus *modbus;
	 ModBusConfig *modcfg;
protected:
	DECLARE_MESSAGE_MAP()
 
};


