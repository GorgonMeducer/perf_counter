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

#if __PERFC_USE_PMU_PORTING__

#include "cmsis_compiler.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
#ifndef __perfc_sync_barrier__
#   define __perfc_sync_barrier__(...)         do {__DSB();__ISB();} while(0)
#endif


#define __cpu_perf__(__str, ...)                                                \
    using(                                                                      \
        struct {                                                                \
            uint64_t dwNoInstr;                                                 \
            uint64_t dwNoMemAccess;                                             \
            uint64_t dwNoL1DCacheRefill;                                        \
            uint64_t dwNoL1ICacheRefill;                                        \
            int64_t lCycles;                                                    \
            uint32_t wInstrCalib;                                               \
            uint32_t wMemAccessCalib;                                           \
            float fCPI;                                                         \
            float fDCacheMissRate;                                              \
            float fICacheMissRate;                                              \
        } __PERF_INFO__ = {0},                                                  \
        ({                                                                      \
            __PERF_INFO__.dwNoInstr = perfc_pmu_get_instruction_count();        \
            __PERF_INFO__.dwNoMemAccess = perfc_pmu_get_memory_access_count();  \
            __PERF_INFO__.wInstrCalib = perfc_pmu_get_instruction_count()       \
                                - __PERF_INFO__.dwNoInstr;                      \
            __PERF_INFO__.wMemAccessCalib = perfc_pmu_get_memory_access_count() \
                                          - __PERF_INFO__.dwNoMemAccess;        \
            __PERF_INFO__.dwNoL1DCacheRefill                                    \
                = perfc_pmu_get_L1_dcache_refill_count();                       \
            __PERF_INFO__.dwNoL1ICacheRefill                                    \
                = perfc_pmu_get_L1_icache_refill_count();                       \
            __PERF_INFO__.dwNoInstr = perfc_pmu_get_instruction_count();        \
            __PERF_INFO__.dwNoMemAccess = perfc_pmu_get_memory_access_count();  \
        }),                                                                     \
        ({                                                                      \
            __PERF_INFO__.dwNoInstr = perfc_pmu_get_instruction_count()         \
                                    - __PERF_INFO__.dwNoInstr                   \
                                    - __PERF_INFO__.wInstrCalib;                \
            __PERF_INFO__.dwNoMemAccess = perfc_pmu_get_memory_access_count()   \
                                        - __PERF_INFO__.dwNoMemAccess           \
                                        - __PERF_INFO__.wMemAccessCalib;        \
            __PERF_INFO__.dwNoL1DCacheRefill                                    \
                = perfc_pmu_get_L1_dcache_refill_count()                        \
                - __PERF_INFO__.dwNoL1DCacheRefill;                             \
            __PERF_INFO__.dwNoL1ICacheRefill                                    \
                = perfc_pmu_get_L1_icache_refill_count()                        \
                - __PERF_INFO__.dwNoL1ICacheRefill;                             \
                                                                                \
            __PERF_INFO__.fDCacheMissRate                                       \
                        = (float)( (double)__PERF_INFO__.dwNoL1DCacheRefill     \
                                 / (double)__PERF_INFO__.dwNoMemAccess)         \
                        * 100.0f;                                               \
                                                                                \
            __PERF_INFO__.fICacheMissRate                                       \
                        = (float)( (double)__PERF_INFO__.dwNoL1ICacheRefill     \
                                 / (double)__PERF_INFO__.dwNoInstr)             \
                        * 100.0f;                                               \
            __PERF_INFO__.fCPI = (float)(    (double)__PERF_INFO__.lCycles      \
                                       /    (double)__PERF_INFO__.dwNoInstr);   \
            if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                        \
                __perf_counter_printf__( "\r\n"                                 \
                        "[Report for %s]\r\n"                                   \
                        "-----------------------------------------\r\n"         \
                        "Instruction executed: %"PRIi64"\r\n"                   \
                        "Cycle Used: %"PRIi64"\r\n"                             \
                        "Cycles per Instructions: %3.3f \r\n\r\n"               \
                        "Memory Access Count: %"PRIi64"\r\n"                    \
                        "L1 DCache Refill Count: %"PRIi64"\r\n"                 \
                        "L1 DCache Miss Rate: %3.4f %% \r\n"                    \
                        "L1 ICache Refill Count: %"PRIi64"\r\n"                 \
                        "L1 ICache Miss Rate: %3.4f %% \r\n"                    \
                        ,                                                       \
                        (__str),                                                \
                        __PERF_INFO__.dwNoInstr,                                \
                        __PERF_INFO__.lCycles,                                  \
                        (double)__PERF_INFO__.fCPI,                             \
                        __PERF_INFO__.dwNoMemAccess,                            \
                        __PERF_INFO__.dwNoL1DCacheRefill,                       \
                        (double)__PERF_INFO__.fDCacheMissRate,                  \
                        __PERF_INFO__.dwNoL1ICacheRefill,                       \
                        (double)__PERF_INFO__.fICacheMissRate                   \
                        );                                                      \
             } else {                                                           \
                __VA_ARGS__                                                     \
             }                                                                  \
        }))                                                                     \
        __cycleof__("", { __PERF_INFO__.lCycles = __cycle_count__; })



