// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jarosaw Karwik
   E-Mail:     jaroslaw.karwik(at)gmail.com
   
**/
// ----------------------------------------------------------------------------


#ifndef SERIAL_H
#define SERIAL_H


/*---------------------------------------------------------------------------
;
;      File:    serial.h
;
---------------------------------------------------------------------------*/

#include "stdint.h"

int   serial_init(void);
void  serial_send_response(void);
void  serial_receive(void);


extern uint32_t  oslot;



#endif 
