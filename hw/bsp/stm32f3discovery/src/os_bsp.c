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
#include <sys/types.h>
#include <hal/flash_map.h>
#include <hal/hal_bsp.h>

void _close(int fd);

/*
 * XXXX for now have it here.
 */
static struct flash_area bsp_flash_areas[] = {
    [FLASH_AREA_BOOTLOADER] = {
        .fa_flash_id = 0,       /* internal flash */
        .fa_off = 0x08000000,   /* beginning */
        .fa_size = (36 * 1024)
    },
    [FLASH_AREA_IMAGE_0] = {
        .fa_flash_id = 0,
        .fa_off = 0x08009000,
        .fa_size = (102 * 1024)
    },
    [FLASH_AREA_IMAGE_1] = {
        .fa_flash_id = 0,
        .fa_off = 0x08022800,
        .fa_size = (102 * 1024)
    },
    [FLASH_AREA_IMAGE_SCRATCH] = {
        .fa_flash_id = 0,
        .fa_off = 0x0803c000,
        .fa_size = (8 * 1024)
    },
    [FLASH_AREA_NFFS] = {
        .fa_flash_id = 0,
        .fa_off = 0x0803e000,
        .fa_size = (8 * 1024)
    }
};

int
bsp_imgr_current_slot(void)
{
    return FLASH_AREA_IMAGE_0;
}

void
bsp_init(void)
{
    /*
     * XXX these references are here to keep the functions in for libc to find.
     */
    _sbrk(0);
    _close(0);
    flash_area_init(bsp_flash_areas,
      sizeof(bsp_flash_areas) / sizeof(bsp_flash_areas[0]));
}
