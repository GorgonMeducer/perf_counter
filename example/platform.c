/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher for MPS2
 * Note(s): possible defines set in "options for target - C/C++ - Define"
 *            __USE_LCD    - enable Output on GLCD
 *            __USE_TIMER0 - use Timer0  to generate timer interrupt
 *                         - use SysTick to generate timer interrupt (default)
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2015 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "ARMCM3.h"                     // Keil::Board Support:V2M-MPS2:Common
#include <assert.h>

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

void SysTick_Handler (void) 
{
    if (s_wMSCounter) {
        s_wMSCounter--;
    }

    systimer_1ms_handler();
}

void delay_ms(uint32_t wMillisecond)
{
    s_wMSCounter = wMillisecond;
    while( s_wMSCounter > 0 );
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


