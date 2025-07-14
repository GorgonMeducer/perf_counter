/****************************************************************************
*  Copyright 2024 Gorgon Meducer (Email:embedded_zhuoran@hotmail.com)       *
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

/*============================ INCLUDES ======================================*/
#undef __PERF_COUNT_PLATFORM_SPECIFIC_HEADER__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define __IMPLEMENT_PERF_COUNTER
#include "perf_counter.h"

#if defined(__IS_COMPILER_GCC__)
#   pragma GCC diagnostic ignored "-Wattributes"
#endif

#if defined(__clang__)
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wconditional-uninitialized"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif

#if defined(_RTE_)
#   include "RTE_Components.h"
#endif


/*============================ MACROS ========================================*/

#if defined(CMSIS_device_header)
#   include CMSIS_device_header
#else

#ifndef __PMU_NUM_EVENTCNT
#   define __PMU_NUM_EVENTCNT   8
#endif

/* IO definitions (access restrictions to peripheral registers) */
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/** \brief DCB Debug Halting Control and Status Register Definitions */
#define DCB_DHCSR_DBGKEY_Pos               16U                                            /*!< DCB DHCSR: Debug key Position */
#define DCB_DHCSR_DBGKEY_Msk               (0xFFFFUL << DCB_DHCSR_DBGKEY_Pos)             /*!< DCB DHCSR: Debug key Mask */

#define DCB_DHCSR_S_RESTART_ST_Pos         26U                                            /*!< DCB DHCSR: Restart sticky status Position */
#define DCB_DHCSR_S_RESTART_ST_Msk         (1UL << DCB_DHCSR_S_RESTART_ST_Pos)            /*!< DCB DHCSR: Restart sticky status Mask */

#define DCB_DHCSR_S_RESET_ST_Pos           25U                                            /*!< DCB DHCSR: Reset sticky status Position */
#define DCB_DHCSR_S_RESET_ST_Msk           (1UL << DCB_DHCSR_S_RESET_ST_Pos)              /*!< DCB DHCSR: Reset sticky status Mask */

#define DCB_DHCSR_S_RETIRE_ST_Pos          24U                                            /*!< DCB DHCSR: Retire sticky status Position */
#define DCB_DHCSR_S_RETIRE_ST_Msk          (1UL << DCB_DHCSR_S_RETIRE_ST_Pos)             /*!< DCB DHCSR: Retire sticky status Mask */

#define DCB_DHCSR_S_FPD_Pos                23U                                            /*!< DCB DHCSR: Floating-point registers Debuggable Position */
#define DCB_DHCSR_S_FPD_Msk                (1UL << DCB_DHCSR_S_FPD_Pos)                   /*!< DCB DHCSR: Floating-point registers Debuggable Mask */

#define DCB_DHCSR_S_SUIDE_Pos              22U                                            /*!< DCB DHCSR: Secure unprivileged halting debug enabled Position */
#define DCB_DHCSR_S_SUIDE_Msk              (1UL << DCB_DHCSR_S_SUIDE_Pos)                 /*!< DCB DHCSR: Secure unprivileged halting debug enabled Mask */

#define DCB_DHCSR_S_NSUIDE_Pos             21U                                            /*!< DCB DHCSR: Non-secure unprivileged halting debug enabled Position */
#define DCB_DHCSR_S_NSUIDE_Msk             (1UL << DCB_DHCSR_S_NSUIDE_Pos)                /*!< DCB DHCSR: Non-secure unprivileged halting debug enabled Mask */

#define DCB_DHCSR_S_SDE_Pos                20U                                            /*!< DCB DHCSR: Secure debug enabled Position */
#define DCB_DHCSR_S_SDE_Msk                (1UL << DCB_DHCSR_S_SDE_Pos)                   /*!< DCB DHCSR: Secure debug enabled Mask */

#define DCB_DHCSR_S_LOCKUP_Pos             19U                                            /*!< DCB DHCSR: Lockup status Position */
#define DCB_DHCSR_S_LOCKUP_Msk             (1UL << DCB_DHCSR_S_LOCKUP_Pos)                /*!< DCB DHCSR: Lockup status Mask */

#define DCB_DHCSR_S_SLEEP_Pos              18U                                            /*!< DCB DHCSR: Sleeping status Position */
#define DCB_DHCSR_S_SLEEP_Msk              (1UL << DCB_DHCSR_S_SLEEP_Pos)                 /*!< DCB DHCSR: Sleeping status Mask */

#define DCB_DHCSR_S_HALT_Pos               17U                                            /*!< DCB DHCSR: Halted status Position */
#define DCB_DHCSR_S_HALT_Msk               (1UL << DCB_DHCSR_S_HALT_Pos)                  /*!< DCB DHCSR: Halted status Mask */

#define DCB_DHCSR_S_REGRDY_Pos             16U                                            /*!< DCB DHCSR: Register ready status Position */
#define DCB_DHCSR_S_REGRDY_Msk             (1UL << DCB_DHCSR_S_REGRDY_Pos)                /*!< DCB DHCSR: Register ready status Mask */

#define DCB_DHCSR_C_PMOV_Pos                6U                                            /*!< DCB DHCSR: Halt on PMU overflow control Position */
#define DCB_DHCSR_C_PMOV_Msk               (1UL << DCB_DHCSR_C_PMOV_Pos)                  /*!< DCB DHCSR: Halt on PMU overflow control Mask */

#define DCB_DHCSR_C_SNAPSTALL_Pos           5U                                            /*!< DCB DHCSR: Snap stall control Position */
#define DCB_DHCSR_C_SNAPSTALL_Msk          (1UL << DCB_DHCSR_C_SNAPSTALL_Pos)             /*!< DCB DHCSR: Snap stall control Mask */

#define DCB_DHCSR_C_MASKINTS_Pos            3U                                            /*!< DCB DHCSR: Mask interrupts control Position */
#define DCB_DHCSR_C_MASKINTS_Msk           (1UL << DCB_DHCSR_C_MASKINTS_Pos)              /*!< DCB DHCSR: Mask interrupts control Mask */

#define DCB_DHCSR_C_STEP_Pos                2U                                            /*!< DCB DHCSR: Step control Position */
#define DCB_DHCSR_C_STEP_Msk               (1UL << DCB_DHCSR_C_STEP_Pos)                  /*!< DCB DHCSR: Step control Mask */

#define DCB_DHCSR_C_HALT_Pos                1U                                            /*!< DCB DHCSR: Halt control Position */
#define DCB_DHCSR_C_HALT_Msk               (1UL << DCB_DHCSR_C_HALT_Pos)                  /*!< DCB DHCSR: Halt control Mask */

#define DCB_DHCSR_C_DEBUGEN_Pos             0U                                            /*!< DCB DHCSR: Debug enable control Position */
#define DCB_DHCSR_C_DEBUGEN_Msk            (1UL /*<< DCB_DHCSR_C_DEBUGEN_Pos*/)           /*!< DCB DHCSR: Debug enable control Mask */

/** \brief DCB Debug Core Register Selector Register Definitions */
#define DCB_DCRSR_REGWnR_Pos               16U                                            /*!< DCB DCRSR: Register write/not-read Position */
#define DCB_DCRSR_REGWnR_Msk               (1UL << DCB_DCRSR_REGWnR_Pos)                  /*!< DCB DCRSR: Register write/not-read Mask */

#define DCB_DCRSR_REGSEL_Pos                0U                                            /*!< DCB DCRSR: Register selector Position */
#define DCB_DCRSR_REGSEL_Msk               (0x7FUL /*<< DCB_DCRSR_REGSEL_Pos*/)           /*!< DCB DCRSR: Register selector Mask */

/** \brief DCB Debug Core Register Data Register Definitions */
#define DCB_DCRDR_DBGTMP_Pos                0U                                            /*!< DCB DCRDR: Data temporary buffer Position */
#define DCB_DCRDR_DBGTMP_Msk               (0xFFFFFFFFUL /*<< DCB_DCRDR_DBGTMP_Pos*/)     /*!< DCB DCRDR: Data temporary buffer Mask */

/** \brief DCB Debug Exception and Monitor Control Register Definitions */
#define DCB_DEMCR_TRCENA_Pos               24U                                            /*!< DCB DEMCR: Trace enable Position */
#define DCB_DEMCR_TRCENA_Msk               (1UL << DCB_DEMCR_TRCENA_Pos)                  /*!< DCB DEMCR: Trace enable Mask */

#define DCB_DEMCR_MONPRKEY_Pos             23U                                            /*!< DCB DEMCR: Monitor pend req key Position */
#define DCB_DEMCR_MONPRKEY_Msk             (1UL << DCB_DEMCR_MONPRKEY_Pos)                /*!< DCB DEMCR: Monitor pend req key Mask */

#define DCB_DEMCR_UMON_EN_Pos              21U                                            /*!< DCB DEMCR: Unprivileged monitor enable Position */
#define DCB_DEMCR_UMON_EN_Msk              (1UL << DCB_DEMCR_UMON_EN_Pos)                 /*!< DCB DEMCR: Unprivileged monitor enable Mask */

#define DCB_DEMCR_SDME_Pos                 20U                                            /*!< DCB DEMCR: Secure DebugMonitor enable Position */
#define DCB_DEMCR_SDME_Msk                 (1UL << DCB_DEMCR_SDME_Pos)                    /*!< DCB DEMCR: Secure DebugMonitor enable Mask */

#define DCB_DEMCR_MON_REQ_Pos              19U                                            /*!< DCB DEMCR: Monitor request Position */
#define DCB_DEMCR_MON_REQ_Msk              (1UL << DCB_DEMCR_MON_REQ_Pos)                 /*!< DCB DEMCR: Monitor request Mask */

#define DCB_DEMCR_MON_STEP_Pos             18U                                            /*!< DCB DEMCR: Monitor step Position */
#define DCB_DEMCR_MON_STEP_Msk             (1UL << DCB_DEMCR_MON_STEP_Pos)                /*!< DCB DEMCR: Monitor step Mask */

#define DCB_DEMCR_MON_PEND_Pos             17U                                            /*!< DCB DEMCR: Monitor pend Position */
#define DCB_DEMCR_MON_PEND_Msk             (1UL << DCB_DEMCR_MON_PEND_Pos)                /*!< DCB DEMCR: Monitor pend Mask */

#define DCB_DEMCR_MON_EN_Pos               16U                                            /*!< DCB DEMCR: Monitor enable Position */
#define DCB_DEMCR_MON_EN_Msk               (1UL << DCB_DEMCR_MON_EN_Pos)                  /*!< DCB DEMCR: Monitor enable Mask */

#define DCB_DEMCR_VC_SFERR_Pos             11U                                            /*!< DCB DEMCR: Vector Catch SecureFault Position */
#define DCB_DEMCR_VC_SFERR_Msk             (1UL << DCB_DEMCR_VC_SFERR_Pos)                /*!< DCB DEMCR: Vector Catch SecureFault Mask */

#define DCB_DEMCR_VC_HARDERR_Pos           10U                                            /*!< DCB DEMCR: Vector Catch HardFault errors Position */
#define DCB_DEMCR_VC_HARDERR_Msk           (1UL << DCB_DEMCR_VC_HARDERR_Pos)              /*!< DCB DEMCR: Vector Catch HardFault errors Mask */

#define DCB_DEMCR_VC_INTERR_Pos             9U                                            /*!< DCB DEMCR: Vector Catch interrupt errors Position */
#define DCB_DEMCR_VC_INTERR_Msk            (1UL << DCB_DEMCR_VC_INTERR_Pos)               /*!< DCB DEMCR: Vector Catch interrupt errors Mask */

#define DCB_DEMCR_VC_BUSERR_Pos             8U                                            /*!< DCB DEMCR: Vector Catch BusFault errors Position */
#define DCB_DEMCR_VC_BUSERR_Msk            (1UL << DCB_DEMCR_VC_BUSERR_Pos)               /*!< DCB DEMCR: Vector Catch BusFault errors Mask */

#define DCB_DEMCR_VC_STATERR_Pos            7U                                            /*!< DCB DEMCR: Vector Catch state errors Position */
#define DCB_DEMCR_VC_STATERR_Msk           (1UL << DCB_DEMCR_VC_STATERR_Pos)              /*!< DCB DEMCR: Vector Catch state errors Mask */

#define DCB_DEMCR_VC_CHKERR_Pos             6U                                            /*!< DCB DEMCR: Vector Catch check errors Position */
#define DCB_DEMCR_VC_CHKERR_Msk            (1UL << DCB_DEMCR_VC_CHKERR_Pos)               /*!< DCB DEMCR: Vector Catch check errors Mask */

#define DCB_DEMCR_VC_NOCPERR_Pos            5U                                            /*!< DCB DEMCR: Vector Catch NOCP errors Position */
#define DCB_DEMCR_VC_NOCPERR_Msk           (1UL << DCB_DEMCR_VC_NOCPERR_Pos)              /*!< DCB DEMCR: Vector Catch NOCP errors Mask */

#define DCB_DEMCR_VC_MMERR_Pos              4U                                            /*!< DCB DEMCR: Vector Catch MemManage errors Position */
#define DCB_DEMCR_VC_MMERR_Msk             (1UL << DCB_DEMCR_VC_MMERR_Pos)                /*!< DCB DEMCR: Vector Catch MemManage errors Mask */

#define DCB_DEMCR_VC_CORERESET_Pos          0U                                            /*!< DCB DEMCR: Vector Catch Core reset Position */
#define DCB_DEMCR_VC_CORERESET_Msk         (1UL /*<< DCB_DEMCR_VC_CORERESET_Pos*/)        /*!< DCB DEMCR: Vector Catch Core reset Mask */

/** \brief DCB Debug Set Clear Exception and Monitor Control Register Definitions */
#define DCB_DSCEMCR_CLR_MON_REQ_Pos        19U                                            /*!< DCB DSCEMCR: Clear monitor request Position */
#define DCB_DSCEMCR_CLR_MON_REQ_Msk        (1UL << DCB_DSCEMCR_CLR_MON_REQ_Pos)           /*!< DCB DSCEMCR: Clear monitor request Mask */

#define DCB_DSCEMCR_CLR_MON_PEND_Pos       17U                                            /*!< DCB DSCEMCR: Clear monitor pend Position */
#define DCB_DSCEMCR_CLR_MON_PEND_Msk       (1UL << DCB_DSCEMCR_CLR_MON_PEND_Pos)          /*!< DCB DSCEMCR: Clear monitor pend Mask */

#define DCB_DSCEMCR_SET_MON_REQ_Pos         3U                                            /*!< DCB DSCEMCR: Set monitor request Position */
#define DCB_DSCEMCR_SET_MON_REQ_Msk        (1UL << DCB_DSCEMCR_SET_MON_REQ_Pos)           /*!< DCB DSCEMCR: Set monitor request Mask */

#define DCB_DSCEMCR_SET_MON_PEND_Pos        1U                                            /*!< DCB DSCEMCR: Set monitor pend Position */
#define DCB_DSCEMCR_SET_MON_PEND_Msk       (1UL << DCB_DSCEMCR_SET_MON_PEND_Pos)          /*!< DCB DSCEMCR: Set monitor pend Mask */

/** \brief DCB Debug Authentication Control Register Definitions */
#define DCB_DAUTHCTRL_UIDEN_Pos            10U                                            /*!< DCB DAUTHCTRL: Unprivileged Invasive Debug Enable Position */
#define DCB_DAUTHCTRL_UIDEN_Msk            (1UL << DCB_DAUTHCTRL_UIDEN_Pos)               /*!< DCB DAUTHCTRL: Unprivileged Invasive Debug Enable Mask */

#define DCB_DAUTHCTRL_UIDAPEN_Pos           9U                                            /*!< DCB DAUTHCTRL: Unprivileged Invasive DAP Access Enable Position */
#define DCB_DAUTHCTRL_UIDAPEN_Msk          (1UL << DCB_DAUTHCTRL_UIDAPEN_Pos)             /*!< DCB DAUTHCTRL: Unprivileged Invasive DAP Access Enable Mask */

#define DCB_DAUTHCTRL_FSDMA_Pos             8U                                            /*!< DCB DAUTHCTRL: Force Secure DebugMonitor Allowed Position */
#define DCB_DAUTHCTRL_FSDMA_Msk            (1UL << DCB_DAUTHCTRL_FSDMA_Pos)               /*!< DCB DAUTHCTRL: Force Secure DebugMonitor Allowed Mask */

#define DCB_DAUTHCTRL_INTSPNIDEN_Pos        3U                                            /*!< DCB DAUTHCTRL: Internal Secure non-invasive debug enable Position */
#define DCB_DAUTHCTRL_INTSPNIDEN_Msk       (1UL << DCB_DAUTHCTRL_INTSPNIDEN_Pos)          /*!< DCB DAUTHCTRL: Internal Secure non-invasive debug enable Mask */

#define DCB_DAUTHCTRL_SPNIDENSEL_Pos        2U                                            /*!< DCB DAUTHCTRL: Secure non-invasive debug enable select Position */
#define DCB_DAUTHCTRL_SPNIDENSEL_Msk       (1UL << DCB_DAUTHCTRL_SPNIDENSEL_Pos)          /*!< DCB DAUTHCTRL: Secure non-invasive debug enable select Mask */

#define DCB_DAUTHCTRL_INTSPIDEN_Pos         1U                                            /*!< DCB DAUTHCTRL: Internal Secure invasive debug enable Position */
#define DCB_DAUTHCTRL_INTSPIDEN_Msk        (1UL << DCB_DAUTHCTRL_INTSPIDEN_Pos)           /*!< DCB DAUTHCTRL: Internal Secure invasive debug enable Mask */

