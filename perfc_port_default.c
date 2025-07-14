/****************************************************************************
*  Copyright 2024 Gorgon Meducer (Email:embedded_zhuoran@hotmail.com)       *
*                                                                           *
*  Licensed under the Apache License, Version 2.0 (the "License");          *
*  you may not use this file except in compliance with the License.         *
*  You may obtain a copy of the License at                                  *
*                                                                           *
*     http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                           *
*  Unless required by applicable law or agreed to in writing, software      *
*  distributed under the License is distributed on an "AS IS" BASIS,        *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
*  See the License for the specific language governing permissions and      *
*  limitations under the License.                                           *
*                                                                           *
****************************************************************************/

/*============================ INCLUDES ======================================*/
#undef __PERF_COUNT_PLATFORM_SPECIFIC_HEADER__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "cmsis_compiler.h"

#define __IMPLEMENT_PERF_COUNTER
#include "perf_counter.h"

#if defined(__IS_COMPILER_GCC__)
#   pragma GCC diagnostic ignored "-Wattributes"
#endif

#if defined(__clang__)
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wconditional-uninitialized"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif


/*============================ MACROS ========================================*/

/* IO definitions (access restrictions to peripheral registers) */
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/* Memory mapping of Core Hardware */
#define SCS_BASE            (0xE000E000UL)                                      /*!< System Control Space Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                              /*!< SysTick Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                              /*!< System Control Block Base Address */

#define SysTick             ((SysTick_Type   *)     SysTick_BASE     )          /*!< SysTick configuration struct */
#define SCB                 ((SCB_Type       *)     SCB_BASE      )             /*!< SCB configuration struct */

/* SysTick Control / Status Register Definitions */
#define SysTick_CTRL_COUNTFLAG_Pos         16U                                            /*!< SysTick CTRL: COUNTFLAG Position */
#define SysTick_CTRL_COUNTFLAG_Msk         (1UL << SysTick_CTRL_COUNTFLAG_Pos)            /*!< SysTick CTRL: COUNTFLAG Mask */

#define SysTick_CTRL_CLKSOURCE_Pos          2U                                            /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */

#define SysTick_CTRL_TICKINT_Pos            1U                                            /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */

#define SysTick_CTRL_ENABLE_Pos             0U                                            /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL /*<< SysTick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL: ENABLE Mask */

/* SysTick Reload Register Definitions */
#define SysTick_LOAD_RELOAD_Pos             0U                                            /*!< SysTick LOAD: RELOAD Position */
#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFFUL /*<< SysTick_LOAD_RELOAD_Pos*/)    /*!< SysTick LOAD: RELOAD Mask */

/* SysTick Current Register Definitions */
#define SysTick_VAL_CURRENT_Pos             0U                                            /*!< SysTick VAL: CURRENT Position */
#define SysTick_VAL_CURRENT_Msk            (0xFFFFFFUL /*<< SysTick_VAL_CURRENT_Pos*/)    /*!< SysTick VAL: CURRENT Mask */

/* SysTick Calibration Register Definitions */
#define SysTick_CALIB_NOREF_Pos            31U                                            /*!< SysTick CALIB: NOREF Position */
#define SysTick_CALIB_NOREF_Msk            (1UL << SysTick_CALIB_NOREF_Pos)               /*!< SysTick CALIB: NOREF Mask */

#define SysTick_CALIB_SKEW_Pos             30U                                            /*!< SysTick CALIB: SKEW Position */
#define SysTick_CALIB_SKEW_Msk             (1UL << SysTick_CALIB_SKEW_Pos)                /*!< SysTick CALIB: SKEW Mask */

#define SysTick_CALIB_TENMS_Pos             0U                                            /*!< SysTick CALIB: TENMS Position */
#define SysTick_CALIB_TENMS_Msk            (0xFFFFFFUL /*<< SysTick_CALIB_TENMS_Pos*/)    /*!< SysTick CALIB: TENMS Mask */

/*@} end of group CMSIS_SysTick */

#define SCB_ICSR_PENDSTCLR_Pos             25U                                            /*!< SCB ICSR: PENDSTCLR Position */
#define SCB_ICSR_PENDSTCLR_Msk             (1UL << SCB_ICSR_PENDSTCLR_Pos)                /*!< SCB ICSR: PENDSTCLR Mask */

#define SCB_ICSR_PENDSTSET_Pos             26U                                            /*!< SCB ICSR: PENDSTSET Position */
#define SCB_ICSR_PENDSTSET_Msk             (1UL << SCB_ICSR_PENDSTSET_Pos)                /*!< SCB ICSR: PENDSTSET Mask */

#ifndef __PERFC_CFG_DISABLE_DEFAULT_SYSTICK_PORTING__
#   define __PERFC_CFG_DISABLE_DEFAULT_SYSTICK_PORTING__    0
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*!
  \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IOM uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __IOM uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __IM  uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;

/*!
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  __IOM uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;



/*============================ GLOBAL VARIABLES ==============================*/
extern uint32_t SystemCoreClock;

/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ INCLUDES ======================================*/

#if !__PERFC_CFG_DISABLE_DEFAULT_SYSTICK_PORTING__
__WEAK
__attribute__((noinline))
bool perfc_port_init_system_timer(bool bTimerOccupied)
{
    do {
        if (bTimerOccupied) {
            break;
        }

        __IRQ_SAFE {
            SysTick->CTRL  = 0;

            SysTick->LOAD  = SysTick_LOAD_RELOAD_Msk;                               /* set reload register */
            //NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);     /* set Priority for Systick Interrupt */
            SysTick->VAL   = 0UL;                                                   /* Load the SysTick Counter Value */
            SysTick->CTRL  =   SysTick_CTRL_CLKSOURCE_Msk |
                               SysTick_CTRL_TICKINT_Msk   |
                               SysTick_CTRL_ENABLE_Msk;                             /* Enable SysTick IRQ and SysTick Timer */
            //SCB->ICSR      = SCB_ICSR_PENDSTCLR_Msk;
        }
    } while(0);
    
    return true;
}

__WEAK
__attribute__((noinline))
uint32_t perfc_port_get_system_timer_freq(void)
{
    return SystemCoreClock;
}

__WEAK
__attribute__((noinline))
bool perfc_port_is_system_timer_ovf_pending(void)
{
    return SCB->ICSR & SCB_ICSR_PENDSTSET_Msk;
}

__WEAK
__attribute__((noinline))
int64_t perfc_port_get_system_timer_top(void)
{
    return SysTick->LOAD;
}

__WEAK
__attribute__((noinline))
int64_t perfc_port_get_system_timer_elapsed(void)
{
    return (int64_t)SysTick->LOAD - (uint32_t)SysTick->VAL;
}

__WEAK
__attribute__((noinline))
void perfc_port_clear_system_timer_ovf_pending(void)
{
    SCB->ICSR      = SCB_ICSR_PENDSTCLR_Msk;
}

__WEAK
__attribute__((noinline))
void perfc_port_stop_system_timer_counting(void)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

__WEAK
__attribute__((noinline))
void perfc_port_clear_system_timer_counter(void)
{
    SysTick->VAL = 0UL;
}

__WEAK
__attribute__((noinline))
uintptr_t __perfc_port_get_sp(void)
{
    uintptr_t result;

    __ASM volatile ("mov %0, sp" : "=r" (result) );
    return (result);
}

__WEAK
__attribute__((noinline))
void __perfc_port_set_sp(uintptr_t nSP)
{
    __ASM volatile ("mov sp, %0" : "=r" (nSP) );
}

#endif


