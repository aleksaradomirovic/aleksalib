/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef VECTOR_LIST_H_
#define VECTOR_LIST_H_


#include "vector.h"

#ifdef __cplusplus
extern "C" {
#endif


struct vector_list {
    struct vector vector;
    size_t count;
};

#define VECTOR_LIST_INITIALIZER (struct vector_list) { .vector = VECTOR_INITIALIZER, .count = 0 }

void vector_list_init(struct vector_list *__restrict__ list);
void vector_list_free(struct vector_list *__restrict__ list);

int vector_list_append(struct vector_list *__restrict__ list, void **__restrict__ ptr, size_t count, size_t size);

size_t vector_list_elements(const struct vector_list *__restrict__ list, size_t size);


#ifdef __cplusplus
}
#endif


#endif
