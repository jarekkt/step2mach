// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------


#include "stdafx.h"
#include "assert.h"
#include "MyDevice.h"


using namespace System::Text;

MyDeviceClass::MyDeviceClass()
{
	// Just to put data on simple console window
	console		= NULL;
	hardware	= NULL;
	ReadyForRun = 0;

	memset(&stats,0,sizeof(stats));

	InMotion			= 0; 
	WaitForGcodeIdle	= 0;
	WaitForJogIdle		= 0;

	DwellTimestamp		= 0;
    DwellDelay			= 0;

	
	JogAxis				= -1;
    JogFeed				= 0;
    JogVel				= 0;
    JogAcc				= 0;
	JogDistance			= 0;


	HomeAxis			  = -1;
	HomePin				  = 0;
	HomeSignal			  = -1;
	HomeVel				  = 0;
	HomeAcc				  = 0;
	HomeMask			  = 0;
	HomeMaskValActive	  = 0;
	HomeMaskValInActive	  = 0;
	HomeDistance		  = 0;

	
	OutputValid			  = 0;
	OutputCurrent		  = 0;
	OutputMaskCurrent     = 0;

	sequence			= SEQ_IDLE;

}

MyDeviceClass::~MyDeviceClass()
{
	if(hardware != NULL)
	{
		delete hardware;
	}

	if(console != NULL)
	{
		delete console;
	}
}


void  MyDeviceClass::InitControl()
{
	// Comment from "art"
	//
	//		Take note you have to set MachView->m_PrinterOn = false in the myInitControl function to indicate an external device plugin
	//		as well as have set MainPlanner->ExternalType = EX_VMS; for variable ms timing, 
	//		and set the MainPlanner->ExTime == .001 for 1ms timed waypoints..
	//		Then, you have to set the axis maximums , then motor tuning can work..
	//		This woudl set the max to 75K steps/second for example.. The user can then tune the motors with the motor tuning..
	//			for( int x = 0; x < 7; x++ )MainPlanner->ExternalPulseRates* = 75000;
	//
	//		Now if you command a move, the positions will be in the RingBuffer at
	//		MainPlanner->Movements[Engine->TrajIndex].sx;   sy,sz..ect..
	//		I believe the ncPod plugin shows incremental motion from the .ex, .ey, .ez var's, and the sx, sy, sz vars show absolute position..


	// We do not use printer port - we are its replacement
	MachView->m_PrinterOn = false;

	// This seems to be movement buffer length ( in movements)
	MainPlanner->ExBufferHi		= 450;

	// This seems to be single movement length ( in seconds)
	//
	// Comment from "smurph" :
	//		1ms may be putting the trajectory planner through too much.  Or dumping that much granular data to your device may be the bottle neck. 
	//		I've run some of my plugins at 32ms.  But I had the capability of matching that time slice in the hardware.  
	//		The reduced resolution is only noticed at very slow speeds. 
	//		You will never notice anything with a time slice of 16ms or lower.  So if 1ms is not a requirement, try some higher values.  
	//		The Galil plugin uses 4ms time slices and it flies


	MainPlanner->ExTime			= MOTION_TIME_SLICE;


	//  Comment from "smurph" :
	//		Movement type:
	// 			EX_VMS: This is basically what would have been sent to the parallel port.  It is incremental position over time.
	//			EX_COMMAND:  This might be what you would like to use.  Where you send endpoint data to the device.  It uses the GMoves and GMoves1 structures to provide data.  But it eliminates Mach directing things that I described above.
	//			EX_DDA:  That was basically only used to output cubic profile data to the G100 GRex.  It's probably not useful for any other device.
	//
	//  I choose EX_VMS so Mach trajectory planner will make all calculations for us

	MainPlanner->ExternalType	= EX_VMS; 


	//  Setup external pulse rate
	//  Set the max speeds of MAch3 for this device
	//
	//	This has to match your hardware capablities

	for( int x = 0; x < 7; x++ )
	{
		MainPlanner->ExternalPulseRates[x] = HARDWARE_FREQ;
	}

}


//	From GALIL plugin example:
//
//		Called when mach fully set up so all data can be used but initialization  outcomes not affected
//		In the case of a MotionControl plugin, this rouine is only called to tell us to 
//		take over. We HAVE been selected and are now commanded to do whatever it takes 
//		to OWN the IO and movement of this run.
//		If you wish for example, to zero all IO at this point, your free to do so..


