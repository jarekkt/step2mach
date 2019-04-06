// TrajStructs.h : header file
//

#pragma once

#define USE_CONST
#define USE_CCONST
#define USE_REF

#ifdef USE_CCONST
#define PM_CCONST const
#else
#define PM_CCONST
#endif

#ifdef USE_CONST
#define PM_CONST const
#else
#define PM_CONST
#endif

#ifdef USE_REF
#define PM_REF  &
#else
#define PM_REF
#endif

#define TC_IS_UNSET -1
#define TC_IS_DONE 1
#define TC_IS_ACCEL 2
#define TC_IS_CONST 3
#define TC_IS_DECEL 4
#define TC_IS_PAUSED 5
/* values for endFlag */
#define TC_TERM_COND_STOP 1
#define TC_TERM_COND_BLEND 2

#define TC_LINEAR 1
#define TC_CIRCULAR 2

#define TP_DEFAULT_QUEUE_SIZE 32
#define PM_PI      3.14159265358979323846
#define PM_PI_2    1.57079632679489661923
#define PM_PI_4    0.78539816339744830962
#define PM_2_PI    6.28318530717958647692

#define MMS 0
#define INCHES 1
 
typedef struct
{
  double x, y, z;                     /* this.x, etc. */

} PmCartesian;

/* PmSpherical */

typedef struct
{
  double theta, phi, r;

} PmSpherical;

/* PmCylindrical */

typedef struct
{
  double theta, r, z;

} PmCylindrical;

enum PM_AXIS { PM_X, PM_Y, PM_Z};

typedef PM_AXIS PmAxis;

typedef struct
{
  double s, x, y, z;

} PmRotationVector;

/* PmRotationMatrix */

typedef struct
{
  PmCartesian x, y, z;

} PmRotationMatrix;

/* PmQuaternion */

typedef struct
{
  double s, x, y, z;            /* this.s, etc. */

} PmQuaternion;

/* PmEulerZyz */

typedef struct
{
  double z, y, zp;

} PmEulerZyz;

/* PmEulerZyx */

typedef struct
{
  double z, y, x;

} PmEulerZyx;

/* PmRpy */

typedef struct
{
  double r, p, y;

} PmRpy;

/* PmPose */

typedef struct
{
  PmCartesian tran;
  PmQuaternion rot;

} PmPose;

typedef struct _EmcPose {
  PmCartesian tran;
  double a,b,c;
} EmcPose;
/* Homogeneous transform PmHomogeneous */

typedef struct
{
  PmCartesian tran;
  PmRotationMatrix rot;

} PmHomogeneous;
typedef struct
{
  PmPose start;         /* where motion was started */
  PmPose end;           /* where motion is going */
  PmCartesian uVec;            /* unit vector from start to end */
  PmQuaternion qVec;		/* unit of rotation */
  double tmag;
  double rmag;
  int tmag_is_greater_than_rmag;
  int tmag_zero;
  int rmag_zero;

} PmLine;

/* Generalized circle structure */

typedef struct
{
  PmCartesian center;
  PmCartesian normal;
  PmCartesian rTan;
  PmCartesian rPerp;
  PmCartesian rHelix;
  PmCartesian start,end;
  int turn;
  double radius;
  double angle;
  double spiral;
  PmPose begin;
  PmCartesian Icenter;
  EmcPose     Iend;
  PmCartesian Inormal;
  int         Iturn;
  EmcPose     Istart;
} PmCircle;


#define toCart(src,dst) {(dst)->x = (src).x; (dst)->y = (src).y; (dst)->z = (src).z;}

#define toCyl(src,dst) {(dst)->theta = (src).theta; (dst)->r = (src).r; (dst)->z = (src).z;}

#define toSph(src,dst) {(dst)->theta = (src).theta; (dst)->phi = (src).phi; (dst)->r = (src).r;}

#define toQuat(src,dst) {(dst)->s = (src).s; (dst)->x = (src).x; (dst)->y = (src).y; (dst)->z = (src).z;}

#define toRot(src,dst) {(dst)->s = (src).s; (dst)->x = (src).x; (dst)->y = (src).y; (dst)->z = (src).z;}

#define toMat(src,dst) {toCart((src).x, &((dst)->x)); toCart((src).y, &((dst)->y)); toCart((src).z, &((dst)->z));}

