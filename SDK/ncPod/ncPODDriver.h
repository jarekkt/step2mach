// ncPODDriver.h
// Version 0.1.0.0 of the ncPOD Driver.
// Wed 2006-10-04
// Copyright OEMTech

// Version 0.1.0.0 has minimal functionality defined.
// Support for the SD card will be provided in a later version.



#define STATMODERUN 0
#define STATMODEPROBE 1
#define STATMODEDEBUG 2



enum usbCommandEnum 

{

USBPREPAREBURN = 1, // firmware
USBBURN = 2, // firmware
USBRUNMODE = 4,
USBBOOTMODE = 6,
USBSTANDARD = 10,
USBDRIPFEED = 11,
USBFILESTORE = 12, // sd card
USBENDFILESTORE = 13, // sd card
USBRUNFILE = 14, // sd card
USBREADNEXTBLOCK = 15,
USBSETSINGLESTEPMODE = 16,
USBSINGLESTEPFILE = 17,
USBAUTOSTEP = 18,
USBGETSDSTATUS = 19,
USBLEDON = 20,
USBLEDOFF = 21,
USBSDCARDLATCH = 22, // sd card
USBRESETESTOPSWITCH = 23,
USBSIMMODE = 25,
USBSETSTATUSMODE = 26,
USBSETOVERRIDETABLE = 60,
USBSETOVERRIDE = 61,
USBSETINTERPSCALE = 62,
USBSETINDEPENDENTACCEL = 63,
USBSETINTERPSLEWRATE = 75,
USBSETINDEPENDENTSLEWRATE = 76,
USBLINEARPOSITIONMOVEXYZABC = 101,
USBCOORDINATEDVELOCITYMOVEXYZABC = 103,
USBVELOCITYMOVE = 105,
USBRELATIVELINEARPOSITIONMOVEXYZABC = 106,
USBSETUPSCANXY = 125,
USBSETUPSCANXA = 126,
USBSETUPSCANZA = 127,
USBBEGINSCAN = 129,
USBREADSDBLOCK = 130, // sd card
USBUPLOADSDCARD = 131,
USBPREPARESAVEBLOCK = 135,
USBSAVEBLOCK = 136,
USBCONTINUE = 151,
USBPAUSE = 152,
USBOVERRIDE = 154,
USBSETUP = 155,
USBDELAY = 159, // macro
USBSETCOORDSXYZABC = 160,
USBSETPROBE = 162,
USBINTERPHOME = 165,
USBINDEPENDENTHOME = 166,
HOMEUSINGLIMITS = 167,
HOMEPOLARITY = 168,
//If the Loc parameter is 1 then switches are Normally Closed
USBPROBERELATIVEXYZABC = 172,
USBPROBEABSOLUTEXYZABC = 174,
USBOUTPUT = 175,
USBOUTPUT_PWM = 176,
USBCHECKINPUT = 180,
USBWAITFORINPUT = 181,
USBSETUPACUITYSCANNER = 195,
USBESTOP = 200,
USBFINISHMOVE = 201,
USBRESET = 202,
USBEXECUTEMACRO = 225,
USBRETURNTOMACROPOSITION = 226,
USBSAVEPOSITION = 227,
USBRETURNTOPOSITION = 228,
SDWAITFORBUFFERFILL = 2,
SDFLUSHBUFFER = 3

};
 

//Some commands are a work in progress.  I do not know why some are Green and Bold (I just Copy and Pasted).
enum sdCommandEnum
{
SDCOMMENT = 50,
SDSETOVERRIDETABLE = 60,
SDSETINTERPSCALE = 62,
SDSETINDEPENDENTACCEL = 63,
SDSETINTERPSLEWRATE = 75,
SDSETINDEPENDENTSLEWRATE = 76,
SDLINEARPOSITIONMOVEXYZ = 100,
SDLINEARPOSITIONMOVEABC = 101,
SDCOORDINATEDVELOCITYMOVEXYZ = 102,
SDCOORDINATEDVELOCITYMOVEABC = 103,
SDVELOCITYMOVE = 105,
SDPAUSE = 152,
SDINDEPENDENTHOME = 157,
SDDELAY = 159,
SDSETCOORDSXYZ = 160,
SDSETCOORDSABC = 161,
USBINTERPPROBERELATIVE = 162, 
USBINTERPPROBEABSOLUTE = 163, 
SDINTERPHOMEXYZ = 165,
SDINTERPHOMEABC = 166,
SDOUTPUT = 175,
SDOUTPUT_PWM = 176,
SDWAITFORINPUT = 181,
SDWAIT = 182,
SDFINISHMOVE = 201,
SDRETURNTOMACROPOSITION = 226,
SDSAVEPOSITION = 227,
SDRETURNTOPOSITION = 228,
SDJUMPTOMACRO = 229,
SDRETURNFROMMACRO = 230,
SDFILEEND = 255
};

