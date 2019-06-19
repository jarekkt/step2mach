// ScriptView.h : interface of the CScriptEditView class
//

#ifndef SCRIPTEDITVIEW
#define SCRIPTEDITVIEW 1

class CScriptEditView : public CEditView 
{
	DECLARE_DYNCREATE(CScriptEditView)

// Construction
public:
	CScriptEditView();

// Attributes
public:

// Operations
public:
	BOOL OpenFile(LPCTSTR lpszPathName);
	BOOL SaveFile(LPCTSTR lpszPathName);
	void SetDefaultDispatch( IDispatch *pDispatch ) { m_pDefDispatch = pDispatch; };

	HRESULT DisplayResultCodeMessage(HRESULT hr);
	HRESULT PrepareContext(HANDLE &hCtx);
	HRESULT CompileEditWindowScript();
	void FreeContext();
	CDocument* GetDocument( ); 


	HRESULT RunScript(LPCTSTR lpszScriptText);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptEditView)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	HANDLE	m_hCtx;
	IDispatch *m_pDefDispatch;

// Generated message map functions
public:
	//{{AFX_MSG(CScriptEditView)
	afx_msg void OnUpdateRunStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRunEnd(CCmdUI* pCmdUI);
	afx_msg void OnDebugStepInto();
	afx_msg void OnDebugStepOver();
	afx_msg void OnDebugToggleBreakpoint();
	afx_msg void OnDebugClearBreakpoints();
	afx_msg void OnRunStart();
	afx_msg void OnRunEnd();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual void OnDraw(CDC* /*pDC*/);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
	virtual void OnActivateView(BOOL bActivate,CView* pActivateView, CView* pDeactiveView);

	afx_msg void OnEnChange();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	 
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

#endif
/////////////////////////////////////////////////////////////////////////////
