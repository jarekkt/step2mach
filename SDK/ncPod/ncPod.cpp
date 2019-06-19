// ncPod.cpp : implementation file
//

#include "stdafx.h"
#include "MachDevice.h"
#include "ncPod.h"
#include "ExternalMovement.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "XMLProfile.h"
#include "ExternalMovement.h"
#include "math.h"

CString VerString = "&ncPod V2.00.059 Config ";


#pragma warning( disable : 4305 )// truncation warnings..
#pragma warning( disable : 4309 )// "" ""
#pragma warning( disable : 4311 )// "" ""

extern  double total[6] = { 0,0,0,0,0,0 };

extern int RangeStart;
 


extern TrajectoryControl *MainPlanner; //used for most planner funcitons and program control 
extern CMach4View *MachView;  //used for most framework and configuration calls. 
extern TrajBuffer *Engine;     //Ring0 memory for printer port control and other device syncronisation
extern setup *_setup;          //Trajectory planners setup block. Always in effect
extern int HomingType;
extern double PullOff[6];
 

typedef  void (_cdecl *t_init)();
typedef  int  (_cdecl *t_open)( int );
typedef  int  (_cdecl *t_bulkwrite)( void *, int, unsigned char*, int, int );
typedef  int  (_cdecl *t_bulkread)( void *, int, unsigned char*, int, int );
typedef  int  (_cdecl *t_close)( void *);
typedef  int  (_cdecl *t_release)( void *, int );
typedef  LPCSTR  (_cdecl *t_err)( );

extern VoidLPCSTR         Code;         // void    Code( "G0X10Y10" );
extern  void  myReset();



/*
int usb_bulk_write(usb_dev_handle *dev, int ep, char *bytes, int size, int timeout);
int usb_bulk_read(usb_dev_handle *dev, int ep, char *bytes, int size, int timeout);
int usb_release_interface(usb_dev_handle *dev, int interface);
int usb_close(usb_dev_handle *dev);
usb_dev_handle *usb_open(struct *usb_device dev);
*/

t_init         usb_init;
t_open         usb_open;
t_bulkwrite    usb_bulk_write;
t_bulkread     usb_bulk_read;
t_close        usb_close; 
t_release      usb_release_interface;
t_err          usb_strerror;

double fractions[6]; //holding variable for fractional steps..
// ncPod

IMPLEMENT_DYNAMIC(ncPod, CWnd)
ncPod::ncPod()
{
   //lets set connected 0, so the updater knows if it should update the status, 
	Connection.Connected = false;
	SDOpen = false;
	BufferHolding = false;
	MainPlanner->DoExternalProbe = true;

	for( int x = 0; x< 6; x++)
	{ 
	  fractions[x] = 0; 
	  cCount[x] = 0;
	  vtotal[x] = 0;
	  total[x] = 0;
	}
	//diags test
	StartDiagBuff = false;
	ProbeRead = false;
	DiagSeq = 0;
	SpinTarget = 400;
	SpinCur = 400;
	WaitForMove = 0;
	//debug.Open("PodBlocks.bin", CFile::modeCreate | CFile::modeWrite , NULL);
}

ncPod::~ncPod()
{
	//debug.Flush();
	//debug.Close();
	Close();
}


BEGIN_MESSAGE_MAP(ncPod, CWnd)
END_MESSAGE_MAP()

 

// ncPod message handlers

 
 
 

void    ncPod::SetCycleTime(int time)
{
  switch( time )
  {
  case( 0 ): DripTime = 64  ; DripSel = 0; break;
  case( 1 ): DripTime = 75  ; DripSel = 1; break;
  case( 2) : DripTime = 128 ; DripSel = 2; break;
  case( 3 ): DripTime = 150 ; DripSel = 3; break;
  case( 4 ): DripTime = 225;  DripSel = 4; break;
  case( 5 ): DripTime = 300;  DripSel = 5; break;
  case( 6 ): DripTime = 375;  DripSel = 6; break;
  case( 7 ): DripTime = 1024;   DripSel = 7; break;
  }


}

