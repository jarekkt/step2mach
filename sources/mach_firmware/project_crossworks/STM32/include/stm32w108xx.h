/**
  ******************************************************************************
  * @file    stm32w108xx.h
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    30-November-2012
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Header File.  
  *          This file contains all the peripheral register's definitions, bits 
  *          definitions and memory mapping for STM32W108xx devices.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e. 
  *                code will be based on direct access to peripheral’s registers 
  *                rather than drivers API), this option is controlled by 
  *                "#define USE_STDPERIPH_DRIVER"
  *              - To change few application-specific parameters such as the HSE 
  *                crystal frequency
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral’s registers hardware
  *
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

/** @addtogroup stm32w108xx
  * @{
  */

#ifndef __STM32W108XX_H
#define __STM32W108XX_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup Library_configuration_section
  * @{
  */
  
/** Uncomment the line below according to the target STM32 device used in your
  * application 
  */

#if !defined (STM32W108C8) && !defined (STM32W108CB) && !defined (STM32W108CC) && !defined (STM32W108CZ) && !defined (STM32W108HB)  
  /* #define STM32W108C8 */     /*!< STM32W108C8: 64k FLASH */
  /* #define STM32W108CB */     /*!< STM32W108CB: 128k FLASH */  
  /* #define STM32W108CC */     /*!< STM32W108CC: 256k FLASH */
  /* #define STM32W108CZ */     /*!< STM32W108CZ: 192k FLASH */  
  /* #define STM32W108HB */     /*!< STM32W108HB: 128k FLASH */
#endif

/**  Tip: To avoid modifying this file each time you need to switch between these
  *       devices, you can define the device in your toolchain compiler preprocessor.
  */

#if !defined (STM32W108C8) && !defined (STM32W108CB) && !defined (STM32W108CC) && !defined (STM32W108CZ) && !defined (STM32W108HB)  
 #error "Please select first the target STM32W108XX device used in your application (in stm32w108xx.h file)"
#endif

#if !defined  (USE_STDPERIPH_DRIVER)
/**
  * @brief Comment the line below if you will not use the peripherals drivers.
  * In this case, these drivers will not be included and the application code will 
  * be based on direct access to peripherals registers 
  */
  
  /* #define USE_STDPERIPH_DRIVER */
#endif /* USE_STDPERIPH_DRIVER */

/**
  * @brief In the following line adjust the value of External High Speed oscillator (HSE)
  * used in your application 
  * 
  * Tip: To avoid modifying this file each time you need to use different HSE, you
  *     can define the HSE value in your toolchain compiler preprocessor.
  */           
#if !defined  (HSE_VALUE) 
  #define HSE_VALUE    ((uint32_t)24000000) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

/**
  * @brief In the following line adjust the External High Speed oscillator (HSE) Startup 
  * Timeout value 
  */
#if !defined  (HSE_STARTUP_TIMEOUT) 
  #define HSE_STARTUP_TIMEOUT    ((uint16_t)0x0500)   /*!< Time out for HSE start up */
#endif /* HSE_STARTUP_TIMEOUT */

/**
  * @brief The internal high speed clock (HSI) should be calibrated before using it. 
  *        The defined one is the theoretical value. 
  */
#if !defined  (HSI_VALUE)   
  #define HSI_VALUE    ((uint32_t)12000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

/**
  * @brief The internal low speed clock (LSI) should be calibrated before using it. 
  *        The defined one is the theoretical value. 
  */
#if !defined  (LSI_VALUE) 
#define LSI_VALUE  ((uint32_t)10000)    /*!< Value of the Internal Low Speed oscillator in Hz
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif

/**
  * @brief The following line define the External low Speed oscillator (LSE).
  *        
  */
#if !defined  (LSE_VALUE) 
#define LSE_VALUE  ((uint32_t)32768)    /*!< Value of the External Low Speed oscillator in Hz */
#endif

/**
  * @brief STM32W108XX Standard Peripherals Library version number V0.0.1RC1
  */
#define __STM32W108XX_STDPERIPH_VERSION_MAIN   (0x00) /*!< [31:24] main version */
#define __STM32W108XX_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32W108XX_STDPERIPH_VERSION_SUB2   (0x01) /*!< [15:8]  sub2 version */
#define __STM32W108XX_STDPERIPH_VERSION_RC     (0x01) /*!< [7:0]  release candidate */ 
#define __STM32W108XX_STDPERIPH_VERSION        ((__STM32W108XX_STDPERIPH_VERSION_MAIN << 24)\
                                               |(__STM32W108XX_STDPERIPH_VERSION_SUB1 << 16)\
                                               |(__STM32W108XX_STDPERIPH_VERSION_SUB2 << 8)\
                                               |(__STM32W108XX_STDPERIPH_VERSION_RC))
/**
  * @}
  */

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
 * @brief Configuration of the Cortex-M3 Processor and Core Peripherals 
 */
#define __CM3_REV                 0x0101  /*!< Core revision r1p1                              */
#define __MPU_PRESENT             1       /*!< STM32W108XX  provides an MPU                    */
#define __NVIC_PRIO_BITS          4       /*!< STM32W108XX uses 4 Bits for the Priority Levels */
#define __Vendor_SysTickConfig    0       /*!< Set to 1 if different SysTick Config is used    */
#define __FPU_PRESENT             0       /*!< FPU is not present                              */

/**
  * @brief STM32W108XX Interrupt Number Definition, according to the selected device 
  *        in @ref Library_configuration_section 
  */
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ****************************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt                           */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                                   */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                                 */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                                    */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                              */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                                    */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                                */
/******  STM32W108xx specific Interrupt Numbers ****************************************************************/
  TIM1_IRQn                   = 0,      /*!< Timer 1 Interrupt                                                 */
  TIM2_IRQn                   = 1,      /*!< Timer 1 Interrupt                                                 */
  MNG_IRQn                    = 2,      /*!< Management Peripheral Interrupt                                   */
  BASEBAND_IRQn               = 3,      /*!< Base Band Interrupt                                               */
  SLPTIM_IRQn                 = 4,      /*!< Sleep Timer Interrupt                                             */
  SC1_IRQn                    = 5,      /*!< Serial Controller 1 Interrupt                                     */
  SC2_IRQn                    = 6,      /*!< Serial Controller 2 Interrupt                                     */
  SECURITY_IRQn               = 7,      /*!< Security Interrupt                                                */
  MAC_TIM_IRQn                = 8,      /*!< MAC Timer Interrupt                                               */
  MAC_TR_IRQn                 = 9,      /*!< MAC Transmit Interrupt                                            */
  MAC_RE_IRQn                 = 10,     /*!< MAC Receive Interrupt                                             */
  ADC_IRQn                    = 11,     /*!< ADC Interrupt                                                     */
  EXTIA_IRQn                  = 12,     /*!< EXTI port A interrupt                                             */
  EXTIB_IRQn                  = 13,     /*!< EXTI port B interrupt                                             */
  EXTIC_IRQn                  = 14,     /*!< EXTI port C interrupt                                             */
  EXTID_IRQn                  = 15,     /*!< EXTI port D interrupt                                             */    
  DEBUG_IRQn                  = 16      /*!< Debug Interrupt                                                   */
} IRQn_Type;

/**
  * @}
  */

#include "core_cm3.h"             /* Cortex-M3 processor and core peripherals */
#include "system_stm32w108xx.h"
#include <stdint.h>

/** @addtogroup Exported_types
  * @{
  */
  

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;      

/**
  * @}
  */

/** @addtogroup Peripheral_registers_structures
  * @{
  */

/** 
  * @brief Clock Controller Registers 
  */ 
typedef struct
{ 
  __IO uint32_t SLEEPCR;          /*!< Sleep timer control register,            Address offset: 0x0008 */
  __IO uint32_t LSI10KCR;         /*!< LSI Clock (10KHz) control register,      Address offset: 0x000C */
  __IO uint32_t LSI1KCR;          /*!< LSI Clock (1KHz) control register,       Address offset: 0x0010 */
       uint32_t RESERVED0[4092];  /*!< Reserved */
  __IO uint32_t HSECR1;           /*!< HSE Clock (24MHz) control register 1,    Address offset: 0x4004 */
  __IO uint32_t HSICR;            /*!< HSI Clock (12MHz) trim register,         Address offset: 0x4008 */
  __IO uint32_t HSECOMPR;         /*!< HSE comparator Output,                   Address offset: 0x400C */
  __IO uint32_t PERIODCR;         /*!< Clock period control register,           Address offset: 0x4010 */
  __IO uint32_t PERIODSR;         /*!< Clock period status register,            Address offset: 0x4014 */
  __IO uint32_t DITHERCR;         /*!< Clock dither control register,           Address offset: 0x4018 */
  __IO uint32_t HSECR2;           /*!< HSE Clock (24MHz) control register 2,    Address offset: 0x401C */
  __IO uint32_t CPUCR;            /*!< Clock source select register,            Address offset: 0x4020 */
} CLK_TypeDef;

/** 
  * @brief Power Management Registers (PWR)
  */ 
typedef struct
{
  __IO uint32_t DSLEEPCR1;        /*!< Deep Sleep Control register 1            Address offset 0x0004 */
       uint32_t RESERVED0[3];     /*!< Reserved */
  __IO uint32_t DSLEEPCR2;        /*!< Deep Sleep Control register 2            Address offset 0x0014 */
  __IO uint32_t VREGCR;           /*!< Voltage regulator Control register 1     Address offset 0x0018 */
       uint32_t RESERVED1;        /*!< Reserved */
  __IO uint32_t WAKECR1;          /*!< Wake Control register 1                  Address offset 0x0020 */
  __IO uint32_t WAKECR2;          /*!< Wake Control register 2                  Address offset 0x0024 */
  __IO uint32_t WAKESR;           /*!< Wake Status register                     Address offset 0x0028 */
       uint32_t RESERVED2[2];     /*!< Reserved */
  __IO uint32_t CPWRUPREQSR;      /*!< CPWRUPREQ status register                Address offset 0x0034 */
  __IO uint32_t CSYSPWRUPREQSR;   /*!< CSYSPWRUPREQ status register             Address offset 0x0038 */
  __IO uint32_t CSYSPWRUPACKSR;   /*!< CSYSPWRUPACK status register             Address offset 0x003C */
  __IO uint32_t CSYSPWRUPACKCR;   /*!< CSYSPWRUPACK control register            Address offset 0x0040 */
       uint32_t RESERVED3[12017]; /*!< Reserved */
  __IO uint32_t WAKEPAR;          /*!< Wake GPIO Port A register                Address offset 0xBC08 */
  __IO uint32_t WAKEPBR;          /*!< Wake GPIO Port B register                Address offset 0xBC0C */
  __IO uint32_t WAKEPCR;          /*!< Wake GPIO Port C register                Address offset 0xBC10 */
       uint32_t RESERVED4[2];     /*!< Reserved */
  __IO uint32_t WAKEFILTR;        /*!< Wake filter register                     Address offset 0xBC1C */
} PWR_TypeDef; 
         
/** 
  * @brief Reset Registers 
  */
typedef struct
{
  __IO uint32_t SR;               /*!< Reset Status Register                    Address offset: 0x002C */
} RST_TypeDef;

/** 
  * @brief FLASH Registers
  */
typedef struct
{
  __IO uint32_t CLKER; 	          /*!< FLASH controller clock enable register   Address offset: 0x402C */
  __IO uint32_t CLKSR;	          /*!< FLASH controller clock status register   Address offset: 0x4030 */
       uint32_t RESERVED0[4083];  /*!< Reserved */
  __IO uint32_t ACR;              /*!< FLASH access control register,           Address offset: 0x8000 */
  __IO uint32_t KEYR;             /*!< FLASH key register,                      Address offset: 0x8004 */
  __IO uint32_t OPTKEYR;          /*!< FLASH OPT key register,                  Address offset: 0x8008 */
  __IO uint32_t SR;               /*!< FLASH status register,                   Address offset: 0x800C */
  __IO uint32_t CR;               /*!< FLASH control register,                  Address offset: 0x8010 */
  __IO uint32_t AR;               /*!< FLASH address register,                  Address offset: 0x8014 */
       uint32_t RESERVED1;        /*!< Reserved */
  __IO uint32_t OBR;              /*!< FLASH option bytes register,             Address offset: 0x801C */
  __IO uint32_t WRPR;             /*!< FLASH option bytes register,             Address offset: 0x8020 */
} FLASH_TypeDef;

/** 
  * @brief Memory Registers
  */
typedef struct
{
  __IO uint32_t RAMPROTR1;        /*!< Memory protection register1,             Address offset: 0x5000 */
  __IO uint32_t RAMPROTR2;        /*!< Memory protection register2,             Address offset: 0x5004 */
  __IO uint32_t RAMPROTR3;        /*!< Memory protection register3,             Address offset: 0x5008 */
  __IO uint32_t RAMPROTR4;        /*!< Memory protection register4,             Address offset: 0x500C */
  __IO uint32_t RAMPROTR5;        /*!< Memory protection register5,             Address offset: 0x5010 */
  __IO uint32_t RAMPROTR6;        /*!< Memory protection register6,             Address offset: 0x5014 */
  __IO uint32_t RAMPROTR7;        /*!< Memory protection register7,             Address offset: 0x5018 */
  __IO uint32_t RAMPROTR8;        /*!< Memory protection register8,             Address offset: 0x501C */
  __IO uint32_t DMAPROTR1;        /*!< DMA protection register1,                Address offset: 0x5020 */
  __IO uint32_t DMAPROTR2;        /*!< DMA protection register2,                Address offset: 0x5024 */
  __IO uint32_t RAMCR;            /*!< Memory configuration register,           Address offset: 0x5028 */
} MEM_TypeDef;

/** 
  * @brief Option Bytes Registers
  */
typedef struct
{
  __IO uint16_t RDP;              /*!< FLASH option byte Read protection,       Address 0x00 */
  __IO uint16_t Rsvd0;            /*!< Reserved */
  __IO uint16_t Rsvd1;            /*!< Reserved */
  __IO uint16_t Rsvd2;            /*!< Reserved */
  __IO uint16_t WRP0;             /*!< FLASH option byte write protection 0,    Address offset: 0x08 */
  __IO uint16_t WRP1;             /*!< FLASH option byte write protection 1,    Address offset: 0x0A */
  __IO uint16_t WRP2;             /*!< FLASH option byte write protection 2,    Address offset: 0x0C */
  __IO uint16_t WRP3;             /*!< FLASH option byte write protection 0,    Address offset: 0x0E */
} OB_TypeDef;

/** 
  * @brief GPIO Registers
  */
typedef struct
{
  __IO uint32_t CRL;              /*!< GPIO port configuration low register,    Address offset: 0x00 */
  __IO uint32_t CRH;              /*!< GPIO port configuration high register,   Address offset: 0x04 */
  __IO uint32_t IDR;              /*!< GPIO port input data register,           Address offset: 0x08 */
  __IO uint32_t ODR;              /*!< GPIO port output data register,          Address offset: 0x0C */
  __IO uint32_t BSR;              /*!< GPIO port bit set registerBSR,           Address offset: 0x10 */
  __IO uint32_t BRR;              /*!< GPIO port bit reset registerBRR,         Address offset: 0x14 */
} GPIO_TypeDef;
  
/** 
  * @brief GPIO Debug Registers
  */
typedef struct
{
  __IO uint32_t PCTRACECR;        /*!< Clock PC trace register,                 Address offset 0x4028 */
       uint32_t RESERVED[7925];
  __IO uint32_t DBGCR;            /*!< GPIO debug configuration register,       Address offset 0xBC00 */
  __IO uint32_t DBGSR;            /*!< GPIO debug status register,              Address offset 0xBC04 */
} GPIO_DBG_TypeDef;

/** 
  * @brief Management interrupt Registers
  */
typedef struct
{
  __IO uint32_t ISR;            /*!< Management Interrupt status Register,      Address offset 0xA018 */
       uint32_t RESERVED0[15];  /*!< Reserved */
  __IO uint32_t IER;            /*!< Management Interrupt Enable Register,      Address offset 0xA058 */
} MGMT_IT_TypeDef;

/** 
  * @brief EXTI Registers
  */

typedef struct
{  
  __IO uint32_t PR;               /*!< EXTI pending register,                   Address offset 0xA814 */
       uint32_t RESERVED0[18];    /*!< Reserved */
  __IO uint32_t TSR[4];           /*!< EXTI trigger source register,            Address offset 0xA860 */
       uint32_t RESERVED1[1257];  /*!< Reserved */
  __IO uint32_t CR[2];            /*!< EXTI configuration register,             Address offset 0xBC14 */
} EXTI_TypeDef;

/** 
  * @brief WDG Registers
  */

typedef struct
{
  __IO uint32_t CR;               /*!< WDG configuration register,      	      Address offset 0x6000 */
  __IO uint32_t KR;               /*!< WDG key register,      	                Address offset 0x6004 */
  __IO uint32_t KICKSR;           /*!< WDG kick-start register,      	          Address offset 0x6008 */
} WDG_TypeDef;

