// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jarosaw Karwik
   E-Mail:     jaroslaw.karwik(at)gmail.com
   
**/
// ----------------------------------------------------------------------------



#include "stdint.h"
#include "../mach_common/mach_firmware.h"
#include "timer.h"
#include "serial.h"
#include "pinctrl.h"

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"



#define BASE_FREQ        50000   /*  Hz             */
#define IO_FREQ           1000   /*  Hz             */


timer_coord_t       coords;
timer_buffer_t      buffer;
timer_engine_t      engine;
timer_jog_engine_t  engine_jog;


timer_frame_t       frames[TIMER_BUF_LEN];
timer_frame_t       frames_jog[3];


uint32_t            tick;
uint32_t            tick_watchdog;
int32_t             watchdog_active;


int32_t             allow_run         = 0;
int32_t             jog_stop_active   = 0;
int32_t             jog_abort_active  = 0;


uint32_t            frame_counter    = 0;


static  void timer_eng_clear(void);
static  void timer_eng_start(void);
static  void timer_jog_start(void);



typedef struct
{
  TIM_HandleTypeDef  hTim4;
  TIM_HandleTypeDef  hTim3;

  uint32_t           tim_clock;
}timer_srv_t;

timer_srv_t tsrv;


static void timer_reset_hw(void)
{
  NVIC_SystemReset();
}

int timer_execute_frame(const uint8_t * frame_stream,int idx)
{
   int      ii;
   int      head;


   // Copy item from stream buffer
   head = buffer.slots_head;

   memcpy(&frames[head],frame_stream,sizeof(frames[head]));

   if( idx ==0 )
   {
     if(frames[head].header.id == buffer.last_valid_id)
     {
            // Repeated frame, ignore it
            return -1;
      }
   }

   buffer.last_valid_id = frames[head].header.id;


  
   // kick watchdog   
   tick_watchdog   = tick; 
   watchdog_active = 0;    
    
   switch(frames[head].header.command)
   {
       case CMD_START:
       {            
          // start processing buffered data   
          timer_eng_start();            
       }break;
                           
       case CMD_HALT:
       {
           // clear buffers                 
           allow_run         = 0; 
           jog_abort_active  = 1;
       }break;

       case CMD_VECTORS_DELAY:
       case CMD_VECTORS_BUFFER:
       {       
           // buffer data - nothing to do
           buffer.slots_head = (head+1) % TIMER_BUF_LEN;
           buffer.slots_used++;
       }break;
               
       case CMD_VECTORS_RUN:
       {
           // buffer data and execute run
           buffer.slots_head = (head+1) % TIMER_BUF_LEN;                       
           buffer.slots_used++;
           timer_eng_start();                            
       }break;

       case CMD_STOP_JOG:
       {
           // if we jog - stop it
           jog_stop_active = 1;
       }break;


       case CMD_VECTORS_JOG:
       {
           if(frames[head].data.step.line_id < 3)
           {
              memcpy(&frames_jog[frames[head].data.step.line_id],&frames[head],sizeof(timer_frame_t));
              if(frames[head].data.step.line_id == 2)
              {
                 timer_jog_start();
              }
           }

       }break;
       
       case CMD_SET_JOG_BREAK:
       {
           buffer.jog_in_mask  = frames[head].data.stop_condition.mask;
           buffer.jog_in_value = frames[head].data.stop_condition.value;         
       }break;
       
       case CMD_OUTPUTS:
       {
           pinctrl_set_outputs(frames[head].data.io.outputs,frames[head].data.io.mask) ;         
       }break;

                
       case CMD_MAP:
       {
            // remap outputs
            for(ii =0; ii < frames[head].data.map.map_cnt;ii++)
            {
                   pinctrl_map(
                        (pin_map_e) frames[head].data.map.pin_map[ii],
                        (pin_hw_e)  frames[head].data.map.pin_hw[ii]
                   );
            }        
     
       }break;

       case CMD_COORDS:
       {
            // set coords
            coords = frames[head].data.coord;
       }break;


       case CMD_RESET:
       {
            timer_reset_hw();
       }break;


       case CMD_WATCHDOG:
       {
            // Ignore as watchdog timer was already kicked
       }break;
            
       default:
       {
            // Ignore                
       }break;
                    
     }
          
       
     return 0;    
}



