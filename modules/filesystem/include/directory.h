/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_


#include <dirent.h>

#ifdef __cplusplus
extern "C" {
#endif


int directory_foreach(DIR *dirp, int (*visitor)(const char *__restrict__ path, void *arg), void *arg);


#ifdef __cplusplus
}
#endif


#endif