#if defined(__PERFC_STACK_GROWS_UPWARD__)
#error The macro "__PERFC_STACK_GROWS_UPWARD__" is defined but the stacks of \
the Cortex-M architecture grow downward!! Please remove the macro from project!!
#endif

#if defined(__PERFC_STACK_CHECK_IN_ISR__)

#   define __ISR(__ISR_NAME, __STACK_SIZE_HINT)                                 \
volatile                                                                        \
uint32_t g_w##__ISR_NAME##_StackUsage = 0;                                      \
                                                                                \
extern void __origin_##__ISR_NAME (void);                                       \
void __ISR_NAME(void)                                                           \
{                                                                               \
    uint32_t wEXCRETURN;                                                        \
    __disable_irq();                                                            \
    __ASM volatile ("mov %0, lr"  : "=r" (wEXCRETURN) );                        \
    bool bExtendedStackFrame = !(wEXCRETURN & (1 << 4));                        \
    bool bSPSELMSP = !(wEXCRETURN & (1 << 2));                                  \
    bool bCrossSecureDomain = (!!(wEXCRETURN & (1 << 6)))   /* from  */         \
                            ^ (!!(wEXCRETURN & (1 << 0)));  /* to */            \
                                                                                \
    uintptr_t nStackLimit = __perfc_port_get_sp() - (__STACK_SIZE_HINT);        \
    __enable_irq();                                                             \
    __stack_usage_max__(#__ISR_NAME, nStackLimit,                               \
        {                                                                       \
            g_w##__ISR_NAME##_StackUsage = __stack_used_max__;                  \
            /* the interrupted program use MPS and in the same secure domain */ \
            if (bSPSELMSP && !bCrossSecureDomain) {                             \
                /* check FPU lazy stacking */                                   \
                uint32_t wFPCCR = (*(volatile uint32_t *)(0xE000EF34));         \
                bExtendedStackFrame                                             \
                    = bExtendedStackFrame && !(wFPCCR & (1<<0));                \
                uint32_t wFPUFrame = 18 * sizeof(uint32_t)     /* FP context */ \
                                    /* additional FP context */                 \
                                   + (  ((wFPCCR & (1 << 26)))  /* TS */        \
                                     ?  16 * sizeof(uint32_t)                   \
                                     :  0);                                     \
                                              /* state context */               \
                g_w##__ISR_NAME##_StackUsage +=    8 * sizeof(uint32_t)         \
                                              /* FP context */                  \
                                              +     (   bExtendedStackFrame     \
                                                    ?   wFPUFrame               \
                                                    : 0)                        \
                                              /* Additional state context */    \
                                              +     (!(wEXCRETURN & (1 << 5))   \
                                                    ?   10 * sizeof(uint32_t)   \
                                                    : 0);                       \
            }                                                                   \
        }                                                                       \
    ) {                                                                         \
        __origin_##__ISR_NAME();                                                \
    }                                                                           \
}                                                                               \
                                                                                \
void __origin_##__ISR_NAME (void)
#else

#   define __ISR(__ISR_NAME, __STACK_SIZE_HINT)                                 \
volatile                                                                        \
uint32_t g_w##__ISR_NAME##_StackUsage = 0;                                      \
void __ISR_NAME(void)
#endif

#define ISR(__ISR_NAME, __STACK_SIZE_HINT)  __ISR(__ISR_NAME, __STACK_SIZE_HINT)

#ifndef __PERFC_SYSTIMER_PRIORITY__
#   define __PERFC_SYSTIMER_PRIORITY__      0
#endif

/*============================ TYPES =========================================*/
typedef uint32_t perfc_global_interrupt_status_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
extern
void perfc_port_pmu_insert_to_debug_monitor_handler(void);

extern
uint64_t perfc_pmu_get_instruction_count(void);

extern
uint64_t perfc_pmu_get_memory_access_count(void);

extern
uint64_t perfc_pmu_get_L1_dcache_refill_count(void);

extern
uint64_t perfc_pmu_get_L1_icache_refill_count(void);

/*============================ IMPLEMENTATION ================================*/

__STATIC_INLINE 
perfc_global_interrupt_status_t perfc_port_disable_global_interrupt(void)
{
    perfc_global_interrupt_status_t tStatus = __get_PRIMASK();
    __disable_irq();
    
    return tStatus;
}

__STATIC_INLINE 
void perfc_port_resume_global_interrupt(perfc_global_interrupt_status_t tStatus)
{
    __set_PRIMASK(tStatus);
}

__STATIC_INLINE 
perfc_global_interrupt_status_t perfc_port_mask_systimer_interrupt(void)
{
    perfc_global_interrupt_status_t tStatus = __get_BASEPRI();
    __set_BASEPRI_MAX(__PERFC_SYSTIMER_PRIORITY__);
    
    return tStatus;
}

__STATIC_INLINE 
void perfc_port_resume_systimer_interrupt(perfc_global_interrupt_status_t tStatus)
{
    __set_BASEPRI(tStatus);   
}


#endif
