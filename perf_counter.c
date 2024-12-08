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
#ifndef PERF_CNT_COMPENSATION_THRESHOLD
#   define PERF_CNT_COMPENSATION_THRESHOLD          16
#endif

#ifndef PERF_CNT_DELAY_US_COMPENSATION
#   define PERF_CNT_DELAY_US_COMPENSATION           90
#endif

#define MAGIC_WORD_AGENT_LIST_VALID        0x8492A53C
#define MAGIC_WORD_CANARY                  0xDEADBEEF

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

struct __task_cycle_info_t {
    task_cycle_info_t       tInfo;             //!< cycle information
    int64_t                 lLastTimeStamp;    //!< previous timestamp
    task_cycle_info_agent_t tList;             //!< the root of the agent list
    uint32_t                wMagicWord;        //!< an magic word for validation
} ;


/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/

volatile static int64_t s_lOldTimestamp;
volatile static int64_t s_lOldTimestampUS;
volatile static int64_t s_lOldTimestampMS;
volatile static uint32_t s_wUSUnit = 1;
volatile static uint32_t s_wMSUnit = 1;
volatile static uint32_t s_wMSResidule = 0;
volatile static uint32_t s_wUSResidule = 0;
volatile static int64_t s_lSystemMS = 0;
volatile static int64_t s_lSystemUS = 0;

volatile static int64_t s_lSystemClockCounts = 0;

volatile int32_t g_nOffset = 0;
volatile int64_t g_lLastTimeStamp = 0;

/*============================ PROTOTYPES ====================================*/

/* low level interface for porting */
extern
uint32_t perfc_port_get_system_timer_freq(void);
extern
int64_t perfc_port_get_system_timer_top(void);
extern
bool perfc_port_is_system_timer_ovf_pending(void);
extern
bool perfc_port_init_system_timer(bool bTimerOccupied);
extern
int64_t perfc_port_get_system_timer_elapsed(void);
extern
void perfc_port_clear_system_timer_ovf_pending(void);
extern
void perfc_port_stop_system_timer_counting(void);
extern
void perfc_port_clear_system_timer_counter(void);

/*============================ IMPLEMENTATION ================================*/
/*============================ INCLUDES ======================================*/

void perfc_port_insert_to_system_timer_insert_ovf_handler(void)
{
    int64_t lLoad = perfc_port_get_system_timer_top() + 1;

    /* prevent high priority exceptions from preempting the system timer OVF 
     * exception handling
     */
    __IRQ_SAFE {
        s_lSystemClockCounts += lLoad;

        // update system ms counter
        do {
            int64_t lTemp = s_wMSResidule + lLoad;

            int64_t lMS = lTemp / s_wMSUnit;
            s_lSystemMS += lMS;
            s_wMSResidule = (uint32_t)((int64_t)lTemp - (int64_t)lMS * s_wMSUnit);

        } while(0);
    }

    __IRQ_SAFE {
        // update system us counter
        do {
            int64_t lTemp = s_wUSResidule + lLoad;

            int64_t lUS = lTemp / s_wUSUnit;
            s_lSystemUS += lUS;

            s_wUSResidule = (uint32_t)((int64_t)lTemp - (int64_t)lUS * s_wUSUnit);
        } while(0);
    }
}

uint32_t perfc_get_systimer_frequency(void)
{
    return perfc_port_get_system_timer_freq();
}

__WEAK
void __perf_os_patch_init(void)
{
}


void update_perf_counter(void)
{
    uint32_t wSystemFrequency = perfc_port_get_system_timer_freq();
    s_wUSUnit = wSystemFrequency / 1000000ul;
    s_wMSUnit = wSystemFrequency / 1000ul;
    
    __IRQ_SAFE {
        g_lLastTimeStamp = get_system_ticks();
        __perfc_sync_barrier__();
        g_nOffset = get_system_ticks() - g_lLastTimeStamp;
    }
}

bool init_cycle_counter(bool bIsSysTickOccupied)
{
    bool bResult = false;
    __IRQ_SAFE {
        bResult = perfc_port_init_system_timer(bIsSysTickOccupied);             // use the longest period
        perfc_port_clear_system_timer_ovf_pending();
    }
    
    update_perf_counter();
    s_lSystemClockCounts = 0;                       // reset system cycle counter
    s_lSystemMS = 0;                                // reset system millisecond counter
    s_lSystemUS = 0;                                // reset system microsecond counter
    s_lOldTimestamp = 0;
    s_lOldTimestampUS = 0;
    s_lOldTimestampMS = 0;
    
    __perf_os_patch_init();
    
    return bResult;
}

