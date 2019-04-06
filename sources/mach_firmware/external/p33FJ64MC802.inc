;==========================================================================
;  PIC33FJ64MC802 Standard Assembly Include File
; 
;  (c) Copyright 2010 Microchip Technology, All rights reserved
;==========================================================================

.NOLIST

;==========================================================================
;  This header file defines configurations, registers, and other useful
;  bits of information for the PIC33FJ64MC802 microcontroller.  These names
;  are taken to match the data sheets as closely as possible.
;
;  Note that the processor must be selected before this file is included.
;  The processor may be selected the following ways:
;
;       1. Command line switch:
;               C:\> pic30-as file.s -p33FJ64MC802
;       2. Placing a ".equ" directive before the ".include":
;               .equ __33FJ64MC802, 1
;               .include "p33FJ64MC802.inc"
;       3. Setting the processor in the MPLAB IDE Project Dialog
;==========================================================================

;==========================================================================
;
;       Verify Processor
;
;==========================================================================

.IFNDEF __33FJ64MC802
   .ERROR "Include file does not match processor setting."
.ENDIF


;==========================================================================
;
;       Register Definitions
;
;==========================================================================

;----- Register Equates (Low Byte, High Byte) -----------------------------

        .extern WREG0
        .equiv  WREG0L, _WREG0
        .equiv  WREG0H, _WREG0+1

        .extern WREG1
        .equiv  WREG1L, _WREG1
        .equiv  WREG1H, _WREG1+1

        .extern WREG2
        .equiv  WREG2L, _WREG2
        .equiv  WREG2H, _WREG2+1

        .extern WREG3
        .equiv  WREG3L, _WREG3
        .equiv  WREG3H, _WREG3+1

        .extern WREG4
        .equiv  WREG4L, _WREG4
        .equiv  WREG4H, _WREG4+1

        .extern WREG5
        .equiv  WREG5L, _WREG5
        .equiv  WREG5H, _WREG5+1

        .extern WREG6
        .equiv  WREG6L, _WREG6
        .equiv  WREG6H, _WREG6+1

        .extern WREG7
        .equiv  WREG7L, _WREG7
        .equiv  WREG7H, _WREG7+1

        .extern WREG8
        .equiv  WREG8L, _WREG8
        .equiv  WREG8H, _WREG8+1

        .extern WREG9
        .equiv  WREG9L, _WREG9
        .equiv  WREG9H, _WREG9+1

        .extern WREG10
        .equiv  WREG10L, _WREG10
        .equiv  WREG10H, _WREG10+1

        .extern WREG11
        .equiv  WREG11L, _WREG11
        .equiv  WREG11H, _WREG11+1

        .extern WREG12
        .equiv  WREG12L, _WREG12
        .equiv  WREG12H, _WREG12+1

        .extern WREG13
        .equiv  WREG13L, _WREG13
        .equiv  WREG13H, _WREG13+1

        .extern WREG14
        .equiv  WREG14L, _WREG14
        .equiv  WREG14H, _WREG14+1

        .extern WREG15
        .equiv  WREG15L, _WREG15
        .equiv  WREG15H, _WREG15+1

        .extern SPLIM
        .equiv  SPLIML, _SPLIM
        .equiv  SPLIMH, _SPLIM+1

        .extern ACCAL
        .equiv  ACCALL, _ACCAL
        .equiv  ACCALH, _ACCAL+1

        .extern ACCAH
        .equiv  ACCAHL, _ACCAH
        .equiv  ACCAHH, _ACCAH+1

        .extern ACCAU
        .equiv  ACCAUL, _ACCAU
        .equiv  ACCAUH, _ACCAU+1

        .extern ACCBL
        .equiv  ACCBLL, _ACCBL
        .equiv  ACCBLH, _ACCBL+1

        .extern ACCBH
        .equiv  ACCBHL, _ACCBH
        .equiv  ACCBHH, _ACCBH+1

        .extern ACCBU
        .equiv  ACCBUL, _ACCBU
        .equiv  ACCBUH, _ACCBU+1

        .extern PCL
        .equiv  PCLL, _PCL
        .equiv  PCLH, _PCL+1

        .extern PCH
        .equiv  PCHL, _PCH
        .equiv  PCHH, _PCH+1

        .extern TBLPAG
        .equiv  TBLPAGL, _TBLPAG
        .equiv  TBLPAGH, _TBLPAG+1

        .extern PSVPAG
        .equiv  PSVPAGL, _PSVPAG
        .equiv  PSVPAGH, _PSVPAG+1

        .extern RCOUNT
        .equiv  RCOUNTL, _RCOUNT
        .equiv  RCOUNTH, _RCOUNT+1

        .extern DCOUNT
        .equiv  DCOUNTL, _DCOUNT
        .equiv  DCOUNTH, _DCOUNT+1

        .extern DOSTARTL
        .equiv  DOSTARTLL, _DOSTARTL
        .equiv  DOSTARTLH, _DOSTARTL+1

        .extern DOSTARTH
        .equiv  DOSTARTHL, _DOSTARTH
        .equiv  DOSTARTHH, _DOSTARTH+1

        .extern DOENDL
        .equiv  DOENDLL, _DOENDL
        .equiv  DOENDLH, _DOENDL+1

        .extern DOENDH
        .equiv  DOENDHL, _DOENDH
        .equiv  DOENDHH, _DOENDH+1

        .extern SR
        .equiv  SRL, _SR
        .equiv  SRH, _SR+1

        .extern CORCON
        .equiv  CORCONL, _CORCON
        .equiv  CORCONH, _CORCON+1

        .extern MODCON
        .equiv  MODCONL, _MODCON
        .equiv  MODCONH, _MODCON+1

        .extern XMODSRT
        .equiv  XMODSRTL, _XMODSRT
        .equiv  XMODSRTH, _XMODSRT+1

        .extern XMODEND
        .equiv  XMODENDL, _XMODEND
        .equiv  XMODENDH, _XMODEND+1

        .extern YMODSRT
        .equiv  YMODSRTL, _YMODSRT
        .equiv  YMODSRTH, _YMODSRT+1

        .extern YMODEND
        .equiv  YMODENDL, _YMODEND
        .equiv  YMODENDH, _YMODEND+1

        .extern XBREV
        .equiv  XBREVL, _XBREV
        .equiv  XBREVH, _XBREV+1

        .extern DISICNT
        .equiv  DISICNTL, _DISICNT
        .equiv  DISICNTH, _DISICNT+1

        .extern CNEN1
        .equiv  CNEN1L, _CNEN1
        .equiv  CNEN1H, _CNEN1+1

        .extern CNEN2
        .equiv  CNEN2L, _CNEN2
        .equiv  CNEN2H, _CNEN2+1

        .extern CNPU1
        .equiv  CNPU1L, _CNPU1
        .equiv  CNPU1H, _CNPU1+1

        .extern CNPU2
        .equiv  CNPU2L, _CNPU2
        .equiv  CNPU2H, _CNPU2+1

        .extern INTCON1
        .equiv  INTCON1L, _INTCON1
        .equiv  INTCON1H, _INTCON1+1

        .extern INTCON2
        .equiv  INTCON2L, _INTCON2
        .equiv  INTCON2H, _INTCON2+1

        .extern IFS0
        .equiv  IFS0L, _IFS0
        .equiv  IFS0H, _IFS0+1

        .extern IFS1
        .equiv  IFS1L, _IFS1
        .equiv  IFS1H, _IFS1+1

        .extern IFS2
        .equiv  IFS2L, _IFS2
        .equiv  IFS2H, _IFS2+1

        .extern IFS3
        .equiv  IFS3L, _IFS3
        .equiv  IFS3H, _IFS3+1

        .extern IFS4
        .equiv  IFS4L, _IFS4
        .equiv  IFS4H, _IFS4+1

        .extern IEC0
        .equiv  IEC0L, _IEC0
        .equiv  IEC0H, _IEC0+1

        .extern IEC1
        .equiv  IEC1L, _IEC1
        .equiv  IEC1H, _IEC1+1

        .extern IEC2
        .equiv  IEC2L, _IEC2
        .equiv  IEC2H, _IEC2+1

        .extern IEC3
        .equiv  IEC3L, _IEC3
        .equiv  IEC3H, _IEC3+1

        .extern IEC4
        .equiv  IEC4L, _IEC4
        .equiv  IEC4H, _IEC4+1

        .extern IPC0
        .equiv  IPC0L, _IPC0
        .equiv  IPC0H, _IPC0+1

        .extern IPC1
        .equiv  IPC1L, _IPC1
        .equiv  IPC1H, _IPC1+1

        .extern IPC2
        .equiv  IPC2L, _IPC2
        .equiv  IPC2H, _IPC2+1

        .extern IPC3
        .equiv  IPC3L, _IPC3
        .equiv  IPC3H, _IPC3+1

        .extern IPC4
        .equiv  IPC4L, _IPC4
        .equiv  IPC4H, _IPC4+1

        .extern IPC5
        .equiv  IPC5L, _IPC5
        .equiv  IPC5H, _IPC5+1

        .extern IPC6
        .equiv  IPC6L, _IPC6
        .equiv  IPC6H, _IPC6+1

        .extern IPC7
        .equiv  IPC7L, _IPC7
        .equiv  IPC7H, _IPC7+1

        .extern IPC8
        .equiv  IPC8L, _IPC8
        .equiv  IPC8H, _IPC8+1

        .extern IPC9
        .equiv  IPC9L, _IPC9
        .equiv  IPC9H, _IPC9+1

        .extern IPC11
        .equiv  IPC11L, _IPC11
        .equiv  IPC11H, _IPC11+1

        .extern IPC14
        .equiv  IPC14L, _IPC14
        .equiv  IPC14H, _IPC14+1

        .extern IPC15
        .equiv  IPC15L, _IPC15
        .equiv  IPC15H, _IPC15+1

        .extern IPC16
        .equiv  IPC16L, _IPC16
        .equiv  IPC16H, _IPC16+1

        .extern IPC17
        .equiv  IPC17L, _IPC17
        .equiv  IPC17H, _IPC17+1

        .extern IPC18
        .equiv  IPC18L, _IPC18
        .equiv  IPC18H, _IPC18+1

        .extern INTTREG
        .equiv  INTTREGL, _INTTREG
        .equiv  INTTREGH, _INTTREG+1

        .extern TMR1
        .equiv  TMR1L, _TMR1
        .equiv  TMR1H, _TMR1+1

        .extern PR1
        .equiv  PR1L, _PR1
        .equiv  PR1H, _PR1+1

        .extern T1CON
        .equiv  T1CONL, _T1CON
        .equiv  T1CONH, _T1CON+1

        .extern TMR2
        .equiv  TMR2L, _TMR2
        .equiv  TMR2H, _TMR2+1

        .extern TMR3HLD
        .equiv  TMR3HLDL, _TMR3HLD
        .equiv  TMR3HLDH, _TMR3HLD+1

        .extern TMR3
        .equiv  TMR3L, _TMR3
        .equiv  TMR3H, _TMR3+1

        .extern PR2
        .equiv  PR2L, _PR2
        .equiv  PR2H, _PR2+1

        .extern PR3
        .equiv  PR3L, _PR3
        .equiv  PR3H, _PR3+1

        .extern T2CON
        .equiv  T2CONL, _T2CON
        .equiv  T2CONH, _T2CON+1

        .extern T3CON
        .equiv  T3CONL, _T3CON
        .equiv  T3CONH, _T3CON+1

        .extern TMR4
        .equiv  TMR4L, _TMR4
        .equiv  TMR4H, _TMR4+1

        .extern TMR5HLD
        .equiv  TMR5HLDL, _TMR5HLD
        .equiv  TMR5HLDH, _TMR5HLD+1

        .extern TMR5
        .equiv  TMR5L, _TMR5
        .equiv  TMR5H, _TMR5+1

        .extern PR4
        .equiv  PR4L, _PR4
        .equiv  PR4H, _PR4+1

        .extern PR5
        .equiv  PR5L, _PR5
        .equiv  PR5H, _PR5+1

        .extern T4CON
        .equiv  T4CONL, _T4CON
        .equiv  T4CONH, _T4CON+1

        .extern T5CON
        .equiv  T5CONL, _T5CON
        .equiv  T5CONH, _T5CON+1

        .extern IC1BUF
        .equiv  IC1BUFL, _IC1BUF
        .equiv  IC1BUFH, _IC1BUF+1

        .extern IC1CON
        .equiv  IC1CONL, _IC1CON
        .equiv  IC1CONH, _IC1CON+1

        .extern IC2BUF
        .equiv  IC2BUFL, _IC2BUF
        .equiv  IC2BUFH, _IC2BUF+1

        .extern IC2CON
        .equiv  IC2CONL, _IC2CON
        .equiv  IC2CONH, _IC2CON+1

        .extern IC7BUF
        .equiv  IC7BUFL, _IC7BUF
        .equiv  IC7BUFH, _IC7BUF+1

        .extern IC7CON
        .equiv  IC7CONL, _IC7CON
        .equiv  IC7CONH, _IC7CON+1

        .extern IC8BUF
        .equiv  IC8BUFL, _IC8BUF
        .equiv  IC8BUFH, _IC8BUF+1

        .extern IC8CON
        .equiv  IC8CONL, _IC8CON
        .equiv  IC8CONH, _IC8CON+1

        .extern OC1RS
        .equiv  OC1RSL, _OC1RS
        .equiv  OC1RSH, _OC1RS+1

        .extern OC1R
        .equiv  OC1RL, _OC1R
        .equiv  OC1RH, _OC1R+1

        .extern OC1CON
        .equiv  OC1CONL, _OC1CON
        .equiv  OC1CONH, _OC1CON+1

        .extern OC2RS
        .equiv  OC2RSL, _OC2RS
        .equiv  OC2RSH, _OC2RS+1

        .extern OC2R
        .equiv  OC2RL, _OC2R
        .equiv  OC2RH, _OC2R+1

        .extern OC2CON
        .equiv  OC2CONL, _OC2CON
        .equiv  OC2CONH, _OC2CON+1

        .extern OC3RS
        .equiv  OC3RSL, _OC3RS
        .equiv  OC3RSH, _OC3RS+1

        .extern OC3R
        .equiv  OC3RL, _OC3R
        .equiv  OC3RH, _OC3R+1

        .extern OC3CON
        .equiv  OC3CONL, _OC3CON
        .equiv  OC3CONH, _OC3CON+1

        .extern OC4RS
        .equiv  OC4RSL, _OC4RS
        .equiv  OC4RSH, _OC4RS+1

        .extern OC4R
        .equiv  OC4RL, _OC4R
        .equiv  OC4RH, _OC4R+1

        .extern OC4CON
        .equiv  OC4CONL, _OC4CON
        .equiv  OC4CONH, _OC4CON+1

        .extern P1TCON
        .equiv  P1TCONL, _P1TCON
        .equiv  P1TCONH, _P1TCON+1

        .extern PTCON
        .equiv  PTCONL, _PTCON
        .equiv  PTCONH, _PTCON+1

        .extern P1TMR
        .equiv  P1TMRL, _P1TMR
        .equiv  P1TMRH, _P1TMR+1

        .extern PTMR
        .equiv  PTMRL, _PTMR
        .equiv  PTMRH, _PTMR+1

        .extern P1TPER
        .equiv  P1TPERL, _P1TPER
        .equiv  P1TPERH, _P1TPER+1

        .extern PTPER
        .equiv  PTPERL, _PTPER
        .equiv  PTPERH, _PTPER+1

        .extern P1SECMP
        .equiv  P1SECMPL, _P1SECMP
        .equiv  P1SECMPH, _P1SECMP+1

        .extern SEVTCMP
        .equiv  SEVTCMPL, _SEVTCMP
        .equiv  SEVTCMPH, _SEVTCMP+1

        .extern PWM1CON1
        .equiv  PWM1CON1L, _PWM1CON1
        .equiv  PWM1CON1H, _PWM1CON1+1

        .extern PWMCON1
        .equiv  PWMCON1L, _PWMCON1
        .equiv  PWMCON1H, _PWMCON1+1

        .extern PWM1CON2
        .equiv  PWM1CON2L, _PWM1CON2
        .equiv  PWM1CON2H, _PWM1CON2+1

        .extern PWMCON2
        .equiv  PWMCON2L, _PWMCON2
        .equiv  PWMCON2H, _PWMCON2+1

        .extern DTCON1
        .equiv  DTCON1L, _DTCON1
        .equiv  DTCON1H, _DTCON1+1

        .extern P1DTCON1
        .equiv  P1DTCON1L, _P1DTCON1
        .equiv  P1DTCON1H, _P1DTCON1+1

        .extern DTCON2
        .equiv  DTCON2L, _DTCON2
        .equiv  DTCON2H, _DTCON2+1

        .extern P1DTCON2
        .equiv  P1DTCON2L, _P1DTCON2
        .equiv  P1DTCON2H, _P1DTCON2+1

        .extern FLTACON
        .equiv  FLTACONL, _FLTACON
        .equiv  FLTACONH, _FLTACON+1

        .extern P1FLTACON
        .equiv  P1FLTACONL, _P1FLTACON
        .equiv  P1FLTACONH, _P1FLTACON+1

        .extern OVDCON
        .equiv  OVDCONL, _OVDCON
        .equiv  OVDCONH, _OVDCON+1

        .extern P1OVDCON
        .equiv  P1OVDCONL, _P1OVDCON
        .equiv  P1OVDCONH, _P1OVDCON+1

        .extern P1DC1
        .equiv  P1DC1L, _P1DC1
        .equiv  P1DC1H, _P1DC1+1

        .extern PDC1
        .equiv  PDC1L, _PDC1
        .equiv  PDC1H, _PDC1+1

        .extern P1DC2
        .equiv  P1DC2L, _P1DC2
        .equiv  P1DC2H, _P1DC2+1

        .extern PDC2
        .equiv  PDC2L, _PDC2
        .equiv  PDC2H, _PDC2+1

        .extern P1DC3
        .equiv  P1DC3L, _P1DC3
        .equiv  P1DC3H, _P1DC3+1

        .extern PDC3
        .equiv  PDC3L, _PDC3
        .equiv  PDC3H, _PDC3+1

        .extern QEI1CON
        .equiv  QEI1CONL, _QEI1CON
        .equiv  QEI1CONH, _QEI1CON+1

        .extern QEICON
        .equiv  QEICONL, _QEICON
        .equiv  QEICONH, _QEICON+1

        .extern DFLT1CON
        .equiv  DFLT1CONL, _DFLT1CON
        .equiv  DFLT1CONH, _DFLT1CON+1

        .extern DFLTCON
        .equiv  DFLTCONL, _DFLTCON
        .equiv  DFLTCONH, _DFLTCON+1

        .extern POS1CNT
        .equiv  POS1CNTL, _POS1CNT
        .equiv  POS1CNTH, _POS1CNT+1

        .extern POSCNT
        .equiv  POSCNTL, _POSCNT
        .equiv  POSCNTH, _POSCNT+1

        .extern MAX1CNT
        .equiv  MAX1CNTL, _MAX1CNT
        .equiv  MAX1CNTH, _MAX1CNT+1

        .extern MAXCNT
        .equiv  MAXCNTL, _MAXCNT
        .equiv  MAXCNTH, _MAXCNT+1

        .extern QEI2CON
        .equiv  QEI2CONL, _QEI2CON
        .equiv  QEI2CONH, _QEI2CON+1

        .extern DFLT2CON
        .equiv  DFLT2CONL, _DFLT2CON
        .equiv  DFLT2CONH, _DFLT2CON+1

        .extern POS2CNT
        .equiv  POS2CNTL, _POS2CNT
        .equiv  POS2CNTH, _POS2CNT+1

        .extern MAX2CNT
        .equiv  MAX2CNTL, _MAX2CNT
        .equiv  MAX2CNTH, _MAX2CNT+1

        .extern I2C1RCV
        .equiv  I2C1RCVL, _I2C1RCV
        .equiv  I2C1RCVH, _I2C1RCV+1

        .extern I2CRCV
        .equiv  I2CRCVL, _I2CRCV
        .equiv  I2CRCVH, _I2CRCV+1

        .extern I2C1TRN
        .equiv  I2C1TRNL, _I2C1TRN
        .equiv  I2C1TRNH, _I2C1TRN+1

        .extern I2CTRN
        .equiv  I2CTRNL, _I2CTRN
        .equiv  I2CTRNH, _I2CTRN+1

        .extern I2C1BRG
        .equiv  I2C1BRGL, _I2C1BRG
        .equiv  I2C1BRGH, _I2C1BRG+1

        .extern I2C1CON
        .equiv  I2C1CONL, _I2C1CON
        .equiv  I2C1CONH, _I2C1CON+1

        .extern I2CCON
        .equiv  I2CCONL, _I2CCON
        .equiv  I2CCONH, _I2CCON+1

        .extern I2C1STAT
        .equiv  I2C1STATL, _I2C1STAT
        .equiv  I2C1STATH, _I2C1STAT+1

        .extern I2CSTAT
        .equiv  I2CSTATL, _I2CSTAT
        .equiv  I2CSTATH, _I2CSTAT+1

        .extern I2C1ADD
        .equiv  I2C1ADDL, _I2C1ADD
        .equiv  I2C1ADDH, _I2C1ADD+1

        .extern I2CADD
        .equiv  I2CADDL, _I2CADD
        .equiv  I2CADDH, _I2CADD+1

        .extern I2C1MSK
        .equiv  I2C1MSKL, _I2C1MSK
        .equiv  I2C1MSKH, _I2C1MSK+1

        .extern U1MODE
        .equiv  U1MODEL, _U1MODE
        .equiv  U1MODEH, _U1MODE+1

        .extern U1STA
        .equiv  U1STAL, _U1STA
        .equiv  U1STAH, _U1STA+1

        .extern U1TXREG
        .equiv  U1TXREGL, _U1TXREG
        .equiv  U1TXREGH, _U1TXREG+1

        .extern U1RXREG
        .equiv  U1RXREGL, _U1RXREG
        .equiv  U1RXREGH, _U1RXREG+1

        .extern U1BRG
        .equiv  U1BRGL, _U1BRG
        .equiv  U1BRGH, _U1BRG+1

        .extern U2MODE
        .equiv  U2MODEL, _U2MODE
        .equiv  U2MODEH, _U2MODE+1

        .extern U2STA
        .equiv  U2STAL, _U2STA
        .equiv  U2STAH, _U2STA+1

        .extern U2TXREG
        .equiv  U2TXREGL, _U2TXREG
        .equiv  U2TXREGH, _U2TXREG+1

        .extern U2RXREG
        .equiv  U2RXREGL, _U2RXREG
        .equiv  U2RXREGH, _U2RXREG+1

        .extern U2BRG
        .equiv  U2BRGL, _U2BRG
        .equiv  U2BRGH, _U2BRG+1

        .extern SPI1STAT
        .equiv  SPI1STATL, _SPI1STAT
        .equiv  SPI1STATH, _SPI1STAT+1

        .extern SPI1CON1
        .equiv  SPI1CON1L, _SPI1CON1
        .equiv  SPI1CON1H, _SPI1CON1+1

        .extern SPI1CON2
        .equiv  SPI1CON2L, _SPI1CON2
        .equiv  SPI1CON2H, _SPI1CON2+1

        .extern SPI1BUF
        .equiv  SPI1BUFL, _SPI1BUF
        .equiv  SPI1BUFH, _SPI1BUF+1

        .extern SPI2STAT
        .equiv  SPI2STATL, _SPI2STAT
        .equiv  SPI2STATH, _SPI2STAT+1

        .extern SPI2CON1
        .equiv  SPI2CON1L, _SPI2CON1
        .equiv  SPI2CON1H, _SPI2CON1+1

        .extern SPI2CON2
        .equiv  SPI2CON2L, _SPI2CON2
        .equiv  SPI2CON2H, _SPI2CON2+1

        .extern SPI2BUF
        .equiv  SPI2BUFL, _SPI2BUF
        .equiv  SPI2BUFH, _SPI2BUF+1

        .extern TRISA
        .equiv  TRISAL, _TRISA
        .equiv  TRISAH, _TRISA+1

        .extern PORTA
        .equiv  PORTAL, _PORTA
        .equiv  PORTAH, _PORTA+1

        .extern LATA
        .equiv  LATAL, _LATA
        .equiv  LATAH, _LATA+1

        .extern ODCA
        .equiv  ODCAL, _ODCA
        .equiv  ODCAH, _ODCA+1

        .extern TRISB
        .equiv  TRISBL, _TRISB
        .equiv  TRISBH, _TRISB+1

        .extern PORTB
        .equiv  PORTBL, _PORTB
        .equiv  PORTBH, _PORTB+1

        .extern LATB
        .equiv  LATBL, _LATB
        .equiv  LATBH, _LATB+1

        .extern ODCB
        .equiv  ODCBL, _ODCB
        .equiv  ODCBH, _ODCB+1

        .extern PADCFG1
        .equiv  PADCFG1L, _PADCFG1
        .equiv  PADCFG1H, _PADCFG1+1

        .extern ADC1BUF0
        .equiv  ADC1BUF0L, _ADC1BUF0
        .equiv  ADC1BUF0H, _ADC1BUF0+1

        .extern ADCBUF0
        .equiv  ADCBUF0L, _ADCBUF0
        .equiv  ADCBUF0H, _ADCBUF0+1

        .extern AD1CON1
        .equiv  AD1CON1L, _AD1CON1
        .equiv  AD1CON1H, _AD1CON1+1

        .extern AD1CON2
        .equiv  AD1CON2L, _AD1CON2
        .equiv  AD1CON2H, _AD1CON2+1

        .extern AD1CON3
        .equiv  AD1CON3L, _AD1CON3
        .equiv  AD1CON3H, _AD1CON3+1

        .extern AD1CHS123
        .equiv  AD1CHS123L, _AD1CHS123
        .equiv  AD1CHS123H, _AD1CHS123+1

        .extern AD1CHS0
        .equiv  AD1CHS0L, _AD1CHS0
        .equiv  AD1CHS0H, _AD1CHS0+1

        .extern AD1PCFGL
        .equiv  AD1PCFGLL, _AD1PCFGL
        .equiv  AD1PCFGLH, _AD1PCFGL+1

        .extern ADPCFG
        .equiv  ADPCFGL, _ADPCFG
        .equiv  ADPCFGH, _ADPCFG+1

        .extern AD1CSSL
        .equiv  AD1CSSLL, _AD1CSSL
        .equiv  AD1CSSLH, _AD1CSSL+1

        .extern AD1CON4
        .equiv  AD1CON4L, _AD1CON4
        .equiv  AD1CON4H, _AD1CON4+1

        .extern DMA0CON
        .equiv  DMA0CONL, _DMA0CON
        .equiv  DMA0CONH, _DMA0CON+1

        .extern DMA0REQ
        .equiv  DMA0REQL, _DMA0REQ
        .equiv  DMA0REQH, _DMA0REQ+1

        .extern DMA0STA
        .equiv  DMA0STAL, _DMA0STA
        .equiv  DMA0STAH, _DMA0STA+1

        .extern DMA0STB
        .equiv  DMA0STBL, _DMA0STB
        .equiv  DMA0STBH, _DMA0STB+1

        .extern DMA0PAD
        .equiv  DMA0PADL, _DMA0PAD
        .equiv  DMA0PADH, _DMA0PAD+1

        .extern DMA0CNT
        .equiv  DMA0CNTL, _DMA0CNT
        .equiv  DMA0CNTH, _DMA0CNT+1

        .extern DMA1CON
        .equiv  DMA1CONL, _DMA1CON
        .equiv  DMA1CONH, _DMA1CON+1

        .extern DMA1REQ
        .equiv  DMA1REQL, _DMA1REQ
        .equiv  DMA1REQH, _DMA1REQ+1

        .extern DMA1STA
        .equiv  DMA1STAL, _DMA1STA
        .equiv  DMA1STAH, _DMA1STA+1

        .extern DMA1STB
        .equiv  DMA1STBL, _DMA1STB
        .equiv  DMA1STBH, _DMA1STB+1

        .extern DMA1PAD
        .equiv  DMA1PADL, _DMA1PAD
        .equiv  DMA1PADH, _DMA1PAD+1

        .extern DMA1CNT
        .equiv  DMA1CNTL, _DMA1CNT
        .equiv  DMA1CNTH, _DMA1CNT+1

        .extern DMA2CON
        .equiv  DMA2CONL, _DMA2CON
        .equiv  DMA2CONH, _DMA2CON+1

        .extern DMA2REQ
        .equiv  DMA2REQL, _DMA2REQ
        .equiv  DMA2REQH, _DMA2REQ+1

        .extern DMA2STA
        .equiv  DMA2STAL, _DMA2STA
        .equiv  DMA2STAH, _DMA2STA+1

        .extern DMA2STB
        .equiv  DMA2STBL, _DMA2STB
        .equiv  DMA2STBH, _DMA2STB+1

        .extern DMA2PAD
        .equiv  DMA2PADL, _DMA2PAD
        .equiv  DMA2PADH, _DMA2PAD+1

        .extern DMA2CNT
        .equiv  DMA2CNTL, _DMA2CNT
        .equiv  DMA2CNTH, _DMA2CNT+1

        .extern DMA3CON
        .equiv  DMA3CONL, _DMA3CON
        .equiv  DMA3CONH, _DMA3CON+1

        .extern DMA3REQ
        .equiv  DMA3REQL, _DMA3REQ
        .equiv  DMA3REQH, _DMA3REQ+1

        .extern DMA3STA
        .equiv  DMA3STAL, _DMA3STA
        .equiv  DMA3STAH, _DMA3STA+1

        .extern DMA3STB
        .equiv  DMA3STBL, _DMA3STB
        .equiv  DMA3STBH, _DMA3STB+1

        .extern DMA3PAD
        .equiv  DMA3PADL, _DMA3PAD
        .equiv  DMA3PADH, _DMA3PAD+1

        .extern DMA3CNT
        .equiv  DMA3CNTL, _DMA3CNT
        .equiv  DMA3CNTH, _DMA3CNT+1

        .extern DMA4CON
        .equiv  DMA4CONL, _DMA4CON
        .equiv  DMA4CONH, _DMA4CON+1

        .extern DMA4REQ
        .equiv  DMA4REQL, _DMA4REQ
        .equiv  DMA4REQH, _DMA4REQ+1

        .extern DMA4STA
        .equiv  DMA4STAL, _DMA4STA
        .equiv  DMA4STAH, _DMA4STA+1

        .extern DMA4STB
        .equiv  DMA4STBL, _DMA4STB
        .equiv  DMA4STBH, _DMA4STB+1

        .extern DMA4PAD
        .equiv  DMA4PADL, _DMA4PAD
        .equiv  DMA4PADH, _DMA4PAD+1

        .extern DMA4CNT
        .equiv  DMA4CNTL, _DMA4CNT
        .equiv  DMA4CNTH, _DMA4CNT+1

        .extern DMA5CON
        .equiv  DMA5CONL, _DMA5CON
        .equiv  DMA5CONH, _DMA5CON+1

        .extern DMA5REQ
        .equiv  DMA5REQL, _DMA5REQ
        .equiv  DMA5REQH, _DMA5REQ+1

        .extern DMA5STA
        .equiv  DMA5STAL, _DMA5STA
        .equiv  DMA5STAH, _DMA5STA+1

        .extern DMA5STB
        .equiv  DMA5STBL, _DMA5STB
        .equiv  DMA5STBH, _DMA5STB+1

        .extern DMA5PAD
        .equiv  DMA5PADL, _DMA5PAD
        .equiv  DMA5PADH, _DMA5PAD+1

        .extern DMA5CNT
        .equiv  DMA5CNTL, _DMA5CNT
        .equiv  DMA5CNTH, _DMA5CNT+1

        .extern DMA6CON
        .equiv  DMA6CONL, _DMA6CON
        .equiv  DMA6CONH, _DMA6CON+1

        .extern DMA6REQ
        .equiv  DMA6REQL, _DMA6REQ
        .equiv  DMA6REQH, _DMA6REQ+1

        .extern DMA6STA
        .equiv  DMA6STAL, _DMA6STA
        .equiv  DMA6STAH, _DMA6STA+1

        .extern DMA6STB
        .equiv  DMA6STBL, _DMA6STB
        .equiv  DMA6STBH, _DMA6STB+1

        .extern DMA6PAD
        .equiv  DMA6PADL, _DMA6PAD
        .equiv  DMA6PADH, _DMA6PAD+1

        .extern DMA6CNT
        .equiv  DMA6CNTL, _DMA6CNT
        .equiv  DMA6CNTH, _DMA6CNT+1

        .extern DMA7CON
        .equiv  DMA7CONL, _DMA7CON
        .equiv  DMA7CONH, _DMA7CON+1

        .extern DMA7REQ
        .equiv  DMA7REQL, _DMA7REQ
        .equiv  DMA7REQH, _DMA7REQ+1

        .extern DMA7STA
        .equiv  DMA7STAL, _DMA7STA
        .equiv  DMA7STAH, _DMA7STA+1

        .extern DMA7STB
        .equiv  DMA7STBL, _DMA7STB
        .equiv  DMA7STBH, _DMA7STB+1

        .extern DMA7PAD
        .equiv  DMA7PADL, _DMA7PAD
        .equiv  DMA7PADH, _DMA7PAD+1

        .extern DMA7CNT
        .equiv  DMA7CNTL, _DMA7CNT
        .equiv  DMA7CNTH, _DMA7CNT+1

        .extern DMACS0
        .equiv  DMACS0L, _DMACS0
        .equiv  DMACS0H, _DMACS0+1

        .extern DMACS1
        .equiv  DMACS1L, _DMACS1
        .equiv  DMACS1H, _DMACS1+1

        .extern DSADR
        .equiv  DSADRL, _DSADR
        .equiv  DSADRH, _DSADR+1

        .extern C1CTRL1
        .equiv  C1CTRL1L, _C1CTRL1
        .equiv  C1CTRL1H, _C1CTRL1+1

        .extern C1CTRL2
        .equiv  C1CTRL2L, _C1CTRL2
        .equiv  C1CTRL2H, _C1CTRL2+1

        .extern C1VEC
        .equiv  C1VECL, _C1VEC
        .equiv  C1VECH, _C1VEC+1

        .extern C1FCTRL
        .equiv  C1FCTRLL, _C1FCTRL
        .equiv  C1FCTRLH, _C1FCTRL+1

        .extern C1FIFO
        .equiv  C1FIFOL, _C1FIFO
        .equiv  C1FIFOH, _C1FIFO+1

        .extern C1INTF
        .equiv  C1INTFL, _C1INTF
        .equiv  C1INTFH, _C1INTF+1

        .extern C1INTE
        .equiv  C1INTEL, _C1INTE
        .equiv  C1INTEH, _C1INTE+1

        .extern C1EC
        .equiv  C1ECL, _C1EC
        .equiv  C1ECH, _C1EC+1

        .extern C1RERRCNT
        .equiv  C1RERRCNTL, _C1RERRCNT
        .equiv  C1RERRCNTH, _C1RERRCNT+1

        .extern C1TERRCNT
        .equiv  C1TERRCNTL, _C1TERRCNT
        .equiv  C1TERRCNTH, _C1TERRCNT+1

        .extern C1CFG1
        .equiv  C1CFG1L, _C1CFG1
        .equiv  C1CFG1H, _C1CFG1+1

        .extern C1CFG2
        .equiv  C1CFG2L, _C1CFG2
        .equiv  C1CFG2H, _C1CFG2+1

        .extern C1FEN1
        .equiv  C1FEN1L, _C1FEN1
        .equiv  C1FEN1H, _C1FEN1+1

        .extern C1FMSKSEL1
        .equiv  C1FMSKSEL1L, _C1FMSKSEL1
        .equiv  C1FMSKSEL1H, _C1FMSKSEL1+1

        .extern C1FMSKSEL2
        .equiv  C1FMSKSEL2L, _C1FMSKSEL2
        .equiv  C1FMSKSEL2H, _C1FMSKSEL2+1

        .extern C1BUFPNT1
        .equiv  C1BUFPNT1L, _C1BUFPNT1
        .equiv  C1BUFPNT1H, _C1BUFPNT1+1

        .extern C1RXFUL1
        .equiv  C1RXFUL1L, _C1RXFUL1
        .equiv  C1RXFUL1H, _C1RXFUL1+1

        .extern C1BUFPNT2
        .equiv  C1BUFPNT2L, _C1BUFPNT2
        .equiv  C1BUFPNT2H, _C1BUFPNT2+1

        .extern C1RXFUL2
        .equiv  C1RXFUL2L, _C1RXFUL2
        .equiv  C1RXFUL2H, _C1RXFUL2+1

        .extern C1BUFPNT3
        .equiv  C1BUFPNT3L, _C1BUFPNT3
        .equiv  C1BUFPNT3H, _C1BUFPNT3+1

        .extern C1BUFPNT4
        .equiv  C1BUFPNT4L, _C1BUFPNT4
        .equiv  C1BUFPNT4H, _C1BUFPNT4+1

        .extern C1RXOVF1
        .equiv  C1RXOVF1L, _C1RXOVF1
        .equiv  C1RXOVF1H, _C1RXOVF1+1

        .extern C1RXOVF2
        .equiv  C1RXOVF2L, _C1RXOVF2
        .equiv  C1RXOVF2H, _C1RXOVF2+1

        .extern C1RXM0SID
        .equiv  C1RXM0SIDL, _C1RXM0SID
        .equiv  C1RXM0SIDH, _C1RXM0SID+1

        .extern C1TR01CON
        .equiv  C1TR01CONL, _C1TR01CON
        .equiv  C1TR01CONH, _C1TR01CON+1

        .extern C1RXM0EID
        .equiv  C1RXM0EIDL, _C1RXM0EID
        .equiv  C1RXM0EIDH, _C1RXM0EID+1

        .extern C1TR23CON
        .equiv  C1TR23CONL, _C1TR23CON
        .equiv  C1TR23CONH, _C1TR23CON+1

        .extern C1RXM1SID
        .equiv  C1RXM1SIDL, _C1RXM1SID
        .equiv  C1RXM1SIDH, _C1RXM1SID+1

        .extern C1TR45CON
        .equiv  C1TR45CONL, _C1TR45CON
        .equiv  C1TR45CONH, _C1TR45CON+1

        .extern C1RXM1EID
        .equiv  C1RXM1EIDL, _C1RXM1EID
        .equiv  C1RXM1EIDH, _C1RXM1EID+1

        .extern C1TR67CON
        .equiv  C1TR67CONL, _C1TR67CON
        .equiv  C1TR67CONH, _C1TR67CON+1

        .extern C1RXM2SID
        .equiv  C1RXM2SIDL, _C1RXM2SID
        .equiv  C1RXM2SIDH, _C1RXM2SID+1

        .extern C1RXM2EID
        .equiv  C1RXM2EIDL, _C1RXM2EID
        .equiv  C1RXM2EIDH, _C1RXM2EID+1

        .extern C1RXD
        .equiv  C1RXDL, _C1RXD
        .equiv  C1RXDH, _C1RXD+1

        .extern C1RXF0SID
        .equiv  C1RXF0SIDL, _C1RXF0SID
        .equiv  C1RXF0SIDH, _C1RXF0SID+1

        .extern C1RXF0EID
        .equiv  C1RXF0EIDL, _C1RXF0EID
        .equiv  C1RXF0EIDH, _C1RXF0EID+1

        .extern C1TXD
        .equiv  C1TXDL, _C1TXD
        .equiv  C1TXDH, _C1TXD+1

        .extern C1RXF1SID
        .equiv  C1RXF1SIDL, _C1RXF1SID
        .equiv  C1RXF1SIDH, _C1RXF1SID+1

        .extern C1RXF1EID
        .equiv  C1RXF1EIDL, _C1RXF1EID
        .equiv  C1RXF1EIDH, _C1RXF1EID+1

        .extern C1RXF2SID
        .equiv  C1RXF2SIDL, _C1RXF2SID
        .equiv  C1RXF2SIDH, _C1RXF2SID+1

        .extern C1RXF2EID
        .equiv  C1RXF2EIDL, _C1RXF2EID
        .equiv  C1RXF2EIDH, _C1RXF2EID+1

        .extern C1RXF3SID
        .equiv  C1RXF3SIDL, _C1RXF3SID
        .equiv  C1RXF3SIDH, _C1RXF3SID+1

        .extern C1RXF3EID
        .equiv  C1RXF3EIDL, _C1RXF3EID
        .equiv  C1RXF3EIDH, _C1RXF3EID+1

        .extern C1RXF4SID
        .equiv  C1RXF4SIDL, _C1RXF4SID
        .equiv  C1RXF4SIDH, _C1RXF4SID+1

        .extern C1RXF4EID
        .equiv  C1RXF4EIDL, _C1RXF4EID
        .equiv  C1RXF4EIDH, _C1RXF4EID+1

        .extern C1RXF5SID
        .equiv  C1RXF5SIDL, _C1RXF5SID
        .equiv  C1RXF5SIDH, _C1RXF5SID+1

        .extern C1RXF5EID
        .equiv  C1RXF5EIDL, _C1RXF5EID
        .equiv  C1RXF5EIDH, _C1RXF5EID+1

        .extern C1RXF6SID
        .equiv  C1RXF6SIDL, _C1RXF6SID
        .equiv  C1RXF6SIDH, _C1RXF6SID+1

        .extern C1RXF6EID
        .equiv  C1RXF6EIDL, _C1RXF6EID
        .equiv  C1RXF6EIDH, _C1RXF6EID+1

        .extern C1RXF7SID
        .equiv  C1RXF7SIDL, _C1RXF7SID
        .equiv  C1RXF7SIDH, _C1RXF7SID+1

        .extern C1RXF7EID
        .equiv  C1RXF7EIDL, _C1RXF7EID
        .equiv  C1RXF7EIDH, _C1RXF7EID+1

        .extern C1RXF8SID
        .equiv  C1RXF8SIDL, _C1RXF8SID
        .equiv  C1RXF8SIDH, _C1RXF8SID+1

        .extern C1RXF8EID
        .equiv  C1RXF8EIDL, _C1RXF8EID
        .equiv  C1RXF8EIDH, _C1RXF8EID+1

        .extern C1RXF9SID
        .equiv  C1RXF9SIDL, _C1RXF9SID
        .equiv  C1RXF9SIDH, _C1RXF9SID+1

        .extern C1RXF9EID
        .equiv  C1RXF9EIDL, _C1RXF9EID
        .equiv  C1RXF9EIDH, _C1RXF9EID+1

        .extern C1RXF10SID
        .equiv  C1RXF10SIDL, _C1RXF10SID
        .equiv  C1RXF10SIDH, _C1RXF10SID+1

        .extern C1RXF10EID
        .equiv  C1RXF10EIDL, _C1RXF10EID
        .equiv  C1RXF10EIDH, _C1RXF10EID+1

        .extern C1RXF11SID
        .equiv  C1RXF11SIDL, _C1RXF11SID
        .equiv  C1RXF11SIDH, _C1RXF11SID+1

        .extern C1RXF11EID
        .equiv  C1RXF11EIDL, _C1RXF11EID
        .equiv  C1RXF11EIDH, _C1RXF11EID+1

        .extern C1RXF12SID
        .equiv  C1RXF12SIDL, _C1RXF12SID
        .equiv  C1RXF12SIDH, _C1RXF12SID+1

        .extern C1RXF12EID
        .equiv  C1RXF12EIDL, _C1RXF12EID
        .equiv  C1RXF12EIDH, _C1RXF12EID+1

        .extern C1RXF13SID
        .equiv  C1RXF13SIDL, _C1RXF13SID
        .equiv  C1RXF13SIDH, _C1RXF13SID+1

        .extern C1RXF13EID
        .equiv  C1RXF13EIDL, _C1RXF13EID
        .equiv  C1RXF13EIDH, _C1RXF13EID+1

        .extern C1RXF14SID
        .equiv  C1RXF14SIDL, _C1RXF14SID
        .equiv  C1RXF14SIDH, _C1RXF14SID+1

        .extern C1RXF14EID
        .equiv  C1RXF14EIDL, _C1RXF14EID
        .equiv  C1RXF14EIDH, _C1RXF14EID+1

        .extern C1RXF15SID
        .equiv  C1RXF15SIDL, _C1RXF15SID
        .equiv  C1RXF15SIDH, _C1RXF15SID+1

        .extern C1RXF15EID
        .equiv  C1RXF15EIDL, _C1RXF15EID
        .equiv  C1RXF15EIDH, _C1RXF15EID+1

        .extern P2TCON
        .equiv  P2TCONL, _P2TCON
        .equiv  P2TCONH, _P2TCON+1

        .extern P2TMR
        .equiv  P2TMRL, _P2TMR
        .equiv  P2TMRH, _P2TMR+1

        .extern P2TPER
        .equiv  P2TPERL, _P2TPER
        .equiv  P2TPERH, _P2TPER+1

        .extern P2SECMP
        .equiv  P2SECMPL, _P2SECMP
        .equiv  P2SECMPH, _P2SECMP+1

        .extern PWM2CON1
        .equiv  PWM2CON1L, _PWM2CON1
        .equiv  PWM2CON1H, _PWM2CON1+1

        .extern PWM2CON2
        .equiv  PWM2CON2L, _PWM2CON2
        .equiv  PWM2CON2H, _PWM2CON2+1

        .extern P2DTCON1
        .equiv  P2DTCON1L, _P2DTCON1
        .equiv  P2DTCON1H, _P2DTCON1+1

        .extern P2DTCON2
        .equiv  P2DTCON2L, _P2DTCON2
        .equiv  P2DTCON2H, _P2DTCON2+1

        .extern P2FLTACON
        .equiv  P2FLTACONL, _P2FLTACON
        .equiv  P2FLTACONH, _P2FLTACON+1

        .extern P2OVDCON
        .equiv  P2OVDCONL, _P2OVDCON
        .equiv  P2OVDCONH, _P2OVDCON+1

        .extern P2DC1
        .equiv  P2DC1L, _P2DC1
        .equiv  P2DC1H, _P2DC1+1

        .extern PMCON
        .equiv  PMCONL, _PMCON
        .equiv  PMCONH, _PMCON+1

        .extern PMMODE
        .equiv  PMMODEL, _PMMODE
        .equiv  PMMODEH, _PMMODE+1

        .extern PMADDR
        .equiv  PMADDRL, _PMADDR
        .equiv  PMADDRH, _PMADDR+1

        .extern PMDOUT1
        .equiv  PMDOUT1L, _PMDOUT1
        .equiv  PMDOUT1H, _PMDOUT1+1

        .extern PMDOUT2
        .equiv  PMDOUT2L, _PMDOUT2
        .equiv  PMDOUT2H, _PMDOUT2+1

        .extern PMDIN1
        .equiv  PMDIN1L, _PMDIN1
        .equiv  PMDIN1H, _PMDIN1+1

        .extern PMDIN2
        .equiv  PMDIN2L, _PMDIN2
        .equiv  PMDIN2H, _PMDIN2+1

        .extern PMAEN
        .equiv  PMAENL, _PMAEN
        .equiv  PMAENH, _PMAEN+1

        .extern PMSTAT
        .equiv  PMSTATL, _PMSTAT
        .equiv  PMSTATH, _PMSTAT+1

        .extern ALRMVAL
        .equiv  ALRMVALL, _ALRMVAL
        .equiv  ALRMVALH, _ALRMVAL+1

        .extern ALCFGRPT
        .equiv  ALCFGRPTL, _ALCFGRPT
        .equiv  ALCFGRPTH, _ALCFGRPT+1

        .extern RTCVAL
        .equiv  RTCVALL, _RTCVAL
        .equiv  RTCVALH, _RTCVAL+1

        .extern RCFGCAL
        .equiv  RCFGCALL, _RCFGCAL
        .equiv  RCFGCALH, _RCFGCAL+1

        .extern CMCON
        .equiv  CMCONL, _CMCON
        .equiv  CMCONH, _CMCON+1

        .extern CVRCON
        .equiv  CVRCONL, _CVRCON
        .equiv  CVRCONH, _CVRCON+1

        .extern CRCCON
        .equiv  CRCCONL, _CRCCON
        .equiv  CRCCONH, _CRCCON+1

        .extern CRCXOR
        .equiv  CRCXORL, _CRCXOR
        .equiv  CRCXORH, _CRCXOR+1

        .extern CRCDAT
        .equiv  CRCDATL, _CRCDAT
        .equiv  CRCDATH, _CRCDAT+1

        .extern CRCWDAT
        .equiv  CRCWDATL, _CRCWDAT
        .equiv  CRCWDATH, _CRCWDAT+1

        .extern RPINR0
        .equiv  RPINR0L, _RPINR0
        .equiv  RPINR0H, _RPINR0+1

        .extern RPINR1
        .equiv  RPINR1L, _RPINR1
        .equiv  RPINR1H, _RPINR1+1

        .extern RPINR3
        .equiv  RPINR3L, _RPINR3
        .equiv  RPINR3H, _RPINR3+1

        .extern RPINR4
        .equiv  RPINR4L, _RPINR4
        .equiv  RPINR4H, _RPINR4+1

        .extern RPINR7
        .equiv  RPINR7L, _RPINR7
        .equiv  RPINR7H, _RPINR7+1

        .extern RPINR10
        .equiv  RPINR10L, _RPINR10
        .equiv  RPINR10H, _RPINR10+1

        .extern RPINR11
        .equiv  RPINR11L, _RPINR11
        .equiv  RPINR11H, _RPINR11+1

        .extern RPINR12
        .equiv  RPINR12L, _RPINR12
        .equiv  RPINR12H, _RPINR12+1

        .extern RPINR13
        .equiv  RPINR13L, _RPINR13
        .equiv  RPINR13H, _RPINR13+1

        .extern RPINR14
        .equiv  RPINR14L, _RPINR14
        .equiv  RPINR14H, _RPINR14+1

        .extern RPINR15
        .equiv  RPINR15L, _RPINR15
        .equiv  RPINR15H, _RPINR15+1

        .extern RPINR16
        .equiv  RPINR16L, _RPINR16
        .equiv  RPINR16H, _RPINR16+1

        .extern RPINR17
        .equiv  RPINR17L, _RPINR17
        .equiv  RPINR17H, _RPINR17+1

        .extern RPINR18
        .equiv  RPINR18L, _RPINR18
        .equiv  RPINR18H, _RPINR18+1

        .extern RPINR19
        .equiv  RPINR19L, _RPINR19
        .equiv  RPINR19H, _RPINR19+1

        .extern RPINR20
        .equiv  RPINR20L, _RPINR20
        .equiv  RPINR20H, _RPINR20+1

        .extern RPINR21
        .equiv  RPINR21L, _RPINR21
        .equiv  RPINR21H, _RPINR21+1

        .extern RPINR22
        .equiv  RPINR22L, _RPINR22
        .equiv  RPINR22H, _RPINR22+1

        .extern RPINR23
        .equiv  RPINR23L, _RPINR23
        .equiv  RPINR23H, _RPINR23+1

        .extern RPINR26
        .equiv  RPINR26L, _RPINR26
        .equiv  RPINR26H, _RPINR26+1

        .extern RPOR0
        .equiv  RPOR0L, _RPOR0
        .equiv  RPOR0H, _RPOR0+1

        .extern RPOR1
        .equiv  RPOR1L, _RPOR1
        .equiv  RPOR1H, _RPOR1+1

        .extern RPOR2
        .equiv  RPOR2L, _RPOR2
        .equiv  RPOR2H, _RPOR2+1

        .extern RPOR3
        .equiv  RPOR3L, _RPOR3
        .equiv  RPOR3H, _RPOR3+1

        .extern RPOR4
        .equiv  RPOR4L, _RPOR4
        .equiv  RPOR4H, _RPOR4+1

        .extern RPOR5
        .equiv  RPOR5L, _RPOR5
        .equiv  RPOR5H, _RPOR5+1

        .extern RPOR6
        .equiv  RPOR6L, _RPOR6
        .equiv  RPOR6H, _RPOR6+1

        .extern RPOR7
        .equiv  RPOR7L, _RPOR7
        .equiv  RPOR7H, _RPOR7+1

        .extern RPOR8
        .equiv  RPOR8L, _RPOR8
        .equiv  RPOR8H, _RPOR8+1

        .extern RPOR9
        .equiv  RPOR9L, _RPOR9
        .equiv  RPOR9H, _RPOR9+1

        .extern RPOR10
        .equiv  RPOR10L, _RPOR10
        .equiv  RPOR10H, _RPOR10+1

        .extern RPOR11
        .equiv  RPOR11L, _RPOR11
        .equiv  RPOR11H, _RPOR11+1

        .extern RPOR12
        .equiv  RPOR12L, _RPOR12
        .equiv  RPOR12H, _RPOR12+1

        .extern RCON
        .equiv  RCONL, _RCON
        .equiv  RCONH, _RCON+1

        .extern OSCCON

        .extern OSCCONL
        .equiv  OSCCONLL, _OSCCONL
        .equiv  OSCCONLH, _OSCCONL+1

        .extern OSCCONH
        .equiv  OSCCONHL, _OSCCONH
        .equiv  OSCCONHH, _OSCCONH+1

        .extern CLKDIV
        .equiv  CLKDIVL, _CLKDIV
        .equiv  CLKDIVH, _CLKDIV+1

        .extern PLLFBD
        .equiv  PLLFBDL, _PLLFBD
        .equiv  PLLFBDH, _PLLFBD+1

        .extern OSCTUN
        .equiv  OSCTUNL, _OSCTUN
        .equiv  OSCTUNH, _OSCTUN+1

        .extern ACLKCON
        .equiv  ACLKCONL, _ACLKCON
        .equiv  ACLKCONH, _ACLKCON+1

        .extern BSRAM
        .equiv  BSRAML, _BSRAM
        .equiv  BSRAMH, _BSRAM+1

        .extern SSRAM
        .equiv  SSRAML, _SSRAM
        .equiv  SSRAMH, _SSRAM+1

        .extern NVMCON
        .equiv  NVMCONL, _NVMCON
        .equiv  NVMCONH, _NVMCON+1

        .extern NVMKEY
        .equiv  NVMKEYL, _NVMKEY
        .equiv  NVMKEYH, _NVMKEY+1

        .extern PMD1
        .equiv  PMD1L, _PMD1
        .equiv  PMD1H, _PMD1+1

        .extern PMD2
        .equiv  PMD2L, _PMD2
        .equiv  PMD2H, _PMD2+1

        .extern PMD3
        .equiv  PMD3L, _PMD3
        .equiv  PMD3H, _PMD3+1

