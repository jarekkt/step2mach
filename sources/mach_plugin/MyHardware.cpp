// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros�aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------


#include "stdafx.h"
#include "MyHardware.h"
#include "math.h"
#include "mach_pclib_protocol.h"


void MyHardwareClass::Init(double move_tick,const char * address)
{
	this->move_tick	   = move_tick;
	this->move_tick_ms = (uint32_t)(move_tick * 1000);

	memset(this->dev_address,0,sizeof(this->dev_address));
	strncpy(this->dev_address,address,sizeof(this->dev_address)-1);

	memset(steps_accumulated,0,sizeof(steps_accumulated));
	memset(steps_fw,0,sizeof(steps_fw));


}

void MyHardwareClass::Reinit(double move_tick,const char * address)
{
	Cnc_Communication_Disable();

	Init(move_tick,address);
	connected = Cnc_Communication_Enable(this->dev_address);

}

MyHardwareClass::MyHardwareClass(double move_tick,const char * address)
{
	Cnc_Init_Controller();

	Init(move_tick,address);
	connected = Cnc_Communication_Enable(this->dev_address);
}



MyHardwareClass::~MyHardwareClass()
{
	if(connected == 0)
	{
		Cnc_Communication_Disable();
	}

	Cnc_Exit_Controller();
}




void MyHardwareClass::StartJogMove(int32_t axis,int32_t distance,double JogVel, double JogAcc,uint64_t PinStopMask,uint64_t PinStopValue)
{
	timer_frame_t   frames[4];
	VectorSpeedType VS;
	int32_t ii;

	if(connected != 0)
	{
		return;
	}

	memset(frames,0,sizeof(frames));

	// Setup generic stop mask
	frames[0].header.command			= CMD_SET_JOG_BREAK;
	frames[0].header.in_mask			= 0;
	frames[0].data.stop_condition.mask  = PinStopMask;
	frames[0].data.stop_condition.value = PinStopValue;

	for(ii = 1;ii <=3;ii++)
	{
		frames[ii].header.command			= CMD_VECTORS_JOG;
		frames[ii].header.in_mask			= 0;
	}

	// Calculate jogging trajectory
	if(distance < 0)
	{
		VS.Cnt = -distance;
		VS.Dir = -1;
	}
	else
	{
		VS.Cnt = distance;
		VS.Dir = 1;
	}


    VS.V	  = JogVel; 
    VS.Vstart = 0.2*JogVel;
    VS.Vstop  = 0.2*JogVel; 
    VS.Acc	  = JogAcc;
    VS.Dcc	  = JogAcc;


	CalculateAxis(&VS);
	PrepareAxisData(axis,HARDWARE_FREQ,&VS,&(frames[1].data.step),&(frames[2].data.step),&(frames[3].data.step));
	Cnc_SetFrame(frames,4,0);
}


void MyHardwareClass::FinishJogMove(void)
{
	if(connected != 0)
	{
		return;
	}

	Cnc_SendCommand(CMD_STOP_JOG,0);
}

//
//
//	Stops device ( if connected), also reconnects if needed
//
//
int32_t MyHardwareClass::Reset(void)
{


	if(connected == 0)
	{
		Cnc_SendCommand(CMD_HALT,1);
		Cnc_Communication_Disable();
	}

	connected = Cnc_Communication_Enable(this->dev_address);

	return connected;
}




//
//
//	Stops movement, empties queus	 
//
//
void MyHardwareClass::Stop(void)
{	
	if(connected != 0)
	{
		return ;
	}

	Cnc_SendCommand(CMD_HALT,1);
}





//
//
//	 Calculates speed coeffifient for device move
//
//
uint32_t  MyHardwareClass::CalcSpeed(int32_t delta)
{
	uint64_t r;
	uint64_t v;


	if(delta == 0)return 0;

	if(delta < 0)delta = -delta;

	r =  (uint64_t)HARDWARE_FREQ/*khz*/ / (1000/move_tick_ms);
	v =  ((uint64_t)delta << 32) / r;
	return (uint32_t)v;
}



