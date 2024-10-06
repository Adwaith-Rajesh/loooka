/*
BSD 3-Clause License

Copyright (c) 2024, Adwaith Rajesh

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// A dead simple testing "framework"

// all the test file that include "test.h" must be compiled and ran independently

#ifndef _LOOOKA_TEST_H
#define _LOOOKA_TEST_H

#ifndef MAX_TEST_COUNT
#define MAX_TEST_COUNT 128
#endif

#include <stdio.h>

#include "utils/color.h"

typedef struct {
    int test_failed_count;
} GTestCtx;

typedef struct {
    int assertion_err_count;
    int total_assertions;
} TestCtx;

typedef struct {
    void (*fn)(TestCtx *);
    const char *desc;
    int lineno;
} Test;

Test all_test[MAX_TEST_COUNT] = {0};
int test_count = 0;

const char *filename = "";
int initialize = 0;

#define TEST_INIT(FLNAME) \
    filename = (FLNAME);  \
    initialize = 1;

#define DEF_TEST(NAME) void NAME(TestCtx *ctx)
#define ADD_TEST(NAME) add_test(NAME, #NAME, __LINE__)

#define ASSERT(STMT)                                                                 \
    ctx->total_assertions += 1;                                                      \
    if (!(STMT)) {                                                                   \
        printf(RED "[FAIL] Assertion %s:%d: %s\n" RESET, filename, __LINE__, #STMT); \
        ctx->assertion_err_count += 1;                                               \
    }

void add_test(void (*fn)(TestCtx *), const char *desc, int lineno) {
    all_test[test_count].fn = fn;
    all_test[test_count].desc = desc;
    all_test[test_count++].lineno = lineno;
}

void print_test_statistic(TestCtx *ctx, GTestCtx *gctx, Test *test, int final) {
    if (final == 1) {
        if (gctx->test_failed_count != 0) {
            printf(RED "[FAIL] Test Failed (%s) [%d/%d]\n" RESET, filename, test_count - gctx->test_failed_count, test_count);
        } else {
            printf(GREEN "[PASS] Test Passed (%s) [%d/%d]\n" RESET, filename, test_count - gctx->test_failed_count, test_count);
        }

        goto end;
    }

    if (ctx->assertion_err_count != 0) {
        printf(RED "[FAIL] %s:%d (%s) [%d/%d] \n" RESET,
               filename, test->lineno, test->desc, ctx->total_assertions - ctx->assertion_err_count, ctx->total_assertions);
        gctx->test_failed_count += 1;
    } else {
        printf(GREEN "[PASS] %s:%d (%s) [%d/%d] \n" RESET,
               filename, test->lineno, test->desc, ctx->total_assertions - ctx->assertion_err_count, ctx->total_assertions);
    }

end:
    ctx->assertion_err_count = 0;
    ctx->total_assertions = 0;
    return;
}

void run_all_test() {
    if (initialize != 1) {
        printf(RED "[ERROR] Initialize the test first\n" RESET);
        return;
    }

    printf(BLUE "[INFO] Testing %s\n" RESET, filename);
    TestCtx ctx = {0};
    GTestCtx gctx = {0};
    for (int i = 0; i < test_count; i++) {
        all_test[i].fn(&ctx);
        print_test_statistic(&ctx, &gctx, &all_test[i], 0);
    }
    print_test_statistic(&ctx, &gctx, NULL, 1);
    printf("\n");
}

#endif
