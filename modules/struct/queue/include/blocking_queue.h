/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BLOCKING_QUEUE_H_
#define BLOCKING_QUEUE_H_


#include "queue.h"

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


struct blocking_queue {
    struct queue queue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

#define BLOCKING_QUEUE_INITIALIZER (struct blocking_queue) { .queue = QUEUE_INITIALIZER, .mutex = PTHREAD_MUTEX_INITIALIZER, .cond = PTHREAD_COND_INITIALIZER }

void blocking_queue_init(struct blocking_queue *__restrict__ queue);
void blocking_queue_free(struct blocking_queue *__restrict__ queue);

int blocking_queue_enqueue(struct blocking_queue *__restrict__ queue, const void *__restrict__ data, size_t data_size);
int blocking_queue_dequeue(struct blocking_queue *__restrict__ queue, void *__restrict__ data, size_t data_size);
int blocking_queue_trydequeue(struct blocking_queue *__restrict__ queue, void *__restrict__ data, size_t data_size);


#ifdef __cplusplus
}
#endif


#endif
