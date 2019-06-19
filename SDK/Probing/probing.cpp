// probing.cpp : implementation file
//

#include "stdafx.h"
#include "MachDevice.h"
#include "probing.h"


// probing dialog

IMPLEMENT_DYNAMIC(probing, CDialog)
probing::probing(CWnd* pParent /*=NULL*/)
	: CDialog(probing::IDD, pParent)
{
}

probing::~probing()
{
}

void probing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(probing, CDialog)
END_MESSAGE_MAP()


// probing message handlers
