/****************************************************************************
*  Copyright 2025 Gorgon Meducer (Email:embedded_zhuoran@hotmail.com)       *
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

#ifndef __PERFC_COMMON_H__
#define __PERFC_COMMON_H__

/*============================ INCLUDES ======================================*/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*============================ MACROS ========================================*/
/*!
 * \addtogroup gHelper 4 Helper
 * @{
 */

// for IAR
#if defined(__IAR_SYSTEMS_ICC__)
#   undef __IS_COMPILER_IAR__
#   define __IS_COMPILER_IAR__                  1

// TI Arm Compiler (armcl)
#elif defined(__TI_ARM__)
#   undef __IS_COMPILER_TI_ARM__
#   define __IS_COMPILER_TI_ARM__               1

// TASKING Compiler
#elif defined(__TASKING__)
#   undef __IS_COMPLER_TASKING__
#   define __IS_COMPLER_TASKING__               1

// COSMIC Compiler
#elif defined ( __CSMC__ )
#   undef __IS_COMPILER_COSMIC__
#   define __IS_COMPILER_COSMIC__               1

// for arm compiler 5
#elif ((__ARMCC_VERSION >= 5000000) && (__ARMCC_VERSION < 6000000))
#   undef __IS_COMPILER_ARM_COMPILER_5__
#   define __IS_COMPILER_ARM_COMPILER_5__       1

//for arm compiler 6
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#   undef __IS_COMPILER_ARM_COMPILER_6__
#   define __IS_COMPILER_ARM_COMPILER_6__       1

// TI Arm Clang Compiler (tiarmclang)
#elif defined(__ti__)
#undef __IS_COMPILER_TI_ARM_CLANG__
#   define __IS_COMPILER_TI_ARM_CLANG__         1
#else

// for other clang
#   if defined(__clang__) &&                                                    \
    !__IS_COMPILER_ARM_COMPILER_6__ &&                                          \
    !__IS_COMPILER_TI_ARM_CLANG__
#       undef  __IS_COMPILER_LLVM__
#       define __IS_COMPILER_LLVM__                 1

// for gcc
#   elif defined(__GNUC__) && !(  defined(__IS_COMPILER_ARM_COMPILER__)         \
                            ||  defined(__IS_COMPILER_LLVM__)                   \
                            ||  defined(__IS_COMPILER_IAR__))
#       undef __IS_COMPILER_GCC__
#       define __IS_COMPILER_GCC__              1
#   endif

#endif

#undef __IS_COMPILER_ARM_COMPILER__
#if defined(__IS_COMPILER_ARM_COMPILER_5__) && __IS_COMPILER_ARM_COMPILER_5__   \
||  defined(__IS_COMPILER_ARM_COMPILER_6__) && __IS_COMPILER_ARM_COMPILER_6__
#   define __IS_COMPILER_ARM_COMPILER__         1
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

#undef __COMPILER_HAS_GNU_EXTENSIONS__
#if __PLOOC_VA_NUM_ARGS() == 0
#   define __COMPILER_HAS_GNU_EXTENSIONS__      1
#endif

#undef __IS_COMPILER_SUPPORT_C99__
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#   define __IS_COMPILER_SUPPORT_C99__          1
#endif

#undef __IS_COMPILER_SUPPORT_C11__
#if defined(__STDC_VERSION__) && __STDC_VERSION__ > 199901L
#   define __IS_COMPILER_SUPPORT_C11__          1
#endif


