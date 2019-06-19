// probeconfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MachDevice.h"
#include "probeconfig.h"
#include ".\probeconfig.h"
#include "XMLProfile.h"
#include "MenuHandler.h"



extern CXMLProfile *DevProf;
extern MenuHandler *Menus;


// probeconfig dialog

IMPLEMENT_DYNAMIC(probeconfig, CDialog)
probeconfig::probeconfig(CWnd* pParent /*=NULL*/)
	: CDialog(probeconfig::IDD, pParent)
	, m_length(0)
	, m_width(0)
	, m_Xstepover(0)
	, m_Ystepover(0)
	, m_probedist(0)
	, m_clearance(0)
	, m_feedrate(0)
	, m_ProbeRad(0)
	, m_Type(FALSE)
	, m_ProbeStuck(0)
{
}

probeconfig::~probeconfig()
{
}

void probeconfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LENGTH, m_length);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Text(pDX, IDC_XSTEPOVER, m_Xstepover);
	DDX_Text(pDX, IDC_CLEAR, m_clearance);
	DDX_Text(pDX, IDC_FEEDRATE, m_feedrate);
	DDX_Text(pDX, IDC_PROBEDIST, m_probedist );
	DDX_Text(pDX, IDC_PROBEDIAM, m_ProbeRad);
	DDX_Text(pDX, IDC_PROBESTUCK, m_ProbeStuck);
}


BEGIN_MESSAGE_MAP(probeconfig, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCEL, OnBnClickedCancel)
	ON_EN_CHANGE(IDC_FEEDRATE, OnEnChangeFeedrate)
	ON_EN_CHANGE(IDC_YSTEPOVER, OnEnChangeYstepover)
	ON_EN_CHANGE(IDC_PROBEDIST, OnEnChangeProbedist)
END_MESSAGE_MAP()


// probeconfig message handlers

BOOL probeconfig::OnInitDialog()
{
	m_Type = 0;
	CDialog::OnInitDialog();

	UpdateData(false);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void probeconfig::OnBnClickedOk()
{
	UpdateData(true);
	if(m_Xstepover < 0 || m_Ystepover < 0)
	{
		AfxMessageBox("ERROR... Grid Distances must set be > 0.00");
		return;
	}
	if(m_width < 0 || m_length < 0)
	{
		AfxMessageBox("ERROR... Width and Length must set be > 0.00");
		return;
	}
	if(m_clearance < 0)
	{
		AfxMessageBox("ERROR... Clearance must set be > 0.00");
		return;
	}
	if(m_feedrate < 0)
	{
		AfxMessageBox("ERROR... Rate must set be > 0.00");
		return;
	}
	if(m_probedist > 0)
	{
		AfxMessageBox("ERROR... Probe Distance must set be < 0.00");
		return;
	}
    
	
	OnOK();
}

void probeconfig::OnBnClickedCancel()
{
	OnCancel();
}

void probeconfig::OnEnChangeFeedrate()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void probeconfig::OnEnChangeYstepover()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void probeconfig::OnEnChangeProbedist()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
