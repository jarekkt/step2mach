#pragma once

#include <activscp.h>
#include ".\scripting\activdbg.h"
#include "MyScriptObject.h"

// MacroRun dialog

class MacroRun : public CDialog
{
	DECLARE_DYNCREATE(MacroRun)

public:
	MacroRun(CWnd* pParent = NULL);   // standard constructor
	virtual ~MacroRun();
// Overrides
	bool MacroLoaded; 
	HANDLE hCtx;
	CString def;

// Dialog Data
	enum { IDD = IDD_MACRODUMMY, IDH = IDR_HTML_MACRORUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
    CString Macro;
	MyScriptObject m_myScriptObject;
    void RunScript(void);
    DECLARE_MESSAGE_MAP()
	BSTR pParseText;
	void EditMacroPump();
	 
public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
