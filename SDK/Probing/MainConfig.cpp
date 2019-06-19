// MainConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MachDevice.h"
#include "MainConfig.h"
#include ".\mainconfig.h"
 


// MainConfig dialog

IMPLEMENT_DYNAMIC(MainConfig, CDialog)
MainConfig::MainConfig(CWnd* pParent /*=NULL*/)
	: CDialog(MainConfig::IDD, pParent)
{
}

MainConfig::~MainConfig()
{
}

void MainConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainConfig, CDialog)
	ON_BN_CLICKED(IDC_TOOLTOUCH, OnBnClickedTooltouch)
	ON_BN_CLICKED(IDC_CIRCLECENTER, OnBnClickedCirclecenter)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// MainConfig message handlers

void MainConfig::OnBnClickedTooltouch()
{
 
}

void MainConfig::OnBnClickedCirclecenter()
{
	AfxMessageBox( "Not yet implemented" );
}

void MainConfig::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
