//
// Created by haven on 4/19/2023.
//

#ifndef DATATYPES_CONTEXT_H
#define DATATYPES_CONTEXT_H

#include "Context/scope.h"


typedef struct Context {
    Scope **scopes;  // Array of scopes, variable size
    int num_scopes;  // Number of scopes in the array
    int size;        // Size of the array (capacity)
} Context;

Context *context_new();
void context_push_scope(Context *context, Scope *scope);
void context_pop_scope(Context *context);
Scope *context_get_scope(Context *context, int index);

#endif //DATATYPES_CONTEXT_H
