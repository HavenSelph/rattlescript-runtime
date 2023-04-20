//
// Created by haven on 4/7/2023.
//

#ifndef DYNAMICLISTS_HASH_MAP_H
#define DYNAMICLISTS_HASH_MAP_H

#include "Types/value.h"

typedef struct Bucket {
    Value *key;
    Value *value;
    struct Bucket *next;
} Bucket;

typedef struct HashMap {
    Bucket **buckets;
    int num_buckets;
    int size;
    // int num_buckets;
} HashMap;

HashMap *hm_new();
HashMap *hm_new_sized(int size);
HashMap *hm_new_v(int size, ...);

void hm_push(HashMap *hm, Value *key, Value *value);
Value *hm_get(HashMap *hm, Value *key);
Bucket *hm_exists(HashMap *hm, Value *key);

void hm_print(HashMap *hm);

void hm_free(HashMap *hm);

#endif //DYNAMICLISTS_HASH_MAP_H
