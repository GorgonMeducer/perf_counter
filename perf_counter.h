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

#ifndef __PERFORMANCE_COUNTER_H__
#define __PERFORMANCE_COUNTER_H__

/*============================ INCLUDES ======================================*/
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef __PERFC_CFG_PORTING_INCLUDE__
#   include "perfc_port_default.h"
#else
#   include __PERFC_CFG_PORTING_INCLUDE__
#endif

#ifdef __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/

/*!
 * \addtogroup gBasic 1 Basic
 * @{
 */
#define __PERF_COUNTER_VER_MAJOR__          2
#define __PERF_COUNTER_VER_MINOR__          3
#define __PERF_COUNTER_VER_REVISE__         2

#define __PERF_COUNTER_VER_STR__            ""

#define __PER_COUNTER_VER__    (__PERF_COUNTER_VER_MAJOR__ * 10000ul            \
                               +__PERF_COUNTER_VER_MINOR__ * 100ul              \
                               +__PERF_COUNTER_VER_REVISE__)


/*! @} */

/*!
 * \addtogroup gHelper 4 Helper
 * @{
 */

// for IAR
#undef __IS_COMPILER_IAR__
#if defined(__IAR_SYSTEMS_ICC__)
#   define __IS_COMPILER_IAR__                  1
#endif

// for arm compiler 5
#undef __IS_COMPILER_ARM_COMPILER_5__
#if ((__ARMCC_VERSION >= 5000000) && (__ARMCC_VERSION < 6000000))
#   define __IS_COMPILER_ARM_COMPILER_5__       1
#endif


//for arm compiler 6

#undef __IS_COMPILER_ARM_COMPILER_6__
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#   define __IS_COMPILER_ARM_COMPILER_6__       1
#endif
#undef __IS_COMPILER_ARM_COMPILER__
#if defined(__IS_COMPILER_ARM_COMPILER_5__) && __IS_COMPILER_ARM_COMPILER_5__   \
||  defined(__IS_COMPILER_ARM_COMPILER_6__) && __IS_COMPILER_ARM_COMPILER_6__
#   define __IS_COMPILER_ARM_COMPILER__         1
#endif

// for clang
#undef  __IS_COMPILER_LLVM__
#if defined(__clang__) && !__IS_COMPILER_ARM_COMPILER_6__
#   define __IS_COMPILER_LLVM__                 1
#else

// for gcc
#   undef __IS_COMPILER_GCC__
#   if defined(__GNUC__) && !(  defined(__IS_COMPILER_ARM_COMPILER__)           \
                            ||  defined(__IS_COMPILER_LLVM__)                   \
                            ||  defined(__IS_COMPILER_IAR__))
#       define __IS_COMPILER_GCC__              1
#   endif

#endif


#ifdef __PERF_COUNT_PLATFORM_SPECIFIC_HEADER__
#   include __PERF_COUNT_PLATFORM_SPECIFIC_HEADER__
#endif

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
#   pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
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

#ifndef MIN
#   define MIN(__a, __b)  ((__a) <= (__b) ? (__a) : (__b))
#endif

#ifndef MAX
#   define MAX(__a, __b)  ((__a) >= (__b) ? (__a) : (__b))
#endif

/*!
 * \brief an attribute for static variables that no initialisation is required 
 *        in the C startup process.
 */
#ifndef PERF_NOINIT
#   if     defined(__IS_COMPILER_ARM_COMPILER_5__)
#       define PERF_NOINIT   __attribute__(( section( ".bss.noinit"),zero_init))
#   elif   defined(__IS_COMPILER_ARM_COMPILER_6__)
#       define PERF_NOINIT   __attribute__(( section( ".bss.noinit")))
#   elif   defined(__IS_COMPILER_IAR__)
#       define PERF_NOINIT   __no_init
#   elif   (defined(__IS_COMPILER_GCC__) || defined(__IS_COMPILER_LLVM__)) && !defined(__APPLE__)
#       define PERF_NOINIT   __attribute__(( section( ".bss.noinit")))
#   else
#       define PERF_NOINIT
#   endif
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
            using(  perfc_global_interrupt_status_t SAFE_NAME(temp) =           \
                        perfc_port_disable_global_interrupt(),                  \
                    perfc_port_resume_global_interrupt(SAFE_NAME(temp)))
