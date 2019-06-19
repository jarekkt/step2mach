// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "MySplitterWnd.h"
#include "VBEditThread.h"

class CMach4View;
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	CMySplitterWnd m_wndSplitter;
public:
	CView *pVBView;
	CView *MachView;
	

// Operations
	bool Asked;
public:
	void OnClose();

// Overrides
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
	CMach4View* GetLeftPane();
	void OnAppExit();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	
#endif
	void  OnRunStart();
	void CMainFrame::OnRunEnd();
	void CMainFrame::OnSetBreak();
	void CMainFrame::OnKillBreak();
	void CMainFrame::OnSingleStep();
	void CMainFrame::OnRewind();
	void OnSaveScript();
	void OnOpenScript();
	void TurnOffVB();

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	VBEditThread  *VBEdit;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOperatorVbscripteditor();
};