//
//
//	 Buffers and sends to device single move
//
//
int32_t   MyHardwareClass::AddMove(double ex,double ey,double ez,double ea,uint32_t line_id)
{
	timer_frame_t  frames[1];

	if(connected != 0)
	{
		return -1;
	}


	if(Cnc_GetBufferStatus() > 400)
	{
		return -1;
	}

	steps_accumulated[0] += ex;
	steps_accumulated[1] += ey;
	steps_accumulated[2] += ez;
	steps_accumulated[3] += ea;

	steps_fw[0]			= (int32_t)ex;
	steps_fw[1]			= (int32_t)ey;
	steps_fw[2]			= (int32_t)ez;
	steps_fw[3]			= (int32_t)ea;



	frames[0].header.command = CMD_VECTORS_RUN;
	frames[0].header.in_mask = 0;

	frames[0].data.step.line_id = line_id;
	frames[0].data.step.motion.gcode.Xs 	    = steps_fw[0];
	frames[0].data.step.motion.gcode.Ys 		= steps_fw[1];
	frames[0].data.step.motion.gcode.Zs 		= steps_fw[2];
	frames[0].data.step.motion.gcode.As 		= steps_fw[3];

	frames[0].data.step.motion.gcode.Xv		= CalcSpeed(frames[0].data.step.motion.gcode.Xs);
	frames[0].data.step.motion.gcode.Yv		= CalcSpeed(frames[0].data.step.motion.gcode.Ys);
	frames[0].data.step.motion.gcode.Zv		= CalcSpeed(frames[0].data.step.motion.gcode.Zs);
	frames[0].data.step.motion.gcode.Av		= CalcSpeed(frames[0].data.step.motion.gcode.As);

	if( (frames[0].data.step.motion.gcode.Xs != 0) ||  	 
		(frames[0].data.step.motion.gcode.Ys != 0) || 
		(frames[0].data.step.motion.gcode.Zs != 0) || 
		(frames[0].data.step.motion.gcode.As != 0) )
	{
		// Data frame
		Cnc_SetFrame(frames,1,0);
	}
	else
	{
		// Just delay frame
		frames[0].header.command = CMD_VECTORS_DELAY;
		frames[0].data.step.motion.delay.tick_delay = (uint32_t)(HARDWARE_FREQ * move_tick);   
		Cnc_SetFrame(frames,1,0);
	}

	return 0;
}



//
//
//	 Reports current GCODE line
//

uint32_t	 MyHardwareClass::GetLineId(void)
{
	timer_resp_t	status;

	if(connected != 0)
	{
		return 0xFFFFFFFF;
	}


	if(Cnc_Status_Get(&status) == 0)
	{
		return status.data.line_id;
	}
	else
	{
		return 0xFFFFFFFF;
	}
}






//
//
//	 Get digital inputs
//

uint64_t MyHardwareClass::GetInputs(void)
{
	if(connected != 0)
	{
		return 0;
	}

	return Cnc_GetInputs();
}


//
//
//	 Set cooridnates
//
//
void  MyHardwareClass::UpdateCoords(int32_t Xc,int32_t Yc,int32_t Zc, int32_t Ac)
{
	timer_coord_t   coords;

	steps_accumulated[0] = coords.Xc = Xc;
	steps_accumulated[1] = coords.Yc = Yc;
	steps_accumulated[2] = coords.Zc = Zc;
	steps_accumulated[3] = coords.Ac = Ac;

	Cnc_SetCoords(&coords);
}



//
//	 Set outputs
//
//
void MyHardwareClass::SetOutputs(uint64_t outputs,uint64_t mask)
{
	if(connected != 0)
	{
		return;
	}

	// TODO - check what happens for two ports and pin mapping

	Cnc_SetOutputs(outputs,mask);
}


//
//	 Reports if the device is running 
//
//

