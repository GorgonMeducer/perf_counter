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

#ifndef __CPT_EXAMPLE_H__
#define __CPT_EXAMPLE_H__

/*============================ INCLUDES ======================================*/
#include "perf_counter.h"


#ifdef __cplusplus
extern "C" {
#endif

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
typedef struct {
    implement(perfc_cpt_t);
    void *ptResource;
} cpt_led_flash_cb_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

extern
cpt_led_flash_cb_t * cpt_example_led_flash_init(cpt_led_flash_cb_t *ptThis,
                                                void *pStack,
                                                size_t nStackSize);

extern
fsm_rt_t cpt_example_led_flash(cpt_led_flash_cb_t *ptThis);

/*============================ IMPLEMENTATION ================================*/



#ifdef __cplusplus
}
#endif

#endif
