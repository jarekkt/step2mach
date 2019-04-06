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
#include "stdafx.h"
#pragma comment(lib, "WS2_32.lib")

//---------------------------------------------------------------------------



typedef struct {
	char				  name[256];
	int					  HandleValid;
	SOCKET				  s;
	struct  sockaddr_in   remote_addr;
	struct  sockaddr_in   client_addr;
	struct  sockaddr_in   rcv_addr;
	int					  read_tout;
	int					  port;

} commDataType;


//---------------------------------------------------------------------------

static int comm_reopen(commDataType  * ptr)
{
   struct	timeval			tv;
   BOOL						bool_opt;
   struct addrinfo			hints;
   int						retval;
   struct addrinfo		  * result = NULL;
   struct sockaddr_in	  * sockaddr_ipv4;

   ptr->s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

   if(ptr->s == INVALID_SOCKET)
   {
	   return -1;
   }


   memset(&hints,0,sizeof(hints));

   hints.ai_family   = AF_UNSPEC;
   hints.ai_socktype = 0;
   hints.ai_protocol = 0;

   retval = getaddrinfo(ptr->name,NULL,&hints,&result);

   if(retval != 0)
   {
	   return -1;
   }

   sockaddr_ipv4 = (struct sockaddr_in *) result->ai_addr;

   ptr->remote_addr.sin_family		 = AF_INET;							// Address family to use
   ptr->remote_addr.sin_port		 = htons(ptr->port);						// Port number to use
   ptr->remote_addr.sin_addr.s_addr	 = sockaddr_ipv4->sin_addr.s_addr;  // Listen IP address.


   
   ptr->client_addr.sin_family = AF_INET;
   ptr->client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   ptr->client_addr.sin_port = htons(0);

   freeaddrinfo(result);

   tv.tv_sec = 10;/* ms*/ 
   if( setsockopt(ptr->s, SOL_SOCKET, SO_SNDTIMEO,(const char*)&tv,sizeof(struct timeval)) != 0)
   {
	 return -1;
   }

   ptr->read_tout = 30;
   tv.tv_sec	  = ptr->read_tout;/* ms*/ 
   if( setsockopt(ptr->s, SOL_SOCKET, SO_RCVTIMEO,(const char*)&tv,sizeof(struct timeval)) != 0)
   {
	  return -1;
   }

   // Allow address reuse
   bool_opt = TRUE;
   if( setsockopt(ptr->s, SOL_SOCKET, SO_REUSEADDR,(const char*)&bool_opt,sizeof(bool_opt)) != 0)
   {
  	 return -1;
   }

   // Bind local socket
   if(bind(ptr->s, (struct sockaddr *)&ptr->client_addr, sizeof(ptr->client_addr))!= 0)
   {
	   int err;

	   err = WSAGetLastError();

	   return -1;
   }


   return 0;
}


//---------------------------------------------------------------------------

int comm_Open( void ** handle,const char * name_address,int port)
{
   commDataType	  * ptr				  = NULL;
   WORD				wVersionRequested = MAKEWORD(2,2); 
   WSADATA			wsaData; 

   int 				result;

   // allocate data for COM processing

   ptr = new  commDataType;

   if(ptr == NULL)
   {
		return -1;
   }

   // Enable sockets
   if( WSAStartup(wVersionRequested, &wsaData) != 0)
   {
	  delete ptr;
	  ptr    = NULL;
	  result = -1;
   }
   else
   {
	   strncpy(ptr->name,name_address,sizeof(ptr->name));
	   ptr->port = port;
	   if (comm_reopen(ptr) != 0)
	   {
		  delete ptr;
		  ptr    = NULL;
		  result = -1;
	   }
	   else
	   {
		   *handle		    = (void *)ptr;
		   ptr->HandleValid = 1;
		   result 			= 0;
	   }
   }

   return result;
}


//---------------------------------------------------------------------------
int comm_Close(void ** handle)
{
   commDataType  * ptr = (commDataType  *)*handle;

   if(*handle == NULL)
   {
	 return FALSE;
   }

   if(ptr->HandleValid != 0)
   {
	   ptr->HandleValid = 0;
	   WSACleanup();
   }

   return ( TRUE ) ;

}

//---------------------------------------------------------------------------
int comm_Read(void * handle,char * lpBlock, int nMaxLength, int timeout )
{

   struct timeval	   tv;
   int				   slen;
   int				   size;

   commDataType  * ptr = (commDataType  *)handle;


   if(ptr == NULL)
   {
	  return -1;
   }

   if(ptr->HandleValid == 0)
   {
		 Sleep(500);
		 if(comm_reopen(ptr) == 0)
		 {
           ptr->HandleValid = 1;
         }
   }


   if(ptr->HandleValid != 0)
   {

	   if(timeout != (int)ptr->read_tout)
	   {
		   ptr->read_tout = timeout;
	       tv.tv_sec	  = ptr->read_tout;/* ms*/ 
	  	   if( setsockopt(ptr->s, SOL_SOCKET, SO_RCVTIMEO,(const char*)&tv,sizeof(struct timeval)) != 0)
		   {
			 return -1;
		   }
	   }

	   slen =  sizeof(ptr->rcv_addr);
	   size =  recvfrom(ptr->s,lpBlock, nMaxLength, 0,(struct sockaddr *) &ptr->rcv_addr, &slen);
	   if( size ==SOCKET_ERROR)
	   {
		   return -1;
	   }
	   else
	   {
		   return size;
	   }
	 
   }
   else
   {
       return -1;
   }
}

//---------------------------------------------------------------------------

int comm_Write(void * handle,const char * lpBlock , unsigned long dwBytesToWrite)
{
  commDataType  * ptr = (commDataType  *)handle;
  int			  bytesWritten;
  int 			  result = 0;
  int			  slen;


  if(ptr == NULL)
  {
	 return -1;
  }

  if(ptr->HandleValid != 0)
  {
	  slen = sizeof(ptr->remote_addr);
	  bytesWritten = sendto(ptr->s, lpBlock, dwBytesToWrite, 0,(struct sockaddr *) &ptr->remote_addr, slen);
	  if(bytesWritten ==SOCKET_ERROR)
	  {
		 result = -1;
	  }
	  else
	  {
		  return bytesWritten;
	  }
  }
  else
  {
	 result = -1;
  }

  return result;
}