bool MyHardwareClass::IsIdle()
{
	timer_resp_t	status;

	if(connected != 0)
	{
		// Not connected, assume worst case
		return false;
	}

	if(Cnc_Status_Get(&status) == 0)
	{
		if(Cnc_IsQueEmpty() != 0 )
		{
			// Queue is not empty yet
			return false;
		}

		if(status.header.state == ENG_STATE_IDLE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		// We do not know, but assume worst case
		return false;
	}
}





//
//
//	Reads device status sent to PC
//
//
int32_t MyHardwareClass::ReadDeviceFeedback(int32_t * coords)
{
	timer_resp_t status;

	if(connected != 0)
	{
		return -1;
	}

	if(Cnc_Status_Get(&status) == 0)
	{
		coords[0] = status.data.coords.Xc;
		coords[1] = status.data.coords.Yc;
		coords[2] = status.data.coords.Zc;
		coords[3] = status.data.coords.Ac;

		return 0;
	}
	else
	{
		return -1;
	}
}




//
//
//	Maps pin function for the hardware
//
//
pin_hw_e MyHardwareClass::PinNr2Fn(int32_t pin_nr,int32_t polarity,int32_t pin_port)
{
	pin_hw_e result;

	if(pin_port == 1)
	{
		switch(pin_nr)
		{
			case 1: result = PIN_LPT1_01;break;
			case 2: result = PIN_LPT1_02;break;
			case 3: result = PIN_LPT1_03;break;
			case 4: result = PIN_LPT1_04;break;
			case 5: result = PIN_LPT1_05;break;
			case 6: result = PIN_LPT1_06;break;
			case 7: result = PIN_LPT1_07;break;
			case 8: result = PIN_LPT1_08;break;
			case 9: result = PIN_LPT1_09;break;
			case 14: result = PIN_LPT1_14;break;
			case 16: result = PIN_LPT1_16;break;
			case 17: result = PIN_LPT1_17;break;
			default: result = PIN_LPT_NONE;break;
		}
	}
	else if (pin_port == 2)
	{
		switch(pin_nr)
		{
			case 1: result = PIN_LPT2_01;break;
			case 2: result = PIN_LPT2_02;break;
			case 3: result = PIN_LPT2_03;break;
			case 4: result = PIN_LPT2_04;break;
			case 5: result = PIN_LPT2_05;break;
			case 6: result = PIN_LPT2_06;break;
			case 7: result = PIN_LPT2_07;break;
			case 8: result = PIN_LPT2_08;break;
			case 9: result = PIN_LPT2_09;break;
			case 14: result = PIN_LPT2_14;break;
			case 16: result = PIN_LPT2_16;break;
			case 17: result = PIN_LPT2_17;break;
			default: result = PIN_LPT_NONE;break;
		}
	}
	else
	{
		result = PIN_LPT_NONE;
	}

	if((pin_nr != PIN_LPT_NONE) && (polarity != 0))
	{
		result = (pin_hw_e)((int32_t)result+1); // This gives inversed polarity
	}

	return result;
}

//
//
//	Configures step/dir pins
//
//
int32_t MyHardwareClass::ConfigureStepPins(int32_t axis,int32_t step_pin_nr,int32_t step_polarity,int32_t step_pin_port,int32_t dir_pin_nr,int32_t dir_polarity,int32_t dir_pin_port)
{
	pin_map_e		step_pin;
	pin_map_e		dir_pin;
	timer_map_t     map;

	if(connected != 0)
	{
		return -1;
	}

	switch(axis)
	{
		case 0:
		{
			step_pin = PIN_MAP_X_STEP;
			dir_pin  = PIN_MAP_X_DIR;
		}break;

		case 1:
		{
			step_pin = PIN_MAP_Y_STEP;
			dir_pin  = PIN_MAP_Y_DIR;
		}break;

		case 2:
		{
			step_pin = PIN_MAP_Z_STEP;
			dir_pin  = PIN_MAP_Z_DIR;
		}break;

		case 3:
		{
			step_pin = PIN_MAP_A_STEP;
			dir_pin  = PIN_MAP_A_DIR;
		}break;

		default:
		{
			return -1;
		}
	}


	map.map_cnt = 2;
	map.pin_map[0] = step_pin;
	map.pin_hw[0]  = PinNr2Fn(step_pin_nr,step_polarity,step_pin_port);
	map.pin_map[1] = dir_pin;
	map.pin_hw[1]  = PinNr2Fn(dir_pin_nr,dir_polarity,dir_pin_port);

    Cnc_SetMap(&map,1);

	return 0;
}



//
//
//	Dumps internal variables into strings
//
//
int32_t MyHardwareClass::GetStats(char * buffer,int32_t buffer_size,int32_t line)
{
	int32_t result;
	timer_resp_t	status;

	switch(line)
	{
		case 0:
		{
			result = _snprintf(buffer,buffer_size,"Hardware connected : %d",
							   connected
			);
			buffer[buffer_size-1] = 0;
		}break;

		case 1:
		{
			result = _snprintf(buffer,buffer_size,"Hardware acum      :X(%12f) Y(%12f) Z(%12f) A(%12f)",
							  steps_accumulated[0],steps_accumulated[1],steps_accumulated[2],steps_accumulated[3]
			);
			buffer[buffer_size-1] = 0;
		}break;


		case 2:
		{
		   if(Cnc_Status_Get(&status) == 0)
		   {
			   result = _snprintf(buffer,buffer_size,"Hardware feedback  : X:%05d Y:%05d Z:%05d A:%05d  Tid:%03X In:0x%02x Fs:%03d Li:%03u S:%02x",
						 status.data.coords.Xc,
						 status.data.coords.Yc,
						 status.data.coords.Zc,
						 status.data.coords.Ac,
						 status.data.line_id,
						 status.data.inputs,
						 status.data.free_slots,
						 status.data.last_valid_id,
						 status.header.state

						 );
		   }
		   else
		   {
			     result = _snprintf(buffer,buffer_size,"Hardware feedback  : Not available                                                                    ");
		   }
		   buffer[buffer_size-1] = 0;
		}break;

		default:
		{
			buffer[0] = 0;
			result = 0;
		}
	}

	return result;
}




//
//
//	Calculate Jog data
//
//

void   MyHardwareClass::CalculateAxis(
    VectorSpeedType * VS
)
{

   if(VS->Cnt != 0)
   {
     if( (VS->Acc != 0) && (VS->Dcc != 0) )
	 {

		 VS->LineAcc.T = (VS->V-VS->Vstart) / VS->Acc;
		 VS->LineDcc.T = (VS->V-VS->Vstop)  / VS->Dcc;


		 VS->LineAcc.S  = VS->LineAcc.T * VS->Vstart +  VS->Acc * VS->LineAcc.T * VS->LineAcc.T /2;
		 VS->LineDcc.S  = VS->LineDcc.T * VS->Vstop  +  VS->Dcc * VS->LineDcc.T * VS->LineDcc.T /2;

		 if(VS->LineAcc.S + VS->LineDcc.S < VS->Cnt)
		 {
			VS->LineConst.S = VS->Cnt - VS->LineAcc.S - VS->LineDcc.S;
			VS->LineConst.T = (VS->LineConst.S / VS->V);

			VS->LineAcc.Cnt   = (uint32_t)VS->LineAcc.S;
			VS->LineDcc.Cnt   = (uint32_t)VS->LineDcc.S;
			VS->LineConst.Cnt  = VS->Cnt - (VS->LineAcc.Cnt + VS->LineDcc.Cnt);

			assert( fabs((double)(VS->V -( VS->Vstart + VS->Acc*VS->LineAcc.T))) < 0.1);

		 }
		 else
		 {
			double WA,WB,WC;

			VS->LineConst.T   = 0;
			VS->LineConst.S   = 0;
			VS->LineConst.Cnt = 0;

			WA = VS->Acc/2 + VS->Dcc/2 *(VS->Acc/VS->Dcc)*(VS->Acc/VS->Dcc);
			WB = VS->Vstart + (VS->Acc/VS->Dcc)*VS->Vstop;
			WC = -(double)VS->Cnt;


			VS->LineAcc.T   =  (-WB+sqrt(WB*WB-4*WA*WC))/(2*WA);
			VS->LineAcc.S   = VS->Acc*VS->LineAcc.T*VS->LineAcc.T/2 + VS->LineAcc.T*VS->Vstart;
			VS->LineAcc.Cnt = (uint32_t)VS->LineAcc.S;

			VS->LineDcc.T   = (VS->LineAcc.T*VS->Acc)/VS->Dcc;
			VS->LineDcc.S   = VS->Dcc*VS->LineDcc.T*VS->LineDcc.T/2 + VS->LineDcc.T*VS->Vstop;
			VS->LineDcc.Cnt = VS->Cnt - VS->LineAcc.Cnt;

			VS->V = VS->Vstart + VS->Acc*VS->LineAcc.T;

		 }
	   }
	   else
	   {
		   VS->Vstart        = 0;
		   VS->LineAcc.T     = 0;
		   VS->LineAcc.S     = 0;
		   VS->LineAcc.Cnt   = 0;

		   VS->Vstop		 = 0;
		   VS->LineDcc.T     = 0;
		   VS->LineDcc.S     = 0;
		   VS->LineDcc.Cnt   = 0;


		   VS->LineConst.Cnt  = VS->Cnt;
		   VS->LineConst.S    = VS->Cnt;
		   VS->LineConst.T    = (VS->LineConst.S / VS->V);  	

	   }
    }	
	else
	{
	   VS->LineAcc.T     = 0;
	   VS->LineAcc.S     = 0;
	   VS->LineAcc.Cnt   = 0;

	   VS->LineDcc.T     = 0;
	   VS->LineDcc.S     = 0;
	   VS->LineDcc.Cnt   = 0;

	   VS->LineConst.T     = 0;
	   VS->LineConst.S     = 0;
	   VS->LineConst.Cnt   = 0;

	}
}




void   MyHardwareClass::PrepareAxisData(
	int32_t						  axis,
	uint32_t                  Frequency,
    VectorSpeedType        *  Vs,
    timer_step_t		   *  AccVector,
	timer_step_t		   *  ConstVector,
	timer_step_t		   *  DccVector
)
{
   uint32_t  fract_end;

   memset(AccVector,0,sizeof(*AccVector));
   memset(DccVector,0,sizeof(*DccVector));
   memset(ConstVector,0,sizeof(*ConstVector));

   AccVector->line_id				= 0;
   AccVector->motion.jog.axis		= axis;
   AccVector->motion.jog.cnt		= Vs->LineAcc.Cnt;
   AccVector->motion.jog.dir		= Vs->Dir;
   AccVector->motion.jog.fract      = (unsigned long)(( (double)0xFFFFFFFF * Vs->Vstart )/(double)Frequency);

   ConstVector->line_id				= 1;
   ConstVector->motion.jog.axis		= axis;
   ConstVector->motion.jog.cnt		= Vs->LineConst.Cnt;
   ConstVector->motion.jog.dir		= Vs->Dir;	

   ConstVector->motion.jog.fract    = (unsigned long)(( (double)0xFFFFFFFF * Vs->V )/(double)Frequency);
   ConstVector->motion.jog.vfract   = 0;

   DccVector->line_id				= 2;
   DccVector->motion.jog.axis		= axis;
   DccVector->motion.jog.cnt		= Vs->LineDcc.Cnt;
   DccVector->motion.jog.dir		= Vs->Dir;
   DccVector->motion.jog.fract		= ConstVector->motion.jog.fract;

   fract_end					    = (unsigned long)(( (double)0xFFFFFFFF * Vs->Vstop )/(double)Frequency);

   if( (ConstVector->motion.jog.fract  !=  AccVector->motion.jog.fract ) && ( AccVector->motion.jog.cnt != 0))
   {
      AccVector->motion.jog.vfract   = (int32_t)(((int64_t)(uint64_t)ConstVector->motion.jog.fract-(int64_t)(uint64_t)AccVector->motion.jog.fract) /  AccVector->motion.jog.cnt);
	  if(AccVector->motion.jog.vfract   == 0)
	  {
		  AccVector->motion.jog.vfract  = 1;
	  }
	  AccVector->motion.jog.fract   += AccVector->motion.jog.vfract;
	  ConstVector->motion.jog.fract  = AccVector->motion.jog.fract  + AccVector->motion.jog.vfract * AccVector->motion.jog.cnt;
   }
   else
   {
      AccVector->motion.jog.vfract = 0;
   }

   if( ( ConstVector->motion.jog.fract !=  fract_end ) && ( DccVector->motion.jog.cnt != 0))
   {
	  DccVector->motion.jog.vfract = (int32_t)(((int64_t)(uint64_t)fract_end - (int64_t)(uint64_t)ConstVector->motion.jog.fract) / DccVector->motion.jog.cnt);
   }
   else
   {
      DccVector->motion.jog.vfract = 0;
   }

   
}