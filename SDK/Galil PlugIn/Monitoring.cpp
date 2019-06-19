#include "stdafx.h"
#include "externalmovement.h"
#include "G100-Structs.h"
#include "Engine.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "rs274ngc.h"
#include "math.h"
#include "Messagetracker.h"
#include "Monitoring.h"
#include ".\monitoring.h"
#include "MachDevice.h"


extern TrajBuffer *Engine;  //Main Engine Block Variables
extern TrajectoryControl *MainPlanner;  //Trajectory Planner Vars. 
extern setup *_setup;   //RS274 Var block.
extern CMach4View *MachView;
G100Message MonitorMessage; //Temp Holding for monitoring  messages. 

extern GRex G100;
extern MessageTracker  *G100Mess;
extern bool ShutDown;
extern int ShuffleOutWord(int data);
extern int InitQueue;
extern VoidLPCSTR  Code;
G100Message        TempMessage;
 
// Monitoring

IMPLEMENT_DYNAMIC(Monitoring, CWnd)
Monitoring::Monitoring()
{
	G100Mess->SetMessDef( &MonitorMess, WT_MONITOR );
	G100.CurrentChallenge = 1;
	G100.Homing = false;
	G100.HomingMask = 0;
	G100.HomeAxis = -1;
	G100.SEQUENCE = NOSEQ; 
	G100.MESSAGESEQ = NOMSEQ;
}

Monitoring::~Monitoring()
{
}


BEGIN_MESSAGE_MAP(Monitoring, CWnd)
END_MESSAGE_MAP()



// Monitoring message handlers

