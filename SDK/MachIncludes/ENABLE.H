//============================================================================
//
//      Enable.h - Interface definition for Enable40.dll
//
//      Copyright 1993-2005 Cypress Software Inc.
//      All Rights Reserved.
//
//============================================================================

#ifndef __ENABLE_H__
#define __ENABLE_H__

// Error return codes

#define ENS_FUNCNOTDEFINED  0x8007007F	// Sub or function not defined
#define ENS_RUNTIMEERROR    0x8007065B  // Runtime error

// Informational return codes

#define ENS_END_INSTRUCTION 0x00040201  // Encountered End instruction
#define ENS_HIT_BREAKPOINT  0x00040202  // Encountered breakpoint

//--------------------------- Function Interface -----------------------------

#ifdef __cplusplus
extern "C" {    // Assume C declarations for C++
#endif          // __cplusplus

// The following structure is DWORD aligned (sizeof is 44)
typedef struct {
    HANDLE context;        // Context in which error or print statment occurred
    short type;            // Type 0 indicates Print statement, 1 indicates
                           // general error, 2 compile error, 3 runtime error
    HRESULT scode;         // Bit encoded HRESULT (see codes above)
    PCWSTR str;            // Extra info (eg. function name), optional
    short bufNum;          // Buffer number
    long lineNum;          // Line number
    short offset;          // Offset of token for syntax error
    short tokenLen;        // Token length for syntax error
    short runtimeErr;      // Err.Number for runtime errors (see errors.txt)
    PCWSTR errMessage;     // Display error message (error type, line #, and text)
    BOOL bOnErrorStmt;     // True if there is an OnError statement in effect for this scope
    EXCEPINFO *pExcepInfo; // Pointer to EXCEPINFO structure returned from IDispatch::Invoke
}
ENOUTPUTINFOW, *LPENOUTPUTINFOW;

// The following structure is DWORD aligned (sizeof is 44)
typedef struct {
    HANDLE context;        // Context in which error or print statment occurred
    short type;            // Type 0 indicates Print statement, 1 indicates
                           // general error, 2 compile error, 3 runtime error
    HRESULT scode;         // Bit encoded HRESULT (see codes above)
    LPCSTR str;            // Extra info (eg. function name), optional
    short bufNum;          // Buffer number
    long lineNum;          // Line number
    short offset;          // Offset of token for syntax error
    short tokenLen;        // Token length for syntax error
    short runtimeErr;      // Err.Number for runtime errors (see errors.txt)
    LPCSTR errMessage;     // Display error message (error type, line #, and text)
    BOOL bOnErrorStmt;     // True if there is an OnError statement in effect for this scope
    EXCEPINFO *pExcepInfo; // Pointer to EXCEPINFO structure returned from IDispatch::Invoke
}
ENOUTPUTINFOA, *LPENOUTPUTINFOA;

// Return codes for OutputCallback function
#define EN_DEFAULTACTION 0 // Continue run using default handling
#define EN_ENDRUN        1 // End script run immediately regardless of handler in script
#define EN_RESUMENEXT    2 // Simulate OnError Resume Next, regardless of OnError status
#define EN_DEBUGBREAK    3 // Debug break
#define EN_DISPLAYOUTPUT 4 // Enable should display output

#ifdef UNICODE
#define ENOUTPUTINFO    ENOUTPUTINFOW
#define LPENOUTPUTINFO  LPENOUTPUTINFOW
#else
#define ENOUTPUTINFO    ENOUTPUTINFOA
#define LPENOUTPUTINFO  LPENOUTPUTINFOA
#endif // !UNICODE

typedef HRESULT (CALLBACK *ENAOUTPUTCALLBACKW)( LPENOUTPUTINFOW pOutputInfo );
typedef HRESULT (CALLBACK *ENAOUTPUTCALLBACKA)( LPENOUTPUTINFOA pOutputInfo );

typedef long (CALLBACK *ENAGETPROCADDRCALLBACKW)( HANDLE hCtx, PCWSTR funcName );
typedef long (CALLBACK *ENAGETPROCADDRCALLBACKA)( HANDLE hCtx, LPCSTR funcName );

typedef HRESULT (CALLBACK *ENAUNDEFFUNCCALLBACKW)( HANDLE hCtx, PCWSTR funcName, DISPPARAMS *args, LPVARIANT retVal );
typedef HRESULT (CALLBACK *ENAUNDEFFUNCCALLBACKA)( HANDLE hCtx, LPCSTR funcName, DISPPARAMS *args, LPVARIANT retVal );
typedef HRESULT (CALLBACK *ENAUNDEFVARCALLBACKW) ( HANDLE hCtx, PCWSTR varName, LPVARIANT varContent );
typedef HRESULT (CALLBACK *ENAUNDEFVARCALLBACKA) ( HANDLE hCtx, LPCSTR varName, LPVARIANT varContent );
typedef HRESULT (CALLBACK *ENAPARSEFUNCCALLBACKW)( HANDLE hCtx, int bufNum, long lineNum, PCWSTR funcName, VARTYPE retType, VARTYPE *pArgTypes, int nArg );
typedef HRESULT (CALLBACK *ENAPARSEFUNCCALLBACKA)( HANDLE hCtx, int bufNum, long lineNum, LPCSTR funcName, VARTYPE retType, VARTYPE *pArgTypes, int nArg );
typedef HRESULT (CALLBACK *ENADIMVARCALLBACKW)   ( HANDLE hCtx, PCWSTR varName, VARTYPE vt );
typedef HRESULT (CALLBACK *ENADIMVARCALLBACKA)   ( HANDLE hCtx, LPCSTR varName, VARTYPE vt );
typedef HRESULT (CALLBACK *ENAYIELDCALLBACK)     ( HANDLE hCtx );
typedef HRESULT (CALLBACK *ENATOKENCALLBACKW)    ( HANDLE hCtx, int nToken, PCWSTR pTokenName, LPARAM lParam );
typedef HRESULT (CALLBACK *ENABREAKPOINTCALLBACK)( HANDLE hCtx, int breakreason, void *pReserved );

typedef void    (CALLBACK *ENAHIDEDBGCURCALLBACK)( HANDLE hCtx, HWND hWnd );
typedef void    (CALLBACK *ENASHOWDBGCURCALLBACK)( HANDLE hCtx, HWND hWnd, int nBuf, long nLine );

STDAPI enaSetSymbolTableSize( int nSize );	// The range for nSize is 2 through 96 and specifies #k of chars

LPCSTR APIENTRY enaVersion            ( int *major = NULL, int *minor = NULL );

STDAPI enaCreateContextW( PCWSTR pszContextName, HINSTANCE hInst, HWND hWnd, HANDLE *pEnaCtx );
STDAPI enaCreateContextA( LPCSTR pszContextName, HINSTANCE hInst, HWND hWnd, HANDLE *pEnaCtx );

#ifdef UNICODE
#define enaCreateContext  enaCreateContextW
#else
#define enaCreateContext  enaCreateContextA
#endif // !UNICODE

STDAPI enaRegisterGetProcAddrCallbackW( HANDLE hCtx, ENAGETPROCADDRCALLBACKW pfn );
STDAPI enaRegisterGetProcAddrCallbackA( HANDLE hCtx, ENAGETPROCADDRCALLBACKA pfn );
STDAPI enaRegisterOutputCallbackW     ( HANDLE hCtx, ENAOUTPUTCALLBACKW pfn );
STDAPI enaRegisterOutputCallbackA     ( HANDLE hCtx, ENAOUTPUTCALLBACKA pfn );
STDAPI enaRegisterUndefFuncCallbackW  ( HANDLE hCtx, ENAUNDEFFUNCCALLBACKW pfn );
STDAPI enaRegisterUndefFuncCallbackA  ( HANDLE hCtx, ENAUNDEFFUNCCALLBACKA pfn );
STDAPI enaRegisterUndefVarCallbackW   ( HANDLE hCtx, ENAUNDEFVARCALLBACKW pfn );
STDAPI enaRegisterUndefVarCallbackA   ( HANDLE hCtx, ENAUNDEFVARCALLBACKA pfn );
STDAPI enaRegisterParseFuncCallbackW  ( HANDLE hCtx, ENAPARSEFUNCCALLBACKW pfn );
STDAPI enaRegisterParseFuncCallbackA  ( HANDLE hCtx, ENAPARSEFUNCCALLBACKA pfn );
STDAPI enaRegisterDimVarCallbackW     ( HANDLE hCtx, ENADIMVARCALLBACKW pfn );
STDAPI enaRegisterDimVarCallbackA     ( HANDLE hCtx, ENADIMVARCALLBACKA pfn );
STDAPI enaRegisterYieldCallback       ( HANDLE hCtx, ENAYIELDCALLBACK pfn );
STDAPI enaRegisterBreakpointCallback  ( HANDLE hCtx, ENABREAKPOINTCALLBACK pfn );
STDAPI enaRegisterDebugCursorCallbacks( HANDLE hCtx, ENAHIDEDBGCURCALLBACK pfnHide, ENASHOWDBGCURCALLBACK pfnShow );

#define ENOPT_CALL_APP_WITH_CTX          1
#define ENOPT_ALLOW_IMMEDIATE_CODE       2
#define ENOPT_CACHE_DISPIDS              4
#define ENOPT_ONERROR_CALLBACK           8
#define ENOPT_RELAX_STRING_CONVERSION   16	// Not recommended
#define ENOPT_COMPCODE_SAVE_LOCAL_VARS  32
#define ENOPT_NO_IMPLICIT_END_STATEMENT 64

STDAPI enaSetUserParam                ( HANDLE hCtx, long lParam );
STDAPI enaSetDialogFontW              ( HANDLE hCtx, short nFontSize, PWSTR fontName );
STDAPI enaSetDialogFontA              ( HANDLE hCtx, short nFontSize, LPSTR fontName );

long APIENTRY enaGetUserParam(HANDLE hCtx);

#ifdef UNICODE
#define enaRegisterGetProcAddrCallback enaRegisterGetProcAddrCallbackW
#define enaRegisterOutputCallback      enaRegisterOutputCallbackW
#define enaRegisterUndefFuncCallback   enaRegisterUndefFuncCallbackW
#define enaRegisterUndefVarCallback    enaRegisterUndefVarCallbackW
#define enaRegisterParseFuncCallback   enaRegisterParseFuncCallbackW
#define enaRegisterDimVarCallback      enaRegisterDimVarCallbackW
#define enaSetDialogFont               enaSetDialogFontW
#else
#define enaRegisterGetProcAddrCallback enaRegisterGetProcAddrCallbackA
#define enaRegisterOutputCallback      enaRegisterOutputCallbackA
#define enaRegisterUndefFuncCallback   enaRegisterUndefFuncCallbackA
#define enaRegisterUndefVarCallback    enaRegisterUndefVarCallbackA
#define enaRegisterParseFuncCallback   enaRegisterParseFuncCallbackA
#define enaRegisterDimVarCallback      enaRegisterDimVarCallbackA
#define enaSetDialogFont               enaSetDialogFontA
#endif // !UNICODE

STDAPI enaSetOption(HANDLE hCtx, long lOption, long lParam);

STDAPI enaLoadCompiledCodeW       ( HANDLE hCtx, PCWSTR fileName );
STDAPI enaLoadCompiledCodeA       ( HANDLE hCtx, LPCSTR fileName );
STDAPI enaSetCompiledCode         ( HANDLE hCtx, LPVOID codeBuf );
STDAPI enaAddTypeLibReference     ( HANDLE hCtx, ITypeLib *ptlib );
STDAPI enaAddTypeLibFileRefW      ( HANDLE hCtx, PCWSTR szFile, DWORD dwFlags );
STDAPI enaAddTypeLibFileRefA      ( HANDLE hCtx, PCSTR szFile, DWORD dwFlags );
STDAPI enaAddFileW                ( HANDLE hCtx, PCWSTR fileName );
STDAPI enaAddFileA                ( HANDLE hCtx, LPCSTR fileName );
STDAPI enaAppendTextW             ( HANDLE hCtx, PCWSTR str );
STDAPI enaAppendTextA             ( HANDLE hCtx, LPCSTR str );
STDAPI enaAppendEditWindow        ( HANDLE hCtx, HWND hWnd );

STDAPI enaCompile                 ( HANDLE hCtx );
STDAPI enaSaveCompiledCodeW       ( HANDLE hCtx, PCWSTR fileName );
STDAPI enaSaveCompiledCodeA       ( HANDLE hCtx, LPCSTR fileName );
STDAPI enaGetCompiledCodeSize     ( HANDLE hCtx, long *pSize );
STDAPI enaGetCompiledCode         ( HANDLE hCtx, LPVOID codeBuf, long bufSize );

#ifdef UNICODE
#define enaLoadCompiledCode         enaLoadCompiledCodeW
#define enaAddTypeLibFileRef        enaAddTypeLibFileRefW
#define enaAddFile                  enaAddFileW
#define enaAppendText               enaAppendTextW
#define enaSaveCompiledCode         enaSaveCompiledCodeW
#else
#define enaLoadCompiledCode         enaLoadCompiledCodeA
#define enaAddTypeLibFileRef        enaAddTypeLibFileRefA
#define enaAddFile                  enaAddFileA
#define enaAppendText               enaAppendTextA
#define enaSaveCompiledCode         enaSaveCompiledCodeA
#endif // !UNICODE

STDAPI enaEnumValidTokensW        ( HANDLE hCtx, ENATOKENCALLBACKW pfn, LPARAM lParam, DWORD dwFlags );

STDAPI enaSetGlobalIntegerVarW    ( HANDLE hCtx, PCWSTR varName, short val );
STDAPI enaSetGlobalLongVarW       ( HANDLE hCtx, PCWSTR varName, long val );
STDAPI enaSetGlobalSingleVarW     ( HANDLE hCtx, PCWSTR varName, float val );
STDAPI enaSetGlobalDoubleVarW     ( HANDLE hCtx, PCWSTR varName, double val );
STDAPI enaSetGlobalStringVarW     ( HANDLE hCtx, PCWSTR varName, PCWSTR str );
STDAPI enaSetGlobalObjectVarW     ( HANDLE hCtx, PCWSTR varName, LPUNKNOWN val );
STDAPI enaSetGlobalBooleanVarW    ( HANDLE hCtx, PCWSTR varName, short val );
STDAPI enaSetGlobalVariantVarW    ( HANDLE hCtx, PCWSTR varName, VARIANT var );
STDAPI enaSetGlobalArrayElementW  ( HANDLE hCtx, PCWSTR arrName, long *indices, LPVOID pvData );
STDAPI enaSetErrorCodeW           ( HANDLE hCtx, HRESULT scode, short runtimeErr, PCWSTR str );

STDAPI enaSetGlobalIntegerRefW    ( HANDLE hCtx, PCWSTR varName, short *pVal );
STDAPI enaSetGlobalLongRefW       ( HANDLE hCtx, PCWSTR varName, long *pVal );
STDAPI enaSetGlobalSingleRefW     ( HANDLE hCtx, PCWSTR varName, float *pVal );
STDAPI enaSetGlobalDoubleRefW     ( HANDLE hCtx, PCWSTR varName, double *pVal );
STDAPI enaSetGlobalStringRefW     ( HANDLE hCtx, PCWSTR varName, BSTR *pbstr  );
STDAPI enaSetGlobalFixedStringRefW( HANDLE hCtx, PCWSTR varName, PWSTR pVal  );
STDAPI enaSetGlobalObjectRefW     ( HANDLE hCtx, PCWSTR varName, LPDISPATCH *ppDisp );
STDAPI enaSetGlobalBooleanRefW    ( HANDLE hCtx, PCWSTR varName, short *pVal );
STDAPI enaSetGlobalVariantRefW    ( HANDLE hCtx, PCWSTR varName, LPVARIANT pVar );
STDAPI enaSetGlobalArrayRefW      ( HANDLE hCtx, PCWSTR varName, LPSAFEARRAY *ppsa  );

STDAPI enaSetGlobalIntegerVarA    ( HANDLE hCtx, LPCSTR varName, short val );
STDAPI enaSetGlobalLongVarA       ( HANDLE hCtx, LPCSTR varName, long val );
STDAPI enaSetGlobalSingleVarA     ( HANDLE hCtx, LPCSTR varName, float val );
STDAPI enaSetGlobalDoubleVarA     ( HANDLE hCtx, LPCSTR varName, double val );
STDAPI enaSetGlobalStringVarA     ( HANDLE hCtx, LPCSTR varName, LPCSTR str );
STDAPI enaSetGlobalObjectVarA     ( HANDLE hCtx, LPCSTR varName, LPUNKNOWN val );
STDAPI enaSetGlobalBooleanVarA    ( HANDLE hCtx, LPCSTR varName, short val );
STDAPI enaSetGlobalVariantVarA    ( HANDLE hCtx, LPCSTR varName, VARIANT var );
STDAPI enaSetGlobalArrayElementA  ( HANDLE hCtx, LPCSTR arrName, long *indices, LPVOID pvData );

STDAPI enaSetErrorCodeA           ( HANDLE hCtx, HRESULT scode, short runtimeErr, LPCSTR str );

STDAPI enaSetGlobalIntegerRefA    ( HANDLE hCtx, LPCSTR varName, short *pVal );
STDAPI enaSetGlobalLongRefA       ( HANDLE hCtx, LPCSTR varName, long *pVal );
STDAPI enaSetGlobalSingleRefA     ( HANDLE hCtx, LPCSTR varName, float *pVal );
STDAPI enaSetGlobalDoubleRefA     ( HANDLE hCtx, LPCSTR varName, double *pVal );
STDAPI enaSetGlobalStringRefA     ( HANDLE hCtx, LPCSTR varName, BSTR *pbstr  );
STDAPI enaSetGlobalFixedStringRefA( HANDLE hCtx, LPCSTR varName, LPSTR pVal  );
STDAPI enaSetGlobalObjectRefA     ( HANDLE hCtx, LPCSTR varName, LPDISPATCH *ppDisp );
STDAPI enaSetGlobalBooleanRefA    ( HANDLE hCtx, LPCSTR varName, short *pVal );
STDAPI enaSetGlobalVariantRefA    ( HANDLE hCtx, LPCSTR varName, LPVARIANT pVar );
STDAPI enaSetGlobalArrayRefA      ( HANDLE hCtx, LPCSTR varName, LPSAFEARRAY *ppsa  );

STDAPI enaSetDefaultDispatch      ( HANDLE hCtx, UINT uModule, IDispatch *pdisp );

#ifdef UNICODE
#define enaSetGlobalIntegerVar      enaSetGlobalIntegerVarW
#define enaSetGlobalLongVar         enaSetGlobalLongVarW
#define enaSetGlobalSingleVar       enaSetGlobalSingleVarW
#define enaSetGlobalDoubleVar       enaSetGlobalDoubleVarW
#define enaSetGlobalStringVar       enaSetGlobalStringVarW
#define enaSetGlobalObjectVar       enaSetGlobalObjectVarW
#define enaSetGlobalBooleanVar      enaSetGlobalBooleanVarW
#define enaSetGlobalVariantVar      enaSetGlobalVariantVarW
#define enaSetGlobalArrayElement    enaSetGlobalArrayElementW
#define enaSetErrorCode             enaSetErrorCodeW

#define enaSetGlobalIntegerRef      enaSetGlobalIntegerRefW
#define enaSetGlobalLongRef         enaSetGlobalLongRefW
#define enaSetGlobalSingleRef       enaSetGlobalSingleRefW
#define enaSetGlobalDoubleRef       enaSetGlobalDoubleRefW
#define enaSetGlobalStringRef       enaSetGlobalStringRefW
#define enaSetGlobalFixedStringRef  enaSetGlobalFixedStringRefW
#define enaSetGlobalObjectRef       enaSetGlobalObjectRefW
#define enaSetGlobalBooleanRef      enaSetGlobalBooleanRefW
#define enaSetGlobalVariantRef      enaSetGlobalVariantRefW
#define enaSetGlobalArrayRef        enaSetGlobalArrayRefW
#else
#define enaSetGlobalIntegerVar      enaSetGlobalIntegerVarA
#define enaSetGlobalLongVar         enaSetGlobalLongVarA
#define enaSetGlobalSingleVar       enaSetGlobalSingleVarA
#define enaSetGlobalDoubleVar       enaSetGlobalDoubleVarA
#define enaSetGlobalStringVar       enaSetGlobalStringVarA
#define enaSetGlobalObjectVar       enaSetGlobalObjectVarA
#define enaSetGlobalBooleanVar      enaSetGlobalBooleanVarA
#define enaSetGlobalVariantVar      enaSetGlobalVariantVarA
#define enaSetGlobalArrayElement    enaSetGlobalArrayElementA
#define enaSetErrorCode             enaSetErrorCodeA

#define enaSetGlobalIntegerRef      enaSetGlobalIntegerRefA
#define enaSetGlobalLongRef         enaSetGlobalLongRefA
#define enaSetGlobalSingleRef       enaSetGlobalSingleRefA
#define enaSetGlobalDoubleRef       enaSetGlobalDoubleRefA
#define enaSetGlobalStringRef       enaSetGlobalStringRefA
#define enaSetGlobalFixedStringRef  enaSetGlobalFixedStringRefA
#define enaSetGlobalObjectRef       enaSetGlobalObjectRefA
#define enaSetGlobalBooleanRef      enaSetGlobalBooleanRefA
#define enaSetGlobalVariantRef      enaSetGlobalVariantRefA
#define enaSetGlobalArrayRef        enaSetGlobalArrayRefA
#endif // !UNICODE

STDAPI enaGetScriptDispatch       ( HANDLE hCtx, IDispatch **ppDisp );
STDAPI enaExecute                 ( HANDLE hCtx );
STDAPI enaCallFunctionW           ( HANDLE hCtx, PCWSTR funcName, DISPPARAMS *args = NULL, LPVARIANT retval = NULL );
STDAPI enaCallFunctionA           ( HANDLE hCtx, LPCSTR funcName, DISPPARAMS *args = NULL, LPVARIANT retval = NULL );
STDAPI enaDebugFunctionW          ( HANDLE hCtx, PCWSTR funcName, DISPPARAMS *args = NULL, LPVARIANT retval = NULL, int *pBufNum = NULL, long *pLineNum = NULL );
STDAPI enaDebugFunctionA          ( HANDLE hCtx, LPCSTR funcName, DISPPARAMS *args = NULL, LPVARIANT retval = NULL, int *pBufNum = NULL, long *pLineNum = NULL );

STDAPI enaSetBreakpoint           ( HANDLE hCtx, int bufNum, long nLine );
STDAPI enaClearBreakpoint         ( HANDLE hCtx, int bufNum, long nLine );

STDAPI enaDebugStep               ( HANDLE hCtx, int *pBufNum = NULL, long *pLineNum = NULL );
STDAPI enaDebugStepInto           ( HANDLE hCtx, int *pBufNum = NULL, long *pLineNum = NULL );
STDAPI enaDebugGo                 ( HANDLE hCtx, int *pBufNum = NULL, long *pLineNum = NULL );
STDAPI enaDebugReset              ( HANDLE hCtx );

STDAPI enaClearDispIDCache        ( HANDLE hCtx );

// The following structure is DWORD aligned (sizeof is 16)
typedef struct RuntimeInfo {
    UINT  cbSize;                           // Set equal to sizeof( ENRUNTIMEINFO )
	int	  nInst;
	int   nBuf;
	int   nLine;
}
ENRUNTIMEINFO, *PENRUNTIMEINFO;

STDAPI enaGetRuntimeInfo          ( HANDLE hCtx, ENRUNTIMEINFO *pRuntimeInfo, DWORD dwFlags );

STDAPI enaGetVarValueStringW      ( HANDLE hCtx, PCWSTR varName, PWSTR buf, int max );
STDAPI enaGetVarValueStringA      ( HANDLE hCtx, LPCSTR varName, LPSTR buf, int max );

#ifdef UNICODE
#define enaCallFunction             enaCallFunctionW
#define enaDebugFunction            enaDebugFunctionW
#define enaGetVarValueString        enaGetVarValueStringW
#else
#define enaCallFunction             enaCallFunctionA
#define enaDebugFunction            enaDebugFunctionA
#define enaGetVarValueString        enaGetVarValueStringA
#endif // !UNICODE

STDAPI enaGetGlobalIntegerVarW    ( HANDLE hCtx, PCWSTR varName, short *valPtr );
STDAPI enaGetGlobalLongVarW       ( HANDLE hCtx, PCWSTR varName, long *valPtr );
STDAPI enaGetGlobalSingleVarW     ( HANDLE hCtx, PCWSTR varName, float *valPtr );
STDAPI enaGetGlobalDoubleVarW     ( HANDLE hCtx, PCWSTR varName, double *valPtr );
STDAPI enaGetGlobalStringVarW     ( HANDLE hCtx, PCWSTR varName, PWSTR buf, int max );
STDAPI enaGetGlobalBooleanVarW    ( HANDLE hCtx, PCWSTR varName, short *valPtr );
STDAPI enaGetGlobalVariantVarW    ( HANDLE hCtx, PCWSTR varName, LPVARIANT pVar );
STDAPI enaGetGlobalArrayElementW  ( HANDLE hCtx, PCWSTR arrName, long *indices, LPVOID pvData );

STDAPI enaGetGlobalIntegerVarA    ( HANDLE hCtx, LPCSTR varName, short *valPtr );
STDAPI enaGetGlobalLongVarA       ( HANDLE hCtx, LPCSTR varName, long *valPtr );
STDAPI enaGetGlobalSingleVarA     ( HANDLE hCtx, LPCSTR varName, float *valPtr );
STDAPI enaGetGlobalDoubleVarA     ( HANDLE hCtx, LPCSTR varName, double *valPtr );
STDAPI enaGetGlobalStringVarA     ( HANDLE hCtx, LPCSTR varName, LPSTR buf, int max );
STDAPI enaGetGlobalBooleanVarA    ( HANDLE hCtx, LPCSTR varName, short *valPtr );
STDAPI enaGetGlobalVariantVarA    ( HANDLE hCtx, LPCSTR varName, LPVARIANT pVar );
STDAPI enaGetGlobalArrayElementA  ( HANDLE hCtx, LPCSTR arrName, long *indices, LPVOID pvData );

#ifdef UNICODE
#define enaGetGlobalIntegerVar      enaGetGlobalIntegerVarW
#define enaGetGlobalLongVar         enaGetGlobalLongVarW
#define enaGetGlobalSingleVar       enaGetGlobalSingleVarW
#define enaGetGlobalDoubleVar       enaGetGlobalDoubleVarW
#define enaGetGlobalStringVar       enaGetGlobalStringVarW
#define enaGetGlobalBooleanVar      enaGetGlobalBooleanVarW
#define enaGetGlobalVariantVar      enaGetGlobalVariantVarW
#define enaGetGlobalArrayElement    enaGetGlobalArrayElementW
#else
#define enaGetGlobalIntegerVar      enaGetGlobalIntegerVarA
#define enaGetGlobalLongVar         enaGetGlobalLongVarA
#define enaGetGlobalSingleVar       enaGetGlobalSingleVarA
#define enaGetGlobalDoubleVar       enaGetGlobalDoubleVarA
#define enaGetGlobalStringVar       enaGetGlobalStringVarA
#define enaGetGlobalBooleanVar      enaGetGlobalBooleanVarA
#define enaGetGlobalVariantVar      enaGetGlobalVariantVarA
#define enaGetGlobalArrayElement    enaGetGlobalArrayElementA
#endif // !UNICODE

STDAPI enaGetVarRef               ( HANDLE hCtx, PCWSTR varName, VARIANT *pVar, DWORD dwFlags = 0 );

STDAPI enaFreeContext             ( HANDLE hCtx );

//------------------------ Built in editor/debugger -----------------------------

BOOL APIENTRY enaIsEditWindow     ( HWND hWnd );

typedef HRESULT (CALLBACK *ENACALLBACKA)( HANDLE hCtx );
typedef HRESULT (CALLBACK *ENAABOUTDLGCALLBACKA)( HWND hwnd, DLGPROC pfnDlgProc );

// The following structure is DWORD aligned (sizeof is 52)
typedef struct CustomEdit {
    UINT  cbSize;                           // Set equal to sizeof( ENCUSTOMEDIT )
    PCSTR pszContextName;                   // Parameter to enaCreateContext
    long lUserParam;                        // Parameter to enaSetUserParam
    DWORD dwOptions;                        // Parameter to enaSetOption( ctx, dwOptions, TRUE )
    ENAGETPROCADDRCALLBACKA pfnGetProcAddr; // Parameter to enaRegisterGetProcAddrCallback
    ENAOUTPUTCALLBACKA pfnOutput;           // Parameter to enaRegisterOutputCallback
    ENAUNDEFFUNCCALLBACKA pfnUndefFunc;     // Parameter to enaUndefFuncCallback
    IDispatch *pDefaultDispatch;            // Parameter to enaSetDefaultDispatch
    PCSTR pszDeclarations;                  // Script fragment containing constant and functions declarations
    ENACALLBACKA pfnSetGlobals;             // This function gets called after enaCompile, but before any
                                            // script code is executed to allow for calls to enaSetGlobal*
    ENACALLBACKA pfnGetGlobals;             // This function gets called before enaFreeContext to allow
                                            // for retrieval of global variables (enaGetGlobal*)
    ENAABOUTDLGCALLBACKA pfnAbout;          // This function gets called for About menu processing
    char szFileName[260]; /*_MAX_PATH*/     // Current open file name in EnableEdit control, Specify initial file
    PCSTR pszReferences;                    // Type library references
}
ENCUSTOMEDIT, *PENCUSTOMEDIT;

#define ENEDIT_DISPLAY_INIT_ERROR   0x1     // Display a message on a script editor initialization error
#define ENEDIT_CALLING_FROM_VB      0x2     // The caller of this function is a VB application or control

STDAPI enaScriptEditor( ENCUSTOMEDIT *pCustomEdit, PCSTR szCmdLine, int iCmdShow, DWORD flags );
STDAPI enaStartScript ( ENCUSTOMEDIT *pCustomEdit, HWND hwnd, PCSTR scriptText = NULL );

STDAPI enaShowHTMLDialogW( PCWSTR pHTMFileName, PCWSTR pchOptions = NULL );

static PCSTR pcszEnableEditClassName = "EnableEdit42";
STDAPI enaInitEnableEdit( DWORD flags );

// Script Edit Messages
#define SEM_SHOWOPTIONS			0x00DD		// Display the options dialog box
#define SEM_ADDTYPELIBREF		0x00EC		// Add a type library reference

#define SEM_SETCOLORTABLE		0x00FC		// Set the color table for syntax coloring
#define SEM_SETEDITOPTIONS		0x00FB		// Set editing options

#define SEM_CRLF				0x00ED

#define SEM_SETCONTEXT			0x00FA		// Context used to update debug cursor, etc.

#define SEM_BREAKPOINT			0x00EF		// Toggle, set, or clear a breakpoint
#define SEM_CLEARBREAKPOINTS	0x00EE		// Remove all breakpoints
#define SEM_ENUMBREAKPOINTS		0x00F9		// Enumerate all breakpoints

#define SEM_GETTEXTSELECTION	0x00F7		// Return an ITextSelection * to the current selection

#define SEM_OPEN				0x00FE		// Open a file or stream in the edit control
#define SEM_SAVE				0x00FD		// Save the contents of the edit control

// Options for SEM_BREAKPOINT
#define BRKPNT_TOGGLE			0			// Toggle the breakpoint
#define BRKPNT_SET				1			// Set a breakpoint

// The following structure is DWORD aligned (sizeof is 16)
typedef struct sBreakpoint {
    UINT  cbSize;							// Set equal to sizeof( sBreakpoint )
    DWORD dwFlags;							// Reserved (always zero)
	int   nBuf;								// Buffer number of the breakpoint
	int   nLine;							// Line number of the breakpoint
}
ENBREAKPOINT;

typedef HRESULT (CALLBACK* LPENUMBREAKPOINTSCALLBACK)(ENBREAKPOINT *pBreakPoint, LPARAM lParam);

//-------------------------------------------------------------------------------

#define SEM_BASE				0x4200		// Private Window Messages: WM_USER (0x0400) - 0x7fff

#define SEM_Bookmark			(SEM_BASE + 25)		// Bookmark ops (See eecIndicatorOps below)
#define SEM_ClearBookmarks		(SEM_BASE + 26)		// Remove all bookmarks
#define SEM_EnumBookmarks		(SEM_BASE + 27)		// Enumerate all breakpoints

// Constants for SEM_Bookmark
typedef enum {
    iopToggle				  = 0,			// Toggle the indicator (Set or Clear)
    iopSet					  = 1,			// Set an indicator
    iopClear				  = 2,			// Clear/remove a indicator
    iopToggleEnabled		  = 3,			// Toggle between Enabled and Disabled state
    iopEnable				  = 4,			// Enable indicator
    iopDisable				  = 5,			// Disable indicator
    iopFindNext				  = 6,			// Find next indicator
    iopFindPrev				  = 7,			// Find previous indicator
    iopGotoNext				  = 8,			// Go to next indicator
    iopGotoPrev				  = 9,			// Go to previous
    iopGetState				  = 10			// Return state (1-Enabled, 0-Disabled, < 0-Error)
} eecIndicatorOps;

//-------------------------------------------------------------------------------

//== Deprecated
#define SEM_LOADFILE			0x00EB		// Load the contents of a file into the edit control
#define SEM_SAVEFILE			0x00EA		// Save the contents of the edit control to a file

#define SEM_CLEARBRKPNTS		0x00EE		// Clear all breakpoints
//== End Deprecated

#ifdef _USE_OBSOLETE						// Defined for backward compatibility
typedef HRESULT			ENSTATUS;
typedef HANDLE			ENACTX;

#define ENS_SUCCESS		S_OK
#define ENS_FAIL		E_FAIL

#define ENEXPORTED		APIENTRY
#define ENAPI			HRESULT APIENTRY
#endif

#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // !__ENABLE_H__
