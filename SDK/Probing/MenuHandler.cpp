// MenuHandler.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MachDevice.h"
#include "MenuHandler.h"
#include ".\menuhandler.h"
#include "Mach4View.h"
#include "TrajectoryControl.h"
#include "Mach4View.h"
#include "Engine.h"
#include "rs274ngc.h"
#include "math.h"
#include "probeconfig.h"
#include "OkayToMove.h"
#include "XMLProfile.h"
#include "enter.h"

extern CXMLProfile *DevProf;

 
extern TrajectoryControl *MainPlanner; //used for most planner funcitons and program control 
extern CMach4View *MachView;   //used for most framework and configuration calls. 
extern TrajBuffer *Engine;     //Ring0 memory for printer port control and other device syncronisation
extern setup *_setup;          //Trajectory planners setup block. Always in effect

extern VoidLPCSTR         Code;         // void    Code( "G0X10Y10" );
extern OneShort           DoButton;     // void DoButton( code )
extern DoubleShort        GetDRO;       // Double GetDRO( code )
extern VoidShortDouble  SetDRO;         // void   SetDRO( short code, double value);
extern BoolShort          GetLED;       // bool   GetLED( short code );
extern VoidShortBool      SetLED;       //SetLED Fucntion
 
 

// MenuHandler

IMPLEMENT_DYNAMIC(MenuHandler, CWnd)
MenuHandler::MenuHandler()
{
	RangeStart = -1;
	SEQUENCE = SEQNONE; //no sequence in effect..
	m_length = 10;
	m_width = 10;
	m_XGrid = 1;
	m_YGrid = 1;
	m_probedist = -1;
	m_clearance = .1;
	m_feedrate = 60;
	m_ProbeRad = 0.0;
	m_probestuck = 0;
}

MenuHandler::~MenuHandler()
{
}


BEGIN_MESSAGE_MAP(MenuHandler, CWnd)

  
 
END_MESSAGE_MAP()


int FindMenuItem(CMenu* Menu, LPCTSTR MenuString)
{
	ASSERT(Menu);
	ASSERT(::IsMenu(Menu->GetSafeHmenu()));

	int count = Menu->GetMenuItemCount();
	for (int i = 0; i < count; i++)
	{
		CString str;
		if (Menu->GetMenuString(i, str, MF_BYPOSITION) &&
			(strcmp(str, MenuString) == 0))
			return i;
	}

	return -1;
}



// MenuHandler message handlers
// Initialise and setup manu items for MAch3's menu control