void  MyDeviceClass::Reconfigure(std::string ip_address,bool debug_mode)
{
	
	// Initialize hardware
	if( hardware == NULL)
	{
		hardware = new MyHardwareClass(MOTION_TIME_SLICE,ip_address.c_str());
	}
	else
	{
		// Reinit hardware - in case of different address
		if(dev_ip_addr != ip_address)
		{
			delete hardware;
			hardware = new MyHardwareClass(MOTION_TIME_SLICE,ip_address.c_str());
		}
	}
	dev_ip_addr = ip_address;


	if(debug_mode == true)
	{
		if(console == NULL)
		{
			// Initialize debug console
			console  = new MyConsoleClass;
			console->ConsolePrint(0,0,"Step2Mach plugin activated");
		}
	}
	else
	{
		if(console != NULL)
		{
			delete console;
			console = NULL;
		}
	}

	SetMachError("Starting Step2Mach plugin");
	Reset();

	ReadyForRun = 1;
}





// 
//	Main update loop at 10hz.
//	Called only when plugin enabled
//
void  MyDeviceClass::Update()
{
	int				coords[4];
	
	// Make sure we are initialized
	if(ReadyForRun != 0)
	{
		// Get postion from the device
		if(hardware->ReadDeviceFeedback(coords) == 0)
		{
			Engine->Axis[0].Index = coords[0];
			Engine->Axis[1].Index = coords[1];
			Engine->Axis[2].Index = coords[2];
			Engine->Axis[3].Index = coords[3];
		}
		else
		{
			// Data link is broken !! Fatal error
			if(!Engine->EStop )
			{
				Engine->EStop = true;
				SetMachError("Step2Cnc communication error!!");
			}
		}

		// Process movements
		SendHoldingMovement();

		// Process inputs
		GetInputs();

		// Process outputs
		SetOutputs();

		// Process sequences ( state machines )
		HandleSequences();

		// Some debug info
		DumpConfig();
	}

}



//
//	Here we process Mach trajector and send movements to the device
//
// 
void  MyDeviceClass::SendHoldingMovement()
{
	unsigned int line_num;


	 // Highest priority event - ESTOP
	 // Do not operate in such case 
	 if( Engine->EStop )
	 {
		return;
	 }

	 //If these ring buffer pointers are not equal, we have movement waiting..
	 if( Engine->TrajHead != Engine->TrajIndex) 
	 {  
	 
		  //if Mavg is not set properly for the coming movement, set it now in a dwell message of 0 dwell
		  while ( Engine->TrajHead != Engine->TrajIndex )
		  {
			stats.TrajectoryItems++;
		
			//We will now loop though the moves that are holding.. 
			GMoves move =  MainPlanner->Movements[Engine->TrajIndex];

			//you must deal with this "move" , then increment the ring buffer and so forth till no more moves exist.
			if( hardware->AddMove(move.ex,move.ey,move.ez,move.ea,Engine->Trajectories[ Engine->TrajIndex ].ID )  != 0)
			{
				// Hardware buffers full, do not accept new moves
				break;
			}

			Engine->TrajIndex = (Engine->TrajIndex + 1) & 0xfff;
			InMotion = 1;
		  }
	 }
	 else
	 {
		// Unusual. Device queues are empty and no more trajectory data.
		// This happens e.g. when somebody stops the program in the middle
		// I would like to know better way to find it...
		if(hardware->IsIdle())
		{
			WaitForGcodeIdle = 1;
		}
	 }
	

	 // Update current line info from device status feeddback
	 // Not valid when jogging or homeing (as we run our own sequences and hardware->GetLineId() gives our internal id's, not line numbers
	 if( (Engine->Jogging	== false) && (Engine->Homing == false))
	 {
		 line_num = hardware->GetLineId();
		 if(line_num != 0xFFFFFFFF) 
		 {
			Engine->DisplayLine = line_num;
		 }
	 }


	 if( (Engine->TrajHead == Engine->TrajIndex) &&  MainPlanner->BufferEnding )
	 {
		// No more data ? We should Mach that we have finished, but we may still have some 
		// movement in buffers. Wait until device reports end of operation
		if(InMotion != 0)
		{
			WaitForGcodeIdle = 1;
		}
	 }


}

//
//	Get inputs from the device and set them in Mach3s variables..
//
//
void MyDeviceClass::GetInputs(void)
{
   int  x;
   unsigned int  hw_input;

   // Get input state to local variable
   hw_input = hardware->GetInputs();

   // First put first 32 inputs in an integer. 
   // Check all signals from 0 to max number of signals.
   for(x = 0; x< nSigs; x++) 
   {
		if( (Engine->InSigs[x].Active) && (Engine->InSigs[x].InPort == 1 )) //if this signal is turned on, and its set to port #1..check it..
		{			
           if(( hw_input  >> (Engine->InSigs[x].InPin -1  ) ) & 0x01 ) // if the nth (pin number) bit is active..
		   {
			   Engine->InSigs[x].Activated = !Engine->InSigs[x].Negated; //set it high or low depending on the "low active"..
		   }
		   else
		   {
			   Engine->InSigs[x].Activated = Engine->InSigs[x].Negated; //setting..
		   }
     	}

	}
}



