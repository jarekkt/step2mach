// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jarosaw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------


#ifndef MACH_FIRMWARE_H
#define MACH_FIRMWARE_H


#ifdef _WIN32
#pragma pack(push, 2)
#endif

#define VERSION_NR              0x11
#define WATCHDOG_JOG_TIMEOUT    400
#define WATCHDOG_COMM_TIMEOUT   250
#define HARDWARE_FREQ           100000 /*Hz*/

typedef enum
{
    PIN_LPTO_NONE = 0,      
    PIN_LPTO_1,      
    PIN_LPTO_1_INV,      
    PIN_LPTO_2,      
    PIN_LPTO_2_INV,      
    PIN_LPTO_3,      
    PIN_LPTO_3_INV,      
    PIN_LPTO_4,      
    PIN_LPTO_4_INV,      
    PIN_LPTO_5,      
    PIN_LPTO_5_INV,      
    PIN_LPTO_6,      
    PIN_LPTO_6_INV,      
    PIN_LPTO_7,      
    PIN_LPTO_7_INV,      
    PIN_LPTO_8,      
    PIN_LPTO_8_INV,      
    PIN_LPTO_9,      
    PIN_LPTO_9_INV,      
    PIN_LPTO_14,
    PIN_LPTO_14_INV,
    PIN_LPTO_16,
    PIN_LPTO_16_INV,
    PIN_LPTO_17,
    PIN_LPTO_17_INV
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
            int16_t       Xs;
            int16_t       Ys;
            int16_t       Zs;
            int16_t       As;

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
            uint16_t      axis;
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
    uint32_t mask;
    uint32_t outputs;
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
            uint16_t    mask;
            uint16_t    value;
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
    uint16_t          last_valid_id;
    uint8_t           free_slots;
    uint8_t           inputs;
    timer_coord_t     coords;
    uint32_t          line_id;
}timer_resp_data_t;

typedef struct
{
    timer_resp_header_t header;
    timer_resp_data_t   data;

    uint16_t              crc16;
    uint8_t               magic_end;
}timer_resp_t;


#ifdef _WIN32
#pragma pack(pop)
#endif



#endif // MACH_FIRMWARE_H

