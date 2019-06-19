// LeftView.h : interface of the CLeftView class
//


#pragma once
#include "ControlRect.h" //to allow all the other classes to get their definitions here
#include "Afxtempl.h"
#include "xmlprofile.h"
#include "engine.h"
#include "trajectoryControl.h"
#include "Addondlg.h"

class CMach4Doc;

class CLeftView : public CView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CMach4Doc* GetDocument();

// Operations
public:
	COLORREF BackColor;
	CBrush BackBrush;

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	virtual void OnDraw(CDC* /*pDC*/);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CMach4Doc* CLeftView::GetDocument()
   { return reinterpret_cast<CMach4Doc*>(m_pDocument); }
#endif

