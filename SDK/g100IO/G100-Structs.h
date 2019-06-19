#include "g100.h"




/*


// This is plug-in specific information.
struct GRex
{
	G100Enumerator *	ge;						// G100 Enumerator
	G100Part *  		p;							// Selected G100 partition.  Mach requires this to be partition 0, with all axes.
	unsigned				inst;						// The instance number of the G100 we picked.  Always 0, since currently we always pick the 1st.
	unsigned				HomingMask;				// Bit set for each axis currently homing or reffing
	WTSDDA 				ddas_when_off[6];		// Homing velocity when off switch
	WTSDDA 				ddas_when_on[6];		// Homing velocity when on switch

	enum {
		PROBE_NONE = 0,
		PROBE_START,
		PROBE_MOVING
	} ProbeState;									// Probing state
	
	Phase					PHASE;					//	Current phase of G100 code. 

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

	unsigned				InJog;					// Is any axis jogging: bitmask per axis

	double				LastCoord[6];			// Last coordinate estimate, munged to units (mm or inch) - used by monitor panel.
	int					LastVel[6];				// Last velocity (RRV).  This is updated with low-pass filtering based on estimated velocity.
	WTSDDA				JogDDAs[6];				// Last jog velocity

	G100Timer			msg_stamp;				// Timestamp of last debug message

	char					message_buf[4096];	// Message buffer
	unsigned				msg_offs;				// Offset in above message past timestamp
	
	WTPartition			partInfo;				// Current partitioning state
	
	// Misc functions
	GRex();
	~GRex();
	void DebugOut(const char * string,...);		// For debugging.
	bool dumpErrors(const char * string = NULL, bool set_disabled = FALSE);
	
	// Inline helpers
	const WTConfig * Config() { return ge->getConfig(inst); }
	slong RateToPos(int axis, slong pos) const { return pos >> (ge->getConfig(inst)->axis[axis].divider + 3); }
	slong RateToPos(int axis, WTSDDA pos) const { return (slong)(pos >> (ge->getConfig(inst)->axis[axis].divider + 35)); }
	
	
	// Functional helpers
	double ActualPos(int x, slong pos) const;		// Returns the position in a mm's or inches, given internal step count
	double ActualPos(int x, WTSDDA pos) const;	// Returns the position in a mm's or inches, given DDA
	void Purge(word flags);
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
	void home(unsigned ax);
	void probe();
	

};



// Derive a G100 common library handler class


// Global state
extern GRex G100;


// Some inline helpers

/// Set or reset a bit, with bits numbered starting at 1 for LSB

*/
