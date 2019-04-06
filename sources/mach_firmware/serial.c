// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------



/*---------------------------------------------------------------------------
;
;	   File:	serdrv.c	
;
---------------------------------------------------------------------------*/

#include <string.h>
#include "..\mach_common\types.h"
#include "..\mach_common\mach_firmware.h"
#include "hwinit.h"
#include "serial.h"
#include "crc16.h"
#include "timer.h"






#define BAUDRATE            1000000



static timer_resp_t     response             __attribute__((space(dma)));
static Uint8_t          recv_buffer[1988]  __attribute__((space(dma)));
static Uint16_t         last_ptr = 0;





/*---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

void serial_dma_init(void)
{


	/*  
	   Associate DMA Channel 0 with UART Tx 
	*/
	
	DMA1REQ = 0x0C;         // Select UART1 Transmitter DMA association
	DMA1PAD = (volatile unsigned int) &U1TXREG;
	
	/*  
	    Configure DMA Channel 0 to: 
	    Transfer data from RAM to UART
	    Continous mode, no ping-pong
	    Register Indirect with Post-Increment
	    Using single buffer
	    Transfer bytes
       */
	DMA1CONbits.AMODE = 0;
	DMA1CONbits.MODE  = 1;
	DMA1CONbits.DIR   = 1;
	DMA1CONbits.SIZE  = 1;

    /* 
	    Setup buffers & sizes
    	*/

	DMA1STA = __builtin_dmaoffset(&response);
    DMA1CNT = sizeof(response)-1;

	/*	
	    Enable interrupt		
	*/
	IFS0bits.DMA1IF  = 0;			// Clear DMA Interrupt Flag
	IEC0bits.DMA1IE	 = 1;			// Enable DMA interrupt


    /*  
            Associate DMA Channel 1 with UART Rx 
       */
     DMA0REQ = 0x0B       ;         // Select UART1 Receiver DMA association
     DMA0PAD = (volatile unsigned int) &U1RXREG;
        
    /*  
         Configure DMA Channel 0 to: 
         Transfer data from UART to RAM
         Continous  mode, no ping-pong
         Register Indirect with Post-Increment
         Using single buffer
         Transfer bytes
        */
     DMA0CONbits.AMODE = 0;
     DMA0CONbits.MODE  = 1;
     DMA0CONbits.DIR   = 0;
     DMA0CONbits.SIZE  = 1;


     /* 
         Setup buffers & sizes
         */
     
     DMA0STA = __builtin_dmaoffset(recv_buffer);
     DMA0CNT = sizeof(recv_buffer);
     
     /*  
         Enable interrupt        
         */
     IFS0bits.DMA0IF  = 0;           // Clear DMA0 Interrupt Flag
     IEC0bits.DMA0IE  = 1;           // Enable DMA0 interrupt
     DMA0CONbits.CHEN = 1;           // Enable DMA0 Channel

     

 }




/*---------------------------------------------------------------------------
---------------------------------------------------------------------------*/


int serial_init(void)
{
	/*
		 UART Configuration
	*/
	U1MODEbits.STSEL = 0;			// 1-stop bit
	U1MODEbits.PDSEL = 0;			// No Parity, 8-data bits
	U1MODEbits.ABAUD = 0;			// Autobaud Disabled
    U1MODEbits.BRGH  = 1;           // High speed mode

	U1BRG = ((FCY/BAUDRATE)/4)-1 ;	// Baudrate

	/*
	   Configure UART for Tx DMA transfers / Rx interrupt
	*/
	U1STAbits.UTXISEL0 = 0;			// Interrupt after one Tx character is transmitted
	U1STAbits.UTXISEL1 = 0;			                            
	U1STAbits.URXISEL  = 0;			// Interrupt after one RX character is received

	/*
	    Enable UART Rx and Tx
       */
	U1MODEbits.UARTEN   = 1;		// Enable UART
	U1STAbits.UTXEN     = 1;		// Enable UART Tx
	
	IFS0bits.U1RXIF     = 0;		// Clear the Recieve Interrupt Flag
    IFS0bits.U1TXIF     = 0;        // Clear the Transmit Interrupt Flag

	serial_dma_init();


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

    
	DMA1CONbits.CHEN            = 1;			// Re-enable DMA1 Channel
	DMA1REQbits.FORCE           = 1;			// Manual mode: Kick-start the first transfer




    
}


/*---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

void  serial_receive(void)
{
    Uint16_t cnt;
    Uint16_t item_idx;
    Uint16_t item_idx_max;
    Uint16_t free_slots;
    
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

    
}


/*---------------------------------------------------------------------------*/
 
void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void)
{
	IFS0bits.DMA1IF = 0; // Clear the DMA1 Interrupt Flag;
}

/*---------------------------------------------------------------------------*/
 
void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
	IFS0bits.DMA0IF = 0; // Clear the DMA0 Interrupt Flag;
}



