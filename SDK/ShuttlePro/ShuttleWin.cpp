// ShuttleWin.cpp : implementation file
//

#include "stdafx.h"
#include "MachDevice.h"
#include "ShuttleWin.h"
#include ".\shuttlewin.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "math.h"
#include "hidsdi.h"
#include "MachDevImplementation.h"


extern TrajectoryControl *MainPlanner; //used for most planner funcitons and program control 
extern CMach4View *MachView;  //used for most framework and configuration calls. 
extern TrajBuffer *Engine;     //Ring0 memory for printer port control and other device syncronisation
extern setup *_setup;          //Trajectory planners setup block. Always in effect

extern short m_Macro1;
extern short m_Macro2;
extern short m_OEM1;
extern short m_OEM2;

bool  ShuttleOpened = false;
int VendorID = 0x0B33;
int ProductID = 0x0030;
extern setup *_setup;          //Trajectory planners setup block. Always in effect
extern char *ButtonLabels[];
extern OneShort  DoButton;     // void DoButton( code )
short ButtonCodes[]= {0, 0, 0, 0, 1, 2, 3, 4, 43, 0, 0, 0, 0, 0, 0, 0};
extern VoidLPCSTR         Code;         // void    Code( "G0X10Y10" );
// ShuttleWin

IMPLEMENT_DYNAMIC(ShuttleWin, CWnd)
ShuttleWin::ShuttleWin()
{
	first = 0; second = 0;
	InputReport[0] = 0;
	InputReport[1] = 0;
	hEventObject= 0;
	for( int x = 0; x< 15; x++)
		Buttons[x] = false;
	LockWheel = false;
	LockShuttle = false;
	restart = false;
	CurrentAxis = 0;
	LastPos = 0;
	Jogging = false;
	IncMode = true;
	WasG90 = true;
	WheelPos = 0;
	WaitForZeroPos = false;
	DeviceHandle = ReadHandle = WriteHandle = INVALID_HANDLE_VALUE;
}

ShuttleWin::~ShuttleWin()
{

	if (DeviceHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(DeviceHandle);
	}

	if (ReadHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(ReadHandle);
	}

	if (WriteHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(WriteHandle);
	}
}


BEGIN_MESSAGE_MAP(ShuttleWin, CWnd)
	ON_MESSAGE(WM_DEVICECHANGE, OnDeviceChange)
	ON_WM_TIMER()
END_MESSAGE_MAP()



// ShuttleWin message handlers

