// _SpindleFM - replaced class with struct
//

#pragma once

struct	_SpindleFM
{
	bool	SpindleOn;
	double	P,I,D;
	bool	ClosedLoop;
	bool	FloodOn;
	bool	MistOn;
	bool	LaserMode;
	bool	MotorEnabled;
	bool	PWMEnabled;
	double	SpindleMaxVel;
	bool	ImmediateOff;
	int		SpinSettle;
	double	Linearity[101];
	bool	SpindleRelayEnabled;
	int		SpindleSignalCW;
	int		SpindleSignalCCW;
	bool	FloodRelayEnabled;
	bool	WaitingForDelay;
	int		FloodSignal;
	int		MistSignal;
    int		PWMMinimum;
    double	PWMMax;
	int		PWMFreq;
	int		Direction;
	int		newdirection;
	double	SpindleSpeed;
	double	ratio;
	double	TrueSpindleRPM;
	bool	SpindleAvging;
	bool	WaitingForOff;
	double	CSSpeed;
	double	CSSmin;

	int		MaxSpeeds[25];
	int		MinSpeeds[25];
	bool	Reversals[25];
	unsigned int	last8[8];  
	int		CurrentPulley;
	double	SpinSecondsCW;
	double	SpinSecondsCCW;
	double	SpinDownCW;
    double	SpinDownCCW;	
};
