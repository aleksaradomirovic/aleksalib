/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <gtest/gtest.h>

extern "C" {
#   include "vector.h"
#   include "vector_list.h"
}

TEST(vector, allocate) {
    struct vector vec = VECTOR_INITIALIZER;
    ASSERT_EQ(vector_guarantee_size(&vec, 10), 0);
    EXPECT_NE(vec.data, nullptr);
    EXPECT_GE(vec.size, 10);
    vector_free(&vec);
}

TEST(vector, reallocate) {
    struct vector vec = VECTOR_INITIALIZER;
    ASSERT_EQ(vector_guarantee_size(&vec, 10), 0);
    EXPECT_NE(vec.data, nullptr);
    EXPECT_GE(vec.size, 10);
    size_t nsize = vec.size + 10;
    ASSERT_EQ(vector_guarantee_size(&vec, nsize), 0);
    EXPECT_NE(vec.data, nullptr);
    EXPECT_GE(vec.size, nsize);
    vector_free(&vec);
}

TEST(vector_list, allocate) {
    struct vector_list list = VECTOR_LIST_INITIALIZER;
    void *ptr = nullptr;
    ASSERT_EQ(vector_list_append(&list, &ptr, 1, 10), 0);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(list.count, 10);
    EXPECT_EQ(vector_list_elements(&list, 10), 1);
    EXPECT_NE(list.vector.data, nullptr);
    EXPECT_GE(list.vector.size, 10);
    vector_list_free(&list);
}

TEST(vector_list, allocate_multi) {
    struct vector_list list = VECTOR_LIST_INITIALIZER;
    void *ptr[2] = { nullptr };
    ASSERT_EQ(vector_list_append(&list, ptr, 2, 10), 0);
    EXPECT_NE(ptr[0], nullptr);
    EXPECT_NE(ptr[1], nullptr);
    EXPECT_EQ(list.count, 20);
    EXPECT_EQ(vector_list_elements(&list, 10), 2);
    EXPECT_NE(list.vector.data, nullptr);
    EXPECT_GE(list.vector.size, 20);
    vector_list_free(&list);
}

TEST(vector_list, reallocate) {
    struct vector_list list = VECTOR_LIST_INITIALIZER;
    void *ptr = nullptr;
    ASSERT_EQ(vector_list_append(&list, &ptr, 1, 10), 0);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(list.count, 10);
    EXPECT_NE(list.vector.data, nullptr);
    EXPECT_GE(list.vector.size, 10);

    ASSERT_EQ(vector_list_append(&list, &ptr, 1, 10), 0);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(list.count, 20);
    EXPECT_NE(list.vector.data, nullptr);
    EXPECT_GE(list.vector.size, 20);

    vector_list_free(&list);
}
