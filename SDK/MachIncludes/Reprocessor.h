#pragma once

// Reprocessor
#include "Processor.h"

class Reprocessor : public CWinThread
{
	DECLARE_DYNCREATE(Reprocessor)

public:
	Reprocessor();           // protected constructor used by dynamic creation
	virtual ~Reprocessor();
	Processor *procdlg;
    
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


 