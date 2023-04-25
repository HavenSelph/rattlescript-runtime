//
// Created by haven on 4/20/2023.
//

#include "scope.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Types/value.h"
#include "common.h"

Scope *current_scope = NULL;

typedef struct VariableBucket {
    char *key;
    Value *value;
    struct VariableBucket *next;
} VariableBucket;

typedef struct VariableHashMap {
    VariableBucket **buckets;
    int num_buckets;
    int size;
} VariableHashMap;

static void variable_hm_check_size(VariableHashMap *vhm);

static VariableBucket *variable_bucket_new(char *key, Value *value) {
    VariableBucket *bucket = allocate(1, sizeof(VariableBucket));
    bucket->key = allocate(strlen(key) + 1, sizeof(char));
    strcpy(bucket->key, key);
    bucket->value = value;
    return bucket;
}

static void variable_bucket_free(VariableBucket *bucket) {
    deallocate(bucket->key);
    value_unref(bucket->value);
    deallocate(bucket);
}

static int variable_hm_hash(char *key) {
    int hash = 0;
    for (int i = 0; i < strlen(key); ++i) {
        hash += key[i];
    }
    return hash;
}

static VariableHashMap *variable_hm_new() {
    VariableHashMap *hm = allocate(1, sizeof(VariableHashMap));
    hm->num_buckets = 8;
    hm->buckets = allocate(hm->num_buckets, sizeof(VariableBucket*));
    return hm;
}

static VariableBucket *variable_hm_exists(VariableHashMap *vhm, int hash, char *key) {
    int index = hash % vhm->num_buckets;
    VariableBucket *current = vhm->buckets[index];
    for (; current; current = current->next) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
    }
    return NULL;
}

static void variable_hm_push(VariableHashMap *vhm, char *key, Value *val) {
    variable_hm_check_size(vhm);
    int hash = variable_hm_hash(key);
    int index = hash % vhm->num_buckets;
    VariableBucket *bucket = variable_hm_exists(vhm, hash, key);
    if (bucket) {
        value_unref(bucket->value);
        bucket->value = val;
    } else {
        bucket = variable_bucket_new(key, val);
        bucket->next = vhm->buckets[index];
        vhm->buckets[index] = bucket;
        vhm->size++;
    }
}

static Value *variable_hm_get(VariableHashMap *vhm, char *key) {
    int hash = variable_hm_hash(key);
    VariableBucket *bucket = variable_hm_exists(vhm, hash, key);
    if (bucket) {
        return bucket->value;
    }
    printf("Variable %s not found in scope\n", key);
    return NULL;
}

static void variable_hm_check_size(VariableHashMap *vhm) {
    if (vhm->size > vhm->num_buckets * 1.5) {
        VariableBucket **new_buckets = allocate(vhm->num_buckets*2, sizeof(VariableBucket*));
        VariableBucket **old_buckets = vhm->buckets;
        int old_num_buckets = vhm->num_buckets;
        vhm->buckets = new_buckets;
        vhm->num_buckets *= 2;
        vhm->size = 0;
        for (int i = 0; i < old_num_buckets; ++i) {
            VariableBucket *current = old_buckets[i];
            for (; current; current = current->next) {
                VariableBucket *next = current->next;
                variable_hm_push(vhm, current->key, current->value);
                variable_bucket_free(current);
                current = next;
            }
        }
        deallocate(old_buckets);
    }
}

static void variable_hm_free(VariableHashMap *vhm) {
    for (int i = 0; i < vhm->num_buckets; ++i) {
        VariableBucket *current = vhm->buckets[i];
        while (current) {
            VariableBucket *next = current->next;
            variable_bucket_free(current);
            current = next;
        }
    }
    deallocate(vhm->buckets);
    deallocate(vhm);
}

typedef struct Scope {
    struct Scope *parent;
    VariableHashMap *variables;
    int ref_count;
} Scope;

Scope *scope_new_global() {
    Scope *scope = allocate(1, sizeof(Scope));
    scope->parent = NULL;
    scope->variables = variable_hm_new();
    scope->ref_count = 1;
    return scope;
}

Scope *scope_new(Scope *parent) {
    Scope *scope = scope_new_global();
    scope->parent = scope_ref(parent);
    return scope;
}

void scope_push(Scope *scope, char *key, Value *val) {
    variable_hm_push(scope->variables, key, val);
}

Value *scope_get(Scope *scope, char *key) {
    int hash = variable_hm_hash(key);
    Scope *current = scope;
    while (current) {
        VariableBucket *bucket = variable_hm_exists(current->variables, hash, key);
        if (bucket) {
            return ref(bucket->value);
        }
        current = current->parent;
    }
    printf("Variable %s not found in scope\n", key);
    exit(1);
}

void scope_free(Scope *scope) {
    if (scope->parent) scope_unref(scope->parent);
    variable_hm_free(scope->variables);
    deallocate(scope);
}

Scope *scope_ref(Scope *scope) {
    scope->ref_count++;
    return scope;
}

void scope_unref(Scope *scope) {
    if (--scope->ref_count == 0) scope_free(scope);
}

void init_scope() {
    current_scope = scope_new_global();
}

void scope_stack_push() {
    current_scope = scope_new(current_scope);
}

void scope_stack_pop() {
    Scope *old = current_scope;
    current_scope = current_scope->parent;
    scope_unref(old);
}
