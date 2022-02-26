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


#include <rtthread.h>
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

struct __task_cycle_info_t {
    task_cycle_info_t       tInfo;
    int64_t                 lLastTimeStamp;
    task_cycle_info_agent_t tList;
    uint32_t                wMagicWord;
} ;



#ifndef RT_USING_HOOK
#error In order to use perf_counter:RT-Thread-Patch, please define RT_USING_HOOK\
 in rtconfig.h. If you don't want to use this patch, please un-select it in RTE.
#endif


/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
extern void __on_context_switch_in(uint32_t *pwStack);
extern void __on_context_switch_out(uint32_t *pwStack);
extern struct rt_thread *rt_current_thread;
/*============================ IMPLEMENTATION ================================*/

void __rt_thread_scheduler_hook(struct rt_thread *from, struct rt_thread *to)
{
    if (NULL != from) {
        __on_context_switch_out(from->stack_addr);
    }
    
    __on_context_switch_in(to->stack_addr);
}

#if RTTHREAD_VERSION <= 40100
void __perf_os_patch_init(void)
{
    rt_scheduler_sethook(&__rt_thread_scheduler_hook);
}
#endif

task_cycle_info_t * get_rtos_task_cycle_info(void)
{   
    return &(((struct __task_cycle_info_t *)rt_current_thread->stack_addr)->tInfo);
}
