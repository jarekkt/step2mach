// this file uses JavaDoc style comment blocks for automatic extraction of source code documentation.

/*!\file
 \brief Contains some useful math helpers for common 3D graphics entities.

 In this file are implemented some mathematical entities often used in 3D graphics (vecors, points, etc.) plus some useful constants, macros and definitions
 \version 0.1
 \date 12/06/99
 \author Alessandro Falappa
*/

#ifndef _3D_MATH_H
#define _3D_MATH_H

#include <iostream.h>
#include <assert.h>
#include <math.h>
#ifdef _AFXDLL // see if we are using MFC...
#include <afxwin.h>
#endif

#ifdef HIGH_PRECISION

//! The base type for all the math helpers
typedef double real;
//! the treshold for comparisons with zero, mainly used to avoid division by zero errors
const real epsilon=1e-12;
//! defined when high precision is requested
#define REAL_IS_DOUBLE

#else

// WARNING: these pragmas below could be MSVC compiler specific
#pragma warning( push )// memorize the warning status
#pragma warning( disable : 4305 )// disable "initializing : truncation from 'const double' to 'float'" warning
#pragma warning( disable : 4244 )// disable "double to float conversion possible loss of data" warning
#pragma warning( disable : 4136 )// disable "conversion between different floating-point types" warning
#pragma warning( disable : 4309 )// disable " 'conversion' : truncation of constant value" warning
#pragma warning( disable : 4051 )// disable " 'type conversion' ; possible loss of data" warning
//! The base type for all the math helpers
typedef float real;
//! the treshold for comparisons with zero, mainly used to avoid division by zero errors
const real epsilon=1e-7;
//! defined when high precision is not requested
#define REAL_IS_FLOAT

#endif

//=============================================================================
//=============================================================================

//!A vector class.
/*!
The vector class incapsulates a classic C++ vector of three real values and treats them as a 3 dimensional mathematical vectors.

The most common operations between mathematical vectors (and some which involves scalars too) are defined.
*/
class vector
{
public:
	static int counter;//!< counts how many vector objects are present
	real vec[3];//!< the actual vector

public:
// operators
	vector();//!< default constructor
	vector(const real& x,const real& y,const real& z);//!< constructs a vector from three values
	vector(vector& from, vector& to);//!< constructs a vector from two other vectors
	vector(const vector& other);//!< the copy constructor
	~vector();//!< the distructor
	real& x();//!< accessor for the x component (can be used as l-value too)
	real& y();//!< accessor for the y component (can be used as l-value too)
	real& z();//!< accessor for the z component (can be used as l-value too)
	real x() const;//!< returns the x component (r-value only)
	real y() const;//!< returns the y component (r-value only)
	real z() const;//!< returns the z component (r-value only)
	vector& operator=(const vector& other);//!< the assignment
	vector& operator+=(const vector& other);//!< the sum & assign
	vector& operator-=(const vector& other);//!< the subtract & assign
	vector& operator*=(const real& fact);//!< the short multiply by a scalar factor & assign
	vector& operator/=(const real& fact);//!< the short divide by a scalar factor & assign
	real& operator[](const int& index);//!< an "access like a C++ vector"
#ifdef HIGH_PRECISION
	operator double*();//!< the conversion to a 3 double elements C++ vector
#else
	operator float*();//!< the conversion to a 3 float elements C++ vector
#endif
//	operator char*();//!< the conversion of the vector into a textual form (null terminated string)
	real normalize();//!< normalize the vector
	vector normalized() const;//!< normalized copy of the vector
	real length() const;//!< get the length of the vector
	real length2() const;//!< get the squared length of the vector
	void EpsilonCorrect(const vector& v);//!< if the vector is almost equal to the origin substitute it with v
// ststic functions
	static int howMany();//!< returns how many vector objects exists

// friend functions	
	friend int operator==(const vector& v1,const vector& v2);//!< the equality operator
	friend int operator!=(const vector& v1,const vector& v2);//!< the inequality operator
	friend vector operator+(const vector& v1,const vector& v2);//!< the sum
	friend vector operator-(const vector& v1,const vector& v2);//!< the difference
	friend vector operator-(const vector& v1);//!< the negation
	friend real operator*(const vector& v1,const vector& v2);//!< the vector dot product
	friend vector operator^(const vector& v1,const vector& v2);//!< the vector cross product
	friend vector operator*(const vector& v,const real& fact);//!< the multiply a vector by a scalar factor
	friend vector operator*(const real& fact,const vector& v);//!< the multiply a scalar factor by a vector
	friend vector operator/(const vector& v,const real& fact);//!< the divide a vector by a scalar factor
	friend vector Bisect(vector v0,vector v1);//!< returns the unit vector which halves the arc between v0 and v1
	friend void clamp(vector& vec,const real& low,const real& high);//!< clamps all the vector components between the given tresholds
	friend ostream& operator<<(ostream& os,const vector& vect);//!< the print vector to C++ stream
#ifdef _AFXDLL // see if we are using MFC...
#ifdef _DEBUG		//.. and if we are in a debug build
	friend CDumpContext& operator<<(CDumpContext& cd,const vector& vect);//!< the print vector to MSVC++ debug console
#endif
#endif
};
//-----------------------------------------------------------------------------
// inlines