/** 
  * @brief Sleep Timer Registers
  */
typedef struct 
{
  __IO uint32_t CR;               /*!< SLPTMR configuration register,           Address offset 0x600C */
  __IO uint32_t CNTH;             /*!< SLPTMR counter high register,            Address offset 0x6010 */
  __IO uint32_t CNTL;             /*!< SLPTMR counter high register,            Address offset 0x6014 */
  __IO uint32_t CMPAH;            /*!< SLPTMR compare A high register,          Address offset 0x6018 */
  __IO uint32_t CMPAL;            /*!< SLPTMR compare A low register,           Address offset 0x601C */
  __IO uint32_t CMPBH;            /*!< SLPTMR compare B high register,          Address offset 0x6020 */
  __IO uint32_t CMPBL;            /*!< SLPTMR compare B low register,           Address offset 0x6024 */
       uint32_t RESERVED0[4091];  /*!< Reserved */
  __IO uint32_t ISR;              /*!< SLPTMR interrupt status register,        Address offset 0xA014 */
       uint32_t RESERVED1[2];     /*!< Reserved */
  __IO uint32_t IFR;              /*!< SLPTMR force interrupts register,        Address offset 0xA020 */
       uint32_t RESERVED2[12];    /*!< Reserved */
  __IO uint32_t IER;              /*!< SLPTMR interrupt enable register,        Address offset 0xA054 */
} SLPTMR_TypeDef;

/** 
  * @brief MAC Timer Registers
  */
typedef struct 
{
  __IO uint32_t CNTR;            /*!< MACTMR counter register,                  Address offset 0x2038 */
       uint32_t RESERVED[20];    /*!< Reserved */
  __IO uint32_t CR;              /*!< MACTMR configuration register,            Address offset 0x208C */
} MACTMR_TypeDef;

/** 
  * @brief  Analog to Digital Converter (ADC) Registers
  */ 
typedef struct
{  
  __IO uint32_t ISR;              /*!< ADC Interrupt Status Register,           Address offset: 0xA810 */
       uint32_t RESERVED0[15];    /*!< Reserved */
  __IO uint32_t IER;              /*!< ADC Interrupt Enable Register,           Address offset: 0xA850 */
       uint32_t RESERVED1[2540];  /*!< Reserved.*/
  __IO uint32_t CR;               /*!< ADC Configuration Register,              Address offset: 0xD004 */
  __IO uint32_t OFFSETR;          /*!< ADC Offset Register,                     Address offset: 0xD008 */
  __IO uint32_t GAINR;            /*!< ADC Gain Register,                       Address offset: 0xD00C */
  __IO uint32_t DMACR;            /*!< ADC DMA Configuration Register,          Address offset: 0xD010 */
  __IO uint32_t DMASR;            /*!< ADC DMA Status Register,                 Address offset: 0xD014 */
  __IO uint32_t DMAMSAR;          /*!< ADC DMA Memory Start Address Register,   Address offset: 0xD018 */
  __IO uint32_t DMANDTR;          /*!< ADC DMA Number of Data Register,         Address offset: 0xD01C */
  __IO uint32_t DMAMNAR;          /*!< ADC DMA Memory Next Address Register,    Address offset: 0xD020 */
  __IO uint32_t DMACNDTR;         /*!< ADC DMA Channel Number of Data Register, Address offset: 0xD024 */
} ADC_TypeDef;

/** 
  * @brief Timer Registers
  */
typedef struct 
{
 __IO uint32_t CR1;               /*!< TIM control register 1,                  Address offset 0x00 */
 __IO uint32_t CR2;               /*!< TIM control register 2,                  Address offset 0x04 */
 __IO uint32_t SMCR;              /*!< TIM slave Mode Control register,         Address offset 0x08 */
      uint32_t RESERVED0[2];      /*!< Reserved */
 __IO uint32_t EGR;               /*!< TIM event generation register            Address offset 0x14 */
 __IO uint32_t CCMR1;             /*!< TIM capture/compare mode register 1,     Address offset 0x18 */
 __IO uint32_t CCMR2;             /*!< TIM capture/compare mode register 2,     Address offset 0x1C */
 __IO uint32_t CCER;              /*!< TIM capture/compare enable register,     Address offset 0x20 */
 __IO uint32_t CNT;               /*!< TIM counter register,                    Address offset 0x24 */
 __IO uint32_t PSC;               /*!< TIM prescaler register,                  Address offset 0x28 */
 __IO uint32_t ARR;               /*!< TIM auto-reload register,                Address offset 0x2C */
      uint32_t RESERVED1;         /*!< Reserved */
 __IO uint32_t CCR1;              /*!< TIM capture/compare register 1,          Address offset 0x34 */
 __IO uint32_t CCR2;              /*!< TIM capture/compare register 2,          Address offset 0x38 */
 __IO uint32_t CCR3;              /*!< TIM capture/compare register 3,          Address offset 0x3C */
 __IO uint32_t CCR4;              /*!< TIM capture/compare register 4,          Address offset 0x40 */
      uint32_t RESERVED2[3];      /*!< Reserved */
 __IO uint32_t OR;                /*!< TIM option register,                     Address offset 0x50 */
} TIM_TypeDef;

/** 
  * @brief Serial Controller Registers (Universal Asynchronous Receiver/Transmitter)
  */ 
typedef struct
{
  __IO uint32_t DR;               /*!< Serial control Data register             Address offset 0x00 */
       uint32_t RESERVED0[2];     /*!< Reserved */
  __IO uint32_t UARTSR;           /*!< UART control register                    Address offset 0x08 */
       uint32_t RESERVED1[2];     /*!< Reserved */
  __IO uint32_t CR;               /*!< Serial control control register          Address offset 0x14 */
       uint32_t RESERVED2[1];     /*!< Reserved */
  __IO uint32_t UARTCR;           /*!< UART control register                    Address offset 0x1C */
       uint32_t RESERVED3[2];     /*!< Reserved */
  __IO uint32_t UARTBRR1;         /*!< UART Baud rate register 1                Address offset 0x28 */
  __IO uint32_t UARTBRR2;         /*!< UART Baud rate register 2                Address offset 0x2C */
} SC_UART_TypeDef;

/** 
  * @brief Serial Controller Registers (Serial peripheral interface)
  */ 
typedef struct
{
  __IO uint32_t DR;               /*!< Serial control Data register             Address offset 0x00 */
  __IO uint32_t SPISR;            /*!< SPI status register                      Address offset 0x04 */ 
       uint32_t RESERVED0[4];     /*!< Reserved */
  __IO uint32_t CR;               /*!< Serial control control register          Address offset 0x18 */
  __IO uint32_t SPICR;            /*!< SPI status register                      Address offset 0x1C */ 
       uint32_t RESERVED1[1];     /*!< Reserved */
  __IO uint32_t CRR1;             /*!< Serial control clock rate register 1     Address offset 0x24 */
  __IO uint32_t CRR2;             /*!< Serial control clock rate register 2     Address offset 0x28 */
} SC_SPI_TypeDef;

/** 
  * @brief Serial Controller Registers (Inter-Integrated circuit)
  */ 
typedef struct
{
  __IO uint32_t DR;               /*!< Serial control Data register             Address offset 0x00 */
       uint32_t RESERVED0[1];     /*!< Reserved */
  __IO uint32_t I2CSR;            /*!< I2C status register                      Address offset 0x08 */
       uint32_t RESERVED1[1];     /*!< Reserved */
  __IO uint32_t I2CCR1;           /*!< I2C control register 1                   Address offset 0x10 */
  __IO uint32_t I2CCR2;           /*!< I2C control register 2                   Address offset 0x14 */
  __IO uint32_t CR;               /*!< Serial control control register          Address offset 0x18 */
       uint32_t RESERVED2[2];     /*!< Reserved */
  __IO uint32_t CRR1;             /*!< Serial control clock rate register 1     Address offset 0x24 */
  __IO uint32_t CRR2;             /*!< Serial control clock rate register 2     Address offset 0x28 */
} SC_I2C_TypeDef;

/** 
  * @brief Timer Interrupt Registers
  */
typedef struct 
{
  __IO uint32_t ISR;              /*!< TIM interrupt and status register        Address offset 0x00 */
       uint32_t RESERVED0[5];     /*!< Reserved */
  __IO uint32_t IMR;              /*!< TIM interrupt missed register            Address offset 0x18 */
       uint32_t RESERVED1[9];     /*!< Reserved */
  __IO uint32_t IER;              /*!< TIM interrupt enable register            Address offset 0x40 */
} TIM_IT_TypeDef;

/** 
  * @brief Serial Controller interrupt Registers
  */ 
typedef struct
{
  __IO uint32_t ISR;              /*!< Interrupt Status register                Address offset 0x08 */
       uint32_t RESERVED0[15];    /*!< Reserved */
  __IO uint32_t IER;              /*!< Interrupt Enable register                Address offset 0x48 */
       uint32_t RESERVED1[2];     /*!< Reserved */
  __IO uint32_t ICR;              /*!< Interrupt Control register               Address offset 0x54 */
} SC_IT_TypeDef;

/** 
  * @brief Serial Controller DMA Registers
  */ 
typedef struct
{
  __IO uint32_t DMARXCNTAR;       /*!< DMA Rx counter A register                Address offset 0x20 */
  __IO uint32_t DMARXCNTBR;       /*!< DMA Rx counter B register                Address offset 0x24 */
  __IO uint32_t DMATXCNTR;        /*!< DMA Tx counter register                  Address offset 0x28 */
  __IO uint32_t DMASR;            /*!< DMA status register                      Address offset 0x2C */ 
  __IO uint32_t DMACR;            /*!< DMA control register                     Address offset 0x30 */ 
  __IO uint32_t DMARXERRAR;       /*!< DMA Rx error A register                  Address offset 0x34 */
  __IO uint32_t DMARXERRBR;       /*!< DMA Rx error B register                  Address offset 0x38 */
       uint32_t RESERVED0[13];    /*!< Reserved */
  __IO uint32_t DMARXCNTSAVEDR;   /*!< DMA Rx Counter saved register            Address offset 0x70 */ 
} SC_DMA_TypeDef;

/** 
  * @brief Serial Controller DMA Channel Registers
  */
typedef struct
{
  __IO uint32_t DMABEGADDAR;      /*!< DMA begin address A register             Address offset 0x00 */
  __IO uint32_t DMAENDADDAR;      /*!< DMA end address A register               Address offset 0x04 */
  __IO uint32_t DMABEGADDBR;      /*!< DMA begin address B register             Address offset 0x08 */
  __IO uint32_t DMAENDADDBR;      /*!< DMA end address B register               Address offset 0x0C */
} SC_DMA_Channel_TypeDef;

/** @addtogroup Peripheral_memory_map
  * @{
  */
#define FLASH_BASE                  ((uint32_t)0x08000000)       /*!< FLASH base address in the alias region */
#define SRAM_BASE                   ((uint32_t)0x20000000)       /*!< SRAM base address in the alias region */ 
#define PERIPH_BASE                 ((uint32_t)0x40000000)       /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE                ((uint32_t)0x22000000)       /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE              ((uint32_t)0x42000000)       /*!< Peripheral base address in the bit-band region */

/*!< Peripheral memory map */
#define PWR_BASE                    (PERIPH_BASE + 0x0004)
#define CLK_BASE                    (PERIPH_BASE + 0x0008)
#define RST_BASE                    (PERIPH_BASE + 0x002C)
#define MACTMR_BASE                 (PERIPH_BASE + 0x2038)
#define GPIO_DBG_BASE               (PERIPH_BASE + 0x4028)
#define FLASH_R_BASE                (PERIPH_BASE + 0x402C)
#define MEM_R_BASE                  (PERIPH_BASE + 0x5000)
#define WDG_BASE                    (PERIPH_BASE + 0x6000)
#define SLPTMR_BASE                 (PERIPH_BASE + 0x600C)
#define ADC_BASE                    (PERIPH_BASE + 0xA810)
#define EXTI_BASE                   (PERIPH_BASE + 0xA814)
#define GPIOA_BASE                  (PERIPH_BASE + 0xB000)
#define GPIOB_BASE                  (PERIPH_BASE + 0xB400)
#define GPIOC_BASE                  (PERIPH_BASE + 0xB800)
#define SC1_UART_BASE               (PERIPH_BASE + 0xC83C)
#define SC1_SPI_BASE                (PERIPH_BASE + 0xC83C)
#define SC1_I2C_BASE                (PERIPH_BASE + 0xC83C)
#define SC2_UART_BASE               (PERIPH_BASE + 0xC03C)
#define SC2_SPI_BASE                (PERIPH_BASE + 0xC03C)
#define SC2_I2C_BASE                (PERIPH_BASE + 0xC03C)
#define TIM1_BASE                   (PERIPH_BASE + 0xE000)
#define TIM2_BASE                   (PERIPH_BASE + 0xF000)
#define OB_BASE                     ((uint32_t)0x08040800)       /*!< Flash Option Bytes base address */

#define MGMT_IT_BASE                (PERIPH_BASE + 0xA018)
#define TIM1_IT_BASE                (PERIPH_BASE + 0xA800)
#define TIM2_IT_BASE                (PERIPH_BASE + 0xA804)
#define SC1_IT_BASE                 (PERIPH_BASE + 0xA808)
#define SC2_IT_BASE                 (PERIPH_BASE + 0xA80C)

#define SC2_DMA_ChannelRx_BASE      (PERIPH_BASE + 0xC000)
#define SC2_DMA_ChannelTx_BASE      (PERIPH_BASE + 0xC010)
#define SC2_DMA_BASE                (PERIPH_BASE + 0xC020)

#define SC1_DMA_ChannelRx_BASE      (PERIPH_BASE + 0xC800)
#define SC1_DMA_ChannelTx_BASE      (PERIPH_BASE + 0xC810)
#define SC1_DMA_BASE                (PERIPH_BASE + 0xC820)

/** @addtogroup Peripheral_declaration
  * @{
  */  

#define PWR                         ((PWR_TypeDef *) PWR_BASE)
#define CLK                         ((CLK_TypeDef *) CLK_BASE)
#define RST                         ((RST_TypeDef *) RST_BASE)
#define MACTMR                      ((MACTMR_TypeDef *) MACTMR_BASE)
#define GPIO_DBG                    ((GPIO_DBG_TypeDef *) GPIO_DBG_BASE)
#define FLASH                       ((FLASH_TypeDef *) FLASH_R_BASE)
#define MEM                         ((MEM_TypeDef *) MEM_R_BASE)
#define WDG                         ((WDG_TypeDef *) WDG_BASE)
#define SLPTMR                      ((SLPTMR_TypeDef *) SLPTMR_BASE)
#define EXTI                        ((EXTI_TypeDef *) EXTI_BASE)
#define GPIOA                       ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB                       ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC                       ((GPIO_TypeDef *) GPIOC_BASE)
#define SC1_UART                    ((SC_UART_TypeDef *) SC1_UART_BASE)
#define SC1_SPI                     ((SC_SPI_TypeDef *) SC1_SPI_BASE)
#define SC1_I2C                     ((SC_I2C_TypeDef *) SC1_I2C_BASE)
#define SC2_UART                    ((SC_UART_TypeDef *) SC2_UART_BASE)
#define SC2_SPI                     ((SC_SPI_TypeDef *) SC2_SPI_BASE)
#define SC2_I2C                     ((SC_I2C_TypeDef *) SC2_I2C_BASE)
#define ADC                         ((ADC_TypeDef *) ADC_BASE) 
#define TIM1                        ((TIM_TypeDef *) TIM1_BASE)
#define TIM2                        ((TIM_TypeDef *) TIM2_BASE)
#define OB                          ((OB_TypeDef *) OB_BASE)
 
#define MGMT_IT                     ((MGMT_IT_TypeDef *) MGMT_IT_BASE)
#define TIM1_IT                     ((TIM_IT_TypeDef *) TIM1_IT_BASE)
#define TIM2_IT                     ((TIM_IT_TypeDef *) TIM2_IT_BASE)
#define SC1_IT                      ((SC_IT_TypeDef *) SC1_IT_BASE)
#define SC2_IT                      ((SC_IT_TypeDef *) SC2_IT_BASE)

#define SC2_DMA_ChannelRx           ((SC_DMA_Channel_TypeDef *) SC2_DMA_ChannelRx_BASE)
#define SC2_DMA_ChannelTx           ((SC_DMA_Channel_TypeDef *) SC2_DMA_ChannelTx_BASE)
#define SC2_DMA                     ((SC_DMA_TypeDef *) SC2_DMA_BASE)

#define SC1_DMA_ChannelRx           ((SC_DMA_Channel_TypeDef *) SC1_DMA_ChannelRx_BASE)
#define SC1_DMA_ChannelTx           ((SC_DMA_Channel_TypeDef *) SC1_DMA_ChannelTx_BASE)
#define SC1_DMA                     ((SC_DMA_TypeDef *) SC1_DMA_BASE)