#define toEulerZyz(src,dst) {(dst)->z = (src).z; (dst)->y = (src).y; (dst)->zp = (src).zp;}

#define toEulerZyx(src,dst) {(dst)->z = (src).z; (dst)->y = (src).y; (dst)->x = (src).x;}

#define toRpy(src,dst) {(dst)->r = (src).r; (dst)->p = (src).p; (dst)->y = (src).y;}

#define toPose(src,dst) {toCart((src).tran, &((dst)->tran)); toQuat((src).rot, &((dst)->rot));}

#define toHom(src,dst) {toCart((src).tran, &((dst)->tran)); toMat((src).rot, &((dst)->rot));}

#define toLine(src,dst) {toPose((src).start, &((dst)->start)); toPose((src).end, &((dst)->end)); toCart((src).uVec, &((dst)->uVec));}

#define toCircle(src,dst) {toCart((src).center, &((dst)->center)); toCart((src).normal, &((dst)->normal)); toCart((src).rTan, &((dst)->rTan)); toCart((src).rPerp, &((dst)->rPerp)); toCart((src).rHelix, &((dst)->rHelix)); (dst)->radius = (src).radius; (dst)->angle = (src).angle; (dst)->spiral = (src).spiral;}

typedef PmCartesian       VECTOR;
typedef PmSpherical       SPHERICAL;
typedef PmCylindrical     CYLINDRICAL;
typedef PmQuaternion      QUATERNION;
typedef PmRotationMatrix  MATRIX;
typedef PmEulerZyz        ZYZ;
typedef PmEulerZyx        ZYX;
typedef PmRpy             RPY;
typedef PmPose            POSE;
typedef PmHomogeneous     HX;
typedef PmCircle          CIRCLE;
typedef PmLine            LINE;

typedef struct
{
  double cycleTime;
  double targetPos;             /* positive motion progession */
  double vMax;                  /* max velocity */
  double vScale;                /* scale factor for vMax */
  bool   override;              /* Velcoity scalable?? */
  double aMax;                  /* max accel */
  double preVMax;               /* vel from previous blend */
  double preAMax;               /* decel (negative) from previous blend */
  double vLimit;                /* abs vel limit, including scale */
  double toGo;
  double currentPos;
  double currentVel;
  double currentAccel;
  int tcFlag;                   /* TC_IS_DONE,ACCEL,CONST,DECEL*/
  int type;                     /* TC_LINEAR, TC_CIRCULAR */
  int id;                       /* id for motion segment */
  int termCond;                 /* TC_END_STOP,BLEND */
  PmLine line;
  PmLine line_abc;
  PmCircle circle;
  double tmag;			/* magnitude of translation */
  double abc_mag;			/* magnitude of rotation  */
  double tvMax;			/* maximum translational velocity */
  double taMax;              /* maximum translational accelleration */
  double abc_vMax;			/* maximum rotational velocity */
  double abc_aMax;		/* maximum rotational accelleration */
  PmCartesian unitCart;
  PmSpherical dirAngles;
  EmcPose     goalPos;
  double      LastScale;
  double      PartialVMax;
  double      PartialAMax; 
  bool        Comping;

} TC_STRUCT;

typedef struct
{
  TC_STRUCT *queue;             /* ptr to the tcs */
  int size;                     /* size of queue */
  int _len;                     /* number of tcs now in queue */
  int start, end;               /* indices to next to get, next to put */
  int allFull;                  /* flag meaning it's actually full */
} TC_QUEUE_STRUCT;

typedef struct
{
  TC_QUEUE_STRUCT queue;
  int queueSize;
  double cycleTime;
  double vMax;                  /* vel for subsequent moves */
  double vScale, vRestore;
  double aMax;
  double vLimit;                /* absolute upper limit on all vels */
  double wMax;			/* rotational velocity max  */
  double wDotMax;		/* rotational accelleration max */
  int nextId;
  int execId;
  int termCond;
  EmcPose currentPos;
  EmcPose goalPos;
  int done;
  int depth;                    /* number of total queued motions */
  int activeDepth;              /* number of motions blending */
  int aborting;
  int pausing;
  
} TP_STRUCT;


