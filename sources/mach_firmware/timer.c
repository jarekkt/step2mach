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


#define BASE_FREQ      100000   /* Hz             */
#define IO_FREQ          1000   /*  Hz             */
#define RESP_TOUT          25   /*  IO ticks      */


timer_coord_t       coords;
timer_buffer_t      buffer;
timer_engine_t      engine;
timer_jog_engine_t  engine_jog;


timer_frame_t       frames[TIMER_BUF_LEN];
timer_frame_t       frames_jog[3];



uint32_t            tick;
uint32_t            tick_watchdog;
int                 watchdog_active;


int                 allow_run         = 0;
int                 jog_stop_active   = 0;
int                 jog_abort_active  = 0;




unsigned int        response_timeout = RESP_TOUT;
uint32_t            frame_counter    = 0;



static inline void timer_eng_clear(void);
static inline void timer_eng_start(void);
static inline void timer_jog_start(void);



static void timer_reset_hw(void)
{
#if 0
    // Execute software reset
    RCONbits.SWDTEN = 1;
    CORCONbits.IPL3 = 1;
    while(1)
    {
        ;
    }  
#endif
}

int timer_execute_frame(uint8_t * frame_stream,int idx)
{
   int      ipl;
   int      ii;
   int      head;

#if 0
   // Copy item from DMA stream buffer
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
   response_timeout     = 0; 

   
   SET_AND_SAVE_CPU_IPL(ipl,7); 

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
            
     SET_CPU_IPL(ipl);  
#endif               
       
     return 0;    
}



static inline void timer_eng_clear(void)
{
  engine.Xac             = 0;
  engine.Yac             = 0;
  engine.Zac             = 0;
  engine.Aac             = 0;            
}

static inline void timer_jog_start(void)
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


static inline void timer_eng_prepare_new_vector(void)
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

static inline void timer_eng_start(void)
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


static inline void timer_gcode_mode(void)
{
    static int  next_step_pulse = 0;
    static int  phase;   
    int         is_active = 0;
    int32_t    tmp;

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


static inline void timer_jog_mode(void)
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


#if 0   

// Timer  interrupt routine
void __attribute__((interrupt,no_auto_psv)) _T1Interrupt( void )
{    


    PIN_DBG(1);

    if(buffer.jog_mode != 0)
    {
        timer_jog_mode();
    }
    else
    {
        timer_gcode_mode();
    }

    PIN_DBG(0);


    IFS0bits.T1IF = 0;


}

void __attribute__((interrupt,no_auto_psv))  _T2Interrupt( void )
{    
    Uint8_t    inputs = 0;
    static int hit_cntr = 0;
    
    IFS0bits.T2IF = 0;

    // System 1ms tick
    tick++;

    // Process receive frames
    serial_receive();

    if(watchdog_active == 0)
    {
        if( (tick - tick_watchdog) > WATCHDOG_JOG_TIMEOUT)
        {

            watchdog_active = 1;                        
            jog_stop_active = 1;
        }   
    }

    // Read inputs

    if(PORTBbits.RB5)inputs|= 0x01;
    if(PORTBbits.RB8)inputs|= 0x02;
    if(PORTBbits.RB7)inputs|= 0x04;
    if(PORTBbits.RB6)inputs|= 0x08;
    if(PORTBbits.RB9)inputs|= 0x20;

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




    // Send response ?
    if(response_timeout == 0)
    {
        serial_send_response();
        response_timeout = RESP_TOUT;
    }
    else
    {
       response_timeout--; 
    }    

    
}

#endif


void timer_init( void )
{


    memset(&coords,0,sizeof(coords));
    memset(&buffer,0,sizeof(buffer));
    memset(&engine,0,sizeof(engine));

    buffer.last_valid_id = -1;

#if 0
    // Timer 1 - base runner

    T1CON           =  0;      // Timer reset
    T1CONbits.TCKPS =  0;      // Fcy/1
    TMR1            =  0;   
    PR1             =  (FCY /1) / (BASE_FREQ * 2);  

    IFS0bits.T1IF   = 0;      // Reset Timer interrupt flag
    IPC0bits.T1IP   = 5;      // Timer Interrupt priority 
    IEC0bits.T1IE   = 1;      // Enable Timer interrupt

    T1CONbits.TON   = 1;

    // Timer 2 

    T2CON           =  0;      // Timer reset
    T2CONbits.TCKPS =  3;      // Fcy/256
    TMR2            =  0; 
    PR2             = (FCY /256) / (IO_FREQ);  
    
    IFS0bits.T2IF   =  0;      // Reset Timer interrupt flag
    IPC1bits.T2IP   =  2;      // Timer Interrupt priority 
    IEC0bits.T2IE   =  1;      // Enable Timer interrupt

    T2CONbits.TON   = 1;


    watchdog_active = 0;
#endif

}

