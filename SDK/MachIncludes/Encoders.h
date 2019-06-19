#pragma once
#include "afxcmn.h"


class Encoders : public CPropertyPage
{
	DECLARE_DYNAMIC(Encoders)

public:
	Encoders();
	virtual ~Encoders();
    CImageList m_ImageList;
	virtual BOOL OnSetActive();
	static BOOL CALLBACK GridCallBack(GV_DISPINFO *pDispInfo, LPARAM /*lParam*/);
	LRESULT OnListChanged( WPARAM, LPARAM);
	void SetData();

// Dialog Data
	enum { IDD = IDD_ENCODERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	CGridCtrl m_Encs;
	void StoreResults(void);
	virtual void OnOK();
	virtual BOOL OnApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLvnItemchangedEncs(NMHDR *pNMHDR, LRESULT *pResult);
};
