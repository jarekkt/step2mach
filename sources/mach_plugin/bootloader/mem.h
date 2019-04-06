#ifndef _mem_h
#define _mem_h


class mem_cMemRow
{
public:

	mem_cMemRow(unsigned int StartAddr, int RowNumber);

	bool InsertData(unsigned int Address, char * pData);
	void FormatData(void);
	int  SendData  (void *pComDev);

private:
	char           * m_pBuffer;
	unsigned int     m_Address;
	bool             m_bEmpty;
	unsigned short   m_Data[PM33F_ROW_SIZE*2];
	int              m_RowNumber;
	int				 m_RowSize;
};


#endif