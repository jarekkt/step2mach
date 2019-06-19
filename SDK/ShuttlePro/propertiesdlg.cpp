// propertiesdlg.cpp : implementation file
//

#include "stdafx.h"
#include "MachDevice.h"
#include "propertiesdlg.h"
#include ".\propertiesdlg.h"


extern short ButtonCodes[15];

extern int ProductID;
short m_Macro1;
short m_Macro2;
short m_OEM1;
short m_OEM2;

#define nbuttons  73
char *ButtonLabels[] = 
{
  //800 series are for the plugin to use internally.
  "899,NONE",
  "800,Select X axis",
  "801,Select Y axis",
  "802,Select Z axis",
  "803,Select A axis",
  "804,Select B axis",
  "805,Select C axis",
  "806,Lockout Wheels",
  "807,Unlock  Wheels",
  "808,Lock/Unlock Movement",
  "809,Lock/Unlock  Shuttle",
  "810,Rapid Axis ++",
  "811,Rapid Axis --",
  "812,Cont/Inc Center Mode",
  "813, Custom Macro #1",
  "814, Custom Macro #2",
  "815, OEM Button #1",
  "816, OEM Button #2",
  //these are Mach3 buttons..
  "1000,Run File",
  "1001,Pause",
  "1002,Rewind",
  "1003,Stop File",
  "1004,SingleStep",
  "1007,ZeroAll",
  "1008,ZeroX",
  "1009,ZeroY",
  "1010,ZeroZ",
  "1011,ZeroA",
  "1012,ZeroB",
  "1013,ZeroC",
  "1014,FeedOvrd Reset",
  "1015,Simulate",
  "1016,RunAt",
  "1017,Goto Z's",
  "1018,Machine Coords",
  "1020,Verify",
  "1021,Reset",
  "1022,Home X",
  "1023,Home Y",
  "1024,Home Z",
  "1025,Home A",
  "1026,Home B",
  "1027,Home C",
  "1028,JoyStick",
  "1029,SoftLimits",
  "100,Jog Incr++",
  "101,Jog Incr--",
  "102,RS274 Init",
  "103,Jog On/Off",
  "104,Goto Safe_Z",
  "105,Ref All",
  "106,mm/inch",
  "107,ToGo",
  "108, FeedUp",
  "109, FeedDn",
  "110, Spin on/off",
  "111, Jog% Up",
  "112, Jog% Dn",
  "113, Flood on/off",
  "114, Mist on/off",
  "115, Edit",
  "116, Radius A = 0",
  "117, Radius B = 0",
  "118, Radius C = 0",
  "119, SoftLimits On/Off",
  "120, Touch Tool",
  "123, THC On/Off",
  "124, Zero THC",
  "132, Toolpath on/off",
  "258, OnLine ",
  "257, OffLine",
  "178, On/Off Online Toggle",
  "171, Cycle Jog Inc."

};
char *ButtonWheelLables[] = 
{
  "1,Cont mode",
  "1,Inc mode"
};



// propertiesdlg dialog

IMPLEMENT_DYNAMIC(propertiesdlg, CDialog)
propertiesdlg::propertiesdlg(CWnd* pParent /*=NULL*/)
	: CDialog(propertiesdlg::IDD, pParent)
	, test(0)
	, m_Type(1)
	, m_dMacro1(0)
	, m_dMacro2(0)
{
}

propertiesdlg::~propertiesdlg()
{
}

void propertiesdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO1, m_Function[0]);
	DDX_Control(pDX, IDC_COMBO2, m_Function[1]);
	DDX_Control(pDX, IDC_COMBO3, m_Function[2]);
	DDX_Control(pDX, IDC_COMBO4, m_Function[3]);
	DDX_Control(pDX, IDC_COMBO5, m_Function[4]);
	DDX_Control(pDX, IDC_COMBO6, m_Function[5]);
	DDX_Control(pDX, IDC_COMBO7, m_Function[6]);
	DDX_Control(pDX, IDC_COMBO8, m_Function[7]);
	DDX_Control(pDX, IDC_COMBO9, m_Function[8]);
	DDX_Control(pDX, IDC_COMBO10, m_Function[9]);
	DDX_Control(pDX, IDC_COMBO11, m_Function[10]);
	DDX_Control(pDX, IDC_COMBO12, m_Function[11]);
	DDX_Control(pDX, IDC_COMBO13, m_Function[12]);
	DDX_Control(pDX, IDC_COMBO14, m_Function[13]);
	DDX_Control(pDX, IDC_COMBO15, m_Function[14]);
	DDX_Radio(pDX, IDC_TYPE, m_Type);
	DDX_Text(pDX, IDC_MACRO1, m_dMacro1);
	DDX_Text(pDX, IDC_MACRO2, m_dMacro2);
	DDX_Text(pDX, IDC_OEM1, m_dOEM1);
	DDX_Text(pDX, IDC_OEM2, m_dOEM2);
}


BEGIN_MESSAGE_MAP(propertiesdlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO7, OnBnClickedRadio7)
END_MESSAGE_MAP()


// propertiesdlg message handlers

 

BOOL propertiesdlg::OnInitDialog()
{

CDialog::OnInitDialog();

CString copy;
m_dMacro1 = m_Macro1;
m_dMacro2 = m_Macro2;
m_dOEM1 = m_OEM1;
m_dOEM2 = m_OEM2;

if( ProductID == 0x10)  m_Type = 0;
if( ProductID == 0x30)  m_Type = 1;
if( ProductID == 0x20)  m_Type = 2;
if( ProductID == 0x240) m_Type = 3;
if( ProductID == 0x11)  m_Type = 4;
 

for( int a = 0; a < 15; a++ )
{
	m_Function[a].ResetContent();
	for( int x = 0; x < nbuttons; x++)
	{
		CString line = ButtonLabels[x];
		int b = line.Find(",") + 1;
		copy = line.Mid( b , line.GetLength() - b );
		m_Function[a].AddString( copy );
		m_Function[a].SetCurSel(ButtonCodes[a]);

	}
 UpdateData( false );
}
/*for( int a = 15; a <= 16; a++ )
{
	m_Function[a].ResetContent();
	for( int x = 0; x < 3; x++)
	{
		CString line = ButtonWheelLables[x];
		int b = line.Find(",") + 1;
		copy = line.Mid( b , line.GetLength() - b );
		m_Function[a].AddString( copy );
		m_Function[a].SetCurSel(ButtonCodes[a]);

	}
}
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	 
}

void propertiesdlg::OnBnClickedOk()
{
	UpdateData( true );

	m_Macro1 = m_dMacro1;
	m_Macro2 = m_dMacro2;
	m_OEM1 = m_dOEM1;
	m_OEM2 = m_dOEM2;

    for( int a = 0; a < 15; a++ )
    {
		ButtonCodes[a] = m_Function[a].GetCurSel();
	}
	if( m_Type == 0 ) ProductID = 0x10;
	if( m_Type == 1 ) ProductID = 0x30;
	if( m_Type == 2 ) ProductID = 0x20;
	if( m_Type == 3 ) ProductID = 0x240;
	if( m_Type == 4 ) ProductID = 0x11;
 
	OnOK();
}

void propertiesdlg::OnBnClickedRadio7()
{
	// TODO: Add your control notification handler code here
}
