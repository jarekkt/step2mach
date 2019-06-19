// G100Config.cpp : implementation file
// 

#include "stdafx.h"
#include "resource.h"
#include "MachDevice.h"
#include "G100Config.h"
#include "G100-Structs.h"
#include ".\g100config.h"
#include "LocalIPQuery.h"
#include "GRexControl.h"


extern GRexControl *TheRex;

bool Exit;

// G100Config dialog

IMPLEMENT_DYNAMIC(G100Config, CDialog)
G100Config::G100Config(CWnd* pParent /*=NULL*/)
	: CDialog(G100Config::IDD, pParent)
	, m_Error(_T(""))
	, m_Perm(FALSE)
{
	Exit = false;
}

G100Config::~G100Config()
{
}

void G100Config::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPG100, m_G100IP);
	DDX_Control(pDX, IDC_NMG100, m_G100NM);
	DDX_Control(pDX, IDC_MYIP, m_MyIP);
	DDX_Text(pDX, IDC_ERRORS, m_Error);
}


BEGIN_MESSAGE_MAP(G100Config, CDialog)
	ON_BN_CLICKED(IDC_SENDNEW, OnBnClickedSendnew)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
END_MESSAGE_MAP()


// G100Config message handlers

BOOL G100Config::OnInitDialog()
{
	CDialog::OnInitDialog();
	//Lets show what we have recieved so far in terms of G100 Address.
	unsigned ipaddr, netmask;
	if (!TheRex->ge || !TheRex->ge->getIP(TheRex->inst, ipaddr, netmask))
		ipaddr = netmask = 0;
	m_G100IP.SetAddress(ipaddr);
	m_G100NM.SetAddress(netmask);
	//now lets get ours..
	LocalIPQuery LocalMachine; //setup a localIp search class
	// Search for an address which is _not_ 127.****
	//FIXME: should display a list of addresses to do this properly.

	DWORD test;
	for (unsigned i = 0; i < LocalMachine.m_vIPAddress.size(); ++i) {
		test = (LocalMachine.m_vIPAddress[LocalMachine.m_vIPAddress.size()-1].GetNBO());
		if ((test & 0xFF) != 127)
			break;
	}
	m_MyIP.SetAddress(test);
	m_Error = TheRex->Disability;
	UpdateData( false );
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void G100Config::OnBnClickedSendnew()
{
	UpdateData( true );
	DWORD data;
	m_G100IP.GetAddress( data );
	unsigned ipaddr = (unsigned)data;
	m_G100NM.GetAddress( data);
	unsigned netmask = (unsigned)data;
	TheRex->ge->setIP(TheRex->inst, ipaddr, netmask);
	TheRex->PHASE = SETIP;
	UpdateData( false );

}

void G100Config::OnBnClickedOk()
{
	if( !Exit )
	{
		TheRex->PHASE = DISCOVERY;
	}
	OnOK();
}

void G100Config::OnBnClickedButton2()
{
	Exit = true;
	OnOK();
}
