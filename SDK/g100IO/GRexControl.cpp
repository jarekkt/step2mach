
//This class will be used to separate the G100 from the rest of the plugin..

#include "stdafx.h"		// For use of precompiled headers
#include "resource.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "XMLProfile.h"
#include "MachDevice.h"
#include "G100-Structs.h"		// Includes protocol messages and common G100 library
#include "G100Config.h"
#include "G100General.h"
#include "GRexControl.h"
#include "math.h"

extern TrajectoryControl *MainPlanner;	// used for most planner functions and program control 
extern CMach4View *MachView;			// used for most framework and configuration calls. 
extern TrajBuffer *Engine;				// Ring0 memory for printer port control and other device syncronisation
extern setup *_setup;					// Trajectory planners setup block. Always in effect

extern MyHandler *myG100handler;
extern int RangeStart;
extern CString DefDir;
extern CString Profile;
extern int m_AnaSel;
extern bool m_SpinAnaOff;
extern double m_CVRadius;
extern double m_MaxDev;
extern int MPGs[3];

extern int GLookAhead;
extern double ASC;



extern unsigned int  IP;

#pragma warning(disable:4554)	// We know what we're doing with operators



GRexControl::GRexControl(void)
{
	// Startup of the G100 controller class.
	 ge = NULL;
	 p = NULL;
	 s = NULL;
	 OffHomeMonitorReset = false;
	 HomingMask = 0;
	 memset(LastVel, 0, sizeof(LastVel));
	 memset(LastCoord, 0, sizeof(LastCoord));
	for (int i = 0; i < 6; ++i) {
		 JogDDAs[i] = 0;
		 ddas_when_off[i] = 0;
		 ddas_when_on[i] = 0;
	}
	 PHASE = DISCOVERY;
	 ProbeState = PROBE_NONE;
	 InJog = false;
	 Monitoring = false;
	 MonitorHaltBits = 0;
	 MonitorHaltMask = 0;
	 MonitorMask = 0xFFFFFFFF;
	if (! ge) {
		 ge = new G100Enumerator(1500);
	}
	//open debug file for the session
	
	

}

GRexControl::~GRexControl(void)
{
	 

}

void GRexControl::deletePartitions()
{
	if ( s) {
		DebugOut("Deleting spindle partition...\n");
		delete  s;
		s = NULL;
		DebugOut("...done\n");
	}
	 
	if ( p) {
		 DebugOut("Deleting master partition...\n");
		delete  p;
		 p = NULL;
		 DebugOut("...done\n");
	 }
}

void GRexControl::DebugOut(const char * string, ...)
{
	 
	//}
}


void  GRexControl::ShutDown()
{
   //any shutdown specific matters..
   //Kill any partitions
   deletePartitions();
   //kill any enumerators..
   if ( ge) {
	    DebugOut("Deleting enumerator...\n");
	   delete  ge;
	    ge = NULL;
	    DebugOut("...done\n");
   }
}

//actually, called for any spin up, spind down, or set speed conditions..
//so this routine shoudl update the s partition to do as it needs to keep the 
// 6th axis runnign at the right rate.
void  GRexControl::SpinOn(int mess)
{
   
 
}


unsigned GRexControl::machSwitchState(unsigned machInSig, unsigned bitno, unsigned * isDefined, unsigned * native, unsigned * nativeMask)
{
	unsigned s, machbit;

	if (Engine->InSigs[machInSig].InPort == 3 
		&& Engine->InSigs[machInSig].Active 
		&& (machbit = Engine->InSigs[machInSig].InPin-1) < 32) { 

			if (isDefined)
				*isDefined |= 1u<<bitno;
			if (nativeMask)
				*nativeMask |= 1u << machbit;
			s =  p->getSingleDigIn(machbit);
			if (Engine->InSigs[machInSig].Negated)
				s = !s;
			if (native)
				*native |= s << machbit;
			return s << bitno;
		}
	else {
		return 0;
	}
}


