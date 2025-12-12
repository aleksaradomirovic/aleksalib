# Copyright (C) 2025  Aleksa Radomirovic
# SPDX-License-Identifier: BSD-3-Clause

filesystem = declare_dependency(sources: [ 'src/directory.c' ], include_directories: [ 'include' ])

if build_tests
    filesystem_test = executable('filesystem_test', 'test/filesystem_test.cpp', dependencies: [ filesystem, gtest ])
endif
