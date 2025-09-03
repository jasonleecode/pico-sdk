/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/float.h"

void float_init_rom(void) {
    // 对于RP2350，浮点初始化可能不需要特殊处理
    // 因为Cortex-M33的浮点单元在启动时已经初始化
}