unsigned GRexControl::homeSwitchState(unsigned axesInterested, unsigned * defMask, unsigned * native, unsigned * nativeMask)
{
	return
		(axesInterested & 0x01 ? machSwitchState(XHOME, 0, defMask, native, nativeMask) : 0)
		| (axesInterested & 0x02 ? machSwitchState(YHOME, 1, defMask, native, nativeMask) : 0)
		| (axesInterested & 0x04 ? machSwitchState(ZHOME, 2, defMask, native, nativeMask) : 0)
		| (axesInterested & 0x08 ? machSwitchState(AHOME, 3, defMask, native, nativeMask) : 0)
		| (axesInterested & 0x10 ? machSwitchState(BHOME, 4, defMask, native, nativeMask) : 0)
		| (axesInterested & 0x20 ? machSwitchState(CHOME, 5, defMask, native, nativeMask) : 0);

}

unsigned GRexControl::estopSwitchState(unsigned * defMask, unsigned * native, unsigned * nativeMask)
{
	return
		machSwitchState(EMERGENCY, 0, defMask, native, nativeMask);

}

unsigned GRexControl::probeSwitchState(unsigned * defMask, unsigned * native, unsigned * nativeMask)
{
	return
		machSwitchState(DIGITIZE, 0, defMask, native, nativeMask);

}

void GRexControl::home(unsigned axis)
{
}


void GRexControl::probe()
{
	
}


void GRexControl::setupMainPartition()
{
	// This is called when the initial partition (0) is created.  Set up "permanent" things like
	// slaved axes,
	DebugOut("setupMainPartition: <entry>\n");
	// Temporarily set all resources in partition 0 (master).
	// All your outputs are belong to us!
	memset(& partInfo, 0, sizeof( partInfo));
   s = NULL;
   //If the C axis isn't enabled, set the 6th axis to its own partition.

	//set InJog to zero to stop any  rejogs from going out during startup
	InJog = 0;

	// Now we need to tell Mach3 how many pulses per second each axis can do. 
	// we do this here as the config is now available. 
	 	// Set up partition scaling parameters
	for (int x = 0; x < 8; ++x) {
		p->setAnaOutScale(x, 0.0, 32767.0);		// Modbus regs are signed short, so this is full-scale.
		p->setAnaInScale(x, 0.0, 32767.0);
	}
	// Set monitoring and halting parameters
	p->setRate(1.0);
	 

	// Set native axis slaving - assumes here that only A,B,C may be slaved to X,Y,Z.
	// Illegal bindings will be ignored.
	// It is OK for more than 1 of A,B,C to be bound to a single X,Y,Z axis.
	 
}