#define DCB_DAUTHCTRL_SPIDENSEL_Pos         0U                                            /*!< DCB DAUTHCTRL: Secure invasive debug enable select Position */
#define DCB_DAUTHCTRL_SPIDENSEL_Msk        (1UL /*<< DCB_DAUTHCTRL_SPIDENSEL_Pos*/)       /*!< DCB DAUTHCTRL: Secure invasive debug enable select Mask */

/** \brief DCB Debug Security Control and Status Register Definitions */
#define DCB_DSCSR_CDSKEY_Pos               17U                                            /*!< DCB DSCSR: CDS write-enable key Position */
#define DCB_DSCSR_CDSKEY_Msk               (1UL << DCB_DSCSR_CDSKEY_Pos)                  /*!< DCB DSCSR: CDS write-enable key Mask */

#define DCB_DSCSR_CDS_Pos                  16U                                            /*!< DCB DSCSR: Current domain Secure Position */
#define DCB_DSCSR_CDS_Msk                  (1UL << DCB_DSCSR_CDS_Pos)                     /*!< DCB DSCSR: Current domain Secure Mask */

#define DCB_DSCSR_SBRSEL_Pos                1U                                            /*!< DCB DSCSR: Secure banked register select Position */
#define DCB_DSCSR_SBRSEL_Msk               (1UL << DCB_DSCSR_SBRSEL_Pos)                  /*!< DCB DSCSR: Secure banked register select Mask */

#define DCB_DSCSR_SBRSELEN_Pos              0U                                            /*!< DCB DSCSR: Secure banked register select enable Position */
#define DCB_DSCSR_SBRSELEN_Msk             (1UL /*<< DCB_DSCSR_SBRSELEN_Pos*/)            /*!< DCB DSCSR: Secure banked register select enable Mask */

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_DWT     Data Watchpoint and Trace (DWT)
  \brief    Type definitions for the Data Watchpoint and Trace (DWT)
  @{
 */

/**
  \brief  Structure type to access the Data Watchpoint and Trace Register (DWT).
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  Control Register */
  __IOM uint32_t CYCCNT;                 /*!< Offset: 0x004 (R/W)  Cycle Count Register */
  __IOM uint32_t CPICNT;                 /*!< Offset: 0x008 (R/W)  CPI Count Register */
  __IOM uint32_t EXCCNT;                 /*!< Offset: 0x00C (R/W)  Exception Overhead Count Register */
  __IOM uint32_t SLEEPCNT;               /*!< Offset: 0x010 (R/W)  Sleep Count Register */
  __IOM uint32_t LSUCNT;                 /*!< Offset: 0x014 (R/W)  LSU Count Register */
  __IOM uint32_t FOLDCNT;                /*!< Offset: 0x018 (R/W)  Folded-instruction Count Register */
  __IM  uint32_t PCSR;                   /*!< Offset: 0x01C (R/ )  Program Counter Sample Register */
  __IOM uint32_t COMP0;                  /*!< Offset: 0x020 (R/W)  Comparator Register 0 */
        uint32_t RESERVED1[1U];
  __IOM uint32_t FUNCTION0;              /*!< Offset: 0x028 (R/W)  Function Register 0 */
        uint32_t RESERVED2[1U];
  __IOM uint32_t COMP1;                  /*!< Offset: 0x030 (R/W)  Comparator Register 1 */
        uint32_t RESERVED3[1U];
  __IOM uint32_t FUNCTION1;              /*!< Offset: 0x038 (R/W)  Function Register 1 */
        uint32_t RESERVED4[1U];
  __IOM uint32_t COMP2;                  /*!< Offset: 0x040 (R/W)  Comparator Register 2 */
        uint32_t RESERVED5[1U];
  __IOM uint32_t FUNCTION2;              /*!< Offset: 0x048 (R/W)  Function Register 2 */
        uint32_t RESERVED6[1U];
  __IOM uint32_t COMP3;                  /*!< Offset: 0x050 (R/W)  Comparator Register 3 */
        uint32_t RESERVED7[1U];
  __IOM uint32_t FUNCTION3;              /*!< Offset: 0x058 (R/W)  Function Register 3 */
        uint32_t RESERVED8[1U];
  __IOM uint32_t COMP4;                  /*!< Offset: 0x060 (R/W)  Comparator Register 4 */
        uint32_t RESERVED9[1U];
  __IOM uint32_t FUNCTION4;              /*!< Offset: 0x068 (R/W)  Function Register 4 */
        uint32_t RESERVED10[1U];
  __IOM uint32_t COMP5;                  /*!< Offset: 0x070 (R/W)  Comparator Register 5 */
        uint32_t RESERVED11[1U];
  __IOM uint32_t FUNCTION5;              /*!< Offset: 0x078 (R/W)  Function Register 5 */
        uint32_t RESERVED12[1U];
  __IOM uint32_t COMP6;                  /*!< Offset: 0x080 (R/W)  Comparator Register 6 */
        uint32_t RESERVED13[1U];
  __IOM uint32_t FUNCTION6;              /*!< Offset: 0x088 (R/W)  Function Register 6 */
        uint32_t RESERVED14[1U];
  __IOM uint32_t COMP7;                  /*!< Offset: 0x090 (R/W)  Comparator Register 7 */
        uint32_t RESERVED15[1U];
  __IOM uint32_t FUNCTION7;              /*!< Offset: 0x098 (R/W)  Function Register 7 */
        uint32_t RESERVED16[1U];
  __IOM uint32_t COMP8;                  /*!< Offset: 0x0A0 (R/W)  Comparator Register 8 */
        uint32_t RESERVED17[1U];
  __IOM uint32_t FUNCTION8;              /*!< Offset: 0x0A8 (R/W)  Function Register 8 */
        uint32_t RESERVED18[1U];
  __IOM uint32_t COMP9;                  /*!< Offset: 0x0B0 (R/W)  Comparator Register 9 */
        uint32_t RESERVED19[1U];
  __IOM uint32_t FUNCTION9;              /*!< Offset: 0x0B8 (R/W)  Function Register 9 */
        uint32_t RESERVED20[1U];
  __IOM uint32_t COMP10;                 /*!< Offset: 0x0C0 (R/W)  Comparator Register 10 */
        uint32_t RESERVED21[1U];
  __IOM uint32_t FUNCTION10;             /*!< Offset: 0x0C8 (R/W)  Function Register 10 */
        uint32_t RESERVED22[1U];
  __IOM uint32_t COMP11;                 /*!< Offset: 0x0D0 (R/W)  Comparator Register 11 */
        uint32_t RESERVED23[1U];
  __IOM uint32_t FUNCTION11;             /*!< Offset: 0x0D8 (R/W)  Function Register 11 */
        uint32_t RESERVED24[1U];
  __IOM uint32_t COMP12;                 /*!< Offset: 0x0E0 (R/W)  Comparator Register 12 */
        uint32_t RESERVED25[1U];
  __IOM uint32_t FUNCTION12;             /*!< Offset: 0x0E8 (R/W)  Function Register 12 */
        uint32_t RESERVED26[1U];
  __IOM uint32_t COMP13;                 /*!< Offset: 0x0F0 (R/W)  Comparator Register 13 */
        uint32_t RESERVED27[1U];
  __IOM uint32_t FUNCTION13;             /*!< Offset: 0x0F8 (R/W)  Function Register 13 */
        uint32_t RESERVED28[1U];
  __IOM uint32_t COMP14;                 /*!< Offset: 0x100 (R/W)  Comparator Register 14 */
        uint32_t RESERVED29[1U];
  __IOM uint32_t FUNCTION14;             /*!< Offset: 0x108 (R/W)  Function Register 14 */
        uint32_t RESERVED30[1U];
  __IOM uint32_t COMP15;                 /*!< Offset: 0x110 (R/W)  Comparator Register 15 */
        uint32_t RESERVED31[1U];
  __IOM uint32_t FUNCTION15;             /*!< Offset: 0x118 (R/W)  Function Register 15 */
        uint32_t RESERVED32[934U];
  __IM  uint32_t LSR;                    /*!< Offset: 0xFB4 (R  )  Lock Status Register */
        uint32_t RESERVED33[1U];
  __IM  uint32_t DEVARCH;                /*!< Offset: 0xFBC (R/ )  Device Architecture Register */
} DWT_Type;

/* DWT Control Register Definitions */
#define DWT_CTRL_NUMCOMP_Pos               28U                                         /*!< DWT CTRL: NUMCOMP Position */
#define DWT_CTRL_NUMCOMP_Msk               (0xFUL << DWT_CTRL_NUMCOMP_Pos)             /*!< DWT CTRL: NUMCOMP Mask */

#define DWT_CTRL_NOTRCPKT_Pos              27U                                         /*!< DWT CTRL: NOTRCPKT Position */
#define DWT_CTRL_NOTRCPKT_Msk              (0x1UL << DWT_CTRL_NOTRCPKT_Pos)            /*!< DWT CTRL: NOTRCPKT Mask */

#define DWT_CTRL_NOEXTTRIG_Pos             26U                                         /*!< DWT CTRL: NOEXTTRIG Position */
#define DWT_CTRL_NOEXTTRIG_Msk             (0x1UL << DWT_CTRL_NOEXTTRIG_Pos)           /*!< DWT CTRL: NOEXTTRIG Mask */

#define DWT_CTRL_NOCYCCNT_Pos              25U                                         /*!< DWT CTRL: NOCYCCNT Position */
#define DWT_CTRL_NOCYCCNT_Msk              (0x1UL << DWT_CTRL_NOCYCCNT_Pos)            /*!< DWT CTRL: NOCYCCNT Mask */

#define DWT_CTRL_NOPRFCNT_Pos              24U                                         /*!< DWT CTRL: NOPRFCNT Position */
#define DWT_CTRL_NOPRFCNT_Msk              (0x1UL << DWT_CTRL_NOPRFCNT_Pos)            /*!< DWT CTRL: NOPRFCNT Mask */

#define DWT_CTRL_CYCDISS_Pos               23U                                         /*!< DWT CTRL: CYCDISS Position */
#define DWT_CTRL_CYCDISS_Msk               (0x1UL << DWT_CTRL_CYCDISS_Pos)             /*!< DWT CTRL: CYCDISS Mask */

#define DWT_CTRL_CYCEVTENA_Pos             22U                                         /*!< DWT CTRL: CYCEVTENA Position */
#define DWT_CTRL_CYCEVTENA_Msk             (0x1UL << DWT_CTRL_CYCEVTENA_Pos)           /*!< DWT CTRL: CYCEVTENA Mask */

#define DWT_CTRL_FOLDEVTENA_Pos            21U                                         /*!< DWT CTRL: FOLDEVTENA Position */
#define DWT_CTRL_FOLDEVTENA_Msk            (0x1UL << DWT_CTRL_FOLDEVTENA_Pos)          /*!< DWT CTRL: FOLDEVTENA Mask */

#define DWT_CTRL_LSUEVTENA_Pos             20U                                         /*!< DWT CTRL: LSUEVTENA Position */
#define DWT_CTRL_LSUEVTENA_Msk             (0x1UL << DWT_CTRL_LSUEVTENA_Pos)           /*!< DWT CTRL: LSUEVTENA Mask */

#define DWT_CTRL_SLEEPEVTENA_Pos           19U                                         /*!< DWT CTRL: SLEEPEVTENA Position */
#define DWT_CTRL_SLEEPEVTENA_Msk           (0x1UL << DWT_CTRL_SLEEPEVTENA_Pos)         /*!< DWT CTRL: SLEEPEVTENA Mask */

#define DWT_CTRL_EXCEVTENA_Pos             18U                                         /*!< DWT CTRL: EXCEVTENA Position */
#define DWT_CTRL_EXCEVTENA_Msk             (0x1UL << DWT_CTRL_EXCEVTENA_Pos)           /*!< DWT CTRL: EXCEVTENA Mask */

#define DWT_CTRL_CPIEVTENA_Pos             17U                                         /*!< DWT CTRL: CPIEVTENA Position */
#define DWT_CTRL_CPIEVTENA_Msk             (0x1UL << DWT_CTRL_CPIEVTENA_Pos)           /*!< DWT CTRL: CPIEVTENA Mask */

#define DWT_CTRL_EXCTRCENA_Pos             16U                                         /*!< DWT CTRL: EXCTRCENA Position */
#define DWT_CTRL_EXCTRCENA_Msk             (0x1UL << DWT_CTRL_EXCTRCENA_Pos)           /*!< DWT CTRL: EXCTRCENA Mask */

#define DWT_CTRL_PCSAMPLENA_Pos            12U                                         /*!< DWT CTRL: PCSAMPLENA Position */
#define DWT_CTRL_PCSAMPLENA_Msk            (0x1UL << DWT_CTRL_PCSAMPLENA_Pos)          /*!< DWT CTRL: PCSAMPLENA Mask */

#define DWT_CTRL_SYNCTAP_Pos               10U                                         /*!< DWT CTRL: SYNCTAP Position */
#define DWT_CTRL_SYNCTAP_Msk               (0x3UL << DWT_CTRL_SYNCTAP_Pos)             /*!< DWT CTRL: SYNCTAP Mask */

#define DWT_CTRL_CYCTAP_Pos                 9U                                         /*!< DWT CTRL: CYCTAP Position */
#define DWT_CTRL_CYCTAP_Msk                (0x1UL << DWT_CTRL_CYCTAP_Pos)              /*!< DWT CTRL: CYCTAP Mask */

#define DWT_CTRL_POSTINIT_Pos               5U                                         /*!< DWT CTRL: POSTINIT Position */
#define DWT_CTRL_POSTINIT_Msk              (0xFUL << DWT_CTRL_POSTINIT_Pos)            /*!< DWT CTRL: POSTINIT Mask */

#define DWT_CTRL_POSTPRESET_Pos             1U                                         /*!< DWT CTRL: POSTPRESET Position */
#define DWT_CTRL_POSTPRESET_Msk            (0xFUL << DWT_CTRL_POSTPRESET_Pos)          /*!< DWT CTRL: POSTPRESET Mask */

#define DWT_CTRL_CYCCNTENA_Pos              0U                                         /*!< DWT CTRL: CYCCNTENA Position */
#define DWT_CTRL_CYCCNTENA_Msk             (0x1UL /*<< DWT_CTRL_CYCCNTENA_Pos*/)       /*!< DWT CTRL: CYCCNTENA Mask */

/* DWT CPI Count Register Definitions */
#define DWT_CPICNT_CPICNT_Pos               0U                                         /*!< DWT CPICNT: CPICNT Position */
#define DWT_CPICNT_CPICNT_Msk              (0xFFUL /*<< DWT_CPICNT_CPICNT_Pos*/)       /*!< DWT CPICNT: CPICNT Mask */

/* DWT Exception Overhead Count Register Definitions */
#define DWT_EXCCNT_EXCCNT_Pos               0U                                         /*!< DWT EXCCNT: EXCCNT Position */
#define DWT_EXCCNT_EXCCNT_Msk              (0xFFUL /*<< DWT_EXCCNT_EXCCNT_Pos*/)       /*!< DWT EXCCNT: EXCCNT Mask */

/* DWT Sleep Count Register Definitions */
#define DWT_SLEEPCNT_SLEEPCNT_Pos           0U                                         /*!< DWT SLEEPCNT: SLEEPCNT Position */
#define DWT_SLEEPCNT_SLEEPCNT_Msk          (0xFFUL /*<< DWT_SLEEPCNT_SLEEPCNT_Pos*/)   /*!< DWT SLEEPCNT: SLEEPCNT Mask */

/* DWT LSU Count Register Definitions */
#define DWT_LSUCNT_LSUCNT_Pos               0U                                         /*!< DWT LSUCNT: LSUCNT Position */
#define DWT_LSUCNT_LSUCNT_Msk              (0xFFUL /*<< DWT_LSUCNT_LSUCNT_Pos*/)       /*!< DWT LSUCNT: LSUCNT Mask */

/* DWT Folded-instruction Count Register Definitions */
#define DWT_FOLDCNT_FOLDCNT_Pos             0U                                         /*!< DWT FOLDCNT: FOLDCNT Position */
#define DWT_FOLDCNT_FOLDCNT_Msk            (0xFFUL /*<< DWT_FOLDCNT_FOLDCNT_Pos*/)     /*!< DWT FOLDCNT: FOLDCNT Mask */

/* DWT Comparator Function Register Definitions */
#define DWT_FUNCTION_ID_Pos                27U                                         /*!< DWT FUNCTION: ID Position */
#define DWT_FUNCTION_ID_Msk                (0x1FUL << DWT_FUNCTION_ID_Pos)             /*!< DWT FUNCTION: ID Mask */

#define DWT_FUNCTION_MATCHED_Pos           24U                                         /*!< DWT FUNCTION: MATCHED Position */
#define DWT_FUNCTION_MATCHED_Msk           (0x1UL << DWT_FUNCTION_MATCHED_Pos)         /*!< DWT FUNCTION: MATCHED Mask */

#define DWT_FUNCTION_DATAVSIZE_Pos         10U                                         /*!< DWT FUNCTION: DATAVSIZE Position */
#define DWT_FUNCTION_DATAVSIZE_Msk         (0x3UL << DWT_FUNCTION_DATAVSIZE_Pos)       /*!< DWT FUNCTION: DATAVSIZE Mask */

#define DWT_FUNCTION_ACTION_Pos             4U                                         /*!< DWT FUNCTION: ACTION Position */
#define DWT_FUNCTION_ACTION_Msk            (0x1UL << DWT_FUNCTION_ACTION_Pos)          /*!< DWT FUNCTION: ACTION Mask */

#define DWT_FUNCTION_MATCH_Pos              0U                                         /*!< DWT FUNCTION: MATCH Position */
#define DWT_FUNCTION_MATCH_Msk             (0xFUL /*<< DWT_FUNCTION_MATCH_Pos*/)       /*!< DWT FUNCTION: MATCH Mask */

