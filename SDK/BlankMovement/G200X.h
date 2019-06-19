/*** BeginHeader */

/*
   Copyright (C) 2005 Xarach Controls, 204 Cypress Drive, Woodland, CA, U.S.A..
   All rights reserved.

   You may use this software under the terms of the Gnu Public License
   provided that this copyright notice is retained in its entirety.
 */
#ifndef PROTOCOL_HH
#define PROTOCOL_HH

/*
   This file defines a communications protocol between the G100 (step
   generator unit) and a host computer.

   The protocol is defined in terms of C structure definitions, which are
   passed in UDP (or any other packet-based transport protocol) without any
   translation, in native binary format.

   These structs are sent over a comm link for control, configuration and monitoring.
   This header is for the host PC and the g200x, thus struct definitions must map
   to 32-bit alignment requirements.  Where relevant, there is also a 64-bit
   alignment restriction on some structs.  In order to produce the correct
   alignment on a variety of host architectures, reserved fields are added.
   These fields should always be set to zeros for upward compatibility.

   If the host supports native 64-bit integers (long long) then you can
   define the preprocessor symbol HAVE_LONG_LONG to use this type in the
   appropriate field definitions in this header.

   Since the host is likely to be little-endian, and the Rabbit is also little-endian,
   all multi-byte fields are coded in little-endian format i.e. least significant
   byte first.

   Floating point values are passed in 4-byte IEEE format, LSB first.

   Since UDP (over IP and Ethernet) is expected to be the prevalent network/
   transport protocol, some elements of the protocol defined herein are
   specifically targeted at that medium.  In particular, there is a UDP
   "discovery" protocol defined so that G100 units may be located on a
   local Ethernet segment.

   If a point-to-point medium is used (such as PPP over USB) then
   the discovery protocol is irrelevant.

   -----

   Protocol Classes

   The G100 supports two classes of protocol.

   (1) "Command-based"

   (2) "Direct"

   Command-based protocol attempts to completely relieve the host of any
   real-time requirements.  Direct protocol is intended for hosts which
   prefer almost instantaneous access to the G100 hardware, at the possible
   cost of a much more stringent real-time network layer.

   Whichever class is used, the G100 starts out using the discovery process
   outlined below.  Once an initial "connection" is established, a special
   message may be used to change over to direct class protocol.  Until
   such time, the G100 remains in command class.

   Command class uses normal UDP/IP packets.  Direct class, once started,
   completely abandons the normal IP network stack, and changes over to
   using raw ethernet frames.  Once in this mode, it ignores normal IP
   (and ARP) packets and can only be restored to command class by rebooting.
   The use of raw ethernet frames by direct class precludes use of any
   IP router between the host and the G100 -- there must be a direct ethernet
   segment.

   Also, only the actual Ethernet interface is supported.  USB has too much
   overhead on the Rabbit to be practicable for direct class protocol.

   -----

   Channel numbers (defined in the MsgHeader section) are used as follows:

   Channel 0 - control channel (binary structs as defined herein, bidirectional).

   No other channels currently used.


   NOTE: the bigest packet allowed is 258 bytes.  With the addition of the
   8-byte MsgHeader, this requires a transport MTU of 266 bytes.

   Since this header is included by both dynamic C and the host (gcc etc.), make sure it
   is "self-sufficient".  For parts which are for Dynamic C only, surround
   with '#ifdef G200X_FIRMWARE  ...  #endif', or '#ifndef G200X_FIRMWARE...' for host-only.
   G200X_FIRMWARE should be defined only in the Rabbit code (g200x.c), never the host
   code.


   No substantial changes should be made unless the version number (VERSION) is
   incremented.


   General notes:

     The message structures are designed such that, if the message is shorter than
     the full structure length, the highest numbered axes are assumed to have all
     zero values.  This makes it more efficient when the machine only has, say,
     3 axes.  In this case, the first 3 array elements can be filled, and the
     rest of the structure implicitly set to zeros by sending a shortened message.
     This requires that all values which are axis-specific are coalesced into their
     own structure, then the last part of the message is always an array of these
     structures.

     Design philosophy puts the onus on the PC (host) side to perform error
     correction, retransmission etc.  The g100 simply blasts out replies
     (or unsolicited messages) without worrying about whether thay are received.

   UDP discovery protocol, on Ethernet:

     The host PC starts by creating a UDP (datagram) socket.  Any local port
     number may be used.  It then sends an empty (zero length) datagram to
     port DISCOVERY_PORT (normally 13887), using the broadcast IP and hardware
     addresses (all 1's).

     All G100s on the local ethernet will respond with a datagram containing
     only a WTConfig struct i.e. without the normal MessageHdr.  Inside this
     struct, the ipaddr field contains the IP address of the G100.  The PC
     should select one of the responding units.  If the ipaddr field is zero,
     then that unit could not determine its own IP address.  In this case, the
     PC should prompt the user to supply an address and netmask.  Otherwise,
     the IP address given in the WTConfig reply may be used for normal
     session communication.

     In the case that the IP address was zero, then another discovery packet
     should be broadcast, except that this time the datagram contents should be
     an AddressAssign struct.  The unit whose hardware address matches the
     'mac' field in the AddressAssign will then assume it can use the other
     fields (ipaddr and netmask) and will then assume it can use these parameters,
     and will respond with a WTConfig reflecting the new settings.

     If the G100's IP address is non-zero, but the host PC determines that
     the address is not suitable for the current network segment, then it
     may send an AddressAssign message with a different IP address/netmask.
     In this case, the G100 will temporarily change its network parameters
     to those provided.

     The host PC can obtain the hardware address from the 'mac' field in the
     initial WTConfig.  If there is an AddressAssign struct in a discovery
     packet, _only_ the G100 with a matching hardware address will respond.

     In general, the host PC should wait about 1 second before declaring a
     timeout condition.  It should retry discovery operations about 3 times
     before giving up and informing the user.

     A G100 which is assigned a network address in the discovery phase will
     only use that address until its next power cycle, after which the
     discovery/address assign needs to be repeated.  If the address is to be
     made permanent, then the PC should send a WT_CONFIG message (in the normal
     session traffic) in order to save the address permanently into flash
     memory.

     If, during a session, the host sends a WT_CONFIG message, the G100 will
     reboot.  It is recommended that the host waits 6 seconds, then re-initiates
     the discovery phase.  In principle, discovery could be omitted if the host
     remembered the last IP address in use, however it is possible for the
     G100's IP address to change on boot-up (e.g. if it is using DHCP).

   UDP normal session traffic:

     The purpose of discovery, above, is to determine the network address of
     a G100.  Once this has happened, further communication happens exclusively
     on the session socket.

     The host PC creates a new UDP socket with any local port, and a destination
     port of SESSION_PORT (normally 13888).  Unicast mode should be used i.e.
     use the unique hardware and IP address.

     The session needs to be established.  The first message sent by the host
     PC must set the UCHAN_SYN flag.  After receiving a response with the
     same flag, then the session is considered open.  At and after this point,
     the G100 will only respond to the host who sent the original UCHAN_SYN
     flag, and that host has to use the same local UDP port number.  If another
     host wants to take over the session, then it must initiate communications
     from the discovery phase.

     All datagrams sent on the session socket have the same format: a
     MessageHdr followed by one of a number of structures as documented
     herein.  The header contains a type field which indicates which of the
     message structures follows.  The type numbers are all defined as macros
     starting with 'WT_'.

     Each message is sequenced.  Message sequence numbers are single byte
     fields in the MessageHdr, and wrap around from 255 back to 0.  The G100
     is only capable of processing messages in strictly ascending order.
     If it receives an out-of-order sequence number, it immediately responds
     with a message which has a shortened (6-byte, no type field) header.
     This allows the host to resync to where the G100 is actually up to,
     and retransmit if necessary.

     The only exception to the strictly ascending sequence numbers is in the
     case of the initial UCHAN_SYN flag, in which case both sides' sequence
     numbers are reset to zero.

     The protocol is designed so that each host message will elicit a
     response.  In addition, the G100 sends unsolicited messages every
     250ms, and possibly other messages when 'unpredictable' events occur.
     The G100 is not capable of retransmitting, so the host must be able to
     deal with the odd missing message.

     As an aid to developing correct host software implementations, there
     is a special "test mode" message which may be sent.  This message may
     tell the G100 to "act strange" (e.g. ignoring every Nth packet, or
     pretend that certain events happen which would be very rare in normal
     circumstances).

   Change History:
    2005 May 12  SJH  Initial cut.
    2005 May 30  SJH  Co-operative release.
    2005 Aug 02  SJH  Update WT_MONITOR semantics, enhance documentation
    2005 Aug 20  SJH  Add direct class protocol (for EMC project)

*/