#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wtypedef-redefinition"
#   pragma clang diagnostic ignored "-Wmissing-declarations"
#   pragma clang diagnostic ignored "-Wempty-body"
#   pragma clang diagnostic ignored "-Wmicrosoft-anon-tag"
#   pragma clang diagnostic ignored "-Wmissing-field-initializers"
#   pragma clang diagnostic ignored "-Wmissing-declarations"
#   pragma clang diagnostic ignored "-Wmissing-braces"
#elif __IS_COMPILER_ARM_COMPILER_5__
/*! arm compiler 5 */
#   pragma push
#   pragma diag_suppress 1,64,174,177,188,68,513,144,2525
#elif __IS_COMPILER_IAR__
/*! IAR */
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wmissing-declarations"
#   pragma GCC diagnostic ignored "-Wempty-body"
#   pragma GCC diagnostic ignored "-Wpragmas"
#   pragma GCC diagnostic ignored "-Wformat="
#   pragma GCC diagnostic ignored "-Wmissing-braces"
#   pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/

/*----------------------------------------------------------------------------*
 * OOC                                                                        *
 *----------------------------------------------------------------------------*/
/*  minimal support for OOPC */
#undef __implement_ex
#undef __implement
#undef implement
#undef implement_ex
#undef inherit
#undef inherit_ex

/*!
 * \note do NOT use this macro directly
 */
#ifdef   __cplusplus
#   define __implement_ex(__type, __name)   __type  __name
#else
#   define __implement_ex(__type, __name)                                       \
            union {                                                             \
                __type  __name;                                                 \
                __type;                                                         \
            }
#endif
/*!
 * \note do NOT use this macro
 */
#define __inherit_ex(__type, __name)   __type  __name


/*!
 * \note do NOT use this macro directly
 */
#define __implement(__type)             __implement_ex( __type,                 \
                                                        use_as__##__type)


/*!
 * \note do NOT use this macro directly
 */
#define __inherit(__type)               __inherit_ex(__type,use_as__##__type)


/*!
 * \brief inherit a given class
 * \param __type the base class, you can use .use_as_xxxxx for referencing 
 *               the base.
 * \note this macro supports microsoft extensions (-fms-extensions)
 */
#define implement(__type)               __implement(__type)

/*!
 * \brief inherit a given class and give it an alias name
 * \param __type the base class
 * \param __name an alias name for referencing the base class
 * \note this macro supports microsoft extensions (-fms-extensions)
 */
#define implement_ex(__type, __name)    __implement_ex(__type, __name)


/*!
 * \brief inherit a given class
 * \param __type the base class, you can use .use_as_xxxxx for referencing 
 *               the base.
 * \note this macro does NOT support microsoft extensions (-fms-extensions)
 */
#define inherit(__type)                 __inherit(__type)

/*!
 * \brief inherit a given class and give it an alias name
 * \param __type the base class
 * \param __name an alias name for referencing the base class
 * \note this macro does NOT support microsoft extensions (-fms-extensions)
 */
#define inherit_ex(__type, __name)      __inherit_ex(__type, __name)

/*----------------------------------------------------------------------------*
 * Helpers                                                                    *
 *----------------------------------------------------------------------------*/
#undef _

#undef __PERFC_CONNECT2
#undef __PERFC_CONNECT3
#undef __PERFC_CONNECT4
#undef __PERFC_CONNECT5
#undef __PERFC_CONNECT6
#undef __PERFC_CONNECT7
#undef __PERFC_CONNECT8
#undef __PERFC_CONNECT9

#undef PERFC_CONNECT2
#undef PERFC_CONNECT3
#undef PERFC_CONNECT4
#undef PERFC_CONNECT5
#undef PERFC_CONNECT6
#undef PERFC_CONNECT7
#undef PERFC_CONNECT8
#undef PERFC_CONNECT9
#undef ALT_PERFC_CONNECT2

#undef SAFE_NAME
#undef PERFC_SAFE_NAME

#undef PERFC_CONNECT

#undef __MACRO_EXPANDING
#define __MACRO_EXPANDING(...)                      __VA_ARGS__

#define __PERFC_CONNECT2(__A, __B)                        __A##__B
#define __PERFC_CONNECT3(__A, __B, __C)                   __A##__B##__C
#define __PERFC_CONNECT4(__A, __B, __C, __D)              __A##__B##__C##__D
#define __PERFC_CONNECT5(__A, __B, __C, __D, __E)                               \
                                    __A##__B##__C##__D##__E
