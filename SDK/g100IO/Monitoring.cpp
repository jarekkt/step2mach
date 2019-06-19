// Monitoring.cpp : implementation file
//

#include "stdafx.h"
#include "MachDevice.h"
#include "Monitoring.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "XMLProfile.h"
#include "MachDevice.h"
#include "G100-Structs.h"		// Includes protocol messages and common G100 library
#include "G100Config.h"
#include "G100General.h"
#include "GRexControl.h"
#include ".\monitoring.h"

extern TrajectoryControl *MainPlanner;	// used for most planner funcitons and program control 
extern CMach4View *MachView;			// used for most framework and configuration calls. 
extern TrajBuffer *Engine;				// Ring0 memory for printer port control and other device syncronisation
extern setup *_setup;					// Trajectory planners setup block. Always in effect

extern MyHandler *myG100handler;
extern GRexControl *TheRex;

extern Monitoring *Monitor;
extern bool        ShutDown;

// Monitoring dialog

IMPLEMENT_DYNAMIC(Monitoring, CDialog)
Monitoring::Monitoring(CWnd* pParent /*=NULL*/)
	: CDialog(Monitoring::IDD, pParent)
	, m_IsConnected(FALSE)
	, m_IsMovable(FALSE)
	, m_EndOfQueue(FALSE)
	, m_SyncError(FALSE)
	, m_BufferTime(0)
	, m_Rate(0)
	, m_Clock(0)
	, m_SpinDDA(0)
	, m_Queue5(FALSE)
{
}

Monitoring::~Monitoring()
{
}

