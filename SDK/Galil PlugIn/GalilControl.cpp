// GalilControl.cpp : implementation file
//

#include "stdafx.h"
#include "MachDevice.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "GalilControl.h"
#include "GalilStructs.h"
#include ".\galilcontrol.h"
#include "math.h"


extern TrajectoryControl *MainPlanner;	// used for most planner funcitons and program control 
extern CMach4View *MachView;			// used for most framework and configuration calls. 
extern TrajBuffer *Engine;				// Ring0 memory for printer port control and other device syncronisation
extern setup *_setup;					// Trajectory planners setup block. Always in effect 
// GalilControl

 bool m_UseRefPostion;
 bool m_UseCalcSpeed;
 int m_UseVectorDecel;
 double m_UseVectorTimeConst;
 GalilStruct State;

IMPLEMENT_DYNAMIC(GalilControl, CWnd)


#define UNITTIME  .004
 
 
#define ConProgramsz 30 //nLines + 1

GalilControl::GalilControl()
{
	//initialition of the Galil Unit controller
	State.Connected = false; // But were not connected as yet..
	State.HomeData.HomeStage = SEQNONE;
	State.SoftLimitsOn = false;
	m_DMCWin = new CDMCWin(1);
	memset( Ids, 0, sizeof(short)*255 );
	IdIn = 0;
	debug.Open(" GalilDebug.txt", CFile::modeCreate | CFile::modeWrite  | CFile::shareDenyNone);

    DebugCtl = 0x01;  //set for full command output..
	
}

GalilControl::~GalilControl()
{
	 m_DMCWin->Close();
     delete m_DMCWin;
	 debug.Flush();
	 debug.Close();
}


BEGIN_MESSAGE_MAP(GalilControl, CWnd)
END_MESSAGE_MAP()



// GalilControl message handlers

//Connects to the Galil 
bool GalilControl::Connect(void)
{
   // Open a connection to the controller 
	m_hDmc = NULL;
	MainPlanner->ExBufferHi = 350;
	MainPlanner->ExTime = UNITTIME;
	MainPlanner->ExternalType = EX_VMS; //EX_COMMAND;
	rc =  m_DMCWin->Open(1,m_hWnd);
	State.IsMoving = false;
	if(!rc==DMCNOERROR)
	{
		rc = m_DMCWin->Close();
		SetMachError( "Galil card not connected!!" ); 
		State.Connected = false;
		return false;
	}
	rc = DMCOpen( 1, m_hWnd, &m_hDmc );
	rc = DMCGetDataRecordConstPointer( m_hDmc, (const char**)&State.Record );
	if( rc != S_OK ) CheckError();
	State.Connected = true;
	if( rc == S_OK )
       SetMachError( "Galil Communications begun!!" ); 	
	else
	{
       SetMachError( "Galil Communications Open, but error in getting data record.!!" ); 	
	   return false;
	}
	ResetControl();
	//set the max speeds of MAch3 for this device..
	for( int x = 0; x < 7; x++ )
		MainPlanner->ExternalPulseRates[x] = 3000000;

	//set the begin command for the correct axis number.
	switch( State.nAxis )
	{
	case( 1 ): State.Begin = "BG A"; State.Linear = "LMA";    State.Contour = "CMA";     break;
    case( 2 ): State.Begin = "BG AB";  State.Linear = "LMAB";  State.Contour = "CMAB";    break;
    case( 3 ): State.Begin = "BG ABC";  State.Linear = "LMABC"; State.Contour = "CMABC";    break;
    case( 4 ): State.Begin = "BG ABCD";  State.Linear = "LMABCD"; State.Contour = "CMABCD";   break;
    case( 5 ): State.Begin = "BG ABCDE";  State.Linear = "LMABCDE"; State.Contour = "CMABCDE";  break;
    case( 6 ): State.Begin = "BG ABCDEF";  State.Linear = "LMABCDEF"; State.Contour = "CMABCDEF"; break;

	}
	for( int x = 0; x < 6; x++)
	   fractions[x] = 0;
//	SendCommand("RS");
	SendCommand("HX0");
   	SendCommand("DT1"); //set for 1ms traffic..
	//Set the string for the Axis that is going to be the spinlde axis... State.Spindle
	//We will also have the Bool to see that we have turned the spinlde on. State.SpindleOn
	State.Spinlde = "";
	State.SpindleRate = 0.0;
	if(State.nSpindle>=0 && State.nSpindle<=5)
	{
		for(int x=0;x<State.nSpindle-1;x++)
			State.Spinlde = State.Spinlde +",";
	}
	/*
	//Look to see if there is slaving that needs to be added to an axis...
	CString AxisName[6] = { "X","Y","Z","A","B","C" };
	for(int x=0;x<6;x++)
	{
		if(Engine->Axis[x].SlaveAxis>=0 && Engine->Axis[x].SlaveAxis<=6)
		{
			CString Com = "";
			//Now check to see if there is an axis slaved to an other... 
			for(int i=0;i<Engine->Axis[x].SlaveAxis;i++)
			{
				if(i!=0)Com += ",";
			}
			CString mes = "Please send this back to me\n";
			CString Temp = "GA"+Com+"C" + AxisName[x];
			mes = mes +Temp+"\n";
			SendCommand(Temp);
			Temp = "GR"+Com+"1";
			mes = mes +Temp+"\n";
			SendCommand(Temp);
			Temp = "GM"+Com+"1";
			mes = mes +Temp+"\n";
			SendCommand(Temp);
			mes = mes +"Thank you for the help \n";
			AfxMessageBox(mes);
		}
		
	}
 */
	return true;
}

