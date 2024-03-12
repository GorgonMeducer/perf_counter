;/****************************************************************************
;*  Copyright 2024 Gorgon Meducer (Email:embedded_zhuoran@hotmail.com)       *
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

    .syntax unified
    .arch   armv6-m

    .eabi_attribute Tag_ABI_align_preserved, 1
    .text
    .thumb
    .thumb_func
    .align  2
    .globl  $Sub$$SysTick_Handler
    .type   $Sub$$SysTick_Handler, %function

$Sub$$SysTick_Handler:
    push    {r4, r5}
    push    {r4, lr}
    ldr     R0, =perfc_port_insert_to_system_timer_insert_ovf_handler
    blx     R0
    pop     {r4, r5}
    mov     lr, r5
    pop     {r4, r5}
    ldr     R0, =$Super$$SysTick_Handler
    bx      R0

    .globl  __ensure_systick_wrapper
    .type   __ensure_systick_wrapper, %function

__ensure_systick_wrapper:
    bx      lr