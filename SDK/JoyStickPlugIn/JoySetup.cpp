/ JoySetup.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "JoySetup.h"
#include ".\joysetup.h"


extern int  XJoyAxis;
extern int  YJoyAxis;

// JoySetup dialog

IMPLEMENT_DYNAMIC(JoySetup, CDialog)
JoySetup::JoySetup(CWnd* pParent /*=NULL*/)
	: CDialog(JoySetup::IDD, pParent)
	, m_JoyOn(FALSE)
	, m_Horiz(0)
	, m_Vert(0)
{
}

JoySetup::~JoySetup()
{
}

void JoySetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_ENABLE, m_JoyOn);
	DDX_CBIndex(pDX, IDC_HORIZAXIS, m_Horiz);
	DDX_CBIndex(pDX, IDC_VERTAXIS, m_Vert);
}


BEGIN_MESSAGE_MAP(JoySetup, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
//	ON_NOTIFY(TTN_GETDISPINFO, IDC_CUSTOM1, OnTtnGetDispInfoCustom1)
END_MESSAGE_MAP()


// JoySetup message handlers

BOOL JoySetup::OnInitDialog()
{
	CDialog::OnInitDialog();
    m_Horiz = XJoyAxis;
	m_Vert = YJoyAxis;
	UpdateData( false );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void JoySetup::OnBnClickedOk()
{
	UpdateData( true );
	OnOK();
}

void JoySetup::OnTtnGetDispInfoCustom1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTTDISPINFO pNMTTDI = reinterpret_cast<LPNMTTDISPINFO>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
