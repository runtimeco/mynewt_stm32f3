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

#include "hal/hal_watchdog.h"
#include "mcu/stm32f30x.h"
#include "mcu/stm32f30x_iwdg.h"

struct stm_wdt_cfg
{
    uint8_t prescaler;
    uint16_t reload
};
struct stm_wdt_cfg g_wdt_cfg;

int
hal_watchdog_init(uint32_t expire_msecs)
{
    uint32_t reload;

    /* Max prescaler is 256 */
    reload = 32768 / 256;
    reload = (reload * expire_msecs) / 1000;

    /* Check to make sure we are not trying a reload value that is too large */
    if (reload > IWDG_RLR_RL) {
        return -1;
    }

    g_wdt_cfg.prescaler = IWDG_Prescaler_256;
    g_wdt_cfg.reload = reload;

    return 0;
}

void
hal_watchdog_enable(void)
{
    FlagStatus rc;

    DBGMCU->APB1FZ |= DBGMCU_IWDG_STOP;
    IWDG_Enable();
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(g_wdt_cfg.prescaler);
    IWDG_SetReload(g_wdt_cfg.reload);
    rc = SET;
    while (rc != RESET) {
        rc = IWDG_GetFlagStatus();
        /* XXX: need to break out of this somehow. */
    }
    IWDG_ReloadCounter();
}

void
hal_watchdog_tickle(void)
{
    HAL_IWDG_Refresh(&g_wdt_cfg);
}

