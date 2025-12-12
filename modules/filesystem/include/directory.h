/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_


#ifdef __cplusplus
extern "C" {
#endif


int directory_iterate_at(int dirfd, int (*foreach)(const char *__restrict__ path, int dirfd));


#ifdef __cplusplus
}
#endif


#endif
