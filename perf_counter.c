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
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "cmsis_compiler.h"

#define __IMPLEMENT_PERF_COUNTER
#include "perf_counter.h"

#if defined(__IS_COMPILER_GCC__)
#   pragma GCC diagnostic ignored "-Wattributes"
#endif


/*============================ MACROS ========================================*/
#ifndef PERF_CNT_COMPENSATION_THRESHOLD
#   define PERF_CNT_COMPENSATION_THRESHOLD          16
#endif

#ifndef PERF_CNT_DELAY_US_COMPENSATION
#   define PERF_CNT_DELAY_US_COMPENSATION           90
#endif


/* IO definitions (access restrictions to peripheral registers) */
/*!
    \defgroup CMSIS_glob_defs CMSIS Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
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

/*!
 * \name __task_cycle_info_t
 *
 */
//! @{
struct __task_cycle_info_t {
    task_cycle_info_t       tInfo;             //!< cycle information
    int64_t                 lLastTimeStamp;    //!< previous timestamp
    task_cycle_info_agent_t tList;             //!< the root of the agent list
    uint32_t                wMagicWord;        //!< an magic word for validation
} ;
//! @}


/*============================ GLOBAL VARIABLES ==============================*/
extern uint32_t SystemCoreClock;

/*============================ LOCAL VARIABLES ===============================*/
volatile static int32_t s_nCycleCounts = 0;
volatile static int32_t s_nOffset = 0;
volatile static int32_t s_nUSUnit = 1;
volatile static int32_t s_nMSUnit = 1;
volatile static int32_t s_nMSResidule = 0;
volatile static int32_t s_nSystemMS = 0;

volatile static int64_t s_lSystemClockCounts = 0;


/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ INCLUDES ======================================*/


/*!
  \brief   System Tick Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
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

/*!
 * \note  - if you are using a compiler other than armcc or armclang, e.g. iar,
 *        arm gcc etc, the systick_wrapper_ual.o doesn't work with the linker
 *        of your target toolchain as it use the $Super$$ which is only supported
 *        by armlink. For this condition, you have to manually put this function
 *        into your existing SysTick_Handler to make the perf_counter library
 *        work.
 *
 * \note  - if you are using Arm Compiler 5 (armcc) or Arm Compiler 6 (armclang)
 *        you do NOT have to insert this function into your SysTick_Handler,
 *        the systick_wrapper_ual.s will do the work for you.
 */
void user_code_insert_to_systick_handler(void)
{
    uint32_t wLoad = SysTick->LOAD + 1;
    s_nCycleCounts += wLoad;
    s_lSystemClockCounts += wLoad;

    //! update system ms counter
    s_nMSResidule += wLoad;
    int32_t nMS = s_nMSResidule / s_nMSUnit;
    s_nMSResidule -= nMS * s_nMSUnit;
    s_nSystemMS += nMS;

}

__WEAK
void __perf_os_patch_init(void)
{
}

/*!
 * \brief update perf_counter as SystemCoreClock has been updated.
 */
void update_perf_counter(void)
{
    s_nUSUnit = SystemCoreClock / 1000000ul;
    s_nMSUnit = SystemCoreClock / 1000ul;
}

/*! \brief   initialise cycle counter service
 *  \note    - don't forget to tell the function whether the systick is already
 *           used by user applications.
 *           Don't worry, this cycle counter service won't affect your existing
 *           systick service.
 *
 *  \note    - Usually the perf_counter can initialise itself with the help of
 *           __attribute__((constructor(255))), this works fine in Arm Compiler
 *           5 (armcc), Arm Compiler 6 (armclang), arm gcc and llvm. It doesn't
 *           work for IAR. So, when you are using IAR, please call this function
 *           manually to initialise the perf_counter service.
 *
 *  \note    - Perf_counter library assumes that:
 *           1. Your project has already using SysTick
 *           2. It assumes that you have already implemented the SysTick_Handler
 *           3. It assumes that you have enabled the exception handling for
 *              SysTick.
 *           If these are not the case, please:
 *               1. Add an empty SysTick_Handler to your project if you don't have
 *              one
 *               2. Make sure you have the SysTick Exception handling enabled
 *               3. And call function init_cycle_counter(false) if you doesn't
 *              use SysTick in your project at all.
 *
 *  \param bIsSysTickOccupied  A boolean value which indicates whether SysTick
 *           is already used by user application.
 */
void init_cycle_counter(bool bIsSysTickOccupied)
{
    __IRQ_SAFE {
        if (!bIsSysTickOccupied) {
            SysTick_Config(0x01000000);             // use the longest period
        }
        SCB->ICSR      = SCB_ICSR_PENDSTCLR_Msk;
    }

    start_cycle_counter();
    //s_nSystemClockCounts = s_nCycleCounts;
    s_nOffset = stop_cycle_counter();

    update_perf_counter();
    s_lSystemClockCounts = 0;                       // reset system cycle counter
    s_nSystemMS = 0;                                // reset system millisecond counter

#if     defined(__IS_COMPILER_ARM_COMPILER_5__)                                 \
    ||  defined(__IS_COMPILER_ARM_COMPILER_6__)                                 \
    ||  defined(__IS_COMPILER_GCC__)                                            \
    ||  defined(__IS_COMPILER_LLVM__)
    extern void __ensure_systick_wrapper(void);
    __ensure_systick_wrapper();
#endif

    __perf_os_patch_init();
}

