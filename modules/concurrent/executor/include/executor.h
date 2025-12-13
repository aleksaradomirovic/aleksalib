/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef EXECUTOR_H_
#define EXECUTOR_H_


#include <stdatomic.h>

#include "blocking_queue.h"
#include "thread_pool.h"

#ifdef __cplusplus
extern "C" {
#endif


struct executor {
    struct thread_pool thread_pool;
    struct blocking_queue task_queue;
};

int executor_init(struct executor *__restrict__ executor, size_t nproc);
void executor_stopjoin(struct executor *__restrict__ executor);

int executor_enqueue_task(struct executor *executor, void (*task_routine)(void *arg), void *task_arg);


#ifdef __cplusplus
}
#endif


#endif
