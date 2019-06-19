// G100Monitor.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MachDevice.h"
#include "G100Monitor.h"
#include ".\g100monitor.h"
#include "g100-Structs.h"
#include "Engine.h"
#include "TrajectoryControl.h"
#include "MessageTracker.h"

extern MessageTracker *G100Mess;

//Thread functions..

IMPLEMENT_DYNCREATE(CMonitorThread, CWinThread)

extern G100Monitor *monitor;
extern CMonitorThread *pThread;
extern GRex G100;
extern TrajBuffer *Engine;  
extern TrajectoryControl *MainPlanner; 
extern bool ShutDown;


CMonitorThread::CMonitorThread(  )
{
   
}

CMonitorThread::~CMonitorThread()
{
	
}

BOOL CMonitorThread::InitInstance()
{
   if( monitor != NULL ) return false;
   monitor = new G100Monitor();
   monitor->DoModal();
   delete monitor;
   return TRUE;
}

int CMonitorThread::ExitInstance()
{
   pThread = NULL;
   return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMonitorThread, CWinThread)
END_MESSAGE_MAP()

// G100Monitor dialog

IMPLEMENT_DYNAMIC(G100Monitor, CDialog)
G100Monitor::G100Monitor(CWnd* pParent /*=NULL*/)
	: CDialog(G100Monitor::IDD, pParent)
	, m_LastMessage(0)
	, m_LastSent(0)
	, m_LastQueued(0)
	, m_Window(0)
	, m_ISR(0)
	, m_SSEQ(0)
	, m_ESEQ(0)
	, m_Still(FALSE)
	, m_Drained(FALSE)
	, m_Flags(0)
	, m_DigReq(FALSE)
	, m_AnaReq(FALSE)
	, m_Debug(FALSE)
	, m_SEQError(FALSE)
	, m_QueueUsed(0)
	, m_MISR(0)
	, m_Mavg(0)
	, m_HaltWait(FALSE)
	, m_nMess(0)
{
}

G100Monitor::~G100Monitor()
{
}

void G100Monitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LASTACK, m_LastMessage);
	DDX_Text(pDX, IDC_LASTSENT, m_LastSent);
	DDX_Text(pDX, IDC_LASTQUEUED, m_LastQueued);
	DDX_Text(pDX, IDC_WINDOW, m_Window);
	DDX_Text(pDX, IDC_ISR, m_ISR);
	DDX_Text(pDX, IDC_SSEQ, m_SSEQ);
	DDX_Text(pDX, IDC_ESEQ, m_ESEQ);
	DDX_Check(pDX, IDC_STILL, m_Still);
	DDX_Check(pDX, IDC_DRAINED, m_Drained);
	DDX_Text(pDX, IDC_QUEUEFLAGS, m_Flags);
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
	DDX_Check(pDX, IDC_DIGREQ, m_DigReq);
	DDX_Check(pDX, IDC_ANAREQ, m_AnaReq);
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
	DDX_Check(pDX, IDC_ENABLEDEBUG, m_Debug);
	DDX_Text(pDX, IDC_ANAOUT1, m_AnaOut[0]);
	DDX_Text(pDX, IDC_ANAOUT2, m_AnaOut[1]);
	DDX_Text(pDX, IDC_ANAOUT3, m_AnaOut[2]);
	DDX_Text(pDX, IDC_ANAOUT4, m_AnaOut[3]);
	DDX_Text(pDX, IDC_ANAIN1, m_AnaIn[0]);
	DDX_Text(pDX, IDC_ANAIN2, m_AnaIn[1]);
	DDX_Text(pDX, IDC_ANAIN3, m_AnaIn[2]);
	DDX_Text(pDX, IDC_ANAIN4, m_AnaIn[3]);
	DDX_Control(pDX, IDC_ENABLEDEBUG, m_DebugBox);
	DDX_Check(pDX, IDC_SEQERROR, m_SEQError);
	DDX_Text(pDX, IDC_QUEUEUSED, m_QueueUsed);
	DDX_Text(pDX, IDC_MISR, m_MISR);
	DDX_Text(pDX, IDC_CMAVG, m_Mavg);
	DDX_Check(pDX, IDC_HALTACK, m_HaltWait);
	DDX_Text(pDX, IDC_NMESS, m_nMess);
}


BEGIN_MESSAGE_MAP(G100Monitor, CDialog)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ENABLEDEBUG, OnBnClickedEnabledebug)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// G100Monitor message handlers

BOOL G100Monitor::OnInitDialog()
{
	CDialog::OnInitDialog();
    FillData();
	SetTimer( 1, 200, NULL );
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void G100Monitor::OnClose()
{
	KillTimer(1);
	monitor = NULL;
    CDialog::OnClose();
	 
}

void G100Monitor::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

void G100Monitor::OnBnClickedEnabledebug()
{
	m_Debug = !m_Debug;
	UpdateData( false );
	if( m_Debug )MainPlanner->DebugRun = true;
	else
	    MainPlanner->DebugRun = false;

}

void G100Monitor::OnTimer(UINT nIDEvent)
{
	if( ShutDown ) { KillTimer(1); return; }
	FillData();
	CDialog::OnTimer(nIDEvent);
}

void  G100Monitor::FillData()
{
	m_nMess = G100Mess->nMessages;
	m_HaltWait = G100.SystemHalted;
	m_Mavg = G100.CurrentMavg;
	m_LastMessage = G100.LastAck;
	m_LastSent = G100.LastMess;
	m_SEQError = (G100.QueueFlags & QC_S_ERROR) != 0;
	m_LastQueued = G100.LastStored;
	m_Window = G100.Window;
	m_ISR = G100.CurrentISR;
	m_QueueUsed = G100.EndQueueSeq - G100.CurrentQueueSeq;
	m_SSEQ = G100.CurrentQueueSeq;
	m_ESEQ = G100.EndQueueSeq;
	m_Still = G100.IsStill;
	m_Drained = G100.IsDrained;
	m_MISR = G100.CurrentMISR;
	m_Flags = G100.QueueFlags;
	for( int x = 0; x < 6; x++)
	{
	  m_Encoder[x] = Engine->Encoders[x].Count[0];
	  m_DDAS[x] = G100.CurDDA[x];
	  m_Pos[x] = G100.LastCoord[x];
	}
	m_DigReq = G100.NeedDigOutputs;
	m_AnaReq = G100.NeedAnaOutputs;
    for( int x = 0; x < 22; x++)
	{
		m_Halt[x] = ((G100.CurrentHaltBits >> x)& 0x01) ? false : true;
		m_Ins[x] = ((G100.InWord    >> x)& 0x01) ? false : true;;
	    if( x > 15 ) continue;
		m_Outs[x] = ((G100.OutputWord >> x)& 0x01) ? true : false;
	}
    for( int x = 0; x < 4; x++)
	{
		m_AnaIn[x].Format("%.2f",(((double)MainPlanner->ModInputs[124+x]+.001)/65535 ) * 5); 
		m_AnaOut[x].Format("%.2f",(((double)MainPlanner->ModOutputs[124+x]+.001)/65535) * 5);
	}
    UpdateData( false );
	
}

void G100Monitor::OnBnClickedOk()
{
	KillTimer(1);
	monitor = NULL;
	OnOK();
	 
}


