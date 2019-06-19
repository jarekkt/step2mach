// G100FLASHCONFIG.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MachDevice.h"
#include "G100FLASHCONFIG.h"
#include ".\g100flashconfig.h"
#include "G100-Structs.h"
#include "g200x.h"

extern GRex   G100;
extern CString DefDir;
extern CString Profile;
extern G100Message  ImmediateMess;
extern void SendImmediateMessage(int size);
extern void myPostInitControl();

// G100FLASHCONFIG dialog

IMPLEMENT_DYNAMIC(G100FLASHCONFIG, CDialog)
G100FLASHCONFIG::G100FLASHCONFIG(CWnd* pParent /*=NULL*/)
	: CDialog(G100FLASHCONFIG::IDD, pParent)
	, m_Firmware(0)
	, m_BoardID(0)
	, m_nInputs(0)
	, m_nAnaIns(0)
	, m_nAnaOuts(0)
	, m_nMavg(0)
	, m_nAxis(0)
	, m_Verbosity(0)
	, m_Controller(_T(""))
	, m_ExternalInc(0)
	, m_InternalInc(0)
	, m_nOutPuts(0)
{
}

G100FLASHCONFIG::~G100FLASHCONFIG()
{
}

void G100FLASHCONFIG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FIRMWARE, m_Firmware);
	DDX_Text(pDX, IDC_BOARDID, m_BoardID);
	DDX_Text(pDX, IDC_VENDOR, m_VendorID);
	DDX_Text(pDX, IDC_NINPUT, m_nInputs);
	DDX_Text(pDX, IDC_NANAIN, m_nAnaIns);
	DDX_Text(pDX, IDC_NANAOUT, m_nAnaOuts);
	DDX_Text(pDX, IDC_MAVG, m_nMavg);
	DDX_Text(pDX, IDC_NAXIS, m_nAxis);
	DDX_Text(pDX, IDC_VERBOSITY, m_Verbosity);
	DDX_Text(pDX, IDC_CONTROLNAME, m_Controller);
	DDX_Control(pDX, IDC_IPG100, m_IP);
	DDX_Control(pDX, IDC_NETMASK, m_NetMask);
	DDX_Control(pDX, IDC_NETFLAGS, m_NetFlags);
	DDX_Control(pDX, IDC_PULSEMODE, m_PulseMode);
	DDX_Control(pDX, IDC_COUNTERTRIGGER, m_EncoderCtrl);
	DDX_Text(pDX, IDC_EXTINC, m_ExternalInc);
	DDX_Text(pDX, IDC_INTINC, m_InternalInc);
	DDX_Control(pDX, IDC_DIVIDER, m_Freq);
	DDX_Radio(pDX, IDC_AXISSEL, m_CurSel);
	DDX_Text(pDX, IDC_NOUTPUTS, m_nOutPuts);
}


BEGIN_MESSAGE_MAP(G100FLASHCONFIG, CDialog)
	ON_BN_CLICKED(ID_FLASH, OnBnClickedFlash)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_READSETUP, OnBnClickedReadsetup)
	ON_BN_CLICKED(IDC_AXISSEL, OnBnClickedAxissel)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnBnClickedRadio6)
	ON_CBN_SELCHANGE(IDC_PULSEMODE, OnCbnSelchangePulsemode)
	ON_CBN_SELCHANGE(IDC_COUNTERTRIGGER, OnCbnSelchangeCountertrigger)
	ON_EN_CHANGE(IDC_EXTINC, OnEnChangeExtinc)
	ON_CBN_SELCHANGE(IDC_DIVIDER, OnCbnSelchangeDivider)
	ON_EN_CHANGE(IDC_INTINC, OnEnChangeIntinc)
	ON_CBN_SELCHANGE(IDC_NETFLAGS, OnCbnSelchangeNetflags)
	ON_EN_CHANGE(IDC_VERBOSITY, OnEnChangeVerbosity)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPG100, OnIpnFieldchangedIpg100)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_NETMASK, OnIpnFieldchangedNetmask)
	ON_EN_CHANGE(IDC_CONTROLNAME, OnEnChangeControlname)
END_MESSAGE_MAP()


// G100FLASHCONFIG message handlers

void G100FLASHCONFIG::OnBnClickedFlash()
{

	//Lets create this on a backup file so later on it can be either compared, 
	//or recovered for a new Grex. This File GConf.dat will store the complete 
	// GREX WT_CONFIG block. All data will be saved. 
	CFile GConf;
    CString fname;
    fname.Format( "%s\\Macros\\%s\\GConf.dat", DefDir , Profile );
    if( GConf.Open( fname ,CFile::modeWrite | CFile::modeCreate, NULL)) 
    {	
 	 try 
	 {
	    GConf.Write( &G100.Config , sizeof( WTConfig));  
     }
	catch(...)
	{
         
	}
	GConf.Close();
	//So now the File is updated, so lets Flash the G100 so its all permanent. 
	// This will store the IP and NetMask permanently if its was only temp as well.
	// Redisovery will set the temp assignments as well, so no need to do that.
	ImmediateMess.Header.type = WT_CONFIG;
	ImmediateMess.Header.chanflgs = UCHAN_WNDO;
	ImmediateMess.Header.chksum = 0;
	ImmediateMess.Header.ack = 0;
	ImmediateMess.Header.resv = 0;
	ImmediateMess.Header.seq = G100.LastAck+1; //set for the next message number
	memcpy( ImmediateMess.Message, &G100.Config, sizeof( WTConfig ));
	SendImmediateMessage(sizeof( WTConfig )+sizeof(MessageHdr) );  //Send a general WTCONFIG and reboot G100. 
	MessageBox("Flashing and Rebooting");
	Sleep( 4000 );
	myPostInitControl(); //Start the rediscovery process so we Reconnect. 
	//myPostInitControl should setup startup defaults as well. 
	 
  }
  else
    MessageBox("Could not save GRex config data."); //Oops, file error ro something..warn the user ..
                                                    // No file, no flash. Fix that and reflash the G100.	
	OnOK();
  }

