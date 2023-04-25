//
// Created by haven on 4/20/2023.
//

#ifndef DATATYPES_SCOPE_H
#define DATATYPES_SCOPE_H

typedef struct Scope Scope;
typedef struct Value Value;

extern Scope *current_scope;

Scope *scope_new_global();
Scope *scope_new(Scope *parent);
void scope_push(Scope *scope, char *key, Value *val);
void scope_pop(Scope *scope, char *key);
Value *scope_get(Scope *scope, char *key);

void init_scope();
void scope_stack_push();
void scope_stack_pop();

Scope *scope_ref(Scope *scope);
void scope_unref(Scope *scope);
void scope_free(Scope *scope);

#endif //DATATYPES_SCOPE_H
