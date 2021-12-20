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


/*============================ INCLUDES ======================================*/


#include "rtx_os.h"
#include "perf_counter.h"

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
    uint64_t            dwLastTimeStamp;
    task_cycle_info_t   tInfo;
} ;

/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/


__attribute__((used))
/*! \brief wrapper function for rtos context switching */
void WRAP_FUNC(osRtxThreadSwitch) (osRtxThread_t *thread)
{
    extern void ORIG_FUNC(osRtxThreadSwitch) (osRtxThread_t *thread);
    //assert(NULL != ptThread);

    do {
        struct __task_cycle_info_t *ptFrame = NULL;
        uint64_t dwTimeStamp;
        osRtxThread_t *curr = osRtxInfo.thread.run.curr;
        if (curr == thread) {
            break;
        }
        
        //! get current system ticks
        dwTimeStamp = get_system_ticks();
        
        if (NULL != curr) {
            ptFrame = (struct __task_cycle_info_t *)curr->stack_mem;
        
            ptFrame->tInfo.dwUsedRecent = dwTimeStamp - ptFrame->dwLastTimeStamp;
            ptFrame->tInfo.dwUsedTotal += ptFrame->tInfo.dwUsedRecent;
        }
        
        //! inital target thread
        
        ptFrame = (struct __task_cycle_info_t *)thread->stack_mem;
        
        if (0 == ptFrame->tInfo.dwStart) {
            ptFrame->tInfo.dwStart = dwTimeStamp;
        }
        ptFrame->dwLastTimeStamp = dwTimeStamp;
        ptFrame->tInfo.wActiveCount++;
    } while(0);
    
    ORIG_FUNC(osRtxThreadSwitch)(thread);
}


task_cycle_info_t * get_rtos_thread_cycle_info(void)
{   
    osRtxThread_t *curr = osRtxInfo.thread.run.curr;
    if (NULL == curr) {
        return NULL;
    }
    
    return &(((struct __task_cycle_info_t *)curr->stack_mem)->tInfo);
}
