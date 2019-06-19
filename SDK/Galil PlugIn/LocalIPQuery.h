// LocalIPQuery.h: interface for the LocalIPQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCALIPQUERY_H__2D4B8641_0BFB_49E8_9C5C_3C86917FA10A__INCLUDED_)
#define AFX_LOCALIPQUERY_H__2D4B8641_0BFB_49E8_9C5C_3C86917FA10A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



const UINT TABLESIZE = (500*20+4);

 
#include <vector>
#include "iphlpapi.h"

class IPAddressBase  
{
public:
	IPAddressBase();
	virtual ~IPAddressBase();

	DWORD GetHBO()const;
	DWORD GetNBO()const;
	CString GetString()const;

	void SetHBO(DWORD dwInValue);
	void SetNBO(DWORD dwInValue);
	void SetString(CString csInString);

protected:
	CString				m_csAddress;

};


using namespace std;


#define LIPQ_PORTABLE		1
#define LIPQ_MULTI			2

// User must choose which method they want to use
//#define USE_THIS	LIPQ_PORTABLE
#define USE_THIS	LIPQ_MULTI


class LocalIPQuery  
{
public:
	LocalIPQuery();
	virtual ~LocalIPQuery();
	vector<IPAddressBase> m_vIPAddress;

#if (USE_THIS == LIPQ_MULTI)
protected:
	PMIB_TCPTABLE		m_tcpTable;
	BYTE				m_pBuffer[TABLESIZE];
	DWORD				m_dwTableSize;
	in_addr				m_addrLoc;
#endif

};

#endif // !defined(AFX_LOCALIPQUERY_H__2D4B8641_0BFB_49E8_9C5C_3C86917FA10A__INCLUDED_)
