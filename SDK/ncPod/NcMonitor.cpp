// NcMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "MachDevice.h"
#include "NcMonitor.h"
#include ".\ncmonitor.h"
#include "externalmovement.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "XMLProfile.h"
#include "ncPod.h"
#include "resource.h"
 

 
extern TrajBuffer *Engine;  //Main Engine Block Variables
extern TrajectoryControl *MainPlanner;  //Trajectory Planner Vars. 
extern setup *_setup;   //RS274 Var block.
extern CMach4View *MachView;
extern ncPod *Pod;
extern bool   ShutDown;
extern int HomingType;


NcMonitor *monitor = NULL;
extern PodThread* pThread;
extern double PullOff[6];

//Monitor thread

IMPLEMENT_DYNCREATE(PodThread, CWinThread)

PodThread::PodThread(  )
{
   
}

PodThread::~PodThread()
{
  if( monitor != NULL )
  {
	  monitor->CloseWindow();
	  monitor = NULL;
  }
}

BOOL PodThread::InitInstance()
{
   if( monitor != NULL ) return false;
   monitor = new NcMonitor();
   monitor->DoModal();
   delete monitor;
   monitor = NULL;
   return TRUE;
}

int PodThread::ExitInstance()
{
	 
   pThread = NULL;
   return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(PodThread, CWinThread)
END_MESSAGE_MAP()

// G100Monitor dialog

// NcMonitor dialog

IMPLEMENT_DYNAMIC(NcMonitor, CDialog)
NcMonitor::NcMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(NcMonitor::IDD, pParent)
	, m_MachTotal(0)
	, m_VelTotal(0)
	, m_PodTotal(0)
	, m_Firmware(_T(""))
	, m_HomeType(FALSE)
	, m_Diffs(0)
	 
	
{
}

NcMonitor::~NcMonitor()
{
}

void NcMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SBIT1, Bit1);
	DDX_Control(pDX, IDC_SBIT2, Bit2);
	DDX_Control(pDX, IDC_SBIT4, Bit4);
	DDX_Control(pDX, IDC_SBIT8, Bit8);
	DDX_Control(pDX, IDC_SBIT16, Bit16);
	DDX_Control(pDX, IDC_SBIT32, Bit32);
	DDX_Control(pDX, IDC_SBIT64, Bit64);
	DDX_Control(pDX, IDC_SBIT128, Bit128);
	DDX_Control(pDX, IDC_SBIT256, Bit256);
	DDX_Control(pDX, IDC_SBIT512, Bit512);
	DDX_Control(pDX, IDC_BIT0, m_Out0);
	DDX_Control(pDX, IDC_IN00, m_In0);
	DDX_Control(pDX, IDC_BIT1, m_Out1);
	DDX_Control(pDX, IDC_IN01, m_In1);
	DDX_Control(pDX, IDC_BIT2, m_Out2);
	DDX_Control(pDX, IDC_IN02, m_In2);
	DDX_Control(pDX, IDC_BIT3, m_Out3);
	DDX_Control(pDX, IDC_IN03, m_In3);
	DDX_Control(pDX, IDC_BIT4, m_Out4);
	DDX_Control(pDX, IDC_IN04, m_In4);
	DDX_Control(pDX, IDC_BIT5, m_Out5);
	DDX_Control(pDX, IDC_IN05, m_In5);
	DDX_Control(pDX, IDC_BIT6, m_Out6);
	DDX_Control(pDX, IDC_IN06, m_In6);
	DDX_Control(pDX, IDC_BIT7, m_Out7);
	DDX_Control(pDX, IDC_IN07, m_In7);
	DDX_Control(pDX, IDC_CYCLE, m_Cycle);
	DDX_Text(pDX, IDC_VELTOTAL, m_VelTotal);
	DDX_Text(pDX, IDC_PODTOTAL, m_PodTotal);
	DDX_Text(pDX, IDC_FIRMWARE, m_Firmware);
	DDX_Radio(pDX, IDC_HOMING, m_HomeType);
	DDX_Text(pDX, IDC_DIFFS, m_Diffs);
	DDX_Check(pDX, IDC_HOME,  m_Home[0]);
	DDX_Check(pDX, IDC_HOME2, m_Home[1]);
	DDX_Check(pDX, IDC_HOME3, m_Home[2]);
	DDX_Check(pDX, IDC_HOME4, m_Home[3]);
	if(Apply)
	{
	DDX_Text(pDX, IDC_PULLOFF1, m_Pulloff[0]);
	DDX_Text(pDX, IDC_PULLOFF2, m_Pulloff[1]);
	DDX_Text(pDX, IDC_PULLOFF3, m_Pulloff[2]);
	DDX_Text(pDX, IDC_PULLOFF4, m_Pulloff[3]);
	DDX_Text(pDX, IDC_PULLOFF5, m_Pulloff[4]);
	DDX_Text(pDX, IDC_PULLOFF6, m_Pulloff[5]);
	Apply = false;
	}
}


BEGIN_MESSAGE_MAP(NcMonitor, CDialog)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_CYCLE, OnCbnSelchangeCycle)
	ON_BN_CLICKED(IDC_CLEARCOUNTS, OnBnClickedClearcounts)
	ON_BN_CLICKED(IDC_HOMING, OnBnClickedHoming)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio3)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_APPLYPODSETTINGS, OnBnClickedApplypodsettings)
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
END_MESSAGE_MAP()


