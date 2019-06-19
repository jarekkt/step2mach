// DMCWIN Class Library

#ifndef DMCWIN_H
	#define DMCWIN_H

#ifndef DMCCOM_H
	#include "dmccom.h"
#endif

// For multi-threading support, this preprocessor variable should be
// defined
#define DMCMULTIPLETHREADS

class CDMCWin
{
public:
	// Contructors

	// Default constructor
	CDMCWin();
	// Construct the CDMCWin object and call Open to establish a connection
	// with the controller
	CDMCWin(USHORT usController, HWND hWnd = 0, LONG lThreadID = 0);

	// Destructor - calls Close if a connection is still active	
	~CDMCWin();

protected:
	USHORT		    m_usController;	// Controller number
	HWND			m_hWnd;				// Window handle to notify for interrupts
	LONG			m_lThreadID;		// Thread ID to notify for interrupts
	HANDLEDMC	    m_hDmc;				// Handle to the controller
	BOOL			m_bConnected;		// Is there an active connection?
	LONG			m_lLastError;		// Last return code from a DMCWIN library function

#ifdef DMCMULTIPLETHREADS
	CRITICAL_SECTION m_CritSec;	// Critical section used to single thread access to the DLLs
#endif
		
public:
	// Operations

	// All functions return an error code unless stated

	// See DMCWIN.H for more detailed information for many of these functions

	// Set the controller number to be used by Open
	//   returns void
	void SetController(USHORT usController) {m_usController = usController;};
	// Set the window handle to be used by Open
	// Can be used to change the window handle dynamically
	//   returns void
	void SethWnd(HWND hWnd);
	// Set the thread ID number to be used by Open
	// Can be used to change the thread ID dynamically
	//   returns void
	void SetThreadID(LONG lThreadID);	
	// Open a connection with the controller using already supplied parameters
	//   returns error code
	LONG Open();
	// Open a connection with the controller using these specific parameters
	//   returns error code
	LONG Open(USHORT usController, HWND hwnd = 0, LONG lThreadID = 0);
	// Is there an active connection?
	//   returns TRUE or FALSE
	BOOL IsConnected() {return m_bConnected;};
	// Get the value of the controller handle
	//   returns the value of the controller handle 
	HANDLEDMC GetHandle();
	// Close a connection with the controller
	//   returns error code
	LONG Close();
	// Send an ASCII command to the controller
	//   returns error code
	LONG Command(const PSZ pszCommand, PCHAR pchResponse = NULL, ULONG cbResponse = 0);
	// Send an ASCII command to the controller without waiting for a response
	//   returns error code
	LONG FastCommand(const PSZ pszCommand);
	// Send a binary command to the controller
	//   returns error code
	LONG BinaryCommand(PBYTE pbCommand, ULONG ulCommandLength, PCHAR pchResponse, ULONG cbResponse);
	// Get the unsolicited responses from the controller
	//   returns error code
	LONG GetUnsolicitedResponse(PCHAR pchResponse, ULONG cbResponse);
	// Get the additional response length
	//   returns the value of the additional response length 
	//   returns error code
	LONG GetAdditionalResponseLen();
	// Get the additional response
	//   returns error code
	LONG GetAdditionalResponse(PCHAR pchResponse, ULONG cbResponse);
	// Clear the controller (FIFO)
	//   returns error code
	LONG Clear();
	// Reset the controller
	//   returns error code
	LONG Reset();
	// Master reset the controller
	//   returns error code
	LONG MasterReset();
	// Get the controller version information
	//   returns error code
	LONG GetVersion(PCHAR pchVersion, ULONG cbVersion);
	// Download a DMC program to the controller from a file
	//   returns error code
	LONG DownloadFile(const PSZ pszFileName, const PSZ pszLabel = NULL);
	// Download a DMC program to the controller from a buffer
	//   returns error code
	LONG DownloadFromBuffer(const PSZ pszBuffer, const PSZ pszLabel = NULL);
	// Upload a DMC program from the controller to a file
	//   returns error code
	LONG UploadFile(const PSZ pszFileName);
	// Upload a DMC program from the controller to a buffer
	//   returns error code
	LONG UploadToBuffer(PCHAR pchBuffer, ULONG cbBuffer);
	// Send a file to the controller - reads and sends ASCII commands to the controller
	// line-by-line
	//   returns error code
	LONG SendFile(const PSZ pszFileName);
	// Send a file to the controller - reads and sends binary commands to the controller
	// line-by-line
	//   returns error code
	LONG SendBinaryFile(const PSZ pszFileName);
	// Refresh data record for data record access
	//   returns error code
	LONG RefreshDataRecord(ULONG ulLength = 0);
	// Get data record item using an offset for data record access
	//   returns error code
	LONG GetDataRecord(USHORT usGeneralOffset, USHORT usAxisInfoOffset, PUSHORT pusDataType, PLONG plData);
	// Get data record item using an item Id for data record access
	//   returns error code
	LONG GetDataRecordByItemId(USHORT usItemId, USHORT usAxisId, PUSHORT pusDataType, PLONG plData);
	// Get the size of the data record for data record access
	//   returns error code
	LONG GetDataRecordSize(PUSHORT pusRecordSize);
	// Get of a copy of the data record for data record access 
	//   returns error code
	LONG CopyDataRecord(PVOID pDataRecord);
	// Get the revision of the data record for data record access 
	//   returns error code
	LONG GetDataRecordRevision(PUSHORT pusRevision);
	// Convert an ASCII DMC command to a binary DMC command
	//   returns error code
	LONG AsciiCommandToBinaryCommand(PSZ pszAsciiCommand, ULONG ulAsciiCommandLength, PBYTE pbBinaryResult, ULONG
	cbBinaryResult, ULONG FAR *pulBinaryResultLength);
	// Convert a binary DMC command to an ASCII DMC command
	//   returns error code
	LONG BinaryCommandToAsciiCommand(PBYTE pbBinaryCommand, ULONG ulBinaryCommandLength, PSZ pszAsciiResult, ULONG
	cbAsciiResult, ULONG FAR *pulAsciiResultLength);
	// Convert a file consisting of ASCII commands to a file consisting of binary commands
	//   returns error code
	LONG AsciiFileToBinaryFile(const PSZ pszInputFileName, const PSZ pszOutputFileName);
	// Convert a file consisting of binary commands to a file consisting of ASCII commands
	//   returns error code
	LONG BinaryFileToAsciiFile(const PSZ pszInputFileName, const PSZ pszOutputFileName);
	// Turn diagnostics trace on
	//   returns error code
	LONG DiagnosticsOn(const PSZ pszFileName, BOOL bAppend = FALSE);
	// Turn diagnostics trace off
	//   returns error code
	LONG DiagnosticsOff();
	// Get the current timeout value for the controller
	//   returns the value for timeout
	LONG GetTimeout();
	// Set the timeout for the controller
	//   returns void
	void SetTimeout(LONG lTimeout);
	// Get the current delay value for the controller
	//   returns the value for delay
	LONG GetDelay();
	// Set the delay for the controller
	//   returns void
	void SetDelay(LONG lDelay);
	// Wait for motion complete
	//   returns error code
	LONG WaitForMotionComplete(const PSZ pszAxes, SHORT fDispatchMsgs = TRUE);
	// Get the error text for an error code
	//   returns error code
	LONG GetErrorText(LONG lError, PCHAR pchMessage, ULONG cbMessage);
	// Get the last error code from a DMCWIN libary function
	//   returns error code
	LONG GetLastError() {return m_lLastError;};
};

