/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <gtest/gtest.h>

extern "C" {
#   include "queue.h"
#   include "blocking_queue.h"
}

TEST(queue, init) {
    struct queue queue = QUEUE_INITIALIZER;
    EXPECT_TRUE(queue_empty(&queue));
    ASSERT_EQ(queue_dequeue(&queue, NULL, 0), EWOULDBLOCK);
    queue_free(&queue);
}

TEST(queue, fill) {
    struct queue queue = QUEUE_INITIALIZER;
    ASSERT_EQ(queue_enqueue(&queue, NULL, 8), 0);
    EXPECT_FALSE(queue_empty(&queue));

    EXPECT_NE(queue.head, nullptr);
    EXPECT_NE(queue.tail, nullptr);

    queue_free(&queue);
}

TEST(queue, fill_and_empty) {
    struct queue queue = QUEUE_INITIALIZER;
    ASSERT_EQ(queue_enqueue(&queue, NULL, 8), 0);
    ASSERT_EQ(queue_dequeue(&queue, NULL, 8), 0);
    EXPECT_TRUE(queue_empty(&queue));
    ASSERT_EQ(queue_dequeue(&queue, NULL, 0), EWOULDBLOCK);

    EXPECT_EQ(queue.head, nullptr);
    EXPECT_EQ(queue.tail, nullptr);

    queue_free(&queue);
}

TEST(blocking_queue, init) {
    struct blocking_queue queue = BLOCKING_QUEUE_INITIALIZER;
    ASSERT_EQ(blocking_queue_trydequeue(&queue, NULL, 0), EWOULDBLOCK);
    blocking_queue_free(&queue);
}

TEST(blocking_queue, fill_and_empty) {
    struct blocking_queue queue = BLOCKING_QUEUE_INITIALIZER;
    ASSERT_EQ(blocking_queue_enqueue(&queue, NULL, 8), 0);
    ASSERT_EQ(blocking_queue_trydequeue(&queue, NULL, 8), 0);
    ASSERT_EQ(blocking_queue_trydequeue(&queue, NULL, 0), EWOULDBLOCK);
    blocking_queue_free(&queue);
}
