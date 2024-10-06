#ifndef _LOOOKA_MEM_H
#define _LOOOKA_MEM_H

#include <stddef.h>

void *malloc_with_check(size_t size);

void *realloc_with_check(void *pre, size_t size);

#endif

#ifdef _LOOOKA_MEM_IMPLEMENTATION

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

#endif
