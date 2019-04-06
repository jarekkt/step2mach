#include "..\..\mach_common\types.h"
#include "memory.h"


#define PM_ROW_SIZE (64 * 8)
#define CM_ROW_SIZE 8
#define CONFIG_WORD_SIZE 1

#define PM_ROW_ERASE 		0x4042
#define PM_ROW_WRITE 		0x4001
#define CONFIG_WORD_WRITE	0X4000

typedef union tuReg32
{
	Uint32_t Val32;

	struct
	{
		Uint16_t LW;
		Uint16_t HW;
	} Word;

	char Val[4];
} uReg32;



Uint32_t ReadLatch(Uint16_t,  Uint16_t);
void   WriteLatch(Uint16_t, Uint16_t,Uint16_t, Uint16_t);
void   WriteMem(Uint16_t sequence);
void   Erase(Uint16_t page, Uint16_t row,Uint16_t sequence); 



void flash_read_pm(char * ptrData, Uint32_t SourceAddr,Uint16_t length)
{
	int    Size;
	uReg32 Temp;
	uReg32 TempSourceAddr;

	TempSourceAddr.Val32 = SourceAddr;

	for(Size = 0; Size < PM_ROW_SIZE; Size++)
	{
		Temp.Val32 = ReadLatch(TempSourceAddr.Word.HW, TempSourceAddr.Word.LW);

		ptrData[0] = Temp.Val[0];
		if(--length == 0)break; 
		ptrData[1] = Temp.Val[1];
		if(--length == 0)break; 
		ptrData[2] = Temp.Val[2];
		if(--length == 0)break; 

		ptrData = ptrData + 3;

		TempSourceAddr.Val32 = TempSourceAddr.Val32 + 2;
	}
}


int flash_write_pm(char * ptrData, Uint32_t DestAddr,Uint16_t eraselength,Uint16_t writelength)
{
	int    Size,Size1;
	uReg32 Temp;
	uReg32 TempAddr;
	uReg32 TempData;
	uReg32 TempDestAddr;
	Uint16_t alignedWriteLength;


	/*
		 Erase block is PM_ROW_SIZE * 3
		 We support only Erase Block granularity Erase
	*/ 
	if( eraselength != (PM_ROW_SIZE*3) )
	{
		return -1;
	}


	alignedWriteLength = ((writelength + 64 -1) / 64)*64;

	TempDestAddr.Val32 = DestAddr;

	Erase(TempDestAddr.Word.HW,TempDestAddr.Word.LW,PM_ROW_ERASE);

	for(Size = 0,Size1=0; Size < alignedWriteLength; Size++)
	{
		if(Size1 < writelength)
		{
			Temp.Val[0]=ptrData[Size1+0];
		}
		else
		{
			Temp.Val[0]=0;
		}

		if(Size1 +1 < writelength)
		{
			Temp.Val[1]=ptrData[Size1+1];
		}
		else
		{
			Temp.Val[1]=0;
		}

		if(Size1 +2 < writelength)
		{
			Temp.Val[2]=ptrData[Size1+2];
		}
		else
		{
			Temp.Val[2]=0;
		}
		
		Temp.Val[3]=0;
		Size1+=3;
	
	    WriteLatch(TempDestAddr.Word.HW, TempDestAddr.Word.LW,Temp.Word.HW,Temp.Word.LW);

		/* Device ID errata workaround: Save data at any address that has LSB 0x18 */
		if((TempDestAddr.Val32 & 0x0000001F) == 0x18)
		{
			TempAddr.Val32 = TempDestAddr.Val32;
			TempData.Val32 = Temp.Val32;
		}

		if( ((Size !=0) && (((Size + 1) % 64) == 0)))
		{
			/* Device ID errata workaround: Reload data at address with LSB of 0x18 */
	        WriteLatch(TempAddr.Word.HW, TempAddr.Word.LW,TempData.Word.HW,TempData.Word.LW);
			WriteMem(PM_ROW_WRITE);
		}

		TempDestAddr.Val32 = TempDestAddr.Val32 + 2;
	}

   	 return 0;
}