/**
  * @}
  */

/** @defgroup PPP_Exported_Constants
  * @{
  */ 

/** @defgroup Peripheral_Registers_Bits_Definition 
  * @{
  */ 

/******************************************************************************/
/*                                                                            */
/*                        Clock Control (CLK)                                 */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for CLK_SLEEPCR register  ***************/
#define  CLK_SLEEPCR_LSEEN                    ((uint32_t)0x00000001)       /*!< Enables 32kHz external XTAL */
#define  CLK_SLEEPCR_LSI10KEN                 ((uint32_t)0x00000002)       /*!< Enables 10kHz internal RC during deep */

/********************  Bit definition for CLK_LSI10KCR register  **************/
#define  CLK_LSI10KCR_TUNE                   ((uint32_t)0x0000000F)        /*!< Tune value for clkrc */

/********************  Bit definition for CLK_LSI1KCR register  ***************/
#define  CLK_LSI1KCR_CALFRAC                 ((uint32_t)0x000007FF)        /*!< Divider value fractional portion */
#define  CLK_LSI1KCR_CALINT                  ((uint32_t)0x0000F800)        /*!< Divider value integer portion */

/********************  Bit definition for CLK_HSECR1 register  ****************/
#define  CLK_HSECR1_BIASTRIM                 ((uint32_t)0x0000000F)        /*!< Bias trim setting for 24MHz oscillator */

/********************  Bit definition for CLK_HSICR register  *****************/
#define  CLK_HSICR_TUNE                      ((uint32_t)0x0000001F)        /*!< Frequency trim setting for HF RC oscillator */

/********************  Bit definition for CLK_HSECOMPR register  **************/
#define  CLK_HSECOMPR_HLEVEL                 ((uint32_t)0x00000002)        /*!< Frequency trim setting for HF RC oscillator */
#define  CLK_HSECOMPR_LLEVEL                 ((uint32_t)0x00000001)        /*!< Frequency trim setting for HF RC oscillator */

/********************  Bit definition for CLK_PERIODCR register  **************/
#define  CLK_PERIODCR_MODE                   ((uint32_t)0x00000003)        /*!< Sets clock to be measured by CLK_PERIOD */

/********************  Bit definition for CLK_PERIODSR register  **************/
#define  CLK_PERIODSR_PERIOD                 ((uint32_t)0x0000FFFF)        /*!< Clock period measurement */

/********************  Bit definition for CLK_DITHERCR register  **************/
#define  CLK_DITHERCR_DIS                    ((uint32_t)0x00000001)        /*!< Dither disable */

/********************  Bit definition for CLK_HSECR2 register  ****************/
#define  CLK_HSECR2_SW1                      ((uint32_t)0x00000001)        /*!< 0/1: OSCHF/XTAL is selected */
#define  CLK_HSECR2_EN                       ((uint32_t)0x00000002)        /*!< 1: 24 MHz crystal oscillator is main clock */

/********************  Bit definition for CLK_CPUCR register  *****************/
#define  CLK_CPUCR_SW2                       ((uint32_t)0x00000001)        /*!< 0/1: 12MHz/24MHz is selected */

/******************************************************************************/
/*                                                                            */
/*                        Reset Event source (RST)                            */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for RST_SR register  ********************/
#define  RST_SR_PWRHV                        ((uint32_t)0x00000001)        /*!< Normal power applied */
#define  RST_SR_PWRLV                        ((uint32_t)0x00000002)        /*!< The application of a Core power supply */
#define  RST_SR_PIN                          ((uint32_t)0x00000004)        /*!< External reset pin signal */
#define  RST_SR_WDG                          ((uint32_t)0x00000008)        /*!< Watchdog expiration */
#define  RST_SR_SWRST                        ((uint32_t)0x00000010)        /*!< Software reset */
#define  RST_SR_WKUP                         ((uint32_t)0x00000020)        /*!< Wake-up from Deep Sleep */
#define  RST_SR_OBFAIL                       ((uint32_t)0x00000040)        /*!< Option byte load failure */
#define  RST_SR_LKUP                         ((uint32_t)0x00000080)        /*!< Core lockup */

/******************************************************************************/
/*                                                                            */
/*                                    PWR                                     */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for PWR_DSLEEPCR1 register  **************/
#define PWR_DSLEEPCR1_LVFREEZE               ((uint32_t)0x00000002)        /*!< Freeze state LV output states */

/*******************  Bit definition for PWR_DSLEEPCR2 register  **************/
#define PWR_DSLEEPCR2_MODE                   ((uint32_t)0x00000001)        /*!< Selects deep sleep mode 0 when the debugger is attached */

/*******************  Bit definition for PWR_VREGCR register  *****************/
#define PWR_VREGCR_VREFEN                    ((uint32_t)0x00008000)        /*!< VREF on/off */

#define PWR_VREGCR_1V8EN                     ((uint32_t)0x00000800)        /*!< 1V8 direct controle of regulator on/off */
#define PWR_VREGCR_1V8TRIM                   ((uint32_t)0x00000380)        /*!< 1V2 regulator trim value */

#define PWR_VREGCR_1V2EN                     ((uint32_t)0x00000010)        /*!< 1V2 direct controle of regulator on/off */
#define PWR_VREGCR_1V2TRIM                   ((uint32_t)0x00000007)        /*!< 1V2 regulator trim value */

/*******************  Bit definition for PWR_WAKECR1 register  ****************/
#define PWR_WAKECR1_CSYSPWRRUPREQ            ((uint32_t)0x00000200)        /*!< Wake up method on CSYSPWRUPREQ event */
#define PWR_WAKECR1_CPWRRUPREQ               ((uint32_t)0x00000100)        /*!< Wake up method on CPWRRUPREQ event */
#define PWR_WAKECR1_CORE                     ((uint32_t)0x00000080)        /*!< Wake up method on COREWAKE bit */
#define PWR_WAKECR1_WRAP                     ((uint32_t)0x00000040)        /*!< Wake up method on sleep timer compare wrap/overflow event */
#define PWR_WAKECR1_COMPB                    ((uint32_t)0x00000020)        /*!< Wake up method on sleep timer compare B event */
#define PWR_WAKECR1_COMPA                    ((uint32_t)0x00000010)        /*!< Wake up method on sleep timer compare A event */
#define PWR_WAKECR1_IRQD                     ((uint32_t)0x00000008)        /*!< Wake up method on falling/rising edge of pin PC0*/
#define PWR_WAKECR1_SC2                      ((uint32_t)0x00000004)        /*!< Wake up method on falling/rising edge of pin PA2 for SC2 */
#define PWR_WAKECR1_SC1                      ((uint32_t)0x00000002)        /*!< Wake up method on falling/rising edge of pin PB2 for SC1*/
#define PWR_WAKECR1_MONEN                    ((uint32_t)0x00000001)        /*!< Enable the GPIO monitoring to wake from deep sleep */

/*******************  Bit definition for PWR_WAKECR2 register  ****************/
#define PWR_WAKECR2_COREWAKE                 ((uint32_t)0x00000020)        /*!< Power up controlled by debug port activity */

/*******************  Bit definition for PWR_WAKESR register ******************/
#define PWR_WAKESR_CSYSPWRRUPREQ             ((uint32_t)0x00000200)        /*!< Wake up done using the DAP access to SYS registers */
#define PWR_WAKESR_CPWRRUPREQ                ((uint32_t)0x00000100)        /*!< Wake up done using the DAP access to DBG registers */
#define PWR_WAKESR_CORE                      ((uint32_t)0x00000080)        /*!< Wake up done using debug port activity */
#define PWR_WAKESR_WRAP                      ((uint32_t)0x00000040)        /*!< Wake up done using sleep timer wrap */
#define PWR_WAKESR_COMPB                     ((uint32_t)0x00000020)        /*!< Wake up done using sleep timer compare B */
#define PWR_WAKESR_COMPA                     ((uint32_t)0x00000010)        /*!< Wake up done using sleep timer compare A */
#define PWR_WAKESR_IRQD                      ((uint32_t)0x00000008)        /*!< Wake up done using external interrupt IRQD */
#define PWR_WAKESR_SC2                       ((uint32_t)0x00000004)        /*!< Wake up done using serial controller 2 (PA2) */
#define PWR_WAKESR_SC1                       ((uint32_t)0x00000002)        /*!< Wake up done using serial controller 1 (PB2) */
#define PWR_WAKESR_MON                       ((uint32_t)0x00000001)        /*!< Wake up done using GPIO monitoring */

/*******************  Bit definition for PWR_CPWRUPREQSR register  ************/
#define PWR_CPWRUPREQSR_REQ                  ((uint32_t)0x00000001)        /*!< Current value of CPWRUPREQ */

/*******************  Bit definition for PWR_CSYSPWRUPREQSR register  *********/
#define PWR_CSYSPWRUPREQSR_REQ               ((uint32_t)0x00000001)        /*!< Current value of CSYSPWRUPREQ */

/*******************  Bit definition for PWR_CSYSPWRUPACKSR register  *********/
#define PWR_CSYSPWRUPACKSR_ACK               ((uint32_t)0x00000001)        /*!< Current value of CSYSPWRUPACK */

/*******************  Bit definition for PWR_CSYSPWRUPACKCR register  *********/
#define PWR_CSYSPWRUPACKCR_INHIBIT           ((uint32_t)0x00000001)        /*!< Inhibit CSYSPWRUPACK */

/*******************  Bit definition for PWR_WAKEPxR register  ****************/
#define PWR_WAKEPxR_Px0                      ((uint32_t)0x00000001)
#define PWR_WAKEPxR_Px1                      ((uint32_t)0x00000002)
#define PWR_WAKEPxR_Px2                      ((uint32_t)0x00000004)
#define PWR_WAKEPxR_Px3                      ((uint32_t)0x00000008)
#define PWR_WAKEPxR_Px4                      ((uint32_t)0x00000010)
#define PWR_WAKEPxR_Px5                      ((uint32_t)0x00000020)
#define PWR_WAKEPxR_Px6                      ((uint32_t)0x00000040)
#define PWR_WAKEPxR_Px7                      ((uint32_t)0x00000080)

/*******************  Bit definition for PWR_WAKEFILTR register  **************/
#define PWR_WAKEFILTR_GPIO                   ((uint32_t)0x00000001)        /*!< Enable filter on GPIO wakeup sources enabled by the PWR_WAKEPxR registers */
#define PWR_WAKEFILTR_SC1                    ((uint32_t)0x00000002)        /*!< Enable filter on GPIO wakeup source SC1 (PB2) */ 
#define PWR_WAKEFILTR_SC2                    ((uint32_t)0x00000004)        /*!< Enable filter on GPIO wakeup source SC2 (PA2) */ 
#define PWR_WAKEFILTR_IRQD                   ((uint32_t)0x00000008)        /*!< Enable filter on GPIO wakeup source EXTI D */ 

/******************************************************************************/
/*                                                                            */
/*                        Management interrupt (MGMT)                         */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for MGMT_ISR register  ******************/
#define  MGMT_ISR_HSECOMPLLIF                ((uint32_t)0x00000001)        /*!< HSE COMP Low Level flag */
#define  MGMT_ISR_HSECOMPHLIF                ((uint32_t)0x00000002)        /*!< HSE COMP High Level flag */

/********************  Bit definition for MGMT_IER register  ******************/
#define  MGMT_IER_HSECOMPLLIE                ((uint32_t)0x00000001)        /*!< HSE COMP Low Level Interrupt source */
#define  MGMT_IER_HSECOMPHLIE                ((uint32_t)0x00000002)        /*!< HSE COMP High Level Interrupt source */


/******************************************************************************/
/*                                                                            */
/*                      General Purpose IOs (GPIO)                            */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for GPIO_CRL register  *******************/
#define GPIO_CRL_CNFMODE0                    ((uint32_t)0x0000000F)        /*!< CNFMODE0[3:0] bits (GPIO Configuration and Mode Control) */
#define GPIO_CRL_CNFMODE0_0                  ((uint32_t)0x00000001)
#define GPIO_CRL_CNFMODE0_1                  ((uint32_t)0x00000002)
#define GPIO_CRL_CNFMODE0_2                  ((uint32_t)0x00000004)
#define GPIO_CRL_CNFMODE0_3                  ((uint32_t)0x00000008)
#define GPIO_CRL_CNFMODE1                    ((uint32_t)0x000000F0)        /*!< CNFMODE1[3:0] bits (GPIO Configuration and Mode Control) */
#define GPIO_CRL_CNFMODE1_0                  ((uint32_t)0x00000010)
#define GPIO_CRL_CNFMODE1_1                  ((uint32_t)0x00000020)
#define GPIO_CRL_CNFMODE1_2                  ((uint32_t)0x00000040)
#define GPIO_CRL_CNFMODE1_3                  ((uint32_t)0x00000080)
#define GPIO_CRL_CNFMODE2                    ((uint32_t)0x00000F00)        /*!< CNFMODE2[3:0] bits (GPIO Configuration and Mode Control) */
#define GPIO_CRL_CNFMODE2_0                  ((uint32_t)0x00000100)
#define GPIO_CRL_CNFMODE2_1                  ((uint32_t)0x00000200)
#define GPIO_CRL_CNFMODE2_2                  ((uint32_t)0x00000400)
#define GPIO_CRL_CNFMODE2_3                  ((uint32_t)0x00000800)
#define GPIO_CRL_CNFMODE3                    ((uint32_t)0x0000F000)        /*!< CNFMODE3[3:0] bits (GPIO Configuration and Mode Control) */
#define GPIO_CRL_CNFMODE3_0                  ((uint32_t)0x00001000)
#define GPIO_CRL_CNFMODE3_1                  ((uint32_t)0x00002000)
#define GPIO_CRL_CNFMODE3_2                  ((uint32_t)0x00004000)
#define GPIO_CRL_CNFMODE3_3                  ((uint32_t)0x00008000)

/*******************  Bit definition for GPIO_CRH register  *******************/
#define GPIO_CRH_CNFMODE4                    ((uint32_t)0x0000000F)        /*!< CNFMODE4[3:0] bits (GPIO Configuration and Mode Control) */
#define GPIO_CRH_CNFMODE4_0                  ((uint32_t)0x00000001)
#define GPIO_CRH_CNFMODE4_1                  ((uint32_t)0x00000002)
#define GPIO_CRH_CNFMODE4_2                  ((uint32_t)0x00000004)
#define GPIO_CRH_CNFMODE4_3                  ((uint32_t)0x00000008)
#define GPIO_CRH_CNFMODE5                    ((uint32_t)0x000000F0)        /*!< CNFMODE5[3:0] bits (GPIO Configuration and Mode Control) */
#define GPIO_CRH_CNFMODE5_0                  ((uint32_t)0x00000010)
#define GPIO_CRH_CNFMODE5_1                  ((uint32_t)0x00000020)
#define GPIO_CRH_CNFMODE5_2                  ((uint32_t)0x00000040)
#define GPIO_CRH_CNFMODE5_3                  ((uint32_t)0x00000080)
#define GPIO_CRH_CNFMODE6                    ((uint32_t)0x00000F00)        /*!< CNFMODE6[3:0] bits (GPIO Configuration and Mode Control) */
#define GPIO_CRH_CNFMODE6_0                  ((uint32_t)0x00000100)
#define GPIO_CRH_CNFMODE6_1                  ((uint32_t)0x00000200)
#define GPIO_CRH_CNFMODE6_2                  ((uint32_t)0x00000400)
#define GPIO_CRH_CNFMODE6_3                  ((uint32_t)0x00000800)
#define GPIO_CRH_CNFMODE7                    ((uint32_t)0x0000F000)        /*!< CNFMODE7[3:0] bits (GPIO Configuration and Mode Control) */
#define GPIO_CRH_CNFMODE7_0                  ((uint32_t)0x00001000)
#define GPIO_CRH_CNFMODE7_1                  ((uint32_t)0x00002000)
#define GPIO_CRH_CNFMODE7_2                  ((uint32_t)0x00004000)
#define GPIO_CRH_CNFMODE7_3                  ((uint32_t)0x00008000)

/*******************  Bit definition for GPIO_IDR register     ****************/ 
#define GPIO_IDR_IDR0                        ((uint32_t)0x00000001)
#define GPIO_IDR_IDR1                        ((uint32_t)0x00000002)
#define GPIO_IDR_IDR2                        ((uint32_t)0x00000004)
#define GPIO_IDR_IDR3                        ((uint32_t)0x00000008)
#define GPIO_IDR_IDR4                        ((uint32_t)0x00000010)
#define GPIO_IDR_IDR5                        ((uint32_t)0x00000020)
#define GPIO_IDR_IDR6                        ((uint32_t)0x00000040)
#define GPIO_IDR_IDR7                        ((uint32_t)0x00000080)