//
//	Query Mach for outpus required and send them to the device
//
//
void MyDeviceClass::SetOutputs(void)
{
	int x;

	unsigned int  hw_output = 0;
	unsigned int  hw_mask = 0;

	// Check all signals from 0 to max number of signals.
	for( x = 0; x< nSigsOut; x++) 
	{		
		//If this signal is turned on, and its set to port #1..check it..
		if( (Engine->OutSigs[x].active)  && (Engine->OutSigs[x].OutPort == 1) && (Engine->OutSigs[x].OutPin < 18 )) 
		{
		   bool Should = Engine->OutSigs[x].Activated;


		   hw_mask |= 1 << (Engine->OutSigs[x].OutPin-1);

		   if( Should ) 
		   {
			  //we are activated..
			  Should = !Engine->OutSigs[x].Negated;
			  if (Should)
			  {
				hw_output |= 1 << (Engine->OutSigs[x].OutPin-1);
			  }
			  else
			  {
				 hw_output &=  0xffff ^ (1 << (Engine->OutSigs[x].OutPin-1));
			  }
		   }
		   else
		   {
		      //we are inactive
			  Should = Engine->OutSigs[x].Negated;
			  if (Should)
			  {
			     hw_output |= 1 << (Engine->OutSigs[x].OutPin-1);
			  }
			  else
			  {
			     hw_output &=  0xffff ^ (1 << (Engine->OutSigs[x].OutPin-1));
			  }
		   }		   
     	}
	}

	// Check if hardware needs update
	if( (OutputValid == 0) || ( hw_output != OutputCurrent) ||( hw_mask !=OutputMaskCurrent))
	{
		hardware->SetOutputs(hw_output,hw_mask);

		OutputValid			= 1;
		OutputCurrent		= hw_output;
		OutputMaskCurrent   = hw_mask;
	}
}



//
//	Handle any sequenctial logic from int to int you may use..
//
//
void MyDeviceClass::HandleSequences(void)
{
	
  // This processes end of GCODE movement
  if(WaitForGcodeIdle != 0)
  {
	  if(hardware->IsIdle()==true)
	  {
        WaitForGcodeIdle = 0;
		InMotion		 = 0;
		//
		// Comment from "art" : ExternalStill -  plugin telling mach3 it is idle, all movement is complete.
		//
		MainPlanner->ExternalStill = true;
	  }
  }

  // This processes end of Jog operations
  if(WaitForJogIdle != 0)
  {
	  if(hardware->IsIdle()==true)
	  {
		 WaitForJogIdle = 0;
		 InMotion		= 0;

		 // Clear jog info from Mach variables
		 Engine->Axis[JogAxis].Jogging	= false;
		 Engine->Jogging				= false;
		 MainPlanner->Jogging			= false;
		 JogAxis						= -1;
		 MainPlanner->ExternalStill		= true;
		 Engine->Sync					= true;
	  }
  }
  
  
  switch(sequence)
  {
		default:
		case SEQ_IDLE:
		{

		}break;

		case SEQ_WAIT_FOR_IDLE:
		{
			if(hardware->IsIdle()==true)
			{
				hardware->UpdateCoords(Engine->Axis[0].Index,Engine->Axis[1].Index,Engine->Axis[2].Index,Engine->Axis[3].Index);
				Engine->Sync				= true;  
				MainPlanner->ExternalStill	= true;
				sequence					= SEQ_IDLE;
				InMotion					= 0;
			}break;
		}break;

		case SEQ_DWELLING:
		{
			if(GetTickCount() - DwellTimestamp > DwellDelay)
			{
			   // Well, dwelling time has expired
			   Engine->DwellTime = 0;
			   sequence			 = SEQ_IDLE;
			}
		}break;

		case SEQ_HOME_FIND:
		{
			if(hardware->IsIdle()==true)
			{
				if(HomeDelay == 0)
				{
					// Hopefully this means we hit the limit switch
					if(Engine->InSigs[HomeSignal].Activated)
					{
						// Move slowly axis the other way ( to leave home switch )
						hardware->StartJogMove(HomeAxis,-HomeDistance,HomeVel/10,HomeAcc,HomeMask,HomeMaskValInActive);
						sequence  = SEQ_HOME_DEREF;
						HomeDelay = 10;
					}
					else
					{
						SetMachError("Something wrong with homing - switch should be activated");
						sequence = SEQ_HOME_FINISHED;
					}
				}
				else
				{
					// Give it some time - needed sometimes to start home move ( until hw reacts )
					HomeDelay--;
				}
			}
		}break;
	   	
		case SEQ_HOME_DEREF:
		{
			if(hardware->IsIdle()==true)
			{
				if(HomeDelay == 0)
				{
					// We should be off the limit switch
					if(!Engine->InSigs[HomeSignal].Activated)
					{
						//Finish sequence
						Engine->Referenced[ HomeAxis ] = true;
						Engine->Axis[HomeAxis].Index = Engine->RefCounts[HomeAxis];
						// Update axis coords ( to reference value)
						hardware->UpdateCoords(Engine->Axis[0].Index,Engine->Axis[1].Index,Engine->Axis[2].Index,Engine->Axis[3].Index);
					}
					else
					{
						SetMachError("Something wrong with homing - switch should NOT be activated");					
					}
				}
				else
				{
					// Give it some time - needed sometimes to start home move ( until hw reacts )
					HomeDelay--;
				}

				sequence = SEQ_HOME_FINISHED;
			}
		}break;


		case SEQ_HOME_FINISHED:
		{				
			//Turn off home wait..
			MainPlanner->SoftWait &=  ( 0xffffffffffffffff ^ ( ((__int64)1) << EXHOME)); 

			//Turn off the homing , this sequence is done..
			Engine->Homing				= false;
			Engine->Sync				= true;  
			MainPlanner->ExternalStill	= true;
			sequence					= SEQ_IDLE;
			InMotion					= 0;
			HomeAxis					= -1;
		}break;
  }
}



