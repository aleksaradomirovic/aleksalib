/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SHARED_FIELD_H_
#define SHARED_FIELD_H_


#include "refcount.h"

#ifdef __cplusplus
extern "C" {
#endif


struct shared_field {
    refcount_t refcount;
    unsigned char data[];
};

int shared_field_alloc(struct shared_field **__restrict__ field_ptr, size_t data_size, size_t init_refs);
void shared_field_hardfree(struct shared_field *__restrict__ field);

void shared_field_incref(struct shared_field *field);
void shared_field_decref(struct shared_field *field);


#ifdef __cplusplus
}
#endif


#endif