;----- SR Bits -----------------------------------------------------
        .equiv C,       0x0000
        .equiv Z,       0x0001
        .equiv OV,      0x0002
        .equiv N,       0x0003
        .equiv RA,      0x0004
        .equiv DC,      0x0008
        .equiv DA,      0x0009
        .equiv SAB,     0x000A
        .equiv OAB,     0x000B
        .equiv SB,      0x000C
        .equiv SA,      0x000D
        .equiv OB,      0x000E
        .equiv OA,      0x000F

        .equiv IPL0,    0x0005
        .equiv IPL1,    0x0006
        .equiv IPL2,    0x0007


;----- CORCON Bits -----------------------------------------------------
        .equiv IF,      0x0000
        .equiv RND,     0x0001
        .equiv PSV,     0x0002
        .equiv IPL3,    0x0003
        .equiv ACCSAT,  0x0004
        .equiv SATDW,   0x0005
        .equiv SATB,    0x0006
        .equiv SATA,    0x0007
        .equiv EDT,     0x000B
        .equiv US,      0x000C

        .equiv DL0,     0x0008
        .equiv DL1,     0x0009
        .equiv DL2,     0x000A


;----- MODCON Bits -----------------------------------------------------
        .equiv YMODEN,  0x000E
        .equiv XMODEN,  0x000F

        .equiv XWM0,    0x0000
        .equiv XWM1,    0x0001
        .equiv XWM2,    0x0002
        .equiv XWM3,    0x0003
        .equiv YWM0,    0x0004
        .equiv YWM1,    0x0005
        .equiv YWM2,    0x0006
        .equiv YWM3,    0x0007
        .equiv BWM0,    0x0008
        .equiv BWM1,    0x0009
        .equiv BWM2,    0x000A
        .equiv BWM3,    0x000B


