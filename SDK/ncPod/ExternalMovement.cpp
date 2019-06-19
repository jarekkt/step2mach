#include "stdafx.h"
#include "externalmovement.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "XMLProfile.h"
#include "ncPod.h"
#include "math.h"

 
extern TrajBuffer *Engine;  //Main Engine Block Variables
extern TrajectoryControl *MainPlanner;  //Trajectory Planner Vars. 
extern setup *_setup;   //RS274 Var block.
extern CMach4View *MachView;
extern ncPod *Pod;

extern int DripSel;
extern int HomingType;

#pragma warning( disable : 4305 )// truncation warnings..
#pragma warning( disable : 4309 )// "" ""

 
 


void GetInputs()
{
  for( int x = 0; x < nSigs; x++)
  {
	  if( Engine->InSigs[x].Active && 
		  Engine->InSigs[x].InPort == 1 &&
		  Engine->InSigs[x].InPin < 7 )
	  {
		  int pin = (Engine->InSigs[x].InPin+1);
		  if( pin == 6 ) 
			  pin = 7;
		  else 
			  if( pin == 7 ) 
				  pin = 6;
		  short i = (Pod->PodStatus.inio >> pin) &0x01;
		  short e =   Engine->InSigs[x].Negated ? 0:1; 
		  Engine->InSigs[x].Activated = i == e;

		  //check limits to trigger an Estop.
		  if( x < 18 && !( HomingType == 3 && Pod->SEQUENCE != PNOSEQ) )
		  {
		   if( Engine->InSigs[x].Activated && !Engine->EStop )
		   {
			   if( x == 2 || x == 5 || x == 8 || x == 11 ||
				   x == 14 || x == 17 ) continue;
			   if( !Engine->LimitsOff)
			   { 
				   Engine->EStop = true;
			       MyJogOff(0);
			   }
		   }
		  }

	  }

  }

  if( Engine->LimitsOff )
  {
	  bool limitson = true;
	  for( int x = 0; x < 18; x++)
	  {
         if( Engine->InSigs[x].Active && Engine->InSigs[x].Activated)
             limitson = false;
	  }
	  if( limitson ) 
	  {
		  Pod->SetMachError("Limits Re-engaged" );
		  Engine->LimitsOff = false;
	  }
  }





}


void SetOutputs()
{
  //query Mach for outpus required and send them to the device
  if(Engine->OffLine) return;  
  unsigned char out = 0;
  for( int x = 0; x < nSigsOut; x++)
  {
	  if( Engine->OutSigs[x].active && 
		  Engine->OutSigs[x].OutPort == 1 &&
		  Engine->OutSigs[x].OutPort < 8 )
	  {
		  if( Engine->OutSigs[x].Activated)
		  {
		     if( !Engine->OutSigs[x].Negated )
		         out |= 1 << ( Engine->OutSigs[x].OutPin + 3 ); //set the pin
		     else
			     out &= ~(  1 << ( Engine->OutSigs[x].OutPin + 3) ); //reset the pin
		  }
		  else
		  {
              if( Engine->OutSigs[x].Negated )
		         out |= 1 << ( Engine->OutSigs[x].OutPin + 3); //set the pin
		     else
			     out &= ~(  1 << ( Engine->OutSigs[x].OutPin + 3 ) ); //reset the pin

		  }
		  
	  }

  }
  if( out != Pod->PodStatus.outio ) 
  {
	//   axisX: mask
    //   axisY: value of output signals
	Pod->ClearCommand();
	Pod->Command.axisX = 0xff;
	Pod->Command.axisY = out;
	Pod->SendSimpleCommand( (char)USBOUTPUT );
  }

}



