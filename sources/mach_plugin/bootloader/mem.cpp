#include "stdafx.h"

/******************************************************************************/
mem_cMemRow::mem_cMemRow(unsigned int StartAddr, int RowNumber)
{
	int Size;

	m_RowNumber = RowNumber;
	m_bEmpty    = TRUE;
	m_RowSize   = PM33F_ROW_SIZE;
	Size		= m_RowSize * 3;
	m_Address   = StartAddr + RowNumber * m_RowSize * 2;

	m_pBuffer   = (char *)malloc(Size);

	memset(m_Data, 0xFFFF, sizeof(unsigned short)*PM33F_ROW_SIZE*2);	
}
/******************************************************************************/
bool mem_cMemRow::InsertData(unsigned int Address, char * pData)
{
	if(Address < m_Address)
	{
		return FALSE;
	}

	if(Address >= (m_Address + m_RowSize * 2))
	{
		return FALSE;
	}

	m_bEmpty    = FALSE;

	sscanf(pData, "%4hx", &(m_Data[Address - m_Address]));
	
	return TRUE;
}
/******************************************************************************/
void mem_cMemRow::FormatData(void)
{
	if(m_bEmpty == TRUE)
	{
		return;
	}

	for(int Count = 0; Count < m_RowSize; Count += 1)
	{
		m_pBuffer[0 + Count * 3] = (m_Data[Count * 2]     >> 8) & 0xFF;
		m_pBuffer[1 + Count * 3] = (m_Data[Count * 2])          & 0xFF;
		m_pBuffer[2 + Count * 3] = (m_Data[Count * 2 + 1] >> 8) & 0xFF;
	}
}
/******************************************************************************/
int mem_cMemRow::SendData(void *pComDev)
{
	char Buffer[64];
	int attempt = 0;
	int ii;
	int len;
	int commands[] = {COMMAND_WRITE_PM1,COMMAND_WRITE_PM2,COMMAND_WRITE_PM3 };

	if(m_bEmpty == TRUE)
	{
		// Well empty item, we can treat it as 'sent'
		return 0;
	}

	while(1)
	{
		attempt++;

		if(attempt > 5)
		{
			return -1;
		}

		for( ii = 0; ii < 3;ii++)
		{
			Buffer[0] =  commands[ii];
			Buffer[1] = (m_Address)       & 0xFF;
			Buffer[2] = (m_Address >> 8)  & 0xFF;
			Buffer[3] = (m_Address >> 16) & 0xFF;

			WriteFrame(pComDev, Buffer, 4,&m_pBuffer[ii * m_RowSize], m_RowSize );

			len = ReadFrame(pComDev, Buffer, sizeof(Buffer));
			if( len > 0)
			{
				if(Buffer[1] != COMMAND_ACK)
				{
					// Error
					break;
				}
				else
				{
					if(ii == 2)
					{
						// All sent
						return 0;
					}
				}
			}
			else
			{
				// Error
				break;
			}
		}


	}
}