#endif

#ifndef __IRQ_SAFE
#   define __IRQ_SAFE                                                           \
            using(  perfc_global_interrupt_status_t SAFE_NAME(temp) =           \
                        perfc_port_disable_global_interrupt(),                  \
                    perfc_port_resume_global_interrupt(SAFE_NAME(temp)))
#endif

#ifndef __perf_counter_printf__
#   define __perf_counter_printf__      printf
#endif

/* deprecated macro for backward compatibility */
#define user_code_insert_to_systick_handler                                     \
            perfc_port_insert_to_system_timer_insert_ovf_handler

#if __PLOOC_VA_NUM_ARGS() != 0
#warning Please enable GNU extensions, it is required by __cycleof__() and \
__super_loop_monitor__()
#endif

#if defined(__PERF_COUNTER_CFG_USE_SYSTICK_WRAPPER__)                           \
 && (   !defined(__PERFC_USE_PORTING__)                                         \
    ||  (defined(__PERFC_USE_PORTING__) && (0 == __PERFC_USE_PORTING__)) )

#   if defined(__IS_COMPILER_ARM_COMPILER_5__) && __IS_COMPILER_ARM_COMPILER_5__
#       pragma import(__ensure_systick_wrapper)
#   elif    (defined(__GNUC__) || defined(__clang__))                           \
        &&  (!defined(__IS_COMPILER_IAR__) || !__IS_COMPILER_IAR__)
__asm(".global __ensure_systick_wrapper\n\t");
#   endif

#ifndef __perfc_sync_barrier__

/* default implementation */
#if defined(__clang__) || __IS_COMPILER_GCC__
#   define __perfc_sync_barrier__(...)      __sync_synchronize()
#else
#   define __perfc_sync_barrier__(...)
#endif

#endif

#endif
/*! @} */

/*============================ MACROFIED FUNCTIONS ===========================*/

/*!
 * \addtogroup gBasic 1 Basic
 * @{
 */

/*!
 * \brief measure the cycle count of a given code segment
 * \param[in] __STR a description string for the measurement
 * \param[in] ... an optional code segement, in which we can read the measured
 *                result from __cycle_count__.
 * \details Here is an example:
    E.g.
    \code
        __cycleof__("printf") {
            printf("hello world\r\n");
        }
    \endcode
 */
#define __cycleof__(__STR, ...)                                                 \
            using(int64_t _ = get_system_ticks(), __cycle_count__ = _,          \
                {__perfc_sync_barrier__();},                                    \
                {                                                               \
                __perfc_sync_barrier__();                                       \
                _ = get_system_ticks() - _ - g_nOffset;                         \
                __cycle_count__ = _;                                            \
                if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                    \
                    __perf_counter_printf__("\r\n");                            \
                    __perf_counter_printf__("-[Cycle Report]");                 \
                    __perf_counter_printf__(                                    \
                        "------------------------------------\r\n");            \
                    __perf_counter_printf__(                                    \
                        __STR " total cycle count: %ld [%08lx]\r\n",            \
                            (long)_, (long)_);                                  \
                } else {                                                        \
                    __VA_ARGS__                                                 \
                };                                                              \
            })

/*!
 * \brief measure the cpu usage for a given code segment and print out the
 *        result in percentage.
 * \param[in] __CNT generate result on every given iterations
 * \param[in] ... an optional code segement, in which we can read the measured
 *                result from __usage__ which is a float value.
 * \details Here is an example, 50% cpu time:
    E.g.
    \code
        while (1) {
            __cpu_usage__(100) {
                delay_us(5000);
            }
            delay_us(5000);
        }
    \endcode
 */
