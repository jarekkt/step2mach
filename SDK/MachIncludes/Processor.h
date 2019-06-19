#pragma once
#include "ReProcessWin.h"
#include "afxwin.h"
#include "serialport.h"
// Processor dialog



 
class cCallback
{
	public:
		virtual bool Execute(int Param) const =0;
};


template <class cInstance>
class TCallback : public cCallback // Inheriting
{
	public:
		TCallback() // constructor
		{
			// Important : zeroing the pointer so we later can check for errors
			pFunction = 0;
		}

		// (You can change the callback to take more parameters or to return something)
		typedef void (cInstance::*tFunction)(int Param);
		
		// Execute the Callback
		virtual bool Execute(int Param) const 
		{
			if (pFunction) (cInst->*pFunction)(Param);
			else printf("ERROR : the callback function has not been defined !!!!");
			// an undefined callback function will crash the program if you don't check here !
			return false;
		}

		// Set or change the Callback
		void SetCallback (cInstance  *cInstancePointer, 
						  tFunction   pFunctionPointer)
		{
			cInst     = cInstancePointer;
			pFunction = pFunctionPointer;
		}

	private:
		cInstance  *cInst;
		tFunction  pFunction;
};

class Processor : public CDialog
{
	DECLARE_DYNAMIC(Processor)

public:
	Processor(CWnd* pParent = NULL);   // standard constructor
	virtual ~Processor();

// Dialog Data
	enum { IDD = 1111111 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    DECLARE_MESSAGE_MAP()
public:
	bool    visible;
	CString InData;
	CString hist;
	void Regen();
	void OnDataArrival(int size, char *buffer);
	virtual BOOL OnInitDialog();
	void Message(int mess );
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void SerialEventManager(unsigned long object, unsigned long  event);
	CEdit m_Display;
	TCallback<Processor> CallbackOutput; 
	int m_Port;
	int m_Baud;
	BOOL m_StopBits;
	BOOL m_DataBits;
	CString RingBuffer[100];
	
	CString Terminal;
	CString m_InitString;
	CString m_CommandString;
	clock_t start;
	afx_msg void OnBnClickedSendacq();
	afx_msg void OnBnClickedSendinit();
	afx_msg void OnBnClickedReconnect();
	void InitSerial();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnEnChangeTerminal();
	afx_msg void OnEnSetfocusTerminal();
	afx_msg void OnEnUpdateTerminal();
	void Processor::CheckTime();
	CString m_Char;
    int m_UseCR;
	afx_msg void OnBnClickedUsecr();
	CEdit m_CREdit;
	afx_msg void OnBnClickedRadio5();
	CListBox m_History;
	CEdit m_EditHist;
	CTime Trigger;
	BOOL m_SLS;
	afx_msg void OnBnClickedSls5000();
};
