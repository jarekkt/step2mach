// _Traj.h : header file
//
//	modified by j1sys to make _Traj a struct instead of a class
//

#pragma once

#include "TrajStructs.h"

struct _Traj
{
	BYTE		_fillCWnd1[0x04];		// fill to replace private CObject data
	int			m_dwRef;				// CWnd public data
	BYTE		_fillCWnd2[0x14];		// fill to replace private CWnd data
	HWND		m_hWnd;					// only published CWnd data
	BYTE		_fillCWnd3[0x14];		// fill to replace private CWnd data
	HWND		m_hWndOwner;			// CWnd public data
	int			m_nFlags;				// Cwnd public data
	BYTE		_fillCWnd4[0x14];		// fill to replace private CWnd data

	TP_STRUCT	queue;
	TP_STRUCT	freeAxis[6];
	TC_STRUCT	queueTcSpace[210];
	TC_STRUCT	freeAxisTcSpace[6][4];

	double		Scale;

	EmcPose		PausedAt;

	TC_STRUCT	PartialLine;
	TC_STRUCT	ForwardLine;
	TC_STRUCT	ReverseLine;
};