void HandleSequences()
{
 int temp;
 
  if( !MainPlanner->ExternalStill ) return;
  if( Pod->WaitForMove > 0 )
  {
	  Pod->WaitForMove--;
	  return;
  }

  switch( Pod->SEQUENCE )
  {
  case( PNOSEQ ): break;
  case( PHOMING ):
	  
	      //set the coordinates to zero for now..
		  if( MainPlanner->m_MutiHome)
		  {
			  for( int x = 0; x < 6; x++)
				  if(( Pod->HomeAxis >> x) & 0x01 )
				  {
					  
					  Engine->Axis[x].Index = Engine->RefCounts[0];
				  }
		  }
		  else
		  {
		    Engine->Axis[Pod->HomeAxis].Index = Engine->RefCounts[Pod->HomeAxis];
  	      }
		  Pod->ClearCommand();
		  Pod->Command.axisX = Engine->Axis[0].Index * (Engine->Directions[0] ? 1: -1);
		  Pod->Command.axisY = Engine->Axis[1].Index * (Engine->Directions[1] ? 1: -1);
		  Pod->Command.axisZ = Engine->Axis[2].Index * (Engine->Directions[2] ? 1: -1);
		  Pod->Command.axisA = Engine->Axis[3].Index * (Engine->Directions[3] ? 1: -1);
		  Pod->Command.axisB = Engine->Axis[4].Index * (Engine->Directions[4] ? 1: -1);
		  Pod->Command.axisC = Engine->Axis[5].Index * (Engine->Directions[5] ? 1: -1);
		  Pod->Command.loc = 0x3f;
		  if( !Engine->OffLine)  Pod->SendSimpleCommand(USBSETCOORDSXYZABC);
		  //so now this home is on the switch, any others?
		  //lets gang them up so they all go though..
		  if( HomingType == 1 ) //stop after hitting switch if only stage 1 homing.
		  {
			  Pod->SetDrip();
	          MainPlanner->SoftWait &=  ( 0xffffffffffffffff ^ ( ((__int64)1) << EXHOME)); //turn off home wait..
	          Engine->Homing = false;
	          Engine->Sync = true;  //turn off the homing , this sequence is done..
	          Pod->SEQUENCE = PNOSEQ;
	 	  }
		  else
		  Pod->SEQUENCE = PHOMING2;
	   
	  break;
  case( PHOMING2 ):
	  //next stage of the homing..
	  if( Engine->Sync ) return; //test fix
	  Pod->HomeDeRef();  //Jog off the switch/// 
	  MainPlanner->ExternalStill = false;
	  Pod->WaitForMove = 5;
	  Pod->SEQUENCE = PHOMING3;
	  break;	

   case( PHOMING3 ):

	   Pod->Home(  Pod->HomeAxis , true); //rehome
	   Pod->SEQUENCE = PHOMING31;
	   Pod->WaitForMove = 5;
	  break;

   case( PHOMING31 ):

	   if( Engine->Sync ) return; //test fix
	   Pod->HomeDeRef();  //Jog off the switch/// 
	   MainPlanner->ExternalStill = false;
	   Pod->SEQUENCE = PHOMING4;
	   Pod->WaitForMove = 5; 
	   break;

   case( PHOMING4 ):
	  //next stage of the homing..
	   if( MainPlanner->m_MutiHome)
		  {
			  for( int x = 0; x < 6; x++)
				  if(( Pod->HomeAxis >> x) & 0x01 )
				  {
					  Engine->Referenced[x ] = true;
					  Engine->Axis[x].Index = Engine->RefCounts[x];
				  }
					   
		  }
		  else
		  {
		      Engine->Referenced[ Pod->HomeAxis ] = true;
			  Engine->Axis[Pod->HomeAxis].Index = Engine->RefCounts[Pod->HomeAxis];

		  }
	  Pod->ClearCommand();
	  Pod->Command.axisX = Engine->Axis[0].Index * (Engine->Directions[0] ? 1: -1);
	  Pod->Command.axisY = Engine->Axis[1].Index * (Engine->Directions[1] ? 1: -1);
	  Pod->Command.axisZ = Engine->Axis[2].Index * (Engine->Directions[2] ? 1: -1);
	  Pod->Command.axisA = Engine->Axis[3].Index * (Engine->Directions[3] ? 1: -1);
	  Pod->Command.axisB = Engine->Axis[4].Index * (Engine->Directions[4] ? 1: -1);
	  Pod->Command.axisC = Engine->Axis[5].Index * (Engine->Directions[5] ? 1: -1);
	  Pod->Command.loc = 0x3f;
	  if( !Engine->OffLine)   Pod->SendSimpleCommand(USBSETCOORDSXYZABC);
	  Pod->SetDrip();
	  MainPlanner->SoftWait &=  ( 0xffffffffffffffff ^ ( ((__int64)1) << EXHOME)); //turn off home wait..
	  Engine->Homing = false;
	  Engine->Sync = true;  //turn off the homing , this sequence is done..
	  Pod->SEQUENCE = PNOSEQ;
	  
	  break;

   case( PDWELL ): temp = GetTickCount() - Pod->DwellTick;
		              if( temp > Pod->DwellTarget ) 
					  {
						  Pod->SEQUENCE = PNOSEQ;
						  Engine->DwellTime = 0;
					  }
					  break;
					
   case( PPROBE ):  	  
	   
		   //get the data of what the probe location was..
		    _setup->parameters[2000] = - Pod->PodStatus.ProbexAxis;
		    _setup->parameters[2001] = - Pod->PodStatus.ProbeyAxis;
		    _setup->parameters[2002] = - Pod->PodStatus.ProbezAxis;
		    _setup->parameters[2003] = - Pod->PodStatus.ProbeaAxis;
		   
		   Engine->Sync = true;
		   Engine->Axis[0].Probing = false;
		   Pod->SEQUENCE = PNOSEQ;
	       break; // 
	 

  }

}

