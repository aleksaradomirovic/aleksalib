# Copyright (C) 2025  Aleksa Radomirovic
# SPDX-License-Identifier: BSD-3-Clause

executor = declare_dependency(sources: [ 'src/executor.c' ], include_directories: [ 'include' ], dependencies: [ thread_pool, queue ])

if build_tests
    executor_test = executable('executor_test', 'test/executor_test.cpp', dependencies: [ executor, gtest ])
    test('executor_test', executor_test)
endif