#define __cpu_usage__(__CNT, ...)                                               \
    static int64_t SAFE_NAME(s_lTimestamp) = 0, SAFE_NAME(s_lTotal) = 0;        \
    static uint32_t SAFE_NAME(s_wLoopCounter) = (__CNT);                        \
    using(float __usage__ = 0, ({                                               \
    if (0 == SAFE_NAME(s_wLoopCounter)) {                                       \
        __usage__ = (float)((double)SAFE_NAME(s_lTotal)                         \
                        / (double)(     get_system_ticks()                      \
                                  -     SAFE_NAME(s_lTimestamp)));              \
        __usage__ *= 100.0f;                                                    \
        SAFE_NAME(s_lTimestamp) = 0;                                            \
        SAFE_NAME(s_lTotal) = 0;                                                \
        if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                            \
            __perf_counter_printf__("CPU Usage %3.2f%%\r\n", (double)__usage__);\
        } else {                                                                \
            __VA_ARGS__                                                         \
        }                                                                       \
    }                                                                           \
    if (0 == SAFE_NAME(s_lTimestamp)) {                                         \
        SAFE_NAME(s_lTimestamp) = get_system_ticks();                           \
        SAFE_NAME(s_wLoopCounter) = (__CNT);                                    \
    }                                                                           \
    start_task_cycle_counter();}),                                              \
    ({SAFE_NAME(s_lTotal) += stop_task_cycle_counter();                         \
    SAFE_NAME(s_wLoopCounter)--;}))

#define __cpu_time__    __cpu_usage__

/*!
 * \addtogroup gBasicTimerService 1.2 Timer Service
 * \ingroup gBasic
 * @{
 */

/*!
 * \brief should not use
 */
#define perfc_is_time_out_ms0()         true

/*!
 * \brief set an alarm with given period in ms and check the status
 *
 * \param[in] __ms a time period in millisecond
 * \param[in] __timestamp_ptr an optional timestamp holder
 * \param[in] __auto_reload whether starting next period after a timeout event
 *
 * \return bool whether it is timeout
 */
#define perfc_is_time_out_ms3(__ms, __timestamp_ptr, __auto_reload)             \
    ({  static int64_t SAFE_NAME(s_lTimestamp);  (void)SAFE_NAME(s_lTimestamp); \
        __perfc_is_time_out(perfc_convert_ms_to_ticks(__ms),                    \
        (__timestamp_ptr), (__auto_reload));})

/*!
 * \brief set an alarm with given period in ms and check the status
 *
 * \param[in] __ms a time period in millisecond
 * \param[in] __timestamp_ptr an optional timestamp holder
 *
 * \return bool whether it is timeout
 */
#define perfc_is_time_out_ms2(__ms, __timestamp_ptr)                            \
            perfc_is_time_out_ms3((__ms), (__timestamp_ptr), true)


/*!
 * \brief set an alarm with given period in ms and check the status
 *
 * \param[in] __ms a time period in millisecond
 * \param[in] __timestamp_ptr an optional timestamp holder
 *
 * \return bool whether it is timeout
 */
#define perfc_is_time_out_ms1(__ms)                                             \
            perfc_is_time_out_ms3((__ms), &SAFE_NAME(s_lTimestamp), true)

/*!
 * \brief set an alarm with given period in ms and check the status
 *
 * \param[in] __ms a time period in millisecond
 * \param[in] ... an optional timestamp holder
 * \param[in] ... an optional indicator for whether starting next period after a timeout event
 *
 * \return bool whether it is timeout
 */
#define perfc_is_time_out_ms(...)                                               \
            CONNECT2(perfc_is_time_out_ms, __PLOOC_VA_NUM_ARGS(__VA_ARGS__))    \
                (__VA_ARGS__)

