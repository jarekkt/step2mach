#pragma once

#define PAN 1
#define ROT 2
#define ZOOM 3

#include "3dmath.h" 
 
extern bool ShiftState, CtrlState;
 
#define IsSHIFTpressed() ShiftState
#define IsCTRLpressed()  CtrlState

// Backwards compatibility for pre 2.20 grid versions
 

struct Tri
{
	CVector3 v1, v2, v3;
};
struct GLFace {
   unsigned int v1, v2, v3;
};


 
 

// LathePath view

class LathePath : public COpenGLView
{
public:
	LathePath();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(LathePath)

// Attributes
public:

	double mvmatrix[16];
    double projmatrix[16];
    int viewport[4]; //for storage

	GLPoint LathePath:: GetScreenPoint( CPoint point);
	 
     CBallController trackball;
     GLUquadricObj* quad;
	 bool  arrowdone;
	 double MaxZSolid;
	 int NumVertices;
	 int nVectors;
	 double diamsolid;
	 double lengthsolid;
	 double rev;
     CVector3 *Vertices; 
	 Tri     *faces;
	 bool  FileLoaded; 
	 CString FileName;
	 double  XOffset,  ZOffset ;
	 double  ToolOffset;
	 int     toolpath,cone,solid,solidobject;
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
	 int    curline;
	 EmcPose  lasttool;
	 bool     DoneSolid;
	 bool     toolon;
	 double   lastxline,lastyline,lastzline,lastaline;
	 bool     redraw;
	 bool     JustFocused;
	 int      extra;
	 GLPoint  down;

	 CPoint   downat;
	 bool     tracking;
	 double   centerX, centerY, centerZ;
	 double   zoom;
	 double   panx,pany,panz;
	 int      function;
	 double panratiox, panratioy;
	 double rotratiox, rotratioy;

	 int   CoorMode;
	 bool  MillMode;
	 bool   draw;
	 double LatheRad;
	 double diffx, diffy,diffz, diffa;
     double aoffX,aoffY,aoffZ;
	 int    arot;
     GLfloat profilez[2048];
	 GLfloat profilex[2048];

	 GLfloat nprofilez[4096];
	 GLfloat nprofilex[4096];

	 GLPoint  lastmouse;
	 bool      PanUp;
	 

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LathePath)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
	 void SetInitRot();
	void MakeArrow();
	void OnDrawLath( CDC *pDC);
	void GenListLathe();
	void GenSolidList();
	bool DrawBit();
	void DeleteTraj();
	void CalcSolid();
	void GenList();
	void Update();
	void DoSpin();
	void MakeText();
	void Text2D(CString text);
	void DoText();
	virtual ~LathePath();
    double m_rr, m_rb, m_rg;
	int m_Tool;
	int m_Tip;
	int m_Side;
	bool JustText;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(LathePath)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
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
	void ClosePath(void);
protected:
	virtual void PostNcDestroy();
};

