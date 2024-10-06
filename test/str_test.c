#include <stdio.h>

#include "string.h"
#include "test.h"

#define STR_MALLOC(SZ) malloc_with_check(SZ)
#define STR_REALLOC(PTR, SZ) realloc_with_check(PTR, SZ)
#define FREE(PTR) free(PTR)

#define _LOOOKA_MEM_IMPLEMENTATION
#include "mem.h"

#define _LOOOKA_STR_IMPLEMENTATION
#include "str.h"

DEF_TEST(test_str_create) {
    String *new_str = str_create(10);
    ASSERT(new_str->size == 10);
}

int main(void) {
    TEST_INIT(__FILE__);

    ADD_TEST(test_str_create);

    run_all_test();
}