bool ShuttleWin::GetHIDDevice()
{
	HIDD_ATTRIBUTES						Attributes;
	SP_DEVICE_INTERFACE_DATA			devInfoData;
	bool								LastDevice = FALSE;
	int									MemberIndex = 0;
	LONG								Result;	
	CString								UsageDescription;

	if( ProductID == 0x240)
		VendorID = 0x5f3;
	Length = 0;
	detailData = NULL;
	DeviceHandle=NULL;
	HidD_GetHidGuid(&HidGuid);	
	hDevInfo=SetupDiGetClassDevs 
		(&HidGuid, 
		NULL, 
		NULL, 
		DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
	devInfoData.cbSize = sizeof(devInfoData);
    MemberIndex = 0;
	LastDevice = FALSE;
	do
	{
	    Result=SetupDiEnumDeviceInterfaces 
			(hDevInfo, 
			0, 
			&HidGuid, 
			MemberIndex, 
			&devInfoData);

		if (Result != 0)
		{
		 Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				NULL, 
				0, 
				&Length, 
				NULL);
 		 detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);
		 detailData -> cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
 		 Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				detailData, 
				Length, 
				&Required, 
				NULL);
    	DeviceHandle=CreateFile 
				(detailData->DevicePath, 
				0, 
				FILE_SHARE_READ|FILE_SHARE_WRITE, 
				(LPSECURITY_ATTRIBUTES)NULL,
				OPEN_EXISTING, 
				0, 
				NULL);
     	Attributes.Size = sizeof(Attributes);

		Result = HidD_GetAttributes 
				(DeviceHandle, 
				&Attributes);
		MyDeviceDetected = FALSE;
	  	if (Attributes.VendorID == VendorID)
			{
				if (Attributes.ProductID == ProductID)
				{
					MyDeviceDetected = TRUE;
					MyDevicePathName = detailData->DevicePath;
					RegisterforNotify();
	 				//DisplayData("Device detected");
				    if (hEventObject == 0)
	                    {
						hEventObject = CreateEvent 
							(NULL, 
							TRUE, 
							TRUE, 
								"");
	                    HIDOverlapped.hEvent = hEventObject;
	                    HIDOverlapped.Offset = 0;
	                    HIDOverlapped.OffsetHigh = 0;
	                     }
                    //this sets up the file handle to poll the control bytes in the refresh timer..
  			        ReadHandle=CreateFile 
					(detailData->DevicePath, 
							GENERIC_READ, 
							FILE_SHARE_READ|FILE_SHARE_WRITE,
							(LPSECURITY_ATTRIBUTES)NULL, 
							OPEN_EXISTING, 
							FILE_FLAG_OVERLAPPED, 
							NULL);
					MyDeviceDetected = true;
					DevPath = detailData->DevicePath;
				 } //if (Attributes.ProductID == ProductID)
 				  else
					CloseHandle(DeviceHandle);
			} //if (Attributes.VendorID == VendorID)
 		else
	    CloseHandle(DeviceHandle);
		free(detailData);
		}  //if (Result != 0)
		else
  		 LastDevice=TRUE;
		MemberIndex = MemberIndex + 1;
	}while ((LastDevice == FALSE) && (MyDeviceDetected == FALSE)); //do..

  	SetupDiDestroyDeviceInfoList(hDevInfo);
	SetTimer( 1, 50, NULL);

	if( !MyDeviceDetected ) SetMachError( " No Shuttle Detected of type selected.");
	else
	   SetMachError( "Shuttle Plugin Enabled."); 
	return MyDeviceDetected;
}

void ShuttleWin::RegisterforNotify()
{
	//Register to receive device notifications.
	DEV_BROADCAST_DEVICEINTERFACE DevBroadcastDeviceInterface;
	HDEVNOTIFY DeviceNotificationHandle;
    DevBroadcastDeviceInterface.dbcc_size = sizeof(DevBroadcastDeviceInterface);
    DevBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    DevBroadcastDeviceInterface.dbcc_classguid = HidGuid;
    DeviceNotificationHandle =
    RegisterDeviceNotification(m_hWnd, &DevBroadcastDeviceInterface, DEVICE_NOTIFY_WINDOW_HANDLE);
	 
}

//this will take care of removal and replugging in the device..
LRESULT ShuttleWin::OnDeviceChange(WPARAM wParam, LPARAM lParam)  
	{
  
	//DisplayData("Device change detected.");

	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;

	switch(wParam) 
		{
		// Find out if a device has been attached or removed.
		// If yes, see if the name matches the device path name of the device we want to access.

		case DBT_DEVICEARRIVAL:
			 
		        MyDeviceDetected = true; //just got plugged in..
				
				ReadHandle=CreateFile 
					(DevPath, 
					GENERIC_READ, 
					FILE_SHARE_READ|FILE_SHARE_WRITE,
					(LPSECURITY_ATTRIBUTES)NULL, 
					OPEN_EXISTING, 
					FILE_FLAG_OVERLAPPED, 
					NULL);
				MyDeviceDetected = true;
			   
			   
			   return TRUE; 
	
		case DBT_DEVICEREMOVECOMPLETE:
	    	if (DeviceNameMatch(lParam))
			{
				if (ReadHandle != INVALID_HANDLE_VALUE)
				{
					CloseHandle(ReadHandle);
					ReadHandle = INVALID_HANDLE_VALUE;
				}
			    MyDeviceDetected = false; //just got unplugged..
				Engine->Axis[CurrentAxis].Dec = true;
				Code("ENDJOG");
			}
			return TRUE; 
	
		default:
			return TRUE; 
		} 
  }

