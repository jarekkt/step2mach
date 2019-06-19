// G100General.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MachDevice.h"
#include "G100General.h"
#include "G100Config.h"
#include "G100FlashConfig.h"
#include ".\g100general.h"
#include "G100Monitor.h"

extern void OpenMonitorWindow();
extern G100Monitor *monitor;
extern CMonitorThread* pThread;


// G100General dialog

IMPLEMENT_DYNAMIC(G100General, CDialog)
G100General::G100General(CWnd* pParent /*=NULL*/)
	: CDialog(G100General::IDD, pParent)
{
	 
}

G100General::~G100General()
{
}

void G100General::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(G100General, CDialog)
	ON_BN_CLICKED(IDC_DISCOVERY, OnBnClickedDiscovery)
	ON_BN_CLICKED(IDC_GENERALPARAM, OnBnClickedGeneralparam)
	ON_BN_CLICKED(IDC_STATUS, OnBnClickedStatus)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// G100General message handlers

void G100General::OnBnClickedDiscovery()
{
	G100Config *cfg = new G100Config();
	cfg->DoModal();
	delete cfg;
}

void G100General::OnBnClickedGeneralparam()
{
	G100FLASHCONFIG *cfg = new G100FLASHCONFIG();
	cfg->DoModal();
	delete cfg;
}

void G100General::OnBnClickedStatus()
{
	if( monitor != NULL ) return;
	if( pThread != NULL ) delete pThread;
	pThread = new CMonitorThread( );
	pThread->CreateThread();
	OnBnClickedOk();
}

void G100General::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