/*******************  Bit definition for GPIO_ODR register     ****************/
#define GPIO_ODR_ODR0                        ((uint32_t)0x00000001)
#define GPIO_ODR_ODR1                        ((uint32_t)0x00000002)
#define GPIO_ODR_ODR2                        ((uint32_t)0x00000004)
#define GPIO_ODR_ODR3                        ((uint32_t)0x00000008)
#define GPIO_ODR_ODR4                        ((uint32_t)0x00000010)
#define GPIO_ODR_ODR5                        ((uint32_t)0x00000020)
#define GPIO_ODR_ODR6                        ((uint32_t)0x00000040)
#define GPIO_ODR_ODR7                        ((uint32_t)0x00000080)

/*******************  Bit definition for GPIO_BRR register     ****************/
#define GPIO_BRR_BR0                         ((uint32_t)0x00000001)
#define GPIO_BRR_BR1                         ((uint32_t)0x00000002)
#define GPIO_BRR_BR2                         ((uint32_t)0x00000004)
#define GPIO_BRR_BR3                         ((uint32_t)0x00000008)
#define GPIO_BRR_BR4                         ((uint32_t)0x00000010)
#define GPIO_BRR_BR5                         ((uint32_t)0x00000020)
#define GPIO_BRR_BR6                         ((uint32_t)0x00000040)
#define GPIO_BRR_BR7                         ((uint32_t)0x00000080)

/*******************  Bit definition for GPIO_BSR register     ****************/
#define GPIO_BSR_BS0                         ((uint32_t)0x00000001)
#define GPIO_BSR_BS1                         ((uint32_t)0x00000002)
#define GPIO_BSR_BS2                         ((uint32_t)0x00000004)
#define GPIO_BSR_BS3                         ((uint32_t)0x00000008)
#define GPIO_BSR_BS4                         ((uint32_t)0x00000010)
#define GPIO_BSR_BS5                         ((uint32_t)0x00000020)
#define GPIO_BSR_BS6                         ((uint32_t)0x00000040)
#define GPIO_BSR_BS7                         ((uint32_t)0x00000080)

/********************  Bit definition for GPIO_PCTRACECR register  *************/
#define  GPIO_PCTRACECR_SEL                  ((uint32_t)0x00000001)        /*!< selects PC_TRACE source on bb_debug GPIO pins */

/*******************  Bit definition for GPIO_DBGCR   register ****************/
#define GPIO_DBGCR_PADDRIVE                  ((uint32_t)0x00000008)        /*!< Global Pad drive strength */
#define GPIO_DBGCR_EXTREGEN                  ((uint32_t)0x00000010)        /*!< Disable REG_EN override of PA7's normal GPIO configuration */
#define GPIO_DBGCR_DBGDIS                    ((uint32_t)0x00000020)        /*!< Disable debug interface override of normal GPIO configuration */
/*******************  Bit definition for GPIO_DBGSR register   ****************/
#define GPIO_DBGSR_SWEN                      ((uint32_t)0x00000001)        /*!< Status of Serial Wire interface */
#define GPIO_DBGSR_FORCEDBG                  ((uint32_t)0x00000002)        /*!< Status of debugger interface */
#define GPIO_DBGSR_BOOTMODE                  ((uint32_t)0x00000008)        /*!< Status of the nBOOTMODE signal sampled at the end of reset */
/******************************************************************************/
/*                                                                            */
/*                                      EXTI                                  */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for EXTI_CR register  ********************/
#define EXTI_CR_GPIO_SEL                     ((uint32_t)0x0000001F)        /*!< GPIO_SEL[4:0]bits  (GPIO EXTIx Selection) */
#define EXTI_CR_GPIO_SEL_0                   ((uint32_t)0x00000001)        /*!< bit0 */
#define EXTI_CR_GPIO_SEL_1                   ((uint32_t)0x00000002)        /*!< bit1 */
#define EXTI_CR_GPIO_SEL_2                   ((uint32_t)0x00000004)        /*!< bit2 */
#define EXTI_CR_GPIO_SEL_3                   ((uint32_t)0x00000008)        /*!< bit3 */
#define EXTI_CR_GPIO_SEL_4                   ((uint32_t)0x00000010)        /*!< bit4 */

/*******************  Bit definition for EXTI_TSR register     ****************/
#define EXTI_TSR_INTMOD                      ((uint32_t)0x000000E0)        /*!< INTMOD[7:5]bits  (EXTIx triggering mode) */
#define EXTI_TSR_INTMOD_0                    ((uint32_t)0x00000020)        /*!< bit5 */
#define EXTI_TSR_INTMOD_1                    ((uint32_t)0x00000040)        /*!< bit6 */
#define EXTI_TSR_INTMOD_2                    ((uint32_t)0x00000080)        /*!< bit7 */

#define EXTI_TSR_FILTEN                      ((uint32_t)0x00000100)        /*!< Set this bit to enable digital filtering on EXTIx */

/*******************  Bit definition for EXTI_PR register      ****************/
#define EXTI_PR_IRQAP                        ((uint32_t)0x00000001)        /*!< EXTIA interrupt pending */
#define EXTI_PR_IRQBP                        ((uint32_t)0x00000002)        /*!< EXTIB interrupt pending */
#define EXTI_PR_IRQCP                        ((uint32_t)0x00000004)        /*!< EXTIC interrupt pending */
#define EXTI_PR_IRQDP                        ((uint32_t)0x00000008)        /*!< EXTID interrupt pending */

/******************************************************************************/
/*                                                                            */
/*                                    WDG                                     */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for WDG_CR  register *********************/
#define WDG_CR_WDGEN                         ((uint32_t)0x00000001)        /*!< WDG enable */
#define WDG_CR_WDGDIS                        ((uint32_t)0x00000002)        /*!< WDG disable */

/*******************  Bit definition for WDG_KR  register *********************/
#define WDG_KR_KEY                           ((uint32_t)0x0000FFFF)        /*!< WDG key value */

/*******************  Bit definition for WDG_KICKSR  register *****************/
#define WDG_KICKSR_KS                        ((uint32_t)0x0000FFFF)        /*!< WDG kick start value */

/******************************************************************************/
/*                                                                            */
/*                               Sleep Timer                                  */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for SLPTMR_CR  register ******************/
#define SLPTMR_CR_CLKSEL                     ((uint32_t)0x00000001)        /*!< clock select */
#define SLPTMR_CR_PSC                        ((uint32_t)0x000000F0)        /*!< Sleep timer prescaler setting */
#define SLPTMR_CR_DBGP                       ((uint32_t)0x00000400)        /*!< Debug Pause */
#define SLPTMR_CR_EN                         ((uint32_t)0x00000800)        /*!< Enable/Disable Sleep Timer */
#define SLPTMR_CR_REVERSE                    ((uint32_t)0x00001000)        /*!< count forward or backword */

/*******************  Bit definition for SLPTMR_CNTH register *****************/
#define SLPTMR_CNTH_CNTH                     ((uint32_t)0x0000FFFF)        /*!< Sleep timer count high register */

/*******************  Bit definition for SLPTMR_CNTL register *****************/
#define SLPTMR_CNTL_CNTL                     ((uint32_t)0x0000FFFF)        /*!< Sleep timer count low register */

/*******************  Bit definition for SLPTMR_CMPAH register ****************/
#define SLPTMR_CMPAH_CMPAH                   ((uint32_t)0x0000FFFF)        /*!< Sleep timer compare A high register */

/*******************  Bit definition for SLPTMR_CMPAL register ****************/
#define SLPTMR_CMPAL_CMPAL                   ((uint32_t)0x0000FFFF)        /*!< Sleep timer compare A low register */

/*******************  Bit definition for SLPTMR_CMPBH register ****************/
#define SLPTMR_CMPBH_CMPBH                   ((uint32_t)0x0000FFFF)        /*!< Sleep timer compare B high register */

/*******************  Bit definition for SLPTMR_CMPBL register ****************/
#define SLPTMR_CMPBL_CMPBL                   ((uint32_t)0x0000FFFF)        /*!< Sleep timer compare B low register */

/*******************  Bit definition for SLPTMR_ISR register ******************/
#define SLPTMR_ISR_WRAP                      ((uint32_t)0x00000001)        /*!< Sleep timer overflow */
#define SLPTMR_ISR_CMPA                      ((uint32_t)0x00000002)        /*!< Sleep timer compare A */
#define SLPTMR_ISR_CMPB                      ((uint32_t)0x00000004)        /*!< Sleep timer compare B */

/*******************  Bit definition for SLPTMR_IFR register ******************/
#define SLPTMR_IFR_WRAP                      ((uint32_t)0x00000001)        /*!< Sleep timer overflow */
#define SLPTMR_IFR_CMPA                      ((uint32_t)0x00000002)        /*!< Sleep timer compare A */
#define SLPTMR_IFR_CMPB                      ((uint32_t)0x00000004)        /*!< Sleep timer compare B */

/*******************  Bit definition for SLPTMR_IER   register ****************/
#define SLPTMR_IER_WRAP                      ((uint32_t)0x00000001)        /*!< Sleep timer overflow */
#define SLPTMR_IER_CMPA                      ((uint32_t)0x00000002)        /*!< Sleep timer compare A */
#define SLPTMR_IER_CMPB                      ((uint32_t)0x00000004)        /*!< Sleep timer compare B */

/******************************************************************************/
/*                                                                            */
/*                                 MAC Timer                                  */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for SLPTMR_CNTR register *****************/
#define MACTMR_CNTR_CNT                     ((uint32_t)0x000FFFFF)         /*!< MAC timer count register */

/********************  Bit definition for MACTMR_CR register ******************/
#define MACTMR_CR_EN                        ((uint32_t)0x00000001)         /*!< MAC timer enable */
#define MACTMR_CR_RST                       ((uint32_t)0x00000002)         /*!< MAC timer reset */

/******************************************************************************/
/*                                                                            */
/*                        Analog to Digital Converter (ADC)                   */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for ADC_CR register  ********************/

#define  ADC_CR_ADON                         ((uint32_t)0x00000001)        /*!< ADC enable */
#define  ADC_CR_CLK                          ((uint32_t)0x00000004)        /*!< Clock selection */

/*!< MUXN configuration */
#define  ADC_CR_CHSELN                       ((uint32_t)0x00000078)        /*!< Input selection for the N channel */
#define  ADC_CR_CHSELN_0                     ((uint32_t)0x00000008)        /*!< Bit0 */
#define  ADC_CR_CHSELN_1                     ((uint32_t)0x00000010)        /*!< Bit1 */
#define  ADC_CR_CHSELN_2                     ((uint32_t)0x00000020)        /*!< Bit2 */
#define  ADC_CR_CHSELN_3                     ((uint32_t)0x00000040)        /*!< Bit3 */

/*!< MUXP configuration */
#define  ADC_CR_CHSELP                       ((uint32_t)0x00000780)        /*!< Input selection for the P channel */
#define  ADC_CR_CHSELP_0                     ((uint32_t)0x00000080)        /*!< Bit0 */
#define  ADC_CR_CHSELP_1                     ((uint32_t)0x00000100)        /*!< Bit1 */
#define  ADC_CR_CHSELP_2                     ((uint32_t)0x00000200)        /*!< Bit2 */
#define  ADC_CR_CHSELP_3                     ((uint32_t)0x00000400)        /*!< Bit3 */

/*!< HVSELN configuration */
#define  ADC_CR_HVSELN                       ((uint32_t)0x00000800)        /*!< Select voltage range for the N input channel */

/*!< HVSELP configuration */
#define  ADC_CR_HVSELP                       ((uint32_t)0x00001000)        /*!< Select voltage range for the P input channel */

/*!< PERIOD configuration */
#define  ADC_CR_SMP                          ((uint32_t)0x0000E000)        /*!< ADC sample time in clocks */
#define  ADC_CR_SMP_0                        ((uint32_t)0x00002000)        /*!< Bit0 */
#define  ADC_CR_SMP_1                        ((uint32_t)0x00004000)        /*!< Bit1 */
#define  ADC_CR_SMP_2                        ((uint32_t)0x00008000)        /*!< Bit2 */

/********************  Bit definition for ADC_OFFSETR register  ***************/

#define  ADC_OFFSETR_OFFSET                  ((uint32_t)0x0000FFFF)        /*!< 16-bit signed offset added to the basic ADC conversion 
                                                                                result before gain correction is applied.*/

/********************  Bit definition for ADC_GAINR register  *****************/

#define  ADC_GAINR_GAIN                      ((uint32_t)0x0000FFFF)        /*!< Gain factor that is multiplied by the offset-corrected 
                                                                                ADC result to produce the output value */
/********************  Bit definition for ADC_DMACR register  *****************/

#define  ADC_DMACR_LOAD                      ((uint32_t)0x00000001)        /*!< Starts the ADC DMA */
#define  ADC_DMACR_AUTOWRAP                  ((uint32_t)0x00000002)        /*!< Selects DMA mode */
#define  ADC_DMACR_RST                       ((uint32_t)0x00000010)        /*!< Reset the ADC DMA */

/********************  Bit definition for ADC_DMASR register  *****************/

#define  ADC_DMASR_ACT                       ((uint32_t)0x00000001)        /*!< DMA active */
#define  ADC_DMASR_OVF                       ((uint32_t)0x00000002)        /*!< DMA overflow */

/********************  Bit definition for ADC_DMAMSAR register  ***************/

#define  ADC_DMAMSAR_MSA                     ((uint32_t)0x00003FFF)        /*!< ADC buffer start address */

/********************  Bit definition for ADC_DMANDTR register  ***************/

#define  ADC_DMANDTR_NDT                     ((uint32_t)0x00001FFF)        /*!< ADC buffer size */

/********************  Bit definition for ADC_DMAMNAR register  ***************/

#define  ADC_DMAMNAR_MNA                     ((uint32_t)0x00003FFE)        /*!< Current DMA address */

/********************  Bit definition for ADC_DMACNDTR register  **************/

#define  ADC_DMACNDTR_CNDT                   ((uint32_t)0x00001FFF)        /*!< The number of 16-bit conversion results that have been
                                                                                     written to the buffer */
/********************  Bit definition for ADC_ISR register  *******************/

#define  ADC_ISR_ADCFLAG                     ((uint32_t)0x0000001F)        /*!< ADC interrupt flag register */
#define  ADC_ISR_ADCFLAG_0                   ((uint32_t)0x00000001)        /*!< Bit0: reserved and should always be set to 1 */
#define  ADC_ISR_DMABHF                      ((uint32_t)0x00000002)        /*!< DMA buffer half full interrupt pending */
#define  ADC_ISR_DMABF                       ((uint32_t)0x00000004)        /*!< DMA buffer full interrupt pending */
#define  ADC_ISR_SAT                         ((uint32_t)0x00000008)        /*!< Gain correction saturation interrupt pending */
#define  ADC_ISR_DMAOVF                      ((uint32_t)0x00000010)        /*!< DMA buffer overflow interrupt pending */

/********************  Bit definition for ADC_IER register  *******************/

#define  ADC_IER_ADCCFG                      ((uint32_t)0x0000001F)        /*!< ADC interrupt configuration register */
#define  ADC_IER_ADCCFG_0                    ((uint32_t)0x00000001)        /*!< Bit0: reserved and should always be set to 0 */
#define  ADC_IER_DMABHFIE                    ((uint32_t)0x00000002)        /*!< DMA buffer half full interrupt enable */
#define  ADC_IER_DMABFIE                     ((uint32_t)0x00000004)        /*!< DMA buffer full interrupt enable */
#define  ADC_IER_SATIE                       ((uint32_t)0x00000008)        /*!< Gain correction saturation interrupt enable */
#define  ADC_IER_DMAOVFIE                    ((uint32_t)0x00000010)        /*!< DMA buffer overflow interrupt enable */

/******************************************************************************/
/*                                                                            */
/*                      FLASH and Option Bytes Registers                      */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for FLASH_ACR register  ******************/
#define  FLASH_ACR_LATENCY                   ((uint32_t)0x00000007)        /*!< LATENCY[2:0] bits (Latency) */
#define  FLASH_ACR_LATENCY_0                 ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  FLASH_ACR_LATENCY_1                 ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  FLASH_ACR_LATENCY_2                 ((uint32_t)0x00000004)        /*!< Bit 2 */

#define  FLASH_ACR_HLFCYA                    ((uint32_t)0x00000008)        /*!< Flash Half Cycle Access Enable */
#define  FLASH_ACR_PRFTBE                    ((uint32_t)0x00000010)        /*!< Prefetch Buffer Enable */
#define  FLASH_ACR_PRFTBS                    ((uint32_t)0x00000020)        /*!< Prefetch Buffer Status */

/******************  Bit definition for FLASH_KEYR register  ******************/
#define  FLASH_KEYR_FKEYR                    ((uint32_t)0xFFFFFFFF)        /*!< FPEC Key */

