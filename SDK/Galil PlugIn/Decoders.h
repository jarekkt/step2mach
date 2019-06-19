#include "G200x.h"


extern 	void FillFromFullStatus( WTMsFull full);   //handle full status message
extern 	void CheckCurrentState( WTMsQstat state );   // State Checker, homes, limits, probing, ...etc..
extern 	void CheckQueueCap( WTMsQcap cap , bool ASync = false );  //check the queue capacity
extern 	void CheckABSPosition( WTMsAbs abs   ); // positions
extern 	void CheckRELPosition( WTMsPos pos);
extern 	void CheckEncoders( WTMsCtr counts  ); //encoder positions
extern 	void CheckInputs( WTMsIn In );  //inputs 
extern 	void CheckOutputs( WTMsOut out   ); //outputs
extern  int ShuffleInWord(int data);
extern  int ShuffleOutWord(int data);
extern  void SetBit( unsigned int &data, bool OnOff, short nBit);
extern  slong   RateToPos( int axis, slong pos);
extern  double  ActualPos( int x, slong pos );
extern  CString IpToString(DWORD ip);
extern  void    SyncStates();
extern  void    CompleteSequences();