class CDMCWinRegistry
{
public:
	// Constructor
	CDMCWinRegistry();

	// Destructor
	~CDMCWinRegistry();

protected:
	LONG	m_lLastError;		// Last return code from a DMCWIN library function

public:
	// Add a Galil controller to the Windows registry - the controller number is
	// returned in the argument pusController
	// Supports old-style registry structure.
	//   returns error code
	LONG AddGalilRegistry(PGALILREGISTRY pgalilregistry, PUSHORT pusController);
	// Same as above but supports new-style registry structure.
	//   returns error code
	LONG AddGalilRegistry(PGALILREGISTRY2 pgalilregistry2, PUSHORT pusController);
	// Change a Galil controller in the Windows registry
	// Supports old-style registry structure.
	//   returns error code
	LONG ModifyGalilRegistry(USHORT usController, PGALILREGISTRY pgalilregistry);
	// Same as above but supports new-style registry structure.
	//   returns error code
	LONG ModifyGalilRegistry(USHORT usController, PGALILREGISTRY2 pgalilregistry2);
	// Get Windows registry information for a given Galil controller
	// Supports old-style registry structure.
	//   returns error code
	LONG GetGalilRegistryInfo(USHORT usController, PGALILREGISTRY pgalilregistry);
	// Same as above but supports new-style registry structure.
	//   returns error code
	LONG GetGalilRegistryInfo(USHORT usController, PGALILREGISTRY2 pgalilregistry2);
	// Delete a Galil controller in the Windows registry, or -1 for all controllers
	// Supports both old and new registry structures
	//   returns error code
	LONG DeleteGalilRegistry(SHORT sController);
	// Select a Galil motion controller from a list of registered controllers
	//   returns the selected controller number or -1 if no controller was selected
	SHORT SelectController(HWND hwnd);
	// Edit the Windows registry: add, change, or delete Galil motion controllers
	//   returns void
	void EditRegistry(HWND hwnd);
	// Get the last error code from a DMCWIN libary function
	//   returns error code
	LONG GetLastError() {return m_lLastError;};
};

// For WaitForMotionComplete
typedef struct _MOTIONTHREAD
{
	HANDLEDMC	hDmc;
	CHAR			szAxes[16];
	LONG			rc;
	DWORD			ThreadId;
#ifdef DMCMULTIPLETHREADS
	PCRITICAL_SECTION pCritSec;
#endif
} MOTIONTHREAD;

DWORD WINAPI MotionCompleteThread(LPVOID pArgs);

#endif // DMCWIN_H