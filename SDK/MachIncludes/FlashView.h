#pragma once
#include "ControlRect.h"


struct Toolpaths 
{
    CControlRect *cToolPath;
	int XYWidthHeight[4];
	int RXYWidthHeight[4];
	bool Showing;
};


// FlashView view

class FlashView : public CView
{
	DECLARE_DYNCREATE(FlashView)

public:
	FlashView();           // protected constructor used by dynamic creation
	virtual ~FlashView();

	CControlRect *cToolPath;
	CControlRect *cMDILine;
	CControlRect *cGCodeList;

	

//toolpath
	int ToolX,ToolY,ToolWidth,ToolHeight; //real settings
	int RToolX,RToolY,RToolWidth,RToolHeight; //requested settings..
//Gcode
    int GCodeX,GCodeY,GCodeWidth,GCodeHeight; //real settings
	int RGCodeX,RGCodeY,RGCodeWidth,RGCodeHeight; //requested settings..

//MDILine
	int MDIX,MDIY,MDIWidth,MDIHeight; //real settings
	int RMDIX,RMDIY,RMDIWidth,RMDIHeight; //requested settings..


public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnChangeUIState(UINT nAction, UINT nUIElement);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);

	Toolpaths  Displays[25];
	int        CurShow;

};


