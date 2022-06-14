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

#include "tx_api.h"
#include "tx_thread.h"

#include "perf_counter.h"
#include "cmsis_compiler.h"

/*============================ MACROS ========================================*/

#undef __WRAP_FUNC
#undef WRAP_FUNC
#if defined(__IS_COMPILER_ARM_COMPILER__) && __IS_COMPILER_ARM_COMPILER__

#   define __WRAP_FUNC(__NAME)     $Sub$$##__NAME
#   define __ORIG_FUNC(__NAME)     $Super$$##__NAME

#elif (defined(__IS_COMPILER_LLVM__) && __IS_COMPILER_LLVM__) \
  ||  (defined(__IS_COMPILER_GCC__) && __IS_COMPILER_GCC__)

#   define __WRAP_FUNC(__NAME)     __wrap_##__NAME
#   define __ORIG_FUNC(__NAME)     __real_##__NAME

#endif
#define WRAP_FUNC(__NAME)       __WRAP_FUNC(__NAME)
#define ORIG_FUNC(__NAME)       __ORIG_FUNC(__NAME)


#ifndef TX_ENABLE_EXECUTION_CHANGE_NOTIFY
#error In order to use perf_counter:ThreadX-Patch, please define\
 TX_ENABLE_EXECUTION_CHANGE_NOTIFY in the project configuration.\
 If you don't want to use this patch, please un-select it in RTE\
 or remove this patch from the compilation.
#endif


/*============================ TYPES =========================================*/
struct __task_cycle_info_t {
    task_cycle_info_t       tInfo;
    int64_t                 lLastTimeStamp;
    task_cycle_info_agent_t tList;
    uint32_t                wMagicWord;
} ;


/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
extern void __on_context_switch_in(uint32_t *pwStack);
extern void __on_context_switch_out(uint32_t *pwStack);

/*============================ IMPLEMENTATION ================================*/

#if defined(TX_EXECUTION_PROFILE_ENABLE)
void WRAP_FUNC(_tx_execution_thread_enter)(void)
#else
void _tx_execution_thread_enter (void)
#endif
{
    TX_THREAD * ptThread = NULL;
    TX_THREAD_GET_CURRENT(ptThread);

    __on_context_switch_in(ptThread->tx_thread_stack_start);

#if defined(TX_EXECUTION_PROFILE_ENABLE)
    extern void ORIG_FUNC(_tx_execution_thread_enter)(void);

    ORIG_FUNC(_tx_execution_thread_enter)();
#endif
}

#if defined(TX_EXECUTION_PROFILE_ENABLE)
void WRAP_FUNC(_tx_execution_thread_exit)(void)
#else
void _tx_execution_thread_exit(void)
#endif
{
    TX_THREAD * ptThread = NULL;
    TX_THREAD_GET_CURRENT(ptThread);

    if (NULL != ptThread) {
        __on_context_switch_out(ptThread->tx_thread_stack_start);
    }
#if defined(TX_EXECUTION_PROFILE_ENABLE)
    extern void ORIG_FUNC(_tx_execution_thread_exit)(void);

    ORIG_FUNC(_tx_execution_thread_exit)();
#endif
}

#if !defined(TX_EXECUTION_PROFILE_ENABLE)
void _tx_execution_isr_exit(void)
{

}

void _tx_execution_isr_enter(void)
{

}
#endif

task_cycle_info_t * get_rtos_task_cycle_info(void)
{
    TX_THREAD * ptThread = NULL;
    TX_THREAD_GET_CURRENT(ptThread);

    return &(((struct __task_cycle_info_t *)ptThread->tx_thread_stack_start)->tInfo);
}
