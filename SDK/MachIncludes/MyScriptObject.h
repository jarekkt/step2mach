#if !defined(AFX_MYSCRIPTOBJECT_H__1C7D9AE8_FCAF_47D1_8C09_2CCF34FB3411__INCLUDED_)
#define AFX_MYSCRIPTOBJECT_H__1C7D9AE8_FCAF_47D1_8C09_2CCF34FB3411__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyScriptObject.h : header file
//

#include "Mach1Button.h"
#include "DRO2.h"
 

/////////////////////////////////////////////////////////////////////////////
// MyScriptObject command target

class MyScriptObject : public CCmdTarget
{
	DECLARE_DYNCREATE(MyScriptObject)

	MyScriptObject();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
 
	virtual ~MyScriptObject();
	void    *TrajControl;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyScriptObject)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	

	// Generated message map functions
	//{{AFX_MSG(MyScriptObject)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(MyScriptObject)
	afx_msg void StraightFeed(double x, double y, double z, double a, double b, double c);
	afx_msg void HelpAbout();
	afx_msg double GetSafeZ();
	afx_msg void SetSafeZ(double SafeZ);
	afx_msg void SetCurrentTool(short Tool);
	afx_msg short GetSelectedTool();
	afx_msg double GetToolChangeStart(short Axis);
	afx_msg void StraightTraverse(double x, double y, double z, double a, double b, double c);
	afx_msg double ToolLengthOffset();
	afx_msg double CommandedFeed();
	afx_msg void SetFeedRate(double Rate);
	afx_msg void ActivateSignal(short Signal);
	afx_msg BOOL IsActive(short Signal);
	afx_msg void DeActivateSignal(short Signal);
	afx_msg void SystemWaitFor(short Signal);
	afx_msg double Param1();
	afx_msg double Param2();
	afx_msg double Param3();
	afx_msg void VerifyAxis(BOOL Silent);
	afx_msg double GetVar(short var);
	afx_msg void SetVar(short var, double value);
	afx_msg double Question(LPCTSTR Text);
	afx_msg short QueueDepth();
	afx_msg void OpenDigFile();
	afx_msg void CloseDigFile();
	afx_msg void THCOn();
	afx_msg void THCOff();
	afx_msg void Code(LPCTSTR Command);
	afx_msg double GetScale(short Axis);
	afx_msg void SetScale(short Axis, double Scale);
	afx_msg void SendSerial(LPCTSTR String);

	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	 Mach1Button  OEMButton;
	 DRO2         OEMDro;
     
	 
