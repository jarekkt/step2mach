// Include this file for Microsoft Visual C++ if you are using pre-compiled headers
#include "stdafx.h"

#include "dmcwin.h"

CDMCWin::CDMCWin()
{
	m_usController = 0;
	m_hWnd = 0;
	m_lThreadID = 0;
	m_bConnected = FALSE;
	m_hDmc = -1;
	m_lLastError = 0;

#ifdef DMCMULTIPLETHREADS
	InitializeCriticalSection(&m_CritSec);
#endif
}

CDMCWin::CDMCWin(USHORT usController, HWND hWnd, LONG lThreadID)
{
	m_usController = usController;
	m_hWnd = hWnd;
	m_lThreadID = lThreadID;
	m_bConnected = FALSE;	
	m_hDmc = -1;
	m_lLastError = 0;

#ifdef DMCMULTIPLETHREADS
	InitializeCriticalSection(&m_CritSec);
#endif
	
	if (m_usController > 0 && m_usController < 17)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		if (m_lThreadID)
			m_lLastError = DMCOpen2(m_usController, m_lThreadID, &m_hDmc);
		else	
			m_lLastError = DMCOpen(m_usController, m_hWnd, &m_hDmc);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
		if (m_lLastError == 0)
			m_bConnected = TRUE;
		else
			m_hDmc = -1;
	}
}

CDMCWin::~CDMCWin()
{
	if (m_hDmc != -1)
		Close();

#ifdef DMCMULTIPLETHREADS
	DeleteCriticalSection(&m_CritSec);
#endif
}

LONG CDMCWin::Open()
{
	m_lLastError = 0;
	
	if (m_bConnected)
		return m_lLastError;
	
	if (m_usController > 0 && m_usController < 17)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		if (m_lThreadID)
			m_lLastError = DMCOpen2(m_usController, m_lThreadID, &m_hDmc);
		else	
			m_lLastError = DMCOpen(m_usController, m_hWnd, &m_hDmc);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif		
		if (m_lLastError == 0)
			m_bConnected = TRUE;
		else
			m_hDmc = -1;
	}
	else
		m_lLastError = DMCERROR_CONTROLLER; 
		
	return m_lLastError;		
}

LONG CDMCWin::Open(USHORT usController, HWND hWnd, LONG lThreadID)
{
	m_usController = usController;
	m_hWnd = hWnd;
	m_lThreadID = lThreadID;

	return Open();
}

HANDLEDMC CDMCWin::GetHandle()
{
	if (m_hDmc != -1)
		return m_hDmc;
		
	if (m_usController > 0 && m_usController < 17)
	{	
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCGetHandle(m_usController, &m_hDmc);		
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
		if (m_lLastError == 0)
			return m_hDmc;
	}		
	
	return -1;			
}

void CDMCWin::SethWnd(HWND hWnd)
{
	m_hWnd = hWnd;

	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCChangeInterruptNotification(m_hDmc, (long)hWnd);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
};

void CDMCWin::SetThreadID(LONG lThreadID)
{
	m_lThreadID = lThreadID;

	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCChangeInterruptNotification(m_hDmc, (long)lThreadID);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
};	

LONG CDMCWin::Close()
{
	m_lLastError = 0;

	if (m_hDmc != -1)	
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCClose(m_hDmc);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}

	m_hDmc = -1;
	m_bConnected = FALSE;
	
	return m_lLastError;
}

LONG CDMCWin::Command(const PSZ pszCommand, PCHAR pchResponse, ULONG cbResponse)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCCommand(m_hDmc, (PSZ)pszCommand, pchResponse, cbResponse);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	else
		m_lLastError = DMCERROR_HANDLE;		
	
	return m_lLastError;
}

LONG CDMCWin::FastCommand(const PSZ pszCommand)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCFastCommand(m_hDmc, (PSZ)pszCommand);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	else
		m_lLastError = DMCERROR_HANDLE;		
	
	return m_lLastError;
}

LONG CDMCWin::BinaryCommand(PBYTE pbCommand, ULONG ulCommandLength, PCHAR pchResponse, ULONG cbResponse)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCBinaryCommand(m_hDmc, pbCommand, ulCommandLength, pchResponse, cbResponse);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	else
		m_lLastError = DMCERROR_HANDLE;		
	
	return m_lLastError;
}

