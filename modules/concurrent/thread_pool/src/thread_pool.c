/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "thread_pool.h"

#include <stdint.h>
#include <unistd.h>

static size_t get_nproc() {
    long nproc = sysconf(_SC_NPROCESSORS_ONLN);
    if(nproc <= 0) {
        nproc = 1;
    }
    if(nproc > SIZE_MAX) {
        nproc = SIZE_MAX;
    }

    return (size_t) nproc;
}

static void * thread_pool_routine(void *arg) {
    struct thread_pool *thread_pool = arg;
    thread_pool->task.task_routine(thread_pool->task.task_arg);
    return NULL;
}

int thread_pool_init(struct thread_pool *__restrict__ thread_pool, size_t nproc, void (*task_routine)(void *arg), void *task_arg) {
    thread_pool->threads = VECTOR_LIST_INITIALIZER;
    thread_pool->task.task_routine = task_routine;
    thread_pool->task.task_arg = task_arg;

    if(nproc <= 0) {
        nproc = get_nproc();
    }

    int status = vector_list_append(&thread_pool->threads, NULL, nproc, sizeof(pthread_t));
    if(status) {
        return status;
    }

    pthread_t *threads = thread_pool->threads.vector.data;
    for(size_t i = 0; i < nproc; i++) {
        int pthread_status = pthread_create(threads + i, NULL, thread_pool_routine, thread_pool);
        if(pthread_status) {
            for(size_t j = i; j > 0;) {
                j--;
                pthread_cancel(threads[j]);
                pthread_join(threads[j], NULL);
            }
            return pthread_status;
        }
    }

    return 0;
}

static void thread_pool_stop(struct thread_pool *__restrict__ thread_pool) {
    pthread_t *threads = thread_pool->threads.vector.data;
    size_t nproc = vector_list_elements(&thread_pool->threads, sizeof(pthread_t));

    for(size_t i = 0; i < nproc; i++) {
        pthread_cancel(threads[i]);
    }
}

void thread_pool_stopjoin(struct thread_pool *__restrict__ thread_pool) {
    thread_pool_stop(thread_pool);
    thread_pool_join(thread_pool);
}

void thread_pool_join(struct thread_pool *__restrict__ thread_pool) {
    pthread_t *threads = thread_pool->threads.vector.data;
    size_t nproc = vector_list_elements(&thread_pool->threads, sizeof(pthread_t));

    for(size_t i = 0; i < nproc; i++) {
        pthread_join(threads[i], NULL);
    }

    vector_list_free(&thread_pool->threads);
}
