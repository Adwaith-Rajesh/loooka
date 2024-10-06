#include "mem.h"

#include <stdio.h>
#include <stdlib.h>

void *malloc_with_check(size_t size) {
    void *mem = malloc(size);
    if (mem == NULL) {
        perror("Cannot allocated memory");
        exit(EXIT_FAILURE);
    }
    return mem;
}

void *realloc_with_check(void *ptr, size_t size) {
    void *mem = realloc(ptr, size);
    if (mem == NULL) {
        perror("Cannot reallocate memory");
        exit(EXIT_FAILURE);
    }
    return mem;
}
