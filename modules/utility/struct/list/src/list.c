/**
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "list.h"

#include <errno.h>
#include <stdckdint.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct list_node {
    struct list_node *next;
    size_t head, tail;
    unsigned char data[];
};

#define LIST_NODE_INITIALIZER (struct list_node) { .next = NULL, .head = 0, .tail = 0 }

#define LIST_NODE_MIN_DATA_SIZE (256 - sizeof(struct list_node))

static int list_node_alloc(struct list_node **node_ptr, size_t min_data_size) {
    if(min_data_size < LIST_NODE_MIN_DATA_SIZE) {
        min_data_size = LIST_NODE_MIN_DATA_SIZE;
    }

    size_t alloc_size;
    if(ckd_add(&alloc_size, sizeof(struct list_node), min_data_size)) {
        return EOVERFLOW;
    }

    struct list_node *node = malloc(alloc_size);
    if(!node) {
        __builtin_assume(errno);
        return errno;
    }

    *node = LIST_NODE_INITIALIZER;
    *node_ptr = node;
    return 0;
}

static void list_node_free(struct list_node *node) {
    free(node);
}

void list_init(struct list *restrict list) {
    *list = LIST_INITIALIZER;
}

void list_free(struct list *restrict list) {
    for(struct list_node *node = list->head; node;) {
        struct list_node *next = node->next;
        list_node_free(node);
        node = next;
    }

    *list = LIST_INITIALIZER;
}

int list_add_tail(struct list *restrict list, const void *restrict element_ptr, size_t element_size) {
    struct list_node *tail = list->tail;
    if(!tail || tail->tail > LIST_NODE_MIN_DATA_SIZE || LIST_NODE_MIN_DATA_SIZE - tail->tail < element_size) {
        struct list_node *node;
        int status = list_node_alloc(&node, element_size);
        if(status) {
            return status;
        }

        if(tail) {
            tail->next = node;
        } else {
            list->head = node;
        }
        list->tail = node;
        tail = node;
    }

    if(element_ptr) {
        memcpy(tail->data + tail->tail, element_ptr, element_size);
    }
    tail->tail += element_size;

    return 0;
}

void list_foreach(struct list *restrict list, iterator_t *iterator_function, void *iterator_arg, size_t element_size) {
    for(struct list_node *node = list->head; node; node = node->next) {
        if(node->tail - node->head < element_size) {
            continue;
        }

        for(size_t iter_pos = node->head; iter_pos <= node->tail - element_size; iter_pos += element_size) {
            enum iterator_command cmd = iterator_function(node->data + iter_pos, iterator_arg);
            switch(cmd) {
                case ITERATOR_STOP:
                    return;
                case ITERATOR_NEXT:
                    break;
                default:
                    return;
            }
        }
    }
}