/*!
 * \brief set an alarm with given period in us and check the status
 *
 * \param[in] __us a time period in microsecond
 * \param[in] __timestamp_ptr an optional timestamp holder
 * \param[in] __auto_reload whether starting next period after a timeout event
 *
 * \return bool whether it is timeout
 */
#define perfc_is_time_out_us3(__us, __timestamp_ptr, __auto_reload)             \
    ({  static int64_t SAFE_NAME(s_lTimestamp); (void)SAFE_NAME(s_lTimestamp);  \
        __perfc_is_time_out(perfc_convert_us_to_ticks(__us),                    \
        (__timestamp_ptr), (__auto_reload));})

/*!
 * \brief set an alarm with given period in us and check the status
 *
 * \param[in] __us a time period in microsecond
 * \param[in] __timestamp_ptr an optional timestamp holder
 *
 * \return bool whether it is timeout
 */
#define perfc_is_time_out_us2(__us, __timestamp_ptr)                            \
            perfc_is_time_out_us3((__us), (__timestamp_ptr), true)


/*!
 * \brief set an alarm with given period in us and check the status
 *
 * \param[in] __us a time period in microsecond
 * \param[in] __timestamp_ptr an optional timestamp holder
 *
 * \return bool whether it is timeout
 */
#define perfc_is_time_out_us1(__us)                                             \
            perfc_is_time_out_us3((__us), &SAFE_NAME(s_lTimestamp), true)

/*!
 * \brief set an alarm with given period in us and check the status
 *
 * \param[in] __us a time period in microsecond
 * \param[in] ... an optional timestamp holder
 * \param[in] ... an optional indicator for whether starting next period after a timeout event
 *
 * \return bool whether it is timeout
 */
#define perfc_is_time_out_us(...)                                               \
            CONNECT2(perfc_is_time_out_us, __PLOOC_VA_NUM_ARGS(__VA_ARGS__))    \
                (__VA_ARGS__)


/*! @} */

/*! @} */

/*!
 * \addtogroup gRTOS 2 RTOS Support
 * @{
 */
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
                = get_system_ticks() - __cpu_usage__.lStart - g_nOffset;        \
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

/*! @} */

/*============================ GLOBAL VARIABLES ==============================*/
extern volatile int64_t g_lLastTimeStamp;
extern volatile int32_t g_nOffset;
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/


/*!
 * \addtogroup gBasicTicks 1.1 Ticks APIs
 * \ingroup gBasic
 * @{
 */
/*!
 * \brief get the elapsed cycles since perf_counter is initialised
 * \return int64_t the elpased cycles
 */
__attribute__((noinline))
extern int64_t get_system_ticks(void);


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
__attribute__((noinline))
extern int64_t clock(void);
#endif

/*!
 * \brief try to set a start pointer for the performance counter
 */
static inline
void start_cycle_counter(void)
{
    g_lLastTimeStamp = get_system_ticks();
}

/*!
 * \brief calculate the elapsed cycle count since the last start point
 * \note  you can have multiple stop_cycle_counter following one start point
 * \return int32_t the elapsed cycle count
 */
static inline
int64_t stop_cycle_counter(void)
{
    int64_t lTemp = (get_system_ticks() - g_lLastTimeStamp);

    return lTemp - g_nOffset;
}




/*! @} */


/*!
 * \addtogroup gBasicTimerService 1.2 Timer Service
 * \ingroup gBasic
 * @{
 */

/*!
 * \brief get the system timer frequency
 * \return uint32_t the system timer frequency in Hz
 */
extern uint32_t perfc_get_systimer_frequency(void);

/*!
 * \brief get the elapsed milliseconds since perf_counter is initialised
 * \return int64_t the elapsed milliseconds
 */
extern int64_t get_system_ms(void);

/*!
 * \brief get the elapsed microsecond since perf_counter is initialised
 * \return int64_t the elapsed microsecond
 */
extern int64_t get_system_us(void);

/*!
 * \brief delay specified time in microsecond
 * \param[in] wUs time in microsecond
 */
extern void delay_us(uint32_t wUs);