#define __PERFC_CONNECT6(__A, __B, __C, __D, __E, __F)                          \
                                    __A##__B##__C##__D##__E##__F
#define __PERFC_CONNECT7(__A, __B, __C, __D, __E, __F, __G)                     \
                                    __A##__B##__C##__D##__E##__F##__G
#define __PERFC_CONNECT8(__A, __B, __C, __D, __E, __F, __G, __H)                \
                                    __A##__B##__C##__D##__E##__F##__G##__H
#define __PERFC_CONNECT9(__A, __B, __C, __D, __E, __F, __G, __H, __I)           \
                                    __A##__B##__C##__D##__E##__F##__G##__H##__I


#define ALT_PERFC_CONNECT2(__A, __B)        __PERFC_CONNECT2(__A, __B)
#define PERFC_CONNECT2(__A, __B)            __PERFC_CONNECT2(__A, __B)
#define PERFC_CONNECT3(__A, __B, __C)       __PERFC_CONNECT3(__A, __B, __C)
#define PERFC_CONNECT4(__A, __B, __C, __D)                                      \
                __PERFC_CONNECT4(__A, __B, __C, __D)
#define PERFC_CONNECT5(__A, __B, __C, __D, __E)                                 \
                __PERFC_CONNECT5(__A, __B, __C, __D, __E)
#define PERFC_CONNECT6(__A, __B, __C, __D, __E, __F)                            \
                __PERFC_CONNECT6(__A, __B, __C, __D, __E, __F)
#define PERFC_CONNECT7(__A, __B, __C, __D, __E, __F, __G)                       \
                __PERFC_CONNECT7(__A, __B, __C, __D, __E, __F, __G)
#define PERFC_CONNECT8(__A, __B, __C, __D, __E, __F, __G, __H)                  \
                __PERFC_CONNECT8(__A, __B, __C, __D, __E, __F, __G, __H)
#define PERFC_CONNECT9(__A, __B, __C, __D, __E, __F, __G, __H, __I)             \
                __PERFC_CONNECT9(__A, __B, __C, __D, __E, __F, __G, __H, __I)

#define PERFC_CONNECT(...)                                                      \
            ALT_PERFC_CONNECT2( PERFC_CONNECT,                                  \
                                __PLOOC_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)



#define SAFE_NAME(__NAME)           PERFC_CONNECT3(__,__NAME,__LINE__)
#define PERFC_SAFE_NAME(__name)     PERFC_CONNECT3(__,__name,__LINE__)


#undef __perfc_using1
#undef __perfc_using2
#undef __perfc_using3
#undef __perfc_using4
#undef perfc_using

#define __perfc_using1(__declare)                                               \
            for (__declare,                                                     \
                *PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr) = NULL;          \
                 PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr)++ == NULL;       \
                )

#define __perfc_using2(__declare, __on_leave_expr)                              \
            for (__declare,                                                     \
                *PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr) = NULL;          \
                 PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr)++ == NULL;       \
                 (__on_leave_expr)                                              \
                )

#define __perfc_using3(__declare, __on_enter_expr, __on_leave_expr)             \
            for (__declare,                                                     \
                *PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr) = NULL;          \
                 PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr)++ == NULL ?      \
                    ((__on_enter_expr),1) : 0;                                  \
                 (__on_leave_expr)                                              \
                )

#define __perfc_using4(__dcl1, __dcl2, __on_enter_expr, __on_leave_expr)        \
            for (__dcl1, __dcl2,                                                \
                *PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr) = NULL;          \
                 PERFC_CONNECT3(__perfc_using_, __LINE__,_ptr)++ == NULL ?      \
                    ((__on_enter_expr),1) : 0;                                  \
                 (__on_leave_expr)                                              \
                )

