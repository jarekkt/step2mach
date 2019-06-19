#include "stdafx.h"
#include "externalmovement.h"
#include "G100-Structs.h"
#include "Engine.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "rs274ngc.h"
#include "math.h"
#include "Messagetracker.h"

extern TrajBuffer *Engine;  //Main Engine Block Variables
extern TrajectoryControl *MainPlanner;  //Trajectory Planner Vars. 
extern setup *_setup;   //RS274 Var block.
extern CMach4View *MachView;
G100Message JogMessage; //this message is reserved for Jogging messages  alone. 
G100Message PurgeMessage;
G100Message MoveMessage; //Temp Holding for movement messages. 
G100Message Cubic; //All Gcode movement are Cubic moves.
extern GRex G100;
extern MessageTracker  *G100Mess;
extern bool ShutDown;
extern int InitQueue;

 
int       IDs[64];  //used to get MAch3 to display the current line it is on..
int       tIDs[64];


void InitJogMessage()
{
  //This sets up the general JogMessage parameters so we dont have to keep intialising the ones that stay static..
	for( int x = 0; x<6; x++ )
   {
      ((WTLinear*)&JogMessage.Message)->v[x].i = 0;
      ((WTLinear*)&JogMessage.Message)->v[x].f = 0;
   }
  G100Mess->SetMessDef( &JogMessage, WT_LINEAR ); 
  ((WTLinear*)&JogMessage.Message)->m.T = 0; //All Jog Message Times are 0 to indicate Jog..
  G100Mess->SetMessDef( &Cubic, WT_CUBIC );
  Cubic.size = sizeof( WTCubic );


}

void myPurge( short flags)
{
   G100Mess->SetMessDef( &PurgeMessage, WT_PURGE );
   PurgeMessage.size = sizeof( WTPurge );
   ((WTPurge*)&PurgeMessage.Message)->flags = flags;
   G100Mess->Add2Queue( &PurgeMessage ); //send responce.
}

void myDwell( double time)
{
 
	SendDwell( time );
	G100.Dwelling = true;
	Engine->DwellTime = 1; //this stops mach until the dwell runs out. 
}

