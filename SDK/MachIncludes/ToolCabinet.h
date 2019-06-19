#pragma once

struct Tool
{

 short tiptype;
 double diameter;
 double direction;
 CString description;
 double xoffset;
 double zoffset;
 double xWear;
 double zWear;
 double turretang;
 double toolradius;
 int id;
 bool front;
};

class ToolCabinet
{
public:
	ToolCabinet(void);
	~ToolCabinet(void);

public:

  Tool Tools[255];
  void Load(void);
  void Save(void);
  double GetDiam(int tool);
  double GetZOffset(int tool);
  double GetToolRadius(int tool);
  double GetXOffset(int tool);
  double GetXWear(int tool);
  double GetZWear(int tool);
  void SetDiam(int tool, double val);
  void SetZOffset(int tool, double val);
  void SetToolRadius(int tool, double val);
  void SetXOffset(int tool, double val);
  void SetXWear(int tool, double val);
  void SetZWear(int tool, double val);
  double convert( double val );
  double ConvertO( double val );
};