void    ncPod::SetDrip()
{
   SetCycleTime( DripSel );
   MainPlanner->ExBufferHi = 350;
   switch( DripSel )
   {
   case( 0 ):  MainPlanner->ExTime = .00085; break;
   case( 1 ):  MainPlanner->ExTime = .001; break;
   case( 2 ):  MainPlanner->ExTime = .00177; break;
   case( 3 ):  MainPlanner->ExTime = .002; break;
   case( 4 ):  MainPlanner->ExTime = .003; break;
   case( 5 ):  MainPlanner->ExTime = .004; break;
   case( 6 ):  MainPlanner->ExTime = .005; break;
   case( 7 ):  MainPlanner->ExTime = .00976563; break;
   }
   MainPlanner->ExternalType = EX_VMS; //EX_COMMAND;
   
   ClearCommand( );
   Command.velocity = (int)DripTime;  //set for 1/75000 * 300 for 4ms mode.. 75 = 1ms 300 = 4ms..
   Command.commandEnum = USBSETUP;
   SendCommand();
     //and one to signify that dats is about to come in..
   ClearCommand( );
   SendSimpleCommand( USBDRIPFEED );
   ClearCommand();
   Command.loc = 4;
   Command.commandEnum = USBSETSTATUSMODE;
   SendCommand();

}

int FindMenuItem(CMenu* Menu, LPCTSTR MenuString)
{
   ASSERT(Menu);
   ASSERT(::IsMenu(Menu->GetSafeHmenu()));

   int count = Menu->GetMenuItemCount();
   for (int i = 0; i < count; i++)
   {
      CString str;
      if (Menu->GetMenuString(i, str, MF_BYPOSITION) &&
         (strcmp(str, MenuString) == 0))
         return i;
   }

   return -1;
}


bool ncPod::Connect()
{
	//set the max speeds of MAch3 for this device..
	for( int x = 0; x < 7; x++ )
		MainPlanner->ExternalPulseRates[x] = 75000;
	SEQUENCE = PNOSEQ;
	memset( buffer, 0, 64 );
    HMODULE hLib = LoadLibrary( "ncPOD.dll" );
	char mod[150];
	GetModuleFileName((HMODULE)hLib, (LPTSTR)mod, 150);
	usb_init =       (t_init)GetProcAddress((HMODULE)hLib, "usb_init");
    usb_open =       (t_open)GetProcAddress((HMODULE)hLib, "usb_open");
	usb_bulk_write = (t_bulkwrite)GetProcAddress((HMODULE)hLib, "usb_bulk_write");
	usb_bulk_read =  (t_bulkwrite)GetProcAddress((HMODULE)hLib, "usb_bulk_read");
	usb_close     =  (t_close)GetProcAddress((HMODULE)hLib, "usb_close"); 
	usb_release_interface     =  (t_release)GetProcAddress((HMODULE)hLib, "usb_release_interface"); 
	usb_strerror              =  (t_err)GetProcAddress((HMODULE)hLib, "usb_strerror"); 
    
	//OK, we have the routines, lets connect to the pod..
	Open();
 	if( !Connection.Connected ) return Connection.Connected;

	
    SetDrip();
	MainPlanner->m_MutiHome = false;
	//set indexes to MAch3 indexes.
	ClearCommand();
	Command.commandEnum = USBSETCOORDSXYZABC;
	Command.axisX = Engine->Axis[0].Index * (Engine->Directions[0] ? 1: -1);
	Command.axisY = Engine->Axis[1].Index * (Engine->Directions[1] ? 1: -1);
	Command.axisZ = Engine->Axis[2].Index * (Engine->Directions[2] ? 1: -1);
	Command.axisA = Engine->Axis[3].Index * (Engine->Directions[3] ? 1: -1);
	Command.axisB = Engine->Axis[4].Index * (Engine->Directions[4] ? 1: -1);
	Command.axisC = Engine->Axis[5].Index * (Engine->Directions[5] ? 1: -1);
	Command.loc = 0x3f;
	SendCommand( );

	ClearCommand();
	Command.loc = 4;
	Command.commandEnum = USBSETSTATUSMODE;
	SendCommand();

	ReadStatus();


static bool menued = false;

if( !menued)
{
	menued = true;
	CFrameWnd *MachFrame = MachView->MachFrame;
	CMenu *menu = MachFrame->GetMenu();
	HMENU hSubmenu = CreatePopupMenu();
	int pos = FindMenuItem(menu,"PlugIn Control");
    //here we can add menu items to MAch3's menu..
	int x = pos;
	HMENU control = GetSubMenu( menu->m_hMenu, pos);

    InsertMenu ( control, -1, MF_BYPOSITION, RangeStart , _T(VerString) );
    //we can add as many as we want up to the amount we requested in the implementation file..
	//here we add the menu to the Mach3 menu..
	//InsertMenu( control , -1 , MF_POPUP, (UINT_PTR) hSubmenu, _T("&ncPod Control") );  //this adds the probing menu item. 
	MachFrame->DrawMenuBar();
} 

     
//This is where we set the amount of pull off for the Pod... 
	return Connection.Connected;
}


