//
// Created by haven on 4/7/2023.
//

#include "linked_list.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

static LLNode *ll_node_new(Value *val) {
    LLNode *ll_node = calloc(1, sizeof(LLNode));
    ll_node->val = val;
    return ll_node;
}

static void ll_node_free(LLNode *ll_node) {
    value_free(ll_node->val);
    free(ll_node);
}

LinkedList *ll_new() {
    LinkedList *ll = calloc(1, sizeof(LinkedList));
    return ll;
}

LinkedList *ll_new_v(int size, ...) {
    LinkedList *ll = ll_new();
    va_list args;
    va_start(args, size);
    Value *val = va_arg(args, Value*);
    while (val) {
        ll_push(ll, val);
        val = va_arg(args, Value*);
    }
    va_end(args);
    return ll;
}

void ll_push(LinkedList *ll, Value *val) {
    LLNode *ll_node = ll_node_new(val);
    LLNode **cur = &ll->start;
    for (int i = 0; i < ll->size; ++i) {
        cur = &(*cur)->next;
    }
    ll->size++;
    *cur = ll_node;
}

void ll_insert(LinkedList *ll, int index, Value *val) {
    if (index > ll->size || 0 > index) {
        printf("Invalid index for insert\n");
        exit(1);
    }
    LLNode *ll_node = ll_node_new(val);
    LLNode **cur = &ll->start;
    for (int i = 0; i < index; ++i) {
        cur = &(*cur)->next;
    }
    ll->size++;
    ll_node->next = *cur;
    *cur = ll_node;
}

Value *ll_pop(LinkedList *ll) {
    if (ll->size == 0) {
        printf("Cannot pop from empty linked list");
        exit(1);
    }
    LLNode **last = &ll->start;
    for (int i = 0; i < ll->size-1; ++i) {
        last = &(*last)->next;
    }
    ll->size--;
    Value *val = (*last)->val;
    free(*last);
    *last = NULL;
    return val;
}

void ll_clear(LinkedList *ll) {
    LLNode *cur = ll->start;
    for (int i = 0; i < ll->size; ++i) {
        LLNode *next = cur->next;
        ll_node_free(cur);
        cur = next;
    }
    ll->size = 0;
}

void ll_free(LinkedList *ll) {
    ll_clear(ll);
    free(ll);
}

void ll_print(LinkedList *ll) {
    printf("LinkedList: ");
    LLNode *cur = ll->start;
    for (int i = 0; i < ll->size; ++i) {
        if (i>0) printf(" -> ");
        value_print(cur->val);
        cur = cur->next;
    }
}
