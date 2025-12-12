/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "vector_list.h"

#include <errno.h>
#include <stdckdint.h>

void vector_list_init(struct vector_list *__restrict__ list) {
    *list = VECTOR_LIST_INITIALIZER;
}

void vector_list_free(struct vector_list *__restrict__ list) {
    vector_free(&list->vector);
    *list = VECTOR_LIST_INITIALIZER;
}

int vector_list_append(struct vector_list *__restrict__ list, void **__restrict__ ptr, size_t count, size_t size) {
    size_t total_append;
    if(ckd_mul(&total_append, count, size)) {
        return EOVERFLOW;
    }

    size_t old_size = list->count;
    size_t total_size;
    if(ckd_add(&total_size, old_size, total_append)) {
        return EOVERFLOW;
    }

    int status;
    status = vector_guarantee_size(&list->vector, total_size);
    if(status) {
        return status;
    }

    list->count = total_size;
    if(ptr) {
        for(size_t i = 0; i < count; i++) {
            ptr[i] = list->vector.data + old_size + (i * size);
        }
    }
    return 0;
}

size_t vector_list_elements(const struct vector_list *__restrict__ list, size_t size) {
    return list->count / size;
}
