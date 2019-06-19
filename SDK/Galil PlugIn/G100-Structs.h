#include "G200x.h"



enum Phase { DISABLED ,RUNONIP , DISCOVERY };
enum Stages {DISCNONE , STAGE1 , STAGE2, STAGE3, STAGE4, STAGE5, STAGE6, STAGE7, STAGE8 };
enum WaitState { NONE, MONITORSET, MONITORCHALLENGE };
enum Sequencing { NOSEQ, PROBESTART, PROBEACTIVE, PROBEHIT, HOMESTART, HOMEWAIT, HOMEONSWITCH ,HOMEMOVEOFF, HOMEISOFF, HOMEDONE };
enum MessageSeq { NOMSEQ, PURGEAFTERHALT };


struct Discovery
{

  CTime                      started;
  CTime                        ended;
  Stages                       Stage;
  bool                         Done;

};

struct GRex
{

	WTConfig         Config;               //main configuration block for the GRex
	Phase            PHASE;                //current phase of G100 code. 
	Sequencing       SEQUENCE;             //Home and Probhe sequences
	MessageSeq       MESSAGESEQ;
    Discovery        Discovered;           //network and idscovery process information
	CString          Disability;           //Reason G100 is disabled. (If it is..)
	AddressAssign    G100Address;          // Address Asignment Block
	bool             StartUp;              //initial message traffic begins. Set defaults..
	CTime            LastMessageTime;      // Time last message was recieved, for Link checking in the update loop.

	// Traffic variables. 

	short            LastAck;              //The last message Acked on this device
	short            LastMess;             //The last Message Sent.
	short            LastStored;           //the last message stored. 
	short            Window;               //Last Window recieved. The Window tells us how many messages the 
                                           //G100's FTDI chip can accept in its holding buffer. 
 	//Condition Varibale
	int             InWord;                //the last 32bit input word.
	int             OutputWord;            //The last OutputWord sent
	int             CurrentISR;            //Current G100 timer count. ISR counter.
	int             CurrentMISR;           // ISR's remaining in current queues move.
	WTMsAbs         LastAbs;               //Last absolute structure sent
    int             CurDDA[6];             //Current DDA's from last status
	double          LastCoord[6];          //last ABS coordinate from status.
	int             CurrentQueueSeq;       //Current Queue Seq. number from status input
	int             NextQueue;             //the next movements queue sequence.
	int             EndQueueSeq;           // As of last status, the last move message in the queue
	int             QueueFlags;            // and the last Queue Flags in the status
	int             CurrentHaltBits;       //Current monitoring bits reported form status
	int             CurrentHaltMask;       // Current halt condition mask from the monitoring facility.
	int             CurrentMonMask;        //Current monitoring mask reported from status
	bool            IsStill;               // Set by status if the G100 is state.sflags & QS_STILL.
    bool            IsDrained;             // set by last state is state.sflags & QS_MAVGZ
	bool            InJog;                 //Is any axis Joggin
	int             CurrentMavg;           //Current Mavg in use. 
	int             CalcMavg;              //Expected Mavg
	bool            Dwelling;              //bool that tells the system were waiting for a IsStill to clear a dwell
    bool            HasMoved;              //tracks that a move has started for probeing and homing sequences.  
	bool            NeedDigOutputs;        //Trigger to send new outputs.
	bool            NeedAnaOutputs;        //Trigger to make Analogues go out..
	bool            Homing;                // We're in a homing sequence..
    int             HomingMask;            //needed for homing the appropriate axis
	int             HomeAxis;              //current homing axis;

	//Monitoring Vars.
    int             LastChallenge;         //the last responded to challenge.
	bool            Monitoring;            // Are we currently monitor for halt conditions..
	int             MonitorHaltBits;       //halt conditions and levels..
	int             MonitorHaltMask;
	int             MonitorMask;           //Non critical monitoring mask
	int             CurrentChallenge;      // Currently sent Challenge
	bool            SystemHalted;          //System is currently halted..
	CTime           WaitSet;


    //G100 Sync Events

	WaitState                WaitForState;
	unsigned int             WaitForValue;

};

struct G100Message              //this is a G100 message structure
{
  MessageHdr  Header;
  char  Message[512];
  short size;
};
