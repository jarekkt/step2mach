#pragma once

#include "MyToolbar.h"
// VBFrame frame

class VBFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(VBFrame)
public:
	VBFrame();           // protected constructor used by dynamic creation
	virtual ~VBFrame();
	CView *pView;
	CMyToolBar myBar;
    CToolTipCtrl m_toolTip;
	CStatusBar  m_wndStatusBar;
 

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnVbfileopen();
	afx_msg void OnVbfileclose();
	afx_msg void OnVbFind();
	afx_msg void OnVbReplace();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditFindnext();
	afx_msg void OnVbrun();
	afx_msg void OnDebugStepinto();
	afx_msg void OnDebugStepover();
	afx_msg void OnDebugEnd();
	afx_msg void OnBreakpointsSetbreakpoint();
	afx_msg void OnBreakpointsClearallbreakpoints();
	afx_msg void OnBreakpointsEnumeratebreakpoints();
	afx_msg void OnRunRun();
	afx_msg void OnRunStop();
	afx_msg void OnDebugRun();
	afx_msg void OnDebugReset();
	afx_msg void OnFileSavefile();
	afx_msg void OnFileSaveas();
	afx_msg void OnDestroy();
	void LoadFile( );
	afx_msg void OnDebugContinue();
	afx_msg void OnUndo();
	afx_msg void OnCut();
	afx_msg void OnCopy();
	afx_msg void OnPaste();
	afx_msg void OnClear();
	afx_msg void OnSelall();
	afx_msg void OnFileOptions();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnClose();
};


