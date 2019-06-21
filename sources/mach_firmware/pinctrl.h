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


    

typedef struct
{
   pin_hw_e map[PIN_MAP_COUNT];
}pinctrl_data_t;


void pinctrl_map(pin_map_e  pin_id,pin_hw_e pin_fn);
void pinctrl_set(pin_map_e pin_id);
void pinctrl_clear(pin_map_e pin_id);


void pinctrl_set_outputs(uint64_t outputs,uint64_t mask);

uint64_t pinctrl_read(void);



