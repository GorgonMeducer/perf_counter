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

#ifndef __PERFC_TASK_PT_H__
#define __PERFC_TASK_PT_H__


/*============================ INCLUDES ======================================*/
#include "perf_counter.h"

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wunused-label"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \addtogroup gLanguageExtensios 4 Language Extensions
 * @{
 */

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/

/*----------------------------------------------------------------------------*
 * PT Operations                                                              *
 *----------------------------------------------------------------------------*/
/*
Protothreads open source BSD-style license
The protothreads library is released under an open source license that allows 
both commercial and non-commercial use without restrictions. The only 
requirement is that credits is given in the source code and in the documentation 
for your product.

The full license text follows.

Copyright (c) 2004-2005, Swedish Institute of Computer Science.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. Neither the name of the Institute nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS `AS IS' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.

Author: Adam Dunkels
*/
#define PERFC_PT_BEGIN(__state)                                                 \
            enum {                                                              \
                count_offset = __COUNTER__ + 1,                                 \
            };                                                                  \
            uint8_t *ptPTState = &(__state);                                    \
            switch (__state) {                                                  \
                case __COUNTER__ - count_offset: 

#define PERFC_PT_ENTRY(...)                                                     \
                    (*ptPTState) = (__COUNTER__ - count_offset + 1) >> 1;       \
                    __VA_ARGS__                                                 \
                case (__COUNTER__ - count_offset) >> 1: (void)(*ptPTState);
            
#define PERFC_PT_YIELD(...)                                                     \
            PERFC_PT_ENTRY(return __VA_ARGS__;)
            
#define PERFC_PT_END()                                                          \
                    (*ptPTState) = 0;                                           \
                    break;                                                      \
            }

#define PERFC_PT_GOTO_PREV_ENTRY(...)    return __VA_ARGS__;

#define PERFC_PT_WAIT_UNTIL(__CONDITION, ...)                                   \
            {                                                                   \
            PERFC_PT_ENTRY()                                                    \
                __VA_ARGS__;                                                    \
                if (!(__CONDITION)) {                                           \
                    PERFC_PT_GOTO_PREV_ENTRY(fsm_rt_on_going);                  \
                }                                                               \
            }

#define PERFC_PT_WAIT_FOR_OBJ_UNTIL(__CONDITION, ...)                           \
            {                                                                   \
            PERFC_PT__ENTRY()                                                   \
                __VA_ARGS__;                                                    \
                if (!(__CONDITION)) {                                           \
                    PERFC_PT_GOTO_PREV_ENTRY(fsm_rt_wait_for_obj);              \
                }                                                               \
            }

#define PERFC_PT_WAIT_FOR_RES_UNTIL(__CONDITION, ...)                           \
            {                                                                   \
            PERFC_PT_ENTRY()                                                    \
                __VA_ARGS__;                                                    \
                if (!(__CONDITION)) {                                           \
                    PERFC_PT_GOTO_PREV_ENTRY(fsm_rt_wait_for_res);              \
                }                                                               \
            }

#define PERFC_PT_DELAY_MS(__ms, ...)                                            \
            {                                                                   \
                PERFC_PT_ENTRY(                                                 \
                    static int64_t PERFC_SAFE_NAME(s_lTimestamp);               \
                    UNUSED_PARAM(PERFC_SAFE_NAME(s_lTimestamp));                \
                    int64_t *PERFC_SAFE_NAME(plTimestamp)                       \
                        = (&PERFC_SAFE_NAME(s_lTimestamp), ##__VA_ARGS__);      \
                    *PERFC_SAFE_NAME(plTimestamp) = get_system_ms();            \
                )                                                               \
                PERFC_SAFE_NAME(plTimestamp)                                    \
                    = (&PERFC_SAFE_NAME(s_lTimestamp), ##__VA_ARGS__);          \
                int64_t PERFC_SAFE_NAME(lElapsedMs) =                           \
                    get_system_ms() - *PERFC_SAFE_NAME(plTimestamp);            \
                if (PERFC_SAFE_NAME(lElapsedMs) < (__ms)) {                     \
                    PERFC_PT_GOTO_PREV_ENTRY(fsm_rt_on_going);                  \
                }                                                               \
            }


#define PERFC_PT_REPORT_STATUS(...)                                             \
            PERFC_PT_ENTRY(                                                     \
                return __VA_ARGS__;                                             \
            )
            
#define PERFC_PT_RETURN(...)                                                    \
        {                                                                       \
            (*ptPTState) = 0;                                                   \
            return __VA_ARGS__;                                                 \
        }

/* coroutine PT */
#if __C_LANGUAGE_EXTENSIONS_PERFC_COROUTINE__

#define PERFC_CPT_BEGIN(__cpt)                                                  \
            enum {                                                              \
                count_offset = __COUNTER__ + 1,                                 \
            };                                                                  \
            perfc_cpt_t *ptTask = (perfc_cpt_t *)&(__cpt);                      \
label_switch_start:                                                             \
            switch (ptTask->chState) {                                          \
                case __COUNTER__ - count_offset: 

#define PERFC_CPT_ENTRY(...)                                                    \
                    (ptTask->chState) = (__COUNTER__ - count_offset + 1) >> 1;  \
                    __VA_ARGS__                                                 \
                case (__COUNTER__ - count_offset) >> 1: (void)(ptTask->chState);
            
#define PERFC_CPT_YIELD(...)                                                    \
                {                                                               \
                    ptTask->tCoroutine.tReturn.nResult = __VA_ARGS__;           \
                    perfc_coroutine_yield(&ptTask->tCoroutine);                 \
                }

#define PERFC_CPT_END()                                                         \
                    (ptTask->chState) = 0;                                      \
                    break;                                                      \
            }                                                                   \

#define PERFC_CPT_GOTO_PREV_ENTRY(...)                                          \
                {                                                               \
                    PERFC_CPT_YIELD((fsm_rt_on_going,##__VA_ARGS__));           \
                    goto label_switch_start;                                    \
                }

#define PERFC_CPT_WAIT_UNTIL(__CONDITION, ...)                                  \
            {                                                                   \
        label_wait_until_entry_##__LINE__:                                      \
                (void)(ptTask);                                                 \
                __VA_ARGS__;                                                    \
                if ((__CONDITION)) {                                            \
                    goto label_wait_until_exit_##__LINE__;                      \
                }                                                               \
                PERFC_CPT_YIELD(fsm_rt_on_going);                               \
                goto label_wait_until_entry_##__LINE__;                         \
        label_wait_until_exit_##__LINE__:                                       \
                (void)(ptTask);                                                 \
            }

#define PERFC_CPT_WAIT_FOR_OBJ_UNTIL(__CONDITION, ...)                          \
            {                                                                   \
        label_wait_for_obj_until_entry_##__LINE__:                              \
                (void)(ptTask);                                                 \
                __VA_ARGS__;                                                    \
                if ((__CONDITION)) {                                            \
                    goto label_wait_for_obj_until_exit_##__LINE__;              \
                }                                                               \
                PERFC_CPT_YIELD(fsm_rt_wait_for_obj);                           \
                goto label_wait_for_obj_until_entry_##__LINE__;                 \
        label_wait_for_obj_until_exit_##__LINE__:                               \
                (void)(ptTask);                                                 \
            }

#define PERFC_CPT_WAIT_FOR_RES_UNTIL(__CONDITION, ...)                          \
            {                                                                   \
        label_wait_for_res_until_entry_##__LINE__:                              \
                (void)(ptTask);                                                 \
                __VA_ARGS__;                                                    \
                if ((__CONDITION)) {                                            \
                    goto label_wait_for_res_until_exit_##__LINE__;              \
                }                                                               \
                PERFC_CPT_YIELD(fsm_rt_wait_for_res);                           \
                goto label_wait_for_res_until_entry_##__LINE__;                 \
        label_wait_for_res_until_exit_##__LINE__:                               \
                (void)(ptTask);                                                 \
            }

#define PERFC_CPT_DELAY_MS(__ms, ...)                                           \
            {                                                                   \
                int64_t lDelayTimestampInMs = get_system_ms();                  \
                do {                                                            \
                    if ((get_system_ms() - lDelayTimestampInMs) >= (__ms)) {    \
                        break;                                                  \
                    }                                                           \
                    PERFC_CPT_YIELD(fsm_rt_on_going);                           \
                } while(1);                                                     \
            }


#define PERFC_CPT_REPORT_STATUS(...)   PERFC_CPT_YIELD(__VA_ARGS__)
            
#define PERFC_CPT_RETURN(...)                                                   \
            {                                                                   \
                (ptTask->chState) = 0;                                          \
                return __VA_ARGS__;                                             \
            }

#endif

/*============================ TYPES =========================================*/

#if __C_LANGUAGE_EXTENSIONS_PERFC_COROUTINE__

typedef struct perfc_cpt_t {
    perfc_coroutine_t tCoroutine;
    uint8_t chState;
} perfc_cpt_t;

#endif
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/*! @} */


#ifdef __cplusplus
}
#endif

#endif
