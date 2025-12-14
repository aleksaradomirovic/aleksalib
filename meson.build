# Copyright (C) 2025  Aleksa Radomirovic
# SPDX-License-Identifier: BSD-3-Clause

project('aleksalib',
        'c',
        default_options: { 'b_lto': true, 'c_std': 'c23', 'debug': true, 'optimization': 'g' }
        )

add_project_arguments('-ffat-lto-objects', '-D_POSIX_C_SOURCE=202405L', language: [ 'c' ])

if not meson.is_subproject()
    build_tests = true
    add_languages('cpp', required: true, native: false)
    gtest = dependency('gtest', fallback: 'gtest', native: false)
    gtest_main = dependency('gtest_main', fallback: 'gtest', native: false)
else
    build_tests = false
endif

subdir('modules/utility')
