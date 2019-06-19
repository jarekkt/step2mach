// G100Config.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MachDevice.h"
#include "G100Config.h"
#include "G100-Structs.h"
#include "UDPSocket.h"
#include ".\g100config.h"
#include "LocalIPQuery.h"

extern GRex   G100;
CUDPSocket *configsock;
bool Exit;
extern void StartNetwork();

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
	m_G100IP.SetAddress(G100.G100Address.ipaddr);
	m_G100NM.SetAddress(G100.G100Address.netmask);
	//now lets get ours..
	LocalIPQuery LocalMachine; //setup a localIp search class
	DWORD test = (LocalMachine.m_vIPAddress[LocalMachine.m_vIPAddress.size()-1].GetNBO());
	m_MyIP.SetAddress(test);
	m_Error = G100.Disability;
	UpdateData( false );
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void G100Config::OnBnClickedSendnew()
{
	UpdateData( true );
	DWORD data;
	int res;
	//first, set the G100 config area to the new address requested. 
	m_G100IP.GetAddress( data );
	G100.G100Address.ipaddr = data;
	m_G100NM.GetAddress( data);
	G100.G100Address.netmask = data;
    //now send a UDP packet to set this address
	configsock = new CUDPSocket();
	res = configsock->Create( 13887 ); //open on socket 13887 for setting IP.
	if( !res) m_Error = "Port open Error. ";
	res = configsock->SetSockOpt( SO_BROADCAST, &res, 1);
	if( !res) m_Error = "Error setting socket options.";
	res = configsock->AsyncSelect( FD_READ | FD_WRITE );
	if( !res) m_Error = "Error setting Asyn on socket.";
	res = configsock->SendTo( &G100.G100Address, 
		                      sizeof(G100.G100Address),13887, 
							  "255.255.255.255",MSG_DONTROUTE ); //sets a temporary IP up..
	if( !res ) m_Error = "Error sending on socket.";
	else m_Error.Format("%d bytes sent to socket. - Try Rediscovery", res );
	configsock->Close();
	UpdateData( false );

}

void G100Config::OnBnClickedOk()
{
	if( !Exit )
	{
		StartNetwork();
	}
	OnOK();
}

void G100Config::OnBnClickedButton2()
{
	Exit = true;
	OnOK();
}