void Monitoring::SetWords()
{
   
    static int limits[12] = { 0,1,3,4,6,7,9,10,12,13,15,16 };
	short homeaxis[6] = { 2,5,8,11,14,17 }; //homes for the 6 axis
	G100.MonitorHaltBits = 0;
	G100.MonitorHaltMask = 0;
	G100.MonitorMask = 0xffff; //for now monitor all input for toggles.
	/////////////////////////////////////////////////////////////////////////
	//
	//   Limit Switches
	//
	if( !Engine->Homing  ) //no limit switches in homing...
	{
	for( int x = 0; x<12; x++)   //this sets monitoring on limits and on Estop unless limits are overridden..
	 {
		if( Engine->InSigs[limits[x]].Active &&
			Engine->InSigs[limits[x]].InPort == 1 &&
			Engine->InSigs[limits[x]].InPin < 22 &&
			Engine->InSigs[limits[x]].InPin > 0 )
		{ //these signals are all needing monitoring for halt..
		  if( Engine->LimitsOff && Engine->InSigs[limits[x]].Activated ) 
		  {  
			  continue; //skip it if overridden..
		  }
          if( Engine->InSigs[limits[x]].Activated )
		  {
             G100.MonitorHaltMask = 0;
			 G100.MonitorHaltBits = 0;
			 Engine->EStop = true;
			 Engine->EStopReason = LIMITSWITCH; //Tell the use his Limit Switch is on..
			 return;
		  }
		  G100.MonitorHaltBits |= ( 1 <<  (Engine->InSigs[limits[x]].InPin - 1 ));
		  if( !Engine->InSigs[limits[x]].Negated )
			  G100.MonitorHaltMask |= ( 1 << ( Engine->InSigs[limits[x]].InPin - 1 ));
		  else
		  {
			 G100.MonitorHaltMask = G100.MonitorHaltMask ^ 0xffffffff;
	         G100.MonitorHaltMask |= ( 1 <<  (Engine->InSigs[limits[x]].InPin - 1 ));
	         G100.MonitorHaltMask = G100.MonitorHaltMask ^ 0xffffffff;  
		  }
		}
		else 
			G100.MonitorHaltMask &= 0xffffffff ^ ( 1 <<  (Engine->InSigs[limits[x]].InPin - 1 )); //turn off bit, not monitored. 
	  }
	}
	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  ESTOP Input monitored at all times...

	if( Engine->EStop)
	{
		G100.MonitorHaltBits = 0;  //no monitoring in Estop;
		G100.Homing = false;       //just in case Estop happened during homing;
		G100.HomingMask = 0;
		G100.SEQUENCE = NOSEQ;
		for( int x = 0; x < 6; x++)
		{
			Engine->Axis[x].Homing = false;
			Engine->Axis[x].DeRef = false;
			MainPlanner->Homeing = false;
		}
	}

	if( Engine->InSigs[EMERGENCY].InPort == 1 && Engine->InSigs[EMERGENCY].InPin <= 22 )
	{
		G100.MonitorHaltBits |= ( 1 <<  (Engine->InSigs[EMERGENCY].InPin - 1 )); 
       if( !Engine->InSigs[EMERGENCY].Negated )
		      G100.MonitorHaltMask |= ( 1 << ( Engine->InSigs[EMERGENCY].InPin - 1 ));
		  else
		  {
             G100.MonitorHaltMask = G100.MonitorHaltMask ^ 0xffffffff;
	         G100.MonitorHaltMask |= ( 1 <<  (Engine->InSigs[EMERGENCY].InPin - 1 ));
	         G100.MonitorHaltMask = G100.MonitorHaltMask ^ 0xffffffff;  
		  }
		  if( Engine->InSigs[EMERGENCY].Activated )
		  {
		     
             G100.MonitorHaltMask = 0;
			 G100.MonitorHaltBits = 0;
			 if( Engine->EStop ) return;
			 Engine->EStop = true;
			 Engine->EStopReason = ESTOPINPUTLINE; //Tell the use his Limit Switch is on..
			 return;
		  }
	}
/////////////////////////////////////////////////////////////////////////////////////////////////
   //
   //  Homing , set to match the HomingMask value bits..

  if( G100.HomeAxis != -1  )
	{
	   int x = G100.HomeAxis;
       //this sets up monitoring for any single axis that is going to home. Slaving is automaticlly handled by the Gcode move. 
	   //Todo.. add a way for autosquareing to work..
	   G100.MonitorHaltBits |= ( 1 <<  (Engine->InSigs[homeaxis[x]].InPin - 1 )); //set the monitor to the home pin for each axis;
	   if( (!Engine->InSigs[homeaxis[x]].Negated && !Engine->Axis[x].DeRef) || (Engine->InSigs[homeaxis[x]].Negated && Engine->Axis[x].DeRef))
		      G100.MonitorHaltMask |= ( 1 << ( Engine->InSigs[homeaxis[x]].InPin - 1 ));
		  else
		  {
             G100.MonitorHaltMask = G100.MonitorHaltMask ^ 0xffffffff;
	         G100.MonitorHaltMask |= ( 1 <<  (Engine->InSigs[homeaxis[x]].InPin - 1 ));
	         G100.MonitorHaltMask = G100.MonitorHaltMask ^ 0xffffffff;  
		  }
	}
	

//////////////////////////////////////////////////////////////////////////

	if( G100.SEQUENCE == PROBESTART || G100.SEQUENCE == PROBEACTIVE )
	{
	 if( !Engine->InSigs[DIGITIZE].Active || (Engine->InSigs[DIGITIZE].Active && Engine->InSigs[DIGITIZE].Activated ))
	 {
		  
			 //Digitizing failure. Probe Active or not used. 
           G100.SEQUENCE =  NOSEQ; //turn off the probeing sequence.
		   G100Mess->Purge();
		   MainPlanner->PurgeMovements = true;
		   Engine->Sync = true; //tell Mach3 we are finished with this probe move. 
		                      // At sync time Mach3 will turn off the wait for probe, record
		 //present position if appropriate, and resume program..

	 }
	 else
	 {
	   G100.MonitorHaltBits |= ( 1 <<  (Engine->InSigs[DIGITIZE].InPin - 1 )); //set the monitor to the Probe pin as well as all others..
        if( !Engine->InSigs[DIGITIZE].Negated )
		      G100.MonitorHaltMask |= ( 1 << ( Engine->InSigs[DIGITIZE].InPin - 1 ));
		  else
		  {
             G100.MonitorHaltMask = G100.MonitorHaltMask ^ 0xffffffff;
	         G100.MonitorHaltMask |= ( 1 <<  (Engine->InSigs[DIGITIZE].InPin - 1 ));
	         G100.MonitorHaltMask = G100.MonitorHaltMask ^ 0xffffffff;  
		  }
	 }
	}
    G100.MonitorHaltMask &= 0xffffff;
	G100.MonitorHaltBits &= 0xffffff;
   
  //We now have a Monitoring word and a Monitoring mask sufficient for the Estop and limit switches..

}// Monitoring.cpp : implementation file
//


