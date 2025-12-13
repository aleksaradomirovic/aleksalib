/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <gtest/gtest.h>

extern "C" {
#   include "executor.h"
}

TEST(executor, init_join) {
    struct executor executor;
    ASSERT_EQ(executor_init(&executor, 0), 0);
    executor_stopjoin(&executor);
}

static void dummy_task(void *) {
}

TEST(executor, init_task_join) {
    struct executor executor;
    ASSERT_EQ(executor_init(&executor, 0), 0);
    ASSERT_EQ(executor_enqueue_task(&executor, dummy_task, NULL), 0);
    executor_stopjoin(&executor);
}