void MyJogOn( short axis, short direction, double SpeedNorm)
{
  
  if( InitQueue != 0 ) return;
  if( Engine->EStop ) return; //no joggin in Estop.
  if( G100.SEQUENCE != NOSEQ && G100.SEQUENCE != HOMEWAIT && G100.SEQUENCE != HOMEMOVEOFF) return; //were running some sequence in which jogging is not allowed. 
  if( G100.WaitForState != NONE ) return;
  G100Mess->DebugOut( "---- JogOn ---\n" );
  if( G100Mess->nMessages > 3 || G100.Window < 4 ) return;
  if( Engine->Axis[axis].Jogging ) //no quick reverse of axis joggin, just stop it..
  {                                //the axis will stop when the key is lifted. 
    if( ((WTLinear*)&JogMessage.Message)->v[axis].i < 0 &&  Engine->Axis[axis].JoggDir == 0 && direction == 0) return;
	if( ((WTLinear*)&JogMessage.Message)->v[axis].i > 0 &&  Engine->Axis[axis].JoggDir == 0 && direction == 1) return;
  }
  //Now we need to know the appropriate Jogging Speed
  // the Rapid Jog speed?
  double JogFeed = (MainPlanner->Velocities[axis]); //rapid steps per second
  // JogSpeed OverRide. (Used in Velocity mode of MPG jog.) ?
  if( SpeedNorm != 0 ) JogFeed = SpeedNorm;
  //Keyboard Shift key is on?
  // If shift is not on, then JogPercent is the speed to use. 
  if( !(*MachView->m_ShiftState) && SpeedNorm == 0) 
            JogFeed = (JogFeed * _setup->JogPercent / 100); //JogSteps/Sec..

  // Lets check the G100 block to see if Jogging is presently on. G100.InJog keep track from here and is reset by the queue checker in decoding..
  if(  G100.InJog ) 
	  //If we are jogging, clip the velocity to the Mavg's maximum speed. 
	  JogFeed =  JogClipVel( axis, JogFeed ); //clip if Mavg is already in effect..
  else
	  //otherwise set a new Mavg for this jog speed. 
	  JogSetMavg( axis, JogFeed ); //set a new mavg if nothing is already running..

  // Lets change JogFeed to a number of steps per second and call it spd (speed). 
  double spd = JogFeed * MainPlanner->StepsPerAxis[axis];
  G100.InJog = true; //and set the G100 Block to indicate we are currently jogging on an axis ..any axis.. 
  //spd should be negative if the direction is backwards. 
  if( direction == 1) 
	  spd *= -1;
  //and Re-Reversed if the axis is reversed. 
  if( Engine->Directions[axis] ) spd *= -1;
  //Now calculate the actual DDA for this jog move;
  //taking into accoutn the divider indicating maximum speed of this axis in the G100
  long long dda;
  switch(G100.Config.axis[axis].divider  ) 
  {
  case (0): dda = (uint64)(spd * 33554432.0);  break; // 2**32 (or 1/128 )..
  case (1): dda = (uint64)(spd * 33554432.0) * 2;  break; // 2**32
  case (2): dda = (uint64)(spd * 33554432.0) * 4;  break; // 2**32
  case (3): dda = (uint64)(spd * 33554432.0) * 8;  break; // 2**32
  case (4): dda = (uint64)(spd * 33554432.0) * 16;  break; // 2**32
  case (5): dda = (uint64)(spd * 33554432.0) * 32;  break; // 2**32
  case (6): dda = (uint64)(spd * 33554432.0) * 64;  break; // 2**32
  case (7): dda = (uint64)(spd * 33554432.0) * 128;  break; // 2**32
  }
  //Set the DDA values in the Jog Message for this move. 
  ((WTLinear*)&JogMessage.Message)->v[axis].i = (signed long)(dda >> 32);
  ((WTLinear*)&JogMessage.Message)->v[axis].f = (unsigned long)(dda & 0xFFFFFFFFuLL);
  //And slave the axis if selected
  for( int a = 3; a<6; a++)
  if( Engine->Axis[a].Slave && Engine->Axis[a].SlaveAxis == axis )
  {
    ((WTLinear*)&JogMessage.Message)->v[a].i = (signed long)(dda >> 32);
    ((WTLinear*)&JogMessage.Message)->v[a].f = (unsigned long)(dda & 0xFFFFFFFFuLL);
	Engine->Axis[a].Jogging = true;
  }
  MainPlanner->Jogging = true;
  Engine->Axis[axis].Jogging = true;
  tIDs[ G100.LastStored & 0x3f ] =  Engine->CurrentLineExec;;  //repeat until break by full message queue
  G100Mess->Add2Queue( &JogMessage);
  MainPlanner->ExternalStill = false;
  G100Mess->SendMessages();
  
}

void  MyJogOff(short axis)
{
   if( InitQueue != 0 ) return;
   if( G100.SEQUENCE != NOSEQ && G100.SEQUENCE != HOMEWAIT && G100.SEQUENCE != HOMEMOVEOFF) return; //were running some sequence in which jogging is not allowed. 
   G100Mess->DebugOut( "---- Jog Off --- \n" );
// Turn off the jog spped on this message..
  
  ((WTLinear*)&JogMessage.Message)->v[axis].i = 0; //stop this axis from jogging..
  ((WTLinear*)&JogMessage.Message)->v[axis].f = 0;
//and if its slaved, turn the slave off as well. 

  for( int a = 3; a<6; a++)
  if( Engine->Axis[a].Slave && Engine->Axis[a].SlaveAxis == axis )
  {
    ((WTLinear*)&JogMessage.Message)->v[a].i = 0;
    ((WTLinear*)&JogMessage.Message)->v[a].f = 0;
	Engine->Axis[a].Jogging = false;
  }
  tIDs[ G100.LastStored & 0x3f ] =  Engine->CurrentLineExec;;  //repeat until break by full message queue
  G100Mess->Add2Queue( &JogMessage);
 
  MainPlanner->ExternalStill = false;

  short check = 0;
  for( int x = 0; x<6; x++ )
  {
    if( ((WTLinear*)&JogMessage.Message)->v[x].i == 0 && ((WTLinear*)&JogMessage.Message)->v[x].f == 0) check ++;
  }
  Engine->Axis[axis].Jogging = false;
  if( check >= 6) //no axis jogging, lets do a sync..
  {
	  MainPlanner->Jogging = false;
	  Engine->Sync = true;
	  G100.InJog = false;
  }

}

