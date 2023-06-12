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

#include <stdint.h>
#include <stdio.h>
#include <cmsis_compiler.h>
#include "perf_counter.h"


#ifndef __PERF_CNT_USE_LONG_CLOCK__
#include <time.h>
#else
typedef int64_t clock_t ;
#endif

extern void systimer_1ms_handler(void);

void systimer_1ms_handler(void)
{
    //printf("Running original Systick_Handler...\r\n");
}

typedef struct example_lv1_t {
    uint32_t wLV1A;
    uint16_t hwLV1B;
    uint8_t  chLV1C;
    uint8_t  chLV1D;
}example_lv1_t;


typedef struct example_lv0_t {

    uint32_t    wA;
    uint16_t    hwB;
    uint8_t     chC;
    uint8_t     chID;
    example_lv1_t tLV1;
} example_lv0_t;


static example_lv0_t s_tItem[8] = {
    {.chID = 0},
    {.chID = 1},
    {.chID = 2},
    {.chID = 3},
    {.chID = 4},
    {.chID = 5},
    {.chID = 6},
    {.chID = 7},
};
#if __IS_COMPILER_ARM_COMPILER__
#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif
uint32_t calculate_stack_usage_topdown(void)
{
    extern uint32_t Image$$ARM_LIB_STACK$$Limit[];
    extern uint32_t Image$$ARM_LIB_STACK$$Length;

    uint32_t *pwStack = Image$$ARM_LIB_STACK$$Limit;
    uint32_t wStackSize = (uintptr_t)&Image$$ARM_LIB_STACK$$Length / 4;
    uint32_t wStackUsed = 0;


    do {
        if (*--pwStack == 0xDEADBEEF) {
            break;
        }
        wStackUsed++;
    } while(--wStackSize);
    
    
    printf("\r\nStack Usage: [%d/%d] %2.2f%%\r\n", 
            wStackUsed * 4, 
            (uintptr_t)&Image$$ARM_LIB_STACK$$Length,
            (   (float)wStackUsed * 400.0f 
            /   (float)(uintptr_t)&Image$$ARM_LIB_STACK$$Length));

    return wStackUsed * 4;
}

uint32_t calculate_stack_usage_bottomup(void)
{
    extern uint32_t Image$$ARM_LIB_STACK$$Base[];
    extern uint32_t Image$$ARM_LIB_STACK$$Length;

    uint32_t *pwStack = Image$$ARM_LIB_STACK$$Base;
    uint32_t wStackSize = (uintptr_t)&Image$$ARM_LIB_STACK$$Length;
    uint32_t wStackUsed = wStackSize / 4;

    do {
        if (*pwStack++ != 0xDEADBEEF) {
            break;
        }
    } while(--wStackUsed);
    
    printf("\r\nStack Usage: [%d/%d] %2.2f%%\r\n", 
            wStackUsed * 4, 
            wStackSize,
            (   (float)wStackUsed * 400.0f / (float)wStackSize));

    return wStackUsed * 4;
}

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
#endif

/*----------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/
int main (void)
{
    int32_t iCycleResult = 0;

    /*! demo of using() block */
    using(int a = 0,printf("========= On Enter =======\r\n"),
                    printf("========= On Leave =======\r\n")) {
        printf("\t In Body a=%d \r\n", ++a);
    }

    __cycleof__("Calibration") {}

    printf("\r\n\r\n\r\n\r\n");

    /*! demo of __cycleof__() operation */
    __cycleof__() {
        foreach(example_lv0_t, s_tItem, ptItem) {
            printf("Processing item with ID = %d\r\n", _->chID);
        }
    }

    /* measure cycles and store it in a dedicated variable without printf */
    __cycleof__("delay_us(1000ul)",
        /* insert code to __cycleof__ body, "{}" can be omitted  */
        {
            iCycleResult = __cycle_count__;   /*< "__cycle_count__" stores the result */
        }) {
        delay_us(1000ul);
    }

    printf("\r\n delay_us(1000ul) takes %d cycles\r\n", (int)iCycleResult);

    /*! demo of with block */
    with(example_lv0_t, &s_tItem[0], pitem) {
        _->wA = 1;
        _->hwB = 2;
        _->chC = 3;

        with(example_lv1_t, &pitem->tLV1) {
            _->wLV1A = 4;
            _->hwLV1B = 5;
            _->chLV1C = 6;
        }
    }

    //! demo of using clock() in timer.h
    do {
        int64_t tStart = get_system_ticks();
        __IRQ_SAFE {
            printf("no interrupt \r\n");
        }
        printf("used clock cycle: %d", (int32_t)(get_system_ticks() - tStart));
    } while(0);

#if __IS_COMPILER_ARM_COMPILER__
    calculate_stack_usage_topdown();
    calculate_stack_usage_bottomup();
#endif

#ifdef __PERF_COUNTER_COREMARK__
    coremark_main();
#endif

    while (1) {
        if (perfc_is_time_out_ms(1000)) {
            printf("\r[%010d]", get_system_ms());
        }

        __cpu_time__(10) {
            delay_us(30000);
        }
        delay_us(70000);

    }
}