inline vector::vector()
{
	vec[0]=vec[1]=vec[2]=0.0;
	counter++;
}

inline vector::vector(const real& x,const real& y,const real& z)
{
	vec[0]=x;
	vec[1]=y;
	vec[2]=z;
	counter++;
}

/*!
This function constructs the vector which goes from the vector \e from to the vector \e to.
It is useful when a vector has to be constructed from the difference of two other vectors.
\param from the first vector
\param to the second vector
*/
inline vector::vector(vector& from, vector& to)
{
	vec[0]=to.vec[0]-from.vec[0];
	vec[1]=to.vec[1]-from.vec[1];
	vec[2]=to.vec[2]-from.vec[2];
	counter++;
}

inline vector::vector(const vector& other)
{
	*this=other;
	counter++;
}

inline vector::~vector()
{
	counter--;
}

inline real& vector::x()
{
	return vec[0];
}

inline real& vector::y()
{
	return vec[1];
}

inline real& vector::z()
{
	return vec[2];
}

inline real vector::x() const
{
	return vec[0];
}

inline real vector::y() const
{
	return vec[1];
}

inline real vector::z() const
{
	return vec[2];
}

inline vector& vector::operator=(const vector& other)
{
	//check for 'a=a' case
	if (this==&other) return *this;
	vec[0]=other.vec[0];
	vec[1]=other.vec[1];
	vec[2]=other.vec[2];
	return *this;
}

inline vector& vector::operator+=(const vector& other)
{
	vec[0]+=other.vec[0];
	vec[1]+=other.vec[1];
	vec[2]+=other.vec[2];
	return *this;
}

inline vector& vector::operator-=(const vector& other)
{
	vec[0]-=other.vec[0];
	vec[1]-=other.vec[1];
	vec[2]-=other.vec[2];
	return *this;
}

inline vector& vector::operator*=(const real& fact)
{
	vec[0]*=fact;
	vec[1]*=fact;
	vec[2]*=fact;
	return *this;
}

inline vector& vector::operator/=(const real& fact)
{
	assert(fabs(fact) >= epsilon);
	vec[0]/=fact;
	vec[1]/=fact;
	vec[2]/=fact;
	return *this;
}

/*!
This operator redirects the access to the internal vector. It does make a range check on the index in debug builds trough the ANSI assert function.
It can be used on both sides of an assignment.
\return a reference to the requested element
\param index the index which should be one of 0,1,2
*/
inline real& vector::operator[](const int& index)
{
	assert(index>=0 && index<=2);
	return vec[index];
}

inline real vector::length2() const
{
	return (*this)*(*this);
}

inline real vector::length() const
{
	return sqrt(this->length2());
}

