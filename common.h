//
// Created by haven on 4/17/2023.
//
#ifndef DATATYPES_COMMON_H
#define DATATYPES_COMMON_H

#include <stdlib.h>
#include <stdio.h>

#define endln printf("\n")
#define ref value_ref
#define unref value_unref

void *allocate(int num, int size);
void *reallocate(void *ptr, int size);
void deallocate(void *ptr);

void error(char *message);

#define realloc error("Use reallocate() instead of realloc()")
#define free error("Use deallocate() instead of free()")
#define malloc error("Use allocate() instead of malloc()")

void print_allocation_stats();

#endif //DATATYPES_COMMON_H
