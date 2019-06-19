#include "stdafx.h"
#include "G100-Structs.h"
#include "decoders.h"
#include "Engine.h"
#include "TrajectoryControl.h"
#include "MessageTracker.h"
#include "Monitoring.h"
#include "math.h"


extern TrajBuffer *Engine; 
extern TrajectoryControl *MainPlanner;
extern MessageTracker *G100Mess;
extern Monitoring     *G100Mon;
extern int InitQueue; //this is set to sync the Queue sequence to the G100 current state at startup or after a seq error.
extern int IDs[64]; //Line numbers for each queue move..
 


//////////////////////////////////////////////////// INPUT MESSAGE DECODING //////////////////////////////////////////////


//These routines are decoders of various messages structures. Their responsibility is to fill the G100 
//superstructure and perhaps trigger other events. Events are best hanlded by times repsonce however, not immediate 
// responce. TIming is not critical in most cases, and overflow of the G100 can result from pressing too much. 

extern GRex G100;

//this is responsibel for syncing states with anythign we're waiting for..
void SyncStates()
{
 int curmon;

	switch( G100.WaitForState )
	{
	case( NONE ): return;

	case( MONITORSET ):
	case( MONITORCHALLENGE ):
        curmon = G100.CurrentHaltBits ^ 0xffffff;
		if( G100.MonitorHaltBits == curmon ) 
			G100.WaitForState = NONE; //inversion in effect
		return;  //Todo.. Add timer for resend of halt mask if this times out..
	}

}


void FillFromFullStatus(WTMsFull status)
{ 
	CheckQueueCap( status.qcap , false );  //check the queue capacity before chekcing the monitor.
	CheckABSPosition( status.abs ); //active position update
	CheckCurrentState( status.qstate );  //check the state of the queue
	CheckEncoders( status.ctr ); //active
	CheckInputs(status.in ); //active
	CheckOutputs( status.out ); //active

} 


void CheckCurrentState( WTMsQstat state )
{
 static int lastm_isr = -1;
 static int lastque = 0;
 bool  WasStopped = G100.HasMoved;

 	state.halt_bits = ShuffleInWord( state.halt_bits );
	G100.CurrentHaltBits = state.halt_bits & 0xffffff;
	G100.CurrentISR = state.m_isr;
	G100.CurrentMISR = state.iters;
	// for realtime checks..
	G100.IsStill = ( state.sflags & QS_STILL ) != 0;
	G100.IsDrained = ( state.sflags & QS_MAVGZ) != 0;
	if( !G100.IsStill && !G100.IsDrained )
	{
		G100.HasMoved = true;
	}

	if( G100.EndQueueSeq == G100.CurrentQueueSeq &&
        lastm_isr == G100.CurrentMISR )
	{

	    //G100.IsStill = true;
		//G100.IsDrained = true;  //this corrects for a halt bug in the G100 that refuses to set IsStill 
		                        // And Is Drained if a monitor command is pending..
	}
    lastm_isr = G100.CurrentMISR;
	lastque = G100.CurrentQueueSeq;
	
    if( G100.Dwelling  && G100.CurrentMISR == 0)
		{
			//this will clear the dwell flag in the Engine, and 
			//mach3 will continue translating code..
			G100.Dwelling = false;
			Engine->DwellTime = 0;
		}
   if(  state.sflags & QS_HALT ) //we have a monitoring trigger..
	{
		G100Mon->OnMonitor(state.curr , state.halt_bits ); //this sends the challenge number and mask to the OnMonitor to decide what to do..
		G100.SystemHalted = true;
	}
	else
		G100.SystemHalted = false;
  //now check every WTMsQstat for a sequence change..
   
}

 



void CheckQueueCap( WTMsQcap cap , bool ASync )
{
 CString debug;

	G100.CurrentQueueSeq = cap.cseq;  // Current queue sequence number
	//Store the next sequence number if we're init'ing the queue
   	G100.EndQueueSeq = cap.eseq;      // Ending (most forward) QSN, plus one.
	if (IDs[ G100.CurrentQueueSeq & 0x3f ] != 0 && Engine->TrajHead != Engine->TrajIndex )
	{
		debug.Format("Set to Display line: %d", IDs[ G100.CurrentQueueSeq & 0x3f ] );
		Engine->DisplayLine = IDs[ G100.CurrentQueueSeq & 0x3f ];
		G100Mess->DebugOut( debug );
	}

	if( InitQueue == 1 ) 
	{ 
		G100.NextQueue =  G100.EndQueueSeq;  //sync the SEQ and the ACK
		G100.LastStored = G100.LastAck +1;
		debug.Format( "Initit Queue to %d and Seq to %d", G100.NextQueue, G100.LastStored );
		G100Mess->DebugOut( debug );
		InitQueue = 0; 
	}
	if( InitQueue > 0 ) InitQueue--;

	G100.QueueFlags = cap.flags;   	 // Queue capacity flags  
 	
};  //check the queue capacity


