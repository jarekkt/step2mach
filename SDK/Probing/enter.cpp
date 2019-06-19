// enter.cpp : implementation file
//

#include "stdafx.h"
#include "MachDevice.h"
#include "enter.h"
#include ".\enter.h"


// Center dialog

IMPLEMENT_DYNAMIC(Center, CDialog)
Center::Center(CWnd* pParent /*=NULL*/)
	: CDialog(Center::IDD, pParent)
	, m_Xloc(0)
	, m_YLoc(0)
	, m_Rad(0)
{
}

Center::~Center()
{
}

void Center::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_XPOINT, m_Xloc);
	DDX_Text(pDX, IDC_YPOINT, m_YLoc);
	DDX_Text(pDX, IDC_RADIUS, m_Rad);
}


BEGIN_MESSAGE_MAP(Center, CDialog)
	ON_BN_CLICKED(IDC_MOVETO, OnBnClickedMoveto)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// Center message handlers

void Center::OnBnClickedMoveto()
{
	Move = true;
	OnOK();
	// TODO: Add your control notification handler code here
}

BOOL Center::OnInitDialog()
{
	CDialog::OnInitDialog();
    Move = false;
	UpdateData( false );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void Center::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
