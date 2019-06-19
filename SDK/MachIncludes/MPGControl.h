#pragma once

class MPGControl
{
public:
	MPGControl(void);
	~MPGControl(void);
    Encoder* Encoders[7];
    double StepsPerUnit[7];
	double Count[7];
    double LastCount[7];
	double Velocity[7];
	double MaxVelocity[7];
	double Positions[7];
    void Update(void);
	bool  TwoMPGs;
	bool  CalOn;
	void Clear(void);
	void SetPosition(short Encoder, double Position);
	double Per,Per2,Per3;
	bool   IsJogging;
	int VelocityStepMode(void);
	int SingleStepCalMode(void);
	int VelocityMode(void);
};