/*@}*/ /* end of group CMSIS_DWT */


/** \brief SCB Debug Fault Status Register Definitions */
#define SCB_DFSR_PMU_Pos                    5U                                            /*!< SCB DFSR: PMU Position */
#define SCB_DFSR_PMU_Msk                   (1UL << SCB_DFSR_PMU_Pos)                      /*!< SCB DFSR: PMU Mask */

#endif


#if !defined(__PMU_PRESENT) || (0 == __PMU_PRESENT)
/** \brief PMU Event Counter Registers (0-30) Definitions  */
#define PMU_EVCNTR_CNT_Pos                    0U                                           /*!< PMU EVCNTR: Counter Position */
#define PMU_EVCNTR_CNT_Msk                   (0xFFFFUL /*<< PMU_EVCNTRx_CNT_Pos*/)         /*!< PMU EVCNTR: Counter Mask */

/** \brief PMU Event Type and Filter Registers (0-30) Definitions  */
#define PMU_EVTYPER_EVENTTOCNT_Pos            0U                                           /*!< PMU EVTYPER: Event to Count Position */
#define PMU_EVTYPER_EVENTTOCNT_Msk           (0xFFFFUL /*<< EVTYPERx_EVENTTOCNT_Pos*/)     /*!< PMU EVTYPER: Event to Count Mask */

/** \brief PMU Count Enable Set Register Definitions */
#define PMU_CNTENSET_CNT0_ENABLE_Pos          0U                                           /*!< PMU CNTENSET: Event Counter 0 Enable Set Position */
#define PMU_CNTENSET_CNT0_ENABLE_Msk         (1UL /*<< PMU_CNTENSET_CNT0_ENABLE_Pos*/)     /*!< PMU CNTENSET: Event Counter 0 Enable Set Mask */

#define PMU_CNTENSET_CNT1_ENABLE_Pos          1U                                           /*!< PMU CNTENSET: Event Counter 1 Enable Set Position */
#define PMU_CNTENSET_CNT1_ENABLE_Msk         (1UL << PMU_CNTENSET_CNT1_ENABLE_Pos)         /*!< PMU CNTENSET: Event Counter 1 Enable Set Mask */

#define PMU_CNTENSET_CNT2_ENABLE_Pos          2U                                           /*!< PMU CNTENSET: Event Counter 2 Enable Set Position */
#define PMU_CNTENSET_CNT2_ENABLE_Msk         (1UL << PMU_CNTENSET_CNT2_ENABLE_Pos)         /*!< PMU CNTENSET: Event Counter 2 Enable Set Mask */

#define PMU_CNTENSET_CNT3_ENABLE_Pos          3U                                           /*!< PMU CNTENSET: Event Counter 3 Enable Set Position */
#define PMU_CNTENSET_CNT3_ENABLE_Msk         (1UL << PMU_CNTENSET_CNT3_ENABLE_Pos)         /*!< PMU CNTENSET: Event Counter 3 Enable Set Mask */

#define PMU_CNTENSET_CNT4_ENABLE_Pos          4U                                           /*!< PMU CNTENSET: Event Counter 4 Enable Set Position */
#define PMU_CNTENSET_CNT4_ENABLE_Msk         (1UL << PMU_CNTENSET_CNT4_ENABLE_Pos)         /*!< PMU CNTENSET: Event Counter 4 Enable Set Mask */

#define PMU_CNTENSET_CNT5_ENABLE_Pos          5U                                           /*!< PMU CNTENSET: Event Counter 5 Enable Set Position */
#define PMU_CNTENSET_CNT5_ENABLE_Msk         (1UL << PMU_CNTENSET_CNT5_ENABLE_Pos)         /*!< PMU CNTENSET: Event Counter 5 Enable Set Mask */

#define PMU_CNTENSET_CNT6_ENABLE_Pos          6U                                           /*!< PMU CNTENSET: Event Counter 6 Enable Set Position */
#define PMU_CNTENSET_CNT6_ENABLE_Msk         (1UL << PMU_CNTENSET_CNT6_ENABLE_Pos)         /*!< PMU CNTENSET: Event Counter 6 Enable Set Mask */

#define PMU_CNTENSET_CNT7_ENABLE_Pos          7U                                           /*!< PMU CNTENSET: Event Counter 7 Enable Set Position */
#define PMU_CNTENSET_CNT7_ENABLE_Msk         (1UL << PMU_CNTENSET_CNT7_ENABLE_Pos)         /*!< PMU CNTENSET: Event Counter 7 Enable Set Mask */

#define PMU_CNTENSET_CNT8_ENABLE_Pos          8U                                           /*!< PMU CNTENSET: Event Counter 8 Enable Set Position */
#define PMU_CNTENSET_CNT8_ENABLE_Msk         (1UL << PMU_CNTENSET_CNT8_ENABLE_Pos)         /*!< PMU CNTENSET: Event Counter 8 Enable Set Mask */

#define PMU_CNTENSET_CNT9_ENABLE_Pos          9U                                           /*!< PMU CNTENSET: Event Counter 9 Enable Set Position */
#define PMU_CNTENSET_CNT9_ENABLE_Msk         (1UL << PMU_CNTENSET_CNT9_ENABLE_Pos)         /*!< PMU CNTENSET: Event Counter 9 Enable Set Mask */

#define PMU_CNTENSET_CNT10_ENABLE_Pos         10U                                          /*!< PMU CNTENSET: Event Counter 10 Enable Set Position */
#define PMU_CNTENSET_CNT10_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT10_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 10 Enable Set Mask */

#define PMU_CNTENSET_CNT11_ENABLE_Pos         11U                                          /*!< PMU CNTENSET: Event Counter 11 Enable Set Position */
#define PMU_CNTENSET_CNT11_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT11_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 11 Enable Set Mask */

#define PMU_CNTENSET_CNT12_ENABLE_Pos         12U                                          /*!< PMU CNTENSET: Event Counter 12 Enable Set Position */
#define PMU_CNTENSET_CNT12_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT12_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 12 Enable Set Mask */

#define PMU_CNTENSET_CNT13_ENABLE_Pos         13U                                          /*!< PMU CNTENSET: Event Counter 13 Enable Set Position */
#define PMU_CNTENSET_CNT13_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT13_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 13 Enable Set Mask */

#define PMU_CNTENSET_CNT14_ENABLE_Pos         14U                                          /*!< PMU CNTENSET: Event Counter 14 Enable Set Position */
#define PMU_CNTENSET_CNT14_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT14_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 14 Enable Set Mask */

#define PMU_CNTENSET_CNT15_ENABLE_Pos         15U                                          /*!< PMU CNTENSET: Event Counter 15 Enable Set Position */
#define PMU_CNTENSET_CNT15_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT15_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 15 Enable Set Mask */

#define PMU_CNTENSET_CNT16_ENABLE_Pos         16U                                          /*!< PMU CNTENSET: Event Counter 16 Enable Set Position */
#define PMU_CNTENSET_CNT16_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT16_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 16 Enable Set Mask */

#define PMU_CNTENSET_CNT17_ENABLE_Pos         17U                                          /*!< PMU CNTENSET: Event Counter 17 Enable Set Position */
#define PMU_CNTENSET_CNT17_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT17_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 17 Enable Set Mask */

#define PMU_CNTENSET_CNT18_ENABLE_Pos         18U                                          /*!< PMU CNTENSET: Event Counter 18 Enable Set Position */
#define PMU_CNTENSET_CNT18_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT18_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 18 Enable Set Mask */

#define PMU_CNTENSET_CNT19_ENABLE_Pos         19U                                          /*!< PMU CNTENSET: Event Counter 19 Enable Set Position */
#define PMU_CNTENSET_CNT19_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT19_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 19 Enable Set Mask */

#define PMU_CNTENSET_CNT20_ENABLE_Pos         20U                                          /*!< PMU CNTENSET: Event Counter 20 Enable Set Position */
#define PMU_CNTENSET_CNT20_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT20_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 20 Enable Set Mask */

#define PMU_CNTENSET_CNT21_ENABLE_Pos         21U                                          /*!< PMU CNTENSET: Event Counter 21 Enable Set Position */
#define PMU_CNTENSET_CNT21_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT21_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 21 Enable Set Mask */

#define PMU_CNTENSET_CNT22_ENABLE_Pos         22U                                          /*!< PMU CNTENSET: Event Counter 22 Enable Set Position */
#define PMU_CNTENSET_CNT22_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT22_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 22 Enable Set Mask */

#define PMU_CNTENSET_CNT23_ENABLE_Pos         23U                                          /*!< PMU CNTENSET: Event Counter 23 Enable Set Position */
#define PMU_CNTENSET_CNT23_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT23_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 23 Enable Set Mask */

#define PMU_CNTENSET_CNT24_ENABLE_Pos         24U                                          /*!< PMU CNTENSET: Event Counter 24 Enable Set Position */
#define PMU_CNTENSET_CNT24_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT24_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 24 Enable Set Mask */

#define PMU_CNTENSET_CNT25_ENABLE_Pos         25U                                          /*!< PMU CNTENSET: Event Counter 25 Enable Set Position */
#define PMU_CNTENSET_CNT25_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT25_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 25 Enable Set Mask */

#define PMU_CNTENSET_CNT26_ENABLE_Pos         26U                                          /*!< PMU CNTENSET: Event Counter 26 Enable Set Position */
#define PMU_CNTENSET_CNT26_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT26_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 26 Enable Set Mask */

#define PMU_CNTENSET_CNT27_ENABLE_Pos         27U                                          /*!< PMU CNTENSET: Event Counter 27 Enable Set Position */
#define PMU_CNTENSET_CNT27_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT27_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 27 Enable Set Mask */

#define PMU_CNTENSET_CNT28_ENABLE_Pos         28U                                          /*!< PMU CNTENSET: Event Counter 28 Enable Set Position */
#define PMU_CNTENSET_CNT28_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT28_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 28 Enable Set Mask */

#define PMU_CNTENSET_CNT29_ENABLE_Pos         29U                                          /*!< PMU CNTENSET: Event Counter 29 Enable Set Position */
#define PMU_CNTENSET_CNT29_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT29_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 29 Enable Set Mask */

#define PMU_CNTENSET_CNT30_ENABLE_Pos         30U                                          /*!< PMU CNTENSET: Event Counter 30 Enable Set Position */
#define PMU_CNTENSET_CNT30_ENABLE_Msk        (1UL << PMU_CNTENSET_CNT30_ENABLE_Pos)        /*!< PMU CNTENSET: Event Counter 30 Enable Set Mask */

#define PMU_CNTENSET_CCNTR_ENABLE_Pos         31U                                          /*!< PMU CNTENSET: Cycle Counter Enable Set Position */
#define PMU_CNTENSET_CCNTR_ENABLE_Msk        (1UL << PMU_CNTENSET_CCNTR_ENABLE_Pos)        /*!< PMU CNTENSET: Cycle Counter Enable Set Mask */

/** \brief PMU Count Enable Clear Register Definitions */
#define PMU_CNTENSET_CNT0_ENABLE_Pos          0U                                           /*!< PMU CNTENCLR: Event Counter 0 Enable Clear Position */
#define PMU_CNTENCLR_CNT0_ENABLE_Msk         (1UL /*<< PMU_CNTENCLR_CNT0_ENABLE_Pos*/)     /*!< PMU CNTENCLR: Event Counter 0 Enable Clear Mask */

#define PMU_CNTENCLR_CNT1_ENABLE_Pos          1U                                           /*!< PMU CNTENCLR: Event Counter 1 Enable Clear Position */
#define PMU_CNTENCLR_CNT1_ENABLE_Msk         (1UL << PMU_CNTENCLR_CNT1_ENABLE_Pos)         /*!< PMU CNTENCLR: Event Counter 1 Enable Clear */

#define PMU_CNTENCLR_CNT2_ENABLE_Pos          2U                                           /*!< PMU CNTENCLR: Event Counter 2 Enable Clear Position */
#define PMU_CNTENCLR_CNT2_ENABLE_Msk         (1UL << PMU_CNTENCLR_CNT2_ENABLE_Pos)         /*!< PMU CNTENCLR: Event Counter 2 Enable Clear Mask */

#define PMU_CNTENCLR_CNT3_ENABLE_Pos          3U                                           /*!< PMU CNTENCLR: Event Counter 3 Enable Clear Position */
#define PMU_CNTENCLR_CNT3_ENABLE_Msk         (1UL << PMU_CNTENCLR_CNT3_ENABLE_Pos)         /*!< PMU CNTENCLR: Event Counter 3 Enable Clear Mask */

#define PMU_CNTENCLR_CNT4_ENABLE_Pos          4U                                           /*!< PMU CNTENCLR: Event Counter 4 Enable Clear Position */
#define PMU_CNTENCLR_CNT4_ENABLE_Msk         (1UL << PMU_CNTENCLR_CNT4_ENABLE_Pos)         /*!< PMU CNTENCLR: Event Counter 4 Enable Clear Mask */

#define PMU_CNTENCLR_CNT5_ENABLE_Pos          5U                                           /*!< PMU CNTENCLR: Event Counter 5 Enable Clear Position */
#define PMU_CNTENCLR_CNT5_ENABLE_Msk         (1UL << PMU_CNTENCLR_CNT5_ENABLE_Pos)         /*!< PMU CNTENCLR: Event Counter 5 Enable Clear Mask */

#define PMU_CNTENCLR_CNT6_ENABLE_Pos          6U                                           /*!< PMU CNTENCLR: Event Counter 6 Enable Clear Position */
#define PMU_CNTENCLR_CNT6_ENABLE_Msk         (1UL << PMU_CNTENCLR_CNT6_ENABLE_Pos)         /*!< PMU CNTENCLR: Event Counter 6 Enable Clear Mask */

#define PMU_CNTENCLR_CNT7_ENABLE_Pos          7U                                           /*!< PMU CNTENCLR: Event Counter 7 Enable Clear Position */
#define PMU_CNTENCLR_CNT7_ENABLE_Msk         (1UL << PMU_CNTENCLR_CNT7_ENABLE_Pos)         /*!< PMU CNTENCLR: Event Counter 7 Enable Clear Mask */

#define PMU_CNTENCLR_CNT8_ENABLE_Pos          8U                                           /*!< PMU CNTENCLR: Event Counter 8 Enable Clear Position */
#define PMU_CNTENCLR_CNT8_ENABLE_Msk         (1UL << PMU_CNTENCLR_CNT8_ENABLE_Pos)         /*!< PMU CNTENCLR: Event Counter 8 Enable Clear Mask */

#define PMU_CNTENCLR_CNT9_ENABLE_Pos          9U                                           /*!< PMU CNTENCLR: Event Counter 9 Enable Clear Position */
#define PMU_CNTENCLR_CNT9_ENABLE_Msk         (1UL << PMU_CNTENCLR_CNT9_ENABLE_Pos)         /*!< PMU CNTENCLR: Event Counter 9 Enable Clear Mask */

#define PMU_CNTENCLR_CNT10_ENABLE_Pos         10U                                          /*!< PMU CNTENCLR: Event Counter 10 Enable Clear Position */
#define PMU_CNTENCLR_CNT10_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT10_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 10 Enable Clear Mask */

#define PMU_CNTENCLR_CNT11_ENABLE_Pos         11U                                          /*!< PMU CNTENCLR: Event Counter 11 Enable Clear Position */
#define PMU_CNTENCLR_CNT11_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT11_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 11 Enable Clear Mask */

#define PMU_CNTENCLR_CNT12_ENABLE_Pos         12U                                          /*!< PMU CNTENCLR: Event Counter 12 Enable Clear Position */
#define PMU_CNTENCLR_CNT12_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT12_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 12 Enable Clear Mask */

#define PMU_CNTENCLR_CNT13_ENABLE_Pos         13U                                          /*!< PMU CNTENCLR: Event Counter 13 Enable Clear Position */
#define PMU_CNTENCLR_CNT13_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT13_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 13 Enable Clear Mask */

#define PMU_CNTENCLR_CNT14_ENABLE_Pos         14U                                          /*!< PMU CNTENCLR: Event Counter 14 Enable Clear Position */
#define PMU_CNTENCLR_CNT14_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT14_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 14 Enable Clear Mask */

#define PMU_CNTENCLR_CNT15_ENABLE_Pos         15U                                          /*!< PMU CNTENCLR: Event Counter 15 Enable Clear Position */
#define PMU_CNTENCLR_CNT15_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT15_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 15 Enable Clear Mask */

#define PMU_CNTENCLR_CNT16_ENABLE_Pos         16U                                          /*!< PMU CNTENCLR: Event Counter 16 Enable Clear Position */
#define PMU_CNTENCLR_CNT16_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT16_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 16 Enable Clear Mask */

#define PMU_CNTENCLR_CNT17_ENABLE_Pos         17U                                          /*!< PMU CNTENCLR: Event Counter 17 Enable Clear Position */
#define PMU_CNTENCLR_CNT17_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT17_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 17 Enable Clear Mask */

#define PMU_CNTENCLR_CNT18_ENABLE_Pos         18U                                          /*!< PMU CNTENCLR: Event Counter 18 Enable Clear Position */
#define PMU_CNTENCLR_CNT18_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT18_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 18 Enable Clear Mask */

#define PMU_CNTENCLR_CNT19_ENABLE_Pos         19U                                          /*!< PMU CNTENCLR: Event Counter 19 Enable Clear Position */
#define PMU_CNTENCLR_CNT19_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT19_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 19 Enable Clear Mask */

#define PMU_CNTENCLR_CNT20_ENABLE_Pos         20U                                          /*!< PMU CNTENCLR: Event Counter 20 Enable Clear Position */
#define PMU_CNTENCLR_CNT20_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT20_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 20 Enable Clear Mask */