static  void timer_eng_clear(void)
{
  engine.Xac             = 0;
  engine.Yac             = 0;
  engine.Zac             = 0;
  engine.Aac             = 0;            
}

static  void timer_jog_start(void)
{
    memset(&engine_jog,0,sizeof(engine_jog));

    if( (buffer.current_step != NULL)|| (buffer.current_jog != 0))
    {
        // We do not jog while gcode movement is in progress nor when other jog is in progress
        return;
    }

    // Check which axis we use
    switch(frames_jog[0].data.step.motion.jog.axis)
    {
        case 0:
        {
            engine_jog.coord_ptr = &coords.Xc;
            engine_jog.pulse     = 0x01;
            if(frames_jog[0].data.step.motion.jog.dir < 0)
            {
                pinctrl_clear(PIN_MAP_X_DIR);
                
            }
            else
            {
                pinctrl_set(PIN_MAP_X_DIR);
            }
        }break;
        
        case 1:
        {
            engine_jog.coord_ptr = &coords.Yc;
            engine_jog.pulse     = 0x02;                       
            if(frames_jog[0].data.step.motion.jog.dir < 0)
            {
                pinctrl_clear(PIN_MAP_Y_DIR);
            }
            else
            {
                pinctrl_set(PIN_MAP_Y_DIR);
            }            
        }break;
        
        case 2:
        {
            engine_jog.coord_ptr = &coords.Zc;
            engine_jog.pulse     = 0x04;
            if(frames_jog[0].data.step.motion.jog.dir < 0)
            {
                pinctrl_clear(PIN_MAP_Z_DIR);
            }
            else
            {
                pinctrl_set(PIN_MAP_Z_DIR);
            }            
        }break;
        
        case 3:
        {
           engine_jog.coord_ptr = &coords.Ac;
           engine_jog.pulse     = 0x08;           
           if(frames_jog[0].data.step.motion.jog.dir < 0)
           {
                pinctrl_clear(PIN_MAP_A_DIR);
           }
           else
           {
               pinctrl_set(PIN_MAP_A_DIR);
           }           
        }break;
        
        default:
        {
            return; // Error ?!
        }
    };


    if(frames_jog[0].data.step.motion.jog.dir < 0)
    {
       engine_jog.dir_neg = 1;
    }
    else
    {
       engine_jog.dir_neg = 0;
    }

    jog_abort_active = 0;
    jog_stop_active  = 0;
    
    buffer.current_jog = &frames_jog[0]; 
    buffer.jog_mode = 1;
    
}


