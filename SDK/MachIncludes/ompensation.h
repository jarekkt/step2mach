#pragma once

struct DPoint
{
	double x,y;
};
 
 
class Compensation
{
public:
	Compensation(void);
	void CorrectTangent( double *newx, double *newy , double endx, double endy );
	void TurnTangent( double *newx, double *newz , double endx, double endz );
	double Compensation::square( double f ) { return (f*f) ;};
	int Compensation::line_line( double dist, double x1, double y1, double x2, double y2, 
                                 double x3, double y3, double *x4, double *y4, double *x5, double *y5 );
	int Compensation::circle_line ( double dist, double x1, double y1, double x2, double y2, 
                                    double x3, double y3, double *x4, double *y4, double *x5, double *y5, int rotation );
	int Compensation::circle_circle ( double dist, double x1, double y1, double x2, double y2, 
                                      double x3, double y3, double *x4, double *y4, double *x5, double *y5, 
                                      int rotation1, int rotation2 );
	int Compensation::turn_circle_circle ( double dist, double x1, double y1, double x2, double y2, 
                                      double x3, double y3, double *x4, double *y4, double *x5, double *y5, 
                                      int rotation1, int rotation2 );
    int Compensation::circle_circle_intersection(double x0, double y0, double r0,
                               double x1, double y1, double r1,
                               double *xi, double *yi,
                               double *xi_prime, double *yi_prime);
	bool Compensation::CheckForHit( double radius, double x0, double y0,  double x1, double y1, double x2, double y2 );
    double Compensation::LineCircle( DPoint lstart, DPoint lend, DPoint center, double radius );
	~Compensation(void);
};