/*!
 * \brief try to set a start pointer for the performance counter
 *
 * \retval false the LOAD register is too small
 *
 * \retval true performance counter starts
 */
bool start_cycle_counter(void)
{
    if (SysTick->LOAD < PERF_CNT_COMPENSATION_THRESHOLD) {
        return false;
    }

    __IRQ_SAFE {
        s_nCycleCounts =  (int32_t)SysTick->VAL - (int32_t)SysTick->LOAD;
    }
    return true;
}

/*! \note this function should only be called when irq is disabled
 *        hence SysTick-LOAD and (SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)
 *        won't change.
 */
__STATIC_INLINE int32_t check_systick(void)
{
    int32_t nTemp = (int32_t)SysTick->LOAD - (int32_t)SysTick->VAL;

    /*! \note Since we cannot stop counting temporarily, there are several
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

/*!
 * \brief calculate the elapsed cycle count since the last start point
 *
 * \note  you can have multiple stop_cycle_counter following one start point
 *
 * \return int32_t the elapsed cycle count
 */
int32_t stop_cycle_counter(void)
{
    int32_t nTemp = 0;

    __IRQ_SAFE {
        nTemp = check_systick() + s_nCycleCounts;
    }

    return nTemp - s_nOffset;
}

#if defined(__IS_COMPILER_IAR__)
__attribute__((constructor))
#else
__attribute__((constructor(255)))
#endif
void __perf_counter_init(void)
{
    init_cycle_counter(true);
}

/*!
 * \brief delay specified time in microsecond
 *
 * \param nUs time in microsecond
 */
void delay_us(int32_t nUs)
{
    int64_t lUs = nUs * s_nUSUnit;

    if (lUs <= PERF_CNT_DELAY_US_COMPENSATION) {
        return ;
    }

    lUs -= PERF_CNT_DELAY_US_COMPENSATION;

    lUs += get_system_ticks();
    while(get_system_ticks() < lUs);
}

/*!
 * \brief delay specified time in millisecond
 *
 * \param nUs time in millisecond
 */
void delay_ms(int32_t nMs)
{
    int64_t lUs = nMs * s_nMSUnit;

    if (lUs <= PERF_CNT_DELAY_US_COMPENSATION) {
        return ;
    }

    lUs -= PERF_CNT_DELAY_US_COMPENSATION;

    lUs += get_system_ticks();
    while(get_system_ticks() < lUs);
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

int64_t clock(void)
{
    int64_t lTemp = 0;

    __IRQ_SAFE {
        lTemp = check_systick() + s_lSystemClockCounts;
    }

    return lTemp;
}

/*!
 * \brief get the elapsed cycles since perf_counter is initialised
 *
 * \return int64_t the elpased cycles
 */
int64_t get_system_ticks(void)
{
    int64_t lTemp = 0;

    __IRQ_SAFE {
        lTemp = check_systick() + s_lSystemClockCounts;
    }

    return lTemp;
}

/*!
 * \brief get the elapsed milliseconds since perf_counter is initialised
 *
 * \return int32_t the elapsed milliseconds
 */
int32_t get_system_ms(void)
{
    int32_t nTemp = 0;

    __IRQ_SAFE {
        nTemp = s_nSystemMS + (check_systick() + s_nMSResidule) / s_nMSUnit;
    }

    return nTemp;
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

            //! push to the stack
            do {
                //! set next-list
                ptAgent->ptNext = ptRootAgent->tList.ptNext;
                ptRootAgent->tList.ptNext = ptAgent;

                //! set prev-list
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
                //! already removed
                break;
            }

            //! remove agent from the next-list
            ptPrev->ptNext = ptAgent->ptNext;

            if (NULL != ptAgent->ptNext) {
                //! remove agent from the prev-list
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
    uint64_t dwTimeStamp = get_system_ticks();

    ptRootAgent->lLastTimeStamp = dwTimeStamp;
    ptRootAgent->tInfo.hwActiveCount++;

    if (MAGIC_WORD_AGENT_LIST_VALID == ptRootAgent->wMagicWord) {
        //! update all agents
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
    int64_t lCycleUsed = get_system_ticks() - ptRootAgent->lLastTimeStamp;

    ptRootAgent->tInfo.nUsedRecent = lCycleUsed;
    ptRootAgent->tInfo.lUsedTotal += lCycleUsed;

    if (MAGIC_WORD_AGENT_LIST_VALID == ptRootAgent->wMagicWord) {
        //! update all agents
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


int64_t __stop_task_cycle_counter(task_cycle_info_t *ptInfo)
{
    struct __task_cycle_info_t * ptRootAgent =
        (struct __task_cycle_info_t *)get_rtos_task_cycle_info();
    if (NULL == ptRootAgent) {
        return 0;
    }

    int64_t lCycles = 0;

    __IRQ_SAFE {
        int64_t lCycleUsed = get_system_ticks() - ptRootAgent->lLastTimeStamp;
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

