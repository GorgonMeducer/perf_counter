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


/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
all the API functions to use the MPU wrappers.  That should only be done when
task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "stack_macros.h"

/* Lint e9021, e961 and e750 are suppressed as a MISRA exception justified
because the MPU ports require MPU_WRAPPERS_INCLUDED_FROM_API_FILE to be defined
for the header files above, but not in this file, in order to generate the
correct privileged Vs unprivileged linkage and placement. */
#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE /*lint !e961 !e750 !e9021. */

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



/*============================ TYPES =========================================*/

/*
 * Task control block.  A task control block (TCB) is allocated for each task,
 * and stores task state information, including a pointer to the task's context
 * (the task's run time environment, including register values)
 */
typedef struct tskTaskControlBlock          /* The old naming convention is used to prevent breaking kernel aware debuggers. */
{
    volatile StackType_t    *pxTopOfStack;  /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

    #if ( portUSING_MPU_WRAPPERS == 1 )
        xMPU_SETTINGS   xMPUSettings;       /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
    #endif

    ListItem_t          xStateListItem; /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
    ListItem_t          xEventListItem;     /*< Used to reference a task from an event list. */
    UBaseType_t         uxPriority;         /*< The priority of the task.  0 is the lowest priority. */
    StackType_t         *pxStack;           /*< Points to the start of the stack. */
    char                pcTaskName[ configMAX_TASK_NAME_LEN ];/*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

    #if ( ( portSTACK_GROWTH > 0 ) || ( configRECORD_STACK_HIGH_ADDRESS == 1 ) )
        StackType_t     *pxEndOfStack;      /*< Points to the highest valid address for the stack. */
    #endif

    #if ( portCRITICAL_NESTING_IN_TCB == 1 )
        UBaseType_t     uxCriticalNesting;  /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
    #endif

    #if ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t     uxTCBNumber;        /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
        UBaseType_t     uxTaskNumber;       /*< Stores a number specifically for use by third party trace code. */
    #endif

    #if ( configUSE_MUTEXES == 1 )
        UBaseType_t     uxBasePriority;     /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
        UBaseType_t     uxMutexesHeld;
    #endif

    #if ( configUSE_APPLICATION_TASK_TAG == 1 )
        TaskHookFunction_t pxTaskTag;
    #endif

    #if( configNUM_THREAD_LOCAL_STORAGE_POINTERS > 0 )
        void            *pvThreadLocalStoragePointers[ configNUM_THREAD_LOCAL_STORAGE_POINTERS ];
    #endif

    #if( configGENERATE_RUN_TIME_STATS == 1 )
        uint32_t        ulRunTimeCounter;   /*< Stores the amount of time the task has spent in the Running state. */
    #endif

    #if ( configUSE_NEWLIB_REENTRANT == 1 )
        /* Allocate a Newlib reent structure that is specific to this task.
        Note Newlib support has been included by popular demand, but is not
        used by the FreeRTOS maintainers themselves.  FreeRTOS is not
        responsible for resulting newlib operation.  User must be familiar with
        newlib and must provide system-wide implementations of the necessary
        stubs. Be warned that (at the time of writing) the current newlib design
        implements a system-wide malloc() that must be provided with locks.

        See the third party link http://www.nadler.com/embedded/newlibAndFreeRTOS.html
        for additional information. */
        struct  _reent xNewLib_reent;
    #endif

    #if( configUSE_TASK_NOTIFICATIONS == 1 )
        volatile uint32_t ulNotifiedValue;
        volatile uint8_t ucNotifyState;
    #endif

    /* See the comments in FreeRTOS.h with the definition of
    tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
    #if( tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
        uint8_t ucStaticallyAllocated;      /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
    #endif

    #if( INCLUDE_xTaskAbortDelay == 1 )
        uint8_t ucDelayAborted;
    #endif

    #if( configUSE_POSIX_ERRNO == 1 )
        int iTaskErrno;
    #endif

} tskTCB;

/* The old tskTCB name is maintained above then typedefed to the new TCB_t name
below to enable the use of older kernel aware debuggers. */
typedef tskTCB TCB_t;

/*lint -save -e956 A manual analysis and inspection has been used to determine
which static variables must be declared volatile. */
PRIVILEGED_DATA
extern TCB_t * volatile pxCurrentTCB;

/*! \note if you aren't using perf_counter inside KEIL with RTE, please create
 *!          a header file called "Pre_Include_Global.h", copy the following
 *!          content into the header file and and put following option
 *!          to your command line (supposing you are using arm compiler 6):
 *!          -include "Pre_Include_Global.h"
 */

/*
//! \brief Enable RTOS Patch for perf_counter
#define __PERF_CNT_USE_RTOS__

#define traceTASK_SWITCHED_OUT_DISABLE
#define traceTASK_SWITCHED_IN_DISABLE

extern void __freertos_evr_on_task_switched_out (void *ptTCB);
extern void __freertos_evr_on_task_switched_in(void *ptTCB, unsigned int uxTopPriority) ;

#   define traceTASK_SWITCHED_OUT()                                             \
        __freertos_evr_on_task_switched_out(pxCurrentTCB)
#   define traceTASK_SWITCHED_IN()                                              \
        __freertos_evr_on_task_switched_in(pxCurrentTCB, uxTopReadyPriority)

 */


/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
extern void __on_context_switch_in(uint32_t *pwStack);
extern void __on_context_switch_out(uint32_t *pwStack);

/*============================ IMPLEMENTATION ================================*/


#if defined(RTE_Compiler_EventRecorder)

#   include "EventRecorder.h"

#endif


#define EvtFreeRTOSTasksNo              (0xF0U)

#define EvtFreeRTOSTasks_TaskSwitchedOut                    \
            EventID(EventLevelOp,     EvtFreeRTOSTasksNo, 0x0BU)
#define EvtFreeRTOSTasks_TaskSwitchedIn                     \
            EventID(EventLevelOp,     EvtFreeRTOSTasksNo, 0x0CU)

void __freertos_evr_on_task_switched_out (void *ptTCB) {
#if defined(RTE_Compiler_EventRecorder)
  EventRecord2(EvtFreeRTOSTasks_TaskSwitchedOut, (uint32_t)ptTCB, 0U);
#else
  (void)pxCurrentTCB;
#endif

    __on_context_switch_out(((TCB_t *)ptTCB)->pxStack);

}


void __freertos_evr_on_task_switched_in(void *ptTCB, uint32_t uxTopPriority) {
#if defined(RTE_Compiler_EventRecorder)
  EventRecord2(EvtFreeRTOSTasks_TaskSwitchedIn, (uint32_t)ptTCB, uxTopPriority);
#else
  (void)pxCurrentTCB;
  (void)uxTopPriority;
#endif

    __on_context_switch_in(((TCB_t *)ptTCB)->pxStack);
}


task_cycle_info_t * get_rtos_task_cycle_info(void)
{
    return &(((struct __task_cycle_info_t *)pxCurrentTCB->pxStack)->tInfo);
}
