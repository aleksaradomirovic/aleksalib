/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_


#include "vector_list.h"

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


struct task {
    void (*task_routine)(void *arg);
    void *task_arg;
};

struct thread_pool {
    struct vector_list threads;
};

int thread_pool_init(struct thread_pool *__restrict__ thread_pool, size_t nproc, void (*task_routine)(void *arg), void *task_arg);
void thread_pool_stopjoin(struct thread_pool *__restrict__ thread_pool);
void thread_pool_join(struct thread_pool *__restrict__ thread_pool);


#ifdef __cplusplus
}
#endif


#endif