//Sends messages out the Status line of Mach3

void GalilControl::SetMachError(CString Message)
{
	CString *err = &MainPlanner->LastError;
	*err = Message;

}
//main update loop at 10hz.
void GalilControl::Update(void)
{
	static bool busy = false;
	
	if(State.HomeData.HomeStage != SEQNONE)
	{
		busy = true;
		DMCRefreshDataRecord( m_hDmc,0 );
		UpdateInputs();//update the inputs... 
		static int Homes[6] = { 2,5,8,11,14,17 };
		static CString AxisName[6] = { "X","Y","Z","A","B","C" };
		static double LastPos=0;//This is needed to figure out if the home is finished to the index pulse... 
		//The only way that I can tell if the index is found is from the Galil setting the Posion to 0.0000 and that it is no longer moving
		static int PosCecks = 0;
		CString Com;
		int temp;
		//The Axis is homing and need to check and see that all movment is finished... 
		//We are going to look at the ISMOVING in the Galil to see if all the homing is done.
		//Once the homing is finished we will run the other cycle that is going to Zero the DRO's
		bool Moving;
		if(((unsigned char)State.Record->AxisInfo[State.HomeData.HomingAxis].Status >> 4 ) & 0x01&&
			((unsigned char)State.Record->AxisInfo[State.HomeData.HomingAxis].Status >> 5 )& 0x01)
			Moving = false;
		else
			Moving  = true;
		switch (State.HomeData.HomeStage)
		{
			case(FINDSWITCH):
				//We are looking to see if the home switch is hit....
				if(Engine->InSigs[Homes[State.HomeData.HomingAxis]].Activated)
				{
					//We have hit the switch so we need to tell the Axis to stop!
					SendCommand("ST");
					//Now we can move off the switch... 
					State.HomeData.HomeStage = MOVEOFFSWITCH;
					PosCecks = -1;
				}
				break;
			case(MOVEOFFSWITCH):
				 if(Moving)
					 return;
				 //Now that everything has stopped it is time to jog off the switch at a nice slow rate (10% of jog rate)
				 temp = (int)(State.HomeData.HomeVel*-.1);
				 
				Com.Format("JG%s%d", State.HomeData.AxisString , temp);
				SendCommand( Com ); // Start the Axis moving... 
				SendCommand( "BG" );//Now Start the Home Jog Move...
				State.HomeData.HomeStage = ROUGHHOME;
				break;
			case(ROUGHHOME):
				
				if(!Engine->InSigs[Homes[State.HomeData.HomingAxis]].Activated)
				{
					//We have hit the switch so we need to tell the Axis to stop!
					SendCommand("ST");
					//Now we can move off the switch... 
					State.HomeData.HomeStage = MOVEOFFSWITCH;
					if(State.HomeData.UseIndex[State.HomeData.HomingAxis])
					{
						State.HomeData.HomeStage = FINDINDEX;
						PosCecks = 0;
					}
					else 
						State.HomeData.HomeStage = SYNCSTATE;
				}
				break;
			case(FINDINDEX):
				if(Moving)
					 return;//This is telling us that the Galil is still moving...
				if(State.HomeData.HomeVel>0)
					temp = -400;
				else
					temp = 400;
				Com.Format("JG%s%d", State.HomeData.AxisString , temp);
				SendCommand( Com );
				Com.Format("FI%s", AxisName[State.HomeData.HomingAxis]);
				SendCommand( Com ); // Tell the axis to find the index pulse 
				Com.Format("BG%s", AxisName[State.HomeData.HomingAxis]);
				SendCommand( Com ); // Start the Axis moving... 
				State.HomeData.HomeStage = SYNCSTATE;
				break;
			case(SYNCSTATE):
				if(State.HomeData.UseIndex[State.HomeData.HomingAxis])
				{
					if(PosCecks<=3 )//If the axis has not moved in 3 scans we are good to go :)
					{
						if(fabs(Engine->Axis[State.HomeData.HomingAxis].Index - LastPos) <2)
						{
							PosCecks++;
							return;
						}
						LastPos = Engine->Axis[State.HomeData.HomingAxis].Index;
						return;
					}
				}
				else
				{
				 if(Moving)
					 return;//This is telling us that the Galil is still moving...
				}
				
				
				SendCommand("ST");
				//this is where we need to set the position in the Galil to Zero and set Mach3 to be Zero...
				// AxisBeingHomed is holding the number of the axis that we are homing...
				Com = "DP" + State.HomeData.AxisString + "0";
				SendCommand( Com );//Set the position of the axis to be Zero....
				//Now that the Galil is set to Zero now it is time to set Mach3 to be Zero...
				Engine->Axis[State.HomeData.HomingAxis].Index = 0;
				Engine->Referenced[State.HomeData.HomingAxis] = true;
				Engine->Axis[State.HomeData.HomingAxis].Homing = false;
				MainPlanner->ExternalStill = true;
				//Engine->Axis[x].Indes = MainPlanner->RefCounts[x]
				
				SendCommand("ST");
				SendCommand("CS");
				IdIn = 0;
				SendCommand( "SH" );
				MainPlanner->SoftWait = 0;

				State.HomeData.HomeStage = SEQNONE;
				busy = false;
				
				break;
		}

		
		

	}

		

	if( busy  ) return;//If you are busy exit....
	busy = true;
	if(Engine->SoftLimitEnable != State.SoftLimitsOn)
	{
		
		CString Com = "FL";
		CString Temp = "";
		for(int x=0;x<6;x++)
		{
			if(x!=0)Com += ",";
            int SoftMax = Engine->SoftLimitsHi[x];
			if(Engine->SoftLimitsHi[x]>=2147483647 || !Engine->SoftLimitEnable)SoftMax = 2147483647;
			Temp.Format("%d",SoftMax);
			Com+=Temp;
			
		}
		SendCommand(Com);
		Com = "BL";
		for(x=0;x<6;x++)
		{
			if(x!=0)Com += ",";
			int SoftMin = Engine->SoftLimitsLo[x];
			if(Engine->SoftLimitsHi[x]>=2147483648 || !Engine->SoftLimitEnable)SoftMin = -2147483648;
			Temp.Format("%d",SoftMin);
			Com+=Temp;
		}
		SendCommand(Com);
		State.SoftLimitsOn = Engine->SoftLimitEnable;//Set the state of the softlimits...
	}
	//Only gets called if we're connected, but called at 10hz..(Can be reprogrammed to as high as 50hz..)
 	USHORT sz = 0;
	DMCRefreshDataRecord( m_hDmc,0 );
	//rc = m_DMCWin->RefreshDataRecord(); //update the data block from the device. 
	if( rc != S_OK ) CheckError();
	if( rc == S_OK )
	{
	  bool hold = State.IsMoving;
	  State.IsMoving = false;
	  for( int x = 0; x< State.nAxis; x++ )
	    if( State.Record->AxisInfo[x].Status & 0x8000  )
		{
			State.IsMoving = true;
		    MainPlanner->ExternalStill = false;
		}
		if( hold && !State.IsMoving ) 
			Engine->Sync = true;

	  if( !State.IsMoving ) MainPlanner->ExternalStill = true;
	  if( !State.IsMoving && BufferLeft()== 511)
		  for( int x = 0; x< State.nAxis; x++ )
		  {
             Indexs[x] = Engine->Axis[x].Index;
		  }
      static int idmax = 0;
	  UpdateInputs(); //we have the data block, so update all the inputs..
	}
	else
	{   //Hmm, not speaking to us, lets stop everythinf for now, should never happen..
		SetMachError( "Galil Communications Failure.Restart program..!!" ); 
		Engine->EStop = true; //trigger an Estop so things come to a halt..
		rc = m_DMCWin->Close();
		State.Connected = false;
	}
	switch( MainPlanner->ExternalType )
	{
	  case ( EX_COMMAND ):  DoCommandGCode();  break;  //only for command mode..
	  case ( EX_VMS):        Do4MsGCode();     break;
	  case ( EX_DDA):                          break;
	}
	
    busy = false;
  
}

