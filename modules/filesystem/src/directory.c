/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "directory.h"

#include <errno.h>
#include <dirent.h>
#include <unistd.h>

int directory_foreach(DIR *dirp, int (*visitor)(const char *__restrict__ path, void *arg), void *arg) {
    while(true) {
        errno = 0;
        struct dirent *entry = readdir(dirp);
        if(!entry) {
            int err = errno;
            if(err) {
                closedir(dirp);
                return err;
            }

            break;
        }

        int status = visitor(entry->d_name, arg);
        if(status) {
            closedir(dirp);
            return status;
        }
    }

    if(closedir(dirp)) {
        __builtin_assume(errno);
        return errno;
    }

    return 0;
}
