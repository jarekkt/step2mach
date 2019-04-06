// _MPGControl.h - replaced class with struct
//

#pragma once

#include "Encoder.h"

struct _MPGControl
{
    Encoder*	Encoders[7];
    double		StepsPerUnit[7];
	double		Count[7];
    double		LastCount[7];
	double		Velocity[7];
	double		MaxVelocity[7];
	double		Positions[7];
 	bool		TwoMPGs;
	bool		CalOn;
	double		Per,Per2,Per3;
	bool		IsJogging;
};