//
//	  Turn on a jog in this routine..
//
//

void MyDeviceClass::JogOn( short axis, short direction, double SpeedNorm)
{
   double JogMaxDistance;
   double JogMinDistance;



   stats.JogOnCall++;  

   if(axis >= 4)
   {
	   // My device is 4 axis only, Mach can use also axis 5 and 6
	   return;
   }

   if( Engine->OffLine )
   {
	   // Well, not in such state
	   return;
   }

   if( Engine->EStop )
   {
	   // Not allowed
       SetMachError( "No Jogging in Estop!!" ); 
	   return;
   }

   if( (Engine->TrajHead != Engine->TrajIndex ) || (WaitForGcodeIdle != 0))
   {
	   // Hmm, there is stil something going on - we do not want to mess it
	   return;
   }

   if( Engine->Jogging )   
   {
	   // Well, this means we are jogging. In theory we could allow jogging with  more axis 
	   // but this is tricky and depends on your hardware and possibility of calculating new trajectory
	   // My hardware supports jogging with one axis only
	   return;
   }

   if( sequence != SEQ_IDLE)
   {
	   // We are already in some sequence which must be finished first	
       SetMachError( "Waiting for sequence to End!" ); 
       return;
   }

   // OK, so we should start jogging with given axis
   // Calculate jog parameters

   JogAxis = axis;

   // Rapid steps per second
   JogFeed = (MainPlanner->Velocities[JogAxis]); 

   // JogSpeed OverRide. (Used in Velocity mode of MPG jog.) ?
   if( SpeedNorm != 0 )
   {
	  JogFeed = SpeedNorm;
   }

   // Keyboard Shift key is on?
   // If shift is not on, then JogPercent is the speed to use. 
   if( !(*MachView->m_ShiftState) && SpeedNorm == 0) 
   {
      JogFeed = (JogFeed * _setup->JogPercent / 100); //JogSteps/Sec..
   }

   // Calculate speed and acceleration
   JogVel   = ( JogFeed * MainPlanner->StepsPerAxis[JogAxis]);
   JogAcc   = ( MainPlanner->Acceleration[JogAxis] * MainPlanner->StepsPerAxis[ JogAxis]);
   
   // In case of using soft limits calculate max travel distance which 	
   JogMaxDistance =  999999;
   JogMinDistance = -999999;

   if( Engine->SoftLimitEnable)
   {
	  switch( JogAxis )
	  {
 		case(0):
		{
			JogMaxDistance = (MainPlanner->MXPosition * MainPlanner->StepsPerAxis[0]) - Engine->SoftLimitsHi[0];
			JogMinDistance = (MainPlanner->MXPosition * MainPlanner->StepsPerAxis[0]) - Engine->SoftLimitsLo[0];  
		}break;

	    case(1):
	    {
			JogMaxDistance = (MainPlanner->MYPosition * MainPlanner->StepsPerAxis[1]) - Engine->SoftLimitsHi[1];
		    JogMinDistance = (MainPlanner->MYPosition * MainPlanner->StepsPerAxis[1]) - Engine->SoftLimitsLo[1]; 
		}break;

	    case(2):
		{
			JogMaxDistance = (MainPlanner->MZPosition * MainPlanner->StepsPerAxis[2]) - Engine->SoftLimitsHi[2];
		    JogMinDistance = (MainPlanner->MZPosition * MainPlanner->StepsPerAxis[2]) - Engine->SoftLimitsLo[2]; 
		}break;

	    case(3):
		{
			JogMaxDistance = (MainPlanner->MAPosition * MainPlanner->StepsPerAxis[3]) - Engine->SoftLimitsHi[3];
		    JogMinDistance = (MainPlanner->MAPosition * MainPlanner->StepsPerAxis[3]) - Engine->SoftLimitsLo[3];    
		}break;

		default:
		{

		}break;
	  }
   }

   if( Engine->Directions[ JogAxis ] ) 
   {
		  JogMaxDistance = -JogMaxDistance;
		  JogMinDistance = -JogMinDistance;
   }

   if(direction == 0)
   {
		JogDistance = (int)JogMaxDistance;
   }
   else
   {
	   JogDistance = (int)JogMinDistance;
   }

   // Mark that our hardware is in controll
   MainPlanner->ExternalStill = false;
   InMotion					  = 1;

   // Now execute Jog
   hardware->StartJogMove(JogAxis, JogDistance,JogVel,JogAcc,0,0);

   // Mark jogging in internal Mach variables
   MainPlanner->Jogging       = true;
   Engine->Jogging			  = true;  
   Engine->Axis[JogAxis].Jogging = true;   


}