#define PMU_CNTENCLR_CNT21_ENABLE_Pos         21U                                          /*!< PMU CNTENCLR: Event Counter 21 Enable Clear Position */
#define PMU_CNTENCLR_CNT21_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT21_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 21 Enable Clear Mask */

#define PMU_CNTENCLR_CNT22_ENABLE_Pos         22U                                          /*!< PMU CNTENCLR: Event Counter 22 Enable Clear Position */
#define PMU_CNTENCLR_CNT22_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT22_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 22 Enable Clear Mask */

#define PMU_CNTENCLR_CNT23_ENABLE_Pos         23U                                          /*!< PMU CNTENCLR: Event Counter 23 Enable Clear Position */
#define PMU_CNTENCLR_CNT23_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT23_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 23 Enable Clear Mask */

#define PMU_CNTENCLR_CNT24_ENABLE_Pos         24U                                          /*!< PMU CNTENCLR: Event Counter 24 Enable Clear Position */
#define PMU_CNTENCLR_CNT24_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT24_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 24 Enable Clear Mask */

#define PMU_CNTENCLR_CNT25_ENABLE_Pos         25U                                          /*!< PMU CNTENCLR: Event Counter 25 Enable Clear Position */
#define PMU_CNTENCLR_CNT25_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT25_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 25 Enable Clear Mask */

#define PMU_CNTENCLR_CNT26_ENABLE_Pos         26U                                          /*!< PMU CNTENCLR: Event Counter 26 Enable Clear Position */
#define PMU_CNTENCLR_CNT26_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT26_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 26 Enable Clear Mask */

#define PMU_CNTENCLR_CNT27_ENABLE_Pos         27U                                          /*!< PMU CNTENCLR: Event Counter 27 Enable Clear Position */
#define PMU_CNTENCLR_CNT27_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT27_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 27 Enable Clear Mask */

#define PMU_CNTENCLR_CNT28_ENABLE_Pos         28U                                          /*!< PMU CNTENCLR: Event Counter 28 Enable Clear Position */
#define PMU_CNTENCLR_CNT28_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT28_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 28 Enable Clear Mask */

#define PMU_CNTENCLR_CNT29_ENABLE_Pos         29U                                          /*!< PMU CNTENCLR: Event Counter 29 Enable Clear Position */
#define PMU_CNTENCLR_CNT29_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT29_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 29 Enable Clear Mask */

#define PMU_CNTENCLR_CNT30_ENABLE_Pos         30U                                          /*!< PMU CNTENCLR: Event Counter 30 Enable Clear Position */
#define PMU_CNTENCLR_CNT30_ENABLE_Msk        (1UL << PMU_CNTENCLR_CNT30_ENABLE_Pos)        /*!< PMU CNTENCLR: Event Counter 30 Enable Clear Mask */

#define PMU_CNTENCLR_CCNTR_ENABLE_Pos         31U                                          /*!< PMU CNTENCLR: Cycle Counter Enable Clear Position */
#define PMU_CNTENCLR_CCNTR_ENABLE_Msk        (1UL << PMU_CNTENCLR_CCNTR_ENABLE_Pos)        /*!< PMU CNTENCLR: Cycle Counter Enable Clear Mask */

/** \brief PMU Interrupt Enable Set Register Definitions */
#define PMU_INTENSET_CNT0_ENABLE_Pos          0U                                           /*!< PMU INTENSET: Event Counter 0 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT0_ENABLE_Msk         (1UL /*<< PMU_INTENSET_CNT0_ENABLE_Pos*/)     /*!< PMU INTENSET: Event Counter 0 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT1_ENABLE_Pos          1U                                           /*!< PMU INTENSET: Event Counter 1 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT1_ENABLE_Msk         (1UL << PMU_INTENSET_CNT1_ENABLE_Pos)         /*!< PMU INTENSET: Event Counter 1 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT2_ENABLE_Pos          2U                                           /*!< PMU INTENSET: Event Counter 2 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT2_ENABLE_Msk         (1UL << PMU_INTENSET_CNT2_ENABLE_Pos)         /*!< PMU INTENSET: Event Counter 2 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT3_ENABLE_Pos          3U                                           /*!< PMU INTENSET: Event Counter 3 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT3_ENABLE_Msk         (1UL << PMU_INTENSET_CNT3_ENABLE_Pos)         /*!< PMU INTENSET: Event Counter 3 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT4_ENABLE_Pos          4U                                           /*!< PMU INTENSET: Event Counter 4 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT4_ENABLE_Msk         (1UL << PMU_INTENSET_CNT4_ENABLE_Pos)         /*!< PMU INTENSET: Event Counter 4 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT5_ENABLE_Pos          5U                                           /*!< PMU INTENSET: Event Counter 5 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT5_ENABLE_Msk         (1UL << PMU_INTENSET_CNT5_ENABLE_Pos)         /*!< PMU INTENSET: Event Counter 5 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT6_ENABLE_Pos          6U                                           /*!< PMU INTENSET: Event Counter 6 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT6_ENABLE_Msk         (1UL << PMU_INTENSET_CNT6_ENABLE_Pos)         /*!< PMU INTENSET: Event Counter 6 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT7_ENABLE_Pos          7U                                           /*!< PMU INTENSET: Event Counter 7 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT7_ENABLE_Msk         (1UL << PMU_INTENSET_CNT7_ENABLE_Pos)         /*!< PMU INTENSET: Event Counter 7 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT8_ENABLE_Pos          8U                                           /*!< PMU INTENSET: Event Counter 8 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT8_ENABLE_Msk         (1UL << PMU_INTENSET_CNT8_ENABLE_Pos)         /*!< PMU INTENSET: Event Counter 8 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT9_ENABLE_Pos          9U                                           /*!< PMU INTENSET: Event Counter 9 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT9_ENABLE_Msk         (1UL << PMU_INTENSET_CNT9_ENABLE_Pos)         /*!< PMU INTENSET: Event Counter 9 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT10_ENABLE_Pos         10U                                          /*!< PMU INTENSET: Event Counter 10 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT10_ENABLE_Msk        (1UL << PMU_INTENSET_CNT10_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 10 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT11_ENABLE_Pos         11U                                          /*!< PMU INTENSET: Event Counter 11 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT11_ENABLE_Msk        (1UL << PMU_INTENSET_CNT11_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 11 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT12_ENABLE_Pos         12U                                          /*!< PMU INTENSET: Event Counter 12 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT12_ENABLE_Msk        (1UL << PMU_INTENSET_CNT12_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 12 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT13_ENABLE_Pos         13U                                          /*!< PMU INTENSET: Event Counter 13 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT13_ENABLE_Msk        (1UL << PMU_INTENSET_CNT13_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 13 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT14_ENABLE_Pos         14U                                          /*!< PMU INTENSET: Event Counter 14 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT14_ENABLE_Msk        (1UL << PMU_INTENSET_CNT14_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 14 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT15_ENABLE_Pos         15U                                          /*!< PMU INTENSET: Event Counter 15 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT15_ENABLE_Msk        (1UL << PMU_INTENSET_CNT15_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 15 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT16_ENABLE_Pos         16U                                          /*!< PMU INTENSET: Event Counter 16 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT16_ENABLE_Msk        (1UL << PMU_INTENSET_CNT16_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 16 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT17_ENABLE_Pos         17U                                          /*!< PMU INTENSET: Event Counter 17 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT17_ENABLE_Msk        (1UL << PMU_INTENSET_CNT17_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 17 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT18_ENABLE_Pos         18U                                          /*!< PMU INTENSET: Event Counter 18 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT18_ENABLE_Msk        (1UL << PMU_INTENSET_CNT18_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 18 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT19_ENABLE_Pos         19U                                          /*!< PMU INTENSET: Event Counter 19 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT19_ENABLE_Msk        (1UL << PMU_INTENSET_CNT19_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 19 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT20_ENABLE_Pos         20U                                          /*!< PMU INTENSET: Event Counter 20 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT20_ENABLE_Msk        (1UL << PMU_INTENSET_CNT20_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 20 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT21_ENABLE_Pos         21U                                          /*!< PMU INTENSET: Event Counter 21 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT21_ENABLE_Msk        (1UL << PMU_INTENSET_CNT21_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 21 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT22_ENABLE_Pos         22U                                          /*!< PMU INTENSET: Event Counter 22 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT22_ENABLE_Msk        (1UL << PMU_INTENSET_CNT22_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 22 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT23_ENABLE_Pos         23U                                          /*!< PMU INTENSET: Event Counter 23 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT23_ENABLE_Msk        (1UL << PMU_INTENSET_CNT23_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 23 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT24_ENABLE_Pos         24U                                          /*!< PMU INTENSET: Event Counter 24 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT24_ENABLE_Msk        (1UL << PMU_INTENSET_CNT24_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 24 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT25_ENABLE_Pos         25U                                          /*!< PMU INTENSET: Event Counter 25 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT25_ENABLE_Msk        (1UL << PMU_INTENSET_CNT25_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 25 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT26_ENABLE_Pos         26U                                          /*!< PMU INTENSET: Event Counter 26 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT26_ENABLE_Msk        (1UL << PMU_INTENSET_CNT26_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 26 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT27_ENABLE_Pos         27U                                          /*!< PMU INTENSET: Event Counter 27 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT27_ENABLE_Msk        (1UL << PMU_INTENSET_CNT27_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 27 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT28_ENABLE_Pos         28U                                          /*!< PMU INTENSET: Event Counter 28 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT28_ENABLE_Msk        (1UL << PMU_INTENSET_CNT28_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 28 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT29_ENABLE_Pos         29U                                          /*!< PMU INTENSET: Event Counter 29 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT29_ENABLE_Msk        (1UL << PMU_INTENSET_CNT29_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 29 Interrupt Enable Set Mask */

#define PMU_INTENSET_CNT30_ENABLE_Pos         30U                                          /*!< PMU INTENSET: Event Counter 30 Interrupt Enable Set Position */
#define PMU_INTENSET_CNT30_ENABLE_Msk        (1UL << PMU_INTENSET_CNT30_ENABLE_Pos)        /*!< PMU INTENSET: Event Counter 30 Interrupt Enable Set Mask */

#define PMU_INTENSET_CYCCNT_ENABLE_Pos        31U                                          /*!< PMU INTENSET: Cycle Counter Interrupt Enable Set Position */
#define PMU_INTENSET_CCYCNT_ENABLE_Msk       (1UL << PMU_INTENSET_CYCCNT_ENABLE_Pos)       /*!< PMU INTENSET: Cycle Counter Interrupt Enable Set Mask */

/** \brief PMU Interrupt Enable Clear Register Definitions */
#define PMU_INTENSET_CNT0_ENABLE_Pos          0U                                           /*!< PMU INTENCLR: Event Counter 0 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT0_ENABLE_Msk         (1UL /*<< PMU_INTENCLR_CNT0_ENABLE_Pos*/)     /*!< PMU INTENCLR: Event Counter 0 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT1_ENABLE_Pos          1U                                           /*!< PMU INTENCLR: Event Counter 1 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT1_ENABLE_Msk         (1UL << PMU_INTENCLR_CNT1_ENABLE_Pos)         /*!< PMU INTENCLR: Event Counter 1 Interrupt Enable Clear */

#define PMU_INTENCLR_CNT2_ENABLE_Pos          2U                                           /*!< PMU INTENCLR: Event Counter 2 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT2_ENABLE_Msk         (1UL << PMU_INTENCLR_CNT2_ENABLE_Pos)         /*!< PMU INTENCLR: Event Counter 2 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT3_ENABLE_Pos          3U                                           /*!< PMU INTENCLR: Event Counter 3 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT3_ENABLE_Msk         (1UL << PMU_INTENCLR_CNT3_ENABLE_Pos)         /*!< PMU INTENCLR: Event Counter 3 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT4_ENABLE_Pos          4U                                           /*!< PMU INTENCLR: Event Counter 4 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT4_ENABLE_Msk         (1UL << PMU_INTENCLR_CNT4_ENABLE_Pos)         /*!< PMU INTENCLR: Event Counter 4 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT5_ENABLE_Pos          5U                                           /*!< PMU INTENCLR: Event Counter 5 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT5_ENABLE_Msk         (1UL << PMU_INTENCLR_CNT5_ENABLE_Pos)         /*!< PMU INTENCLR: Event Counter 5 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT6_ENABLE_Pos          6U                                           /*!< PMU INTENCLR: Event Counter 6 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT6_ENABLE_Msk         (1UL << PMU_INTENCLR_CNT6_ENABLE_Pos)         /*!< PMU INTENCLR: Event Counter 6 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT7_ENABLE_Pos          7U                                           /*!< PMU INTENCLR: Event Counter 7 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT7_ENABLE_Msk         (1UL << PMU_INTENCLR_CNT7_ENABLE_Pos)         /*!< PMU INTENCLR: Event Counter 7 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT8_ENABLE_Pos          8U                                           /*!< PMU INTENCLR: Event Counter 8 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT8_ENABLE_Msk         (1UL << PMU_INTENCLR_CNT8_ENABLE_Pos)         /*!< PMU INTENCLR: Event Counter 8 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT9_ENABLE_Pos          9U                                           /*!< PMU INTENCLR: Event Counter 9 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT9_ENABLE_Msk         (1UL << PMU_INTENCLR_CNT9_ENABLE_Pos)         /*!< PMU INTENCLR: Event Counter 9 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT10_ENABLE_Pos         10U                                          /*!< PMU INTENCLR: Event Counter 10 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT10_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT10_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 10 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT11_ENABLE_Pos         11U                                          /*!< PMU INTENCLR: Event Counter 11 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT11_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT11_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 11 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT12_ENABLE_Pos         12U                                          /*!< PMU INTENCLR: Event Counter 12 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT12_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT12_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 12 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT13_ENABLE_Pos         13U                                          /*!< PMU INTENCLR: Event Counter 13 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT13_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT13_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 13 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT14_ENABLE_Pos         14U                                          /*!< PMU INTENCLR: Event Counter 14 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT14_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT14_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 14 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT15_ENABLE_Pos         15U                                          /*!< PMU INTENCLR: Event Counter 15 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT15_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT15_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 15 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT16_ENABLE_Pos         16U                                          /*!< PMU INTENCLR: Event Counter 16 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT16_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT16_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 16 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT17_ENABLE_Pos         17U                                          /*!< PMU INTENCLR: Event Counter 17 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT17_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT17_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 17 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT18_ENABLE_Pos         18U                                          /*!< PMU INTENCLR: Event Counter 18 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT18_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT18_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 18 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT19_ENABLE_Pos         19U                                          /*!< PMU INTENCLR: Event Counter 19 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT19_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT19_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 19 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT20_ENABLE_Pos         20U                                          /*!< PMU INTENCLR: Event Counter 20 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT20_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT20_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 20 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT21_ENABLE_Pos         21U                                          /*!< PMU INTENCLR: Event Counter 21 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT21_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT21_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 21 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT22_ENABLE_Pos         22U                                          /*!< PMU INTENCLR: Event Counter 22 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT22_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT22_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 22 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT23_ENABLE_Pos         23U                                          /*!< PMU INTENCLR: Event Counter 23 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT23_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT23_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 23 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT24_ENABLE_Pos         24U                                          /*!< PMU INTENCLR: Event Counter 24 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT24_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT24_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 24 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT25_ENABLE_Pos         25U                                          /*!< PMU INTENCLR: Event Counter 25 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT25_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT25_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 25 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT26_ENABLE_Pos         26U                                          /*!< PMU INTENCLR: Event Counter 26 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT26_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT26_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 26 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT27_ENABLE_Pos         27U                                          /*!< PMU INTENCLR: Event Counter 27 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT27_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT27_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 27 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT28_ENABLE_Pos         28U                                          /*!< PMU INTENCLR: Event Counter 28 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT28_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT28_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 28 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT29_ENABLE_Pos         29U                                          /*!< PMU INTENCLR: Event Counter 29 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT29_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT29_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 29 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CNT30_ENABLE_Pos         30U                                          /*!< PMU INTENCLR: Event Counter 30 Interrupt Enable Clear Position */
#define PMU_INTENCLR_CNT30_ENABLE_Msk        (1UL << PMU_INTENCLR_CNT30_ENABLE_Pos)        /*!< PMU INTENCLR: Event Counter 30 Interrupt Enable Clear Mask */

#define PMU_INTENCLR_CYCCNT_ENABLE_Pos        31U                                          /*!< PMU INTENCLR: Cycle Counter Interrupt Enable Clear Position */
#define PMU_INTENCLR_CYCCNT_ENABLE_Msk       (1UL << PMU_INTENCLR_CYCCNT_ENABLE_Pos)       /*!< PMU INTENCLR: Cycle Counter Interrupt Enable Clear Mask */

/** \brief PMU Overflow Flag Status Set Register Definitions */
#define PMU_OVSSET_CNT0_STATUS_Pos            0U                                           /*!< PMU OVSSET: Event Counter 0 Overflow Set Position */
#define PMU_OVSSET_CNT0_STATUS_Msk           (1UL /*<< PMU_OVSSET_CNT0_STATUS_Pos*/)       /*!< PMU OVSSET: Event Counter 0 Overflow Set Mask */

#define PMU_OVSSET_CNT1_STATUS_Pos            1U                                           /*!< PMU OVSSET: Event Counter 1 Overflow Set Position */
#define PMU_OVSSET_CNT1_STATUS_Msk           (1UL << PMU_OVSSET_CNT1_STATUS_Pos)           /*!< PMU OVSSET: Event Counter 1 Overflow Set Mask */

#define PMU_OVSSET_CNT2_STATUS_Pos            2U                                           /*!< PMU OVSSET: Event Counter 2 Overflow Set Position */
#define PMU_OVSSET_CNT2_STATUS_Msk           (1UL << PMU_OVSSET_CNT2_STATUS_Pos)           /*!< PMU OVSSET: Event Counter 2 Overflow Set Mask */

