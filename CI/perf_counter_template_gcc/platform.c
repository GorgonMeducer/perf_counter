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

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "perf_counter.h"
//#include "ARMCM0.h"                     // Keil::Board Support:V2M-MPS2:Common
#include "main.h"
#include <assert.h>

extern
void uart_config(uint32_t wUARTFrequency);


__attribute__((weak))
void systimer_1ms_handler(void)
{
    HAL_IncTick();
}

static volatile uint32_t s_wMSCounter = 0;

/*----------------------------------------------------------------------------
  SysTick / Timer0 IRQ Handler
 *----------------------------------------------------------------------------*/

void SysTick_Handler (void) 
{
    if (s_wMSCounter) {
        s_wMSCounter--;
    }
    user_code_insert_to_systick_handler();
    systimer_1ms_handler();
}

/*! \brief initialise platform before main()
 */
__attribute__((constructor(101)))
void platform_init(void)
{
    SystemCoreClockUpdate();
    
    uart_config(25000000ul);
    
    /* Generate interrupt each 1 ms  */
    SysTick_Config(SystemCoreClock / 1000);    
}


