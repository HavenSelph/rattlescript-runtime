//
// Created by haven on 4/19/2023.
//

#ifndef DATATYPES_SCOPE_H
#define DATATYPES_SCOPE_H

#include "common.h"
#include "Types/value.h"

typedef struct Scope Scope;
typedef struct VariableBucket VariableBucket;

struct VariableBucket {
    char *key;
    Value *value;
    VariableBucket *next;
};

VariableBucket *variable_bucket_new(char *key, Value *value);
void variable_bucket_free(VariableBucket *bucket);

typedef struct VariableHashMap {
    VariableBucket **buckets;
    int num_buckets;
    int size;
} VariableHashMap;

VariableHashMap *variable_hash_map_new();
void variable_hash_map_push(VariableHashMap *hm, char *key, Value *value);
Value *variable_hash_map_get(VariableHashMap *hm, char *key);

void variable_hash_map_free(VariableHashMap *hm);

struct Scope {
    Scope *parent;
    VariableHashMap *variables;
    int ref_count;
};

Scope *scope_new();
Scope *scope_new_child(Scope *parent);

void scope_push_variable(Scope *scope, char *key, Value *value);
Value *scope_get_variable(Scope *scope, char *key);

void scope_free(Scope *scope);
Scope *scope_ref(Scope *scope);
void scope_unref(Scope *scope);

#endif //DATATYPES_SCOPE_H
