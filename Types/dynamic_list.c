//
// Created by haven on 4/7/2023.
//
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "common.h"
#include "Types/dynamic_list.h"

List *list_new(int capacity) {
    List *list = allocate(1, sizeof(List));
    list->val = allocate(capacity, sizeof(Value));
    list->size = 0;
    list->capacity = capacity;
    return list;
}

List *list_new_v(int size, ...) {
    // take in variable number of values and push them to the list
    List *list = list_new(size);
    va_list args;
    va_start(args, size);
    for (int i = 0; i < size; ++i) {
        Value *val = va_arg(args, Value*);
        list_push(list, val);
    }
    va_end(args);
    return list;
}

static void list_check_under(List *list) {
    if (list->size >= list->capacity) {
        list->capacity = (list->capacity == 0) ? 10 : list->capacity*2;
        list->val = reallocate(list->val, list->capacity*sizeof(Value));
    }
}

static void list_check_over(List *list) {
    if (list->size < list->capacity/4 && list->capacity > 10) {
        list->capacity /= 2;
        list->val = reallocate(list->val, list->capacity*sizeof(Value));
    }
}

void list_push(List *list, Value *val) {
    list_check_under(list);
    list->val[list->size++] = val;
}

Value *list_pop(List *list) {
    list_check_over(list);
    if (list->size <= 0) {
        printf("List is empty\n");
        exit(1);
    }
    Value *val = list->val[--list->size];
    return val;
}

void list_insert(List *list, int index, Value *val) {
    list_check_over(list);
    if (index > list->size || 0 > list->size) {
        printf("Invalid index for insert\n");
        exit(1);
    }
    list_push(list, value_new_bool(1));
    for (int i = list->size-2; i >= index; --i) {
        list->val[i+1] = list->val[i];
    }
    list->val[index] = val;
}

void list_clear(List *list) {
    for (;0 < list->size; list->size--) {
        value_unref(list->val[list->size-1]);
    }
}

void list_free(List *list) {
    list_clear(list);
    deallocate(list->val);
    deallocate(list);
}

void list_print(List *list) {
    printf("[");
    for (int i = 0; i < list->size; ++i) {
        if (i>0) printf(", ");
        value_print(list->val[i]);
    }
    printf("]");
}
