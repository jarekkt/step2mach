// G100FLASHCONFIG.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MachDevice.h"
#include "G100FLASHCONFIG.h"
#include ".\g100flashconfig.h"
#include "G100-Structs.h"
#include "GRexControl.h"
#include "TrajectoryControl.h"
 

extern GRexControl *TheRex;
extern TrajectoryControl *MainPlanner;	// used for most planner funcitons and program control 

extern int m_AnaSel;
extern bool m_SpinAnaOff;

extern int GLookAhead;
WTConfig  LocalConfig;
extern CString DefDir;
extern CString Profile;
extern double m_CVRadius;
extern double m_MaxDev;
//extern G100Message  ImmediateMess;
extern void SendImmediateMessage(int size);
extern void myPostInitControl();
extern double ASC;

extern bool IPValid;
extern unsigned int  IP;
extern int MPGs[3];

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
	, m_MaxVel(0)
	, m_MaxAcc(0)
	, m_SpinOnOff(FALSE)
	, m_AnaSelect(FALSE)
	, m_Rad(0)
	, m_LookAhead(0)
	, m_ASC(0)
	, m_MaxD(0)
{
}

G100FLASHCONFIG::~G100FLASHCONFIG()
{
}

void G100FLASHCONFIG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_GFIRMWARE, m_Firmware);
	DDX_Text(pDX, IDC_GBOARDID, m_BoardID);
	DDX_Text(pDX, IDC_GVENDOR, m_VendorID);
	DDX_Text(pDX, IDC_GNINPUT, m_nInputs);
	DDX_Text(pDX, IDC_GNANAIN, m_nAnaIns);
	DDX_Text(pDX, IDC_GNANAOUT, m_nAnaOuts);
	DDX_Text(pDX, IDC_GMAVG, m_nMavg);
	DDX_Text(pDX, IDC_GNAXIS, m_nAxis);
	DDX_Text(pDX, IDC_GCONTROLNAME, m_Controller);
	DDX_Control(pDX, IDC_GIPG100, m_IP);
	DDX_Control(pDX, IDC_GNETMASK, m_NetMask);
	DDX_Control(pDX, IDC_GNETFLAGS, m_NetFlags);
	DDX_Control(pDX, IDC_GPULSEMODE, m_PulseMode);
	DDX_Control(pDX, IDC_GCOUNTERTRIGGER, m_EncoderCtrl);
	DDX_Text(pDX, IDC_GEXTINC, m_ExternalInc);
	DDX_Text(pDX, IDC_GINTINC, m_InternalInc);
	DDX_Control(pDX, IDC_GDIVIDER, m_Freq);
	DDX_Radio(pDX, IDC_GAXISSEL, m_CurSel);
	DDX_Text(pDX, IDC_GNOUTPUTS, m_nOutPuts);

	DDX_Text(pDX, IDC_GMAXVEL, m_MaxVel);
	DDX_Text(pDX, IDC_GMAXACC, m_MaxAcc);
	DDX_Check(pDX, IDC_ANAONOFF, m_SpinOnOff);
	DDX_Radio(pDX, IDC_ANASEL, m_AnaSelect);
	DDX_Text(pDX, IDC_CVRAD, m_Rad);
	DDX_Control(pDX, IDC_GMPG1, m_MPG1);
	DDX_Control(pDX, IDC_GMPG2, m_MPG2);
	DDX_Control(pDX, IDC_GMPG3, m_MPG3);
	DDX_Text(pDX, IDC_GLOOKAHEAD, m_LookAhead);
	DDX_Slider(pDX, IDC_ASC, m_ASC);
	DDX_Control(pDX, IDC_ASC, m_AscCtrl);
	DDX_Text(pDX, IDC_MAXDEV, m_MaxD);
}


BEGIN_MESSAGE_MAP(G100FLASHCONFIG, CDialog)
	ON_BN_CLICKED(ID_FLASH, OnBnClickedFlash)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_READSETUP, OnBnClickedReadsetup)
	ON_BN_CLICKED(IDC_GAXISSEL, OnBnClickedAxissel)
	ON_BN_CLICKED(IDC_GRADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_GRADIO3, OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_GRADIO4, OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_GRADIO5, OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_GRADIO6, OnBnClickedRadio6)
	ON_CBN_SELCHANGE(IDC_GPULSEMODE, OnCbnSelchangePulsemode)
	ON_CBN_SELCHANGE(IDC_GCOUNTERTRIGGER, OnCbnSelchangeCountertrigger)
	ON_EN_CHANGE(IDC_GEXTINC, OnEnChangeExtinc)
	ON_CBN_SELCHANGE(IDC_GDIVIDER, OnCbnSelchangeDivider)
	ON_EN_CHANGE(IDC_GINTINC, OnEnChangeIntinc)
	ON_CBN_SELCHANGE(IDC_GNETFLAGS, OnCbnSelchangeNetflags)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_GIPG100, OnIpnFieldchangedIpg100)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_GNETMASK, OnIpnFieldchangedNetmask)
	ON_EN_CHANGE(IDC_CONTROLNAME, OnEnChangeControlname)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ASC, OnNMReleasedcaptureAsc)