public:
	BYTE GetPortByte(USHORT PortAddress);

	enum 
	{dispidResetAxisSwap = 165L,dispidSwapAxis = 164L,dispidLoadLinTable = 163L,dispidGetDROString = 162L,dispidAskTextQuestion = 161L,dispidGetTimer = 160L,dispidSetTimer = 159L,dispidSendFIFOword = 158L,dispidSendFIFObyte = 157L,dispidSendFIFOcr = 156L,dispidSleep = 155L,dispidSetModIOString = 154L,dispidWaitForPoll = 153L,dispidIsWiz = 152L,dispidZeroTHC = 151L,dispidnFmt = 150L,dispidroun = 149L,dispidRound = 148L,dispidSendFIFO = 147L,   dispidRunProgram = 146L,dispidGetFiFoEntry = 145L,dispidGetTurretAng = 144L,dispidSetToolZ = 143L,dispidSetToolX = 142L,dispidOpenSubFile = 141L,dispidJogOff = 140L,dispidJogOn = 139L,dispidSetHomannString = 138L,   dispidSetTriggerMacro = 137L,
		dispidLoadFile = 136L,		dispidSetModOutput = 135L,		
		dispidGetInput = 134L,		dispidSetOutput = 133L,		
		dispidLoadWizard = 132L,		dispidSetPulley = 131L,	
		dispidGotoSafeZ = 130L,		dispidRetractMode = 129L,		
		dispidMaxY = 128L,		dispidMinY = 127L,		dispidMaxX = 126L,	
		dispidMinX = 125L,		dispidFileName = 124L,		dispidtCutDepth = 123L,	
		dispidFeedRate = 122L,		dispidtZClear = 121L,		
		dispidOpenSubroutineFile = 120L,		dispidtSetInFeedType = 119L,
		dispidtSetCutType = 118L,		dispidtGetInfeedType = 117L,
		dispidtGetCutType = 116L,		dispidtMinDepth = 115L,		
		dispidGetModWord = 114L,		dispidFillFromInput = 113L,
		dispidFillFromHolding = 112L,		dispidFillFromStatus = 111L,
		dispidFillFromCoil = 110L,		dispidModGetInputWord = 109L,	
		dispidIsDiameter = 108L,		dispidRandom = 107L,	
		dispidAppendTeachFile = 106L,		dispidGetMinPass = 105L,	
		dispidGetIJMode = 104L,		dispidSetIJMode = 103L,	
		dispidSingleVerifyReport = 102L,		dispidSaveWizard = 101L,		
		dispidIsStopped = 100L,		dispidMessage = 99L,		dispidSpeak = 98L,	
		dispidPlayWave = 97L,		dispidToggleScreens = 96L,		dispidSetPage = 95L,	
		dispidGetPage = 94L,		dispidSingleVerify = 93L,	
		dispidIsOutputActive = 92L,		dispidLoadTeachFile = 91L,	
		dispidLoadStandardLayout = 90L,		dispidSetButtonText = 89L,	
		dispidCloseTeachFile = 88L,		dispidOpenTeachFile = 87L,		
		dispidIsSuchSignal = 86L,		dispidRefCombination = 85L,	
		dispidSetUserLabel = 84L,		dispidSetTicker = 83L,		
		dispidtTapers = 82L,		dispidThreadDepth = 81L,	
		dispidInFeeds = 80L,		dispidSetSpinSpeed = 79L,	
		dispidDoSpinStop = 78L,		dispidDoSpinCCW = 77L,		
		dispidDoSpinCW = 76L,		dispidGetRPM = 75L,		
		dispidGetABSPosition = 74L,		dispidIsLoading = 73L,	
		dispidtDepthLastPass = 72L,		dispidtInFeed = 71L,	
		dispidtTaper = 70L,		dispidtChamfer = 69L,	
		dispidtFirstPass = 68L,		dispidtSpring = 67L,
		dispidtLead = 66L,		dispidtClearX = 65L,		
		dispidtEndZ = 64L,		dispidtEndX = 63L,		
		dispidtZStart = 62L,		dispidtXStart = 61L,
		dispidGetUserLED = 60L,		dispidGetUserDRO = 59L,	
		dispidSetUserLED = 58L,	
		dispidSetUserDRO = 57L,		dispidRunFile = 56L,	
		dispidSetMachZero = 55L,		dispidIsFirst = 54L,	
		dispidGetACoor = 53L,		dispidGetZCoor = 52L,	
		dispidGetYCoor = 51L,		dispidGetXCoor = 50L,	
		dispidGetCoord = 49L,		dispidSetOEMDRO = 48L,	
		dispidSetDRO = 47L,		dispidGetDRO = 46L,		
		dispidGetOEMDRO = 45L,		dispidGetOEMLed = 44L,	
		dispidGetLED = 43L,		dispidDoButton = 42L,	
		dispidLoadRun = 41L,		dispidDoOEMButton = 40L,	
		dispidGetCurrentTool = 39L,		 dispidSetParam = 37L,	
		dispidGetParam = 36L,		dispidResetTHC = 35L,	
		dispidIsMoving = 34L,		dispidPutPortByte = 33L,	
		dispidGetPortByte = 32L
	};
	SHORT PutPortByte(USHORT PortAddress, BYTE data);
	USHORT IsMoving(void);
	void ResetTHC(void);
	DOUBLE GetParam(LPCTSTR Param);
	void SetParam(LPCTSTR Param, DOUBLE Value);
	 
	SHORT GetCurrentTool(void);
	void DoOEMButton(SHORT Button);
	void LoadRun(LPCTSTR FileName);
	void DoButton(SHORT function);
	void KillExponent( CString &com, LPCTSTR Original );
public:
	bool GetLEDCondition(int Led);
	bool GetFloodCond();
	bool GetMistCond();
	bool GetSpindleCond();
