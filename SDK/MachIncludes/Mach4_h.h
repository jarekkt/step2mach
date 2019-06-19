

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue May 09 23:55:30 2006
 */
/* Compiler settings for .\Mach4.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Mach4_h_h__
#define __Mach4_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMach4_FWD_DEFINED__
#define __IMach4_FWD_DEFINED__
typedef interface IMach4 IMach4;
#endif 	/* __IMach4_FWD_DEFINED__ */


#ifndef __CMach4Doc_FWD_DEFINED__
#define __CMach4Doc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMach4Doc CMach4Doc;
#else
typedef struct CMach4Doc CMach4Doc;
#endif /* __cplusplus */

#endif 	/* __CMach4Doc_FWD_DEFINED__ */


#ifndef __IMyScriptObject_FWD_DEFINED__
#define __IMyScriptObject_FWD_DEFINED__
typedef interface IMyScriptObject IMyScriptObject;
#endif 	/* __IMyScriptObject_FWD_DEFINED__ */


#ifndef __MyScriptObject_FWD_DEFINED__
#define __MyScriptObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyScriptObject MyScriptObject;
#else
typedef struct MyScriptObject MyScriptObject;
#endif /* __cplusplus */

#endif 	/* __MyScriptObject_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __Mach4_LIBRARY_DEFINED__
#define __Mach4_LIBRARY_DEFINED__

/* library Mach4 */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Mach4;

#ifndef __IMach4_DISPINTERFACE_DEFINED__
#define __IMach4_DISPINTERFACE_DEFINED__

/* dispinterface IMach4 */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IMach4;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D5DC1674-0CB6-47D4-BD22-E6D60631C86D")
    IMach4 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMach4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMach4 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMach4 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMach4 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMach4 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMach4 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMach4 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMach4 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMach4Vtbl;

    interface IMach4
    {
        CONST_VTBL struct IMach4Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMach4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMach4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMach4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMach4_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMach4_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMach4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMach4_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMach4_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CMach4Doc;

#ifdef __cplusplus

class DECLSPEC_UUID("CA7992B2-2653-4342-8061-D7D385C07809")
CMach4Doc;
#endif
#endif /* __Mach4_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


