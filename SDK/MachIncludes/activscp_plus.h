// activscp_plus.h

///////////////////////////////////////////////////////////////////////////////////////////
// This header file is only included in the absence of Microsoft's official header file
// It should be replaces as soon as an official Microsofrt header becomes available
///////////////////////////////////////////////////////////////////////////////////////////

#ifndef h_activscp_plus
#define h_activscp_plus

// {51973C11-CB0C-11d0-B5C9-00A0244A0E7A}
DEFINE_GUID(IID_IActiveScriptSiteDebug, 0x51973C11, 0xcb0c, 0x11d0, 0xb5, 0xc9, 0x0, 0xa0, 0x24, 0x4a, 0x0e, 0x7a);
 
// class predeclares
class IDebugDocumentContext;
class IDebugApplication;
class IDebugApplicationNode;
class IDebugDocumentHost;
class IActiveScriptErrorDebug;
class IDebugDocumentHelper;
class IDebugStackFrameSniffer;
class IDebugApplicationThread;
class IDebugSyncOperation;
class IDebugAsyncOperation;
class IDebugThreadCall;
class IRemoteDebugApplicationThread;
class IEnumRemoteDebugApplicationThreads;
class IApplicationDebugger;
class IEnumDebugExpressionContexts;
class IProvideExpressionContexts;

typedef WORD SOURCE_TEXT_ATTR; 
// The character is a part of a language keyword. Example: while 
const SOURCE_TEXT_ATTR SOURCETEXT_ATTR_KEYWORD= 0x0001; 
// The character is a part of a comment block. 
const SOURCE_TEXT_ATTR SOURCETEXT_ATTR_COMMENT= 0x0002; 
// The character is not part of compiled language source text. Example: 
// the HTML surrounding script blocks. 
const SOURCE_TEXT_ATTR SOURCETEXT_ATTR_NONSOURCE= 0x0004; 
// The character is a part of a language operator. Example: * 
const SOURCE_TEXT_ATTR SOURCETEXT_ATTR_OPERATOR= 0x0008; 
// The character is a part of a language numeric constant. Example: 1234 
const SOURCE_TEXT_ATTR SOURCETEXT_ATTR_NUMBER= 0x0010; 
// The character is a part of a language string constant. Example: "Hello World" 
const SOURCE_TEXT_ATTR SOURCETEXT_ATTR_STRING= 0x0020; 
// The character indicates the start of a function block 
const SOURCE_TEXT_ATTR SOURCETEXT_ATTR_FUNCTION_START = 0x0040;

typedef DWORD TEXT_DOC_ATTR; 
// Indicates that the document is read-only. 
const TEXT_DOC_ATTR TEXT_DOC_ATTR_READONLY = 0x00000001;

typedef DWORD APPBREAKFLAGS; 

// DEBUGGER_BLOCK 
// languages should break immediately with BREAKREASON_DEBUGGER_BLOCK 
const APPBREAKFLAGSAPPBREAKFLAG_DEBUGGER_BLOCK= 0x00000001; 
// DEBUGGER_HALT 
// languages should break immediately with BREAKREASON_DEBUGGER_HALT 
const APPBREAKFLAGSAPPBREAKFLAG_DEBUGGER_HALT= 0x00000002; 
// STEP 
// languages should break immediately in the stepping thread with BREAKREASON_STEP 
const APPBREAKFLAGSAPPBREAKFLAG_STEP= 0x00010000; 
// NESTED - the application is in nested execution on a breakpoint 
const APPBREAKFLAGSAPPBREAKFLAG_NESTED= 0x00020000; 
// STEP TYPES - defines whether we are stepping at source, bytecode, or machine level. 
const APPBREAKFLAGSAPPBREAKFLAG_STEPTYPE_SOURCE= 0x00000000; 
const APPBREAKFLAGSAPPBREAKFLAG_STEPTYPE_BYTECODE= 0x00100000; 
const APPBREAKFLAGSAPPBREAKFLAG_STEPTYPE_MACHINE= 0x00200000; 
const APPBREAKFLAGSAPPBREAKFLAG_STEPTYPE_MASK= 0x00F00000; 
// BREAKPOINT IN_PROGRESS 
const APPBREAKFLAGSAPPBREAKFLAG_IN_BREAKPOINT= 0x80000000;

