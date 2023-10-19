/****************************************************************************
*  Copyright 2022 Gorgon Meducer (Email:embedded_zhuoran@hotmail.com)       *
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
#ifndef PERF_CNT_COMPENSATION_THRESHOLD
#   define PERF_CNT_COMPENSATION_THRESHOLD          16
#endif

#ifndef PERF_CNT_DELAY_US_COMPENSATION
#   define PERF_CNT_DELAY_US_COMPENSATION           90
#endif


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


#define MAGIC_WORD_AGENT_LIST_VALID        0x8492A53C
#define MAGIC_WORD_CANARY                  0xDEADBEEF

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

struct __task_cycle_info_t {
    task_cycle_info_t       tInfo;             //!< cycle information
    int64_t                 lLastTimeStamp;    //!< previous timestamp
    task_cycle_info_agent_t tList;             //!< the root of the agent list
    uint32_t                wMagicWord;        //!< an magic word for validation
} ;


/*============================ GLOBAL VARIABLES ==============================*/
extern uint32_t SystemCoreClock;

/*============================ LOCAL VARIABLES ===============================*/
volatile int64_t g_lLastTimeStamp = 0;
volatile static int64_t s_lOldTimestamp;
volatile int32_t g_nOffset = 0;
volatile static int32_t s_nUSUnit = 1;
volatile static int32_t s_nMSUnit = 1;
volatile static int32_t s_nMSResidule = 0;
volatile static int32_t s_nUSResidule = 0;
volatile static int32_t s_nSystemMS = 0;
volatile static int32_t s_nSystemUS = 0;

volatile static int64_t s_lSystemClockCounts = 0;


/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ INCLUDES ======================================*/

__STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
{
    if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
    {
        return (1UL);                                                           /* Reload value impossible */
    }

    //__IRQ_SAFE {
        SysTick->CTRL  = 0;

        SysTick->LOAD  = (uint32_t)(ticks - 1UL);                               /* set reload register */
        //NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);     /* set Priority for Systick Interrupt */
        SysTick->VAL   = 0UL;                                                   /* Load the SysTick Counter Value */
        SysTick->CTRL  =   SysTick_CTRL_CLKSOURCE_Msk |
                           SysTick_CTRL_TICKINT_Msk   |
                           SysTick_CTRL_ENABLE_Msk;                             /* Enable SysTick IRQ and SysTick Timer */
        //SCB->ICSR      = SCB_ICSR_PENDSTCLR_Msk;
    //}
    return (0UL);                                                               /* Function successful */
}

void user_code_insert_to_systick_handler(void)
{
    uint32_t wLoad = SysTick->LOAD + 1;
    s_lSystemClockCounts += wLoad;

    // update system ms counter
    do {
        s_nMSResidule += wLoad;
        int32_t nMS = s_nMSResidule / s_nMSUnit;
        s_nMSResidule -= nMS * s_nMSUnit;
        s_nSystemMS += nMS;
    } while(0);

    // update system us counter
    do {
        s_nUSResidule += wLoad;
        int32_t nUS = s_nUSResidule / s_nUSUnit;
        s_nUSResidule -= nUS * s_nUSUnit;
        s_nSystemUS += nUS;
    } while(0);

}

__WEAK
void __perf_os_patch_init(void)
{
}


void update_perf_counter(void)
{
    s_nUSUnit = SystemCoreClock / 1000000ul;
    s_nMSUnit = SystemCoreClock / 1000ul;
    
    __IRQ_SAFE {
        g_lLastTimeStamp = get_system_ticks();
        g_nOffset = get_system_ticks() - g_lLastTimeStamp;
    }
}


void init_cycle_counter(bool bIsSysTickOccupied)
{
    __IRQ_SAFE {
        if (!bIsSysTickOccupied) {
            SysTick_Config(0x01000000);             // use the longest period
        }
        SCB->ICSR      = SCB_ICSR_PENDSTCLR_Msk;
    }
    
    update_perf_counter();
    s_lSystemClockCounts = 0;                       // reset system cycle counter
    s_nSystemMS = 0;                                // reset system millisecond counter
    s_nSystemUS = 0;                                // reset system microsecond counter

    __perf_os_patch_init();
}

