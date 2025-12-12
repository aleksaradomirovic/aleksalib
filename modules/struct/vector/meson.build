# Copyright (C) 2025  Aleksa Radomirovic
# SPDX-License-Identifier: BSD-3-Clause

vector = declare_dependency(sources: [ 'src/vector.c', 'src/vector_list.c' ], include_directories: [ 'include' ])

if build_tests
    vector_test = executable('vector_test', 'test/vector_test.cpp', dependencies: [ vector, gtest ])
endif