/*****************  Bit definition for FLASH_OPTKEYR register  ****************/
#define  FLASH_OPTKEYR_OPTKEYR               ((uint32_t)0xFFFFFFFF)        /*!< Option Byte Key */

/******************  Bit definition for FLASH_SR register  ********************/
#define  FLASH_SR_BSY                        ((uint32_t)0x00000001)        /*!< Busy */
#define  FLASH_SR_PGERR                      ((uint32_t)0x00000004)        /*!< Programming Error */
#define  FLASH_SR_WRPRTERR                   ((uint32_t)0x00000010)        /*!< Write Protection Error */
#define  FLASH_SR_EOP                        ((uint32_t)0x00000020)        /*!< End of operation */

/*******************  Bit definition for FLASH_CR register  *******************/
#define  FLASH_CR_PG                         ((uint32_t)0x00000001)        /*!< Programming */
#define  FLASH_CR_PER                        ((uint32_t)0x00000002)        /*!< Page Erase */
#define  FLASH_CR_MER                        ((uint32_t)0x00000004)        /*!< Mass Erase */
#define  FLASH_CR_OPTPG                      ((uint32_t)0x00000010)        /*!< Option Byte Programming */
#define  FLASH_CR_OPTER                      ((uint32_t)0x00000020)        /*!< Option Byte Erase */
#define  FLASH_CR_STRT                       ((uint32_t)0x00000040)        /*!< Start */
#define  FLASH_CR_LOCK                       ((uint32_t)0x00000080)        /*!< Lock */
#define  FLASH_CR_OPTWRE                     ((uint32_t)0x00000200)        /*!< Option Bytes Write Enable */
#define  FLASH_CR_ERRIE                      ((uint32_t)0x00000400)        /*!< Error Interrupt Enable */
#define  FLASH_CR_EOPIE                      ((uint32_t)0x00001000)        /*!< End of operation interrupt enable */

/*******************  Bit definition for FLASH_AR register  *******************/
#define  FLASH_AR_FAR                        ((uint32_t)0xFFFFFFFF)        /*!< Flash Address */

/******************  Bit definition for FLASH_OBR register  *******************/
#define  FLASH_OBR_OPTERR                    ((uint32_t)0x00000001)        /*!< Option Byte Error */
#define  FLASH_OBR_RDPRT                     ((uint32_t)0x00000002)        /*!< Read protection */

/******************  Bit definition for FLASH_WRPR register  ******************/
#define  FLASH_WRPR_WRP                      ((uint32_t)0xFFFFFFFF)        /*!< Write Protect */

/******************  Bit definition for FLASH_CLKER register  *****************/
#define  FLASH_CLKER_EN                      ((uint32_t)0x00000001)        /*!< Request enabling of FPEC_CLK */

/******************  Bit definition for FLASH_CLKSR register  ******************/
#define  FLASH_CLKSR_ACK                     ((uint32_t)0x00000001)        /*!< Indicates FPEC_CLK is running and FCLK is 12MHz */
#define  FLASH_CLKSR_BSY                     ((uint32_t)0x00000002)        /*!< Indicates FPEC is Busy */

/*----------------------------------------------------------------------------*/

/******************  Bit definition for FLASH_RDP register  *******************/
#define  FLASH_RDP_RDP                       ((uint32_t)0x000000FF)        /*!< Read protection option byte */
#define  FLASH_RDP_nRDP                      ((uint32_t)0x0000FF00)        /*!< Read protection complemented option byte */

/******************  Bit definition for FLASH_Rsvd0 register ******************/
#define  FLASH_Rsvd0_Rsvd0                   ((uint32_t)0x00FF0000)        /*!< Reserved option byte */
#define  FLASH_Rsvd0_nRsvd0                  ((uint32_t)0xFF000000)        /*!< Reserved complemented option byte */

/******************  Bit definition for FLASH_Rsvd1 register  *****************/
#define  FLASH_Rsvd1_Rsvd1                   ((uint32_t)0x000000FF)        /*!< Reserved option byte */
#define  FLASH_Rsvd1_nRsvd1                  ((uint32_t)0x0000FF00)        /*!< Reserved complemented option byte */

/******************  Bit definition for FLASH_Rsvd2 register  *****************/
#define  FLASH_Rsvd2_Rsvd2                   ((uint32_t)0x00FF0000)        /*!< Reserved option byte */
#define  FLASH_Rsvd2_nRsvd2                   ((uint32_t)0xFF000000)       /*!< Reserved complemented option byte */

/******************  Bit definition for FLASH_WRP0 register  ******************/
#define  FLASH_WRP0_WRP0                     ((uint32_t)0x000000FF)        /*!< Flash memory write protection option bytes */
#define  FLASH_WRP0_nWRP0                    ((uint32_t)0x0000FF00)        /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRP1 register  ******************/
#define  FLASH_WRP1_WRP1                     ((uint32_t)0x00FF0000)        /*!< Flash memory write protection option bytes */
#define  FLASH_WRP1_nWRP1                    ((uint32_t)0xFF000000)        /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRP2 register  ******************/
#define  FLASH_WRP2_WRP2                     ((uint32_t)0x000000FF)        /*!< Flash memory write protection option bytes */
#define  FLASH_WRP2_nWRP2                    ((uint32_t)0x0000FF00)        /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRP3 register  ******************/
#define  FLASH_WRP3_WRP3                     ((uint32_t)0x00FF0000)        /*!< Flash memory write protection option bytes */
#define  FLASH_WRP3_nWRP3                    ((uint32_t)0xFF000000)        /*!< Flash memory write protection complemented option bytes */
/******************************************************************************/
/*                                                                            */
/*                       Serial Controllers Interface                         */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for SC_ISR register  ********************/

#define  SC_ISR_PE                           ((uint32_t)0x00004000)        /*!< UART Parity error pending interrupt */
#define  SC_ISR_FE                           ((uint32_t)0x00002000)        /*!< UART Frame error pending interrupt */
#define  SC_ISR_TXULODB                      ((uint32_t)0x00001000)        /*!< DMA transmit buffer B unloaded pending interrupt */
#define  SC_ISR_TXULODA                      ((uint32_t)0x00000800)        /*!< DMA transmit buffer A unloaded pending interrupt */
#define  SC_ISR_RXULODB                      ((uint32_t)0x00000400)        /*!< DMA receive buffer B unloaded pending interrupt */
#define  SC_ISR_RXULODA                      ((uint32_t)0x00000200)        /*!< DMA receive buffer A unloaded pending interrupt */
#define  SC_ISR_NACK                         ((uint32_t)0x00000100)        /*!< I2C not acknowledge received pending interrupt */
#define  SC_ISR_CMDFIN                       ((uint32_t)0x00000080)        /*!< I2C command complete detection pending interrupt */
#define  SC_ISR_BTF                          ((uint32_t)0x00000040)        /*!< I2C byte transmit finished pending interrupt */
#define  SC_ISR_BRF                          ((uint32_t)0x00000020)        /*!< I2C byte receive finished pending interrupt */
#define  SC_ISR_UND                          ((uint32_t)0x00000010)        /*!< Underrun pending interrupt */
#define  SC_ISR_OVR                          ((uint32_t)0x00000008)        /*!< Overrun pending interrupt */
#define  SC_ISR_IDLE                         ((uint32_t)0x00000004)        /*!< IDLE line detection pending interrupt */
#define  SC_ISR_TXE                          ((uint32_t)0x00000002)        /*!< Transmit data register empty pending interrupt */
#define  SC_ISR_RXNE                         ((uint32_t)0x00000001)        /*!< Data register not empty pending interrupt */

/********************  Bit definition for SC_IER register  ********************/

#define  SC_IER_PEIE                         ((uint32_t)0x00004000)        /*!< UART Parity error interrupt enable */
#define  SC_IER_FEIE                         ((uint32_t)0x00002000)        /*!< UART Frame error interrupt enable */
#define  SC_IER_TXULODBIE                    ((uint32_t)0x00001000)        /*!< DMA transmit buffer B unloaded interrupt enable */
#define  SC_IER_TXULODAIE                    ((uint32_t)0x00000800)        /*!< DMA transmit buffer A unloaded interrupt enable */
#define  SC_IER_RXULODBIE                    ((uint32_t)0x00000400)        /*!< DMA receive buffer B unloaded interrupt enable */
#define  SC_IER_RXULODAIE                    ((uint32_t)0x00000200)        /*!< DMA receive buffer A unloaded interrupt enable */
#define  SC_IER_NACKIE                       ((uint32_t)0x00000100)        /*!< I2C not acknowledge received interrupt enable */
#define  SC_IER_CMDFINIE                     ((uint32_t)0x00000080)        /*!< I2C command complete detection interrupt enable */
#define  SC_IER_BTFIE                        ((uint32_t)0x00000040)        /*!< I2C byte transmit finished interrupt enable */
#define  SC_IER_BRFIE                        ((uint32_t)0x00000020)        /*!< I2C byte receive finished interrupt enable */
#define  SC_IER_UNDIE                        ((uint32_t)0x00000010)        /*!< Underrun interrupt enable */
#define  SC_IER_OVRIE                        ((uint32_t)0x00000008)        /*!< Overrun interrupt enable */
#define  SC_IER_IDLEIE                       ((uint32_t)0x00000004)        /*!< IDLE line detection interrupt enable */
#define  SC_IER_TXEIE                        ((uint32_t)0x00000002)        /*!< Transmit data register empty interrupt enable */
#define  SC_IER_RXNEIE                       ((uint32_t)0x00000001)        /*!< Data register not empty interrupt enable */

/********************  Bit definition for SC_ICR register  ********************/
#define  SC_ICR_IDLELEVEL                    ((uint32_t)0x00000004)        /*!< Trigger event configuration to generate the IDLE interrupt */
#define  SC_ICR_TXELEVEL                     ((uint32_t)0x00000002)        /*!< Trigger event configuration to generate the TXE interrupt */
#define  SC_ICR_RXNELEVEL                    ((uint32_t)0x00000001)        /*!< Trigger event configuration to generate the RXNE interrupt */
   
/********************  Bit definition for SC_DMARXBEGADDAR register  **********/
#define  SC_DMARXBEGADDAR_ADD                ((uint32_t)0x00003FFF)        /*!< DMA channelA Rx begin address */

/********************  Bit definition for SC_DMARXENDADDAR register  **********/
#define  SC_DMARXENDADDAR_ADD                ((uint32_t)0x00003FFF)        /*!< DMA channelA Rx end address */

/********************  Bit definition for SC_DMARXBEGADDBR register  **********/
#define  SC_DMARXBEGADDBR_ADD                ((uint32_t)0x00003FFF)        /*!< DMA channelB Rx begin address */

/********************  Bit definition for SC_DMARXENDADDBR register  **********/
#define  SC_DMARXENDADDBR_ADD                ((uint32_t)0x00003FFF)        /*!< DMA channelB Rx end address */
   
/********************  Bit definition for SC_DMATXBEGADDAR register  **********/
#define  SC_DMATXBEGADDAR_ADD                ((uint32_t)0x00003FFF)        /*!< DMA channelA Tx begin address */

/********************  Bit definition for SC_DMARXENDADDBR register  **********/
#define  SC_DMATXENDADDAR_ADD                ((uint32_t)0x00003FFF)        /*!< DMA channelA Tx end address */
   
/********************  Bit definition for SC_DMATXBEGADDBR register  **********/
#define  SC_DMATXBEGADDBR_ADD                ((uint32_t)0x00003FFF)        /*!< DMA channelB Tx begin address */

/********************  Bit definition for SC_DMARXENDADDBR register  **********/
#define  SC_DMATXENDADDBR_ADD                ((uint32_t)0x00003FFF)        /*!< DMA channelB Tx end address */

/********************  Bit definition for SC_DMARXCNTAR register  *************/
#define  SC_DMARXCNTAR_CNT                   ((uint32_t)0x00003FFF)        /*!< Receive DMA counter A */
  
/********************  Bit definition for SC_DMARXCNTBR register  *************/
#define  SC_DMARXCNTBR_CNT                   ((uint32_t)0x00003FFF)        /*!< Receive DMA counter B */
    
/********************  Bit definition for SC_DMATXCNTR register  **************/
#define  SC_DMATXCNTR_CNT                    ((uint32_t)0x00003FFF)        /*!< Transmit DMA counter */
 
/********************  Bit definition for SC_DMASR register  ******************/
#define  SC_DMASR_NSSS                       ((uint32_t)0x00001C00)        /*!< NSSS[2:0] Status of the receiver count saved in the SCx_DMARXCNTSAVEDR when nSSEL deasserts */
#define  SC_DMASR_NSSS_0                     ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  SC_DMASR_NSSS_1                     ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  SC_DMASR_NSSS_2                     ((uint32_t)0x00001000)        /*!< Bit 2 */

#define  SC_DMASR_FEB                        ((uint32_t)0x00000200)        /*!< DMA channel B Frame error flag */
#define  SC_DMASR_FEA                        ((uint32_t)0x00000100)        /*!< DMA channel A Frame error flag */
#define  SC_DMASR_PEB                        ((uint32_t)0x00000080)        /*!< DMA channel B Parity error flag */
#define  SC_DMASR_PEA                        ((uint32_t)0x00000040)        /*!< DMA channel A Parity error flag */
#define  SC_DMASR_OVRB                       ((uint32_t)0x00000020)        /*!< DMA channel B overrun error flag */
#define  SC_DMASR_OVRA                       ((uint32_t)0x00000010)        /*!< DMA channel A overrun error flag */
#define  SC_DMASR_TXBACK                     ((uint32_t)0x00000008)        /*!< DMA Transmit channel B ACK flag */
#define  SC_DMASR_TXAACK                     ((uint32_t)0x00000004)        /*!< DMA Transmit channel A ACK flag */
#define  SC_DMASR_RXBACK                     ((uint32_t)0x00000002)        /*!< DMA Receive channel B ACK flag */
#define  SC_DMASR_RXAACK                     ((uint32_t)0x00000001)        /*!< DMA Receive channel B ACK flag */

/********************  Bit definition for SC_DMACR register  ******************/
#define  SC_DMACR_TXRST                      ((uint32_t)0x00000020)        /*!< DMA transmit Channels reset */
#define  SC_DMACR_RXRST                      ((uint32_t)0x00000010)        /*!< DMA receive Channels reset */
#define  SC_DMACR_TXLODB                     ((uint32_t)0x00000008)        /*!< DMA transmit Channel B load */
#define  SC_DMACR_TXLODA                     ((uint32_t)0x00000004)        /*!< DMA transmit Channel A load */
#define  SC_DMACR_RXLODB                     ((uint32_t)0x00000002)        /*!< DMA receive Channel B load */
#define  SC_DMACR_RXLODA                     ((uint32_t)0x00000001)        /*!< DMA receive Channel A load */

/********************  Bit definition for SC_DMARXERRAR register  *************/
#define  SC_DMARXERRAR_ADD                   ((uint32_t)0x00003FFF)                   /*! DMA receive channel A error offset address */

/********************  Bit definition for SC_DMARXERRBR register  *************/
#define  SC_DMARXERRBR_ADD                   ((uint32_t)0x00003FFF)                   /*! DMA receive channel B error offset address */

/********************  Bit definition for SC_DR register  *********************/
#define  SC_DR_DR                            ((uint32_t)0x000000FF)        /*!< Data value */

/********************  Bit definition for SC_SPISR register  ******************/
#define  SC_SPISR_IDLE                       ((uint32_t)0x00000008)        /*!< SPI Idle line detected flag */
#define  SC_SPISR_TXE                        ((uint32_t)0x00000004)        /*!< SPI Transmit data register empty flag */
#define  SC_SPISR_RXNE                       ((uint32_t)0x00000002)        /*!< SPI Data register not empty flag */
#define  SC_SPISR_OVR                        ((uint32_t)0x00000001)        /*!< SPI Overrun flag */

/********************  Bit definition for SC_I2CSR register  ******************/
#define  SC_I2CSR_CMDFIN                     ((uint32_t)0x00000008)        /*!< I2C Command finished flag */
#define  SC_I2CSR_BRF                        ((uint32_t)0x00000004)        /*!< I2C Byte received finished flag */
#define  SC_I2CSR_BTF                        ((uint32_t)0x00000002)        /*!< I2C Byte transfer finished flag  */
#define  SC_I2CSR_NACK                       ((uint32_t)0x00000001)        /*!< I2C Not acknowledge flag */

/********************  Bit definition for SC_UARTSR register  *****************/
#define  SC_UARTSR_IDLE                      ((uint32_t)0x00000040)        /*!< UART Idle line detected flag */
#define  SC_UARTSR_PE                        ((uint32_t)0x00000020)        /*!< UART Parity error flag */
#define  SC_UARTSR_FE                        ((uint32_t)0x00000010)        /*!< UART Frame error flag */
#define  SC_UARTSR_OVR                       ((uint32_t)0x00000008)        /*!< UART Overrun flag */
#define  SC_UARTSR_TXE                       ((uint32_t)0x00000004)        /*!< UART Transmit data register empty flag */
#define  SC_UARTSR_RXNE                      ((uint32_t)0x00000002)        /*!< UART Data register not empty flag */
#define  SC_UARTSR_CTS                       ((uint32_t)0x00000001)        /*!< UART Clear to send flag */

