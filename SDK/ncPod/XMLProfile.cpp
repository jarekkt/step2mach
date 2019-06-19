// XMLProfile.cpp
// By Emilio Guijarro Cameros

#include "stdafx.h"
#include "XMLProfile.h"

extern CXMLProfile *AppProf;

// CXMLProfile

extern CString ProfileName;

CXMLProfile::CXMLProfile()
{
	VARIANT_BOOL bResult;
	IXMLDOMElement *base;
	HRESULT hr;
	if( AppProf == NULL ) AppProf = this;
	if (GetVersion() < 0x80000000) 
	{
		//szProfilesDir = new TCHAR[MAX_PATH];
		//SHGetSpecialFolderPath(NULL, szProfilesDir, CSIDL_LOCAL_APPDATA, true);
	    //::GetCurrentDirectory( 50, szProfilesDir ); //make this the filename of the MAch3 xml..
		szFileName = ProfileName; //Should be local Mach3 folder now..
		//delete szProfilesDir;
	}
	hr = CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER , IID_IXMLDOMDocument, (void**)&pXMLDoc);
	if(SUCCEEDED(hr)) 
	{
		pXMLDoc->load(COleVariant(szFileName), &bResult);
    }
   	pXMLDoc->get_documentElement(&base);

	if(base == NULL) {
		pXMLDoc->createElement(CComBSTR("profile"), &base);
		pXMLDoc->appendChild(base, NULL);
	}
	
}

CXMLProfile::~CXMLProfile()
{
	pXMLDoc->save(COleVariant(szFileName));
	pXMLDoc->Release();
}

 

// Funciones de miembro de CXMLProfile

bool CXMLProfile::WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue) {	
	IXMLDOMNode    *nEntry;
	wchar_t        *szTemp = new wchar_t[255];

	_itow(nValue, szTemp, 10);
	nEntry = GetEntry4Write(lpszSection, lpszEntry);
	nEntry->put_text(CComBSTR(szTemp));
	nEntry->Release();

	delete szTemp;
	
	return true;
}

bool CXMLProfile::WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, CString szValue) {
	IXMLDOMNode    *nEntry;

	nEntry = GetEntry4Write(lpszSection, lpszEntry);
	nEntry->put_text(CComBSTR(szValue));
	nEntry->Release();
	
	return true;
}

int CXMLProfile::GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault) {
	IXMLDOMNode    *nEntry;
	CComBSTR       szContent;

	nEntry = GetEntry(lpszSection, lpszEntry);
	if( nEntry == NULL ) return nDefault;
	nEntry->get_text(&szContent);	
	
	if(szContent == CComBSTR("")) {
		IXMLDOMNode *nParent;
		
		nEntry->get_parentNode(&nParent);
		nParent->removeChild(nEntry, NULL);
		
		nEntry->Release();
		nParent->Release();

		return nDefault;
	}	
	
	nEntry->Release();

	return _wtoi(szContent);
}

CString CXMLProfile::GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, CString szDefault) {
	IXMLDOMNode    *nEntry;
	CComBSTR       szContent;

	nEntry = GetEntry(lpszSection, lpszEntry);
	if( nEntry == NULL ) return szDefault;
	nEntry->get_text(&szContent);
	
	if(szContent == CComBSTR("")) {
		IXMLDOMNode *nParent;
		
		nEntry->get_parentNode(&nParent);
		nParent->removeChild(nEntry, NULL);
		
		nEntry->Release();
		nParent->Release();

		return szDefault;
	}

	nEntry->Release();

	return CString(szContent);
}

IXMLDOMNode * CXMLProfile::GetSection(LPCTSTR lpszSection)
{
	IXMLDOMElement *base, *element;
	IXMLDOMNode    *nSec, *nResult;
	CComBSTR       szName;
	bool           bSecFound = false, bEntryFound = false;
	wchar_t        *szTemp = new wchar_t[255];

	pXMLDoc->get_documentElement(&base);
	
	for(base->get_firstChild(&nSec); nSec != NULL; nSec->get_nextSibling(&nSec)) {
		nSec->get_baseName(&szName);

		if(szName == CComBSTR(lpszSection)) {
			nResult = nSec;
			break;
		}
	}

	if(nSec == NULL) {
		pXMLDoc->createElement(CComBSTR(lpszSection), &element);
		base->appendChild(element, &nSec);
		element->Release();
		nResult = nSec;
	}

	base->Release();
	
	return nResult;
}

IXMLDOMNode * CXMLProfile::GetEntry(LPCTSTR lpszSection, LPCTSTR lpszEntry)
{
	IXMLDOMElement *base ;
	IXMLDOMNode    *nSec, *nResult;
	CComBSTR       szName;
	CComBSTR       szNameCmp = CComBSTR(lpszEntry);

	pXMLDoc->get_documentElement(&base);
	base->selectSingleNode(CComBSTR(lpszSection),&nSec);
	if( nSec == NULL ) return NULL;
    nSec->selectSingleNode(CComBSTR(lpszEntry),&nResult);
    return nResult;
}
IXMLDOMNode * CXMLProfile::GetEntry4Write(LPCTSTR lpszSection, LPCTSTR lpszEntry)
{
		IXMLDOMElement *base, *element ;
	IXMLDOMNode    *nSec,  *nResult,   *nEntry;
	 
    
	pXMLDoc->get_documentElement(&base);
	base->selectSingleNode(CComBSTR(lpszSection),&nSec);
	if( nSec == NULL ) 
	{
	  pXMLDoc->createElement(CComBSTR(lpszSection), &element);
	  base->appendChild(element, &nSec);
	  element->Release();
	  pXMLDoc->createElement(CComBSTR(lpszEntry), &element);
	  nSec->appendChild(element, &nEntry);
	  element->Release();
	  nResult = nEntry;
	  base->Release();
	  return nResult;
	}
	else
	 nSec->selectSingleNode(CComBSTR(lpszEntry),&nEntry);

   
   if(nEntry == NULL)
     {
	  pXMLDoc->createElement(CComBSTR(lpszEntry), &element);
	  nSec->appendChild(element, &nEntry);
	  element->Release();
	  
	 }
   nSec->Release();
   base->Release();
   return nEntry;

}
