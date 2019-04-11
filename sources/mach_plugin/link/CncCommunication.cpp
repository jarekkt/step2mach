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
#include <windows.h>
#include <winbase.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>

#pragma hdrstop

#include "serW32.h"
#include "crc16.h"
#include "mach_pclib_protocol.h"
#include "..\bootloader\bootloader.h"

#define MAX_COMM_BUFFER							  16384
#define MAX_FRAME_BUFFER						   4096
#define MAX_FRAME_OUT								 42


static void				*   ComHandle;
static void				*   ComHandleReset;
static int					ComOpen;
static int					ComCloseAck;
static int					ComUpdateRequest;
static int					ComUpdateResult;
static int                  Terminated;
static clock_t				last_recv;

FILE				      * fdbg = NULL;


static CRITICAL_SECTION     CriticalSection;
static HANDLE               Event;
static HANDLE               Thread;
static DWORD                ThreadId;

DWORD						frame_cntr = 0;


#pragma pack(push, 1)
static timer_frame_t		frame_buf[MAX_FRAME_BUFFER][2];
static struct
{
	uint8_t					start;
	timer_frame_t			frame_buf[MAX_FRAME_OUT];
	uint32_t				extra;
}send_buf;
#pragma pack(pop)


static int					frame_beg[2];
static int					frame_end_sent[2];
static int					frame_end[2];
static int 					frame_free[2];

static int					frame_buf_in_use;

static uint8_t				frame_id;

#pragma pack(push, 1)
static timer_resp_t			current_response;
#pragma pack(pop)
int							current_response_valid;
static clock_t				current_response_timestamp;


static int					frame_last_id;
static int					frame_last_attempt;
static int                  frame_last_count;


static DWORD  __stdcall CncComm_Execute(void * arg);
static void	  CncCom_SendQueue(void);
static void	  CncCom_SendKeepalive(void);




//---------------------------------------------------------------------------
static void CncInitVariables(void)
{
	int ii;

	for(ii = 0; ii < 2;ii++)
	{
		frame_beg[ii]		 = frame_end[ii] = frame_end_sent[ii] = 0;
		frame_free[ii]       = MAX_FRAME_BUFFER - 1;
	}
	frame_buf_in_use     = 0;


	frame_id             = 0;
	
	frame_last_id        = -1;
	frame_last_attempt   = 0;
	frame_last_count     = 0;


	current_response_valid		= 0;
	current_response_timestamp	= 0;

}

//---------------------------------------------------------------------------
int STDCALL Cnc_Init_Controller()
{


	ComOpen			 =  0;
	ComCloseAck		 = -1;
	ComUpdateRequest =  0;
	Terminated		 =  0;
	Event			 =  CreateEvent( NULL,    // no security
									 TRUE,    // explicit reset req
									 FALSE,   // initial event reset
									 NULL ) ; // no name

	InitializeCriticalSection(&CriticalSection);
	Thread = CreateThread(NULL,0,CncComm_Execute,NULL,0,&ThreadId);

	CncInitVariables();
	
	fdbg = fopen("d:\\dbg.txt","wt");

	memset(&current_response,0,sizeof(current_response));
	memset(&frame_buf,0,sizeof(frame_buf));	
	memset(&send_buf,0,sizeof(send_buf));

	send_buf.start     = '<';

	return 0;
}
//---------------------------------------------------------------------------