#define perfc_using(...)                                                        \
                PERFC_CONNECT2( __perfc_using,                                  \
                                __PLOOC_VA_NUM_ARGS(__VA_ARGS__))               \
                                    (__VA_ARGS__)

#undef __perfc_with2
#undef __perfc_perfc_with3
#undef perfc_with

#define __perfc_with1(__addr)                                                   \
            perfc_using(__typeof__(*__addr) *_=(__addr))

#define __perfc_with2(__type, __addr)                                           \
            perfc_using(__type *_=(__addr))
#define __perfc_with3(__type, __addr, __item)                                   \
            perfc_using(__type *_=(__addr), *__item = _, _=_,_=_ )

#define perfc_with(...)                                                         \
            PERFC_CONNECT2( __perfc_with,                                       \
                            __PLOOC_VA_NUM_ARGS(__VA_ARGS__))                   \
                                (__VA_ARGS__)

#undef perfc_foreach2
#undef perfc_foreach3
#undef perfc_foreach

#define perfc_foreach1(__array)                                                 \
            perfc_using(__typeof__(__array[0]) *_ = __array)                    \
            for (   uint_fast32_t PERFC_SAFE_NAME(count) = dimof(__array);      \
                    PERFC_SAFE_NAME(count) > 0;                                 \
                    _++, PERFC_SAFE_NAME(count)--                               \
                )

#define perfc_foreach2(__type, __array)                                         \
            perfc_using(__type *_ = __array)                                    \
            for (   uint_fast32_t PERFC_SAFE_NAME(count) = dimof(__array);      \
                    PERFC_SAFE_NAME(count) > 0;                                 \
                    _++, PERFC_SAFE_NAME(count)--                               \
                )

#define perfc_foreach3(__type, __array, __item)                                 \
            perfc_using(__type *_ = __array, *__item = _, _ = _, _ = _ )        \
            for (   uint_fast32_t PERFC_SAFE_NAME(count) = dimof(__array);      \
                    PERFC_SAFE_NAME(count) > 0;                                 \
                    _++, __item = _, PERFC_SAFE_NAME(count)--                   \
                )

#define perfc_foreach(...)                                                      \
            PERFC_CONNECT2( perfc_foreach,                                      \
                            __PLOOC_VA_NUM_ARGS(__VA_ARGS__))                   \
                                (__VA_ARGS__)

#ifndef __perf_counter_printf__
#   define __perf_counter_printf__      printf
#endif

#ifndef __PERFC_STACK_WATERMARK_U32__
#   define __PERFC_STACK_WATERMARK_U32__            0xDEADBEEF
#endif

#undef __PERFC_STACK_WATERMARK_U64__
#define __PERFC_STACK_WATERMARK_U64__                                           \
            ((uint64_t) (   __PERFC_STACK_WATERMARK_U32__                       \
                        |   ((uint64_t)__PERFC_STACK_WATERMARK_U32__ << 32)     \
                        ))

#undef __stack_usage__
#undef __stack_usage_max__
#ifdef __PERFC_STACK_GROWS_UPWARD__
/*!
 * \brief measure the stack usage of the given code segement
 * \param[in] __STR a name for this measurement
 * \param[in] __perfc_stack_limit the stack limit address (the last availble 
 *                                byte address of the stack)
 * \param[in] ... an optional code segement, in which we can read the measured
 *                result from __stack_used__.
 */
