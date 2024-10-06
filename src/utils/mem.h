#ifndef _LOOOKA_MEM_H
#define _LOOOKA_MEM_H

#include <stddef.h>

void *malloc_with_check(size_t size);

void *realloc_with_check(void *pre, size_t size);

#endif
