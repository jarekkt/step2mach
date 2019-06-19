/*******************************************************************************
 JMatrixCtrl.h

 *******************************************************************************/

#pragma once

#include <afxtempl.h>

class JMatrixCtrl : public CWnd
{
public:

	JMatrixCtrl();

	virtual	~JMatrixCtrl();

	void	AddTextLine(LPCTSTR lpszLine);

	void	SetIntervals(const int intro, const int restart);
	void	SetCursor(const BOOL show, const BOOL solid);
	void	SetMaxPhaseCount(const int maxCount);
	void	AllowEuropeanChars(const BOOL allow);

	//{{AFX_VIRTUAL(JMatrixCtrl)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID=NULL);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(JMatrixCtrl)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	struct MatrixColumn
	{
		BOOL	bActive;				// column is active
		int		nCounter;				// current, glowing row index
		int		nCounterMax;			// row index where animation stops
		char	prev;					// previous character in column
	};

	struct SpinChar
	{
		BOOL	bActive;				// character is active
		int		nCounter;				// number of iterations left
		CPoint	pt;						// location
		char	c;						// current character
	};

	typedef CArray<CPoint, CPoint&>	CPointList;
	typedef CArray<int, int>		CPhaseList;

private:

	int				m_nTextHeight;
	int				m_nTextWidth;
	int				m_nRows;
	int				m_nCols;

	char			m_MaxChar;			// out of 255
	int				m_IntroInterval;	// seconds
	int				m_RestartInterval;	// seconds
	int				m_nMaxPhaseCount;	// cycles

	BOOL			m_bShowCursor;		// FALSE => phase in entire line immediately
	CPoint			m_CursorPt;
	char			m_CursorChar;		// 1 => solid block

	CStringArray	m_LineList;			// all lines to display
	int				m_nPageStartLine;	// first line on current page
	int				m_nPageEndLine;		// last line on current page
	CPointList		m_LineStartList;	// character grid coordinates
	int				m_nActiveLine;		// index of line being phased in
	CString			m_ActiveLine;		// partially phased in line
	CPhaseList		m_PhaseList;		// phase count for each character in active line
	int				m_nPauseInterval;	// seconds; how long to wait before going to next page

	CDC				m_DC;
	CFont*			m_pFontOld;
	CBitmap*		m_pBitmapOld;
	CBitmap			m_Bitmap;

	MatrixColumn*	m_pMatrixColumns;	// all the columns that are displayed
	int				m_nActiveColumns;	// number of active columns

	int				m_nTotalSpins;
	SpinChar*		m_pSpinChars;
	int				m_nActiveSpins;

	CDC				m_BackDC;
	CFont*			m_pBackFontOld;
	CBitmap*		m_pBackBitmapOld;
	CBitmap			m_BackBitmap;

	CFont			m_Font;

private:

	void	Draw();

	void	InitText();
	void	UpdateText();
	void	DrawText();

	void	InitCursor();
	void	UpdateCursor();
	BOOL	CursorFinished();
	void	DrawCursor();

	void	UpdateBackground();
	void	InitBackgroundCharacters(const int nColumn);
	void	DrawActiveBackgroundChar(const int col);
	void	DrawFadedBackgroundChar(const int col);

	void	UpdateSpin();
	void	DrawSpin();

	void	DrawActiveString(CDC& dc, const int row, const int col,
							 const char* str, const int len, const COLORREF green);
};


/*******************************************************************************
 AddTextLine

 *******************************************************************************/

inline void
JMatrixCtrl::AddTextLine
	(
	LPCTSTR lpszLine
	)
{
	m_LineList.Add(lpszLine);
	m_nPageEndLine = (int)m_LineList.GetSize();	// force InitText() to start at beginning
}

/*******************************************************************************
 SetIntervals

	The larger the max phase count, the longer it may take for the text
	to settle down.

 *******************************************************************************/

inline void
JMatrixCtrl::SetIntervals
	(
	const int intro,
	const int restart
	)
{
	m_IntroInterval   = intro;
	m_RestartInterval = restart;
}

/*******************************************************************************
 SetMaxPhaseCount

	The larger the max phase count, the longer it may take for the text
	to settle down.

 *******************************************************************************/

inline void
JMatrixCtrl::SetMaxPhaseCount
	(
	const int maxCount
	)
{
	m_nMaxPhaseCount = maxCount;
}

/*******************************************************************************
 AllowEuropeanChars

	The disadvantage of allowing European characters is that it takes longer
	for the text to phase in.

 *******************************************************************************/

inline void
JMatrixCtrl::AllowEuropeanChars
	(
	const BOOL allow
	)
{
	m_MaxChar = (allow ? 255 : 127);
}

/*******************************************************************************
 CursorFinished (private)

 *******************************************************************************/

inline BOOL
JMatrixCtrl::CursorFinished()
{
	return (m_CursorPt.x >= m_nCols);
}