;----- XBREV Bits -----------------------------------------------------
        .equiv BREN,    0x000F

        .equiv XB0,     0x0000
        .equiv XB1,     0x0001
        .equiv XB2,     0x0002
        .equiv XB3,     0x0003
        .equiv XB4,     0x0004
        .equiv XB5,     0x0005
        .equiv XB6,     0x0006
        .equiv XB7,     0x0007
        .equiv XB8,     0x0008
        .equiv XB9,     0x0009
        .equiv XB10,    0x000A
        .equiv XB11,    0x000B
        .equiv XB12,    0x000C
        .equiv XB13,    0x000D
        .equiv XB14,    0x000E


;----- CNEN1 Bits -----------------------------------------------------
        .equiv CN0IE,   0x0000
        .equiv CN1IE,   0x0001
        .equiv CN2IE,   0x0002
        .equiv CN3IE,   0x0003
        .equiv CN4IE,   0x0004
        .equiv CN5IE,   0x0005
        .equiv CN6IE,   0x0006
        .equiv CN7IE,   0x0007
        .equiv CN11IE,  0x000B
        .equiv CN12IE,  0x000C
        .equiv CN13IE,  0x000D
        .equiv CN14IE,  0x000E
        .equiv CN15IE,  0x000F


;----- CNEN2 Bits -----------------------------------------------------
        .equiv CN16IE,  0x0000
        .equiv CN21IE,  0x0005
        .equiv CN22IE,  0x0006
        .equiv CN23IE,  0x0007
        .equiv CN24IE,  0x0008
        .equiv CN27IE,  0x000B
        .equiv CN29IE,  0x000D
        .equiv CN30IE,  0x000E


;----- CNPU1 Bits -----------------------------------------------------
        .equiv CN0PUE,  0x0000
        .equiv CN1PUE,  0x0001
        .equiv CN2PUE,  0x0002
        .equiv CN3PUE,  0x0003
        .equiv CN4PUE,  0x0004
        .equiv CN5PUE,  0x0005
        .equiv CN6PUE,  0x0006
        .equiv CN7PUE,  0x0007
        .equiv CN11PUE, 0x000B
        .equiv CN12PUE, 0x000C
        .equiv CN13PUE, 0x000D
        .equiv CN14PUE, 0x000E
        .equiv CN15PUE, 0x000F


;----- CNPU2 Bits -----------------------------------------------------
        .equiv CN16PUE, 0x0000
        .equiv CN21PUE, 0x0005
        .equiv CN22PUE, 0x0006
        .equiv CN23PUE, 0x0007
        .equiv CN24PUE, 0x0008
        .equiv CN27PUE, 0x000B
        .equiv CN29PUE, 0x000D
        .equiv CN30PUE, 0x000E


;----- INTCON1 Bits -----------------------------------------------------
        .equiv OSCFAIL, 0x0001
        .equiv STKERR,  0x0002
        .equiv ADDRERR, 0x0003
        .equiv MATHERR, 0x0004
        .equiv DMACERR, 0x0005
        .equiv DIV0ERR, 0x0006
        .equiv SFTACERR, 0x0007
        .equiv COVTE,   0x0008
        .equiv OVBTE,   0x0009
        .equiv OVATE,   0x000A
        .equiv COVBERR, 0x000B
        .equiv COVAERR, 0x000C
        .equiv OVBERR,  0x000D
        .equiv OVAERR,  0x000E
        .equiv NSTDIS,  0x000F


;----- INTCON2 Bits -----------------------------------------------------
        .equiv INT0EP,  0x0000
        .equiv INT1EP,  0x0001
        .equiv INT2EP,  0x0002
        .equiv DISI,    0x000E
        .equiv ALTIVT,  0x000F


;----- IFS0 Bits -----------------------------------------------------
        .equiv INT0IF,  0x0000
        .equiv IC1IF,   0x0001
        .equiv OC1IF,   0x0002
        .equiv T1IF,    0x0003
        .equiv DMA0IF,  0x0004
        .equiv IC2IF,   0x0005
        .equiv OC2IF,   0x0006
        .equiv T2IF,    0x0007
        .equiv T3IF,    0x0008
        .equiv SPI1EIF, 0x0009
        .equiv SPI1IF,  0x000A
        .equiv U1RXIF,  0x000B
        .equiv U1TXIF,  0x000C
        .equiv AD1IF,   0x000D
        .equiv DMA1IF,  0x000E


;----- IFS1 Bits -----------------------------------------------------
        .equiv SI2C1IF, 0x0000
        .equiv MI2C1IF, 0x0001
        .equiv CMIF,    0x0002
        .equiv CNIF,    0x0003
        .equiv INT1IF,  0x0004
        .equiv IC7IF,   0x0006
        .equiv IC8IF,   0x0007
        .equiv DMA2IF,  0x0008
        .equiv OC3IF,   0x0009
        .equiv OC4IF,   0x000A
        .equiv T4IF,    0x000B
        .equiv T5IF,    0x000C
        .equiv INT2IF,  0x000D
        .equiv U2RXIF,  0x000E
        .equiv U2TXIF,  0x000F

        .equiv SI2CIF,  0x0000


;----- IFS2 Bits -----------------------------------------------------
        .equiv SPI2EIF, 0x0000
        .equiv SPI2IF,  0x0001
        .equiv C1RXIF,  0x0002
        .equiv C1IF,    0x0003
        .equiv DMA3IF,  0x0004
        .equiv PMPIF,   0x000D
        .equiv DMA4IF,  0x000E


;----- IFS3 Bits -----------------------------------------------------
        .equiv PWM1IF,  0x0009
        .equiv QEI1IF,  0x000A
        .equiv DMA5IF,  0x000D
        .equiv RTCIF,   0x000E
        .equiv FLTA1IF, 0x000F


;----- IFS4 Bits -----------------------------------------------------
        .equiv U1EIF,   0x0001
        .equiv U2EIF,   0x0002
        .equiv CRCIF,   0x0003
        .equiv DMA6IF,  0x0004
        .equiv DMA7IF,  0x0005
        .equiv C1TXIF,  0x0006
        .equiv PWM2IF,  0x0009
        .equiv FLTA2IF, 0x000A
        .equiv QEI2IF,  0x000B


;----- IEC0 Bits -----------------------------------------------------
        .equiv INT0IE,  0x0000
        .equiv IC1IE,   0x0001
        .equiv OC1IE,   0x0002
        .equiv T1IE,    0x0003
        .equiv DMA0IE,  0x0004
        .equiv IC2IE,   0x0005
        .equiv OC2IE,   0x0006
        .equiv T2IE,    0x0007
        .equiv T3IE,    0x0008
        .equiv SPI1EIE, 0x0009
        .equiv SPI1IE,  0x000A
        .equiv U1RXIE,  0x000B
        .equiv U1TXIE,  0x000C
        .equiv AD1IE,   0x000D
        .equiv DMA1IE,  0x000E


;----- IEC1 Bits -----------------------------------------------------
        .equiv SI2C1IE, 0x0000
        .equiv MI2C1IE, 0x0001
        .equiv CMIE,    0x0002
        .equiv CNIE,    0x0003
        .equiv INT1IE,  0x0004
        .equiv IC7IE,   0x0006
        .equiv IC8IE,   0x0007
        .equiv DMA2IE,  0x0008
        .equiv OC3IE,   0x0009
        .equiv OC4IE,   0x000A
        .equiv T4IE,    0x000B
        .equiv T5IE,    0x000C
        .equiv INT2IE,  0x000D
        .equiv U2RXIE,  0x000E
        .equiv U2TXIE,  0x000F

        .equiv SI2CIE,  0x0000


;----- IEC2 Bits -----------------------------------------------------
        .equiv SPI2EIE, 0x0000
        .equiv SPI2IE,  0x0001
        .equiv C1RXIE,  0x0002
        .equiv C1IE,    0x0003
        .equiv DMA3IE,  0x0004
        .equiv PMPIE,   0x000D
        .equiv DMA4IE,  0x000E


;----- IEC3 Bits -----------------------------------------------------
        .equiv PWM1IE,  0x0009
        .equiv QEI1IE,  0x000A
        .equiv DMA5IE,  0x000D
        .equiv RTCIE,   0x000E
        .equiv FLTA1IE, 0x000F


;----- IEC4 Bits -----------------------------------------------------
        .equiv U1EIE,   0x0001
        .equiv U2EIE,   0x0002
        .equiv CRCIE,   0x0003
        .equiv DMA6IE,  0x0004
        .equiv DMA7IE,  0x0005
        .equiv C1TXIE,  0x0006
        .equiv PWM2IE,  0x0009
        .equiv FLTA2IE, 0x000A
        .equiv QEI2IE,  0x000B


;----- IPC0 Bits -----------------------------------------------------
        .equiv INT0IP0, 0x0000
        .equiv INT0IP1, 0x0001
        .equiv INT0IP2, 0x0002
        .equiv IC1IP0,  0x0004
        .equiv IC1IP1,  0x0005
        .equiv IC1IP2,  0x0006
        .equiv OC1IP0,  0x0008
        .equiv OC1IP1,  0x0009
        .equiv OC1IP2,  0x000A
        .equiv T1IP0,   0x000C
        .equiv T1IP1,   0x000D
        .equiv T1IP2,   0x000E


;----- IPC1 Bits -----------------------------------------------------
        .equiv DMA0IP0, 0x0000
        .equiv DMA0IP1, 0x0001
        .equiv DMA0IP2, 0x0002
        .equiv IC2IP0,  0x0004
        .equiv IC2IP1,  0x0005
        .equiv IC2IP2,  0x0006
        .equiv OC2IP0,  0x0008
        .equiv OC2IP1,  0x0009
        .equiv OC2IP2,  0x000A
        .equiv T2IP0,   0x000C
        .equiv T2IP1,   0x000D
        .equiv T2IP2,   0x000E


;----- IPC2 Bits -----------------------------------------------------
        .equiv T3IP0,   0x0000
        .equiv T3IP1,   0x0001
        .equiv T3IP2,   0x0002
        .equiv SPI1EIP0, 0x0004
        .equiv SPI1EIP1, 0x0005
        .equiv SPI1EIP2, 0x0006
        .equiv SPI1IP0, 0x0008
        .equiv SPI1IP1, 0x0009
        .equiv SPI1IP2, 0x000A
        .equiv U1RXIP0, 0x000C
        .equiv U1RXIP1, 0x000D
        .equiv U1RXIP2, 0x000E


