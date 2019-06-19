#if !defined(AFX_TOOLPATH_H__95C8375B_FFEF_4105_A759_B44A74C24410__INCLUDED_)
#define AFX_TOOLPATH_H__95C8375B_FFEF_4105_A759_B44A74C24410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolPath.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ToolPath view
 
#define PAN 1
#define ROT 2
#define ZOOM 3

extern bool ShiftState, CtrlState;

#define IsSHIFTpressed() ShiftState

class ToolPath : public COpenGLView
{
public:
	ToolPath();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ToolPath)

// Attributes
public:
	 
     CBallController trackball;
     GLUquadricObj* quad;
	 bool  arrowdone;
	 bool  FileLoaded; 
	 CString FileName;
	 double  XOffset, YOffset, ZOffset, AOffset, BOffset, COffset;
	 double  ToolOffset;
	 int     toolpath,cone;
	 int     arrow;
	 CPoint  MouseDownPoint;
	 double minx,miny,minz,mina,minb,minc;
	 double maxx,maxy,maxz,maxa,maxb,maxc;
	 double widthx,widthy,widthz,widtha,widthb,widthc;
	 double maxscreen;
	 double hcenter,vcenter;
	 double sizex,sizey;
	 double ratiox, ratioy;
	 bool   PathLoaded;
	 bool   FixOK;
	 int    curline;
	 EmcPose  lasttool;
	 bool     toolon;
	 double   lastxline,lastyline,lastzline,lastaline;
	 bool     redraw;
	 bool     JustFocused;
	 int      extra;

	 CPoint   downat;
	 bool     tracking;
	 double   centerX, centerY, centerZ;
	 double   zoom;
	 double   panx,pany;
	 int      function;
	 double panratiox, panratioy;
	 double rotratiox, rotratioy;

	 int   CoorMode;
	 bool   draw;
	 double LatheRad;
	 double aoffX,aoffY,aoffZ;
	 int    arot;
	 bool   JustText;
	 double m_rr, m_rb, m_rg;

	 //text dispalys
	 int m_Tool;
	 

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ToolPath)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
	void HiLine( int Line );
	EmcPose DoFormulaLine( EmcPose end );
    void SetInitRot();
	void MakeText();
	void Text2D(CString text);
	void MakeZBar();
	void MakeArrow();
	bool DrawBit();
	void DeleteTraj();
	void GenList();
	void Update();
	virtual ~ToolPath();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ToolPath)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void LatheDefs(void);
	void MillDefs(void);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	 
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	void ClosePath(void);
protected:
	virtual void PostNcDestroy();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLPATH_H__95C8375B_FFEF_4105_A759_B44A74C24410__INCLUDED_)
