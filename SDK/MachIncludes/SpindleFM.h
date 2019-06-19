#pragma once

class SpindleFM
{
public:
	SpindleFM(void);
	~SpindleFM(void);
	bool  SpindleOn;
	double P,I,D;
	bool   ClosedLoop;
	bool  FloodOn;
	bool  MistOn;
	bool  LaserMode;
	bool  MotorEnabled;
	bool  PWMEnabled;
	double SpindleMaxVel;
	bool   ImmediateOff;
	int    SpinSettle;
	double Linearity[101];
	bool  SpindleRelayEnabled;
	int   SpindleSignalCW;
	int   SpindleSignalCCW;
	bool  FloodRelayEnabled;
	bool  WaitingForDelay;
	int   FloodSignal;
	int   MistSignal;
    int   PWMMinimum;
    double PWMMax;
	int   PWMFreq;
	int   Direction;
	int   newdirection;
	double SpindleSpeed;
	double ratio;
	double TrueSpindleRPM;
	bool   SpindleAvging;
	bool   WaitingForOff;
	double CSSpeed;
	double CSSmin;
	
    

	int   Update(void);
	void TimedOff(void);
	void SetSpindleSpeed(double RPM);
	bool IsSpindleOn(void);
	void SpindleONCW(void);
	void SpindleONCCW(void);
	void TurnSpindleOff(void);
    void MistSigOn(void);
	void MistSigOff(void);
	void FloodSigOn(void);
	void FloodSigOff(void);
	void TimedOn(void);
	double ConvertSpeed( double rpm );
	void   UpdateSpeedG96( );
	void FillCalcs( double rpm);
	double GetLinearity( double per );
	int MaxSpeeds[25];
	int MinSpeeds[25];
	bool Reversals[25];
	unsigned int last8[8];  
	int CurrentPulley;
	double SpinSecondsCW;
	double SpinSecondsCCW;
	double SpinDownCW;
    double SpinDownCCW;	

private:
	void TurnSpindleOn(void);
public:
	void CalcSpindle(void);
	 
};