// Maximum size message payload.  This is everything after the header (MessageHdr).
// The longest message is currently WT_CONFIG, at 298 bytes.
#define MAX_MESSAGE	384	// Allow a bit extra for future enhancements


#define DISCOVERY_PORT	13887		// UDP port number for discovery messages
#define SESSION_PORT		13888		// UDP port number for normal session traffic


#define CONTROL_CHAN		0			// The only defined channel.


#define BOARD_G100		0x03		// is a FPGA-based board (G200X renamed to G100).

// Type codes in the 'MessageHdr' packet header.
// Naming convention:
//   WT_XYYYY   Type code for message
//   WTXyyyy    Corresponding struct
//   WTSXzzzz   Sub-structure
// The struct typedef name is the same as the macro, except underscores removed
// and the letters other than 'WT' and the first letter of the specific word
// are in lowercase.

	// g200x -> host, and host -> g200x
#define WT_NULL		0		// Null packet (no operation, no data).  May be used to
										// verify the connection.  The g200x will always
                              // respond to a WT_NULL message with another WT_NULL,
                              // however the host must not respond (to avoid an
                              // infinite message loop).
#define WT_CONFIG		1		// Configuration record.  Allows the host to
										// upload a complete configuration, which the
                              // G100 will save in non-volatile memory, then
                              // reboot.

	// g200x -> host.
#define WT_MSG       17		// An ASCII-formatted message.  No struct is defined.
									// See comment below for formatting requirements.

   // host -> g200x (codes in range 32-63).
#define WT_GETCONFIG	32		// Get G100 to send WT_CONFIG message
#define WT_DWELL		33		// Add dwell queue element
#define WT_LINEAR		34		// Add linear queue element
#define WT_CUBIC		35		// Add cubic queue element
#define WT_RATE		36		// Set execution rate
#define WT_PURGE		37		// Purge forward
#define WT_DIGOUT		38		// Set digital outputs
#define WT_ANAOUT		39		// Set analog outputs
#define WT_MONITOR	40		// Monitor digital and/or analog inputs
#define WT_GETPOS		41		// Get current position (pre mavq)
#define WT_WH_PROG	42		// White Heat program record
#define WT_WH_DATA	43		// White Heat data record
#define WT_WH_LOAD	44		// White Heat program load control
#define WT_DIRECT		61		// Change over to direct protocol class -
										// This breaks IP!  From the point of
                              // this message, raw ethernet frames with type
                              // DT* (instead of WT*) are exchanged.
#define WT_TESTMODE	62		// Set various test modes
#define WT_BYE			63		// Halt the g200x (but remain alive).  It stops sending
									// any messages until the host sends a SYN message.
                           // The purpose of this is to remove network traffic
                           // when Mach4 shuts down.  No additional data,
                           // no response (by definition!).

	// g200x -> host.  The MS_* codes are not used alone, but are ORed with WT_MSTATE.
   // The host should be prepared to handle any of these combinations, for
   // upward compatibility.  The ordering of the sub-message parts is the same
   // as the bit ordering here:
   #define MS_QCAP	0x01	// Queue capacity
   #define MS_QSTAT	0x02	// Queue status
   #define MS_ABS		0x04	// Absolute co-ordinates and velocity (post mavg)
   #define MS_OUT		0x08	// Current digital and analog output settings
   #define MS_IN		0x10	// Digital and analog inputs
   #define MS_CTR		0x20	// Counters and encoders
   #define MS_POS		0x40	// Absolute co-ordinates (pre-mavg, high precision)

#define WT_MSTATE		0x80	// Machine state.  This code is ORed with one
									// or more of the MS_* codes, resulting in one of
                           // the follwing allowable combinations:
// MSTATES with single contents
#define WT_MS_QCAP (WT_MSTATE | MS_QCAP)
#define WT_MS_QSTAT (WT_MSTATE | MS_QSTAT)
#define WT_MS_ABS (WT_MSTATE | MS_ABS)
#define WT_MS_OUT (WT_MSTATE | MS_OUT)
#define WT_MS_IN (WT_MSTATE | MS_IN)
#define WT_MS_CTR (WT_MSTATE | MS_CTR)
#define WT_MS_POS (WT_MSTATE | MS_POS)
// MSTATES with multiple contents
#define WT_MS_FULL	0xBF	// Mostly complete MSTATE record (these are issued
                           // every 250ms,
									// and constitute a heartbeat from the g200x).
#define WT_MS_ASYNC	(WT_MSTATE|MS_QCAP|MS_QSTAT|MS_POS)
									// Record sent on asynchronous (unpredictable) event,
                           // as well as WT_GETPOS and WT_PURGE requests from host.
#define WT_MS_OUTIN	(WT_MSTATE|MS_OUT|MS_IN)
									// Response to I/O setting/monitor commands from host