/*! \note this function should only be called when irq is disabled
 *        hence SysTick-LOAD and (SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)
 *        won't change.
 */
__STATIC_INLINE int32_t check_systick(void)
{
    int32_t nTemp = (int32_t)SysTick->LOAD - (int32_t)SysTick->VAL;

    /*        Since we cannot stop counting temporarily, there are several
     *        conditions which we should take into consideration:
     *        - Condition 1: when assigning nTemp with the register value (LOAD-VAL),
     *            the underflow didn't happen but when we check the PENDSTSET bit,
     *            the underflow happens, for this condition, we should not
     *            do any compensation. When this happens, the (LOAD-nTemp) is
     *            smaller than PERF_CNT_COMPENSATION_THRESHOLD (a small value) as
     *            long as LOAD is bigger than (or equals to) the
     *            PERF_CNT_COMPENSATION_THRESHOLD;
     *        - Condition 2: when assigning nTemp with the register value (LOAD-VAL),
     *            the VAL is zero and underflow happened and the PENDSTSET bit
     *            is set, for this condition, we should not do any compensation.
     *            When this happens, the (LOAD-nTemp) is equals to zero.
     *        - Condition 3: when assigning nTemp with the register value (LOAD-VAL),
     *            the underflow has already happened, hence the PENDSTSET
     *            is set, for this condition, we should compensate the return
     *            value. When this happens, the (LOAD-nTemp) is bigger than (or
     *            equals to) PERF_CNT_COMPENSATION_THRESHOLD.
     *        The following code implements an equivalent logic.
     */
    if (SCB->ICSR & SCB_ICSR_PENDSTSET_Msk){
        if (((int32_t)SysTick->LOAD - nTemp) >= PERF_CNT_COMPENSATION_THRESHOLD) {
            nTemp += SysTick->LOAD + 1;
        }
    }

    return nTemp;
}

void before_cycle_counter_reconfiguration(void)
{
    __IRQ_SAFE {
        SysTick->CTRL  = 0;                                                     /* disable SysTick first */

        if (SCB->ICSR & SCB_ICSR_PENDSTSET_Msk) {                               /* pending SysTick exception */
            SCB->ICSR = SCB_ICSR_PENDSTCLR_Msk;                                 /* clear pending bit */

            user_code_insert_to_systick_handler();                              /* manually handle exception */

        }
        s_lSystemClockCounts = get_system_ticks();                              /* get the final cycle counter value */

        SysTick->LOAD = 0UL;
        SysTick->VAL = 0UL;                                                     /* clear the Current Value Register */
    }
}



__attribute__((constructor))
void __perf_counter_init(void)
{
    init_cycle_counter(true);
}


void delay_us(int32_t nUs)
{
    int64_t lUs = (int64_t)nUs * (int64_t)s_nUSUnit;
    int32_t iCompensate = g_nOffset > PERF_CNT_DELAY_US_COMPENSATION
                        ? g_nOffset 
                        : PERF_CNT_DELAY_US_COMPENSATION;

    if (lUs <= iCompensate) {
        return ;
    }

    lUs -= iCompensate;

    lUs += get_system_ticks();
    while(get_system_ticks() < lUs);
}


void delay_ms(int32_t nMs)
{
    int64_t lUs = (int64_t)nMs * (int64_t)s_nMSUnit;
    int32_t iCompensate = g_nOffset > PERF_CNT_DELAY_US_COMPENSATION
                        ? g_nOffset 
                        : PERF_CNT_DELAY_US_COMPENSATION;

    if (lUs <= iCompensate) {
        return ;
    }

    lUs -= iCompensate;

    lUs += get_system_ticks();
    while(get_system_ticks() < lUs);
}