void Monitoring::Update(void)
{
   if( G100.SystemHalted ) return; //no monitoring if halted already..
   if( InitQueue > 0 ) return; //no monitorsing if resyncing..
   SetWords(); //recalculate the Monitoring Words.
   int hlt = (G100.MonitorHaltBits ^ 0x00ffffff);
   if( G100.CurrentHaltBits != hlt )
   { //time to update the monitoring hardwares masks..
     UpdateMasks();
   }
   else
   {
    //monitoring now agrees with conditions. If probeing or homing, we can trigger events here..
    //we now know the mask is properly set..
     G100.LastChallenge = -1;
	 CompleteSequences(); //now , since masks must be good. Lets complete any waiting sequences..

   }
}



void Monitoring::UpdateMasks(void)
{

   CTimeSpan sec = CTime::GetCurrentTime() - G100.WaitSet;
   if(( G100.WaitForState == MONITORSET || G100.WaitForState == MONITORCHALLENGE )&& sec.GetSeconds() < 1 ) return;//add a time check here.. We're waiting for it to acknowledge the last Monitor setting..

   G100.CurrentChallenge += 3; //Lets bump it to be easily recognised.
   if( G100.CurrentChallenge > 256 ) G100.CurrentChallenge = 1;
   ((WTMonitor*)&MonitorMess.Message)->chResponse = G100.CurrentChallenge;
   ((WTMonitor*)&MonitorMess.Message)->haltMask =   ShuffleOutWord(G100.MonitorHaltBits);
   ((WTMonitor*)&MonitorMess.Message)->haltValue =  ShuffleOutWord(G100.MonitorHaltMask);
   ((WTMonitor*)&MonitorMess.Message)->mask = 0xffffff;//G100.MonitorMask; //monitors all inputs.
   ((WTMonitor*)&MonitorMess.Message)->anaMask = 0;
   G100Mess->DebugOut( "New Monitor Sent." );
   G100Mess->Add2Queue( &MonitorMess );
   G100.WaitForState = MONITORSET;   //Lets tell the system to wait for this mask to be acknoledged and set..
   G100.WaitSet = CTime::GetCurrentTime();
   G100.WaitForValue = G100.MonitorHaltBits;
   G100.WaitSet = CTime::GetCurrentTime(); //lets set the time we set this message..
   CString debug;
   debug.Format( " New Mask queues : HaltBits: %x, Mask: %x  \n", ((WTMonitor*)&MonitorMess.Message)->haltMask,
	   ((WTMonitor*)&MonitorMess.Message)->haltValue );
   G100Mess->DebugOut( debug );

}

void Monitoring::OnMonitor(short curr, DWORD hBits)
{
   CString out; //we get a Monitor report..we can ack it , cuz we'll wait fo rthe new one to be set anyway..
   CTimeSpan sec;
   CTime now = CTime::GetCurrentTime();
   out.Format( " Recieved Monitor #%d , cancelling haltbits %x...  \n ", curr, hBits );
   G100Mess->DebugOut( out );
   out.Format( " Recieved Monitor #%d  Halt %x..Terminating queue... \n ", curr, hBits );
   G100Mess->DebugOut( out );
   G100Mess->Purge(); //Kill all traffic and messages.  
  
  
   //BUT we need to kill the planners current queue..and resync movement..
   //Ansewer the challenge., this will keep the G1200 happy..
   ((WTMonitor*)&MonitorMess.Message)->chResponse = curr;    //Acknowlede this message..
   ((WTMonitor*)&MonitorMess.Message)->haltMask = 0;
   ((WTMonitor*)&MonitorMess.Message)->haltValue = 0;
   ((WTMonitor*)&MonitorMess.Message)->anaMask = 0;
   G100.WaitSet = CTime::GetCurrentTime();
   G100Mess->Add2Queue( &MonitorMess ); //send responce. //this kills the monitoring , new monitoring required..

   if( G100.WaitForState == MONITORCHALLENGE ) return;
   G100.WaitForState = MONITORCHALLENGE;  //we'll wait till this gets acked..
   
   G100.MESSAGESEQ = PURGEAFTERHALT;  //send a purge of movemnt when the new mask gets established..
   //We only get here is system is no longer halted. So all is OK message wise from here..
   //So now lets deal with the issue at hand, the fault reason..
  if( G100.LastChallenge == curr ) return; //we've already done the action for this halt. 
  G100.LastChallenge = curr; // remember it. 

 for( int x = 0; x< nSigs; x++) 
   {
	   if( Engine->InSigs[x].InPort == 1 && Engine->InSigs[x].Active )
	   {
		   if(( (hBits & G100.MonitorHaltBits) >> (Engine->InSigs[x].InPin-1 )) & 0x01 )
		   {
			  if( x <  18 )           
				  LimitHomeActivated(x); //Limit Switch or Home switch
			  if( x == EMERGENCY )    
				  DoEmerg();
			  if( x == DIGITIZE )    
				  ProbeHit();  // Probe Switch
		   }
	   }
   }
 }