void GRexControl::Update()
{
	static int mess = -1;
	static bool busy = false;
	if( busy ) return;
	busy = true;
	static CTime startime = CTime::GetCurrentTime();

	G100Config * fig;
	CTimeSpan intvl;
	CTimeSpan dif;

	//FIXME: for debugging, slow this down to 2 Hz
#ifdef SUPERDEBUG
	//if (++upd_count % 5 != 0)
	//	return;

	 DebugOut("--- Update %d, phase=%d ---\n", upd_count,  PHASE);
#endif

	// Check here for disconnection for   If more than 1/2 second has passed and no ethernet message, trigger an EStop
	// Inputs to InActive..

	//................
	//CTime Now = CTime::GetCurrentTime();
	//CTimeSpan Since = Now -  LastMessageTime; //Time since last RX meesage in IPRun mode. 

	//	Main message phase loop. Routes update loops to the code that manages that particular phase of operation
	// Only Discovery and RunIP are necessary at the moment. 
	switch ( PHASE )
	{
	case DISABLED:
		if( mess != 1)
			SetMachError(" G100 Disabled.");
		mess = 1;
		busy = false;

		return; 			// Unit is disabled. No code operation possible until re-enabled. 

	case RUNONIP:
		// Reconcile G100 state with what is desired.
		//FIXME: this seems too passive; we need to continuously interrogate the Mach3 state.  It would
		// be better if there was a separate plugin function which Mach3 could call when, e.g., an output needed
		// to change.
		
		
	    Do10HzUpdate();
		break;

	case DISCOVERY:

		if( mess != 3)
			SetMachError("Please wait..G100 init...");
		mess = 3;
		if ( ge->discovery_tick()) {
			// Operation completed.
			 DebugOut("Discovery completed\n");
			if( mess != 4)
				SetMachError("G100 Found...");
			mess = 4;
			if ( ge->getNumInstances()) {
				// Good, got at least 1 instance.  Pick the 1st one (for now).
				//FIXME: could be nice and show a chooser dialogue.
				// We use  inst from here on, so as not to hard-code anything.
				 inst = 0;
				if ( ge->isRunningDLM( inst)) {
					 DebugOut("Running DLM\n");
					 PHASE = SETDLP;
					//FIXME: prompt the user to avoid aggravation when his DLM config session gets trashed :-(
					if (! ge->runDLP( inst)) {
						 dumpErrors("Could not start DLP", TRUE);
						fig = new G100Config();
						if( fig->DoModal() == IDCANCEL ) PHASE = DISABLED;
					}
					break;	// continue start DLP next time
				}
				 DebugOut("Discovery successful!\n");

_get_partitions:
				// Copy the current config for dialogues etc.
				memcpy(& newConfig,  Config(), sizeof( newConfig));

				 DebugOut(
					"Config:\n"
					"  Firmware datecode: %6.6s\n"
					"     max_partitions: %u\n"
					"      controller ID: %16.16s\n"
					,  newConfig.datecode
					,  newConfig.max_partitions
					,  newConfig.id
					);

				//get rid of any spindle partition.
				if ( s) {
					delete  s;
					s = NULL;
				}

				// Get rid of any old (defunct) partition
				if ( p) {
					delete  p;
					p = NULL;
				}

				// Is running DLP, so get master partition.
				p =  ge->getPartition( inst, myG100handler, 0);
				if (! p) {
					 dumpErrors("Could not obtain master partition", TRUE);
					SetMachError("Could not get Master Partition.");
					fig = new G100Config();
					if( fig->DoModal() == IDCANCEL ) PHASE = DISABLED;
					break;
				}
				// Normal operations can now be done, however it may turn out that the partition
				// is already in use by another program or host.  In this case, we don't find out
				// until the initial SYN message times out.  This is picked up in the RUNONIP state.
		
				DebugOut("Obtained master partition, %d axes\n",  p->getDimension());

				setupMainPartition();

				PHASE = RUNONIP;   
				SetMachError("G100 Initialised. Ready to run.");
			}
			else {
				// No instances, bummer.
				SetMachError("No G100's found in system.");
				 dumpErrors("No G100 instances found", TRUE);
				fig = new G100Config();
				if( fig->DoModal() == IDCANCEL ) PHASE = DISABLED;
				delete fig;
			}

		}
		break; 

	case SETDLP:
		 dumpErrors("Failed to set DLP mode");
		if ( ge->discovery_tick()) {
			// Run DLP Operation completed.  Go back to discovery mode.
			//FIXME we could get into an endless loop (discover, DLM, discover, DLM...), so at some point we should give up
			 PHASE = DISCOVERY;
			SetMachError("G100 rebooted. Re-initialising.");

		}
		break;

	case SETIP:
		 dumpErrors("Failed to set new IP parameters");
		if ( ge->discovery_tick()) {
			// Set IP operation completed.  Go back to discovery mode.
			 DebugOut("Set IP completed\n");
			 PHASE = DISCOVERY;
			SetMachError("New IP Set, re-init in progress...");
		}
		break;

	case RECONFIG:
		// Reconfig upsets all partitions, so they need to be recreated.
		 DebugOut("Start reconfig (6 sec wait)...\n");
		deletePartitions();
		 PHASE = RECONFIG_WAIT;
		SetMachError("Waiting 6 seconds for reboot.");
		 basetime = CTime::GetCurrentTime();
		break;

	case RECONFIG_WAIT:
		intvl = CTime::GetCurrentTime() -  basetime;
		if (intvl.GetSeconds() > 6) {
			// Done waiting, reconnect partitions.  No need for rediscovery, since IP does not change.
			 DebugOut("Reconfig successful!\n");
			SetMachError("Reboot Complete, rediscovery in progress.");
			 PHASE = DISCOVERY;	// set this in case of error
			goto _get_partitions;			
		}
		break;
	}
	busy = false;

} // myUpdate


void   GRexControl::Do10HzUpdate()
{
 
	
}