//
//	  Turn off a jog in this routine..
//
//
void  MyDeviceClass::JogOff(short axis)
{
  int check = 0;
 
  stats.JogOffCall++;

  if( !Engine->Jogging )
  {
	  // Well, nothing to do
	  return;
  }

  // Stop the device
  // Hmm, we operate on the original jog axis regardles what we get now in 'axis'
  hardware->FinishJogMove();
  Engine->Axis[JogAxis].Dec = true;

  // The device will nto stop immediately, so arm the waiting
  WaitForJogIdle = 1;


}

//
//	  Dwell request
//
//
 void MyDeviceClass::Dwell(double time)
 {

	// Calculate dwell time and record timestamp - will be serviced from state machine
	if( !MainPlanner->DwellMilli )
	{
		time = time * 1000; 
	}
	
	DwellTimestamp  = GetTickCount();
	DwellDelay		= (DWORD)time; 

	// Tell Mach we are dwelling
	Engine->DwellTime = 1;

	// There is silent assumption that dwell request will  come
	// only during GCode execution, when there is no other sequences running
	// ( no homing,jogging probing - etc.)
	assert( (sequence == SEQ_IDLE) || (sequence == SEQ_DWELLING) );

	sequence = SEQ_DWELLING;


	stats.DwellCall++;
 }


//
//	  Used to configure hardware according to settings in Mach structures
//
//
void  MyDeviceClass::ConfigureHardware(void)
{
	int ii;

	// Configure step pins
	for( ii =0; ii < 4;ii++)
	{
		if(Engine->Axis[ii].Enable)
		{
			if( (Engine->Axis[ii].DirPort ==1) && (Engine->Axis[ii].StepPort ==1) )
			{
				if(hardware->ConfigureStepPins(ii,Engine->Axis[ii].StepPin,Engine->Axis[ii].StepNegate,Engine->Axis[ii].DirPin,Engine->Axis[ii].DirNegate)!=0)
				{
					SetMachError("Detected wrong step/dir pin configuration");
				}
			}
			else
			{
				SetMachError("Detected wrong step/dir port configuration");
			}
		}
		else
		{
			// Basically disables axis pins
			hardware->ConfigureStepPins(ii,0,0,0,0);
		}
	}


}


