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

#define GPIO_STRAIGHT(n_,s_)           { GPIO_PORT_SET(n_),GPIO_PORT_READ(n_),((uint32_t)GPIO_PIN(n_)),     ((uint32_t)GPIO_PIN(n_)<<16), ((uint64_t)1) << (s_) }
#define GPIO_INV(n_,s_)                { GPIO_PORT_SET(n_),GPIO_PORT_READ(n_),((uint32_t)GPIO_PIN(n_)<<16), ((uint32_t)GPIO_PIN(n_))    , ((uint64_t)1) << (s_) }

#define GPIO_NONE()                 { NULL,0,0,0 }


typedef struct
{ 
    volatile uint32_t   * regaddr_set;
    volatile uint32_t   * regaddr_read;
    uint32_t              regval_set;
    uint32_t              regval_clr;
    uint64_t              seq_mask;

}gpio_sequence_t;

gpio_sequence_t gpio_map[] = 
{
   GPIO_NONE(),
   GPIO_STRAIGHT(LPT1_01,0),
   GPIO_INV(LPT1_01,0),
   GPIO_STRAIGHT(LPT1_02,1),
   GPIO_INV(LPT1_02,1),
   GPIO_STRAIGHT(LPT1_03,2),
   GPIO_INV(LPT1_03,2),
   GPIO_STRAIGHT(LPT1_04,3),
   GPIO_INV(LPT1_04,3),
   GPIO_STRAIGHT(LPT1_05,4),
   GPIO_INV(LPT1_05,4),
   GPIO_STRAIGHT(LPT1_06,5),
   GPIO_INV(LPT1_06,5),
   GPIO_STRAIGHT(LPT1_07,6),
   GPIO_INV(LPT1_07,6),
   GPIO_STRAIGHT(LPT1_08,7),
   GPIO_INV(LPT1_08,7),
   GPIO_STRAIGHT(LPT1_09,8),
   GPIO_INV(LPT1_09,8),
   GPIO_STRAIGHT(LPT1_10,9),
   GPIO_INV(LPT1_10,9),
   GPIO_STRAIGHT(LPT1_11,10),
   GPIO_INV(LPT1_11,10),
   GPIO_STRAIGHT(LPT1_12,11),
   GPIO_INV(LPT1_12,11),
   GPIO_STRAIGHT(LPT1_13,12),
   GPIO_INV(LPT1_13,12),
   GPIO_STRAIGHT(LPT1_14,13),
   GPIO_INV(LPT1_14,13),
   GPIO_STRAIGHT(LPT1_15,14),
   GPIO_INV(LPT1_15,14),
   GPIO_STRAIGHT(LPT1_16,15),
   GPIO_INV(LPT1_16,15),
   GPIO_STRAIGHT(LPT1_17,16),
   GPIO_INV(LPT1_17,16),

   GPIO_STRAIGHT(LPT2_01,32),
   GPIO_INV(LPT2_01,32),
   GPIO_STRAIGHT(LPT2_02,33),
   GPIO_INV(LPT2_02,33),
   GPIO_STRAIGHT(LPT2_03,34),
   GPIO_INV(LPT2_03,34),
   GPIO_STRAIGHT(LPT2_04,35),
   GPIO_INV(LPT2_04,35),
   GPIO_STRAIGHT(LPT2_05,36),
   GPIO_INV(LPT2_05,36),
   GPIO_STRAIGHT(LPT2_06,37),
   GPIO_INV(LPT2_06,37),
   GPIO_STRAIGHT(LPT2_07,38),
   GPIO_INV(LPT2_07,38),
   GPIO_STRAIGHT(LPT2_08,39),
   GPIO_INV(LPT2_08,39),
   GPIO_STRAIGHT(LPT2_09,40),
   GPIO_INV(LPT2_09,40),
   GPIO_STRAIGHT(LPT2_10,42),
   GPIO_INV(LPT2_10,42),
   GPIO_STRAIGHT(LPT2_11,42),
   GPIO_INV(LPT2_11,42),
   GPIO_STRAIGHT(LPT2_12,43),
   GPIO_INV(LPT2_12,43),
   GPIO_STRAIGHT(LPT2_13,44),
   GPIO_INV(LPT2_13,44),
   GPIO_STRAIGHT(LPT2_14,45),
   GPIO_INV(LPT2_14,45),
   GPIO_STRAIGHT(LPT2_15,46),
   GPIO_INV(LPT2_15,46),
   GPIO_STRAIGHT(LPT2_16,47),
   GPIO_INV(LPT2_16,47),
   GPIO_STRAIGHT(LPT2_17,48),
   GPIO_INV(LPT2_17,48)

};



