#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "Types/dynamic_list.h"
#include "Types/hash_map.h"
#include "Types/linked_list.h"
#include "Types/String.h"
#include "Types/vector.h"

// Define a new struct type Queue
typedef struct Queue {
    LinkedList *ll;
    LLNode *front;
    LLNode *rear;
    int size;
} Queue;


/* - Define a function to create a new Queue struct -
 * 1. Allocate memory for a new Queue struct and store its pointer in the queue variable.
 * 2. Initialize the linked list in the Queue struct
 * 3. Set the front of the queue to NULL
 * 4. Set the rear of the queue to NULL
 * 5. Initialize the size of the queue to 0
 * 6. Return the pointer to the new Queue struct
 */

Queue *queue_new() {
    Queue *queue = allocate(1, sizeof(Queue));
    queue->ll = ll_new();
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}


// Define a function to push a Value onto the queue
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


// Define a function to pop a Value from the queue
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


// Define a function to print the content of the queue
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

    // Create a new, empty linked list and store its pointer in the ll variable
    LinkedList *ll = ll_new();

    // Create a new integer value with the value 1, and push it to the end of the linked list
    ll_push(ll, value_new_int(1));

    // Same thing, with value 2
    ll_push(ll, value_new_int(2));

    // Create a new integer value with the value 3, and push it to the front of the linked list
    ll_push_front(ll, value_new_int(3));

    // Create a new list with an initial capacity of 10, wrap it in a Value struct of type list,
    // and store its pointer in the list variable
    Value *list = value_new_list(list_new(10));

    // For each iteration of the loop, create a new integer value with the value of the iterator,
    // and push it to the end of the list
    for (int i = 0; i < 100; ++i) {
        list_push(list->as_list, value_new_int(i));
    }

    // Create a new string value containing "Hello world!", and push it to the front of the linked list
    ll_push_front(ll, value_new_string_from(string_new(14, "Hello world\0!")));

    RVector *vec1 = rvector_new_size(1000);
    RVector *vec2 = rvector_new_size(1000);

    // Add the Vectors and store the result in a new Vector
    //RVector result = addVectors(vec1, vec2);

   // ll_push_front(ll, value_new_rvector(result.size, result.data));

    // Add a reference to the list value and push it to the front of the linked list
    ll_push_front(ll, ref(list));

    // Decrease the reference count of the list value
    unref(list);

    // Print the content of the linked list to the console
    ll_print(ll);

    // Free the memory occupied by the linked list and its elements
    ll_free(ll);

    /******************************************************************************/

    /*
    // Print the Vectors
    printf("Vector 1: ");
    printVector(&vec1);
    printf("\n");

    printf("Vector 2: ");
    printVector(&vec2);
    printf("\n");

    printf("Result Vector (vec1 + vec2): ");
    printVector(&result);
    printf("\n");

    // Free the memory allocated for the Vectors
    freeVector(&vec1);
    freeVector(&vec2);
    freeVector(&result);

     */
}