void GalilControl::UpdateInputs()
{
	//updates Mach3's input signals..

bool test = Engine->OutSigs[SPINDLEOFF].Activated;
	
	if(Engine->OutSigs[SPINDLECCW].Activated && MainPlanner->Spindle.ratio*10 != State.SpindleRate)
	{
		State.SpindleRate = MainPlanner->Spindle.ratio*10;
		CString Spindle;
		Spindle.Format("%.3f",State.SpindleRate);
		Spindle = "OF" + State.Spinlde + Spindle ;
		SendCommand(Spindle.GetBuffer(20));
	}
	if(!Engine->OutSigs[SPINDLECCW].Activated && State.SpindleRate!=0.0)
	{
		//If the spindle is not activated See if the Offset has been set to zero on the dac
		State.SpindleRate =0.0;
		CString Spindle;
		Spindle = "OF" + State.Spinlde + "0" ;//Set the spindle to Zero offset...
		SendCommand(Spindle.GetBuffer(20));
	}

static int loop = 0;
static int    steps10[6];

	unsigned int in = (unsigned char)State.Record->Input0 |
		              (unsigned char)State.Record->Input1 << 8  |
					  (unsigned char)State.Record->Input2 << 16 |
					  (unsigned char)State.Record->Input3 << 24 ;
	MainPlanner->OEMDROs[1] = in;
	//first put first 32 inputs in an integer. 
	for( int x = 0; x< nSigs; x++) //check all signals from 0 to max number of signals.
	{
		if( Engine->InSigs[x].Active &&
			Engine->InSigs[x].InPort == 1 ) //if this signal is turned on, and its set to port #1..check it..
		{
			
           if(( in >> (Engine->InSigs[x].InPin -1  ) ) & 0x01 ) // if the nth (pin number) bit is active..
			   Engine->InSigs[x].Activated = !Engine->InSigs[x].Negated; //set it high or low depending on the "low active"..
		   else
			   Engine->InSigs[x].Activated = Engine->InSigs[x].Negated; //setting..
		   int g=0 ;
     	}

	} //There, all digital inputs done..
  //Now outputs..
  //get 32 outputs..and see if we need to send a general output command..

 
  //current output word.. 
  unsigned int out  = (unsigned char)State.Record->Output0 |
		              (unsigned char)State.Record->Output1 << 8  |
					  (unsigned char)State.Record->Output2 << 16 |
					  (unsigned char)State.Record->Output3 << 24 ;

  //what we should be outputting..
   unsigned short outword = 0;

  for( int x = 0; x< nSigsOut; x++) //check all signals from 0 to max number of signals.
	{
		
		if( Engine->OutSigs[x].active &&
			Engine->OutSigs[x].OutPort == 1 && 
			Engine->OutSigs[x].OutPin < 16 ) //if this signal is turned on, and its set to port #1..check it..
		{
		   bool Should = Engine->OutSigs[x].Activated;
		   if( Should ) 
		   {
           //we are activated..
		   Should = !Engine->OutSigs[x].Negated;
		   if (Should)
               outword |= 1 << (Engine->OutSigs[x].OutPin-1);
		   else
			   outword &=  0xffff ^ (1 << (Engine->OutSigs[x].OutPin-1));
		   }
		   else
		   {
		    //we are inactive
			Should = Engine->OutSigs[x].Negated;
			if (Should)
			   outword |= 1 << (Engine->OutSigs[x].OutPin-1);
			 else
			   outword &=  0xffff ^ (1 << (Engine->OutSigs[x].OutPin-1));
		   }
		   
     	}

	}
  //since output words dont match with Mach3's output variables, lets update the Galil 
  //to proper output level. Should only occur whwn an output changes..
  if(  out != outword )
  {
	  CString Com;
	  Com.Format( "OP %d",outword );
	  SendCommand(Com.GetBuffer(20));
  }
  
  //OK, so now lets read the encoders of the system..
  //We read only the Auxillary encoders..
  //We'll also update the main index registers here. SO the Axis DRO's 
  // reflect actual position in the machine coordinates.
  static int Homes[6] = { 2,5,8,11,14,17 };
  static int PosLimits[6] = {0,3,6,9,12,15};
  static int NegLimits[6] = {1,4,7,10,13,16};
  
  
  for( int x = 0; x< 7; x++)
  {
	  
	 Engine->Encoders[x].Count[0] = State.Record->AxisInfo[x].AuxillaryPosition;

	 if( m_UseRefPostion ) Engine->Axis[x].Index = State.Record->AxisInfo[x].ReferencePosition;
	 else                  Engine->Axis[x].Index = State.Record->AxisInfo[x].MotorPosition;

	 //MainPlanner->OEMDROs[x] = State.Record->AxisInfo[x].AnalogInput;//Get the analog inputs...
	//for(int i=0;i<16;i++)
	//{
	//	if(((unsigned char)State.Record->AxisInfo[0].Status >> x ) & 0x01)//was 4 for Is moving
	//		MainPlanner->OEMLeds[10+x] = true;
	//	else
	//		MainPlanner->OEMLeds[10+x] = false;
	//}

	unsigned int InAxisData  = (unsigned char)State.Record->AxisInfo[x].Switches;
	if(x<6)
	{
		if( Engine->InSigs[Homes[x]].Active)
		{
			//Get the state of the Home input...
			if((InAxisData >> 1) & 0x01)
				Engine->InSigs[Homes[x]].Activated = !Engine->InSigs[Homes[x]].Negated; 
			else
				Engine->InSigs[Homes[x]].Activated = Engine->InSigs[Homes[x]].Negated;
		}
		if( Engine->InSigs[NegLimits[x]].Active)
		{
			//get the state of the Negitive limit...
			if((InAxisData  >>2) & 0x01)
				Engine->InSigs[NegLimits[x]].Activated = !Engine->InSigs[NegLimits[x]].Negated; 
			else
				Engine->InSigs[NegLimits[x]].Activated = Engine->InSigs[NegLimits[x]].Negated;
		}
		if( Engine->InSigs[PosLimits[x]].Active)
		{
			//Get the state of the positive limit switch..
			if((InAxisData  >> 3) & 0x01)
				Engine->InSigs[PosLimits[x]].Activated = !Engine->InSigs[PosLimits[x]].Negated; 
			else
				Engine->InSigs[PosLimits[x]].Activated = Engine->InSigs[PosLimits[x]].Negated;
		}
	}
  }

  //Well, since we're doign everything else in here..lets get the current velocities as well..
  //but this will only work for encoders on the motors.. 
  if( !m_UseCalcSpeed )
  {
    Engine->StatLast[0] = State.Record->AxisInfo[0].Velocity  / 5;
    Engine->StatLast[1] = State.Record->AxisInfo[1].Velocity  / 5;
    Engine->StatLast[2] = State.Record->AxisInfo[2].Velocity  / 5;
    Engine->StatLast[3] = State.Record->AxisInfo[3].Velocity  / 5;
    Engine->StatLast[4] = State.Record->AxisInfo[4].Velocity  / 5;
    Engine->StatLast[5] = State.Record->AxisInfo[5].Velocity  / 5;
  }
  else
  {
    //here we need to fake movement statistics due to no encoder..over 200ms..
	  loop++;
	  if( loop >= 2 )
	  {
	    
        loop = 0; 
		for( int x = 0; x<6;x++)
		{
			Engine->StatLast[x] = abs( Engine->Axis[x].Index - steps10[x]);
			steps10[x] = Engine->Axis[x].Index; //start with current position..
		}
	  }  
     
  }
  
  if( Engine->EStop )
	  EnsureStopped();

}

