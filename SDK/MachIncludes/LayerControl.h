#if !defined(AFX_LAYERCONTROL_H__59F14DF3_B2A0_4AC4_ADB3_1D53F9A4BED2__INCLUDED_)
#define AFX_LAYERCONTROL_H__59F14DF3_B2A0_4AC4_ADB3_1D53F9A4BED2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LayerControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LayerControl dialog
#include "./ListCtrl/GridCtrl.h"

#include "DXFDlgDlg.h"
 
class LayerControl : public CDialog
{
// Construction
public:
	static BOOL CALLBACK GridCallBack(GV_DISPINFO *pDispInfo, LPARAM /*lParam*/);
	void SetTitles();
	LayerControl(CWnd* pParent = NULL);   // standard constructor

	int   nLayers;
	MyLayers *Layers;
	CImageList m_ImageList;
// Dialog Data
	//{{AFX_DATA(LayerControl)
	enum { IDD = IDD_LAYERDIALOG };
	CGridCtrl	m_LayerCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LayerControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LayerControl)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAlllevels();
	afx_msg void OnNolevels();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void ReOrder(int Row, int NewOrder);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERCONTROL_H__59F14DF3_B2A0_4AC4_ADB3_1D53F9A4BED2__INCLUDED_)