typedef enum tagBREAKREASON{ 
   BREAKREASON_STEP,// Caused by the stepping mode 
   BREAKREASON_BREAKPOINT,// Caused by an explicit breakpoint 
   BREAKREASON_DEBUGGER_BLOCK,// Caused by another thread breaking 
   BREAKREASON_HOST_INITIATED,// Caused by host requested break 
   BREAKREASON_LANGUAGE_INITIATED,// Caused by a scripted break 
   BREAKREASON_DEBUGGER_HALT,// Caused by debugger IDE requested break 
   BREAKREASON_ERROR// Caused by an execution error 
} BREAKREASON;

typedef enum tagBREAKRESUME_ACTION{ 
   BREAKRESUMEACTION_ABORT,// Abort the application 
   BREAKRESUMEACTION_CONTINUE,// Continue running 
   BREAKRESUMEACTION_STEP_INTO,// Step into a procedure 
   BREAKRESUMEACTION_STEP_OVER,// Step over a procedure 
   BREAKRESUMEACTION_STEP_OUT// Step out of the current procedure 
} BREAKRESUMEACTION;

typedef enum tagERRORRESUMEACTION { 
   ERRORRESUMEACTION_ReexecuteErrorStatement,// try executing the erroneous line again 
   ERRORRESUMEACTION_AbortCallAndReturnErrorToCaller,// let the language engine handle the error 
   ERRORRESUMEACTION_SkipErrorStatement,// resume execution from beyond the error 
} ERRORRESUMEACTION;

class IActiveScriptSiteDebug : public IUnknown 
{ 
public:
   // Used by the language engine to delegate IDebugCodeContext::GetSourceContext. 
   virtual HRESULT STDMETHODCALLTYPE GetDocumentContextFromPosition(
      DWORD dwSourceContext,// As provided to ParseScriptText 
                            // or AddScriptlet 
      ULONG uCharacterOffset,// character offset relative 
                             // to start of script block or scriptlet 
      ULONG uNumChars,// Number of characters in context 
                      // Returns the document context corresponding to this character-position range. 
      IDebugDocumentContext **ppsc) = 0; 

   // Returns the debug application object associated with this script site. Provides 
   // a means for a smart host to define what application object each script belongs to. 
   // Script engines should attempt to call this method to get their containing application 
   // and resort to IProcessDebugManager::GetDefaultApplication if this fails. 
   virtual HRESULT STDMETHODCALLTYPE GetApplication( 
      IDebugApplication **ppda) = 0; 

   // Gets the application node under which script documents should be added 
   // can return NULL if script documents should be top-level. 
   virtual HRESULT STDMETHODCALLTYPE GetRootApplicationNode( 
      IDebugApplicationNode **ppdanRoot) = 0; 

   // Allows a smart host to control the handling of runtime errors 
   virtual HRESULT STDMETHODCALLTYPE OnScriptErrorDebug( 
      // the runtime error that occurred 
      IActiveScriptErrorDebug *pErrorDebug, 
      // whether to pass the error to the debugger to do JIT debugging 
      BOOL*pfEnterDebugger, 
      // whether to call IActiveScriptSite::OnScriptError() when the user 
      // decides to continue without debugging 
      BOOL *pfCallOnScriptErrorWhenContinuing) = 0; 
};


// IProcessDebugManager Interface
// (51973C2f-CB0C-11d0-B5C9-00A0244A0E7A), 
DEFINE_GUID(IID_IProcessDebugManager, 0x51973C2f, 0xcb0c, 0x11d0, 0xb5, 0xc9, 0x0, 0xa0, 0x24, 0x4a, 0x0e, 0x7a);

class IProcessDebugManager : public IUnknown 
{ 
public:
   // Creates a new debug application object. The new object is not added to the 
   // running application list and has no name. 
   virtual HRESULT STDMETHODCALLTYPE CreateApplication( 
      IDebugApplication **ppda) = 0; 

   // Returns a default application object for the current process, creating one and adding 
   // it to the running application list if necessary. Language engines should use this 
   // application if they are running on a host that does not provide an application. 
   virtual HRESULT STDMETHODCALLTYPE GetDefaultApplication( 
      IDebugApplication **ppda) = 0; 