void    ncPod::Stop()
{
	SEQUENCE = PNOSEQ;
	Engine->Homing = false;
	if( !MainPlanner->ExternalStill )
	{ //stop the thing..
       SendSimpleCommand(SDFINISHMOVE); //this should stop us..
	   //Engine->Sync = true;
	}
	nHolding = 0;
	nHomePos = 0;

}

void  ncPod::DoProbe()
{

	ClearCommand();
    //no probeing if the probe is made..
	//we'll use absolute number because Mach3 calculated them already.
	ProbeRead = false; //this will be true after the probe.
	Command.commandEnum = USBPROBEABSOLUTEXYZABC;
	Command.loc = Engine->InSigs[DIGITIZE].Negated ? 1:2 ; //NC probe.. 1 is NO probe, 2 is NC..
	Command.velocity = 1000; //as a test
	Command.axisX = -(int)(MainPlanner->aProbeX * MainPlanner->StepsPerAxis[0]);
	Command.axisY = -(int)(MainPlanner->aProbeY * MainPlanner->StepsPerAxis[1]);
	Command.axisZ = -(int)(MainPlanner->aProbeZ * MainPlanner->StepsPerAxis[2]);
	Command.axisA = -(int)(MainPlanner->aProbeA * MainPlanner->StepsPerAxis[3]);
    Command.axisB = -(int)(MainPlanner->aProbeB * MainPlanner->StepsPerAxis[4]);
	Command.axisC = -(int)(MainPlanner->aProbeC * MainPlanner->StepsPerAxis[5]);
    WaitForMove = 5;
	SEQUENCE = PPROBE;
	SendCommand();
 
}

void    ncPod::HomeDeRef()
{
	//this routine derefs a single axis, all handled in the plugin as MAch3 is waiting for the home to be completed..
    //first find the distance to move off..
	double dist;
    //if( _setup->length_units == MMS )
    //    dist = 6.25;
	//   else
	//    dist = .25; //we now have 6 target positions.. 1/2" or 12.5mm's from switch..
	dist = PullOff[HomeAxis];
	if(dist<=0) return;
	dist = dist *  (MainPlanner->AxisNegs[HomeAxis] ? 1:-1);
	if( !Engine->Directions[ HomeAxis ] ) dist = -dist;
	
    double JogFeed = (MainPlanner->Velocities[HomeAxis]); //rapid steps per second
    double vel = (int)( JogFeed * MainPlanner->StepsPerAxis[HomeAxis]);
   
	ClearCommand();
    double moveaccel =  ((MainPlanner->Acceleration[HomeAxis] * MainPlanner->StepsPerAxis[HomeAxis])* 32.767) / 75000;
    Command.axisX = (int)moveaccel;
    SendSimpleCommand( USBSETINDEPENDENTACCEL );
    ClearCommand();

	//now move ...

	int distance = (int)( dist * MainPlanner->StepsPerAxis[HomeAxis] );
	
    switch( HomeAxis )
    {
	   case (0) : Command.axisX = distance; break;
	   case (1) : Command.axisY = distance; break;
       case (2) : Command.axisZ = distance; break;
	   case (3) : Command.axisA = distance; break;
	   case (4) : Command.axisB = distance; break;
	   case (5) : Command.axisC = distance; break;
    }

	for (int x = 3; x < 6; ++x)
		if (Engine->Axis[x].Slave && Engine->Axis[x].SlaveAxis == HomeAxis) 
		{
			switch( x )
			{
			  case( 3): Command.axisA = distance; break;
			  case( 4): Command.axisB = distance; break;
			  case( 5): Command.axisC = distance; break;
			}
		}

    Command.velocity = (int)vel;
    SendSimpleCommand(USBRELATIVELINEARPOSITIONMOVEXYZABC);
   
}


