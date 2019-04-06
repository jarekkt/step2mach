// Encoder.h - new .h split out of Engine.h

#pragma once

// encoder inputs
struct Encoder
{
	bool Active;  // is the encoder turned on?
	int  APin;    //  A Pin designations
	int  BPin;    //  B Pin designations
	int  APort;   //  A Pin Ports
	int  BPort;   //  B Pin Ports
	bool LastStateA;
	bool LastStateB;  // storage for the last known state
	int  Count[2];  //  Index counts for each encoder
	int  Memory[16];
	int  ActiveMemory;
	int  Color;
};
