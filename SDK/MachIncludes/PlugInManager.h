#pragma once

 

struct MyPlugs
{
  
};

extern MyPlugs PlugIns;


// PlugInManager

class PlugInManager : public CWnd
{
	DECLARE_DYNAMIC(PlugInManager)

public:
	PlugInManager();
	virtual ~PlugInManager();

protected:
	DECLARE_MESSAGE_MAP()
public:
	bool Init(void);
	void Config(void);
};