void   ncPod::Home(int axis , bool slow )
{
	if( Engine->OffLine)  return;
    HomeAxis = axis;
	if( !MainPlanner->m_MutiHome || HomingType == 3 ) 
	{
		CString mess;
		mess.Format("Homing axis:%d",axis);
		HomeSingle( axis , slow );
	}
	else
	{
     //first, lets set an acceleration up..(int) ((MainPlanner->Acceleration[0] * MainPlanner->StepsPerAxis[ 0])* 32.767) / 75000; 
	   double dists[6] = { 0,0,0,0,0,0 };
	   double accel = 99999;
       axis = MainPlanner->m_HomeMask;
   	   double speed = 999999;
		if( axis & 0x01 && Engine->Axis[0].Enable )
		{
			speed = min(speed, ((double)MainPlanner->Velocities[0]) * ( ((double)MainPlanner->RefSpeed[ 0]) / 100)); //units per second
			if( slow ) speed = speed / 10;
            int distance = 99999 *  (MainPlanner->AxisNegs[0] ? 1:-1);
			if( !Engine->Directions[ axis ] ) distance = -distance;
			dists[0] = distance; 
			accel = min( accel,  ((MainPlanner->Acceleration[0] * MainPlanner->StepsPerAxis[ 0])* 32.767) / 75000);
		}
		if(( axis >> 1) & 0x01 && Engine->Axis[1].Enable )
		{
			speed = min(speed, ((double)MainPlanner->Velocities[1]) * ( ((double)MainPlanner->RefSpeed[ 1]) / 100)); //units per second
			if( slow ) speed = speed / 10;
            int distance = 99999 *  (MainPlanner->AxisNegs[1] ? 1:-1);
			if( !Engine->Directions[ axis ] ) distance = -distance;
			dists[1] = distance; 
			accel = min( accel,  ((MainPlanner->Acceleration[1] * MainPlanner->StepsPerAxis[1])* 32.767) / 75000);
		}
        if(( axis >> 2) & 0x01 && Engine->Axis[2].Enable)
		{
			speed = min(speed, ((double)MainPlanner->Velocities[2]) * ( ((double)MainPlanner->RefSpeed[ 2]) / 100)); //units per second
			if( slow ) speed = speed / 10;
            int distance = 99999 *  (MainPlanner->AxisNegs[2] ? 1:-1);
			if( !Engine->Directions[ axis ] ) distance = -distance;
			accel = min( accel,  ((MainPlanner->Acceleration[2] * MainPlanner->StepsPerAxis[2])* 32.767) / 75000);
			dists[2] = distance; 
		}
		if(( axis >> 3) & 0x01 && Engine->Axis[3].Enable)
		{
			speed = min(speed, ((double)MainPlanner->Velocities[3]) * ( ((double)MainPlanner->RefSpeed[ 3]) / 100)); //units per second
			if( slow ) speed = speed / 10;
            int distance = 99999 *  (MainPlanner->AxisNegs[3] ? 1:-1);
			if( !Engine->Directions[ axis ] ) distance = -distance;
			accel = min( accel, ((MainPlanner->Acceleration[3] * MainPlanner->StepsPerAxis[3])* 32.767) / 75000);
			dists[3] = distance; 
		}
		if(( axis >> 4) & 0x01 && Engine->Axis[4].Enable)
		{
			speed = min(speed, ((double)MainPlanner->Velocities[4]) * ( ((double)MainPlanner->RefSpeed[4]) / 100)); //units per second
			if( slow ) speed = speed / 10;
            int distance = 99999 *  (MainPlanner->AxisNegs[4] ? 1:-1);
			if( !Engine->Directions[ axis ] ) distance = -distance;
			dists[4] = distance;
			accel = min( accel,((MainPlanner->Acceleration[4] * MainPlanner->StepsPerAxis[4])* 32.767) / 75000);
		}
		if(( axis >> 5) & 0x01 && Engine->Axis[5].Enable )
		{
			speed = min(speed, ((double)MainPlanner->Velocities[5]) * ( ((double)MainPlanner->RefSpeed[ 5]) / 100)); //units per second
			if( slow ) speed = speed / 10;
            int distance = 99999 *  (MainPlanner->AxisNegs[5] ? 1:-1);
			if( !Engine->Directions[ axis ] ) distance = -distance;
			dists[5] = distance; 
			accel = min( accel, ((MainPlanner->Acceleration[5] * MainPlanner->StepsPerAxis[ 5])* 32.767) / 75000);
		}
		//set accel
		ClearCommand();
		Command.axisX = (int)accel;
        SendSimpleCommand( USBSETINDEPENDENTACCEL );
         
		//send home command;
        ClearCommand();
		Command.axisX = (int)dists[0];
		Command.axisY = (int)dists[1];
		Command.axisZ = (int)dists[2];
		Command.axisA = (int)dists[3];
		Command.axisB = (int)dists[4];
		Command.axisC = (int)dists[5];
        Command.velocity = 0;//(int)speed;
        Command.commandEnum =  USBINDEPENDENTHOME;//USBINTERPHOME;
        SendCommand();
		Engine->Homing = true;
		if( !slow ) SEQUENCE = PHOMING;
		else
			SEQUENCE = PHOMING4; //final home sequence..
	    MainPlanner->ExternalStill = false; 
		WaitForMove = 5;
	}

}

