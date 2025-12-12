/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "directory.h"

#include <errno.h>
#include <dirent.h>
#include <unistd.h>

int directory_iterate_at(int dirfd, int (*foreach)(const char *__restrict__ path, int dirfd)) {
    DIR *dirp;
    {
        int fd = dup(dirfd);
        if(fd < 0) {
            __builtin_assume(errno);
            return errno;
        }

        dirp = fdopendir(fd);
        if(!dirp) {
            int err = errno;
            __builtin_assume(err);
            close(fd);
            return err;
        }
    }

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

        int status = foreach(entry->d_name, dirfd);
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
