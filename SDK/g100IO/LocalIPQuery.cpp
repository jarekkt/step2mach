// LocalIPQuery.cpp: implementation of the LocalIPQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LocalIPQuery.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 

IPAddressBase::IPAddressBase():m_csAddress("127.0.0.1")
{

}

IPAddressBase::~IPAddressBase()
{

}


DWORD IPAddressBase::GetHBO() const
{
	return inet_addr(m_csAddress);
}


DWORD IPAddressBase::GetNBO() const
{
	return htonl(inet_addr(m_csAddress));
}


CString IPAddressBase::GetString() const
{
	return this->m_csAddress;
}


void IPAddressBase::SetHBO(DWORD dwInValue)
{
	in_addr addrLoc;
	addrLoc.S_un.S_addr = dwInValue;
	this->m_csAddress = inet_ntoa(addrLoc);
}

void IPAddressBase::SetNBO(DWORD dwInValue)
{
	in_addr addrLoc;
	addrLoc.S_un.S_addr = ntohl(dwInValue);
	this->m_csAddress = inet_ntoa(addrLoc);
}


void IPAddressBase::SetString(CString csInString)
{
	this->m_csAddress = csInString;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LocalIPQuery::LocalIPQuery()
{

#if (USE_THIS == LIPQ_MULTI) //method to extract all active IP address on machine uses iphlpapi
	m_dwTableSize = TABLESIZE;
	IPAddressBase ipaTemp;
	DWORD dw127001 = ipaTemp.GetHBO(); // sets dw127001 to "127.0.0.1" in HBO
	DWORD dwHBOLocIP;	

	DWORD dwRet = GetTcpTable((PMIB_TCPTABLE)m_pBuffer, &m_dwTableSize, TRUE);
	
	if(dwRet == NO_ERROR)
	{
		m_tcpTable = (PMIB_TCPTABLE)m_pBuffer;

		// use to prevent "127.0.0.1" from being filtered out if it is first in table
		if(m_tcpTable->table[0].dwLocalAddr == dw127001)
		{
			m_vIPAddress.push_back(ipaTemp);
		}

		for(DWORD i = 0; i < m_tcpTable->dwNumEntries; i++)
		{ 
			dwHBOLocIP = (m_tcpTable->table[i].dwLocalAddr);

			if(dwHBOLocIP != ipaTemp.GetHBO())
			{
				ipaTemp.SetHBO(dwHBOLocIP);
				m_vIPAddress.push_back(ipaTemp);
			}
		}
	}
	
#endif // END LIPQ_MULTI




#if (USE_THIS == LIPQ_PORTABLE) // portable Method based on winsocks
	IPAddressBase ipaTemp;
	WSAData wsaData;
    WSAStartup(MAKEWORD(1, 1), &wsaData);


    char sAc[80];
    gethostname(sAc, sizeof(sAc));


    struct hostent *pHe = gethostbyname(sAc);


    for (int i = 0; pHe->h_addr_list[i] != 0; ++i) 
	{
        struct in_addr addrLoc;
        memcpy(&addrLoc, pHe->h_addr_list[i], sizeof(struct in_addr));
		ipaTemp.SetString(inet_ntoa(addrLoc));
        this->m_vIPAddress.push_back(ipaTemp);
    }


    WSACleanup();
#endif // END LIPQ_PORTABLE

}

LocalIPQuery::~LocalIPQuery()
{

}