void Monitoring::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_STILL, m_Still);
	DDX_Text(pDX, IDC_MENC1, m_Encoder[0]);
	DDX_Text(pDX, IDC_MENC2, m_Encoder[1]);
	DDX_Text(pDX, IDC_MENC3, m_Encoder[2]);
	DDX_Text(pDX, IDC_MENC4, m_Encoder[3]);
	DDX_Text(pDX, IDC_MENC5, m_Encoder[4]);
	DDX_Text(pDX, IDC_MENC6, m_Encoder[5]);
	DDX_Text(pDX, IDC_DDA1, m_DDAS[0]);
	DDX_Text(pDX, IDC_DDA2, m_DDAS[1]);
	DDX_Text(pDX, IDC_DDA3, m_DDAS[2]);
	DDX_Text(pDX, IDC_DDA4, m_DDAS[3]);
	DDX_Text(pDX, IDC_DDA5, m_DDAS[4]);
	DDX_Text(pDX, IDC_DDA6, m_DDAS[5]);
	DDX_Text(pDX, IDC_POS1, m_Pos[0]);
	DDX_Text(pDX, IDC_POS2, m_Pos[1]);
	DDX_Text(pDX, IDC_POS3, m_Pos[2]);
	DDX_Text(pDX, IDC_POS4, m_Pos[3]);
	DDX_Text(pDX, IDC_POS5, m_Pos[4]);
	DDX_Text(pDX, IDC_POS6, m_Pos[5]);
	DDX_Check(pDX, IDC_HALT1, m_Halt[0]);
	DDX_Check(pDX, IDC_HALT2, m_Halt[1]);
	DDX_Check(pDX, IDC_HALT3, m_Halt[2]);
	DDX_Check(pDX, IDC_HALT4, m_Halt[3]);
	DDX_Check(pDX, IDC_HALT5, m_Halt[4]);
	DDX_Check(pDX, IDC_HALT6, m_Halt[5]);
	DDX_Check(pDX, IDC_HALT7, m_Halt[6]);
	DDX_Check(pDX, IDC_HALT8, m_Halt[7]);
	DDX_Check(pDX, IDC_HALT9, m_Halt[8]);
	DDX_Check(pDX, IDC_HALT10, m_Halt[9]);
	DDX_Check(pDX, IDC_HALT11, m_Halt[10]);
	DDX_Check(pDX, IDC_HALT12, m_Halt[11]);
	DDX_Check(pDX, IDC_HALT13, m_Halt[12]);
	DDX_Check(pDX, IDC_HALT14, m_Halt[13]);
	DDX_Check(pDX, IDC_HALT15, m_Halt[14]);
	DDX_Check(pDX, IDC_HALT16, m_Halt[15]);
	DDX_Check(pDX, IDC_HALT17, m_Halt[16]);
	DDX_Check(pDX, IDC_HALT18, m_Halt[17]);
	DDX_Check(pDX, IDC_HALT19, m_Halt[18]);
	DDX_Check(pDX, IDC_HALT20, m_Halt[19]);
	DDX_Check(pDX, IDC_HALT21, m_Halt[20]);
	DDX_Check(pDX, IDC_HALT22, m_Halt[21]);
	DDX_Check(pDX, IDC_IN1, m_Ins[0]);
	DDX_Check(pDX, IDC_IN2, m_Ins[1]);
	DDX_Check(pDX, IDC_IN3, m_Ins[2]);
	DDX_Check(pDX, IDC_IN4, m_Ins[3]);
	DDX_Check(pDX, IDC_IN5, m_Ins[4]);
	DDX_Check(pDX, IDC_IN6, m_Ins[5]);
	DDX_Check(pDX, IDC_IN7, m_Ins[6]);
	DDX_Check(pDX, IDC_IN8, m_Ins[7]);
	DDX_Check(pDX, IDC_IN9, m_Ins[8]);
	DDX_Check(pDX, IDC_IN10, m_Ins[9]);
	DDX_Check(pDX, IDC_IN11, m_Ins[10]);
	DDX_Check(pDX, IDC_IN12, m_Ins[11]);
	DDX_Check(pDX, IDC_IN13, m_Ins[12]);
	DDX_Check(pDX, IDC_IN14, m_Ins[13]);
	DDX_Check(pDX, IDC_IN15, m_Ins[14]);
	DDX_Check(pDX, IDC_IN16, m_Ins[15]);
	DDX_Check(pDX, IDC_IN17, m_Ins[16]);
	DDX_Check(pDX, IDC_IN18, m_Ins[17]);
	DDX_Check(pDX, IDC_IN19, m_Ins[18]);
	DDX_Check(pDX, IDC_IN20, m_Ins[19]);
	DDX_Check(pDX, IDC_IN21, m_Ins[20]);
	DDX_Check(pDX, IDC_IN22, m_Ins[21]);
	DDX_Check(pDX, IDC_OUT1, m_Outs[0]);
	DDX_Check(pDX, IDC_OUT2, m_Outs[1]);
	DDX_Check(pDX, IDC_OUT3, m_Outs[2]);
	DDX_Check(pDX, IDC_OUT4, m_Outs[3]);
	DDX_Check(pDX, IDC_OUT5, m_Outs[4]);
	DDX_Check(pDX, IDC_OUT6, m_Outs[5]);
	DDX_Check(pDX, IDC_OUT7, m_Outs[6]);
	DDX_Check(pDX, IDC_OUT8, m_Outs[7]);
	DDX_Check(pDX, IDC_OUT9, m_Outs[8]);
	DDX_Check(pDX, IDC_OUT10, m_Outs[9]);
	DDX_Check(pDX, IDC_OUT11, m_Outs[10]);
	DDX_Check(pDX, IDC_OUT12, m_Outs[11]);
	DDX_Check(pDX, IDC_OUT13, m_Outs[12]);
	DDX_Check(pDX, IDC_OUT14, m_Outs[13]);
	DDX_Check(pDX, IDC_OUT15, m_Outs[14]);
	DDX_Check(pDX, IDC_OUT16, m_Outs[15]);
	DDX_Text(pDX, IDC_ANAOUT1, m_AnaOut[0]);
	DDX_Text(pDX, IDC_ANAOUT2, m_AnaOut[1]);
	DDX_Text(pDX, IDC_ANAOUT3, m_AnaOut[2]);
	DDX_Text(pDX, IDC_ANAOUT4, m_AnaOut[3]);
	DDX_Text(pDX, IDC_ANAIN1, m_AnaIn[0]);
	DDX_Text(pDX, IDC_ANAIN2, m_AnaIn[1]);
	DDX_Text(pDX, IDC_ANAIN3, m_AnaIn[2]);
	DDX_Text(pDX, IDC_ANAIN4, m_AnaIn[3]);
	DDX_Check(pDX, IDC_CONNECTED, m_IsConnected);
	DDX_Check(pDX, IDC_MOVABLE, m_IsMovable);
	DDX_Check(pDX, IDC_ENDQUEUE, m_EndOfQueue);
	DDX_Check(pDX, IDC_SYNCERROR, m_SyncError);
	DDX_Text(pDX, IDC_TIME, m_BufferTime);
	DDX_Text(pDX, IDC_RATE, m_Rate);
	DDX_Text(pDX, IDC_TIME2, m_LocalTime);
	DDX_Text(pDX, IDC_CLOCK, m_Clock);
	DDX_Control(pDX, IDC_HALT1, m_bHalt[0]);
	DDX_Control(pDX, IDC_HALT2, m_bHalt[1]);
	DDX_Control(pDX, IDC_HALT3, m_bHalt[2]);
	DDX_Control(pDX, IDC_HALT4, m_bHalt[3]);
	DDX_Control(pDX, IDC_HALT5, m_bHalt[4]);
	DDX_Control(pDX, IDC_HALT6, m_bHalt[5]);
	DDX_Control(pDX, IDC_HALT7, m_bHalt[6]);
	DDX_Control(pDX, IDC_HALT8, m_bHalt[7]);
	DDX_Control(pDX, IDC_HALT9, m_bHalt[8]);
	DDX_Control(pDX, IDC_HALT10, m_bHalt[9]);
	DDX_Control(pDX, IDC_HALT11, m_bHalt[10]);
	DDX_Control(pDX, IDC_HALT12, m_bHalt[11]);
	DDX_Control(pDX, IDC_HALT13, m_bHalt[12]);
	DDX_Control(pDX, IDC_HALT14, m_bHalt[13]);
	DDX_Control(pDX, IDC_HALT15, m_bHalt[14]);
	DDX_Control(pDX, IDC_HALT16, m_bHalt[15]);
	DDX_Control(pDX, IDC_HALT17, m_bHalt[16]);
	DDX_Control(pDX, IDC_HALT18, m_bHalt[17]);
	DDX_Control(pDX, IDC_HALT19, m_bHalt[18]);
	DDX_Control(pDX, IDC_HALT20, m_bHalt[19]);
	DDX_Control(pDX, IDC_HALT21, m_bHalt[20]);
	DDX_Control(pDX, IDC_HALT22, m_bHalt[21]);
	DDX_Text(pDX, IDC_SPINDDA1, m_SpinDDA);
	DDX_Check(pDX, IDC_QUEUE, m_Queue5);
}


