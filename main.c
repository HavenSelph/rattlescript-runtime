#include <stdio.h>

#include "common.h"
#include "Types/dynamic_list.h"
#include "Types/hash_map.h"
#include "Types/linked_list.h"
#include "Types/string.h"
#include "Types/queue.h"


int main() {
    Queue *queue = queue_new();
    queue_enqueue(queue, value_new_int(1));
    queue_enqueue(queue, value_new_int(2));
    queue_enqueue(queue, value_new_int(3));

    queue_print(queue); endln;
    Value *val = queue_dequeue(queue);
    value_print(val); endln;
    queue_print(queue); endln;
    value_unref(val);
    queue_free(queue);
}
