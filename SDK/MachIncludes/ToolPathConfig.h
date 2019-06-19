#pragma once
#include "afxwin.h"


// ToolPathConfig dialog

class ToolPathConfig : public CDialog
{
	DECLARE_DYNAMIC(ToolPathConfig)

public:
	ToolPathConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~ToolPathConfig();

// Dialog Data
	enum { IDD = IDD_TOOLCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_OriginSphere;
	BOOL m_3dCompass;
	BOOL m_Boundries;
	BOOL m_ToolPosition;
	BOOL m_AParallel;
	 
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	double m_AtoXOff;
	double m_AtoYOff;
	double m_AtoZOff;
	double	m_BB;
	double	m_BG;
	double	m_BR;
	double	m_FB;
	double	m_FG;
	double	m_FR;
	double	m_RB;
	double	m_RG;
	double	m_RR;
	double	m_AB;
	double	m_AG;
	double	m_AR;
	double	m_EB;
	double	m_EG;
	double	m_ER;
    double  m_MTR;
	double  m_MTG;
	double  m_MTB;
	BOOL m_JogFollow;
	BOOL ARotsOn;
	 
	BOOL m_ToolFlip;
	double m_StockSize;
	BOOL m_ShowSolid;
	BOOL m_Plane;
	BOOL m_Boxed;
	BOOL m_Lines;
};
