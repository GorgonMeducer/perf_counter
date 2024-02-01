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




#endif