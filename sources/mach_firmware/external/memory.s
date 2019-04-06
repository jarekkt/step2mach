;********************************************************************
; FileName:		memory.s
; Dependencies:    
; Processor:		dsPIC33F Family
; Hardware:		Explorer 16
; Assembler:		ASM30 2.14
; Company:		Microchip Technology, Inc.
;
; Software License Agreement
;
; The software supplied herewith by Microchip Technology Incorporated
; (the “Company”) for its PICmicro® Microcontroller is intended and
; supplied to you, the Company’s customer, for use solely and
; exclusively on Microchip PICmicro Microcontroller products. The
; software is owned by the Company and/or its supplier, and is
; protected under applicable copyright laws. All rights are reserved.
; Any use in violation of the foregoing restrictions may subject the
; user to criminal sanctions under applicable laws, as well as to
; civil liability for the breach of the terms and conditions of this
; license.
;
; THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
; WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
; TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
; PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
; IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
; CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
;
;********************************************************************/

.include "p33fxxxx.inc"

.global _LoadAddr,_WriteMem,_WriteLatch,_ReadLatch,_ResetDevice,_Erase ;C called


_LoadAddr:	;W0=NVMADRU,W1=NVMADR - no return values
	mov	W0,TBLPAG
	mov	W1,W1
	
	return
	
;***************************************************************		
_WriteMem:	;W0=NVMCON - no return values
	mov	W0,NVMCON
	mov	#0x55,W0	;Unlock sequence - interrupts need to be off
	mov	W0,NVMKEY
	mov	#0xAA,W0
	mov	W0,NVMKEY
	bset NVMCON,#WR
	nop				;Required
	nop
1:	btsc NVMCON,#WR	;Wait for write end
	bra 1b
	
	return
	
;***************************************************************	
_WriteLatch: ;W0=TBLPAG,W1=Wn,W2=WordHi,W3=WordLo - no return values
	mov	W0,TBLPAG	
	tblwtl W3,[W1]
	tblwth W2,[W1]
	
	return
	
;***************************************************************	
_ReadLatch: ;W0=TBLPAG,W1=Wn - data in W1:W0
	mov	W0,TBLPAG	
	tblrdl [W1],W0
	tblrdh [W1],W1
	
	return



;***************************************************************
_Erase:	

	
	push    TBLPAG
	mov	W2,NVMCON
					
	mov     w0,TBLPAG           	; Init Pointer to page to be erased
	tblwtl  w1,[w1]		        	; Dummy write to select the row

	
	mov	#0x55,W0	                ;Unlock sequence - interrupts need to be off
	mov	W0,NVMKEY
	mov	#0xAA,W0
	mov	W0,NVMKEY
	bset NVMCON,#WR
	nop				;Required
	nop

erase_wait:
	btsc NVMCON,#WR	;Wait for write end
	bra erase_wait
	
	pop     TBLPAG
	return

;***************************************************************	
.end