/******************************************************************************
 ASCII message format
 ******************************************************************************/

/*
   For the purpose of debugging, the g200x may send ASCII messages to the PC,
   with the type field set to WT_MSG.

   The message strings are limited to about 256 bytes, and follow this format:

     - First character

         E   Error message
         W   Warning
         I   Informational
         anything else: debug (usually 'd')

     - A colon (:)

     - Free format message text (printable ASCII)

     - Newline (\n)

   E.g. (in C syntax)  "E: acceleration limit for axis 2 exceeded\n".

   Note that there is no requirement to send the null terminator, but the
   receiver should be able to discard a trailing null.
*/


/******************************************************************************
 Platform compatibility typedefs
 ******************************************************************************/

#ifndef G200X_FIRMWARE
	// Set appropriate host type.
   // NOTE: review these if porting to non-i386 architecture.
	typedef unsigned short word;  // 16-bit unsigned
	typedef unsigned int   lword; // 32-bit unsigned
	typedef signed int     slong; // 32-bit signed
	typedef unsigned int   ufrac; // 32-bit unsigned fraction part of 64-bit signed word.
	typedef unsigned char  uchar; // 8-bit unsigned
#else
	// Dynamic C types ('word' is predefined)
	typedef unsigned long lword;
	typedef unsigned long ufrac;
	typedef long          slong;
	typedef unsigned char uchar;
#endif


/******************************************************************************
 Overall message and protocol header definition
 ******************************************************************************/

// If using UDP transport, the UDP datagram consists of a MessageHdr followed by
// one of the WT* structures.
//
// If using USB, then the same payload is generated, plus the checksum is computed,
// then the payload is escaped using the HDLC framing (0x7E frame delimiter,
// 0x7D escape).
//
// Note that there is no explicit length field.  It is assumed that the lower
// network layers maintain the message length.  This is true in the case of IP.
// For HDLC-framed USB, the frame delimiter implicitly determines the message
// length - no padding is transmitted.

typedef struct {
	uchar	chanflgs;	// Channel number plus flags:
#define UCHAN_MASK	0xE0	// Channel number field (0..7) - use 0 (CONTROL_CHAN) for this application
#define UCHAN_VERS	0x10	// Version bit (currently must be 0)
#define UCHAN_SYN 	0x08	// SYN bit.  Set 1 when starting session.
#define UCHAN_WNDO	0x07	// Receive window (packet count) for this channel
	uchar  seq;			// Transmit sequence number (packet count, wraps mod 256).
	uchar  ack;			// Acknowledged sequence number (last seq field received on this channel)
   uchar  resv;		// Reserved; set zero.
   word   chksum;		// Internet type checksum.  Only used if USB transport, otherwise
   						// set zero.   If used, it covers the entire message
                     // including this header.  For purpose of computation, this field
                     // is initialized to zero.  Then the 1's complement sum of all
                     // 16-bit words in the message is computed (pad with one zero byte
                     // at end if an odd length).  The 1's complement of this value
                     // is then stored in this field.
   word	 type;		// One of the WT_* numbers.  Followed immediately by the
   							// appropriate structure (if any).  This field is omitted
                        // if a 'zero length' message is being sent.
} MessageHdr;

// Note that the window field is used in the following manner: it indicates how
// many packets ahead of the 'ack' number may be transmitted, with guaranteed
// buffer space.  For example, on receipt of a message with ack=10, and wndo=4,
// then messages with seq=11,12,13 and 14 (on the same channel) could be sent.
// The seq and ack spaces apply globally to all channels (not just the
// channel mentioned in the message), however the wndo field applies just to
// the specified channel.

// If the g100 receives a message with an out-of-sequence 'seq' number, then it
// will respond with a zero length message.  This message will indicate the correct
// sequence points.  A 'zero length' message is one in which a shortened MesageHeader
// is sent (i.e. with no type field, just the first 6 bytes).  These messages do
// not increment the transmit sequence number; it stays the same as the last normal
// message.

// Messages with a channel number not '0', or a bad checksum, or from a host
// or UDP port other than the one which sent the SYN, will be quietly dropped.

/******************************************************************************
 Sub-structures incorporated into messages
 ******************************************************************************/

// Common sub-struct for motion commands (DWELL, LINEAR, CUBIC)
typedef struct {
   word		qseq;	// Target motion queue sequence number
	word		T;		// Step generator ISR iteration count
   word		resv[2];	// Padding for 8-byte alignment, since followed by DDAs
} WTSMotion;

// Common sub-struct for a 64-bit fixed point DDA coefficient.  This is split
// into two 'long' values, however for hosts with a native 64-bit data type
// (long long in C) the alignment of this sub-structure is guaranteed to be
// on an 8-byte boundary.   This precision may seem extreme, however it allows
// the cubic DDA algorithm to run for at least 2000 iterations without any
// practical error.
#ifdef HAVE_LONG_LONG
typedef long long	WTSDDA;	// 64-bit fixed point.  Integer part in most significant 32 bits.
#else
typedef struct {
	ufrac		f;		// Unsigned fraction extension
   slong		i;		// Integer part
} WTSDDA;
#endif

// Collection of 3 DDA's for cubic motion
typedef struct {
	WTSDDA	dda1;	// Velocity
	WTSDDA	dda2;	// accel = dv/dt
	WTSDDA	dda3;	// jerk = da/dt
} WTSDDAs;

// Low and high bounds for analog input monitoring
typedef struct {
	word		low;
   word		high;
   word		resv[2];
} WTSLohi;

// Encoder/counter and lead/lag readings
typedef struct {
	word		c;		// Counter reading
   char		LL;	// Lead/lag reading (-128..127).
   uchar		aflags;// Axis flags:
#define AF_CTRA	0x01		// State of counter input A
#define AF_CTRB	0x02		// State of counter input B
#define AF_CTRX	0x04		// State of counter input X (index)
#define AF_CTRF	0x08		// Counter fault detected
#define AF_XLOHI	0x10		// Counter index input went lo->hi
#define AF_XHILO	0x20		// Counter index input went hi->lo
// Note that CTRF, XLOHI and XHILO are only reset when a WT_PURGE message is received,
// or a new session is established.
} WTSFeedback;

