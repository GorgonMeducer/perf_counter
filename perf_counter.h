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

#ifndef __PERFORMANCE_COUNTER_H__
#define __PERFORMANCE_COUNTER_H__

/*============================ INCLUDES ======================================*/
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "cmsis_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/

#define __PERF_COUNTER_VER_MAJOR__          1
#define __PERF_COUNTER_VER_MINOR__          9
#define __PERF_COUNTER_VER_REVISE__         6

#define __PERF_COUNTER_VER_STR__            "dev"

#define __PER_COUNTER_VER__    (__PERF_COUNTER_VER_MAJOR__ * 10000ul            \
                               +__PERF_COUNTER_VER_MINOR__ * 100ul              \
                               +__PERF_COUNTER_VER_REVISE__)

//! \name The macros to identify the compiler
//! @{

//! \note for IAR
#undef __IS_COMPILER_IAR__
#if defined(__IAR_SYSTEMS_ICC__)
#   define __IS_COMPILER_IAR__                  1
#endif

//! \note for arm compiler 5
#undef __IS_COMPILER_ARM_COMPILER_5__
#if ((__ARMCC_VERSION >= 5000000) && (__ARMCC_VERSION < 6000000))
#   define __IS_COMPILER_ARM_COMPILER_5__       1
#endif
//! @}

//! \note for arm compiler 6

#undef __IS_COMPILER_ARM_COMPILER_6__
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#   define __IS_COMPILER_ARM_COMPILER_6__       1
#endif

#undef __IS_COMPILER_ARM_COMPILER__
#if defined(__IS_COMPILER_ARM_COMPILER_5__) && __IS_COMPILER_ARM_COMPILER_5__   \
||  defined(__IS_COMPILER_ARM_COMPILER_6__) && __IS_COMPILER_ARM_COMPILER_6__

#   define __IS_COMPILER_ARM_COMPILER__         1

#endif


#undef  __IS_COMPILER_LLVM__
#if defined(__clang__) && !__IS_COMPILER_ARM_COMPILER_6__
#   define __IS_COMPILER_LLVM__                 1
#else
//! \note for gcc
#   undef __IS_COMPILER_GCC__
#   if defined(__GNUC__) && !(  defined(__IS_COMPILER_ARM_COMPILER__)           \
                            ||  defined(__IS_COMPILER_LLVM__)                   \
                            ||  defined(__IS_COMPILER_IAR__))
#       define __IS_COMPILER_GCC__              1
#   endif
//! @}
#endif
//! @}

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#   pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#   pragma clang diagnostic ignored "-Wgnu-statement-expression"
#   pragma clang diagnostic ignored "-Wunused-but-set-variable"
#   pragma clang diagnostic ignored "-Wshadow"
#   pragma clang diagnostic ignored "-Wshorten-64-to-32"
#   pragma clang diagnostic ignored "-Wcompound-token-split-by-macro"
#elif defined(__IS_COMPILER_ARM_COMPILER_5__)
#   pragma diag_suppress 550
#elif defined(__IS_COMPILER_GCC__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wpedantic"
#   pragma GCC diagnostic ignored "-Wunused-variable"
#   pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#   pragma GCC diagnostic ignored "-Wformat="
#endif

#ifndef __PLOOC_VA_NUM_ARGS_IMPL
#   define __PLOOC_VA_NUM_ARGS_IMPL( _0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,     \
                                    _12,_13,_14,_15,_16,__N,...)      __N
#endif

#ifndef __PLOOC_VA_NUM_ARGS
#define __PLOOC_VA_NUM_ARGS(...)                                                \
            __PLOOC_VA_NUM_ARGS_IMPL( 0,##__VA_ARGS__,16,15,14,13,12,11,10,9,   \
                                      8,7,6,5,4,3,2,1,0)
#endif

#ifndef UNUSED_PARAM
#   define UNUSED_PARAM(__VAR)     (void)(__VAR)
#endif

#undef __CONNECT2
#undef __CONNECT3
#undef __CONNECT4
#undef __CONNECT5
#undef __CONNECT6
#undef __CONNECT7
#undef __CONNECT8
#undef __CONNECT9

#undef CONNECT2
#undef CONNECT3
#undef CONNECT4
#undef CONNECT5
#undef CONNECT6
#undef CONNECT7
#undef CONNECT8
#undef CONNECT9

#undef CONNECT

#undef __MACRO_EXPANDING
#define __MACRO_EXPANDING(...)                      __VA_ARGS__

