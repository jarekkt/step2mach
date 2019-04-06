// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------



#include "../mach_common/types.h"
#include "../mach_common/mach_firmware.h"
#include "p33fj64MC802.h"


    
typedef struct
{
   pin_hw_e map[PIN_MAP_COUNT];
}pinctrl_data_t;


void   pinctrl_map(pin_map_e  pin_id,pin_hw_e pin_fn);

void inline pinctrl_set(pin_map_e pin_id);
void inline pinctrl_clear(pin_map_e pin_id);

void inline pinctrl_set_outputs(Uint32_t outputs,Uint32_t mask);




