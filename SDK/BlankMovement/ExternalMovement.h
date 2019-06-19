

//The following routines are used to initiate and control movement overall. 
// There are basically two modes of movement, Jogging, and Gcode planned movement.


//JogOff is obvious, it stops any joggin on an axis. 
//JogOn, will jog an axis in the commanded direction, and at a speed commanded, or , if zero is 
// the commanded spped, it will jog at the rate commanded by the JogPer variabel which is the 
// % of speed 0-100% of rapid for that axis..

typedef __int64 uint64;

 void GetInputs();
 void SetOutputs();
 void SendHoldingMovement();
 void HandleSequences();
 void myDwell(double time);
 void MyJogOn( short axis, short direction, double SpeedNorm);
 void  MyJogOff(short axis);

