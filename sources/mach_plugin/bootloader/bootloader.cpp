#include "stdafx.h"


static int  SendHexFile(void *pComDev);


int update_firmware(void * handle,void * reset_handle)
{
	unsigned char   cmd[2];
	int		result = -1;

	cmd[0] = 0xAB;
	cmd[1] = 0xBA;
	comm_Write(reset_handle,(const char *)cmd,sizeof(cmd));
	comm_Close(&reset_handle);			

	result = SendHexFile(handle);


	return result;
	

 	return 0;
}

/******************************************************************************/

static int GetEmbeddedLine(char * buf,int buf_size,int * pos)
{
	int ii = 0;

	while( (ii < buf_size) && (*pos < bin_data_size ))
	{
		buf[ii] = bin_data[*pos];
		(*pos)++;

		if(buf[ii] == '\n')
		{
			buf[ii] = 0;
			break;
		}

		ii++;
		
	}

	return ii;
}


/******************************************************************************/

static int  SendHexFile(void *pComDev)
{
	char Buffer[BUFFER_SIZE];
	int  ExtAddr = 0;
	int	 FilePos = 0;

	// Initialize Memory 
	mem_cMemRow ** ppMemory = (mem_cMemRow **)malloc(sizeof(mem_cMemRow *) * PM_SIZE);

	for(int Row = 0; Row < PM_SIZE; Row++)
	{
		ppMemory[Row] = new mem_cMemRow(0x000000, Row);
	}

		
	// Parsing HexFile
	 

	while(GetEmbeddedLine(Buffer, sizeof(Buffer),&FilePos) != 0)
	{
		int ByteCount;
		int Address;
		int RecordType;

		sscanf(Buffer+1, "%2x%4x%2x", &ByteCount, &Address, &RecordType);

		if(RecordType == 0)
		{	
			Address = (Address + ExtAddr) / 2;

			for(int CharCount = 0; CharCount < ByteCount*2; CharCount += 4, Address++)
			{
				bool bInserted = FALSE;

				for(int Row = 0; Row < PM_SIZE; Row++)
				{
					if( ppMemory[Row]->InsertData(Address, Buffer + 9 + CharCount) == TRUE)
					{
						bInserted = TRUE;
						break;
					}
				}


				if(bInserted != TRUE)
				{
					// We ignore EEPROM and configuration area, so some records will be dropped
				}
			}
		}
		else if(RecordType == 1)
		{
		}
		else if(RecordType == 4)
		{
			sscanf(Buffer+9, "%4x", &ExtAddr);

			ExtAddr = ExtAddr << 16;
		}
		else
		{
			assert(!"Unknown hex record type\n");
		}
	}


	// Path jump vector - must point to bootloader ( address 0x400 )
	strcpy(Buffer,"0004040000000000");
	ppMemory[0]->InsertData(0x000000, Buffer + 0);
	ppMemory[0]->InsertData(0x000001, Buffer + 4);
	ppMemory[0]->InsertData(0x000002, Buffer + 8);
	ppMemory[0]->InsertData(0x000003, Buffer + 12);


	for(int Row = 0; Row < (PM_SIZE); Row++)
	{
		ppMemory[Row]->FormatData();
	}

	// Programming Device

	for(int Row = 0; Row < (PM_SIZE); Row++)
	{
		if(ppMemory[Row]->SendData(pComDev) != 0)
		{
			return -1;
		}
	}

	Buffer[0] = COMMAND_RESET;
	WriteFrame(pComDev,Buffer,1);
	

	// Done
	for(int Row = 0; Row < PM_SIZE; Row++)
	{
		delete ppMemory[Row];
	}

	return 0;
}





