// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// -------------------------------------------------------------------------------------------------------------------------------------------------------




#ifndef MACH_PCLIB_PROTOCOL_H
#define MACH_PCLIB_PROTOCOL_H

#include "types.h"
#include "mach_firmware.h"

#ifdef WIN32
#ifdef _USRDLL
#define FNTYPE  extern "C"  __declspec( dllexport )
#else
#define FNTYPE  extern "C" __declspec( dllimport )
#endif
#define STDCALL __stdcall
#else
#define FNTYPE
#define STDCALL
#endif

////////////////////////////////////////////////////////////////////////////////
// Response status info
////////////////////////////////////////////////////////////////////////////////

#define  S_IDLE            0
#define  S_RUNNING         1
#define  S_ESTOP           2

////////////////////////////////////////////////////////////////////////////////
// Interface function definitions
////////////////////////////////////////////////////////////////////////////////

FNTYPE int  STDCALL Cnc_Init_Controller(void);
FNTYPE int  STDCALL Cnc_Exit_Controller(void);

FNTYPE int	STDCALL Cnc_Communication_Enable(const char * address);
FNTYPE int  STDCALL Cnc_Communication_Disable(void);

FNTYPE int  STDCALL Cnc_Communication_GetSerial(void);


FNTYPE int  STDCALL Cnc_Status_Get(timer_resp_t  * status);

FNTYPE int  STDCALL Cnc_SetCoords(timer_coord_t  * coord);
FNTYPE int  STDCALL Cnc_SetMap(timer_map_t    * map, int map_cnt);
FNTYPE int  STDCALL Cnc_SetOutputs(Uint32_t outputs,Uint32_t mask);

FNTYPE void STDCALL Cnc_SendCommand(command_e cmd,int clear_queue);

FNTYPE int  STDCALL Cnc_GetBufferStatus(void);
FNTYPE int  STDCALL Cnc_IsQueEmpty(void);
FNTYPE int  STDCALL Cnc_GetInputs(void);

FNTYPE int  STDCALL Cnc_SetFrame(timer_frame_t  * frame, int frame_cnt,int replace_queue);


#endif //MACH_PCLIB_PROTOCOL_H