void   GRexControl::Update40Hz()
{
 
  //this is for a 40hz update , any high speed things can be done here..
  // DebugOut("doJog...\n");
  if( PHASE != RUNONIP )return;
	  
	
  static double FRO = 100;
  static bool mess = false;

  //monitoring..

  ge->tick();
  if ( dumpErrors("Communication/programming error", TRUE)) {
	  SetMachError("Com Error, Communications lost.");
	  PHASE = DISABLED;
	  G100Config *fig = new G100Config();
	  if( fig->DoModal() == IDCANCEL ) PHASE = DISABLED;
	  delete fig;
	  return;
  }

  MainPlanner->ModInputs[117] = p->getClock();
  //reset the dwell if one is active.
  doDigOuts();
  doAnaOuts();



  if( !mess )
	  SetMachError(" G100 Connected to Port3.");
  mess = true;
  // Process any input events
  doDigIns();
  doAnaIns();


   

 
}

 

void GRexControl::Reset()
{
 
}

void GRexControl::FeedHold()
{
	 
}

void GRexControl::Run()
{
	 
}



void   GRexControl::Dwell( double time)
{
	 
}

void   GRexControl::JogOn( short axis, short direction, double SpeedNorm)
{
	 
}

void   GRexControl::JogOff(short axis)
{
	 

}


bool GRexControl::dumpErrors(const char * string, bool set_disabled)
{
	return false;
}



void GRexControl::myPurge(word flags)
{
	DebugOut("Purge: <entry flags=0x%X>\n", flags);
	if (!p || p->isPurging())
		return;
	Engine->TrajHead = Engine->TrajIndex;	// Kill the Mach queue just in case of asyn error..
	//MainPlanner->PurgeMovements = true;
	 InJog = false;
	for (int x = 0; x<6; x++ ) {
		Engine->Axis[x].Jogging = false;
	}
	MainPlanner->Jogging = false;
	if (p) {
		DebugOut("Purge: purging\n");
		p->purge(flags);
	}
}


CString GRexControl::IpToString(DWORD ip) const
{
	char s[50];   
	itoa ((int)(ip >> 24), s, 10);
	strcat (s, ".");
	itoa ((int)(ip >> 16) & 0xFF, strchr(s,'\0'), 10);
	strcat (s, ".");
	itoa ((int)(ip >> 8) & 0xFF, strchr(s,'\0'), 10);
	strcat (s, ".");
	itoa ((int)(ip & 0xFF), strchr(s,'\0'), 10);
	CString out = s;
	return out;
}


void GRexControl::doProbe()
{
	 
}

void GRexControl::doDigOuts()
{
	// Interrogate Mach desired state, and update G100 if necessary
	bool On;
	unsigned outs = 0;	// Desired state
	unsigned mask = 0;	// Which bits are requested by Mach, AND controllable by master partition
	unsigned curr;			// Current state at G100 end

	// Toggle "charge pump" if so requested
	if (Engine->OutSigs[CHARGE].active) 
		Engine->OutSigs[CHARGE].Activated = !Engine->OutSigs[CHARGE].Activated;

	// Set output according to current movement
	if (Engine->OutSigs[CURRENTHILOW].active) 
		Engine->OutSigs[CURRENTHILOW].Activated = (bool)(p->isStill()==1);

	// Find out what Mach wants
	for( int x = 0; x< nSigsOut; x++ ) {
		if(Engine->OutSigs[x].OutPort == 3 &&
			Engine->OutSigs[x].active &&
			Engine->OutSigs[x].OutPin >= 1 &&
			Engine->OutSigs[x].OutPin < 33 ) {  // pins 1-32 (although only 1..16 are actual hardware outputs)

				SetBit(mask, 1, Engine->OutSigs[x].OutPin);
				On = Engine->OutSigs[x].Activated;
				if (Engine->OutSigs[x].Negated) 
					On = !On;
				if (On)
					SetBit(outs, On, Engine->OutSigs[x].OutPin); // set the bit in the output..
			}
	}
	mask &= p->getDigOutMask();				// Forget ones we can't control
	outs &= mask;

	// The following is commented out.  Instead, we assume the outputs get set as commanded.
	// This prevents message flooding in the case that the G100 refuses to comply for some reason.
	//curr = p->getDigOuts() & mask;
	curr = DigOutsCommanded;

	if (outs != curr) {
		p->setDigOuts(mask, outs);
		DigOutsCommanded = outs;
	}
}

