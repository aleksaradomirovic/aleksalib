/*
 * Copyright (C) 2025  Aleksa Radomirovic
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "queue.h"

#include <errno.h>
#include <stdckdint.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_NODE_MIN_SIZE (256)

struct queue_node {
    struct queue_node *next;
    size_t head, tail;
    unsigned char data[];
};

#define QUEUE_NODE_INITIALIZER (struct queue_node) { .next = NULL, .head = 0, .tail = 0 }

static int queue_node_alloc(struct queue_node **node_ptr, size_t data_size) {
    if(data_size < QUEUE_NODE_MIN_SIZE) {
        data_size = QUEUE_NODE_MIN_SIZE;
    }

    size_t alloc_size;
    if(ckd_add(&alloc_size, data_size, sizeof(struct queue_node))) {
        return EOVERFLOW;
    }

    struct queue_node *node = malloc(alloc_size);
    if(!node) {
        __builtin_assume(errno);
        return errno;
    }

    *node = QUEUE_NODE_INITIALIZER;
    *node_ptr = node;
    return 0;
}

static void queue_node_free(struct queue_node *node) {
    free(node);
}

static void queue_enqueue_node(struct queue *__restrict__ queue, struct queue_node *__restrict__ node) {
    *node = QUEUE_NODE_INITIALIZER;

    struct queue_node *tail = queue->tail;
    if(tail) {
        tail->next = node;
    } else {
        queue->head = node;
    }

    queue->tail = node;
}

static struct queue_node * queue_dequeue_node(struct queue *__restrict__ queue) {
    struct queue_node *node = queue->head;
    if(!node) {
        return NULL;
    }

    queue->head = node->next;
    if(queue->tail == node) {
        queue->tail = NULL;
    }

    return node;
}

void queue_init(struct queue *__restrict__ queue) {
    *queue = QUEUE_INITIALIZER;
}

void queue_free(struct queue *__restrict__ queue) {
    while(true) {
        struct queue_node *node = queue_dequeue_node(queue);
        if(!node) {
            break;
        }

        queue_node_free(node);
    }

    *queue = QUEUE_INITIALIZER;
}

int queue_enqueue(struct queue *__restrict__ queue, const void *__restrict__ data, size_t data_size) {
    struct queue_node *tail = queue->tail;
    if(!tail || tail->tail >= QUEUE_NODE_MIN_SIZE || QUEUE_NODE_MIN_SIZE - tail->tail > data_size) {
        int status = queue_node_alloc(&tail, data_size);
        if(status) {
            return status;
        }
        queue_enqueue_node(queue, tail);
    }

    if(data) {
        memcpy(tail->data + tail->tail, data, data_size);
    }
    tail->tail += data_size;
    return 0;
}

int queue_dequeue(struct queue *__restrict__ queue, void *__restrict__ data, size_t data_size) {
    struct queue_node *head = queue->head;
    if(!head) {
        return EWOULDBLOCK;
    }

    if(data) {
        memcpy(data, head->data + head->head, data_size);
    }
    head->head += data_size;
    if(head->head >= head->tail) {
        queue_dequeue_node(queue);
        free(head);
    }

    return 0;
}

bool queue_empty(const struct queue *__restrict__ queue) {
    return !(queue->head);
}
