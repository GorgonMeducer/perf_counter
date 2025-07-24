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
#include "perf_counter.h"
#include <assert.h>
#include <RTE_Components.h>
#if defined(RTE_Compiler_EventRecorder)
#   include <EventRecorder.h>
#endif

extern
void uart_config(uint32_t wUARTFrequency);


__attribute__((weak))
void systimer_1ms_handler(void)
{
    //assert(false);
}

static volatile uint32_t s_wMSCounter = 0;

/*----------------------------------------------------------------------------
  SysTick / Timer0 IRQ Handler
 *----------------------------------------------------------------------------*/

ISR(SysTick_Handler, 512)
{
    if (s_wMSCounter) {
        s_wMSCounter--;
    }
    volatile float static s_fPI = 3.14;
    s_fPI *= 1.01f;

    systimer_1ms_handler();
}

/*! \brief initialise platform before main()
 */
__attribute__((constructor(101)))
void platform_init(void)
{
    extern void SystemCoreClockUpdate(void);
    SystemCoreClockUpdate();

    /* Generate interrupt each 1 ms  */
    //SysTick_Config(SystemCoreClock / 1000);
    perfc_init(false);
    
#if defined(RTE_Compiler_EventRecorder) && defined(RTE_Compiler_IO_STDOUT_EVR)
    EventRecorderInitialize(0,1);
#else
    uart_config(25000000ul);
#endif
}