void CheckABSPosition( WTMsAbs abs   )
{
   G100.LastAbs = abs;
   static int last[6] = { 0,0,0,0,0,0 };
   for( int x = 0; x<6; x++)
   {
	   if( Engine->Directions[x] ) abs.p[x] = - abs.p[x];
	   MainPlanner->PosChange[x] = RateToPos( x, abs.p[x]);
	   G100.CurDDA[x] = abs.p[x];
	   G100.LastCoord[x] = ActualPos( x, abs.p[x] );
  //Mach3 Position update here
	   Engine->Axis[x].Index = (int) RateToPos( x,G100.CurDDA[x]);  //update the MAch3 index registers with absolute position..
  //Feedrate realtime update here for each axis.
	   Engine->StatLast[x] = ((abs.v[x] + last[x]) / 2) * 205;  //amount per ms * 200 to match a 200ms calculation in Mach3
       Engine->StatLast[x] = RateToPos( x, Engine->StatLast[x] );
	   last[x] = abs.v[x];
   }

   if( G100.IsStill && G100.IsDrained && G100Mess->nMessages == 0)  //tell the Engine that all is done..
	    MainPlanner->ExternalStill = true;
	else
        MainPlanner->ExternalStill = false;

   for( int a = 3; a<6; a++)
    if( Engine->Axis[a].Slave )  //slaved axis should always report zero;
    {
     MainPlanner->PosChange[a] = 0;
	 G100.LastCoord[a] = 0;
	 Engine->StatLast[a] = 0;
	 last[a] = 0;
    }
   
	
}; // positions


void CheckRELPosition( WTMsPos abs)
{
 for( int x = 0; x<6; x++)
   {
	   Engine->Axis[x].DepthCount = RateToPos( x, abs.pos[x].i ); 
	   if(Engine->Directions[x] )  Engine->Axis[x].DepthCount =  -Engine->Axis[x].DepthCount;
   }
	
};


void CheckEncoders( WTMsCtr counts  )
{
  for( int x = 0; x<6; x++)
  {
	  Engine->Encoders[x].Count[0] = (counts.cex[x] << 16 | counts.f[x].c) - MainPlanner->EncoderZeros[x];  //ask Steve about this being short?
  }
  Engine->Counter = G100.CurrentISR;
}; //encoder positions


void CheckInputs( WTMsIn In ) 
{
  In.i = ShuffleInWord( In.i); //shuffle the input word.. 
  G100.InWord = In.i;
  bool On = false;
  for( int x = 0; x< nSigs; x++ )
  {
	  if( Engine->InSigs[x].InPort == 1 &&
		  Engine->InSigs[x].Active &&
		  Engine->InSigs[x].InPin >= 1 &&
		  Engine->InSigs[x].InPin < 23 )
	  {
	  On = ((In.i >>  (Engine->InSigs[x].InPin -1)) & 0x01);
	  Engine->InSigs[x].Activated = On;
	  if( Engine->InSigs[x].Negated ) Engine->InSigs[x].Activated = !On;
	  }
	  if( x < 64 )
      {
       int mask = 1 << x;
       if( (Engine->WaitCondition & mask) > 0 )
	   if( Engine->InSigs[x].Active && Engine->InSigs[x].Activated ) //to make Mach3 waitcondition work..
		   Engine->WaitCondition &= ( 0xffffffff ^ mask );
      }
  }
  MainPlanner->ModInputs[124] = In.ain[0]; //analogue inputs to the analogue holding registers.
  MainPlanner->ModInputs[125] = In.ain[1];
  MainPlanner->ModInputs[126] = In.ain[2];
  MainPlanner->ModInputs[127] = In.ain[3];
	
};  //inputs

void CheckOutputs( WTMsOut out   )
{
  bool On = false;
  G100.NeedDigOutputs = false;
  unsigned int outs = 0;
  for( int x = 0; x< nSigsOut; x++ )
    {
	  if( Engine->OutSigs[x].OutPort == 1 &&
		  Engine->OutSigs[x].active &&
		  Engine->OutSigs[x].OutPin >= 1 &&
		  Engine->OutSigs[x].OutPin < 17 )  //pins 1-16
	  {
		  On =  Engine->OutSigs[x].Activated;
		  if( Engine->OutSigs[x].Negated) On = !On;
		  //On is now true or false depending on the current state
		  SetBit( outs, On, Engine->OutSigs[x].OutPin); //set the bit in the output..
      }
	}
  if( out.o != outs )
	 G100.NeedDigOutputs = true;

  G100.NeedAnaOutputs = false;
  if( (unsigned short)MainPlanner->ModOutputs[124] != out.aout[0] || //analogue outputs from analogue holding registers.
	  (unsigned short)MainPlanner->ModOutputs[125] != out.aout[1] ||
	  (unsigned short)MainPlanner->ModOutputs[126] != out.aout[2] || //analogue #3 seems unable to accept data
	  (unsigned short)MainPlanner->ModOutputs[127] != out.aout[3])
	  G100.NeedAnaOutputs = true; 

}; //outputs


//Numeric Helpers/ ////////////////////////////////////////////////////////////////////////////


int ShuffleInWord(int data)
{
	int a = (( data & 0xff0000) >> 16);
	int b = (( data & 0x00ff000000) >> 16);
	int c = (( data & 0xff00) << 8);
	return a | b | c;
}

int ShuffleOutWord(int data)
{
	int a = (( data & 0xff) << 16);
	int b = (( data & 0x00ff00) << 16);
	int c = (( data & 0xff0000) >> 8);
	return a | b | c;
}
void SetBit( unsigned int &data, bool OnOff, short nBit)
{
	if( OnOff ) //bit shoudl be made high
	{
		data |= ( 1 << (nBit-1) ); 
		return;
	}
	data = data ^ 0xffffffff;
	data |= ( 1 << (nBit-1) );
	data = data ^ 0xffffffff;
	 
}

slong   RateToPos( int axis, slong pos)
{
  slong poso;
  poso =  (slong)(pos / pow( (int)2, G100.Config.axis[axis].divider + 3));  
  return poso;
}

double  ActualPos( int x, slong pos )
{

  double poso;
  poso =  (pos / pow( (int) 2, G100.Config.axis[x].divider  + 3));  
  return poso / MainPlanner->StepsPerAxis[x];

}

////////////////////////////////////////////////////////////////////// Helper routines for Network Traffic.
//

CString IpToString(DWORD ip)
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


