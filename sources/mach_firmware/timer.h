  // ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jarosaw Karwik
   E-Mail:     jaroslaw.karwik(at)gmail.com
   
**/
// ----------------------------------------------------------------------------



#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"
#include "../mach_common/mach_firmware.h"
#include "init.h"



#define TIMER_BUF_LEN   1024


#if defined(__DEBUG)
#define PIN_DBG(X_)      LATAbits.LATA0 = X_                
#else
#define PIN_DBG(X_)                  
#endif

typedef struct
{   
    timer_frame_t    * current_step;
    timer_frame_t    * current_jog;
    uint64_t           inputs; 

    int32_t            last_valid_id;              
    uint32_t           slots_head;    
    uint32_t           slots_tail;
    uint32_t           slots_used;     
    int32_t            jog_mode;
    uint64_t           jog_in_mask;
    uint64_t           jog_in_value;
    
}timer_buffer_t;

typedef struct
{
    uint32_t           Xac;
    uint32_t           Yac;
    uint32_t           Zac;
    uint32_t           Aac;
}timer_engine_t;


typedef struct
{
    uint32_t           accumulator;
    int32_t          * coord_ptr;    
    int                dir_neg; 
    int                pulse;
}timer_jog_engine_t;




extern timer_coord_t    coords;
extern timer_buffer_t   buffer;
extern uint32_t         tick;

void timer_init(void);

void timer_enable_run(void);
void timer_disable_run(void);
void timer_flush_buffers(void);
void timer_sync_coords(void);
int  timer_execute_frame(uint8_t * frame_stream,int idx);


#endif
