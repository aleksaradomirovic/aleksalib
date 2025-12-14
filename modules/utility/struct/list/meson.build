# Copyright (C) 2025  Aleksa Radomirovic
# SPDX-License-Identifier: BSD-3-Clause

list = declare_dependency(sources: [ 'src/list.c' ], include_directories: [ 'include' ], dependencies: [ iterator ])

if build_tests
    list_test = executable('list_test', 'test/list_test.cpp', dependencies: [ list, gtest, gtest_main ])
    test('list_test', list_test)
endif