static  void timer_eng_prepare_new_vector(void)
{
    if( (buffer.current_step->header.command == CMD_VECTORS_DELAY) )
    {
        // Dummy vestors which do not update coords - used for idle delay only
        return;
    }
       
    coords.Xc += buffer.current_step->data.step.motion.gcode.Xs;
    if(buffer.current_step->data.step.motion.gcode.Xs < 0)
    {   
        buffer.current_step->data.step.motion.gcode.Xs = -buffer.current_step->data.step.motion.gcode.Xs;
        pinctrl_clear(PIN_MAP_X_DIR);
    }
    else
    {
        pinctrl_set(PIN_MAP_X_DIR);
    }
    
    coords.Yc += buffer.current_step->data.step.motion.gcode.Ys;
    if(buffer.current_step->data.step.motion.gcode.Ys < 0)
    {
        buffer.current_step->data.step.motion.gcode.Ys = -buffer.current_step->data.step.motion.gcode.Ys;
        pinctrl_clear(PIN_MAP_Y_DIR);
    }
    else
    {
        pinctrl_set(PIN_MAP_Y_DIR);
    }
    
    coords.Zc += buffer.current_step->data.step.motion.gcode.Zs;
    if(buffer.current_step->data.step.motion.gcode.Zs < 0)
    {
        buffer.current_step->data.step.motion.gcode.Zs = -buffer.current_step->data.step.motion.gcode.Zs;
        pinctrl_clear(PIN_MAP_Z_DIR);
    }
    else
    {
        pinctrl_set(PIN_MAP_Z_DIR);
    }
    
    coords.Ac += buffer.current_step->data.step.motion.gcode.As;
    if(buffer.current_step->data.step.motion.gcode.As < 0)
    {
        buffer.current_step->data.step.motion.gcode.Zs = -buffer.current_step->data.step.motion.gcode.As;
        pinctrl_clear(PIN_MAP_A_DIR);
    }
    else
    {
        pinctrl_set(PIN_MAP_A_DIR);
    }

}

static  void timer_eng_start(void)
{
   if(buffer.current_step == NULL )
   {
     // New vector start 
     if(buffer.slots_head != buffer.slots_tail)
     {
            buffer.current_step   =  &frames[buffer.slots_tail];
            timer_eng_prepare_new_vector();
            timer_eng_clear();
            allow_run = 1;
     }
   }
   else
   {        
       allow_run = 1;
   }
}


static  void timer_gcode_mode(void)
{
    static int  next_step_pulse = 0;
    static int  phase;   
    int         is_active = 0;
    uint32_t    tmp;

    if(phase++ & 0x01)
    {        

      pinctrl_clear(PIN_MAP_X_STEP);
      pinctrl_clear(PIN_MAP_Y_STEP);
      pinctrl_clear(PIN_MAP_Z_STEP);
      pinctrl_clear(PIN_MAP_A_STEP);

      if(buffer.current_step != NULL )
      {
          if( (buffer.current_step->header.command == CMD_VECTORS_DELAY) )
          {
              if(buffer.current_step->data.step.motion.delay.tick_delay != 0)
              {
                buffer.current_step->data.step.motion.delay.tick_delay--;
                is_active = 1;               
              }
          }
          else  
          {

            
              if(buffer.current_step->data.step.motion.gcode.Xs != 0)
              {
                  tmp = engine.Xac;
                  engine.Xac += buffer.current_step->data.step.motion.gcode.Xv;
                  if(engine.Xac < tmp)
                  {
                      next_step_pulse |= 0x01;
                      buffer.current_step->data.step.motion.gcode.Xs--;
                  }
                  is_active = 1;
              }

              if(buffer.current_step->data.step.motion.gcode.Ys != 0)
              {
                  tmp = engine.Yac;
                  engine.Yac += buffer.current_step->data.step.motion.gcode.Yv;
                  if(engine.Yac < tmp)
                  {
                      next_step_pulse |= 0x02;
                      buffer.current_step->data.step.motion.gcode.Ys--;
                  }
                  is_active = 1;
              }
              
              if(buffer.current_step->data.step.motion.gcode.Zs != 0)
              {
                  tmp = engine.Zac;
                  engine.Zac += buffer.current_step->data.step.motion.gcode.Zv;
                  if(engine.Zac < tmp)
                  {
                      next_step_pulse |= 0x04;
                      buffer.current_step->data.step.motion.gcode.Zs--;
                  }
                  is_active = 1;
              }
              
              if(buffer.current_step->data.step.motion.gcode.As != 0)
              {
                  tmp = engine.Aac;
                  engine.Aac += buffer.current_step->data.step.motion.gcode.Av;
                  if(engine.Aac < tmp)
                  {
                      next_step_pulse |= 0x08;
                      buffer.current_step->data.step.motion.gcode.As--;
                  }
                  is_active = 1;
              }
          }
                      
          if(is_active == 0)
          {
              // We must be allowed to run
              if(allow_run == 0)
              {
                  buffer.slots_tail   = buffer.slots_head;
                  buffer.current_step = NULL;                     
              }
              else
              {
                   // Take next slot                  
                   buffer.slots_used--;
                      
                   // update circular buffer
                   buffer.slots_tail =  (buffer.slots_tail + 1)%TIMER_BUF_LEN;

                   // look for next vector frame
                   if(buffer.slots_tail != buffer.slots_head)
                   {               
                        buffer.current_step = &frames[buffer.slots_tail];
                        timer_eng_prepare_new_vector();
                        timer_eng_clear();
                    }                
                    else
                    {
                        buffer.current_step = NULL; 
                    }                      
              }
          }
      }
  }
  else    
  {
      if(next_step_pulse & 0x01) pinctrl_set(PIN_MAP_X_STEP);
      if(next_step_pulse & 0x02) pinctrl_set(PIN_MAP_Y_STEP);
      if(next_step_pulse & 0x04) pinctrl_set(PIN_MAP_Z_STEP);        
      if(next_step_pulse & 0x08) pinctrl_set(PIN_MAP_A_STEP);        
      next_step_pulse = 0;
  }

  
}


