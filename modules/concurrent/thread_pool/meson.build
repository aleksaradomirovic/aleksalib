# Copyright (C) 2025  Aleksa Radomirovic
# SPDX-License-Identifier: BSD-3-Clause

thread_pool = declare_dependency(sources: [ 'src/thread_pool.c' ], include_directories: [ 'include' ], dependencies: [ vector, refcount ])

if build_tests
    thread_pool_test = executable('thread_pool_test', 'test/thread_pool_test.cpp', dependencies: [ thread_pool, gtest ])
    test('thread_pool_test', thread_pool_test)
endif