/*!
The counting of the vector objects is realized trough a static counter variable.
\return the number of vector objects in memory
*/
inline int vector::howMany()
{
	return counter;
}

/*!
this conversion operator allows to use a vector in places of a classic real[3]
*/
/*
inline vector::operator real*()
{
	return (real*)vec;
}
*/
#ifdef HIGH_PRECISION

/*!
this conversion operator allows to use a vector in places of a classic double[3]
*/
inline vector::operator double*()
{
	return (double*)vec;
}

#else

/*!
this conversion operator allows to use a vector in place of a classic float[3]
*/
inline vector::operator float*()
{
	return (float*)vec;
}

#endif

//-----------------------------------------------------------------------------
// useful constants (declaration)

extern const vector ORIGIN;
extern const vector X_AXIS;
extern const vector Y_AXIS;
extern const vector Z_AXIS;

//=============================================================================
//=============================================================================

/*!
A transformation matrix class.

The matrix class groups sixteen real values an treats them as a 4x4 matrix. Standard
C++ matrices (2 dimensional vectors) are stored by row, since for graphical applications
a column major order is preferable the access indices are internally swapped.

The most common operators between matrices (and some which involves scalars and vectors too) are defined.
*/
class tmatrix
{
private:
	static int counter;//!< counts how many matrices objects are present
	real mat[4][4];//!< the matrix data
public:
	//! Espresses how to store a tmatrix in a single 16 elements vector, by column or by row
	enum ordermode
	{
		COLUMN,//!< column major order
		ROW//!< row major order
	};
	tmatrix();//!< default constructor
	tmatrix(const real& val);//!< constructs a tmatrix and fills it with a value
	tmatrix(const real vector[16],ordermode ord=COLUMN);//!< constructs a tmatrix from a vector which contains a 4x4 matrix in row major or column major order
	tmatrix(const tmatrix& other);//!< the copy constructor
	~tmatrix();//!< the distructor
	tmatrix& operator-();//!< negation
	tmatrix& operator=(const tmatrix& other);//!< assignment
	tmatrix& operator+=(const tmatrix& other);//!< sum & assign
	tmatrix& operator-=(const tmatrix& other);//!< subtract & assign
	tmatrix& operator*=(const tmatrix& other);//!< multiply by a tmatrix & assign
	tmatrix& operator*=(const real& fact);//!< multiply by a scalar factor & assign
	tmatrix& operator/=(const real& fact);//!< divide by a scalar factor & assign
	real& operator()(const int& row,const int& col);//!< an "access like a C++ tmatrix"
#ifdef HIGH_PRECISION
	operator double*();//!< conversion to a 16 doubles C++ vector (column major order)
#else
	operator float*();//!< conversion to a 16 floats C++ vector (column major order)
#endif
	void loadIdentity();//!< fills the matrix with the identity matrix
//	operator char*();//!< conversion of the tmatrix into a textual form (null terminated string)
//static functions
	static int howMany();//!< returns how many tmatrix objects exists
// friend functions	
	friend int operator==(const tmatrix& t1,const tmatrix& t2);//!< the equality operator
	friend int operator!=(const tmatrix& t1,const tmatrix& t2);//!< the inequality operator
	friend tmatrix operator+(const tmatrix& t1,const tmatrix& t2);//!< the sum
	friend tmatrix operator-(const tmatrix& t1,const tmatrix& t2);//!< the difference
	friend tmatrix operator*(const tmatrix& t1,const tmatrix& t2);//!< tmatrix product
	friend tmatrix operator*(const tmatrix& tmat,const real& fact);//!< multiply a tmatrix by a scalar factor
	friend tmatrix operator*(const real& fact,const tmatrix& tmat);//!< multiply a scalar factor by a tmatrix
	friend tmatrix operator/(const tmatrix& tmat,const real& fact);//!< divide a tmatrix by a scalar factor
	friend ostream& operator<<(ostream& os,const tmatrix& m);//!< print tmatrix to C++ stream
#ifdef _AFXDLL // see if we are using MFC
#ifdef _DEBUG
	friend CDumpContext& operator<<(CDumpContext& cd,const tmatrix& m);//!< print tmatrix to MSVC++ debug console
#endif
#endif
};

