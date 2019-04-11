// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jarosaw Karwik
   E-Mail:     jaroslaw.karwik(at)gmail.com
   
**/
// ----------------------------------------------------------------------------


#ifndef MACH_FIRMWARE_H
#define MACH_FIRMWARE_H


#define VERSION_NR              0x11
#define WATCHDOG_JOG_TIMEOUT    400
#define WATCHDOG_COMM_TIMEOUT   250
#define HARDWARE_FREQ           100000 /*Hz*/

typedef enum
{
    PIN_LPT_NONE = 0,      

    PIN_LPT1_01,      
    PIN_LPT1_01_INV,      
    PIN_LPT1_02,      
    PIN_LPT1_02_INV,      
    PIN_LPT1_03,      
    PIN_LPT1_03_INV,      
    PIN_LPT1_04,      
    PIN_LPT1_04_INV,      
    PIN_LPT1_05,      
    PIN_LPT1_05_INV,      
    PIN_LPT1_06,      
    PIN_LPT1_06_INV,      
    PIN_LPT1_07,      
    PIN_LPT1_07_INV,      
    PIN_LPT1_08,      
    PIN_LPT1_08_INV,      
    PIN_LPT1_09,      
    PIN_LPT1_09_INV,  
    PIN_LPT1_10,      
    PIN_LPT1_10_INV,  
    PIN_LPT1_11,      
    PIN_LPT1_11_INV,  
    PIN_LPT1_12,      
    PIN_LPT1_12_INV,  
    PIN_LPT1_13,      
    PIN_LPT1_13_INV,          
    PIN_LPT1_14,
    PIN_LPT1_14_INV,
    PIN_LPT1_16,
    PIN_LPT1_16_INV,
    PIN_LPT1_17,
    PIN_LPT1_17_INV,

    PIN_LPT2_01,      
    PIN_LPT2_01_INV,      
    PIN_LPT2_02,      
    PIN_LPT2_02_INV,      
    PIN_LPT2_03,      
    PIN_LPT2_03_INV,      
    PIN_LPT2_04,      
    PIN_LPT2_04_INV,      
    PIN_LPT2_05,      
    PIN_LPT2_05_INV,      
    PIN_LPT2_06,      
    PIN_LPT2_06_INV,      
    PIN_LPT2_07,      
    PIN_LPT2_07_INV,      
    PIN_LPT2_08,      
    PIN_LPT2_08_INV,      
    PIN_LPT2_09,      
    PIN_LPT2_09_INV,  
    PIN_LPT2_10,      
    PIN_LPT2_10_INV,  
    PIN_LPT2_11,      
    PIN_LPT2_11_INV,  
    PIN_LPT2_12,      
    PIN_LPT2_12_INV,  
    PIN_LPT2_13,      
    PIN_LPT2_13_INV,          
    PIN_LPT2_14,
    PIN_LPT2_14_INV,
    PIN_LPT2_16,
    PIN_LPT2_16_INV,
    PIN_LPT2_17,
    PIN_LPT2_17_INV,

}pin_hw_e;
    
typedef enum
{ 
    PIN_MAP_X_STEP = 0,  
    PIN_MAP_X_DIR,
    PIN_MAP_Y_STEP,
    PIN_MAP_Y_DIR,
    PIN_MAP_Z_STEP,
    PIN_MAP_Z_DIR,   
    PIN_MAP_A_STEP,
    PIN_MAP_A_DIR,    
    PIN_MAP_COUNT
}pin_map_e;

typedef enum
{
    CMD_IGNORE = 0,
    CMD_START,
    CMD_HALT,
    CMD_STOP_JOG,
    CMD_VECTORS_BUFFER,
    CMD_VECTORS_RUN,
    CMD_VECTORS_JOG,
    CMD_VECTORS_DELAY,
    CMD_SET_JOG_BREAK,
    CMD_MAP,
    CMD_COORDS,
    CMD_OUTPUTS,
    CMD_WATCHDOG,
    CMD_RESET
}command_e;

typedef enum
{ 
    ENG_STATE_IDLE,
    ENG_STATE_RUNNING        
}state_e;



#pragma pack(push, 1)

typedef struct
{
     uint8_t size;
     uint8_t id;
     uint8_t command;
     uint8_t in_mask;
}header_u;

typedef struct
{
    uint32_t      line_id;

    union
    {
        struct
        {
            int32_t       Xs;
            int32_t       Ys;
            int32_t       Zs;
            int32_t       As;

            uint32_t      Xv;
            uint32_t      Yv;
            uint32_t      Zv;
            uint32_t      Av;
        }gcode;

        struct
        {
            uint32_t      cnt;
            int32_t       dir;
            uint32_t      fract;
            int32_t       vfract;
            uint32_t      axis;
        }jog;

        struct
        {
            uint32_t     tick_delay;
        }delay;
        
    }motion;
}timer_step_t;


typedef struct
{
    int32_t Xc;
    int32_t Yc;
    int32_t Zc;
    int32_t Ac;
}timer_coord_t;


typedef struct
{
    uint8_t    map_cnt;
    uint8_t    pin_map[8];
    uint8_t    pin_hw[8];
}timer_map_t;

typedef struct
{
    uint64_t mask;
    uint64_t outputs;
}timer_io_t;


typedef struct
{
    header_u  header;
    union
    {
        timer_step_t    step;
        timer_coord_t   coord;
        timer_map_t     map;
        timer_io_t      io;

        struct
        {
            uint64_t    mask;
            uint64_t    value;
        }stop_condition;
    }data;

}timer_frame_t;


typedef struct
{
    uint8_t        magic_beg;
    uint8_t        size;
    uint8_t        version;
    uint8_t        state;
}timer_resp_header_t;

typedef struct
{
    timer_coord_t     coords;
    uint32_t          line_id;
    uint64_t          inputs;
    uint32_t          last_valid_id;
    uint32_t          free_slots;

}timer_resp_data_t;

typedef struct
{
    timer_resp_header_t header;
    timer_resp_data_t   data;

    uint16_t              crc16;
    uint8_t               magic_end;
}timer_resp_t;


#pragma pack(pop) 


#endif // MACH_FIRMWARE_H