/*

USBWAITFORINPUT:

Put a 'code' in the X axis when using this command.  When the SD file is run and USBWAITFORINPUT is reached, 
the STAT variable in the Status will return the 512 bit mask and the Range variable in the Status will return the 'code'. 
Mach will monitor the Status as the file is run.  When it reads the 512 bit mask from the STAT in the Status, 
then Mach knows to execute the Macro tied to the 'code' value.  After Mach executes the Macro, 
it sends a USBCONTINUE command and the machining continues.

You will Store 1 mS moves to the SD card. 
If you really want to do this in 'Pseudo Real Time' 
(not store the commnds but rather Drip Feed them in) then let me know and I will resurrect
the USBDRIPFEED=11 command (currently broke).  If a 1mS move is zero then there will simply be a 1mS delay. 
Your 1 mS stream is exactly what is required - All Accel/Decel stuff is already 'in there'.  
The Positional 1mS stream that you calculate will be based on 32768 / 75 Fractional Step Ratio  so...
1.  X=0
2.  X=1
3.  X=1
4.  X=2
...are absolute full step positions at 1mS intervals.  You will calculate relative moves...
1.  X=0 
2.  1-0 = 1
3.  1-1 = 0
4.  2-1 = 1
 ... convert them to Relative Fractional steps (*32768 / 75)...
1.  X = 0
2.  X = 1 * (32768 / 75) = 437
3.  X = 0
4.  X = 1 * (32768 / 75) = 437
... and send these values.  Of course it would be better to calculate the Fractional steps from Floating Point 1 mS positions (rather than the Full step values above)  so the 'stutter' is eliminated.
*/


// USB end points.
// Commands sent to the ncPOD.
#define VELPOINT  1
#define COMMANDENDPOINT 3
// Status received from the ncPOD.
#define STATUSENDPOINT (2+128)



#define STATPOWEREDON 1            
#define STATSDCARDMISSING 2
#define STATSDCARDWASREMOVED 4
#define STATLIMITHIT 8      
#define STATPROBEHIT 16
#define STATPAUSED 32
#define STATWAITING 64
#define STATINTERPMOVEINPROGRESS 128
#define STATVELOCITYMOVEINPROGRESS 256
#define STATSCANINPROGRESS 512



// ncPODStatus.ack values. These are not necessary for driver use.
#define ACKOK 1
#define ACKFAILED 2
#define ACKUNKNOWNCOMMAND 5
#define ACKCOMMANDISALREADYINPROGRESS 13
#define ACKBUFFERNOTREADY 20
#define ACKBURNWAITING 25
#define ACKBURNING 26
#define ACKBURNT 27
#define ACKBURNERROR 28
#define ACKUNKNOWN 45
#define ACKCOMMENT 50
#define ACKSETOVERRIDETABLE 60
#define ACKSETINTERPSCALE 62
#define ACKSETINDEPENDENTACCEL 63
#define ACKSETINTERPSLEWRATE 75
#define ACKSETINDEPENDENTSLEWRATE 76
#define ACKLINEARPOSITIONMOVEXYZ 100
#define ACKLINEARPOSITIONMOVEABC 101
#define ACKCOORDINATEDVELOCITYMOVEXYZ 102
#define ACKCOORDINATEDVELOCITYMOVEXYZABC 103
#define ACKVELOCITYMOVE 105
#define ACKPAUSE 152
#define ACKINDEPENDENTHOME 157
#define ACKDELAY 159
#define ACKSETCOORDSXYZ 160
#define ACKSETCOORDSABC 161
#define ACKSETPROBE 162
#define ACKINTERPHOMEXYZ 165
#define ACKINTERPHOMEABC 166
#define ACKOUTPUT 175
#define ACKOUTPUT_PWM 176
#define ACKWAITFORINPUT 181
#define ACKFINISHMOVE 201
#define ACKWAITING 253
#define ACKMOVEINPROGRESS 254
#define ACKFILEEND 255

// ncPODCommand.commandEnum values
// Put the ncPOD into run mode - the normal state of firmware.
//  this needs to be sent after opening the usb device.
#define USBRUNMODE 4
// Put the ncPOD into boot mode - this permits updating the firmware.
//  This is not available in version 0.1.0.0.
#define USBBOOTMODE 6
// Put the ncPOD into a simulator mode (after already being in run mode.)
//  This disables the motor drivers while the ncPOD executes motion commands.
//  axisX: 0 normal mode (assert the driver signals)
//  axisX: 1 simulator mode (do not assert the driver signals)
#define USBSIMMODE 25
// Set the independent acceleration parameter. The acceleration parameter
//  will apply to subsequent move commands.
//  axisX: the integer number of steps per second per second
#define USBSETINDEPENDENTACCEL 63
// Move to absolute position
//  axisX: the absolute position in steps to which to move the X axis
//   other axes are similar
//  velocity: the speed at which to make the move, in steps per second
#define USBLINEARPOSITIONMOVEXYZABC 101
// Move to relative position
//  axisX: the relative position in steps to which to move the X axis
//   other axes are similar
//  velocity: the speed at which to make the move, in steps per second
#define USBRELATIVELINEARPOSITIONMOVEXYZABC 106
// Continue execution after being paused.
#define USBCONTINUE 151
// Pause execution.
#define USBPAUSE 152
// Set feed rate override. The feed rate can be varied between 25% and 100%.
//  velocity: an integer between 0 and 249 representing the feed rate
//             0: 25%
//           249: 100%
#define USBOVERRIDE 154
// Set the ncPOD's axis positions measured in steps.
//   axisX: number of full steps for x axis
//     the other axes are similar
//   loc: a bit mask used to select which axis coordinates will actually be set
//        0x20: x axis
//        0x10: y axis
//        0x08: z axis
//        0x04: a axis
//        0x02: b axis
//        0x01: c axis
#define USBSETCOORDSXYZABC 160
// Move until the home switches are activated
#define USBINTERPHOME 165
// Set the ncPOD's output signals. Each of the least significant 5 bits represents
//   an output signal. The output signal is set to the value of the corresponding bit in axisY
//   if the corresponding bit is 1 in axisX. If the corresponding bit is 0 in axisX, the
//   value of the output signal is not changed.
//   axisX: mask
//   axisY: value of output signals
#define USBOUTPUT 175
// Perform an emergency stop.
#define USBESTOP 200
// Stop moving. This can be issued after a USBLINEARPOSITIONMOVEXYZABC
//  or USBRELATIVELINEARPOSITIONMOVEXYZABC command. The intent is that a continuous jog
//  would issue a command to move a fairly long distance. The machine will move until
//  USBFINISHMOVE is issued.
#define USBFINISHMOVE 201