// Axis configuration settings
typedef struct {
	uchar		divider;			// Axis divider setting (0..7) 0 gives 4MHz full scale;
   								// 7 gives 32kHz full scale.
   uchar		out_mode;		// Output mode for step generator as follows:
#define OM_SD_50		0x00		// Step/Direction, 50% duty, active on positive step edge.
#define OM_SD_50_INV	0x08		// Step/Direction, 50% duty, active on negative step edge.
#define OM_SD_25     0x10		// Step/Direction, 25% duty, active on either step edge.
#define OM_SD_75     0x18		// Step/Direction, 75% duty, active on either step edge.
#define OM_SD_QUAD	0x20		// Quadrature.  Step is channel A, Direction is channel B.
   uchar		ctr_mode;		// Counter mode as follows:
#define CM_QUADRATURE			0x00
#define CM_TACHA_RISING			0x50
#define CM_TACHA_FALLING		0x90
#define CM_TACHA_DOUBLE			0xD0
#define CM_TACHB_RISING			0x60
#define CM_TACHB_FALLING		0xA0
#define CM_TACHB_DOUBLE			0xE0
#define CM_STEP_FALLING			0x30
#define CM_STEP_RISING			0x70
#define CM_STEP_REV_FALLING	0xB0
#define CM_STEP_REV_RISING		0xF0
   uchar		resv;				// Reserved, set 0.
	short		ext_ctr;			// External counter increment (-2048..2047)
   short		int_ctr;			// Internal counter increment (-2048..2047)

   // The above fields directly affect the hardware settings.  The following
   // fields are used by the firmware to help control acceleration, velocity etc.
   float		maxa;				// Maximum acceleration, internal steps/ms/ms.
   float		maxv;				// Max velocity, internal steps/ms.
   /*
      When the global rate setting is changed (WT_RATE), the above values
      are used to determine the allowable increment in the global rate register
      for each I/O ISR period.  When the GRR is requested to change, the
      current post-mavg velocity (= v(i)) of each axis is considered.  The
      allowable delta GRR is computed as
        dGRR = maxa(i) * 65536 / f(v(i))
      taking the minimum over all axes i = 1..6.  f(v) is a function which
      acts to reduce the allowable acceleration for high velocities v ~ maxv.
      Typically, the accel at full speed is half that at speeds near zero.
      Thus, f(v) = v (1 + v/maxv).  The accel is constant for any given initial
      velocity, however the slower accel at high v compensates for the reduced
      torque available at higher speeds.
   */
   char		pad[16];			// Pad axis config sub-struct to 32 bytes.  Set zero.
} WTSAxisConf;

/******************************************************************************
 WT_CONFIG  Configuration data struct stored in user block
    Bidirectional message.  G200x sends when session established.
    Host may send to change configuration (causes reboot).

    This is also sent directly, without any header, in a response to a UDP
    discovery request from the host.  The host may include an AddressAssign
    struct in its discovery request, which will temporarily set the IP address
    if it is not already valid.
 ******************************************************************************/

// Define firmware version/release.  Goes in WTConfig.version field.
// Only change this for some protocol incompatibility.
#define VERSION_DLM			0x00	// This means the DLM is running
#define VERSION				0x01	// Otherwise, it's the DLP.

typedef struct {
// NOTE: if any of the following fields are changed (because of re-compile), then
//   the user block (non-volatile copy) is automatically updated:
	uchar version;					// Config block (and firmware) version -- set to VERSION
   									// NOTE: if this is VERSION_DLM, it means that the download
                              // manager is running.  Otherwise, it identifies the firmware.
	uchar board_id;				// Hardware ID -- set to BOARD_G100
	word  coremodule_id;			// Rabbit core module etc. ID (from _BOARD_TYPE_ macro)
   										// Set to 0x8... for non-Rabbit MCU boards
   word  max_mavg;				// Max entries in moving average queue (power of 2 between 4 and 4096)
   uchar	axes_compiled;			// Bit set for each axis compiled in.  Normally, you get all axes (0x3F)
                              // Bit [axis#] is set if the axis is compiled in.
   uchar	input_bits;				// Number of digital inputs.  22 on the current g200x.
   										// Architected maximum of 31.  Higher than this requires
                                 // protocol version increment.
   uchar output_bits;			// Number of digital outputs.  Currently 16 outputs.
   										// Architected maximum of 31.
	uchar input_ana;				// Number of analog inputs (4)
   uchar output_ana;          // Number of analog outputs (4)
   uchar	fpga_id;					// FPGA config version/release.  High 4 bits is version,
   									//  low 4 bits are release.  0xFF if FPGA failed to configure.
   uchar mac[6];					// Ethernet MAC address.  Zero for non-ethernet boards.
   char  datecode[6];			// Firmware datecode.  This is not actually stored in the
   									// user flash block.  It is always set by the firmware.
                              // YYMMDD format.
   char	verbosity;				// Firmware debug level
   uchar	resvb[3];
   char	vend_id[36];			// Firmware vendor ID string/copyright notice.  Pad unused
   										// part on the right with nulls.

	// Note: above 64 bytes are read-only i.e. initialized by constants in the
	// firmware and/or flash memory.  Following fields may be reconfigured by the host.

   char	id[16];					// Controller name (0-15 chars, plus null terminator)
   									// "FACTORY" until set by host assignment.
   lword ipaddr;					// Hard-coded IP address (0 if not assigned)
   lword	netmask;					// Netmask (default 255.255.255.0)
   word  netflags;				// Networking flags as follows:  (default is USE_DHCP)
#define NF_USE_DHCP 		0x0001		// Attept to use DHCP
#define NF_FORCE_USB		0x0002		// Don't use Ethernet
#define NF_FORCE_ETH		0x0004		// Don't use USB (overrides the above)
	word	resvh;					// Reserved
   lword resvl;					// Pad to 32 bytes from end of read-only area
	WTSAxisConf		axis[6];		// Config for each axis (32 bytes each)
} WTConfig;

// Sent as raw data in a discovery packet which is assigning a temporary address.
typedef struct
{
	lword		ipaddr;
   lword		netmask;
   uchar    mac[6];
   uchar		resv[18];		// Pad to 32 bytes
} AddressAssign;

/******************************************************************************
 WT_DWELL  Dwell queue element addition
	Host -> g200x
   Response: WT_MS_QCAP
 ******************************************************************************/

typedef struct {
	WTSMotion	m;					// m.T is dwell interval at guaranteed zero velocity.
   										// Must be 0..65534 (65535 is reserved, do not use).
   word			FMsize;			// Resize moving average queue
   										// If zero, no resize.  Otherwise, must be
                                 // 4, 8, 16, 32 ... 4096, but no higher
                                 // than the limit in WTConfig.max_mavg.
   word			RMsize;			// Reserved field, set zero.
} WTDwell;


/******************************************************************************
 WT_LINEAR  Linear motion queue element addition
	Host -> g200x
   Response: WT_MS_QCAP (or WT_MS_ASYNC if T==0)

   Safety note for jogging (T=0) moves:

   We force the iteration limit to a finite value, to prevent the
   machine 'running away' if a message goes missing.  The time limit is 1/4
   second.  Thus, during a jog sequence, the host must provide messages at least
   every 200ms or so to avoid jerky motion.  Since jog moves are considered
   asynchronous, a WTMsAsync message is sent instead of the normal WTMsQcap.

   Queue sequence numbers must be strictly ascending whether or not this is
   a jogging move.

   Apart from the T=0 convention, a linear motion segment is identical to
   a cubic segment (see below) with dda2=dda3=0.


 ******************************************************************************/

