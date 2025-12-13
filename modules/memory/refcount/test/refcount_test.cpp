/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <gtest/gtest.h>

extern "C" {
#   include "refcount.h"
#   include "shared_field.h"
}

TEST(refcount, ref_unref) {
    refcount_t refs;
    refcount_set(&refs, 2);
    ASSERT_EQ(refcount_dec(&refs), true);
    ASSERT_EQ(refcount_dec(&refs), false);
}

TEST(shared_field, ref_unref) {
    struct shared_field *field;
    ASSERT_EQ(shared_field_alloc(&field, 10, 2), 0);
    shared_field_decref(field);
    shared_field_decref(field);
}