   // Adds an application to the running application list in the machine debug manager. 
   virtual HRESULT STDMETHODCALLTYPE AddApplication( 
      IDebugApplication *pda, 
      // Returns a cookie used to remove the application from the machine debug manager. 
      DWORD *pdwAppCookie) = 0; 

   // Removes an application from the running application list. 
   virtual HRESULT STDMETHODCALLTYPE RemoveApplication( 
      // The cookie provided by AddApplication. 
      DWORD dwAppCookie) = 0; 
   
   virtual HRESULT STDMETHODCALLTYPE CreateDebugDocumentHelper( 
      IUnknown *punkOuter, 
      IDebugDocumentHelper** pddh) = 0; 
}; 

// IDebugDocumentHelper Interface
// (51973C26-CB0C-11d0-B5C9-00A0244A0E7A), 
DEFINE_GUID(IID_IDebugDocumentHelper, 0x51973c26, 0xcb0c, 0x11d0, 0xb5, 0xc9, 0x0, 0xa0, 0x24, 0x4a, 0x0e, 0x7a);
class IDebugDocumentHelper : public IUnknown 
{ 
public:
   // Initialize a debug doc helper with the given name and 
   // initial attributes. 
   // 
   // Note: The document will not actually appear in the tree 
   // until Attach is called. 
   virtual HRESULT STDMETHODCALLTYPE Init( 
      IDebugApplication *pda, 
      LPCOLESTR pszShortName, 
      LPCOLESTR pszLongName, 
      TEXT_DOC_ATTR docAttr) = 0; 

   // Add the document to the doc tree, using pddhParent as the parent. 
   // If the ppdhParent is NULL, the document will be top-level. 
   virtual HRESULT STDMETHODCALLTYPE Attach(IDebugDocumentHelper *pddhParent) = 0; 

   // Remove the document from the doc tree. 
   virtual HRESULT STDMETHODCALLTYPE Detach() = 0; 

   // Add the given set of unicode characters to end of the document. 
   // (This will generate IDebugDocumentTextEvent notifications.) 
   // 
   // If this method is called after AddDeferredText has been called, 
   // E_FAIL will be returned. 
   virtual HRESULT STDMETHODCALLTYPE AddUnicodeText( 
      LPCOLESTR pszText) = 0; 

   // Add the given set of DBCS characters to end of the document. 
   // (This will generate IDebugDocumentTextEvent notifications.) 
   // 
   // If this method is called after AddDeferredText has been called, 
   // E_FAIL will be returned. 
   virtual HRESULT STDMETHODCALLTYPE AddDBCSText( 
      LPCSTR pszText) = 0; 

   // Set the DebugDocumentHost interface. 
   // If provided, this interface will be used for 
   // smart-host syntax coloring, fetching deferred text, and returning 
   // controlling unknowns for newly created document contexts. 
   virtual HRESULT STDMETHODCALLTYPE SetDebugDocumentHost( 
      IDebugDocumentHost* pddh) = 0; 

   // Notify the helper that the given text is available, but don't actually 
   // provide the characters. 
   // This allows the host to defer providing the characters unless they 
   // are actually needed, while still allowing the helper to generate 
   // accurate notifications and size information. 
   // 
   // dwTextStartCookie is a cookie, defined by the host, that represents 
   // the starting position of the text. (For example, in a host that 
   // represents text in DBCS, the cookie could be a byte offset.) 
   // This cookie will be provided in subsequent calls to GetText. 
   // 
   // NB: It is assumed that a single call to 
   // GetText can get characters from multiple calls to AddDeferredText. 
   // The helper classes may also ask for the same range of deferred 
   // characters more than once. 
   // 
   // It is an error to mix calls to AddDeferredText with calls to 
   // AddUnicodeText or AddDBCSText-- Doing so will cause E_FAIL to be 
   // returned. 
   virtual HRESULT STDMETHODCALLTYPE AddDeferredText( 
      ULONG cChars,// number of (Unicode) characters to add 
      DWORD dwTextStartCookie 
      // host-defined cookie representing the starting position of the text. 
      ) = 0; 

