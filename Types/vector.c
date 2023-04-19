#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vector.h"

// Initialize a vector with a specified size and default-initialized elements
RVector *rvector_new_size(int size) {
    RVector *vec = (RVector *)malloc(sizeof(RVector));
    vec->size = size;
    vec->data = (int *)calloc(size, sizeof(int));

    return vec;
}

// Initialize a vector with a specified size and initialize all elements with the given value
RVector *rvector_new_size_value(int size, int value) {
    RVector *vec = (RVector *)malloc(sizeof(RVector));
    vec->size = size;
    vec->data = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < size; ++i) {
        vec->data[i] = value;
    }

    return vec;
}

// Initialize a vector using an array of integers
RVector *rvector_new_array(const int *arr, int size) {
    RVector *vec = (RVector *)malloc(sizeof(RVector));
    vec->size = size;
    vec->data = (int *)malloc(sizeof(int) * size);

    memcpy(vec->data, arr, sizeof(int) * size);

    return vec;
}

// Free vector's memory
void freeRVector(RVector *vec) {
    free(vec->data);
    free(vec);
}

// Add two vectors element-wise, creating a new vector
RVector addVectors(const RVector *vec1, const RVector *vec2) {
    RVector result;

    // Check that the input vectors have the same size
    if (vec1->size == vec2->size) {
        // Initialize the output vector with the same size as the input vectors
        result = *rvector_new_size(vec1->size);
    } else {
        printf("Error: Vectors must have the same size\n");
        exit(1);
    }

    // Add the input vectors element-wise
    for (int i = 0; i < vec1->size; ++i) {
        result.data[i] = vec1->data[i] + vec2->data[i];
    }

    return result;
}

// Print the elements of a vector
void printVector(const RVector *vec) {
    printf("[");
    for (int i = 0; i < vec->size; ++i) {
        printf("%d", vec->data[i]);
        if (i < vec->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
