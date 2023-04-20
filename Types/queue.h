//
// Created by haven on 4/19/2023.
//

#ifndef DATATYPES_QUEUE_H
#define DATATYPES_QUEUE_H

#include "value.h"

typedef struct QueueNode {
    Value *value;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *head;
    QueueNode *tail;
    int size;
} Queue;

Queue *queue_new();

void queue_enqueue(Queue *queue, Value *value);
Value *queue_dequeue(Queue *queue);

void queue_print(Queue *queue);
void queue_free(Queue *queue);

#endif //DATATYPES_QUEUE_H