//-----------------------------------------------------------------------------
// inlines

inline tmatrix::tmatrix(const tmatrix& other)
{
	*this=other;
	counter++;
}

inline tmatrix::~tmatrix()
{
	counter--;
}

/*!
The counting of the tmatrix objects is realized trough a static counter variable.
\return the number of tmatrix objects in memory
*/
inline int tmatrix::howMany()
{
	return counter;
}

/*!
This operator redirects the access to the internal matrix. It does make a range
check on the index in debug builds trough the ANSI assert function.
It can be used on both sides of an assignment.
\return a reference to the requested element
\param row the row index which should be one of 0,1,2,3
\param col the column index which should be one of 0,1,2,3
\date 18/06/99
*/
inline real& tmatrix::operator()(const int& row,const int& col)
{
	assert(row>=0 && row<=3);
	assert(col>=0 && col<=3);
	return mat[col][row];// swap indices to store by column
}

#ifdef HIGH_PRECISION

/*!
this conversion operator allows to use a tmatrix in places where a column major
order vector of 16 double elements is requested (e.g. the OpenGL functions for
retrieving/setting the modelview or projection matrix).
*/
inline tmatrix::operator double*()
{
	return (double*)mat;
}

#else

/*!
this conversion operator allows to use a tmatrix in places where a column major
order vector of 16 float elements is requested (e.g. the OpenGL functions for
retrieving/setting the modelview or projection matrix).
*/
inline tmatrix::operator float*()
{
	return (float*)mat;
}

#endif

//-----------------------------------------------------------------------------
// useful constants


//=============================================================================
//=============================================================================