struct PM_CARTESIAN;       /* Cart */
struct PM_SPHERICAL;       /* Sph */
struct PM_CYLINDRICAL;     /* Cyl */

/* rotation types */
struct PM_ROTATION_VECTOR; /* Rot */
struct PM_ROTATION_MATRIX; /* Mat */
struct PM_QUATERNION;     /* Quat  */
struct PM_EULER_ZYZ;      /* Zyz */
struct PM_EULER_ZYX;      /* Zyx */
struct PM_RPY;            /* Rpy */

/* pose types */
struct PM_POSE;            /* Pose */
struct PM_HOMOGENEOUS;    /* Hom */





struct PM_CARTESIAN
{
  /* ctors/dtors */
  PM_CARTESIAN() {};
  PM_CARTESIAN(double _x, double _y, double _z);
  PM_CARTESIAN(PM_CCONST PM_CARTESIAN &cart); // added  7-May-1997 by WPS
  PM_CARTESIAN(PM_CONST PM_CYLINDRICAL PM_REF c); /* conversion */
  PM_CARTESIAN(PM_CONST PM_SPHERICAL PM_REF s); /* conversion */
  /* operators */
  double & operator [] (int n);             /* this[n] */
  PM_CARTESIAN operator = (PM_CARTESIAN v); /* this = v */
  /* data */
  double x, y, z;                     /* this.x, etc. */
};

struct PM_SPHERICAL
{
  /* ctors/dtors */
  PM_SPHERICAL() {};
  PM_SPHERICAL(PM_CCONST PM_SPHERICAL &s);
  PM_SPHERICAL(double _theta, double _phi, double _r);
  PM_SPHERICAL(PM_CONST PM_CYLINDRICAL PM_REF v); /* conversion */
  PM_SPHERICAL(PM_CONST PM_CARTESIAN PM_REF v); /* conversion */
  /* operators */
  double & operator [] (int n);             /* this[n] */
  PM_SPHERICAL operator = (PM_SPHERICAL s); /* this = s */
  /* data */
  double theta, phi, r;
};

struct PM_CYLINDRICAL
{
  /* ctors/dtors */
  PM_CYLINDRICAL() {};
  PM_CYLINDRICAL(PM_CCONST PM_CYLINDRICAL &c);
  PM_CYLINDRICAL(double _theta, double _r, double _z);
  PM_CYLINDRICAL(PM_CONST PM_CARTESIAN  PM_REF v); /* conversion */
  PM_CYLINDRICAL(PM_CONST PM_SPHERICAL  PM_REF v); /* conversion */
  /* operators */
  double & operator [] (int n);             /* this[n] */
  PM_CYLINDRICAL operator = (PM_CYLINDRICAL c); /* this = c */
  /* data */
  double theta, r, z;
};

struct PM_ROTATION_VECTOR
{
  /* ctors/dtors */
  PM_ROTATION_VECTOR() {};
  PM_ROTATION_VECTOR(PM_CCONST PM_ROTATION_VECTOR &r);
  PM_ROTATION_VECTOR(double _r, double _x, double _y, double _z);
  PM_ROTATION_VECTOR(PM_CONST PM_QUATERNION PM_REF q); /* conversion */
  /* operators */
  double &  operator [] (int n);        /* this[n] */
  PM_ROTATION_VECTOR operator = (PM_ROTATION_VECTOR r); /* this = r */
  /* data */
  double s, x, y, z;
};

struct PM_ROTATION_MATRIX
{
  /* ctors/dtors */
  PM_ROTATION_MATRIX() {};
  PM_ROTATION_MATRIX(PM_CCONST PM_ROTATION_MATRIX &mat); /* added  7-May-1997 by WPS */
  PM_ROTATION_MATRIX(double xx, double xy, double xz,
                     double yx, double yy, double yz,
                     double zx, double zy, double zz);
  PM_ROTATION_MATRIX(PM_CARTESIAN _x, PM_CARTESIAN _y, PM_CARTESIAN _z);
  PM_ROTATION_MATRIX(PM_CONST PM_ROTATION_VECTOR PM_REF v); /* conversion */
  PM_ROTATION_MATRIX(PM_CONST PM_QUATERNION PM_REF q);      /* conversion */
  PM_ROTATION_MATRIX(PM_CONST PM_EULER_ZYZ PM_REF zyz);     /* conversion */
  PM_ROTATION_MATRIX(PM_CONST PM_EULER_ZYX PM_REF zyx);     /* conversion */
  PM_ROTATION_MATRIX(PM_CONST PM_RPY PM_REF rpy);           /* conversion */
  /* operators */
  PM_CARTESIAN & operator [] (int n);   /* this[n] */
  PM_ROTATION_MATRIX operator = (PM_ROTATION_MATRIX m); /* this = m */
  /* data */
  PM_CARTESIAN x, y, z;
};



