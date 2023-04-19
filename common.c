#include <stdlib.h>
#include <stdio.h>

static int allocated = 0;
static int freed = 0;

void *allocate(int num, int size) {
    allocated++;
    void *out = calloc(num, size);
    return out;
}

void deallocate(void *ptr) {
    freed++;
    free(ptr);
}

__attribute__((destructor))
void print_allocation_stats() {
    printf("\nAllocated: %d, Freed: %d", allocated, freed);
}