__attribute__((noinline))
int64_t get_system_ticks(void)
{
    int64_t lTemp = 0;

    __IRQ_SAFE {
        lTemp = check_systick() + s_lSystemClockCounts;
        
        /* When calling get_system_ticks() in an exception handler that has a  
         * higher priority than the SysTick_Handler, in some rare cases, the 
         * lTemp might be temporarily smaller than the previous value (i.e. 
         * s_lOldTimestamp), to mitigate the adverse effects of this problem,
         * we use the following code to avoid time-rolling-back issue.
         * 
         * NOTE: the issue mentioned above doesn't accumulate or have long-lasting
         *       effects.
         */
        if (lTemp < s_lOldTimestamp) {
            lTemp = s_lOldTimestamp;
        } else {
            s_lOldTimestamp = lTemp;
        }
    }

    return lTemp;
}

/*! \note the prototype of this clock() is different from the one defined in
 *!           time.h. As clock_t is usually defined as unsigned int, it is
 *!           not big enough in Cortex-M system to hold a time-stamp. clock()
 *!           defined here returns the timestamp since the begining of main()
 *!           and its unit is clock cycle (rather than 1ms). Hence, for a system
 *!           running under several hundreds MHz or even 1GHz, e.g. RT10xx from
 *!           NXP, it is very easy to see a counter overflow as clock_t is
 *!           defined as uint32_t in timer.h.
 *!           Since we are not allowed to change the defintion of clock_t in
 *!           official header file, i.e. time.h, I use a compatible prototype
 *!           after I checked the AAPCS spec. So, the return of the clock() is
 *!           int64_t, which will use the R0 to store the lower 32bits and R1
 *!           to store the higher 32bits. When you are using the prototype from
 *!           timer.h, caller will only take the lower 32bits stored in R0 and
 *!           the higher 32bits stored in R1 will be ignored.
 *!
 *!           If you want to use the non-overflow version of this clock(), please
 *!           1) define the MACRO: __PERF_CNT_USE_LONG_CLOCK__ in your project
 *!           and 2) do not include system header file <time.h>
 *!
 */
#if !defined(__IS_COMPILER_IAR__)
__attribute__((nothrow))
#endif
__attribute__((noinline))
int64_t clock(void)
{
    return get_system_ticks();
}

int32_t get_system_ms(void)
{
    int32_t nTemp = 0;

    __IRQ_SAFE {
        nTemp = s_nSystemMS + (check_systick() + s_nMSResidule) / s_nMSUnit;
    }

    return nTemp;
}

int32_t get_system_us(void)
{
    int32_t nTemp = 0;

    __IRQ_SAFE {
        nTemp = s_nSystemUS + (check_systick() + s_nUSResidule) / s_nUSUnit;
    }

    return nTemp;
}

int64_t perfc_convert_ticks_to_ms(int64_t lTick)
{
    return lTick / (int64_t)s_nMSUnit;
}

int64_t perfc_convert_ms_to_ticks(uint32_t wMS)
{
    int64_t lResult = (int64_t)s_nMSUnit * (int64_t)wMS;
    return lResult ? lResult : 1;
}

int64_t perfc_convert_ticks_to_us(int64_t lTick)
{
    return lTick / (int64_t)s_nUSUnit;
}

int64_t perfc_convert_us_to_ticks(uint32_t wMS)
{
    int64_t lResult = (int64_t)s_nUSUnit * (int64_t)wMS;
    return lResult ? lResult : 1;
}


bool __perfc_is_time_out(int64_t lPeriod, int64_t *plTimestamp, bool bAutoReload)
{
    if (NULL == plTimestamp) {
        return false;
    }
    
    int64_t lTimestamp = get_system_ticks();


    if (0 == *plTimestamp) {
        *plTimestamp = lPeriod;
        *plTimestamp += lTimestamp;
        
        return false;
    }

    if (lTimestamp >= *plTimestamp) {
        if (bAutoReload) {
            *plTimestamp = lPeriod + lTimestamp;
        }
        return true;
    }

    return false;
}


/// Setup timer hardware.
/// \return       status (1=Success, 0=Failure)
uint32_t EventRecorderTimerSetup (void)
{
    /* doing nothing at all */
    return 1;
}

/// Get timer frequency.
/// \return       timer frequency in Hz
uint32_t EventRecorderTimerGetFreq (void)
{
    return SystemCoreClock;
}

