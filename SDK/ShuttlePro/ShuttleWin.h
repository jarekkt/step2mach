#pragma once


extern "C" {

// This file is in the Windows DDK available from Microsoft.
#include "hidsdi.h"
#include <setupapi.h>
#include <dbt.h>
}

// ShuttleWin

class ShuttleWin : public CWnd
{
	DECLARE_DYNAMIC(ShuttleWin)

public:
	ShuttleWin();
	virtual ~ShuttleWin();
	void RegisterforNotify();
	LRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam);
	BOOL    DeviceNameMatch(LPARAM lParam);
	void TranslateConditions();
	double GetAxisPos(int axis,CString *AxisName);
	void CallWheels();
	void CallButtons();
	void SetMachError(CString Message);
	//Conditions..
	int     WheelPos;     //position of wheel from  32bits..
	double  WheelSpeed;   // 0 - 100 %
	int     OuterWheel;
	bool    Buttons[15];
	int		LastPos;
	int		LastOutterPos;
	bool    LockWheel;
	bool	LockShuttle;
	bool	restart;
	int     CurrentAxis;
	bool	WheelStopped;
	bool    WheelJogOn;
	bool    Jogging;
	bool	IncMode;
	CString DevPath;
	bool    WaitForZeroPos;
    bool    WasG90;
    


	void    ButtonUp( int button );  //operate the button
    void    ButtonDown( int button );  //operate the button
	void    OnWheelPos( int Pos );
	void    OnOuterPos( int pos );
    

	//Specific to HID's

	int  first,second;

    bool GetHIDDevice();

    DWORD								ActualBytesRead;
	DWORD								BytesRead;
	HIDP_CAPS							Capabilities;
	DWORD								cbBytesRead;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	detailData;
	HANDLE								DeviceHandle;
	DWORD								dwError;
	char								FeatureReport[256];
	HANDLE								hEventObject;
	HDEVINFO							hDevInfo;
	GUID								HidGuid;
	OVERLAPPED							HIDOverlapped;
	DWORD  						        InputReport[2];
	ULONG								Length;
	LPOVERLAPPED						lpOverLap;
	bool								MyDeviceDetected; 
	CString								MyDevicePathName;
	DWORD								NumberOfBytesRead;
	char								OutputReport[256];
	HANDLE								ReadHandle;
	DWORD								ReportType;
	ULONG								Required;
	CString								ValueToDisplay;
	HANDLE								WriteHandle;
	DWORD  						        InputReport1[2];


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT nIDEvent);
};