   // Notify the helper that a particular range of 
   // characters is a script block handled by the given script engine. 
   // All syntax coloring and code context lookups for that range will be 
   // delegated to that script engine. 
   // 
   // This method would be used by a smart host whose documents contained 
   // embedded script blocks, or by a language engine containing embedded 
   // scripts for other languages. 
   // 
   // DefineScriptBlock should be called after the text has been 
   // added (via AddDBCSText, etc) but before the script script block 
   // has been parsed (via IActiveScriptParse). 
   virtual HRESULT STDMETHODCALLTYPE DefineScriptBlock( 
      ULONG ulCharOffset, 
      ULONG cChars, 
      IActiveScript* pas, 
      BOOL fScriptlet, 
      DWORD* pdwSourceContext 
      ) = 0; 

   // Set the default attribute to use for text that is not in a 
   // script block. (If not explicitly set, the default attributes for 
   // text outside of a script block is SOURCETEXT_ATTR_NONSOURCE.) 
   // 
   // This would allow, for example, for text outside of script blocks 
   // to be colored grey and marked read-only. 
   virtual HRESULT STDMETHODCALLTYPE SetDefaultTextAttr(SOURCE_TEXT_ATTR staTextAttr) = 0; 

   // Explicilty set the attributes on a range of text, overriding any 
   // other attributes on that text. 
   // 
   // It is an error to set the attributes on a text range that has not 
   // yet been added using AddText. 
   virtual HRESULT STDMETHODCALLTYPE SetTextAttributes( 
      ULONG ulCharOffset, 
      ULONG cChars, 
      SOURCE_TEXT_ATTR* pstaTextAttr) = 0; 

   // Set a new long name for the document 
   virtual HRESULT STDMETHODCALLTYPE SetLongName( 
      LPCOLESTR pszLongName) = 0; 

   // Set a new short name for the document 
   virtual HRESULT STDMETHODCALLTYPE SetShortName( 
      LPCOLESTR pszShortName) = 0; 

   // Define a new set of document attributes 
   virtual HRESULT STDMETHODCALLTYPE SetDocumentAttr( 
      TEXT_DOC_ATTR pszAttributes) = 0; 

   // Return the debug application node corresponding to this document 
   virtual HRESULT STDMETHODCALLTYPE GetDebugApplicationNode( 
      IDebugApplicationNode **ppdan) = 0; 

   // Once a script block has been defined, this method allows the 
   // associate range and script engine to be retrieved. 
   virtual HRESULT STDMETHODCALLTYPE GetScriptBlockInfo( 
      DWORD dwSourceContext, 
      IActiveScript** ppasd, 
      ULONG *piCharPos, 
      ULONG *pcChars) = 0; 

   // Allows the host to create a new debug document context 
   virtual HRESULT STDMETHODCALLTYPE CreateDebugDocumentContext( 
      ULONG iCharPos, 
      ULONG cChars, 
      IDebugDocumentContext** ppddc) = 0; 

   // Bring this document to the top in the debugger UI. 
   // If the debugger isn't started already, start it now. 
   virtual HRESULT STDMETHODCALLTYPE BringDocumentToTop() = 0; 

   // Bring the given context in this document to the top 
   // in the debugger UI. 
   virtual HRESULT STDMETHODCALLTYPE BringDocumentContextToTop(IDebugDocumentContext *pddc) = 0; 
};

// IRemoteDebugApplication Interface
// (51973C30-CB0C-11d0-B5C9-00A0244A0E7A), 
DEFINE_GUID(IID_IRemoteDebugApplication, 0x51973c30, 0xcb0c, 0x11d0, 0xb5, 0xc9, 0x0, 0xa0, 0x24, 0x4a, 0x0e, 0x7a);
class IRemoteDebugApplication : public IUnknown 
{ 
public:
   // Continue an application which is currently in a breakpoint. 
   virtual HRESULT STDMETHODCALLTYPE ResumeFromBreakPoint( 
      // For stepping modes, the thread which is to be affected by the stepping mode. 
      IRemoteDebugApplicationThread *prptFocus, 
      // The action to take (step mode, etc.) upon resuming the application 
      BREAKRESUMEACTION bra, 
      // the action to take in the case that we stopped because of an error 
      ERRORRESUMEACTION era) = 0; 

   // Causes the application to break into the debugger at the earliest opportunity. Note 
   // that a long time may elapse before the application actually breaks, particularly if 
   // the application is not currently executing script code. 
   virtual HRESULT STDMETHODCALLTYPE CauseBreak(void) = 0; 