LONG CDMCWin::GetUnsolicitedResponse(PCHAR pchResponse, ULONG cbResponse)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCGetUnsolicitedResponse(m_hDmc, pchResponse, cbResponse);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	else
		m_lLastError = DMCERROR_HANDLE;		
	
	return m_lLastError;
}

LONG CDMCWin::GetAdditionalResponseLen()
{
	LONG	lLength;

	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCGetAdditionalResponseLen(m_hDmc, (PULONG)&lLength);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	else
		m_lLastError = DMCERROR_HANDLE;		
	
	if (m_lLastError != 0)
		lLength = 0;
		
	return lLength;		
}

LONG CDMCWin::GetAdditionalResponse(PCHAR pchResponse, ULONG cbResponse)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCGetAdditionalResponse(m_hDmc, pchResponse, cbResponse);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	else
		m_lLastError = DMCERROR_HANDLE;		
	
	return m_lLastError;
}

LONG CDMCWin::GetErrorText(LONG lError, PCHAR pchMessage, ULONG cbMessage)
{
#ifdef DMCMULTIPLETHREADS
	EnterCriticalSection(&m_CritSec);
#endif
	m_lLastError = DMCError(m_hDmc, lError, pchMessage, cbMessage);
#ifdef DMCMULTIPLETHREADS
	LeaveCriticalSection(&m_CritSec);
#endif
	
	return m_lLastError;
}

LONG CDMCWin::Clear()
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCClear(m_hDmc);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}

	return m_lLastError;
}

LONG CDMCWin::Reset()
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCReset(m_hDmc);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}

	return m_lLastError;
}

LONG CDMCWin::MasterReset()
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCMasterReset(m_hDmc);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}

	return m_lLastError;
}

LONG CDMCWin::GetVersion(PCHAR pchVersion, ULONG cbVersion)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCVersion(m_hDmc, pchVersion, cbVersion);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	
	return m_lLastError;
}

LONG CDMCWin::DownloadFile(const PSZ pszFileName, const PSZ pszLabel)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCDownloadFile(m_hDmc, (PSZ)pszFileName, (PSZ)pszLabel);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	
	return m_lLastError;
}

LONG CDMCWin::DownloadFromBuffer(const PSZ pszBuffer, const PSZ pszLabel)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCDownloadFromBuffer(m_hDmc, (PSZ)pszBuffer, (PSZ)pszLabel);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	
	return m_lLastError;
}

LONG CDMCWin::UploadFile(const PSZ pszFileName)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCUploadFile(m_hDmc, (PSZ)pszFileName);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	
	return m_lLastError;
}

LONG CDMCWin::UploadToBuffer(PCHAR pchBuffer, ULONG cbBuffer)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCUploadToBuffer(m_hDmc, pchBuffer, cbBuffer);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	
	return m_lLastError;
}

LONG CDMCWin::SendFile(const PSZ pszFileName)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCSendFile(m_hDmc, (PSZ)pszFileName);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	
	return m_lLastError;
}

LONG CDMCWin::SendBinaryFile(const PSZ pszFileName)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCSendBinaryFile(m_hDmc, (PSZ)pszFileName);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	
	return m_lLastError;
}

LONG CDMCWin::AsciiCommandToBinaryCommand(PSZ pszAsciiCommand, ULONG ulAsciiCommandLength, PBYTE pbBinaryResult, ULONG cbBinaryResult, ULONG FAR *pulBinaryResultLength)
{
	m_lLastError = DMCCommand_AsciiToBinary(m_hDmc, pszAsciiCommand, ulAsciiCommandLength, pbBinaryResult, cbBinaryResult, pulBinaryResultLength);

	return m_lLastError;
}

LONG CDMCWin::BinaryCommandToAsciiCommand(PBYTE pbBinaryCommand, ULONG ulBinaryCommandLength, PSZ pszAsciiResult, ULONG cbAsciiResult, ULONG FAR *pulAsciiResultLength)
{
	m_lLastError = DMCCommand_BinaryToAscii(m_hDmc, pbBinaryCommand, ulBinaryCommandLength, pszAsciiResult, cbAsciiResult, pulAsciiResultLength);

	return m_lLastError;
}

LONG CDMCWin::AsciiFileToBinaryFile(const PSZ pszInputFileName, const PSZ pszOutputFileName)
{
	m_lLastError = DMCFile_AsciiToBinary(m_hDmc, (PSZ)pszInputFileName, (PSZ)pszOutputFileName);

	return m_lLastError;
}