struct PM_QUATERNION
{
  /* ctors/dtors */
  PM_QUATERNION() {};
  PM_QUATERNION(PM_CCONST PM_QUATERNION &quat); /* added  7-May-1997 by WPS */
  PM_QUATERNION(double _s, double _x, double _y, double _z);
  PM_QUATERNION(PM_CONST PM_ROTATION_VECTOR PM_REF v); /* conversion */
  PM_QUATERNION(PM_CONST PM_ROTATION_MATRIX PM_REF m); /* conversion */
  PM_QUATERNION(PM_CONST PM_EULER_ZYZ PM_REF zyz);     /* conversion */
  PM_QUATERNION(PM_CONST PM_EULER_ZYX PM_REF zyx);     /* conversion */
  PM_QUATERNION(PM_CONST PM_RPY PM_REF rpy);           /* conversion */
  PM_QUATERNION(PM_AXIS  axis, double angle);  /* conversion */
  /* operators */
  double & operator [] (int n); /* this[n] */
  PM_QUATERNION operator = (PM_QUATERNION q);   /* this = q */
  /* functions */
  void axisAngleMult(PM_AXIS axis, double angle);
  /* data */
  double s, x, y, z;            /* this.s, etc. */
};

/* PM_EULER_ZYZ */

struct PM_EULER_ZYZ
{
  /* ctors/dtors */
  PM_EULER_ZYZ() {};
  PM_EULER_ZYZ(PM_CCONST PM_EULER_ZYZ &zyz);
  PM_EULER_ZYZ(double _z, double _y, double _zp);
  PM_EULER_ZYZ(PM_CONST PM_QUATERNION PM_REF q); /* conversion */
  PM_EULER_ZYZ(PM_CONST PM_ROTATION_MATRIX PM_REF m); /* conversion */
  /* operators */
  double & operator [] (int n);
  PM_EULER_ZYZ operator = (PM_EULER_ZYZ zyz);
  /* data */
  double z, y, zp;
};

/* PM_EULER_ZYX */

struct PM_EULER_ZYX
{
  /* ctors/dtors */
  PM_EULER_ZYX() {};
  PM_EULER_ZYX(PM_CCONST PM_EULER_ZYX &zyx);
  PM_EULER_ZYX(double _z, double _y, double _x);
  PM_EULER_ZYX(PM_CONST PM_QUATERNION PM_REF q); /* conversion */
  PM_EULER_ZYX(PM_CONST PM_ROTATION_MATRIX PM_REF m); /* conversion */
  /* operators */
  double & operator [] (int n);
  PM_EULER_ZYX operator = (PM_EULER_ZYX zyx);
  /* data */
  double z, y, x;
};

/* PM_RPY */

struct PM_RPY
{
  /* ctors/dtors */
  PM_RPY() {};
  PM_RPY(PM_CCONST PM_RPY &rpy);                /* added  7-May-1997 by WPS */
  PM_RPY(double _r, double _p, double _y);
  PM_RPY(PM_CONST PM_QUATERNION  PM_REF q);     /* conversion */
  PM_RPY(PM_CONST PM_ROTATION_MATRIX PM_REF m); /* conversion */
  /* operators */
  double & operator [] (int n);
  PM_RPY operator = (PM_RPY rpy);
  /* data */
  double r, p, y;
};

/* PM_POSE */

struct PM_POSE
{
  /* ctors/dtors */
  PM_POSE() {};
 
