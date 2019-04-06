// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------




#include "..\mach_common\types.h" 
#include "hwinit.h" 
#include "serial.h"
#include "pinctrl.h"
#include "timer.h"






// Fuse configuration for the device
_FBS(RBS_NO_RAM & BWRP_WRPROTECT_OFF & BSS_NO_BOOT_CODE & BSS_NO_FLASH); // No boot segment

_FSS(RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF);                   // No secure segments 
_FGS(GSS_OFF);                                                          // No code protection     

_FOSCSEL(FNOSC_PRIPLL); 				
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON  & POSCMD_EC);	                        // Clock Switching Enabled and Fail Safe Clock Monitor is disabled
													                    // OSC2 Pin Function: OSC2 is IO
													                    // Primary Oscillator Mode:External clock

_FWDT(FWDTEN_OFF & WDTPRE_PR32 & WDTPOST_PS64 & WINDIS_ON  );       	// Watchdog Timer Enabled/disabled by user software
															            // Watchdog prescaler 1:32
															            // Watchdog postscaler 1:64
															            // No window

_FPOR(PWMPIN_ON);                                                       // PWM pins controlled by port registers

_FICD(JTAGEN_OFF & ICS_PGD1 );                                          // No JTAG and PGD/PGC set 1                   




void hwinit_oscilator_init(void)
{
#ifndef __DEBUG
    // Configure Oscillator to operate the device at 40Mhz
    // Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
    // Fosc= 6.25M*128/(5*2)=80Mhz
    
    PLLFBD             = 126;   // M=128
    CLKDIVbits.PLLPOST = 0;     // N2=2
    CLKDIVbits.PLLPRE  = 3;     // N1=5
    CLKDIVbits.DOZE    = 0;     // No clock reduction
#else
    // Configure Oscillator to operate the device at 20Mhz ( no possibility to debug 40Mhz running device)
    // Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
    // Fosc= 6.25M*40/(5*4)=40Mhz
    
    PLLFBD             = 126;   // M=128
    CLKDIVbits.PLLPOST = 1;     // N2=4
    CLKDIVbits.PLLPRE  = 3;     // N1=5
    CLKDIVbits.DOZE    = 0;     // No clock reduction
    
#endif

	// Clock switching to incorporate PLL
	__builtin_write_OSCCONH(0x03);		// Initiate Clock Switch to Primary
										// Oscillator with PLL (NOSC=0b011)
	__builtin_write_OSCCONL(0x01);		// Start clock switching
	while (OSCCONbits.COSC != 0b011);	// Wait for Clock switch to occur	

}


void hwinit_ioport_init(void)
{

	// Inputs

    // RP3-> U1RX
    TRISBbits.TRISB2  = 1; RPINR18bits.U1RXR = 0x02; //Input tied to RP2
   
    TRISBbits.TRISB0  = 1; // BOOT
    TRISBbits.TRISB5  = 1; // IN1
    TRISBbits.TRISB6  = 1; // IN4
    TRISBbits.TRISB7  = 1; // IN3
    TRISBbits.TRISB8  = 1; // IN2
    TRISBbits.TRISB9  = 1; // IN5

    // Pullups on inputs

    CNPU2bits.CN21PUE = 1; // IN5
    CNPU2bits.CN22PUE = 1; // IN2
    CNPU2bits.CN23PUE = 1; // IN3
    CNPU2bits.CN24PUE = 1; // IN4
    CNPU2bits.CN27PUE = 1; // IN1

  
	// Outputs

    // RP3-> U1TX
    TRISBbits.TRISB3  = 0; RPOR1bits.RP3R    = 0b00011;// RPn tied to UART1 Transmit
    
    TRISAbits.TRISA0   = 0;  // LPT_O1
    TRISAbits.TRISA1   = 0;  // LPT_O2
    TRISBbits.TRISB14  = 0;  // LPT_O3        
    TRISBbits.TRISB13  = 0;  // LPT_O4
    TRISBbits.TRISB11  = 0;  // LPT_O5    
    TRISBbits.TRISB10  = 0;  // LPT_O6    
    TRISAbits.TRISA3   = 0;  // LPT_O7
    TRISBbits.TRISB4   = 0;  // LPT_O8
    TRISAbits.TRISA4   = 0;  // LPT_O9

    TRISBbits.TRISB15  = 0;  // LPT_O14
    TRISBbits.TRISB1   = 0;  // LPT_O16
    TRISBbits.TRISB12  = 0;  // LPT_O17






    

	// Analog inputs AN0..AN15 disabled (digital)
	AD1PCFGL = 0xFFFF;
	


}


void hwinit_reset(void)
{
	RCONbits.SWDTEN=1;
	CORCONbits.IPL3 = 1;
	while(1)
	{
		;
	}
}


/*-----------------------*/


int main(void)
{
	hwinit_oscilator_init();
	hwinit_ioport_init();
    pinctrl_set_outputs(0x0,0xFFFF);
    
    INTCON1bits.NSTDIS = 0;


    serial_init();
    timer_init();

    CORCONbits.IPL3 = 0;

    while(1)
    {
    }

	return 0; /* Note - never comes here */

}
/******************************************************************************/

