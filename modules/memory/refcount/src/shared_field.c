/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "shared_field.h"

#include <errno.h>
#include <stdckdint.h>
#include <stdlib.h>

int shared_field_alloc(struct shared_field **__restrict__ field_ptr, size_t data_size, size_t init_refs) {
    if(init_refs == 0) {
        return 0;
    }

    size_t alloc_size;
    if(ckd_add(&alloc_size, data_size, sizeof(struct shared_field))) {
        return EOVERFLOW;
    }

    struct shared_field *field = malloc(alloc_size);
    if(!field) {
        __builtin_assume(errno);
        return errno;
    }

    refcount_set(&field->refcount, init_refs);

    *field_ptr = field;
    return 0;
}

void shared_field_hardfree(struct shared_field *__restrict__ field) {
    free(field);
}

void shared_field_incref(struct shared_field *field) {
    refcount_inc(&field->refcount);
}

void shared_field_decref(struct shared_field *field) {
    if(!refcount_dec(&field->refcount)) {
        shared_field_hardfree(field);
    }
}
