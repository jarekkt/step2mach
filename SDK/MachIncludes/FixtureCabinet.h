#pragma once

 

class FixtureCabinet
{
public:
	FixtureCabinet(void);
	~FixtureCabinet(void);

public:

   
  void Load(void);
  void Save(void);
  double GetOffset(int axis);
  void   SetOffset(int axis, double offset);
  void   SetFixture(int fixture);
  double GetTableOffset(int axis, int origin );
  void   SetTableOffset(int axis, int origin, double value );
  
  double convertI( double val );
  double ConvertO( double val );
};