#define __CONNECT2(__A, __B)                        __A##__B
#define __CONNECT3(__A, __B, __C)                   __A##__B##__C
#define __CONNECT4(__A, __B, __C, __D)              __A##__B##__C##__D
#define __CONNECT5(__A, __B, __C, __D, __E)         __A##__B##__C##__D##__E
#define __CONNECT6(__A, __B, __C, __D, __E, __F)    __A##__B##__C##__D##__E##__F
#define __CONNECT7(__A, __B, __C, __D, __E, __F, __G)                           \
                                                    __A##__B##__C##__D##__E##__F##__G
#define __CONNECT8(__A, __B, __C, __D, __E, __F, __G, __H)                      \
                                                    __A##__B##__C##__D##__E##__F##__G##__H
#define __CONNECT9(__A, __B, __C, __D, __E, __F, __G, __H, __I)                 \
                                                    __A##__B##__C##__D##__E##__F##__G##__H##__I

#define ALT_CONNECT2(__A, __B)              __CONNECT2(__A, __B)
#define CONNECT2(__A, __B)                  __CONNECT2(__A, __B)
#define CONNECT3(__A, __B, __C)             __CONNECT3(__A, __B, __C)
#define CONNECT4(__A, __B, __C, __D)        __CONNECT4(__A, __B, __C, __D)
#define CONNECT5(__A, __B, __C, __D, __E)   __CONNECT5(__A, __B, __C, __D, __E)
#define CONNECT6(__A, __B, __C, __D, __E, __F)                                  \
                                            __CONNECT6(__A, __B, __C, __D, __E, __F)
#define CONNECT7(__A, __B, __C, __D, __E, __F, __G)                             \
                                            __CONNECT7(__A, __B, __C, __D, __E, __F, __G)
#define CONNECT8(__A, __B, __C, __D, __E, __F, __G, __H)                        \
                                            __CONNECT8(__A, __B, __C, __D, __E, __F, __G, __H)
#define CONNECT9(__A, __B, __C, __D, __E, __F, __G, __H, __I)                   \
                                            __CONNECT9(__A, __B, __C, __D, __E, __F, __G, __H, __I)

