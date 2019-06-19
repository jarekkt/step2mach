#pragma once

#include "MyHandler.h"
#include "TrajectoryControl.h"
 
 

enum Phase { DISABLED ,RUNONIP, DISCOVERY, SETDLP, SETIP, RECONFIG, RECONFIG_WAIT };

class GRexControl
{
public:
	GRexControl(void);
	~GRexControl(void);

	Phase					PHASE;					//	Current phase of G100 code. 

	MyHandler myG100handler;
	//Control functions.
	void DebugOut(const char * string,...);		// For debugging.
	bool dumpErrors(const char * string = NULL, bool set_disabled = FALSE);

	// Inline helpers
	const WTConfig * Config() { return ge->getConfig(inst); }
	

	void  myPurge(word flags);
    void  ShutDown();
	unsigned machSwitchState(unsigned machInSig, 
		                     unsigned bitno = 0, 
		                     unsigned * isDefined = NULL, 
		                     unsigned * native = NULL, 
		                     unsigned * nativeMask = NULL);
	unsigned homeSwitchState(unsigned axesInterested, 
		                     unsigned * defMask = NULL, 
		                     unsigned * native = NULL, 
		                      unsigned * nativeMask = NULL);		// Return bit set for each axis which is currently ON its home switch
	unsigned estopSwitchState(unsigned * defMask = NULL, 
		                      unsigned * native = NULL, 
		                      unsigned * nativeMask = NULL);	
	unsigned probeSwitchState(unsigned * defMask = NULL, 
		                      unsigned * native = NULL, 
		                      unsigned * nativeMask = NULL);	

	void      home(unsigned axis);
	void      deletePartitions();
	void      probe();
	void      Dwell( double time);
	void      JogOn( short axis, short direction, double SpeedNorm);
	void      JogOff(short axis);
	void      Reset();
	void      FillAndBurn(void);  //resets the motor tuning in the rex when tuning is used.
	void      Do10HzUpdate();
	void      Update40Hz();
	void      UserStop();
	void      EStop();
	void      DoCommandGCode();
	void      HandleLinear( GMoves *move, GMoves1 *rest);
	void      HandleCVLinear( GMoves *move, GMoves1 *rest, GMoves *move_next, GMoves1 *rest_next);
	void      HandleArc( GMoves *move, GMoves1 *rest);
	void      NeedSetup();
	void      FeedHold();
	void      Run();
	void      SpinOn( int message);

//Control Variables..
	G100Enumerator *	ge;						// G100 Enumerator
	G100Part *  		p;							// Selected G100 partition.  Mach requires this to be partition 0, with all axes.
    G100Part *          s;                          //A spindle partition, will ne NULL if unused.
	unsigned				inst;						// The instance number of the G100 we picked.  Always 0, since currently we always pick the 1st.
	unsigned				HomingMask;				// Bit set for each axis currently homing or reffing
	WTSDDA 				ddas_when_off[6];		// Homing velocity when off switch
	WTSDDA 				ddas_when_on[6];		// Homing velocity when on switch

	enum {
		PROBE_NONE = 0,
		PROBE_START,
		PROBE_MOVING
	} ProbeState;									// Probing state

	CStdioFile			debugfile;				// For output deebugging messages.
	WTConfig				newConfig;				// Temporary config parameters for config update dialogues.
	CTime					basetime;				// Start time of some timeout interval
	CString				Disability;				// Headline error message

	bool					Monitoring;				// Are we currently monitor for halt conditions..
	unsigned				MonitorHaltBits;		// Halt conditions and levels..
	unsigned				MonitorHaltMask;
	unsigned				MonitorMask;			// Non critical monitoring mask
	bool					reset_monitor;			// Reset limit switch monitoring when possible
	unsigned				DigOutsCommanded;		// Last commanded digital outputs
	int					AnaOutsCommanded[8];	// Last commanded analog outputs
	bool                SkipDwell;              //Skip next dwell, its a spindle dwell and only meant for the Spindle
	bool                 OffHomeMonitorReset;   //used to delay the monitoring untill after Mach3 resets the homing cycle.

	unsigned				InJog;					// Is any axis jogging: bitmask per axis

	double				LastCoord[6];			// Last coordinate estimate, munged to units (mm or inch) - used by monitor panel.
	double				LastVel[6];				// Last velocity (units/s). This is updated with low-pass filtering 
														// based on estimated velocity.
	WTSDDA				JogDDAs[6];				// Last jog velocity

	G100Timer			msg_stamp;				// Timestamp of last debug message

	char					message_buf[4096];	// Message buffer
	unsigned				msg_offs;				// Offset in above message past timestamp

	WTPartition			partInfo;				// Current partitioning state

	// Misc functions
 	
	CString IpToString(DWORD ip) const;
	int notifyHalt(
		unsigned qid, 
		void * qdata, 
		G100Part * gp, 
		unsigned halt_bit,
		unsigned halt_value
		);
	void LimitHomeActivated(int Signal);
	void DoEmerg();
	void ProbeHit();
	void setMonitoring();
	void doDigOuts();
	void doAnaOuts();
	void doDigIns();
	void doAnaIns();
	void doPosFeedback();
	void doJog();
	void doProbe();
	void doMovement();
	void Update();
	void setupMainPartition();
 
};

inline unsigned SetBit(unsigned &data, bool OnOff, unsigned nBit)
{
	if (--nBit < 32) {
		if( OnOff )
			data |= 1u << nBit; 
		else
			data &= ~(1u << nBit);	 
	}
	return data;
}