   // Connects a debugger to the application. Only one debugger may be connected at a 
   // time; this method fails if there is already a debugger connected 
   virtual HRESULT STDMETHODCALLTYPE ConnectDebugger( 
      IApplicationDebugger *pad) = 0; 

   // Disconnects the current debugger from the application. 
   virtual HRESULT STDMETHODCALLTYPE DisconnectDebugger(void) = 0; 

   // Returns the current debugger connected to the application. 
   virtual HRESULT STDMETHODCALLTYPE GetDebugger( 
      IApplicationDebugger **pad) = 0; 

   // Provides a mechanism for the debugger IDE, running out-of-process to the 
   // application, to create objects in the application process. 
   // This method simply delegates to CoCreateInstance. 
   virtual HRESULT STDMETHODCALLTYPE CreateInstanceAtApplication( 
      REFCLSID rclsid,// Class identifier (CLSID) of the object 
      // Note: This parameter may have to be removed. 
      IUnknown *pUnkOuter,// Object is or isn't part of an aggregate 
      DWORD dwClsContext,// Context for running executable code 
      REFIID riid,// Interface identifier 
      IUnknown **ppvObject) = 0; 

   // Points to requested interface pointer 
   // Indicates if the application is alive. Should always return S_OK. If the application 
   // process has rudely shut down COM will return an error from the marshalling proxy. 
   virtual HRESULT STDMETHODCALLTYPE QueryAlive(void) = 0; 

   // Enumerates all threads known to be associated with the application. 
   // New threads may be added at any time. 
   virtual HRESULT STDMETHODCALLTYPE EnumThreads( 
      IEnumRemoteDebugApplicationThreads **pperdat) = 0; 

   // Returns the application node under which all nodes associated with the 
   // application are added. 
   virtual HRESULT STDMETHODCALLTYPE GetName( 
      BSTR *pbstrName) = 0; 

   // Returns a node for the application 
   virtual HRESULT STDMETHODCALLTYPE GetRootNode( 
      IDebugApplicationNode **ppdanRoot) = 0; 

   // Returns an enumerator that lists the global expression 
   // contexts for all languages running in this application 
   virtual HRESULT STDMETHODCALLTYPE EnumGlobalExpressionContexts ( 
      IEnumDebugExpressionContexts **ppedec) = 0; 
}; 


// IDebugApplication Interface
// (51973C32-CB0C-11d0-B5C9-00A0244A0E7A), 
DEFINE_GUID(IID_IDebugApplication, 0x51973c32, 0xcb0c, 0x11d0, 0xb5, 0xc9, 0x0, 0xa0, 0x24, 0x4a, 0x0e, 0x7a);
class IDebugApplication : public IRemoteDebugApplication 
{ 
public:
   // Sets the name of the application. The provided name will be returned in subsequent calls 
   // to IRemoteDebugApplication::GetName. 
   virtual HRESULT STDMETHODCALLTYPE SetName( 
      LPCOLESTR pstrName) = 0; 

   // This method is called by language engines, in single step mode, just before they 
   // return to their caller. The process debug manager uses this opportunity to notify all 
   // other script engines that they should break at the first opportunity. This is how 
   // cross language step modes are implemented. 
   virtual HRESULT STDMETHODCALLTYPE StepOutComplete(void) = 0; 

   // Causes the given string to be displayed by the debugger IDE, normally in an output 
   // window. This mechanism provides the means for a language engine to implement language 
   // specific debugging output support. Example: Debug.writeln("Help") in JavaScript. 
   virtual HRESULT STDMETHODCALLTYPE DebugOutput( 
      LPCOLESTR pstr) = 0; 

   // Causes a default debugger IDE to be started and a debug session to be attached to 
   // this application if one does not already exist. This is used to implement just-in-time 
   // debugging. 
   virtual HRESULT STDMETHODCALLTYPE StartDebugSession(void) = 0; 

   // Called by the language engine in the context of a thread that has hit a breakpoint. 
   // This method causes the current thread to block and a notification of the breakpoint 
   // to be sent to the debugger IDE. When the debugger IDE resumes the application this 
   // method returns with the action to be taken. 
   // 
   // Note: While in the breakpoint the language engine may be called in this thread to do 
   // various things such as enumerating stack frames or evaluating expressions. 
   virtual HRESULT STDMETHODCALLTYPE HandleBreakPoint( 
      BREAKREASON br, 
      BREAKRESUMEACTION *pbra) = 0; 