void GalilControl::JogOn( short axis, short dir, double speed)
{
	if( Engine->EStop )
	{
       SetMachError( "No Jogging in Estop!!" ); 
	   return;
	}
	if( Engine->TrajHead != Engine->TrajIndex ) return;
	SendCommand( "LE" );
    double JogFeed = (MainPlanner->Velocities[axis]); //rapid steps per second
    // JogSpeed OverRide. (Used in Velocity mode of MPG jog.) ?
    if( speed != 0 ) JogFeed = speed;
    //Keyboard Shift key is on?
    // If shift is not on, then JogPercent is the speed to use. 
   if( !(*MachView->m_ShiftState) && speed == 0) 
            JogFeed = (JogFeed * _setup->JogPercent / 100); //JogSteps/Sec..

    int accs[7];
	for( int x = 0; x < State.nAxis + 1; x++)
	{
		accs[x] = (int)(MainPlanner->Acceleration[x]  * MainPlanner->StepsPerAxis[x]);
	}
	//set the accelerations of tha axis..
	CString Com;
	Com.Format( "AC %d,%d,%d,%d,%d,%d ", accs[0], accs[1], accs[2], accs[3], accs[4], accs[5], accs[6] );
	HRESULT res = m_DMCWin->Command(Com.GetBuffer(20));
	
	Com.Format( "DC %d,%d,%d,%d,%d,%d ", accs[0], accs[1], accs[2], accs[3], accs[4], accs[5], accs[6] );
	res = m_DMCWin->Command(Com.GetBuffer(20));
    if( dir == 0 ) JogFeed = -JogFeed;
	int feeds[6];
	memset( feeds, 0, sizeof(int) * 6);
	Engine->Axis[axis].Jogging = true;
	feeds[axis] = (int) (JogFeed * MainPlanner->StepsPerAxis[axis]);
	Engine->Axis[axis].Memory[0] = feeds[axis];
	for( int x=0; x< State.nAxis + 1; x++)
		if( Engine->Axis[x].Jogging && x != axis )
		{
          feeds[x] = Engine->Axis[x].Memory[0];
		}

	Com.Format( "JG %d,%d,%d,%d,%d,%d ", feeds[0], feeds[1], feeds[2], feeds[3], feeds[4], feeds[5] );
	SendCommand(Com.GetBuffer(20));
	Ids[IdIn & 0xff] = Engine->DisplayLine;
    SendCommand(State.Begin.GetBuffer(20)); 
}

