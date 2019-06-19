#pragma once


// ReProcessWin frame

class ReProcessWin : public CFrameWnd
{
	
public:
	DECLARE_DYNCREATE(ReProcessWin)
	ReProcessWin();           // protected constructor used by dynamic creation
	virtual ~ReProcessWin();
	virtual BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle = WS_VISIBLE | WS_CHILD);
    bool m_bCreated;
	CToolBar m_wndToolBar;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


