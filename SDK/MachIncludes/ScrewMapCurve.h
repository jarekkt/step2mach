#pragma once

class ScrewMapCurve
{
public:
	ScrewMapCurve(void);
	~ScrewMapCurve(void);
	double GetValue( double where );
	double GetCorrectionAt( double where );
	void   Spline();
    int    nPoints;  //number of points in this curve;
	double *X1,*X2;  // the dataset of points
	double *B,*C,*D; //coefficients of the spline
	double  length;
	bool    Invert;
	void LoadCurve(int axis);
	void SaveCurve(int axis);
	void AddPoint( double orig, double where);

};