void G100FLASHCONFIG::OnBnClickedOk()
{
	// Simple Exit, data was only played with. 
	// Caution here though, data can be changed temporarily here
	// in the config , but will affect only this run. 
	//Each run will load the config from the G100 foe startup defaults. 
	//Not from the cfg file. Though they should be compared.
	OnOK();
}

 

void G100FLASHCONFIG::OnBnClickedReadsetup()
{
  //User has selected a general overwrite of the config data
  // If must be reflashed or it will be lost..

	CFile GConf;
    CString fname;
    fname.Format( "%s\\Macros\\%s\\GConf.dat", DefDir , Profile );
    if( GConf.Open( fname ,CFile::modeRead , NULL)) 
    {	
 	 try 
	 {
	    GConf.Read( &G100.Config , sizeof( WTConfig));  
     }
	catch(...)
	{
         
	}
	GConf.Close();
	MessageBox( "Configuration overwritten by previously saved config.",MB_OK);
   }
  else
    MessageBox("Could not read GRex config data.");
	FillData();
	 
}

BOOL G100FLASHCONFIG::OnInitDialog()
{
	CDialog::OnInitDialog();
	if( G100.PHASE != RUNONIP )
	{
		MessageBox( "G100 not connected or busy. ReDiscover , then reselect this dialog." );
		OnOK();
		return false;
	}
	m_CurSel = 0;
	FillData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void G100FLASHCONFIG::FillData(void)
{
 //Display the data current to the G100's setup..
	m_Firmware =      G100.Config.fpga_id;
	m_BoardID =       G100.Config.board_id;
	m_VendorID =      G100.Config.datecode;
	m_nInputs =       G100.Config.input_bits;
	m_nOutPuts =      G100.Config.output_bits;
	m_nAnaIns =       G100.Config.input_ana;
	m_nAnaOuts =      G100.Config.output_ana;
	m_nMavg =         G100.Config.max_mavg;
	m_nAxis =         G100.Config.axes_compiled;
	m_Verbosity =     G100.Config.verbosity;
	m_Controller=     (LPCTSTR)G100.Config.vend_id;
	m_IP.SetAddress( G100.Config.ipaddr );
	m_NetMask.SetAddress( G100.Config.netmask );
	m_NetFlags.SetCurSel( G100.Config.netflags );

	m_PulseMode.SetCurSel( G100.Config.axis[m_CurSel].out_mode );
	m_EncoderCtrl.SetCurSel( G100.Config.axis[m_CurSel].ctr_mode);
	m_ExternalInc = G100.Config.axis[m_CurSel].ext_ctr;
	m_InternalInc = G100.Config.axis[m_CurSel].int_ctr;
	m_Freq.SetCurSel( G100.Config.axis[m_CurSel].divider);

    UpdateData( false );

}

void G100FLASHCONFIG::OnBnClickedAxissel()
{
	UpdateData( true );
	FillData();
}

void G100FLASHCONFIG::OnBnClickedRadio2()
{
    UpdateData( true );
	FillData();
}

void G100FLASHCONFIG::OnBnClickedRadio3()
{
	UpdateData( true );
	FillData();
}

void G100FLASHCONFIG::OnBnClickedRadio4()
{
	UpdateData( true );
	FillData();
}

void G100FLASHCONFIG::OnBnClickedRadio5()
{
	UpdateData( true );
	FillData();
}

void G100FLASHCONFIG::OnBnClickedRadio6()
{
	UpdateData( true );
	FillData();
}

void G100FLASHCONFIG::OnCbnSelchangePulsemode()
{
	G100.Config.axis[m_CurSel].out_mode = m_PulseMode.GetCurSel();
}

void G100FLASHCONFIG::OnCbnSelchangeCountertrigger()
{
	G100.Config.axis[m_CurSel].ctr_mode = m_EncoderCtrl.GetCurSel();
}

void G100FLASHCONFIG::OnEnChangeExtinc()
{
	UpdateData( true );
	G100.Config.axis[m_CurSel].ext_ctr = m_ExternalInc;
}

void G100FLASHCONFIG::OnCbnSelchangeDivider()
{
	G100.Config.axis[m_CurSel].divider = m_Freq.GetCurSel();
}

void G100FLASHCONFIG::OnEnChangeIntinc()
{
	UpdateData( true );
	G100.Config.axis[m_CurSel].int_ctr = m_InternalInc;
}

void G100FLASHCONFIG::OnCbnSelchangeNetflags()
{
	G100.Config.netflags = m_NetFlags.GetCurSel();
}

void G100FLASHCONFIG::OnEnChangeVerbosity()
{
	UpdateData( true );
	G100.Config.verbosity = m_Verbosity;
}

void G100FLASHCONFIG::OnIpnFieldchangedIpg100(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	*pResult = 0;
    DWORD Address; 
	m_IP.GetAddress(Address);
	G100.Config.ipaddr = Address;
}

void G100FLASHCONFIG::OnIpnFieldchangedNetmask(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
    DWORD Address; 
	m_NetMask.GetAddress(Address);
	G100.Config.netmask = Address;
}

void G100FLASHCONFIG::OnEnChangeControlname()
{
	UpdateData( true );
	memcpy( G100.Config.vend_id, m_Controller.GetBuffer(35), 35 );
}