BOOL ShuttleWin::DeviceNameMatch(LPARAM lParam)
	{

	// Compare the device path name of a device recently attached or removed 
	// with the device path name of the device we want to communicate with.
	
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
	if (lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) 
	{
		
		PDEV_BROADCAST_DEVICEINTERFACE lpdbi = (PDEV_BROADCAST_DEVICEINTERFACE)lParam;
		CString DeviceNameString;
		DeviceNameString = lpdbi->dbcc_name;
    	if ((DeviceNameString.CompareNoCase(MyDevicePathName)) == 0)
		{
            return true;
		}
		else
		{
            return false;
    	}
		
	}
		else
		{
			return false;
		}	
}

	void ShuttleWin::TranslateConditions()
	{
      if( first != InputReport[0] )
	  {
		  first = InputReport[0];
		  if (!Engine->EStop) CallWheels();
     }
     if( second != InputReport[1] )
	 {
		  second = InputReport[1];
		  CallButtons();
	 }
	 static int ticks = GetTickCount();
	 static int OldWheel = 0;
	 double diff = GetTickCount() - ticks;
	 
	 if( diff > 355 )
	  {
		  ticks = GetTickCount();
          int total = abs(WheelPos - OldWheel);
		  WheelSpeed = ((double)total / 12);
		  if(WheelSpeed > 1) WheelSpeed = 1.0;
		 // MainPlanner->OEMDROs[79] = WheelSpeed;
          OldWheel = WheelPos;
	  }
      if(WheelSpeed ==0 && WheelJogOn )
	  {
		  WheelStopped = true;
		  WheelJogOn = false;
		  Engine->Axis[CurrentAxis].Dec = true;
		  Code("ENDJOG");
	  }
	 
	}

	void ShuttleWin::CallWheels()
	{
      //lets measure the time taken..
	  //diff is now total ticks since last time..
	  //first inner wheel
	  signed int newcount = (first & 0x00ff0000) >> 16;
	  int diff = WheelPos - newcount;
      if( abs(diff) > 128 )
	  {
		  if( diff > 128)
		  {
			  diff = 256 - diff;//rollover of the counter..
              LastPos = (newcount - diff);
		  }
		  else
		  if( diff < -128) 
		  {
			  diff = -(256 + diff);
         	  LastPos = (newcount - diff);
		  }
	  }

	  
	  double Speed = abs( diff ); //number of counts change from last reading..

	  if( WheelPos != newcount )
	  {
	     WheelPos = (signed int)newcount;
		 OnWheelPos( WheelPos );
	  }

     newcount = (first & 0x0000ff00) >> 8;
     if( OuterWheel != newcount )
	  {
	     OuterWheel = (signed int)newcount;
		 OnOuterPos( OuterWheel );
		 //call any code specific to when outer wheel is turned here..
	  }
     
        
	}

	void ShuttleWin::CallButtons()
	{
      for( int x = 0; x < 15; x++)
	  {
		  bool check = (((second >> x)&0x01)? 1:0 );
		  if( Buttons[x] != check )
		  {
			  Buttons[x] = check;
			  if( check ) ButtonDown( x );
			  else        ButtonUp(x);
		  }
	  }
       
	}


	void ShuttleWin::OnTimer(UINT nIDEvent)
	{
		if( !MyDeviceDetected ) return;
		
		if( MainPlanner->CannonBuffer.nCommands == 0
			&& MainPlanner->CommandBuffer.head == MainPlanner->CommandBuffer.tail 
			&& Engine->TrajHead == Engine->TrajIndex )
		    WasG90 = _setup->distance_mode == MODE_ABSOLUTE;

		bool intimer = false;
		BOOL Result = 0;
		//this makes it wait if the Probe was used as a shutoff for a jog move;
		if( Engine->InSigs[DIGITIZE].Active && Engine->Axis[0].Memory[6] == 2 && Engine->InSigs[DIGITIZE].Activated)
			restart = true; //ignore jogs till wheels are zeroed.

		InputReport1[0] = InputReport[0];
		InputReport1[1] = InputReport[1];
	    if( !intimer ) 
		{  //re-entrance safety

		 intimer = true;
         if (ReadHandle != INVALID_HANDLE_VALUE)
		  {
		    Result = ReadFile(ReadHandle,InputReport,6,&NumberOfBytesRead,(LPOVERLAPPED) &HIDOverlapped); 
		  }
		  if( !Result ) 
		  {
			  Result = WaitForSingleObject(hEventObject, 5);
              if( Result != WAIT_OBJECT_0)
			  {
				  InputReport[0] = InputReport1[0];
				  InputReport[1] = InputReport1[1]; 
			        
			  }
			  TranslateConditions();
		  }
		  else
			  TranslateConditions();
		 
		  intimer = false;
		}
		CWnd::OnTimer(nIDEvent);
	}

	void  ShuttleWin::ButtonUp( int button )  //operate the button 
	{
		CString ThisBut = ButtonLabels[ButtonCodes[button]];
		int code = atoi( ThisBut );
		switch (code )
	   {
	   case( 810 ): Engine->Axis[CurrentAxis].Dec = true;//turn off the axis if it is jogging
		            Code("ENDJOG");
					Jogging = false;
					break;
	   case( 811 ): Engine->Axis[CurrentAxis].Dec = true;//turn off the axis if it is jogging
					Jogging = false;
					Code("ENDJOG");
					break;
		}
	}

	void  ShuttleWin::ButtonDown( int button )  //operate the button 
	{
	  CString ThisBut = ButtonLabels[ButtonCodes[button]];
	  CString Mac;
	  int code = atoi( ThisBut );
	  if(code != 809 && LockShuttle)
	  {
		  MessageBeep( MB_ICONEXCLAMATION );
		  return;
	  }
	  MessageBeep( MB_OK );
      if( code < 800 || code >=900 )
		  DoButton( code ); //do the function...
	  else
	  {
       //special button processing here.any 800 series command
       switch (code )
	   {
	   case( 806 ): LockWheel = true; 
                    
					SetMachError( " Shuttle Wheel Locked. ");
					Engine->Axis[CurrentAxis].Dec = true;//turn off the axis if it is jogging
					Code("ENDJOG");
					break;
	   case( 807 ): LockWheel = false; 
		            SetMachError( " Shuttle Wheel Unlocked. ");
					restart=true;
					break;
	   case( 800 ): if(CurrentAxis != 0)
					{
						Engine->Axis[CurrentAxis].Dec = true;
						Code("ENDJOG");
						CurrentAxis = 0;
						SetMachError( " X Shuttle Axis selected. ");
						restart=true; 
					}
					break;
	   case( 801 ): if(CurrentAxis != 1)
					{
						Engine->Axis[CurrentAxis].Dec = true;
						Code("ENDJOG");
						CurrentAxis = 1;
						SetMachError( " Y Shuttle Axis selected. ");
						restart=true; 
					}
					break;
       case( 802 ): if(CurrentAxis != 2)
					{
						Engine->Axis[CurrentAxis].Dec = true;
						Code("ENDJOG");
						SetMachError( " Z Shuttle Axis selected. ");
						CurrentAxis = 2;
						restart=true; 
					}
					break;
       case( 803 ): if(CurrentAxis != 3)
					{
						Engine->Axis[CurrentAxis].Dec = true;
						Code("ENDJOG");
						SetMachError( " A Shuttle Axis selected. ");
						CurrentAxis = 3;
						restart=true; 
					}
					break;
       case( 804 ): if(CurrentAxis != 4)
					{
						Engine->Axis[CurrentAxis].Dec = true;
						Code("ENDJOG");
						SetMachError( " B Shuttle Axis selected. ");
						CurrentAxis = 4;
						restart=true; 
					}
					break;
       case( 805 ): if(CurrentAxis != 5)
					{
						Engine->Axis[CurrentAxis].Dec = true;
						Code("ENDJOG");
						SetMachError( " C Shuttle Axis selected. ");
						CurrentAxis = 5;
						restart=true; 
					}
					break;
	   case( 808 ): LockWheel = !LockWheel;
		            if(LockWheel) 
		              { 
						  Engine->Axis[CurrentAxis].Dec = true;
					      Code("ENDJOG");
					  }
					if( LockWheel )
						SetMachError( " Shuttle Wheel Locked. ");
					else 
					{
						SetMachError( " Shuttle Wheel Unlocked. ");
					   restart=true;
					}
					break;
	   case( 809 ): LockShuttle = !LockShuttle;
					if(LockShuttle)
					{
						LockWheel = true;
						SetMachError( " Shuttle Locked. ");
						Engine->Axis[CurrentAxis].Dec = true;
						Code("ENDJOG");
					}
					else 
					{
						SetMachError( "Shuttle Unlocked. ");
						LockWheel = false;
						restart=true;
					}
					break;
	   case( 810 ): 
					if(LockWheel) 
					{
						SetMachError( " Wheel Locked. Unlock first. ");
						break;
					}
					Jogging = true;
					Engine->Axis[ CurrentAxis ].MaxVelocity = MainPlanner->Vels[ CurrentAxis ]; 
					Engine->Axis[ CurrentAxis ].Acceleration = MainPlanner->Accs[  CurrentAxis ];
					Engine->Axis[ CurrentAxis ].MasterVelocity = MainPlanner->Vels[  CurrentAxis ];
					Engine->Axis[ CurrentAxis ].Dec = false;
					Engine->Axis[ CurrentAxis ].Jogging = true;
					Engine->Axis[ CurrentAxis ].JoggDir = 0;
					Code("DOJOG");
					break;
	   case( 811 ): 
					if(LockWheel) 
					{
						SetMachError( " Wheel Locked. Unlock first. ");
						break;
					}
					Jogging = true;
					Engine->Axis[ CurrentAxis ].MaxVelocity = MainPlanner->Vels[ CurrentAxis ]; 
					Engine->Axis[ CurrentAxis ].Acceleration = MainPlanner->Accs[  CurrentAxis ];
					Engine->Axis[ CurrentAxis ].MasterVelocity = MainPlanner->Vels[  CurrentAxis ];
					Engine->Axis[ CurrentAxis ].Dec = false;
					Engine->Axis[ CurrentAxis ].Jogging = true;
					Engine->Axis[ CurrentAxis ].JoggDir = 1;
					Code("DOJOG");
					break;
	   case( 812 ):

					IncMode = !IncMode;
					if( IncMode )SetMachError( " Center Wheel Incremental. ");
					else
						SetMachError( "Center Wheel Velocity mode");
					break;
	   case( 813 ):

		   Mac.Format("M%d",m_Macro1);
		   Code( Mac );
		   SetMachError( " Custom Macro #1 executed. ");
		   break;
	   case( 814 ):
		   Mac.Format("M%d",m_Macro2);
		   Code( Mac ); 
		   SetMachError( " Custom Macro #2 executed. ");
		   break;
	   case( 815 ):
		   
		   DoButton( m_OEM1 );
		   SetMachError( " OEM Function #1 executed. ");
		   break;
	   case( 816 ):
		   
		   DoButton( m_OEM2 );
		   SetMachError( "OEM Function #2 executed.");
		   break;

	   }

	  }

	}