void GalilControl::JogOff( short axis )
{
   Engine->Axis[axis].Jogging = false;
   char * axiscoms[6] = {  "STA" , "STB" , "STC", "STD", "STE", "STF" }; 
   SendCommand(axiscoms[axis]); 
   //SendCommand( "CD0,0=0" ); This is not needed because we are not doing this
   bool injog = false;
   for( int x=0; x< State.nAxis + 1; x++)
		if( Engine->Axis[x].Jogging ) injog = true;
   if( !injog)
   {
	   Engine->Sync = true;
	   SendCommand(" ST ");
   }
   

}

void GalilControl::EnsureStopped( )
{ 
	//Should add some thing to see if the control is in a stoped condition and not send data if it is
	//we get her eonly if we are EStopped. So stop all motion if any is going on..
	for( int x = 0; x< 6; x++) 
	  if( State.Record->AxisInfo[x].Status & 0x8000 ) JogOff( x );

    SendCommand( "LE" );
	//SendCommand( "CD0,0=0" );
   SendCommand( "AB" );
}
void GalilControl::ResetControl(void)
{
    //we do this at the start, and whenever reset is pressed. 
	if( !State.Connected)
	{
	   m_hDmc = NULL;
       rc =  m_DMCWin->Open(1,m_hWnd);
	   if(!rc==DMCNOERROR)
	   {
		 rc = m_DMCWin->Close();
		 SetMachError( "Galil card not connected after reset!!" ); 
		 State.Connected = false;
		 return;
	   }
	   rc = DMCOpen( 1, m_hWnd, &m_hDmc );
	   rc = DMCGetDataRecordConstPointer( m_hDmc, (const char**)&State.Record );
	   State.Connected = true;
	}
    //SendCommand("CD,0=0"); 
	//GetNumber of axis
	double Types[6] = { 1, -1, -2, 2, -2.5, 2.5 }; 
	CString Com;
	//SendCommand("TM 1000");
	State.nAxis = SendCommand( "QZ" );
	if( State.nAxis > 6 ) State.nAxis = 6;
	//now to set each axis to rigth type.
	CString total;
	total.Format( "MT %1.1f",Types[ State.motortype[0] ] );
    for( int x = 1; x < State.nAxis; x++)
	{
		short h = State.motortype[x];
		double t = Types[ h ];
		Com.Format( ",%0.1f", t );
		total += Com;
		
	}
	
    SendCommand( "ST" );
	Sleep(50);
	Com.Format("DP %i,%i,%i,%i,%i,%i",Engine->Axis[0].Index,
		                              Engine->Axis[1].Index,
									  Engine->Axis[2].Index, 
									  Engine->Axis[3].Index, 
									  Engine->Axis[4].Index, 
									  Engine->Axis[5].Index  );
	SendCommand( Com );
	SendCommand( total ); 
	IdIn = 0;
    SendCommand( "SH" ); //servo here command to start the Galil's postioning algorithm
	
	 
}