   // Causes this application to release all references and enter a zombie state. Called 
   // by the owner of the application generally on shut down. 
   virtual HRESULT STDMETHODCALLTYPE Close(void) = 0; 

   // Returns the current break flags for the application. 
   virtual HRESULT STDMETHODCALLTYPE GetBreakFlags( 
      APPBREAKFLAGS *pabf, 
      IRemoteDebugApplicationThread **pprdatSteppingThread) = 0; 

   // Returns the application thread object associated with the currently running thread. 
   virtual HRESULT STDMETHODCALLTYPE GetCurrentThread( 
      IDebugApplicationThread **pat) = 0; 

   // Creates an IDebugAsyncOperation object to wrap a provided IDebugSyncOperation object. 
   // This provides a mechanism for language engines to implement asynchronous expression and 
   // evaluation, etc. without having to know the details of synchronization with the 
   // debugger thread. See the descriptions for IDebugSyncOperation and IDebugAsyncOperation 
   // for more details. 
   virtual HRESULT STDMETHODCALLTYPE CreateAsyncDebugOperation( 
      IDebugSyncOperation *psdo, 
      IDebugAsyncOperation **ppado) = 0; 

   // Adds a stack frame sniffer to this application. Generally called by a language engine 
   // to expose its stack frames to the debugger. It is possible for other entities to 
   // expose stack frames. 
   virtual HRESULT STDMETHODCALLTYPE AddStackFrameSniffer( 
      IDebugStackFrameSniffer *pdsfs, 
      // Returns a cookie that is used to remove this stack frame sniffer 
      // from the application. 
      DWORD *pdwCookie) = 0; 

   // Removes a stack frame sniffer from this application. 
   virtual HRESULT STDMETHODCALLTYPE RemoveStackFrameSniffer( 
      // The cookie returned by AddStackFrameSniffer. 
      DWORD dwCookie) = 0; 

   // Returns S_OK if the current running thread is the debugger thread. 
   // Otherwise, returns S_FALSE. 
   virtual HRESULT STDMETHODCALLTYPE QueryCurrentThreadIsDebuggerThread(void) = 0; 

   // Provides a mechanism for the caller to run code in the debugger thread. This is generally 
   // used so that language engines and hosts can implement free threaded objects on top 
   // of their single threaded implementations. 
   virtual HRESULT STDMETHODCALLTYPE SynchronousCallInDebuggerThread( 
      IDebugThreadCall *pptc, 
      DWORD dwParam1, 
      DWORD dwParam2, 
      DWORD dwParam3) = 0; 

   // Creates a new application node which is associated with a specific 
   // document provider. Before it is visible, the new node must be 
   // attached to a parent node. 
   virtual HRESULT STDMETHODCALLTYPE CreateApplicationNode( 
      IDebugApplicationNode **ppdanNew) = 0; 

   // Fire a generic event to the IApplicationDebugger (if any) 
   // The semantics of the GUID and IUnknown are entirely application/debugger defined 
   // 
   // This method is currently unimplemented but is here to allow for future extensions. 
   virtual HRESULT STDMETHODCALLTYPE FireDebuggerEvent( 
      REFGUID riid, 
      IUnknown *punk) = 0; 

   // Called by the language engine in the context of a thread that has caused a runtime error. 
   // This method causes the current thread to block and a notification of the error 
   // to be sent to the debugger IDE. When the debugger IDE resumes the application this 
   // method returns with the action to be taken. 
   // 
   // Note: While in the runtime error the language engine may be called in this thread to do 
   // various things such as enumerating stack frames or evaluating expressions. 
   virtual HRESULT STDMETHODCALLTYPE HandleRuntimeError( 
      IActiveScriptErrorDebug *pErrorDebug,// the error that occurred 
      IActiveScriptSite *pScriptSite,// the script site of the thread 
      BREAKRESUMEACTION *pbra,// how to continue execution (stepping etc...) 
      ERRORRESUMEACTION *perra,// how to handle the error case 
      BOOL *pfCallOnScriptError) = 0;// if TRUE then engine should call IActiveScriptSite::OnScriptError() 

   // BUGBGU BUGBGU - how the hell are these implemented ?!?!?!
   // return TRUE if there is a JIT debugger registered 
   virtual BOOL FCanJitDebug () = 0; 