int STDCALL Cnc_Exit_Controller()
{
	Terminated = 1;
	WaitForSingleObject(Thread,INFINITE);
	DeleteCriticalSection(&CriticalSection);
	CloseHandle(Event);

	fclose(fdbg);

	return 0;
}
//---------------------------------------------------------------------------
static DWORD __stdcall CncComm_Execute(void * arg)
{
	char		TmpBuffer[MAX_COMM_BUFFER];
	int			TmpIndexBeg = 0;
	int			TmpIndexEnd = 0;

	double		timeout;

#pragma pack(push, 1)
	timer_resp_t	response;
#pragma pack(pop)

	int  			PartialIndex = 0;

	arg = arg;



	while(Terminated == 0)
	{
		if(ComOpen == 0)
		{
			if(ComCloseAck == 0)
			{
				comm_Close(&ComHandle);
				comm_Close(&ComHandleReset);
				ComCloseAck = 1;
			}
			Sleep(100);
			continue;
		}


		if(ComUpdateRequest != 0)
		{
			ComUpdateResult  = update_firmware(ComHandle,ComHandleReset);
			ComUpdateRequest = 0;
		}




NextFrame:


		timeout = ((double)(clock() - last_recv));
		timeout = timeout / CLOCKS_PER_SEC ;

		if( timeout  > ((((double)WATCHDOG_JOG_TIMEOUT)/1000))) /* timeout, also conversion from ms to seconds */
		{			
			CncCom_SendKeepalive();
		} 


		TmpIndexBeg = 0;
		TmpIndexEnd =  comm_Read(ComHandle,TmpBuffer,sizeof(TmpBuffer),20);
		if(TmpIndexEnd > 0)
		{

MoreFrames:
			if(PartialIndex == 0)
			{
			  for(; TmpIndexBeg <TmpIndexEnd;TmpIndexBeg++)
			  {
				 if(TmpBuffer[TmpIndexBeg] == '>')
				 {
					goto FrameChars;
				 }
			  }
			}
			else
			{
FrameChars:
				for(; TmpIndexBeg <TmpIndexEnd;TmpIndexBeg++)
				{

				  ((char *)&response)[PartialIndex++] = TmpBuffer[TmpIndexBeg];

				  if( PartialIndex == (int)sizeof(response) )
				  {
					  if(response.magic_end == '#')
					  {
						  if(crc_verify(((const unsigned char *)&response),sizeof(response)) != 0)
						  {
							  current_response_timestamp = last_recv = clock();
							  current_response_valid	 = 1;
							  // Valid message received
							  EnterCriticalSection(&CriticalSection);
							  memcpy(&current_response,&response,sizeof(current_response));
							  CncCom_SendQueue();							 

							  LeaveCriticalSection(&CriticalSection);
							  PartialIndex = 0;
						  }
					  }
					  goto MoreFrames;
				  }

				  if(PartialIndex >= (int)sizeof(response))
				  {
  				     PartialIndex = 0;
					 goto NextFrame;
				  }

				}
			}
		}
	 }

	 return 0;
}

//---------------------------------------------------------------------------

void CncCom_SendQueue(void)
{
	int						ii;
	int						retry			  = 0;	
	uint16_t				crc_calc          = CRC_INIT;
	static clock_t			last_sent;	
	double					timeout;



	if(frame_last_id >= 0)
	{
		if(current_response.data.last_valid_id == frame_last_id)
		{
			// previous sent attempt succeded
			// adjust buffer indexes and free space count
			frame_beg[frame_buf_in_use] 	  = frame_end_sent[frame_buf_in_use];
			frame_free[frame_buf_in_use]     += frame_last_count;
			 
			// Increment frame identification
			frame_id++;
			frame_last_id = -1;
		}
		else
		{
			frame_last_attempt++;
			if(frame_last_attempt < 4)
			{
				// Wait  a while until retry attempt is made
				return;
			}
			else
			{
				// Assume it was lost, will be resent
				frame_last_id = -1;
				retry		  =  1;
			}

		}
	}
	else
	{
		if(current_response.data.last_valid_id == frame_id)
		{
			frame_id++;
        }
	}


	// Check which queue should be used
	if(retry == 0)
	{
		// Never switch queues when previus attempt failed
		// Otherwise you may send twice same frames

		if(frame_end[1] != frame_beg[1])
		{
			// Slot 1 for control commands has higher priority
			frame_buf_in_use = 1;
		}
		else
		{
			frame_buf_in_use = 0;
		}
	}


	// Send packets from queue
	frame_last_attempt					  = 0;
	frame_end_sent[frame_buf_in_use]      = frame_beg[frame_buf_in_use];
	ii									  = 0;

	while(frame_end_sent[frame_buf_in_use] != frame_end[frame_buf_in_use])
	{
		if( ii >= (2* (int)(unsigned int)current_response.data.free_slots /* herewe have real value divided by 2 - due to Uint8 limitation*/) )
		{
			break;
		}

		send_buf.frame_buf[ii] 			   = frame_buf[frame_end_sent[frame_buf_in_use]][frame_buf_in_use];
		send_buf.frame_buf[ii].header.id   = frame_id;
		send_buf.frame_buf[ii].header.size = 0;
		ii++;

		frame_end_sent[frame_buf_in_use] = (frame_end_sent[frame_buf_in_use] + 1) % MAX_FRAME_BUFFER;

		if(ii == MAX_FRAME_OUT)
		{
			break;
		}
	}


	if(ii == 0)
	{
		timeout = ((double)(clock() - last_sent));
		timeout = timeout / CLOCKS_PER_SEC ;

		if( timeout  > ((((double)WATCHDOG_JOG_TIMEOUT)/1000)/2)) /* half of the timeout, also conversion from ms to seconds */
		{
				// Send watchdog frame
				send_buf.frame_buf[0].header.id			= frame_id++;
				send_buf.frame_buf[0].header.command	= CMD_WATCHDOG;
				send_buf.frame_buf[0].header.in_mask	= 0;
				ii					= 1;
				frame_last_count	= 0;	// not from queues
		}
	}
	else
	{
		frame_last_count				  = ii;	
	}

	// Adjust packet size
	if( ii > 0)
	{

		frame_last_id 					  = frame_id;
		send_buf.frame_buf[0].header.size = ii;

		// Calculate crc
		crc_calc  = crc_sum( (unsigned char*)send_buf.frame_buf,ii*sizeof(timer_frame_t),crc_calc);
		((unsigned char*)&(send_buf.frame_buf[ii]))[0] = (crc_calc >> 8) & 0xFF;
		((unsigned char*)&(send_buf.frame_buf[ii]))[1] = (crc_calc) & 0xFF;

		if(comm_Write(ComHandle,(const char *)&send_buf ,1 /*start*/ + ii*sizeof(timer_frame_t) + 2 /* crc */ ) >= 0)
		{
			// Update watchdog tick
			last_sent = clock();
		}

	}


}