double JogClipVel(short axis, double JogFeed)
{   //return allowable speed of this jog axis depending on Current Mavg settings..
	if( JogFeed > MainPlanner->Velocities[axis])
		JogFeed = MainPlanner->Velocities[axis];
	double ms =  JogFeed / MainPlanner->Acceleration[axis]; //seconds of accel time
	//ms is how long to speed up to the requested speed.
	ms = ms * 1024; //how many int's to get to this speed. 
	if( ms > ((double)G100.CurrentMavg)) //taks to long to get up to speed , slow it down..
	{
	 double per = ((double)G100.CurrentMavg)/ ms;
	 return per * JogFeed;
	}
	return JogFeed;
}

void JogSetMavg(int axis, double JogFeed)
{  //jogfeed should be feedrate in units/sec
   //ms will be acceleration time.. 
	double ms =  JogFeed / MainPlanner->Acceleration[axis]; //seconds of accel
	int nAvg = 512; //max of 1/2 second acceleration..
    if( ms <  .256 )
		nAvg = 256;
	if( ms < .128 )
		nAvg = 128;
	if( ms < .064 )
		nAvg = 64;
	if( ms < .032 )
		nAvg = 32;
	if( ms < .016 )
		nAvg = 16;
	if( ms < .008 )
		nAvg = 8;
	if( ms < .004 )
		nAvg = 4;

	if( G100.CurrentMavg != nAvg )
	{
	G100.CurrentMavg = nAvg;
	G100Mess->SetMessDef( &MoveMessage, WT_DWELL );
    MoveMessage.size = sizeof( WTDwell );
	((WTDwell*)&MoveMessage.Message)->FMsize = nAvg;
	((WTDwell*)&MoveMessage.Message)->RMsize = 0;
	((WTDwell*)&MoveMessage.Message)->m.T = 0;
	tIDs[ G100.LastStored & 0x3f ] =  Engine->CurrentLineExec;;  //repeat until break by full message queue;
	G100Mess->Add2Queue( &MoveMessage);
	}
}

// In a G100, any jogging must be repeated at least once every 250ms for safety
//this routime is called by the Message input receiver, every 250ms to keep the joggin moving..

void Rejog()
{
	if( InitQueue != 0 ) return;
    if( G100.WaitForState != NONE ) return;
    if( Engine->EStop)
	{
     for( int x = 0; x < 6; x++)
	 {
		 Engine->Axis[x].Homing = false;
		 Engine->Axis[x].DeRef = false;
		 MyJogOff(x);
	 }
	 G100.SEQUENCE = NOSEQ;
	 return;
	}
	//Dont rejogg if we have more than 2 messages in the queue, this would
	//likely mesn we already have rejoggs waiting..
	if( G100Mess->nMessages > 0 || G100.Window < 6) return;
    tIDs[ G100.LastStored & 0x3f ] =  Engine->CurrentLineExec;;  //repeat until break by full message queue
	G100Mess->Add2Queue( &JogMessage ); //just send the previous jog message
 

}

