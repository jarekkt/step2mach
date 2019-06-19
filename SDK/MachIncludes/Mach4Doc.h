// Mach4Doc.h : interface of the CMach4Doc class
//


#pragma once

class CMach4Doc : public CDocument
{
protected: // create from serialization only
	CMach4Doc();
	DECLARE_DYNCREATE(CMach4Doc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CMach4Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	void LoadGCodeFile(LPCTSTR FileName);

	enum 
	{
		dispidCloseFile = 2L,		dispidLoadGCodeFile = 1L
	};
	void CloseFile(void);
};