;----- IPC3 Bits -----------------------------------------------------
        .equiv U1TXIP0, 0x0000
        .equiv U1TXIP1, 0x0001
        .equiv U1TXIP2, 0x0002
        .equiv AD1IP0,  0x0004
        .equiv AD1IP1,  0x0005
        .equiv AD1IP2,  0x0006
        .equiv DMA1IP0, 0x0008
        .equiv DMA1IP1, 0x0009
        .equiv DMA1IP2, 0x000A


;----- IPC4 Bits -----------------------------------------------------
        .equiv SI2C1IP0, 0x0000
        .equiv SI2C1IP1, 0x0001
        .equiv SI2C1IP2, 0x0002
        .equiv MI2C1IP0, 0x0004
        .equiv MI2C1IP1, 0x0005
        .equiv MI2C1IP2, 0x0006
        .equiv CMIP0,   0x0008
        .equiv CMIP1,   0x0009
        .equiv CMIP2,   0x000A
        .equiv CNIP0,   0x000C
        .equiv CNIP1,   0x000D
        .equiv CNIP2,   0x000E


;----- IPC5 Bits -----------------------------------------------------
        .equiv INT1IP0, 0x0000
        .equiv INT1IP1, 0x0001
        .equiv INT1IP2, 0x0002
        .equiv IC7IP0,  0x0008
        .equiv IC7IP1,  0x0009
        .equiv IC7IP2,  0x000A
        .equiv IC8IP0,  0x000C
        .equiv IC8IP1,  0x000D
        .equiv IC8IP2,  0x000E


;----- IPC6 Bits -----------------------------------------------------
        .equiv DMA2IP0, 0x0000
        .equiv DMA2IP1, 0x0001
        .equiv DMA2IP2, 0x0002
        .equiv OC3IP0,  0x0004
        .equiv OC3IP1,  0x0005
        .equiv OC3IP2,  0x0006
        .equiv OC4IP0,  0x0008
        .equiv OC4IP1,  0x0009
        .equiv OC4IP2,  0x000A
        .equiv T4IP0,   0x000C
        .equiv T4IP1,   0x000D
        .equiv T4IP2,   0x000E


;----- IPC7 Bits -----------------------------------------------------
        .equiv T5IP0,   0x0000
        .equiv T5IP1,   0x0001
        .equiv T5IP2,   0x0002
        .equiv INT2IP0, 0x0004
        .equiv INT2IP1, 0x0005
        .equiv INT2IP2, 0x0006
        .equiv U2RXIP0, 0x0008
        .equiv U2RXIP1, 0x0009
        .equiv U2RXIP2, 0x000A
        .equiv U2TXIP0, 0x000C
        .equiv U2TXIP1, 0x000D
        .equiv U2TXIP2, 0x000E


;----- IPC8 Bits -----------------------------------------------------
        .equiv SPI2EIP0, 0x0000
        .equiv SPI2EIP1, 0x0001
        .equiv SPI2EIP2, 0x0002
        .equiv SPI2IP0, 0x0004
        .equiv SPI2IP1, 0x0005
        .equiv SPI2IP2, 0x0006
        .equiv C1RXIP0, 0x0008
        .equiv C1RXIP1, 0x0009
        .equiv C1RXIP2, 0x000A
        .equiv C1IP0,   0x000C
        .equiv C1IP1,   0x000D
        .equiv C1IP2,   0x000E


;----- IPC9 Bits -----------------------------------------------------
        .equiv DMA3IP0, 0x0000
        .equiv DMA3IP1, 0x0001
        .equiv DMA3IP2, 0x0002


;----- IPC11 Bits -----------------------------------------------------
        .equiv PMPIP0,  0x0004
        .equiv PMPIP1,  0x0005
        .equiv PMPIP2,  0x0006
        .equiv DMA4IP0, 0x0008
        .equiv DMA4IP1, 0x0009
        .equiv DMA4IP2, 0x000A


;----- IPC14 Bits -----------------------------------------------------
        .equiv PWM1IP0, 0x0004
        .equiv PWM1IP1, 0x0005
        .equiv PWM1IP2, 0x0006
        .equiv QEI1IP0, 0x0008
        .equiv QEI1IP1, 0x0009
        .equiv QEI1IP2, 0x000A


;----- IPC15 Bits -----------------------------------------------------
        .equiv DMA5IP0, 0x0004
        .equiv DMA5IP1, 0x0005
        .equiv DMA5IP2, 0x0006
        .equiv RTCIP0,  0x0008
        .equiv RTCIP1,  0x0009
        .equiv RTCIP2,  0x000A
        .equiv FLTA1IP0, 0x000C
        .equiv FLTA1IP1, 0x000D
        .equiv FLTA1IP2, 0x000E


;----- IPC16 Bits -----------------------------------------------------
        .equiv U1EIP0,  0x0004
        .equiv U1EIP1,  0x0005
        .equiv U1EIP2,  0x0006
        .equiv U2EIP0,  0x0008
        .equiv U2EIP1,  0x0009
        .equiv U2EIP2,  0x000A
        .equiv CRCIP0,  0x000C
        .equiv CRCIP1,  0x000D
        .equiv CRCIP2,  0x000E


;----- IPC17 Bits -----------------------------------------------------
        .equiv DMA6IP0, 0x0000
        .equiv DMA6IP1, 0x0001
        .equiv DMA6IP2, 0x0002
        .equiv DMA7IP0, 0x0004
        .equiv DMA7IP1, 0x0005
        .equiv DMA7IP2, 0x0006
        .equiv C1TXIP0, 0x0008
        .equiv C1TXIP1, 0x0009
        .equiv C1TXIP2, 0x000A


;----- IPC18 Bits -----------------------------------------------------
        .equiv PWM2IP0, 0x0004
        .equiv PWM2IP1, 0x0005
        .equiv PWM2IP2, 0x0006
        .equiv FLTA2IP0, 0x0008
        .equiv FLTA2IP1, 0x0009
        .equiv FLTA2IP2, 0x000A
        .equiv QEI2IP0, 0x000C
        .equiv QEI2IP1, 0x000D
        .equiv QEI2IP2, 0x000E


;----- INTTREG Bits -----------------------------------------------------
        .equiv VECNUM0, 0x0000
        .equiv VECNUM1, 0x0001
        .equiv VECNUM2, 0x0002
        .equiv VECNUM3, 0x0003
        .equiv VECNUM4, 0x0004
        .equiv VECNUM5, 0x0005
        .equiv VECNUM6, 0x0006
        .equiv ILR0,    0x0008
        .equiv ILR1,    0x0009
        .equiv ILR2,    0x000A
        .equiv ILR3,    0x000B


;----- T1CON Bits -----------------------------------------------------
        .equiv TCS,     0x0001
        .equiv TSYNC,   0x0002
        .equiv TGATE,   0x0006
        .equiv TSIDL,   0x000D
        .equiv TON,     0x000F

        .equiv TCKPS0,  0x0004
        .equiv TCKPS1,  0x0005


;----- T2CON Bits -----------------------------------------------------
       ;.equiv TCS,     0x0001
        .equiv T32,     0x0003
       ;.equiv TGATE,   0x0006
       ;.equiv TSIDL,   0x000D
       ;.equiv TON,     0x000F

       ;.equiv TCKPS0,  0x0004
       ;.equiv TCKPS1,  0x0005


;----- T3CON Bits -----------------------------------------------------
       ;.equiv TCS,     0x0001
       ;.equiv TGATE,   0x0006
       ;.equiv TSIDL,   0x000D
       ;.equiv TON,     0x000F

       ;.equiv TCKPS0,  0x0004
       ;.equiv TCKPS1,  0x0005


;----- T4CON Bits -----------------------------------------------------
       ;.equiv TCS,     0x0001
       ;.equiv T32,     0x0003
       ;.equiv TGATE,   0x0006
       ;.equiv TSIDL,   0x000D
       ;.equiv TON,     0x000F

       ;.equiv TCKPS0,  0x0004
       ;.equiv TCKPS1,  0x0005


;----- T5CON Bits -----------------------------------------------------
       ;.equiv TCS,     0x0001
       ;.equiv TGATE,   0x0006
       ;.equiv TSIDL,   0x000D
       ;.equiv TON,     0x000F

       ;.equiv TCKPS0,  0x0004
       ;.equiv TCKPS1,  0x0005


;----- IC1CON Bits -----------------------------------------------------
        .equiv ICBNE,   0x0003
        .equiv ICOV,    0x0004
        .equiv ICTMR,   0x0007
        .equiv ICSIDL,  0x000D

        .equiv ICM0,    0x0000
        .equiv ICM1,    0x0001
        .equiv ICM2,    0x0002
        .equiv ICI0,    0x0005
        .equiv ICI1,    0x0006


;----- IC2CON Bits -----------------------------------------------------
       ;.equiv ICBNE,   0x0003
       ;.equiv ICOV,    0x0004
       ;.equiv ICTMR,   0x0007
       ;.equiv ICSIDL,  0x000D

       ;.equiv ICM0,    0x0000
       ;.equiv ICM1,    0x0001
       ;.equiv ICM2,    0x0002
       ;.equiv ICI0,    0x0005
       ;.equiv ICI1,    0x0006


;----- IC7CON Bits -----------------------------------------------------
       ;.equiv ICBNE,   0x0003
       ;.equiv ICOV,    0x0004
       ;.equiv ICTMR,   0x0007
       ;.equiv ICSIDL,  0x000D

       ;.equiv ICM0,    0x0000
       ;.equiv ICM1,    0x0001
       ;.equiv ICM2,    0x0002
       ;.equiv ICI0,    0x0005
       ;.equiv ICI1,    0x0006


;----- IC8CON Bits -----------------------------------------------------
       ;.equiv ICBNE,   0x0003
       ;.equiv ICOV,    0x0004
       ;.equiv ICTMR,   0x0007
       ;.equiv ICSIDL,  0x000D

       ;.equiv ICM0,    0x0000
       ;.equiv ICM1,    0x0001
       ;.equiv ICM2,    0x0002
       ;.equiv ICI0,    0x0005
       ;.equiv ICI1,    0x0006


;----- OC1CON Bits -----------------------------------------------------
        .equiv OCTSEL,  0x0003
        .equiv OCFLT,   0x0004
        .equiv OCSIDL,  0x000D

        .equiv OCM0,    0x0000
        .equiv OCM1,    0x0001
        .equiv OCM2,    0x0002


;----- OC2CON Bits -----------------------------------------------------
       ;.equiv OCTSEL,  0x0003
       ;.equiv OCFLT,   0x0004
       ;.equiv OCSIDL,  0x000D

       ;.equiv OCM0,    0x0000
       ;.equiv OCM1,    0x0001
       ;.equiv OCM2,    0x0002


;----- OC3CON Bits -----------------------------------------------------
       ;.equiv OCTSEL,  0x0003
       ;.equiv OCFLT,   0x0004
       ;.equiv OCSIDL,  0x000D

       ;.equiv OCM0,    0x0000
       ;.equiv OCM1,    0x0001
       ;.equiv OCM2,    0x0002


;----- OC4CON Bits -----------------------------------------------------
       ;.equiv OCTSEL,  0x0003
       ;.equiv OCFLT,   0x0004
       ;.equiv OCSIDL,  0x000D

       ;.equiv OCM0,    0x0000
       ;.equiv OCM1,    0x0001
       ;.equiv OCM2,    0x0002


;----- P1TCON Bits -----------------------------------------------------
        .equiv PTSIDL,  0x000D
        .equiv PTEN_P1TCON, 0x000F

        .equiv PTMOD0,  0x0000
        .equiv PTMOD1,  0x0001
        .equiv PTCKPS0, 0x0002
        .equiv PTCKPS1, 0x0003
        .equiv PTOPS0,  0x0004
        .equiv PTOPS1,  0x0005
        .equiv PTOPS2,  0x0006
        .equiv PTOPS3,  0x0007


;----- PTCON Bits -----------------------------------------------------
       ;.equiv PTSIDL,  0x000D
        .equiv PTEN_PTCON, 0x000F

       ;.equiv PTMOD0,  0x0000
       ;.equiv PTMOD1,  0x0001
       ;.equiv PTCKPS0, 0x0002
       ;.equiv PTCKPS1, 0x0003
       ;.equiv PTOPS0,  0x0004
       ;.equiv PTOPS1,  0x0005
       ;.equiv PTOPS2,  0x0006
       ;.equiv PTOPS3,  0x0007


;----- P1TMR Bits -----------------------------------------------------
        .equiv PTDIR,   0x000F


;----- PTMR Bits -----------------------------------------------------
       ;.equiv PTDIR,   0x000F


;----- P1SECMP Bits -----------------------------------------------------
        .equiv SEVTDIR, 0x000F


;----- SEVTCMP Bits -----------------------------------------------------
       ;.equiv SEVTDIR, 0x000F


;----- PWM1CON1 Bits -----------------------------------------------------
        .equiv PEN1L,   0x0000
        .equiv PEN2L,   0x0001
        .equiv PEN3L,   0x0002
        .equiv PEN1H,   0x0004
        .equiv PEN2H,   0x0005
        .equiv PEN3H,   0x0006
        .equiv PMOD1,   0x0008
        .equiv PMOD2,   0x0009
        .equiv PMOD3,   0x000A


;----- PWMCON1 Bits -----------------------------------------------------
       ;.equiv PEN1L,   0x0000
       ;.equiv PEN2L,   0x0001
       ;.equiv PEN3L,   0x0002
       ;.equiv PEN1H,   0x0004
       ;.equiv PEN2H,   0x0005
       ;.equiv PEN3H,   0x0006
       ;.equiv PMOD1,   0x0008
       ;.equiv PMOD2,   0x0009
       ;.equiv PMOD3,   0x000A


;----- PWM1CON2 Bits -----------------------------------------------------
        .equiv UDIS,    0x0000
        .equiv OSYNC,   0x0001
        .equiv IUE,     0x0002

        .equiv SEVOPS0, 0x0008
        .equiv SEVOPS1, 0x0009
        .equiv SEVOPS2, 0x000A
        .equiv SEVOPS3, 0x000B


;----- PWMCON2 Bits -----------------------------------------------------
       ;.equiv UDIS,    0x0000
       ;.equiv OSYNC,   0x0001
       ;.equiv IUE,     0x0002

       ;.equiv SEVOPS0, 0x0008
       ;.equiv SEVOPS1, 0x0009
       ;.equiv SEVOPS2, 0x000A
       ;.equiv SEVOPS3, 0x000B


;----- DTCON1 Bits -----------------------------------------------------
        .equiv DTA0,    0x0000
        .equiv DTA1,    0x0001
        .equiv DTA2,    0x0002
        .equiv DTA3,    0x0003
        .equiv DTA4,    0x0004
        .equiv DTA5,    0x0005
        .equiv DTAPS0,  0x0006
        .equiv DTAPS1,  0x0007
        .equiv DTB0,    0x0008
        .equiv DTB1,    0x0009
        .equiv DTB2,    0x000A
        .equiv DTB3,    0x000B
        .equiv DTB4,    0x000C
        .equiv DTB5,    0x000D
        .equiv DTBPS0,  0x000E
        .equiv DTBPS1,  0x000F


;----- P1DTCON1 Bits -----------------------------------------------------
       ;.equiv DTA0,    0x0000
       ;.equiv DTA1,    0x0001
       ;.equiv DTA2,    0x0002
       ;.equiv DTA3,    0x0003
       ;.equiv DTA4,    0x0004
       ;.equiv DTA5,    0x0005
       ;.equiv DTAPS0,  0x0006
       ;.equiv DTAPS1,  0x0007
       ;.equiv DTB0,    0x0008
       ;.equiv DTB1,    0x0009
       ;.equiv DTB2,    0x000A
       ;.equiv DTB3,    0x000B
       ;.equiv DTB4,    0x000C
       ;.equiv DTB5,    0x000D
       ;.equiv DTBPS0,  0x000E
       ;.equiv DTBPS1,  0x000F


;----- DTCON2 Bits -----------------------------------------------------
        .equiv DTS1I,   0x0000
        .equiv DTS1A,   0x0001
        .equiv DTS2I,   0x0002
        .equiv DTS2A,   0x0003
        .equiv DTS3I,   0x0004
        .equiv DTS3A,   0x0005


;----- P1DTCON2 Bits -----------------------------------------------------
       ;.equiv DTS1I,   0x0000
       ;.equiv DTS1A,   0x0001
       ;.equiv DTS2I,   0x0002
       ;.equiv DTS2A,   0x0003
       ;.equiv DTS3I,   0x0004
       ;.equiv DTS3A,   0x0005


;----- FLTACON Bits -----------------------------------------------------
        .equiv FAEN1,   0x0000
        .equiv FAEN2,   0x0001
        .equiv FAEN3,   0x0002
        .equiv FLTAM,   0x0007
        .equiv FAOV1L,  0x0008
        .equiv FAOV1H,  0x0009
        .equiv FAOV2L,  0x000A
        .equiv FAOV2H,  0x000B
        .equiv FAOV3L,  0x000C
        .equiv FAOV3H,  0x000D


;----- P1FLTACON Bits -----------------------------------------------------
       ;.equiv FAEN1,   0x0000
       ;.equiv FAEN2,   0x0001
       ;.equiv FAEN3,   0x0002
       ;.equiv FLTAM,   0x0007
       ;.equiv FAOV1L,  0x0008
       ;.equiv FAOV1H,  0x0009
       ;.equiv FAOV2L,  0x000A
       ;.equiv FAOV2H,  0x000B
       ;.equiv FAOV3L,  0x000C
       ;.equiv FAOV3H,  0x000D


;----- OVDCON Bits -----------------------------------------------------
        .equiv POUT1L,  0x0000
        .equiv POUT1H,  0x0001
        .equiv POUT2L,  0x0002
        .equiv POUT2H,  0x0003
        .equiv POUT3L,  0x0004
        .equiv POUT3H,  0x0005
        .equiv POVD1L,  0x0008
        .equiv POVD1H,  0x0009
        .equiv POVD2L,  0x000A
        .equiv POVD2H,  0x000B
        .equiv POVD3L,  0x000C
        .equiv POVD3H,  0x000D


;----- P1OVDCON Bits -----------------------------------------------------
       ;.equiv POUT1L,  0x0000
       ;.equiv POUT1H,  0x0001
       ;.equiv POUT2L,  0x0002
       ;.equiv POUT2H,  0x0003
       ;.equiv POUT3L,  0x0004
       ;.equiv POUT3H,  0x0005
       ;.equiv POVD1L,  0x0008
       ;.equiv POVD1H,  0x0009
       ;.equiv POVD2L,  0x000A
       ;.equiv POVD2H,  0x000B
       ;.equiv POVD3L,  0x000C
       ;.equiv POVD3H,  0x000D


;----- QEI1CON Bits -----------------------------------------------------
        .equiv UPDN_SRC, 0x0000
        .equiv TQCS,    0x0001
        .equiv POSRES,  0x0002
        .equiv TQGATE,  0x0005
        .equiv PCDOUT,  0x0006
        .equiv SWPAB,   0x0007
        .equiv UPDN,    0x000B
        .equiv INDX,    0x000C
        .equiv QEISIDL, 0x000D
        .equiv CNTERR,  0x000F

        .equiv TQCKPS0, 0x0003
        .equiv TQCKPS1, 0x0004
        .equiv QEIM0,   0x0008
        .equiv QEIM1,   0x0009
        .equiv QEIM2,   0x000A


;----- QEICON Bits -----------------------------------------------------
       ;.equiv UPDN_SRC, 0x0000
       ;.equiv TQCS,    0x0001
       ;.equiv POSRES,  0x0002
       ;.equiv TQGATE,  0x0005
       ;.equiv PCDOUT,  0x0006
       ;.equiv SWPAB,   0x0007
       ;.equiv UPDN,    0x000B
       ;.equiv INDX,    0x000C
       ;.equiv QEISIDL, 0x000D
       ;.equiv CNTERR,  0x000F

       ;.equiv TQCKPS0, 0x0003
       ;.equiv TQCKPS1, 0x0004
       ;.equiv QEIM0,   0x0008
       ;.equiv QEIM1,   0x0009
       ;.equiv QEIM2,   0x000A


;----- DFLT1CON Bits -----------------------------------------------------
        .equiv QEOUT,   0x0007
        .equiv CEID,    0x0008

        .equiv QECK0,   0x0004
        .equiv QECK1,   0x0005
        .equiv QECK2,   0x0006
        .equiv IMV0,    0x0009
        .equiv IMV1,    0x000A


;----- DFLTCON Bits -----------------------------------------------------
       ;.equiv QEOUT,   0x0007
       ;.equiv CEID,    0x0008

       ;.equiv QECK0,   0x0004
       ;.equiv QECK1,   0x0005
       ;.equiv QECK2,   0x0006
       ;.equiv IMV0,    0x0009
       ;.equiv IMV1,    0x000A


;----- QEI2CON Bits -----------------------------------------------------
       ;.equiv UPDN_SRC, 0x0000
       ;.equiv TQCS,    0x0001
       ;.equiv POSRES,  0x0002
       ;.equiv TQGATE,  0x0005
       ;.equiv PCDOUT,  0x0006
       ;.equiv SWPAB,   0x0007
       ;.equiv UPDN,    0x000B
       ;.equiv INDX,    0x000C
       ;.equiv QEISIDL, 0x000D
       ;.equiv CNTERR,  0x000F

       ;.equiv TQCKPS0, 0x0003
       ;.equiv TQCKPS1, 0x0004
       ;.equiv QEIM0,   0x0008
       ;.equiv QEIM1,   0x0009
       ;.equiv QEIM2,   0x000A


;----- DFLT2CON Bits -----------------------------------------------------
       ;.equiv QEOUT,   0x0007
       ;.equiv CEID,    0x0008

       ;.equiv QECK0,   0x0004
       ;.equiv QECK1,   0x0005
       ;.equiv QECK2,   0x0006
       ;.equiv IMV0,    0x0009
       ;.equiv IMV1,    0x000A


;----- I2C1CON Bits -----------------------------------------------------
        .equiv SEN,     0x0000
        .equiv RSEN,    0x0001
        .equiv PEN,     0x0002
        .equiv RCEN,    0x0003
        .equiv ACKEN,   0x0004
        .equiv ACKDT,   0x0005
        .equiv STREN,   0x0006
        .equiv GCEN,    0x0007
        .equiv SMEN,    0x0008
        .equiv DISSLW,  0x0009
        .equiv A10M,    0x000A
        .equiv IPMIEN,  0x000B
        .equiv SCLREL,  0x000C
        .equiv I2CSIDL, 0x000D
        .equiv I2CEN,   0x000F


