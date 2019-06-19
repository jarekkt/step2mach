// OkayToMove.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MachDevice.h"
#include "OkayToMove.h"
#include "XMLProfile.h"
#include "MenuHandler.h"
#include "Engine.h"
#include "TrajectoryControl.h"

extern TrajBuffer *Engine;  
extern TrajectoryControl *MainPlanner; 
extern bool ShutDown;

// OkayToMove dialog

IMPLEMENT_DYNAMIC(OkayToMove, CDialog)
OkayToMove::OkayToMove(CWnd* pParent /*=NULL*/)
	: CDialog(OkayToMove::IDD, pParent)
	, m_IsProbeActive(false)
{
}

OkayToMove::~OkayToMove()
{
}

void OkayToMove::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX,IDC_PROBEACTIVE, m_IsProbeActive);
}


BEGIN_MESSAGE_MAP(OkayToMove, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDYES, OnBnClickedYes)
	ON_BN_CLICKED(IDNO, OnBnClickedNo)
END_MESSAGE_MAP()


// OkayToMove message handlers

void OkayToMove::OnTimer(UINT nIDEvent)
{
	//Update the probe on/off state...
	//if( ShutDown ) { KillTimer(1); return; }
	m_IsProbeActive = Engine->InSigs[22].Activated;
	UpdateData( false );
	CDialog::OnTimer(nIDEvent);
}

BOOL OkayToMove::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_IsOkayToMove = false;
	SetTimer( 1, 200, NULL );

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void OkayToMove::OnBnClickedYes()
{
	KillTimer(1);
	m_IsOkayToMove = true;
	CDialog::OnOK();
}

void OkayToMove::OnBnClickedNo()
{
	KillTimer(1);
	m_IsOkayToMove = false;
	CDialog::OnOK();
}