END_MESSAGE_MAP()


// G100FLASHCONFIG message handlers

void G100FLASHCONFIG::OnBnClickedFlash()
{
	UpdateData(true);
	m_CVRadius = m_Rad;
	m_MaxDev = m_MaxD;
	m_AnaSel = m_AnaSelect;
	m_SpinAnaOff = m_SpinOnOff; 
	//Lets create this on a backup file so later on it can be either compared, 
	//or recovered for a new Grex. This File GConf.dat will store the complete 
	// GREX WT_CONFIG block. All data will be saved. 
	CFile GConf;
    CString fname;
	IP = LocalConfig.ipaddr;
	IPValid = true;
	fname.Format( "%s\\Macros\\%s\\GConf.dat", DefDir , Profile );
    if( GConf.Open( fname ,CFile::modeWrite | CFile::modeCreate, NULL)) 
    {	
 	 try 
	 {
	    GConf.Write( &LocalConfig , sizeof( WTConfig));  
     }
	catch(...)
	{
         
	}
	GConf.Close();
	//So now the File is updated, so lets Flash the G100 so its all permanent. 
	// This will store the IP and NetMask permanently if its was only temp as well.
	// Redisovery will set the temp assignments as well, so no need to do that.
    //set the config into the flash..

	TheRex->p->setConfig(1,0,1,0,&LocalConfig,NULL);
	//myPostInitControl should setup startup defaults as well. 
	Sleep(100); 
  }
  else
    MessageBox("Could not save GRex config data."); //Oops, file error ro something..warn the user ..
                                                    // No file, no flash. Fix that and reflash the TheRex->	
	OnOK();
  }

void G100FLASHCONFIG::OnBnClickedOk()
{
	// Simple Exit, data was only played with. 
	UpdateData(true);
	m_AnaSel = m_AnaSelect;
	m_SpinAnaOff = m_SpinOnOff; 
	m_CVRadius = m_Rad;
	m_MaxDev = m_MaxD;

	MPGs[0] = m_MPG1.GetCurSel();
	MPGs[1] = m_MPG2.GetCurSel();
	MPGs[2] = m_MPG3.GetCurSel();
    if( m_LookAhead > 100) m_LookAhead = 100;
	GLookAhead = m_LookAhead;

	 
	 
	OnOK();
}

 

void G100FLASHCONFIG::OnBnClickedReadsetup()
{
  //User has selected a general overwrite of the config data
  // If must be reflashed or it will be lost..
/*
	CFile GConf;
    CString fname;
    fname.Format( "%s\\Macros\\%s\\GConf.dat", DefDir , Profile );
    if( GConf.Open( fname ,CFile::modeRead , NULL)) 
    {	
 	 try 
	 {
	    GConf.Read( &TheRex->Config , sizeof( WTConfig));  
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
	*/
	 
}