;----- I2C1STAT Bits -----------------------------------------------------
        .equiv TBF,     0x0000
        .equiv RBF,     0x0001
        .equiv R_W,     0x0002
        .equiv S,       0x0003
        .equiv P,       0x0004
        .equiv D_A,     0x0005
        .equiv I2COV,   0x0006
        .equiv IWCOL,   0x0007
        .equiv ADD10,   0x0008
        .equiv GCSTAT,  0x0009
        .equiv BCL,     0x000A
        .equiv TRSTAT,  0x000E
        .equiv ACKSTAT, 0x000F


;----- U1MODE Bits -----------------------------------------------------
        .equiv STSEL,   0x0000
        .equiv BRGH,    0x0003
        .equiv URXINV,  0x0004
        .equiv ABAUD,   0x0005
        .equiv LPBACK,  0x0006
        .equiv WAKE,    0x0007
        .equiv RTSMD,   0x000B
        .equiv IREN,    0x000C
        .equiv USIDL,   0x000D
        .equiv UARTEN,  0x000F

        .equiv PDSEL0,  0x0001
        .equiv PDSEL1,  0x0002
        .equiv UEN0,    0x0008
        .equiv UEN1,    0x0009


;----- U1STA Bits -----------------------------------------------------
        .equiv URXDA,   0x0000
        .equiv OERR,    0x0001
        .equiv FERR,    0x0002
        .equiv PERR,    0x0003
        .equiv RIDLE,   0x0004
        .equiv ADDEN,   0x0005
        .equiv TRMT,    0x0008
        .equiv UTXBF,   0x0009
        .equiv UTXEN,   0x000A
        .equiv UTXBRK,  0x000B
        .equiv UTXISEL0, 0x000D
        .equiv UTXINV,  0x000E
        .equiv UTXISEL1, 0x000F

        .equiv URXISEL0, 0x0006
        .equiv URXISEL1, 0x0007


;----- U1TXREG Bits -----------------------------------------------------
        .equiv UTXREG0, 0x0000
        .equiv UTXREG1, 0x0001
        .equiv UTXREG2, 0x0002
        .equiv UTXREG3, 0x0003
        .equiv UTXREG4, 0x0004
        .equiv UTXREG5, 0x0005
        .equiv UTXREG6, 0x0006
        .equiv UTXREG7, 0x0007
        .equiv UTXREG8, 0x0008


;----- U1RXREG Bits -----------------------------------------------------
        .equiv URXREG0, 0x0000
        .equiv URXREG1, 0x0001
        .equiv URXREG2, 0x0002
        .equiv URXREG3, 0x0003
        .equiv URXREG4, 0x0004
        .equiv URXREG5, 0x0005
        .equiv URXREG6, 0x0006
        .equiv URXREG7, 0x0007
        .equiv URXREG8, 0x0008


;----- U2MODE Bits -----------------------------------------------------
       ;.equiv STSEL,   0x0000
       ;.equiv BRGH,    0x0003
       ;.equiv URXINV,  0x0004
       ;.equiv ABAUD,   0x0005
       ;.equiv LPBACK,  0x0006
       ;.equiv WAKE,    0x0007
       ;.equiv RTSMD,   0x000B
       ;.equiv IREN,    0x000C
       ;.equiv USIDL,   0x000D
       ;.equiv UARTEN,  0x000F

       ;.equiv PDSEL0,  0x0001
       ;.equiv PDSEL1,  0x0002
       ;.equiv UEN0,    0x0008
       ;.equiv UEN1,    0x0009


;----- U2STA Bits -----------------------------------------------------
       ;.equiv URXDA,   0x0000
       ;.equiv OERR,    0x0001
       ;.equiv FERR,    0x0002
       ;.equiv PERR,    0x0003
       ;.equiv RIDLE,   0x0004
       ;.equiv ADDEN,   0x0005
       ;.equiv TRMT,    0x0008
       ;.equiv UTXBF,   0x0009
       ;.equiv UTXEN,   0x000A
       ;.equiv UTXBRK,  0x000B
       ;.equiv UTXISEL0, 0x000D
       ;.equiv UTXINV,  0x000E
       ;.equiv UTXISEL1, 0x000F

       ;.equiv URXISEL0, 0x0006
       ;.equiv URXISEL1, 0x0007


;----- U2TXREG Bits -----------------------------------------------------
       ;.equiv UTXREG0, 0x0000
       ;.equiv UTXREG1, 0x0001
       ;.equiv UTXREG2, 0x0002
       ;.equiv UTXREG3, 0x0003
       ;.equiv UTXREG4, 0x0004
       ;.equiv UTXREG5, 0x0005
       ;.equiv UTXREG6, 0x0006
       ;.equiv UTXREG7, 0x0007
       ;.equiv UTXREG8, 0x0008


;----- U2RXREG Bits -----------------------------------------------------
       ;.equiv URXREG0, 0x0000
       ;.equiv URXREG1, 0x0001
       ;.equiv URXREG2, 0x0002
       ;.equiv URXREG3, 0x0003
       ;.equiv URXREG4, 0x0004
       ;.equiv URXREG5, 0x0005
       ;.equiv URXREG6, 0x0006
       ;.equiv URXREG7, 0x0007
       ;.equiv URXREG8, 0x0008


;----- SPI1STAT Bits -----------------------------------------------------
        .equiv SPIRBF,  0x0000
        .equiv SPITBF,  0x0001
        .equiv SPIROV,  0x0006
        .equiv SPISIDL, 0x000D
        .equiv SPIEN,   0x000F


;----- SPI1CON1 Bits -----------------------------------------------------
        .equiv MSTEN,   0x0005
        .equiv CKP,     0x0006
        .equiv SSEN,    0x0007
        .equiv CKE,     0x0008
        .equiv SMP,     0x0009
        .equiv MODE16,  0x000A
        .equiv DISSDO,  0x000B
        .equiv DISSCK,  0x000C

        .equiv PPRE0,   0x0000
        .equiv PPRE1,   0x0001
        .equiv SPRE0,   0x0002
        .equiv SPRE1,   0x0003
        .equiv SPRE2,   0x0004


;----- SPI1CON2 Bits -----------------------------------------------------
        .equiv FRMDLY,  0x0001
        .equiv FRMPOL,  0x000D
        .equiv SPIFSD,  0x000E
        .equiv FRMEN,   0x000F


;----- SPI2STAT Bits -----------------------------------------------------
       ;.equiv SPIRBF,  0x0000
       ;.equiv SPITBF,  0x0001
       ;.equiv SPIROV,  0x0006
       ;.equiv SPISIDL, 0x000D
       ;.equiv SPIEN,   0x000F



;----- SPI2CON1 Bits -----------------------------------------------------
       ;.equiv MSTEN,   0x0005
       ;.equiv CKP,     0x0006
       ;.equiv SSEN,    0x0007
       ;.equiv CKE,     0x0008
       ;.equiv SMP,     0x0009
       ;.equiv MODE16,  0x000A
       ;.equiv DISSDO,  0x000B
       ;.equiv DISSCK,  0x000C

       ;.equiv PPRE0,   0x0000
       ;.equiv PPRE1,   0x0001
       ;.equiv SPRE0,   0x0002
       ;.equiv SPRE1,   0x0003
       ;.equiv SPRE2,   0x0004


;----- SPI2CON2 Bits -----------------------------------------------------
       ;.equiv FRMDLY,  0x0001
       ;.equiv FRMPOL,  0x000D
       ;.equiv SPIFSD,  0x000E
       ;.equiv FRMEN,   0x000F


;----- TRISA Bits -----------------------------------------------------
        .equiv TRISA0,  0x0000
        .equiv TRISA1,  0x0001
        .equiv TRISA2,  0x0002
        .equiv TRISA3,  0x0003
        .equiv TRISA4,  0x0004


;----- PORTA Bits -----------------------------------------------------
        .equiv RA0,     0x0000
        .equiv RA1,     0x0001
        .equiv RA2,     0x0002
        .equiv RA3,     0x0003
        .equiv RA4,     0x0004


;----- LATA Bits -----------------------------------------------------
        .equiv LATA0,   0x0000
        .equiv LATA1,   0x0001
        .equiv LATA2,   0x0002
        .equiv LATA3,   0x0003
        .equiv LATA4,   0x0004


;----- ODCA Bits -----------------------------------------------------
        .equiv ODCA0,   0x0000
        .equiv ODCA1,   0x0001
        .equiv ODCA2,   0x0002
        .equiv ODCA3,   0x0003
        .equiv ODCA4,   0x0004


;----- TRISB Bits -----------------------------------------------------
        .equiv TRISB0,  0x0000
        .equiv TRISB1,  0x0001
        .equiv TRISB2,  0x0002
        .equiv TRISB3,  0x0003
        .equiv TRISB4,  0x0004
        .equiv TRISB5,  0x0005
        .equiv TRISB6,  0x0006
        .equiv TRISB7,  0x0007
        .equiv TRISB8,  0x0008
        .equiv TRISB9,  0x0009
        .equiv TRISB10, 0x000A
        .equiv TRISB11, 0x000B
        .equiv TRISB12, 0x000C
        .equiv TRISB13, 0x000D
        .equiv TRISB14, 0x000E
        .equiv TRISB15, 0x000F


;----- PORTB Bits -----------------------------------------------------
        .equiv RB0,     0x0000
        .equiv RB1,     0x0001
        .equiv RB2,     0x0002
        .equiv RB3,     0x0003
        .equiv RB4,     0x0004
        .equiv RB5,     0x0005
        .equiv RB6,     0x0006
        .equiv RB7,     0x0007
        .equiv RB8,     0x0008
        .equiv RB9,     0x0009
        .equiv RB10,    0x000A
        .equiv RB11,    0x000B
        .equiv RB12,    0x000C
        .equiv RB13,    0x000D
        .equiv RB14,    0x000E
        .equiv RB15,    0x000F


;----- LATB Bits -----------------------------------------------------
        .equiv LATB0,   0x0000
        .equiv LATB1,   0x0001
        .equiv LATB2,   0x0002
        .equiv LATB3,   0x0003
        .equiv LATB4,   0x0004
        .equiv LATB5,   0x0005
        .equiv LATB6,   0x0006
        .equiv LATB7,   0x0007
        .equiv LATB8,   0x0008
        .equiv LATB9,   0x0009
        .equiv LATB10,  0x000A
        .equiv LATB11,  0x000B
        .equiv LATB12,  0x000C
        .equiv LATB13,  0x000D
        .equiv LATB14,  0x000E
        .equiv LATB15,  0x000F


;----- ODCB Bits -----------------------------------------------------
        .equiv ODCB0,   0x0000
        .equiv ODCB1,   0x0001
        .equiv ODCB2,   0x0002
        .equiv ODCB3,   0x0003
        .equiv ODCB4,   0x0004
        .equiv ODCB5,   0x0005
        .equiv ODCB6,   0x0006
        .equiv ODCB7,   0x0007
        .equiv ODCB8,   0x0008
        .equiv ODCB9,   0x0009
        .equiv ODCB10,  0x000A
        .equiv ODCB11,  0x000B
        .equiv ODCB12,  0x000C
        .equiv ODCB13,  0x000D
        .equiv ODCB14,  0x000E
        .equiv ODCB15,  0x000F


;----- PADCFG1 Bits -----------------------------------------------------
        .equiv PMPTTL,  0x0000
        .equiv RTSECSEL, 0x0001


;----- AD1CON1 Bits -----------------------------------------------------
        .equiv DONE,    0x0000
        .equiv SAMP,    0x0001
        .equiv ASAM,    0x0002
        .equiv SIMSAM,  0x0003
        .equiv AD12B,   0x000A
        .equiv ADDMABM, 0x000C
        .equiv ADSIDL,  0x000D
        .equiv ADON,    0x000F

        .equiv SSRC0,   0x0005
        .equiv SSRC1,   0x0006
        .equiv SSRC2,   0x0007
        .equiv FORM0,   0x0008
        .equiv FORM1,   0x0009


;----- AD1CON2 Bits -----------------------------------------------------
        .equiv ALTS,    0x0000
        .equiv BUFM,    0x0001
        .equiv BUFS,    0x0007
        .equiv CSCNA,   0x000A

        .equiv SMPI0,   0x0002
        .equiv SMPI1,   0x0003
        .equiv SMPI2,   0x0004
        .equiv SMPI3,   0x0005
        .equiv CHPS0,   0x0008
        .equiv CHPS1,   0x0009
        .equiv VCFG0,   0x000D
        .equiv VCFG1,   0x000E
        .equiv VCFG2,   0x000F


;----- AD1CON3 Bits -----------------------------------------------------
        .equiv ADRC,    0x000F

        .equiv ADCS0,   0x0000
        .equiv ADCS1,   0x0001
        .equiv ADCS2,   0x0002
        .equiv ADCS3,   0x0003
        .equiv ADCS4,   0x0004
        .equiv ADCS5,   0x0005
        .equiv ADCS6,   0x0006
        .equiv ADCS7,   0x0007
        .equiv SAMC0,   0x0008
        .equiv SAMC1,   0x0009
        .equiv SAMC2,   0x000A
        .equiv SAMC3,   0x000B
        .equiv SAMC4,   0x000C


;----- AD1CHS123 Bits -----------------------------------------------------
        .equiv CH123SA, 0x0000
        .equiv CH123SB, 0x0008

        .equiv CH123NA0, 0x0001
        .equiv CH123NA1, 0x0002
        .equiv CH123NB0, 0x0009
        .equiv CH123NB1, 0x000A


;----- AD1CHS0 Bits -----------------------------------------------------
        .equiv CH0NA,   0x0007
        .equiv CH0NB,   0x000F

        .equiv CH0SA0,  0x0000
        .equiv CH0SA1,  0x0001
        .equiv CH0SA2,  0x0002
        .equiv CH0SA3,  0x0003
        .equiv CH0SA4,  0x0004
        .equiv CH0SB0,  0x0008
        .equiv CH0SB1,  0x0009
        .equiv CH0SB2,  0x000A
        .equiv CH0SB3,  0x000B
        .equiv CH0SB4,  0x000C


;----- AD1PCFGL Bits -----------------------------------------------------
        .equiv PCFG0,   0x0000
        .equiv PCFG1,   0x0001
        .equiv PCFG2,   0x0002
        .equiv PCFG3,   0x0003
        .equiv PCFG4,   0x0004
        .equiv PCFG5,   0x0005


;----- AD1CSSL Bits -----------------------------------------------------
        .equiv CSS0,    0x0000
        .equiv CSS1,    0x0001
        .equiv CSS2,    0x0002
        .equiv CSS3,    0x0003
        .equiv CSS4,    0x0004
        .equiv CSS5,    0x0005


;----- AD1CON4 Bits -----------------------------------------------------
        .equiv DMABL0,  0x0000
        .equiv DMABL1,  0x0001
        .equiv DMABL2,  0x0002


;----- DMA0CON Bits -----------------------------------------------------
        .equiv NULLW,   0x000B
        .equiv HALF,    0x000C
        .equiv DIR,     0x000D
        .equiv SIZE,    0x000E
        .equiv CHEN,    0x000F

        .equiv MODE0_DMA0CON, 0x0000
        .equiv MODE1_DMA0CON, 0x0001
        .equiv AMODE0,  0x0004
        .equiv AMODE1,  0x0005


;----- DMA0REQ Bits -----------------------------------------------------
        .equiv FORCE,   0x000F

        .equiv IRQSEL0, 0x0000
        .equiv IRQSEL1, 0x0001
        .equiv IRQSEL2, 0x0002
        .equiv IRQSEL3, 0x0003
        .equiv IRQSEL4, 0x0004
        .equiv IRQSEL5, 0x0005
        .equiv IRQSEL6, 0x0006


;----- DMA1CON Bits -----------------------------------------------------
       ;.equiv NULLW,   0x000B
       ;.equiv HALF,    0x000C
       ;.equiv DIR,     0x000D
       ;.equiv SIZE,    0x000E
       ;.equiv CHEN,    0x000F

        .equiv MODE0_DMA1CON, 0x0000
        .equiv MODE1_DMA1CON, 0x0001
       ;.equiv AMODE0,  0x0004
       ;.equiv AMODE1,  0x0005


;----- DMA1REQ Bits -----------------------------------------------------
       ;.equiv FORCE,   0x000F

       ;.equiv IRQSEL0, 0x0000
       ;.equiv IRQSEL1, 0x0001
       ;.equiv IRQSEL2, 0x0002
       ;.equiv IRQSEL3, 0x0003
       ;.equiv IRQSEL4, 0x0004
       ;.equiv IRQSEL5, 0x0005
       ;.equiv IRQSEL6, 0x0006


;----- DMA2CON Bits -----------------------------------------------------
       ;.equiv NULLW,   0x000B
       ;.equiv HALF,    0x000C
       ;.equiv DIR,     0x000D
       ;.equiv SIZE,    0x000E
       ;.equiv CHEN,    0x000F

        .equiv MODE0_DMA2CON, 0x0000
        .equiv MODE1_DMA2CON, 0x0001
       ;.equiv AMODE0,  0x0004
       ;.equiv AMODE1,  0x0005


;----- DMA2REQ Bits -----------------------------------------------------
       ;.equiv FORCE,   0x000F

       ;.equiv IRQSEL0, 0x0000
       ;.equiv IRQSEL1, 0x0001
       ;.equiv IRQSEL2, 0x0002
       ;.equiv IRQSEL3, 0x0003
       ;.equiv IRQSEL4, 0x0004
       ;.equiv IRQSEL5, 0x0005
       ;.equiv IRQSEL6, 0x0006


;----- DMA3CON Bits -----------------------------------------------------
       ;.equiv NULLW,   0x000B
       ;.equiv HALF,    0x000C
       ;.equiv DIR,     0x000D
       ;.equiv SIZE,    0x000E
       ;.equiv CHEN,    0x000F

        .equiv MODE0_DMA3CON, 0x0000
        .equiv MODE1_DMA3CON, 0x0001
       ;.equiv AMODE0,  0x0004
       ;.equiv AMODE1,  0x0005


;----- DMA3REQ Bits -----------------------------------------------------
       ;.equiv FORCE,   0x000F

       ;.equiv IRQSEL0, 0x0000
       ;.equiv IRQSEL1, 0x0001
       ;.equiv IRQSEL2, 0x0002
       ;.equiv IRQSEL3, 0x0003
       ;.equiv IRQSEL4, 0x0004
       ;.equiv IRQSEL5, 0x0005
       ;.equiv IRQSEL6, 0x0006


;----- DMA4CON Bits -----------------------------------------------------
       ;.equiv NULLW,   0x000B
       ;.equiv HALF,    0x000C
       ;.equiv DIR,     0x000D
       ;.equiv SIZE,    0x000E
       ;.equiv CHEN,    0x000F

        .equiv MODE0_DMA4CON, 0x0000
        .equiv MODE1_DMA4CON, 0x0001
       ;.equiv AMODE0,  0x0004
       ;.equiv AMODE1,  0x0005


;----- DMA4REQ Bits -----------------------------------------------------
       ;.equiv FORCE,   0x000F

       ;.equiv IRQSEL0, 0x0000
       ;.equiv IRQSEL1, 0x0001
       ;.equiv IRQSEL2, 0x0002
       ;.equiv IRQSEL3, 0x0003
       ;.equiv IRQSEL4, 0x0004
       ;.equiv IRQSEL5, 0x0005
       ;.equiv IRQSEL6, 0x0006


;----- DMA5CON Bits -----------------------------------------------------
       ;.equiv NULLW,   0x000B
       ;.equiv HALF,    0x000C
       ;.equiv DIR,     0x000D
       ;.equiv SIZE,    0x000E
       ;.equiv CHEN,    0x000F

        .equiv MODE0_DMA5CON, 0x0000
        .equiv MODE1_DMA5CON, 0x0001
       ;.equiv AMODE0,  0x0004
       ;.equiv AMODE1,  0x0005


;----- DMA5REQ Bits -----------------------------------------------------
       ;.equiv FORCE,   0x000F

       ;.equiv IRQSEL0, 0x0000
       ;.equiv IRQSEL1, 0x0001
       ;.equiv IRQSEL2, 0x0002
       ;.equiv IRQSEL3, 0x0003
       ;.equiv IRQSEL4, 0x0004
       ;.equiv IRQSEL5, 0x0005
       ;.equiv IRQSEL6, 0x0006


;----- DMA6CON Bits -----------------------------------------------------
       ;.equiv NULLW,   0x000B
       ;.equiv HALF,    0x000C
       ;.equiv DIR,     0x000D
       ;.equiv SIZE,    0x000E
       ;.equiv CHEN,    0x000F

        .equiv MODE0_DMA6CON, 0x0000
        .equiv MODE1_DMA6CON, 0x0001
       ;.equiv AMODE0,  0x0004
       ;.equiv AMODE1,  0x0005


;----- DMA6REQ Bits -----------------------------------------------------
       ;.equiv FORCE,   0x000F

       ;.equiv IRQSEL0, 0x0000
       ;.equiv IRQSEL1, 0x0001
       ;.equiv IRQSEL2, 0x0002
       ;.equiv IRQSEL3, 0x0003
       ;.equiv IRQSEL4, 0x0004
       ;.equiv IRQSEL5, 0x0005
       ;.equiv IRQSEL6, 0x0006


;----- DMA7CON Bits -----------------------------------------------------
       ;.equiv NULLW,   0x000B
       ;.equiv HALF,    0x000C
       ;.equiv DIR,     0x000D
       ;.equiv SIZE,    0x000E
       ;.equiv CHEN,    0x000F

        .equiv MODE0_DMA7CON, 0x0000
        .equiv MODE1_DMA7CON, 0x0001
       ;.equiv AMODE0,  0x0004
       ;.equiv AMODE1,  0x0005


;----- DMA7REQ Bits -----------------------------------------------------
       ;.equiv FORCE,   0x000F

       ;.equiv IRQSEL0, 0x0000
       ;.equiv IRQSEL1, 0x0001
       ;.equiv IRQSEL2, 0x0002
       ;.equiv IRQSEL3, 0x0003
       ;.equiv IRQSEL4, 0x0004
       ;.equiv IRQSEL5, 0x0005
       ;.equiv IRQSEL6, 0x0006


