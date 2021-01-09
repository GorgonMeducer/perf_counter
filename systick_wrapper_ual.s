                PRESERVE8
                THUMB
                AREA    |.text|, CODE, READONLY

|$Sub$$SysTick_Handler|   PROC
                EXPORT  |$Sub$$SysTick_Handler|
                IMPORT  user_code_insert_to_systick_handler
                IMPORT  |$Super$$SysTick_Handler|
                push	{r4, lr}
                bl	    user_code_insert_to_systick_handler
                pop	    {r4, lr}
                b	    |$Super$$SysTick_Handler|
                ENDP
                
                AREA    |.text|, CODE, READONLY

__ensure_systick_wrapper   PROC
                EXPORT  __ensure_systick_wrapper
                NOP
                BX      LR
                ENDP
                
                END