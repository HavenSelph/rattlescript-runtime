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
    ValueType_LinkedList,
    ValueType_HashMap,
} ValueType;

typedef struct LinkedList LinkedList;
typedef struct List List;
typedef struct HashMap HashMap;
typedef struct String String;

typedef struct Value {
    union {
        bool as_bool;
        float as_float;
        int as_int;
        String *as_string;
        List *as_list;
        LinkedList *as_linked_list;
        HashMap *as_hash_map;
    };
    ValueType type;
    int ref_count;
} Value;

Value *value_new_int(int num);
Value *value_new_float(float num);
Value *value_new_bool(bool boo);
Value *value_new_string(int length, char *str);
Value *value_new_list(List *list);
Value *value_new_linked_list(LinkedList *ll);
Value *value_new_hash_map(HashMap *hm);

bool value_equals(Value *lhs, Value *rhs);
int value_hash(Value *val);

Value *value_ref(Value *val);
void value_free(Value *val);

void value_print(Value *val);

#endif //DYNAMICLISTS_VALUE_H