// 64 byte usb packets are sent to and from the pod through 2 different endpoints.  There is
// a 3rd endpoint for transferring 512 byte packets to the SD card that we will get to later.
// The micro-controller on the pod uses reversed Most Significant Byte so all 2 and 4 byte
// data types need to be 'reversed'.  We will probably put this in the low level usb driver later
// but that is why you see the read4() etc commands to reverse the bytes.

#define USBDRIPFEED  11

#define USBSETUP 155

 
 
struct ncRunPODStatus
{
	int fullStepsX;
	int fullStepsY;
	int fullStepsZ;
	int fullStepsA;
	int fullStepsB;
	int fullStepsC;
	unsigned int synch; 
	unsigned char outio; 
	unsigned char inio;
	unsigned char ack;     // 31 
	unsigned short stat;
	unsigned short range;
	unsigned short Q;       // 37
	unsigned long USBid;  
	unsigned short firmwareVersion;
	unsigned short TimeStamp;   // 45
	byte NumBuffer;
	byte NumQBuffer;  
	byte RunMode; 
	byte statusMode;  // 49  
	byte comment[15];
};
struct ncPODStatus
{
	int fullStepsX;
	int fullStepsY;
	int fullStepsZ;
	int fullStepsA;
	int fullStepsB;
	int fullStepsC;
	unsigned int synch; 
	unsigned char outio; 
	unsigned char inio;
	unsigned char ack;     // 31 
	unsigned short stat;
	unsigned short range;
	unsigned short Q;       // 37
	unsigned long USBid;  
	unsigned short firmwareVersion;
	unsigned short TimeStamp;   // 45
	byte NumBuffer;
	byte NumQBuffer;  
	byte RunMode; 
	byte statusMode;  // 49  
	byte Homestatus;
	long ProbexAxis;                                       
	long ProbeyAxis;                                       
	long ProbezAxis;                                       
	long ProbeaAxis;                                      
	long ProbebAxis; 
	byte comment[14];
};

/*
struct ncPODStatus
{
	// Current position of each axis, measured in full steps.
	int fullStepsX;
	int fullStepsY;
	int fullStepsZ;
	int fullStepsA;
	int fullStepsB;
	int fullStepsC;
	// Synchronization number - this comes from the last SD command executed.
	unsigned int synch;
	// Current state of output signals.
	unsigned char outio;
	// Current state of input signals.
	unsigned char inio;
	// See #define ACK*
	unsigned char ack;
	// See #define STAT*
    unsigned short stat;
	// Distance of laser probe when in scan mode.
	unsigned short range;
	// Most recent sequence number received.
	unsigned short Q;
	// Number of fractional steps per axis. Always positive. Divide by 32768 to get fraction.
	unsigned long  USBid;
	// Firmware version as a decimal integer. Currently 2003.
	unsigned short firmwareVersion;
	unsigned short TimeStamp;
	byte NumBuffer;
    byte NumQBuffer;  
    byte RunMode;     
	long ProbexAxis;                                       
    long ProbeyAxis;                                       
    long ProbezAxis;                                       
    long ProbeaAxis;                                      
    long ProbebAxis; 
    byte comment[1];
	char dummy[20];
};
*/

struct ncPODCommand
{
	// See #define USB*
	unsigned char commandEnum;
	// synch is not used at this time.
	unsigned int synch;
	// Parameters for the command, usually per axis. Sometimes axesX and axesY are general parameters.
	int axisX;
	int axisY;
	int axisZ;
	int axisA;
	int axisB;
	int axisC;
	// Velocity in steps per second, when applicable.
	int velocity;
	// Additional parameter.
	unsigned short loc;
	// Sequence number is supplied by the host in the command structure, and is echoed back in the status structure.
	unsigned int sequenceNumber;
};

 