//this routine for begugging command errors..

void GalilControl::CheckError( )
{
   long error = m_DMCWin->GetLastError();
   char err[80];
   m_DMCWin->GetErrorText( error, err, 80 ); 
   CString mess = err;
   SetMachError( mess ); 	
   int g = 9;
}

int GalilControl::BufferLeft(void)
{
	HRESULT res;
	CString Com;
	Com = "LM ?";
    ULONG ures = 80;
	char cres[80];
	res = m_DMCWin->Command(Com.GetBuffer(20), cres, ures);
	if( res != S_OK ) CheckError();
	State.BufferLeft = atoi( cres );
	return State.BufferLeft;
}

int GalilControl::SendCommand(CString com, bool nobinary )
{
    HRESULT rc;
     BYTE BinaryCommand[100];
    ULONG BinaryLength;
	ULONG ures = 80;
	HRESULT res;
	char cres[80];

 if( DebugCtl & 0x01 )
 {
    debug.WriteString( com );
    CString t;
	t.Format( "  Slots : %d, \n ",slots); 
    debug.WriteString( t );
 }

	char *buf = com.GetBuffer();
	short len = com.GetLength();
    rc = m_DMCWin->AsciiCommandToBinaryCommand( buf, len , BinaryCommand,100,&BinaryLength);
    if( rc == S_OK && !nobinary)
	{
      res = m_DMCWin->BinaryCommand( BinaryCommand,BinaryLength, cres, ures);
	  if( res != S_OK ) CheckError(); 
	  return atoi( cres );
	}
	res = m_DMCWin->Command( com.GetBuffer(), cres, ures);
	if( res != S_OK ) CheckError(); 
	return atoi( cres );


}


void GalilControl::SendProgram(char* Program[],int sz)
{
	CString com = " ";
	CString com2;
	for ( int x = 0; x < sz; x++ )
	{
		char *text = Program[x];
		com2 =  text;
		com += com2 + "\n";
		int h = 9;
	}
	
	//execute the program
	HRESULT res = m_DMCWin->DownloadFromBuffer( com.GetBuffer() );
	if( res != S_OK ) CheckError();
    com.Format("XQ%s,0", Program[0]);
	SendCommand( com );
}

void GalilControl::Do4MsGCode() 
{

 CString Com,dummy;  
 
 if( Engine->TrajHead == Engine->TrajIndex ) return;
 slots = BufferLeft();
 short origslots = slots;
 if( slots == 511 && !State.IsMoving )
 {
    IdIn = 0;
    SendCommand( State.Linear ); //turn on Linear mode cuz nothing is moving at the moment, just in case.
	CString Com;
	Com.Format("VT%.3f",m_UseVectorTimeConst) ;
	SendCommand( Com ); 
	Com.Format("VD%d",m_UseVectorDecel);
	SendCommand( Com );
  }
 static double xtotal = 0;
 if( slots < 350 ) return;
 int onecall = 0;
 while( Engine->TrajIndex != Engine->TrajHead )
 {
	 Engine->DisplayLine = Engine->Trajectories[ Engine->TrajIndex ].ID;
	 if(Engine->Trajectories[ Engine->TrajIndex ].ID == 0 )
		 int g = 8;
	 MoveRelative( Engine->TrajIndex );
	 xtotal += Engine->Trajectories[ Engine->TrajIndex ].Points[0];

	 Engine->TrajIndex++;
	 Engine->TrajIndex &= 0xfff; //lock the ring.
     onecall++;
     slots--;
     if( slots < 350 || onecall > 50 ) break;
 }
 State.IsMoving = true;
 if( Engine->TrajIndex == Engine->TrajHead && MainPlanner->BufferEnding)
     SendCommand( "LE" );
  

}

void GalilControl::DoCommandGCode(void)
{
 CString Com,dummy;  
 
 if( Engine->TrajHead == Engine->TrajIndex ) return;
 slots = BufferLeft();
 short origslots = slots;

  
 if( slots == 511 && !State.IsMoving )
 {
    IdIn = 0;
    SendCommand( State.Linear ); //turn on Linear mode cuz nothing is moving at the moment, just in case.
	CString Com;
	Com.Format("VT%.3f",m_UseVectorTimeConst); 
	SendCommand( Com ); 
	Com.Format("VD%d",m_UseVectorDecel);
	SendCommand( Com );
  }
 if( slots < 300 ) return;
 while( Engine->TrajIndex != Engine->TrajHead )
 {
	 
	 GMoves  move = MainPlanner->Movements[Engine->TrajIndex];
	 GMoves1 rest = MainPlanner->MovementsAdd[Engine->TrajIndex];
	 Engine->TrajIndex++;
	 Engine->TrajIndex &= 0xfff; //lock the ring.
	 //now add this move.
	 if( move.type == TC_LINEAR )
	 {
       AddLinear( &move,&rest);
   	 }
	 else
	 {
      int dummy = 6;
	 }
	 slots--;
     if( slots < 300 ) break;
 }
 State.IsMoving = true;
 if( Engine->TrajIndex == Engine->TrajHead && MainPlanner->BufferEnding)
     SendCommand( "LE" );
  
 return;
}

