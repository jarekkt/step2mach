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

#include <string.h>
#include "stdint.h"
#include "../mach_common/mach_firmware.h"
#include "init.h"
#include "serial.h"
#include "crc16.h"
#include "timer.h"



static timer_resp_t     response;
static uint8_t          recv_buffer[1988];
static uint16_t         last_ptr = 0;







/*---------------------------------------------------------------------------
---------------------------------------------------------------------------*/


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



/*---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

void serial_send_response(void)
{
#if 0 //TODO
    int ipl;


    while(DMA1CONbits.CHEN  != 0)
    {
     // Transmission in progrss
    }

    SET_AND_SAVE_CPU_IPL(ipl,7); 
   
    response.data.inputs         = buffer.inputs;    
    response.data.last_valid_id  = buffer.last_valid_id;

    // We have only 8 bit variable for free slots, so we have 2 slots resolution
    response.data.free_slots   = (Uint8_t)((TIMER_BUF_LEN  - buffer.slots_used)/2);
     

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
    
    SET_CPU_IPL(ipl);
    
    crc_append((unsigned char*)&response,offsetof(timer_resp_t,crc16));

    IFS0bits.DMA1IF = 0; // Clear DMA interrupt
    IEC0bits.DMA1IE = 1; // Enable DMA interrupt

    
    DMA1CONbits.CHEN            = 1;            // Re-enable DMA1 Channel
    DMA1REQbits.FORCE           = 1;            // Manual mode: Kick-start the first transfer



#endif
    
}


/*---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

void  serial_receive(void)
{
#if 0
    uint16_t cnt;
    uint16_t item_idx;
    uint16_t item_idx_max;
    uint16_t free_slots;
    
    if( (last_ptr != DMA0STA) || (DMA0STA == __builtin_dmaoffset(recv_buffer) ))
    {
       // Receive process in progress, wait until finishes or nothing received
       last_ptr = DMA0STA;      
        
       if(U1STAbits.OERR )
       {
            DMA0CONbits.CHEN = 0;
            goto reinit;
       }

       return;
    }
    

    // Timeout - during 1ms we should have received something (unless the transmission has finished)
    // Disable DMA0 Channel

    // Check count
    cnt = DMA0STA - __builtin_dmaoffset(recv_buffer);

    DMA0CONbits.CHEN = 0;    

    if(cnt >= 3 + sizeof(timer_frame_t))
    {
        if(recv_buffer[0] == '<')
        {
            if( (cnt-3)% sizeof(timer_frame_t) == 0)
            {
                if(crc_verify(&recv_buffer[1],cnt-1)!=0)
                {
                    item_idx_max = (cnt-3) / sizeof(timer_frame_t);

                    free_slots = TIMER_BUF_LEN  - buffer.slots_used;

                    if( item_idx_max  < free_slots)
                    {
                        for(item_idx = 0; item_idx < item_idx_max; item_idx++)
                        {
                           if(timer_execute_frame(&recv_buffer[1+sizeof(timer_frame_t) * item_idx],item_idx)!=0)
                           {
                              goto reinit;
                           }
                        }
                    }
                }                
            }
        }        
    }


reinit:

    // Reinit receiveing    
    DMA0STA = __builtin_dmaoffset(recv_buffer);
    last_ptr = DMA0STA;
    DMA0CNT = sizeof(recv_buffer);
    IFS0bits.DMA0IF  = 0;           // Clear DMA0 Interrupt Flag
    IEC0bits.DMA0IE  = 1;           // Enable DMA0 interrupt
    U1STAbits.OERR = 0;             // Just in case     - clear UART overrun status
    DMA0CONbits.CHEN = 1;           // Enable DMA0 Channel    
#endif
    
}

