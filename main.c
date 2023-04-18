#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "Types/dynamic_list.h"
#include "Types/hash_map.h"
#include "Types/linked_list.h"
#include "Types/String.h"

typedef struct Queue {
    LinkedList *ll;
    LLNode *front;
    LLNode *rear;
    int size;
} Queue;


Queue *queue_new() {
    Queue *queue = allocate(1, sizeof(Queue));
    queue->ll = ll_new();
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void queue_push(Queue *queue, Value *val) {
    // F v v v R
    //         ^x
    // F v v v x R

    ll_push(queue->ll, val);
    if (queue->size++ == 0) {
        queue->front = queue->ll->start;
    }
    queue->rear = queue->ll->end;
}


Value *queue_pop(Queue *queue) {
    Value *val = NULL;
    if (queue->size == 0) {
        printf("Queue is empty\n");
        exit(1);
    } else {
        val = queue->front->val;
        if (queue->size == 1) {
            queue->front = NULL;
            queue->rear = NULL;
        } else {
            queue->front = queue->front->next;
        }
    }
    queue->size--;
    return val;
}

void queue_print(Queue *queue) {
    // print from head to tail
    LLNode *cur = queue->front;
    printf("Queue: ");
    for (int i = 0; i < queue->size; ++i) {
        value_print(cur->val);
        if (i!=queue->size) printf("->");
        cur = cur->next;
    }
}


int main() {
    LinkedList *ll = ll_new();
    ll_push(ll, value_new_int(1));
    ll_push(ll, value_new_int(2));
    ll_push_front(ll, value_new_int(3));

    Value *list = value_new_list(list_new(10));
    for (int i = 0; i < 100; ++i) {
        list_push(list->as_list, value_new_int(i));
    }
    ll_push_front(ll, value_new_string_from(string_new(14, "Hello world\0!")));
    ll_push_front(ll, ref(list));
    unref(list);
    ll_print(ll);
    ll_free(ll);
}
