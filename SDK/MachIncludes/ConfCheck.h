#pragma once


// CConfCheck

class CConfCheck : public CWnd
{
	DECLARE_DYNAMIC(CConfCheck)

public:
	CConfCheck();
	virtual ~CConfCheck();
	void     CheckIt();

protected:
	DECLARE_MESSAGE_MAP()
};