  PM_POSE(PM_CCONST PM_POSE &p);
  PM_POSE(PM_CARTESIAN v, PM_QUATERNION q);
  PM_POSE(double x, double y, double z,
          double s, double sx, double sy, double sz);
  PM_POSE(PM_CONST PM_HOMOGENEOUS PM_REF h);    /* conversion */
  /* operators */
  double & operator [] (int n); /* this[n] */
  PM_POSE operator = (PM_POSE p);       /* this = p */
  /* data */
  PM_CARTESIAN tran;
  PM_QUATERNION rot;
};

/* PM_HOMOGENEOUS */

struct PM_HOMOGENEOUS
{
  /* ctors/dtors */
  PM_HOMOGENEOUS() {};
  PM_HOMOGENEOUS(PM_CCONST PM_HOMOGENEOUS &h);
  PM_HOMOGENEOUS(PM_CARTESIAN v, PM_ROTATION_MATRIX m);
  PM_HOMOGENEOUS(PM_CONST PM_POSE PM_REF  p);   /* conversion */
  /* operators */
  PM_CARTESIAN & operator [] (int n); /* column vector */
  PM_HOMOGENEOUS operator = (PM_HOMOGENEOUS h);
  /* data ( [ 0 0 0 1 ] element is manually returned by [] if needed ) */
  PM_CARTESIAN tran;
  PM_ROTATION_MATRIX rot;
};
  static bool LeaveOneMove;
/* PM_LINE */

struct PM_LINE
{
  /* ctors/dtors */
  PM_LINE() {};
  PM_LINE(PM_CCONST PM_LINE &);
  /* functions */
  int init(PM_POSE start, PM_POSE end);
  int point(double len, PM_POSE * point);
  /* data */
  PM_POSE start;                /* where motion was started */
  PM_POSE end;          /* where motion is going */
  PM_CARTESIAN uVec;             /* unit vector from start to end */
};

/* PM_CIRCLE */

double pmlinelineangleCW( PmCartesian p1s,PmCartesian p1e,PmCartesian p2s,PmCartesian p2e);//added 12/18/05
double pmlinelineangleCCW( PmCartesian p1s,PmCartesian p1e,PmCartesian p2s,PmCartesian p2e);//added 12/18/05
double Arccosec(double A);//added 12/18/05


struct PM_CIRCLE
{
  /* ctors/dtors */
  PM_CIRCLE() {};
  PM_CIRCLE(PM_CCONST PM_CIRCLE &);
  /* functions */
  int init(PM_POSE start, PM_POSE end,
           PM_CARTESIAN center, PM_CARTESIAN normal,
           int turn);
  int point(double angle, PM_POSE * point);
  /* data */
  PM_CARTESIAN center;
  PM_CARTESIAN normal;
  PM_CARTESIAN rTan;
  PM_CARTESIAN rPerp;
  PM_CARTESIAN rHelix;
  double radius;
  double angle;
  double spiral;
};



//#define PI                PM_PI
#define PI_2              PM_PI_2
#define PI_4              PM_PI_4
//#define TWO_PI            PM_2_PI /* 2_PI invalid macro name */
/* overloaded  al functions */

#define pmClose(a, b, eps) ((fabs((a) - (b)) < (eps)) ? 1 : 0)
#define pmSq(x) ((x)*(x))

#define TO_DEG (180./PM_PI)
#define TO_RAD (PM_PI/180.)

#define DOUBLE_FUZZ 2.2204460492503131e-16
#define DOUBLECP_FUZZ 1.0842021724855044e-19
#define CART_FUZZ (0.000001)
/* how close a cartesian vector's magnitude must be for it to be considered
   a zero vector */

#define Q_FUZZ (.000001)
/* how close elements of a Q must be to be equal */

#define QS_FUZZ (.000001)
/* how close q.s is to 0 to be 180 deg rotation */

#define RS_FUZZ (.000001)
/* how close r.s is for a rotation vector to be considered 0 */

#define QSIN_FUZZ (.000001)
/* how close sin(a/2) is to 0 to be zero rotat */

#define V_FUZZ (.000001)
/* how close elements of a V must be to be equal */

#define SQRT_FUZZ (-.000001)
/* how close to 0 before math_sqrt() is error */

#define UNIT_VEC_FUZZ (.000001)
/* how close mag of vec must be to 1.00 */

#define UNIT_QUAT_FUZZ (.000001)
/* how close mag of quat must be to 1.00 */

#define UNIT_SC_FUZZ (.000001)
/* how close mag of sin, cos must be to 1.00 */