/// Get timer count.
/// \return       timer count (32-bit)
uint32_t EventRecorderTimerGetCount (void)
{
    return get_system_ticks();
}



__WEAK
task_cycle_info_t * get_rtos_task_cycle_info(void)
{
    return NULL;
}

void init_task_cycle_counter(void)
{
    struct __task_cycle_info_t * ptRootAgent =
        (struct __task_cycle_info_t *)get_rtos_task_cycle_info();
    if (NULL == ptRootAgent) {
        return ;
    }

    memset(ptRootAgent, 0, sizeof(struct __task_cycle_info_t));

    ptRootAgent->tList.ptInfo = &(ptRootAgent->tInfo);
    ptRootAgent->tInfo.lStart = get_system_ticks();
    ptRootAgent->wMagicWord = MAGIC_WORD_CANARY;
}

bool perfc_check_task_stack_canary_safe(void)
{
    struct __task_cycle_info_t * ptRootAgent =
        (struct __task_cycle_info_t *)get_rtos_task_cycle_info();
    do {
        if (NULL == ptRootAgent) {
            break;
        }
    
        if  (   (MAGIC_WORD_CANARY == ptRootAgent->wMagicWord)
            ||  (MAGIC_WORD_AGENT_LIST_VALID == ptRootAgent->wMagicWord)) {
            return true;
        }
    } while(0);
    
    return false;
}

task_cycle_info_t *init_task_cycle_info(task_cycle_info_t *ptInfo)
{
    do {
        if (NULL == ptInfo) {
            break;
        }

        memset(ptInfo, 0, sizeof(task_cycle_info_t));

        ptInfo->bEnabled = true;
    } while(0);

    return ptInfo;
}

bool enable_task_cycle_info(task_cycle_info_t *ptInfo)
{
    if (NULL == ptInfo) {
        return false;
    }
    bool bOrig;
    __IRQ_SAFE {
        bOrig = ptInfo->bEnabled;
        ptInfo->bEnabled = true;
    }
    return bOrig;
}

bool disable_task_cycle_info(task_cycle_info_t *ptInfo)
{
    if (NULL == ptInfo) {
        return false;
    }
    bool bOrig;
    __IRQ_SAFE {
        bOrig = ptInfo->bEnabled;
        ptInfo->bEnabled = false;
    }
    return bOrig;
}

void resume_task_cycle_info(task_cycle_info_t *ptInfo, bool bEnabledStatus)
{
    if (NULL == ptInfo) {
        return;
    }

    ptInfo->bEnabled = bEnabledStatus;
}


task_cycle_info_agent_t *register_task_cycle_agent(task_cycle_info_t *ptInfo,
                                             task_cycle_info_agent_t *ptAgent)
{
    __IRQ_SAFE {
        do {
            if (NULL == ptAgent || NULL == ptInfo) {
                break;
            }

            struct __task_cycle_info_t * ptRootAgent =
                (struct __task_cycle_info_t *)get_rtos_task_cycle_info();
            if (NULL == ptRootAgent) {
                break;
            }

            ptRootAgent->wMagicWord = MAGIC_WORD_AGENT_LIST_VALID;

            ptAgent->ptInfo = ptInfo;

            // push to the stack
            do {
                // set next-list
                ptAgent->ptNext = ptRootAgent->tList.ptNext;
                ptRootAgent->tList.ptNext = ptAgent;

                // set prev-list
                ptAgent->ptPrev = &(ptRootAgent->tList);
                if (NULL != ptAgent->ptNext) {
                    ptAgent->ptNext->ptPrev = ptAgent;
                }
            } while(0);

        } while(0);
    }

    return ptAgent;
}