void GalilControl::Stop()
{
  SendCommand("ST");
  SendCommand("CS");
  IdIn = 0;
 // SendCommand("TM 1000"); //Set time constant to 1000us ( 1ms)
  SendCommand( "SH" ); //servo here command to start the Galil's postioning algorithm

}

void GalilControl::MoveRelative( short index )
{
  CString temp,Com = "LI ";
  double steps[6];
  double udist = 0;

  bool IsNext  = ((Engine->TrajIndex + 1 ) & 0xfff ) != Engine->TrajHead ;
  bool Decel = false;

  steps[0] = Engine->Trajectories[index].Points[0];
  steps[1] = Engine->Trajectories[index].Points[1];
  steps[2] = Engine->Trajectories[index].Points[2];
  steps[3] = Engine->Trajectories[index].Points[3];
  steps[4] = Engine->Trajectories[index].Points[4];
  steps[5] = Engine->Trajectories[index].Points[5];
 // count += steps[0];
  short zeros = 0;
  for( int x = 0; x < State.nAxis; x++)
   {
     int v = (int)(steps[x]);
	 if( v == 0) zeros++;
     temp.Format( "%s %i,", Com, v );
     udist += steps[x] * steps[x];
     Com = temp;
	 if( IsNext )
	 {
       if(  Engine->Trajectories[((Engine->TrajIndex + 1 ) & 0xfff )].Points[x] == 0 && v != 0 )
		   Decel = true;
     }
   }
   if( zeros == State.nAxis ) return; //no actual movement;
   udist = sqrt( udist ); // unit vector distance in steps..
   double  speed = udist / UNITTIME;  //distance divided by 4ms to get speed.
   temp = Com.Left( Com.GetLength() - 1);
   Com.Format("%s <%i ", temp, (((int)speed ) & 0xfffffffe));
   
   if( (MainPlanner->BufferEnding && ((Engine->TrajIndex + 1 ) & 0xfff ) == Engine->TrajHead) )
   {
	   temp.Format( "%s >0 ", Com );
	   Com = temp;
   }
   SendCommand(  Com,true  ); //no binary on this command 

   MainPlanner->ExternalStill = false;
   Ids[IdIn & 0xff] = Engine->Trajectories[index].ID;
   IdIn++;
   if(!State.IsMoving ) SendCommand( "BGS" );
   State.IsMoving = true;
  

}