void   ncPod::HomeSingle(int axis, bool slow )
{
 	if( !Engine->Axis[axis].Enable || HomingType == 0 || Engine->Axis[axis].Slave) 
	{
       Engine->Referenced[axis] = true;
	   Engine->Axis[HomeAxis].Index = Engine->RefCounts[HomeAxis];
       ClearCommand();
	   Command.axisX = Engine->Axis[0].Index * (Engine->Directions[0] ? 1: -1);
	   Command.axisY = Engine->Axis[1].Index * (Engine->Directions[1] ? 1: -1);
	   Command.axisZ = Engine->Axis[2].Index * (Engine->Directions[2] ? 1: -1);
	   Command.axisA = Engine->Axis[3].Index * (Engine->Directions[3] ? 1: -1);
	   Command.axisB = Engine->Axis[4].Index * (Engine->Directions[4] ? 1: -1);
	   Command.axisC = Engine->Axis[5].Index * (Engine->Directions[5] ? 1: -1);
	   Command.loc = 0x3f;
	   SendSimpleCommand(USBSETCOORDSXYZABC);
	   Engine->Homing = false;
	   Engine->Sync = true;
	   MainPlanner->SoftWait &=  ( 0xffffffffffffffff ^ ( ((__int64)1) << EXHOME));
	   return;
	}
	//AccelConstant = (AccelerationInStepsSecond * 32.767) / 75000
    //USBSETINDEPENDENTACCEL = 63 command
    ClearCommand();
	Command.axisX = (int) ((MainPlanner->Acceleration[0] * MainPlanner->StepsPerAxis[ 0])* 32.767) / 75000;  
	Command.axisY = (int) ((MainPlanner->Acceleration[1] * MainPlanner->StepsPerAxis[ 1])* 32.767) / 75000;  
	Command.axisZ = (int) ((MainPlanner->Acceleration[2] * MainPlanner->StepsPerAxis[ 2])* 32.767) / 75000;  
	Command.axisA = (int) ((MainPlanner->Acceleration[3] * MainPlanner->StepsPerAxis[ 3])* 32.767) / 75000;   
	Command.axisB = (int) ((MainPlanner->Acceleration[4] * MainPlanner->StepsPerAxis[ 4])* 32.767) / 75000;   
	Command.axisC = (int) ((MainPlanner->Acceleration[5] * MainPlanner->StepsPerAxis[ 5])* 32.767) / 75000;   
		
	SendSimpleCommand( USBSETINDEPENDENTACCEL );
	ClearCommand();

	if( HomingType == 3 ) //set polarity to 1.
	{
		Command.commandEnum = HOMEPOLARITY ;
	    Command.loc = 1; //polarity, nc...
	    SendCommand();
		ClearCommand();
	}


 
	double speed = ((double)MainPlanner->Velocities[axis]) * ( ((double)MainPlanner->RefSpeed[ axis]) / 100); //units per second
	if( slow ) speed = speed / 10; //slow down for final homing..
	int distance = -999999;// *  (MainPlanner->AxisNegs[axis] ? 1:-1);
	if( Engine->Directions[ axis ] ) distance = -distance;
	if( MainPlanner->AxisNegs[axis] ) distance = -distance;

	switch(axis)
	{
	case(0): Command.velocity = (int) (speed * MainPlanner->StepsPerAxis[ 0]); Command.axisX = distance; break;
    case(1): Command.velocity = (int) (speed * MainPlanner->StepsPerAxis[ 1]); Command.axisY = distance; break;
    case(2): Command.velocity = (int) (speed * MainPlanner->StepsPerAxis[ 2]); Command.axisZ = distance; break;
    case(3): Command.velocity = (int) (speed * MainPlanner->StepsPerAxis[ 3]); Command.axisA = distance; break;
    case(4): Command.velocity = (int) (speed * MainPlanner->StepsPerAxis[ 4]); Command.axisB = distance; break;
    case(5): Command.velocity = (int) (speed * MainPlanner->StepsPerAxis[ 5]); Command.axisC = distance; break;
	default: return; //no correct axis
	}
	//slaving check..
	for (int x = 3; x < 6; ++x)
		if (Engine->Axis[x].Slave && Engine->Axis[x].SlaveAxis == axis) 
		{
			switch( x )
			{
			  case( 3): Command.axisA = distance; break;
			  case( 4): Command.axisB = distance; break;
			  case( 5): Command.axisC = distance; break;
			}
		}
     
	
	 Engine->Homing = true;
	// Command.velocity = 0; //set to zero for soft homing..
  if( HomingType != 3 )
  {
	Command.commandEnum =  USBINDEPENDENTHOME;
	 Command.loc = 0; //0 = softhoming..1 is hard homing.
  }
  else
  {
    Command.commandEnum = HOMEUSINGLIMITS ;
    Command.loc = 1; //0 = softhoming..1 is hard homing.
  }

    SendCommand();
    if( !slow )SEQUENCE = PHOMING;
	else
		 SEQUENCE = PHOMING4; //final home sequence..
	MainPlanner->ExternalStill = false; 
	WaitForMove = 5;

}