/*!
A generic quaternion class.
The quaternion uses internally the (s,<B>v</B>) representation, where s is a scalar and <B>v</B> a vector.
The most common operations from quaternion calculus are implemented.

Some internet references are:
<UL>
<LI>http://www.cs.berkley.edu/~laura/cs184/quat/quaternion.html
<LI>http://www.astro.virginia.edu/~eww6n/math/Quaternion.html
<LI>http://forum.swarthmore.edu/dr.math/problems/prasad2.17.96.html
<LI>http://graphics.cs.ucdavis.edu/GraphicsNotes/Quaternions/Quaternions.html
</UL>

A paper by Ken Shoemake (the quaternions "inventor") is available at<BR>
<UL>
<LI>ftp://ftp.cis.upenn.edu/pub/graphics/shoemake/
</UL>
*/
class quaternion
{
private:
	static int counter;//!< counts how many quaternion objects are present
public:
	real s;//!< the scalar part of a quaternion
	vector v;//!< the vector part of a quaternion
public:
	quaternion();//!< default constructor
	quaternion(const real& scal, const vector& vec);//!< constructs a quaternion from the scalar and vector components
	quaternion(const real& s1,const real& s2,const real& s3,const real& s4);//!< constructs a quaternion from four real values
	quaternion(const quaternion& other);//!< the copy constructor
	virtual ~quaternion();//!< the distructor
	real& x();//!< accessor for the x component of the vector part (can be used as l-value too)
	real& y();//!< accessor for the y component of the vector part (can be used as l-value too)
	real& z();//!< accessor for the z component of the vector part (can be used as l-value too)
	real& w();//!< accessor for the scalar part (can be used as l-value too)
	real& scalarPart();//!< other accessor for the scalar component (can be used as l-value too)
	vector& vectorPart();//!< accessor for the vector part (can be used as l-value too)
	quaternion& operator=(const quaternion& other);//!< assignment
	quaternion& operator+=(const quaternion& other);//!< sum & assign
	quaternion& operator-=(const quaternion& other);//!< subtract & assign
	quaternion& operator*=(const quaternion& other);//!< multiply by a quaternion & assign
	quaternion& operator/=(const quaternion& other);//!< divide by a quaternion & assign
	quaternion& operator*=(const real& fact);//!< multiply by a scalar factor & assign
	quaternion& operator/=(const real& fact);//!< divide by a scalar factor & assign
//	operator float*();//!< conversion to a 4 elements C++ vector
//	operator char*();//!< conversion of the quaternion into a textual form (null terminated string)
	real normalize();//!< normalize the quaternion
	quaternion normalized() const;//!< normalized copy of the quaternion
	void conjugate();//!< conjugate of the quaternion
	quaternion conjugated() const;//!< conjugated copy of the quaternion
	real inverse();//!< inverse of the quaternion
	quaternion inversed() const;//!< inversed copy of the quaternion
	real length() const;//!< get the length of the quaternion
	real norm() const;//!< get the norm (similar to the squared length) of the quaternion
	virtual tmatrix getRotMatrix();//<! constructs a rotation matrix from the quaternion
// static functions
	static int howMany();//!< returns how many quaternion objects exists
// friend functions	
	friend int operator==(const quaternion& q1,const quaternion& q2);//!< the equality operator
	friend int operator!=(const quaternion& q1,const quaternion& q2);//!< the inequality operator
	friend quaternion operator+(const quaternion& q1,const quaternion& q2);//!< the sum
	friend quaternion operator-(const quaternion& q1,const quaternion& q2);//!< the difference
	friend quaternion operator-(const quaternion& q1);//!< negation
	friend quaternion operator*(const quaternion& q1,const quaternion& q2);//!< quaternion product
	friend quaternion operator*(const quaternion& q,const real& s);//!< multiply a quaternion by a scalar
	friend quaternion operator*(const real& s,const quaternion& q);//!< multiply a scalar by a quaternion
	friend quaternion operator/(const quaternion& q,const real& s);//!< divide a quaternion by a scalar factor
	friend quaternion operator/(const quaternion& q1,const quaternion& q2);//!< divide a quaternion by a quaternion
	friend ostream& operator<<(ostream& os,const quaternion& q);//!< print quaternion to C++ stream
#ifdef _AFXDLL // see if we are using MFC
#ifdef _DEBUG
	friend CDumpContext& operator<<(CDumpContext& ad,const quaternion& q);//!< print quaternion to MSVC++ debug console
#endif
#endif
};

//-----------------------------------------------------------------------------
// inlines

inline quaternion::quaternion()
{
	s=0.0;
	counter++;
};

/*!
This constructor assumes an (s,\b v) form so interprets the real calues as w,x,y,z respectively.
Another common representation for quaternions, the "homogeneous" one, is x,y,x,w ordered.
\param s1 the scalar part
\param s2 the x component of the vector part
\param s3 the y component of the vector part
\param s4 the z component of the vector part
\date 15/06/99
*/
inline quaternion::quaternion (const real& s1,const real& s2,const real& s3,const real& s4)
:s(s1),v(s2,s3,s4)
{
	counter++;
}

inline quaternion::quaternion (const real& scal, const vector& vec)
:s(scal),v(vec)
{
	s=scal;
	counter++;
}

inline quaternion::~quaternion()
{
	counter--;
}

inline quaternion::quaternion(const quaternion& other)
{
	*this=other;
	counter++;
}

/*!
The counting of the quaternion objects is realized trough a static counter variable.
\return the number of quaternion objects in memory
*/
inline int quaternion::howMany()
{
	return counter;
}

inline real& quaternion::x()
{
	return v.x();
}

inline real& quaternion::y()
{
	return v.y();
}

inline real& quaternion::z()
{
	return v.z();
}

inline real& quaternion::w()
{
	return s;
}

inline real& quaternion::scalarPart()
{
	return s;
}

inline vector& quaternion::vectorPart()
{
	return v;
}

inline quaternion& quaternion::operator=(const quaternion& other)
{
	//check for 'a=a' case
	if (this==&other) return *this;
	s=other.s;
	v=other.v;
	return *this;
}

inline quaternion& quaternion::operator+=(const quaternion& other)
{
	s+=other.s;
	v+=other.v;
	return *this;
}