/*!
 * \brief delay specified time in millisecond
 * \param[in] wMs time in millisecond
 */
extern void delay_ms(uint32_t nMs);

/*!
 * \brief convert ticks of a reference timer to millisecond
 *
 * \param[in] lTick the tick count
 * \return int64_t the millisecond
 */
extern
int64_t perfc_convert_ticks_to_ms(int64_t lTick);

/*!
 * \brief convert millisecond into ticks of the reference timer
 *
 * \param[in] wMS the target time in millisecond
 * \return int64_t the ticks
 */
extern
int64_t perfc_convert_ms_to_ticks(uint32_t wMS);

/*!
 * \brief convert ticks of a reference timer to microsecond
 *
 * \param[in] lTick the tick count
 * \return int64_t the microsecond
 */
extern
int64_t perfc_convert_ticks_to_us(int64_t lTick);

/*!
 * \brief convert microsecond into ticks of the reference timer
 *
 * \param[in] wUS the target time in microsecond
 * \return int64_t the ticks
 */
extern
int64_t perfc_convert_us_to_ticks(uint32_t wUS);

/*!
 * \brief set an alarm with given period and check the status
 *
 * \param[in] lPeriod a time period in ticks
 * \param[in] plTimestamp a pointer points to an int64_t integer, if NULL is
 *            passed, an static local variable inside the function will be used
 * \param[in] bAutoReload whether starting next period after a timeout event.
 * \return bool whether it is timeout or not
 */
extern
bool __perfc_is_time_out(int64_t lPeriod, int64_t *plTimestamp, bool bAutoReload);

/*! @} */




/*!
 * \addtogroup gRTOS 2 RTOS Support
 * @{
 */

#if defined(__PERF_CNT_USE_RTOS__)

/*! \brief initialize the default virtual cycle counter for the current task
 */
extern void init_task_cycle_counter(void);

/*! \brief check whether the task stack canary is safe or not
 *  \retval false likely to be a stack-overflow
 *  \retval true task stack is safe
 */
extern
bool perfc_check_task_stack_canary_safe(void);

/*! \brief provide cycle information for target task
 *  \details Support RTOS List:
 *           - RTX5
 *           - RT-Thread
 *           - ThreadX
 *           - FreeRTOS
 *
 * \return task_cycle_info_t* the cycle info object passed to this function
 */
extern task_cycle_info_t * get_rtos_task_cycle_info(void);


/*!
 * \brief intialize a given task_cycle_info_t object and enable it before
 *        registering it.
 * \return task_cycle_info_t* the cycle info object passed to this function
 */
extern task_cycle_info_t *init_task_cycle_info(task_cycle_info_t *ptInfo);

/*! \brief enable a given task_cycle_info_t object
 *
 * \param[in] ptInfo the address of target task_cycle_info_t object
 * \return bool previous status
 */
extern bool enable_task_cycle_info(task_cycle_info_t *ptInfo);

/*! \brief disable a given task_cycle_info_t object
 *
 * \param[in] ptInfo the address of target task_cycle_info_t object
 * \return bool previous status
 */
extern bool disable_task_cycle_info(task_cycle_info_t *ptInfo);

/*! \brief resume the enabled status of a given task_cycle_info_t object
 *
 * \param[in] ptInfo the address of target task_cycle_info_t object
 * \param[in] bEnabledStatus the previous status
 */
extern
void resume_task_cycle_info(task_cycle_info_t *ptInfo, bool bEnabledStatus);

/*!
 * \brief register a global virtual cycle counter agent to the current task
 * \param[in] ptInfo the address of target task_cycle_info_t object
 * \param[in] ptAgent an list node for the task_cycle_info_t object
 * \note the ptAgent it is better to be allocated as a static variable, global
 *       variable or comes from heap or pool
 *
 * \return task_cycle_info_agent_t* the agent passed to this function
 */
extern
task_cycle_info_agent_t *register_task_cycle_agent(
                                            task_cycle_info_t *ptInfo,
                                            task_cycle_info_agent_t *ptAgent);

