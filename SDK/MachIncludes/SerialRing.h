#pragma once
#include "processor.h"
#include "afxwin.h"
#include "afxcmn.h"

struct ComQueue
{
  CString Command;
  short Type;
  short Pnum;
};

struct Params
{
  double P[70];
};

enum {FIRMWARE, INITRING, RESET ,STATUS, CLEAR, GETPARAM ,SETPARAM, RESTART, ADJUSTINC,RMSSTATUS, GETPOS, GETVEL, MOVEDRIVE };
 

 

class SerialRing : public CDialog
{
	DECLARE_DYNAMIC(SerialRing)

public:
	SerialRing(CWnd* pParent = NULL);   // standard constructor
	virtual ~SerialRing();
    void Message(int mess );

// Dialog Data
	enum { IDD = IDD_SERIALRING };
	bool visible;
	TCallback<SerialRing> CallbackOutput; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnDataArrival(int size, char *buffer);
	void InitSerial();
	void SendReset();
	void TranslateMessage();
	void     PushString( char *buffer, short size,short Type,short pNum = 0 );
	CString  PopString();
	void    SetCommand( short drive, CString Command, short type, short pNum = 0 ); //formats and sends a command by drive#
	void    InitVars();
	void    ShowData(short drive);
	void    GetStatus( short Drive );
	void    ClearSafety( short Drive);
	void    GetParameter(short drive, short param);
	void    SetParameter(short drive, short param, double value);
	double  String2Param( CString in );
	int     Param2Int( double in );
	void    ReStartDrive(short drive);
	void    AdjustPosition(short drive, int amount);
	void    ClearStatus(short drive);
	void    GetRMS(short drive);
	void    GetPosition(short drive);
	void    GetVelocity(short drive);
	void    MoveDrive(short drive,short dist);
	void    UpdateParam();
	short    IsDisabled(void);

public:
	bool    FirstShrink;
	CStatic m_Display;
	short CurDriveDisp;
	int m_Port;
	bool connected;
	bool newdata;
	BOOL m_AutoConnect;
	unsigned char InData[256];
	char OutData[256];
	short InPtrHead;
	short InPtrTail;
	short OutPtr;
	bool AckComplete;
    bool CommandHolding;
    short nCommands;
	short comtail,comhead;
    ComQueue  Holding[256];
	CString   Firmware[6];
	int       Position[6];
	int       Error[6];
	double    Velocity[6];
	unsigned int Status[6];
	BOOL m_StatusBits[32];
    Params   DriveParam[6];
	double   RMSstatus[6];
	short    Expecting;  //currently waiting for this type of message ack..
	short    ExpectParam;
	bool     Init;
	CString  com;  // temp var for command processing
	bool editing;
	CTime   lastmess;
	bool    comlost;

//raw commands

	void SerialRing::GetFirmware( short Drive );


//messages..

	afx_msg void OnBnClickedConnect();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedResetring();
	int m_MessCnt;
	afx_msg void OnTimer(UINT nIDEvent);
protected:
	virtual void OnOK();
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnBnClickedAutoconnect();
	void SendCommand(char * buffer, short size, short type, short pNum = 0);
	void SendBufferedCommand(void);
	afx_msg void OnBnClickedInitring();
	short m_nDrives;
	CComboBox m_DriveSelect;
	afx_msg void OnBnClickedShowdata();
	afx_msg void OnBnClickedRefreshdata();
	CStatic m_DataStatus;
	// Firmware level display
	CString m_Firm;
	afx_msg void OnCbnSelchangeDriveselect();
	afx_msg void OnBnClickedClearshut();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	

	
	double m_CurSpeed;
	double m_CurRMS;
	int m_CurError;
	int m_CurPos;
	afx_msg void OnBnClickedZero();
	CSliderCtrl m_Movement;
	int m_Count;
	afx_msg void OnNMReleasedcaptureMovement(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawMovement(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_Meaning;
	CString m_Value;
	int m_PNum;
	afx_msg void OnBnClickedPup();
	afx_msg void OnBnClickedPdn();
	afx_msg void OnBnClickedSet();
	afx_msg void OnEnSetfocusParamval();
	afx_msg void OnEnKillfocusParamval();
	
};

 

