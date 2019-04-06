//	_Normals.h - replaced class with struct
//

#pragma once

// Normals

struct _Normals
{
	BYTE	_fillCObject[0x04];		// fill to replace private CObject data
	int		m_dwRef;				// CWnd public data
	BYTE	_fillCWnd1[0x14];		// fill to replace private CWnd data
	HWND	m_hWnd;					// only published CWnd data
	BYTE	_fillCWnd2[0x14];		// fill to replace private CWnd data
	HWND	m_hWndOwner;			// CWnd public data
	int		m_nFlags;				// Cwnd public data
	BYTE	_fillCWnd3[0x14];		// fill to replace private CWnd data

	double	Conditions[50];
	double	Check[50];
    bool	Normal[50];

	LPCSTR	Abnormal;
};