#define E_EPSILON (.000001)
/* how close second ZYZ euler angle must be to 0/PI for degeneration */

#define SINGULAR_EPSILON (.000001)
/* how close to zero the determinate of a matrix must be for singularity */

#define RPY_P_FUZZ (0.000001)
/* how close pitch is to zero for RPY to degenerate */

#define ZYZ_Y_FUZZ (0.000001)
/* how close Y is to zero for ZYZ Euler to degenerate */

#define ZYX_Y_FUZZ (0.000001)
/* how close Y is to zero for ZYX Euler to degenerate */

/* debug output printing */
  void pmPrintError(const char *fmt, ...);





/* line structure */



#define PM_ERR             -1   /* unspecified error */
#define PM_IMPL_ERR        -2   /* not implemented */
#define PM_NORM_ERR        -3   /* arg should have been norm */
#define PM_DIV_ERR         -4   /* divide by zero error */

/* compare operators */
  int operator == (PM_CARTESIAN v1, PM_CARTESIAN v2);
  int operator == (PM_QUATERNION q1, PM_QUATERNION q2);
  int operator == (PM_POSE p1, PM_POSE p2);
  int operator != (PM_CARTESIAN v1, PM_CARTESIAN v2);
  int operator != (PM_QUATERNION q1, PM_QUATERNION q2);
  int operator != (PM_POSE p1, PM_POSE p2);

/////////////////////////////////////////////////////////////////////////////
  PM_CARTESIAN operator + (PM_CARTESIAN v1, PM_CARTESIAN v2);
/* v - v */
  PM_CARTESIAN operator - (PM_CARTESIAN v1, PM_CARTESIAN v2);
/* v * s */
  PM_CARTESIAN operator * (PM_CARTESIAN v, double s);
/* s * v */
  PM_CARTESIAN operator * (double s, PM_CARTESIAN v);
/* v / s */
  PM_CARTESIAN operator / (PM_CARTESIAN v, double s);    // global operators

    PM_QUATERNION operator * (double s, PM_QUATERNION q);
/* q * s */
  PM_QUATERNION operator * ( PM_QUATERNION q, double s);
/* q / s */
  PM_QUATERNION operator / ( PM_QUATERNION q, double s);
/* q * v */
  PM_CARTESIAN operator * (PM_QUATERNION q, PM_CARTESIAN v);
/* q * q */
  PM_QUATERNION operator * (PM_QUATERNION q1, PM_QUATERNION q2);
/* m * m */
  PM_ROTATION_MATRIX operator * (PM_ROTATION_MATRIX m1, PM_ROTATION_MATRIX m2);

/* pose operators */

/* q * p */
  PM_POSE operator * (PM_QUATERNION q, PM_POSE p);
/* p * p */
  PM_POSE operator * (PM_POSE p1, PM_POSE p2);
/* p * v */
  PM_CARTESIAN operator * (PM_POSE p, PM_CARTESIAN v);
double TimeToMove(double Acc,double Vel,double Start,double End);//This is new for the SetVel accel

// global Posemath definitions
PmSpherical GetIntersecAngle(int Thistype,PmCartesian ThisStart,PmCartesian ThisEnd,
							 PmCartesian ThisCenter,bool ThisDir,int NextType,PmCartesian NextStart,
							 PmCartesian NextEnd,PmCartesian NextCenter,bool NextDir);
  int pmCartSphConvert(PmCartesian, PmSpherical *);
  int pmCartCylConvert(PmCartesian, PmCylindrical *);
  int pmSphCartConvert(PmSpherical, PmCartesian *);
  int pmSphCylConvert(PmSpherical, PmCylindrical *);
  int pmCylCartConvert(PmCylindrical, PmCartesian *);
  int pmCylSphConvert(PmCylindrical, PmSpherical *);
    int pmCartCartCompare(PmCartesian, PmCartesian);
  int pmCartCartDot(PmCartesian, PmCartesian, double *);
  int pmCartCartCross(PmCartesian, PmCartesian, PmCartesian *);
  int pmCartMag(PmCartesian, double *);
  int pmCartCartDisp(PmCartesian v1, PmCartesian v2, double *d);
  int pmCartCartAdd(PmCartesian, PmCartesian, PmCartesian *);
  int pmCartCartSub(PmCartesian, PmCartesian, PmCartesian *);
  int pmCartScalMult(PmCartesian, double, PmCartesian *);
  int pmCartScalDiv(PmCartesian, double, PmCartesian *);
  int pmCartNeg(PmCartesian, PmCartesian *);
  int pmCartUnit(PmCartesian v, PmCartesian * vout);
  int pmCartNorm(PmCartesian v, PmCartesian * vout);
  int pmCartIsNorm(PmCartesian v);
  int pmCartInv(PmCartesian, PmCartesian *);
  int pmCartCartProj(PmCartesian, PmCartesian, PmCartesian *);
  int pmCartPlaneProj(PmCartesian v, PmCartesian normal, PmCartesian * vout);

