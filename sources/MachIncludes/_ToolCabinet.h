// _ToolCabinet - replacement for class based header
//

#pragma once

struct _Tool
{
 short		tiptype;
 double		diameter;
 double		direction;
 TCHAR *	description;
 double		xoffset;
 double		zoffset;
 double		xWear;
 double		zWear;
 double		turretang;
 double		toolradius;
 int		id;
 bool		front;
};

struct _ToolCabinet
{
  _Tool		Tools[255];
};
