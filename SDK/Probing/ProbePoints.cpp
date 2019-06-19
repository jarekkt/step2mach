// ProbePoints.cpp : implementation file
//

#include "stdafx.h"
#include "MachDevice.h"
#include "ProbePoints.h"


// ProbePoints dialog

IMPLEMENT_DYNAMIC(ProbePoints, CDialog)
ProbePoints::ProbePoints(CWnd* pParent /*=NULL*/)
	: CDialog(ProbePoints::IDD, pParent)
{
}

ProbePoints::~ProbePoints()
{
}

void ProbePoints::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ProbePoints, CDialog)
END_MESSAGE_MAP()


// ProbePoints message handlers