/********************  Bit definition for SC_I2CCR1 register  *****************/
#define  SC_I2CCR1_STOP                      ((uint32_t)0x00000008)        /*!< I2C stop command generation */
#define  SC_I2CCR1_START                     ((uint32_t)0x00000004)        /*!< I2C start command generation */
#define  SC_I2CCR1_BTE                       ((uint32_t)0x00000002)        /*!< I2C byte transmit enable */
#define  SC_I2CCR1_BRE                       ((uint32_t)0x00000001)        /*!< I2C byte receive enable */

/********************  Bit definition for SC_I2CCR2 register  *****************/
#define  SC_I2CCR2_ACK                       ((uint32_t)0x00000001)        /*!< I2C Not Acknowledge generation */

/********************  Bit definition for SC_CR register  *********************/
#define  SC_CR_MODE                          ((uint32_t)0x00000003)        /*!< MODE[1:0] Serial controller mode selection */
#define  SC_CR_MODE_0                        ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  SC_CR_MODE_1                        ((uint32_t)0x00000002)        /*!< Bit 1 */
  
/********************  Bit definition for SC_SPICR register  ******************/
#define  SC_SPICR_RXMODE                     ((uint32_t)0x00000020)        /*!< SPI Receiver-driven mode */
#define  SC_SPICR_MSTR                       ((uint32_t)0x00000010)        /*!< SPI Master mode selection */
#define  SC_SPICR_RPTEN                      ((uint32_t)0x00000008)        /*!< SPI transmit Repeat enable */
#define  SC_SPICR_LSBFIRST                   ((uint32_t)0x00000004)        /*!< SPI frame format */
#define  SC_SPICR_CPHA                       ((uint32_t)0x00000002)        /*!< SPI clock phase */
#define  SC_SPICR_CPOL                       ((uint32_t)0x00000001)        /*!< SPI clock polarity */

/********************  Bit definition for SC_UARTCR register  *****************/
#define  SC_UARTCR_AHFCE                     ((uint32_t)0x00000040)        /*!< UART automatic hardware flow control enable */
#define  SC_UARTCR_HFCE                      ((uint32_t)0x00000020)        /*!< UART hardware flow control enable */
#define  SC_UARTCR_PS                        ((uint32_t)0x00000010)        /*!< UART parity selection */
#define  SC_UARTCR_PCE                       ((uint32_t)0x00000008)        /*!< UART parity control enable */
#define  SC_UARTCR_STOP                      ((uint32_t)0x00000004)        /*!< UART number of STOP bits */
#define  SC_UARTCR_M                         ((uint32_t)0x00000002)        /*!< UART word length */
#define  SC_UARTCR_nRTS                      ((uint32_t)0x00000001)        /*!< UART request to send */

/********************  Bit definition for SC_CRR1 register  *******************/
#define  SC_CRR1_LIN                         ((uint32_t)0x0000000F)        /*!< LIN[3:0] The linear component of the clock rate */
#define  SC_CRR1_LIN_0                       ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  SC_CRR1_LIN_1                       ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  SC_CRR1_LIN_2                       ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  SC_CRR1_LIN_3                       ((uint32_t)0x00000008)        /*!< Bit 3 */

/********************  Bit definition for SC_CRR2 register  *******************/
#define  SC_CRR2_EXP                         ((uint32_t)0x0000000F)        /*!< EXP[3:0] The exponential component of the clock rate */
#define  SC_CRR2_EXP_0                       ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  SC_CRR2_EXP_1                       ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  SC_CRR2_EXP_2                       ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  SC_CRR2_EXP_3                       ((uint32_t)0x00000008)        /*!< Bit 3 */

/********************  Bit definition for SC_UARTBRR1 register  ***************/
#define  SC_UARTBRR1_N                       ((uint32_t)0x0000FFFF)        /*!< N[15:0] The integer part of baud rate period */

/********************  Bit definition for SC_UARTBRR2 register  ***************/
#define  SC_UARTBRR1_F                       ((uint32_t)0x00000001)        /*!< The fractional part of baud rate period */

/********************  Bit definition for SC_DMARXCNTSAVEDR register  *********/
#define  SC_DMARXCNTSAVEDR_CNT               ((uint32_t)0x00003FFF)        /*!< DMA received counter in SPI slave mode when nSSEL deasserts */

/******************************************************************************/
/*                                                                            */
/*                                    TIM                                     */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for TIM_CR1 register  ********************/
#define  TIM_CR1_CEN                         ((uint32_t)0x00000001)        /*!< Counter enable */
#define  TIM_CR1_UDIS                        ((uint32_t)0x00000002)        /*!< Update disable */
#define  TIM_CR1_URS                         ((uint32_t)0x00000004)        /*!< Update request source */
#define  TIM_CR1_OPM                         ((uint32_t)0x00000008)        /*!< One pulse mode */
#define  TIM_CR1_DIR                         ((uint32_t)0x00000010)        /*!< Direction */

#define  TIM_CR1_CMS                         ((uint32_t)0x00000060)        /*!< CMS[1:0] bits (Center-aligned mode selection) */
#define  TIM_CR1_CMS_0                       ((uint32_t)0x00000020)        /*!< Bit 0 */
#define  TIM_CR1_CMS_1                       ((uint32_t)0x00000040)        /*!< Bit 1 */

#define  TIM_CR1_ARPE                        ((uint32_t)0x00000080)        /*!< Auto-reload Buffer enable */

#define  TIM_CR1_CKD                         ((uint32_t)0x00000300)        /*!< CKD[1:0] bits (clock division) */
#define  TIM_CR1_CKD_0                       ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  TIM_CR1_CKD_1                       ((uint32_t)0x00000200)        /*!< Bit 1 */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define  TIM_CR2_MMS                         ((uint32_t)0x00000070)        /*!< MMS[2:0] bits (Master Mode Selection) */
#define  TIM_CR2_MMS_0                       ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  TIM_CR2_MMS_1                       ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  TIM_CR2_MMS_2                       ((uint32_t)0x00000040)        /*!< Bit 2 */

#define  TIM_CR2_TI1S                        ((uint32_t)0x00000080)        /*!< TI1 Selection */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define  TIM_SMCR_SMS                        ((uint32_t)0x00000007)        /*!< SMS[2:0] bits (Slave mode selection) */
#define  TIM_SMCR_SMS_0                      ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  TIM_SMCR_SMS_1                      ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  TIM_SMCR_SMS_2                      ((uint32_t)0x00000004)        /*!< Bit 2 */

#define  TIM_SMCR_TS                         ((uint32_t)0x00000070)        /*!< TS[2:0] bits (Trigger selection) */
#define  TIM_SMCR_TS_0                       ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  TIM_SMCR_TS_1                       ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  TIM_SMCR_TS_2                       ((uint32_t)0x00000040)        /*!< Bit 2 */

#define  TIM_SMCR_MSM                        ((uint32_t)0x00000080)        /*!< Master/slave mode */

#define  TIM_SMCR_ETF                        ((uint32_t)0x00000F00)        /*!< ETF[3:0] bits (External trigger filter) */
#define  TIM_SMCR_ETF_0                      ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  TIM_SMCR_ETF_1                      ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  TIM_SMCR_ETF_2                      ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  TIM_SMCR_ETF_3                      ((uint32_t)0x00000800)        /*!< Bit 3 */

#define  TIM_SMCR_ETPS                       ((uint32_t)0x00003000)        /*!< ETPS[1:0] bits (External trigger prescaler) */
#define  TIM_SMCR_ETPS_0                     ((uint32_t)0x00001000)        /*!< Bit 0 */
#define  TIM_SMCR_ETPS_1                     ((uint32_t)0x00002000)        /*!< Bit 1 */

#define  TIM_SMCR_ECE                        ((uint32_t)0x00004000)        /*!< External clock enable */
#define  TIM_SMCR_ETP                        ((uint32_t)0x00008000)        /*!< External trigger polarity */

/*******************  Bit definition for TIM_EGR register  ********************/
#define  TIM_EGR_UG                          ((uint32_t)0x000001)          /*!< Update Generation */
#define  TIM_EGR_CC1G                        ((uint32_t)0x000002)          /*!< Capture/Compare 1 Generation */
#define  TIM_EGR_CC2G                        ((uint32_t)0x000004)          /*!< Capture/Compare 2 Generation */
#define  TIM_EGR_CC3G                        ((uint32_t)0x000008)          /*!< Capture/Compare 3 Generation */
#define  TIM_EGR_CC4G                        ((uint32_t)0x000010)          /*!< Capture/Compare 4 Generation */
#define  TIM_EGR_COMG                        ((uint32_t)0x000020)          /*!< Capture/Compare Control Update Generation */
#define  TIM_EGR_TG                          ((uint32_t)0x000040)          /*!< Trigger Generation */
#define  TIM_EGR_BG                          ((uint32_t)0x000080)          /*!< Break Generation */

/******************  Bit definition for TIM_CCMR1 register  *******************/
#define  TIM_CCMR1_CC1S                      ((uint32_t)0x00000003)        /*!< CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define  TIM_CCMR1_CC1S_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  TIM_CCMR1_CC1S_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */

#define  TIM_CCMR1_OC1FE                     ((uint32_t)0x00000004)        /*!< Output Compare 1 Fast enable */
#define  TIM_CCMR1_OC1PE                     ((uint32_t)0x00000008)        /*!< Output Compare 1 Buffer enable */

#define  TIM_CCMR1_OC1M                      ((uint32_t)0x00000070)        /*!< OC1M[2:0] bits (Output Compare 1 Mode) */
#define  TIM_CCMR1_OC1M_0                    ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  TIM_CCMR1_OC1M_1                    ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  TIM_CCMR1_OC1M_2                    ((uint32_t)0x00000040)        /*!< Bit 2 */

#define  TIM_CCMR1_CC2S                      ((uint32_t)0x00000300)        /*!< CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define  TIM_CCMR1_CC2S_0                    ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  TIM_CCMR1_CC2S_1                    ((uint32_t)0x00000200)        /*!< Bit 1 */

#define  TIM_CCMR1_OC2FE                     ((uint32_t)0x00000400)        /*!< Output Compare 2 Fast enable */
#define  TIM_CCMR1_OC2PE                     ((uint32_t)0x00000800)        /*!< Output Compare 2 Buffer enable */

#define  TIM_CCMR1_OC2M                      ((uint32_t)0x00007000)        /*!< OC2M[2:0] bits (Output Compare 2 Mode) */
#define  TIM_CCMR1_OC2M_0                    ((uint32_t)0x00001000)        /*!< Bit 0 */
#define  TIM_CCMR1_OC2M_1                    ((uint32_t)0x00002000)        /*!< Bit 1 */
#define  TIM_CCMR1_OC2M_2                    ((uint32_t)0x00004000)        /*!< Bit 2 */

#define  TIM_CCMR1_IC1PSC                    ((uint32_t)0x0000000C)        /*!< IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define  TIM_CCMR1_IC1PSC_0                  ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  TIM_CCMR1_IC1PSC_1                  ((uint32_t)0x00000008)        /*!< Bit 1 */

#define  TIM_CCMR1_IC1F                      ((uint32_t)0x000000F0)        /*!< IC1F[3:0] bits (Input Capture 1 Filter) */
#define  TIM_CCMR1_IC1F_0                    ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  TIM_CCMR1_IC1F_1                    ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  TIM_CCMR1_IC1F_2                    ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  TIM_CCMR1_IC1F_3                    ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  TIM_CCMR1_IC2PSC                    ((uint32_t)0x00000C00)        /*!< IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define  TIM_CCMR1_IC2PSC_0                  ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  TIM_CCMR1_IC2PSC_1                  ((uint32_t)0x00000800)        /*!< Bit 1 */

#define  TIM_CCMR1_IC2F                      ((uint32_t)0x0000F000)        /*!< IC2F[3:0] bits (Input Capture 2 Filter) */
#define  TIM_CCMR1_IC2F_0                    ((uint32_t)0x00001000)        /*!< Bit 0 */
#define  TIM_CCMR1_IC2F_1                    ((uint32_t)0x00002000)        /*!< Bit 1 */
#define  TIM_CCMR1_IC2F_2                    ((uint32_t)0x00004000)        /*!< Bit 2 */
#define  TIM_CCMR1_IC2F_3                    ((uint32_t)0x00008000)        /*!< Bit 3 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define  TIM_CCMR2_CC3S                      ((uint32_t)0x00000003)        /*!< CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define  TIM_CCMR2_CC3S_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  TIM_CCMR2_CC3S_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */

#define  TIM_CCMR2_OC3FE                     ((uint32_t)0x00000004)        /*!< Output Compare 3 Fast enable */
#define  TIM_CCMR2_OC3PE                     ((uint32_t)0x00000008)        /*!< Output Compare 3 Buffer enable */

#define  TIM_CCMR2_OC3M                      ((uint32_t)0x00000070)        /*!< OC3M[2:0] bits (Output Compare 3 Mode) */
#define  TIM_CCMR2_OC3M_0                    ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  TIM_CCMR2_OC3M_1                    ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  TIM_CCMR2_OC3M_2                    ((uint32_t)0x00000040)        /*!< Bit 2 */

#define  TIM_CCMR2_CC4S                      ((uint32_t)0x00000300)        /*!< CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define  TIM_CCMR2_CC4S_0                    ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  TIM_CCMR2_CC4S_1                    ((uint32_t)0x00000200)        /*!< Bit 1 */

#define  TIM_CCMR2_OC4FE                     ((uint32_t)0x00000400)        /*!< Output Compare 4 Fast enable */
#define  TIM_CCMR2_OC4PE                     ((uint32_t)0x00000800)        /*!< Output Compare 4 Buffer enable */

#define  TIM_CCMR2_OC4M                      ((uint32_t)0x00007000)        /*!< OC4M[2:0] bits (Output Compare 4 Mode) */
#define  TIM_CCMR2_OC4M_0                    ((uint32_t)0x00001000)        /*!< Bit 0 */
#define  TIM_CCMR2_OC4M_1                    ((uint32_t)0x00002000)        /*!< Bit 1 */
#define  TIM_CCMR2_OC4M_2                    ((uint32_t)0x00004000)        /*!< Bit 2 */

#define  TIM_CCMR2_IC3PSC                    ((uint32_t)0x0000000C)        /*!< IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define  TIM_CCMR2_IC3PSC_0                  ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  TIM_CCMR2_IC3PSC_1                  ((uint32_t)0x00000008)        /*!< Bit 1 */

#define  TIM_CCMR2_IC3F                      ((uint32_t)0x000000F0)        /*!< IC3F[3:0] bits (Input Capture 3 Filter) */
#define  TIM_CCMR2_IC3F_0                    ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  TIM_CCMR2_IC3F_1                    ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  TIM_CCMR2_IC3F_2                    ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  TIM_CCMR2_IC3F_3                    ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  TIM_CCMR2_IC4PSC                    ((uint32_t)0x00000C00)        /*!< IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define  TIM_CCMR2_IC4PSC_0                  ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  TIM_CCMR2_IC4PSC_1                  ((uint32_t)0x00000800)        /*!< Bit 1 */

#define  TIM_CCMR2_IC4F                      ((uint32_t)0x0000F000)        /*!< IC4F[3:0] bits (Input Capture 4 Filter) */
#define  TIM_CCMR2_IC4F_0                    ((uint32_t)0x00001000)        /*!< Bit 0 */
#define  TIM_CCMR2_IC4F_1                    ((uint32_t)0x00002000)        /*!< Bit 1 */
#define  TIM_CCMR2_IC4F_2                    ((uint32_t)0x00004000)        /*!< Bit 2 */
#define  TIM_CCMR2_IC4F_3                    ((uint32_t)0x00008000)        /*!< Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define  TIM_CCER_CC1E                       ((uint32_t)0x00000001)        /*!< Capture/Compare 1 output enable */
#define  TIM_CCER_CC1P                       ((uint32_t)0x00000002)        /*!< Capture/Compare 1 output Polarity */
#define  TIM_CCER_CC2E                       ((uint32_t)0x00000010)        /*!< Capture/Compare 2 output enable */
#define  TIM_CCER_CC2P                       ((uint32_t)0x00000020)        /*!< Capture/Compare 2 output Polarity */
#define  TIM_CCER_CC3E                       ((uint32_t)0x00000100)        /*!< Capture/Compare 3 output enable */
#define  TIM_CCER_CC3P                       ((uint32_t)0x00000200)        /*!< Capture/Compare 3 output Polarity */
#define  TIM_CCER_CC4E                       ((uint32_t)0x00001000)        /*!< Capture/Compare 4 output enable */
#define  TIM_CCER_CC4P                       ((uint32_t)0x00002000)        /*!< Capture/Compare 4 output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define  TIM_CNT_CNT                         ((uint32_t)0x0000FFFF)        /*!< Counter Value */