void ShuttleWin::OnWheelPos( int Pos )
	{
		
		if( LockWheel || Jogging) return;
		if( Engine->TrajHead != Engine->TrajIndex ) return;
		WheelJogOn = true;
		int dir = (Pos < LastPos ) ? 1 : 0;
		LastPos = Pos;
		if (IncMode)
		{
		CString Block, temp;

		 if( _setup->Rotation == 0 || CurrentAxis > 1)
		 {
	 	   double incr = GetAxisPos(CurrentAxis,&temp);
		   if(dir == 0) incr = MainPlanner->m_Increment;
		   else
		     incr = -MainPlanner->m_Increment;
		   Block.Format("G91G1 %s %.4f",temp,incr);
		   Code(Block);
		   if(WasG90) Code( "G90");
		   return;
		}
		 else
		 {
			 //rotated incremental jog.
			 double ang = _setup->Rotation * .017453293; //convert to Radians
			 double dx = 0,dy=0 ;
			 double incr;
			 if(dir == 0) incr = MainPlanner->m_Increment;
			 else
				 incr = -MainPlanner->m_Increment;
			 double rotx = 0,roty = 0;
			 //now we have the current X,Y in unrotated system
			 switch(CurrentAxis)
			 {
			   case( 0 ): dx = incr; break;
			   case( 1 ): dy = incr; break;
			 }
			 //all axis incrmented, just rotate x,y back.
			 rotx = (dx * cos(ang) - dy * sin(-ang));
			 roty = (dy * cos(ang) + dx * sin(-ang)); 
			 Block.Format("G91G1 X%.4f Y%.4f ", rotx, roty );
			 Code(Block);
			 if(WasG90) Code( "G90");
			 return;
		 }


		 }

		double tVel = ((double)MainPlanner->Vels[ CurrentAxis ]) * ( _setup->JogPercent / 100); //get current Jog Speed.
		tVel *= fabs( (WheelSpeed/1) ); //percentage of speed..
		if(WheelSpeed >.75)
			int g=1;
		if( tVel != 0)
		{
      		Engine->Axis[ CurrentAxis ].MaxVelocity = (int) tVel; 
			Engine->Axis[ CurrentAxis ].Acceleration = MainPlanner->Accs[  CurrentAxis ];
			Engine->Axis[ CurrentAxis ].MasterVelocity = MainPlanner->Vels[  CurrentAxis ];
			Engine->Axis[ CurrentAxis ].Dec = false;
			Engine->Axis[ CurrentAxis ].Jogging = true;
			Engine->Axis[ CurrentAxis ].JoggDir = dir;
			Code("DOJOG");
		}
		else
		{
			Engine->Axis[CurrentAxis].Dec = true;
			Code("ENDJOG");
		}

	}

