// SMRL.h   Include file for SMRL Modbus/RTU Master Dynamic Link Library.


// SMRL Version 1.0


// This file is included by C and C++ applications using the SMRL library.


// Copyright (C) 2004, Sapia, Inc., All Rights Reserved

// Warning:  This product is licensed to you pursuant to the terms of the
// license agreement included with the original software, and is
// protected by copyright law and international treaties.  Unauthorized
// reproduction or distribution may result in severe civil and criminal
// penalties, and will be prosecuted to the maximum extent possible under
// the law.


// Sapia, Inc.
// PO Box 633
// Milford, MI 48381
// Web: www.sapia-inc.com
// Email: support@sapia-inc.com

// Revision History

// Version  Date         Description
// -------  -----------  -----------------------------------------------------------
// 1.0      4-4-2004     First Release (V1.0).







///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Definitions //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// Define error status returned by the SMRL functions.

#define MB_NO_ERROR 0


// This group represents Modbus exception status code per the
// Modbus specification.  These are explained in detail in 
// Chapter 4, "Exception Responses" of the Modbus specification. 

#define MB_ILLEGAL_FUNCTION 1
#define MB_ILLEGAL_DATA_ADDRESS 2
#define MB_ILLEGAL_DATA_VALUE 3
#define MB_SLAVE_DEVICE_FAILURE 4
#define MB_ACKNOWLEDGE 5
#define MB_SLAVE_DEVICE_BUSY 6
#define MB_NEGATIVE_ACKNOWLEDGE 7
#define MB_MEMORY_PARITY_ERROR 8


// This group represents additional errors reported that have to
// do with communications.

#define MB_RCV_TIMEOUT 9				// receive timeout error
#define MB_XMT_TIMEOUT 10				// transmit timeout error
#define MB_CRC_ERROR 11					// CRC error in response from slave


// Communications Configuration Parameter error codes.
// These are used to signal errors when configuring communications.

#define MB_PORT_ERROR 20				// illegal comm port number
#define MB_OPEN_ERROR 21				// can't open comm port 
#define MB_CLOSE_ERROR 22				// can't close comm port
#define MB_PARITY_ERROR 23				// illegal parity type
#define MB_BAUD_ERROR 24				// illegal baud rate
#define MB_STOPBITS_ERROR 25			// illegal number of stop bits
#define MB_DATABITS_ERROR 26			// illegal number of data bits
#define MB_PARAM_ERROR 27				// unspecified parameter error
#define MB_TIMEOUT_ERROR 28				// illegal timeout value
#define MB_DELAY_ERROR 29				// illegal tranmsit delay
#define MB_CONTROL_ERROR 30				// illegal control value
#define MB_DEMO_EXPIRED 31				// demo period expired
#define MB_COMM_PORT_NOT_OPEN 32		// comm port not open error




// RTS Control selector constants used by SmrlSetRTSControl() and SmrlGetRTSControl()

#define RTS_NEGATED 0					// RTS always negated (-V)
#define RTS_ASSERTED 1					// RTS always asserted (+V)
#define RTS_XMT 2						// RTS asserted during transmission


// DTR Control selector constants used by SmrlSetDTRControl() and SmrlGetDTRControl()

#define DTR_NEGATED 0					// DTR always negated (-V)
#define DTR_ASSERTED 1					// DTR always asserted (+V)
#define DTR_TRACKS_RTS 2				// DTR tracks RTS line


// Parity selector constants used by SmrlSetParity() and SmrlGetParity()

#define PAR_NONE 0						// no parity
#define PAR_ODD 1						// odd parity
#define PAR_EVEN 2						// even parity






///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// API Function Prototypes ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

#undef DLL_IMPORT_EXPORT

#ifdef SMRL_EXPORTS
   #define DLL_IMPORT_EXPORT __declspec(dllexport) __stdcall // used when compiling SMRL
#else
   #define DLL_IMPORT_EXPORT __declspec(dllimport) __stdcall // used by apps linking to SMRL
#endif

#ifdef __cplusplus
  #define NoMangle extern "C"
#else
  #define NoMangle
#endif