#define CONNECT(...)                                                            \
            ALT_CONNECT2(CONNECT, __PLOOC_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

#undef __using1
#undef __using2
#undef __using3
#undef __using4
#undef using

#define __using1(__declare)                                                     \
            for (__declare, *CONNECT3(__using_, __LINE__,_ptr) = NULL;          \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL;                   \
                )

#define __using2(__declare, __on_leave_expr)                                    \
            for (__declare, *CONNECT3(__using_, __LINE__,_ptr) = NULL;          \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL;                   \
                 (__on_leave_expr)                                              \
                )

#define __using3(__declare, __on_enter_expr, __on_leave_expr)                   \
            for (__declare, *CONNECT3(__using_, __LINE__,_ptr) = NULL;          \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL ?                  \
                    ((__on_enter_expr),1) : 0;                                  \
                 (__on_leave_expr)                                              \
                )

#define __using4(__dcl1, __dcl2, __on_enter_expr, __on_leave_expr)              \
            for (__dcl1, __dcl2, *CONNECT3(__using_, __LINE__,_ptr) = NULL;     \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL ?                  \
                    ((__on_enter_expr),1) : 0;                                  \
                 (__on_leave_expr)                                              \
                )

#define using(...)                                                              \
                CONNECT2(__using, __PLOOC_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)


#undef __with2
#undef __with3
#undef with

#define __with2(__type, __addr)                                                 \
            using(__type *_=(__addr))
#define __with3(__type, __addr, __item)                                         \
            using(__type *_=(__addr), *__item = _, _=_,_=_ )

#define with(...)                                                               \
            CONNECT2(__with, __PLOOC_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

#undef _

#ifndef dimof
#   define dimof(__array)          (sizeof(__array)/sizeof(__array[0]))
#endif


#define SAFE_NAME(__NAME)   CONNECT3(__,__NAME,__LINE__)

#undef foreach2
#undef foreach3
#undef foreach

#define foreach2(__type, __array)                                               \
            using(__type *_ = __array)                                          \
            for (   uint_fast32_t SAFE_NAME(count) = dimof(__array);            \
                    SAFE_NAME(count) > 0;                                       \
                    _++, SAFE_NAME(count)--                                     \
                )

#define foreach3(__type, __array, __item)                                       \
            using(__type *_ = __array, *__item = _, _ = _, _ = _ )              \
            for (   uint_fast32_t SAFE_NAME(count) = dimof(__array);            \
                    SAFE_NAME(count) > 0;                                       \
                    _++, __item = _, SAFE_NAME(count)--                         \
                )

#define foreach(...)                                                            \
            CONNECT2(foreach, __PLOOC_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

#ifndef safe_atom_code
#   define safe_atom_code()                                                     \
            using(  uint32_t SAFE_NAME(temp) =                                  \
                        ({  uint32_t SAFE_NAME(temp2)=__get_PRIMASK();          \
                            __disable_irq();                                    \
                            SAFE_NAME(temp2);}),                                \
                        __set_PRIMASK(SAFE_NAME(temp)))
#endif

#ifndef __IRQ_SAFE
#   define __IRQ_SAFE                                                           \
            using(  uint32_t SAFE_NAME(temp) =                                  \
                        ({  uint32_t SAFE_NAME(temp2)=__get_PRIMASK();          \
                            __disable_irq();                                    \
                            SAFE_NAME(temp2);}),                                \
                        __set_PRIMASK(SAFE_NAME(temp)))
#endif

#if defined(__RTTHREAD__)
#   include <rtthread.h>
#   define __perf_counter_printf__      rt_kprintf
#elif !defined(__perf_counter_printf__)
#   define __perf_counter_printf__      printf
#endif

#if __PLOOC_VA_NUM_ARGS() != 0
#warning Please enable GNC extensions, it is required by __cycleof__() and \
__super_loop_monitor__()
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/

#define __cycleof__(__STR, ...)                                                 \
            using(int64_t _ = get_system_ticks(), __cycle_count__ = _,          \
                _=_, {                                                          \
                _ = get_system_ticks() - _;                                     \
                __cycle_count__ = _;                                            \
                if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                    \
                    __perf_counter_printf__("\r\n");                            \
                    __perf_counter_printf__("-[Cycle Report]");                 \
                    __perf_counter_printf__(                                    \
                        "--------------------------------------------\r\n");    \
                    __perf_counter_printf__(                                    \
                        __STR " total cycle count: %d [%08x]\r\n",              \
                            (int)_, (int)_);                                    \
                } else {                                                        \
                    __VA_ARGS__                                                 \
                };                                                              \
            })



#define __super_loop_monitor__(__N, ...)                                        \
    using(                                                                      \
        struct {                                                                \
            int64_t lStart;                                                     \
            int64_t lTaskUsedCycles;                                            \
            int64_t lTimeElapsed;                                               \
        } __cpu_usage__ = {.lStart = get_system_ticks()})                       \
    using(int SAFE_NAME(cnt) = (__N))                                           \
    for(start_task_cycle_counter();; ({                                         \
        if (!(--SAFE_NAME(cnt))) {                                              \
            __cpu_usage__.lTimeElapsed                                          \
                = get_system_ticks() - __cpu_usage__.lStart;                    \
            __cpu_usage__.lTaskUsedCycles = stop_task_cycle_counter();          \
                                                                                \
            if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                        \
                __perf_counter_printf__(                                        \
                    "%s CPU Usage %2.3f%%\r\n", __func__,                       \
                    (float)((double)__cpu_usage__.lTaskUsedCycles * 100.0 /     \
                            (double)__cpu_usage__.lTimeElapsed));               \
            } else {                                                            \
                __VA_ARGS__;                                                    \
            }                                                                   \
            SAFE_NAME(cnt) = (__N);                                             \
            __cpu_usage__.lStart = get_system_ticks();                          \
            start_task_cycle_counter();                                         \
        };                                                                      \
    }))

/*============================ TYPES =========================================*/
typedef struct {
    int64_t             lStart;
    int64_t             lUsedTotal;
    int32_t             nUsedRecent;
    uint16_t            hwActiveCount;
    uint16_t                        : 15;
    uint16_t            bEnabled    : 1;
} task_cycle_info_t;

typedef struct task_cycle_info_agent_t task_cycle_info_agent_t;

struct task_cycle_info_agent_t {
    task_cycle_info_t *ptInfo;
    task_cycle_info_agent_t *ptNext;
    task_cycle_info_agent_t *ptPrev;
};


/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/


/*!
 * \brief try to set a start pointer for the performance counter
 *
 * \retval false the LOAD register is too small
 *
 * \retval true performance counter starts
 */
extern bool start_cycle_counter(void);

/*!
 * \brief calculate the elapsed cycle count since the last start point
 *
 * \note  you can have multiple stop_cycle_counter following one start point
 *
 * \return int32_t the elapsed cycle count
 */
extern int32_t stop_cycle_counter(void);

/*!
 * \brief delay specified time in microsecond
 *
 * \param nUs time in microsecond
 */
extern void delay_us(int32_t nUs);

/*!
 * \brief delay specified time in millisecond
 *
 * \param nUs time in millisecond
 */
extern void delay_ms(int32_t nMs);

#ifdef __PERF_CNT_USE_LONG_CLOCK__
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
extern int64_t clock(void);
#endif

/*!
 * \brief get the elapsed cycles since perf_counter is initialised
 *
 * \return int64_t the elpased cycles
 */
extern int64_t get_system_ticks(void);

/*!
 * \brief get the elapsed milliseconds since perf_counter is initialised
 *
 * \return int32_t the elapsed milliseconds
 */
extern int32_t get_system_ms(void);


#if defined(__PERF_CNT_USE_RTOS__)

/*! \brief initialize the default virtual cycle counter for the current task
 */
extern void init_task_cycle_counter(void);

/*! \brief provide cycle information for target task if perf_counter is used
 *!        together with an RTOS in the support list.
 *!        Support RTOS List:
 *!           - RTX5
 *!           - RT-Thread
 *!           - ThreadX
 *!           - FreeRTOS
 *!
 *! \return task_cycle_info_t* the cycle info object passed to this function
 */
extern task_cycle_info_t * get_rtos_task_cycle_info(void);


/*!
 *! \brief intialize a given task_cycle_info_t object and enable it before
 *!        registering it.
 *!
 *! \return task_cycle_info_t* the cycle info object passed to this function
 */
extern task_cycle_info_t *init_task_cycle_info(task_cycle_info_t *ptInfo);

/*! \brief enable a given task_cycle_info_t object
 *!
 *! \param ptInfo the address of target task_cycle_info_t object
 *! \return bool previous status
 */
extern bool enable_task_cycle_info(task_cycle_info_t *ptInfo);

/*! \brief disable a given task_cycle_info_t object
 *!
 *! \param ptInfo the address of target task_cycle_info_t object
 *! \return bool previous status
 */
extern bool disable_task_cycle_info(task_cycle_info_t *ptInfo);

/*! \brief resume the enabled status of a given task_cycle_info_t object
 *!
 *! \param ptInfo the address of target task_cycle_info_t object
 *! \param bEnabledStatus the previous status
 */
extern
void resume_task_cycle_info(task_cycle_info_t *ptInfo, bool bEnabledStatus);

/*! \brief register a global virtual cycle counter agent to the current task
 *!
 *! \note the ptAgent it is better to be allocated as a static variable, global
 *!       variable or comes from heap or pool
 *!
 *! \return task_cycle_info_agent_t* the agent passed to this function
 */
extern
task_cycle_info_agent_t *register_task_cycle_agent(
                                            task_cycle_info_t *ptInfo,
                                            task_cycle_info_agent_t *ptAgent);

/*!
 *! \brief remove a global virtual cycle counter agent from the current task
 *!
 *! \return task_cycle_info_agent_t* the agent passed to this function
 */
extern
task_cycle_info_agent_t *
unregister_task_cycle_agent(task_cycle_info_agent_t *ptAgent);

/*! \brief reset and start the virtual cycle counter for the current task
 *!
 *! \param ptInfo the target task_cycle_info_t object
 */
extern void __start_task_cycle_counter(task_cycle_info_t *ptInfo);

/*! \brief calculate the elapsed cycle count for current task since the last
 *!        start point
 *!
 *! \note you can call stop_cycle_counter() multiple times following one
 *!       start_task_cycle_counter()
 *!
 *! \param ptInfo the target task_cycle_info_t object
 *!
 *! \note  When ptInfo is NULL, it returns current task cycle info, when ptInfo
 *!        is non-NULL, it returns the total used cycles of the specified
 *!        task_cycle_info_t object.
 *!
 *! \return int64_t the elapsed cycle count.
 */
extern int64_t __stop_task_cycle_counter(task_cycle_info_t *ptInfo);


#define start_task_cycle_counter(...)                                           \
            __start_task_cycle_counter((NULL,##__VA_ARGS__))

#define stop_task_cycle_counter(...)                                            \
            __stop_task_cycle_counter((NULL,##__VA_ARGS__))

#elif !defined(__IMPLEMENT_PERF_COUNTER)
#   define start_task_cycle_counter(...)    start_cycle_counter()
#   define stop_task_cycle_counter(...)     stop_cycle_counter()
#   define init_task_cycle_counter()
#   define register_task_cycle_agent(...)
#   define unregister_task_cycle_agent(...)
#   define init_task_cycle_info(...)        (NULL)
#   define enable_task_cycle_info(...)      (false)
#   define disable_task_cycle_info(...)     (false)
#   define resume_task_cycle_info(...)
#endif

/*----------------------------------------------------------------------------*
 * Please ignore the following APIs unless you have encountered some known    *
 * special conditions                                                         *
 *----------------------------------------------------------------------------*/


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
extern void init_cycle_counter(bool bIsSysTickOccupied);


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
extern void user_code_insert_to_systick_handler(void);

/*!
 * \brief update perf_counter as SystemCoreClock has been updated.
 */
extern void update_perf_counter(void);

//#if defined(__clang__)
//#   pragma clang diagnostic pop
//#elif defined(__IS_COMPILER_GCC__)
//#   pragma GCC diagnostic pop
//#endif

#ifdef __cplusplus
}
#endif

#endif