void   ncPod::ClearCommand( )
{

   Command.commandEnum = 0;
   Command.synch = 0;
   Command.axisX = 0;
   Command.axisY = 0;
   Command.axisZ = 0;
   Command.axisA = 0;
   Command.axisB = 0;
   Command.axisC = 0;
   Command.velocity = 0;
   Command.loc = 0;
   Command.sequenceNumber = 0;

}

void    ncPod::SendCommand( ) 
{
	if( handle == 0) return;
	index = 0;
	write1(Command.commandEnum);
	write4(Command.synch);
	write4(Command.axisX);
	write4(Command.axisY);
	write4(Command.axisZ);
	write4(Command.axisA);
	write4(Command.axisB);
	write4(Command.axisC);
	write4(Command.velocity);
	write2(Command.loc);
	write4(Command.sequenceNumber);
	returnCode = usb_bulk_write( (void*)handle, COMMANDENDPOINT, buffer, 64, 300);
	if( returnCode != 64 ) CheckError();
	else
	{
		Connection.LastError = 0;
	}
};


void    ncPod::SendEP1Command() 
{
	returnCode = usb_bulk_write( (void*)handle, VELPOINT, bufferout, 512, 200);
	if( returnCode < 512 ) 
	{
		if( returnCode >0 )
			int temp = 1;
		BufferHolding = true;
        Holding++;
	}
	else
	{
		//debug.Write( bufferout, 512 );
		Holding = 0;
		BufferHolding = false;
		memset( bufferout, 0, 512 );
		Connection.LastError = 0;
	}
};


