//
// Created by haven on 4/7/2023.
//

#ifndef DYNAMICLISTS_DYNAMIC_LIST_H
#define DYNAMICLISTS_DYNAMIC_LIST_H

#include "value.h"

typedef struct List {
    Value **val;
    int size;
    int capacity;
} List;

List *list_new(int capacity);
List *list_new_v(int size, ...);

void list_push(List *list, Value *val);
Value *list_pop(List *list);
void list_insert(List *list, int index, Value *val);
void list_clear(List *list);
void list_free(List *list);

void list_print(List *list);
#endif //DYNAMICLISTS_DYNAMIC_LIST_H