/*! \note this function should only be called when irq is disabled
 *        hence SysTick-LOAD and (SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)
 *        won't change.
 */
__STATIC_INLINE int64_t check_systick(void)
{
    int64_t lTemp = perfc_port_get_system_timer_elapsed();

    /*        Since we cannot stop counting temporarily, there are several
     *        conditions which we should take into consideration:
     *        - Condition 1: when assigning nTemp with the register value (LOAD-VAL),
     *            the underflow didn't happen but when we check the PENDSTSET bit,
     *            the underflow happens, for this condition, we should recall the
     *            perfc_port_get_system_timer_elapsed().
     *        The following code implements an equivalent logic.
     */
    if (perfc_port_is_system_timer_ovf_pending()){
        /* refresh the elapsed just in case the counter has just overflowed/underflowed
         * after we called the perfc_port_get_system_timer_elapsed()
         */
        lTemp = perfc_port_get_system_timer_elapsed();
        lTemp += perfc_port_get_system_timer_top() + 1;
    }

    return lTemp;
}

void before_cycle_counter_reconfiguration(void)
{
    __IRQ_SAFE {
        perfc_port_stop_system_timer_counting();

        if (perfc_port_is_system_timer_ovf_pending()) {                         
            perfc_port_clear_system_timer_ovf_pending();                        /* clear pending bit */

            perfc_port_insert_to_system_timer_insert_ovf_handler();             /* manually handle exception */

        }
        s_lSystemClockCounts = get_system_ticks();                              /* get the final cycle counter value */

        perfc_port_clear_system_timer_counter();
    }
}

__attribute__((constructor))
void __perf_counter_init(void)
{
    init_cycle_counter(true);
}


void delay_us(uint32_t wUs)
{
    int64_t lUs = (int64_t)wUs * (int64_t)s_wUSUnit;
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

void delay_ms(uint32_t wMs)
{
    int64_t lMs = (int64_t)wMs * (int64_t)s_wMSUnit;
    int32_t iCompensate = g_nOffset > PERF_CNT_DELAY_US_COMPENSATION
                        ? g_nOffset 
                        : PERF_CNT_DELAY_US_COMPENSATION;

    if (lMs <= iCompensate) {
        return ;
    }

    lMs -= iCompensate;

    lMs += get_system_ticks();
    while(get_system_ticks() < lMs);
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

int64_t get_system_ms(void)
{
    int64_t lTemp = 0;

    __IRQ_SAFE {
        lTemp = s_lSystemMS 
              + (   (check_systick() 
                +   (int64_t)s_wMSResidule) / s_wMSUnit);

        if (lTemp < s_lOldTimestampMS) {
            lTemp = s_lOldTimestampMS;
        } else {
            s_lOldTimestampMS = lTemp;
        }
    }

    return lTemp;
}

int64_t get_system_us(void)
{
    int64_t lTemp = 0;

    __IRQ_SAFE {
        lTemp = s_lSystemUS 
              + (   (check_systick() 
                +   (int64_t)s_wUSResidule) / s_wUSUnit);

        if (lTemp < s_lOldTimestampUS) {
            lTemp = s_lOldTimestampUS;
        } else {
            s_lOldTimestampUS = lTemp;
        }

    }

    return lTemp;
}

int64_t perfc_convert_ticks_to_ms(int64_t lTick)
{
    return lTick / (int64_t)s_wMSUnit;
}

int64_t perfc_convert_ms_to_ticks(uint32_t wMS)
{
    int64_t lResult = (int64_t)s_wMSUnit * (int64_t)wMS;
    return lResult ? lResult : 1;
}

int64_t perfc_convert_ticks_to_us(int64_t lTick)
{
    return lTick / (int64_t)s_wUSUnit;
}

int64_t perfc_convert_us_to_ticks(uint32_t wMS)
{
    int64_t lResult = (int64_t)s_wUSUnit * (int64_t)wMS;
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
    return perfc_port_get_system_timer_freq();
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