void Monitoring::LimitHomeActivated( int Signal )
{
short homeaxis = 0;
CString out;
 
switch( Signal )
	{
	case( XLIMITPLUS ):
	case( XLIMITMINUS):
	case( YLIMITPLUS):
	case( YLIMITMINUS):
	case( ZLIMITPLUS):
	case( ZLIMITMINUS):
	case( ALIMITPLUS):
	case( ALIMITMINUS):
	case( BLIMITPLUS):
	case( BLIMITMINUS):
	case( CLIMITPLUS):
	case( CLIMITMINUS):

		if( G100.HomeAxis != -1) return; //if homing or dereffing, limit switches are off..
		out = "Limit Switch Activated *****************\n";
		G100Mess->DebugOut( out );
		Engine->EStopReason = LIMITSWITCH;
		DoEmerg();  //set the reason, then trip an EStop..
		            //Movement has already been purged..
	    break;

	case( XHOME ):  
	case( YHOME ): 
	case( ZHOME ):
	case( AHOME ):
	case( BHOME ):
	case( CHOME ):
		out = "Home Switch Activated *****************\n";
		G100Mess->DebugOut( out );
	    if( G100.SEQUENCE == HOMEWAIT )
		{
		  G100Mess->DebugOut("Switched to  HomeOnSwitch \n");
          G100.SEQUENCE = HOMEONSWITCH;  //this will switch us to home on switch routine, and set deref on home signal...
		  Engine->Axis[G100.HomeAxis].DeRef = true; //this will toggle the polarity of the expected signal to halt..
		}
		else
		if( G100.SEQUENCE = HOMEMOVEOFF )
		{
          G100Mess->DebugOut("Switched to  HomeIsOffSwitch \n");
          G100.SEQUENCE = HOMEISOFF;  //this will switch us to home on switch routine..
		  Engine->Axis[G100.HomeAxis].DeRef = false; //this will flip the polaity back to a normal monitor. 
		}
		//TODO  Add homing sequencer code..
		break;
	}
}

void Monitoring::DoEmerg()
{
	Engine->EStop = true;
	G100Mess->DebugOut(" ****ESTOP Triggered****\n ");
	G100.SEQUENCE = NOSEQ;
	G100.HomeAxis = -1;
	for( int x = 0; x < 6; x++) 
	{
      Engine->Axis[x].Homing = false;
	  Engine->Axis[x].DeRef = false;
	}
	Engine->Sync  = true;

}

void Monitoring::ProbeHit()
{
	if ( G100.SEQUENCE  != PROBEACTIVE ) return;
    G100Mess->DebugOut(" SEQUENCE changed to PROBEHIT");
	//when we get here, the probe has been hit, and the message traffic told to purge. 
	//now we need to wait for the new Haltmask of zero to be effected, and for the G100 to be fully still
	G100.SEQUENCE = PROBEHIT;  //lets switch to ProbeHit as our new state. The decoder sequencer will now
	                           //complete the move when all is purged, halted and still..

}

void Monitoring::OnMonitorMessage( WTMonitor *mon )
{
	 //unused at present..

}

//Sequences resides here because it deals with synconising to the currently monitored signals for halt. 
//this is primarily fgor Homing or probine..