/*******************  Bit definition for TIM_PSC register  ********************/
#define  TIM_PSC_PSC                         ((uint32_t)0x0000000F)        /*!< Prescaler Value */

/*******************  Bit definition for TIM_ARR register  ********************/
#define  TIM_ARR_ARR                         ((uint32_t)0x0000FFFF)        /*!< actual auto-reload Value */

/*******************  Bit definition for TIM_RCR register  ********************/
#define  TIM_RCR_REP                         ((uint32_t)0x0000FF)          /*!< Repetition Counter Value */

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define  TIM_CCR1_CCR1                       ((uint32_t)0x0000FFFF)        /*!< Capture/Compare 1 Value */

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define  TIM_CCR2_CCR2                       ((uint32_t)0x0000FFFF)        /*!< Capture/Compare 2 Value */

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define  TIM_CCR3_CCR3                       ((uint32_t)0x0000FFFF)        /*!< Capture/Compare 3 Value */
                                                                           
/*******************  Bit definition for TIM_CCR4 register  *******************/
#define  TIM_CCR4_CCR4                       ((uint32_t)0x0000FFFF)        /*!< Capture/Compare 4 Value */

/*******************  Bit definition for TIM1_OR register   *******************/
#define TIM1_OR_EXTRIGSEL                    ((uint32_t)0x00000003)        /*!< Selects the external trigger used in external clock mode 2 */
#define TIM1_OR_EXTRIGSEL_0                  ((uint32_t)0x00000001)        /*!< Bit 0 */
#define TIM1_OR_EXTRIGSEL_1                  ((uint32_t)0x00000002)        /*!< Bit 1 */

#define TIM1_OR_CLKMSKEN                     ((uint32_t)0x00000004)        /*!< Enables TIM1MSK when TIM1CLK is selected as the external trigger */
#define TIM1_OR_ORRSVD                       ((uint32_t)0x00000008)        /*!< Reserved: this bit must always be set to 0 */

/*******************  Bit definition for TIM2_OR register   *******************/
#define TIM2_OR_EXTRIGSEL                    ((uint32_t)0x00000003)        /*!< Selects the external trigger used in external clock mode 2 */
#define TIM2_OR_EXTRIGSEL_0                  ((uint32_t)0x00000001)        /*!< Bit 0 */
#define TIM2_OR_EXTRIGSEL_1                  ((uint32_t)0x00000002)        /*!< Bit 1 */

#define TIM2_OR_CLKMSKEN                     ((uint32_t)0x00000004)        /*!< Enables TIM2MSK when TIM2CLK is selected as the external trigger */
#define TIM2_OR_ORRSVD                       ((uint32_t)0x00000008)        /*!< Reserved: this bit must always be set to 0 */
#define TIM2_OR_REMAPC1                      ((uint32_t)0x00000010)        /*!< Selects the GPIO used for TIM2_CH1 */
#define TIM2_OR_REMAPC2                      ((uint32_t)0x00000020)        /*!< Selects the GPIO used for TIM2_CH2 */
#define TIM2_OR_REMAPC3                      ((uint32_t)0x00000040)        /*!< Selects the GPIO used for TIM2_CH3 */
#define TIM2_OR_REMAPC4                      ((uint32_t)0x00000080)        /*!< Selects the GPIO used for TIM2_CH4 */

/*******************  Bit definition for TIM_IER register        **************/
#define TIM_IER_UIE                         ((uint32_t)0x00000001)         /*!< Update interrupt enable */
#define TIM_IER_CC1IE                       ((uint32_t)0x00000002)         /*!< Capture or compare 1 interrupt enable */
#define TIM_IER_CC2IE                       ((uint32_t)0x00000004)         /*!< Capture or compare 2 interrupt enable */
#define TIM_IER_CC3IE                       ((uint32_t)0x00000008)         /*!< Capture or compare 3 interrupt enable */
#define TIM_IER_CC4IE                       ((uint32_t)0x00000010)         /*!< Capture or compare 4 interrupt enable */
#define TIM_IER_TIE                         ((uint32_t)0x00000040)         /*!< Trigger interrupt enable */
 
/*******************  Bit definition for TIM_ISR register        **************/
#define TIM_ISR_UIP                         ((uint32_t)0x00000001)         /*!< Update interrupt pending */
#define TIM_ISR_CC1IP                       ((uint32_t)0x00000002)         /*!< Capture or compare 1 interrupt pending */
#define TIM_ISR_CC2IP                       ((uint32_t)0x00000004)         /*!< Capture or compare 2 interrupt pending */
#define TIM_ISR_CC3IP                       ((uint32_t)0x00000008)         /*!< Capture or compare 3 interrupt pending */
#define TIM_ISR_CC4IP                       ((uint32_t)0x00000010)         /*!< Capture or compare 4 interrupt pending */
#define TIM_ISR_TIP                         ((uint32_t)0x00000040)         /*!< Trigger interrupt */

#define TIM_ISR_RSVD                        ((uint32_t)0x00001E00)         /*!< Reserved: May change during normal operation */
#define TIM_ISR_RSVD_0                      ((uint32_t)0x00001E00)         /*!< Bit 0 */
#define TIM_ISR_RSVD_1                      ((uint32_t)0x00001E00)         /*!< Bit 1 */
#define TIM_ISR_RSVD_3                      ((uint32_t)0x00001E00)         /*!< Bit 2 */

/*******************  Bit definition for TIM_IMR register        **************/
#define TIM_IMR_RSVD                        ((uint32_t)0x000000EF)         /*!< Reserved: May change during normal operation */
#define TIM_IMR_RSVD_0                      ((uint32_t)0x00000001)         /*!< Bit 0 */
#define TIM_IMR_RSVD_1                      ((uint32_t)0x00000002)         /*!< Bit 1 */
#define TIM_IMR_RSVD_2                      ((uint32_t)0x00000004)         /*!< Bit 2 */
#define TIM_IMR_RSVD_3                      ((uint32_t)0x00000008)         /*!< Bit 3 */
#define TIM_IMR_RSVD_4                      ((uint32_t)0x00000010)         /*!< Bit 4 */
#define TIM_IMR_RSVD_5                      ((uint32_t)0x00000020)         /*!< Bit 5 */
#define TIM_IMR_RSVD_6                      ((uint32_t)0x00000040)         /*!< Bit 6 */

#define TIM_IMR_CC1IM                       ((uint32_t)0x00000200)         /*!< Capture or compare 1 interrupt missed */
#define TIM_IMR_CC2IM                       ((uint32_t)0x00000400)         /*!< Capture or compare 2 interrupt missed */
#define TIM_IMR_CC3IM                       ((uint32_t)0x00000800)         /*!< Capture or compare 3 interrupt missed */
#define TIM_IMR_CC4IM                       ((uint32_t)0x00001000)         /*!< Capture or compare 4 interrupt missed */

/******************************************************************************/
/*                                                                            */
/*                               SystemTick                                   */
/*                                                                            */
/******************************************************************************/

/*****************  Bit definition for SysTick_CTRL register  *****************/
#define  SysTick_CTRL_ENABLE                 ((uint32_t)0x00000001)        /*!< Counter enable */
#define  SysTick_CTRL_TICKINT                ((uint32_t)0x00000002)        /*!< Counting down to 0 pends the SysTick handler */
#define  SysTick_CTRL_CLKSOURCE              ((uint32_t)0x00000004)        /*!< Clock source */
#define  SysTick_CTRL_COUNTFLAG              ((uint32_t)0x00010000)        /*!< Count Flag */

/*****************  Bit definition for SysTick_LOAD register  *****************/
#define  SysTick_LOAD_RELOAD                 ((uint32_t)0x00FFFFFF)        /*!< Value to load into the SysTick Current Value Register when the counter reaches 0 */

/*****************  Bit definition for SysTick_VAL register  ******************/
#define  SysTick_VAL_CURRENT                 ((uint32_t)0x00FFFFFF)        /*!< Current value at the time the register is accessed */

/*****************  Bit definition for SysTick_CALIB register  ****************/
#define  SysTick_CALIB_TENMS                 ((uint32_t)0x00FFFFFF)        /*!< Reload value to use for 10ms timing */
#define  SysTick_CALIB_SKEW                  ((uint32_t)0x40000000)        /*!< Calibration value is not exactly 10 ms */
#define  SysTick_CALIB_NOREF                 ((uint32_t)0x80000000)        /*!< The reference clock is not provided */

/******************************************************************************/
/*                                                                            */
/*                  Nested Vectored Interrupt Controller                      */
/*                                                                            */
/******************************************************************************/

/*Bit definition for NVIC_ISER, NVIC_ICER, NVIC_ISPR, NVIC_ICPR and NVIC_IABR**/
#define  NVIC_IxxR_TIM1                      ((uint32_t)0x00000001)        /*!< bit 0 */
#define  NVIC_IxxR_TIM2                      ((uint32_t)0x00000002)        /*!< bit 1 */
#define  NVIC_IxxR_MGMT                      ((uint32_t)0x00000004)        /*!< bit 2 */
#define  NVIC_IxxR_SLEEPTMR                  ((uint32_t)0x00000010)        /*!< bit 4 */
#define  NVIC_IxxR_SC1                       ((uint32_t)0x00000020)        /*!< bit 5 */
#define  NVIC_IxxR_SC2                       ((uint32_t)0x00000040)        /*!< bit 6 */
#define  NVIC_IxxR_ADC                       ((uint32_t)0x00000800)        /*!< bit 11 */
#define  NVIC_IxxR_IRQA                      ((uint32_t)0x00001000)        /*!< bit 12 */
#define  NVIC_IxxR_IRQB                      ((uint32_t)0x00002000)        /*!< bit 13 */
#define  NVIC_IxxR_IRQC                      ((uint32_t)0x00004000)        /*!< bit 14 */
#define  NVIC_IxxR_IRQD                      ((uint32_t)0x00008000)        /*!< bit 15 */
#define  NVIC_IxxR_DEBUG                     ((uint32_t)0x00010000)        /*!< bit 16 */

/******************  Bit definition for NVIC_ISER register  *******************/
#define  NVIC_ISER_TIM1                      ((uint32_t)0x00000001)        /*!< bit 0 */
#define  NVIC_ISER_TIM2                      ((uint32_t)0x00000002)        /*!< bit 1 */
#define  NVIC_ISER_MGMT                      ((uint32_t)0x00000004)        /*!< bit 2 */
#define  NVIC_ISER_SLEEPTMR                  ((uint32_t)0x00000010)        /*!< bit 4 */
#define  NVIC_ISER_SC1                       ((uint32_t)0x00000020)        /*!< bit 5 */
#define  NVIC_ISER_SC2                       ((uint32_t)0x00000040)        /*!< bit 6 */
#define  NVIC_ISER_ADC                       ((uint32_t)0x00000800)        /*!< bit 11 */
#define  NVIC_ISER_IRQA                      ((uint32_t)0x00001000)        /*!< bit 12 */
#define  NVIC_ISER_IRQB                      ((uint32_t)0x00002000)        /*!< bit 13 */
#define  NVIC_ISER_IRQC                      ((uint32_t)0x00004000)        /*!< bit 14 */
#define  NVIC_ISER_IRQD                      ((uint32_t)0x00008000)        /*!< bit 15 */
#define  NVIC_ISER_DEBUG                     ((uint32_t)0x00010000)        /*!< bit 16 */

/******************  Bit definition for NVIC_ICER register  *******************/
#define  NVIC_ICER_TIM1                      ((uint32_t)0x00000001)        /*!< bit 0 */
#define  NVIC_ICER_TIM2                      ((uint32_t)0x00000002)        /*!< bit 1 */
#define  NVIC_ICER_MGMT                      ((uint32_t)0x00000004)        /*!< bit 2 */
#define  NVIC_ICER_SLEEPTMR                  ((uint32_t)0x00000010)        /*!< bit 4 */
#define  NVIC_ICER_SC1                       ((uint32_t)0x00000020)        /*!< bit 5 */
#define  NVIC_ICER_SC2                       ((uint32_t)0x00000040)        /*!< bit 6 */
#define  NVIC_ICER_ADC                       ((uint32_t)0x00000800)        /*!< bit 11 */
#define  NVIC_ICER_IRQA                      ((uint32_t)0x00001000)        /*!< bit 12 */
#define  NVIC_ICER_IRQB                      ((uint32_t)0x00002000)        /*!< bit 13 */
#define  NVIC_ICER_IRQC                      ((uint32_t)0x00004000)        /*!< bit 14 */
#define  NVIC_ICER_IRQD                      ((uint32_t)0x00008000)        /*!< bit 15 */
#define  NVIC_ICER_DEBUG                     ((uint32_t)0x00010000)        /*!< bit 16 */ 

/******************  Bit definition for NVIC_ISPR register  *******************/
#define  NVIC_ISPR_TIM1                      ((uint32_t)0x00000001)        /*!< bit 0 */
#define  NVIC_ISPR_TIM2                      ((uint32_t)0x00000002)        /*!< bit 1 */
#define  NVIC_ISPR_MGMT                      ((uint32_t)0x00000004)        /*!< bit 2 */
#define  NVIC_ISPR_SLEEPTMR                  ((uint32_t)0x00000010)        /*!< bit 4 */
#define  NVIC_ISPR_SC1                       ((uint32_t)0x00000020)        /*!< bit 5 */
#define  NVIC_ISPR_SC2                       ((uint32_t)0x00000040)        /*!< bit 6 */
#define  NVIC_ISPR_ADC                       ((uint32_t)0x00000800)        /*!< bit 11 */
#define  NVIC_ISPR_IRQA                      ((uint32_t)0x00001000)        /*!< bit 12 */
#define  NVIC_ISPR_IRQB                      ((uint32_t)0x00002000)        /*!< bit 13 */
#define  NVIC_ISPR_IRQC                      ((uint32_t)0x00004000)        /*!< bit 14 */
#define  NVIC_ISPR_IRQD                      ((uint32_t)0x00008000)        /*!< bit 15 */
#define  NVIC_ISPR_DEBUG                     ((uint32_t)0x00010000)        /*!< bit 16 */ 

/******************  Bit definition for NVIC_ICPR register  *******************/
#define  NVIC_ICPR_TIM1                      ((uint32_t)0x00000001)        /*!< bit 0 */
#define  NVIC_ICPR_TIM2                      ((uint32_t)0x00000002)        /*!< bit 1 */
#define  NVIC_ICPR_MGMT                      ((uint32_t)0x00000004)        /*!< bit 2 */
#define  NVIC_ICPR_SLEEPTMR                  ((uint32_t)0x00000010)        /*!< bit 4 */
#define  NVIC_ICPR_SC1                       ((uint32_t)0x00000020)        /*!< bit 5 */
#define  NVIC_ICPR_SC2                       ((uint32_t)0x00000040)        /*!< bit 6 */
#define  NVIC_ICPR_ADC                       ((uint32_t)0x00000800)        /*!< bit 11 */
#define  NVIC_ICPR_IRQA                      ((uint32_t)0x00001000)        /*!< bit 12 */
#define  NVIC_ICPR_IRQB                      ((uint32_t)0x00002000)        /*!< bit 13 */
#define  NVIC_ICPR_IRQC                      ((uint32_t)0x00004000)        /*!< bit 14 */
#define  NVIC_ICPR_IRQD                      ((uint32_t)0x00008000)        /*!< bit 15 */
#define  NVIC_ICPR_DEBUG                     ((uint32_t)0x00010000)        /*!< bit 16 */ 

/******************  Bit definition for NVIC_IABR register  *******************/
#define  NVIC_IABR_TIM1                      ((uint32_t)0x00000001)        /*!< bit 0 */
#define  NVIC_IABR_TIM2                      ((uint32_t)0x00000002)        /*!< bit 1 */
#define  NVIC_IABR_MGMT                      ((uint32_t)0x00000004)        /*!< bit 2 */
#define  NVIC_IABR_SLEEPTMR                  ((uint32_t)0x00000010)        /*!< bit 4 */
#define  NVIC_IABR_SC1                       ((uint32_t)0x00000020)        /*!< bit 5 */
#define  NVIC_IABR_SC2                       ((uint32_t)0x00000040)        /*!< bit 6 */
#define  NVIC_IABR_ADC                       ((uint32_t)0x00000800)        /*!< bit 11 */
#define  NVIC_IABR_IRQA                      ((uint32_t)0x00001000)        /*!< bit 12 */
#define  NVIC_IABR_IRQB                      ((uint32_t)0x00002000)        /*!< bit 13 */
#define  NVIC_IABR_IRQC                      ((uint32_t)0x00004000)        /*!< bit 14 */
#define  NVIC_IABR_IRQD                      ((uint32_t)0x00008000)        /*!< bit 15 */
#define  NVIC_IABR_DEBUG                     ((uint32_t)0x00010000)        /*!< bit 16 */ 

