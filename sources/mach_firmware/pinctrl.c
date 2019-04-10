// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jarosaw Karwik
   E-Mail:     jaroslaw.karwik(at)gmail.com
   
**/
// ----------------------------------------------------------------------------



#include "pinctrl.h"
#include "init.h"

#include "main.h"

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"


#define GPIO_PORT(name_)            name_##_GPIO_Port
#define GPIO_PORT_SET(name_)        &GPIO_PORT(name_)->BSRR
#define GPIO_PORT_READ(name_)       &GPIO_PORT(name_)->IDR
#define GPIO_PIN(name_)             name_##_Pin

#define GPIO_STRAIGHT(n_)           { GPIO_PORT_SET(n_),GPIO_PORT_READ(n_),((uint32_t)GPIO_PIN(n_)),     ((uint32_t)GPIO_PIN(n_)<<16) }
#define GPIO_INV(n_)                { GPIO_PORT_SET(n_),GPIO_PORT_READ(n_),((uint32_t)GPIO_PIN(n_)<<16), ((uint32_t)GPIO_PIN(n_))     }


typedef struct
{  
    volatile uint32_t   * regaddr_set;
    volatile uint32_t   * regaddr_read;
    uint32_t              regval_set;
    uint32_t              regval_clr;

}gpio_sequence_t;


gpio_sequence_t gpio_map[] = 
{
   { NULL,0,0 },
   GPIO_STRAIGHT(LPT1_1),
   GPIO_INV(LPT1_1),
   GPIO_STRAIGHT(LPT1_2),
   GPIO_INV(LPT1_2),
   GPIO_STRAIGHT(LPT1_3),
   GPIO_INV(LPT1_3),
   GPIO_STRAIGHT(LPT1_4),
   GPIO_INV(LPT1_4),
   GPIO_STRAIGHT(LPT1_5),
   GPIO_INV(LPT1_5),
   GPIO_STRAIGHT(LPT1_6),
   GPIO_INV(LPT1_6),
   GPIO_STRAIGHT(LPT1_7),
   GPIO_INV(LPT1_7),
   GPIO_STRAIGHT(LPT1_8),
   GPIO_INV(LPT1_8),
   GPIO_STRAIGHT(LPT1_9),
   GPIO_INV(LPT1_9),
   GPIO_STRAIGHT(LPT1_10),
   GPIO_INV(LPT1_10),
   GPIO_STRAIGHT(LPT1_11),
   GPIO_INV(LPT1_11),
   GPIO_STRAIGHT(LPT1_12),
   GPIO_INV(LPT1_12),
   GPIO_STRAIGHT(LPT1_13),
   GPIO_INV(LPT1_13),
   GPIO_STRAIGHT(LPT1_14),
   GPIO_INV(LPT1_14),
   GPIO_STRAIGHT(LPT1_15),
   GPIO_INV(LPT1_15),
   GPIO_STRAIGHT(LPT1_16),
   GPIO_INV(LPT1_16),
   GPIO_STRAIGHT(LPT1_17),
   GPIO_INV(LPT1_17)

};



gpio_sequence_t gpio_output_map[] = 
{
   GPIO_STRAIGHT(LPT1_1),
   GPIO_STRAIGHT(LPT1_2),
   GPIO_STRAIGHT(LPT1_3),
   GPIO_STRAIGHT(LPT1_4),
   GPIO_STRAIGHT(LPT1_5),
   GPIO_STRAIGHT(LPT1_6),
   GPIO_STRAIGHT(LPT1_7),
   GPIO_STRAIGHT(LPT1_8),
   GPIO_STRAIGHT(LPT1_9),
   GPIO_STRAIGHT(LPT1_10),
   GPIO_STRAIGHT(LPT1_11),
   GPIO_STRAIGHT(LPT1_12),
   GPIO_STRAIGHT(LPT1_13),
   GPIO_STRAIGHT(LPT1_14),
   GPIO_STRAIGHT(LPT1_15),
   GPIO_STRAIGHT(LPT1_16),
   GPIO_STRAIGHT(LPT1_17)
};

gpio_sequence_t gpio_input_map[] = 
{
   GPIO_STRAIGHT(LPT1_10),
   GPIO_STRAIGHT(LPT1_11),
   GPIO_STRAIGHT(LPT1_12),
   GPIO_STRAIGHT(LPT1_13),
   GPIO_STRAIGHT(LPT1_15),
};



pinctrl_data_t  pcd = 
{
    {
       PIN_LPTO_2,  //PIN_MAP_X_STEP  
       PIN_LPTO_3,  //PIN_MAP_X_DIR
       PIN_LPTO_4,  //PIN_MAP_Y_STEP
       PIN_LPTO_5,  //PIN_MAP_Y_DIR
       PIN_LPTO_6,  //PIN_MAP_Z_STEP
       PIN_LPTO_7,  //PIN_MAP_Z_DIR   
       PIN_LPTO_8,  //PIN_MAP_A_STEP
       PIN_LPTO_9,  //PIN_MAP_A_DIR    
    }

};


void   pinctrl_map(pin_map_e  pin_id,pin_hw_e pin_fn)
{
    if(pin_id < PIN_MAP_COUNT)
    {
        pcd.map[pin_id] = pin_fn;
    }
}

void inline pinctrl_set(pin_map_e pin_id)
{
    *gpio_map[pin_id].regaddr_set = gpio_map[pin_id].regval_set;            
}

void inline pinctrl_clear(pin_map_e pin_id)
{
    *gpio_map[pin_id].regaddr_set = gpio_map[pin_id].regval_clr;    

}


void inline pinctrl_set_outputs(uint32_t outputs,uint32_t mask)
{
    int ii;

    for(ii = 0; ii < DIM(gpio_output_map);ii++)
    {
      if(mask & (1<<ii))
      {
          if(outputs & (1<<ii))
          {
             *gpio_output_map[ii].regaddr_set = gpio_output_map[ii].regval_set;
          }
          else
          {
             *gpio_output_map[ii].regaddr_set = gpio_output_map[ii].regval_clr;
          }
      }
    }

}


uint32_t pinctrl_read(void)
{
    int      ii;
    uint32_t result = 0;

    for(ii = 0; ii < DIM(gpio_input_map);ii++)
    {
        if( (*gpio_input_map[ii].regaddr_read & gpio_input_map[ii].regval_set) != 0)
        {
           result |= (1<<ii);
        }
    }

    return result;
}



