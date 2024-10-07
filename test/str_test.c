#include <stdio.h>

#include "string.h"
#include "test.h"

#define STR_MALLOC(SZ) malloc_with_check(SZ)
#define STR_REALLOC(PTR, SZ) realloc_with_check(PTR, SZ)
#define STR_FREE(PTR) free(PTR)

#define _LOOOKA_MEM_IMPLEMENTATION
#include "mem.h"

#define _LOOOKA_STR_IMPLEMENTATION
#include "str.h"

DEF_TEST(test_str_create) {
    String *new_str = str_create(10);
    ASSERT(new_str->size == 10);
    str_free(new_str);
}

DEF_TEST(test_str_create_cstr) {
    const char *c = "hello";
    String *new_str = str_create_cstr(c);

    ASSERT(strlen(new_str->str) == 5);
    ASSERT(strncmp(new_str->str, "hello", 5) == 0);
    ASSERT(new_str->size == 5);

    str_free(new_str);
}

int main(void) {
    TEST_INIT(__FILE__);

    ADD_TEST(test_str_create);
    ADD_TEST(test_str_create_cstr);

    run_all_test();
}
