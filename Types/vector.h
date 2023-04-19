#include <stdlib.h>

// Define a custom struct for a fixed-size vector of integers
typedef struct RVector {
    int size;       // Size of the vector
    int *data;      // Pointer to the array of integers
} RVector;

// Initialize a vector with a specified size and default-initialized elements
RVector *rvector_new_size(int size);

// Initialize a vector with a specified size and initialize all elements with the given value
RVector *rvector_new_size_value(int size, int value);

// Initialize a vector using an array of integers
RVector *rvector_new_array(const int *arr, int size);

// Free vector's memory
void freeRVector(RVector *vec);

// Add two vectors element-wise, creating a new vector
RVector addVectors(const RVector *vec1, const RVector *vec2);

// Print the elements of a vector
void printVector(const RVector *vec);