LONG CDMCWin::BinaryFileToAsciiFile(const PSZ pszInputFileName, const PSZ pszOutputFileName)
{
	m_lLastError = DMCFile_BinaryToAscii(m_hDmc, (PSZ)pszInputFileName, (PSZ)pszOutputFileName);

	return m_lLastError;
}

LONG CDMCWin::RefreshDataRecord(ULONG ulLength)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCRefreshDataRecord(m_hDmc, ulLength);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	
	return m_lLastError;
}

LONG CDMCWin::GetDataRecord(USHORT usGeneralOffset, USHORT usAxisInfoOffset, PUSHORT pusDataType, PLONG plData)
{
	if (pusDataType)
		*pusDataType = 0;

	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCGetDataRecord(m_hDmc, usGeneralOffset, usAxisInfoOffset, pusDataType, plData);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}
	
	return m_lLastError;
}

LONG CDMCWin::GetDataRecordByItemId(USHORT usItemId, USHORT usAxisId, PUSHORT pusDataType, PLONG plData)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCGetDataRecordByItemId(m_hDmc, usItemId, usAxisId, pusDataType, plData);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}

	return m_lLastError;
}

LONG CDMCWin::GetDataRecordSize(PUSHORT pusRecordSize)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCGetDataRecordSize(m_hDmc, pusRecordSize);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}

	return m_lLastError;
}

LONG CDMCWin::CopyDataRecord(PVOID pDataRecord)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCCopyDataRecord(m_hDmc, pDataRecord);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}

	return m_lLastError;
}

LONG CDMCWin::GetDataRecordRevision(PUSHORT pusRevision)
{
	if (m_bConnected)
	{
#ifdef DMCMULTIPLETHREADS
		EnterCriticalSection(&m_CritSec);
#endif
		m_lLastError = DMCGetDataRecordRevision(m_hDmc, pusRevision);
#ifdef DMCMULTIPLETHREADS
		LeaveCriticalSection(&m_CritSec);
#endif
	}

	return m_lLastError;
}

LONG CDMCWin::DiagnosticsOn(const PSZ pszFileName, BOOL bAppend)
{
	m_lLastError = DMCDiagnosticsOn(m_hDmc, (PSZ)pszFileName, bAppend);
	
	return m_lLastError;
}

LONG CDMCWin::DiagnosticsOff()
{
	m_lLastError = DMCDiagnosticsOff(m_hDmc);
	
	return m_lLastError;
}

LONG CDMCWin::GetTimeout()
{
	LONG	lTimeout;

	m_lLastError = DMCGetTimeout(m_hDmc, &lTimeout);
	
	if (m_lLastError != 0)
		lTimeout = 0;
		
	return lTimeout;		
}

void CDMCWin::SetTimeout(LONG lTimeout)
{
	m_lLastError = DMCSetTimeout(m_hDmc, lTimeout);
}

LONG CDMCWin::GetDelay()
{
	LONG	lDelay;

	m_lLastError = DMCGetDelay(m_hDmc, &lDelay);
	
	if (m_lLastError != 0)
		lDelay = 0;
		
	return lDelay;		
}

void CDMCWin::SetDelay(LONG lDelay)
{
	m_lLastError = DMCSetDelay(m_hDmc, lDelay);	
}

