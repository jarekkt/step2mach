// UDPSocket.cpp : implementation file
//
//  This file is used for asyncronous communications to and from the G100. 
// It uses an IP or a UDP Socket to do so. 


#include "stdafx.h"
#include "UDPSocket.h"
#include "G200x.h"

extern void PlugReceive( char *Buffer, int m_size );
 
// CUDPSocket

CUDPSocket::CUDPSocket()
{
}

CUDPSocket::~CUDPSocket()
{
}

void CUDPSocket::OnReceive(int nErrorCode) 
{
	int m_size;
	CString m_IPAddress;
	UINT m_Port;
	CString Message;
	char Buffer[512];	// Increase in size as needed
	DWORD Error;
   
    if (nErrorCode) 
	{
	   return;
	}
    m_size = ReceiveFrom(Buffer, sizeof Buffer, m_IPAddress, m_Port);
    if (!m_size || m_size == SOCKET_ERROR) 
	{
	  Error = GetLastError();
	  return;
	}
	
    PlugReceive( Buffer, m_size ); //send message to PlugIn. Itll know what to do with it..
	CAsyncSocket::OnReceive(nErrorCode);
// process the data
}

bool CUDPSocket::Create(UINT nSocketPort) {
	CString Message;
	DWORD Error;

if (CAsyncSocket::Create(nSocketPort, 
	         SOCK_DGRAM, FD_READ | FD_WRITE | FD_ACCEPT | FD_CONNECT | FD_CLOSE,
			 0))
	return true;
Error = GetLastError();
Message.Format("The socket for port %u was not created; error %u",
		nSocketPort, Error);
AfxMessageBox(Message);
return false;
}

bool CUDPSocket::CreateStream(UINT nSocketPort,LPCTSTR ip ) {
	CString Message;
	DWORD Error;

if (CAsyncSocket::Create(nSocketPort, 
	         SOCK_STREAM, FD_READ | FD_WRITE | FD_ACCEPT | FD_CONNECT | FD_CLOSE,
			 ip))
	return true;
Error = GetLastError();
Message.Format("The socket for port %u was not created; error %u",
		nSocketPort, Error);
//AfxMessageBox(Message);
return false;
}

void CUDPSocket::OnAccept(int nErrorCode)
{ 

}

void CUDPSocket::OnConnect(int nErrorCode)
{

}
int CUDPSocket::ReceiveFromHelper(void* lpBuf, int nBufLen,
		SOCKADDR* lpSockAddr, int* lpSockAddrLen, int nFlags)
{
 return CAsyncSocket::ReceiveFromHelper(lpBuf, nBufLen,lpSockAddr,lpSockAddrLen,nFlags);
}

// CUDPSocket member functions
