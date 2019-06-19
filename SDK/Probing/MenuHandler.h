#pragma once

enum seq { SEQNONE, TOOLSTAGE1, TOOLSTAGE2, TOOLSTAGE3, TOOLSTAGE4,
                    CENSTAGE1,  CENSTAGE2,  CENSTAGE3,  CENSTAGE4,
					PROBESTART,PROBEMOVE,PROBEMOVEY,PROBEMEASURE,
					PROBEREV,PROBEREVY,RAISEZ,PROBEBEGIN,HOLESTART,
					HOLE1,HOLE2,HOLE3,HOLE4,HOLE5,HOLE6,HOLE7,HOLE8,HOLE9,
					GETPOINT
};

enum REVMOVES { NONE, XMOVE, YMOVE, ZMOVE };
// MenuHandler
struct ProbePoint
{
   double x,y,z,a,b,c;
};
class MenuHandler : public CWnd
{
	DECLARE_DYNAMIC(MenuHandler)

public:
	MenuHandler();
	virtual ~MenuHandler();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void InitMenus(void);
	void OnCenter();
	void ToolTouch(void);
	void DoPoint(void);
	void DoCenter3(void);
	void DoRotate3(void);
	void SetMachError(CString Message);
	void CalcPoint( int point );
	void CheckMenu( int PointSearch, bool done);
	seq SEQUENCE;
//Now some variables for the tool touch probe sequence..
	 
	ProbePoint target,current,lastmove,points[3];
	bool         POK[3];
	REVMOVES     LastMove;
	int          Reversals;
	double       XDir,YDir,ZDir;
	int          PointSearch;


	double m_length,m_width,m_XGrid,m_YGrid,m_probedist,m_clearance,m_feedrate,m_ProbeRad;

//vars for the spiral generator, prober #1
	double XInc,YInc,XMax,YMax;
	double ratiox,ratioy;
	bool MeasureMove;
	int  ProbeAxis;
	double backx,backy;
	double m_probestuck;



public:

	 CMenu addon;
protected:
	
public:
	int  Restcycles;
	int  RangeStart;
	void DoMenuItem(int ID);
	void CalcRatios(double , double );
	void Sequencer(void);
	bool OKtoStart(void);
	void ThreeDprobe(void);
	bool IsProbeHit();
	bool Rest();
	bool CheckTarget();
	ProbePoint GetGridPoint();
};


