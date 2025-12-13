/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "executor.h"

static void executor_kill_routine(void *) {
    pthread_exit(NULL);
}

static const struct task executor_kill_task = {
    .task_routine = executor_kill_routine,
};

static void executor_routine(void *arg) {
    struct blocking_queue *queue = arg;
    while(true) {
        struct task task;
        if(blocking_queue_dequeue(queue, &task, sizeof(task))) {
            continue;
        }

        task.task_routine(task.task_arg);
    }
}

int executor_init(struct executor *__restrict__ executor, size_t nproc) {
    executor->task_queue = BLOCKING_QUEUE_INITIALIZER;
    int status = thread_pool_init(&executor->thread_pool, nproc, executor_routine, &executor->task_queue);
    if(status) {
        return status;
    }

    return 0;
}

void executor_stopjoin(struct executor *__restrict__ executor) {
    size_t nproc = vector_list_elements(&executor->thread_pool.threads, sizeof(pthread_t));
    for(size_t i = 0; i < nproc;) {
        if(blocking_queue_enqueue(&executor->task_queue, &executor_kill_task, sizeof(executor_kill_task))) {
            continue;
        }

        i++;
    }

    thread_pool_join(&executor->thread_pool);
}

int executor_enqueue_task(struct executor *executor, void (*task_routine)(void *arg), void *task_arg) {
    struct task task = { .task_routine = task_routine, .task_arg = task_arg };
    return blocking_queue_enqueue(&executor->task_queue, &task, sizeof(task));
}
