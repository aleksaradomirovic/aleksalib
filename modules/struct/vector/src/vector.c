/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "vector.h"

#include <errno.h>
#include <stdlib.h>

void vector_init(struct vector *__restrict__ vector) {
    *vector = VECTOR_INITIALIZER;
}

void vector_free(struct vector *__restrict__ vector) {
    free(vector->data);
    *vector = VECTOR_INITIALIZER;
}

int vector_guarantee_size(struct vector *__restrict__ vector, size_t size) {
    if(vector->size >= size) {
        return 0;
    }

    void *ndata = realloc(vector->data, size);
    if(!ndata) {
        __builtin_assume(errno);
        return errno;
    }

    vector->data = ndata;
    vector->size = size;
    return 0;
}