typedef struct {
	WTSMotion	m;             // T is number of iterations, for standard chained
   										// motion (1..65535).  If T=0, then this is
                                 // treated as an interrupting move (e.g. for jog).
                                 // In this case, it is as if a WT_PURGE command
                                 // was sent (with no flags) followed by a
                                 // 256ms linear motion as specified in the
                                 // dda1 parameters.
   WTSDDA		v[6];				// dda1 (velocity) for each axis
} WTLinear;


/******************************************************************************
 WT_CUBIC  Spline motion queue element addition
	Host -> g200x
   Response: WT_MS_QCAP

   This segment is intended for efficient generation of arcs and curved
   motion.  The math is simple: at each iteration (1024Hz rate) the
   following operations are performed in sequence:
     <current velocity> = dda1
     dda1 += dda2
     dda2 += dda3
   At T=0, all ddas are set to the value in this message.
   After T iterations of this algorithm,
     <pos> = <start pos> + dda3*T*(T-1)*(T-2)/6 + dda2*T*(T-1)/2 + dda1*T
     dda1 = dda3*T*(T-1)/2 + dda2*T + dda1
     dda2 = dda3*T + dda2
     dda3 = <unchanged>
   where the right hand side dda's are the initial values.
   Linear motion (with dda2=dda3=0) may run for 65536 iterations (the max) with
   no loss of accuracy.  Parabolic motion (dda3=0, dda2 != 0) may also run
   for this many iterations.  General cubic motion may run for about 4096
   iterations, after which there may be some rounding error.   Rounding
   error is defined as more than 1/2 an output step.
 ******************************************************************************/

typedef struct {
	WTSMotion	m;             // Number of iterations (1-4096).
   WTSDDAs		d[6];				// all 3 ddas for each axis
} WTCubic;


/******************************************************************************
 WT_RATE  Start execution and control motion ISR rate (Global Rate Register)
	Host -> g200x
   Response: WT_MS_QSTAT (immediate).  When target rate is reached, then
     a WT_MS_FULL is sent, in which the QS_GRR_OK flag will be set.  This
     may be some time after the initial response, since rate changes require
     some finite time to accelerate/decelerate.
   This is intended to be used for pausing motion (set r=0.0), or for feed
   rate overrides (e.g. r=0.5 for 50% normal feed rates).
   Note that the acceleration profile is not necessarily linear.  In general,
   the allowable acceleration when the velocity is high (maxv) is half that
   of when the velocity is near zero.  This accounts for the lower available
   torque at high speeds.
   NB: the minimum allowable rate is 0.25.  Anything less than this is
   treated as full stop via the moving average queue.  The limit on the
   minimum rate is because low rates slow down the interrupt service
   rate in proportion.  This stretches out everything, and becomes untenable
   when slower than 1/4 the normal rate.  [Even dwells are extended].
   If slower feed rate overrides are required, then the host will have to
   modify the commanded feed rates, rather than relying on this dynamic
   feature.
   If rate was set to zero (pause), then the G100 may be unpaused by
   either writing a new rate (0.25 or above), or issuing WT_PURGE which
   will restore to the previous rate setting.
 ******************************************************************************/

typedef struct {
	float			r;					// Execution rate: 0.0 (or less than 0.25) = halt,
   									// 1.0 = normal (fastest),
                              // 0.25-0.99 = feed rate override.
   float			afac;				// Acceleration factor.  1.0 = max accel,
   									// 0.0 = min.   Max accel is defined by the
                              // maxa/maxv fields in the config.
} WTRate;


/******************************************************************************
 WT_PURGE  Purge queue in forward direction.
	Host -> g200x
   Response: WT_MS_ASYNC
   Note that purge automatically unpauses the mavg queue (if it was paused),
   however the current rate (WT_RATE) is not changed.
   The flags allow one or more axis positions to be zerod (mainly for
   debugging, but possibly for zeroing when limit switch hit).
 ******************************************************************************/

typedef struct {
	word			flags;			// Purge flags as follows:
#define PF_ZERO_X	0x0001			// When halted, set X axis position to zero
#define PF_ZERO_Y 0x0002			// Similar, for Y,Z,A,B,C
#define PF_ZERO_Z 0x0004
#define PF_ZERO_A 0x0008
#define PF_ZERO_B 0x0010
#define PF_ZERO_C 0x0020
// Other flags reserved, set zero.
#define PF_WAIT_HALT	0x8000		// No action other than to wait for all
											// motion to cease i.e. wait for mavg queue
                                 // to drain.  If this flag is set, or any of
                                 // the above, then the response message
                                 // (WT_MS_ASYNC) is not sent until the
                                 // mavg queue is drained.
} WTPurge;

/******************************************************************************
 WT_DIGOUT   Set digital outputs immediately
	Host -> g200x
   Response: WT_MS_OUTIN
   Refer to the G100 hardware manual for which bit positions correspond to
   which numbered outputs.  The mapping is not intuitive.
 ******************************************************************************/

typedef struct {
	lword		mask;				// Mask of bits to affect (1=affect, 0=don't touch)
   lword		value;			// Value to set those bits (1=active=pulled low).
} WTDigout;


/******************************************************************************
 WT_ANAOUT   Set analog outputs immediately
	Host -> g200x
   Response: WT_MS_OUTIN
 ******************************************************************************/

typedef struct {
	word		mask;				// Mask of analog outputs to set
   word		value[4];		// Value for each output (0xFFFF is full-scale)
} WTAnaout;