void ncPod::CheckError()
{
  //just for debugging..
   LPCSTR err = usb_strerror();
   Connection.LastError = returnCode;
   Connection.ErrorString = err;

}


void    ncPod::Close()
{
  if( handle == 0 ) return;
  usb_release_interface((void*)handle,0);
  usb_close((void*)handle);
};
 

void  ncPod::ReadStatus()
{
 static errcnt = 0;

	  if( handle == 0 ) return;
      returnCode = usb_bulk_read((void*)handle, STATUSENDPOINT, buffer, 64, 150);
	  if( returnCode != 64 ) 
	  {
	    CheckError();
		errcnt++;
	 	if( errcnt > 60 )
		{
			Engine->EStop = true;
			errcnt = 0;
			SetMachError("The Pod has ceased to Respond...");
			return;
		}
	  }
	 

      Connection.LastError = 0;
	  if (returnCode < 64)
	  { 
		  PodStatus.stat = STATPOWEREDON;
		  return;
	  }
      //now copy the status in..
     if( 0) //(PodStatus.stat & STATLIMITHIT) != 0 ) //not working....
	  {
		  if( !Engine->EStop )
		  {
			  Engine->EStop = true;
		      SetMachError("The Pod has called for an Estop...");
		  }
	  }

      CString  err;
	  CString  stat;
	  index = 0;

	  PodStatus.fullStepsX = read4() * ((Engine->Directions[0]== 0) ? -1 : 1);
	  PodStatus.fullStepsY = read4() * ((Engine->Directions[1]== 0) ? -1 : 1);
	  PodStatus.fullStepsZ = read4() * ((Engine->Directions[2]== 0) ? -1 : 1);
	  PodStatus.fullStepsA = read4() * ((Engine->Directions[3]== 0) ? -1 : 1);
	  PodStatus.fullStepsB = read4() * ((Engine->Directions[4]== 0) ? -1 : 1);
	  PodStatus.fullStepsC = read4() * ((Engine->Directions[5]== 0) ? -1 : 1);
	  PodStatus.synch = read4();
	  PodStatus.outio = read1();
	  PodStatus.inio = read1();
	  PodStatus.ack = read1();
	  PodStatus.stat = read2();
	  PodStatus.range = read2();
	  PodStatus.Q = read2();
	  PodStatus.firmwareVersion = read2();
	  PodStatus.TimeStamp = read2();
	  PodStatus.NumBuffer = read1();
      PodStatus.NumQBuffer = read1();  
      PodStatus.Homestatus = read1();
	  PodStatus.ProbexAxis = read4();                                       
      PodStatus.ProbeyAxis = read4();                                         
      PodStatus.ProbezAxis = read4();                                         
      PodStatus.ProbeaAxis = read4();                                        
      PodStatus.ProbebAxis = read4();   
      

  	  bool laststill = MainPlanner->ExternalStill;

	  if( (PodStatus.stat & STATINTERPMOVEINPROGRESS) != 0  ||
		  (PodStatus.stat & STATVELOCITYMOVEINPROGRESS) !=0)  
      {
		  MainPlanner->ExternalStill = false;
	  }
	  else
	  {
		  MainPlanner->ExternalStill = true;
		  if( !laststill )
			  for( int x = 0; x < 6; x++ )
		         fractions[x] = 0;
	  }
	      

     if( Engine->Sync )
	  {
		for( int x = 0; x< 6; x++)
           fractions[x] = 0;       //zero out the fractionator, its about to get synced anyway..
      }
      if( !MainPlanner->ExternalStill && !Engine->Jogging )
      {
		  Engine->DisplayLine = PodStatus.synch;
      }

	  if((PodStatus.stat & STATLIMITHIT) != 0  && !Engine->EStop )
	  {
		  Engine->EStopReason = ESTOPINPUTLINE;
		  Engine->EStop = true;
		  myReset();
	  }

      return;
};
void    ncPod::Open()
{
	CString mess;
    ClearCommand( );
	usb_init();
	Connection.Connected = false;
	Holding = 0;
	handle  =  usb_open(0);
	SendSimpleCommand(USBRUNMODE);
	if( Connection.LastError == 0 ) Connection.Connected = true;
	Sleep(20);
	if( Connection.Connected )
	{
		ReadStatus();
		SetMachError( "USB Com Channel Open.");
	}
	else SetMachError("Failed to open USB Channel!.");

	Command.commandEnum = USBSETINDEPENDENTACCEL;
	Command.axisX = 500;
	SendCommand();
};

