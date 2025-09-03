/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

.syntax unified
.cpu cortex-m33
.thumb

// 对于RP2350，这个shim可能不需要特殊处理
// 因为Cortex-M33的浮点单元已经内置支持

.section .text.float_v1_rom_shim

// 空的shim实现
.global float_v1_rom_shim_init
.type float_v1_rom_shim_init, %function
float_v1_rom_shim_init:
    bx lr
