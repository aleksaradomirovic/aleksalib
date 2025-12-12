/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef VECTOR_H_
#define VECTOR_H_


#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


struct vector {
    void *data;
    size_t size;
};

#define VECTOR_INITIALIZER (struct vector) { .data = NULL, .size = 0 }

void vector_init(struct vector *__restrict__ vector);
void vector_free(struct vector *__restrict__ vector);

int vector_guarantee_size(struct vector *__restrict__ vector, size_t size);


#ifdef __cplusplus
}
#endif


#endif
