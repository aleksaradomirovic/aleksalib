/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "blocking_queue.h"

#include <errno.h>

void blocking_queue_init(struct blocking_queue *__restrict__ queue) {
    *queue = BLOCKING_QUEUE_INITIALIZER;
}

void blocking_queue_free(struct blocking_queue *__restrict__ queue) {
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->cond);
    queue_free(&queue->queue);
    *queue = BLOCKING_QUEUE_INITIALIZER;
}

int blocking_queue_enqueue(struct blocking_queue *__restrict__ queue, const void *__restrict__ data, size_t data_size) {
    int pthread_status, status;
    pthread_status = pthread_mutex_lock(&queue->mutex);
    if(pthread_status) {
        return pthread_status;
    }

    status = queue_enqueue(&queue->queue, data, data_size);
    pthread_status = pthread_cond_signal(&queue->cond);
    if(pthread_status) {
        pthread_mutex_unlock(&queue->mutex);
        return pthread_status;
    }

    pthread_status = pthread_mutex_unlock(&queue->mutex);
    if(pthread_status) {
        return pthread_status;
    }

    return status;
}

int blocking_queue_trydequeue(struct blocking_queue *__restrict__ queue, void *__restrict__ data, size_t data_size) {
    int pthread_status, status;
    pthread_status = pthread_mutex_lock(&queue->mutex);
    if(pthread_status) {
        return pthread_status;
    }

    status = queue_dequeue(&queue->queue, data, data_size);

    pthread_status = pthread_mutex_unlock(&queue->mutex);
    if(pthread_status) {
        return pthread_status;
    }

    return status;
}

int blocking_queue_dequeue(struct blocking_queue *__restrict__ queue, void *__restrict__ data, size_t data_size) {
    int pthread_status, status;
    pthread_status = pthread_mutex_lock(&queue->mutex);
    if(pthread_status) {
        return pthread_status;
    }

    while(true) {
        status = queue_dequeue(&queue->queue, data, data_size);
        if(status != EWOULDBLOCK) {
            break;
        }

        pthread_status = pthread_cond_wait(&queue->cond, &queue->mutex);
        if(pthread_status) {
            pthread_mutex_unlock(&queue->mutex);
            return pthread_status;
        }
    }

    pthread_status = pthread_mutex_unlock(&queue->mutex);
    if(pthread_status) {
        return pthread_status;
    }

    return status;
}
