#pragma once
#include "socketcomm.h"

#define uchar unsigned char
#define word  short

typedef struct {
	uchar	chanflgs;	// Channel number plus flags:
#define UCHAN_MASK	0xE0	// Channel number field (0..7) - use 0 (CONTROL_CHAN) for this application
#define UCHAN_VERS	0x10	// Version bit (currently must be 0)
#define UCHAN_SYN 	0x08	// SYN bit.  Set 1 when starting session.
#define UCHAN_WNDO	0x07	// Receive window (packet count) for this channel
	uchar  seq;			// Transmit sequence number (packet count, wraps mod 256).
	uchar  ack;			// Acknowledged sequence number (last seq field received on this channel)
    uchar  resv;		// Reserved; set zero.
    word   chksum;		// Internet type checksum.  Only used if USB transport, otherwise set zero.
    word	 type;		// One of the WT_* numbers.  Followed immediately by the
   							// appropriate structure (if any).  This field is omitted
                        // if a 'zero length' message is being sent.
} MessageHdr;

struct AddressAssign
{
   int		ipaddr;
   int		netmask;
   unsigned char     mac[6];
   unsigned char     resv[15];
};

struct wtsConf
{
	unsigned char divider;
	unsigned char outMode;
	unsigned char ctrMode;
	unsigned char resvb;
	short  extctr;
	short  intctr;
	float  MaxAccel;
	float  MaxVel;
};

struct config 
{
	unsigned char Version;
	unsigned char BoardID;
	short CoreModule;
	short MaxMavg;
	unsigned char AxisCompiled;
	unsigned char InputBits;
	unsigned char OutputBits;
	unsigned char AnaInput;
	unsigned char AnaOutput;
	unsigned char FPGAID;
	unsigned char MAC[6];
	unsigned char DateCode[6];
	char     Verbosity;
	unsigned char resvb[3];
	char     ID[16];
	unsigned int IP;
	unsigned int NetMask;
	short    netflags;
    short    resvw;
	wtsConf  Axis[6];
};



class SlabSockets :
	public CSocketComm
{
public:
	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);
	virtual void OnEvent(UINT uEvent);
	SlabSockets(void);
	~SlabSockets(void);
	bool MessageHolding;
};
