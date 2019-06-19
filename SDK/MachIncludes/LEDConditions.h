#pragma once


// LEDConditions

class LEDConditions : public CWnd
{
	DECLARE_DYNAMIC(LEDConditions)

public:
	LEDConditions();
	virtual ~LEDConditions();

	bool GetLed( int led );
	bool LEDConditions::IsMoving();
	bool LEDConditions::GetSpindleCond();
	bool LEDConditions::GetMistCond();
	bool LEDConditions::GetFloodCond();


protected:
	DECLARE_MESSAGE_MAP()
};


