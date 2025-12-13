# Copyright (C) 2025  Aleksa Radomirovic
# SPDX-License-Identifier: BSD-3-Clause

refcount = declare_dependency(sources: [ 'src/refcount.c', 'src/shared_field.c' ], include_directories: [ 'include' ])

if build_tests
    refcount_test = executable('refcount_test', 'test/refcount_test.cpp', dependencies: [ refcount, gtest ])
    test('refcount_test', refcount_test)
endif