void MenuHandler::InitMenus(void)
{

	if( RangeStart == -1 ) 
	{
		AfxMessageBox( " Error in Adding Menus " );
		return;
	}

	CFrameWnd *MachFrame = MachView->MachFrame;
	CMenu *menu = MachFrame->GetMenu();
	HMENU hSubmenu = CreatePopupMenu();
    //here we can add menu items to MAch3's menu..
	InsertMenu ( hSubmenu, 0, MF_BYPOSITION, RangeStart ,     _T("&Probe object with grid") );
	InsertMenu ( hSubmenu, 1, MF_BYPOSITION, RangeStart + 1 , _T("&Probe inside center of hole") );
	InsertMenu ( hSubmenu, 4, MF_SEPARATOR,  RangeStart + 2 ,NULL );

	//for getting points..
	InsertMenu ( hSubmenu, 5, MF_BYPOSITION,  RangeStart + 3 ,_T("&Get Point1")  );
	InsertMenu ( hSubmenu, 6, MF_BYPOSITION,  RangeStart + 4 ,_T("&Set Point1")  );
	InsertMenu ( hSubmenu, 7, MF_BYPOSITION,  RangeStart + 5 ,_T("&Get Point2")  );
	InsertMenu ( hSubmenu, 8, MF_BYPOSITION,  RangeStart + 6 ,_T("&Set Point2")  );
	InsertMenu ( hSubmenu, 9, MF_BYPOSITION,  RangeStart + 7 ,_T("&Get Point3")  );
	InsertMenu ( hSubmenu, 10, MF_BYPOSITION,  RangeStart + 8 ,_T("&Set Point3")  );
	InsertMenu ( hSubmenu, 11, MF_BYPOSITION,  RangeStart + 9 ,_T("&Center from 3-points") );
	InsertMenu ( hSubmenu, 13, MF_SEPARATOR,  RangeStart + 13 ,NULL );


	//we can add as many as we want up to the amount we requested in the implementation file..
	//here we add the menu to the Mach3 menu..
	InsertMenu( menu->m_hMenu , -1 , MF_POPUP, (UINT_PTR) hSubmenu, _T("&3d Probing") );  //this adds the probing menu item. 

	//disable points 2 and 3
	int pos = FindMenuItem(menu, "&3d Probing");
	CMenu* submenu = menu->GetSubMenu(pos);
    POK[0] = POK[1] = POK[2] = false;
    if( pos != -1)
	{
	  submenu->EnableMenuItem(9, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
	//  submenu->EnableMenuItem(9, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
	}
	m_length = atof( DevProf->GetProfileString("Probe3d", "Length", "10.0" ));
	m_width = atof( DevProf->GetProfileString("Probe3d", "Width", "10.0" ));
	m_XGrid = atof( DevProf->GetProfileString("Probe3d", "XGrid", "1.0" ));
	m_YGrid = atof( DevProf->GetProfileString("Probe3d", "YGrid", "1.0" ));
	m_ProbeRad = atof( DevProf->GetProfileString("Probe3d", "ProbeDia", "0.0" ));
	m_probedist = atof( DevProf->GetProfileString("Probe3d", "ProbeDepth", "0.0" ));
	m_clearance = atof( DevProf->GetProfileString("Probe3d", "Clearance", ".5" ));
	m_feedrate = atof( DevProf->GetProfileString("Probe3d", "FeedRate", "10.0" ));
	m_probestuck = atof( DevProf->GetProfileString("Probe3d", "ProbeStuck", "0.0" ));

}

void MenuHandler::CheckMenu(int PointSearch, bool done)
{

	CFrameWnd *MachFrame = MachView->MachFrame;
	CMenu *menu = MachFrame->GetMenu();
	int pos = FindMenuItem(menu, "&3d Probing");
	CMenu* submenu = menu->GetSubMenu(pos);
	if( pos != -1)
	{
		if( done )
		{
		  submenu->CheckMenuItem((PointSearch*2) + 4, MF_BYPOSITION  | MF_CHECKED);
		  POK[PointSearch] = true;
		}
		else
		{
          submenu->CheckMenuItem((PointSearch*2) + 4, MF_BYPOSITION  | MF_UNCHECKED);
		  POK[PointSearch] = false;
		}
		CString mess;
		if( done)
		{ 
			mess.Format("Point #%i Recorded",PointSearch+1);
		    SetMachError(mess);
		}
		if( POK[0] && POK[1] && POK[2])
		{
			submenu->EnableMenuItem(9, MF_BYPOSITION | MF_ENABLED);
		}
		else
		{
 			submenu->EnableMenuItem(9, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
	    }
	}
	else
		SetMachError("Internal Error");
}

//Activate Fucntions based on menu item selection.

void MenuHandler::DoMenuItem(int ID)  
{

 if( SEQUENCE != SEQNONE )
 {
   AfxMessageBox( "Previous SEQ not yet complete. ");
   return;
 }
 int sw = ID - RangeStart;

	switch( sw )
	{
	case( 0 ):    DoButton( 169 );
		          ThreeDprobe();
		          break;
    case( 1 ):    DoButton(169);
		          OnCenter();
		          break;
		 
		          break;
	case( 3 ):    PointSearch = 0;
		          DoPoint();
		break;
	case( 4 ):    PointSearch = 0;
		          CalcPoint(PointSearch);
		          CheckMenu(PointSearch,true);
		          break;

	case( 5 ):    PointSearch = 1;
		          DoPoint();
		break;
	case( 6 ):    PointSearch = 1;
		          CalcPoint(PointSearch);
		          CheckMenu(PointSearch,true);
		           break;
	case( 7 ):    PointSearch = 2;
		          DoPoint();
		          break;
	case( 8 ):    PointSearch = 2;
		           CalcPoint(PointSearch);
		           CheckMenu(PointSearch,true);
		           break;
	case( 9 ):    DoCenter3();
		break;
	 

	}
}

void MenuHandler::DoCenter3()
{
   if( !POK[0] || !POK[1] || !POK[3])
   {
	   SetMachError("Fill Three Jog Points First!");
	   return;
   }
   //three points are stored..
   //caclulate the center from them..
   ProbePoint center; 
   double radius;
   double bx = points[0].x;
   double by = points[0].y;
   double cx = points[1].x;
   double cy = points[1].y;
   double dx = points[2].x;
   double dy = points[2].y;

   double temp = cx*cx+cy*cy;
   double bc = (bx*bx + by*by - temp)/2.0;
   double cd = (temp - dx*dx - dy*dy)/2.0;
   double det = (bx-cx)*(cy-dy)-(cx-dx)*(by-cy);
   if( det == 0 )
   {
	   SetMachError("Radius is Zero, points not on circle" );
	   CheckMenu( 0 , false );
	   CheckMenu( 1 , false );
	   CheckMenu( 2 , false );
	   return;
   }
   det = 1/det;
   center.x = (bc*(cy-dy)-cd*(by-cy))*det;
   center.y = ((bx-cx)*cd-(cx-dx)*bc)*det;
   center.z = points[0].z;
   if( (cx-bx)*(cx-bx)+(cy-by)*(cy-by) != 0 ) 
   {
	   radius = sqrt((cx-bx)*(cx-bx)+(cy-by)*(cy-by));
   }
   else
   {
	   SetMachError("Radius is Zero, points not on circle" );
	   CheckMenu( 0 , false );
	   CheckMenu( 1 , false );
	   CheckMenu( 2 , false );
	   return;
   }
   Center *cen = new Center();
   cen->m_Rad = radius;
   cen->m_Xloc = center.x;
   cen->m_YLoc = center.y;
   cen->DoModal();
   if(cen->Move)
   {
	   CString move;
	   move.Format("G90G01X%.4fY%.4f",cen->m_Xloc, cen->m_YLoc);
	   Code(move);
   }
   delete cen;

}

void MenuHandler::DoRotate3()
{
	if( !POK[0] || !POK[1] || !POK[3])
	{
		SetMachError("Fill Three Jog Points First!");
		return;
	}
	//calculate the angle of the line..
	SetMachError("Function not yet implemented.");

}

void MenuHandler::DoPoint()
{
	if( !Engine->InSigs[DIGITIZE].Active || Engine->InSigs[DIGITIZE].Activated )
	{
		SetMachError(" Probe Activated or Disabled. Command Ignored");
	}
	 Engine->Axis[0].Memory[6] = 2;
	 CString mess;
	 mess.Format("Jog Probe Active->Slow Jog till probe finds Point #%i",PointSearch+1);
	 for( int c = 0; c<6; c++)
	 {
		Engine->Axis[c].DepthCount = -9999;
	 }
	 SetMachError(mess);
	 SEQUENCE = GETPOINT; 
	 
}

void MenuHandler::CalcPoint( int point )
{
	for( int c = 0; c<6; c++)
	{
		//probe not active, current position is the probe position..
     	double temp = Engine->Axis[c].DepthCount;
		if( temp != -9999 )
		{
		   temp /= MainPlanner->StepsPerAxis[ c ];
		   temp = temp - _setup->CurrentOrigins[c];
		   _setup->parameters[c+2000] = temp;
		}
		else
           _setup->parameters[c+2000] = MainPlanner->MachPositions[c] - _setup->CurrentOrigins[c];
		 
	}
    points[point].x = _setup->parameters[2000];
	points[point].y = _setup->parameters[2001];
    points[point].z = _setup->parameters[2002];
	Engine->Axis[0].Memory[6] = 0;
     
}
 

void MenuHandler::Sequencer(void)
{
	
 CString temp,Block; 
 double x,y,z;
 int g;
 static double var1,var2,var3,var4;
 static bool warned = false;

 if( MainPlanner->SoftWait != 0 ) return; //wait for Mach3 to process whatever is going on before continueing..

 if ( SEQUENCE != SEQNONE )
 {
	 Engine->DisplayLine = 0;
	 MainPlanner->Line = 0;
 }

	switch (SEQUENCE )
	{
	  case ( GETPOINT ) : if( !Engine->InSigs[DIGITIZE].Activated) return;
                        //probe is hit. Grab this point.
		                CalcPoint(PointSearch);
						SEQUENCE = SEQNONE;
						CheckMenu(PointSearch,true);
		                return; //Get Point1
	  
	  case ( SEQNONE ) :	
						return; //no sequence in operation..
      case( PROBESTART)://This stage will start the probe move
						if( !Engine->InSigs[DIGITIZE].Active || 
							 Engine->InSigs[DIGITIZE].Activated )
						{
							SEQUENCE = SEQNONE;
							MainPlanner->Sequence = false;
							AfxMessageBox( "Error in Probe Condition. No Probe, or Probe active! ");
							return;
						}
						
						//We're OK to go, lets init the spiral control, set first target and start the search pattern..
						target.x = m_length / 2; target.y = m_width / 2; target.z = 0;
						Engine->Jogging = false;
						XInc = YInc = 1; //these basically indicate direction of current movement.
						XDir = 1; YDir = 1;
						MainPlanner->OldState = STOP;
	                    Engine->State = STOP;
						MainPlanner->Sequence = true;
						Code( "M40" );
                        SEQUENCE = PROBEBEGIN;
					    LastMove = NONE; //no correction moves in operation
						break;
   	case( PROBEBEGIN):  if( !MainPlanner->MovementDone && Engine->State != STOP) return;
						MainPlanner->MovementDone = false;
						XMax = m_XGrid ; YMax = m_YGrid ; // this is how far to move in each axis before reversing direction for that axis..
						ProbeAxis = 0;
						MainPlanner->FeedRate = m_feedrate / 60;
                        CalcRatios( target.x, target.y );					
						Block.Format("G31X%.4fY%.4f ", target.x, target.y );
						MeasureMove = false;
						MainPlanner->SLSDist = min( m_XGrid, m_YGrid);
						Code( Block ); //we're now moving toward the first target point for the probe to be done..
                        SEQUENCE = PROBEMOVE;
					    LastMove = NONE; //no correction moves in operation


	case( PROBEMOVE)://This stage is just for the Prep move in the X and Y direction. 

						if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
		 				if( Engine->InSigs[DIGITIZE].Activated )
						{
						  SEQUENCE = PROBEREV;
						  Reversals = 0;     //this is a mistake, we need to reverse only in the direction of last movement. 
						  //we need to use a vector here..
						  x=  _setup->parameters[2000] + backx; //we get the trip point.
						  y=  _setup->parameters[2001] + backy; //we get the trip point.
						  for( g = 0; g< 6; g++) 
						   { 
							   Engine->Axis[g].Probing = false;
							   Engine->Axis[g].Jogging = false;
						   }
						  Block.Format("G0X%.4fY%.4f ", x,y  );
						  MeasureMove = false;
						  Code( Block ); //we're now moving up to a new Z
						  return;
						}//we're on  target for a probe, and probe is not active.. do a measurement..
						else
						{
						   Reversals = 0;
 						   Block.Format("G31Z%.4f ", m_probedist  );
						   SEQUENCE = PROBEMEASURE;
						   Code( Block ); //we're now moving toward the first target point for the probe to be done..
						}
						break;
     case( PROBEREV)://This stage is just for Moving Off off an XY move..

						if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
		 				if( Engine->InSigs[DIGITIZE].Activated )
						{
						  Reversals ++;
						  if( Reversals > 5 )
						  {
						    Reversals = 0;
                            SEQUENCE = RAISEZ;
							//mess = &MainPlanner->LastError;
							//*mess = "Switched to RaiseZ after pullback failure.";
						    return;
						  }
						  SEQUENCE = PROBEREV;
						  x=  MainPlanner->XPosition + backx; //move off trip point in opposite direction.
						  y=  MainPlanner->YPosition + backy; //we get the trip point.
						  Block.Format("G0X%.4fY%.4f ", x,y );
						  MeasureMove = false;
						 // MessageBox( Block );
						  Code( Block ); //we're now moving up to a reversal on the X and Y axis of clearance amount..
						  return;
						}//we're on  target for a probe, and probe is not active.. do a measurement..
						else
						{
						   Reversals = 0;
						   Block.Format("G31Z%.4f ", MainPlanner->ZPosition + m_XGrid ); //raise one grid distance
						   SEQUENCE = RAISEZ;
						   Code( Block ); //we're now moving toward the first target point for the probe to be done..
						}
						break;
     case( RAISEZ):  //this deals only with Z upward movements.. which are real measurements..
		                if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
						if( Engine->InSigs[DIGITIZE].Activated )
						{
						  //Reversals++;
						 if( MainPlanner->ZPosition < m_probestuck )
						  {
                           warned = false;
                           for( g = 0; g< 6; g++) 
						   { 
							   Engine->Axis[g].Probing = false;
							   Engine->Axis[g].Jogging = false;
						   }
						   Block.Format("G00Z%.4f ", MainPlanner->ZPosition + m_clearance );
						   Code( Block ); //we're now moving away from this x point  
						   SEQUENCE = RAISEZ;
						   return;
						  }
						  else
						  {
						   if( !warned ) 
							  {
								  SetMachError(" Probe Stuck, flick it to continue sequence. ");
								  warned = true;
							  }

							SEQUENCE = RAISEZ;
							MainPlanner->Sequence = false;
						    return;
						  }
                     	} 
						else
						{ //we're off the switch, so we can go back to targeting on X or Y..
						  Reversals = 0;
						  CalcRatios( target.x, target.y );
						  Block.Format("G31X%.4fY%.4f ", target.x, target.y );
						  MeasureMove = false;
						  Code( Block ); //we're now moving toward the first target point for the probe to be done..
                          SEQUENCE = PROBEMOVE;
						  return;
						 }
					     break;
	case( PROBEMEASURE):  //this deals only with Z movements.. which are real measurements..
		                  //this means the probe move is done..
		                if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
                        target = GetGridPoint();
						if( target.y >  m_width  ||  target.x > m_length ||
						     target.y < 0        ||  target.x  < 0) 
						  {
                             SEQUENCE = SEQNONE;
							 Code( "M41" );
							 MainPlanner->Sequence = false;
							 AfxMessageBox( "Sequence complete..!");
					    	 return;
						  }

						if( Engine->InSigs[DIGITIZE].Activated )
						{
						  //we hit, so start raising Z first..
							//first we need the trigger point.
						    z=  _setup->parameters[2002]; //we get the trip point.
							z += fabs(m_clearance); //lets raise the Z to just above the trip point..
							Reversals = 0;
						    Block.Format("G0Z%.4f ", z );
						    Code( Block ); //we're now moving away from this x point  
						    SEQUENCE = RAISEZ;
							return;
						}
						else
						{ //no hit, just move to next target
						 
                         CalcRatios( target.x, target.y );
						 Block.Format("G31X%.4f Y%.4f ", target.x, target.y );
						 MeasureMove = false;
						 Code( Block ); //we're now moving toward the first target point for the probe to be done..
                         SEQUENCE = PROBEMOVE;
						 return;
                     	}
						break;
	 case(HOLESTART)://This stage will start the probe move
                        if( Engine->State == STOP ) return;
						if( !Engine->InSigs[DIGITIZE].Active || 
							 Engine->InSigs[DIGITIZE].Activated )
						{
							SEQUENCE = SEQNONE;
							MainPlanner->Sequence = false;
							AfxMessageBox( "Error in Probe Condition. No Probe, or Probe active! ");
							return;
						}
						//We're OK to go, lets init the spiral control, set first target and start the search pattern..
						  var1 = MainPlanner->XPosition; //start point
						  x=  MainPlanner->XPosition + 100; //move off trip point in opposite direction.
						  Block.Format("G31X%.4f",x );
						  MeasureMove = false;
				 	      Code( Block ); //we're now moving X 100 forward..
						  SEQUENCE = HOLE2; //measure X minimum
						  break;
    case( HOLE2 ):// found edge of X ++
						if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
		 				if( !Engine->InSigs[DIGITIZE].Activated )
						{
						  AfxMessageBox("Could not find hole edge"); //no edge found..
						  SEQUENCE = SEQNONE;
						  return;
						}
						else
						{
						   var2 = _setup->parameters[2000];  
                           Block.Format("G1X%.4f", var1 );  
						   Code( Block );  
						   SEQUENCE = HOLE3;
						   return;
						}
						break;
    case( HOLE3 )://Pulled back to start
						if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
		 				if( Engine->InSigs[DIGITIZE].Activated )
						{
						  AfxMessageBox("Could not exit hole edge"); //no edge found..
						  SEQUENCE = SEQNONE;
						  return;
						}
						x=  MainPlanner->XPosition - 100; //move off trip point in opposite direction.
						Block.Format("G31X%.4f",x );
						MeasureMove = false;
				 	    Code( Block ); //we're now moving X 100 forward..
						SEQUENCE = HOLE4; //measure X minimum
						break;
   case( HOLE4 )://found other edge
						if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
		 				if( !Engine->InSigs[DIGITIZE].Activated )
						{
						  AfxMessageBox("Could not find hole edge"); //no edge found..
						  SEQUENCE = SEQNONE;
						  return;
						}
						else
						{
						   var3 = _setup->parameters[2000]; //one edge
						   var4 = ((var2 - var3)/2) + var3;
                           Block.Format("G1X%.4f", var4 ); //back to center of hole
						   Code( Block ); //we're now moving toward the first target point for the probe to be done..
						   SEQUENCE = HOLE5;
						   return;
						}
						break;
   case( HOLE5 )://pulled back to center, now fine one edge of the Y
						if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
		 				if( Engine->InSigs[DIGITIZE].Activated )
						{
						  AfxMessageBox("Could not move to X center"); //no edge found..
						  SEQUENCE = SEQNONE;
						  return;
						}
						else
						{

						  var1 = MainPlanner->YPosition; //start point
						  y=  MainPlanner->YPosition + 100; //move off trip point in opposite direction.
						  Block.Format("G31Y%.4f",y );
						  MeasureMove = false;
				 	      Code( Block ); //we're now moving Y 100 forward..
						  SEQUENCE = HOLE6; //measure X minimum
						  break;
						}
						break;
   case( HOLE6 )://Found one edge, now return to origin
						if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
		 				if( !Engine->InSigs[DIGITIZE].Activated )
						{
						  AfxMessageBox("Could not fine Y hole edge"); //no edge found..
						  SEQUENCE = SEQNONE;
						  return;
						}
						y = var1;
						var2 = _setup->parameters[2001];  
						Block.Format("G1Y%.4f",y );
						MeasureMove = false;
				 	    Code( Block ); //we're now moving X 100 forward..
						SEQUENCE = HOLE7; //measure X minimum
						break;
  case( HOLE7 )://Found one edge, now return to origin
						if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
		 				if( Engine->InSigs[DIGITIZE].Activated )
						{
						  AfxMessageBox("Could not exit Y hole edge"); //no edge found..
						  SEQUENCE = SEQNONE;
						  return;
						}
					    y=  MainPlanner->YPosition - 100; // 
						Block.Format("G31Y%.4f",y );
						MeasureMove = false;
				 	    Code( Block ); //we're now moving X 100 forward..
						SEQUENCE = HOLE8; //measure X minimum
						break;
  case( HOLE8 )://Found one edge, now return to origin
						if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
		 				if( !Engine->InSigs[DIGITIZE].Activated )
						{
						  AfxMessageBox("Could not find Y hole edge #2"); //no edge found..
						  SEQUENCE = SEQNONE;
						  return;
						}
						var3 = _setup->parameters[2001]; //one edge
						var4 = ((var2 - var3)/2) + var3;
						Block.Format("G1Y%.4f", var4  ); //back to center of hole
						MeasureMove = false;
				 	    Code( Block ); //we're now moving X 100 forward..
						SEQUENCE = HOLE9; //measure X minimum
						break;
  case( HOLE9 )://Found one edge, now return to origin
						if( !MainPlanner->MovementDone ) return;
						MainPlanner->MovementDone = false;
		 				if( Engine->InSigs[DIGITIZE].Activated )
						{
						  AfxMessageBox("Could not find center without probe hit"); //no edge found..
						  SEQUENCE = SEQNONE;
						  return;
						}
						AfxMessageBox(" X/Y Axis are now in center of hole." ); 
						Engine->LastState = STOP;
						Engine->State = STOP;
						SEQUENCE = SEQNONE; //measure X minimum
						DoButton( 1003 ); //press the stop button, just in case..
						break;
  }
}
void MenuHandler::CalcRatios(double x, double y)
{
	double dx = x - MainPlanner->XPosition;
	double dy = y - MainPlanner->YPosition;
	double angle = atan2( dx, dy);
    backy = -m_clearance * cos( angle);
 	backx = -m_clearance * sin( angle);
}
 

ProbePoint MenuHandler::GetGridPoint()
{
  ProbePoint res;
  target.x -= m_length / 2;
  target.y -= m_width / 2;
  switch( ProbeAxis )
  {
  case( 0 ):
       target.x += m_XGrid * XInc; //move X one iteration;
	   if( target.x >= XMax )
	   {
		   ProbeAxis = 1; XInc = -1;
	   }
       if( target.x <= -XMax )
	   {
		   ProbeAxis = 1; XInc = 1;
		   XMax += m_XGrid;
	   }
	   break;
  case( 1 ):
       target.y += m_YGrid * YInc; //move X one iteration;
	   if( target.y >= YMax )
	   {
		   ProbeAxis = 0; YInc = -1;
		   
	   }
	   if( target.y <= -YMax )
	   {
		   ProbeAxis = 0; YInc = 1;
		   YMax += m_YGrid;
	   }
	   break;

  }
  target.x += m_length / 2;
  target.y += m_width / 2;
  res = target;
  return res;
}

bool MenuHandler::OKtoStart(void)
{
	OkayToMove* start = new OkayToMove();
	start->DoModal();
	MainPlanner->ProbeRad = m_ProbeRad;
	bool result = start->m_IsOkayToMove;
	delete start;
    if( result ) return true;
	return false;
}

void MenuHandler::OnCenter()
{
	SEQUENCE = SEQNONE;
    HRESULT res = AfxMessageBox( "Probe should now be IN the hole and ready to measure X&Y..Continue?", MB_YESNO);
	if( res == IDNO) return;
    if(!OKtoStart())
		return;
	//Add dialog to get the data from the user...
	SEQUENCE = HOLESTART;
}

 
void MenuHandler::ThreeDprobe(void)
{

	if( abs( MainPlanner->XPosition) > .01 ||
							abs( MainPlanner->YPosition) > .01 )
						{
                            SEQUENCE = SEQNONE;
							AfxMessageBox( "X and Y Axis must be zeroed to proceed!");
							return;
						}
	if( MainPlanner->m_Loaded ) 
						{
                           SEQUENCE = SEQNONE;
							AfxMessageBox( "Please close current Gcode file before probing!");
							return;

						}
	 
	probeconfig *pro = new probeconfig();

	pro->m_feedrate = m_feedrate;
	pro->m_length = m_length;
	pro->m_width = m_width;
	pro->m_clearance = m_clearance;
	pro->m_probedist = m_probedist;
	pro->m_Xstepover = m_XGrid;
	pro->m_Ystepover = m_YGrid;
	pro->m_ProbeRad = m_ProbeRad;
	pro->m_ProbeStuck = m_probestuck;
	if( pro->DoModal()== IDCANCEL)
	{
		delete pro;
		return;
	}

	m_feedrate = pro->m_feedrate;
	m_length =   pro->m_length;
	m_width =    pro->m_width;
	m_clearance = pro->m_clearance;
	m_probedist = pro->m_probedist;
	m_XGrid = pro->m_Xstepover;
	m_YGrid = pro->m_Xstepover;
	delete pro;

	double test = m_clearance * 5;
	double Tol = 5;
	if( _setup->length_units == INCHES ) Tol = .25;
	if( Tol < test )
	{
       AfxMessageBox(" Probe Clearance too high, should be less than .2mm or .05 inches.");
       return;
	}
	if( m_length / m_XGrid >  m_width / m_YGrid )
	{
		 m_YGrid = m_width / ( m_length / m_XGrid);
	}
	if( m_width / m_YGrid >  m_length / m_XGrid )
	{
		 m_XGrid = m_length / ( m_width / m_YGrid);
	}

	if(!OKtoStart())
		return;
	//Add dialog to get the data from the user...
	SEQUENCE = PROBESTART;
}
 
bool MenuHandler::IsProbeHit()
{
	return Engine->InSigs[DIGITIZE].Activated;
}
bool MenuHandler::Rest()
{ 
	if(Restcycles <= 0) return false;
	Restcycles--;
	return true;
}

void MenuHandler::SetMachError(CString Message)
{
	CString *err = &MainPlanner->LastError;
	if( err != NULL )
		*err = Message;

}