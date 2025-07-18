;/****************************************************************************
;*  Copyright 2022 Gorgon Meducer (Email:embedded_zhuoran@hotmail.com)       *
;*                                                                           *
;*  Licensed under the Apache License, Version 2.0 (the "License");          *
;*  you may not use this file except in compliance with the License.         *
;*  You may obtain a copy of the License at                                  *
;*                                                                           *
;*     http://www.apache.org/licenses/LICENSE-2.0                            *
;*                                                                           *
;*  Unless required by applicable law or agreed to in writing, software      *
;*  distributed under the License is distributed on an "AS IS" BASIS,        *
;*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
;*  See the License for the specific language governing permissions and      *
;*  limitations under the License.                                           *
;*                                                                           *
;****************************************************************************/


                PRESERVE8
                THUMB
                AREA    |.text|, CODE, READONLY

|$Sub$$SysTick_Handler|   PROC
                EXPORT  |$Sub$$SysTick_Handler|
                IMPORT  perfc_port_insert_to_system_timer_insert_ovf_handler
                IMPORT  |$Super$$SysTick_Handler|
                push    {r4, r5}
                push	    {r4, lr}
                LDR      R0, =perfc_port_insert_to_system_timer_insert_ovf_handler
                BLX      R0
                pop         {r4, r5}
                mov     lr, r5
                pop     {r4, r5}
                LDR      R0, =|$Super$$SysTick_Handler|
                BX      R0
                ENDP
                
                ALIGN
                AREA    |.text|, CODE, READONLY

__ensure_systick_wrapper   PROC
                EXPORT  __ensure_systick_wrapper
                NOP
                BX      LR
                ENDP

                ALIGN
                AREA    |.text|, CODE, READONLY

__perfc_port_set_sp   PROC
                EXPORT  __perfc_port_set_sp
                MOV     SP, R0
                BX      LR
                ENDP

                END