#define PMU_OVSSET_CNT3_STATUS_Pos            3U                                           /*!< PMU OVSSET: Event Counter 3 Overflow Set Position */
#define PMU_OVSSET_CNT3_STATUS_Msk           (1UL << PMU_OVSSET_CNT3_STATUS_Pos)           /*!< PMU OVSSET: Event Counter 3 Overflow Set Mask */

#define PMU_OVSSET_CNT4_STATUS_Pos            4U                                           /*!< PMU OVSSET: Event Counter 4 Overflow Set Position */
#define PMU_OVSSET_CNT4_STATUS_Msk           (1UL << PMU_OVSSET_CNT4_STATUS_Pos)           /*!< PMU OVSSET: Event Counter 4 Overflow Set Mask */

#define PMU_OVSSET_CNT5_STATUS_Pos            5U                                           /*!< PMU OVSSET: Event Counter 5 Overflow Set Position */
#define PMU_OVSSET_CNT5_STATUS_Msk           (1UL << PMU_OVSSET_CNT5_STATUS_Pos)           /*!< PMU OVSSET: Event Counter 5 Overflow Set Mask */

#define PMU_OVSSET_CNT6_STATUS_Pos            6U                                           /*!< PMU OVSSET: Event Counter 6 Overflow Set Position */
#define PMU_OVSSET_CNT6_STATUS_Msk           (1UL << PMU_OVSSET_CNT6_STATUS_Pos)           /*!< PMU OVSSET: Event Counter 6 Overflow Set Mask */

#define PMU_OVSSET_CNT7_STATUS_Pos            7U                                           /*!< PMU OVSSET: Event Counter 7 Overflow Set Position */
#define PMU_OVSSET_CNT7_STATUS_Msk           (1UL << PMU_OVSSET_CNT7_STATUS_Pos)           /*!< PMU OVSSET: Event Counter 7 Overflow Set Mask */

#define PMU_OVSSET_CNT8_STATUS_Pos            8U                                           /*!< PMU OVSSET: Event Counter 8 Overflow Set Position */
#define PMU_OVSSET_CNT8_STATUS_Msk           (1UL << PMU_OVSSET_CNT8_STATUS_Pos)           /*!< PMU OVSSET: Event Counter 8 Overflow Set Mask */

#define PMU_OVSSET_CNT9_STATUS_Pos            9U                                           /*!< PMU OVSSET: Event Counter 9 Overflow Set Position */
#define PMU_OVSSET_CNT9_STATUS_Msk           (1UL << PMU_OVSSET_CNT9_STATUS_Pos)           /*!< PMU OVSSET: Event Counter 9 Overflow Set Mask */

#define PMU_OVSSET_CNT10_STATUS_Pos           10U                                          /*!< PMU OVSSET: Event Counter 10 Overflow Set Position */
#define PMU_OVSSET_CNT10_STATUS_Msk          (1UL << PMU_OVSSET_CNT10_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 10 Overflow Set Mask */

#define PMU_OVSSET_CNT11_STATUS_Pos           11U                                          /*!< PMU OVSSET: Event Counter 11 Overflow Set Position */
#define PMU_OVSSET_CNT11_STATUS_Msk          (1UL << PMU_OVSSET_CNT11_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 11 Overflow Set Mask */

#define PMU_OVSSET_CNT12_STATUS_Pos           12U                                          /*!< PMU OVSSET: Event Counter 12 Overflow Set Position */
#define PMU_OVSSET_CNT12_STATUS_Msk          (1UL << PMU_OVSSET_CNT12_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 12 Overflow Set Mask */

#define PMU_OVSSET_CNT13_STATUS_Pos           13U                                          /*!< PMU OVSSET: Event Counter 13 Overflow Set Position */
#define PMU_OVSSET_CNT13_STATUS_Msk          (1UL << PMU_OVSSET_CNT13_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 13 Overflow Set Mask */

#define PMU_OVSSET_CNT14_STATUS_Pos           14U                                          /*!< PMU OVSSET: Event Counter 14 Overflow Set Position */
#define PMU_OVSSET_CNT14_STATUS_Msk          (1UL << PMU_OVSSET_CNT14_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 14 Overflow Set Mask */

#define PMU_OVSSET_CNT15_STATUS_Pos           15U                                          /*!< PMU OVSSET: Event Counter 15 Overflow Set Position */
#define PMU_OVSSET_CNT15_STATUS_Msk          (1UL << PMU_OVSSET_CNT15_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 15 Overflow Set Mask */

#define PMU_OVSSET_CNT16_STATUS_Pos           16U                                          /*!< PMU OVSSET: Event Counter 16 Overflow Set Position */
#define PMU_OVSSET_CNT16_STATUS_Msk          (1UL << PMU_OVSSET_CNT16_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 16 Overflow Set Mask */

#define PMU_OVSSET_CNT17_STATUS_Pos           17U                                          /*!< PMU OVSSET: Event Counter 17 Overflow Set Position */
#define PMU_OVSSET_CNT17_STATUS_Msk          (1UL << PMU_OVSSET_CNT17_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 17 Overflow Set Mask */

#define PMU_OVSSET_CNT18_STATUS_Pos           18U                                          /*!< PMU OVSSET: Event Counter 18 Overflow Set Position */
#define PMU_OVSSET_CNT18_STATUS_Msk          (1UL << PMU_OVSSET_CNT18_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 18 Overflow Set Mask */

#define PMU_OVSSET_CNT19_STATUS_Pos           19U                                          /*!< PMU OVSSET: Event Counter 19 Overflow Set Position */
#define PMU_OVSSET_CNT19_STATUS_Msk          (1UL << PMU_OVSSET_CNT19_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 19 Overflow Set Mask */

#define PMU_OVSSET_CNT20_STATUS_Pos           20U                                          /*!< PMU OVSSET: Event Counter 20 Overflow Set Position */
#define PMU_OVSSET_CNT20_STATUS_Msk          (1UL << PMU_OVSSET_CNT20_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 20 Overflow Set Mask */

#define PMU_OVSSET_CNT21_STATUS_Pos           21U                                          /*!< PMU OVSSET: Event Counter 21 Overflow Set Position */
#define PMU_OVSSET_CNT21_STATUS_Msk          (1UL << PMU_OVSSET_CNT21_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 21 Overflow Set Mask */

#define PMU_OVSSET_CNT22_STATUS_Pos           22U                                          /*!< PMU OVSSET: Event Counter 22 Overflow Set Position */
#define PMU_OVSSET_CNT22_STATUS_Msk          (1UL << PMU_OVSSET_CNT22_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 22 Overflow Set Mask */

#define PMU_OVSSET_CNT23_STATUS_Pos           23U                                          /*!< PMU OVSSET: Event Counter 23 Overflow Set Position */
#define PMU_OVSSET_CNT23_STATUS_Msk          (1UL << PMU_OVSSET_CNT23_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 23 Overflow Set Mask */

#define PMU_OVSSET_CNT24_STATUS_Pos           24U                                          /*!< PMU OVSSET: Event Counter 24 Overflow Set Position */
#define PMU_OVSSET_CNT24_STATUS_Msk          (1UL << PMU_OVSSET_CNT24_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 24 Overflow Set Mask */

#define PMU_OVSSET_CNT25_STATUS_Pos           25U                                          /*!< PMU OVSSET: Event Counter 25 Overflow Set Position */
#define PMU_OVSSET_CNT25_STATUS_Msk          (1UL << PMU_OVSSET_CNT25_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 25 Overflow Set Mask */

#define PMU_OVSSET_CNT26_STATUS_Pos           26U                                          /*!< PMU OVSSET: Event Counter 26 Overflow Set Position */
#define PMU_OVSSET_CNT26_STATUS_Msk          (1UL << PMU_OVSSET_CNT26_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 26 Overflow Set Mask */

#define PMU_OVSSET_CNT27_STATUS_Pos           27U                                          /*!< PMU OVSSET: Event Counter 27 Overflow Set Position */
#define PMU_OVSSET_CNT27_STATUS_Msk          (1UL << PMU_OVSSET_CNT27_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 27 Overflow Set Mask */

#define PMU_OVSSET_CNT28_STATUS_Pos           28U                                          /*!< PMU OVSSET: Event Counter 28 Overflow Set Position */
#define PMU_OVSSET_CNT28_STATUS_Msk          (1UL << PMU_OVSSET_CNT28_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 28 Overflow Set Mask */

#define PMU_OVSSET_CNT29_STATUS_Pos           29U                                          /*!< PMU OVSSET: Event Counter 29 Overflow Set Position */
#define PMU_OVSSET_CNT29_STATUS_Msk          (1UL << PMU_OVSSET_CNT29_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 29 Overflow Set Mask */

#define PMU_OVSSET_CNT30_STATUS_Pos           30U                                          /*!< PMU OVSSET: Event Counter 30 Overflow Set Position */
#define PMU_OVSSET_CNT30_STATUS_Msk          (1UL << PMU_OVSSET_CNT30_STATUS_Pos)          /*!< PMU OVSSET: Event Counter 30 Overflow Set Mask */

#define PMU_OVSSET_CYCCNT_STATUS_Pos          31U                                          /*!< PMU OVSSET: Cycle Counter Overflow Set Position */
#define PMU_OVSSET_CYCCNT_STATUS_Msk         (1UL << PMU_OVSSET_CYCCNT_STATUS_Pos)         /*!< PMU OVSSET: Cycle Counter Overflow Set Mask */

/** \brief PMU Overflow Flag Status Clear Register Definitions */
#define PMU_OVSCLR_CNT0_STATUS_Pos            0U                                           /*!< PMU OVSCLR: Event Counter 0 Overflow Clear Position */
#define PMU_OVSCLR_CNT0_STATUS_Msk           (1UL /*<< PMU_OVSCLR_CNT0_STATUS_Pos*/)       /*!< PMU OVSCLR: Event Counter 0 Overflow Clear Mask */

#define PMU_OVSCLR_CNT1_STATUS_Pos            1U                                           /*!< PMU OVSCLR: Event Counter 1 Overflow Clear Position */
#define PMU_OVSCLR_CNT1_STATUS_Msk           (1UL << PMU_OVSCLR_CNT1_STATUS_Pos)           /*!< PMU OVSCLR: Event Counter 1 Overflow Clear */

#define PMU_OVSCLR_CNT2_STATUS_Pos            2U                                           /*!< PMU OVSCLR: Event Counter 2 Overflow Clear Position */
#define PMU_OVSCLR_CNT2_STATUS_Msk           (1UL << PMU_OVSCLR_CNT2_STATUS_Pos)           /*!< PMU OVSCLR: Event Counter 2 Overflow Clear Mask */

#define PMU_OVSCLR_CNT3_STATUS_Pos            3U                                           /*!< PMU OVSCLR: Event Counter 3 Overflow Clear Position */
#define PMU_OVSCLR_CNT3_STATUS_Msk           (1UL << PMU_OVSCLR_CNT3_STATUS_Pos)           /*!< PMU OVSCLR: Event Counter 3 Overflow Clear Mask */

#define PMU_OVSCLR_CNT4_STATUS_Pos            4U                                           /*!< PMU OVSCLR: Event Counter 4 Overflow Clear Position */
#define PMU_OVSCLR_CNT4_STATUS_Msk           (1UL << PMU_OVSCLR_CNT4_STATUS_Pos)           /*!< PMU OVSCLR: Event Counter 4 Overflow Clear Mask */

#define PMU_OVSCLR_CNT5_STATUS_Pos            5U                                           /*!< PMU OVSCLR: Event Counter 5 Overflow Clear Position */
#define PMU_OVSCLR_CNT5_STATUS_Msk           (1UL << PMU_OVSCLR_CNT5_STATUS_Pos)           /*!< PMU OVSCLR: Event Counter 5 Overflow Clear Mask */

#define PMU_OVSCLR_CNT6_STATUS_Pos            6U                                           /*!< PMU OVSCLR: Event Counter 6 Overflow Clear Position */
#define PMU_OVSCLR_CNT6_STATUS_Msk           (1UL << PMU_OVSCLR_CNT6_STATUS_Pos)           /*!< PMU OVSCLR: Event Counter 6 Overflow Clear Mask */

#define PMU_OVSCLR_CNT7_STATUS_Pos            7U                                           /*!< PMU OVSCLR: Event Counter 7 Overflow Clear Position */
#define PMU_OVSCLR_CNT7_STATUS_Msk           (1UL << PMU_OVSCLR_CNT7_STATUS_Pos)           /*!< PMU OVSCLR: Event Counter 7 Overflow Clear Mask */

#define PMU_OVSCLR_CNT8_STATUS_Pos            8U                                           /*!< PMU OVSCLR: Event Counter 8 Overflow Clear Position */
#define PMU_OVSCLR_CNT8_STATUS_Msk           (1UL << PMU_OVSCLR_CNT8_STATUS_Pos)           /*!< PMU OVSCLR: Event Counter 8 Overflow Clear Mask */

#define PMU_OVSCLR_CNT9_STATUS_Pos            9U                                           /*!< PMU OVSCLR: Event Counter 9 Overflow Clear Position */
#define PMU_OVSCLR_CNT9_STATUS_Msk           (1UL << PMU_OVSCLR_CNT9_STATUS_Pos)           /*!< PMU OVSCLR: Event Counter 9 Overflow Clear Mask */

#define PMU_OVSCLR_CNT10_STATUS_Pos           10U                                          /*!< PMU OVSCLR: Event Counter 10 Overflow Clear Position */
#define PMU_OVSCLR_CNT10_STATUS_Msk          (1UL << PMU_OVSCLR_CNT10_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 10 Overflow Clear Mask */

#define PMU_OVSCLR_CNT11_STATUS_Pos           11U                                          /*!< PMU OVSCLR: Event Counter 11 Overflow Clear Position */
#define PMU_OVSCLR_CNT11_STATUS_Msk          (1UL << PMU_OVSCLR_CNT11_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 11 Overflow Clear Mask */

#define PMU_OVSCLR_CNT12_STATUS_Pos           12U                                          /*!< PMU OVSCLR: Event Counter 12 Overflow Clear Position */
#define PMU_OVSCLR_CNT12_STATUS_Msk          (1UL << PMU_OVSCLR_CNT12_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 12 Overflow Clear Mask */

#define PMU_OVSCLR_CNT13_STATUS_Pos           13U                                          /*!< PMU OVSCLR: Event Counter 13 Overflow Clear Position */
#define PMU_OVSCLR_CNT13_STATUS_Msk          (1UL << PMU_OVSCLR_CNT13_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 13 Overflow Clear Mask */

#define PMU_OVSCLR_CNT14_STATUS_Pos           14U                                          /*!< PMU OVSCLR: Event Counter 14 Overflow Clear Position */
#define PMU_OVSCLR_CNT14_STATUS_Msk          (1UL << PMU_OVSCLR_CNT14_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 14 Overflow Clear Mask */

#define PMU_OVSCLR_CNT15_STATUS_Pos           15U                                          /*!< PMU OVSCLR: Event Counter 15 Overflow Clear Position */
#define PMU_OVSCLR_CNT15_STATUS_Msk          (1UL << PMU_OVSCLR_CNT15_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 15 Overflow Clear Mask */

#define PMU_OVSCLR_CNT16_STATUS_Pos           16U                                          /*!< PMU OVSCLR: Event Counter 16 Overflow Clear Position */
#define PMU_OVSCLR_CNT16_STATUS_Msk          (1UL << PMU_OVSCLR_CNT16_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 16 Overflow Clear Mask */

#define PMU_OVSCLR_CNT17_STATUS_Pos           17U                                          /*!< PMU OVSCLR: Event Counter 17 Overflow Clear Position */
#define PMU_OVSCLR_CNT17_STATUS_Msk          (1UL << PMU_OVSCLR_CNT17_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 17 Overflow Clear Mask */

#define PMU_OVSCLR_CNT18_STATUS_Pos           18U                                          /*!< PMU OVSCLR: Event Counter 18 Overflow Clear Position */
#define PMU_OVSCLR_CNT18_STATUS_Msk          (1UL << PMU_OVSCLR_CNT18_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 18 Overflow Clear Mask */

#define PMU_OVSCLR_CNT19_STATUS_Pos           19U                                          /*!< PMU OVSCLR: Event Counter 19 Overflow Clear Position */
#define PMU_OVSCLR_CNT19_STATUS_Msk          (1UL << PMU_OVSCLR_CNT19_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 19 Overflow Clear Mask */

#define PMU_OVSCLR_CNT20_STATUS_Pos           20U                                          /*!< PMU OVSCLR: Event Counter 20 Overflow Clear Position */
#define PMU_OVSCLR_CNT20_STATUS_Msk          (1UL << PMU_OVSCLR_CNT20_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 20 Overflow Clear Mask */

#define PMU_OVSCLR_CNT21_STATUS_Pos           21U                                          /*!< PMU OVSCLR: Event Counter 21 Overflow Clear Position */
#define PMU_OVSCLR_CNT21_STATUS_Msk          (1UL << PMU_OVSCLR_CNT21_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 21 Overflow Clear Mask */

#define PMU_OVSCLR_CNT22_STATUS_Pos           22U                                          /*!< PMU OVSCLR: Event Counter 22 Overflow Clear Position */
#define PMU_OVSCLR_CNT22_STATUS_Msk          (1UL << PMU_OVSCLR_CNT22_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 22 Overflow Clear Mask */

#define PMU_OVSCLR_CNT23_STATUS_Pos           23U                                          /*!< PMU OVSCLR: Event Counter 23 Overflow Clear Position */
#define PMU_OVSCLR_CNT23_STATUS_Msk          (1UL << PMU_OVSCLR_CNT23_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 23 Overflow Clear Mask */