void GRexControl::UserStop()
{
   
}

void GRexControl::EStop()
{
 
}


void GRexControl::doAnaOuts()
{
	unsigned mask = 0;
	float values[8];

	for (int i = 0; i < 4; ++i)
		if (abs( MainPlanner->ModOutputs[124+i] - AnaOutsCommanded[i]) > 2) {
			AnaOutsCommanded[i] = (unsigned short) MainPlanner->ModOutputs[124+i];
			mask |= 1u << i;
			values[i] = (float)AnaOutsCommanded[i];
		}
		if (mask)
			p->setAnaOuts(mask, values);
}



void GRexControl::doDigIns()
{
	unsigned ins = p->getDigIns();
	bool On;

	for (unsigned x = 0; x < (unsigned)nSigs; x++) {
		if (Engine->InSigs[x].InPort == 3 &&
			Engine->InSigs[x].Active &&
			Engine->InSigs[x].InPin >= 1 &&
			Engine->InSigs[x].InPin < 33 ) {		// Really only 22 inputs, but may have software functions defined

				On = ((ins >> (Engine->InSigs[x].InPin-1)) & 1) != 0;
				Engine->InSigs[x].Activated = Engine->InSigs[x].Negated ? !On : On;
				 
			}
			if ( x < sizeof(Engine->WaitCondition)*8) {
				if (Engine->WaitCondition & 1uLL << x &&
					Engine->InSigs[x].Active && 
					Engine->InSigs[x].Activated ) //to make Mach3 waitcondition work..
					Engine->WaitCondition &= ~(1uLL << x);
			}
	}
}


void GRexControl::doAnaIns()
{
	for (int i = 0; i < 4; ++i)
		MainPlanner->ModInputs[124+i] = (short)p->getSingleAnaIn(i);

	for (unsigned x = 0; x< p->getDimension(); x++)
	{
		 MainPlanner->ModInputs[118+x] = p->getSingleCounter(x);
	}
}


void GRexControl::doPosFeedback()
{

	
}


void GRexControl::doJog()
{
	 
}


void GRexControl::doMovement()
{
	 
}




void GRexControl::LimitHomeActivated( int Signal )
{
	 
}

void GRexControl::DoEmerg()
{
	 
}

void GRexControl::ProbeHit()
{
	 
}


int GRexControl::notifyHalt(
					 unsigned qid, 
					 void * qdata, 
					 G100Part * gp, 
					 unsigned halt_bit,
					 unsigned halt_value
					 )
{
	// This called from handler, so don't do any queueing.  Just save info and change state.

	 
	return 0;
}


void GRexControl::setMonitoring()
{
	 
}

void GRexControl::FillAndBurn(void)
{
	//burn new motor params into the G100
    WTConfig LocalConfig;
	AfxMessageBox("Flashing and Rebooting G100");
	memcpy( &LocalConfig, Config(),sizeof(WTConfig));
	//now set the max accel and max velocities..
	for(int x = 0; x < 6 ; x++)
	{
		double ispos = ((double) (8 <<LocalConfig.axis[x].divider));
		double maxv = (32768 * MainPlanner->Velocities[x] * MainPlanner->StepsPerAxis[x] ) / (33554432/ispos);    //stesp/ms.
		double maxa = (MainPlanner->Acceleration[x] * MainPlanner->StepsPerAxis[x] * ispos)/ 1048576; //steps/ms^2

		LocalConfig.axis[x].maxv = (float)maxv;
		LocalConfig.axis[x].maxa = (float)maxa;
	}
	CFile GConf;
	CString fname;
	fname.Format( "%s\\Macros\\%s\\GConf.dat", DefDir , Profile );
	if( GConf.Open( fname ,CFile::modeWrite | CFile::modeCreate, NULL)) 
	{	
		try 
		{
			GConf.Write( &LocalConfig , sizeof( WTConfig));  
		}
		catch(...)
		{

		}
		GConf.Close();
	}
		//So now the File is updated, so lets Flash the G100 so its all permanent. 
		// This will store the IP and NetMask permanently if its was only temp as well.
		// Redisovery will set the temp assignments as well, so no need to do that.
		//set the config into the flash..
		p->setConfig(1,0,1,0,&LocalConfig,NULL);

		 
		 
		//myPostInitControl should setup startup defaults as well. 
	 
	 
}