static  void timer_jog_mode(void)
{
    static int  next_step_pulse = 0;
    static int  phase;   
    uint32_t    tmp;

    if(phase++ & 0x01)
    {        
      pinctrl_clear(PIN_MAP_X_STEP);
      pinctrl_clear(PIN_MAP_Y_STEP);
      pinctrl_clear(PIN_MAP_Z_STEP);
      pinctrl_clear(PIN_MAP_A_STEP);


      if(jog_abort_active != 0)
      {
          buffer.current_jog = NULL;
          buffer.jog_mode    = 0;
          return;
      }

      if(jog_stop_active != 0)
      {
          jog_stop_active = 0;

          if(buffer.current_jog->data.step.line_id == 1)
          {
              // Switch to dcc phase
              engine_jog.accumulator = 0;
              buffer.current_jog = &frames_jog[2];
          }
          else if(buffer.current_jog->data.step.line_id == 0)
          {
             // Jump to proper point in dcc  phase
             buffer.current_jog = &frames_jog[2];            
             buffer.current_jog->data.step.motion.jog.cnt    =  buffer.current_jog->data.step.motion.jog.cnt - frames_jog[0].data.step.motion.jog.cnt;
             buffer.current_jog->data.step.motion.jog.fract  += buffer.current_jog->data.step.motion.jog.vfract * frames_jog[0].data.step.motion.jog.cnt;

             if( buffer.current_jog->data.step.motion.jog.cnt > 0)
             {
                // Some margin
                buffer.current_jog->data.step.motion.jog.cnt--;
             }
          }
          else
          {
             // Already dcc phase - nothing to do
          }

          
      }


      if(buffer.current_jog->data.step.motion.jog.cnt > 0)
      {
         
        
         tmp = engine_jog.accumulator;
         
         engine_jog.accumulator += buffer.current_jog->data.step.motion.jog.fract;
         if(engine_jog.accumulator < tmp)
         {
            buffer.current_jog->data.step.motion.jog.cnt--;
            next_step_pulse = engine_jog.pulse;
            if(engine_jog.dir_neg)
            {
               (*engine_jog.coord_ptr)--;
            }
            else
            {
               (*engine_jog.coord_ptr)++; 
            }
            buffer.current_jog->data.step.motion.jog.fract += buffer.current_jog->data.step.motion.jog.vfract;
         }            
      }
      else
      {
          engine_jog.accumulator = 0;
          if(buffer.current_jog->data.step.line_id < 2)
          {
            buffer.current_jog = &frames_jog[buffer.current_jog->data.step.line_id + 1];
          }
          else
          {
            buffer.current_jog = NULL;
            buffer.jog_mode    = 0;
          }
        
      }
    }
    else    
    {
        if(next_step_pulse & 0x01) pinctrl_set(PIN_MAP_X_STEP);
        if(next_step_pulse & 0x02) pinctrl_set(PIN_MAP_Y_STEP);
        if(next_step_pulse & 0x04) pinctrl_set(PIN_MAP_Z_STEP);        
        if(next_step_pulse & 0x08) pinctrl_set(PIN_MAP_A_STEP);        
        next_step_pulse = 0;
    }
    
}