/******************************************************************************
 WT_MONITOR   Specify events to monitor
	Host -> g200x
   Response: WT_MS_OUTIN, or WT_MS_FULL if a challenge was successfully
             answered.

   The 'mask' field indicates the digital inputs to monitor.  Ordinary
   monitoring does not cause the G100 to halt, but it reduces the delay between
   an input changing and when the host is informed.  Without any monitoring,
   there will be up to 1/4 sec delay, and the host may also miss on/off
   events which occur within less that 1/4 sec.  Setting monitoring means
   that the host will be informed of all state changes of the selected
   inputs.

   Refer to the G100 hardware manual for the correspondence between bit
   positions in these fields, and the numbered inputs on the hardware.

   A stronger input monitoring condition is to halt any motion occuring if
   an input reaches a defined state (high or low).  These input bits are
   specified in the haltMask field, and the target state is in haltValue.

   Note that the haltMask gets set into the WtMSQstat field halt_bits.  When a
   matching input is activated (to the corresponding bit state in haltValue),
   then the queue is automatically paused.  An immediate WTMsFull is generated
   at this point.  The WtMSQstate sub-structure therein will indicate, via the
   halt_bits field, which input bit(s) caused the halt condition.  For each
   input bit which has 'hit' (since the last WTMonitor), the corresponding
   bit in the WTMsQstate.halt_bits field will be set to a 1.  There will be
   0's only for each remaining input which is being monitored, but has _not_
   yet hit.  Other bits are irrelevant and should be ignored.

   Any halt condition is a one-time event.  The host is required to re-instate
   the haltMask by sending another WTMonitor.  This facility is intended to be
   used for limit switches and the like.

   For safety, there is also a challenge/response process required.  If a
   limit switch hits, then the G100 increments the 16-bit challenge number.
   The challenge number is basically determined by the last WT_MONITOR message
   received by the G100.  That number, plus 1, is the new challenge number
   when any halt event occurs.

   After a halt, it refuses to perform any motion command until the host sends
   a WT_MONITOR command with a matching response.  This ensures that there is
   no possibility of accidentally restarting motion after a limit switch,
   merely because there were pending motion messages in the queue or network.
   Note that the challenge is repeated every 250ms just in case it was dropped
   the first time.

   Example scenario:

   (1) when the host initially connects, it issues an initial WT_MONITOR for
   the appropriate limit switches, with the chResponse field set to an
   arbitrary number - assume the number is '1' for this scenario.

   (2) when one of the selected limit switches is hit (i.e. matches the
   selected high or low state) then the G100 halts and sends an immediate
   message containing a WTMsQstate.  In this message, the 'curr' field
   will be set to '2' (i.e. 1+1).  It refuses to perform any other motion
   commands until the host responds as follows.  The sflags field also
   has the QS_HALT bit set so that the host can recognize this condition.

   (3) when the host sees a WTMsQstate with the QS_HALT bit set, it looks
   at the challenge number in 'curr' (2 in this case), and thus determines
   that the message is in response to its initial WT_MONITOR.  It can then
   decide how to proceed (either by ignoring further limit switch activity,
   or re-instating monitoring of the affected switch by inverting its
   matching level).  The host sends a new WT_MONITOR with chResponse set
   the '2'.

   (4) when the G100 gets the new WT_MONITOR, with chResponse matching the
   'curr' field it sent, it will install the new monitor and allow motion
   commands to be issued.

   Notes:

   When a halt event occurs, the G100 purges all pending motion from its
   queue.  The host is thus responsible for re-sending any purged commands
   (one of which may have been partially completed).  In practice, this is
   unlikely to be required, since hitting a limit usually aborts the NC
   program or, in the case of probing, the purged part of the motion sequence
   is irrelevant anyway.  The host will need to read back the

   If more than one input is mon'd for halting, then it is possible for several
   halting events to occur in sequence without receiving a host response.
   In this case, more than one WTMsQstate may be sent with the same challenge
   number in 'curr'.  The 'halt_bits' field will indicate the total inputs which
   match the halt condition at the time of each halt event.  There will thus
   be an increasing number of halt_bits set.

   If a new WT_MONITOR is issued by the host, but not in response to an
   outstanding halt event (challenge), the host should pick a new chResponse
   If there is no halt event pending, then the G100 will use
   that chResponse, and add 1 for the next challenge.  Host code should
   remember the previous WT_MONITOR just in case a halt event occurred before
   the G100 got the new WT_MONITOR.
 ******************************************************************************/

typedef struct {
	lword		mask;				// Mask of digital inputs to monitor (1=monitor)
   lword		haltMask;		// Mask of digital inputs to auto-halt queue
   lword		haltValue;		// Required polarity of halting inputs (0=when active=low)
   word		anaMask;			// Analog inputs to monitor
	word		chResponse;		// If the QS_HALT flags is set in WT_MS_QSTAT,
   									// then the 'curr' field in same is a challenge
                              // number.  To proceed (and unlock the halt condition)
                              // then the host must set this field to the same
                              // number.  Any halt condition that occurs after
                              // this message will have its challenge number
                              // set to this number plus 1.
   WTSLohi	a[4];				// Low/high bounds for analog input monitoring
} WTMonitor;


/******************************************************************************
 WT_WH_PROG   White Heat program record
	Host -> g200x
   Response: WT_NULL

   This contains up to 64 White Heat instructions in binary form.  These are
   buffered in the G100's memory until a WT_WH_LOAD message is received.
 ******************************************************************************/

typedef struct {
	word		insn_seq;		// Sequence number of first instruction to program
   								// (must be 0..1023, and insn_seq+num_insn must
                           // be <= 1024).
   word		num_insn;		// Number of instructions following.  Each insn is
   								// a group of 5 bytes.  The actual instructions are
                           // 36-bit, packed little-endian in each 5-byte tuple.
                           // The 4 remaining MSBs must be set zero.
                           // If this is over 64, then it is assumed to be 64.
   char		insn[5];			// First instruction.  Following ones are packed into
   								// groups of 5 bytes, with no padding.  If num_insn
                           // is less than the actual number provided, the others
                           // are ignored.  If num_insn is greater, then the
                           // others are assumed to be all zeros (which is
                           // an unconditional branch to location 1 in the current
                           // version of White Heat).
} WTWHProg;



/******************************************************************************
 WT_WH_DATA   White Heat data space record
	Host -> g200x
   Response: WT_NULL

   This contains up to 128 White Heat data words in binary form.  These
   are written immediately to the WH data memory, without halting it or any
   other action.  If necessary, White Heat should be halted using a
   WT_WH_LOAD message.
 ******************************************************************************/

typedef struct {
	word		data_addr;		// Address of first data word to write
   								// (must be 0..1023, and data_addr+num_data must
                           // be <= 1024).
   word		num_data;		// Number of data words following.  If over 128, is
   								// assumed to be 128.
   short		data[1];			// First data word.  Following ones are extension
   								// of this array.  If num_data
                           // is less than the actual number provided, the others
                           // are ignored.  If num_data is greater, then the
                           // others are assumed to be all zeros.
} WTWHData;



/******************************************************************************
 WT_WH_LOAD   Load and optionally start a White Heat program.
	Host -> g200x
   Response: WT_NULL

   Note that if the WH_LOAD flag is set, this message requires axes to be
   halted, otherwise disaster would ensue.
   To enforce this, the G100 will issue a queue purge and
   wait for all axes to come to rest.  In addition, the ISR is disabled
   during program load (WH_LOAD set).  For this purpose, the watchdog is
   disabled.

   This is best performed at host software initialization time.  It is not
   intended for dynamic control, however that is a possibility.

   Important: this message is potentially dangerous, since it can fundamentally
   change the way that the G100 operates.  In particular, White Heat is
   responsible for performing the digital I/Os, DAC and ADC conversions
   (at least).  Thus, any program must emulate these functions if proper
   behavior of these peripherals is expected.

   White Heat is effectively a specialized CPU within the FPGA.  It is capable of
   fast (50 MIPS) arithmetic evaluation and general control.  Tinkerers please
   refer to the manual.
 ******************************************************************************/