//---------------------------------------------------------------------------
int  STDCALL Cnc_GetBufferStatus(void)
{
	// Slot 0 is for ordinary movement vectors which occupy buffer
	// Slot 1 is priority slot for control commands which do not occupy device buffer
	return (MAX_FRAME_BUFFER - frame_free[0]);
}
//---------------------------------------------------------------------------
int	STDCALL Cnc_Communication_Enable(const char * address)
{
	int					ii;
	timer_resp_t		status;
	bool			    upgrade;

	
	
	// Open both sockets
	if(comm_Open(&ComHandle,address,7000) == 0)
	{
		if(comm_Open(&ComHandleReset,address,7001) == 0)
		{
			ComOpen = 1;
			upgrade = false;

			for(ii = 0; ii < 5;ii++)
			{
				CncCom_SendKeepalive();
				Sleep(50);
			}
			
			// Check if alive 
			if(Cnc_Status_Get(&status)== 0)
			{
				if(status.header.version != step2mach_ver)
				{
					upgrade = true;
				}
				else
				{
					ComUpdateRequest = 0;
				}
			}
			else
			{
				upgrade = true;
			}

#if 0 // TODO
			// Check if upgrade needed ( tried also if there is no answer)
			if(upgrade == true)
			{
				ComUpdateRequest = 1;

				while(ComUpdateRequest != 0)
				{
					Sleep(100);
				}
			}


			return ComUpdateResult;
#else
			return 0;	
#endif
		}
		else
		{
			comm_Close(&ComHandle);
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

//---------------------------------------------------------------------------

int  STDCALL Cnc_Communication_Disable(void)
{
	ComOpen = 0;
	ComCloseAck = 0;

	while(ComCloseAck == 0)
	{
		Sleep(100);
	}

	return 0;
}


//---------------------------------------------------------------------------

int  STDCALL Cnc_IsQueEmpty(void)
{
   int result;

   EnterCriticalSection(&CriticalSection);

   if( (frame_end[1] == frame_beg[1]) && (frame_end[0] == frame_beg[0]) )
   {
	   result = 0;
   }
   else
   {
	   result = -1;
   }

   LeaveCriticalSection(&CriticalSection);

   return result;
}

//---------------------------------------------------------------------------
void STDCALL Cnc_SendCommand(command_e cmd,int clear_queue)
{
	// Send outputs directly
	EnterCriticalSection(&CriticalSection);

	// Clear all queues
	if(clear_queue != 0)
	{
		CncInitVariables();
	}

	frame_buf[frame_end[1]][1].header.size 		= 0;
	frame_buf[frame_end[1]][1].header.id   		= 0;
	frame_buf[frame_end[1]][1].header.command	= cmd;
	frame_buf[frame_end[1]][1].header.in_mask   = 0;


	frame_end[1] = (frame_end[1] + 1) % MAX_FRAME_BUFFER;

	frame_free[1]--;



	LeaveCriticalSection(&CriticalSection);
}

//---------------------------------------------------------------------------

int  STDCALL Cnc_SetCoords(timer_coord_t  * coord)
{
   int result = -1;

   EnterCriticalSection(&CriticalSection);

   if(frame_free[1] > 0)
   {


	   frame_buf[frame_end[1]][1].header.size 		= 0;
	   frame_buf[frame_end[1]][1].header.id   		= 0;
	   frame_buf[frame_end[1]][1].header.command	= CMD_COORDS;
	   frame_buf[frame_end[1]][1].header.in_mask	= 0;

	   frame_buf[frame_end[1]][1].data.coord = *coord;

	   frame_end[1] = (frame_end[1] + 1) % MAX_FRAME_BUFFER;

	   frame_free[1]--;
	   result = 0;
   }

   LeaveCriticalSection(&CriticalSection);

   return result;
}


//---------------------------------------------------------------------------

int  STDCALL Cnc_SetOutputs(uint64_t outputs,uint64_t mask)
{
	int result = -1;


	// Send outputs directly
	EnterCriticalSection(&CriticalSection);

	if(frame_free[1] >= 1)
	{
	   frame_buf[frame_end[1]][1].header.size 		= 0;
	   frame_buf[frame_end[1]][1].header.id   		= 0;
	   frame_buf[frame_end[1]][1].header.command	= CMD_OUTPUTS;
	   frame_buf[frame_end[1]][1].header.in_mask	= 0;
	   frame_buf[frame_end[1]][1].data.io.outputs	= outputs;
	   frame_buf[frame_end[1]][1].data.io.mask		= mask;

	   frame_end[1] = (frame_end[1] + 1) % MAX_FRAME_BUFFER;

	   frame_free[1]--;
	   result = 0;
	}

	LeaveCriticalSection(&CriticalSection);

	return result;
}

//---------------------------------------------------------------------------

FNTYPE uint64_t  STDCALL Cnc_GetInputs(void)
{
	// Inputs are directly mapped
	return current_response.data.inputs;
}



//---------------------------------------------------------------------------

int  STDCALL Cnc_SetMap(timer_map_t * map, int map_cnt)
{
	int result = -1;
	int ii;

	EnterCriticalSection(&CriticalSection);

	if(frame_free[1] >= map_cnt)
	{
	   for(ii = 0; ii < map_cnt;ii++)
	   {
		   frame_buf[frame_end[1]][1].header.size 		= 0;
		   frame_buf[frame_end[1]][1].header.id   		= 0;
		   frame_buf[frame_end[1]][1].header.command	= CMD_MAP;
		   frame_buf[frame_end[1]][1].header.in_mask	= 0;
		   frame_buf[frame_end[1]][1].data.map			= map[ii];

		   frame_end[1] = (frame_end[1] + 1) % MAX_FRAME_BUFFER;

		   frame_free[1]--;
	   }
	   result = 0;
	}

	LeaveCriticalSection(&CriticalSection);

	return result;
}

//---------------------------------------------------------------------------

int  STDCALL Cnc_SetFrame(timer_frame_t  * frame, int frame_cnt,int replace_queue)
{
   int result = -1;
   int ii;

   EnterCriticalSection(&CriticalSection);

   if(replace_queue != 0)
   {
		frame_beg[0]  = frame_end[0] = 0;
		frame_free[0] = MAX_FRAME_BUFFER - 1;
   }

   if(frame_free[0] > frame_cnt)
   {

	   for(ii = 0; ii < frame_cnt;ii++)
	   {
		   frame_buf[frame_end[0]][0].header.size 	= 0;
		   frame_buf[frame_end[0]][0].header.id   	= 0;
		   frame_buf[frame_end[0]][0].header.command	= frame[ii].header.command;
		   frame_buf[frame_end[0]][0].header.in_mask  = frame[ii].header.in_mask;

		   frame_buf[frame_end[0]][0].data			= frame[ii].data;

		   frame_end[0] = (frame_end[0] + 1) % MAX_FRAME_BUFFER;
		   frame_free[0]--;

		   frame_cntr++;


	   }


	   result = 0;
   }

   LeaveCriticalSection(&CriticalSection);


   return result;

}

//--------------------------------------------------------------------------
static void	  CncCom_SendKeepalive(void)
{
	// Send keep alive on UDP ( also used for establishing communication
	comm_Write(ComHandle,"keepalive" ,9) ;
	last_recv = clock();
}

//---------------------------------------------------------------------------

int  STDCALL Cnc_Status_Get(timer_resp_t  * status)
{
	int			result = -1;
	double		diff;
	double      limit = ((double)WATCHDOG_COMM_TIMEOUT/1000);

	EnterCriticalSection(&CriticalSection);

	if( current_response_valid != 0)
	{
		diff = 	  ((double)(clock() - current_response_timestamp))/CLOCKS_PER_SEC;
		if(  diff < limit )
		{
			memcpy(status,&current_response,sizeof(*status));
			result = 0;
		}
		else
		{
			current_response_valid = -1;
		}
	}


	LeaveCriticalSection(&CriticalSection);

	return result;
}



