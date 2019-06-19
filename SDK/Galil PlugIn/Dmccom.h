// Note: Include this file afer WINDOWS.H
// WINDOWS.H must be included in your project

#ifndef DMCCOM_H
	#define DMCCOM_H

#ifdef __cplusplus
	extern "C" {
#endif

// Common datatypes (see WINDOWS.H)
#ifndef FAR
	#define FAR
#endif
#ifndef NEAR
	#define NEAR
#endif
typedef short int SHORT;
typedef short int NEAR* PSHORT;
typedef short int FAR* LPSHORT;
typedef unsigned short int USHORT;
typedef unsigned short int NEAR* PUSHORT;
typedef unsigned short int FAR* LPUSHORT;
#if defined(_WIN32) || defined(__WIN32__)
	typedef long int LONG;
#endif
typedef long int NEAR* PLONG;
typedef long int FAR* LPLONG;
typedef unsigned long int ULONG;
typedef unsigned long int NEAR* PULONG;
typedef unsigned long int FAR* LPULONG;
typedef char CHAR;
typedef char NEAR* PCHAR;
typedef char FAR* LPCHAR;
typedef unsigned char UCHAR;
typedef unsigned char NEAR* PUCHAR;
typedef unsigned char FAR* LPUCHAR;
typedef unsigned char BYTE;
typedef unsigned char NEAR* PBYTE;
typedef unsigned char FAR* LPBYTE;
typedef void NEAR* PVOID;
typedef void FAR* LPVOID;
typedef char FAR* PSZ;

#if defined(_WIN32) || defined(__WIN32__)
	#define GALILCALL __stdcall
#else
	#define GALILCALL FAR PASCAL __export
#endif

#if !defined(_WIN32) && !defined(__WIN32__)
	#ifndef TEXT
		#define TEXT
	#endif
#endif

// Controller model constants
#define DMC400   TEXT("DMC-400")
#define DMC600   TEXT("DMC-600")
#define DMC700   TEXT("DMC-700")
#define DMC1000  TEXT("DMC-1000")
#define DMC1200  TEXT("DMC-1200")
#define DMC1300  TEXT("DMC-1300")
#define DMC1410  TEXT("DMC-1410")
#define DMC1411  TEXT("DMC-1411")
#define DMC1412  TEXT("DMC-1412")
#define DMC1413  TEXT("DMC-1413")
#define DMC1414  TEXT("DMC-1414")
#define DMC1415  TEXT("DMC-1415")
#define DMC1425  TEXT("DMC-1425")
#define DMC3425  TEXT("DMC-3425")
#define DMC1416  TEXT("DMC-1416")
#define DMC1417  TEXT("DMC-14x7")
#define DMC1500  TEXT("DMC-1500")
#define DMC1600  TEXT("DMC-1600")
#define DMC1700  TEXT("DMC-1700")
#define DMC1800  TEXT("DMC-1800")
#define DMC1802  TEXT("DMC-1802")
#define DMC1806  TEXT("DMC-18x6")
#define DMC2000  TEXT("DMC-2000")
#define DMC2100  TEXT("DMC-2100")
#define DMC2102	 TEXT("DMC-21x3/2")
#define DMC2200	 TEXT("DMC-2200")
#define CDS3300	 TEXT("CDS-33x0")
#define DMC7007	 TEXT("IOC-7007")

#define MODEL_UNKNOWN       0
#define MODEL_600           600
#define MODEL_700           700
#define MODEL_1000          1000
#define MODEL_1200          1200
#define MODEL_1300          1300
#define MODEL_1410          1410
#define MODEL_1411          1411
#define MODEL_1412          1412
#define MODEL_1413          1413
#define MODEL_1414          1414
#define MODEL_1415          1415
#define MODEL_1416          1416
#define MODEL_1417          1417
#define MODEL_1500          1500
#define MODEL_1600          1600
#define MODEL_1700          1700
#define MODEL_1800          1800
#define MODEL_1802          1802
#define MODEL_1806          1806
#define MODEL_2000          2000
#define MODEL_2100          2100
#define MODEL_2102          2102
#define MODEL_2200          2200
#define MODEL_3300          3300
#define MODEL_7007			7007
#define MODEL_USERDEFINED   9999


// General defines
#define COMMAND_SIZE        80
#define MAX_CONTROLLERS     64

// User defined message to notify application program of an interrupt
#define WM_DMCINTERRUPT    (WM_USER+128)	// Status byte from the controller is passed to user via the wParam argument
#define WM_MOTIONCOMPLETE  (WM_USER+129)
#define WM_UNSOLICITEDMSG  (WM_USER+130)
#define WM_NEWDATARECORD   (WM_USER+131)

// Errors
#define DMCNOERROR             0
#define DMCWARNING_MONITOR     1

#define DMCERROR_TIMEOUT              -1
#define DMCERROR_COMMAND              -2
#define DMCERROR_CONTROLLER           -3
#define DMCERROR_FILE                 -4
#define DMCERROR_DRIVER               -5
#define DMCERROR_HANDLE               -6
#define DMCERROR_HMODULE              -7
#define DMCERROR_MEMORY               -8
#define DMCERROR_BUFFERFULL           -9
#define DMCERROR_RESPONSEDATA         -10
#define DMCERROR_DMA                  -11 
#define DMCERROR_ARGUMENT             -12
#define DMCERROR_DATARECORD           -13
#define DMCERROR_DOWNLOAD             -14
#define DMCERROR_FIRMWARE             -15
#define DMCERROR_CONVERSION           -16
#define DMCERROR_RESOURCE             -17
#define DMCERROR_REGISTRY             -18
#define DMCERROR_BUSY                 -19
#define DMCERROR_DEVICE_DISCONNECTED  -20
#define DMCERROR_TIMEING_ERROR				-21
#define DMCERROR_WRITEBUFFER_TOO_LARGE		-22
#define DMCERROR_NO_MODIFY_PNP_CONTROLLER	-23
#define DMCERROR_FUNCTION_OBSOLETE			-24
#define DMCERROR_STREAMING_COMMAND_IN_PROGRESS	-25
#define DMCERROR_DEVICEDRIVER_VERSION_TOO_OLD	-26
#define DMCERROR_STREAMING_COMMAND_MUST_BE_SOLITARY	-27
#define DMCERROR_FIRMWARE_VERSION_TOO_OLD	  -28
#define DMCERROR_ETHERNET_NO_MORE_HANDLES	  -29
#define DMCERROR_NETWORK_UNREACHABLE		  -30


// Data types
typedef LONG HANDLEDMC;
typedef HANDLEDMC FAR* PHANDLEDMC;

// Constant values

// Constant values for data record access
#include "dmcdrc.h"

// Constant values for registry structures
enum DMCControllerTypes
{
   ControllerTypeISABus = 0,     // ISA or PC-104 bus controller
   ControllerTypeSerial = 1,     // RS-232 serial controller
   ControllerTypePCIBus = 2,     // PCI or Compact PCI bus controller
   ControllerTypeUSB = 3,        // Universal serial bus controller
   ControllerTypeEthernet = 4,   // Ethernet controller
   ControllerTypeVMEBus = 5      // VME bus controller
};

enum DMCDeviceDrivers
{
   DeviceDriverWinRT = 0,        // Use WinRT device driver
   DeviceDriverGalil = 1         // Use Galil device driver
};

enum DMCSerialHandshake
{
   SerialHandshakeHardware = 0,  // Hardware handshake (RTS/CTS)
   SerialHandshakeSoftware = 1,  // Software handshake (XOn/XOff) 
   SerialHandshakeBoth = 2       // RESERVED FOR GALIL USE ONLY
};

enum DMCBusIOStyle
{
   DMC600IOStyle = 0,            // For DMC-600, DMC-1400
   DMC1000IOStyle = 1,           // For DMC-1000, DMC-1200, DMC-1700, DMC-1802
   DMC1600IOStyle = 2            // For DMC-1600, DMC-1800
};

enum DMCInterruptStyle
{
   DMC1000InterruptStyle = 0,    // For DMC-1000
   DMC1400InterruptStyle = 1,    // For DMC-1400
   DMC1700InterruptStyle = 2,    // For DMC-1200, DMC-1700, DMC-1802
   DMC1600InterruptStyle = 3     // For DMC-1600, DMC-1800
};

enum DMCDataRecordAccess
{
   DataRecordAccessNone = 0,     // No data record access capability or data record access is off
   DataRecordAccessDMA = 1,      // Use DMA for data record access
   DataRecordAccessFIFO = 2,     // Use FIFO for data record access
   DataRecordAccessBoth = 3,     // RESERVED FOR GALIL USE ONLY
   DataRecordAccessQR = 4        // RESERVED FOR GALIL USE ONLY
};

enum DMCEthernetProtocol
{
   EthernetProtocolTCP = 0,
   EthernetProtocolUDP = 1
};
enum DMCVMEBusInterface
{
   VMEBusInterfaceBit3 = 0,
   VMEBusInterfaceVMIC = 1
};

// Ethernet flags
#define ETH_NO_MULTICAST					0x0001	// Do not open a multi-cast session
#define ETH_UNSOLICITEDMESSAGES				0x0002	// Open an unsolicited message session on second handle
#define ETH_UNSOLICITEDMESSAGES_SAMEHANDLE	0x0004	// Open an unsolicited message session on same handle

// Structures

// Structure used to add/change/delete registry information
// Old-style structure
typedef struct _GALILREGISTRY
{
#ifdef UNDER_CE
   TCHAR   szModel[32];          // Controller model string
#else
   CHAR    szModel[16];          // Controller model string
#endif
   USHORT  usDeviceNumber;       // Device number - for Galil use only
   USHORT  fDeviceDriver;        // Use Galil or WinRT device driver
   ULONG   ulTimeout;            // Time-out in milliseconds
   ULONG   ulDelay;              // Delay in microsceonds
   USHORT  fControllerType;      // Controller type (ISA bus, PCI bus, serial, etc.)
   USHORT  usCommPort;           // Serial communications port
   ULONG   ulCommSpeed;          // Serial Communications speed
   USHORT  fHandshake;           // Serial communications handshake
   USHORT  usAddress;            // Bus address
   USHORT  usInterrupt;          // Interrupt
   USHORT  fDataRecordAccess;    // Data record access type
   USHORT  usDMAChannel;         // DMA channel
   USHORT  usDataRecordSize;     // Data record size (for data record access)
   USHORT  usRefreshRate;        // Data record refresh rate in 2^usRefreshRate ms
   USHORT  usSerialNumber;       // Controller Serial Number
#ifdef UNDER_CE
   TCHAR   szPNPHardwareKey[128];// Hardware registry key for PNP controllers - for Galil use only
#else
   CHAR    szPNPHardwareKey[64]; // Hardware registry key for PNP controllers - for Galil use only
#endif
} GALILREGISTRY, FAR* PGALILREGISTRY;

// Hardware info - ISA and PCI bus communications
typedef struct _BUSINFO
{
   USHORT  usDeviceNumber;       // Device number - for Galil use only
   USHORT  fDeviceDriver;        // Use Galil or WinRT device driver
   USHORT  fIOStyle;             // Style of addressing status register on controller
   USHORT  usAddress;            // I/O port address
   USHORT  fInterruptStyle;      // Style of handling interrupts from controller  
   USHORT  usInterrupt;          // Interrupt
   USHORT  fDataRecordAccess;    // Data record access type
   USHORT  usDMAChannel;         // DMA channel
   USHORT  usDataRecordSize;     // Data record size (for data record access)
   USHORT  usRefreshRate;        // Data record refresh rate in 2^usRefreshRate ms
   USHORT  bPNP;                 // Plug and play? (TRUE | FALSE)
   USHORT  usAddress2;           // Alternate I/O port address for PCI controllers
   USHORT  usReserved1;          // Reserved for future use
   USHORT  nCommWaitMethod	;	 // Added 8/8/02 for specifying DMCCommand communication method.
   BOOL	   bFirmSupportsIntComm; // Added 8/8/02 for signaling if device firmware supports int comm.
   SHORT   nDRCacheDepth;		 // Added 10/28/02 for recording data record cache depth.
   ULONG   ulHardwareID;		 // Added to uniquely identify controllers by serial number and function.
#ifdef UNDER_CE
   TCHAR   szPNPHardwareKey[128];// Hardware registry key for PNP controllers - for Galil use only
#else
   CHAR    szPNPHardwareKey[55]; // Hardware registry key for PNP controllers - for Galil use only
#endif
} BUSINFO;

// Hardware info - serial communications
typedef struct _SERIALINFO
{
   USHORT  usCommPort;           // Communications port
   ULONG   ulCommSpeed;          // Communications speed
   USHORT  fHandshake;           // Communications handshake
   USHORT  usDeviceNumber;       // Device number - for Galil use only
   USHORT  usReserved1;          // Reserved for future use
} SERIALINFO;

// Hardware info - serial communications
typedef struct _WINSOCKINFO
{
   ULONG   ulPort;					// Host port number - for Galil use only
#ifdef UNDER_CE
   TCHAR   szIPAddress[64];      // Host name string
#else
   CHAR    szIPAddress[32];      // Host name string
#endif
   USHORT  fProtocol;            // UDP or TCP
   ULONG   fFlags;				 // Controls auto opening of multi-cast and unsolicited message sessions
   USHORT  fMsgProtocol;		 // Added 9/15/03. UDP or TCP. Relevant only when second handle is used for unsolicited messages.
   USHORT  fUseEthernetWait;     // Added 9/15/03. Allows Ethernet read calls to wait on a FD_READ event rather than spinning the processor.
   USHORT  fUseUnsolicitedDR;	 // Added 10/7/03. Commands driver to open dedicated data record handle.
   USHORT  nRefreshRate;         // Added 10/15/03. Sets the ethernet DR command frequency in millisec.
   USHORT  nCacheDepth;			 // Added 12/1/03.  Allows ethernet implementation of DMCmGetDataRecordConstPointerArray and DMCmGetDataRecordArray.
   USHORT  usReserved3;          // Reserved for future use
} WINSOCKINFO;

// Hardware info - ISA and PCI bus communications
typedef struct _VMEBUSINFO
{
   USHORT  usDeviceNumber;       // Device number - for Galil use only
   USHORT  fDeviceDriver;        // Use Galil or WinRT device driver
	USHORT  fInterface;           // Which VME to PC interface
	ULONG   ulMemoryAddress;      // Physical memory address of VME interface card
	ULONG   ulMemoryOffset;       // Offset in memory to Galil controller
   USHORT  usAddress;            // I/O port address for VME interface card
   USHORT  fIOStyle;             // Style of addressing status register on controller
   USHORT  fInterruptStyle;      // Style of handling interrupts from controller  
   USHORT  usInterrupt;          // Interrupt (IRQ) mapped to PC (jumper on VME interface card)
   USHORT  usInterruptLevel;     // Interrupt level on the VME bus (jumper on controller)
   USHORT  fDataRecordAccess;    // Data record access type
   USHORT  usDataRecordSize;     // Data record size (for data record access)
   USHORT  usRefreshRate;        // Data record refresh rate in 2^usRefreshRate ms
   USHORT  bPNP;                 // Plug and play? (TRUE | FALSE)
   ULONG   ulReserved1;          // Reserved for future use
   ULONG   ulReserved2;          // Reserved for future use
   ULONG   ulReserved3;          // Reserved for future use
   ULONG   ulReserved4;          // Reserved for future use
} VMEBUSINFO;

// Hardware info for registry
typedef union _HARDWAREINFO
{
   BUSINFO      businfo;         // ISA and PCI bus information
   SERIALINFO   serialinfo;      // Serial information
	WINSOCKINFO  winsockinfo;     // WinSock (e.g. Ethernet) information
	VMEBUSINFO   vmebusinfo;      // VME bus information
} HARDWAREINFO; 

// Structure used to add/change/delete registry information
// New-style structure
typedef struct _GALILREGISTRY2
{
	USHORT  usVersion;                   // Structure version
	CHAR    szModel[16];                 // Controller model string
	USHORT  usModelID;                   // Model ID
	USHORT  fControllerType;             // Controller type (ISA bus, PCI bus, serial, etc.)
	ULONG   ulTimeout;                   // Time-out in milliseconds
	ULONG   ulDelay;                     // Delay in microsceonds
	ULONG   ulSerialNumber;              // Controller serial number
	HARDWAREINFO hardwareinfo;           // Union defining the hardware characteristics of the controller
} GALILREGISTRY2, FAR* PGALILREGISTRY2;

// Added 8/4/04 to support friendly name.
typedef struct _GALILREGISTRY3
{
	USHORT  usVersion;                   // Structure version
	CHAR    szModel[16];                 // Controller model string
	USHORT  usModelID;                   // Model ID
	USHORT  fControllerType;             // Controller type (ISA bus, PCI bus, serial, etc.)
	ULONG   ulTimeout;                   // Time-out in milliseconds
	ULONG   ulDelay;                     // Delay in microsceonds
	ULONG   ulSerialNumber;              // Controller serial number
	HARDWAREINFO hardwareinfo;           // Union defining the hardware characteristics of the controller
	CHAR	szDescription[16];			 // 8/4/04.  Added so that the controller can be referred to by description.
} GALILREGISTRY3, FAR* PGALILREGISTRY3;

// Hardware info for user-defined bus controllers
// RESERVED FOR GALIL USE ONLY 
typedef struct _BUSDEF
{
   SHORT iIOType;
   SHORT iIOMin;
   SHORT iIOMax;
   SHORT iIOSize;
   SHORT iInterruptType;
   SHORT iInterrupts;
   SHORT iInterruptList[16];
   SHORT iDataRecordAccessType;
   SHORT iDMAChannels;
   SHORT iDMAChannelList[8];
   SHORT nCommWaitMethod;
   UCHAR bFirmSupportsIntComm;
} BUSDEF;

// Hardware info for user-defined serial controllers 
// RESERVED FOR GALIL USE ONLY 
typedef struct _SERIALDEF
{
   SHORT iCommPorts;
   SHORT iCommPortList[16];
   SHORT iCommSpeeds;
   LONG  iCommSpeedList[16];
   SHORT iHandshake;
} SERIALDEF;

// Hardware info for user-defined controllers 
// RESERVED FOR GALIL USE ONLY 
typedef union _HARDWAREDEF
{
   BUSDEF     busdef;
   SERIALDEF  serialdef;
} HARDWAREDEF;

// Structure used to describe user-defined controllers
// RESERVED FOR GALIL USE ONLY 
typedef struct _CONTROLLERDEF
{
#ifdef UNDER_CE
   TCHAR szModel[32];
#else
   CHAR  szModel[16];
#endif
   SHORT iControllerType;
   HARDWAREDEF hardwaredef;
} CONTROLLERDEF;

// Function prototypes

// All functions return an error code. DMCNOERROR (0) is function completed
// successfully. < 0 is a local error (see the error codes above). > 0 is an
// Win32 API error (if you are using the 32-bit DLLs). These are documented in
// the Win32 Programming Reference.

// General functions for all controllers

LONG FAR GALILCALL DMCOpen(USHORT usController, HWND hwnd,
   PHANDLEDMC phdmc);
// Open communications with the Galil controller. The handle to the Galil
// controller is returned in the argument phdmc.
// NOTE: hwnd is not used for controllers which do not support bus interrupts.

// usController      A number between 1 and 16. Up to 16 Galil controllers may be
//                   addressed per process.
// hwnd              The window handle to use for notifying the application
//                   program of an interrupt via PostMessage.
// phdmc             Buffer to receive the handle to the Galil controller to be
//                   used for all subsequent API calls. Users should declare a
//                   variable of type HANDLEDMC and pass the address of the
//                   variable to the function. Output only.

LONG FAR GALILCALL DMCOpen2(USHORT usController, LONG lThreadID,
   PHANDLEDMC phdmc);
// Open communications with the Galil controller. The handle to the Galil
// controller is returned in the argument phdmc.
// NOTE: lThreadID is not used for controllers which do not support bus interrupts.

// usController      A number between 1 and 16. Up to 16 Galil controllers may be
//                   addressed per process.
// lThreadID         The thread ID to use for notifying the application
//                   program of an interrupt via PostThreadMessage.
// phdmc             Buffer to receive the handle to the Galil controller to be
//                   used for all subsequent API calls. Users should declare a
//                   variable of type HANDLEDMC and pass the address of the
//                   variable to the function. Output only.

LONG FAR GALILCALL DMCOpenDesc(PSZ pszDescription, HWND hwnd, PHANDLEDMC phdmc, PUSHORT pControllerNum);
// Open communications with the Galil controller specified by the szDescription field. 
// szDescription fields are not guaranteed to be unique.  The first match found is opened.
// The handle to the Galil controller is returned in the argument phdmc.
// NOTE: hwnd is not used for controllers which do not support bus interrupts.

// pszDescription    The description string of the controller.  See GALILREGISTRY3::szDescription.
//                   
// hwnd              The window handle to use for notifying the application
//                   program of an interrupt via PostMessage.
//
// phdmc             Buffer to receive the handle to the Galil controller to be
//                   used for all subsequent API calls. Users should declare a
//                   variable of type HANDLEDMC and pass the address of the
//                   variable to the function. Output only.
// pControllerNum	 Optional. Buffer to receive Galil Registry index that corresponds
//					 to the pszDescription found.  Set NULL if unused.

LONG FAR GALILCALL DMCOpenDesc2(PSZ pszDescription, LONG lThreadID, PHANDLEDMC phdmc, PUSHORT pControllerNum);
// Open communications with the Galil controller specified by the szDescription field. 
// szDescription fields are not guaranteed to be unique.  The first match found is opened.
// The handle to the Galil controller is returned in the argument phdmc.
// NOTE: lThreadID is not used for controllers which do not support bus interrupts.

// pszDescription    The description string of the controller.  See GALILREGISTRY3::szDescription.
//                   
// hwnd              The window handle to use for notifying the application
//                   program of an interrupt via PostMessage.
//
// phdmc             Buffer to receive the handle to the Galil controller to be
//                   used for all subsequent API calls. Users should declare a
//                   variable of type HANDLEDMC and pass the address of the
//                   variable to the function. Output only.
// pControllerNum	 Optional. Buffer to receive Galil Registry index that corresponds
//					 to the pszDescription found.  Set NULL if unused.


LONG FAR GALILCALL DMCGetHandle(USHORT usController, PHANDLEDMC phdmc);
// Get the handle for a Galil controller which was already opened using
// DMCOpen or DMCOpen2. The handle to the Galil controller is returned in the
// argument phdmc.

// usController      A number between 1 and 16. Up to 16 Galil controllers may be
//                   addressed per process.
// phdmc             Buffer to receive the handle to the Galil controller to be
//                   used for all subsequent API calls. Users should declare a
//                   variable of type HANDLEDMC and pass the address of the
//                   variable to the function. Output only.

HANDLE GALILCALL DMCInterruptEventHandle( USHORT );
// Get the handle to the Event that is set signled to indicate an interrupt occured
// usController      A number between 1 and 16. Up to 16 Galil controllers may be
//                   addressed per process.

LONG FAR GALILCALL DMCChangeInterruptNotification(HANDLEDMC hdmc, LONG lHandle);
// Change the window handle used in DMCOpen or the thread ID used in DMCOpen2. This
// value is for notification of interrupts.
// NOTE: This function is not used for controllers which do not support bus interrupts.

// hdmc              Handle to the Galil controller.
// lHandle           New window handle or thread ID.

LONG FAR GALILCALL DMCClose(HANDLEDMC hdmc);
// Close communications with the Galil controller.

// hdmc              Handle to the Galil controller.

LONG FAR GALILCALL DMCCommand(HANDLEDMC hdmc, PSZ pszCommand,
   LPCHAR pchResponse, ULONG cbResponse);
// Send a DMC command in ascii format to the Galil controller.
// NOTE: This function can only send commands or groups of commands up to
// 1024 bytes long.

// hdmc              Handle to the Galil controller.
// pszCommand        The command to send to the Galil controller.
// pchResponse       Buffer to receive the response data. If the buffer is too
//                   small to recieve all the response data from the controller,
//                   the error code DMCERROR_BUFFERFULL will be returned. The
//                   user may get additional response data by calling the
//                   function DMCGetAdditionalResponse. The length of the
//                   additonal response data may ascertained by call the
//                   function DMCGetAdditionalResponseLen. If the response
//                   data from the controller is too large for the internal
//                   additional response buffer, the error code
//                   DMCERROR_RESPONSEDATA will be returned. Output only.
// cbResponse        Length of the buffer.

LONG FAR GALILCALL DMCFastCommand(HANDLEDMC hdmc, PSZ pszCommand);
// Send a DMC command in ascii format to the Galil controller and do not
// wait for a response. Use this function with extreme caution as command
// errors will not be reported and the out-going FIFO or communciations buffer
// may fill up. Use this function for Galil commands which do
// not return an acknowlegement from the controller such as providing data
// for the Galil DL and QD commands. Other uses may be to send contour data.
// NOTE: This function can only send commands or groups of commands up to
// 1024 bytes long.

// hdmc              Handle to the Galil controller.
// pszCommand        The command to send to the Galil controller.

LONG FAR GALILCALL DMCBinaryCommand(HANDLEDMC hdmc, LPBYTE pbCommand, ULONG ulCommandLength,
	LPCHAR pchResponse, ULONG cbResponse);
// Send a DMC command in binary format to the Galil controller.

// hdmc              Handle to the Galil controller.
// pbCommand         The command to send to the Galil controller in binary.
// ulCommandLength   The length of the command (binary commands are not null-terminated).
// pchResponse       Buffer to receive the response data. If the buffer is too
//                   small to recieve all the response data from the controller,
//                   the error code DMCERROR_BUFFERFULL will be returned. The
//                   user may get additional response data by calling the
//                   function DMCGetAdditionalResponse. The length of the
//                   additonal response data may ascertained by call the
//                   function DMCGetAdditionalResponseLen. If the response
//                   data from the controller is too large for the internal
//                   additional response buffer, the error code
//                   DMCERROR_RESPONSEDATA will be returned. Output only.
// cbResponse        Length of the buffer.

LONG FAR GALILCALL DMCGetUnsolicitedResponse(HANDLEDMC hdmc,
	LPCHAR pchResponse, ULONG cbResponse);
// Query the Galil controller for unsolicited responses. These are messages
// output from programs running in the background in the Galil controller.
// The data placed in the user buffer (pchResponse) is NULL terminated.

// hdmc              Handle to the Galil controller.
// pchResponse       Buffer to receive the response data.
// cbResponse        Length of the buffer.

LONG FAR GALILCALL DMCWriteData(HANDLEDMC hdmc,
	LPCHAR pchBuffer, ULONG cbBuffer, LPULONG pulBytesWritten);
// Low-level I/O routine to write data to the Galil controller. Data is written
// to the Galil controller only if it is "ready" to receive it. The function
// will attempt to write exactly cbBuffer characters to the controller.
// NOTE: For Win32 and WinRT driver the maximum number of bytes which can be
// written each time is 64. There are no restrictions with the Galil driver. 

// hdmc              Handle to the Galil controller.
// pchBuffer         Buffer to write the data from. Data does not need to be 
//                   NULL terminated.
// cbBuffer          Length of the data in the buffer.
// pulBytesWritten   Number of bytes written.

LONG FAR GALILCALL DMCReadData(HANDLEDMC hdmc,
	LPCHAR pchBuffer, ULONG cbBuffer, LPULONG pulBytesRead);
// Low-level I/O routine to read data from the Galil controller. The routine
// will read what ever is currently in the FIFO (bus controller) or
// communications port input queue (serial controller). The function will read
// up to cbBuffer characters from the controller. The data placed in the 
// user buffer (pchBuffer) is NOT NULL terminated. The data returned is not
// guaranteed to be a complete response - you may have to call this function
// repeatedly to get a complete response.
// NOTE: For Win32 and WinRT driver the maximum number of bytes which can be
// read each time is 64. There are no restrictions with the Galil driver. 

// hdmc              Handle to the Galil controller.
// pchBuffer         Buffer to read the data into. Data will not be NULL
//                   terminated.
// cbBuffer          Length of the buffer.
// pulBytesRead      Number of bytes read.

LONG FAR GALILCALL DMCGetAdditionalResponseLen(HANDLEDMC hdmc,
	LPULONG pulResponseLen);
// Query the Galil controller for the length of additional response data. There
// will be more response data available if the DMCCommand function returned
// DMCERROR_BUFFERFULL.

// hdmc              Handle to the Galil controller.
// pulResponseLen    Buffer to receive the additional response data length.
//                   Output only.

LONG FAR GALILCALL DMCGetAdditionalResponse(HANDLEDMC hdmc,
	LPCHAR pchResponse, ULONG cbResponse);
// Query the Galil controller for more response data. There will be more
// response data available if the DMCCommand function returned
// DMCERROR_BUFFERFULL. Once this function is called, the internal
// additonal response buffer is cleared.

// hdmc              Handle to the Galil controller.
// pchResponse       Buffer to receive the response data. Output only.
// cbResponse        Length of the buffer.

LONG FAR GALILCALL DMCError(HANDLEDMC hdmc, LONG lError, LPCHAR pchMessage,
	ULONG cbMessage);
// Retrieve the error message text from a DMCERROR_COMMAND error.

// hdmc              Handle to the Galil controller.
// pchMessage        Buffer to receive the error message text. Output only.
// cbMessage         Length of the buffer.

LONG FAR GALILCALL DMCClear(HANDLEDMC hdmc);
// Clear the Galil controller FIFO.

// hdmc              Handle to the Galil controller.

LONG FAR GALILCALL DMCReset(HANDLEDMC hdmc);
// Reset the Galil controller.

// hdmc              Handle to the Galil controller.

LONG FAR GALILCALL DMCMasterReset(HANDLEDMC hdmc);
// Master reset the Galil controller.

// hdmc              Handle to the Galil controller.

LONG FAR GALILCALL DMCVersion(HANDLEDMC hdmc, LPCHAR pchVersion,
	ULONG cbVersion);
// Get the version of the Galil controller.

// hdmc              Handle to the Galil controller.
// pchVersion        Buffer to receive the version information. Output only.
// cbVersion         Length of the buffer.

LONG FAR GALILCALL DMCDownloadFile(HANDLEDMC hdmc, PSZ pszFileName,
   PSZ pszLabel);
// Download a file to the Galil controller.

// hdmc              Handle to the Galil controller.
// pszFileName       File name to download to the Galil controller.
// pszLabel          Program label to download to. This argument is ignored if
//                   NULL.

LONG FAR GALILCALL DMCDownloadFromBuffer(HANDLEDMC hdmc, PSZ pszBuffer,
   PSZ pszLabel);
// Download from a buffer to the Galil controller.

// hdmc              Handle to the Galil controller.
// pszBuffer         Buffer of DMC commands to download to the Galil controller.
// pszLabel          Program label to download to. This argument is ignored if
//                   NULL.

LONG FAR GALILCALL DMCUploadFile(HANDLEDMC hdmc, PSZ pszFileName);
// Upload a file from the Galil controller.

// hdmc              Handle to the Galil controller.
// pszFileName       File name to upload from the Galil controller.

LONG FAR GALILCALL DMCUploadToBuffer(HANDLEDMC hdmc, LPCHAR pchBuffer,
	ULONG cbBuffer);
// Upload to a buffer from the Galil controller.

// hdmc              Handle to the Galil controller.
// pchBuffer         Buffer of DMC commands to upload from the Galil controller.
//                   Output only.
// cbBuffer          Length of the buffer.

LONG FAR GALILCALL DMCSendFile(HANDLEDMC hdmc, PSZ pszFileName);
// Send a file consisting of DMC commands in ascii format to the Galil controller.

// hdmc              Handle to the Galil controller.
// pszFileName       File name to send to the Galil controller.

// Binary communications functions

LONG FAR GALILCALL DMCSendBinaryFile(HANDLEDMC hdmc, PSZ pszFileName);
// Send a file consisting of DMC commands in binary format to the Galil controller.

// hdmc              Handle to the Galil controller.
// pszFileName       File name to send to the Galil controller.

LONG FAR GALILCALL DMCArrayDownload(HANDLEDMC hdmc, PSZ pszArrayName,
   USHORT usFirstElement, USHORT usLastElement, LPCHAR pchData, ULONG cbData,
	LPULONG cbBytesWritten);
// Download an array to the Galil controller. The array must exist. Array data can be
// delimited by a comma or CR (0x0D) or CR/LF (0x0D0A).
// NOTE: The firmware on the controller must be recent enough to support the QD command.

// hdmc              Handle to the Galil controller.
// pszArrayName      Array name to download to the Galil controller.
// usFirstElement    First array element.
// usLastElement     Last array element.
// pchData           Buffer to write the array data from. Data does not need to be
//                   NULL terminated.
// cbData            Length of the array data in the buffer.
// cbBytesWritten    Number of bytes written.

LONG FAR GALILCALL DMCArrayUpload(HANDLEDMC hdmc, PSZ pszArrayName,
   USHORT usFirstElement, USHORT usLastElement, LPCHAR pchData, ULONG cbData,
	LPULONG pulBytesRead, SHORT fComma);
// Upload an array from the Galil controller. The array must exist. Array data will be
// delimited by a comma or CR (0x0D) depending of the value of fComma.
// NOTE: The firmware on the controller must be recent enough to support the QU command.

// hdmc              Handle to the Galil controller.
// pszArrayName      Array name to upload from the Galil controller.
// usFirstElement    First array element.
// usLastElement     Last array element.
// pchData           Buffer to read the array data into. Array data will not be
//                   NULL terminated.
// cbData            Length of the buffer.
// pulBytesRead      Number of bytes read.
// fComma            0 = delimit by "\r", 1 = delimit by ",".

LONG FAR GALILCALL DMCCommand_AsciiToBinary(HANDLEDMC hdmc, PSZ pszAsciiCommand,
   ULONG ulAsciiCommandLength, LPBYTE pbBinaryResult,
	ULONG cbBinaryResult, LPULONG pulBinaryResultLength);
// Convert an ascii DMC command to a binary DMC command.

// hdmc                  Handle to the Galil controller.
// pszAsciiCommand       Ascii DMC command(s) to be converted.
// ulAsciiCommandLength  Length of DMC command(s).
// pbBinaryResult        Buffer to receive the translated DMC command.
// cbBinaryResult        Length of the buffer.
// pulBinaryResultLength Length of the translated DMC command.

LONG FAR GALILCALL DMCCommand_BinaryToAscii(HANDLEDMC hdmc, LPBYTE pbBinaryCommand,
   ULONG ulBinaryCommandLength, PSZ pszAsciiResult,
	ULONG cbAsciiResult, LPULONG pulAsciiResultLength);
// Convert a binary DMC command to an ascii DMC command.

// hdmc                  Handle to the Galil controller.
// pbBinaryCommand       Binary DMC command(s) to be converted.
// ulBinaryCommandLength Length of DMC command(s).
// pszAsciiResult        Buffer to receive the translated DMC command.
// cbAsciiResult         Length of the buffer.
// pulAsciiResultLength  Length of the translated DMC command.

LONG FAR GALILCALL DMCFile_AsciiToBinary(HANDLEDMC hdmc, PSZ pszInputFileName,
   PSZ pszOutputFileName);
// Convert a file consisting of ascii commands to a file consisting of binary commands.

// hdmc              Handle to the Galil controller.
// pszInputFileName  File name for the input ascii file.
// pszOutputFileName File name for the output binary file.

LONG FAR GALILCALL DMCFile_BinaryToAscii(HANDLEDMC hdmc, PSZ pszInputFileName,
   PSZ pszOutputFileName);
// Convert a file consisting of binary commands to a file consisting of ascii commands.

// hdmc              Handle to the Galil controller.
// pszInputFileName  File name for the input binary file.
// pszOutputFileName File name for the output ascii file.

LONG FAR GALILCALL DMCReadSpecialConversionFile(HANDLEDMC hdmc, PSZ pszFileName);
// Read into memory a special BinaryToAscii/AsciiToBinary conversion table.

// hdmc              Handle to the Galil controller.
// pszFileName       File name for the special conversion file.

// Data record access (DMA/FIFO) functions.

LONG FAR GALILCALL DMCRefreshDataRecord(HANDLEDMC hdmc, ULONG ulLength);
// Refresh the data record used for fast polling.

// hdmc              Handle to the Galil controller.
// ulLength          Refresh size in bytes. Set to 0 unless you do not want a full-buffer
//                   refresh.

LONG FAR GALILCALL DMCGetDataRecord(HANDLEDMC hdmc, USHORT usGeneralOffset,
	USHORT usAxisInfoOffset, LPUSHORT pusDataType, LPLONG plData);
// Get a data item from the data record used for fast polling. Gets one item from the
// data record by using offsets (see data record constants defined in DMCDRC.H). To
// retrieve data record items by Id instead of offset, use the function
// DMCGetDataRecordByItemId.

// hdmc              Handle to the Galil controller.
// usGeneralOffset   Data record offset for general data item.
// usAxisInfoOffset  Additional data record offset for axis data item.
// pusDataType       Data type of the data item. If you are using the standard, 
//                   pre-defined offsets, set this argument to zero before calling this
//                   function. The actual data type of the data item is returned
//                   on output.
// plData            Buffer to receive the data record data. Output only.

LONG FAR GALILCALL DMCGetDataRecordByItemId(HANDLEDMC hdmc, USHORT usItemId,
	USHORT usAxisId, LPUSHORT pusDataType, LPLONG plData);
// Get a data item from the data record used for fast polling. Gets one item from the
// data record by using Id (see data record Ids defined in DMCDRC.H). To
// retrieve data record items by offset instead of Id, use the function DMCGetDataRecord.

// hdmc              Handle to the Galil controller.
// usItemId          Data record item Id.
// usAxisId          Axis Id used for axis data items.
// pusDataType       Data type of the data item. The data type of the
//                   data item is returned on output. Output Only.
// plData            Buffer to receive the data record data. Output only.

LONG FAR GALILCALL DMCGetDataRecordSize(HANDLEDMC hdmc, LPUSHORT pusRecordSize);
// Get the size of the data record used for fast polling.

// hdmc              Handle to the Galil controller.
// pusRecordSize     The size of the data record is returned on output. Output Only.

LONG FAR GALILCALL DMCCopyDataRecord(HANDLEDMC hdmc, PVOID pDataRecord);
// Get a copy of the data record used for fast polling. The data record is
// only as recent as the last call made to DMCRefreshDataRecord.

// hdmc              Handle to the Galil controller.
// pDataRecord       A copy of the data record is returned on output. Output Only.

LONG FAR GALILCALL DMCGetDataRecordRevision(HANDLEDMC hdmc, LPUSHORT pusRevision);
// Get the revision of the data record structure used for fast polling.

// hdmc              Handle to the Galil controller.
// pusRevision       The revision of the data record structure is returned on
//                   output. Output Only.

// Diagnostics functions for all controllers

LONG FAR GALILCALL DMCDiagnosticsOn(HANDLEDMC hdmc, PSZ pszFileName,
	SHORT fAppend);
// Turn on diagnostics.

// hdmc              Handle to the Galil controller.
// pszFileName       File name for the diagnostic file.
// fAppend           TRUE if the file will open for append, otherwise FALSE.

LONG FAR GALILCALL DMCDiagnosticsOff(HANDLEDMC hdmc);
// Turn off diagnostics.

// hdmc              Handle to the Galil controller.

// Configuration functions for all controllers

LONG FAR GALILCALL DMCGetTimeout(HANDLEDMC hdmc, LONG FAR* pTimeout);
// Get current time-out value. The default is 1000.

// hdmc              Handle to the Galil controller.
// pTimeout          Buffer to receive the current time-out value in
//                   milliseconds. Output only.

LONG FAR GALILCALL DMCSetTimeout(HANDLEDMC hdmc, LONG lTimeout);
// Set time-out value. The default is 1000. If the time-out value is set to
// zero, the DLLs will ignore time-out errors. This is useful for sending
// Galil commands which do not return a response, such as providing records
// to the DL or QD commands. 

// hdmc              Handle to the Galil controller.
// lTimeout          Time-out value in milliseconds.

LONG FAR GALILCALL DMCGetDelay(HANDLEDMC hdmc, LONG FAR* pDelay);
// *** THIS FUNCTION IS OBSOLETE. DELAY IS NO LONGER USED ***

// hdmc              Handle to the Galil controller.
// pDelay            Buffer to receive the current delay value in
//                   milliseconds. Output only.

LONG FAR GALILCALL DMCSetDelay(HANDLEDMC hdmc, LONG lDelay);
// *** THIS FUNCTION IS OBSOLETE. DELAY IS NO LONGER USED ***

// hdmc              Handle to the Galil controller.
// lDelay            Delay value in milliseconds.

// Registry functions for all controllers

LONG FAR GALILCALL DMCAddGalilRegistry(PGALILREGISTRY pgalilregistry,
	LPUSHORT pusController);
// Add a Galil controller to the Windows registry. The controller number is
// returned in the argument pusController.
// Supports old-style registry structure.

// pgalilregistry    Pointer to a GALILREGISTRY struct.
// pusController     Buffer to receive the Galil controller number. Output only. 

LONG FAR GALILCALL DMCAddGalilRegistry2(PGALILREGISTRY2 pgalilregistry2,
	LPUSHORT pusController);
// Add a Galil controller to the Windows registry. The controller number is
// returned in the argument pusController.
// Supports new-style registry structure.

// pgalilregistry    Pointer to a GALILREGISTRY2 struct.
// pusController     Buffer to receive the Galil controller number. Output only. 

LONG FAR GALILCALL DMCAddGalilRegistry3(PGALILREGISTRY3 pgalilregistry3,
	LPUSHORT pusController);
// Add a Galil controller to the Windows registry. The controller number is
// returned in the argument pusController.
// Version 3 of the registry structure adds the description.

// pgalilregistry3    Pointer to a GALILREGISTRY3 struct.
// pusController     Buffer to receive the Galil controller number. Output only. 

LONG FAR GALILCALL DMCModifyGalilRegistry(USHORT usController,
	PGALILREGISTRY pgalilregistry);
// Change a Galil controller in the Windows registry.
// Supports old-style registry structure.

// usController      Galil controller number.
// pgalilregistry    Pointer to a GALILREGISTRY struct.

LONG FAR GALILCALL DMCModifyGalilRegistry2(USHORT usController,
	PGALILREGISTRY2 pgalilregistry2);
// Change a Galil controller in the Windows registry.
// Supports new-style registry structure.

// usController      Galil controller number.
// pgalilregistry2   Pointer to a GALILREGISTRY2 struct.

LONG FAR GALILCALL DMCModifyGalilRegistry3(USHORT usController,
	PGALILREGISTRY3 pgalilregistry3);
// Change a Galil controller in the Windows registry.
// Version 3 of the registry structure adds the description.

// usController      Galil controller number.
// pgalilregistry3   Pointer to a GALILREGISTRY3 struct.

LONG FAR GALILCALL DMCGetGalilRegistryInfo(USHORT usController,
	PGALILREGISTRY pgalilregistry);
// Get Windows registry information for a given Galil controller.
// Supports old-style registry structure.

// usController      Galil controller number.
// pgalilregistry    Pointer to a GALILREGISTRY struct. Output only.

LONG FAR GALILCALL DMCGetGalilRegistryInfo2(USHORT usController,
	PGALILREGISTRY2 pgalilregistry2);
// Get Windows registry information for a given Galil controller.
// Supports new-style registry structure.

// usController      Galil controller number.
// pgalilregistry2   Pointer to a GALILREGISTRY2 struct. Output only.

LONG FAR GALILCALL DMCGetGalilRegistryInfo3(USHORT usController,
	PGALILREGISTRY3 pgalilregistry3);
// Get Windows registry information for a given Galil controller.
// Version 3 adds szDescription to version 2.  See DMCOpenDesc(...).

// usController      Galil controller number.
// pgalilregistry3   Pointer to a GALILREGISTRY3 struct. Output only.

LONG FAR GALILCALL DMCEnumGalilRegistry(USHORT FAR* pusCount,
	PGALILREGISTRY pgalilregistry);
// Enumerate or list all the Galil controllers in the Windows registry. The
// user needs to make two calls to this function. The first call should
// have a NULL for the argument pgalilregistry. The number of GALILREGISTRY
// structs (number of Galil controllers in the Windows registry) will be
// returned in the argument pusCount. The second call should have sufficient
// memory allocated for all the GALILREGISTRY structs to be returned
// and pass the pointer to that memory as the argument pgalilregistry.
// It is the users responsibility to allocate and free memory to hold the
// GALILREGISTRY structs.
// Supports old-style registry structure.

// pusCount          Pointer to the number of GALILREGISTRY structs returned.
// pgalilregistry    Pointer to a GALILREGISTRY struct. Output only.

LONG FAR GALILCALL DMCEnumGalilRegistry2(USHORT FAR* pusCount,
	PGALILREGISTRY2 pgalilregistry2);
// Enumerate or list all the Galil controllers in the Windows registry. The
// user needs to make two calls to this function. The first call should
// have a NULL for the argument pgalilregistry. The number of GALILREGISTRY2
// structs (number of Galil controllers in the Windows registry) will be
// returned in the argument pusCount. The second call should have sufficient
// memory allocated for all the GALILREGISTRY2 structs to be returned
// and pass the pointer to that memory as the argument pgalilregistry.
// It is the users responsibility to allocate and free memory to hold the
// GALILREGISTRY2 structs.
// Supports new-style registry structure.

// pusCount          Pointer to the number of GALILREGISTRY2 structs returned.
// pgalilregistry2   Pointer to a GALILREGISTRY2 struct. Output only.

LONG FAR GALILCALL DMCEnumGalilRegistry3(USHORT FAR* pusCount,
	PGALILREGISTRY3 pgalilregistry3);
// Enumerate or list all the Galil controllers in the Windows registry. The
// user needs to make two calls to this function. The first call should
// have a NULL for the argument pgalilregistry. The number of GALILREGISTRY3
// structs (number of Galil controllers in the Windows registry) will be
// returned in the argument pusCount. The second call should have sufficient
// memory allocated for all the GALILREGISTRY3 structs to be returned
// and pass the pointer to that memory as the argument pgalilregistry.
// It is the users responsibility to allocate and free memory to hold the
// GALILREGISTRY3 structs.
// Version 3 adds the szDescription field.

// pusCount          Pointer to the number of GALILREGISTRY3 structs returned.
// pgalilregistry3   Pointer to a GALILREGISTRY3 struct. Output only.

LONG FAR GALILCALL DMCDeleteGalilRegistry(SHORT sController);
// Delete a Galil controller in the Windows registry.
// Supports both old-style and new-style registry structures.

// sController       Galil controller number. Use -1 to delete all Galil
//                   controllers.

LONG FAR GALILCALL DMCGetControllerDesc(USHORT usController, PSZ pszControllerDesc, ULONG cbControllerDesc);
// Get a description of the controller from the registry.

// usController      Galil controller number.
// pszControllerDesc Buffer to receive the controller description. Output only.
// cbControllerDesc  Length of the buffer.

// Windows plug-and-play functions

LONG FAR GALILCALL DMCRegisterPnpControllers(USHORT* pusCount);
// Update Windows registry for all Galil Plug-and-Play (PnP) controllers. This function
// will add new controllers to the registry or update existing ones.
// NOTE: This function is for the DMC-1600, DMC-1700, and DMC-1800 only.
// NOTE: This function is for Win16 and Windows NT only. Windows 95/98 
// automatically register controllers through the device driver.  

// pusCount          Pointer to the number of Galil PnP controllers registered
//                   (and/or updated).

// Registry dialog windows

SHORT FAR GALILCALL DMCSelectController(HWND hwnd);
// Select a Galil motion controller from a list of registered controllers. Returns the
// selected controller number or -1 if no controller was selected.
// NOTE: This function invokes a dialog window.  

// hwnd              The window handle of the calling application. If NULL, the
//                   window with the current input focus is used.

VOID FAR GALILCALL DMCEditRegistry(HWND hwnd);
// Edit the Windows registry: add, change, or delete Galil motion controllers.
// NOTE: This function invokes a dialog window.  

// hwnd              The window handle of the calling application. If NULL, the
//                   window with the current input focus is used.

LONG FAR GALILCALL DMCAssignIPAddress(HWND hWnd, PGALILREGISTRY2 pgalilregistry2);
// Assign the IP Address to a DMC-2100 or DMC-1415 Ethernet controller. The controller must be in
// BOOTP broadcast mode.

// hwnd              The window handle of the calling application. If NULL, the
//                   window with the current input focus is used.
// szIPAddress       The IP address as a string.  Example: "160.35.50.1".

// Utility functions

LONG FAR GALILCALL DMCWaitForMotionComplete(HANDLEDMC hdmc, PSZ pszAxes, SHORT fDispatchMsgs);
// Wait for motion complete by creating a thread to query the controller. The function returns
// when motion is complete.

// hdmc              Handle to the Galil controller.
// pszAxes           Which axes to wait for: X, Y, Z, W, E, F, G, H, or S for
//                   coordinated motion. To wait for more than one axis (other than
//                   coordinated motion), simply concatenate the axis letters in the string.
// fDispatchMsgs     Set to TRUE if you want to get and dispatch Windows messages
//                   while waiting for motion complete. This flag is always TRUE for Win16.

LONG FAR GALILCALL DMCDownloadFirmwareFile(HANDLEDMC hdmc, PSZ pszFileName, SHORT fDisplayDialog);
// Update the controller's firmware. This function will open a binary firmware file and refresh
// the flash EEPROM of the controller.

// hdmc              Handle to the Galil controller.
// pszFileName       File name to download to the Galil controller.
// fDisplayDialog    Display a progress dialog while the firmware file is being downloaded.

LONG FAR GALILCALL DMCCompressFile(PSZ pszInputFileName, PSZ pszOutputFileName, USHORT usLineWidth,
	PUSHORT pusLineCount);
// Compress a DMC file so that program space in the controller is fully utilized. Lines
// are put together whenever possible to make more lines available. Leading and trailing spaces
// are removed as well.

// pszInputFileName  The name of the DMC file to compress.
// pszOutputFileName The name of the resulting compressed DMC file.
// usLineWidth       The maximum line width. For most controllers, this value is either 40 or 80.
// pusLineCount      The line count of the resulting compressed DMC file is returned on output.
//                   Output Only.

#if defined(_WIN32) || defined(__WIN32__)
// Win32 device driver functions

LONG FAR GALILCALL DMCReadRegister(HANDLEDMC hdmc, USHORT usOffset, PBYTE pbStatus);
// Read from a register (FIFO) of a bus controller.
// NOTE: This function is for Galil bus controllers and Win32 only.

// ** THIS FUNCTION IS FOR EXPERIENCED PROGRAMMERS ONLY **

// hdmc              Handle to the Galil controller.
// usOffset          Register offset. 0 = mailbox, 1 = status.
// pbStatus          Buffer to receive status register data.

LONG FAR GALILCALL DMCWriteRegister(HANDLEDMC hdmc, USHORT usOffset, BYTE bStatus);
// Write to a register (FIFO) of a bus controller.
// NOTE: This function is for Galil bus controllers and Win32 only.

// ** THIS FUNCTION IS FOR EXPERIENCED PROGRAMMERS ONLY **

// hdmc              Handle to the Galil controller.
// usOffset          Register offset. 0 = mailbox, 1 = status.
// bStatus           Status register data.

LONG FAR GALILCALL DMCStartDeviceDriver(USHORT usController);
// Start the device driver associated with the given controller. All controller
// handles must be closed. Use this function to recycle the device driver after
// making a configuration change through the Windows registry. For bus controllers
// only.
// NOTE: This function is for Win32 only. Windows NT requires
//       administrative authority.

// usController      Galil controller number.

LONG FAR GALILCALL DMCStopDeviceDriver(USHORT usController);
// Stop the device driver associated with the given controller. All controller
// handles must be closed. Use this function to recycle the device driver after
// making a configuration change through the Windows registry. For bus controllers
// only.
// NOTE: This function is for Win32 only. Windows NT requires
//       administrative authority.

// usController      Galil controller number.

LONG FAR GALILCALL DMCStopDeviceDriverEx( DWORD dwType );
// Stop the device driver type. All controller
// handles must be closed. Use this function to recycle the device driver after
// making a configuration change through the Windows registry. For bus controllers
// only.
// NOTE: This function is for Win32 only. Windows NT requires
//       administrative authority.

// dwType  Galil driver type.

LONG FAR GALILCALL DMCStartDeviceDriverEx( DWORD dwType );
// Start the device driver associated with the given controller. All controller
// handles must be closed. Use this function to recycle the device driver after
// making a configuration change through the Windows registry. For bus controllers
// only.
// NOTE: This function is for Win32 only. Windows NT requires administrative authority.

// dwType  Galil driver type.

LONG FAR GALILCALL DMCQueryDeviceDriver( DWORD dwType );
// Start the device driver associated with the given controller. All controller
// handles must be closed. Use this function to recycle the device driver after
// making a configuration change through the Windows registry. For bus controllers
// only.
// NOTE: This function is for Win32 only. Windows NT requires administrative authority.

// dwType  Galil driver type.


LONG FAR GALILCALL DMCSendCW2OnClose( HANDLEDMC hdmc, BOOL *pbValue );
// This function sets the bSendCW2OnClose property of the dmc handle.  This property
// determines if the controller is sent a "CW2" command on closing.  The "CW2" 
// command causes the controller to NOT set the most significant bit of unsolicited
// messages to 1 (please see the Galil Motion Control Command reference).  The default
// behavior is TRUE, which means the CW2 command is sent prior to closing a controller 
// handle.

// hdmc              Handle to the Galil controller.
// pbValue           Desired boolean value. On function return pbValue contains the
//					 previous value.					 .


LONG FAR GALILCALL DMCGetDataRecordItemOffsetById( HANDLEDMC hdmc, USHORT usItemId,
   USHORT usAxisId, LPUSHORT pusOffset, LPUSHORT pusDataType );
// Get the total offset for a data item by data item Id(see data record Ids defined in DMCDRC.H). 
// The returned offset and datatype can then be used to extract a value from the data record
// pointer retrieved using DMCCopyDataRecord.

// hdmc              Handle to the Galil controller.
// usItemId          Data record item Id.
// usAxisId          Axis Id used for axis data items.
// pusOffset         Total offset (number of bytes) from the beginning of the data
//					 record to the data item. Output Only.
// pusDataType       Data type of the data item. The data type of the
//                   data item is returned on output. Output Only.

LONG FAR GALILCALL DMCGetDataRecordConstPointer(HANDLEDMC hdmc, const char **pchDataRecord);
// Get a const pointer to the most recent data record.  Using this method to access the information
// in the data record eliminates the copying necessary with DMCCopyDataRecord.  For PCI and ISA controllers
// using WDM drivers 5.0.0.0 and higher, this function retrieves the most recent data record available.  If
// the cache depth is set larger than 1, the records are lost.  If an application is using this function 
// exclusively, the data record cache depth should be set to 1.  DMCRefreshDataRecord must be called prior to
// calling this function.

// hdmc              Handle to the Galil controller.
// pchDataRecord     Const pointer to the data record.

LONG FAR GALILCALL DMCGetDataRecordConstPointerArray(HANDLEDMC hdmc, const char **pchDataRecord, LPUSHORT pusNumDataRecords);
// Get a const pointer to the available data records.  This function retrieves all the available cached
// data records from a PCI and ISA controller with 2nd FIFO. Compatible with Glwdmpci.sys, Glwdmisa.sys, 
// and GalilPCI.sys driver versions 7.0.0.0 and higher.  The cache depth is set by controller properties 
// stored in the Galil Registry.  It is not necessary to call DMCRefreshDataRecord prior to calling this function.

// hdmc              Handle to the Galil controller.
// pchDataRecord     Const pointer to an array of data records.
// psNumDataRecords	 The number of data records contained in the character array.


#ifdef __cplusplus

struct CDMCFullDataRecord;	// Forward declaration.
LONG FAR GALILCALL DMCGetDataRecordArray(HANDLEDMC hdmc, CDMCFullDataRecord **pDataRecordArray, LPUSHORT pusNumDataRecords);
// Get an array of data records.  This function retrieves all the available cached
// data records from a PCI and ISA controller with 2nd FIFO or dual port ram, and ethernet controllers with
// firmware supporting the DR command.  Compatible with Glwdmpci.sys, Glwdmisa.sys, 
// and GalilPCI.sys driver versions 7.0.0.0 and higher.  The cache depth is set by controller properties 
// stored in the Galil Registry.  It is not necessary to call DMCRefreshDataRecord prior to calling this function.

// hdmc              Handle to the Galil controller.
// pchDataRecord     Pointer to an array of CDMCFullDataRecord objects.  CDMCFullDataRecord contains members
//					 for every possible item in a record up to REV04 of the data record.  If a member doesn't 
//					 apply to a given controller (such as axes 5-8 on a four axis controller) then these 
//					 members must be disregarded.  
// psNumDataRecords	 The number of data records contained in the data record array.

struct CDMCFullDataRecord2;	// Forward declaration.
LONG FAR GALILCALL DMCGetDataRecordArray2(HANDLEDMC hdmc, CDMCFullDataRecord2 **pDataRecordArray, LPUSHORT pusNumDataRecords);
// Get an array of data records.  This function retrieves all the available cached
// data records from a PCI and ISA controller with 2nd FIFO or dual port ram, and ethernet controllers with
// firmware supporting the DR command.  Compatible with Glwdmpci.sys, Glwdmisa.sys, 
// and GalilPCI.sys driver versions 7.0.0.0 and higher.  The cache depth is set by controller properties 
// stored in the Galil Registry.  It is not necessary to call DMCRefreshDataRecord prior to calling this function.

// hdmc              Handle to the Galil controller.
// pchDataRecord     Pointer to an array of CDMCFullDataRecord objects.  CDMCFullDataRecord2 contains members
//					 for every possible item in a record up to REV07 of the data record.  If a member doesn't 
//					 apply to a given controller (such as axes 5-8 on a four axis controller) then these 
//					 members must be disregarded.  
// psNumDataRecords	 The number of data records contained in the data record array.

#endif

#endif

#ifdef __cplusplus
	}
#endif

#endif // DMCCOM_H