/* rotation functions */

/* quaternion functions */

  int pmQuatQuatCompare(PmQuaternion, PmQuaternion);
  int pmQuatMag(PmQuaternion q, double * d);
  int pmQuatNorm(PmQuaternion, PmQuaternion *);
  int pmQuatInv(PmQuaternion, PmQuaternion *);
  int pmQuatIsNorm(PmQuaternion);
  int pmQuatScalMult(PmQuaternion q, double s, PmQuaternion * qout);
  int pmQuatScalDiv(PmQuaternion q, double s, PmQuaternion * qout);
  int pmQuatQuatMult(PmQuaternion, PmQuaternion, PmQuaternion *);
  int pmQuatCartMult(PmQuaternion, PmCartesian, PmCartesian *);
  int pmQuatAxisAngleMult(PmQuaternion, PmAxis, double, PmQuaternion *);

/* rotation vector functions */

  int pmRotScalMult(PmRotationVector, double, PmRotationVector *);
  int pmRotScalDiv(PmRotationVector, double, PmRotationVector *);
  int pmRotIsNorm(PmRotationVector);
  int pmRotNorm(PmRotationVector, PmRotationVector *);

/* Rotation rep conversion functions */

  int pmAxisAngleQuatConvert(PmAxis, double, PmQuaternion *);

  int pmRotQuatConvert(PmRotationVector, PmQuaternion *);
  int pmRotMatConvert(PmRotationVector, PmRotationMatrix *);
  int pmRotZyzConvert(PmRotationVector, PmEulerZyz *);
  int pmRotZyxConvert(PmRotationVector, PmEulerZyx *);
  int pmRotRpyConvert(PmRotationVector, PmRpy *);

  int pmQuatRotConvert(PmQuaternion, PmRotationVector *);
  int pmQuatMatConvert(PmQuaternion, PmRotationMatrix *);
  int pmQuatZyzConvert(PmQuaternion, PmEulerZyz *);
  int pmQuatZyxConvert(PmQuaternion, PmEulerZyx *);
  int pmQuatRpyConvert(PmQuaternion, PmRpy *);

  int pmMatRotConvert(PmRotationMatrix, PmRotationVector *);
  int pmMatQuatConvert(PmRotationMatrix, PmQuaternion *);
  int pmMatZyzConvert(PmRotationMatrix, PmEulerZyz *);
  int pmMatZyxConvert(PmRotationMatrix, PmEulerZyx *);
  int pmMatRpyConvert(PmRotationMatrix, PmRpy *);

  int pmZyzRotConvert(PmEulerZyz, PmRotationVector *);
  int pmZyzQuatConvert(PmEulerZyz, PmQuaternion *);
  int pmZyzMatConvert(PmEulerZyz, PmRotationMatrix *);
  int pmZyzZyxConvert(PmEulerZyz, PmEulerZyx *);
  int pmZyzRpyConvert(PmEulerZyz, PmRpy *);

  int pmZyxRotConvert(PmEulerZyx, PmRotationVector *);
  int pmZyxQuatConvert(PmEulerZyx, PmQuaternion *);
  int pmZyxMatConvert(PmEulerZyx, PmRotationMatrix *);
  int pmZyxZyzConvert(PmEulerZyx, PmEulerZyz *);
  int pmZyxRpyConvert(PmEulerZyx, PmRpy *);

  int pmRpyRotConvert(PmRpy, PmRotationVector *);
  int pmRpyQuatConvert(PmRpy, PmQuaternion *);
  int pmRpyMatConvert(PmRpy, PmRotationMatrix *);
  int pmRpyZyzConvert(PmRpy, PmEulerZyz *);
  int pmRpyZyxConvert(PmRpy, PmEulerZyx *);