BEGIN_MESSAGE_MAP(Monitoring, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLOSE, OnBnClickedClose)
END_MESSAGE_MAP()


// Monitoring message handlers

 

void Monitoring::OnTimer(UINT nIDEvent)
{
	if( TheRex == NULL) return;
	if( ShutDown ) return;

	FillData();
	UpdateData(false);

	CDialog::OnTimer(nIDEvent);
}

BOOL Monitoring::OnInitDialog()
{
	CDialog::OnInitDialog();

	FillData();
	UpdateData(false);
	SetTimer(1,250,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void Monitoring::FillData()
{

	if( TheRex == NULL) return;
	if( TheRex->PHASE != RUNONIP ) return;
	WTSDDA pos_ddas[6];
	WTSDDA vel_ddas[6];
	double vel_units[6];
	double pos_units[6];

	TheRex->p->getActualPosEstimate(pos_ddas, vel_ddas); //fill with know DDA positions or estimates.
	TheRex->p->getActualPosEstimateUnits(pos_units, vel_units);

    m_Still = TheRex->p->isStill();
	m_IsConnected = TheRex->p->isConnected();
	m_IsMovable = TheRex->p->isMovable();
	m_EndOfQueue = TheRex->p->isEndOfQueue();
	m_SyncError = TheRex->p->isSyncError();
	m_Rate = TheRex->p->getRate();
	int num1 = Engine->TrajHead - Engine->TrajIndex;
	if( num1 < 0 ) num1 += 4096;
    m_Queue5 = num1 < 5; 

 	for( int x = 0; x < TheRex->p->getDimension() ; x++)
	{
		m_Encoder[x] = MainPlanner->ModInputs[118+x];
		//m_Encoder[x] = Engine->Encoders[x].Count[0];
		m_DDAS[x] = (int) (pos_ddas[x] >> 32);
		m_Pos[x] =  (double) (vel_units[x]);
	}
	if( TheRex->s != NULL)
	{
		TheRex->s->getActualPosEstimate(pos_ddas, vel_ddas); //fill with know DDA positions or estimates.
		TheRex->s->getActualPosEstimateUnits(pos_units, vel_units);
		m_Encoder[5] = Engine->Encoders[0].Count[0];
		m_SpinDDA = (int) (pos_ddas[0] >> 32);
		m_Pos[5] =  (double) (vel_units[0]);
 
	}

	m_BufferTime = TheRex->p->getRemoteLookahead();
	m_LocalTime = TheRex->p->getTotalLookahead();
	unsigned ins = TheRex->p->getDigIns();
	unsigned outs = 0;	// Desired state
	unsigned mask = 0;	// Which bits are requested by Mach, AND controllable by master partition
	mask &= TheRex->p->getDigOutMask();				// Forget ones we can't control
	outs = TheRex->p->getDigOuts() ;//& mask;


	unsigned int mon,monlev;
	TheRex->p->getHaltDigIns( mon, monlev); 

	for( int x = 0; x < 22; x++)
	{
		//if((monlev >> x) & 0x01)
		m_bHalt[x].EnableWindow(((monlev >> x) & 0x01) ? false : true ); 
	    m_Halt[x] = ((mon >> x)& 0x01) ? true : false;
		m_Ins[x] = ((ins    >> x)& 0x01) ? false : true;;
		if( x > 15 ) continue;
		m_Outs[x] = ((outs >> x)& 0x01) ? true : false;
	}
    m_Clock = Engine->Counter;
	 
	for( int x = 0; x < 4; x++)
	{
		m_AnaIn[x].Format("%.2f",(((double)((short)TheRex->p->getSingleAnaIn(x))/32767 ))*5); 
		m_AnaOut[x].Format("%.2f",(((double)((short)TheRex->p->getSingleAnaOut(x)))/32767)*5); //for 5 volt full scale..
	}
	UpdateData( false );

}
void Monitoring::OnBnClickedClose()
{
	Monitor = NULL;
	KillTimer(1);
	OnOK();
}