void GRexControl::NeedSetup()
{
	//first, lets zero the JogDDA's just in case..
	for (int i = 0; i < 6; ++i) JogDDAs[i] = 0;

	if (!p)
		return;	// Should never happen


	// Create default coordinate transformation.  Initially, p is set to 1 external step == 1 unit.
	// Both "steps per unit" and "direction" are incorporated.  We don't use translations as yet.
	double scale[6];
	
	for (unsigned i = 0; i < 6; ++i)
		scale[i] = MainPlanner->StepsPerAxis[i] * (Engine->Directions[i] ? -1.0 : 1.0);
	p->resetTransform();
	p->rateScaleAbsolute(scale);
	p->scale(scale);

	DebugOut("NeedSetup()  Set scale (%g,%g,%g)\n",  
			scale[0], scale[1], scale[2]
			);

	
}

//This routine can deal with data sent to it as full Gcode moves, or at least 
// the primitives that make up a line of Gcode's output, cycles etc..
/*
void GRexControl::DoCommandGCode(void)
{
	//only if connected and movable
	if(HomingMask) return;
	if( !p->isMovable()) return;
	//and only if data is holding..
	if( Engine->TrajHead == Engine->TrajIndex ) return;
 
	// we'll process line by line with a 1 second limit to end movement, and stop after the line 
	// that causes the buffer to exceed 1 second -- how much exceeded doesn't matter, unless the G100 can't take it.

	// -- Art, the G100 can handle anything :-)

	while( Engine->TrajIndex != Engine->TrajHead && p->getTotalLookahead() < 1024 )
	{
        //these two structures have information about the current move.
		GMoves  move = MainPlanner->Movements[Engine->TrajIndex];
		GMoves1 rest = MainPlanner->MovementsAdd[Engine->TrajIndex];
		//signify to Mach3 that this line is done.
		Engine->TrajIndex++;
		Engine->TrajIndex &= 0xfff; //
		//now add this move.
 	    if( move.type == TC_LINEAR )
		{
			HandleLinear( &move,&rest);
		}
		else
		{
			HandleArc( &move,&rest);
		}
		 
	}
	 
	return;
}
*/

void GRexControl::DoCommandGCode(void)
{
	 
}


//Two structures used here to describe movements in the queue
/*
//All coordinates are in abs coordinates, not step counts.
//
// Each structure holds a bit of data for each movement.

struct GMoves
{
   int type;    // 0 is linear, 1 is arc
   double cx,cy,cz; // center of move for arcs.  
   double ex,ey,ez,ea,eb,ec;  //endX, endY...etc..
   double sx,sy,sz,sa,sb,sc;  // StartX, StartY ...ect..
   __int64  DDA1[6]; //unused in the command mode.
   __int64  DDA2[6];
   __int64  DDA3[6]; 
   double Time; // unused in command mode.
   bool   Stop; // unused in command mode.
};

struct GMoves1
{
   double diffs[6];  // unused in command mode.
   double velocity;  // Vector velocity (Feedrate) of this move in units / second
   double accel;     // Acceleration of this move in units/sec^2
   double sweep;     // Sweep angle of this move. (Rads, positive)
   double radius;    // Radius of this arc.
   short nx,ny,nz;   // Normal of this arc.  Right-hand rule.
   short line;       // line number of this movement. In Cycles, this may be the same as other lines.
};
   


*/



void     GRexControl::HandleLinear( GMoves *move, GMoves1 *rest)
{
	 

}


void     GRexControl::HandleCVLinear( GMoves *move, GMoves1 *rest, GMoves *move_next, GMoves1 *rest_next)
{
	 

}






void     GRexControl::HandleArc( GMoves *move, GMoves1 *rest)
{
	 
	

}