;----- DMACS0 Bits -----------------------------------------------------
        .equiv XWCOL0,  0x0000
        .equiv XWCOL1,  0x0001
        .equiv XWCOL2,  0x0002
        .equiv XWCOL3,  0x0003
        .equiv XWCOL4,  0x0004
        .equiv XWCOL5,  0x0005
        .equiv XWCOL6,  0x0006
        .equiv XWCOL7,  0x0007
        .equiv PWCOL0,  0x0008
        .equiv PWCOL1,  0x0009
        .equiv PWCOL2,  0x000A
        .equiv PWCOL3,  0x000B
        .equiv PWCOL4,  0x000C
        .equiv PWCOL5,  0x000D
        .equiv PWCOL6,  0x000E
        .equiv PWCOL7,  0x000F


;----- DMACS1 Bits -----------------------------------------------------
        .equiv PPST0,   0x0000
        .equiv PPST1,   0x0001
        .equiv PPST2,   0x0002
        .equiv PPST3,   0x0003
        .equiv PPST4,   0x0004
        .equiv PPST5,   0x0005
        .equiv PPST6,   0x0006
        .equiv PPST7,   0x0007
        .equiv LSTCH0,  0x0008
        .equiv LSTCH1,  0x0009
        .equiv LSTCH2,  0x000A
        .equiv LSTCH3,  0x000B


;----- C1CTRL1 Bits -----------------------------------------------------
        .equiv WIN,     0x0000
        .equiv CANCAP,  0x0003
        .equiv CANCKS,  0x000B
        .equiv ABAT,    0x000C
        .equiv CSIDL,   0x000D

        .equiv OPMODE0, 0x0005
        .equiv OPMODE1, 0x0006
        .equiv OPMODE2, 0x0007
        .equiv REQOP0,  0x0008
        .equiv REQOP1,  0x0009
        .equiv REQOP2,  0x000A


;----- C1CTRL2 Bits -----------------------------------------------------
        .equiv DNCNT0,  0x0000
        .equiv DNCNT1,  0x0001
        .equiv DNCNT2,  0x0002
        .equiv DNCNT3,  0x0003
        .equiv DNCNT4,  0x0004


;----- C1VEC Bits -----------------------------------------------------
        .equiv ICODE0,  0x0000
        .equiv ICODE1,  0x0001
        .equiv ICODE2,  0x0002
        .equiv ICODE3,  0x0003
        .equiv ICODE4,  0x0004
        .equiv ICODE5,  0x0005
        .equiv ICODE6,  0x0006
        .equiv FILHIT0, 0x0008
        .equiv FILHIT1, 0x0009
        .equiv FILHIT2, 0x000A
        .equiv FILHIT3, 0x000B
        .equiv FILHIT4, 0x000C


;----- C1FCTRL Bits -----------------------------------------------------
        .equiv FSA0,    0x0000
        .equiv FSA1,    0x0001
        .equiv FSA2,    0x0002
        .equiv FSA3,    0x0003
        .equiv FSA4,    0x0004
        .equiv DMABS0,  0x000D
        .equiv DMABS1,  0x000E
        .equiv DMABS2,  0x000F


;----- C1FIFO Bits -----------------------------------------------------
        .equiv FNRB0,   0x0000
        .equiv FNRB1,   0x0001
        .equiv FNRB2,   0x0002
        .equiv FNRB3,   0x0003
        .equiv FNRB4,   0x0004
        .equiv FNRB5,   0x0005
        .equiv FBP0,    0x0008
        .equiv FBP1,    0x0009
        .equiv FBP2,    0x000A
        .equiv FBP3,    0x000B
        .equiv FBP4,    0x000C
        .equiv FBP5,    0x000D


;----- C1INTF Bits -----------------------------------------------------
        .equiv TBIF,    0x0000
        .equiv RBIF,    0x0001
        .equiv RBOVIF,  0x0002
        .equiv FIFOIF,  0x0003
        .equiv ERRIF,   0x0005
        .equiv WAKIF,   0x0006
        .equiv IVRIF,   0x0007
        .equiv EWARN,   0x0008
        .equiv RXWAR,   0x0009
        .equiv TXWAR,   0x000A
        .equiv RXBP,    0x000B
        .equiv TXBP,    0x000C
        .equiv TXBO,    0x000D


;----- C1INTE Bits -----------------------------------------------------
        .equiv TBIE,    0x0000
        .equiv RBIE,    0x0001
        .equiv RBOVIE,  0x0002
        .equiv FIFOIE,  0x0003
        .equiv ERRIE,   0x0005
        .equiv WAKIE,   0x0006
        .equiv IVRIE,   0x0007


;----- C1EC Bits -----------------------------------------------------
        .equiv RERRCNT0, 0x0000
        .equiv RERRCNT1, 0x0001
        .equiv RERRCNT2, 0x0002
        .equiv RERRCNT3, 0x0003
        .equiv RERRCNT4, 0x0004
        .equiv RERRCNT5, 0x0005
        .equiv RERRCNT6, 0x0006
        .equiv RERRCNT7, 0x0007
        .equiv TERRCNT0, 0x0008
        .equiv TERRCNT1, 0x0009
        .equiv TERRCNT2, 0x000A
        .equiv TERRCNT3, 0x000B
        .equiv TERRCNT4, 0x000C
        .equiv TERRCNT5, 0x000D
        .equiv TERRCNT6, 0x000E
        .equiv TERRCNT7, 0x000F


;----- C1CFG1 Bits -----------------------------------------------------
        .equiv BRP0,    0x0000
        .equiv BRP1,    0x0001
        .equiv BRP2,    0x0002
        .equiv BRP3,    0x0003
        .equiv BRP4,    0x0004
        .equiv BRP5,    0x0005
        .equiv SJW0,    0x0006
        .equiv SJW1,    0x0007


;----- C1CFG2 Bits -----------------------------------------------------
        .equiv SAM,     0x0006
        .equiv SEG2PHTS, 0x0007
        .equiv WAKFIL,  0x000E

        .equiv PRSEG0,  0x0000
        .equiv PRSEG1,  0x0001
        .equiv PRSEG2,  0x0002
        .equiv SEG1PH0, 0x0003
        .equiv SEG1PH1, 0x0004
        .equiv SEG1PH2, 0x0005
        .equiv SEG2PH0, 0x0008
        .equiv SEG2PH1, 0x0009
        .equiv SEG2PH2, 0x000A


;----- C1FEN1 Bits -----------------------------------------------------
        .equiv FLTEN0,  0x0000
        .equiv FLTEN1,  0x0001
        .equiv FLTEN2,  0x0002
        .equiv FLTEN3,  0x0003
        .equiv FLTEN4,  0x0004
        .equiv FLTEN5,  0x0005
        .equiv FLTEN6,  0x0006
        .equiv FLTEN7,  0x0007
        .equiv FLTEN8,  0x0008
        .equiv FLTEN9,  0x0009
        .equiv FLTEN10, 0x000A
        .equiv FLTEN11, 0x000B
        .equiv FLTEN12, 0x000C
        .equiv FLTEN13, 0x000D
        .equiv FLTEN14, 0x000E
        .equiv FLTEN15, 0x000F


;----- C1FMSKSEL1 Bits -----------------------------------------------------
        .equiv F0MSK0,  0x0000
        .equiv F0MSK1,  0x0001
        .equiv F1MSK0,  0x0002
        .equiv F1MSK1,  0x0003
        .equiv F2MSK0,  0x0004
        .equiv F2MSK1,  0x0005
        .equiv F3MSK0,  0x0006
        .equiv F3MSK1,  0x0007
        .equiv F4MSK0,  0x0008
        .equiv F4MSK1,  0x0009
        .equiv F5MSK0,  0x000A
        .equiv F5MSK1,  0x000B
        .equiv F6MSK0,  0x000C
        .equiv F6MSK1,  0x000D
        .equiv F7MSK0,  0x000E
        .equiv F7MSK1,  0x000F


;----- C1FMSKSEL2 Bits -----------------------------------------------------
        .equiv F8MSK0,  0x0000
        .equiv F8MSK1,  0x0001
        .equiv F9MSK0,  0x0002
        .equiv F9MSK1,  0x0003
        .equiv F10MSK0, 0x0004
        .equiv F10MSK1, 0x0005
        .equiv F11MSK0, 0x0006
        .equiv F11MSK1, 0x0007
        .equiv F12MSK0, 0x0008
        .equiv F12MSK1, 0x0009
        .equiv F13MSK0, 0x000A
        .equiv F13MSK1, 0x000B
        .equiv F14MSK0, 0x000C
        .equiv F14MSK1, 0x000D
        .equiv F15MSK0, 0x000E
        .equiv F15MSK1, 0x000F


;----- C1BUFPNT1 Bits -----------------------------------------------------
        .equiv F0BP0,   0x0000
        .equiv F0BP1,   0x0001
        .equiv F0BP2,   0x0002
        .equiv F0BP3,   0x0003
        .equiv F1BP0,   0x0004
        .equiv F1BP1,   0x0005
        .equiv F1BP2,   0x0006
        .equiv F1BP3,   0x0007
        .equiv F2BP0,   0x0008
        .equiv F2BP1,   0x0009
        .equiv F2BP2,   0x000A
        .equiv F2BP3,   0x000B
        .equiv F3BP0,   0x000C
        .equiv F3BP1,   0x000D
        .equiv F3BP2,   0x000E
        .equiv F3BP3,   0x000F


;----- C1RXFUL1 Bits -----------------------------------------------------
        .equiv RXFUL0,  0x0000
        .equiv RXFUL1,  0x0001
        .equiv RXFUL2,  0x0002
        .equiv RXFUL3,  0x0003
        .equiv RXFUL4,  0x0004
        .equiv RXFUL5,  0x0005
        .equiv RXFUL6,  0x0006
        .equiv RXFUL7,  0x0007
        .equiv RXFUL8,  0x0008
        .equiv RXFUL9,  0x0009
        .equiv RXFUL10, 0x000A
        .equiv RXFUL11, 0x000B
        .equiv RXFUL12, 0x000C
        .equiv RXFUL13, 0x000D
        .equiv RXFUL14, 0x000E
        .equiv RXFUL15, 0x000F


;----- C1BUFPNT2 Bits -----------------------------------------------------
        .equiv F4BP0,   0x0000
        .equiv F4BP1,   0x0001
        .equiv F4BP2,   0x0002
        .equiv F4BP3,   0x0003
        .equiv F5BP0,   0x0004
        .equiv F5BP1,   0x0005
        .equiv F5BP2,   0x0006
        .equiv F5BP3,   0x0007
        .equiv F6BP0,   0x0008
        .equiv F6BP1,   0x0009
        .equiv F6BP2,   0x000A
        .equiv F6BP3,   0x000B
        .equiv F7BP0,   0x000C
        .equiv F7BP1,   0x000D
        .equiv F7BP2,   0x000E
        .equiv F7BP3,   0x000F


;----- C1RXFUL2 Bits -----------------------------------------------------
        .equiv RXFUL16, 0x0000
        .equiv RXFUL17, 0x0001
        .equiv RXFUL18, 0x0002
        .equiv RXFUL19, 0x0003
        .equiv RXFUL20, 0x0004
        .equiv RXFUL21, 0x0005
        .equiv RXFUL22, 0x0006
        .equiv RXFUL23, 0x0007
        .equiv RXFUL24, 0x0008
        .equiv RXFUL25, 0x0009
        .equiv RXFUL26, 0x000A
        .equiv RXFUL27, 0x000B
        .equiv RXFUL28, 0x000C
        .equiv RXFUL29, 0x000D
        .equiv RXFUL30, 0x000E
        .equiv RXFUL31, 0x000F


;----- C1BUFPNT3 Bits -----------------------------------------------------
        .equiv F8BP0,   0x0000
        .equiv F8BP1,   0x0001
        .equiv F8BP2,   0x0002
        .equiv F8BP3,   0x0003
        .equiv F9BP0,   0x0004
        .equiv F9BP1,   0x0005
        .equiv F9BP2,   0x0006
        .equiv F9BP3,   0x0007
        .equiv F10BP0,  0x0008
        .equiv F10BP1,  0x0009
        .equiv F10BP2,  0x000A
        .equiv F10BP3,  0x000B
        .equiv F11BP0,  0x000C
        .equiv F11BP1,  0x000D
        .equiv F11BP2,  0x000E
        .equiv F11BP3,  0x000F


;----- C1BUFPNT4 Bits -----------------------------------------------------
        .equiv F12BP0,  0x0000
        .equiv F12BP1,  0x0001
        .equiv F12BP2,  0x0002
        .equiv F12BP3,  0x0003
        .equiv F13BP0,  0x0004
        .equiv F13BP1,  0x0005
        .equiv F13BP2,  0x0006
        .equiv F13BP3,  0x0007
        .equiv F14BP0,  0x0008
        .equiv F14BP1,  0x0009
        .equiv F14BP2,  0x000A
        .equiv F14BP3,  0x000B
        .equiv F15BP0,  0x000C
        .equiv F15BP1,  0x000D
        .equiv F15BP2,  0x000E
        .equiv F15BP3,  0x000F


;----- C1RXOVF1 Bits -----------------------------------------------------
        .equiv RXOVF0,  0x0000
        .equiv RXOVF1,  0x0001
        .equiv RXOVF2,  0x0002
        .equiv RXOVF3,  0x0003
        .equiv RXOVF4,  0x0004
        .equiv RXOVF5,  0x0005
        .equiv RXOVF6,  0x0006
        .equiv RXOVF7,  0x0007
        .equiv RXOVF8,  0x0008
        .equiv RXOVF9,  0x0009
        .equiv RXOVF10, 0x000A
        .equiv RXOVF11, 0x000B
        .equiv RXOVF12, 0x000C
        .equiv RXOVF13, 0x000D
        .equiv RXOVF14, 0x000E
        .equiv RXOVF15, 0x000F


;----- C1RXOVF2 Bits -----------------------------------------------------
        .equiv RXOVF16, 0x0000
        .equiv RXOVF17, 0x0001
        .equiv RXOVF18, 0x0002
        .equiv RXOVF19, 0x0003
        .equiv RXOVF20, 0x0004
        .equiv RXOVF21, 0x0005
        .equiv RXOVF22, 0x0006
        .equiv RXOVF23, 0x0007
        .equiv RXOVF24, 0x0008
        .equiv RXOVF25, 0x0009
        .equiv RXOVF26, 0x000A
        .equiv RXOVF27, 0x000B
        .equiv RXOVF28, 0x000C
        .equiv RXOVF29, 0x000D
        .equiv RXOVF30, 0x000E
        .equiv RXOVF31, 0x000F


;----- C1RXM0SID Bits -----------------------------------------------------
        .equiv MIDE,    0x0003

        .equiv EID16,   0x0000
        .equiv EID17,   0x0001
        .equiv SID0,    0x0005
        .equiv SID1,    0x0006
        .equiv SID2,    0x0007
        .equiv SID3,    0x0008
        .equiv SID4,    0x0009
        .equiv SID5,    0x000A
        .equiv SID6,    0x000B
        .equiv SID7,    0x000C
        .equiv SID8,    0x000D
        .equiv SID9,    0x000E
        .equiv SID10,   0x000F


;----- C1TR01CON Bits -----------------------------------------------------
        .equiv RTREN0,  0x0002
        .equiv TXREQ0,  0x0003
        .equiv TXERR0,  0x0004
        .equiv TXLARB0, 0x0005
        .equiv TXABT0,  0x0006
        .equiv TXEN0,   0x0007
        .equiv RTREN1,  0x000A
        .equiv TXREQ1,  0x000B
        .equiv TXERR1,  0x000C
        .equiv TXLARB1, 0x000D
        .equiv TXABT1,  0x000E
        .equiv TXEN1,   0x000F

        .equiv TX0PRI0, 0x0000
        .equiv TX0PRI1, 0x0001
        .equiv TX1PRI0, 0x0008
        .equiv TX1PRI1, 0x0009


;----- C1RXM0EID Bits -----------------------------------------------------
        .equiv EID0,    0x0000
        .equiv EID1,    0x0001
        .equiv EID2,    0x0002
        .equiv EID3,    0x0003
        .equiv EID4,    0x0004
        .equiv EID5,    0x0005
        .equiv EID6,    0x0006
        .equiv EID7,    0x0007
        .equiv EID8,    0x0008
        .equiv EID9,    0x0009
        .equiv EID10,   0x000A
        .equiv EID11,   0x000B
        .equiv EID12,   0x000C
        .equiv EID13,   0x000D
        .equiv EID14,   0x000E
        .equiv EID15,   0x000F


;----- C1TR23CON Bits -----------------------------------------------------
        .equiv RTREN2,  0x0002
        .equiv TXREQ2,  0x0003
        .equiv TXERR2,  0x0004
        .equiv TXLARB2, 0x0005
        .equiv TXABT2,  0x0006
        .equiv TXEN2,   0x0007
        .equiv RTREN3,  0x000A
        .equiv TXREQ3,  0x000B
        .equiv TXERR3,  0x000C
        .equiv TXLARB3, 0x000D
        .equiv TXABT3,  0x000E
        .equiv TXEN3,   0x000F

        .equiv TX2PRI0, 0x0000
        .equiv TX2PRI1, 0x0001
        .equiv TX3PRI0, 0x0008
        .equiv TX3PRI1, 0x0009


;----- C1RXM1SID Bits -----------------------------------------------------
       ;.equiv MIDE,    0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1TR45CON Bits -----------------------------------------------------
        .equiv RTREN4,  0x0002
        .equiv TXREQ4,  0x0003
        .equiv TXERR4,  0x0004
        .equiv TXLARB4, 0x0005
        .equiv TXABT4,  0x0006
        .equiv TXEN4,   0x0007
        .equiv RTREN5,  0x000A
        .equiv TXREQ5,  0x000B
        .equiv TXERR5,  0x000C
        .equiv TXLARB5, 0x000D
        .equiv TXABT5,  0x000E
        .equiv TXEN5,   0x000F

        .equiv TX4PRI0, 0x0000
        .equiv TX4PRI1, 0x0001
        .equiv TX5PRI0, 0x0008
        .equiv TX5PRI1, 0x0009


;----- C1RXM1EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1TR67CON Bits -----------------------------------------------------
        .equiv RTREN6,  0x0002
        .equiv TXREQ6,  0x0003
        .equiv TXERR6,  0x0004
        .equiv TXLARB6, 0x0005
        .equiv TXABT6,  0x0006
        .equiv TXEN6,   0x0007
        .equiv RTREN7,  0x000A
        .equiv TXREQ7,  0x000B
        .equiv TXERR7,  0x000C
        .equiv TXLARB7, 0x000D
        .equiv TXABT7,  0x000E
        .equiv TXEN7,   0x000F

        .equiv TX6PRI0, 0x0000
        .equiv TX6PRI1, 0x0001
        .equiv TX7PRI0, 0x0008
        .equiv TX7PRI1, 0x0009


;----- C1RXM2SID Bits -----------------------------------------------------
       ;.equiv MIDE,    0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXM2EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF0SID Bits -----------------------------------------------------
        .equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF0EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF1SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF1EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF2SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF2EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF3SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF3EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF4SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF4EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF5SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF5EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF6SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF6EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF7SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF7EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF8SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF8EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF9SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF9EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF10SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF10EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF11SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF11EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF12SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF12EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF13SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF13EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF14SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF14EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- C1RXF15SID Bits -----------------------------------------------------
       ;.equiv EXIDE,   0x0003

       ;.equiv EID16,   0x0000
       ;.equiv EID17,   0x0001
       ;.equiv SID0,    0x0005
       ;.equiv SID1,    0x0006
       ;.equiv SID2,    0x0007
       ;.equiv SID3,    0x0008
       ;.equiv SID4,    0x0009
       ;.equiv SID5,    0x000A
       ;.equiv SID6,    0x000B
       ;.equiv SID7,    0x000C
       ;.equiv SID8,    0x000D
       ;.equiv SID9,    0x000E
       ;.equiv SID10,   0x000F


;----- C1RXF15EID Bits -----------------------------------------------------
       ;.equiv EID0,    0x0000
       ;.equiv EID1,    0x0001
       ;.equiv EID2,    0x0002
       ;.equiv EID3,    0x0003
       ;.equiv EID4,    0x0004
       ;.equiv EID5,    0x0005
       ;.equiv EID6,    0x0006
       ;.equiv EID7,    0x0007
       ;.equiv EID8,    0x0008
       ;.equiv EID9,    0x0009
       ;.equiv EID10,   0x000A
       ;.equiv EID11,   0x000B
       ;.equiv EID12,   0x000C
       ;.equiv EID13,   0x000D
       ;.equiv EID14,   0x000E
       ;.equiv EID15,   0x000F


;----- P2TCON Bits -----------------------------------------------------
       ;.equiv PTSIDL,  0x000D
        .equiv PTEN_P2TCON, 0x000F

       ;.equiv PTMOD0,  0x0000
       ;.equiv PTMOD1,  0x0001
       ;.equiv PTCKPS0, 0x0002
       ;.equiv PTCKPS1, 0x0003
       ;.equiv PTOPS0,  0x0004
       ;.equiv PTOPS1,  0x0005
       ;.equiv PTOPS2,  0x0006
       ;.equiv PTOPS3,  0x0007


;----- P2TMR Bits -----------------------------------------------------
       ;.equiv PTDIR,   0x000F


;----- P2SECMP Bits -----------------------------------------------------
       ;.equiv SEVTDIR, 0x000F


;----- PWM2CON1 Bits -----------------------------------------------------
       ;.equiv PEN1L,   0x0000
       ;.equiv PEN1H,   0x0004
       ;.equiv PMOD1,   0x0008


;----- PWM2CON2 Bits -----------------------------------------------------
       ;.equiv UDIS,    0x0000
       ;.equiv OSYNC,   0x0001
       ;.equiv IUE,     0x0002

       ;.equiv SEVOPS0, 0x0008
       ;.equiv SEVOPS1, 0x0009
       ;.equiv SEVOPS2, 0x000A
       ;.equiv SEVOPS3, 0x000B


;----- P2DTCON1 Bits -----------------------------------------------------
       ;.equiv DTA0,    0x0000
       ;.equiv DTA1,    0x0001
       ;.equiv DTA2,    0x0002
       ;.equiv DTA3,    0x0003
       ;.equiv DTA4,    0x0004
       ;.equiv DTA5,    0x0005
       ;.equiv DTAPS0,  0x0006
       ;.equiv DTAPS1,  0x0007
       ;.equiv DTB0,    0x0008
       ;.equiv DTB1,    0x0009
       ;.equiv DTB2,    0x000A
       ;.equiv DTB3,    0x000B
       ;.equiv DTB4,    0x000C
       ;.equiv DTB5,    0x000D
       ;.equiv DTBPS0,  0x000E
       ;.equiv DTBPS1,  0x000F


