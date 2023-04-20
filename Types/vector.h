//
// Created by haven on 4/19/2023.
//

#ifndef DATATYPES_VECTOR_H
#define DATATYPES_VECTOR_H

#include "value.h"

typedef struct Vector {
    Value **values;
    ValueType type;
    int size;
    int capacity;
} Vector;

Vector *vector_new(ValueType type);
Vector *vector_new_v(int size, ValueType type, ...);

void vector_push(Vector *vector, Value *value);
void vector_insert(Vector *vector, int index, Value *value);
Value *vector_pop(Vector *vector);

void vector_print(Vector *vector);
void vector_clear(Vector *vector);
void vector_free(Vector *vector);

#endif //DATATYPES_VECTOR_H