void myDwell( double time)
{
	if( !MainPlanner->DwellMilli ) time = time * 1000; 
	
	Pod->DwellTarget = (int)( time );
	Engine->DwellTime = 1;
	Pod->DwellTick = GetTickCount();
	Pod->SEQUENCE = PDWELL;
}

void MyJogOn( short axis, short direction, double SpeedNorm)
{

   if( Engine->OffLine )return;
   if( Engine->EStop )
	{
       Pod->SetMachError( "No Jogging in Estop!!" ); 
	   return;
	}
	if( Pod->SEQUENCE != PNOSEQ)
	{
     Pod->SetMachError( "Waiting for sequence to End!" ); 
     return;

	}
	if( Engine->TrajHead != Engine->TrajIndex ) return;
	if( Engine->Jogging ) return;

    double JogFeed = (MainPlanner->Velocities[axis]); //rapid steps per second
    // JogSpeed OverRide. (Used in Velocity mode of MPG jog.) ?
    if( SpeedNorm != 0 ) JogFeed = SpeedNorm;
    //Keyboard Shift key is on?
    // If shift is not on, then JogPercent is the speed to use. 
   if( !(*MachView->m_ShiftState) && SpeedNorm == 0) 
            JogFeed = (JogFeed * _setup->JogPercent / 100); //JogSteps/Sec..

   double vel = (int)( JogFeed * MainPlanner->StepsPerAxis[axis]);
   Pod->ClearCommand();

   //this isnt right..
  // double moveaccel = 75 / (MainPlanner->Velocities[axis] / MainPlanner->Acceleration[axis]);

   //Pod->Command.axisX = (int)moveaccel;
   //Pod->SendSimpleCommand( USBSETINDEPENDENTACCEL );


   Pod->ClearCommand();
   switch( axis)
   {
   case( 0 ): Pod->Command.axisX = (int) ((MainPlanner->Acceleration[0] * MainPlanner->StepsPerAxis[ 0])* 32.767) / 75000;   break;
   case( 1 ): Pod->Command.axisX = (int) ((MainPlanner->Acceleration[1] * MainPlanner->StepsPerAxis[ 1])* 32.767) / 75000;   break;
   case( 2 ): Pod->Command.axisX = (int) ((MainPlanner->Acceleration[2] * MainPlanner->StepsPerAxis[ 2])* 32.767) / 75000;   break;
   case( 3 ): Pod->Command.axisX = (int) ((MainPlanner->Acceleration[3] * MainPlanner->StepsPerAxis[ 3])* 32.767) / 75000;   break;
   case( 4 ): Pod->Command.axisX = (int) ((MainPlanner->Acceleration[4] * MainPlanner->StepsPerAxis[ 4])* 32.767) / 75000;   break;
   case( 5 ): Pod->Command.axisX = (int) ((MainPlanner->Acceleration[5] * MainPlanner->StepsPerAxis[ 5])* 32.767) / 75000;   break;

   } 


   Pod->SendSimpleCommand( USBSETINDEPENDENTACCEL );
/*
   Pod->ClearCommand(); //orignal code.
   Pod->Command.axisX = (int) ((MainPlanner->Acceleration[0] * MainPlanner->StepsPerAxis[ 0])* 32.767) / 75000;  
   Pod->Command.axisY = (int) ((MainPlanner->Acceleration[1] * MainPlanner->StepsPerAxis[ 1])* 32.767) / 75000;  
   Pod->Command.axisZ = (int) ((MainPlanner->Acceleration[2] * MainPlanner->StepsPerAxis[ 2])* 32.767) / 75000;  
   Pod->Command.axisA = (int) ((MainPlanner->Acceleration[3] * MainPlanner->StepsPerAxis[ 3])* 32.767) / 75000;   
   Pod->Command.axisB = (int) ((MainPlanner->Acceleration[4] * MainPlanner->StepsPerAxis[ 4])* 32.767) / 75000;   
   Pod->Command.axisC = (int) ((MainPlanner->Acceleration[5] * MainPlanner->StepsPerAxis[ 5])* 32.767) / 75000;   

   Pod->SendSimpleCommand( USBSETINDEPENDENTACCEL );
*/

   Pod->ClearCommand();
  
   bool SoftLimit = Engine->SoftLimitEnable;
   double maxdist = -999999;//They are reversed because the pod takes a negitive number to go positive!
   double mindist = 999999;
   if( SoftLimit)
   {
      switch( axis )
	  {
 	  case(0):  maxdist = (MainPlanner->MXPosition * MainPlanner->StepsPerAxis[0]) - Engine->SoftLimitsHi[0];
		        mindist = (MainPlanner->MXPosition * MainPlanner->StepsPerAxis[0]) - Engine->SoftLimitsLo[0];  
		        break;
	  case(1):  maxdist = (MainPlanner->MYPosition * MainPlanner->StepsPerAxis[1]) - Engine->SoftLimitsHi[1];
		        mindist = (MainPlanner->MYPosition * MainPlanner->StepsPerAxis[1]) - Engine->SoftLimitsLo[1]; 
		        break;
	  case(2):  maxdist = (MainPlanner->MZPosition * MainPlanner->StepsPerAxis[2]) - Engine->SoftLimitsHi[2];
		        mindist = (MainPlanner->MZPosition * MainPlanner->StepsPerAxis[2]) - Engine->SoftLimitsLo[2]; 
		        break;
	  case(3):  maxdist = (MainPlanner->MAPosition * MainPlanner->StepsPerAxis[3]) - Engine->SoftLimitsHi[3];
		        mindist = (MainPlanner->MAPosition * MainPlanner->StepsPerAxis[3]) - Engine->SoftLimitsLo[3];    
		        break;
	  case(4):  maxdist = (MainPlanner->MBPosition * MainPlanner->StepsPerAxis[4]) - Engine->SoftLimitsHi[4];
		        mindist = (MainPlanner->MBPosition * MainPlanner->StepsPerAxis[4]) - Engine->SoftLimitsLo[4];      
		        break;
	  case(5):  maxdist = (MainPlanner->MCPosition * MainPlanner->StepsPerAxis[5]) - Engine->SoftLimitsHi[5];
		        mindist = (MainPlanner->MCPosition * MainPlanner->StepsPerAxis[5]) - Engine->SoftLimitsLo[5];      
		        break;
	  }
	  
   }
    if( Engine->Directions[ axis ] ) 
	  {
		  maxdist *= -1;
		  mindist *= -1;
	  }
   int dist = (int)((direction == 0) ? maxdist : mindist);

      switch( axis )
   {
       case (0) : Pod->Command.axisX = dist; break;
	   case (1) : Pod->Command.axisY = dist; break;
       case (2) : Pod->Command.axisZ = dist; break;
	   case (3) : Pod->Command.axisA = dist; break;
	   case (4) : Pod->Command.axisB = dist; break;
	   case (5) : Pod->Command.axisC = dist; break;
   }
   for (int x = 3; x < 6; ++x)
		if (Engine->Axis[x].Slave && Engine->Axis[x].SlaveAxis == axis) 
		{
			switch( x )
			{
			  case( 3): Pod->Command.axisA = dist; break;
			  case( 4): Pod->Command.axisB = dist; break;
			  case( 5): Pod->Command.axisC = dist; break;
			}
		}
   Pod->Command.velocity = (int)vel;
   Pod->SendSimpleCommand(USBRELATIVELINEARPOSITIONMOVEXYZABC);
   Engine->Jogging = true;  
}

