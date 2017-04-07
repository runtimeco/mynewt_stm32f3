/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#ifndef H_BSP_H
#define H_BSP_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Define special stackos sections */
#define sec_data_core   __attribute__((section(".data.core")))
#define sec_bss_core    __attribute__((section(".bss.core")))
#define sec_bss_nz_core __attribute__((section(".bss.core.nz")))

/* More convenient section placement macros. */
#define bssnz_t         sec_bss_nz_core

/*
 * Symbols from linker script.
 */
extern uint8_t _sram_start;
extern uint8_t _ccram_start;

#define SRAM_SIZE (40 * 1024)
#define CCRAM_SIZE (8 *1024)

/* LED pins */
#define LED_BLINK_PIN_1   (72)
#define LED_BLINK_PIN_2   (73)
#define LED_BLINK_PIN_3   (74)
#define LED_BLINK_PIN_4   (75)
#define LED_BLINK_PIN_5   (76)
#define LED_BLINK_PIN_6   (77)
#define LED_BLINK_PIN_7   (78)
#define LED_BLINK_PIN_8   (79)
    
#define LED_BLINK_PIN LED_BLINK_PIN_1
    

/* UART ports */
#define UART_CNT        1
#define CONSOLE_UART    0

/* This defines the maximum NFFS areas (block) are in the BSPs NFS file 
 * system space.  This in conjunction with flash map determines how 
 * many NFS blocks there will be.  A minimum is the number of individually
 * erasable sectors in the flash area and the maximum is this number. If
 * your max is less than the number of sectors then the NFFS will combine
 * multiple sectors into an NFFS area */
#define NFFS_AREA_MAX    (8)

#ifdef __cplusplus
}
#endif

#endif  /* H_BSP_H */