LONG CDMCWin::WaitForMotionComplete(const PSZ pszAxes, SHORT fDispatchMsgs)
{
	LONG				rc = WAIT_OBJECT_0 + 1;
	DWORD				ThreadId;
	HANDLE			hThread;
	MOTIONTHREAD	mt;

	if (!m_bConnected)
	{
		m_lLastError = DMCERROR_HANDLE;
		return m_lLastError;
	}

	if (!pszAxes)
	{
		m_lLastError = DMCERROR_ARGUMENT;
		return m_lLastError;
	}

	mt.hDmc = m_hDmc;
	strcpy(mt.szAxes, pszAxes);
	mt.rc = 0;
	mt.ThreadId = GetCurrentThreadId();
#ifdef DMCMULTIPLETHREADS
	mt.pCritSec = &m_CritSec;
#endif

	hThread = CreateThread(NULL, 0, MotionCompleteThread, (LPVOID)&mt, 0, &ThreadId);
	if (!hThread)
	{
		m_lLastError = DMCERROR_DRIVER;	
		return m_lLastError;
	}

	if (fDispatchMsgs)
	{
		while (rc != WAIT_OBJECT_0)
		{
			rc = MsgWaitForMultipleObjects(1, &hThread, FALSE, INFINITE, QS_ALLINPUT);
			if (rc == WAIT_OBJECT_0 + 1)
			{
				MSG	msg;
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					if (msg.message == WM_MOTIONCOMPLETE)
					{
						rc = WAIT_OBJECT_0;
						break;
					}
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}
	else
		WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);

	m_lLastError = mt.rc;

	return m_lLastError;
}

DWORD WINAPI MotionCompleteThread(LPVOID pArgs)
{
	int				i;
	int				bLoop;
	int				iAxes;
	long				rc = 0L;
	char				szCMD[8];
	char				szResponse[32];
	MOTIONTHREAD*	pmt = (MOTIONTHREAD*)pArgs;

	if (!pmt)
	{
		ExitThread((DWORD)DMCERROR_DRIVER);
		return (DWORD)DMCERROR_DRIVER;
	}

	// How many axes?
	iAxes = strlen(pmt->szAxes);

	for (i = 0; i < iAxes; i++)
	{
		// Check each axis in turn
		bLoop = TRUE;
		sprintf(szCMD, "MG_BG%c\r", pmt->szAxes[i]);
		// Loop while motion is not complete
		while (bLoop)
		{
#ifdef DMCMULTIPLETHREADS
			EnterCriticalSection(pmt->pCritSec);
#endif
			rc = DMCCommand(pmt->hDmc, szCMD, szResponse, sizeof(szResponse));
#ifdef DMCMULTIPLETHREADS
			LeaveCriticalSection(pmt->pCritSec);
#endif
			if (rc == DMCNOERROR)
			{
				if (!atoi(szResponse))
					bLoop = FALSE;
				else
					Sleep(5);
			}
			else if (rc == DMCERROR_TIMEOUT)
				; // Do nothing
			else 
				bLoop = FALSE;
		}
	}

	if (pmt->ThreadId)
		PostThreadMessage(pmt->ThreadId, WM_MOTIONCOMPLETE, 0, 0);

	pmt->rc = rc;

	ExitThread(0);

	return 0;
}

CDMCWinRegistry::CDMCWinRegistry()
{
	m_lLastError = 0;
}

CDMCWinRegistry::~CDMCWinRegistry()
{

}

LONG CDMCWinRegistry::AddGalilRegistry(PGALILREGISTRY pgalilregistry, PUSHORT pusController)
{

	m_lLastError = DMCAddGalilRegistry(pgalilregistry, pusController);

	return m_lLastError;
}

LONG CDMCWinRegistry::AddGalilRegistry(PGALILREGISTRY2 pgalilregistry2, PUSHORT pusController)
{

	m_lLastError = DMCAddGalilRegistry2(pgalilregistry2, pusController);

	return m_lLastError;
}

LONG CDMCWinRegistry::ModifyGalilRegistry(USHORT usController, PGALILREGISTRY pgalilregistry)
{

	m_lLastError = DMCModifyGalilRegistry(usController, pgalilregistry);

	return m_lLastError;
}

LONG CDMCWinRegistry::ModifyGalilRegistry(USHORT usController, PGALILREGISTRY2 pgalilregistry2)
{

	m_lLastError = DMCModifyGalilRegistry2(usController, pgalilregistry2);

	return m_lLastError;
}

LONG CDMCWinRegistry::GetGalilRegistryInfo(USHORT usController, PGALILREGISTRY pgalilregistry)
{

	m_lLastError = DMCGetGalilRegistryInfo(usController, pgalilregistry);

	return m_lLastError;
}

LONG CDMCWinRegistry::GetGalilRegistryInfo(USHORT usController, PGALILREGISTRY2 pgalilregistry2)
{

	m_lLastError = DMCGetGalilRegistryInfo2(usController, pgalilregistry2);

	return m_lLastError;
}

LONG CDMCWinRegistry::DeleteGalilRegistry(SHORT sController)
{

	m_lLastError = DMCDeleteGalilRegistry(sController);

	return m_lLastError;
}

SHORT CDMCWinRegistry::SelectController(HWND hwnd)
{
	return DMCSelectController(hwnd);
}

void CDMCWinRegistry::EditRegistry(HWND hwnd)
{
	DMCEditRegistry(hwnd);
}