void  MyJogOff(short axis)
{
	if( !Engine->Jogging ) return;
	Engine->Jogging = false;
	Pod->ClearCommand();
	Pod->SendSimpleCommand((char) USBFINISHMOVE );
	Engine->Sync = true;

}

void myReset()
{
	
	if( Pod == 0 ) 
	{
 	   Pod = new ncPod();
 	   if( Pod != 0) Pod->DripSel = DripSel;
       if( !Pod->Connect())
       {
		 AfxMessageBox( "No Pod Detected");
	     delete Pod;
	     Pod = NULL;
		 return;
      }
   }
	Pod->nHolding = 0;
	MainPlanner->SoftWait = 0;
	Pod->nHomePos = 0;
	Engine->Homing = false;
	if( !Pod->Connection.Connected ) Pod->Open();
	Pod->BufferHolding = false;
    Pod->SEQUENCE = PNOSEQ;
if( !Engine->EStop) //switching to safe mode.
	{
    Pod->ClearCommand();
    Pod->SendSimpleCommand( USBRESETESTOPSWITCH ); //just in case..
	//now lets set the position in the pod to the exact position of the software index. 
	Pod->SendSimpleCommand(USBRESET);
	Pod->ClearCommand();
	Pod->Command.commandEnum = USBSETCOORDSXYZABC;
	Pod->Command.axisX = Engine->Axis[0].Index * (Engine->Directions[0] ? 1: -1);
	Pod->Command.axisY = Engine->Axis[1].Index * (Engine->Directions[1] ? 1: -1);
	Pod->Command.axisZ = Engine->Axis[2].Index * (Engine->Directions[2] ? 1: -1);
	Pod->Command.axisA = Engine->Axis[3].Index * (Engine->Directions[3] ? 1: -1);
	Pod->Command.axisB = Engine->Axis[4].Index * (Engine->Directions[4] ? 1: -1);
	Pod->Command.axisC = Engine->Axis[5].Index * (Engine->Directions[5] ? 1: -1);
	Pod->Command.loc = 0x3f;
    Pod->SendCommand( );
	//And back to dripfeed.
	Pod->ClearCommand( );
    Pod->SendSimpleCommand( USBDRIPFEED );
	}
else
{ //an estop is requested..
  Pod->SendSimpleCommand(USBESTOP);
  //diag code
  Pod->fractions[0] = 0; 
  Pod->cCount[0] = 0;
  Pod->vtotal[0] = 0;
  Pod->total[0] = Pod->PodStatus.fullStepsX;
  Pod->ClearCommand();
  Pod->Command.commandEnum = USBOUTPUT_PWM;
  double vel = 0;
  Pod->Command.loc = 400; //send a new PWM duty cycle..
  Pod->SendCommand();

}

}

