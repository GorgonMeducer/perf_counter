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


/*============================ MACROS ========================================*/


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

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_PMU     Performance Monitoring Unit (PMU)
  \brief    Type definitions for the Performance Monitoring Unit (PMU)
  @{
 */

#define PMU_BASE          (0xE0003000UL)                                                   /*!< PMU Base Address */
#define PMU               ((PMU_Type       *)     PMU_BASE         )                       /*!< PMU configuration struct */

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

/*@} end of group CMSIS_PMU */

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

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

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/* low level interface for porting */
extern
uint32_t perfc_port_get_system_freq(void);
extern
int64_t perfc_port_get_system_timer_top(void);
extern
bool perfc_port_is_system_timer_ovf_pending(void);
extern
void perfc_port_init_system_timer(bool bTimerOccupied);
extern
int64_t perfc_port_get_system_timer_elapsed(void);
extern
void perfc_port_clear_system_timer_ovf_pending(void);
extern
void perfc_port_stop_system_timer_counting(void);
extern
void perfc_port_clear_system_timer_counter(void);

/*============================ INCLUDES ======================================*/

#include "m-profile/armv8m_pmu.h"

/*============================ IMPLEMENTATION ================================*/


#if __PERFC_USE_PMU_PORTING__
 
void perfc_port_init_system_timer(bool bIsTimeOccupied)
{
    UNUSED_PARAM(bIsTimeOccupied);

    __IRQ_SAFE {
        ARM_PMU_Disable();
        
        perfc_port_stop_system_timer_counting();
        perfc_port_clear_system_timer_counter();
        perfc_port_clear_system_timer_ovf_pending();

        ARM_PMU_CNTR_Enable(PMU_CNTENSET_CCNTR_ENABLE_Msk);
        ARM_PMU_Enable();
    }
}

uint32_t perfc_port_get_system_freq(void)
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
    ARM_PMU_Set_CNTR_OVS(PMU_OVSCLR_CYCCNT_STATUS_Msk);
}

void perfc_port_stop_system_timer_counting(void)
{
    /* stop the system timer */
    ARM_PMU_CNTR_Disable(PMU_CNTENCLR_CCNTR_ENABLE_Msk);
}

void perfc_port_clear_system_timer_counter(void)
{
    /* clear the system timer counter */
    ARM_PMU_CYCCNT_Reset();
}

#endif