public:
	int GetLED(SHORT Led);
	void SetTriggerMacro(SHORT macro);
	int GetOEMLed(SHORT Led);
	DOUBLE GetOEMDRO(SHORT dro);
	DOUBLE GetDRO(SHORT dro);
	void SetDRO(SHORT dro, DOUBLE value);
	void SetOEMDRO(SHORT dro, DOUBLE Value);
	void GetCoord(LPCTSTR Question);
	DOUBLE GetXCoor(void);
	DOUBLE GetYCoor(void);
	DOUBLE GetZCoor(void);
	DOUBLE GetACoor(void);
	int IsFirst(void);
	void SetMachZero(SHORT axis);
	void RunFile(void);
	void SetUserDRO(SHORT dro, DOUBLE value);
	void SetUserLED(SHORT led, SHORT state);
	DOUBLE GetUserDRO(SHORT dro);
	SHORT GetUserLED(SHORT led);
	DOUBLE tXStart(void);
	DOUBLE tZStart(void);
	DOUBLE tEndX(void);
	DOUBLE tEndZ(void);
	DOUBLE tClearX(void);
	DOUBLE tLead(void);
	SHORT tSpring(void);
	DOUBLE tFirstPass(void);
	DOUBLE tChamfer(void);
	DOUBLE tTaper(void);
	DOUBLE tInFeed(void);
	DOUBLE tDepthLastPass(void);
	SHORT IsLoading(void);
	DOUBLE GetABSPosition(SHORT Axis);
	DOUBLE GetRPM(void);
	void DoSpinCW();
	void DoSpinCCW();
	void DoSpinStop(void);
	void SetSpinSpeed(DOUBLE rpm);
	DOUBLE InFeeds(SHORT iteration);
	DOUBLE ThreadDepth(SHORT iteration);
	DOUBLE tTapers(SHORT iteration);
	void SetTicker(SHORT TickerNum,LPCTSTR Message);
	void SetUserLabel(SHORT LabelNum, LPCTSTR Label);
	void RefCombination(SHORT combo);
	VARIANT_BOOL IsSuchSignal(SHORT signal);
	SHORT OpenTeachFile(LPCTSTR name);
	void CloseTeachFile(void);
	void SetButtonText(LPCTSTR Text);
	void LoadStandardLayout(void);
	void LoadTeachFile(void);
	VARIANT_BOOL IsOutputActive(SHORT signal);
	void SingleVerify(SHORT axis);
	SHORT GetPage(void);
	void SetPage(SHORT page);
	void ToggleScreens(void);
	void PlayWave(LPCTSTR wavename);
	void Speak(LPCTSTR text);
	void Message(LPCTSTR text);
	SHORT IsStopped(void);
	void SaveWizard(void);
	void SingleVerifyReport(SHORT axis);
public:
	void SetIJAbs(void);
	int SetIJInc(void);
public:
	void SetIJMode(SHORT mode);
	SHORT GetIJMode(void);
	DOUBLE GetMinPass(void);
protected:
	SHORT AppendTeachFile(LPCTSTR name);
	DOUBLE Random(void);
	SHORT IsDiameter(void);
	SHORT ModGetInputWord(SHORT bit);
	SHORT FillFromCoil(SHORT slave, SHORT startAddress, SHORT nBytes);
	SHORT FillFromStatus(SHORT slave, SHORT startAddress, SHORT nBytes);
	SHORT FillFromHolding(SHORT slave, SHORT startAddress, SHORT nBytes);
	SHORT FillFromInput(SHORT slave, SHORT startAddress, SHORT nBytes);
	SHORT GetModWord(SHORT index);
	DOUBLE tMinDepth(void);
	SHORT tGetCutType(void);
	SHORT tGetInfeedType(void);
	void tSetCutType(SHORT type);
	void tSetInFeedType(SHORT type);
	SHORT OpenSubroutineFile(LPCTSTR name);
	DOUBLE tZClear(void);
	DOUBLE FeedRate(void);
	DOUBLE tCutDepth(void);
	BSTR FileName(void);
	DOUBLE MinX(void);
	DOUBLE MaxX(void);
	DOUBLE MinY(void);
	DOUBLE MaxY(void);
	SHORT RetractMode(void);
	void GotoSafeZ(void);
	void SetPulley(SHORT pulley);
	 
	void LoadWizard(LPCTSTR Name);
	void SetOutput(SHORT word);
	SHORT GetInput(SHORT word);
	void SetModOutput(SHORT reg, SHORT value);
	void LoadFile(LPCTSTR FileName);
	void SetHomannString(short x, short y,LPCTSTR text);
	void JogOn(SHORT axis, SHORT dir);
	void JogOff(SHORT axis);
	void OpenSubFile(LPCTSTR filename);
	void SetToolX(DOUBLE value);
	void SetToolZ(DOUBLE value);
	DOUBLE GetTurretAng(void);
	BSTR GetFiFoEntry(void);
	void RunProgram(LPCTSTR Program);
	 
	void SendFIFO(LPCTSTR com);
	DOUBLE Round(DOUBLE val);
	DOUBLE roun(DOUBLE val);
	DOUBLE nFmt(DOUBLE vAL, SHORT DEC);
	void ZeroTHC(void);
	SHORT IsWiz(void);
	void WaitForPoll(void);
	void SetModIOString(SHORT Slave, SHORT X, SHORT Y, LPCTSTR OutText);
	void Sleep(SHORT time);
	void SendFIFOcr(LPCTSTR data);
	void SendFIFObyte(SHORT byte);
	void SendFIFOword(SHORT data);
	void SetTimer(SHORT timer);
	DOUBLE GetTimer(SHORT timer);
	BSTR AskTextQuestion(LPCTSTR question);
	BSTR GetDROString(SHORT nDRO);
	void LoadLinTable(void);
	void SwapAxis(SHORT Primary, SHORT Secondary);
	void ResetAxisSwap(void);
};

 

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSCRIPTOBJECT_H__1C7D9AE8_FCAF_47D1_8C09_2CCF34FB3411__INCLUDED_)