#define __stack_usage__(__STR, __perfc_stack_limit, ...)                        \
                                                                                \
        perfc_using(uintptr_t __stack_used__ = (uintptr_t)-1,                   \
            PERFC_SAFE_NAME(nSP) = __perfc_port_get_sp(),                       \
            {perfc_stack_fill(  PERFC_SAFE_NAME(nSP),                           \
                                (uintptr_t)(__perfc_stack_limit));},            \
            {                                                                   \
                PERFC_SAFE_NAME(nSP) = (PERFC_SAFE_NAME(nSP) + 7)               \
                                     & (~((uintptr_t)0x07));                    \
                uintptr_t PERFC_SAFE_NAME(nStackLimit)                          \
                    = (uintptr_t)(__perfc_stack_limit);                         \
                PERFC_SAFE_NAME(nStackLimit) &= (~((uintptr_t)0x07));           \
                if (PERFC_SAFE_NAME(nSP) >= PERFC_SAFE_NAME(nStackLimit)) {     \
                    if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                \
                        __perf_counter_printf__(                                \
                            "\r\n-------------------------------------\r\n"     \
                            "%s Stack Overflow!!!"                              \
                            " SP: [0x%08" PRIxPTR "]"                           \
                            " Stack Limit: [0x%08" PRIxPTR "]\r\n",             \
                            (const char *)(__STR),                              \
                            PERFC_SAFE_NAME(nSP),                               \
                            PERFC_SAFE_NAME(nStackLimit));                      \
                    } else {                                                    \
                        __VA_ARGS__;                                            \
                    }                                                           \
                } else {                                                        \
                    __stack_used__                                              \
                        = PERFC_SAFE_NAME(nStackLimit)                          \
                        - PERFC_SAFE_NAME(nSP)                                  \
                        - perfc_stack_remain(PERFC_SAFE_NAME(nStackLimit));     \
                    if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                \
                        __perf_counter_printf__(                                \
                            "\r\n-------------------------------------\r\n"     \
                            "%s Stack Used: %" PRIuPTR " bytes\r\n",            \
                            (const char *)(__STR),                              \
                            __stack_used__);                                    \
                    } else {                                                    \
                        __VA_ARGS__;                                            \
                    }                                                           \
                }                                                               \
            })

/*!
 * \brief measure the maximum stack usage (so far) for the given code segement
 * \param[in] __STR a name for this measurement
 * \param[in] __perfc_stack_limit the stack limit address (the last availble 
 *                                byte address of the stack)
 * \param[in] ... an optional code segement, in which we can read the measured
 *                result from __stack_used_max__.
 */
#define __stack_usage_max__(__STR, __perfc_stack_limit, ...)                    \
    perfc_using(uintptr_t PERFC_SAFE_NAME(__stack_used__) = (uintptr_t)-1,      \
        PERFC_SAFE_NAME(nSP) = __perfc_port_get_sp(),                           \
        {perfc_stack_fill(  PERFC_SAFE_NAME(nSP),                               \
                            (uintptr_t)(__perfc_stack_limit));},                \
        {                                                                       \
            static size_t PERFC_SAFE_NAME(s_nStackUsedMax) = 0;                 \
                                                                                \
            PERFC_SAFE_NAME(nSP) = (PERFC_SAFE_NAME(nSP) + 7)                   \
                                     & (~((uintptr_t)0x07));                    \
            uintptr_t PERFC_SAFE_NAME(nStackLimit)                              \
                = (uintptr_t)(__perfc_stack_limit);                             \
            PERFC_SAFE_NAME(nStackLimit) &= (~((uintptr_t)0x07));               \
                                                                                \
            if (PERFC_SAFE_NAME(nSP) >= PERFC_SAFE_NAME(nStackLimit)) {         \
                PERFC_SAFE_NAME(s_nStackUsedMax) = (size_t)(-1);                \
                if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                    \
                    __perf_counter_printf__(                                    \
                            "\r\n-------------------------------------\r\n"     \
                            "%s Stack Overflow!!!"                              \
                            " SP: [0x%08" PRIxPTR "]"                           \
                            " Stack Limit: [0x%08" PRIxPTR "]\r\n",             \
                            (const char *)(__STR),                              \
                            PERFC_SAFE_NAME(nSP),                               \
                            PERFC_SAFE_NAME(nStackLimit));                      \
                }                                                               \
            } else if (PERFC_SAFE_NAME(s_nStackUsedMax) >= 0) {                 \
                PERFC_SAFE_NAME(__stack_used__)                                 \
                        = PERFC_SAFE_NAME(nStackLimit)                          \
                        - PERFC_SAFE_NAME(nSP)                                  \
                        - perfc_stack_remain(PERFC_SAFE_NAME(nStackLimit));     \
                if (    PERFC_SAFE_NAME(s_nStackUsedMax)                        \
                   <    PERFC_SAFE_NAME(__stack_used__)) {                      \
                    PERFC_SAFE_NAME(s_nStackUsedMax)                            \
                        = PERFC_SAFE_NAME(__stack_used__);                      \
                                                                                \
                    if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                \
                        __perf_counter_printf__(                                \
                            "\r\n-------------------------------------\r\n"     \
                            "%s Stack Used: %" PRIuPTR " bytes\r\n",            \
                            (const char *)(__STR),                              \
                            PERFC_SAFE_NAME(__stack_used__));                   \
                    }                                                           \
                }                                                               \
            }                                                                   \
            if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) != 0) {                        \
                size_t __stack_used_max__                                       \
                    = PERFC_SAFE_NAME(s_nStackUsedMax);                         \
                UNUSED_PARAM(__stack_used_max__);                               \
                __VA_ARGS__;                                                    \
            }                                                                   \
        })