gpio_sequence_t gpio_output_map[] = 
{
   GPIO_STRAIGHT(LPT1_01,0),
   GPIO_STRAIGHT(LPT1_02,1),
   GPIO_STRAIGHT(LPT1_03,2),
   GPIO_STRAIGHT(LPT1_04,3),
   GPIO_STRAIGHT(LPT1_05,4),
   GPIO_STRAIGHT(LPT1_06,5),
   GPIO_STRAIGHT(LPT1_07,6),
   GPIO_STRAIGHT(LPT1_08,7),
   GPIO_STRAIGHT(LPT1_09,8),
   GPIO_STRAIGHT(LPT1_10,9),
   GPIO_STRAIGHT(LPT1_11,10),
   GPIO_STRAIGHT(LPT1_12,11),
   GPIO_STRAIGHT(LPT1_13,12),
   GPIO_STRAIGHT(LPT1_14,13),
   GPIO_STRAIGHT(LPT1_15,14),
   GPIO_STRAIGHT(LPT1_16,15),
   GPIO_STRAIGHT(LPT1_17,16),
   GPIO_STRAIGHT(LPT2_01,32),
   GPIO_STRAIGHT(LPT2_02,33),
   GPIO_STRAIGHT(LPT2_03,34),
   GPIO_STRAIGHT(LPT2_04,35),
   GPIO_STRAIGHT(LPT2_05,36),
   GPIO_STRAIGHT(LPT2_06,37),
   GPIO_STRAIGHT(LPT2_07,38),
   GPIO_STRAIGHT(LPT2_08,39),
   GPIO_STRAIGHT(LPT2_09,40),
   GPIO_STRAIGHT(LPT2_10,42),
   GPIO_STRAIGHT(LPT2_11,42),
   GPIO_STRAIGHT(LPT2_12,43),
   GPIO_STRAIGHT(LPT2_13,44),
   GPIO_STRAIGHT(LPT2_14,45),
   GPIO_STRAIGHT(LPT2_15,46),
   GPIO_STRAIGHT(LPT2_16,47),
   GPIO_STRAIGHT(LPT2_17,48)
};

gpio_sequence_t gpio_input_map[] = 
{
   GPIO_STRAIGHT(LPT1_10,9),
   GPIO_STRAIGHT(LPT1_11,10),
   GPIO_STRAIGHT(LPT1_12,11),
   GPIO_STRAIGHT(LPT1_13,12),
   GPIO_STRAIGHT(LPT1_15,14),

   GPIO_STRAIGHT(LPT2_02,33),
   GPIO_STRAIGHT(LPT2_03,34),
   GPIO_STRAIGHT(LPT2_04,35),
   GPIO_STRAIGHT(LPT2_05,36),
   GPIO_STRAIGHT(LPT2_06,37),
   GPIO_STRAIGHT(LPT2_07,38),
   GPIO_STRAIGHT(LPT2_08,39),
   GPIO_STRAIGHT(LPT2_09,40),
   GPIO_STRAIGHT(LPT2_10,41),
   GPIO_STRAIGHT(LPT2_11,42),
   GPIO_STRAIGHT(LPT2_12,43),
   GPIO_STRAIGHT(LPT2_13,44),
   GPIO_STRAIGHT(LPT2_15,46)

};



pinctrl_data_t  pcd = 
{
    {
       PIN_LPT1_02,  //PIN_MAP_X_STEP  
       PIN_LPT1_03,  //PIN_MAP_X_DIR
       PIN_LPT1_04,  //PIN_MAP_Y_STEP
       PIN_LPT1_05,  //PIN_MAP_Y_DIR
       PIN_LPT1_06,  //PIN_MAP_Z_STEP
       PIN_LPT1_07,  //PIN_MAP_Z_DIR   
       PIN_LPT1_08,  //PIN_MAP_A_STEP
       PIN_LPT1_09,  //PIN_MAP_A_DIR    
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
   uint32_t   pin_hw;

     
    pin_hw = (uint32_t)pcd.map[pin_id];

    *gpio_map[pin_hw].regaddr_set = gpio_map[pin_hw].regval_set;            
}

void inline pinctrl_clear(pin_map_e pin_id)
{
    uint32_t   pin_hw;
     
    pin_hw = (uint32_t)pcd.map[pin_id];

    *gpio_map[pin_hw].regaddr_set = gpio_map[pin_hw].regval_clr;    

}


void inline pinctrl_set_outputs(uint64_t outputs,uint64_t mask)
{
    int ii;

    for(ii = 0; ii < DIM(gpio_output_map);ii++)
    {
      if(mask & (1<<ii))
      {
          if(outputs & gpio_output_map[ii].seq_mask )
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


uint64_t pinctrl_read(void)
{
    int      ii;
    uint64_t result = 0;

    for(ii = 0; ii < DIM(gpio_input_map);ii++)
    {
        if( ( (*gpio_input_map[ii].regaddr_read) & gpio_input_map[ii].regval_set) != 0)
        {
           result |= gpio_input_map[ii].seq_mask;
        }
    }

    return result;
}