void SetPositions()
{
	if( Pod->PodStatus.statusMode != STATMODERUN )
		int g = 9;

	if( 0 )//Pod->PodStatus.statusMode != STATMODERUN && Pod->PodStatus.statusMode != STATMODEDEBUG) 
	{
		if( Pod->PodStatus.statusMode == STATMODEPROBE )
		{
			Pod->ProbeX = Pod->PodStatus.fullStepsX;
			Pod->ProbeY = Pod->PodStatus.fullStepsY;
			Pod->ProbeZ = Pod->PodStatus.fullStepsZ;
			Pod->ProbeA = Pod->PodStatus.fullStepsA;
			Pod->ProbeB = Pod->PodStatus.fullStepsB;
			Pod->ProbeC = Pod->PodStatus.fullStepsC;
            Pod->ProbeRead = true;
		}
		return;
	}

	Engine->Axis[0].Index = Pod->PodStatus.fullStepsX;
	Engine->Axis[1].Index = Pod->PodStatus.fullStepsY;
	Engine->Axis[2].Index = Pod->PodStatus.fullStepsZ;
	Engine->Axis[3].Index = Pod->PodStatus.fullStepsA;
	Engine->Axis[4].Index = Pod->PodStatus.fullStepsB;
	Engine->Axis[5].Index = Pod->PodStatus.fullStepsC;

}

 
int  buffcount = 0;

