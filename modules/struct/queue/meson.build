# Copyright (C) 2025  Aleksa Radomirovic
# SPDX-License-Identifier: BSD-3-Clause

queue = declare_dependency(sources: [ 'src/queue.c', 'src/blocking_queue.c' ], include_directories: [ 'include' ])

if build_tests
    queue_test = executable('queue_test', 'test/queue_test.cpp', dependencies: [ queue, gtest ])
endif
