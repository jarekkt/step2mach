#pragma once
#include "brain.h"
#include "afxtempl.h"


 

class BrainHandler
{
public:
	BrainHandler(void);
	~BrainHandler(void);

	CArray < Brain*, Brain*> Brains;
    


	void LoadBrains(void);
	void LoadBrainFile(CString filepath);
	void RunBrains(void);
};