void SendHoldingMovement()
{
 static int x = 0;
 if( !Pod->Connection.Connected ) return;
 if( Pod->Holding == 10 ) 
 {
	 CString err;
	 err.Format( "Buffer held 1 Second.. %d times attempted. Terminating Hold..", Pod->Holding );
	 Pod->SetMachError(err);
	 Pod->Holding = 0;
	 Pod->BufferHolding = false;
 }
 if( Pod->BufferHolding ) 
 {
	 Pod->SendEP1Command();
	 return;
 }
 if( Engine->TrajHead == Engine->TrajIndex ) {  return; }

 //Pod->ClearCommand( );
 //Pod->SendSimpleCommand( USBDRIPFEED );
 
 if( Engine->EStop ) return;

 int left = Engine->TrajHead - Engine->TrajIndex;
 if( left < 0 ) left += 4096;
 if( left < 32 && !MainPlanner->BufferEnding) //the buffer is filling, but isnt up to one block as yet..
	 return;

 Send512Block(); //send 128ms of data out. We'll do this at 50hz, that should be fast enough at 4ms or 2ms.. 
 if( Engine->TrajHead == Engine->TrajIndex &&  MainPlanner->BufferEnding )
	 Pod->SendSimpleCommand( SDFLUSHBUFFER );

}