#define PMU_OVSCLR_CNT24_STATUS_Pos           24U                                          /*!< PMU OVSCLR: Event Counter 24 Overflow Clear Position */
#define PMU_OVSCLR_CNT24_STATUS_Msk          (1UL << PMU_OVSCLR_CNT24_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 24 Overflow Clear Mask */

#define PMU_OVSCLR_CNT25_STATUS_Pos           25U                                          /*!< PMU OVSCLR: Event Counter 25 Overflow Clear Position */
#define PMU_OVSCLR_CNT25_STATUS_Msk          (1UL << PMU_OVSCLR_CNT25_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 25 Overflow Clear Mask */

#define PMU_OVSCLR_CNT26_STATUS_Pos           26U                                          /*!< PMU OVSCLR: Event Counter 26 Overflow Clear Position */
#define PMU_OVSCLR_CNT26_STATUS_Msk          (1UL << PMU_OVSCLR_CNT26_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 26 Overflow Clear Mask */

#define PMU_OVSCLR_CNT27_STATUS_Pos           27U                                          /*!< PMU OVSCLR: Event Counter 27 Overflow Clear Position */
#define PMU_OVSCLR_CNT27_STATUS_Msk          (1UL << PMU_OVSCLR_CNT27_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 27 Overflow Clear Mask */

#define PMU_OVSCLR_CNT28_STATUS_Pos           28U                                          /*!< PMU OVSCLR: Event Counter 28 Overflow Clear Position */
#define PMU_OVSCLR_CNT28_STATUS_Msk          (1UL << PMU_OVSCLR_CNT28_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 28 Overflow Clear Mask */

#define PMU_OVSCLR_CNT29_STATUS_Pos           29U                                          /*!< PMU OVSCLR: Event Counter 29 Overflow Clear Position */
#define PMU_OVSCLR_CNT29_STATUS_Msk          (1UL << PMU_OVSCLR_CNT29_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 29 Overflow Clear Mask */

#define PMU_OVSCLR_CNT30_STATUS_Pos           30U                                          /*!< PMU OVSCLR: Event Counter 30 Overflow Clear Position */
#define PMU_OVSCLR_CNT30_STATUS_Msk          (1UL << PMU_OVSCLR_CNT30_STATUS_Pos)          /*!< PMU OVSCLR: Event Counter 30 Overflow Clear Mask */

#define PMU_OVSCLR_CYCCNT_STATUS_Pos          31U                                          /*!< PMU OVSCLR: Cycle Counter Overflow Clear Position */
#define PMU_OVSCLR_CYCCNT_STATUS_Msk         (1UL << PMU_OVSCLR_CYCCNT_STATUS_Pos)         /*!< PMU OVSCLR: Cycle Counter Overflow Clear Mask */

/** \brief PMU Software Increment Counter */
#define PMU_SWINC_CNT0_Pos                    0U                                           /*!< PMU SWINC: Event Counter 0 Software Increment Position */
#define PMU_SWINC_CNT0_Msk                   (1UL /*<< PMU_SWINC_CNT0_Pos */)              /*!< PMU SWINC: Event Counter 0 Software Increment Mask */

#define PMU_SWINC_CNT1_Pos                    1U                                           /*!< PMU SWINC: Event Counter 1 Software Increment Position */
#define PMU_SWINC_CNT1_Msk                   (1UL << PMU_SWINC_CNT1_Pos)                   /*!< PMU SWINC: Event Counter 1 Software Increment Mask */

#define PMU_SWINC_CNT2_Pos                    2U                                           /*!< PMU SWINC: Event Counter 2 Software Increment Position */
#define PMU_SWINC_CNT2_Msk                   (1UL << PMU_SWINC_CNT2_Pos)                   /*!< PMU SWINC: Event Counter 2 Software Increment Mask */

#define PMU_SWINC_CNT3_Pos                    3U                                           /*!< PMU SWINC: Event Counter 3 Software Increment Position */
#define PMU_SWINC_CNT3_Msk                   (1UL << PMU_SWINC_CNT3_Pos)                   /*!< PMU SWINC: Event Counter 3 Software Increment Mask */

#define PMU_SWINC_CNT4_Pos                    4U                                           /*!< PMU SWINC: Event Counter 4 Software Increment Position */
#define PMU_SWINC_CNT4_Msk                   (1UL << PMU_SWINC_CNT4_Pos)                   /*!< PMU SWINC: Event Counter 4 Software Increment Mask */

#define PMU_SWINC_CNT5_Pos                    5U                                           /*!< PMU SWINC: Event Counter 5 Software Increment Position */
#define PMU_SWINC_CNT5_Msk                   (1UL << PMU_SWINC_CNT5_Pos)                   /*!< PMU SWINC: Event Counter 5 Software Increment Mask */

#define PMU_SWINC_CNT6_Pos                    6U                                           /*!< PMU SWINC: Event Counter 6 Software Increment Position */
#define PMU_SWINC_CNT6_Msk                   (1UL << PMU_SWINC_CNT6_Pos)                   /*!< PMU SWINC: Event Counter 6 Software Increment Mask */

#define PMU_SWINC_CNT7_Pos                    7U                                           /*!< PMU SWINC: Event Counter 7 Software Increment Position */
#define PMU_SWINC_CNT7_Msk                   (1UL << PMU_SWINC_CNT7_Pos)                   /*!< PMU SWINC: Event Counter 7 Software Increment Mask */

#define PMU_SWINC_CNT8_Pos                    8U                                           /*!< PMU SWINC: Event Counter 8 Software Increment Position */
#define PMU_SWINC_CNT8_Msk                   (1UL << PMU_SWINC_CNT8_Pos)                   /*!< PMU SWINC: Event Counter 8 Software Increment Mask */

#define PMU_SWINC_CNT9_Pos                    9U                                           /*!< PMU SWINC: Event Counter 9 Software Increment Position */
#define PMU_SWINC_CNT9_Msk                   (1UL << PMU_SWINC_CNT9_Pos)                   /*!< PMU SWINC: Event Counter 9 Software Increment Mask */

#define PMU_SWINC_CNT10_Pos                   10U                                          /*!< PMU SWINC: Event Counter 10 Software Increment Position */
#define PMU_SWINC_CNT10_Msk                  (1UL << PMU_SWINC_CNT10_Pos)                  /*!< PMU SWINC: Event Counter 10 Software Increment Mask */

#define PMU_SWINC_CNT11_Pos                   11U                                          /*!< PMU SWINC: Event Counter 11 Software Increment Position */
#define PMU_SWINC_CNT11_Msk                  (1UL << PMU_SWINC_CNT11_Pos)                  /*!< PMU SWINC: Event Counter 11 Software Increment Mask */

#define PMU_SWINC_CNT12_Pos                   12U                                          /*!< PMU SWINC: Event Counter 12 Software Increment Position */
#define PMU_SWINC_CNT12_Msk                  (1UL << PMU_SWINC_CNT12_Pos)                  /*!< PMU SWINC: Event Counter 12 Software Increment Mask */

#define PMU_SWINC_CNT13_Pos                   13U                                          /*!< PMU SWINC: Event Counter 13 Software Increment Position */
#define PMU_SWINC_CNT13_Msk                  (1UL << PMU_SWINC_CNT13_Pos)                  /*!< PMU SWINC: Event Counter 13 Software Increment Mask */

#define PMU_SWINC_CNT14_Pos                   14U                                          /*!< PMU SWINC: Event Counter 14 Software Increment Position */
#define PMU_SWINC_CNT14_Msk                  (1UL << PMU_SWINC_CNT14_Pos)                  /*!< PMU SWINC: Event Counter 14 Software Increment Mask */

#define PMU_SWINC_CNT15_Pos                   15U                                          /*!< PMU SWINC: Event Counter 15 Software Increment Position */
#define PMU_SWINC_CNT15_Msk                  (1UL << PMU_SWINC_CNT15_Pos)                  /*!< PMU SWINC: Event Counter 15 Software Increment Mask */

#define PMU_SWINC_CNT16_Pos                   16U                                          /*!< PMU SWINC: Event Counter 16 Software Increment Position */
#define PMU_SWINC_CNT16_Msk                  (1UL << PMU_SWINC_CNT16_Pos)                  /*!< PMU SWINC: Event Counter 16 Software Increment Mask */

#define PMU_SWINC_CNT17_Pos                   17U                                          /*!< PMU SWINC: Event Counter 17 Software Increment Position */
#define PMU_SWINC_CNT17_Msk                  (1UL << PMU_SWINC_CNT17_Pos)                  /*!< PMU SWINC: Event Counter 17 Software Increment Mask */

#define PMU_SWINC_CNT18_Pos                   18U                                          /*!< PMU SWINC: Event Counter 18 Software Increment Position */
#define PMU_SWINC_CNT18_Msk                  (1UL << PMU_SWINC_CNT18_Pos)                  /*!< PMU SWINC: Event Counter 18 Software Increment Mask */

#define PMU_SWINC_CNT19_Pos                   19U                                          /*!< PMU SWINC: Event Counter 19 Software Increment Position */
#define PMU_SWINC_CNT19_Msk                  (1UL << PMU_SWINC_CNT19_Pos)                  /*!< PMU SWINC: Event Counter 19 Software Increment Mask */

#define PMU_SWINC_CNT20_Pos                   20U                                          /*!< PMU SWINC: Event Counter 20 Software Increment Position */
#define PMU_SWINC_CNT20_Msk                  (1UL << PMU_SWINC_CNT20_Pos)                  /*!< PMU SWINC: Event Counter 20 Software Increment Mask */

#define PMU_SWINC_CNT21_Pos                   21U                                          /*!< PMU SWINC: Event Counter 21 Software Increment Position */
#define PMU_SWINC_CNT21_Msk                  (1UL << PMU_SWINC_CNT21_Pos)                  /*!< PMU SWINC: Event Counter 21 Software Increment Mask */

#define PMU_SWINC_CNT22_Pos                   22U                                          /*!< PMU SWINC: Event Counter 22 Software Increment Position */
#define PMU_SWINC_CNT22_Msk                  (1UL << PMU_SWINC_CNT22_Pos)                  /*!< PMU SWINC: Event Counter 22 Software Increment Mask */

#define PMU_SWINC_CNT23_Pos                   23U                                          /*!< PMU SWINC: Event Counter 23 Software Increment Position */
#define PMU_SWINC_CNT23_Msk                  (1UL << PMU_SWINC_CNT23_Pos)                  /*!< PMU SWINC: Event Counter 23 Software Increment Mask */

#define PMU_SWINC_CNT24_Pos                   24U                                          /*!< PMU SWINC: Event Counter 24 Software Increment Position */
#define PMU_SWINC_CNT24_Msk                  (1UL << PMU_SWINC_CNT24_Pos)                  /*!< PMU SWINC: Event Counter 24 Software Increment Mask */

#define PMU_SWINC_CNT25_Pos                   25U                                          /*!< PMU SWINC: Event Counter 25 Software Increment Position */
#define PMU_SWINC_CNT25_Msk                  (1UL << PMU_SWINC_CNT25_Pos)                  /*!< PMU SWINC: Event Counter 25 Software Increment Mask */

#define PMU_SWINC_CNT26_Pos                   26U                                          /*!< PMU SWINC: Event Counter 26 Software Increment Position */
#define PMU_SWINC_CNT26_Msk                  (1UL << PMU_SWINC_CNT26_Pos)                  /*!< PMU SWINC: Event Counter 26 Software Increment Mask */

#define PMU_SWINC_CNT27_Pos                   27U                                          /*!< PMU SWINC: Event Counter 27 Software Increment Position */
#define PMU_SWINC_CNT27_Msk                  (1UL << PMU_SWINC_CNT27_Pos)                  /*!< PMU SWINC: Event Counter 27 Software Increment Mask */

#define PMU_SWINC_CNT28_Pos                   28U                                          /*!< PMU SWINC: Event Counter 28 Software Increment Position */
#define PMU_SWINC_CNT28_Msk                  (1UL << PMU_SWINC_CNT28_Pos)                  /*!< PMU SWINC: Event Counter 28 Software Increment Mask */

#define PMU_SWINC_CNT29_Pos                   29U                                          /*!< PMU SWINC: Event Counter 29 Software Increment Position */
#define PMU_SWINC_CNT29_Msk                  (1UL << PMU_SWINC_CNT29_Pos)                  /*!< PMU SWINC: Event Counter 29 Software Increment Mask */

#define PMU_SWINC_CNT30_Pos                   30U                                          /*!< PMU SWINC: Event Counter 30 Software Increment Position */
#define PMU_SWINC_CNT30_Msk                  (1UL << PMU_SWINC_CNT30_Pos)                  /*!< PMU SWINC: Event Counter 30 Software Increment Mask */

/** \brief PMU Control Register Definitions */
#define PMU_CTRL_ENABLE_Pos                   0U                                           /*!< PMU CTRL: ENABLE Position */
#define PMU_CTRL_ENABLE_Msk                  (1UL /*<< PMU_CTRL_ENABLE_Pos*/)              /*!< PMU CTRL: ENABLE Mask */

#define PMU_CTRL_EVENTCNT_RESET_Pos           1U                                           /*!< PMU CTRL: Event Counter Reset Position */
#define PMU_CTRL_EVENTCNT_RESET_Msk          (1UL << PMU_CTRL_EVENTCNT_RESET_Pos)          /*!< PMU CTRL: Event Counter Reset Mask */

#define PMU_CTRL_CYCCNT_RESET_Pos             2U                                           /*!< PMU CTRL: Cycle Counter Reset Position */
#define PMU_CTRL_CYCCNT_RESET_Msk            (1UL << PMU_CTRL_CYCCNT_RESET_Pos)            /*!< PMU CTRL: Cycle Counter Reset Mask */

#define PMU_CTRL_CYCCNT_DISABLE_Pos           5U                                           /*!< PMU CTRL: Disable Cycle Counter Position */
#define PMU_CTRL_CYCCNT_DISABLE_Msk          (1UL << PMU_CTRL_CYCCNT_DISABLE_Pos)          /*!< PMU CTRL: Disable Cycle Counter Mask */

#define PMU_CTRL_FRZ_ON_OV_Pos                9U                                           /*!< PMU CTRL: Freeze-on-overflow Position */
#define PMU_CTRL_FRZ_ON_OV_Msk               (1UL << PMU_CTRL_FRZ_ON_OVERFLOW_Pos)         /*!< PMU CTRL: Freeze-on-overflow Mask */

#define PMU_CTRL_TRACE_ON_OV_Pos              11U                                          /*!< PMU CTRL: Trace-on-overflow Position */
#define PMU_CTRL_TRACE_ON_OV_Msk             (1UL << PMU_CTRL_TRACE_ON_OVERFLOW_Pos)       /*!< PMU CTRL: Trace-on-overflow Mask */

/** \brief PMU Type Register Definitions */
#define PMU_TYPE_NUM_CNTS_Pos                 0U                                           /*!< PMU TYPE: Number of Counters Position */
#define PMU_TYPE_NUM_CNTS_Msk                (0xFFUL /*<< PMU_TYPE_NUM_CNTS_Pos*/)         /*!< PMU TYPE: Number of Counters Mask */

#define PMU_TYPE_SIZE_CNTS_Pos                8U                                           /*!< PMU TYPE: Size of Counters Position */
#define PMU_TYPE_SIZE_CNTS_Msk               (0x3FUL << PMU_TYPE_SIZE_CNTS_Pos)            /*!< PMU TYPE: Size of Counters Mask */

#define PMU_TYPE_CYCCNT_PRESENT_Pos           14U                                          /*!< PMU TYPE: Cycle Counter Present Position */
#define PMU_TYPE_CYCCNT_PRESENT_Msk          (1UL << PMU_TYPE_CYCCNT_PRESENT_Pos)          /*!< PMU TYPE: Cycle Counter Present Mask */

#define PMU_TYPE_FRZ_OV_SUPPORT_Pos           21U                                          /*!< PMU TYPE: Freeze-on-overflow Support Position */
#define PMU_TYPE_FRZ_OV_SUPPORT_Msk          (1UL << PMU_TYPE_FRZ_OV_SUPPORT_Pos)          /*!< PMU TYPE: Freeze-on-overflow Support Mask */

#define PMU_TYPE_TRACE_ON_OV_SUPPORT_Pos      23U                                          /*!< PMU TYPE: Trace-on-overflow Support Position */
#define PMU_TYPE_TRACE_ON_OV_SUPPORT_Msk     (1UL << PMU_TYPE_FRZ_OV_SUPPORT_Pos)          /*!< PMU TYPE: Trace-on-overflow Support Mask */

/** \brief PMU Authentication Status Register Definitions */
#define PMU_AUTHSTATUS_NSID_Pos               0U                                           /*!< PMU AUTHSTATUS: Non-secure Invasive Debug Position */
#define PMU_AUTHSTATUS_NSID_Msk              (0x3UL /*<< PMU_AUTHSTATUS_NSID_Pos*/)        /*!< PMU AUTHSTATUS: Non-secure Invasive Debug Mask */

#define PMU_AUTHSTATUS_NSNID_Pos              2U                                           /*!< PMU AUTHSTATUS: Non-secure Non-invasive Debug Position */
#define PMU_AUTHSTATUS_NSNID_Msk             (0x3UL << PMU_AUTHSTATUS_NSNID_Pos)           /*!< PMU AUTHSTATUS: Non-secure Non-invasive Debug Mask */

#define PMU_AUTHSTATUS_SID_Pos                4U                                           /*!< PMU AUTHSTATUS: Secure Invasive Debug Position */
#define PMU_AUTHSTATUS_SID_Msk               (0x3UL << PMU_AUTHSTATUS_SID_Pos)             /*!< PMU AUTHSTATUS: Secure Invasive Debug Mask */

