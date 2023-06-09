//
// Created by haven on 4/7/2023.
//

#ifndef DYNAMICLISTS_VALUE_H
#define DYNAMICLISTS_VALUE_H

/*
 * Make all value_new_* functions return a pointer to a Value
 * Add value pair type
 * Add tuple type
 * Make hashmap use value pairs
 *
 */

#include <stdbool.h>

typedef enum ValueType {
    ValueType_Integer,
    ValueType_Float,
    ValueType_Bool,
    ValueType_String,
    ValueType_List,
    ValueType_Vector,
    ValueType_LinkedList,
    ValueType_Queue,
    ValueType_HashMap,
} ValueType;

char *value_type_to_string(ValueType type);

typedef struct LinkedList LinkedList;
typedef struct List List;
typedef struct Vector Vector;
typedef struct HashMap HashMap;
typedef struct String String;
typedef struct Queue Queue;

// TODO: Bring allocations down from three for Strings

typedef struct Value {
    union {
        bool as_bool;
        int as_int;
        float as_float;
        String *as_string;
        List *as_list;
        Vector *as_vector;
        LinkedList *as_linked_list;
        Queue *as_queue;
        HashMap *as_hash_map;
    };
    ValueType type;
    int ref_count;
} Value;

Value *value_new_int(int num);
Value *value_new_float(float num);
Value *value_new_bool(bool boo);
Value *value_new_string_from(String *str);
Value *value_new_string(int length, char *str);
Value *value_new_list(List *list);
Value *value_new_vector(Vector *vector);
Value *value_new_linked_list(LinkedList *ll);
Value *value_new_queue(Queue *queue);
Value *value_new_hash_map(HashMap *hm);

// Return Value types
Value *value_equals(Value *left, Value *right);
Value *value_hash(Value *val);

Value *value_add(Value *left, Value *right);
Value *value_subtract(Value *left, Value *right);
Value *value_power(Value *left, Value *right);
Value *value_multiply(Value *left, Value *right);
Value *value_modulo(Value *left, Value *right);
Value *value_divide(Value *left, Value *right);

Value *value_or(Value *left, Value *right);
Value *value_and(Value *left, Value *right);
Value *value_not(Value *val);

// Return C types
bool value_equals_c(Value *left, Value *right);
bool value_as_bool_c(Value *val);
bool value_or_c(Value *left, Value *right);
bool value_and_c(Value *left, Value *right);
bool value_not_c(Value *val);
int value_pow_int_c(int left, int right);
int value_hash_c(Value *val);

Value *value_ref(Value *val);
void value_unref(Value *val);
void value_free(Value *val);

void value_print(Value *val);

#endif //DYNAMICLISTS_VALUE_H