#else
/*!
 * \brief measure the stack usage of the given code segement
 * \param[in] __STR a name for this measurement
 * \param[in] __perfc_stack_limit the stack based address (stack limit)
 * \param[in] ... an optional code segement, in which we can read the measured
 *                result from __stack_used__.
 */
#define __stack_usage__(__STR, __perfc_stack_base, ...)                         \
                                                                                \
        perfc_using(uintptr_t __stack_used__ = (uintptr_t)-1,                   \
            PERFC_SAFE_NAME(nSP) = __perfc_port_get_sp(),                       \
            {perfc_stack_fill(  PERFC_SAFE_NAME(nSP),                           \
                                (uintptr_t)(__perfc_stack_base));},             \
            {                                                                   \
                PERFC_SAFE_NAME(nSP) &= (~((uintptr_t)0x07));                   \
                uintptr_t PERFC_SAFE_NAME(nStackLimit)                          \
                    = (uintptr_t)(__perfc_stack_base);                          \
                PERFC_SAFE_NAME(nStackLimit)                                    \
                    = (PERFC_SAFE_NAME(nStackLimit) + 7)                        \
                    & (~((uintptr_t)0x07));                                     \
                if (PERFC_SAFE_NAME(nSP) <= PERFC_SAFE_NAME(nStackLimit)) {     \
                    if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                \
                        __perf_counter_printf__(                                \
                            "\r\n-------------------------------------\r\n"     \
                            __STR " Stack Overflow!!!"                          \
                            " SP: [0x%08" PRIxPTR "]"                           \
                            " Stack Base: [0x%08" PRIxPTR "]\r\n",              \
                            PERFC_SAFE_NAME(nSP),                               \
                            PERFC_SAFE_NAME(nStackLimit));                      \
                    } else {                                                    \
                        __VA_ARGS__;                                            \
                    }                                                           \
                } else {                                                        \
                    __stack_used__                                              \
                        = PERFC_SAFE_NAME(nSP)                                  \
                        - PERFC_SAFE_NAME(nStackLimit)                          \
                        - perfc_stack_remain(PERFC_SAFE_NAME(nStackLimit));     \
                    if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                \
                        __perf_counter_printf__(                                \
                            "\r\n-------------------------------------\r\n"     \
                            __STR " Stack Used: %" PRIuPTR " bytes\r\n",        \
                            __stack_used__);                                    \
                    } else {                                                    \
                        __VA_ARGS__;                                            \
                    }                                                           \
                }                                                               \
            })

/*!
 * \brief measure the maximum stack usage (so far) for the given code segement
 * \param[in] __STR a name for this measurement
 * \param[in] __perfc_stack_limit the stack based address (stack limit)
 * \param[in] ... an optional code segement, in which we can read the measured
 *                result from __stack_used_max__.
 */