;----- P2DTCON2 Bits -----------------------------------------------------
       ;.equiv DTS1I,   0x0000
       ;.equiv DTS1A,   0x0001


;----- P2FLTACON Bits -----------------------------------------------------
       ;.equiv FAEN1,   0x0000
       ;.equiv FLTAM,   0x0007
       ;.equiv FAOV1L,  0x0008
       ;.equiv FAOV1H,  0x0009


;----- P2OVDCON Bits -----------------------------------------------------
       ;.equiv POUT1L,  0x0000
       ;.equiv POUT1H,  0x0001
       ;.equiv POVD1L,  0x0008
       ;.equiv POVD1H,  0x0009


;----- PMCON Bits -----------------------------------------------------
        .equiv RDSP,    0x0000
        .equiv WRSP,    0x0001
        .equiv BEP,     0x0002
        .equiv CS1P,    0x0003
        .equiv ALP,     0x0005
        .equiv CSF0,    0x0006
        .equiv CSF1,    0x0007
        .equiv PTRDEN,  0x0008
        .equiv PTWREN,  0x0009
        .equiv PTBEEN,  0x000A
        .equiv ADRMUX0, 0x000B
        .equiv ADRMUX1, 0x000C
        .equiv PSIDL,   0x000D
        .equiv PMPEN,   0x000F



;----- PMMODE Bits -----------------------------------------------------
        .equiv WAITE0,  0x0000
        .equiv WAITE1,  0x0001
        .equiv WAITB0,  0x0006
        .equiv WAITB1,  0x0007
        .equiv MODE0_PMMODE, 0x0008
        .equiv MODE1_PMMODE, 0x0009
       ;.equiv MODE16,  0x000A
        .equiv INCM0,   0x000B
        .equiv INCM1,   0x000C
        .equiv IRQM0,   0x000D
        .equiv IRQM1,   0x000E
        .equiv BUSY,    0x000F

        .equiv WAITM0,  0x0002
        .equiv WAITM1,  0x0003
        .equiv WAITM2,  0x0004
        .equiv WAITM3,  0x0005


;----- PMADDR Bits -----------------------------------------------------
        .equiv CS1,     0x000E
        .equiv ADDR15,  0x000F

        .equiv ADDR0,   0x0000
        .equiv ADDR1,   0x0001
        .equiv ADDR2,   0x0002
        .equiv ADDR3,   0x0003
        .equiv ADDR4,   0x0004
        .equiv ADDR5,   0x0005
        .equiv ADDR6,   0x0006
        .equiv ADDR7,   0x0007
        .equiv ADDR8,   0x0008
        .equiv ADDR9,   0x0009
        .equiv ADDR10,  0x000A
        .equiv ADDR11,  0x000B
        .equiv ADDR12,  0x000C
        .equiv ADDR13,  0x000D


;----- PMAEN Bits -----------------------------------------------------
        .equiv PTEN14,  0x000E

        .equiv PTEN0,   0x0000
        .equiv PTEN1,   0x0001


;----- PMSTAT Bits -----------------------------------------------------
        .equiv OB0E,    0x0000
        .equiv OB1E,    0x0001
        .equiv OB2E,    0x0002
        .equiv OB3E,    0x0003
        .equiv OBUF,    0x0006
        .equiv OBE,     0x0007
        .equiv IB0F,    0x0008
        .equiv IB1F,    0x0009
        .equiv IB2F,    0x000A
        .equiv IB3F,    0x000B
        .equiv IBOV,    0x000E
        .equiv IBF,     0x000F


;----- ALCFGRPT Bits -----------------------------------------------------
        .equiv ALRMPTR0, 0x0008
        .equiv ALRMPTR1, 0x0009
        .equiv CHIME,   0x000E
        .equiv ALRMEN,  0x000F

        .equiv ARPT0,   0x0000
        .equiv ARPT1,   0x0001
        .equiv ARPT2,   0x0002
        .equiv ARPT3,   0x0003
        .equiv ARPT4,   0x0004
        .equiv ARPT5,   0x0005
        .equiv ARPT6,   0x0006
        .equiv ARPT7,   0x0007
        .equiv AMASK0,  0x000A
        .equiv AMASK1,  0x000B
        .equiv AMASK2,  0x000C
        .equiv AMASK3,  0x000D


;----- RCFGCAL Bits -----------------------------------------------------
        .equiv RTCPTR0, 0x0008
        .equiv RTCPTR1, 0x0009
        .equiv RTCOE,   0x000A
        .equiv HALFSEC, 0x000B
        .equiv RTCSYNC, 0x000C
        .equiv RTCWREN, 0x000D
        .equiv RTCEN,   0x000F

        .equiv CAL0,    0x0000
        .equiv CAL1,    0x0001
        .equiv CAL2,    0x0002
        .equiv CAL3,    0x0003
        .equiv CAL4,    0x0004
        .equiv CAL5,    0x0005
        .equiv CAL6,    0x0006
        .equiv CAL7,    0x0007


;----- CMCON Bits -----------------------------------------------------
        .equiv C1POS,   0x0000
        .equiv C1NEG,   0x0001
        .equiv C2POS,   0x0002
        .equiv C2NEG,   0x0003
        .equiv C1INV,   0x0004
        .equiv C2INV,   0x0005
        .equiv C1OUT,   0x0006
        .equiv C2OUT,   0x0007
        .equiv C1OUTEN, 0x0008
        .equiv C2OUTEN, 0x0009
        .equiv C1EN,    0x000A
        .equiv C2EN,    0x000B
        .equiv C1EVT,   0x000C
        .equiv C2EVT,   0x000D
        .equiv CMIDL,   0x000F


;----- CVRCON Bits -----------------------------------------------------
        .equiv CVRSS,   0x0004
        .equiv CVRR,    0x0005
        .equiv CVROE,   0x0006
        .equiv CVREN,   0x0007

        .equiv CVR0,    0x0000
        .equiv CVR1,    0x0001
        .equiv CVR2,    0x0002
        .equiv CVR3,    0x0003


;----- CRCCON Bits -----------------------------------------------------
        .equiv CRCGO,   0x0004
        .equiv CRCMPT,  0x0006
        .equiv CRCFUL,  0x0007
       ;.equiv CSIDL,   0x000D

        .equiv PLEN0,   0x0000
        .equiv PLEN1,   0x0001
        .equiv PLEN2,   0x0002
        .equiv PLEN3,   0x0003
        .equiv VWORD0,  0x0008
        .equiv VWORD1,  0x0009
        .equiv VWORD2,  0x000A
        .equiv VWORD3,  0x000B
        .equiv VWORD4,  0x000C


;----- RPINR0 Bits -----------------------------------------------------
        .equiv INT1R0,  0x0008
        .equiv INT1R1,  0x0009
        .equiv INT1R2,  0x000A
        .equiv INT1R3,  0x000B
        .equiv INT1R4,  0x000C


;----- RPINR1 Bits -----------------------------------------------------
        .equiv INT2R0,  0x0000
        .equiv INT2R1,  0x0001
        .equiv INT2R2,  0x0002
        .equiv INT2R3,  0x0003
        .equiv INT2R4,  0x0004


;----- RPINR3 Bits -----------------------------------------------------
        .equiv T2CKR0,  0x0000
        .equiv T2CKR1,  0x0001
        .equiv T2CKR2,  0x0002
        .equiv T2CKR3,  0x0003
        .equiv T2CKR4,  0x0004
        .equiv T3CKR0,  0x0008
        .equiv T3CKR1,  0x0009
        .equiv T3CKR2,  0x000A
        .equiv T3CKR3,  0x000B
        .equiv T3CKR4,  0x000C


;----- RPINR4 Bits -----------------------------------------------------
        .equiv T4CKR0,  0x0000
        .equiv T4CKR1,  0x0001
        .equiv T4CKR2,  0x0002
        .equiv T4CKR3,  0x0003
        .equiv T4CKR4,  0x0004
        .equiv T5CKR0,  0x0008
        .equiv T5CKR1,  0x0009
        .equiv T5CKR2,  0x000A
        .equiv T5CKR3,  0x000B
        .equiv T5CKR4,  0x000C


;----- RPINR7 Bits -----------------------------------------------------
        .equiv IC1R0,   0x0000
        .equiv IC1R1,   0x0001
        .equiv IC1R2,   0x0002
        .equiv IC1R3,   0x0003
        .equiv IC1R4,   0x0004
        .equiv IC2R0,   0x0008
        .equiv IC2R1,   0x0009
        .equiv IC2R2,   0x000A
        .equiv IC2R3,   0x000B
        .equiv IC2R4,   0x000C


;----- RPINR10 Bits -----------------------------------------------------
        .equiv IC7R0,   0x0000
        .equiv IC7R1,   0x0001
        .equiv IC7R2,   0x0002
        .equiv IC7R3,   0x0003
        .equiv IC7R4,   0x0004
        .equiv IC8R0,   0x0008
        .equiv IC8R1,   0x0009
        .equiv IC8R2,   0x000A
        .equiv IC8R3,   0x000B
        .equiv IC8R4,   0x000C


;----- RPINR11 Bits -----------------------------------------------------
        .equiv OCFAR0,  0x0000
        .equiv OCFAR1,  0x0001
        .equiv OCFAR2,  0x0002
        .equiv OCFAR3,  0x0003
        .equiv OCFAR4,  0x0004


;----- RPINR12 Bits -----------------------------------------------------
        .equiv FLTA1R0, 0x0000
        .equiv FLTA1R1, 0x0001
        .equiv FLTA1R2, 0x0002
        .equiv FLTA1R3, 0x0003
        .equiv FLTA1R4, 0x0004


;----- RPINR13 Bits -----------------------------------------------------
        .equiv FLTA2R0, 0x0000
        .equiv FLTA2R1, 0x0001
        .equiv FLTA2R2, 0x0002
        .equiv FLTA2R3, 0x0003
        .equiv FLTA2R4, 0x0004


;----- RPINR14 Bits -----------------------------------------------------
        .equiv QEA1R0,  0x0000
        .equiv QEA1R1,  0x0001
        .equiv QEA1R2,  0x0002
        .equiv QEA1R3,  0x0003
        .equiv QEA1R4,  0x0004
        .equiv QEB1R0,  0x0008
        .equiv QEB1R1,  0x0009
        .equiv QEB1R2,  0x000A
        .equiv QEB1R3,  0x000B
        .equiv QEB1R4,  0x000C


;----- RPINR15 Bits -----------------------------------------------------
        .equiv INDX1R0, 0x0000
        .equiv INDX1R1, 0x0001
        .equiv INDX1R2, 0x0002
        .equiv INDX1R3, 0x0003
        .equiv INDX1R4, 0x0004


;----- RPINR16 Bits -----------------------------------------------------
        .equiv QEA2R0,  0x0000
        .equiv QEA2R1,  0x0001
        .equiv QEA2R2,  0x0002
        .equiv QEA2R3,  0x0003
        .equiv QEA2R4,  0x0004
        .equiv QEB2R0,  0x0008
        .equiv QEB2R1,  0x0009
        .equiv QEB2R2,  0x000A
        .equiv QEB2R3,  0x000B
        .equiv QEB2R4,  0x000C


;----- RPINR17 Bits -----------------------------------------------------
        .equiv INDX2R0, 0x0000
        .equiv INDX2R1, 0x0001
        .equiv INDX2R2, 0x0002
        .equiv INDX2R3, 0x0003
        .equiv INDX2R4, 0x0004


;----- RPINR18 Bits -----------------------------------------------------
        .equiv U1RXR0,  0x0000
        .equiv U1RXR1,  0x0001
        .equiv U1RXR2,  0x0002
        .equiv U1RXR3,  0x0003
        .equiv U1RXR4,  0x0004
        .equiv U1CTSR0, 0x0008
        .equiv U1CTSR1, 0x0009
        .equiv U1CTSR2, 0x000A
        .equiv U1CTSR3, 0x000B
        .equiv U1CTSR4, 0x000C


;----- RPINR19 Bits -----------------------------------------------------
        .equiv U2RXR0,  0x0000
        .equiv U2RXR1,  0x0001
        .equiv U2RXR2,  0x0002
        .equiv U2RXR3,  0x0003
        .equiv U2RXR4,  0x0004
        .equiv U2CTSR0, 0x0008
        .equiv U2CTSR1, 0x0009
        .equiv U2CTSR2, 0x000A
        .equiv U2CTSR3, 0x000B
        .equiv U2CTSR4, 0x000C


;----- RPINR20 Bits -----------------------------------------------------
        .equiv SDI1R0,  0x0000
        .equiv SDI1R1,  0x0001
        .equiv SDI1R2,  0x0002
        .equiv SDI1R3,  0x0003
        .equiv SDI1R4,  0x0004
        .equiv SCK1R0,  0x0008
        .equiv SCK1R1,  0x0009
        .equiv SCK1R2,  0x000A
        .equiv SCK1R3,  0x000B
        .equiv SCK1R4,  0x000C


;----- RPINR21 Bits -----------------------------------------------------
        .equiv SS1R0,   0x0000
        .equiv SS1R1,   0x0001
        .equiv SS1R2,   0x0002
        .equiv SS1R3,   0x0003
        .equiv SS1R4,   0x0004


;----- RPINR22 Bits -----------------------------------------------------
        .equiv SDI2R0,  0x0000
        .equiv SDI2R1,  0x0001
        .equiv SDI2R2,  0x0002
        .equiv SDI2R3,  0x0003
        .equiv SDI2R4,  0x0004
        .equiv SCK2R0,  0x0008
        .equiv SCK2R1,  0x0009
        .equiv SCK2R2,  0x000A
        .equiv SCK2R3,  0x000B
        .equiv SCK2R4,  0x000C


;----- RPINR23 Bits -----------------------------------------------------
        .equiv SS2R0,   0x0000
        .equiv SS2R1,   0x0001
        .equiv SS2R2,   0x0002
        .equiv SS2R3,   0x0003
        .equiv SS2R4,   0x0004


;----- RPINR26 Bits -----------------------------------------------------
        .equiv C1RXR0,  0x0000
        .equiv C1RXR1,  0x0001
        .equiv C1RXR2,  0x0002
        .equiv C1RXR3,  0x0003
        .equiv C1RXR4,  0x0004


;----- RPOR0 Bits -----------------------------------------------------
        .equiv RP0R0,   0x0000
        .equiv RP0R1,   0x0001
        .equiv RP0R2,   0x0002
        .equiv RP0R3,   0x0003
        .equiv RP0R4,   0x0004
        .equiv RP1R0,   0x0008
        .equiv RP1R1,   0x0009
        .equiv RP1R2,   0x000A
        .equiv RP1R3,   0x000B
        .equiv RP1R4,   0x000C


;----- RPOR1 Bits -----------------------------------------------------
        .equiv RP2R0,   0x0000
        .equiv RP2R1,   0x0001
        .equiv RP2R2,   0x0002
        .equiv RP2R3,   0x0003
        .equiv RP2R4,   0x0004
        .equiv RP3R0,   0x0008
        .equiv RP3R1,   0x0009
        .equiv RP3R2,   0x000A
        .equiv RP3R3,   0x000B
        .equiv RP3R4,   0x000C


;----- RPOR2 Bits -----------------------------------------------------
        .equiv RP4R0,   0x0000
        .equiv RP4R1,   0x0001
        .equiv RP4R2,   0x0002
        .equiv RP4R3,   0x0003
        .equiv RP4R4,   0x0004
        .equiv RP5R0,   0x0008
        .equiv RP5R1,   0x0009
        .equiv RP5R2,   0x000A
        .equiv RP5R3,   0x000B
        .equiv RP5R4,   0x000C


;----- RPOR3 Bits -----------------------------------------------------
        .equiv RP6R0,   0x0000
        .equiv RP6R1,   0x0001
        .equiv RP6R2,   0x0002
        .equiv RP6R3,   0x0003
        .equiv RP6R4,   0x0004
        .equiv RP7R0,   0x0008
        .equiv RP7R1,   0x0009
        .equiv RP7R2,   0x000A
        .equiv RP7R3,   0x000B
        .equiv RP7R4,   0x000C


;----- RPOR4 Bits -----------------------------------------------------
        .equiv RP8R0,   0x0000
        .equiv RP8R1,   0x0001
        .equiv RP8R2,   0x0002
        .equiv RP8R3,   0x0003
        .equiv RP8R4,   0x0004
        .equiv RP9R0,   0x0008
        .equiv RP9R1,   0x0009
        .equiv RP9R2,   0x000A
        .equiv RP9R3,   0x000B
        .equiv RP9R4,   0x000C


;----- RPOR5 Bits -----------------------------------------------------
        .equiv RP10R0,  0x0000
        .equiv RP10R1,  0x0001
        .equiv RP10R2,  0x0002
        .equiv RP10R3,  0x0003
        .equiv RP10R4,  0x0004
        .equiv RP11R0,  0x0008
        .equiv RP11R1,  0x0009
        .equiv RP11R2,  0x000A
        .equiv RP11R3,  0x000B
        .equiv RP11R4,  0x000C


;----- RPOR6 Bits -----------------------------------------------------
        .equiv RP12R0,  0x0000
        .equiv RP12R1,  0x0001
        .equiv RP12R2,  0x0002
        .equiv RP12R3,  0x0003
        .equiv RP12R4,  0x0004
        .equiv RP13R0,  0x0008
        .equiv RP13R1,  0x0009
        .equiv RP13R2,  0x000A
        .equiv RP13R3,  0x000B
        .equiv RP13R4,  0x000C


;----- RPOR7 Bits -----------------------------------------------------
        .equiv RP14R0,  0x0000
        .equiv RP14R1,  0x0001
        .equiv RP14R2,  0x0002
        .equiv RP14R3,  0x0003
        .equiv RP14R4,  0x0004
        .equiv RP15R0,  0x0008
        .equiv RP15R1,  0x0009
        .equiv RP15R2,  0x000A
        .equiv RP15R3,  0x000B
        .equiv RP15R4,  0x000C


;----- RPOR8 Bits -----------------------------------------------------
        .equiv RP16R0,  0x0000
        .equiv RP16R1,  0x0001
        .equiv RP16R2,  0x0002
        .equiv RP16R3,  0x0003
        .equiv RP16R4,  0x0004
        .equiv RP17R0,  0x0008
        .equiv RP17R1,  0x0009
        .equiv RP17R2,  0x000A
        .equiv RP17R3,  0x000B
        .equiv RP17R4,  0x000C


;----- RPOR9 Bits -----------------------------------------------------
        .equiv RP18R0,  0x0000
        .equiv RP18R1,  0x0001
        .equiv RP18R2,  0x0002
        .equiv RP18R3,  0x0003
        .equiv RP18R4,  0x0004
        .equiv RP19R0,  0x0008
        .equiv RP19R1,  0x0009
        .equiv RP19R2,  0x000A
        .equiv RP19R3,  0x000B
        .equiv RP19R4,  0x000C


;----- RPOR10 Bits -----------------------------------------------------
        .equiv RP20R0,  0x0000
        .equiv RP20R1,  0x0001
        .equiv RP20R2,  0x0002
        .equiv RP20R3,  0x0003
        .equiv RP20R4,  0x0004
        .equiv RP21R0,  0x0008
        .equiv RP21R1,  0x0009
        .equiv RP21R2,  0x000A
        .equiv RP21R3,  0x000B
        .equiv RP21R4,  0x000C


;----- RPOR11 Bits -----------------------------------------------------
        .equiv RP22R0,  0x0000
        .equiv RP22R1,  0x0001
        .equiv RP22R2,  0x0002
        .equiv RP22R3,  0x0003
        .equiv RP22R4,  0x0004
        .equiv RP23R0,  0x0008
        .equiv RP23R1,  0x0009
        .equiv RP23R2,  0x000A
        .equiv RP23R3,  0x000B
        .equiv RP23R4,  0x000C


;----- RPOR12 Bits -----------------------------------------------------
        .equiv RP24R0,  0x0000
        .equiv RP24R1,  0x0001
        .equiv RP24R2,  0x0002
        .equiv RP24R3,  0x0003
        .equiv RP24R4,  0x0004
        .equiv RP25R0,  0x0008
        .equiv RP25R1,  0x0009
        .equiv RP25R2,  0x000A
        .equiv RP25R3,  0x000B
        .equiv RP25R4,  0x000C


;----- RCON Bits -----------------------------------------------------
        .equiv POR,     0x0000
        .equiv BOR,     0x0001
        .equiv IDLE,    0x0002
        .equiv SLEEP,   0x0003
        .equiv WDTO,    0x0004
        .equiv SWDTEN,  0x0005
        .equiv SWR,     0x0006
        .equiv EXTR,    0x0007
        .equiv VREGS,   0x0008
        .equiv CM,      0x0009
        .equiv IOPUWR,  0x000E
        .equiv TRAPR,   0x000F


;----- OSCCON Bits -----------------------------------------------------
        .equiv OSWEN,   0x0000
        .equiv LPOSCEN, 0x0001
        .equiv CF,      0x0003
        .equiv LOCK,    0x0005
        .equiv IOLOCK,  0x0006
        .equiv CLKLOCK, 0x0007

        .equiv NOSC0,   0x0008
        .equiv NOSC1,   0x0009
        .equiv NOSC2,   0x000A
        .equiv COSC0,   0x000C
        .equiv COSC1,   0x000D
        .equiv COSC2,   0x000E


;----- CLKDIV Bits -----------------------------------------------------
        .equiv DOZEN,   0x000B
        .equiv ROI,     0x000F

        .equiv PLLPRE0, 0x0000
        .equiv PLLPRE1, 0x0001
        .equiv PLLPRE2, 0x0002
        .equiv PLLPRE3, 0x0003
        .equiv PLLPRE4, 0x0004
        .equiv PLLPOST0, 0x0006
        .equiv PLLPOST1, 0x0007
        .equiv FRCDIV0, 0x0008
        .equiv FRCDIV1, 0x0009
        .equiv FRCDIV2, 0x000A
        .equiv DOZE0,   0x000C
        .equiv DOZE1,   0x000D
        .equiv DOZE2,   0x000E


