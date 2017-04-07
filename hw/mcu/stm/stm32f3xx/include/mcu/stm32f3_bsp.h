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

#ifndef __MCU_STM32F3_BSP_H_
#define __MCU_STM32F3_BSP_H_

/**
 * BSP specific UART settings.
 */
struct stm32f3_uart_cfg {
    USART_TypeDef *suc_uart;			/* UART dev registers */
    void (*suc_rcc_cmd)(uint32_t, FunctionalState); /* RCC function to call */
    uint32_t suc_rcc_dev;			/* RCC device ID */
    int8_t suc_pin_tx;				/* pins for IO */
    int8_t suc_pin_rx;
    int8_t suc_pin_rts;
    int8_t suc_pin_cts;
    uint8_t suc_pin_af;				/* AF selection for this */
    enum IRQn suc_irqn;				/* NVIC IRQn */
};

const struct stm32f3_uart_cfg *bsp_uart_config(int port);

/*
 * Internal API for stm32f3xx mcu specific code.
 */
int hal_gpio_init_af(int pin, uint8_t af_type, enum hal_gpio_pull pull);

struct hal_flash;
extern const struct hal_flash stm32f3_flash_dev;

#endif /* __MCU_STM32F3_BSP_H_ */
