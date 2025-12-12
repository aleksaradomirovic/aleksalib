/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef QUEUE_H_
#define QUEUE_H_


#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


struct queue_node;

struct queue {
    struct queue_node *head, *tail;
};

#define QUEUE_INITIALIZER (struct queue) { .head = NULL, .tail = NULL }

void queue_init(struct queue *__restrict__ queue);
void queue_free(struct queue *__restrict__ queue);

int queue_enqueue(struct queue *__restrict__ queue, const void *__restrict__ data, size_t data_size);
int queue_dequeue(struct queue *__restrict__ queue, void *__restrict__ data, size_t data_size);

bool queue_empty(struct queue *__restrict__ queue);


#ifdef __cplusplus
}
#endif


#endif
