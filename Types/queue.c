//
// Created by haven on 4/19/2023.
//
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "common.h"

Queue *queue_new() {
    Queue *queue = allocate(1, sizeof(Queue));
    return queue;
}

void queue_enqueue(Queue *queue, Value *value) {
    QueueNode *node = allocate(1, sizeof(QueueNode));
    node->value = value;
    if (queue->tail) {
        queue->tail->next = node;
    }
    queue->tail = node;
    if (!queue->head) {
        queue->head = node;
    }
    queue->size++;
}

Value *queue_dequeue(Queue *queue) {
    if (!queue->head) {
        printf("Queue is empty");
        exit(1);
    }
    QueueNode *node = queue->head;
    queue->head = node->next;
    if (!queue->head) {
        queue->tail = NULL;
    }
    Value *value = node->value;
    deallocate(node);
    queue->size--;
    return value;
}

void queue_print(Queue *queue) {
    printf("Queue: ");
    QueueNode *current = queue->head;
    for (; current; current = current->next) {
        value_print(current->value);
        if (current->next) printf(" -> ");
    }
}

void queue_free(Queue *queue) {
    QueueNode *current = queue->head;
    while (current) {
        value_unref(current->value);
        QueueNode *next = current->next;
        deallocate(current);
        current = next;
    }
    deallocate(queue);
}
