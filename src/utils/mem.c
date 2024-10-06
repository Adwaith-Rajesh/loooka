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
