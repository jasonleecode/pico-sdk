/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/malloc.h"
#include <stdlib.h>

// 对于RP2350，使用标准的malloc实现
// 这些函数只是标准库函数的包装

void *pico_malloc(size_t size) {
    return malloc(size);
}

void pico_free(void *ptr) {
    free(ptr);
}

void *pico_calloc(size_t count, size_t size) {
    return calloc(count, size);
}

void *pico_realloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}
