#pragma once
#include "spindgraph.h"
#include "afxwin.h"
#include "resource.h"

// ScewMap dialog

class ScewMap : public CDialog
{
	DECLARE_DYNAMIC(ScewMap)

public:
	ScewMap(CWnd* pParent = NULL);   // standard constructor
	virtual ~ScewMap();

// Dialog Data
	enum { IDD = IDD_SCREWMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedClear1();
	afx_msg void OnBnClickedClear2();
	afx_msg void OnBnClickedClear3();
	double m_XCoor;
	double m_YCoor;
	double m_ZCoor;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedReadencoder();
	afx_msg void OnBnClickedAddcorrection();
	double m_RealX;
	double m_RealY;
	double m_RealZ;
	CSpindgraph m_Graph;
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT nIDEvent);
	CEdit m_XBox;
	CEdit m_YBox;
	CEdit m_ZBox;
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedForward();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	void    Graphit();
	int     m_MapAxis;
	double m_ScrewX,m_ScrewY,m_ScrewZ;
	afx_msg void OnBnClickedCheck2();
	BOOL m_Xon;
	BOOL m_Yon;
	BOOL m_Zon;
};
