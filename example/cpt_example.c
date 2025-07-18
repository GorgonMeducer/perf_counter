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

/*============================ INCLUDES ======================================*/
#include "cpt_example.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#   pragma clang diagnostic ignored "-Wcast-function-type-mismatch"
#elif __IS_COMPILER_ARM_COMPILER_5__
#   pragma diag_suppress 111
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*============================ MACROS ========================================*/
#undef this
#define this    (*ptThis)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
cpt_led_flash_cb_t * cpt_example_led_flash_init(cpt_led_flash_cb_t *ptThis,
                                                void *pStack,
                                                size_t nStackSize)
{
    if (NULL == ptThis) {
        return NULL;
    }

    memset(ptThis, 0, sizeof(this));

    perfc_coroutine_init(&this.use_as__perfc_cpt_t.tCoroutine,
                         (perfc_coroutine_task_handler_t *)&cpt_example_led_flash,
                         pStack,
                         nStackSize);

    return ptThis;
}

void perf_coroutine_report_error(   perfc_coroutine_t *ptTask, 
                                    perfc_coroutine_err_t tError)
{
    UNUSED_PARAM(ptTask);
    UNUSED_PARAM(tError);
    
    if (tError == PERFC_CR_ERR_STACK_OVERFLOW) {
        printf("Stack Overflow\r\n");

    }
    
    assert(tError == PERFC_CR_ERR_NONE);
}


fsm_rt_t cpt_example_led_flash(cpt_led_flash_cb_t *ptThis)
{

PERFC_CPT_BEGIN(this)

    do {
        void *ptResource = NULL;
    
    PERFC_CPT_WAIT_FOR_RES_UNTIL( 
        (ptResource != NULL),               /* quit condition */
        ptResource = malloc(100);          /* try to allocate memory */
    )

        printf("LED ON  [%lld][%p]\r\n", get_system_ms(), ptResource);

    PERFC_CPT_DELAY_MS(500);
        
        printf("LED OFF [%lld][%p]\r\n", get_system_ms(), ptResource);

    PERFC_CPT_DELAY_MS(500);
        
        free(ptResource);
        
        PERFC_CPT_REPORT_STATUS(fsm_rt_cpl);
    } while(1);

PERFC_CPT_END()

    return fsm_rt_cpl;

}


#ifdef __cplusplus
}
#endif