void ncPod::SendSimpleCommand(char commandEnum)
{
  Command.commandEnum = commandEnum;
  SendCommand();
}

//Mach3 Update and movement commands form here ///////////////////////////////////////////////

//Called every 100ms or so to get current status, motor positions, inputs and and determine if outputs 
// need to be updated.If so, update them..

void   ncPod::Update( )
{
 static int cnt = 0;

 if( SpinCur != SpinTarget )
 {
	 if( SpinCur < SpinTarget)
	 {
		 SpinCur += 40;
		 if( SpinCur > SpinTarget) SpinCur = SpinTarget;
	 }
	 if( SpinTarget < SpinCur)
	 {
		 SpinCur -= 40;
		 if( SpinCur < SpinTarget) SpinCur = SpinTarget;
	 }
	 ClearCommand();
	 Command.commandEnum = USBOUTPUT_PWM;
	 Command.loc = SpinCur; //send a new PWM duty cycle..
	 SendCommand();
 }

    ReadStatus();
	if( Connection.LastError != 0 )
	{ //we have a problem. Estop, then report and deal with it.
       Engine->EStop = true;
	   cnt++;
	   if( cnt > 15 ) 
	   {
		   Connection.Connected = false;
           SetMachError(" ncPod Communications error!"); 
	   }
       return;
	}

	cnt = 0;

//So now get ms of time from then till now.. 
	static unsigned short time = PodStatus.TimeStamp;
	int timediff = PodStatus.TimeStamp - time;
	time = PodStatus.TimeStamp;
	if( time < 0 ) time += 65535;
	int pos[6];
	double vels[6];

	for( int x = 0; x < 6; x++)
		  pos[x] = Engine->Axis[x].Index; //save old postions
	SetPositions(); //and update
    for( int x = 0; x < 6; x++)
	{
	     vels[x] = ( fabs( ((double)Engine->Axis[x].Index) - ((double)pos[x]))) / (double)timediff;
		
		 if( MainPlanner->ExTime == .001 ) Engine->StatLast[x] = (int) vels[x] * 200 ;  
		 else  
		 if( MainPlanner->ExTime == .002 ) Engine->StatLast[x] = (int) vels[x] * 100 ;  
		 else  
		 if( MainPlanner->ExTime == .003 ) Engine->StatLast[x] = (int) (vels[x] * 66.666);  
		 else  
		 if( MainPlanner->ExTime == .004 ) Engine->StatLast[x] = (int) vels[x] * 50 ;  
		 else  
		 if( MainPlanner->ExTime == .005 ) Engine->StatLast[x] = (int) vels[x] * 40 ;  
		 else  
		 if( MainPlanner->ExTime == .00085 ) Engine->StatLast[x] = (int) (vels[x] * 235.2941176);  
		 else  
		 if( MainPlanner->ExTime == .00177 ) Engine->StatLast[x] = (int) (vels[x] * 112.9943503);  
         
	 }
    //now do all the inputs and outputs.
	GetInputs();
	SetOutputs();
if( SEQUENCE == PNOSEQ ) //only send movement if no sequence is set or if homing in a sequence....
{
	SendHoldingMovement();
	SendHoldingMovement(); //send two buffers if possibel.. May cause a hold, but then the next one is ready..
}
	HandleSequences();
  
}

void ncPod::SetMachError(CString Message)
{
	CString *err = &MainPlanner->LastError;
	if( err != NULL) *err = Message;

}



