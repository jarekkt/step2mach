//	_ScrewMapCurve.h - replaced class with struct
//

#pragma once

struct	_ScrewMapCurve
{
    int		nPoints;  //number of points in this curve;
	double	*X1,*X2;  // the dataset of points
	double	*B,*C,*D; //coefficients of the spline
	double	length;
	bool	Invert;
};
