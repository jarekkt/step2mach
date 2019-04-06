// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------



#include "pinctrl.h"

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
    switch(pcd.map[pin_id])
    {
    default:    
    case PIN_LPTO_NONE:    /* No operation */      break;  
    case PIN_LPTO_1:       LATAbits.LATA0 = 1; break;
    case PIN_LPTO_1_INV:   LATAbits.LATA0 = 0; break;   
    case PIN_LPTO_2:       LATAbits.LATA1  = 1; break;  
    case PIN_LPTO_2_INV:   LATAbits.LATA1  = 0; break;   
    case PIN_LPTO_3:       LATBbits.LATB14 = 1; break;
    case PIN_LPTO_3_INV:   LATBbits.LATB14 = 0; break;   
    case PIN_LPTO_4:       LATBbits.LATB13  = 1; break;  
    case PIN_LPTO_4_INV:   LATBbits.LATB13  = 0; break;   
    case PIN_LPTO_5:       LATBbits.LATB11 = 1; break;
    case PIN_LPTO_5_INV:   LATBbits.LATB11 = 0; break;   
    case PIN_LPTO_6:       LATBbits.LATB10 = 1; break;
    case PIN_LPTO_6_INV:   LATBbits.LATB10 = 0; break;   
    case PIN_LPTO_7:       LATAbits.LATA3 = 1; break;
    case PIN_LPTO_7_INV:   LATAbits.LATA3 = 0; break;   
    case PIN_LPTO_8:       LATBbits.LATB4 = 1; break;
    case PIN_LPTO_8_INV:   LATBbits.LATB4 = 0; break;   
    case PIN_LPTO_9:       LATAbits.LATA4  = 1; break;  
    case PIN_LPTO_9_INV:   LATAbits.LATA4  = 0; break;   
    case PIN_LPTO_14:      LATBbits.LATB15  = 1; break; 
    case PIN_LPTO_14_INV:  LATBbits.LATB15 = 0; break;
    case PIN_LPTO_16:      LATBbits.LATB1  = 1; break; 
    case PIN_LPTO_16_INV:  LATBbits.LATB1  = 0; break; 
    case PIN_LPTO_17:      LATBbits.LATB12  = 1; break;  
    case PIN_LPTO_17_INV:  LATBbits.LATB12  = 0; break;         
    }           
}

void inline pinctrl_clear(pin_map_e pin_id)
{
    switch(pcd.map[pin_id])
    {
    default:    
    case PIN_LPTO_NONE:    /* No operation */      break;  
    case PIN_LPTO_1:       LATAbits.LATA0 = 0; break;
    case PIN_LPTO_1_INV:   LATAbits.LATA0 = 1; break;   
    case PIN_LPTO_2:       LATAbits.LATA1  = 0; break;  
    case PIN_LPTO_2_INV:   LATAbits.LATA1  = 1; break;   
    case PIN_LPTO_3:       LATBbits.LATB14 = 0; break;
    case PIN_LPTO_3_INV:   LATBbits.LATB14 = 1; break;   
    case PIN_LPTO_4:       LATBbits.LATB13  = 0; break;  
    case PIN_LPTO_4_INV:   LATBbits.LATB13  = 1; break;   
    case PIN_LPTO_5:       LATBbits.LATB11 = 0; break;
    case PIN_LPTO_5_INV:   LATBbits.LATB11 = 1; break;   
    case PIN_LPTO_6:       LATBbits.LATB10 = 0; break;
    case PIN_LPTO_6_INV:   LATBbits.LATB10 = 1; break;   
    case PIN_LPTO_7:       LATAbits.LATA3 = 0; break;
    case PIN_LPTO_7_INV:   LATAbits.LATA3 = 1; break;   
    case PIN_LPTO_8:       LATBbits.LATB4 = 0; break;
    case PIN_LPTO_8_INV:   LATBbits.LATB4 = 1; break;   
    case PIN_LPTO_9:       LATAbits.LATA4  = 0; break;  
    case PIN_LPTO_9_INV:   LATAbits.LATA4  = 1; break;   
    case PIN_LPTO_14:      LATBbits.LATB15  = 0; break; 
    case PIN_LPTO_14_INV:  LATBbits.LATB15  = 1; break;
    case PIN_LPTO_16:      LATBbits.LATB1  = 0; break; 
    case PIN_LPTO_16_INV:  LATBbits.LATB1  = 1; break; 
    case PIN_LPTO_17:      LATBbits.LATB12  = 0; break;  
    case PIN_LPTO_17_INV:  LATBbits.LATB12  = 1; break;         
    }
}