void  Send512Block()
{
	

	unsigned char *SDBuffer = &(Pod->bufferout[0]);
    short bc = 0; //buffer count
	memset( SDBuffer, 0, sizeof(char) * 512 ); //first clear the buffer //FIXME was 0
    for( int x = 0; x < 32; x++ )
	{
		short index = Engine->TrajIndex;
		SDBuffer[bc++] = (char)SDVELOCITYMOVE;
		int line =       Engine->Trajectories[index].ID;
        SDBuffer[bc++] = (line >> 16) & 0xff;
        SDBuffer[bc++] = (line >> 8 ) & 0xff;
		SDBuffer[bc++] = line & 0xff;

		short *buff = (short*) &SDBuffer[bc];
		short off = 0;
		short snum[6];
		double d;
		 
		d = ((((double)((MainPlanner->Movements[index].ex) * 32768) / Pod->DripTime))+ Pod->fractions[0]) * ((Engine->Directions[0]== 0) ? -1.0 : 1.0);
 		snum[0] = (short)d;
		if( d >= 0 ) Pod->fractions[0] = d - floor(d);// - (double)snum[0];
		else
			Pod->fractions[0] = -(ceil(d) - d);
		
		Pod->vtotal[0] += snum[0];
		Pod->vtotal[1] += (__int64)(MainPlanner->Movements[index].ex);


		d = ((((double)((MainPlanner->Movements[index].ey) * 32768) / Pod->DripTime))+ Pod->fractions[1]) * ((Engine->Directions[1]== 0) ? -1.0 : 1.0);
		snum[1] = (short)d;

		if( d >= 0 ) Pod->fractions[1] = d - floor(d);// - (double)snum[0];
		else
			Pod->fractions[1] = -(ceil(d) - d);
		
		d = ((((double)((MainPlanner->Movements[index].ez) * 32768) / Pod->DripTime))+ Pod->fractions[2]) * ((Engine->Directions[2]== 0) ? -1.0 : 1.0);
		snum[2] = (short)d;
		if( d >= 0 ) Pod->fractions[2] = d - floor(d);// - (double)snum[0];
		else
			Pod->fractions[2] = -(ceil(d) - d);

		d = ((((double)((MainPlanner->Movements[index].ea) * 32768) / Pod->DripTime))+ Pod->fractions[3]) * ((Engine->Directions[3]== 0) ? -1.0 : 1.0);
		snum[3] = (short)d;
		if( d >= 0 ) Pod->fractions[3] = d - floor(d);// - (double)snum[0];
		else
			Pod->fractions[3] = -(ceil(d) - d);


		d = ((((double)((MainPlanner->Movements[index].eb) * 32768) / Pod->DripTime))+ Pod->fractions[4]) * ((Engine->Directions[4]== 0) ? -1.0 : 1.0);
		snum[4] = (short)d;
		if( d >= 0 ) Pod->fractions[4] = d - floor(d);// - (double)snum[0];
		else
			Pod->fractions[4] = -(ceil(d) - d);


		d = ((((double)((MainPlanner->Movements[index].ec) * 32768) / Pod->DripTime))+ Pod->fractions[5]) * ((Engine->Directions[5]== 0) ? -1.0 : 1.0);
		snum[5] = (short)d;
		if( d >= 0 ) Pod->fractions[5] = d - floor(d);// - (double)snum[0];
		else
			Pod->fractions[5] = -(ceil(d) - d);

		//slaving check
		for (int x = 3; x < 6; ++x)
		if (Engine->Axis[x].Slave ) 
		{
			 snum[x] = snum[Engine->Axis[x].SlaveAxis];
		} //end of slaving ..

	
        buff[off++] = snum[0]; 
		buff[off++] = snum[1];
		buff[off++] = snum[2]; 
		buff[off++] = snum[3];
		buff[off++] = snum[4]; 
		buff[off++] = snum[5]; 

		if( Engine->OffLine)
		{
			Engine->Axis[0].Index = snum[0];
			Engine->Axis[0].Index = snum[1];
			Engine->Axis[0].Index = snum[2];
			Engine->Axis[0].Index = snum[3];
			Engine->Axis[0].Index = snum[4];
			Engine->Axis[0].Index = snum[5];
		}
		//now bytes buff[0] - [12] need to be reversed..
        unsigned char *rev = &SDBuffer[bc];
		char temp;
		for( int y = 0; y < 6; y++)
		{
		 temp = *rev;
         *rev = *(rev+1);
		 *(rev+1) = temp;
         rev = rev +2;
		}
        bc += 12; //sync the counters
  	    Engine->TrajIndex++;
	    Engine->TrajIndex &= 0xfff; //lock the ring.    
		if( Engine->TrajIndex == Engine->TrajHead) 
			break;
	}
	//now we have up to 32 commands ready to go..
	if( !Engine->OffLine)
		Pod->SendEP1Command(  );

	
	

}
 








