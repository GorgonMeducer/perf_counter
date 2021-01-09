#include <stdint.h>
#include <stdio.h>
#include <cmsis_compiler.h>
#include "perf_counter.h"
#include <time.h>

void systimer_1ms_handler(void)
{
    //printf("Running original Systick_Handler...\r\n");
}

typedef struct example_lv1_t {
    uint32_t wLV1A;
    uint16_t hwLV1B;
    uint8_t  chLV1C;
}example_lv1_t;


typedef struct example_lv0_t {
    
    uint32_t    wA;
    uint16_t    hwB;
    uint8_t     chC;
    uint8_t     chID;
    example_lv1_t tLV1;
} example_lv0_t;

example_lv0_t s_tItem[8] = {
    {.chID = 0},
    {.chID = 1},
    {.chID = 2},
    {.chID = 3},
    {.chID = 4},
    {.chID = 5},
    {.chID = 6},
    {.chID = 7},
};

extern void CM7_BLX_R14_Test(void);

/*----------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/
int main (void) 
{
    /*! demo of using() block */
    using(int a = 0,printf("========= On Enter =======\r\n"), 
                    printf("========= On Leave =======\r\n")) {
        printf("\t In Body a=%d \r\n", ++a);
    }    


    printf("\r\n\r\n\r\n\r\n");

    /*! demo of __cycleof__() operation */
    __cycleof__() {
        foreach(example_lv0_t, s_tItem) {
            printf("Processing item with ID = %d\r\n", _.chID);
        }
    }

    /*! demo of with block */
    with(example_lv0_t, &s_tItem[0], pitem) {
        _.wA = 1;
        _.hwB = 2;
        _.chC = 3;
        
        with(example_lv1_t, &pitem->tLV1) {
            _.wLV1A = 4;
            _.hwLV1B = 5;
            _.chLV1C = 6;
        }
    }

    //! demo of using clock() in timer.h
    do {
        clock_t tStart = clock();
        safe_atom_code() 
        {
            printf("no interrupt \r\n");
        }
        printf("used clock cycle: %d", clock() - tStart);
    } while(0);
    
    while (1) {

    }
}