;----- PLLFBD Bits -----------------------------------------------------
        .equiv PLLDIV0, 0x0000
        .equiv PLLDIV1, 0x0001
        .equiv PLLDIV2, 0x0002
        .equiv PLLDIV3, 0x0003
        .equiv PLLDIV4, 0x0004
        .equiv PLLDIV5, 0x0005
        .equiv PLLDIV6, 0x0006
        .equiv PLLDIV7, 0x0007
        .equiv PLLDIV8, 0x0008


;----- OSCTUN Bits -----------------------------------------------------
        .equiv TUN0,    0x0000
        .equiv TUN1,    0x0001
        .equiv TUN2,    0x0002
        .equiv TUN3,    0x0003
        .equiv TUN4,    0x0004
        .equiv TUN5,    0x0005


;----- ACLKCON Bits -----------------------------------------------------
        .equiv ASRCSEL, 0x0007
        .equiv SELACLK, 0x000D

        .equiv APSTSCLR0, 0x0008
        .equiv APSTSCLR1, 0x0009
        .equiv APSTSCLR2, 0x000A
        .equiv AOSCMD0, 0x000B
        .equiv AOSCMD1, 0x000C


;----- BSRAM Bits -----------------------------------------------------
        .equiv RL_BSR,  0x0000
        .equiv IR_BSR,  0x0001
        .equiv IW_BSR,  0x0002


;----- SSRAM Bits -----------------------------------------------------
        .equiv RL_SSR,  0x0000
        .equiv IR_SSR,  0x0001
        .equiv IW_SSR,  0x0002


;----- NVMCON Bits -----------------------------------------------------
        .equiv ERASE,   0x0006
        .equiv WRERR,   0x000D
        .equiv WREN,    0x000E
        .equiv WR,      0x000F

        .equiv NVMOP0,  0x0000
        .equiv NVMOP1,  0x0001
        .equiv NVMOP2,  0x0002
        .equiv NVMOP3,  0x0003


;----- PMD1 Bits -----------------------------------------------------
        .equiv AD1MD,   0x0000
        .equiv C1MD,    0x0001
        .equiv SPI1MD,  0x0003
        .equiv SPI2MD,  0x0004
        .equiv U1MD,    0x0005
        .equiv U2MD,    0x0006
        .equiv I2C1MD,  0x0007
        .equiv PWM1MD,  0x0009
        .equiv QEI1MD,  0x000A
        .equiv T1MD,    0x000B
        .equiv T2MD,    0x000C
        .equiv T3MD,    0x000D
        .equiv T4MD,    0x000E
        .equiv T5MD,    0x000F


;----- PMD2 Bits -----------------------------------------------------
        .equiv OC1MD,   0x0000
        .equiv OC2MD,   0x0001
        .equiv OC3MD,   0x0002
        .equiv OC4MD,   0x0003
        .equiv IC1MD,   0x0008
        .equiv IC2MD,   0x0009
        .equiv IC7MD,   0x000E
        .equiv IC8MD,   0x000F


;----- PMD3 Bits -----------------------------------------------------
        .equiv PWM2MD,  0x0004
        .equiv QEI2MD,  0x0005
        .equiv CRCMD,   0x0007
        .equiv PMPMD,   0x0008
        .equiv RTCCMD,  0x0009
        .equiv CMPMD,   0x000A




;  Some useful macros for PWRSAV instructions

   .equiv SLEEP_MODE, 0x0
   .equiv IDLE_MODE, 0x1


;==========================================================================
;
;   Configuration Words
;
;   Configuration words exist in Program Space and their locations are
;   defined in the device linker script. They can be set in source code
;   or in the MPLAB IDE. Each configuration word should be specified
;   only once (multiple settings may be combined.)
;
;==========================================================================
;
;  Setting configuration words using macros:
;
;  The following macro named 'config' can be used to set configuration words:
;
        .macro config REG, VALUE
        .pushsection \REG.sec, code
        .global \REG
\REG:   .pword \VALUE
        .popsection
        .endm
;
;  For example, to set CONFIG_REG using the macro above, the following line
;  can be pasted only at the beginning of the assembly source code,
;  immediately below the '.include' directive.
;
;        config __CONFIG_REG, SETTING_A & SETTING_B
;
;  Note that the 'config' macro takes two arguments: the first is the name
;  of a configuration word (in this case, __CONFIG_REG), the second argument
;  is a boolean expression that may include multiple settings.
;  The example above would enable SETTING_A and also SETTING_B.
;
;  A description of all possible settings for each configuration word
;  appears below.
;
;==========================================================================
;
;  Setting configuration words without using macros:
;
;  To set configuration words without using the 'config' macro,
;  use the following format:
;
;           .section __CONFIG_REG.sec, code
;           .global __CONFIG_REG
;__CONFIG_REG: .pword SETTING_A & SETTING_B
;
;  This source code is equivalent to the expanded macro from the previous
;  example.
;
;==========================================================================


;----- FBS (0xf80000) --------------------------------------------------
;
;  The following settings are available for FBS:
;
;   Boot Segment Data Ram:
;     RBS_LARGE_RAM        Large Sized Boot Ram
;     RBS_MEDIUM_RAM       Medium Sized Boot Ram 
;     RBS_SMALL_RAM        Small Sized Boot Ram
;     RBS_NO_RAM           No Boot Ram
;
;   Boot Segment Program Memory:
;     BSS_HIGH_LARGE_BOOT_CODE High Security Lar Boot Flash 
;     BSS_LARGE_FLASH_HIGH  High Security Lar Boot Flash 
;     BSS_HIGH_MEDIUM_BOOT_CODE High Security Med Boot Flash 
;     BSS_MEDIUM_FLASH_HIGH High Security Med Boot Flash 
;     BSS_HIGH_SMALL_BOOT_CODE High Security Small Boot Flash 
;     BSS_SMALL_FLASH_HIGH  High Security Small Boot Flash 
;     BSS_LARGE_FLASH_STD   Standard Security Lar Boot Flash 
;     BSS_STRD_LARGE_BOOT_CODE Standard Security Lar Boot Flash 
;     BSS_MEDIUM_FLASH_STD  Standard Security Med Boot Flash 
;     BSS_STRD_MEDIUM_BOOT_CODE Standard Security Med Boot Flash 
;     BSS_SMALL_FLASH_STD  Standard Security Small Boot Flash
;     BSS_STRD_SMALL_BOOT_CODEStandard Security Small Boot Flash
;     BSS_NO_BOOT_CODE     No Boot Segment Program Memory
;     BSS_NO_FLASH         No Boot Segment Program Memory
;
;    Write Protect :
;     BWRP_WRPROTECT_ON     Enabled 
;     BWRP_WRPROTECT_OFF    Disabled 
;
        .equiv RBS_LARGE_RAM,   0xFF3F ; Large Sized Boot Ram
        .equiv RBS_MEDIUM_RAM,  0xFF7F ; Medium Sized Boot Ram 
        .equiv RBS_SMALL_RAM,   0xFFBF ; Small Sized Boot Ram
        .equiv RBS_NO_RAM,      0xFFFF ; No Boot Ram

        .equiv BSS_HIGH_LARGE_BOOT_CODE, 0xFFF1 ;  High Security Lar Boot Flash 
        .equiv BSS_LARGE_FLASH_HIGH, 0xFFF1 ;  High Security Lar Boot Flash 
        .equiv BSS_HIGH_MEDIUM_BOOT_CODE, 0xFFF3 ;  High Security Med Boot Flash 
        .equiv BSS_MEDIUM_FLASH_HIGH, 0xFFF3 ;  High Security Med Boot Flash 
        .equiv BSS_HIGH_SMALL_BOOT_CODE, 0xFFF5 ;  High Security Small Boot Flash 
        .equiv BSS_SMALL_FLASH_HIGH, 0xFFF5 ;  High Security Small Boot Flash 
        .equiv BSS_LARGE_FLASH_STD, 0xFFF9 ;  Standard Security Lar Boot Flash 
        .equiv BSS_STRD_LARGE_BOOT_CODE, 0xFFF9 ;  Standard Security Lar Boot Flash 
        .equiv BSS_MEDIUM_FLASH_STD, 0xFFFB ;  Standard Security Med Boot Flash 
        .equiv BSS_STRD_MEDIUM_BOOT_CODE, 0xFFFB ;  Standard Security Med Boot Flash 
        .equiv BSS_SMALL_FLASH_STD, 0xFFFD ; Standard Security Small Boot Flash
        .equiv BSS_STRD_SMALL_BOOT_CODE, 0xFFFD ; Standard Security Small Boot Flash
        .equiv BSS_NO_BOOT_CODE, 0xFFFF ; No Boot Segment Program Memory
        .equiv BSS_NO_FLASH,    0xFFFF ; No Boot Segment Program Memory

        .equiv BWRP_WRPROTECT_ON, 0xFFFE ;  Enabled 
        .equiv BWRP_WRPROTECT_OFF, 0xFFFF ;  Disabled 


;----- FSS (0xf80002) --------------------------------------------------
;
;  The following settings are available for FSS:
;
;   Secure Segment Data Ram:
;     RSS_LARGE_RAM         Large Sized Secure Ram 
;     RSS_MEDIUM_RAM        Medium Sized Secure Ram 
;     RSS_SMALL_RAM         Small Sized Secure Ram 
;     RSS_NO_RAM           No Secure Ram
;
;   Secure Segment Program Memory:
;     SSS_LARGE_FLASH_HIGH  High Security Lar Secure Flash 
;     SSS_MEDIUM_FLASH_HIGH High Security Med Secure Flash 
;     SSS_SMALL_FLASH_HIGH  High Security Small Secure Flash 
;     SSS_LARGE_FLASH_STD   Standard Security Large Secure Flash 
;     SSS_MEDIUM_FLASH_STD  Standard Security Med Secure Flash 
;     SSS_SMALL_FLASH_STD  Standard Security Small Secure Flash
;     SSS_NO_FLASH         No Secure Segment
;
;    Write Protect :
;     SWRP_WRPROTECT_ON     Enabled 
;     SWRP_WRPROTECT_OFF    Disabled 
;
        .equiv RSS_LARGE_RAM,   0xFF3F ;  Large Sized Secure Ram 
        .equiv RSS_MEDIUM_RAM,  0xFF7F ;  Medium Sized Secure Ram 
        .equiv RSS_SMALL_RAM,   0xFFBF ;  Small Sized Secure Ram 
        .equiv RSS_NO_RAM,      0xFFFF ; No Secure Ram

        .equiv SSS_LARGE_FLASH_HIGH, 0xFFF1 ;  High Security Lar Secure Flash 
        .equiv SSS_MEDIUM_FLASH_HIGH, 0xFFF3 ;  High Security Med Secure Flash 
        .equiv SSS_SMALL_FLASH_HIGH, 0xFFF5 ;  High Security Small Secure Flash 
        .equiv SSS_LARGE_FLASH_STD, 0xFFF9 ;  Standard Security Large Secure Flash 
        .equiv SSS_MEDIUM_FLASH_STD, 0xFFFB ;  Standard Security Med Secure Flash 
        .equiv SSS_SMALL_FLASH_STD, 0xFFFD ; Standard Security Small Secure Flash
        .equiv SSS_NO_FLASH,    0xFFFF ; No Secure Segment

        .equiv SWRP_WRPROTECT_ON, 0xFFFE ;  Enabled 
        .equiv SWRP_WRPROTECT_OFF, 0xFFFF ;  Disabled 


;----- FGS (0xf80004) --------------------------------------------------
;
;  The following settings are available for FGS:
;
;   Code Protect:
;     GSS_HIGH              high security protect on 
;     GSS_STD               standard security code protect on 
;     GSS_OFF              code protect off
;
;   Code Protect:
;     GCP_ON               Enabled
;     GCP_OFF              Disabled
;
;   Write Protect:
;     GWRP_ON              Enabled
;     GWRP_OFF             Disabled
;
        .equiv GSS_HIGH,        0xFFFB ;  high security protect on 
        .equiv GSS_STD,         0xFFFD ;  standard security code protect on 
        .equiv GSS_OFF,         0xFFFF ; code protect off

        .equiv GCP_ON,          0xFFFD ; Enabled
        .equiv GCP_OFF,         0xFFFF ; Disabled

        .equiv GWRP_ON,         0xFFFE ; Enabled
        .equiv GWRP_OFF,        0xFFFF ; Disabled


;----- FOSCSEL (0xf80006) --------------------------------------------------
;
;  The following settings are available for FOSCSEL:
;
;   Oscillator Source Selection:
;     FNOSC_FRC            Fast RC oscillator
;     FNOSC_FRCPLL         Fast RC oscillator w/ divide and PLL
;     FNOSC_PRI            Primary oscillator (XT, HS, EC)
;     FNOSC_PRIPLL         Primary oscillator (XT, HS, EC) w/ PLL
;     FNOSC_SOSC           Secondary oscillator
;     FNOSC_LPRC           Low power RC oscillator
;     FNOSC_FRCDIV16       Fast RC oscillator w/ divide by 16
;     FNOSC_LPRCDIVN        Low power Fast RC oscillator w/divide by N
;
;   Two-speed Oscillator Startup :
;     IESO_OFF             Disabled
;     IESO_ON              Enabled
;
        .equiv FNOSC_FRC,       0xFFF8 ; Fast RC oscillator
        .equiv FNOSC_FRCPLL,    0xFFF9 ; Fast RC oscillator w/ divide and PLL
        .equiv FNOSC_PRI,       0xFFFA ; Primary oscillator (XT, HS, EC)
        .equiv FNOSC_PRIPLL,    0xFFFB ; Primary oscillator (XT, HS, EC) w/ PLL
        .equiv FNOSC_SOSC,      0xFFFC ; Secondary oscillator
        .equiv FNOSC_LPRC,      0xFFFD ; Low power RC oscillator
        .equiv FNOSC_FRCDIV16,  0xFFFE ; Fast RC oscillator w/ divide by 16
        .equiv FNOSC_LPRCDIVN,  0xFFFF ;  Low power Fast RC oscillator w/divide by N

        .equiv IESO_OFF,        0xFF7F ; Disabled
        .equiv IESO_ON,         0xFFFF ; Enabled


;----- FOSC (0xf80008) --------------------------------------------------
;
;  The following settings are available for FOSC:
;
;   Clock switching and clock monitor:
;     FCKSM_CSECME         Both enabled
;     FCKSM_CSECMD         Only clock switching enabled
;     FCKSM_CSDCMD         Both disabled
;
;   Single configuration for remappable I/O:
;     IOL1WAY_OFF          Disabled
;     IOL1WAY_ON           Enabled
;
;   OSC2 Pin function:
;     OSCIOFNC_ON          Digital I/O
;     OSCIOFNC_OFF         OSC2 is clock O/P
;
;   Oscillator Selection:
;     POSCMD_EC            External clock
;     POSCMD_XT            XT oscillator
;     POSCMD_HS            HS oscillator
;     POSCMD_NONE          Primary disabled
;
        .equiv FCKSM_CSECME,    0xFF3F ; Both enabled
        .equiv FCKSM_CSECMD,    0xFF7F ; Only clock switching enabled
        .equiv FCKSM_CSDCMD,    0xFFBF ; Both disabled

        .equiv IOL1WAY_OFF,     0xFFDF ; Disabled
        .equiv IOL1WAY_ON,      0xFFFF ; Enabled

        .equiv OSCIOFNC_ON,     0xFFFB ; Digital I/O
        .equiv OSCIOFNC_OFF,    0xFFFF ; OSC2 is clock O/P

        .equiv POSCMD_EC,       0xFFFC ; External clock
        .equiv POSCMD_XT,       0xFFFD ; XT oscillator
        .equiv POSCMD_HS,       0xFFFE ; HS oscillator
        .equiv POSCMD_NONE,     0xFFFF ; Primary disabled


;----- FWDT (0xf8000a) --------------------------------------------------
;
;  The following settings are available for FWDT:
;
;   Watchdog Timer:
;     FWDTEN_OFF           Disabled
;     FWDTEN_ON            Enabled
;
;   Windowed WDT:
;     WINDIS_ON            Enabled
;     WINDIS_OFF           Disabled
;
;   Watchdog prescaler:
;     WDTPRE_PR32          1:32
;     WDTPRE_PR128         1:128
;
;   Watchdog postscaler:
;     WDTPOST_PS1          1:1
;     WDTPOST_PS2          1:2
;     WDTPOST_PS4          1:4
;     WDTPOST_PS8          1:8
;     WDTPOST_PS16         1:16
;     WDTPOST_PS32         1:32
;     WDTPOST_PS64         1:64
;     WDTPOST_PS128        1:128
;     WDTPOST_PS256        1:256
;     WDTPOST_PS512        1:512
;     WDTPOST_PS1024       1:1,024
;     WDTPOST_PS2048       1:2,048
;     WDTPOST_PS4096       1:4,096
;     WDTPOST_PS8192       1:8,192
;     WDTPOST_PS16384      1:16,384
;     WDTPOST_PS32768      1:32,768
;
        .equiv FWDTEN_OFF,      0xFF7F ; Disabled
        .equiv FWDTEN_ON,       0xFFFF ; Enabled

        .equiv WINDIS_ON,       0xFFBF ; Enabled
        .equiv WINDIS_OFF,      0xFFFF ; Disabled

        .equiv WDTPRE_PR32,     0xFFEF ; 1:32
        .equiv WDTPRE_PR128,    0xFFFF ; 1:128

        .equiv WDTPOST_PS1,     0xFFF0 ; 1:1
        .equiv WDTPOST_PS2,     0xFFF1 ; 1:2
        .equiv WDTPOST_PS4,     0xFFF2 ; 1:4
        .equiv WDTPOST_PS8,     0xFFF3 ; 1:8
        .equiv WDTPOST_PS16,    0xFFF4 ; 1:16
        .equiv WDTPOST_PS32,    0xFFF5 ; 1:32
        .equiv WDTPOST_PS64,    0xFFF6 ; 1:64
        .equiv WDTPOST_PS128,   0xFFF7 ; 1:128
        .equiv WDTPOST_PS256,   0xFFF8 ; 1:256
        .equiv WDTPOST_PS512,   0xFFF9 ; 1:512
        .equiv WDTPOST_PS1024,  0xFFFA ; 1:1,024
        .equiv WDTPOST_PS2048,  0xFFFB ; 1:2,048
        .equiv WDTPOST_PS4096,  0xFFFC ; 1:4,096
        .equiv WDTPOST_PS8192,  0xFFFD ; 1:8,192
        .equiv WDTPOST_PS16384, 0xFFFE ; 1:16,384
        .equiv WDTPOST_PS32768, 0xFFFF ; 1:32,768


;----- FPOR (0xf8000c) --------------------------------------------------
;
;  The following settings are available for FPOR:
;
;   PWM Mode Select:
;     PWMPIN_OFF           PWM Module
;     PWMPIN_ON            Port Register
;
;   PWM High Side Polarity:
;     HPOL_OFF             Active Low
;     HPOL_ON              Active High
;
;   PWM Low Side Polarity:
;     LPOL_OFF             Active Low
;     LPOL_ON              Active High
;
;   Alternate I2C pins:
;     ALTI2C_ON            I2C mapped to ASDA1/ASCL1
;     ALTI2C_OFF           I2C mapped to SDA1/SCL1
;
;   Power-on Reset Value:
;     FPWRT_PWR1           Disabled
;     FPWRT_PWR2           2ms
;     FPWRT_PWR4           4ms
;     FPWRT_PWR8           8ms
;     FPWRT_PWR16          16ms
;     FPWRT_PWR32          32ms
;     FPWRT_PWR64          64ms
;     FPWRT_PWR128         128ms
;
        .equiv PWMPIN_OFF,      0xFF7F ; PWM Module
        .equiv PWMPIN_ON,       0xFFFF ; Port Register

        .equiv HPOL_OFF,        0xFFBF ; Active Low
        .equiv HPOL_ON,         0xFFFF ; Active High

        .equiv LPOL_OFF,        0xFFDF ; Active Low
        .equiv LPOL_ON,         0xFFFF ; Active High

        .equiv ALTI2C_ON,       0xFFEF ; I2C mapped to ASDA1/ASCL1
        .equiv ALTI2C_OFF,      0xFFFF ; I2C mapped to SDA1/SCL1

        .equiv FPWRT_PWR1,      0xFFF8 ; Disabled
        .equiv FPWRT_PWR2,      0xFFF9 ; 2ms
        .equiv FPWRT_PWR4,      0xFFFA ; 4ms
        .equiv FPWRT_PWR8,      0xFFFB ; 8ms
        .equiv FPWRT_PWR16,     0xFFFC ; 16ms
        .equiv FPWRT_PWR32,     0xFFFD ; 32ms
        .equiv FPWRT_PWR64,     0xFFFE ; 64ms
        .equiv FPWRT_PWR128,    0xFFFF ; 128ms


;----- FICD (0xf8000e) --------------------------------------------------
;
;  The following settings are available for FICD:
;
;   JTAG Enable Bit:
;     JTAGEN_OFF           JTAG is disabled
;     JTAGEN_ON            JTAG is enabled
;
;   ICD communication channel select bits:
;     ICS_NONE             Reserved
;     ICS_PGD3              communicate on PGC3/EMUC3 and PGD3/EMUD3
;     ICS_PGD2             communicate on PGC2/EMUC2 and PGD2/EMUD2
;     ICS_PGD1             communicate on PGC1/EMUC1 and PGD1/EMUD1
;
        .equiv JTAGEN_OFF,      0xFFDF ; JTAG is disabled
        .equiv JTAGEN_ON,       0xFFFF ; JTAG is enabled

        .equiv ICS_NONE,        0xFFFC ; Reserved
        .equiv ICS_PGD3,        0xFFFD ;  communicate on PGC3/EMUC3 and PGD3/EMUD3
        .equiv ICS_PGD2,        0xFFFE ; communicate on PGC2/EMUC2 and PGD2/EMUD2
        .equiv ICS_PGD1,        0xFFFF ; communicate on PGC1/EMUC1 and PGD1/EMUD1


;----- FUID0 (0xf80010) --------------------------------------------------
;
;  The following settings are available for FUID0:
;

;----- FUID1 (0xf80012) --------------------------------------------------
;
;  The following settings are available for FUID1:
;

;----- FUID2 (0xf80014) --------------------------------------------------
;
;  The following settings are available for FUID2:
;

;----- FUID3 (0xf80016) --------------------------------------------------
;
;  The following settings are available for FUID3:
;

.LIST