   // returns TRUE if a JIT debugger is registered and it is registered to auto-JIT debug dumb hosts 
   virtual BOOL FIsAutoJitDebugEnabled () = 0; 

   // Adds a global expression context provider to this application 
   virtual HRESULT STDMETHODCALLTYPE AddGlobalExpressionContextProvider( 
      IProvideExpressionContexts *pdsfs, 
      // Returns a cookie that is used to remove this global expression context provider 
      // from the application. 
      DWORD *pdwCookie) = 0; 

   // Removes a global expression context provider from this application. 
   virtual HRESULT STDMETHODCALLTYPE RemoveGlobalExpressionContextProvider( 
      // The cookie returned by AddGlobalExpressionContextProvider. 
      DWORD dwCookie) = 0; 
};
 
// IDebugDocumentHost Interface
// (51973C27-CB0C-11d0-B5C9-00A0244A0E7A), 
DEFINE_GUID(IID_IDebugDocumentHost, 0x51973c27, 0xcb0c, 0x11d0, 0xb5, 0xc9, 0x0, 0xa0, 0x24, 0x4a, 0x0e, 0x7a);
class IDebugDocumentHost : public IUnknown 
{
public:   
   // Return a particular range of characters in the original host document, 
   // added using AddDeferredText. 
   // 
   // It is acceptable for a host to return E_NOTIMPL for this method, 
   // as long as the host doesn't call AddDeferredText. 
   // 
   // (Note that this is text from the _original_ document. The host 
   // does not need to be responsible for keeping track of edits, etc.) 
   virtual HRESULT STDMETHODCALLTYPE GetDeferredText( 
      DWORD dwTextStartCookie, 
      // Specifies a character text buffer. NULL means do not return characters. 
      WCHAR *pcharText, 
      // Specifies a character attribute buffer. NULL means do not return attributes. 
      SOURCE_TEXT_ATTR *pstaTextAttr, 
      // Indicates the actual number of characters/attributes returned. Must be set to zero 
      // before the call. 
      ULONG *pcNumChars, 
      // Specifies the number maximum number of character desired. 
      ULONG cMaxChars) = 0; 

   // Return the text attributes for an arbitrary block of document text. 
   // It is acceptable for hosts to return E_NOTIMPL, in which case the 
   // default attributes are used. 
   virtual HRESULT STDMETHODCALLTYPE GetScriptTextAttributes( 
      // The script block text. This string need not be null terminated. 
      LPCOLESTR pstrCode, 
      // The number of characters in the script block text. 
      ULONG uNumCodeChars, 
      // See IActiveScriptParse::ParseScriptText for a description of this argument. 
      LPCOLESTR pstrDelimiter, 
      // See IActiveScriptParse::ParseScriptText for a description of this argument. 
      DWORD dwFlags, 
      // Buffer to contain the returned attributes. 
      SOURCE_TEXT_ATTR *pattr)  = 0; 

   // Notify the host that a new document context is being created 
   // and allow the host to optionally return a controlling unknown 
   // for the new context. 
   // 
   // This allows the host to add new functionality to the helper-provided 
   // document contexts. It is acceptable for the host to return E_NOTIMPL 
   // or a null outer unknown for this method, in which case the context is 
   // used "as is". 
   virtual HRESULT STDMETHODCALLTYPE OnCreateDocumentContext( 
      IUnknown** ppunkOuter)  = 0; 

   // Return the full path (including file name) to the document's source file. 
   //*pfIsOriginalPath is TRUE if the path refers to the original file for the document. 
   //*pfIsOriginalPath is FALSE if the path refers to a newly created temporary file 
   //Returns E_FAIL if no source file can be created/determined. 
   virtual HRESULT STDMETHODCALLTYPE GetPathName( 
      BSTR *pbstrLongName, 
      BOOL *pfIsOriginalFile)  = 0; 

   // Return just the name of the document, with no path information. 
   // (Used for "Save As...") 
   virtual HRESULT STDMETHODCALLTYPE GetFileName( 
      BSTR *pbstrShortName)  = 0; 

   // Notify the host that the document's source file has been saved and 
   // that its contents should be refreshed. 
   virtual HRESULT STDMETHODCALLTYPE NotifyChanged()  = 0; 
};

#endif // h_activscp_plus
