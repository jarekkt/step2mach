#if !defined(AFX_VARIJOGDISPLAY_H__AD87F483_5A1E_4935_B354_750043BA0716__INCLUDED_)
#define AFX_VARIJOGDISPLAY_H__AD87F483_5A1E_4935_B354_750043BA0716__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VariJogDisplay.h : header file
//

 
 
/////////////////////////////////////////////////////////////////////////////
// VariJogDisplay view

class VariJogDisplay : public CView
{
public:
	VariJogDisplay();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(VariJogDisplay)
    CBitmap background;
	bool  Active;
	double ScaleX,ScaleY;
	int width, height;
	int nX,nY;
	int centerx,centery;
	bool Tracking;
	bool TrackingX,TrackingY;
	bool DeleteMe;
	bool Locked;
    int  timeout;
	int  Horiz,Vert;
	int  VelMaxX,VelMaxY;
	int  AccSecX,AccSecY;
	int  Quadrant;
	int MaxX,MaxY,MinX,MinY;
	int KeyHPlus,KeyHMinus,KeyVPlus,KeyVMinus;
	bool KeysSet;
	int  Accs[6]; // holder for acceleration
	int  Vels[6];  // holder for maximum velocities
    CDC srcDC;
// Attributes
public:
     
// Operations
public:
	void SetHV(int hor, int ver);
	void JogOff( int axis );
	void JogOn( int axis, int direction);
	void SetJogChange();
	void CalcSpeeds();
	void SetJogMode();
	void KillWidget();
	void CloseJog();
 
	void Update();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VariJogDisplay)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~VariJogDisplay();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
    LRESULT OnHotKey(WPARAM wp, LPARAM);

	// Generated message map functions
protected:
	//{{AFX_MSG(VariJogDisplay)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKillFocus(CView* pNewWnd);
	afx_msg void OnSetFocus(CView* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
 
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VARIJOGDISPLAY_H__AD87F483_5A1E_4935_B354_750043BA0716__INCLUDED_)
