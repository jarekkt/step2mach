// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jarosaw Karwik
   E-Mail:     jaroslaw.karwik(at)gmail.com
   
**/
// ----------------------------------------------------------------------------



/*---------------------------------------------------------------------------
;
;      File:    serdrv.c    
;
---------------------------------------------------------------------------*/

#include "string.h"
#include "stdint.h"
#include "stddef.h"

#include "../mach_common/mach_firmware.h"
#include "init.h"
#include "serial.h"
#include "crc16.h"
#include "timer.h"

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"



static timer_resp_t         response;




int serial_init(void)
{
    /*
            Fixed header part
    */

    response.header.magic_beg    = '>';
    response.header.size         = sizeof(response);
    response.header.version      = VERSION_NR;
    response.magic_end           = '#';


    return 0;    
}



void serial_prepare_response(char ** bufp,uint32_t * size)
{

    response.data.inputs         = buffer.inputs;    
    response.data.last_valid_id  = buffer.last_valid_id;
    response.data.free_slots     = TIMER_BUF_LEN  - buffer.slots_used;
     

    if( (buffer.current_step != NULL) || (buffer.current_jog != NULL) )
    {
        response.data.line_id = buffer.current_step->data.step.line_id;
        response.header.state = ENG_STATE_RUNNING;
    }
    else 
    {
        response.data.line_id = 0xFFFFFFFF;
        response.header.state = ENG_STATE_IDLE;
    }
    
    response.data.coords             = coords;
    
    crc_append((unsigned char*)&response,offsetof(timer_resp_t,crc16));
       
    *bufp = (char *)&response;
    *size = sizeof(response);
     
}


void  serial_process_receive(char *recv_buffer, uint32_t cnt)
{
    uint32_t item_idx;
    uint32_t item_idx_max;
    uint32_t free_slots;
    
    if(cnt >= 3 + sizeof(timer_frame_t))
    {
        if(recv_buffer[0] == '<')
        {
            if( (cnt-3)% sizeof(timer_frame_t) == 0)
            {
                if(crc_verify((const uint8_t*)&recv_buffer[1],cnt-1)!=0)
                {
                    item_idx_max = (cnt-3) / sizeof(timer_frame_t);

                    free_slots = TIMER_BUF_LEN  - buffer.slots_used;

                    if( item_idx_max  < free_slots)
                    {
                        for(item_idx = 0; item_idx < item_idx_max; item_idx++)
                        {
                           if(timer_execute_frame((const uint8_t*)&recv_buffer[1+sizeof(timer_frame_t) * item_idx],item_idx)!=0)
                           {
                             return;
                           }
                        }
                    }
                }                
            }
        }        
    }    
}