inline quaternion& quaternion::operator-=(const quaternion& other)
{
	s-=other.s;
	v-=other.v;
	return *this;
}

inline quaternion& quaternion::operator*=(const real& fact)
{
	s*=fact;
	v*=fact;
	return *this;
}

inline quaternion& quaternion::operator/=(const real& fact)
{
	assert(fabs(fact) >= epsilon);
	s/=fact;
	v/=fact;
	return *this;
}

inline real quaternion::length() const
{
	return sqrt(norm());
}

inline void quaternion::conjugate()
{
	v=-v;
}

inline quaternion quaternion::conjugated() const
{
	return quaternion(s,-v);
}

/*!
This function check if all elements of \e v1 are equal to the corresponding elements of \e v2.
*/
inline int operator==(const vector& v1,const vector& v2)
{
	if(v1.vec[0]==v2.vec[0] && v1.vec[1]==v2.vec[1] && v1.vec[2]==v2.vec[2]) return 1;
	else return 0;
}

/*!
This function check if some of the elements of \e v1 differs from the corresponding elements of \e v2.
*/
inline int operator!=(const vector& v1,const vector& v2)
{
	if(v1.vec[0]==v2.vec[0] && v1.vec[1]==v2.vec[1] && v1.vec[2]==v2.vec[2]) return 0;
	else return 1;
}


//=============================================================================
//=============================================================================

/*!
A unit lenght quaternion class.

The unitquaternion class manages quaternions of unit length, such quaternions
can be used to represent arbitrary rotations. To mantain the unit lenght property
along quaternion calculus addition and subtraction as well as multiplication and
division by scalars are not allowed (they're made private or they're overloaded
by "trap" functions).

Actually only a few member functions of the base class are overloaded since
the quaternion calculus apply with no modification to unit quaternions.
*/
class unitquaternion : public quaternion
{
private:
	unitquaternion& operator+=(const unitquaternion& other);//!< sum & assign is not allowed
	unitquaternion& operator-=(const unitquaternion& other);//!< subtract & assign is not allowed
	unitquaternion& operator*=(const real& fact);//!< multiply by a scalar factor & assign is not allowed
	unitquaternion& operator/=(const real& fact);//!< divide by a scalar factor & assign is not allowed
	unitquaternion(const vector& v, const real& s);//!< constructs a unitquaternion assigning directly the scalar and vector parts
public:
	real x() const;//!< accessor for the x component of the vector part
	real y() const;//!< accessor for the y component of the vector part
	real z() const;//!< accessor for the z component of the vector part
	real w() const;//!< accessor for the scalar part
	real scalarPart() const;//!< other accessor for the scalar component
	vector vectorPart() const;//!< accessor for the vector part
	unitquaternion();//!< default constructor
	unitquaternion(const real& angle, const vector& axis);//!< constructs a unitquaternion representing a rotation of angle radiants about axis 
	unitquaternion(const quaternion& q);//!< constructs a unitquaternion from a generic one (conversion by normalizing)
	~unitquaternion();//!< the distructor
	unitquaternion inversed() const;//!< inversed copy of the unitquaternion
	void inverse();//!< inverse of the unitquaternion
	tmatrix getRotMatrix();//<! constructs a rotation matrix from the quaternion
	void getVectorsOnSphere(vector& vfrom,vector& vto);//<! converts a unitquaternion to two vectors on a unit sphere (the extremes of a rotation)
	unitquaternion& operator*=(const unitquaternion& other);//!< multiply by another unitquaternion & assign is not allowed
// friend functions	
	friend unitquaternion operator+(const unitquaternion& q1,const unitquaternion& q2);//!< the sum is not allowed
	friend unitquaternion operator-(const unitquaternion& q1,const unitquaternion& q2);//!< the difference is not allowed
	friend unitquaternion operator*(const unitquaternion& q,const real& s);//!< multiply a unitquaternion by a scalar is not allowed
	friend unitquaternion operator*(const real& s,const unitquaternion& q);//!< multiply a scalar by a unitquaternion is not allowed
	friend unitquaternion operator/(const unitquaternion& q,const real& s);//!< divide a unitquaternion by a scalar factor is not allowed
};