typedef struct {
	word		flags;
#define WH_LOAD   0x8000		// Load program previously downloaded with
										// WT_WH_PROG records.  Otherwise, does
                              // not change the currently running program.
#define WH_RUN		0x0080		// Start execution.  If not set, then stops
										// any current execution.
#define WH_FLIP	0x0040		// Enable data space top/bottom flip (this is
										// usually set for proper execution!).  This
                              // flag is ignored unless WH_RUN set.
#define WH_32KINT	0x0020		// Enable the 32kHz "interrupt" for White Heat.
										// This should always be set for normal functioning.
	word		num_insn;  			// Number of instructions to load (if WH_LOAD).
   word		start_insn;			// Starting sequence to load (if WH_LOAD).
   // Obviously, instructions [start_insn..start_insn+num_insn-1] must have
   // been previously downloaded using WT_WH_PROG records.
} WTWHLoad;



/******************************************************************************
 WT_MS_QCAP   Queue capacity status
	g200x -> host
   Response to WT_DWELL, WT_LINEAR, WT_CUBIC
   Also included in WT_MS_FULL as general heartbeat
 ******************************************************************************/

typedef struct {
	word		cseq;				// Current queue sequence number
   word		sseq;				// Starting (most backward) QSN
   word		eseq;				// Ending (most forward) QSN, plus one.
   word		flags;			// Queue capacity flags as follows:
// Following flags set if an attempted queue addition could not be processed.  These flags
// are only reset when a valid entry is added.
#define QC_F_ERROR   0x4000		// Error: queue was full, ignored.
#define QC_S_ERROR   0x8000		// Error: last queue sequence number was not s-1 or e, ignored.
} WTMsQcap;		// Size 8


/******************************************************************************
 WT_MS_QSTAT   Queue general status
	g200x -> host
   Response to WT_RATE
   Also included in WT_MS_FULL as general heartbeat, and when halting event
   occurs.
 ******************************************************************************/

typedef struct {
	word		curr;				// Two uses:
   								//  If QS_HALT flag set:
                           //    Challenge number.  See WT_MONITOR description
                           //  Else:
                           //    Current QSN (same as cseq in WTMsQcap)
   word		iters;			// Remaining iterations for the current queue element
   word		grr_curr;		// Current Global Rate Register setting
   word		grr_tgt;			// Target GRR setting - set by WT_RATE command (converted
   									// to fixed point: 0=min, 65535=max (1.0)
   word		m_isr;			// Motion ISR counter
   word		i_isr;			// I/O and encoder ISR counter (increases monotonically at 1kHz).
   word		curr_mavg;		// Current mavg queue length
   word		sflags;			// Queue status flags as follows:
// Note that a change in any of the following bits causes a WTMsFull to be sent.
#define QS_HEARTBEAT		0x0001		// This bit toggles every 1/4sec.  Basically, this
													// defines the minimum state update rate.
#define QS_HEARTBEAT_BIT	0

#define QS_STILL_BIT		1
#define QS_STILL			0x0002      // All axes at rest (mavg queue all zeros)

#define QS_END_BIT		2
#define QS_END				0x0004		// Reached end of queue.  This only gets set if the
													// end is reached 'naturally'.  If purged, then
                                       // not necessarily set

#define QS_MAVGZ_BIT		3
#define QS_MAVGZ        0x0008      // Mavg queue is draining (or drained).  When drained,
													// the QS_STILL flag will be set.

#define QS_PAUSE_BIT		4
#define QS_PAUSE			0x0010		// Queue paused (maybe because of halt event).  This
													// Can only be cleared with a WT_PURGE or jog
                                       // command from the host.

#define QS_PURGING_BIT	5
#define QS_PURGING		0x0020		// Queue purge request outstanding (this is
													// unlikely to be seen, since transient condition).

#define QS_HALT_BIT		6
#define QS_HALT			0x0040		// Halting condition active.  This can only be cleared
													// by host issuing WT_MONITOR with matching
                                       // challenge.  See WT_MONITOR description.

#define QS_GRR_OK_BIT	7
#define QS_GRR_OK			0x0080		// GRR reached target value after WT_RATE change
													// This will only be set for one message, then
                                       // is automatically reset.

#define QS_AXIS_HOMED	0x3F00		// On power-up, these bits are zeros.  When a
													// WT_PURGE with axis zeroing bit(s) is received,
                                       // the zerod axes have their HOMED bit set in
                                       // this field.  Once set, these bits remain set
                                       // until the G100 is rebooted.  This is for the
                                       // convenience of the user, who does not have to
                                       // recalibrate the machine each time the host PC
                                       // program is restarted.
	lword		halt_bits;		// Input bit mask of inputs which are being monitored
   								// for halt conditions.  The host may compare this to
                           // the matching WTMonitor.haltMask to determine which
                           // inputs have triggered a halt.  When a halt occurs, the
                           // bits which caused the halt are automatically set in
                           // this field.  The host is responsible for re-instating any
                           // halt monitoring bits by sending another WTMonitor.
                           // Note that this starts out as the _complement_ of the
                           // bit pattern in WTMonitor.haltMask, and bits get
                           // _set_ when they get hit.  Bits are never reset until
                           // a new WTMonitor is sent, even if the axis bounces
                           // right back off a limit switch etc.
} WTMsQstat;		// Size 20


/******************************************************************************
 WT_MS_ABS   Absolute position readback (hardware state)
	g200x -> host
 ******************************************************************************/

typedef struct {
	// Note that these values are _after_ the mavg queue i.e. are the latest
   // values written to the hardware.
	slong		p[6];				// Absolute position (internal steps) of each axis
	short		v[6];				// Current velocity (internal steps per ISR)
} WTMsAbs;		// Size 36


/******************************************************************************
 WT_MS_POS   Absolute position readback (software state - full precision)
	g200x -> host
   This is sent when any asynchronous condition occurs.  Async conditions
   are caused by WT_PURGE messages from the host, or internal events which
   cause a purge such as a halting event.
   Also may be elicited by the host sending a WT_GETPOS message.
 ******************************************************************************/

typedef struct {
	// Note that these values are _before_ the mavg queue.
	WTSDDA	pos[6];			// Current position (internal steps, 64-bit)
} WTMsPos;		// Size 48


/******************************************************************************
 WT_MS_OUT   Digital and analog output readback
	g200x -> host

   This is useful when outputs are set up to operate autonomously
 ******************************************************************************/

typedef struct {
	lword		o;					// Digital outputs
   word		aout[4];			// Analog outputs
} WTMsOut;		// Size 12


