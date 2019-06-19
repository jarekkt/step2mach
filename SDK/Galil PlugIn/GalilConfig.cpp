// GalilConfig.cpp : implementation file
//

#include "stdafx.h"
#include "MachDevice.h"
#include "GalilConfig.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "XMLProfile.h"
#include "dmcwin.h"
#include "MachDevImplementation.h"
#include "GalilControl.h"
#include ".\galilconfig.h"


extern GalilStruct State;

// GalilConfig dialog

IMPLEMENT_DYNAMIC(GalilConfig, CDialog)
GalilConfig::GalilConfig(CWnd* pParent /*=NULL*/)
	: CDialog(GalilConfig::IDD, pParent)
	, m_CalcSpeed(FALSE)
	, m_RefPos(FALSE)
	, m_xbuf(0)
	, m_Compos(0)
	, m_PlanPos(0)
	, m_SpindleAxis(0)
	, m_VectorTimeConst(0)
	, m_VectorDecel(0)
	
{
}

GalilConfig::~GalilConfig()
{
}

void GalilConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CALCSPEED, m_CalcSpeed);
	DDX_Check(pDX, IDC_REFPOS, m_RefPos);
	DDX_Control(pDX, IDC_MT1, m_Motor[0]);
	DDX_Control(pDX, IDC_MT2, m_Motor[1]);
	DDX_Control(pDX, IDC_MT3, m_Motor[2]);
	DDX_Control(pDX, IDC_MT4, m_Motor[3]);
	DDX_Control(pDX, IDC_MT5, m_Motor[4]);
	DDX_Control(pDX, IDC_MT6, m_Motor[5]);

	DDX_Text(pDX, IDC_XBUF, m_xbuf);
	DDX_Text(pDX, IDC_COMPOS, m_Compos);
	DDX_Text(pDX, IDC_PLANPOS, m_PlanPos);
	DDX_Text(pDX, IDC_NSPINDLEAXIS, m_SpindleAxis);
	DDX_Text(pDX, IDC_VECTTIMECONST, m_VectorTimeConst);
	DDX_Text(pDX, IDC_VECTDECEL, m_VectorDecel);
	DDX_Check(pDX, IDC_XINDEX, m_Index[0]);
	DDX_Check(pDX, IDC_YINDEX, m_Index[1]);
	DDX_Check(pDX, IDC_ZINDEX, m_Index[2]);
	DDX_Check(pDX, IDC_AINDEX, m_Index[3]);
	DDX_Check(pDX, IDC_BINDEX, m_Index[4]);
	DDX_Check(pDX, IDC_CINDEX, m_Index[5]);
}


BEGIN_MESSAGE_MAP(GalilConfig, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_VECTDECEL, OnEnChangeVectdecel)
END_MESSAGE_MAP()


// GalilConfig message handlers

BOOL GalilConfig::OnInitDialog()
{
	CDialog::OnInitDialog();
    m_RefPos = m_UseRefPostion;
    m_CalcSpeed = m_UseCalcSpeed;
	m_SpindleAxis = State.nSpindle;
	m_VectorDecel = m_UseVectorDecel;
	m_VectorTimeConst = m_UseVectorTimeConst; 
    for( int x = 0; x < 6; x++)  m_Motor[x].SetCurSel( State.motortype[x] );
	for(x=0;x<6;x++)m_Index[x] = State.HomeData.UseIndex[x];
	UpdateData(false); 
	SetTimer( 1,200,NULL);
	
	return TRUE;  
	 
}

void GalilConfig::OnBnClickedOk()
{
	UpdateData( true );
	for( int x = 0; x < 6; x++)  State.motortype[x] = m_Motor[x].GetCurSel();
	for(x=0;x<6;x++)State.HomeData.UseIndex[x] = m_Index[x];
	m_UseRefPostion = m_RefPos == 1;
    m_UseCalcSpeed = m_CalcSpeed == 1;
	State.nSpindle = m_SpindleAxis;
	m_UseVectorDecel = m_VectorDecel;
	m_UseVectorTimeConst = m_VectorTimeConst; 
	OnOK();
}

void GalilConfig::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnTimer(nIDEvent);
}

void GalilConfig::OnEnChangeVectdecel()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
