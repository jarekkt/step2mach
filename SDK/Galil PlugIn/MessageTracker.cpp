// MessageTracker.cpp : implementation file
//

#include "stdafx.h"
#include "MachDevice.h"
#include "G100-Structs.h"
#include "decoders.h"
#include "Engine.h"
#include "TrajectoryControl.h"
#include "math.h"
#include "g200x.h"
#include "UDPSocket.h"

#include "MessageTracker.h"
#include ".\messagetracker.h"

extern TrajBuffer *Engine; 
extern TrajectoryControl *MainPlanner;
extern GRex G100;
extern CUDPSocket  *g100sock;

extern void DebugOut( CString string);    //for outputting Debug String.
extern CStdioFile debugfile;

extern int IDs[64];
extern int tIDs[64];
extern int InitQueue;
extern G100Message JogMessage;
// MessageTracker

IMPLEMENT_DYNAMIC(MessageTracker, CWnd)

BEGIN_MESSAGE_MAP(MessageTracker, CWnd)
END_MESSAGE_MAP()


MessageTracker::MessageTracker()
{
	ResetQueue();
	debugfile.Open( "GRexMessages.txt", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone   );


}

MessageTracker::~MessageTracker()
{
   DebugOut( "Session Closed.\n");
   debugfile.Flush(); //Flush and close the Debug File . So it is always closed on each run.
   debugfile.Close();
}

void MessageTracker::DebugOut( CString string)
{
   if( MainPlanner->DebugRun )
	   {
		   debugfile.WriteString( string );
		   debugfile.WriteString( "\n");
		   debugfile.Flush();
	   }
}


// MessageTracker message handlers



void MessageTracker::ResetQueue(void)
{
	m_Head = m_Tail = 0; //reset the head and tail to zero
	                     //this means all commands are dumped. Nothing waiting to go out
	                     // and all holding messages are lost. 
	nMessages = 0;       //number of messages holding
	G100.LastMess = G100.LastAck;     //no messages holding, next message should be the next in sequence. 
	G100.LastStored = G100.LastAck;   // and set the last message stored to the same spot. 
	G100.NextQueue = G100.EndQueueSeq;
	for( int x = 0; x< 8; x++ )
	{
		OutMessages[x].Header.seq = 0;  //clear the holding ack tags. 
	}
}

void MessageTracker::Update(void)
{
	//This routine is refreshed on each message reception so that in we can adjust the max queue length
	// and make decisions regarding queue traffic..

	//QueueUsed is a variable telling us how busy the G100 is in the queue. Must keep it less than 32 messages in the queue at all times.
	//but for robustness, we'll keep it to 15 or less.. Ive found SEQ errors result if higher than that..
	m_QueueUsed = G100.EndQueueSeq - G100.CurrentQueueSeq; //this will autorollover at 65536
}



//Thsi routine will add a message to the Ring buffer. No message is sent automatically, all messages are queued here 
//for future trasnmission at the approriate times. They are sent only if the G100 can accept more messages..
// The G100 message type is a generalized variable length message packet. 

bool MessageTracker::Add2Queue(G100Message *OutMessage)
{
 CString debug;
  if((( m_Head + 1) & 0x07) == m_Tail )
  {
    DebugOut( "********************************Locked due to full message Queue. Loss of Message.. \n");
    // Full Buffer.. We shoudl never have gotten here..except perhaps by digital IO and itll catch up on next available slot. 
	//otherwise   Bad Failure.. I screwed up. :-) ..itll never happen.. BUT keep at least one slot open when processing Gcode.
	return false;
  }
  debug.Format( "Add to Qeuue: %d ",G100.LastStored);
  DebugOut( debug );
  OutMessage->Header.seq =  (G100.LastStored & 0xff); //set the sequence number;
  G100.LastStored++;                               //increment the last message Stored. 
  G100.LastStored &= 255;
  OutMessages[m_Head] = *OutMessage; //set the message in the buffer to the queue location.. All messages from 0 - 255 as per head/tail..
  m_Head = ( m_Head + 1) & 0x07; //increment the head pointer.
  nMessages = m_Head - m_Tail;
  if( nMessages < 0 )nMessages += 8; //ring it for proper number of messages to be sent..Now the system can report how many messages can be queued up.
  return true;
}
//This routine will get called to sedn any waiting messages. 
//It will send only if the message state of the G100 is such that it can accept a message..


