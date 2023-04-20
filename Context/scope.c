//
// Created by haven on 4/19/2023.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scope.h"

VariableBucket *variable_bucket_new(char *key, Value *value) {
    VariableBucket *bucket = allocate(1, sizeof(VariableBucket));
    bucket->key = key;
    bucket->value = value;
    return bucket;
}

void variable_bucket_free(VariableBucket *bucket) {
    unref(bucket->value);
    deallocate(bucket);
}

VariableHashMap *variable_hash_map_new() {
    VariableHashMap *hm = allocate(1, sizeof(VariableHashMap));
    hm->num_buckets = 4;
    hm->buckets = allocate(hm->num_buckets, sizeof(VariableBucket*));
    return hm;
}

static int variable_hash_map_hash_key(char *key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; ++i) {
        // big prime
        hash += hash * 31;
        hash ^= key[i];
    }
    return hash;
}

static bool variable_hash_map_key_exists(VariableHashMap *hm, char *key) {
    int hash = variable_hash_map_hash_key(key);
    int index = hash % hm->num_buckets;
    VariableBucket *current = hm->buckets[index];
    for (; current; current = current->next) {
        if (strcmp(current->key, key) == 0) {
            return true;
        }
    }
    return false;
}

static void variable_hash_map_check_size(VariableHashMap *hm) {
    if (hm->size > hm->num_buckets * 1.5) {
        VariableBucket **new_buckets = allocate(hm->num_buckets * 2, sizeof(VariableBucket*));
        VariableBucket **old_buckets = hm->buckets;
        int old_num_buckets = hm->num_buckets;
        hm->buckets = new_buckets;
        hm->num_buckets *= 2;
        for (int i = 0; i < old_num_buckets; ++i) {
            VariableBucket *current = old_buckets[i];
            for (; current; current = current->next) {
                variable_hash_map_push(hm, current->key, current->value);
            }
        }
        deallocate(old_buckets);
    }
}

void variable_hash_map_push(VariableHashMap *hm, char *key, Value *value) {
    variable_hash_map_check_size(hm);
    int hash = variable_hash_map_hash_key(key);
    int index = hash % hm->num_buckets;
    VariableBucket *current = hm->buckets[index];
    for (; current; current = current->next) {
        if (strcmp(current->key, key) == 0) {
            unref(current->value);
            current->value = value;
            return;
        }
    }
    VariableBucket *new_bucket = variable_bucket_new(key, value);
    new_bucket->next = hm->buckets[index];
    hm->buckets[index] = new_bucket;
}

Value *variable_hash_map_get(VariableHashMap *hm, char *key) {
    int hash = variable_hash_map_hash_key(key);
    int index = hash % hm->num_buckets;
    VariableBucket *current = hm->buckets[index];
    for (; current; current = current->next) {
        if (strcmp(current->key, key) == 0) {
            return ref(current->value);
        }
    }
    printf("Key %s not found in VariableHashMap", key);
    exit(1);
}

void variable_hash_map_free(VariableHashMap *hm) {
    for (int i = 0; i < hm->num_buckets; ++i) {
        VariableBucket *current = hm->buckets[i];
        while (current) {
            VariableBucket *next = current->next;
            variable_bucket_free(current);
            current = next;
        }
    }
    deallocate(hm->buckets);
    deallocate(hm);
}

Scope *scope_new() {
    Scope *scope = allocate(1, sizeof(Scope));
    scope->parent = NULL;
    scope->variables = variable_hash_map_new();
    return scope;
}

Scope *scope_new_child(Scope *parent) {
    Scope *scope = scope_new();
    scope->parent = scope_ref(parent);
    return scope;
}

void scope_push_variable(Scope *scope, char *key, Value *value) {
    variable_hash_map_push(scope->variables, key, value);
}

Value *scope_get_variable(Scope *scope, char *key) {
    Scope *current = scope;
    while (current) {
        if (variable_hash_map_key_exists(current->variables, key)) {
            return variable_hash_map_get(current->variables, key);
        }
        current = current->parent;
    }
    printf("Key %s not found in Scope", key);
    exit(1);
}

void scope_free(Scope *scope) {
    variable_hash_map_free(scope->variables);
    if (scope->parent) scope_unref(scope->parent);
    deallocate(scope);
}

Scope *scope_ref(Scope *scope) {
    scope->ref_count++;
    return scope;
}

void scope_unref(Scope *scope) {
    if (scope->ref_count-- == 0) {
        scope_free(scope);
    }
}

