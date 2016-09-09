#!/bin/bash
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
# 
#   http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#

# Called with following variables set:
#  - BSP_PATH is absolute path to hw/bsp/bsp_name
#  - BIN_BASENAME is the path to prefix to target binary,
#    .elf appended to name is the ELF file
#  - IMAGE_SLOT is the image slot to download to
#  - FEATURES holds the target features string
#  - EXTRA_JTAG_CMD holds extra parameters to pass to jtag software
#

if [ -z "$BIN_BASENAME" ]; then
    echo "Need binary to download"
    exit 1
fi

IS_BOOTLOADER=0

# Look for 'bootloader' in FEATURES
for feature in $FEATURES; do
    if [ $feature == "bootloader" ]; then
        IS_BOOTLOADER=1
    fi
done

if [ $IS_BOOTLOADER -eq 1 ]; then
    FLASH_OFFSET=0x08000000
    FILE_NAME=$BIN_BASENAME.elf.bin
else
    FLASH_OFFSET=0x08009000
    FILE_NAME=$BIN_BASENAME.img
fi

echo "Downloading" $FILE_NAME "to" $FLASH_OFFSET

openocd -f board/stm32f3discovery.cfg -c "$EXTRA_JTAG_CMD" -c init -c "reset halt" -c "flash write_image erase $FILE_NAME $FLASH_OFFSET" -c "reset run" -c shutdown

