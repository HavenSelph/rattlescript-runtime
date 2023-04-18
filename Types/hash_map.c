//
// Created by haven on 4/7/2023.
//
#include <stdio.h>
#include <stdarg.h>

#include "common.h"
#include "Types/hash_map.h"

static Bucket *bucket_new(Value *key, Value *value) {
    Bucket *bucket = allocate(1, sizeof(Bucket));
    bucket->key = key;
    bucket->value = value;
    return bucket;
}

static void bucket_free(Bucket *bucket) {
    if (!bucket) return;
    value_unref(bucket->key);
    value_unref(bucket->value);
    deallocate(bucket);
}


void hm_print(HashMap *hm) {
    printf("{");
    for (int i = 0; i < hm->num_buckets; ++i) {
        Bucket *current = hm->buckets[i];
        for (; current; current = current->next) {
            value_print(current->key);
            printf(":");
            value_print(current->value);
            printf(",");
        }
    }
    printf("}");
}

Value *hm_get(HashMap *hm, Value *key) {
    Bucket *bucket = hm_exists(hm, key);
    if (bucket) {
        return bucket->value;
    }
    return NULL;
}

static void hm_check_size(HashMap *hm) {
    if (hm->size > hm->num_buckets * 0.75) {
        Bucket **new_buckets = allocate(hm->num_buckets*2, sizeof(Bucket*));
        Bucket **old_buckets = hm->buckets;
        int old_num_buckets = hm->num_buckets;
        hm->buckets = new_buckets;
        hm->num_buckets *= 2;
        for (int i = 0; i < old_num_buckets; ++i) {
            Bucket *current = old_buckets[i];
            while (current) {
                Bucket *next = current->next;
                hm_push(hm, current->key, current->value);
                current = next;
            }
            bucket_free(current);
        }
    }
}

void hm_push(HashMap *hm, Value *key, Value *value) {
    hm_check_size(hm);
    Bucket *bucket = hm_exists(hm, key);
    if (bucket) {
        value_unref(bucket->value);
        value_unref(key);
        bucket->value = value;
        return;
    }
    int key_hash = value_hash_c(key);
    bucket = bucket_new(key, value);
    Bucket **cur = &hm->buckets[key_hash % hm->num_buckets];
    bucket->next = *cur;
    *cur = bucket;
    hm->size++;
}

Bucket *hm_exists(HashMap *hm, Value *key) {
    int key_hash = value_hash_c(key);
    Bucket *current = hm->buckets[key_hash % hm->num_buckets];
    for (;current; current = current->next) {
        if (value_equals_c(current->key, key))
            return current;
    }
    return NULL;
}

HashMap *hm_new() {
    HashMap *hm = allocate(1, sizeof(HashMap));
    hm->buckets = allocate(64, sizeof(Bucket*));
    hm->num_buckets = 64;
    return hm;
}

HashMap *hm_new_v(int size, ...) {
    HashMap *hm = hm_new();
    va_list args;
    va_start(args, size);
    for (int i = 0; i < size; ++i) {
        Value *key = va_arg(args, Value *);
        Value *value = va_arg(args, Value *);
        hm_push(hm, key, value);
    }
    va_end(args);
    return hm;
}

void hm_free(HashMap *hm) {
    for (int i = 0; i < hm->num_buckets; ++i) {
        Bucket *current = hm->buckets[i];
        while (current) {
            Bucket *next = current->next;
            bucket_free(current);
            current = next;
        }
    }
    deallocate(hm);
}
