// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------


#ifndef SERIAL_H
#define SERIAL_H


/*---------------------------------------------------------------------------
;
;	   File:	serial.h
;
---------------------------------------------------------------------------*/

#include "..\mach_common\types.h"

int   serial_init(void);
void  serial_send_response(void);
void  serial_receive(void);


extern Uint32_t  oslot;



#endif 