/* Combined rep conversion functions */

  int pmPoseHomConvert(PmPose p, PmHomogeneous * h);

  int pmHomPoseConvert(PmHomogeneous h, PmPose * p);

   
  void pmPerror(const char *fmt);
  double pmSqrt(double x);

//////////////////////////////////////////////////////////////////

  double dot(PM_CARTESIAN v1, PM_CARTESIAN v2);
/* cross */
PM_CARTESIAN cross(PM_CARTESIAN v1, PM_CARTESIAN v2);

/* norm */
  PM_CARTESIAN norm(PM_CARTESIAN v);
  PM_QUATERNION norm(PM_QUATERNION q);
  PM_ROTATION_VECTOR norm(PM_ROTATION_VECTOR r);
  PM_ROTATION_MATRIX norm(PM_ROTATION_MATRIX m);


/* unit */
  PM_CARTESIAN unit(PM_CARTESIAN v);
  PM_QUATERNION unit(PM_QUATERNION q);
  PM_ROTATION_VECTOR unit(PM_ROTATION_VECTOR r);
  PM_ROTATION_MATRIX unit(PM_ROTATION_MATRIX m);


/* isNorm */
  int isNorm(PM_CARTESIAN v);
  int isNorm(PM_QUATERNION q);
  int isNorm(PM_ROTATION_VECTOR r);
  int isNorm(PM_ROTATION_MATRIX m);

/* mag */
  double mag(PM_CARTESIAN v);

/* disp */
  double disp(PM_CARTESIAN v1, PM_CARTESIAN v2);

/* inv */
  PM_CARTESIAN inv(PM_CARTESIAN v);
  PM_ROTATION_MATRIX inv(PM_ROTATION_MATRIX m);
  PM_QUATERNION inv(PM_QUATERNION q);
  PM_POSE inv(PM_POSE p);
  PM_HOMOGENEOUS inv(PM_HOMOGENEOUS h);

/* project */
  PM_CARTESIAN proj(PM_CARTESIAN v1, PM_CARTESIAN v2);

/* overloaded arithmetic functions */

/* unary +, - for translation, rotation, pose */
  PM_CARTESIAN operator + (PM_CARTESIAN v);
  PM_CARTESIAN operator - (PM_CARTESIAN v);
  PM_QUATERNION operator + (PM_QUATERNION q);
  PM_QUATERNION operator - (PM_QUATERNION q);
  PM_POSE operator + (PM_POSE p);
  PM_POSE operator - (PM_POSE p);



/* translation +, -, scalar *, - */
/* v + v */


/* rotation * by scalar, translation, and rotation */

/* s * q */

  void vector_rotate_2d ( double v1[2], double angle, double v2[2] );
  int pmMatNorm(PmRotationMatrix m, PmRotationMatrix * mout);
  int pmMatIsNorm(PmRotationMatrix m);
  int pmMatInv(PmRotationMatrix m, PmRotationMatrix *mout);
  int pmMatCartMult(PmRotationMatrix m, PmCartesian v, PmCartesian * vout);
  int pmMatMatMult(PmRotationMatrix m1, PmRotationMatrix m2, PmRotationMatrix * mout);

/* pose functions*/

  int pmPosePoseCompare(PmPose, PmPose);
  int pmPoseInv(PmPose p, PmPose *);
  int pmPoseCartMult(PmPose, PmCartesian, PmCartesian *);
  int pmPosePoseMult(PmPose, PmPose, PmPose *);

/* homogeneous functions */
  int pmHomInv(PmHomogeneous, PmHomogeneous *);

/* line functions */

  int pmLineInit(PmLine * line,PmPose start, PmPose end);
  int pmLinePoint(PmLine * line,double len, PmPose * point);

/* circle functions */

  int pmCircleInit(PmCircle * circle,
                        PmPose start, PmPose end,
                        PmCartesian center, PmCartesian normal,
                        int turn);
  int pmCirclePoint(PmCircle * circle,
                         double angle, PmPose * point);