#define __stack_usage_max__(__STR, __perfc_stack_base, ...)                     \
    perfc_using(uintptr_t PERFC_SAFE_NAME(__stack_used__) = (uintptr_t)-1,      \
        PERFC_SAFE_NAME(nSP) = __perfc_port_get_sp(),                           \
        {perfc_stack_fill(  PERFC_SAFE_NAME(nSP),                               \
                            (uintptr_t)(__perfc_stack_base));},                 \
        {                                                                       \
            static size_t PERFC_SAFE_NAME(s_nStackUsedMax) = 0;                 \
                                                                                \
            PERFC_SAFE_NAME(nSP) &= (~((uintptr_t)0x07));                       \
            uintptr_t PERFC_SAFE_NAME(nStackLimit)                              \
                = (uintptr_t)(__perfc_stack_base);                              \
            PERFC_SAFE_NAME(nStackLimit)                                        \
                = (PERFC_SAFE_NAME(nStackLimit) + 7)                            \
                & (~((uintptr_t)0x07));                                         \
                                                                                \
            if (PERFC_SAFE_NAME(nSP) <= PERFC_SAFE_NAME(nStackLimit)) {         \
                PERFC_SAFE_NAME(s_nStackUsedMax) = (size_t)(-1);                \
                if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                    \
                    __perf_counter_printf__(                                    \
                        "\r\n-------------------------------------\r\n"         \
                        __STR " Stack Overflow!!!"                              \
                        " SP: [0x%08" PRIxPTR "]"                               \
                        " Stack Base: [0x%08" PRIxPTR "]\r\n",                  \
                        PERFC_SAFE_NAME(nSP),                                   \
                        PERFC_SAFE_NAME(nStackLimit));                          \
                }                                                               \
            } else if (PERFC_SAFE_NAME(s_nStackUsedMax) >= 0) {                 \
                PERFC_SAFE_NAME(__stack_used__)                                 \
                    = PERFC_SAFE_NAME(nSP)                                      \
                    - PERFC_SAFE_NAME(nStackLimit)                              \
                    - perfc_stack_remain(PERFC_SAFE_NAME(nStackLimit));         \
                if (    PERFC_SAFE_NAME(s_nStackUsedMax)                        \
                   <    PERFC_SAFE_NAME(__stack_used__)) {                      \
                    PERFC_SAFE_NAME(s_nStackUsedMax)                            \
                        = PERFC_SAFE_NAME(__stack_used__);                      \
                                                                                \
                    if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) == 0) {                \
                        __perf_counter_printf__(                                \
                            "\r\n-------------------------------------\r\n"     \
                            __STR                                               \
                            " Stack Used Max: %" PRIuPTR " bytes\r\n",          \
                            PERFC_SAFE_NAME(__stack_used__));                   \
                    }                                                           \
                }                                                               \
            }                                                                   \
            if (__PLOOC_VA_NUM_ARGS(__VA_ARGS__) != 0) {                        \
                size_t __stack_used_max__                                       \
                    = PERFC_SAFE_NAME(s_nStackUsedMax);                         \
                UNUSED_PARAM(__stack_used_max__);                               \
                __VA_ARGS__;                                                    \
            }                                                                   \
        })
#endif


/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

extern
__attribute__((noinline))
uintptr_t __perfc_port_get_sp(void);

extern
__attribute__((noinline))
void __perfc_port_set_sp(uintptr_t nSP);

extern
__attribute__((noinline))
bool perfc_stack_fill(uintptr_t nSP, uintptr_t nStackLimit);

extern
__attribute__((noinline))
size_t perfc_stack_remain(uintptr_t nStackLimit);

/*============================ IMPLEMENTATION ================================*/

/*! @} */


#ifdef __cplusplus
}
#endif

#endif
