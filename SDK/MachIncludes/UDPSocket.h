#pragma once
 


// CUDPSocket command target
 


class CUDPSocket : public CAsyncSocket
{
public:
	
	CUDPSocket();
	virtual ~CUDPSocket();
	bool Create(UINT nSocketPort);
	bool CreateStream(UINT nSocketPort, LPCTSTR ip);
	void OnReceive(int nErrorCode);
	void OnAccept(int nErrorCode);
	void OnConnect(int err);
	int ReceiveFromHelper(void* lpBuf, int nBufLen,
		SOCKADDR* lpSockAddr, int* lpSockAddrLen, int nFlags);
};


