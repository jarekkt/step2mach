#pragma once
#include "videoocxctrl1.h"
#include "videoocxtoolsctrl2.h"
#include "afxwin.h"


// Mach3Video dialog

class Mach3Video : public CDialog
{
	DECLARE_DYNAMIC(Mach3Video)

public:
	Mach3Video(CWnd* pParent = NULL);   // standard constructor
	virtual ~Mach3Video();

// Dialog Data
	enum { IDD = IDD_VIDEO };
	int m_ToolNumber;
	BOOL m_Running;
	BOOL m_FlipFlag;
	long m_Image;
	long m_ResultImage;
	long m_HelperImage;
	bool CrossHairs;
	int CrossX,CrossY;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CVideoocxctrl1 m_VideoOCX;
	CVideoocxtoolsctrl2 m_VideoOCXTools;
	afx_msg void OnBnClickedSetcamera();
	afx_msg void OnBnClickedOriginal();
	afx_msg void OnBnClickedEdgemag();
	afx_msg void OnBnClickedEdgedir();
	afx_msg void OnBnClickedMotion();
	afx_msg void OnBnClickedFlip();
	CButton m_Flip;
	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnBnClickedCross();
	CButton m_Cross;
	afx_msg void OnBnClickedCrosshair();
	afx_msg void OnBnClickedButtonstop();
	virtual BOOL OnInitDialog();
	BOOL m_FlipImage;
	BOOL m_CrossHairs;
	afx_msg void OnClose();
	void    DrawCircles();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	
};
