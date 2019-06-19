#pragma once

#include "lobe.h"
#include "afxtempl.h"

#define MAXINPUTS 50

class Brain
{
public:
	CArray < CLobe*, CLobe*> Lobes;
public:
	Brain(void);
	~Brain(void);
	int      nInputs;
	int      Inputs[MAXINPUTS];
    CString  INames[MAXINPUTS];
	int      ITokens[MAXINPUTS];
	short    IType[MAXINPUTS];
	bool     InputUsed[MAXINPUTS];
	CString  m_Name; 
	bool     m_Activated;
	int      OldInputs[MAXINPUTS];
	bool     m_InputsModified;
	
	CString  m_FileName;
	void RunBrain(void);
};
