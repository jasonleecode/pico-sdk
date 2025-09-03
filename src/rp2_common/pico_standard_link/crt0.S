/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

.syntax unified
.cpu cortex-m33
.thumb

// 对于RP2350，这个crt0可能不需要特殊处理
// 因为RT-Thread已经提供了启动代码

.section .text.crt0

// 空的crt0实现
.global _crt0_init
.type _crt0_init, %function
_crt0_init:
    bx lr
