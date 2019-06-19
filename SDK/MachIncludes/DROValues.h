#pragma once


// DROValues

class DROValues : public CWnd
{
	DECLARE_DYNAMIC(DROValues)

public:
	DROValues();
	virtual ~DROValues();
	double   GetValue( int code );
	void   SetValue( double Value, int code );

protected:
	DECLARE_MESSAGE_MAP()
};


