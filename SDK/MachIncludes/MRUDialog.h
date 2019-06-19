#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "FileList.h"


// MRUDialog dialog

class MRUDialog: public CDialog
{
	DECLARE_DYNAMIC(MRUDialog)

public:
	MRUDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~MRUDialog();

// Dialog Data
	enum { IDD = IDD_MRULIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int item;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CString m_FileName;
	FileList m_MRUList;
	afx_msg void OnHdnItemclickMru(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