void inline pinctrl_set_outputs(Uint32_t outputs,Uint32_t mask)
{
    if(mask & (((Uint32_t)1)<<0))
    {
        if(outputs & (((Uint32_t)1)<<0) )
        {
           LATAbits.LATA0 = 1; 
        }
        else
        {
          LATAbits.LATA0 = 0;   
        }
    }

    if(mask & (((Uint32_t)1)<<1))
    {

        if(outputs & (((Uint32_t)1)<<1))
        {
           LATAbits.LATA1 = 1; 
        }
        else
        {
          LATAbits.LATA1 = 0;   
        }
    }

    if(mask & (((Uint32_t)1)<<2))
    {

        if(outputs & (((Uint32_t)1)<<2))
        {
          LATBbits.LATB14 = 1; 
        }
        else
        {
          LATBbits.LATB14 = 0;   
        }
    }


    if(mask & (((Uint32_t)1)<<3))
    {

        if(outputs & (((Uint32_t)1)<<3))
        {
           LATBbits.LATB13 = 1; 
        }
        else
        {
           LATBbits.LATB13 = 0;   
        }
    }

    if(mask & (((Uint32_t)1)<<4))
    {

        if(outputs & (((Uint32_t)1)<<4))
        {
          LATBbits.LATB11 = 1; 
        }
        else
        {
          LATBbits.LATB11 = 0;   
        }
    }

    if(mask & (((Uint32_t)1)<<5))
    {

        if(outputs & (((Uint32_t)1)<<5))
        {
          LATBbits.LATB10 = 1; 
        }
        else
        {
          LATBbits.LATB10 = 0;   
        }
    }

    if(mask & (((Uint32_t)1)<<6))
    {

        if(outputs & (((Uint32_t)1)<<6))
        {
           LATAbits.LATA3 = 1; 
        }
        else
        {
          LATAbits.LATA3 = 0;   
        }
    }


    if(mask & (((Uint32_t)1)<<7))
    {

        if(outputs & (((Uint32_t)1)<<7))
        {
          LATBbits.LATB4 = 1; 
        }
        else
        {
          LATBbits.LATB4 = 0;   
        }
    }

    if(mask & (((Uint32_t)1)<<8))
    {

        if(outputs & (((Uint32_t)1)<<8))
        {
           LATAbits.LATA4 = 1; 
        }
        else
        {
           LATAbits.LATA4 = 0;   
        }
    }


    if(mask & (((Uint32_t)1)<<13))
    {

        if(outputs & (((Uint32_t)1)<<13))
        {
           LATBbits.LATB15 = 1; 
        }
        else
        {
           LATBbits.LATB15 = 0;   
        }
    }

    if(mask & (((Uint32_t)1)<<15))
    {

        if(outputs & (((Uint32_t)1)<<15))
        {
           LATBbits.LATB1 = 1; 
        }
        else
        {
          LATBbits.LATB1 = 0;   
        }
    }

    if(mask & (((Uint32_t)1)<<16))
    {

        if(outputs & (((Uint32_t)1)<<16))
        {
          LATBbits.LATB12 = 1; 
        }
        else
        {
          LATBbits.LATB12 = 0;   
        }
    }    
}





