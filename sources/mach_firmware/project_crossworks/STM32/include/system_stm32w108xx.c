/**
  ******************************************************************************
  * @file    system_stm32w108xx.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    30-November-2012
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Source File.
  *             
  * 1.  This file provides two functions and one global variable to be called from 
  *     user application:
  *      - SystemInit(): Setups the system clock (System clock source).
  *                      This function is called at startup just after reset and 
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32w108xx.s" file.
  *                        
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick 
  *                                  timer or configure other parameters.
  *                                     
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.   
  *      
  * 2. After each device reset the HSI (12 MHz) is used as system clock source.
  *    Then SystemInit() function is called, in "startup_stm32w108xx.s" file, to
  *    configure the system clock before to branch to main program.    
  *    
  * 3. If the system clock source selected by user fails to startup, the SystemInit()
  *    function will do nothing and HSI still used as system clock source. User can 
  *    add some code to deal with this issue inside the SetSysClock() function.
  * 
  * 4. The default value of HSE crystal is set to 24MHz, refer to "HSE_VALUE" define
  *    in "stm32w108xx.h" file. When HSE is used as system clock source, directly or
  *    through PLL, and you are using different crystal you have to adapt the HSE
  *    value to your own configuration.
  * 
  * 5. This file configures the system clock as follows:  
  *=============================================================================
  *                         System Clock Configuration
  *=============================================================================
  *        System Clock source          | HSE
  *----------------------------------------------------------------------------- 
  *        SYSCLK                       | 24000000 Hz
  *----------------------------------------------------------------------------- 
  *        HCLK                         | 24000000 Hz
  *----------------------------------------------------------------------------- 
  *        FCLK                         | 12000000 Hz
  *----------------------------------------------------------------------------- 
  *        PCLK = SYSCLK/2              | 12000000 Hz
  *----------------------------------------------------------------------------- 
  *        HSE Frequency                | 24000000 Hz
  *----------------------------------------------------------------------------- 
  *        VDD                          | 3.3 V
  *----------------------------------------------------------------------------- 
  *        Flash Latency                | 1 WS
  *----------------------------------------------------------------------------- 
  *=============================================================================
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32w108xx_system
  * @{
  */  
  
/** @addtogroup STM32W108xx_System_Private_Includes
  * @{
  */

#include "stm32w108xx.h"

/**
  * @}
  */

/** @addtogroup STM32W108xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32W108xx_System_Private_Defines
  * @{
  */
/**
  * @}
  */

/** @addtogroup STM32W108xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32W108xx_System_Private_Variables
  * @{
  */
uint32_t SystemCoreClock    = 24000000;
/**
  * @}
  */

/** @addtogroup STM32W108xx_System_Private_FunctionPrototypes
  * @{
  */

static void SetSysClock(void);

/**
  * @}
  */

/** @addtogroup STM32W108xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
  /* reset the CLK_HSECR2 register */
   CLK->HSECR2 &=  (uint32_t)0x00000000;
   
  /* reset the CLK_CPUCR register */
   CLK->CPUCR &=  (uint32_t)0x00000000;

  /* Configure the System clock frequency */
  SetSysClock();
}

/**
  * @brief  Update SystemCoreClock according to Clock Register Values
  * @note   - The system frequency computed by this function is not the real 
  *           frequency in the chip. It is calculated based on the predefined 
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
  *
  *         (*) HSI_VALUE is a constant defined in stm32w108xx.h file (default value
  *             12 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.   
  *    
  *         (**) HSE_VALUE is a constant defined in stm32w108xx.h file (default value
  *              24 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  uint32_t tmp = 0;
  
  /* Get SYSCLK source -------------------------------------------------------*/   
  tmp = (CLK->HSECR2) & (uint32_t)0x0000003;
  
  if (tmp == 0x0000003) /* HSE used as system clock */  
  {
    SystemCoreClock = HSE_VALUE;
  }  
  else  /* HSI used as system clock */
  {
    SystemCoreClock = HSI_VALUE;
  } 
}

/**
  * @brief  Configures the System clock frequency,
  * @note   This function should be called only once the CLOCK configuration  
  *         is reset to the default reset state (done in SystemInit() function).
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
  __IO uint32_t StartUpCounter = 0;
    
 /* Enable HSE */
  CLK->HSECR2 |= CLK_HSECR2_EN;
 
  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    StartUpCounter++;  
  } while(StartUpCounter != HSE_STARTUP_TIMEOUT);
   
 /* Select HSE system clock */
  CLK->HSECR2 |= CLK_HSECR2_SW1;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
