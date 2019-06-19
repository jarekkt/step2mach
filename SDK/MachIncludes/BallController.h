// BallController.h: interface for the CBallController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BALLCONTROLLER_H__196CBD82_3858_11D2_80B1_A7800FACFE7F__INCLUDED_)
#define AFX_BALLCONTROLLER_H__196CBD82_3858_11D2_80B1_A7800FACFE7F__INCLUDED_

#include "3dmath.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Auxiliary Type Definitions
enum AxisSet
{
	NO_AXES,
	CAMERA_AXES,
	BODY_AXES,
	OTHER_AXES
};

class CBallController  
{
public:
	bool bDrawConstraints;
	tmatrix bodyorientation;
	int angleKeyIncrement;
	void DrawConstraints();
	vector* GetUsedAxisSet();
//	vector vcurr; //vettori iniz e finali per il rubber banding della rotaz
//	vector vdown;
	vector BallColor;
	bool bProjectionMethod2;
	bool bDrawBallArea;
	int GLdisplayList;
	unitquaternion currentQuat;
	unitquaternion previousQuat;
	real radius;
	real winWidth;
	real winHeight;
	real xprev;
	real yprev;
	CPoint center;
	bool mouseButtonDown;
	AxisSet whichConstraints;
	int currentAxisIndex;
	vector cameraAxes[3];
	vector bodyAxes[3];
	vector* otherAxes;
	int otherAxesNum;

	void InitDisplayLists();
	void initVars(void);
	void ProjectOnSphere(vector& v) const;
	unitquaternion RotationFromMove(const vector& vfrom,const vector& vto);
	vector ConstrainToAxis(const vector& loose,const vector& axis);
	int NearestConstraintAxis(const vector& loose);
public:
	bool GetDrawConstraints();
	void SetDrawConstraints(bool flag=true);
	void DrawBall();
	int GetAngleKeyIncrement();
	void SetAngleKeyIncrement(int ang);
	void UseConstraints(AxisSet constraints);
	void ToggleMethod();
	void SetAlternateMethod(bool flag=true);
	vector GetColorV();
	COLORREF GetColor();
	void SetColor(COLORREF col);
	void SetColorV(vector colvec);
	void DrawBallLimit();
	CBallController();
	CBallController(const real& rad);
	CBallController(const real& rad,const unitquaternion& initialOrient);
	CBallController(const CBallController& other);
	virtual ~CBallController();
	CBallController& operator=(const CBallController& other);
	void Resize(const real& newRadius);
	void ClientAreaResize(const CRect& newSize);
	void MouseDown(const CPoint& location);
	void MouseUp(const CPoint& location);
	void MouseMove(const CPoint& location);
	void IssueGLrotation();
	void Key(UINT nChar);
};

//---------------------------------------------------------------------------
// inlines

inline CBallController::~CBallController()
{
	if(otherAxes) delete[] otherAxes;
}

inline CBallController::CBallController(const CBallController& other)
{
	*this=other;
}

inline void CBallController::Resize(const real& newRadius)
{
	radius=newRadius;
}

inline void CBallController::ClientAreaResize(const CRect& newSize)
{
	winWidth=real(newSize.Width());
	winHeight=real(newSize.Height());
//	center=CPoint( (newSize.right-newSize.left)/2 , (newSize.bottom-newSize.top)/2);
}

inline CBallController::CBallController()
{
	initVars();
}

inline COLORREF CBallController::GetColor()
{
	return RGB(int(BallColor.x()*255),int(BallColor.y()*255),int(BallColor.z()*255));
}

inline vector CBallController::GetColorV()
{
	return BallColor;
}

inline void CBallController::SetAlternateMethod(bool flag)
{
	bProjectionMethod2=flag;
}

inline void CBallController::ToggleMethod()
{
	if(bProjectionMethod2) bProjectionMethod2=false;
	else bProjectionMethod2=true;
}

inline void CBallController::UseConstraints(AxisSet constraints)
{
	whichConstraints=constraints;
}

inline int CBallController::GetAngleKeyIncrement()
{
	return angleKeyIncrement;
}

inline void CBallController::SetAngleKeyIncrement(int ang)
{
	angleKeyIncrement=abs(ang)%360;
}

inline bool CBallController::GetDrawConstraints()
{
	return bDrawConstraints;
}

inline void CBallController::SetDrawConstraints(bool flag)
{
	bDrawConstraints=flag;
}


#endif // !defined(AFX_BALLCONTROLLER_H__196CBD82_3858_11D2_80B1_A7800FACFE7F__INCLUDED_)