void Monitoring::CompleteSequences()
{

 CString com;

 
 //OK, lets check what we're waiting for, and see if it is done..

//First, any message traffic Sequencing..higher pritority than nomral movement sequences.

    switch( G100.MESSAGESEQ )
	{
	case( PURGEAFTERHALT ) :    G100Mess->DebugOut(" Sending a post halt Purge message \n" ); 
		                        G100Mess->SetMessDef( &TempMessage, WT_PURGE );
                                TempMessage.size = sizeof( WTPurge );
                                ((WTPurge*)&TempMessage.Message)->flags = 0;
                                G100Mess->Add2Queue( &TempMessage ); //send an abort..
		                        G100.MESSAGESEQ = NOMSEQ; //turn off this sequence flag.
                                return; //no more sequences this pass.
	default: break;

	}
//Now normal sequencing..
	switch ( G100.SEQUENCE )
	{
	case (NOSEQ):  return; //no sequence in effect

    case( PROBESTART ): //we now know then that the monitor bit is set, we can do the move.
		              MainPlanner->DoExternalProbe = true; //this will trigger the move.
	                  G100.HasMoved = false; //lets make sure movement has begun before syncing this moves start or end. 
                      G100.SEQUENCE = PROBEACTIVE; //now wait for probe move to end.
	                  break;
	case (PROBEHIT) : 
		              if( !G100.IsStill || !G100.IsDrained ) return; //we're not yet finsihed the purge after the probe..
                      //we're now at reast after the probe begin hit.
					  G100Mess->DebugOut(" Running PROBEHIT Action. \n" );
                      G100.SEQUENCE = NOSEQ; //stop the sequence for probing..
					  for( int x = 0; x < 6; x++ )
		              Engine->Axis[x].DepthCount = MainPlanner->PosChange[x];
					  Engine->Sync = true;   //this should be all we have to do..
					  break; //all done with hit
   
    case (PROBEACTIVE) : //we're waiting for the probe move to stop..
		              if( G100.SystemHalted ) return;  //we're not stopped and still
					  if( !G100.HasMoved ) return; //we havent started the probe move yet, so ignore this end of move check till then.
					  if( !G100.IsDrained || !G100.IsStill ) return; //we're still moving
					  //we have stopped moving.. This means the probe finished without hitting.
					  G100Mess->DebugOut(" Running PROBEACTIVE action.. End of move seen. \n" );
		              G100.SEQUENCE = NOSEQ; //stop the sequence for probing..
					  for( int x = 0; x < 6; x++ )
		              Engine->Axis[x].DepthCount = MainPlanner->PosChange[x];
					  Engine->Sync = true;   //this should be all we have to do, mach3 will resync and continue..
					  break;
	case( HOMESTART ):
		              //here we start the homing sequence. 
		              //the monitoring for this axis has been set already, but may have tripped the halt already if it 
		              //was already on the switch.. if So, it never gets here.
		              //so here we start the move for the homeing run of this axis. as a GCode move.
		              StartHome( G100.HomeAxis );
                      break;
    case( HOMEWAIT ):
		              //nothing to do here . we're just waiting for a stop..
                      break;
	case( HOMEONSWITCH ):
		              G100Mess->DebugOut(" Starting home off switch de-ref move \n");
		              EndHome(G100.HomeAxis);
                      break;

    case( HOMEMOVEOFF ): //nothing to do here, just waiting for switch to move off
		                 break;
    case( HOMEISOFF ):
		              G100Mess->DebugOut(" Purging Homed axis \n");
		              if( Engine->AutoZero ) myPurge( 1 << G100.HomeAxis );
					  Engine->Axis[G100.HomeAxis].Homing = false;
					  MainPlanner->ExternHomedMask |= 1 << G100.HomeAxis; //record an offset requirement..
					  G100.HomeAxis = -1; //turn off the homed axis monitoring..
					  for( int x = 0; x < 6; x++ )
					  {
						  if( Engine->Axis[x].Homing )
						  {
						     G100.HomeAxis = x;
                             G100.SEQUENCE = HOMESTART;
							 return;
						  }
					  }
					  //when we get here, the home sequences are finished..
                      G100.SEQUENCE = HOMEDONE;
					  break;
					 
					 
	case( HOMEDONE):  //lets send the offsets move.. 
		              // but we'll wait for the coordinates to be synced..
		              G100.SEQUENCE = NOSEQ;
					  G100.Homing = false;
					  Engine->Homing = false;
					  Engine->Sync = true;   //this will trigger the offset move form MAch3, when all the homing is  done..
					  break;
	 
	}
}


void Monitoring::StartHome( int axis )
{ //we're already monitoring this axis for halt, so lets move..
  CString move;
  double feedrate = (MainPlanner->Velocities[axis] ) * (((double)MainPlanner->RefSpeed[axis]) / 100);
  G100.SEQUENCE = HOMEWAIT;
  MyJogOn(axis, MainPlanner->AxisNegs[axis] , feedrate );

}

void Monitoring::EndHome( int axis )
{ //we're already monitoring this axis for halt, so lets move..
  CString move;
  double feedrate = (MainPlanner->Velocities[axis] ) * (((double)MainPlanner->RefSpeed[axis]) / 500);
  G100.SEQUENCE = HOMEMOVEOFF;
  MyJogOn(axis, !MainPlanner->AxisNegs[axis] , feedrate );

}