// Configuration Functions

NoMangle short DLL_IMPORT_EXPORT SmrlSetLicenseKey( char *pKey );
NoMangle long DLL_IMPORT_EXPORT SmrlVersion( void );
NoMangle long DLL_IMPORT_EXPORT SmrlCommPortFlags( void );
NoMangle short DLL_IMPORT_EXPORT SmrlSetPortOpen( short nNewValue );
NoMangle short DLL_IMPORT_EXPORT SmrlGetPortOpen( void );
NoMangle short DLL_IMPORT_EXPORT SmrlSetCommPort( short nNewValue );
NoMangle short DLL_IMPORT_EXPORT SmrlGetCommPort( void );
NoMangle short DLL_IMPORT_EXPORT SmrlSetBaudRate( long nNewValue );
NoMangle long DLL_IMPORT_EXPORT SmrlGetBaudRate( void );
NoMangle short DLL_IMPORT_EXPORT SmrlSetParity( short nNewValue );
NoMangle short DLL_IMPORT_EXPORT SmrlGetParity( void );
NoMangle short DLL_IMPORT_EXPORT SmrlSetDTRControl( short nNewValue );
NoMangle short DLL_IMPORT_EXPORT SmrlGetDTRControl( void );
NoMangle short DLL_IMPORT_EXPORT SmrlSetRTSControl( short nNewValue );
NoMangle short DLL_IMPORT_EXPORT SmrlGetRTSControl( void );
NoMangle short DLL_IMPORT_EXPORT SmrlSetDataBits( short nNewValue );
NoMangle short DLL_IMPORT_EXPORT SmrlGetDataBits( void );
NoMangle short DLL_IMPORT_EXPORT SmrlSetStopBits( short nNewValue );
NoMangle short DLL_IMPORT_EXPORT SmrlGetStopBits( void );
NoMangle short DLL_IMPORT_EXPORT SmrlSetRcvTimeout( short nNewValue );
NoMangle short DLL_IMPORT_EXPORT SmrlGetRcvTimeout( void );
NoMangle short DLL_IMPORT_EXPORT SmrlSetXmtTimeout( short nNewValue );
NoMangle short DLL_IMPORT_EXPORT SmrlGetXmtTimeout( void );
NoMangle short DLL_IMPORT_EXPORT SmrlSetXmtDelay( short nNewValue );
NoMangle short DLL_IMPORT_EXPORT SmrlGetXmtDelay( void );



// Modbus Communications Functions

NoMangle short DLL_IMPORT_EXPORT SmrlMbReadHoldingRegs( short nSlaveAddr, short nStartReg, short nNumRegs, short *pRegs );
NoMangle short DLL_IMPORT_EXPORT SmrlMbReadInputRegs( short nSlaveAddr, short nStartReg, short nNumRegs, short *pRegs );
NoMangle short DLL_IMPORT_EXPORT SmrlMbPresetSingleReg( short nSlaveAddr, short nStartReg, short nRegVal );
NoMangle short DLL_IMPORT_EXPORT SmrlMbPresetMultipleRegs( short nSlaveAddr, short nStartReg, short nNumRegs, short *pRegs );
NoMangle short DLL_IMPORT_EXPORT SmrlMbReadCoilStatus( short nSlaveAddr, short nStartCoil, short nNumCoils, short *pValue );
NoMangle short DLL_IMPORT_EXPORT SmrlMbReadInputStatus( short nSlaveAddr, short nStartInput, short nNumInputs, short *pValue );
NoMangle short DLL_IMPORT_EXPORT SmrlMbForceSingleCoil( short nSlaveAddr, short nStartCoil, short nValue );
NoMangle short DLL_IMPORT_EXPORT SmrlMbForceMultipleCoils( short nSlaveAddr, short nStartCoil, short nNumCoils, short *pValue );
NoMangle short DLL_IMPORT_EXPORT SmrlMbReportSlaveID( short nSlaveAddr, short *pByteCnt, short *pData );
NoMangle short DLL_IMPORT_EXPORT SmrlMbReadExceptionStatus( short nSlaveAddr, short *pData );