//
//	  Called for homeing requests
//
//
 void  MyDeviceClass::Home(short axis)
 {
   int home_signals[] = { XHOME,YHOME,ZHOME,AHOME };

   stats.JogOnCall++;  

   if(axis >= 4)
   {
	   // My device is 4 axis only, Mach can use also axis 5 and 6
	   return;
   }

   if( Engine->OffLine )
   {
	   // Well, not in such state
	   return;
   }

   if( Engine->EStop )
   {
	   // Not allowed
       SetMachError( "No Homing in Estop!!" ); 
	   return;
   }

   if( (Engine->TrajHead != Engine->TrajIndex ) || (WaitForGcodeIdle != 0) || (WaitForJogIdle != 0))
   {
	   // Hmm, there is stil something going on - we do not want to mess it
	   return;
   }

   if( Engine->Homing  )   
   {
	   // Well, this means we are already homing. 
	   // SOmethign wrong - we should not get it again
	   return;
   }

   if( sequence != SEQ_IDLE)
   {
	   // We are already in some sequence which must be finished first	
       SetMachError( "Waiting for sequence to End!" ); 
       return;
   }

   if( (!Engine->InSigs[home_signals[axis]].Active) || (Engine->InSigs[home_signals[axis]].InPort != 1 ))
   {			
	   // Check if home switch is configured properly 
	   // Must be turned on port 1
       SetMachError( "Wrong home switch configuration!" ); 
       return;
   }

   if(Engine->InSigs[home_signals[axis]].Activated )
   {
	   // The home switch is activated
	   // Can we continue ? We could, but only if this is not shared switch
	   // For now just report it to user 
       SetMachError( "Home switch activated, jog off it first" ); 
       return;

   }
	
   // Check pin
   HomeSignal     = home_signals[axis];
   HomePin		  = Engine->InSigs[HomeSignal].InPin;

   if(	(HomePin < 10) || (HomePin == 14) || (HomePin > 15) )
   {
	   // Only input pins allowed - 10,11,12,13,15
       SetMachError( "Wrong home pin" ); 
       return;
   }


   //Ok, now we can start single axis homing

   HomeAxis		  = axis;   
   Engine->Homing = true;
   

   // Calculate movement parameters

   HomeVel		= ((double)MainPlanner->Velocities[HomeAxis]) *(((double)MainPlanner->RefSpeed[ HomeAxis]) / 100);
   HomeVel		= ( HomeVel * MainPlanner->StepsPerAxis[HomeAxis]); // Scaling  to pulses/sec   

   HomeDistance = 99999 *  (MainPlanner->AxisNegs[HomeAxis] ? 1:-1);
   HomeAcc		= ( MainPlanner->Acceleration[HomeAxis] * MainPlanner->StepsPerAxis[ HomeAxis]);


   // Mark that our hardware is in controll
   MainPlanner->ExternalStill = false;
   InMotion					  = 1;

   // Execute home move
   // Run until switch becomes activated
   HomeMask = (1<< (HomePin-1));

   if(Engine->InSigs[HomeSignal].Negated)
   {
	   HomeMaskValActive    = 0;
	   HomeMaskValInActive  = (1<< (HomePin-1));
   }
   else
   {
	   HomeMaskValActive    = (1<< (HomePin-1));
	   HomeMaskValInActive  = 0;
   }

   hardware->StartJogMove(HomeAxis,HomeDistance,HomeVel,HomeAcc,HomeMask,HomeMaskValActive);
   HomeDelay = 10;


   sequence = SEQ_HOME_FIND;

   stats.HomeCall++;
 }


//
//	  
//
//
 void  MyDeviceClass::Probe(void)
 {
	stats.ProbeCall++;
 }

//
//	  
//	Called when jog shoudl stop on a particular axis
//	Seems to be called after jog stopped on particular axis
//
void MyDeviceClass::Purge(short flags)
{
	int ii;
	int axis_index[4];

	stats.PurgeCall++;

	// Sent to zero an axis ( depending on the flag ).
	// This is base functionality 
	
	for(ii = 0; ii < 4;ii++)
	{
		if(flags & ( 1<<ii))
		{
			axis_index[ii] = 0;
		}
		else
		{
			axis_index[ii] = Engine->Axis[0].Index;
		}
	}

	hardware->UpdateCoords(axis_index[0],axis_index[1],axis_index[2],axis_index[3]);

}


//
//	  Called when Mach reset is activated
//	  
//	  Note - the reset is also activated after configuration changes, so we always reconfigure our device here
//
void MyDeviceClass::Reset(void)
{
	// Stop any movement
	hardware->Stop();
	if(hardware->Reset() == 0)
	{
		ConfigureHardware();
		SetMachError("Step2Cnc connected");
	}
	else
	{
		Engine->EStop = true;
		SetMachError("Step2Cnc communication error!!");
	}

	// Cleanup internal state
	WaitForGcodeIdle =  0; 
	WaitForJogIdle	 =  0;
	OutputValid		 =  0;

	// Jog clean - Not sure if all this is necessary
	if(JogAxis >= 0)
	{
		 Engine->Axis[JogAxis].Jogging	= false;
		 JogAxis						= -1;
	}
	Engine->Jogging			= false;
	MainPlanner->Jogging	= false;
	
	// Home clean - Not sure if all this is necessary
	if(HomeAxis >= 0)
	{			
		HomeAxis		   = -1;
	}

	Engine->Homing		  = false;

	// Clean some other variables ( in case we interrupt something in the middle)
	MainPlanner->SoftWait 	  = 0;
    Engine->DwellTime 	  = 0;

	// Make sure the hardware stops - just in case the hardware still runs
	InMotion		 = 1;
	sequence	     = SEQ_WAIT_FOR_IDLE;
	
	
	stats.ResetCall++;
}



