/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "refcount.h"

void refcount_set(refcount_t *refcount, size_t count) {
    atomic_store_explicit(refcount, count, memory_order_release);
}

static void refcount_add(refcount_t *refcount, size_t count) {
    atomic_fetch_add_explicit(refcount, count, memory_order_acquire);
}

void refcount_inc(refcount_t *refcount) {
    refcount_add(refcount, 1);
}

static bool refcount_sub(refcount_t *refcount, size_t count) {
    size_t new_count = atomic_fetch_sub_explicit(refcount, count, memory_order_release) - count;
    return (new_count > 0);
}

bool refcount_dec(refcount_t *refcount) {
    return refcount_sub(refcount, 1);
}
