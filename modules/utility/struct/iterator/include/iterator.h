/**
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ITERATOR_H_
#define ITERATOR_H_


enum iterator_command {
    ITERATOR_STOP,
    ITERATOR_NEXT,
};

typedef enum iterator_command (iterator_t)(void *element, void *arg);


#endif
