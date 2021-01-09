/****************************************************************************
*  Copyright 2021 Gorgon Meducer (Email:embedded_zhuoran@hotmail.com)       *
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

/*============================ MACROS ========================================*/

#define __PLOOC_VA_NUM_ARGS_IMPL(   _0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,  \
                                    _13,_14,_15,_16,__N,...)      __N
#define __PLOOC_VA_NUM_ARGS(...)                                                \
            __PLOOC_VA_NUM_ARGS_IMPL( 0,##__VA_ARGS__,16,15,14,13,12,11,10,9,   \
                                      8,7,6,5,4,3,2,1,0)
            
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
            CONNECT2(CONNECT, __PLOOC_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)
            
            

#define __using1(__declare)                                                     \
            for (__declare, *CONNECT3(__using_, __LINE__,_ptr) = NULL;          \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL;                   \
                )

#define __using2(__declare, __on_leave_expr)                                    \
            for (__declare, *CONNECT3(__using_, __LINE__,_ptr) = NULL;          \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL;                   \
                 __on_leave_expr                                                \
                )

#define __using3(__declare, __on_enter_expr, __on_leave_expr)                   \
            for (__declare, *CONNECT3(__using_, __LINE__,_ptr) = NULL;          \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL ?                  \
                    ((__on_enter_expr),1) : 0;                                  \
                 __on_leave_expr                                                \
                )
                
#define __using4(__dcl1, __dcl2, __on_enter_expr, __on_leave_expr)              \
            for (__dcl1, __dcl2, *CONNECT3(__using_, __LINE__,_ptr) = NULL;     \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL ?                  \
                    ((__on_enter_expr),1) : 0;                                  \
                 __on_leave_expr                                                \
                )
               
#define using(...)                                                              \
            CONNECT2(__using, __PLOOC_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)


#define safe_atom_code()                                                        \
            using(  uint32_t CONNECT2(temp,__LINE__) = __disable_irq(),         \
                    __set_PRIMASK(CONNECT2(temp,__LINE__)))

#define __with2(__type, __addr)                                                 \
            using(__type *_p=(__addr))
#define __with3(__type, __addr, __item)                                         \
            using(__type *_p=(__addr), *__item = _p, _p=_p, )

#define with(...)                                                               \
            CONNECT2(__with, __PLOOC_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

#undef _
#define _       (*_p)

#ifndef dimof
#   define dimof(__array)          (sizeof(__array)/sizeof(__array[0]))
#endif

#define foreach2(__type, __array)                                               \
            using(__type *_p = __array)                                         \
            for (   uint_fast32_t CONNECT2(count,__LINE__) = dimof(__array);    \
                    CONNECT2(count,__LINE__) > 0;                               \
                    _p++, CONNECT2(count,__LINE__)--                            \
                )

#define foreach3(__type, __array, __item)                                       \
            using(__type *_p = __array, *__item = _p, _p = _p, )                \
            for (   uint_fast32_t CONNECT2(count,__LINE__) = dimof(__array);    \
                    CONNECT2(count,__LINE__) > 0;                               \
                    _p++, __item = _p, CONNECT2(count,__LINE__)--               \
                )

#define foreach(...)                                                            \
            CONNECT2(foreach, __PLOOC_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

#ifndef safe_atom_code
#   define safe_atom_code()                                                     \
            using(  uint32_t CONNECT2(temp,__LINE__) = __disable_irq(),         \
                    __set_PRIMASK(CONNECT2(temp,__LINE__)))
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/

            
#define __cycleof__(__STR)                                                      \
            for (int32_t nCycles = 0,                                           \
                    CONNECT2(__cycle_count_s_, __LINE__) = 1;                   \
                 CONNECT2(__cycle_count_s_, __LINE__)-- ?                       \
                    (start_cycle_counter(),1) :                                 \
                    (                                                           \
                    printf( "\r\n-[Cycle Report]"                               \
                        "--------------------------------------------\r\n"      \
                        __STR                                                   \
                        " total cycle count: %d [%08x]\r\n", nCycles, nCycles)  \
                    ,0);                                                        \
                    nCycles = stop_cycle_counter()                              \
                 )
                    
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

/* Function: initialise cycle counter service
 *           and don't forget to tell the function whether the systick is already
 *           used by user applications. 
 *           Don't worry, this cycle counter service won't affect your existing
 *           systick service.
 */
extern void init_cycle_counter(bool bSysTickIsOccupied);

/* Function : start_time
	This function will be called right before starting the timed portion of the benchmark.
	Implementation may be capturing a system timer (as implemented in the example code) 
	or zeroing some system parameters - e.g. setting the cpu clocks cycles to 0.
*/
extern void start_cycle_counter(void);

/* Function : stop_time
	This function will be called right after ending the timed portion of the benchmark.
	Implementation may be capturing a system timer (as implemented in the example code) 
	or other system parameters - e.g. reading the current value of cpu cycles counter.
*/
extern int32_t stop_cycle_counter(void);

/* Function : delay specified us with the help from systick
 */
extern void delay_us(int32_t iUs);

#endif
