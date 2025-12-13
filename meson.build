# Copyright (C) 2025  Aleksa Radomirovic
# SPDX-License-Identifier: BSD-3-Clause

project('aleksalib',
        'c',
        default_options: { 'b_lto': true, 'c_std': 'c23', 'debug': true, 'optimization': 'g' }
        )

add_project_arguments('-ffat-lto-objects', '-D_POSIX_C_SOURCE=202405L', language: [ 'c' ])

build_tests = not meson.is_subproject()
if build_tests
    add_languages('cpp', required: true, native: false)
    gtest_dep = dependency('gtest', fallback: 'gtest', native: false)
    gtest_main_dep = dependency('gtest_main', fallback: 'gtest', native: false)
    gtest = declare_dependency(dependencies: [ gtest_dep, gtest_main_dep ])
endif

subdir('modules/memory')
subdir('modules/struct')

subdir('modules/concurrent')
subdir('modules/filesystem')