/*!
 * \brief remove a global virtual cycle counter agent from the current task
 * \param[in] ptAgent the list node currently in use
 * \return task_cycle_info_agent_t* the agent passed to this function
 */
extern
task_cycle_info_agent_t *
unregister_task_cycle_agent(task_cycle_info_agent_t *ptAgent);

/*! \brief reset and start the virtual cycle counter for the current task
 *
 * \param[in] ptInfo the target task_cycle_info_t object
 */
__attribute__((noinline))
extern void __start_task_cycle_counter(task_cycle_info_t *ptInfo);

/*! \brief calculate the elapsed cycle count for current task since the last
 *        start point
 *
 * \note you can call stop_cycle_counter() multiple times following one
 *       start_task_cycle_counter()
 *
 * \param[in] ptInfo the target task_cycle_info_t object
 *
 * \note  When ptInfo is NULL, it returns current task cycle info, when ptInfo
 *        is non-NULL, it returns the total used cycles of the specified
 *        task_cycle_info_t object.
 *
 * \return int64_t the elapsed cycle count.
 */
__attribute__((noinline))
extern int64_t __stop_task_cycle_counter(task_cycle_info_t *ptInfo);


#define start_task_cycle_counter(...)                                           \
            __start_task_cycle_counter((NULL,##__VA_ARGS__))

#define stop_task_cycle_counter(...)                                            \
            __stop_task_cycle_counter((NULL,##__VA_ARGS__))

#elif !defined(__IMPLEMENT_PERF_COUNTER)
#   define start_task_cycle_counter(...)        start_cycle_counter()
#   define stop_task_cycle_counter(...)         stop_cycle_counter()
#   define init_task_cycle_counter()
#   define register_task_cycle_agent(...)
#   define unregister_task_cycle_agent(...)
#   define init_task_cycle_info(...)            (NULL)
#   define enable_task_cycle_info(...)          (false)
#   define disable_task_cycle_info(...)         (false)
#   define resume_task_cycle_info(...)
#   define perfc_check_task_stack_canary_safe() (false)
#endif

/*! @} */

/*!
 * \addtogroup gBasic 1 Basic
 * @{
 */

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
 *  \param[in] bIsSysTickOccupied  A boolean value which indicates whether SysTick
 *           is already used by user application.
 *
 *  \return false Failed to initialize the timer counter, as the timer is not
 *                available or IO error.
 *  \return true initialization is successful.
 */
extern bool init_cycle_counter(bool bIsSysTickOccupied);


/*!
 * \brief a system timer overflow handler
 *
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
extern void perfc_port_insert_to_system_timer_insert_ovf_handler(void);

/*!
 * \brief update perf_counter as SystemCoreClock has been updated.
 */
extern void update_perf_counter(void);

/*!
 * \brief prepare for reconfiguration of SysTick timer.
 *
 * \note some systems (e.g. FreeRTOS) might reconfigure the systick timer to
 *       fulfil the requirement of their feature. To support this, just
 *       before the reconfiguration, please call this function in order 
 *       to make the perf_counter works correctly later. 
 *
 * \note after the reconfiguration, please call update_perf_counter() to apply
 *       the changes to perf_counter.
 *
 * \note this function will stop the SysTick, clear the pending bit and set
 *       the Load register and Current Value register to zero.
 */
extern void before_cycle_counter_reconfiguration(void);

/*! @} */

/*!
 * \addtogroup gBenchmark 3 Benchmark
 * @{
 */

#ifdef __PERF_COUNTER_COREMARK__

/*!
 * \brief entry for coremark
 */
void coremark_main(void);
#endif

/*! @} */


//#if defined(__clang__)
//#   pragma clang diagnostic pop
//#elif defined(__IS_COMPILER_GCC__)
//#   pragma GCC diagnostic pop
//#endif

#ifdef __cplusplus
}
#endif
#endif
