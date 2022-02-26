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


#include "rtx_os.h"
#include "perf_counter.h"
#include "cmsis_compiler.h"
#include "rtx_evr.h"                    // RTX Event Recorder definitions

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


/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
extern void __on_context_switch_in(uint32_t *pwStack);
extern void __on_context_switch_out(uint32_t *pwStack);

/*============================ IMPLEMENTATION ================================*/


/*! \brief wrapper function for rtos context switching */
void __on_context_switch (osRtxThread_t *thread)
{
    if (NULL != osRtxInfo.thread.run.curr) {
        __on_context_switch_out(osRtxInfo.thread.run.curr->stack_mem);
    }
    
    __on_context_switch_in(thread->stack_mem);
}

__attribute__((used))
void EvrRtxThreadSwitched (osThreadId_t thread_id) 
{
    __on_context_switch((osRtxThread_t *)thread_id);
    
#if defined(RTE_Compiler_EventRecorder)
#   define EvtRtxThreadSwitched     \
        EventID(EventLevelOp,     EvtRtxThreadNo, 0x19U)    
    
    (void)EventRecord2(EvtRtxThreadSwitched, (uint32_t)thread_id, 0U);
#else
    (void)thread_id;
#endif
}


task_cycle_info_t * get_rtos_task_cycle_info(void)
{   
    osRtxThread_t *curr = osRtxInfo.thread.run.curr;
    if (NULL == curr) {
        return NULL;
    }
    
    return &(((struct __task_cycle_info_t *)curr->stack_mem)->tInfo);
}

