#if !defined(AFX_TOOLTABLE_H__F9F410EB_EA59_4864_9FD6_E594461F2BE3__INCLUDED_)
#define AFX_TOOLTABLE_H__F9F410EB_EA59_4864_9FD6_E594461F2BE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolTable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ToolTable dialog

class CToolTable : public CDialog
{
// Construction
public:
	void SetTool(int tool, double diameter, double zoffset, double toolradius, double FeedSpeed,
						  double SpindleSpeed, bool UseFeeds, double xoffset);
	CToolTable(CWnd* pParent = NULL);   // standard constructor
    CImageList m_ImageList;
// Dialog Data
	//{{AFX_DATA(ToolTable)
	enum { IDD = IDD_TOOLTABLE };
	CGridCtrl	m_ToolGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ToolTable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
// Implementation
protected:
    BOOL  OnInitLathe();
	// Generated message map functions
	//{{AFX_MSG(ToolTable)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnApply();
	afx_msg void OnTouch();
	afx_msg void OnSelect();
	afx_msg void OnSetlength();
	afx_msg void OnUseoffset();
	afx_msg void OnUseoffsetoff();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTABLE_H__F9F410EB_EA59_4864_9FD6_E594461F2BE3__INCLUDED_)
