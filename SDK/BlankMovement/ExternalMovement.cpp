#include "stdafx.h"
#include "externalmovement.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "XMLProfile.h"
 
 
extern TrajBuffer *Engine;  //Main Engine Block Variables
extern TrajectoryControl *MainPlanner;  //Trajectory Planner Vars. 
extern setup *_setup;   //RS274 Var block.
extern CMach4View *MachView;
  
 


void GetInputs()
{
	
	//get inputs from the device and set them in Mach3s variables..
	
	
}


void SetOutputs()
{
  //query Mach for outpus required and send them to the device

}

void SendHoldingMovement()
{
	  

 if( Engine->TrajHead != Engine->TrajIndex) //if these ring buffer pointers are not equal, we have movement waiting..
 {  //if Mavg is not set properly for the coming movement, set it now in a dwell message of 0 dwell

  while ( Engine->TrajHead != Engine->TrajIndex )
  {
   //we will now loop though the moves that are holding.. 
   GMoves move =  MainPlanner->Movements[Engine->TrajIndex];
   //you must deal with this "move" , then increment the ring buffer and so forth till no more moves exist.





   Engine->TrajIndex++;  //increment ring
   Engine->TrajIndex &= 0xfff; //rotate the ring if necessary..
  }
 }
   	
	
}

void HandleSequences()
{
  //handle any sequenctial logic from int to int you may use..


}

void myDwell( double time)
{
   //for dwelling
	 
}

void MyJogOn( short axis, short direction, double SpeedNorm)
{
   //turn on a jog in thos routine..
  
  
}

void  MyJogOff(short axis)
{
  int check = 0;
  Engine->Axis[axis].Dec = true;
  Engine->Axis[axis].Jogging = false;
  for( int x = 0; x<6; x++ )
  {
    if( !Engine->Axis[x].Jogging ) check ++;
  }
  if( check >= 6) //no axis jogging, lets do a sync..
  {
	  Engine->Jogging = false;
	  MainPlanner->Jogging = false;
	  Engine->Sync = true;
  }

}




 