void  SendDwell(double time)
{
	G100Mess->SetMessDef( &MoveMessage, WT_DWELL );
    MoveMessage.size = sizeof( WTDwell );
	((WTDwell*)&MoveMessage.Message)->FMsize = 0;
	((WTDwell*)&MoveMessage.Message)->RMsize = 0;
	if( !MainPlanner->DwellMilli )
	  ((WTDwell*)&MoveMessage.Message)->m.T = (int) (time * 1024);
	else
      ((WTDwell*)&MoveMessage.Message)->m.T = (int) (time);

	tIDs[ G100.LastStored & 0x3f ] =  Engine->CurrentLineExec;;  //repeat until break by full message queue
	G100Mess->Add2Queue( &MoveMessage);

	Engine->DwellTime = 1; //holder to keep engine in dwell state while dwell is executed.
	G100.Dwelling = 1;
}

void  DoGcodeMove()
{
 if( InitQueue != 0 ) return;
 if( G100.WaitForState != NONE ) return;
 if( G100.InJog ) return;
 G100.CalcMavg = 64; //as a test we'll use 64ms Mavg on all Gcode moves. 
 if( Engine->TrajHead == Engine->TrajIndex || Engine->DwellTime > 0) return; //no moves to process
 if( G100Mess->QueueLeft() < 2 ) return; //Lets keep message traffic to 5 maximum

 if( G100.CurrentMavg != G100.CalcMavg && Engine->TrajHead != Engine->TrajIndex)
 {  //if Mavg is not set properly for the coming movement, set it now in a dwell message of 0 dwell
    G100Mess->SetMessDef(  &MoveMessage, WT_DWELL );
    MoveMessage.size = sizeof( WTDwell );
	((WTDwell*)&MoveMessage.Message)->FMsize = G100.CalcMavg;
	((WTDwell*)&MoveMessage.Message)->RMsize = 0;
	((WTDwell*)&MoveMessage.Message)->m.T = 0;
	tIDs[ G100.LastStored & 0x3f ] =  Engine->CurrentLineExec;;  //repeat until break by full message queue
	G100Mess->Add2Queue( &MoveMessage);
	G100.CurrentMavg = G100.CalcMavg;
    return;
 }
 while( !Engine->EStop ) //while were not Estopped.
 {
    if( Engine->TrajHead == Engine->TrajIndex ) return; //no moves to process, weve done them all
	if( G100Mess->QueueLeft() < 2 )  return; //Add up to 5 messages to the buffer at once.
	long long dda1[6];
	long long dda2[6];
	long long dda3[6];
	((WTCubic*)&Cubic.Message)->m.T = (int)MainPlanner->Movements[Engine->TrajIndex].Time; //32 ms normally, but can be anything less.

	for( int axis = 0; axis < 6; axis++ )
	{
	 uint64 tdda1 = (uint64) MainPlanner->Movements[Engine->TrajIndex].DDA1[axis];
	 if( axis == 0 )
		 int g = 9;
	 uint64 tdda2 = (uint64) MainPlanner->Movements[Engine->TrajIndex].DDA2[axis];
	 uint64 tdda3 = (uint64) MainPlanner->Movements[Engine->TrajIndex].DDA3[axis];
	 if(Engine->Directions[axis]) 
	 { 
		 tdda1 = -tdda1;
		 tdda2 = -tdda2;
		 tdda3 = -tdda3;
	 }
 	 MainPlanner->Movements[Engine->TrajIndex].DDA1[axis] = 0;
	 MainPlanner->Movements[Engine->TrajIndex].DDA2[axis] = 0;
	 MainPlanner->Movements[Engine->TrajIndex].DDA3[axis] = 0; //we now have all the DDA's we need for a cubic move.
	 
	 switch(G100.Config.axis[axis].divider  ) 
     {
     case (0): dda1[axis] = tdda1 ;      dda2[axis] = tdda2;       dda3[axis] = tdda3;     break; // 2**25 or 1 step at 4Mhz @ 64 ms..
     case (1): dda1[axis] = tdda1 * 2;   dda2[axis] = tdda2 * 2;   dda3[axis] = tdda3 * 2; break;  
     case (2): dda1[axis] = tdda1 * 4;   dda2[axis] = tdda2 * 4;   dda3[axis] = tdda3 * 4; break;    
     case (3): dda1[axis] = tdda1 * 8;   dda2[axis] = tdda2 * 8;   dda3[axis] = tdda3 * 8; break;  
     case (4): dda1[axis] = tdda1 * 16;  dda2[axis] = tdda2 * 16;  dda3[axis] = tdda3 * 16; break;    
     case (5): dda1[axis] = tdda1 * 32;  dda2[axis] = tdda2 * 32;  dda3[axis] = tdda3 * 32; break;
     case (6): dda1[axis] = tdda1 * 64;  dda2[axis] = tdda2 * 64;  dda3[axis] = tdda3 * 64; break; 
     case (7): dda1[axis] = tdda1 * 128; dda2[axis] = tdda2 * 128; dda3[axis] = tdda3 * 128; break;
     }
	 ((WTCubic*)&Cubic.Message)->d[axis].dda1.i = (signed long)(dda1[axis] >> 32);
	 ((WTCubic*)&Cubic.Message)->d[axis].dda1.f = (unsigned long)(dda1[axis] & 0xFFFFFFFFuLL);
     ((WTCubic*)&Cubic.Message)->d[axis].dda2.i = (signed long)(dda2[axis] >> 32);
	 ((WTCubic*)&Cubic.Message)->d[axis].dda2.f = (unsigned long)(dda2[axis] & 0xFFFFFFFFuLL);
	 ((WTCubic*)&Cubic.Message)->d[axis].dda3.i = (signed long)(dda3[axis] >> 32);
	 ((WTCubic*)&Cubic.Message)->d[axis].dda3.f = (unsigned long)(dda3[axis] & 0xFFFFFFFFuLL);

	 if( Engine->Axis[axis].Slave )//for slaving
     {
	  ((WTCubic*)&Cubic.Message)->d[axis].dda1.i = (signed long)  (dda1[Engine->Axis[axis].SlaveAxis] >> 32);
      ((WTCubic*)&Cubic.Message)->d[axis].dda1.f = (unsigned long)(dda1[Engine->Axis[axis].SlaveAxis] & 0xFFFFFFFFuLL);
	  ((WTCubic*)&Cubic.Message)->d[axis].dda2.i = (signed long)  (dda2[Engine->Axis[axis].SlaveAxis] >> 32);
      ((WTCubic*)&Cubic.Message)->d[axis].dda2.f = (unsigned long)(dda2[Engine->Axis[axis].SlaveAxis] & 0xFFFFFFFFuLL);
	  ((WTCubic*)&Cubic.Message)->d[axis].dda3.i = (signed long)  (dda3[Engine->Axis[axis].SlaveAxis] >> 32);
      ((WTCubic*)&Cubic.Message)->d[axis].dda3.f = (unsigned long)(dda3[Engine->Axis[axis].SlaveAxis] & 0xFFFFFFFFuLL);
     }
	}

	tIDs[ G100.LastStored & 0x3f ] =  Engine->Trajectories[Engine->TrajIndex].ID;  //repeat until break by full message queue
 
//lets put out a debug sting if enabled..
	CString out;
	out.Format( "Queuing Move to X %.4f, Y %.4f, Z %.4f Message %d \n" , 
		MainPlanner->Movements[Engine->TrajIndex].ex,
		MainPlanner->Movements[Engine->TrajIndex].ey,
		MainPlanner->Movements[Engine->TrajIndex].ez , G100.LastStored );
	G100Mess->DebugOut(  out );
	
	G100Mess->Add2Queue( &Cubic );
	if( MainPlanner->Movements[Engine->TrajIndex].Stop )
		 SendDwell(0); //exact stop if required.
	Engine->TrajIndex++;
	Engine->TrajIndex &= 0xfff;
 }

}