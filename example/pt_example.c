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
#include "pt_example.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(__IS_COMPILER_ARM_COMPILER_5__)
#   pragma diag_suppress 550, 546, 111
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

pt_led_flash_cb_t * pt_example_led_flash_init(pt_led_flash_cb_t *ptThis)
{
    if (NULL == ptThis) {
        return NULL;
    }
    
    memset(ptThis, 0, sizeof(this));

    return ptThis;
}


fsm_rt_t pt_example_led_flash(pt_led_flash_cb_t *ptThis)
{

PERFC_PT_BEGIN(this.chState)

    do {
    PERFC_PT_WAIT_FOR_RES_UNTIL( 
        (this.ptResource != NULL),               /* quit condition */
        this.ptResource = malloc(100);          /* try to allocate memory */
    )

        printf("LED ON  [%lld]\r\n", get_system_ms());

    PERFC_PT_DELAY_MS(500);
        
        printf("LED OFF [%lld]\r\n", get_system_ms());


    PERFC_PT_DELAY_MS(500);
        
        free(this.ptResource);
    } while(1);

PERFC_PT_END()

    return fsm_rt_cpl;

}


#ifdef __cplusplus
}
#endif