//
//	  Dumps most important internal variables used during movement
//       
//
void  MyDeviceClass::DumpConfig(void)
{
	int		ii;
	char	buffer[256];
	char    axis[] = "XYZABC";
	int     col = 1;
	int		line = 0;
	static int divider = 0;


	if(console == NULL)
	{
		// No debug console
		return;
	}


	/* Momentary info ( updated each time called) */

	sprintf_s(buffer,"Mach Coordinates :X(%12f) Y(%12f) Z(%12f) A(%12f)",GetDRO(800),GetDRO(801),GetDRO(802),GetDRO(803));
	console->ConsolePrint(0,col++,buffer);

	col++;

	_snprintf(buffer,sizeof(buffer),"Mach Internals  : EStop(%d) OffLine(%d) Jogging(E-%d) Jogging(MP-%d) DwellTime(%d) SoftLimitsEnable(%d)",
			Engine->EStop,
			Engine->OffLine,
			Engine->Jogging,
			MainPlanner->Jogging,
			Engine->DwellTime,			
			Engine->SoftLimitEnable
	);
	console->ConsolePrint(0,col++,buffer);

	_snprintf(buffer,sizeof(buffer),"Mach Internals  : Sync(%d) ExternalStill(%d) SoftWait(%08I64X)",
			Engine->Sync,
			MainPlanner->ExternalStill,
			MainPlanner->SoftWait
	);
	console->ConsolePrint(0,col++,buffer);


	col++;

	_snprintf(buffer,sizeof(buffer),"MyDevice Internals : Sequence(%d) InMotion(%d) WaitForGcodeIdle(%d) WaitForJogIdle(%d) OutValid(%d) OutState(%05X/%05X)      ",
			sequence,	
			InMotion, 
			WaitForGcodeIdle,
			WaitForJogIdle,
			OutputValid,
			OutputCurrent,
			OutputMaskCurrent
	);
	console->ConsolePrint(0,col++,buffer);


	_snprintf(buffer,sizeof(buffer),"MyDevice Internals : JogAxis(%d) JogFeed(%f) JogVel(%f) JogAcc(%f) JogDistance(%d)",
		      JogAxis,
    		  JogFeed,
			  JogVel,
			  JogAcc,
			  JogDistance);

	console->ConsolePrint(0,col++,buffer);

	_snprintf(buffer,sizeof(buffer),"MyDevice Internals : HomeAxis(%d) HomePin(%d) HomeSignal(%d) HomeVel(%f)",
		      HomeAxis,
			  HomePin,
			  HomeSignal,
			  HomeVel,
			  HomeAcc
			  );

	console->ConsolePrint(0,col++,buffer);

	_snprintf(buffer,sizeof(buffer),"MyDevice Internals : HomeMask(%04X) HomeMaskValAct(%04X) HomeMaskValInAct(%04X) HomeDistance(%d)",
			  HomeMask,
			  HomeMaskValActive,
			  HomeMaskValInActive,
			  HomeDistance
			  );

	console->ConsolePrint(0,col++,buffer);
	
	col++;

	while(hardware->GetStats((char *)buffer,sizeof(buffer),line++) != 0)
	{
		console->ConsolePrint(0,col++,buffer);
	}


	if( (divider++%10) != 0)
	{
		// Fast info updated, slow info not this time
		return;
	}

	col += 3;

	/* Slow info */


	// Dump axix info
	for(ii = 0; ii < 4;ii++)
	{
		_snprintf(buffer,sizeof(buffer),"%c Vel:%8.4f Acc:%8.4f Steps:%12.4f Epr:%8.4f Dir:%d Slave:%d SlaveA:%d SlimHi:%8d SlimLo:%8d",
					axis[ii],
					MainPlanner->Velocities[ii],
					MainPlanner->Acceleration[ii],
					MainPlanner->StepsPerAxis[ii],
					MainPlanner->ExternalPulseRates[ii],
					(int)Engine->Directions[ii],
					(int)Engine->Axis[ii].Slave,
					Engine->Axis[ii].SlaveAxis,
					Engine->SoftLimitsHi[ii],
					Engine->SoftLimitsLo[ii]
		);

		console->ConsolePrint(0,col++,buffer);
	}

	col++;

	// Dump I/O info
	_snprintf(buffer,sizeof(buffer),"X: HOME -> Port(%d) Pin(%d) Activated(%d) Negated(%d) STEP-> Port(%d) Pin(%d) Negated(%d) DIR-> Port(%d) Pin(%d) Negated(%d)",
			  Engine->InSigs[XHOME].InPort,
			  Engine->InSigs[XHOME].InPin,
			  Engine->InSigs[XHOME].Activated,
			  Engine->InSigs[XHOME].Negated,
			  Engine->Axis[0].StepPort,
			  Engine->Axis[0].StepPin,
			  Engine->Axis[0].StepNegate,
			  Engine->Axis[0].DirPort,
			  Engine->Axis[0].DirPin,
			  Engine->Axis[0].DirNegate
	);
	console->ConsolePrint(0,col++,buffer);

	_snprintf(buffer,sizeof(buffer),"Y: HOME -> Port(%d) Pin(%d) Activated(%d) Negated(%d) STEP-> Port(%d) Pin(%d) Negated(%d) DIR-> Port(%d) Pin(%d) Negated(%d)",
			  Engine->InSigs[YHOME].InPort,
			  Engine->InSigs[YHOME].InPin,
			  Engine->InSigs[YHOME].Activated,
			  Engine->InSigs[YHOME].Negated,
			  Engine->Axis[1].StepPort,
			  Engine->Axis[1].StepPin,
			  Engine->Axis[1].StepNegate,
			  Engine->Axis[1].DirPort,
			  Engine->Axis[1].DirPin,
			  Engine->Axis[1].DirNegate

			  );
	console->ConsolePrint(0,col++,buffer);

	_snprintf(buffer,sizeof(buffer),"Z: HOME -> Port(%d) Pin(%d) Activated(%d) Negated(%d) STEP-> Port(%d) Pin(%d) Negated(%d) DIR-> Port(%d) Pin(%d) Negated(%d)",
			  Engine->InSigs[ZHOME].InPort,
			  Engine->InSigs[ZHOME].InPin,
			  Engine->InSigs[ZHOME].Activated,
			  Engine->InSigs[ZHOME].Negated,
			  Engine->Axis[2].StepPort,
			  Engine->Axis[2].StepPin,
			  Engine->Axis[2].StepNegate,
			  Engine->Axis[2].DirPort,
			  Engine->Axis[2].DirPin,
			  Engine->Axis[2].DirNegate


			  );
	console->ConsolePrint(0,col++,buffer);

	_snprintf(buffer,sizeof(buffer),"A: HOME -> Port(%d) Pin(%d) Activated(%d) Negated(%d) STEP-> Port(%d) Pin(%d) Negated(%d) DIR-> Port(%d) Pin(%d) Negated(%d)",
			  Engine->InSigs[AHOME].InPort,
			  Engine->InSigs[AHOME].InPin,
			  Engine->InSigs[AHOME].Activated,
			  Engine->InSigs[AHOME].Negated,
			  Engine->Axis[3].StepPort,
			  Engine->Axis[3].StepPin,
			  Engine->Axis[3].StepNegate,
			  Engine->Axis[3].DirPort,
			  Engine->Axis[3].DirPin,
			  Engine->Axis[3].DirNegate			  
			  );
	console->ConsolePrint(0,col++,buffer);

	_snprintf(buffer,sizeof(buffer),"EMERGENCY -> Port(%d) Pin(%d) Activated(%d) Negated(%d)",
			  Engine->InSigs[EMERGENCY].InPort,
			  Engine->InSigs[EMERGENCY].InPin,
			  Engine->InSigs[EMERGENCY].Activated,
			  Engine->InSigs[EMERGENCY].Negated);
	console->ConsolePrint(0,col++,buffer);


	col++;
	// Dump trajectory info
	_snprintf(buffer,sizeof(buffer),"Calls-> Traj:%5lu(%3u) JogOn:%3u JogOff:%3u Dwell:%3u  Home:%3u Probe:%3u Purge:%3u Reset:%3u",
					stats.TrajectoryItems,
					Engine->TrajIndex, 
					stats.JogOnCall,
					stats.JogOffCall,
					stats.DwellCall,
					stats.HomeCall,
					stats.ProbeCall,
					stats.PurgeCall,
					stats.ResetCall					
	);

	console->ConsolePrint(0,col++,buffer);


}


//
//	Get message to the Mach log        
//
void MyDeviceClass::SetMachError(CString  Message)
{
	CString  *err = (CString  *) &MainPlanner->LastError;
	if( err != NULL) *err = Message;

}


//
//	Helper for text conversion       
//

std::string MyDeviceClass::wchar2s(wchar_t * wchar_string,int size){			std::string	  result;			char		  cc[8];			int			  cnv_size;			int			  ii,jj;
			for(ii =0; ii < size;ii++)
			{
	#pragma warning (disable : 4996)
				cnv_size = wctomb ((char*)&cc, wchar_string[ii]);				for(jj = 0; jj < cnv_size; jj++)
				{
					result += cc[jj];				}
			}
			return result;
}


//
//	Helper for text conversion       
//
std::string MyDeviceClass::nets2s(System::String^ net_string)
{
		int ii;
		array<System::Byte>^ byte_array = Encoding::UTF8->GetBytes(net_string);
		std::string	  result;
		result.resize(byte_array->Length);
		for(ii =0; ii< byte_array->Length;ii++)
		{
			result[ii] = byte_array[ii];
		}
		return result;
}