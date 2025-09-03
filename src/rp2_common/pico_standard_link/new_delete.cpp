/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <new>
#include <cstdlib>

// 对于RP2350，使用标准的new/delete实现
// 这些函数只是标准库函数的包装

void *operator new(size_t size) {
    return malloc(size);
}

void operator delete(void *ptr) noexcept {
    free(ptr);
}

void *operator new[](size_t size) {
    return malloc(size);
}

void operator delete[](void *ptr) noexcept {
    free(ptr);
}
