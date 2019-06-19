#pragma once

 

enum Operations { BNOP , BCMPI, BCMP, BINV, BTIMER, BFORMULA ,BAND, BOR, BEOR  } ;
enum SubOperation { BLESS, BGREATER, BEQUAL } ;

struct timer
{
	double Delay;
	double PulseA;
	double RepeatDelay;
	bool   Accum;
	bool   Single;
	bool   UseReset;
};

class CLobe
{
public:
	CLobe(void);
	~CLobe(void);

 //lobe variables. 

	int Ident;
	int nInputs;
	int nLobes;
	int Inputs[20];
	int ConLobes[20];
	int Output;
	bool Selected;
	bool Used;
	short Logic;
    short SubLogic;
	CString Formula;
	timer   Timer;
	double  m_CmpIVal;
	bool    Terminated;
	CString TermName;
	int     TermType;
	int     TermToken;
 	int col, rowstart, rowend; //for drawing it.. 
    int OldInputs[20];
	bool OutputModified;

};
