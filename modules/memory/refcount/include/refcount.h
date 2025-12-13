/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef REFCOUNT_H_
#define REFCOUNT_H_


#include <stdatomic.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef atomic_size_t refcount_t;

void refcount_set(refcount_t *refcount, size_t count);

void refcount_inc(refcount_t *refcount);
bool refcount_dec(refcount_t *refcount);


#ifdef __cplusplus
}
#endif


#endif
