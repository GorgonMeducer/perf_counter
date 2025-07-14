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

#ifndef __PERFC_TASK_COMMON_H__
#define __PERFC_TASK_COMMON_H__


/*============================ INCLUDES ======================================*/
#include "perfc_common.h"
#include <setjmp.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \addtogroup gLanguageExtensios 4 Language Extensions
 * @{
 */

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

typedef enum {
    PERFC_CR_ERR_STACK_OVERFLOW = -1,
    PERFC_CR_ERR_NONE,
} perfc_coroutine_err_t;

typedef union perfc_coroutine_rt_t {
    intptr_t *pValue;
    /*
     * NOTE:
     *      when nResult < 0, it is an error code
     *      when nResult <= 255, it is an status code
     *          other postive value can be seen as a valid pointer
     */
    intptr_t  nResult;
} perfc_coroutine_rt_t;

typedef struct perfc_coroutine_t perfc_coroutine_t;
typedef intptr_t perfc_coroutine_task_handler_t(perfc_coroutine_t *ptThis);

/*
 * Please use this perfc_coroutine_t as base class, it is recommended to use
 * implement(perfc_coroutine_t) in your task class definition. E.g.
 *
 *  typedef struct {
 *      implement(perfc_cpt_t);
 *      void *ptResource;
 *  } cpt_led_flash_cb_t;
 * 
 */
struct perfc_coroutine_t {
    jmp_buf *ptYieldPoint;
    jmp_buf *ptCaller;
    void *pStackBase;
    perfc_coroutine_rt_t tReturn;
};

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

extern
__attribute__((noinline))
int perfc_coroutine_init(   perfc_coroutine_t *ptTask, 
                            perfc_coroutine_task_handler_t *fnHandler,
                            void *pStackBase,
                            size_t tSizeInByte);

extern
perfc_coroutine_rt_t perfc_coroutine_call(perfc_coroutine_t *ptTask);

extern
void perfc_coroutine_yield(perfc_coroutine_t *ptTask);

extern
size_t perfc_coroutine_stack_remain(perfc_coroutine_t *ptTask);

/*============================ IMPLEMENTATION ================================*/

/*! @} */


#ifdef __cplusplus
}
#endif

#endif