void MessageTracker::SendMessages(void)
{
CString debug;
   if( m_Head == m_Tail  ) return;  //no messages holding..
   for( int x = m_Tail; x != m_Head; x = (x + 1) & 0x07 )
	  {
		  if( G100.Window < 3 ) 
		  {
			   CString debug;
			   debug.Format(" Window too msall rejecting send. WDO is %d ", G100.Window );
			   DebugOut(debug);
			   return; //weve used up the Window we have currently.
		  }
	    G100.Window--; //reduce the Window we are using..
		//send this message.

		if( !SequenceMessage ( &OutMessages[x] )) 
		{
            G100.Window++;
			CString debug;
			debug.Format(" Sequence queue full.. rejecting send. WDO is %d ", G100.Window );
			DebugOut(debug);
			return; //this will make sure the movement queue sequence is observed and we dont flood the queue. 
		}
		OutTimes[x] = CTime::GetCurrentTime();

		m_Tail++;  //update tail before sending to maintain sync..
		m_Tail &= 0x07;
		G100.LastMess = OutMessages[x].Header.seq;
        g100sock->SendTo( &OutMessages[x] , OutMessages[x].size + sizeof(OutMessages[x].Header)
			              , 13888, IpToString(G100.G100Address.ipaddr));
		G100.LastMess = OutMessages[x].Header.seq;
		debug.Format( "Msg # %d sent. \n", G100.LastMess );
		DebugOut( debug );
		nMessages = m_Head - m_Tail;
        if( nMessages < 0 ) nMessages += 8; //the number of messages we are still holding..
	    return;
	   
   }
}

void MessageTracker::Purge()
{

   if( m_Head != m_Tail )
	   G100.LastStored = G100.LastMess + 1;//OutMessages[m_Tail].Header.seq; //sync to the first messags old sequence number, then kill the message queue

   CString debug;
   debug.Format( "Next Message set to %d", G100.LastStored );
   DebugOut( debug );
   m_Head = m_Tail; //kill the queue
   Engine->TrajHead = Engine->TrajIndex;//kill the Mach queue just in case of asyn error..
   MainPlanner->PurgeMovements = true;
   G100.LastStored = (G100.LastAck +1 ) & 0xff; //set the next message to the last one sent +1;
   for( int x = 0; x< 8; x++ ) //clear the message queue
	{
		OutMessages[x].Header.seq = 0;  //clear the holding ack tags. 
	}

   InitQueue = 3;
   DebugOut(" Queue Purged." );
   G100.InJog = false;
   for( int x = 0; x<6; x++ )
    {
      ((WTLinear*)&JogMessage.Message)->v[x].i = 0; 
	  ((WTLinear*)&JogMessage.Message)->v[x].f = 0;
	  Engine->Axis[x].Jogging = false;
	  MainPlanner->Jogging = false;
   }

}

void MessageTracker::SetMessDef( G100Message* OutMessage, short type)
{  //this sets up the message to be sent by initiializing its headers and such
	OutMessage->Header.chanflgs = UCHAN_WNDO;
	OutMessage->Header.chksum = 0;
	OutMessage->Header.ack = 0;
	OutMessage->Header.resv = 0;
	OutMessage->Header.seq = 0; //set for the next message number
	OutMessage->Header.type = type;
}

bool MessageTracker::SequenceMessage(G100Message* message)
{

 //Put in a proper queue sequence for a movement. 	
 //otherwise a G100 will generate a Queue Sequence Error.
 //this gets called for all messges. SO we'll put out debug messages here for message outputs..
 DebugOut( "Message Send: "); 
 CString debug;

 switch( message->Header.type )
   {
 case( WT_LINEAR ): if( CheckQueueSize() ) return false;  //Check queue is not too full..
	               IDs[G100.NextQueue & 0x3f] = tIDs[ message->Header.seq & 0x3f ];
	               ((WTLinear*)message->Message)->m.qseq = G100.NextQueue++;
	                message->size = sizeof( WTLinear);
	                debug.Format( " LINEAR: SEQ# %d Message # %d \n VEL[ %d,%d,%d ]",G100.NextQueue, message->Header.seq
						,((WTLinear*)message->Message)->v[0].i,((WTLinear*)message->Message)->v[1].i,((WTLinear*)message->Message)->v[2]);
	                DebugOut( debug );   
	                break;
 case( WT_CUBIC ) : if( CheckQueueSize() ) return false; 
                    IDs[G100.NextQueue & 0x3f] = tIDs[ message->Header.seq & 0x3f ];
	                ((WTCubic*)message->Message)->m.qseq = G100.NextQueue++;
	                message->size = sizeof( WTCubic);
					debug.Format( " CUBIC: SEQ# %d Message # %d  DDAs 0-3 -> %x , %x, %x  Time: %d\n",G100.NextQueue, message->Header.seq,
						((WTCubic*)message->Message)->d[0].dda1.i,
						((WTCubic*)message->Message)->d[1].dda1.i, 
						((WTCubic*)message->Message)->d[2].dda1.i,
						((WTCubic*)message->Message)->m.T);
					DebugOut( debug ); 
	                break;
 case( WT_DWELL ) : if( CheckQueueSize() ) return false; 
	                IDs[G100.NextQueue & 0x3f] = tIDs[ message->Header.seq & 0x3f ];
	                ((WTDwell*)message->Message)->m.qseq = G100.NextQueue++;  
	                message->size = sizeof( WTDwell);
	                debug.Format( " DWELL: SEQ# %d Message# %d \n",G100.NextQueue, message->Header.seq);
					DebugOut( debug ); 
                    break;
 case( WT_MONITOR): //no qseq required. 
	                message->size = sizeof( WTMonitor);
					debug.Format( " MONITOR: SEQ# %d Message# %d , mask: %x, states : %x  ID %d\n",G100.NextQueue, message->Header.seq,
						((WTMonitor*)message->Message)->haltMask, ((WTMonitor*)message->Message)->haltValue, 
						((WTMonitor*)message->Message)->chResponse );
					DebugOut( debug ); 
                    break;
 default:           //not a sequenced message, no check necessary
	                debug.Format( "Non Movement: SEQ# %d Message # %d \n",G100.NextQueue, message->Header.seq);
	                DebugOut( debug ); 
	                break;
   }
 G100.NextQueue = G100.NextQueue & 0xffff;
 return true;
}



