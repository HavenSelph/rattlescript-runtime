//
// Created by haven on 4/7/2023.
//

#ifndef DYNAMICLISTS_LINKED_LIST_H
#define DYNAMICLISTS_LINKED_LIST_H

#include "value.h"

typedef struct LLNode {
    Value *val;
    struct LLNode *next;
} LLNode;

typedef struct LinkedList {
    LLNode *start;
    int size;
} LinkedList;

LinkedList *ll_new();
LinkedList *ll_new_v(int size, ...);

void ll_print(LinkedList *ll);

void ll_push(LinkedList *ll, Value *val);
void ll_insert(LinkedList *ll, int, Value *val);
Value *ll_pop(LinkedList *ll);

void ll_clear(LinkedList *ll);
void ll_free(LinkedList *ll);

#endif //DYNAMICLISTS_LINKED_LIST_H