void ShuttleWin::OnOuterPos( int pos )
	{
		double dJogRates [] = {0.0, 0.01, 0.02, 0.05, 0.1, 0.25, 0.5, 1.0};
		
		if( pos > 100) pos = -(256 - pos);
        if( LockWheel || WheelJogOn || Jogging)
			return; //no usage if wheel is locked..
		if(restart && LastOutterPos != 0)//THis is to make sure that the dial has gone back to "0" before we start to jog a new axis
		{
           if(pos==0)
		   {
			   restart = false;
		   }
		   else 
		   {
				LastOutterPos = pos;   
		   }
		   return;
		}
		LastOutterPos = pos;
		if( Engine->TrajHead != Engine->TrajIndex ) return;
		int dir = (pos < 0 ) ? 1 : 0;
		if( Engine->Axis[CurrentAxis].Jogging && Engine->Axis[CurrentAxis].JoggDir != dir ) pos = 0; //stop this axis first..
	     		
		double tVel1 = ((double)MainPlanner->Vels[ CurrentAxis ]) * ( _setup->JogPercent / 100); //get current Jog Speed.
		double tVel = dJogRates [abs(pos)] * tVel1;            //percentage of speed..
     if( tVel != 0)
	 {
      	 Engine->Axis[ CurrentAxis ].MaxVelocity = (int) tVel; 
         Engine->Axis[ CurrentAxis ].Acceleration = MainPlanner->Accs[  CurrentAxis ];
         Engine->Axis[ CurrentAxis ].MasterVelocity = MainPlanner->Vels[  CurrentAxis ];
         Engine->Axis[ CurrentAxis ].Dec = false;
         Engine->Axis[ CurrentAxis ].Jogging = true;
		 Engine->Axis[ CurrentAxis ].JoggDir = dir;
		 restart = false;
		 Code("DOJOG");
	 }
	 else
	 {
		 Engine->Axis[CurrentAxis].Dec = true;
		 Code("ENDJOG");
	 }



	}
double ShuttleWin::GetAxisPos(int Axis,CString *AxisName)
{
	double Position = 0;
	switch(Axis)
	{
		case(0): Position = MainPlanner->XPosition;*AxisName = "X";break;
		case(1): Position = MainPlanner->YPosition;*AxisName = "Y";break;
		case(2): Position = MainPlanner->ZPosition;*AxisName = "Z";break;
		case(3): Position = MainPlanner->APosition;*AxisName = "A";break;
		case(4): Position = MainPlanner->BPosition;*AxisName = "B";break;
		case(5): Position = MainPlanner->CPosition;*AxisName = "C";break;
	}
		return Position;
}

void ShuttleWin::SetMachError(CString Message)
{
	CString *err = &MainPlanner->LastError;
	if( err != NULL )
	    *err = Message;

}