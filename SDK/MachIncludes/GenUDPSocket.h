#pragma once

// CUDPSocket command target
//#define uchar unsigned char


class GenSocket : public CAsyncSocket
{
public:
	
	GenSocket();
	virtual ~GenSocket();
	bool Create(UINT nSocketPort);
	void OnReceive(int nErrorCode);
	void OnAccept(int nErrorCode);
	void OnConnect(int err);
	int ReceiveFromHelper(void* lpBuf, int nBufLen,
		SOCKADDR* lpSockAddr, int* lpSockAddrLen, int nFlags);
};


