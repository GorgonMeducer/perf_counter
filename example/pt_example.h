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

#ifndef __PT_EXAMPLE_H__
#define __PT_EXAMPLE_H__

/*============================ INCLUDES ======================================*/
#include "perf_counter.h"


#ifdef __cplusplus
extern "C" {
#endif

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
typedef struct {
    uint8_t chState;
    void *ptResource;
} pt_led_flash_cb_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

extern
pt_led_flash_cb_t *pt_example_led_flash_init(pt_led_flash_cb_t *ptThis);

extern
fsm_rt_t pt_example_led_flash(pt_led_flash_cb_t *ptThis);

/*============================ IMPLEMENTATION ================================*/



#ifdef __cplusplus
}
#endif

#endif
