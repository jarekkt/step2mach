#if !defined(AFX_CAPTUREVIDEO_H__057736B5_B61B_4850_8D82_E181E0B25B61__INCLUDED_)
#define AFX_CAPTUREVIDEO_H__057736B5_B61B_4850_8D82_E181E0B25B61__INCLUDED_

//--------------------------------------------------------------------------//
// Copyright DILLIP KUMAR KARA 2004
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
// Comments and bug Reports: codeguru_bank@yahoo.com
//--------------------------------------------------------------------------//

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CaptureVideo.h : header file
#include <atlbase.h>
#include <windows.h>
#include <dshow.h>
//
enum PLAYSTATE {STOPPED, PAUSED, RUNNING, INIT};

#define WM_GRAPHNOTIFY  WM_USER+1

#ifndef SAFE_RELEASE

#define SAFE_RELEASE( x )  \
    if ( NULL != x )       \
    {                      \
        x->Release( );     \
        x = NULL;          \
    }

#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptureVideo window

class CCaptureVideo : public CWnd
{
// Construction
public:
	CCaptureVideo();

// Attributes
public:
	void StopCapture();
	void StartTVTuner();
	void StartWebcam();
	void StartCompositeVideo();
	void StartSVideo();
	void RemoveGraphFromRot(DWORD pdwRegister);
	void UnIntializeVideo();
	HRESULT InitializeVideo(HWND hWnd);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptureVideo)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ResizeVideoWindow();
	virtual ~CCaptureVideo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCaptureVideo)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg HRESULT OnGraphNotify(WPARAM wp , LPARAM lp);
	DECLARE_MESSAGE_MAP()
protected:
	void ResizeVideoWindowMoniker();
	void CloseInterfacesMoniker();
	//----------------For Webcam-----------------//
	void RemoveGraphFromRotMoniker(DWORD pdwRegister);
	HRESULT AddGraphToRotMoniker(IUnknown *pUnkGraph, DWORD *pdwRegister);
	HRESULT SetupVideoWindowMoniker();
	HRESULT HandleGraphEventMoniker();
	HRESULT FindCaptureDeviceMoniker(IMoniker** ppMoniker);
	HRESULT AddCaptureMonikerToGraph(IMoniker* pMoniker);
	HRESULT CaptureVideoByMoniker();
	HRESULT GetInterfacesMoniker();

	//------------------Video--------------------//
	void DisplayMesg(TCHAR* szFormat, ...);
	LRESULT ClearInterfaces(WPARAM wp, LPARAM lp);
	void CloseInterfaces();
	HRESULT AddGraphToRot(IUnknown* pUnkGraph, DWORD* pdwRegister);
	
	HRESULT CaptureVideo();
	HRESULT HandleGraphEvent();
	HRESULT ChangePreviewState(int nShow);
	HRESULT SetupVideoWindow();
	HRESULT FindCaptureDevice(IBaseFilter** ppSrcFilter);
	HRESULT GetInterfaces();
		
private:
	UINT chSVideo, chCompVideo , chWebCam , chFullScreen , chAlwaysOnTop ;

	int nVSourceCount;
	int nAnalogCount;

	CBrush m_emptyBrush;
	DWORD m_dwGraphRegister;
	BOOL bDevCheck;
	HWND m_hApp;
	//------------------Video--------------------//
	IVideoWindow* m_pVW ; 
	IMediaControl* m_pMC ;
	IMediaEventEx* m_pME ;
	IGraphBuilder* m_pGraph ;
	ICaptureGraphBuilder2* m_pCapture ;
	IBaseFilter* pSrcF; 
	PLAYSTATE m_psCurrent; 
	
	//----------------For Webcam-----------------//
	IVideoWindow* m_pVWMoniker ;
	IMediaControl* m_pMCMoniker ;
	IMediaEventEx* m_pMEMoniker ;
	ICaptureGraphBuilder2* m_pCaptureMoniker ; 
	IFilterGraph2* m_pFilterGraph ;// IFilterGraph2 provides AddSourceFileForMoniker()

	BOOL bVideo , bWebCam;
	int vType;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTUREVIDEO_H__057736B5_B61B_4850_8D82_E181E0B25B61__INCLUDED_)