/******************************************************************************
 WT_MS_IN   Digital and analog input readback
	g200x -> host
 ******************************************************************************/

typedef struct {
	lword		i;					// Digital input reading
	word		ain[4];			// Analog input readings (0xFFFF is full-scale)
} WTMsIn;		// Size 12


/******************************************************************************
 WT_MS_CTR   Encoder/counter readback
	g200x -> host
 ******************************************************************************/

typedef struct {
	WTSFeedback	f[6];			// Encoder/counter feedback values
   short       cex[6];		// 16 MSbs of counters, extended to 32 bits.
   									// The full counter value is thus
                              // cex[i]<<16 | f[i].ctr
} WTMsCtr;		// Size 36


/******************************************************************************
 WT_MS_FULL   Full machine status (except Pos)
	g200x -> host (unsolicited, every 250ms when session established).
    Implementation note: On Rabbit, make sure out,in,ctr maps to
    tail end of _isrd data struct in g200x.lib.  Also, qcap and qstate are
    mapped directly.  abs is assembled from non-contiguous areas.
 ******************************************************************************/

typedef struct {
	WTMsQcap		qcap;
	WTMsQstat	qstate;
   WTMsAbs		abs;
   WTMsOut		out;
   WTMsIn		in;
   WTMsCtr		ctr;
} WTMsFull;		// Size 124



/******************************************************************************
 WT_MS_ASYNC   Machine status after asynchronous event such as purge.
	g200x -> host
     Also, is response to WT_GETPOS from host.
 ******************************************************************************/

typedef struct {
	WTMsQcap		qcap;
	WTMsQstat	qstate;
   WTMsPos		pos;
} WTMsAsync;



/******************************************************************************
 WT_MS_OUTIN   I/O status.
	g200x -> host
     Response to WT_DIGOUT and WT_ANAOUT from host.
     Also unsolicited when monitored inputs change.
 ******************************************************************************/

typedef struct {
	WTMsOut		out;
	WTMsIn		in;
} WTMsOutIn;


/******************************************************************************
 WT_TESTMODE   Set various test modes.

	host -> g100
     .
 ******************************************************************************/

typedef struct {
	word		drop_in;		// Drop one in this many (+1) incoming messages.
   							// 0 means do not drop.  WTTestMode messages are
                        // never dropped on purpose.
   word		drop_out;	// Drop one in this many (+1)outgoing messages.
   	// Hint: best if the drop numbers are different if not both zero.
} WTTestMode;



/******************************************************************************
 WT_DIRECT   Change over to direct protocol class.  This message is sent
   while in command-based protocol, however that mode is no longer
   available after issuing this message.  The host and G100 communicate using
   DT* messages.

	host -> g100
     .
 ******************************************************************************/

typedef struct {
	word			DIXtype;		// Type field to use in ethernet type field
	word			resv;
   float			min_lat;		// Minimum latency to allow between receipt of
   								// frames and sending data to the hardware.
                           // Puts lower bound on the adaptive latency
	float			stderr_mult;
   								// Multiple of the standard error in frame arrival
                           // times with respect to the average rate.  This
                           // affects the adaptive latency algorithm.  A high
                           // value (like 10) is conservative.  A low
                           // value (like 1) reduces adaptive latency on
                           // well-controlled ethernet segments.
} WTDirect;



/******************************************************************************
 These message formats are used in direct protocol class.
 In order to get into this mode, the host issues a WT_DIRECT.
 After this, UDP, IP and ARP are no longer available.
 The host must send and receive raw ethernet frames (type field of the
 DIX ethernet header is set in the WT_DIRECT message).
	host -> g100 and vice versa as raw ethernet frame contents

   These must be sent at a long-term rate of 1000Hz.  The G100 can adjust
   its local clock to match the incoming message rate, under control of a
   digital PLL.  In order to lock the PLL, at least 1000 messages must be
   received (1 second).  Thereafter, the G100 attempts to control the
   queue latency to conform to the parameters in the WT_DIRECT message.

   NOTE: two DTSet structs may be combined, for added redundancy.  This is
   done by sending an array of two DTSet's.  The second element repeats
   the information sent in the previous DTSet.  The first element is new
   data.  This is only useful if the latency is allowed to extend to
   2ms or more, otherwise the repeated data may be too late to fill in for
   a lost frame.   If this is done, then the DTS_REDUNDANT flag must be set
   in the first array element -- this is required since raw ethernet frames
   do not always allow the length of the frame data to be determined (the
   minimum frame data is 60 bytes, and the host does not necessarily pad
   this with zeros).
 ******************************************************************************/

// Host -> G100
typedef struct {
	word		seq;			// Host-defined sequence number (echoed by DTState).
   							// This should increment by +1 for each message.
   word		stamp;		// Time stamp when host sent (1/32768sec units)
   word		flags;
#define DTS_REDUNDANT	0x0001	// Another (previous, redundant) DTSet follows
											// this one in the frame.
   word		resv;
	slong		pos[6];		// Target axis position.  The G100 resets the position
   							// to all zeros on receipt of the WT_DIRECT message.
                        // The first 1000 or so messages should not attempt
                        // to move the position.  Note that position is sent
                        // (rather than velocity) so that if a message is missed
                        // then the G100 can interpolate and catch up on the
                        // next received message.  Position increments must
                        // be within -32768..32767 inclusive.  Position is
                        // reckoned in internal step units.
   lword		out;			// Digital outputs
   word		aout[4];		// Analog outputs

} DTSet;

// G100 -> Host
typedef struct {
	word		last_seq;	// Last received sequence number of a WTSet message.
   word		stamp_rec;	// Local (G100) timestamp of when that message
   							// received (1/32768 sec units)
   word		stamp_sent;	// Local (G100) timestamp of when this message sent
   word		latency;		// Current latency (1/32768 sec units)
   word		gstderr;		// Weighted average error in message arrival times
   							// with respect to the local 1000Hz PLL clock.  The
                        // weighting is halved for each second in the past.
                        // 1/32768 sec units.
   word		flags;
#define DTS_MISSED	0x0001	// At least one DTSet missed since last DTState
										// If this get set, then network delays are
                              // variable enough to trip up the adaptive latency
                              // algorithm.  Try increasing the stderr_mult
                              // setting in WT_DIRECT, or work on improving the
                              // host or network variability.
#define DTS_DROPPED	0x0002	// At least one DTState message could not be
										// transmitted because the ethernet transmitter
                              // was still busy.  This should not happen
                              // unless there are network problems (like
                              // excessive collisions).
	lword		i;				// Digital input reading
	word		ain[4];		// Analog input readings (0xFFFF is full-scale)
	WTSFeedback	fb[6];	// Axis feedback
} DTState;



#endif	// PROTOCOL_HH
/*** EndHeader */
