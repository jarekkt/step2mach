

//The following routines are used to initiate and control movement overall. 
// There are basically two modes of movement, Jogging, and Gcode planned movement.


//JogOff is obvious, it stops any joggin on an axis. 
//JogOn, will jog an axis in the commanded direction, and at a speed commanded, or , if zero is 
// the commanded spped, it will jog at the rate commanded by the JogPer variabel which is the 
// % of speed 0-100% of rapid for that axis..

typedef __int64 uint64;

void MyJogOn( short axis, short dir, double speed);           //Routines to start and stop Jogging..
void MyJogOff( short axis);                                   //Mach3 commands Jogging to stop on an axis
double JogClipVel(short axis, double JogFeed);                //Clip requested Velcoity of jog to match the curretn Mavg 
void JogSetMavg(int axis, double JogFeed);                    //Set a new Mavg if no already in effect
void InitJogMessage();                                        //Setup a standard Jog messge for use by these rotuines.
void Rejog();                                                 //every 250ms a Jog needs to be refreshed wlese it will stop.
void  DoGcodeMove();                                          //Called every update period to do Gcode movement if movement is holding..
void  SendDwell(double time);                                 //Used to send a Dwell to G100
void  myDwell( double time);                                  //Mach3 sends this to tell us to start a dwell.
void  myPurge( short flags );                                 //used to stop movement or zero DROs in a G100