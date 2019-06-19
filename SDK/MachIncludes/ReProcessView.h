#pragma once


// ReProcessView view

class ReProcessView : public CWnd
{
	DECLARE_DYNCREATE(ReProcessView)

protected:
	ReProcessView();           // protected constructor used by dynamic creation
	virtual ~ReProcessView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	double m_XScale, m_YScale, m_XSize, m_YSize;
	double m_WidthX, m_WidthY, m_WidthZ;
	double m_ScaleDraw;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


