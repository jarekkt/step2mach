/*
Module : SERIALPORT.H
Purpose: Declaration for an MFC wrapper class for serial ports
Created: PJN / 31-05-1999
History: None

Copyright (c) 1999 by PJ Naughter.  
All rights reserved.

Open license, no limits on Usage

*/



///////////////////// Macros / Structs etc //////////////////////////

#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__





/////////////////////////// Classes ///////////////////////////////////////////


////// Serial port exception class ////////////////////////////////////////////

void AfxThrowSerialException(DWORD dwError = 0);

class CSerialException : public CException
{
public:
//Constructors / Destructors
	CSerialException(DWORD dwError);
	~CSerialException();

//Methods
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual BOOL GetErrorMessage(LPTSTR lpstrError, UINT nMaxError,	PUINT pnHelpContext = NULL);
	CString GetErrorMessage();

//Data members
	DWORD m_dwError;

protected:
	DECLARE_DYNAMIC(CSerialException)
};



//// The actual serial port class /////////////////////////////////////////////

class CSerialPort : public CObject
{
public:
//Enums
  enum FlowControl
  {
    NoFlowControl,
    CtsRtsFlowControl,
    CtsDtrFlowControl,
    DsrRtsFlowControl,
    DsrDtrFlowControl,
    XonXoffFlowControl
  };

  enum Parity
  {    
    EvenParity,
    MarkParity,
    NoParity,
    OddParity,
    SpaceParity
  };

  enum StopBits
  {
    OneStopBit,
    OnePointFiveStopBits,
    TwoStopBits
  };

//Constructors / Destructors
  CSerialPort();
  ~CSerialPort();

//General Methods
  void Open(int nPort, DWORD dwBaud = 9600, Parity parity = NoParity, BYTE DataBits = 8, 
            StopBits stopbits = OneStopBit, FlowControl fc = NoFlowControl, BOOL bOverlapped = FALSE);
  void Close();
  void Attach(HANDLE hComm);
  HANDLE Detach();
  operator HANDLE() const { return m_hComm; };
  BOOL IsOpen() const { return m_hComm != INVALID_HANDLE_VALUE; };
#ifdef _DEBUG
  void CSerialPort::Dump(CDumpContext& dc) const;
#endif

//Reading / Writing Methods
  DWORD Read(void* lpBuf, DWORD dwCount);
  BOOL Read(void* lpBuf, DWORD dwCount, OVERLAPPED& overlapped);
  void ReadEx(void* lpBuf, DWORD dwCount);
  DWORD Write(const void* lpBuf, DWORD dwCount);
  BOOL Write(const void* lpBuf, DWORD dwCount, OVERLAPPED& overlapped);
  void WriteEx(const void* lpBuf, DWORD dwCount);
  void TransmitChar(char cChar);
  void GetOverlappedResult(OVERLAPPED& overlapped, DWORD& dwBytesTransferred, BOOL bWait);
  void CancelIo();

//Configuration Methods
  void GetConfig(COMMCONFIG& config);
  static void GetDefaultConfig(int nPort, COMMCONFIG& config);
  void SetConfig(COMMCONFIG& Config);
  static void SetDefaultConfig(int nPort, COMMCONFIG& config);

//Misc RS232 Methods
  void ClearBreak();
  void SetBreak();
  void ClearError(DWORD& dwErrors);
  void GetStatus(COMSTAT& stat);
  void GetState(DCB& dcb);
  void SetState(DCB& dcb);
  void Escape(DWORD dwFunc);
  void ClearDTR();
  void ClearRTS();
  void SetDTR();
  void SetRTS();
  void SetXOFF();
  void SetXON();
  void GetProperties(COMMPROP& properties);
  void GetModemStatus(DWORD& dwModemStatus); 

//Timeouts
  void SetTimeouts(COMMTIMEOUTS& timeouts);
  void GetTimeouts(COMMTIMEOUTS& timeouts);
  void Set0Timeout();
  void Set0WriteTimeout();
  void Set0ReadTimeout();

//Event Methods
  void SetMask(DWORD dwMask);
  void GetMask(DWORD& dwMask);
  void WaitEvent(DWORD& dwMask);
  void WaitEvent(DWORD& dwMask, OVERLAPPED& overlapped);
  
//Queue Methods
  void Flush();
  void Purge(DWORD dwFlags);
  void TerminateOutstandingWrites();
  void TerminateOutstandingReads();
  void ClearWriteBuffer();
  void ClearReadBuffer();
  void Setup(DWORD dwInQueue, DWORD dwOutQueue);

//Overridables
  virtual void OnCompletion(DWORD dwErrorCode, DWORD dwCount, LPOVERLAPPED lpOverlapped);

protected:
  HANDLE m_hComm;       //Handle to the comms port
  BOOL   m_bOverlapped; //Is the port open in overlapped IO

  static void WINAPI _OnCompletion(DWORD dwErrorCode, DWORD dwCount, LPOVERLAPPED lpOverlapped); 

	DECLARE_DYNAMIC(CSerialPort)
};


#endif //__SERIALPORT_H__