//-----------------------------------------------------------------------------
// inlines

inline unitquaternion::unitquaternion()
:quaternion(1,0,0,0)
{
};


inline unitquaternion::unitquaternion (const quaternion& q)
:quaternion(q)
{
	normalize();
}


/*!
This constructor has a different meaning from the same in the base class. Here
the vector means an axis of rotation while the real means the angle to rotate
about the axis.

\b NOTE: the angle and axis vector are not directly assigned to the real part
and the vector part, respectively, of the quaternion. The unit quaternion (<I>s</I>,<B>v</B>)
represents a rotation of \b angle radians about the axis \b a if:

\e s = cos(\e angle / 2)<BR>
\b v = \b a * sin( \e angle / 2)
\param angle the rotation angle
\param axis the axis of rotation
\date 18/06/99
*/
inline unitquaternion::unitquaternion (const real& angle, const vector& axis)
:quaternion( cos(angle/2), sin(angle/2)*axis.normalized() )
{
}

/*!
This constructor has been introduced exclusively to make the inversed function
more efficient by avoiding too many unitquaternion copies and conversions to
quaternions.
*/
inline unitquaternion::unitquaternion (const vector& v, const real& s)
:quaternion( s, v )
{
}

inline unitquaternion::~unitquaternion()
{
}

/*!
For unitquaternions the inverse equals the conjugate (which is simpler to calculate)
This function doesn't modifies the quaternion upon which has been called, it returns a new quaternion instead.
\return the normalized copy of the quaternion
\date 18/06/99
*/
inline unitquaternion unitquaternion::inversed() const
{
	return unitquaternion(-v,s);
}

/*!
For unitquaternions the inverse equals the conjugate (which is simpler
to calculate). The function doesn't call the base conjugate function to
avoid an expensive quaternion to unitquaternion conversion.
This function modifies the quaternion upon which has been called.
*/
inline void unitquaternion::inverse()
{
	v=-v;
}

/*!
This function overrides the same in base class to prevent the use as an l-value
(that is to modify the x component of the vector part).
*/
inline real unitquaternion::x() const
{
	return ((vector&)v).x();// explicit cast to use the non const vector x() function
}

/*!
This function overrides the same in base class to prevent the use as an l-value
(that is to modify the y component of the vector part).
*/
inline real unitquaternion::y() const
{
	return ((vector&)v).y();// explicit cast to use the non const vector y() function
}

/*!
This function overrides the same in base class to prevent the use as an l-value
(that is to modify the z component of the vector part).
*/
inline real unitquaternion::z() const
{
	return ((vector&)v).z();// explicit cast to use the non const vector z() function
}

/*!
This function overrides the same in base class to prevent the use as an l-value
(that is to modify the scalar part).
*/
inline real unitquaternion::w() const
{
	return s;
}

/*!
This function overrides the same in base class to prevent the use as an l-value
(that is to modify the scalar part).
*/
inline real unitquaternion::scalarPart() const
{
	return s;
}

/*!
This function overrides the same in base class to prevent the use as an l-value
(that is to modify the vector part).
*/
inline vector unitquaternion::vectorPart() const
{
	return v;
}


//-----------------------------------------------------------------------------
// useful constants

//=============================================================================
//=============================================================================

/* inserire qui alcune macro o funzioni globali come ad esempio:
	- clamping
	- conversione angoli gradi<->radianti
*/

/*!
limits a value in a range, modifying it.
\param val the value to clamp
\param low the lower treshold
\param high the higher treshold
*/
inline void clamp(real& val,const real& low,const real& high)
{
	if(val<low) val=low;
	if(val>high) val=high;
}

/*!
limits a value in a range, returning the clamped value.
\return the clamped value
\param val the value to clamp
\param low the lower treshold
\param high the higher treshold
*/
inline real clamped(const real& val,const real& low,const real& high)
{
	if(val<low) return low;
	else if(val>high) return high;
		else return val;
}