void GalilControl::AddLinear( GMoves* move, GMoves1 *add)
{
  
   CString temp,Com = "LI ";
   double steps[6];
   double dd[6];
   double Uv[6];//segments that make up the unit length Vector
   dd[0] = (move->ex - move->sx);
   dd[1] = (move->ey - move->sy);
   dd[2] = (move->ez - move->sz);
   dd[3] = (move->ea - move->sa);
   dd[4] = (move->eb - move->sb);
   dd[5] = (move->ec - move->sc);
   //Make the Vector for the move a unit length Vector
   steps[0] = dd[0] * MainPlanner->StepsX;
   steps[1] = dd[1] * MainPlanner->StepsY;
   steps[2] = dd[2] * MainPlanner->StepsZ;
   steps[3] = dd[3] * MainPlanner->StepsA;
   steps[4] = dd[4] * MainPlanner->StepsB;
   steps[5] = dd[5] * MainPlanner->StepsC;

   double vdist = 0;
   long double udist = 0;
   int zeros = 0;
   for( int x = 0; x < State.nAxis; x++)
   {
     int v = (int)(steps[x] + fractions[x]); //add in any fractional steps. 
	 fractions[x] = steps[x] - ((double)v);
	 if( v == 0) zeros++;
     temp.Format( "%s %i,", Com, v );
     udist += dd[x] * dd[x];
     Com = temp;
   }
   if( zeros == State.nAxis ) return; //no actual movement;

   udist = sqrt( udist ); // unit distance..
   double time = udist / add->velocity; // time of move in units. 
   Uv[0] = fabs(dd[0]/time * MainPlanner->StepsX);
   Uv[1] = fabs(dd[1]/time * MainPlanner->StepsY);
   Uv[2] = fabs(dd[2]/time * MainPlanner->StepsZ);
   Uv[3] = fabs(dd[3]/time * MainPlanner->StepsA);
   Uv[4] = fabs(dd[4]/time * MainPlanner->StepsB);
   Uv[5] = fabs(dd[5]/time * MainPlanner->StepsC);
   vdist = Uv[0]*Uv[0] + Uv[1]*Uv[1] + Uv[2]*Uv[2] + Uv[3]*Uv[3] + Uv[4]*Uv[4] + Uv[5]*Uv[5]; 
   vdist = sqrt( vdist );//This is the Steps per sec that the Galil needs (or it should be :) )
     
 //TO get the Accel we need to calc it from scratch because there is no way to convert it :( 
 double Time = 0;//This will give us the rate that we would like to accel the move at...
 //Now we will check to see that we are not going to out accel any of the other axis
 if( Uv[0] > 0 && Time < Uv[0]/(MainPlanner->Acceleration[0]* MainPlanner->StepsX))   
  Time =  Uv[0]/(MainPlanner->Acceleration[0]* MainPlanner->StepsX);
 if( Uv[1] > 0 && Time < Uv[1]/MainPlanner->Acceleration[1]* MainPlanner->StepsY)   
  Time =  Uv[1]/(MainPlanner->Acceleration[1]* MainPlanner->StepsY);
 if( Uv[2] > 0 && Time < Uv[2]/MainPlanner->Acceleration[2]* MainPlanner->StepsZ)   
  Time =   Uv[2]/(MainPlanner->Acceleration[2]* MainPlanner->StepsZ);
 if( Uv[3] > 0 && Time < Uv[3]/MainPlanner->Acceleration[3]* MainPlanner->StepsA)   
  Time =  Uv[3]/(MainPlanner->Acceleration[3]* MainPlanner->StepsA);
 if( Uv[4] > 0 && Time < Uv[4]/MainPlanner->Acceleration[4]* MainPlanner->StepsB)   
  Time =  Uv[4]/(MainPlanner->Acceleration[4]* MainPlanner->StepsB);
 if( Uv[5] > 0 && Time < Uv[5]/MainPlanner->Acceleration[5]* MainPlanner->StepsC)   
  Time =  Uv[5]/(MainPlanner->Acceleration[5]* MainPlanner->StepsC);
  if(Time == 0)Time = 10;
  double atime = vdist/Time;
  CString acc;
  acc.Format("VA %i",(int)atime);
  SendCommand(acc);
   if(!State.IsMoving ) SendCommand("VD 2000000"); //deceleration
  temp = Com.Left( Com.GetLength() - 1);
  if( vdist > 3000000 ) vdist = 12000000;
  Com.Format("%s <%i ", temp, (((int)vdist ) & 0xfffffffe));
  SendCommand(  Com,true  ); //no binary on this command

  MainPlanner->ExternalStill = false;
  Ids[IdIn & 0xff] = add->line;
  IdIn++;
  if(!State.IsMoving ) SendCommand( "BGS" );
  State.IsMoving = true;
  

  
  if( DebugCtl & 0x02 )
 {
    debug.WriteString( Com );
    CString t;
	t.Format( "  with : %.4f to %.4f  starting at %.4f \n", steps[0], dd[0] + move->sx,  move->sx); 
    debug.WriteString( t );
 }

}
void GalilControl::HomeAxis(short axis)
{
	
	if(State.HomeData.HomeStage != SEQNONE)
		return;//Exit because we need to finish the home move that we are doing now.
	State.HomeData.IsHoming = true;
	State.HomeData.HomingAxis = axis;
	Engine->Axis[axis].Homing = true;
	static int Homes[6] = { 2,5,8,11,14,17 };//This is the InSigs that are the home inputs...
	static CString AxisName[6] = { "X","Y","Z","A","B","C" };
	int intaxis = (int)axis;
	CString Com;
	
	MainPlanner->ExternHomedMask = 0;//No idea why the hell I am doing this....
	
			
	double JogFeed = MainPlanner->Velocities[axis] * (double)MainPlanner->RefSpeed[axis] / 100;
	int    direction = MainPlanner->AxisNegs[axis];

	//spd should be negative if the direction is backwards.
	int HomeDir = 1;
	if ((direction != 0) ^ (Engine->Directions[axis] != 0))
		HomeDir = -1;

	State.HomeData.AxisString = "";//Build up the sting to tell the galil what axis we are working with...
	for(int x=0;x<axis;x++)
			 State.HomeData.AxisString =  State.HomeData.AxisString +",";

	int AciveHi =1;
	if(Engine->InSigs[ Homes[intaxis] ].Negated) AciveHi = -1;
	int accs[7];
	int Vel[7];
	
	for( int x = 0; x < State.nAxis + 1; x++)
	{
		accs[x] = (int)(MainPlanner->Acceleration[x]  * MainPlanner->StepsPerAxis[x]);
		Vel[x] = (int)((MainPlanner->Velocities[x] * (double)MainPlanner->RefSpeed[x] / 100)*MainPlanner->StepsPerAxis[x]);
	}
	State.HomeData.HomeVel = Vel[axis]*HomeDir;
	//set the accelerations of tha axis..
	SendCommand("ST");
	Com.Format( "AC %d,%d,%d,%d,%d,%d ", accs[0], accs[1], accs[2], accs[3], accs[4], accs[5], accs[6] );
	m_DMCWin->Command(Com.GetBuffer(20));
	
	Com.Format( "DC %d,%d,%d,%d,%d,%d ", accs[0], accs[1], accs[2], accs[3], accs[4], accs[5], accs[6] );
	m_DMCWin->Command(Com.GetBuffer(20));
	
	SendCommand( Com );
	//Now we are going to start the jog move looking for the Home switch...
	Com = "JG";
	for(x=0;x<6;x++)
	{
		if(x!=0)Com += ",";
		if(axis == x)
			Com.Format("%s%d", Com ,State.HomeData.HomeVel);
		else
			Com+="0";
	}
	

	SendCommand( Com  ); // Start the Axis moving... 
	SendCommand( "BG" );//Now Start the Home Jog Move...
	
	State.HomeData.HomeStage = FINDSWITCH;//Tell the Home sequencer that we are looking for the home switch...
	MainPlanner->ExternalStill = false;
}
