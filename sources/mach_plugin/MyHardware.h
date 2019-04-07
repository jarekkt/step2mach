// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------

#pragma once

#include "stdafx.h"


#include "mach_firmware.h"
#include "mach_pclib_protocol.h"



typedef struct
{
	double		T;
    double		S;
    uint32_t    Cnt;
}LineVectorType;

typedef struct
{
    uint32_t    Cnt;
    int32_t     Dir;

    double V;
    double Vstart;
    double Vstop;
    double Acc;
    double Dcc;

	LineVectorType LineAcc;
	LineVectorType LineConst;
	LineVectorType LineDcc;

}VectorSpeedType;

class MyHardwareClass
{
private:
	int       steps_fw[4];
	double    steps_accumulated[4];
	char      dev_address[128];
	double	  move_tick;
	uint32_t  move_tick_ms;
	int		  connected;	

	uint32_t  CalcSpeed(int delta);


	pin_hw_e PinNr2Fn(int pin_nr,int polarity);

	void	CalculateAxis(VectorSpeedType * VS);
	void	PrepareAxisData(int	axis,uint32_t Frequency,VectorSpeedType *  Vs,timer_step_t	*  AccVector,timer_step_t *  ConstVector,timer_step_t *  DccVector);

public:

	MyHardwareClass(double move_tick,const char * address);	
	virtual ~MyHardwareClass();


	// GCode moves processing
	uint32_t	GetLineId(void);
	int		    AddMove(double ex,double ey,double ez,double ea,uint32_t line_id);

	// IO control
	unsigned int GetInputs(void);
	void         SetOutputs(unsigned int outputs,unsigned int mask);
	void         UpdateCoords(int Xc,int Yc,int Zc, int Ac);

	// Jog
	void		StartJogMove(int axis,int distance,double  JogVel, double JogAcc,int PinStopMask,int PinStopValue);
	void		FinishJogMove(void);

	// Proces control
	int			ReadDeviceFeedback(int * coords);
	bool		IsIdle();
	int			ConfigureStepPins(int axis,int step_pin_nr,int step_polarity,int dir_pin_nr,int dir_polarity);
	int			Reset(void);
	void        Stop(void);

	// Debugging info
	int			GetStats(char * buffer,int buffer_size,int line);

};