/*!
limits the vector components in a range, modifying it.
\param theVec the vector to clamp
\param low the lower treshold
\param high the higher treshold
*/
inline void clamp(vector& theVec,const real& low,const real& high)
{
	clamp(theVec.vec[0],low,high);
	clamp(theVec.vec[1],low,high);
	clamp(theVec.vec[2],low,high);
}

/*!
\short returns \e angle expressed in degrees.
\return the angle expresses in radians
\param angle the angle value
\author Alessandro Falappa
*/
inline real RadToDeg(const real& angle)
{
	return angle*57.29577951308;
}

/*!
\short returns \e angle expressed in radians.
\return the angle expresses in degrees
\param angle the angle value
*/
inline real DegToRad(const real& angle)
{
	return angle*0.01745329251994;
}

/*!
\short converts radiants to degrees.
This function modify its argument.
\param angle the angle to be converted
*/
inline void ConvertToDeg(real& angle)
{
	angle*=57.29577951308;
}

/*!
\short converts degrees to radiants.
This function modify its argument.
\param angle the angle to be converted
*/
inline void ConvertToRad(real& angle)
{
	angle*=0.01745329251994;
}



/*!
\short absolute value function which executes a simple test
This function executes a simple test on \e val negativity returning the
opposite if true. Such a test can be faster than the call to the \e fabs
library routine
\return the absolute value of \e val
*/
inline real simpleabs(const real &val)
{
	return val>0?val:-val;
}
//! the greek pi constant
extern const real G_PI;

//! greek pi / 2
extern const real G_HALF_PI;

//!2 * greek pi
extern const real G_DOUBLE_PI;

#ifdef _AFXDLL
#undef assert
//!maps the assert function to the MFC ASSERT macro
#define assert(exp) ASSERT(exp)
#endif

#ifndef HIGH_PRECISION
// this below could be MSVC compiler specific
#pragma warning( pop )// reset the warning status
#endif

struct CVector3
{
public:
	float x, y, z;						
};


//	This returns a perpendicular vector from 2 given vectors by taking the cross product.
CVector3 Cross(CVector3 vVector1, CVector3 vVector2);

//	This returns a vector between 2 points
CVector3 Vector(CVector3 vPoint1, CVector3 vPoint2);

bool ComputeFaceNormal (CVector3 *p1, CVector3 *p2, CVector3 *p3, CVector3 *pOut);

//	This returns the magnitude of a normal (or any other vector)
float Magnitude(CVector3 vNormal);

//	This returns a normalize vector (A vector exactly of length 1)
CVector3 Normalize(CVector3 vNormal);

//	This returns the normal of a polygon (The direction the polygon is facing)
CVector3 Normal(CVector3 vTriangle[]);

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

 


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// We can now use our 3DMath.cpp and 3DMath.h in any project now by simple
// including it.  We will want at least ALL of these functions from now on
// when ever we do any 3D programming (except for basic OpenGL concepts).
// It is important to know how to use these, even if you don't know how to
// code them if you had to.  As long as you know WHAT they do and what they are
// for, that's a start.  To be a decent 3D programmer though, you have to have 
// this stuff down pretty well where you want have to think about instances when you
// would use them.  If you need a perpendicular vector for something, like to strafe
// the camera left and right, you should immediately think CROSS PRODUCT.
// If this is really confusing for you, don't worry about it.  I wasn't a math
// man until I started actually putting what I learned in school to use.  Even though
// I had taken high calculus classes, I still had to relearn all this stuff when I went
// to 3D programming.  It's one thing to do something on paper, and it's another to actually
// put it to a practical use.  I think math is taught horribly in most schools.  It doesn't
// leave the average person with skills as much as it should.  Of course it is always
// up to the student to learn, but I think it could be taught it a way where you actually
// understand what you are learning and for what reasons and applications it holds.
//

#endif // _3D_MATH_H