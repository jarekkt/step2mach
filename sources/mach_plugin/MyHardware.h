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
	int32_t   steps_fw[4];
	double    steps_accumulated[4];
	char      dev_address[128];
	double	  move_tick;
	uint32_t  move_tick_ms;
	int32_t   connected;	

	uint32_t  CalcSpeed(int32_t delta);


	pin_hw_e PinNr2Fn(int32_t pin_nr,int32_t polarity,int32_t pin_port);

	void	CalculateAxis(VectorSpeedType * VS);
	void	PrepareAxisData(int32_t	axis,uint32_t Frequency,VectorSpeedType *  Vs,timer_step_t	*  AccVector,timer_step_t *  ConstVector,timer_step_t *  DccVector);


	void	Init(double move_tick,const char * address);
	
public:

	MyHardwareClass(double move_tick,const char * address);	
	virtual ~MyHardwareClass();

	void Reinit(double move_tick,const char * address);


	// GCode moves processing
	uint32_t	GetLineId(void);
	int32_t		AddMove(double ex,double ey,double ez,double ea,uint32_t line_id);

	// IO control
	uint64_t    GetInputs(void);
	void        SetOutputs(uint64_t outputs,uint64_t mask);
	void        UpdateCoords(int32_t Xc,int32_t Yc,int32_t Zc, int32_t Ac);

	// Jog
	void		StartJogMove(int32_t axis,int32_t distance,double  JogVel, double JogAcc,uint64_t PinStopMask,uint64_t PinStopValue);
	void		FinishJogMove(void);

	// Proces control
	int32_t		ReadDeviceFeedback(int32_t * coords);
	bool		IsIdle();
	int32_t		ConfigureStepPins(int32_t axis,int32_t step_pin_nr,int32_t step_polarity,int32_t step_pin_port,int32_t dir_pin_nr,int32_t dir_polarity,int32_t dir_pin_port);
	int32_t		Reset(void);
	void        Stop(void);

	// Debugging info
	int32_t		GetStats(char * buffer,int32_t buffer_size,int32_t line);

};