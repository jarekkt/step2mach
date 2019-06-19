#pragma once
// LedButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLedButton window
#include "Mach3Image.h"

 

class CLedButton : public CWnd
{
  // Construction
  public:
    Mach3Image picture;
    Mach3Image picture2;
	 UINT width,height;
    //ReadOnly does not work: it is ALWAYS read-only.
	CLedButton( );
    virtual ~CLedButton() { }
    void Init( );

    //Call "SetImage" once before displaying the control.
 

    // Overrides
	  // ClassWizard generated virtual function overrides
	  //{{AFX_VIRTUAL(CLedButton)
	public:
	virtual void PostNcDestroy();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	
	//}}AFX_VIRTUAL

	  // Generated message map functions
	public:
		bool Loaded;
		void  DrawIt(bool state);
		void Update();
		CControlRect *Control;
	    int  function;
	    int  OEMCode;
	    bool flash;
	    short go;
		CString Path;
		bool  cond;
		bool  ResLoaded;
		bool  IsOn;
		void  SetCode();
	   
  public:
	 
        CSize m_rcImage;
	  //{{AFX_MSG(CLedButton)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	//afx_msg BOOL OnClicked();

	  DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void SetImage(int type, int size);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void SetPath(CString path);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

