// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef serW32H
#define serW32H
//---------------------------------------------------------------------------


int  comm_Open(void ** handle,const char * name_address,int port);
int  comm_Close(void ** handle);
int   comm_Read(void * handle,char  * lpBlock, int nMaxLength ,int timeout  );
int  comm_Write(void * handle,const char * lpBlock , unsigned long dwBytesToWrite);



#endif
