// XMLProfile.h
// By Emilio Guijarro Cameros

#pragma once

#include <msxml.h>
#include <shlobj.h>

class CXMLProfile : public CObject
{
	IXMLDOMDocument *pXMLDoc;
	CString szFileName;
	IXMLDOMNode *GetEntry(LPCTSTR lpszSection, LPCTSTR lpszEntry);
	IXMLDOMNode *GetEntry4Write(LPCTSTR lpszSection, LPCTSTR lpszEntry);
	IXMLDOMNode *GetSection(LPCTSTR lpszEntry);

public:
	CXMLProfile();
	virtual ~CXMLProfile();
	void CloseProfile();
	bool WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue);
	bool WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, CString szDefault);
	int GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault);
	CString GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, CString szDefault);
	
};



