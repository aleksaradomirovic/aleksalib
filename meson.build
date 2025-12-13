# Copyright (C) 2025  Aleksa Radomirovic
# SPDX-License-Identifier: BSD-3-Clause

project('aleksalib',
        'c',
        default_options: { 'b_lto': true, 'c_std': 'gnu23', 'debug': true, 'optimization': 'g' }
        )

add_project_arguments('-ffat-lto-objects', language: [ 'c' ])

build_tests = not meson.is_subproject()
if build_tests
    add_languages('cpp', required: true, native: false)
    gtest_dep = dependency('gtest', native: false)
    gtest_main_dep = dependency('gtest_main', native: false)

    if (not gtest_dep.found()) or (not gtest_main_dep.found())
        gtest_proj = subproject('gtest')
        gtest_dep = gtest.get_variable('gtest_dep')
        gtest_main_dep = gtest.get_variable('gtest_main_dep')
    endif

    gtest = declare_dependency(dependencies: [ gtest_dep, gtest_main_dep ])
endif

subdir('modules/struct')

subdir('modules/concurrent')
subdir('modules/filesystem')
