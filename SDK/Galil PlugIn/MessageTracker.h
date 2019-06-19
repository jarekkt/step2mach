#pragma once


// MessageTracker

class MessageTracker : public CWnd
{
	DECLARE_DYNAMIC(MessageTracker)

public:
	MessageTracker();
	virtual ~MessageTracker();
    G100Message  OutMessages[8];  //Main Message ring buffer only 8 messages will be queued up at any time. 
	CTime        OutTimes[8];
    

	G100Message  TempMessage;     //used for general reset messages from the tracker.

	int       m_Tail;    // this is the Tail of the ring buffer..
	int       m_Head;    // head of ring buffer.
    


	unsigned short   m_QueueUsed; //amount of queue used in the G100. Unsigned short to autorollover with the G100's message queue pointers. 
	int             nMessages;          //the number of messages we are holding to go out when they can.
	int             nSpace;             //the inverse of the above, how many messages do we have space for..
	CStdioFile  debugfile;              //for output deebugging messages.
protected:
	DECLARE_MESSAGE_MAP()
public:
	void ResetQueue(void);
	void Update(void);
	short QueueLeft(void);
	bool Add2Queue( G100Message* OutMessage);  //this copies the temp holder message to the queue for output
	void SendMessages(void);
	void SetMessDef( G100Message* mess, short type); //used to setup an output message size and type
	bool SequenceMessage(G100Message* message);
	void SeqError(void);
	void DebugOut( CString string); //for debugging..
	bool CheckQueueSize();
	void Purge(); // kill all message traffic, queued commands. In other words..STOP!!
	void MessageTracker::LostMessage( int lost ); //recover from lost message..
	void AckMessage(int ack);
};


