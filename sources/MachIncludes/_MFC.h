//=====================================================================
//
//	_MFC.h
//
//		these are converted structs to replace previously used
//		MFC classes
//
//		version 1.0 - 3 aug 2008
//
//		created by j1sys to make all data objects a struct to be more
//		portable across compilers. all data objects are either simple
//		objects (int, double, etc.) or structs containing only simple
//		objects.
//
//=====================================================================

#pragma once

struct _CArchive
{
	LPVOID	m_pDocument;
	BOOL	m_bForceFlat;
	BOOL	m_bDirectBuffer;
	BOOL	m_bBlocking;
	INT32	m_nObjectSchema;
	LPCSTR	m_strFileName;
	BYTE	_fillCArchive[0x30];	// fill to replace private CArchive data
};

struct _CArray
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	LPVOID	m_pData;				// pointer to actual array
	INT_PTR	m_nSize;				// current array size (filled)
	INT_PTR	m_nMaxSize;				// current array max size (area)
	INT_PTR	m_nGrowBy;				// grow by size
};

struct _CBrush
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	HGDIOBJ	m_hObject;
};

struct _CFile
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	HANDLE	m_hFile;
	BYTE	_fillCFile[0x08];		// fill to replace private CFile data
};

struct _CFont
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	HFONT	m_hFont;
};

struct _CFrameWnd
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	int		m_dwRef;				// CWnd public data
	BYTE	_fillCWnd1[0x14];		// fill to replace private CWnd data
	HWND	m_hWnd;					// only published CWnd data
	BYTE	_fillCWnd2[0x14];		// fill to replace private CWnd data
	HWND	m_hWndOwner;			// CWnd public data
	int		m_nFlags;				// Cwnd public data
	BYTE	_fillCWnd3[0x14];		// fill to replace private CWnd data
	BYTE	_fillCFrameWnd[0x80];	// CFrameWnd data - need to define members
};

struct _CMemMapFile
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	HANDLE	m_hFile;
	HANDLE	m_hMapping;
	BOOL	m_bReadOnly;
	BOOL	m_bAppendNull;
	LPVOID	m_lpData;
	LPCSTR	m_sMappingName;
	BOOL	m_bOpen;
	HANDLE	m_hMutex;
	DWORD	m_dwLength;
};

struct _CNode						// used for _Coblist
{
	_CNode	*pNext;
	_CNode	*pPrev;
	void	*data;
};

struct _CObList
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	_CNode	*m_pNodeHead;
	_CNode	*m_pNodeTail;
	INT_PTR	m_nCount;
	_CNode	*m_pNodeFree;
	void	*m_pBlocks;				// orig CPlex
	INT_PTR	m_nBlockSize;
};

struct _CRect
{
	LONG	left;
	LONG	top;
	LONG	right;
	LONG	bottom;
};

struct _CStdioFile
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	HANDLE	m_hFile;
	BYTE	_fillCFile[0x08];		// fill to replace private CFile data
	FILE*	m_pStream;
};

struct _CToolTipCtrl
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	int		m_dwRef;				// CWnd public data
	BYTE	_fillCWnd1[0x14];		// fill to replace private CWnd data
	HWND	m_hWnd;					// only published CWnd data
	BYTE	_fillCWnd2[0x14];		// fill to replace private CWnd data
	HWND	m_hWndOwner;			// CWnd public data
	int		m_nFlags;				// Cwnd public data
	BYTE	_fillCWnd3[0x14];		// fill to replace private CWnd data
	BYTE	_fillCToolTipCtrl[0x1c];// fill to replace private CToolTipCtrl data
};

struct _CWnd
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	int		m_dwRef;				// CWnd public data
	BYTE	_fillCWnd1[0x14];		// fill to replace private CWnd data
	HWND	m_hWnd;					// only published CWnd data
	BYTE	_fillCWnd2[0x14];		// fill to replace private CWnd data
	HWND	m_hWndOwner;			// CWnd public data
	int		m_nFlags;				// Cwnd public data
	BYTE	_fillCWnd3[0x14];		// fill to replace private CWnd data
};