BOOL G100FLASHCONFIG::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_AnaSelect = m_AnaSel;
	m_SpinOnOff = m_SpinAnaOff;
	m_Rad = m_CVRadius;
	m_MaxD = m_MaxDev;
    m_LookAhead = GLookAhead;
	m_AscCtrl.SetRange(0,1000,false);
    m_ASC = (int)(ASC * 10);
	if( TheRex->PHASE != RUNONIP )
	{
		MessageBox( "G100 not connected or busy. ReDiscover , then reselect this dialog." );
		OnOK();
		return false;
	}
	m_CurSel = 0;
	memcpy( &LocalConfig,TheRex->Config(),sizeof(WTConfig));
	FillData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void G100FLASHCONFIG::FillData(void)
{
 //Display the data current to the G100's setup..
	m_ASC = (int)(ASC * 10);
	m_Firmware =      LocalConfig.fpga_id;
	m_BoardID =       LocalConfig.board_id;
	m_VendorID =      LocalConfig.datecode;
	m_nInputs =       LocalConfig.input_bits;
	m_nOutPuts =      LocalConfig.output_bits;
	m_nAnaIns =       LocalConfig.input_ana;
	m_nAnaOuts =      LocalConfig.output_ana;
	m_nMavg =         LocalConfig.max_mavg;
	m_nAxis =         LocalConfig.axes_compiled;
	m_Controller=     (LPCTSTR)LocalConfig.vend_id;
	m_IP.SetAddress( LocalConfig.ipaddr );
	m_NetMask.SetAddress( LocalConfig.netmask );
	m_NetFlags.SetCurSel( LocalConfig.netflags );

	int mode = LocalConfig.axis[m_CurSel].out_mode;

	m_PulseMode.SetCurSel(0 );
	switch ( mode )
	{
	case( OM_SD_50 ) :    m_PulseMode.SetCurSel(0); break;
	case( OM_SD_50_INV) : m_PulseMode.SetCurSel(1); break;
	case( OM_SD_25) :     m_PulseMode.SetCurSel(2); break;
	case( OM_SD_75) :     m_PulseMode.SetCurSel(3); break;
	case( OM_SD_QUAD) :   m_PulseMode.SetCurSel(4); break;

	}
	m_EncoderCtrl.SetCurSel( LocalConfig.axis[m_CurSel].ctr_mode);
	m_ExternalInc = LocalConfig.axis[m_CurSel].ext_ctr;
	m_InternalInc = LocalConfig.axis[m_CurSel].int_ctr;
	m_Freq.SetCurSel( LocalConfig.axis[m_CurSel].divider);
    //now set the max accel and max velocities..
	for(int x = 0; x < 6 ; x++)
	{
		double ispos = ((double) (8 <<LocalConfig.axis[x].divider));
		double maxv = (32768 * MainPlanner->Velocities[x] * MainPlanner->StepsPerAxis[x] ) / (33554432/ispos);    //stesp/ms.
		double maxa = (MainPlanner->Acceleration[x] * MainPlanner->StepsPerAxis[x] * ispos)/ 1048576; //steps/ms^2

		LocalConfig.axis[x].maxv = (float)maxv;
		LocalConfig.axis[x].maxa = (float)maxa;
	}

	m_MaxAcc = LocalConfig.axis[m_CurSel].maxa;
	m_MaxVel = LocalConfig.axis[m_CurSel].maxv;

	m_MPG1.SetCurSel(MPGs[0]);
	m_MPG2.SetCurSel(MPGs[1]);
	m_MPG3.SetCurSel(MPGs[2]);

    
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
	LocalConfig.axis[m_CurSel].out_mode = 0;
	int mode = m_PulseMode.GetCurSel();

	switch ( mode )
	{
	case( 0) :    LocalConfig.axis[m_CurSel].out_mode = OM_SD_50; break;
	case( 1) :    LocalConfig.axis[m_CurSel].out_mode = OM_SD_50_INV; break;
	case( 2) :    LocalConfig.axis[m_CurSel].out_mode =  OM_SD_25; break;
	case( 3) :    LocalConfig.axis[m_CurSel].out_mode = OM_SD_75; break;
	case( 4) :    LocalConfig.axis[m_CurSel].out_mode = OM_SD_QUAD; break;
	}
}

void G100FLASHCONFIG::OnCbnSelchangeCountertrigger()
{
	LocalConfig.axis[m_CurSel].ctr_mode = m_EncoderCtrl.GetCurSel();
}

void G100FLASHCONFIG::OnEnChangeExtinc()
{
	UpdateData( true );
	LocalConfig.axis[m_CurSel].ext_ctr = m_ExternalInc;
}

void G100FLASHCONFIG::OnCbnSelchangeDivider()
{
	LocalConfig.axis[m_CurSel].divider = m_Freq.GetCurSel();
}

void G100FLASHCONFIG::OnEnChangeIntinc()
{
	UpdateData( true );
	LocalConfig.axis[m_CurSel].int_ctr = m_InternalInc;
}

void G100FLASHCONFIG::OnCbnSelchangeNetflags()
{
	LocalConfig.netflags = m_NetFlags.GetCurSel();
}

 

void G100FLASHCONFIG::OnIpnFieldchangedIpg100(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	*pResult = 0;
    DWORD Address; 
	m_IP.GetAddress(Address);
	LocalConfig.ipaddr = Address;
}

void G100FLASHCONFIG::OnIpnFieldchangedNetmask(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
    DWORD Address; 
	m_NetMask.GetAddress(Address);
	LocalConfig.netmask = Address;
}

void G100FLASHCONFIG::OnEnChangeControlname()
{
	UpdateData( true );
	memcpy( &LocalConfig.vend_id, m_Controller.GetBuffer(35), 35 );
}




void G100FLASHCONFIG::OnNMReleasedcaptureAsc(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(true);
	ASC = ((double)m_ASC) / 10;
	if( ASC == 0)
		TheRex->p->setCoalesce(0,0,NULL);
	else
		TheRex->p->setCoalesce(1,ASC,NULL);
	*pResult = 0;
}
