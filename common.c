#include <stdlib.h>
#include <stdio.h>

static int allocated = 0;
static int freed = 0;

void *allocate(int num, int size) {
    allocated++;
    printf("Allocating %d bytes: ", num*size);
    void *out = calloc(num, size);
    printf("%p\n", out);
    return out;
}

void deallocate(void *ptr) {
    freed++;
    printf("Freeing %p ", ptr);
    free(ptr);
    printf("Freed!\n");
}

__attribute__((destructor))
void print_allocation_stats() {
    printf("\nAllocated: %d, Freed: %d", allocated, freed);
}
