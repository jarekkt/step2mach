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
void serial_prepare_response(char ** bufp,uint32_t * size);
void  serial_process_receive(char *recv_buffer, uint32_t cnt);

#endif 
