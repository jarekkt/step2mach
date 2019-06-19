#pragma once
#include "afxcmn.h"


// InputSignals dialog

class InputSignals : public CPropertyPage
{
	DECLARE_DYNAMIC(InputSignals)

public:
	InputSignals();
	virtual ~InputSignals();
    CImageList m_ImageList;
	virtual BOOL OnSetActive();
	static BOOL CALLBACK GridCallBack(GV_DISPINFO *pDispInfo, LPARAM /*lParam*/);
	LRESULT OnListChanged( WPARAM, LPARAM);
	void SetData();

// Dialog Data
	enum { IDD = IDD_INPUTSIGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	CGridCtrl m_Inputs;
	void StoreResults(void);
	virtual void OnOK();
	virtual BOOL OnApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