void TIM3_IRQHandler()  
{
    __HAL_TIM_CLEAR_IT(&tsrv.hTim3, TIM_IT_UPDATE);

    if(buffer.jog_mode != 0)
    {
        timer_jog_mode();
    }
    else
    {
        timer_gcode_mode();
    }
}


void TIM4_IRQHandler() 
{
    
    uint32_t    inputs = 0;
    static int hit_cntr = 0;
    
    __HAL_TIM_CLEAR_IT(&tsrv.hTim4, TIM_IT_UPDATE);

    // System 1ms tick
    tick++;


    if(watchdog_active == 0)
    {
        if( (tick - tick_watchdog) > WATCHDOG_JOG_TIMEOUT)
        {

            watchdog_active = 1;                        
            jog_stop_active = 1;
        }   
    }

    // Read inputs
    inputs = pinctrl_read();

    buffer.inputs = inputs;

    if(buffer.jog_mode != 0)
    {
        if(buffer.jog_in_mask != 0)
        {
            if( (inputs & buffer.jog_in_mask ) == buffer.jog_in_value )
            {
                hit_cntr++;
    
                if(hit_cntr > 5 )
                {
                   // Jog stop condition fulfilled
                   jog_abort_active = 1; 
                }
            } 
            else
            {
                hit_cntr = 0;
            }
        }
    }


}



void timer_init( void )
{
#define TIMER_SRV_1MHZ  1000000

    memset(&coords,0,sizeof(coords));
    memset(&buffer,0,sizeof(buffer));
    memset(&engine,0,sizeof(engine));

    memset(&tsrv,0,sizeof(tsrv));

    buffer.last_valid_id = -1;

    // Becasue of TIM_CLOCKDIVISION_DIV4 and static x2
    tsrv.tim_clock = 2 * SystemCoreClock / 4;

    // Main pulse clock
     __HAL_RCC_TIM3_CLK_ENABLE();

    tsrv.hTim3.Instance           = TIM3;
    tsrv.hTim3.Init.Prescaler     = (tsrv.tim_clock/ TIMER_SRV_1MHZ) - 1;
    tsrv.hTim3.Init.CounterMode   = TIM_COUNTERMODE_UP;
    tsrv.hTim3.Init.Period        = TIMER_SRV_1MHZ  / (BASE_FREQ * 2);
    tsrv.hTim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
    HAL_TIM_Base_Init(&tsrv.hTim3);
    HAL_TIM_Base_Start_IT(&tsrv.hTim3); 
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    // IO clock 
    __HAL_RCC_TIM4_CLK_ENABLE();

    tsrv.hTim4.Instance           = TIM4;
    tsrv.hTim4.Init.Prescaler     = (tsrv.tim_clock/ TIMER_SRV_1MHZ ) - 1;
    tsrv.hTim4.Init.CounterMode   = TIM_COUNTERMODE_UP;
    tsrv.hTim4.Init.Period        = TIMER_SRV_1MHZ / IO_FREQ;
    tsrv.hTim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
    HAL_TIM_Base_Init(&tsrv.hTim4);
    HAL_TIM_Base_Start_IT(&tsrv.hTim4); 
    HAL_NVIC_SetPriority(TIM4_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);

    watchdog_active = 0;
}


