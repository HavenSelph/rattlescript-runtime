//
// Created by haven on 4/19/2023.
//
#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "vector.h"

Vector *vector_new(ValueType type) {
    Vector *vector = allocate(1, sizeof(Vector));
    vector->type = type;
    vector->capacity = 10;
    vector->values = allocate(vector->capacity, sizeof(Value *));
    return vector;
}

void vector_check_over(Vector *vector) {
    if (vector->size < vector->capacity/4 && vector->capacity > 10) {
        vector->capacity /= 2;
        vector->values = reallocate(vector->values, vector->capacity*sizeof(Value*));
    }
}

void vector_check_under(Vector *vector) {
    if (vector->size >= vector->capacity) {
        vector->capacity = (vector->capacity == 0) ? 10 : vector->capacity*2;
        vector->values = reallocate(vector->values, vector->capacity*sizeof(Value*));
    }
}

void vector_push(Vector *vector, Value *value) {
    vector_check_under(vector);
    if (value->type != vector->type) {
        printf("Vector type mismatch\n");
        exit(1);
    }
    vector->values[vector->size++] = value;
}

Value *vector_pop(Vector *vector) {
    vector_check_over(vector);
    if (vector->size == 0) {
        printf("Vector is empty\n");
        exit(1);
    }
    return vector->values[--vector->size];
}

void vector_print(Vector *vector) {
    printf("Vector [");
    for (int i = 0; i < vector->size; ++i) {
        value_print(vector->values[i]);
        if (i < vector->size - 1) printf(", ");
    }
    printf("]");
}

void vector_clear(Vector *vector) {
    for (int i = 0; i < vector->size; ++i) {
        value_free(vector->values[i]);
    }
    vector->size = 0;
}

void vector_free(Vector *vector) {
    vector_clear(vector);
    deallocate(vector->values);
    deallocate(vector);
}
