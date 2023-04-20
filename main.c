#include <stdio.h>

#include "common.h"
#include "Types/dynamic_list.h"
#include "Types/hash_map.h"
#include "Types/linked_list.h"
#include "Types/string.h"
#include "Types/queue.h"
#include "Types/vector.h"
#include "Context/scope.h"


int main() {
    int size = 1000000;
    Value *hm = value_new_hash_map(hm_new_sized(size));
    for (int i = 0; i < size; ++i) {
        Value *key = value_new_int(i);
        Value *val = value_new_string(5, "hello");
        hm_push(hm->as_hash_map, key, val);
    }
    value_free(hm);
    return 0;
}
