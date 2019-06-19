#pragma once
#include "afxwin.h"


// MosBusPoll dialog

class MosBusPoll : public CDialog
{
	DECLARE_DYNAMIC(MosBusPoll)

public:
	MosBusPoll(CWnd* pParent = NULL);   // standard constructor
	virtual ~MosBusPoll();

// Dialog Data
	enum { IDD = IDD_MODBUS2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_PollList;
};
