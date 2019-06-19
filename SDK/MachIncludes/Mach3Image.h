#pragma once

// Mach3Image

class Mach3Image : public CWnd
{
	DECLARE_DYNAMIC(Mach3Image)

public:
	Mach3Image();
	virtual ~Mach3Image();
	CString FindExtension(const CString& name);
	int FindType(const CString& ext);

protected:
	DECLARE_MESSAGE_MAP()
public:
	bool LoadImage(LPCTSTR file);
};


