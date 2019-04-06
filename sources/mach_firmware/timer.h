// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------



#ifndef TIMER_H
#define TIMER_H

#include "..\mach_common\types.h"
#include "..\mach_common\mach_firmware.h"
#include "hwinit.h"



#define TIMER_BUF_LEN   432


#if defined(__DEBUG)
#define PIN_DBG(X_)      LATAbits.LATA0 = X_                
#else
#define PIN_DBG(X_)                  
#endif

typedef struct
{   
    timer_frame_t    * current_step;
    timer_frame_t    * current_jog;
    Uint8_t            inputs; 

    Int16_t            last_valid_id;              
    Uint16_t           slots_head;    
    Uint16_t           slots_tail;
    Uint16_t           slots_used;     
    int                jog_mode;
    Uint16_t           jog_in_mask;
    Uint16_t           jog_in_value;
    
}timer_buffer_t;

typedef struct
{
    Uint32_t           Xac;
    Uint32_t           Yac;
    Uint32_t           Zac;
    Uint32_t           Aac;
}timer_engine_t;


typedef struct
{
    Uint32_t           accumulator;
    Int32_t          * coord_ptr;    
    int                dir_neg; 
    int                pulse;
}timer_jog_engine_t;




extern timer_coord_t    coords;
extern timer_buffer_t   buffer;
extern Uint32_t         tick;

void timer_init(void);

void timer_enable_run(void);
void timer_disable_run(void);
void timer_flush_buffers(void);
void timer_sync_coords(void);
int  timer_execute_frame(Uint8_t * frame_stream,int idx);


#endif
