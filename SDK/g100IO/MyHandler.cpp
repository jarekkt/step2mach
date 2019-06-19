 
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
#include ".\myhandler.h"


extern TrajectoryControl *MainPlanner;	// used for most planner funcitons and program control 
extern CMach4View *MachView;			// used for most framework and configuration calls. 
extern TrajBuffer *Engine;				// Ring0 memory for printer port control and other device syncronisation
extern setup *_setup;					// Trajectory planners setup block. Always in effect
 

 
extern GRexControl *TheRex;
/***********************************************************************************************

G100 Common library handler class implementation

***********************************************************************************************/

int MyHandler::onHalt(
					  unsigned qid, 
					  void * qdata, 
					  G100Part * gp, 
					  unsigned halt_bit,
					  unsigned halt_value
					  )
{
	TheRex->DebugOut("@@@ MyHandler::onHalt qid=%u halt_bit=%u halt_value=%u\n",
		qid, halt_bit, halt_value);

	Engine->DwellTime = 0;
	return TheRex->notifyHalt(qid, qdata, gp, halt_bit, halt_value);
}


void MyHandler::onAck(
					  unsigned qid, 
					  void * qdata, 
					  G100Part * gp
					  )
{
	//printf("@@@ MyHandler::onAck qid=%u\n", qid);
}



void MyHandler::onComplete(
						   unsigned qid, 
						   void * qdata, 
						   G100Part * gp
						   )
{
	//TheRex->DebugOut("@@@ MyHandler::onComplete qid=%u\n", qid);
    
}



void MyHandler::onEndOfQueue(
							 unsigned qid, 
							 void * qdata, 
							 G100Part * gp
							 )
{
	TheRex->DebugOut("@@@ MyHandler::onEndOfQueue qid=%u\n", qid);

	// Done with any dwells
	//Engine->DwellTime = 0;

	if (TheRex->ProbeState != GRexControl::PROBE_MOVING)
		return;

	//Hmmmm... there's nothing to distinguish this case from probe hit as far as Mach3 can tell...
	TheRex->DebugOut("### Probe ran out without hit! ###\n");
	SetMachError("Probe finished with no hit");
	TheRex->ProbeState = GRexControl::PROBE_NONE;
	TheRex->reset_monitor = true;
	for (unsigned x = 0; x < 6; ++x)
		Engine->Axis[x].DepthCount = MainPlanner->PosChange[x];
	Engine->Sync = true;

}

 

void MyHandler::onDiscarded(
							unsigned qid, 
							void * qdata, 
							G100Part * gp
							)
{
	TheRex->DebugOut("@@@ MyHandler::onDiscarded qid=%u\n", qid);
	Engine->DwellTime = 0;
	 
}

 

void MyHandler::onDisconnect(
							 unsigned qid, 
							 void * qdata, 
							 G100Part * gp,
							 int reason
							 )
{
	Engine->DwellTime = 0;
	TheRex->DebugOut("@@@ MyHandler::onDisconnect qid=%u reason=%d\n", qid, reason);
}



void MyHandler::onConnect(
						  G100Part * gp
						  )
{
	TheRex->DebugOut("@@@ MyHandler::onConnect\n");

	// Call the setup routine so we're all on the same page
	TheRex->NeedSetup();
}



void MyHandler::onMsg(
					  G100Part * gp,
					  unsigned len,
					  const char * msg
					  )
{
	TheRex->DebugOut("@@@ MyHandler::onMsg \"%*.*s\"\n", len, len, msg);
	SetMachError("Message Came in" );
}


void MyHandler::onDebug(
						const char * str
						)
{
	TheRex->DebugOut("$$$ %s", str);
}


void MyHandler::onHomed(
						unsigned qid, 
						void * qdata, 
						G100Part * gp
						)
{
	TheRex->DebugOut("@@@ MyHandler::onHomed <entry> qid=%u, HomingMask=0x%02X\n", qid, TheRex->HomingMask);
	MainPlanner->ExternHomedMask |= TheRex->HomingMask; //record an offset requirement..
	for (unsigned x = 0; x < 6; ++x) if (TheRex->HomingMask & 1u<<x) 
	{
		if (Engine->AutoZero[x]) {
			TheRex->DebugOut("@@@   purging with axis zeroing\n");
			gp->purge(TheRex->HomingMask);
		}
		else {
			TheRex->DebugOut("@@@   purging without zeroing\n");
			gp->purge();
		}
		Engine->Axis[x].Homing = false;
		Engine->Axis[x].Jogging = false;
		Engine->Referenced[x] = true;
		TheRex->ddas_when_off[x] = 0;
		TheRex->ddas_when_on[x] = 0;
		//MainPlanner->SoftWait &=  ( 0xffffffffffffffff ^ ( ((__int64)1) << EXHOME)); //turn off home wait..
		
	}
	TheRex->HomingMask = 0;
   // MainPlanner->SoftWait = 0;
	Engine->Homing = false;
	Engine->Sync = true;
	if (Engine->LimitsOff)
		TheRex->reset_monitor = true;
	else
		TheRex->OffHomeMonitorReset = true;
	TheRex->DebugOut("@@@ MyHandler::onHomed <return>\n");
}