#define PMU_AUTHSTATUS_SNID_Pos               6U                                           /*!< PMU AUTHSTATUS: Secure Non-invasive Debug Position */
#define PMU_AUTHSTATUS_SNID_Msk              (0x3UL << PMU_AUTHSTATUS_SNID_Pos)            /*!< PMU AUTHSTATUS: Secure Non-invasive Debug Mask */

#define PMU_AUTHSTATUS_NSUID_Pos              16U                                          /*!< PMU AUTHSTATUS: Non-secure Unprivileged Invasive Debug Position */
#define PMU_AUTHSTATUS_NSUID_Msk             (0x3UL << PMU_AUTHSTATUS_NSUID_Pos)           /*!< PMU AUTHSTATUS: Non-secure Unprivileged Invasive Debug Mask */

#define PMU_AUTHSTATUS_NSUNID_Pos             18U                                          /*!< PMU AUTHSTATUS: Non-secure Unprivileged Non-invasive Debug Position */
#define PMU_AUTHSTATUS_NSUNID_Msk            (0x3UL << PMU_AUTHSTATUS_NSUNID_Pos)          /*!< PMU AUTHSTATUS: Non-secure Unprivileged Non-invasive Debug Mask */

#define PMU_AUTHSTATUS_SUID_Pos               20U                                          /*!< PMU AUTHSTATUS: Secure Unprivileged Invasive Debug Position */
#define PMU_AUTHSTATUS_SUID_Msk              (0x3UL << PMU_AUTHSTATUS_SUID_Pos)            /*!< PMU AUTHSTATUS: Secure Unprivileged Invasive Debug Mask */

#define PMU_AUTHSTATUS_SUNID_Pos              22U                                          /*!< PMU AUTHSTATUS: Secure Unprivileged Non-invasive Debug Position */
#define PMU_AUTHSTATUS_SUNID_Msk             (0x3UL << PMU_AUTHSTATUS_SUNID_Pos)           /*!< PMU AUTHSTATUS: Secure Unprivileged Non-invasive Debug Mask */

/**
 * \brief PMU Events
 * \note  See the Armv8.1-M Architecture Reference Manual for full details on these PMU events.
 * */

#define ARM_PMU_SW_INCR                              0x0000             /*!< Software update to the PMU_SWINC register, architecturally executed and condition code check pass */
#define ARM_PMU_L1I_CACHE_REFILL                     0x0001             /*!< L1 I-Cache refill */
#define ARM_PMU_L1D_CACHE_REFILL                     0x0003             /*!< L1 D-Cache refill */
#define ARM_PMU_L1D_CACHE                            0x0004             /*!< L1 D-Cache access */
#define ARM_PMU_LD_RETIRED                           0x0006             /*!< Memory-reading instruction architecturally executed and condition code check pass */
#define ARM_PMU_ST_RETIRED                           0x0007             /*!< Memory-writing instruction architecturally executed and condition code check pass */
#define ARM_PMU_INST_RETIRED                         0x0008             /*!< Instruction architecturally executed */
#define ARM_PMU_EXC_TAKEN                            0x0009             /*!< Exception entry */
#define ARM_PMU_EXC_RETURN                           0x000A             /*!< Exception return instruction architecturally executed and the condition code check pass */
#define ARM_PMU_PC_WRITE_RETIRED                     0x000C             /*!< Software change to the Program Counter (PC). Instruction is architecturally executed and condition code check pass */
#define ARM_PMU_BR_IMMED_RETIRED                     0x000D             /*!< Immediate branch architecturally executed */
#define ARM_PMU_BR_RETURN_RETIRED                    0x000E             /*!< Function return instruction architecturally executed and the condition code check pass */
#define ARM_PMU_UNALIGNED_LDST_RETIRED               0x000F             /*!< Unaligned memory memory-reading or memory-writing instruction architecturally executed and condition code check pass */
#define ARM_PMU_BR_MIS_PRED                          0x0010             /*!< Mispredicted or not predicted branch speculatively executed */
#define ARM_PMU_CPU_CYCLES                           0x0011             /*!< Cycle */
#define ARM_PMU_BR_PRED                              0x0012             /*!< Predictable branch speculatively executed */
#define ARM_PMU_MEM_ACCESS                           0x0013             /*!< Data memory access */
#define ARM_PMU_L1I_CACHE                            0x0014             /*!< Level 1 instruction cache access */
#define ARM_PMU_L1D_CACHE_WB                         0x0015             /*!< Level 1 data cache write-back */
#define ARM_PMU_L2D_CACHE                            0x0016             /*!< Level 2 data cache access */
#define ARM_PMU_L2D_CACHE_REFILL                     0x0017             /*!< Level 2 data cache refill */
#define ARM_PMU_L2D_CACHE_WB                         0x0018             /*!< Level 2 data cache write-back */
#define ARM_PMU_BUS_ACCESS                           0x0019             /*!< Bus access */
#define ARM_PMU_MEMORY_ERROR                         0x001A             /*!< Local memory error */
#define ARM_PMU_INST_SPEC                            0x001B             /*!< Instruction speculatively executed */
#define ARM_PMU_BUS_CYCLES                           0x001D             /*!< Bus cycles */
#define ARM_PMU_CHAIN                                0x001E             /*!< For an odd numbered counter, increment when an overflow occurs on the preceding even-numbered counter on the same PE */
#define ARM_PMU_L1D_CACHE_ALLOCATE                   0x001F             /*!< Level 1 data cache allocation without refill */
#define ARM_PMU_L2D_CACHE_ALLOCATE                   0x0020             /*!< Level 2 data cache allocation without refill */
#define ARM_PMU_BR_RETIRED                           0x0021             /*!< Branch instruction architecturally executed */
#define ARM_PMU_BR_MIS_PRED_RETIRED                  0x0022             /*!< Mispredicted branch instruction architecturally executed */
#define ARM_PMU_STALL_FRONTEND                       0x0023             /*!< No operation issued because of the frontend */
#define ARM_PMU_STALL_BACKEND                        0x0024             /*!< No operation issued because of the backend */
#define ARM_PMU_L2I_CACHE                            0x0027             /*!< Level 2 instruction cache access */
#define ARM_PMU_L2I_CACHE_REFILL                     0x0028             /*!< Level 2 instruction cache refill */
#define ARM_PMU_L3D_CACHE_ALLOCATE                   0x0029             /*!< Level 3 data cache allocation without refill */
#define ARM_PMU_L3D_CACHE_REFILL                     0x002A             /*!< Level 3 data cache refill */
#define ARM_PMU_L3D_CACHE                            0x002B             /*!< Level 3 data cache access */
#define ARM_PMU_L3D_CACHE_WB                         0x002C             /*!< Level 3 data cache write-back */
#define ARM_PMU_LL_CACHE_RD                          0x0036             /*!< Last level data cache read */
#define ARM_PMU_LL_CACHE_MISS_RD                     0x0037             /*!< Last level data cache read miss */
#define ARM_PMU_L1D_CACHE_MISS_RD                    0x0039             /*!< Level 1 data cache read miss */
#define ARM_PMU_OP_COMPLETE                          0x003A             /*!< Operation retired */
#define ARM_PMU_OP_SPEC                              0x003B             /*!< Operation speculatively executed */
#define ARM_PMU_STALL                                0x003C             /*!< Stall cycle for instruction or operation not sent for execution */
#define ARM_PMU_STALL_OP_BACKEND                     0x003D             /*!< Stall cycle for instruction or operation not sent for execution due to pipeline backend */
#define ARM_PMU_STALL_OP_FRONTEND                    0x003E             /*!< Stall cycle for instruction or operation not sent for execution due to pipeline frontend */
#define ARM_PMU_STALL_OP                             0x003F             /*!< Instruction or operation slots not occupied each cycle */
#define ARM_PMU_L1D_CACHE_RD                         0x0040             /*!< Level 1 data cache read */
#define ARM_PMU_LE_RETIRED                           0x0100             /*!< Loop end instruction executed */
#define ARM_PMU_LE_SPEC                              0x0101             /*!< Loop end instruction speculatively executed */
#define ARM_PMU_BF_RETIRED                           0x0104             /*!< Branch future instruction architecturally executed and condition code check pass */
#define ARM_PMU_BF_SPEC                              0x0105             /*!< Branch future instruction speculatively executed and condition code check pass */
#define ARM_PMU_LE_CANCEL                            0x0108             /*!< Loop end instruction not taken */
#define ARM_PMU_BF_CANCEL                            0x0109             /*!< Branch future instruction not taken */
#define ARM_PMU_SE_CALL_S                            0x0114             /*!< Call to secure function, resulting in Security state change */
#define ARM_PMU_SE_CALL_NS                           0x0115             /*!< Call to non-secure function, resulting in Security state change */
#define ARM_PMU_DWT_CMPMATCH0                        0x0118             /*!< DWT comparator 0 match */
#define ARM_PMU_DWT_CMPMATCH1                        0x0119             /*!< DWT comparator 1 match */
#define ARM_PMU_DWT_CMPMATCH2                        0x011A             /*!< DWT comparator 2 match */
#define ARM_PMU_DWT_CMPMATCH3                        0x011B             /*!< DWT comparator 3 match */
#define ARM_PMU_MVE_INST_RETIRED                     0x0200             /*!< MVE instruction architecturally executed */
#define ARM_PMU_MVE_INST_SPEC                        0x0201             /*!< MVE instruction speculatively executed */
#define ARM_PMU_MVE_FP_RETIRED                       0x0204             /*!< MVE floating-point instruction architecturally executed */
#define ARM_PMU_MVE_FP_SPEC                          0x0205             /*!< MVE floating-point instruction speculatively executed */
#define ARM_PMU_MVE_FP_HP_RETIRED                    0x0208             /*!< MVE half-precision floating-point instruction architecturally executed */
#define ARM_PMU_MVE_FP_HP_SPEC                       0x0209             /*!< MVE half-precision floating-point instruction speculatively executed */
#define ARM_PMU_MVE_FP_SP_RETIRED                    0x020C             /*!< MVE single-precision floating-point instruction architecturally executed */
#define ARM_PMU_MVE_FP_SP_SPEC                       0x020D             /*!< MVE single-precision floating-point instruction speculatively executed */
#define ARM_PMU_MVE_FP_MAC_RETIRED                   0x0214             /*!< MVE floating-point multiply or multiply-accumulate instruction architecturally executed */
#define ARM_PMU_MVE_FP_MAC_SPEC                      0x0215             /*!< MVE floating-point multiply or multiply-accumulate instruction speculatively executed */
#define ARM_PMU_MVE_INT_RETIRED                      0x0224             /*!< MVE integer instruction architecturally executed */
#define ARM_PMU_MVE_INT_SPEC                         0x0225             /*!< MVE integer instruction speculatively executed */
#define ARM_PMU_MVE_INT_MAC_RETIRED                  0x0228             /*!< MVE multiply or multiply-accumulate instruction architecturally executed */
#define ARM_PMU_MVE_INT_MAC_SPEC                     0x0229             /*!< MVE multiply or multiply-accumulate instruction speculatively executed */
#define ARM_PMU_MVE_LDST_RETIRED                     0x0238             /*!< MVE load or store instruction architecturally executed */
#define ARM_PMU_MVE_LDST_SPEC                        0x0239             /*!< MVE load or store instruction speculatively executed */
#define ARM_PMU_MVE_LD_RETIRED                       0x023C             /*!< MVE load instruction architecturally executed */
#define ARM_PMU_MVE_LD_SPEC                          0x023D             /*!< MVE load instruction speculatively executed */
#define ARM_PMU_MVE_ST_RETIRED                       0x0240             /*!< MVE store instruction architecturally executed */
#define ARM_PMU_MVE_ST_SPEC                          0x0241             /*!< MVE store instruction speculatively executed */
#define ARM_PMU_MVE_LDST_CONTIG_RETIRED              0x0244             /*!< MVE contiguous load or store instruction architecturally executed */
#define ARM_PMU_MVE_LDST_CONTIG_SPEC                 0x0245             /*!< MVE contiguous load or store instruction speculatively executed */
#define ARM_PMU_MVE_LD_CONTIG_RETIRED                0x0248             /*!< MVE contiguous load instruction architecturally executed */
#define ARM_PMU_MVE_LD_CONTIG_SPEC                   0x0249             /*!< MVE contiguous load instruction speculatively executed */
#define ARM_PMU_MVE_ST_CONTIG_RETIRED                0x024C             /*!< MVE contiguous store instruction architecturally executed */
#define ARM_PMU_MVE_ST_CONTIG_SPEC                   0x024D             /*!< MVE contiguous store instruction speculatively executed */
#define ARM_PMU_MVE_LDST_NONCONTIG_RETIRED           0x0250             /*!< MVE non-contiguous load or store instruction architecturally executed */
#define ARM_PMU_MVE_LDST_NONCONTIG_SPEC              0x0251             /*!< MVE non-contiguous load or store instruction speculatively executed */
#define ARM_PMU_MVE_LD_NONCONTIG_RETIRED             0x0254             /*!< MVE non-contiguous load instruction architecturally executed */
#define ARM_PMU_MVE_LD_NONCONTIG_SPEC                0x0255             /*!< MVE non-contiguous load instruction speculatively executed */
#define ARM_PMU_MVE_ST_NONCONTIG_RETIRED             0x0258             /*!< MVE non-contiguous store instruction architecturally executed */
#define ARM_PMU_MVE_ST_NONCONTIG_SPEC                0x0259             /*!< MVE non-contiguous store instruction speculatively executed */
#define ARM_PMU_MVE_LDST_MULTI_RETIRED               0x025C             /*!< MVE memory instruction targeting multiple registers architecturally executed */
#define ARM_PMU_MVE_LDST_MULTI_SPEC                  0x025D             /*!< MVE memory instruction targeting multiple registers speculatively executed */
#define ARM_PMU_MVE_LD_MULTI_RETIRED                 0x0260             /*!< MVE memory load instruction targeting multiple registers architecturally executed */
#define ARM_PMU_MVE_LD_MULTI_SPEC                    0x0261             /*!< MVE memory load instruction targeting multiple registers speculatively executed */
#define ARM_PMU_MVE_ST_MULTI_RETIRED                 0x0261             /*!< MVE memory store instruction targeting multiple registers architecturally executed */
#define ARM_PMU_MVE_ST_MULTI_SPEC                    0x0265             /*!< MVE memory store instruction targeting multiple registers speculatively executed */
#define ARM_PMU_MVE_LDST_UNALIGNED_RETIRED           0x028C             /*!< MVE unaligned memory load or store instruction architecturally executed */
#define ARM_PMU_MVE_LDST_UNALIGNED_SPEC              0x028D             /*!< MVE unaligned memory load or store instruction speculatively executed */
#define ARM_PMU_MVE_LD_UNALIGNED_RETIRED             0x0290             /*!< MVE unaligned load instruction architecturally executed */
#define ARM_PMU_MVE_LD_UNALIGNED_SPEC                0x0291             /*!< MVE unaligned load instruction speculatively executed */
#define ARM_PMU_MVE_ST_UNALIGNED_RETIRED             0x0294             /*!< MVE unaligned store instruction architecturally executed */
#define ARM_PMU_MVE_ST_UNALIGNED_SPEC                0x0295             /*!< MVE unaligned store instruction speculatively executed */
#define ARM_PMU_MVE_LDST_UNALIGNED_NONCONTIG_RETIRED 0x0298             /*!< MVE unaligned noncontiguous load or store instruction architecturally executed */
#define ARM_PMU_MVE_LDST_UNALIGNED_NONCONTIG_SPEC    0x0299             /*!< MVE unaligned noncontiguous load or store instruction speculatively executed */
#define ARM_PMU_MVE_VREDUCE_RETIRED                  0x02A0             /*!< MVE vector reduction instruction architecturally executed */
#define ARM_PMU_MVE_VREDUCE_SPEC                     0x02A1             /*!< MVE vector reduction instruction speculatively executed */
#define ARM_PMU_MVE_VREDUCE_FP_RETIRED               0x02A4             /*!< MVE floating-point vector reduction instruction architecturally executed */
#define ARM_PMU_MVE_VREDUCE_FP_SPEC                  0x02A5             /*!< MVE floating-point vector reduction instruction speculatively executed */
#define ARM_PMU_MVE_VREDUCE_INT_RETIRED              0x02A8             /*!< MVE integer vector reduction instruction architecturally executed */
#define ARM_PMU_MVE_VREDUCE_INT_SPEC                 0x02A9             /*!< MVE integer vector reduction instruction speculatively executed */
#define ARM_PMU_MVE_PRED                             0x02B8             /*!< Cycles where one or more predicated beats architecturally executed */
#define ARM_PMU_MVE_STALL                            0x02CC             /*!< Stall cycles caused by an MVE instruction */
#define ARM_PMU_MVE_STALL_RESOURCE                   0x02CD             /*!< Stall cycles caused by an MVE instruction because of resource conflicts */
#define ARM_PMU_MVE_STALL_RESOURCE_MEM               0x02CE             /*!< Stall cycles caused by an MVE instruction because of memory resource conflicts */
#define ARM_PMU_MVE_STALL_RESOURCE_FP                0x02CF             /*!< Stall cycles caused by an MVE instruction because of floating-point resource conflicts */
#define ARM_PMU_MVE_STALL_RESOURCE_INT               0x02D0             /*!< Stall cycles caused by an MVE instruction because of integer resource conflicts */
#define ARM_PMU_MVE_STALL_BREAK                      0x02D3             /*!< Stall cycles caused by an MVE chain break */
#define ARM_PMU_MVE_STALL_DEPENDENCY                 0x02D4             /*!< Stall cycles caused by MVE register dependency */
#define ARM_PMU_ITCM_ACCESS                          0x4007             /*!< Instruction TCM access */
#define ARM_PMU_DTCM_ACCESS                          0x4008             /*!< Data TCM access */
#define ARM_PMU_TRCEXTOUT0                           0x4010             /*!< ETM external output 0 */
#define ARM_PMU_TRCEXTOUT1                           0x4011             /*!< ETM external output 1 */
#define ARM_PMU_TRCEXTOUT2                           0x4012             /*!< ETM external output 2 */
#define ARM_PMU_TRCEXTOUT3                           0x4013             /*!< ETM external output 3 */
#define ARM_PMU_CTI_TRIGOUT4                         0x4018             /*!< Cross-trigger Interface output trigger 4 */
#define ARM_PMU_CTI_TRIGOUT5                         0x4019             /*!< Cross-trigger Interface output trigger 5 */
#define ARM_PMU_CTI_TRIGOUT6                         0x401A             /*!< Cross-trigger Interface output trigger 6 */
#define ARM_PMU_CTI_TRIGOUT7                         0x401B             /*!< Cross-trigger Interface output trigger 7 */

