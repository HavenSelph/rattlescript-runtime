#include <stdio.h>

#include "dynamic_list.h"
#include "hash_map.h"
#include "linked_list.h"

int main() {
    HashMap *hm = hm_new();
    for (int i = 0; i < 10000000; ++i) {
        if (i % 1000000 == 0) printf("\nSize: %d, Number of buckets: %d", hm->size, hm->num_buckets);
        Value *k = value_new_int(i);
        Value *v = value_new_string("hello world");
        hm_push(hm, k, v);
    }
    Value *val = value_new_hash_map(hm);
    value_free(val);
}