bool MessageTracker::CheckQueueSize() //retunr true if the queue is too full already..
{
	if( G100.EndQueueSeq - G100.CurrentQueueSeq > 23 ) return true; //too much used already..
    return false;

}

//Error recovery..

void MessageTracker::SeqError(void)
{ 
	//we are getting a sequence error, time to refresh the queue and change the seq numbers if necessary
	//This may be a repeat message, so if the seq looks good on the messages, just exit.
	//As a test, lets send a DWELL with the proper SEQ just to turn off the error..
static int lastseqerr = -1;

if( G100.LastAck == lastseqerr ) return;

    lastseqerr = G100.LastAck; //one seq error is enough..
	//We really should never get here if the messager class is working well.
 	CString debug;
	DebugOut( "Sequence Error: \n ");
	debug.Format( "Expected SEQ: %d  on  MSG: %d \n",G100.EndQueueSeq, G100.LastAck ); 
    DebugOut( debug );
	InitQueue =1;
}

void MessageTracker::LostMessage( int lost )
{
CString debug;
debug.Format( "Lost Message  # %d \n ", lost ); //retransmitting at ack +1
DebugOut( debug );
//The g100 has reported a lost message. I never got Message number "lost", so lets reset the queue to the proper message.
  bool found = false;
  for( int x = 0; x < 8; x++)
  {
	  if( OutMessages[x].Header.seq == lost  )
	  {
        m_Tail = x; //this shoudl reset us to this message to go out. Hopefully, the head is not too far ahead and overwritten this
		found = true;
		break;
	  }
  }
  if( !found) 
  {
	  DebugOut( "********Lost message not in queue..resetting message sequence to acked value+1 \n" );
	  TRACE( "We have a lost message not found in the queue.. %d", lost );
	  G100.LastStored = G100.LastAck + 1; //set the new message access to the lost message ack +1 for the next message...
	  m_Head = m_Tail = G100.LastStored & 0x07;
  }

}

short MessageTracker::QueueLeft(void)
{
   int nLeft = 6 - nMessages;
   if( OutMessages[m_Head].Header.seq != 0 )
   {
	   nLeft = 0;
       DebugOut( " **Zero message remaining sent due to locked header..** \n" );
	   CString locks;
	   locks.Format(" [%d][%d][%d][%d][%d][%d][%d][%d] ",
		              OutMessages[0].Header.seq,
					  OutMessages[1].Header.seq,
					  OutMessages[2].Header.seq,
					  OutMessages[3].Header.seq,
					  OutMessages[4].Header.seq,
					  OutMessages[5].Header.seq,
					  OutMessages[6].Header.seq,
					  OutMessages[7].Header.seq );
      DebugOut( locks );

   }
   return nLeft;
}

void MessageTracker::AckMessage(int ack)
{
static int lastacked = ack;
CString debug;
debug.Format( "### ACK : %d" , ack); 
DebugOut(debug );

if( lastacked == ack ) return; else lastacked = ack;   //no sense wasting time on repeated acks..
G100.LastAck = ack;  // set the # of the last message number accepted by the G100;

short low = (m_Head == m_Tail) ? 0 : m_Head;
short hi =  (m_Head == m_Tail) ? 7 : m_Tail;

for( int x = 0; x < 8 ; x++ )  //todo, rewrite this to more efficient unsigned test of ack removal..
 {
	  int test = OutMessages[x].Header.seq;
	  if( test !=  ((ack + 1) & 0xff) &&
          test !=  ((ack + 2) & 0xff) &&
		  test !=  ((ack + 3) & 0xff) &&
		  test !=  ((ack + 4) & 0xff) &&
		  test !=  ((ack + 5) & 0xff) &&
		  test !=  ((ack + 6) & 0xff) &&
		  test !=  ((ack + 7) & 0xff) &&
		  test !=  ((ack + 8) & 0xff) &&
		  OutMessages[x].Header.seq != 0 )
	  {
       debug.Format( "Message %d set to zero.", OutMessages[x].Header.seq );
	   DebugOut( debug );
	   OutMessages[x].Header.seq = 0; //Zero out the sequence, so easier debugging is possible.
      }

  }
	 
}