#endif


#ifndef PMU
#   define PMU_BASE        (0xE0003000UL)                                       /*!< PMU Base Address */
#   define PMU             ((PMU_Type       *)     PMU_BASE         )           /*!< PMU configuration struct */
#endif

#ifndef DCB
#   define DCB_BASE        (0xE000EDF0UL)                                       /*!< DCB Base Address */
#   define DCB             ((DCB_Type       *)     DCB_BASE         )           /*!< DCB configuration struct */
#endif

#ifndef SCB
#   define SCS_BASE        (0xE000E000UL)                                       /*!< System Control Space Base Address */
#   define SCB_BASE        (SCS_BASE +  0x0D00UL)                               /*!< System Control Block Base Address */
#   define SCB             ((SCB_Type       *)     SCB_BASE      )              /*!< SCB configuration struct */
#endif

#ifndef DWT
#   define DWT_BASE         (0xE0001000UL)                                      /*!< DWT Base Address */
#   define DWT              ((DWT_Type       *)     DWT_BASE         )          /*!< DWT configuration struct */
#endif


/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

#if !defined(CMSIS_device_header)
/**
  \brief  Structure type to access the Debug Control Block Registers (DCB).
 */
typedef struct
{
  __IOM uint32_t DHCSR;                  /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
  __OM  uint32_t DCRSR;                  /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register */
  __IOM uint32_t DCRDR;                  /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register */
  __IOM uint32_t DEMCR;                  /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
  __OM  uint32_t DSCEMCR;                /*!< Offset: 0x010 ( /W)  Debug Set Clear Exception and Monitor Control Register */
  __IOM uint32_t DAUTHCTRL;              /*!< Offset: 0x014 (R/W)  Debug Authentication Control Register */
  __IOM uint32_t DSCSR;                  /*!< Offset: 0x018 (R/W)  Debug Security Control and Status Register */
} DCB_Type;

/*!
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  __IOM uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;
#endif

#if !defined(__PMU_PRESENT) || (0 == __PMU_PRESENT)
/**
  \brief  Structure type to access the Performance Monitoring Unit (PMU).
 */
typedef struct
{
  __IOM uint32_t EVCNTR[31];        /*!< Offset: 0x0 (R/W)    Event Counter Registers */
  __IOM uint32_t CCNTR;                             /*!< Offset: 0x7C (R/W)   Cycle Counter Register */
        uint32_t RESERVED1[224];
  __IOM uint32_t EVTYPER[31];       /*!< Offset: 0x400 (R/W)  Event Type and Filter Registers */
  __IOM uint32_t CCFILTR;                           /*!< Offset: 0x47C (R/W)  Cycle Counter Filter Register */
        uint32_t RESERVED3[480];
  __IOM uint32_t CNTENSET;                          /*!< Offset: 0xC00 (R/W)  Count Enable Set Register */
        uint32_t RESERVED4[7];
  __IOM uint32_t CNTENCLR;                          /*!< Offset: 0xC20 (R/W)  Count Enable Clear Register */
        uint32_t RESERVED5[7];
  __IOM uint32_t INTENSET;                          /*!< Offset: 0xC40 (R/W)  Interrupt Enable Set Register */
        uint32_t RESERVED6[7];
  __IOM uint32_t INTENCLR;                          /*!< Offset: 0xC60 (R/W)  Interrupt Enable Clear Register */
        uint32_t RESERVED7[7];
  __IOM uint32_t OVSCLR;                            /*!< Offset: 0xC80 (R/W)  Overflow Flag Status Clear Register */
        uint32_t RESERVED8[7];
  __IOM uint32_t SWINC;                             /*!< Offset: 0xCA0 (R/W)  Software Increment Register */
        uint32_t RESERVED9[7];
  __IOM uint32_t OVSSET;                            /*!< Offset: 0xCC0 (R/W)  Overflow Flag Status Set Register */
        uint32_t RESERVED10[79];
  __IOM uint32_t TYPE;                              /*!< Offset: 0xE00 (R/W)  Type Register */
  __IOM uint32_t CTRL;                              /*!< Offset: 0xE04 (R/W)  Control Register */
        uint32_t RESERVED11[108];
  __IOM uint32_t AUTHSTATUS;                        /*!< Offset: 0xFB8 (R/W)  Authentication Status Register */
  __IOM uint32_t DEVARCH;                           /*!< Offset: 0xFBC (R/W)  Device Architecture Register */
        uint32_t RESERVED12[3];
  __IOM uint32_t DEVTYPE;                           /*!< Offset: 0xFCC (R/W)  Device Type Register */
} PMU_Type;
#endif

enum {
    PMU_CNT_INSTRUCTION         = 0,
    PMU_CNT_MEM_ACCESS          = 1,
    PMU_CNT_L1_DCACHE_REFILL    = 2,
};

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/

#if __PMU_NUM_EVENTCNT >= 6
#   define __COUNTER_NUM__      (3 + (__PMU_NUM_EVENTCNT - 6))
#elif __PMU_NUM_EVENTCNT > 2
#   define __COUNTER_NUM__      (__PMU_NUM_EVENTCNT >> 1)
#else
#   define __COUNTER_NUM__      (5)
#endif


static volatile uint64_t s_dwEventCounter[__COUNTER_NUM__] = {0};

/*============================ PROTOTYPES ====================================*/
/* low level interface for porting */
extern
uint32_t perfc_port_get_system_timer_freq(void);
extern
int64_t perfc_port_get_system_timer_top(void);
extern
bool perfc_port_is_system_timer_ovf_pending(void);
extern
bool perfc_port_init_system_timer(bool bTimerOccupied);
extern
int64_t perfc_port_get_system_timer_elapsed(void);
extern
void perfc_port_clear_system_timer_ovf_pending(void);
extern
void perfc_port_stop_system_timer_counting(void);
extern
void perfc_port_clear_system_timer_counter(void);

/*============================ INCLUDES ======================================*/
/*============================ IMPLEMENTATION ================================*/


#if __PERFC_USE_PMU_PORTING__

__USED
void DebugMon_Handler(void)
{
    perfc_port_pmu_insert_to_debug_monitor_handler();
}

void perfc_port_pmu_insert_to_debug_monitor_handler(void)
{
    if (!(SCB->DFSR & SCB_DFSR_PMU_Msk)) {
        return ;
    }

    if (perfc_port_is_system_timer_ovf_pending()) {
        perfc_port_clear_system_timer_ovf_pending();
        
        perfc_port_insert_to_system_timer_insert_ovf_handler();
    }

    /* get number of counters */
    uint_fast8_t chCounter = PMU->TYPE & PMU_TYPE_NUM_CNTS_Msk;
    chCounter = MIN(chCounter, __PMU_NUM_EVENTCNT);

    do {
        /* handle counter 1 */
        if (chCounter < 2) {
            break ;
        }
        if (PMU->OVSCLR & PMU_OVSCLR_CNT1_STATUS_Msk) {
            PMU->OVSCLR = PMU_OVSCLR_CNT1_STATUS_Msk;

            s_dwEventCounter[PMU_CNT_INSTRUCTION] += (uint64_t)0x100000000;
        }


        /* handle counter 3 */
        if (chCounter < 4) {
            break ;
        }
        if (PMU->OVSCLR & PMU_OVSCLR_CNT3_STATUS_Msk) {
            PMU->OVSCLR = PMU_OVSCLR_CNT3_STATUS_Msk;

            s_dwEventCounter[PMU_CNT_MEM_ACCESS] += (uint64_t)0x100000000;
        }


        /* handle counter 5 */
        if (chCounter < 6) {
            break ;
        }
        if (PMU->OVSCLR & PMU_OVSCLR_CNT5_STATUS_Msk) {
            PMU->OVSCLR = PMU_OVSCLR_CNT5_STATUS_Msk;

            s_dwEventCounter[PMU_CNT_L1_DCACHE_REFILL] += (uint64_t)0x100000000;
        }

        if (chCounter > 6) {

            for (uint_fast8_t n = 6; n < chCounter; n++) {
                uint32_t wMask = (1<<n);
                if (PMU->OVSSET & wMask) {
                    /* counter overflow is detected */
                    PMU->OVSCLR = wMask;                                            /* clear Overflow Flag */

                    /* update corresponding counter */
                    s_dwEventCounter[n - 3] += 0x10000;
                }
            }
        }
    } while(0);
}
 
bool perfc_port_init_system_timer(bool bIsTimeOccupied)
{
    UNUSED_PARAM(bIsTimeOccupied);

    if (!(PMU->TYPE & PMU_TYPE_CYCCNT_PRESENT_Msk)) {
        return false;
    }

    __IRQ_SAFE {

        PMU->CTRL &= ~PMU_CTRL_ENABLE_Msk;

        perfc_port_stop_system_timer_counting();
        
        /* disable PMU Cycle Counter interrupt */
        PMU->INTENCLR = PMU_INTENCLR_CYCCNT_ENABLE_Msk;

        perfc_port_clear_system_timer_counter();
        perfc_port_clear_system_timer_ovf_pending();

        /* reset all event counter */
        PMU->CTRL |= PMU_CTRL_EVENTCNT_RESET_Msk;

        /* configure event counter */
        do {
            uint_fast8_t chCounter = PMU->TYPE & PMU_TYPE_NUM_CNTS_Msk;
            chCounter = MIN(chCounter, __PMU_NUM_EVENTCNT);
            
            if (chCounter >= 2) {
                /* 32 bit counter for instruction architecturally executed */
                PMU->EVTYPER[0] = ARM_PMU_INST_RETIRED;
                PMU->EVTYPER[1] = ARM_PMU_CHAIN;

                /* clear counter 0/1 overflow flag */
                PMU->OVSCLR = PMU_OVSCLR_CNT0_STATUS_Msk
                            | PMU_OVSCLR_CNT1_STATUS_Msk;

                /* enable counter 1 interrupt */
                PMU->INTENSET = PMU_INTENSET_CNT1_ENABLE_Msk;

                /* enable counter 0/1 */
                PMU->CNTENSET = PMU_CNTENSET_CNT0_ENABLE_Msk
                              | PMU_CNTENSET_CNT1_ENABLE_Msk;
            }

            if (chCounter >= 4) {
                /* 32bit counter for all Data memory Accesses */
                PMU->EVTYPER[2] = ARM_PMU_MEM_ACCESS;
                PMU->EVTYPER[3] = ARM_PMU_CHAIN;

                /* clear counter 2/3 overflow flag */
                PMU->OVSCLR = PMU_OVSCLR_CNT2_STATUS_Msk
                            | PMU_OVSCLR_CNT3_STATUS_Msk;

                /* enable counter 3 interrupt */
                PMU->INTENSET = PMU_INTENSET_CNT3_ENABLE_Msk;

                /* enable counter 2/3 */
                PMU->CNTENSET = PMU_CNTENSET_CNT2_ENABLE_Msk
                              | PMU_CNTENSET_CNT3_ENABLE_Msk;
            }

            if (chCounter >= 6) {
                /* 32bit counter for all Data memory Accesses */
                PMU->EVTYPER[4] = ARM_PMU_L1D_CACHE_REFILL;
                PMU->EVTYPER[5] = ARM_PMU_CHAIN;

                /* clear counter 4/5 overflow flag */
                PMU->OVSCLR = PMU_OVSCLR_CNT4_STATUS_Msk
                            | PMU_OVSCLR_CNT5_STATUS_Msk;

                /* enable counter 5 interrupt */
                PMU->INTENSET = PMU_INTENSET_CNT5_ENABLE_Msk;

                /* enable counter 4/5 */
                PMU->CNTENSET = PMU_CNTENSET_CNT4_ENABLE_Msk
                              | PMU_CNTENSET_CNT5_ENABLE_Msk;

            }

            if (chCounter > 6) {
                for (uint_fast8_t n = 6; n < chCounter; n++) {
                    uint32_t wMask = (1<<n);

                    PMU->OVSCLR = wMask;        /* clear overflow flag */
                    PMU->INTENSET = wMask;      /* enable interrupt */
                    PMU->CNTENSET = wMask;      /* enable counter */
                }
            }

        } while(0);

        DCB->DEMCR |= DCB_DEMCR_UMON_EN_Msk         |
                      DCB_DEMCR_SDME_Msk            |
                      DCB_DEMCR_TRCENA_Msk          |
                      DCB_DEMCR_MON_EN_Msk          ;

        /* enable PMU Cycle Counter interrupt */
        PMU->INTENSET = PMU_INTENSET_CCYCNT_ENABLE_Msk;

        PMU->CNTENSET = PMU_CNTENSET_CCNTR_ENABLE_Msk;
        PMU->CTRL |= PMU_CTRL_ENABLE_Msk;
        
        /* force to disable DWT */
        DWT->CTRL = 0;
    }
    
    return true;
}

uint64_t perfc_pmu_get_instruction_count(void)
{
    uint32_t wHigh16, wLow16;
    uint64_t dwResult;
    bool bIsOverflow = false;
    __IRQ_SAFE {
        do {
            wHigh16 = PMU->EVCNTR[1];
            wLow16 = PMU->EVCNTR[0];
        } while(wHigh16 < PMU->EVCNTR[1]);
        dwResult = s_dwEventCounter[PMU_CNT_INSTRUCTION];
        bIsOverflow = (0 != (PMU->OVSCLR & PMU_OVSCLR_CNT1_STATUS_Msk));
    }

    dwResult += wLow16 | (wHigh16 << 16);
    
    if (bIsOverflow) {
        dwResult += (uint64_t)1<<32;
    }

    /* force to disable DWT */
    DWT->CTRL = 0;

    return dwResult;
}

uint64_t perfc_pmu_get_memory_access_count(void)
{
    uint32_t wHigh16, wLow16;
    uint64_t dwResult;
    bool bIsOverflow = false;

    __IRQ_SAFE {
        do {
            wHigh16 = PMU->EVCNTR[3];
            wLow16 = PMU->EVCNTR[2];
        } while(wHigh16 < PMU->EVCNTR[3]);
        dwResult = s_dwEventCounter[PMU_CNT_MEM_ACCESS];
        bIsOverflow = (0 != (PMU->OVSCLR & PMU_OVSCLR_CNT3_STATUS_Msk));
    }

    dwResult += wLow16 | (wHigh16 << 16);
    
    if (bIsOverflow) {
        dwResult += (uint64_t)1<<32;
    }

    /* force to disable DWT */
    DWT->CTRL = 0;

    return dwResult;
}


uint64_t perfc_pmu_get_L1_dcache_refill_count(void)
{
    uint32_t wHigh16, wLow16;
    uint64_t dwResult;
    bool bIsOverflow = false;

    __IRQ_SAFE {
        do {
            wHigh16 = PMU->EVCNTR[5];
            wLow16 = PMU->EVCNTR[4];
        } while(wHigh16 < PMU->EVCNTR[5]);
        dwResult = s_dwEventCounter[PMU_CNT_L1_DCACHE_REFILL];
        bIsOverflow = (0 != (PMU->OVSCLR & PMU_OVSCLR_CNT5_STATUS_Msk));
    }

    dwResult += wLow16 | (wHigh16 << 16);
    
    if (bIsOverflow) {
        dwResult += (uint64_t)1<<32;
    }

    /* force to disable DWT */
    DWT->CTRL = 0;

    return dwResult;
}

uint32_t perfc_port_get_system_timer_freq(void)
{
    extern uint32_t SystemCoreClock;

    /* return the system timer frequency */
    return SystemCoreClock;
}

bool perfc_port_is_system_timer_ovf_pending(void)
{
    /* whether the system timer overflow is pending */
    return PMU->OVSSET & PMU_OVSSET_CYCCNT_STATUS_Msk;
}

int64_t perfc_port_get_system_timer_top(void)
{
    /* the top value of the counting */
    return 0xFFFFFFFF;
}

int64_t perfc_port_get_system_timer_elapsed(void)
{
    return (int64_t)PMU->CCNTR;//ARM_PMU_Get_CCNTR();
}

void perfc_port_clear_system_timer_ovf_pending(void)
{
    PMU->OVSCLR = PMU_OVSCLR_CYCCNT_STATUS_Msk;
}

void perfc_port_stop_system_timer_counting(void)
{
    /* stop the system timer */
    PMU->CNTENCLR = PMU_CNTENCLR_CCNTR_ENABLE_Msk;
}

void perfc_port_clear_system_timer_counter(void)
{
    /* clear the system timer counter */
    PMU->CTRL |= PMU_CTRL_CYCCNT_RESET_Msk;
}

__WEAK
__attribute__((noinline))
uintptr_t __perfc_port_get_sp(void)
{
    return __get_MSP();
}

__WEAK
__attribute__((noinline))
void __perfc_port_set_sp(uintptr_t nSP)
{
    __set_MSP(nSP);
}

#endif


