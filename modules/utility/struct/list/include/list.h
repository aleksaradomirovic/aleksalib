/**
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LIST_H_
#define LIST_H_


#include "iterator.h"

#include <stddef.h>

struct list_node;

struct list {
    struct list_node *head, *tail;
};

#define LIST_INITIALIZER (struct list) { .head = NULL, .tail = NULL }

void list_init(struct list *restrict list);
void list_free(struct list *restrict list);

int list_add_head(struct list *restrict list, const void *restrict element_ptr, size_t element_size);
int list_add_tail(struct list *restrict list, const void *restrict element_ptr, size_t element_size);
int list_remove_head(struct list *restrict list, void *restrict element_ptr, size_t element_size);
int list_remove_tail(struct list *restrict list, void *restrict element_ptr, size_t element_size);

int list_foreach(struct list *restrict list, iterator_t *iterator_function, void *iterator_arg, size_t element_size);


#endif
