#include <stdio.h>

#include "utils/test.h"

#define _LOOOKA_STR_IMPLEMENTATION
#include "ds/str.h"

DEF_TEST(test_str_create) {
    // String *new_str = str_create(10);
    ASSERT(1 == 0);
}

DEF_TEST(test_str_create_2) {
    ASSERT(1 == 1);
}

int main(void) {
    TEST_INIT(__FILE__);

    ADD_TEST(test_str_create);
    ADD_TEST(test_str_create_2);

    run_all_test();
}