// NcMonitor message handlers

BOOL NcMonitor::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_Firmware.Format( "Pod Firmware version: %i ", Pod->PodStatus.firmwareVersion);
	for(int i=0;i<6;i++)
	{
		m_Pulloff[i] = PullOff[i];

	}
	UpdateData( false );
    SetTimer(1, 100, NULL);
	m_Cycle.SetCurSel(Pod->DripSel);
	m_HomeType = HomingType;
	Apply = true;
	// TODO:  Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void NcMonitor::OnTimer(UINT nIDEvent)
{
	if( ShutDown )
	{
		KillTimer(1);  
		OnOK(); }
  
	m_MachTotal = (int) Pod->total[0];
	m_VelTotal = (double) (Pod->vtotal[0] / (32768 / Pod->DripTime));
	m_Diffs = (double)Pod->vtotal[1];
	m_PodTotal = Pod->PodStatus.fullStepsX;

	Bit1.SetCheck(( Pod->PodStatus.stat & STATPOWEREDON)  != 0 );
	Bit2.SetCheck(( Pod->PodStatus.stat & STATSDCARDMISSING) != 0 );
	Bit4.SetCheck(( Pod->PodStatus.stat & STATSDCARDWASREMOVED) != 0 );
	Bit8.SetCheck(( Pod->PodStatus.stat & STATLIMITHIT)   != 0 );
	Bit16.SetCheck(( Pod->PodStatus.stat & STATPROBEHIT) != 0 );
	Bit32.SetCheck(( Pod->PodStatus.stat & STATPAUSED) != 0 );
	Bit64.SetCheck(( Pod->PodStatus.stat & STATWAITING) != 0 );
	Bit128.SetCheck(( Pod->PodStatus.stat & STATINTERPMOVEINPROGRESS) != 0 );
	Bit256.SetCheck(( Pod->PodStatus.stat & STATVELOCITYMOVEINPROGRESS) != 0 );
	Bit512.SetCheck(( Pod->PodStatus.stat & STATSCANINPROGRESS) != 0 );
 
	for( int x = 0; x < 4; x ++)
	{
      m_Home[x] = ((Pod->PodStatus.Homestatus >> x) & 0x01) == 1;

	}
	m_Out0.SetCheck( Pod->PodStatus.outio  & 0x01 );
	m_Out1.SetCheck( Pod->PodStatus.outio >> 1  & 0x01 );
	m_Out2.SetCheck( Pod->PodStatus.outio >> 2  & 0x01 );
	m_Out3.SetCheck( Pod->PodStatus.outio >> 3  & 0x01 );
	m_Out4.SetCheck( Pod->PodStatus.outio >> 4  & 0x01 );
	m_Out5.SetCheck( Pod->PodStatus.outio >> 5  & 0x01 );
	m_Out6.SetCheck( Pod->PodStatus.outio >> 6  & 0x01 );
	m_Out7.SetCheck( Pod->PodStatus.outio >> 7  & 0x01 );
	m_In0.SetCheck( Pod->PodStatus.inio  & 0x01 );
	m_In1.SetCheck( Pod->PodStatus.inio >> 1  & 0x01 );
	m_In2.SetCheck( Pod->PodStatus.inio >> 2  & 0x01 );
	m_In3.SetCheck( Pod->PodStatus.inio >> 3  & 0x01 );
	m_In4.SetCheck( Pod->PodStatus.inio >> 4  & 0x01 );
	m_In5.SetCheck( Pod->PodStatus.inio >> 5  & 0x01 );
	m_In6.SetCheck( Pod->PodStatus.inio >> 6  & 0x01 );
	m_In7.SetCheck( Pod->PodStatus.inio >> 7  & 0x01 );
	UpdateData( false );
	CDialog::OnTimer(nIDEvent);
}

void NcMonitor::OnCbnSelchangeCycle()
{
	UpdateData( true );
	int sel = m_Cycle.GetCurSel();
	//select new cycle time;
	Pod->SetCycleTime( sel );
	Pod->SetDrip();
}

void NcMonitor::OnBnClickedClearcounts()
{
	Pod->vtotal[0] = (__int64)( Pod->PodStatus.fullStepsX * ( 32768 / Pod->DripTime));
	Pod->vtotal[1] = 0;
	Pod->fractions[0] = 0;

	
	 
}

void NcMonitor::OnBnClickedHoming()
{
	UpdateData( true );
	HomingType = m_HomeType;
}

void NcMonitor::OnBnClickedRadio2()
{
	UpdateData( true );
	HomingType = m_HomeType;
}

void NcMonitor::OnBnClickedRadio3()
{
	UpdateData( true );
	HomingType = m_HomeType;
}

void NcMonitor::OnBnClickedRadio1()
{
	UpdateData( true );
	HomingType = m_HomeType;
}

void NcMonitor::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void NcMonitor::OnBnClickedApplypodsettings()
{
	KillTimer(1);  
	Apply = true;
	UpdateData(true);
	for(int i=0;i<6;i++)
	{
		PullOff[i] = m_Pulloff[i];

	}
	Apply = true;
	UpdateData(false);
	 SetTimer(1, 100, NULL);
}