/******************  Bit definition for NVIC_PRI0 register  *******************/
#define  NVIC_IPR0_PRI_0                     ((uint32_t)0x000000FF)        /*!< Priority of interrupt 0 */
#define  NVIC_IPR0_PRI_1                     ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 1 */
#define  NVIC_IPR0_PRI_2                     ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 2 */
#define  NVIC_IPR0_PRI_3                     ((uint32_t)0xFF000000)        /*!< Priority of interrupt 3 */

/******************  Bit definition for NVIC_PRI1 register  *******************/
#define  NVIC_IPR1_PRI_4                     ((uint32_t)0x000000FF)        /*!< Priority of interrupt 4 */
#define  NVIC_IPR1_PRI_5                     ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 5 */
#define  NVIC_IPR1_PRI_6                     ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 6 */
#define  NVIC_IPR1_PRI_7                     ((uint32_t)0xFF000000)        /*!< Priority of interrupt 7 */

/******************  Bit definition for NVIC_PRI2 register  *******************/
#define  NVIC_IPR2_PRI_8                     ((uint32_t)0x000000FF)        /*!< Priority of interrupt 8 */
#define  NVIC_IPR2_PRI_9                     ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 9 */
#define  NVIC_IPR2_PRI_10                    ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 10 */
#define  NVIC_IPR2_PRI_11                    ((uint32_t)0xFF000000)        /*!< Priority of interrupt 11 */

/******************  Bit definition for NVIC_PRI3 register  *******************/
#define  NVIC_IPR3_PRI_12                    ((uint32_t)0x000000FF)        /*!< Priority of interrupt 12 */
#define  NVIC_IPR3_PRI_13                    ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 13 */
#define  NVIC_IPR3_PRI_14                    ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 14 */
#define  NVIC_IPR3_PRI_15                    ((uint32_t)0xFF000000)        /*!< Priority of interrupt 15 */

/******************  Bit definition for NVIC_PRI4 register  *******************/
#define  NVIC_IPR4_PRI_16                    ((uint32_t)0x000000FF)        /*!< Priority of interrupt 16 */
#define  NVIC_IPR4_PRI_17                    ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 17 */
#define  NVIC_IPR4_PRI_18                    ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 18 */
#define  NVIC_IPR4_PRI_19                    ((uint32_t)0xFF000000)        /*!< Priority of interrupt 19 */

/******************  Bit definition for NVIC_PRI5 register  *******************/
#define  NVIC_IPR5_PRI_20                    ((uint32_t)0x000000FF)        /*!< Priority of interrupt 20 */
#define  NVIC_IPR5_PRI_21                    ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 21 */
#define  NVIC_IPR5_PRI_22                    ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 22 */
#define  NVIC_IPR5_PRI_23                    ((uint32_t)0xFF000000)        /*!< Priority of interrupt 23 */

/******************  Bit definition for NVIC_PRI6 register  *******************/
#define  NVIC_IPR6_PRI_24                    ((uint32_t)0x000000FF)        /*!< Priority of interrupt 24 */
#define  NVIC_IPR6_PRI_25                    ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 25 */
#define  NVIC_IPR6_PRI_26                    ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 26 */
#define  NVIC_IPR6_PRI_27                    ((uint32_t)0xFF000000)        /*!< Priority of interrupt 27 */

/******************  Bit definition for NVIC_PRI7 register  *******************/
#define  NVIC_IPR7_PRI_28                    ((uint32_t)0x000000FF)        /*!< Priority of interrupt 28 */
#define  NVIC_IPR7_PRI_29                    ((uint32_t)0x0000FF00)        /*!< Priority of interrupt 29 */
#define  NVIC_IPR7_PRI_30                    ((uint32_t)0x00FF0000)        /*!< Priority of interrupt 30 */
#define  NVIC_IPR7_PRI_31                    ((uint32_t)0xFF000000)        /*!< Priority of interrupt 31 */

/******************  Bit definition for SCB_CPUID register  *******************/
#define  SCB_CPUID_REVISION                  ((uint32_t)0x0000000F)        /*!< Implementation defined revision number */
#define  SCB_CPUID_PARTNO                    ((uint32_t)0x0000FFF0)        /*!< Number of processor within family */
#define  SCB_CPUID_Constant                  ((uint32_t)0x000F0000)        /*!< Reads as 0x0F */
#define  SCB_CPUID_VARIANT                   ((uint32_t)0x00F00000)        /*!< Implementation defined variant number */
#define  SCB_CPUID_IMPLEMENTER               ((uint32_t)0xFF000000)        /*!< Implementer code. ARM is 0x41 */

/*******************  Bit definition for SCB_ICSR register  *******************/
#define  SCB_ICSR_VECTACTIVE                 ((uint32_t)0x000001FF)        /*!< Active ISR number field */
#define  SCB_ICSR_RETTOBASE                  ((uint32_t)0x00000800)        /*!< All active exceptions minus the IPSR_current_exception yields the empty set */
#define  SCB_ICSR_VECTPENDING                ((uint32_t)0x003FF000)        /*!< Pending ISR number field */
#define  SCB_ICSR_ISRPENDING                 ((uint32_t)0x00400000)        /*!< Interrupt pending flag */
#define  SCB_ICSR_ISRPREEMPT                 ((uint32_t)0x00800000)        /*!< It indicates that a pending interrupt becomes active in the next running cycle */
#define  SCB_ICSR_PENDSTCLR                  ((uint32_t)0x02000000)        /*!< Clear pending SysTick bit */
#define  SCB_ICSR_PENDSTSET                  ((uint32_t)0x04000000)        /*!< Set pending SysTick bit */
#define  SCB_ICSR_PENDSVCLR                  ((uint32_t)0x08000000)        /*!< Clear pending pendSV bit */
#define  SCB_ICSR_PENDSVSET                  ((uint32_t)0x10000000)        /*!< Set pending pendSV bit */
#define  SCB_ICSR_NMIPENDSET                 ((uint32_t)0x80000000)        /*!< Set pending NMI bit */

/*******************  Bit definition for SCB_VTOR register  *******************/
#define  SCB_VTOR_TBLOFF                     ((uint32_t)0x1FFFFF80)        /*!< Vector table base offset field */
#define  SCB_VTOR_TBLBASE                    ((uint32_t)0x20000000)        /*!< Table base in code(0) or RAM(1) */

/*!<*****************  Bit definition for SCB_AIRCR register  *****************/
#define  SCB_AIRCR_VECTRESET                 ((uint32_t)0x00000001)        /*!< System Reset bit */
#define  SCB_AIRCR_VECTCLRACTIVE             ((uint32_t)0x00000002)        /*!< Clear active vector bit */
#define  SCB_AIRCR_SYSRESETREQ               ((uint32_t)0x00000004)        /*!< Requests chip control logic to generate a reset */

#define  SCB_AIRCR_PRIGROUP                  ((uint32_t)0x00000700)        /*!< PRIGROUP[2:0] bits (Priority group) */
#define  SCB_AIRCR_PRIGROUP_0                ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  SCB_AIRCR_PRIGROUP_1                ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  SCB_AIRCR_PRIGROUP_2                ((uint32_t)0x00000400)        /*!< Bit 2  */

/* prority group configuration */
#define  SCB_AIRCR_PRIGROUP0                 ((uint32_t)0x00000000)        /*!< Priority group=0 (7 bits of pre-emption priority, 1 bit of subpriority) */
#define  SCB_AIRCR_PRIGROUP1                 ((uint32_t)0x00000100)        /*!< Priority group=1 (6 bits of pre-emption priority, 2 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP2                 ((uint32_t)0x00000200)        /*!< Priority group=2 (5 bits of pre-emption priority, 3 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP3                 ((uint32_t)0x00000300)        /*!< Priority group=3 (4 bits of pre-emption priority, 4 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP4                 ((uint32_t)0x00000400)        /*!< Priority group=4 (3 bits of pre-emption priority, 5 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP5                 ((uint32_t)0x00000500)        /*!< Priority group=5 (2 bits of pre-emption priority, 6 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP6                 ((uint32_t)0x00000600)        /*!< Priority group=6 (1 bit of pre-emption priority, 7 bits of subpriority) */
#define  SCB_AIRCR_PRIGROUP7                 ((uint32_t)0x00000700)        /*!< Priority group=7 (no pre-emption priority, 8 bits of subpriority) */

#define  SCB_AIRCR_ENDIANESS                 ((uint32_t)0x00008000)        /*!< Data endianness bit */
#define  SCB_AIRCR_VECTKEY                   ((uint32_t)0xFFFF0000)        /*!< Register key (VECTKEY) - Reads as 0xFA05 (VECTKEYSTAT) */

/*******************  Bit definition for SCB_SCR register  ********************/
#define  SCB_SCR_SLEEPONEXIT                 ((uint8_t)0x02)               /*!< Sleep on exit bit */
#define  SCB_SCR_SLEEPDEEP                   ((uint8_t)0x04)               /*!< Sleep deep bit */
#define  SCB_SCR_SEVONPEND                   ((uint8_t)0x10)               /*!< Wake up from WFE */

/********************  Bit definition for SCB_CCR register  *******************/
#define  SCB_CCR_NONBASETHRDENA              ((uint16_t)0x0001)            /*!< Thread mode can be entered from any level in Handler mode by controlled return value */
#define  SCB_CCR_USERSETMPEND                ((uint16_t)0x0002)            /*!< Enables user code to write the Software Trigger Interrupt register to trigger (pend) a Main exception */
#define  SCB_CCR_UNALIGN_TRP                 ((uint16_t)0x0008)            /*!< Trap for unaligned access */
#define  SCB_CCR_DIV_0_TRP                   ((uint16_t)0x0010)            /*!< Trap on Divide by 0 */
#define  SCB_CCR_BFHFNMIGN                   ((uint16_t)0x0100)            /*!< Handlers running at priority -1 and -2 */
#define  SCB_CCR_STKALIGN                    ((uint16_t)0x0200)            /*!< On exception entry, the SP used prior to the exception is adjusted to be 8-byte aligned */

/*******************  Bit definition for SCB_SHPR register ********************/
#define  SCB_SHPR_PRI_N                      ((uint32_t)0x000000FF)        /*!< Priority of system handler 4,8, and 12. Mem Manage, reserved and Debug Monitor */
#define  SCB_SHPR_PRI_N1                     ((uint32_t)0x0000FF00)        /*!< Priority of system handler 5,9, and 13. Bus Fault, reserved and reserved */
#define  SCB_SHPR_PRI_N2                     ((uint32_t)0x00FF0000)        /*!< Priority of system handler 6,10, and 14. Usage Fault, reserved and PendSV */
#define  SCB_SHPR_PRI_N3                     ((uint32_t)0xFF000000)        /*!< Priority of system handler 7,11, and 15. Reserved, SVCall and SysTick */

/******************  Bit definition for SCB_SHCSR register  *******************/
#define  SCB_SHCSR_MEMFAULTACT               ((uint32_t)0x00000001)        /*!< MemManage is active */
#define  SCB_SHCSR_BUSFAULTACT               ((uint32_t)0x00000002)        /*!< BusFault is active */
#define  SCB_SHCSR_USGFAULTACT               ((uint32_t)0x00000008)        /*!< UsageFault is active */
#define  SCB_SHCSR_SVCALLACT                 ((uint32_t)0x00000080)        /*!< SVCall is active */
#define  SCB_SHCSR_MONITORACT                ((uint32_t)0x00000100)        /*!< Monitor is active */
#define  SCB_SHCSR_PENDSVACT                 ((uint32_t)0x00000400)        /*!< PendSV is active */
#define  SCB_SHCSR_SYSTICKACT                ((uint32_t)0x00000800)        /*!< SysTick is active */
#define  SCB_SHCSR_USGFAULTPENDED            ((uint32_t)0x00001000)        /*!< Usage Fault is pended */
#define  SCB_SHCSR_MEMFAULTPENDED            ((uint32_t)0x00002000)        /*!< MemManage is pended */
#define  SCB_SHCSR_BUSFAULTPENDED            ((uint32_t)0x00004000)        /*!< Bus Fault is pended */
#define  SCB_SHCSR_SVCALLPENDED              ((uint32_t)0x00008000)        /*!< SVCall is pended */
#define  SCB_SHCSR_MEMFAULTENA               ((uint32_t)0x00010000)        /*!< MemManage enable */
#define  SCB_SHCSR_BUSFAULTENA               ((uint32_t)0x00020000)        /*!< Bus Fault enable */
#define  SCB_SHCSR_USGFAULTENA               ((uint32_t)0x00040000)        /*!< UsageFault enable */

/*******************  Bit definition for SCB_CFSR register  *******************/
/*!< MFSR */
#define  SCB_CFSR_IACCVIOL                   ((uint32_t)0x00000001)        /*!< Instruction access violation */
#define  SCB_CFSR_DACCVIOL                   ((uint32_t)0x00000002)        /*!< Data access violation */
#define  SCB_CFSR_MUNSTKERR                  ((uint32_t)0x00000008)        /*!< Unstacking error */
#define  SCB_CFSR_MSTKERR                    ((uint32_t)0x00000010)        /*!< Stacking error */
#define  SCB_CFSR_MMARVALID                  ((uint32_t)0x00000080)        /*!< Memory Manage Address Register address valid flag */
/*!< BFSR */
#define  SCB_CFSR_IBUSERR                    ((uint32_t)0x00000100)        /*!< Instruction bus error flag */
#define  SCB_CFSR_PRECISERR                  ((uint32_t)0x00000200)        /*!< Precise data bus error */
#define  SCB_CFSR_IMPRECISERR                ((uint32_t)0x00000400)        /*!< Imprecise data bus error */
#define  SCB_CFSR_UNSTKERR                   ((uint32_t)0x00000800)        /*!< Unstacking error */
#define  SCB_CFSR_STKERR                     ((uint32_t)0x00001000)        /*!< Stacking error */
#define  SCB_CFSR_BFARVALID                  ((uint32_t)0x00008000)        /*!< Bus Fault Address Register address valid flag */
/*!< UFSR */
#define  SCB_CFSR_UNDEFINSTR                 ((uint32_t)0x00010000)        /*!< The processor attempt to execute an undefined instruction */
#define  SCB_CFSR_INVSTATE                   ((uint32_t)0x00020000)        /*!< Invalid combination of EPSR and instruction */
#define  SCB_CFSR_INVPC                      ((uint32_t)0x00040000)        /*!< Attempt to load EXC_RETURN into pc illegally */
#define  SCB_CFSR_NOCP                       ((uint32_t)0x00080000)        /*!< Attempt to use a coprocessor instruction */
#define  SCB_CFSR_UNALIGNED                  ((uint32_t)0x01000000)        /*!< Fault occurs when there is an attempt to make an unaligned memory access */
#define  SCB_CFSR_DIVBYZERO                  ((uint32_t)0x02000000)        /*!< Fault occurs when SDIV or DIV instruction is used with a divisor of 0 */

/*******************  Bit definition for SCB_HFSR register  *******************/
#define  SCB_HFSR_VECTTBL                    ((uint32_t)0x00000002)        /*!< Fault occurs because of vector table read on exception processing */
#define  SCB_HFSR_FORCED                     ((uint32_t)0x40000000)        /*!< Hard Fault activated when a configurable Fault was received and cannot activate */
#define  SCB_HFSR_DEBUGEVT                   ((uint32_t)0x80000000)        /*!< Fault related to debug */

/*******************  Bit definition for SCB_DFSR register  *******************/
#define  SCB_DFSR_HALTED                     ((uint8_t)0x01)               /*!< Halt request flag */
#define  SCB_DFSR_BKPT                       ((uint8_t)0x02)               /*!< BKPT flag */
#define  SCB_DFSR_DWTTRAP                    ((uint8_t)0x04)               /*!< Data Watchpoint and Trace (DWT) flag */
#define  SCB_DFSR_VCATCH                     ((uint8_t)0x08)               /*!< Vector catch flag */
#define  SCB_DFSR_EXTERNAL                   ((uint8_t)0x10)               /*!< External debug request flag */

/*******************  Bit definition for SCB_MMFAR register  ******************/
#define  SCB_MMFAR_ADDRESS                   ((uint32_t)0xFFFFFFFF)        /*!< Mem Manage fault address field */

/*******************  Bit definition for SCB_BFAR register  *******************/
#define  SCB_BFAR_ADDRESS                    ((uint32_t)0xFFFFFFFF)        /*!< Bus fault address field */

/*******************  Bit definition for SCB_afsr register  *******************/
#define  SCB_AFSR_IMPDEF                     ((uint32_t)0xFFFFFFFF)        /*!< Implementation defined */

/**
  * @}
  */

 /**
  * @}
  */ 
#ifdef USE_STDPERIPH_DRIVER
  #include "stm32w108xx_conf.h"
#endif /* USE_STDPERIPH_DRIVER */

/** @addtogroup Exported_macro
  * @{
  */

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__STM32W108XX_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
