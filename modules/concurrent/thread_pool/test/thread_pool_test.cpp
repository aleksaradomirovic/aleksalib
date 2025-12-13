/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <gtest/gtest.h>

extern "C" {
#   include "thread_pool.h"
}

static void init_join_routine(void *) {}

TEST(thread_pool, init_join) {
    struct thread_pool thread_pool;
    ASSERT_EQ(thread_pool_init(&thread_pool, 0, init_join_routine, NULL), 0);
    thread_pool_join(&thread_pool);
}