task_cycle_info_agent_t *
unregister_task_cycle_agent(task_cycle_info_agent_t *ptAgent)
{
    __IRQ_SAFE {
        do {
            if (NULL == ptAgent) {
                break;
            }

            task_cycle_info_agent_t *ptPrev = ptAgent->ptPrev;
            if (NULL == ptPrev) {
                break;      /* this should not happen */
            }
            if (ptPrev->ptNext != ptAgent) {
                // already removed
                break;
            }

            //! remove agent from the next-list
            ptPrev->ptNext = ptAgent->ptNext;

            if (NULL != ptAgent->ptNext) {
                // remove agent from the prev-list
                ptAgent->ptNext->ptPrev = ptPrev;
            }

            ptAgent->ptNext = NULL;
            ptAgent->ptPrev = NULL;

        } while(0);
    }

    return ptAgent;
}


void __on_context_switch_in(uint32_t *pwStack)
{
    struct __task_cycle_info_t *ptRootAgent = (struct __task_cycle_info_t *)pwStack;
    int64_t lTimeStamp = get_system_ticks();

    ptRootAgent->lLastTimeStamp = lTimeStamp;
    ptRootAgent->tInfo.hwActiveCount++;

    if (MAGIC_WORD_AGENT_LIST_VALID == ptRootAgent->wMagicWord) {
        // update all agents
        task_cycle_info_agent_t *ptAgent = ptRootAgent->tList.ptNext;
        while(NULL != ptAgent) {
            if (NULL != ptAgent->ptInfo) {
                if (ptAgent->ptInfo->bEnabled) {
                    ptAgent->ptInfo->hwActiveCount++;
                }
            }
            ptAgent = ptAgent->ptNext;
        }
    }
}

void __on_context_switch_out(uint32_t *pwStack)
{
    struct __task_cycle_info_t *ptRootAgent = (struct __task_cycle_info_t *)pwStack;
    int64_t lCycleUsed = get_system_ticks() - ptRootAgent->lLastTimeStamp - g_nOffset;

    ptRootAgent->tInfo.nUsedRecent = lCycleUsed;
    ptRootAgent->tInfo.lUsedTotal += lCycleUsed;

    if (MAGIC_WORD_AGENT_LIST_VALID == ptRootAgent->wMagicWord) {
        // update all agents
        task_cycle_info_agent_t *ptAgent = ptRootAgent->tList.ptNext;
        while(NULL != ptAgent) {
            if (NULL != ptAgent->ptInfo) {
                if (ptAgent->ptInfo->bEnabled) {
                    ptAgent->ptInfo->nUsedRecent = lCycleUsed;
                    ptAgent->ptInfo->lUsedTotal += lCycleUsed;
                }
            }
            ptAgent = ptAgent->ptNext;
        }
    }
}

__attribute__((noinline))
void __start_task_cycle_counter(task_cycle_info_t *ptInfo)
{
    struct __task_cycle_info_t * ptRootAgent =
        (struct __task_cycle_info_t *)get_rtos_task_cycle_info();
    if (NULL == ptRootAgent) {
        return ;
    }

    __IRQ_SAFE {
        ptRootAgent->lLastTimeStamp = get_system_ticks();
        ptRootAgent->tInfo.lUsedTotal = 0;

        if (NULL != ptInfo) {
            ptInfo->lUsedTotal = 0;
            ptInfo->bEnabled = true;
        }
    }
}

__attribute__((noinline))
int64_t __stop_task_cycle_counter(task_cycle_info_t *ptInfo)
{
    struct __task_cycle_info_t * ptRootAgent =
        (struct __task_cycle_info_t *)get_rtos_task_cycle_info();
    if (NULL == ptRootAgent) {
        return 0;
    }

    int64_t lCycles = 0;

    __IRQ_SAFE {
        int64_t lCycleUsed = get_system_ticks() - ptRootAgent->lLastTimeStamp - g_nOffset;
        ptRootAgent->tInfo.lUsedTotal += lCycleUsed;

        if (NULL != ptInfo) {
            if (ptInfo->bEnabled) {
                ptInfo->nUsedRecent = lCycleUsed;
                ptInfo->lUsedTotal += lCycleUsed;
                ptInfo->bEnabled = false;
            }

            lCycles = ptInfo->lUsedTotal;
        } else {
            lCycles = ptRootAgent->tInfo.lUsedTotal;
        }
    }

    return lCycles;
}

